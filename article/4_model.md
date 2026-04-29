# VeighNa多因子入门系列4 - AlphaModel训练与预测

在上一篇里，我们已经进入 `AlphaDataset`，说明了如何从行情面板出发，定义因子和标签，并通过 `prepare_data`、`process_data` 生成模型可以使用的数据表。到这一步，投研链路已经完成了从**原始行情**到**训练样本**的转换。

接下来要回答的问题是：**有了因子表之后，模型如何训练、如何预测，又如何把预测结果交给后续信号和回测环节？**

对于已经会使用 Python 和常见机器学习库的读者来说，这一步通常会关心：

1. `AlphaModel` 统一规定了哪些接口
2. 训练集、验证集、测试集在模型阶段分别怎么用
3. Lasso、LightGBM、MLP 三类示例模型有什么差异
4. 样本内和样本外数据处理的边界在哪里
5. 训练好的模型如何保存、加载和查看细节

因此，本篇进入 **`AlphaModel`**：它负责接收 `AlphaDataset`，在训练区间上拟合模型，并在指定 `Segment` 上输出预测值。可以先将它理解为：**`AlphaModel` 管“如何从因子表得到预测分数”。**

## 统一模型接口

`vnpy.alpha` 中所有模型都继承自 `AlphaModel`。这个抽象类本身很简单，核心就是三个方法：

```python
class AlphaModel:
    def fit(self, dataset: AlphaDataset) -> None:
        ...

    def predict(self, dataset: AlphaDataset, segment: Segment) -> np.ndarray:
        ...

    def detail(self) -> Any:
        ...
```

这三个接口可以按下面方式理解。

- **`fit(dataset)`**：从 `AlphaDataset` 中取出训练相关数据，完成模型拟合。
- **`predict(dataset, segment)`**：对指定区间输出预测结果，返回值是一个 NumPy 数组。
- **`detail()`**：输出或返回模型细节，例如特征系数、特征重要性、训练参数等。

这种设计的好处是，后续流程不需要关心底层到底是线性模型、树模型还是神经网络。只要实现了同一套接口，就可以按类似方式训练、预测和保存。

## Segment 在模型阶段的作用

上一篇介绍过，`AlphaDataset` 会把样本区间划分为三段：

- `Segment.TRAIN`：训练集
- `Segment.VALID`：验证集
- `Segment.TEST`：测试集

到了模型阶段，这三段数据的使用方式会因模型而略有不同，但基本原则是一致的：

1. **训练集**用于学习模型参数。
2. **验证集**用于选择训练轮数、观察过拟合或辅助调参。
3. **测试集**用于样本外预测，通常对应后续信号评价和策略回测。

模型内部并不是直接操作原始行情表，而是通过 `AlphaDataset` 的取数方法拿到对应数据：

```python
train_df = dataset.fetch_learn(Segment.TRAIN)
valid_df = dataset.fetch_learn(Segment.VALID)
test_df = dataset.fetch_infer(Segment.TEST)
```

这里的 `learn` 和 `infer` 与上一篇的预处理流程相对应。训练时通常使用 `learn_df`，因为其中包含标签并且可能做过训练专用清洗；预测时则使用 `infer_df`，因为它代表模型在未来实际推理时能看到的特征表。

也就是说，`Segment` 负责告诉模型“取哪一段时间”，而 `fetch_learn` / `fetch_infer` 负责告诉模型“取训练用表还是预测用表”。

## 样本内外的处理边界

对新手来说，模型阶段最容易混淆的地方，是把训练、验证、测试都当成“已经有历史数据，所以可以随便一起处理”。在量化研究里，这样很容易引入未来信息，让回测结果看起来很好，但真正样本外表现却明显变差。

可以先用一个简单划分来理解：

- **样本内**：通常包括 `Segment.TRAIN` 和会被用于调参、早停、模型选择的 `Segment.VALID`。
- **样本外**：通常指最终只用于预测和评价的 `Segment.TEST`。

这里特别要注意，**验证集不是完全意义上的样本外**。虽然模型参数不一定直接在验证集上训练，但只要我们根据验证集表现调整因子、调参数、选择训练轮数或更换模型，它就已经参与了研究决策。因此，验证集更适合作为样本内的“检查区”，而测试集才应尽量保留为最后观察效果的区域。

在数据处理上，可以记住三条原则。

1. **标签只能用于训练和评估，不能进入预测特征**。例如未来 3 日收益可以作为 `label` 训练模型，但在 `predict(dataset, Segment.TEST)` 时，模型真正使用的应当是当时可见的因子列。
2. **预处理规则不能偷看测试集结果**。如果某些标准化、填充或去极值参数需要从样本中估计，应优先只用训练段或训练+验证段确定，再应用到测试段；不要用完整区间统计量反过来处理测试集。
3. **测试集上的表现不应反复用来调模型**。如果每次看完测试集收益后都回头改因子、改参数，再继续用同一测试集比较，测试集也会逐渐变成“被研究过的数据”。

`AlphaDataset` 中的 `learn_df` / `infer_df` 正是为了帮助区分这两类用途：训练时从 `learn_df` 取含标签、经过训练清洗的数据；预测时从 `infer_df` 取推理阶段能看到的特征数据。写自己的处理器时，也应尽量保持这个边界，避免把只在训练阶段才知道的信息混入预测流程。

## 从训练到预测

一个典型的模型使用流程可以写成下面这样：

```python
from vnpy.alpha import Segment
from vnpy.alpha.model.models.lasso_model import LassoModel

model = LassoModel(alpha=0.0005)
model.fit(dataset)

pred = model.predict(dataset, Segment.TEST)
```

