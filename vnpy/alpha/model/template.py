from abc import ABCMeta, abstractmethod

import numpy as np

from vnpy.alpha.dataset import AlphaDataset, Segment


class AlphaModel(metaclass=ABCMeta):
    """Template class for machine learning algorithms"""

    @abstractmethod
    def fit(self, dataset: AlphaDataset) -> None:
        """
        Fit the model with dataset
        """
        pass

    @abstractmethod
    def predict(self, dataset: AlphaDataset, segment: Segment) -> np.ndarray:
        """
        Make predictions using the model
        """
        pass

    def detail(self) -> None:
        """
        Output detailed information about the model
        """
        return
