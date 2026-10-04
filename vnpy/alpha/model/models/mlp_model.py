"""
Multi-layer perceptron model for alpha factor prediction.
"""

import copy
from collections import defaultdict
from collections.abc import Callable
from typing import Literal, cast

import numpy as np
import pandas as pd
import polars as pl
from sklearn.metrics import mean_squared_error      # type: ignore
import torch
import torch.nn as nn
import torch.optim as optim

from vnpy.alpha import (
    AlphaDataset,
    AlphaModel,
    Segment,
    logger
)



class MlpModel(AlphaModel):
    """
    Multi-Layer Perceptron Model

    Alpha factor prediction model implemented using multi-layer perceptron, with main features including:
    1. Building and training multi-layer perceptron neural networks
    2. Predicting Alpha factor values
    3. Model evaluation and feature importance analysis
    4. Support for early stopping and overfitting prevention
    5. Support for MSE loss function
    6. Optional Adam or SGD optimizer
    """

    def __init__(
        self,
        input_size: int,
        hidden_sizes: tuple[int] = (256,),
        lr: float = 0.001,
        n_epochs: int = 300,
        batch_size: int = 2000,
        early_stop_rounds: int = 50,
        eval_steps: int = 20,
        optimizer: Literal["sgd", "adam"] = "adam",
        weight_decay: float = 0.0,
        device: str = "cpu",
        seed: int | None = None
    ) -> None:
        """
        Initialize the network on the given device, accepting only adam or sgd, and seed NumPy and PyTorch when a seed is provided.
        """
        # Save model hyperparameters
        self.input_size: int = input_size
        self.hidden_sizes: tuple[int] = hidden_sizes
        self.lr: float = lr
        self.n_epochs: int = n_epochs
        self.batch_size: int = batch_size
        self.early_stop_rounds: int = early_stop_rounds
        self.eval_steps: int = eval_steps
        self.device: str = device
        self.fitted: bool = False
        self.feature_names: list[str] = []
        self.best_step: int | None = None

        # Set random seed for reproducibility
        if seed is not None:
            np.random.seed(seed)
            torch.manual_seed(seed)

        # Set loss function type
        self._scorer: Callable[..., float] = mean_squared_error

        # Initialize model
        self.model: nn.Module = MlpNetwork(
            input_size=input_size,
            hidden_sizes=hidden_sizes,
        )

        # Move model to specified device
        self.model = self.model.to(device)

        # Set optimizer
        optimizer_name: str = optimizer.lower()
        if optimizer_name == "adam":
            self.optimizer: optim.Optimizer = optim.Adam(
                self.model.parameters(),
                lr=lr,
                weight_decay=weight_decay
            )
        elif optimizer_name == "sgd":
            self.optimizer = optim.SGD(
                self.model.parameters(),
                lr=lr,
                weight_decay=weight_decay
            )
        else:
            raise NotImplementedError(f"optimizer {optimizer} is not supported!")

        # Set learning rate scheduler
        self.scheduler: optim.lr_scheduler.ReduceLROnPlateau = optim.lr_scheduler.ReduceLROnPlateau(
            self.optimizer,
            mode="min",
            factor=0.5,
            patience=10,
            threshold=0.0001,
            threshold_mode="rel",
            cooldown=0,
            min_lr=0.00001,
            eps=1e-08,
        )

    def fit(
        self,
        dataset: AlphaDataset,
        evaluation_results: dict | None = None,
    ) -> None:
        """
        Train with periodic validation and early stopping, and append segment losses to evaluation_results when it is provided.
        """
        # Initialize a new dictionary if evaluation_results is None
        if evaluation_results is None:
            evaluation_results = {}

        # Dictionary to store training and validation data
        train_valid_data: dict[str, dict] = defaultdict(dict)

        # Process training and validation sets separately
        segment: Segment
        for segment in [Segment.TRAIN, Segment.VALID]:
            # Get learning data and sort by time and trading code
            df: pl.DataFrame = dataset.fetch_learn(segment)
            df = df.sort(["datetime", "vt_symbol"])

            # Extract features and labels
            features: np.ndarray = df.select(df.columns[2: -1]).to_numpy()
            labels: np.ndarray = np.array(df["label"])

            # Store feature and label data
            train_valid_data["x"][segment] = torch.from_numpy(features).float().to(self.device)
            train_valid_data["y"][segment] = torch.from_numpy(labels).float().to(self.device)

            # Initialize evaluation results list
            evaluation_results[segment] = []

        # Get feature names
        df = dataset.fetch_learn(Segment.TRAIN)
        self.feature_names = df.columns[2:-1]

        # Initialize training state
        early_stop_count: int = 0           # Number of steps without performance improvement
        train_loss: float = 0               # Current training loss
        best_valid_score: float = np.inf    # Best validation loss
        best_params: dict[str, torch.Tensor] | None = None                  # Best model parameters

        train_samples: int = train_valid_data["y"][Segment.TRAIN].shape[0]

        # Iterate through training steps
        step: int
        for step in range(1, self.n_epochs + 1):
            # Check if early stopping condition is met
            if early_stop_count >= self.early_stop_rounds:
                logger.info("达到早停条件,训练结束")
                break

            # Train one batch
            batch_loss: float = self._train_step(train_valid_data, train_samples)
            train_loss += batch_loss

            # Periodically evaluate the model
            if step % self.eval_steps == 0 or step == self.n_epochs:
                early_stop_count, best_valid_score, best_params = self._evaluate_step(
                    train_valid_data,
                    evaluation_results,
                    step,
                    train_loss,
                    early_stop_count,
                    best_valid_score
                )
                train_loss = 0

        # Mark model as trained
        self.fitted = True

        # Load best model parameters
        if best_params:
            self.model.load_state_dict(best_params)

    def _train_step(
        self,
        train_valid_data: dict[str, dict[Segment, torch.Tensor]],
        train_samples: int
    ) -> float:
        """
        Run one optimization step on a random training batch and return that batch loss.
        """
        batch_loss: AverageMeter = AverageMeter()
        self.model.train()
        self.optimizer.zero_grad()

        # Randomly select batch data
        batch_indices: np.ndarray = np.random.choice(train_samples, self.batch_size)
        batch_features: torch.Tensor = train_valid_data["x"][Segment.TRAIN][batch_indices]
        batch_labels: torch.Tensor = train_valid_data["y"][Segment.TRAIN][batch_indices]

        # Forward and backward propagation
        predictions: torch.Tensor = self.model(batch_features)
        cur_loss: torch.Tensor = self._loss_fn(predictions, batch_labels)
        cur_loss.backward()

        # Update model parameters
        self.optimizer.step()
        batch_loss.update(cur_loss.item())

        return batch_loss.val

    def _evaluate_step(
        self,
        train_valid_data: dict[str, dict[Segment, torch.Tensor]],
        evaluation_results: dict[Segment, list[float]],
        step: int,
        train_loss: float,
        early_stop_count: int,
        best_valid_score: float
    ) -> tuple[int, float, dict[str, torch.Tensor] | None]:
        """
        Score validation, reset the early-stop count when loss improves, and return that count, the best loss, and the new state dict if it improved.
        """
        early_stop_count += 1
        train_loss /= self.eval_steps

        # Evaluate model on validation set
        with torch.no_grad():
            self.model.eval()

            data: torch.Tensor = train_valid_data["x"][Segment.VALID]
            pred: torch.Tensor = cast(torch.Tensor, self._predict_batch(data, return_cpu=False))
            valid_loss: torch.Tensor = self._loss_fn(pred, train_valid_data["y"][Segment.VALID])

            loss_val: float = valid_loss.item()

        # Record evaluation results
        logger.info(f"[Step {step}]: train_loss {train_loss:.6f}, valid_loss {loss_val:.6f}")
        evaluation_results[Segment.TRAIN].append(train_loss)
        evaluation_results[Segment.VALID].append(loss_val)

        # Update best model if validation performance improves
        best_params: dict[str, torch.Tensor] | None = None
        if loss_val < best_valid_score:
            logger.info(f"\t验证集损失从 {best_valid_score:.6f} 降低到 {loss_val:.6f}")
            best_valid_score = loss_val
            self.best_step = step
            early_stop_count = 0
            best_params = copy.deepcopy(self.model.state_dict())

        # Update learning rate
        if self.scheduler is not None:
            self.scheduler.step(metrics=valid_loss, epoch=step)

        return early_stop_count, best_valid_score, best_params

    def _loss_fn(self, pred: torch.Tensor, target: torch.Tensor) -> torch.Tensor:
        """
        Compute mean squared error after flattening predictions and targets.
        """
        pred, target = pred.reshape(-1), target.reshape(-1)
        loss: torch.Tensor = nn.MSELoss()(pred, target)
        return loss

    def _predict_batch(self, data: torch.Tensor, return_cpu: bool = True) -> np.ndarray | torch.Tensor:
        """
        Predict in batches of 8096 and return a NumPy array, or a tensor when return_cpu is false.
        """
        data = data.to(self.device)

        predictions: list[torch.Tensor] = []

        self.model.eval()

        with torch.no_grad():
            batch_size: int = 8096
            i: int
            for i in range(0, len(data), batch_size):
                x: torch.Tensor = data[i: i + batch_size]
                predictions.append(self.model(x.to(self.device)).detach().reshape(-1))

        if return_cpu:
            return np.concatenate([pr.cpu().numpy() for pr in predictions])
        else:
            return torch.cat(predictions, dim=0)

    def predict(self, dataset: AlphaDataset, segment: Segment) -> np.ndarray:
        """
        Predict one dataset segment, or raise ValueError if the model has not been trained.
        """
        if not self.fitted:
            raise ValueError("Model has not been trained yet!")

        df: pl.DataFrame = dataset.fetch_infer(segment)
        df = df.sort(["datetime", "vt_symbol"])

        data: np.ndarray = df.select(df.columns[2: -1]).to_numpy()

        return cast(np.ndarray, self._predict_batch(torch.Tensor(data)))

    def _check_tensor_nan(self, tensor: torch.Tensor, name: str) -> None:
        """
        Print a message when the tensor contains any NaN values.
        """
        if torch.isnan(tensor).any():
            print(f"NaN values detected: {name}")

    def detail(self) -> pd.DataFrame | None:
        """
        Log the model configuration and return feature importance, or None when the model is not trained.
        """
        if not self.fitted:
            logger.info("模型尚未训练，无法显示详细信息")
            return None

        # 显示模型基本信息
        logger.info(f"输入特征维度: {self.input_size}")
        logger.info(f"隐藏层大小: {self.hidden_sizes}")

        # 计算模型总参数量
        total_params: int = sum(p.numel() for p in self.model.parameters())
        logger.info(f"模型总参数量: {total_params:,}")

        # 显示训练状态信息
        logger.info(f"训练设备: {self.device}")
        logger.info(f"当前学习率: {self.lr}")
        logger.info(f"批次大小: {self.batch_size}")

        # Calculate feature importance
        importance_df: pd.DataFrame = self._calculate_feature_importance()
        return importance_df

    def _calculate_feature_importance(self) -> pd.DataFrame:
        """
        Estimate importance from how much predictions move when each input feature is perturbed.
        """
        self.model.eval()
        importance_dict: dict[str, float] = {}

        test_data: torch.Tensor = torch.randn(1000, self.input_size).to(self.device)
        base_pred: torch.Tensor = self.model(test_data).detach()

        noise_level: float = 0.1
        i: int
        feature_name: str
        for i, feature_name in enumerate(self.feature_names):
            perturbed_data: torch.Tensor = test_data.clone()
            perturbed_data[:, i] += torch.randn(1000).to(self.device) * noise_level

            with torch.no_grad():
                new_pred: torch.Tensor = self.model(perturbed_data)
                importance: float = torch.std(torch.abs(new_pred - base_pred)).item()
                importance_dict[feature_name] = importance

        df: pd.DataFrame = pd.DataFrame({
            "Feature": list(importance_dict.keys()),
            "Importance": list(importance_dict.values())
        })
        df = df.sort_values("Importance", ascending=False)
        df = df.set_index("Feature")

        return df