这里的 `pred` 是一个一维数组，顺序与 `dataset.fetch_infer(Segment.TEST)` 按 `datetime`、`vt_symbol` 排序后的行顺序对应。换句话说，每一个预测值都对应某一天、某一只股票的一行特征数据。

因此，在后续生成信号表时，通常需要从同一段 `infer_df` 中取出 `datetime` 和 `vt_symbol`，再把预测数组作为 `signal` 列合并进去。这个环节会在下一篇详细展开。

需要特别注意的是：**模型预测值本身还不是交易指令。** 它只是一个横截面上的分数或收益预测，后面还要经过信号保存、排序选股、换仓规则和回测引擎，才会变成实际组合表现。

## 三类示例模型

当前示例中，比较典型的模型包括 `LassoModel`、`LgbModel` 和 `MlpModel`。它们都遵守 `AlphaModel` 接口，但训练方式和适用场景不同。

| 模型 | 特点 | 适合入门时关注 |
|------|------|----------------|
| `LassoModel` | 线性模型，带 L1 正则，部分特征系数会被压到 0 | 可解释性、线性基线、特征筛选 |
| `LgbModel` | LightGBM 梯度提升树，适合表格数据 | 非线性关系、强基线、特征重要性 |
| `MlpModel` | PyTorch 多层感知机 | 神经网络流程、批量训练、设备和早停 |

### LassoModel

`LassoModel` 是最容易理解的起点。它会从 `AlphaDataset` 中取出 `Segment.TRAIN` 和 `Segment.VALID`，合并后作为训练样本，再用 `label` 作为目标拟合线性回归模型。

这种做法的重点不是追求复杂度，而是快速得到一个可解释的线性基线。训练完成后，`detail()` 会输出非零系数对应的特征，并按系数绝对值排序。对于初学者来说，这有助于观察哪些因子在当前样本中被模型保留下来。

需要注意的是，Lasso 的系数解释依赖于特征尺度。如果不同因子的量纲差异很大，建议结合上一篇的标准化处理器一起使用。

### LgbModel

`LgbModel` 使用 LightGBM 训练梯度提升树。它会分别取出 `Segment.TRAIN` 和 `Segment.VALID`，把训练集作为主训练数据，把验证集作为 `valid_sets` 传入 LightGBM。

这意味着验证集会参与早停判断：如果验证集效果在设定轮数内不再改善，训练会提前停止。与 Lasso 相比，LightGBM 更擅长处理非线性关系和特征交互，也是表格数据任务中常见的强基线。

训练完成后，`detail()` 会绘制两类特征重要性：

- `split`：特征被用于分裂的次数
- `gain`：特征带来的增益贡献

二者视角不同，通常可以结合观察，而不必只看其中一个排序。

### MlpModel

`MlpModel` 使用 PyTorch 实现多层感知机。相比前两类模型，它的参数更多，包括输入维度、隐藏层大小、学习率、训练轮数、批大小、优化器、训练设备等。

它同样会使用 `Segment.TRAIN` 和 `Segment.VALID`：训练集用于批量更新网络参数，验证集用于观察损失变化和早停。若验证集损失长期没有改善，训练会提前结束，并保留表现较好的参数。

使用 MLP 时要额外注意两点：

1. 构造模型时需要传入 `input_size`，通常应与因子列数量一致。
2. 神经网络对特征尺度更敏感，建议先在 `AlphaDataset` 阶段完成稳定的缺失值处理和标准化。

训练完成后，`detail()` 会输出输入维度、隐藏层大小、参数量、设备等信息，并返回一个基于扰动方式估算的特征重要性表。

## 保存和加载模型

模型训练完成后，可以通过 `AlphaLab` 保存到研究目录中的 `model/` 子目录：

```python
lab.save_model("lasso_demo", model)
```

保存文件为 `model/lasso_demo.pkl`。后续需要复用时，可以再加载回来：

```python
model = lab.load_model("lasso_demo")
```

这一点在研究过程中很实用。比如一次完整训练可能需要较长时间，训练完成后保存模型，后面就可以直接加载并重新预测、生成信号或对比回测结果，而不必每次都从头训练。

不过也要注意，模型文件通常和当时使用的因子列、预处理方式、训练区间强相关。若之后修改了 `AlphaDataset` 的因子定义或预处理流程，应当重新训练模型，而不是直接复用旧模型。

## detail不是统一报表

`detail()` 是一个统一入口，但不同模型给出的内容并不完全相同：

- `LassoModel.detail()` 输出非零特征系数，适合观察线性模型保留了哪些因子。
- `LgbModel.detail()` 绘制 LightGBM 特征重要性图，适合查看树模型的分裂和增益贡献。
- `MlpModel.detail()` 输出网络结构、参数量、训练设备，并返回特征重要性估计表。

因此，`detail()` 更像是“查看当前模型内部状态”的入口，而不是一个跨模型完全可比的绩效报表。模型好不好，最终仍然要结合验证集表现、预测信号分析，以及后续策略回测一起判断。

## 小结

这一篇的重点，是把 `AlphaModel` 在投研链路中的位置讲清楚：它从 `AlphaDataset` 中按 `Segment` 取数，通过 `fit(dataset)` 完成训练，再通过 `predict(dataset, segment)` 输出指定区间的预测值。

可以先记住这条顺序：

**处理后的因子表 -> `fit(dataset)` 训练模型 -> `predict(dataset, Segment.TEST)` 输出预测分数 -> 保存模型并进入信号环节**

到这里，我们已经把因子表变成了模型预测值。**下一篇**将进入预测信号与回测衔接：信号表需要哪些字段，如何用 `save_signal` / `load_signal` 管理结果，`show_signal_performance` 与因子评价有什么不同，以及 `BacktestingEngine` 如何接收信号并完成历史回测。