class AverageMeter:
    """
    Track the latest value together with its running sum, count, and average.
    """

    def __init__(self) -> None:
        """
        Start the meter with every statistic set to zero.
        """
        self.reset()

    def reset(self) -> None:
        """
        Clear the current value, sum, count, and average.
        """
        self.val: float = 0
        self.avg: float = 0
        self.sum: float = 0
        self.count: int = 0

    def update(self, val: float, n: int = 1) -> None:
        """
        Record a value weighted by n and refresh the running average.
        """
        self.val = val
        self.sum += val * n
        self.count += n
        self.avg = self.sum / self.count


class MlpNetwork(nn.Module):
    """
    Multilayer perceptron of dropout, linear, batch-norm, and activation layers.
    """

    def __init__(
        self,
        input_size: int,
        output_size: int = 1,
        hidden_sizes: tuple[int] = (256,),
        activation: str = "LeakyReLU"
    ) -> None:
        """
        Build hidden layers of linear, batch norm, and LeakyReLU or SiLU, with 0.05 dropout at the input and before the output. Any other activation name raises ValueError.
        """
        super().__init__()

        # Build network layers
        layers: list[nn.Module] = []
        layer_sizes: list[int] = [input_size] + list(hidden_sizes)

        # Input layer Dropout
        layers.append(nn.Dropout(0.05))

        # Build hidden layers
        in_size: int
        out_size: int
        for in_size, out_size in zip(layer_sizes[:-1], layer_sizes[1:], strict=False):
            # Add a neural network block: linear layer + batch normalization + activation function
            layers.extend([
                nn.Linear(in_size, out_size),
                nn.BatchNorm1d(out_size),
                self._get_activation(activation)
            ])

        # Output layer
        layers.extend([
            nn.Dropout(0.05),
            nn.Linear(hidden_sizes[-1], output_size)
        ])

        # Combine all layers into a sequence
        self.network: nn.ModuleList = nn.ModuleList(layers)

        # Initialize network weights
        self._initialize_weights()

    def _get_activation(self, name: str) -> nn.Module:
        """
        Return LeakyReLU with negative slope 0.1 or SiLU, or raise ValueError for any other name.
        """
        if name == "LeakyReLU":
            return nn.LeakyReLU(negative_slope=0.1)
        elif name == "SiLU":
            return nn.SiLU()
        else:
            raise ValueError(f"Unsupported activation function type: {name}")

    def _initialize_weights(self) -> None:
        """
        Apply Kaiming normal initialization to every linear layer using leaky ReLU.
        """
        module: nn.Module
        for module in self.modules():
            if isinstance(module, nn.Linear):
                nn.init.kaiming_normal_(
                    module.weight,
                    a=0.1,                  # LeakyReLU negative slope
                    mode="fan_in",          # Scale using input node count
                    nonlinearity="leaky_relu"
                )

    def forward(self, x: torch.Tensor) -> torch.Tensor:
        """
        Pass the input through each network layer in order.
        """
        # Pass through all layers in the network sequentially
        layer: nn.Module
        for layer in self.network:
            x = layer(x)
        return x
