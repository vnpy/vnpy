# VeighNa多因子入门系列3 - AlphaDataset特征与标签构建

在上一篇里，我们重点说明了 `AlphaLab` 的目录结构，以及日频 K 线、指数成分和 `contract.json` 怎样准备齐全。

到这一步，研究所需的本地数据已经有了稳定来源：行情可以通过 `load_bar_df` 读成表格，指数成分也可以通过 `load_component_filters` 约束样本范围。

接下来要解决的问题是：**怎样把这些原始行情数据，变成模型可以训练和预测的因子表？**

已经会写 Python、也接触过一些因子研究的读者，这一步通常会关注：

1. 训练、验证、测试三段时间如何定义
2. 因子列和标签列在表里应该如何组织
3. 缺失值、标准化、去极值等预处理放在哪一步完成
4. 内置的 Alpha 158、Alpha 101 因子集应该怎样理解

本篇进入 **`AlphaDataset`**：它负责把多标的行情面板整理成因子、标签和样本区间，并在模型训练前完成必要的数据预处理。可以先将它理解为：**`AlphaDataset` 管“模型要学什么、从哪段数据学、用哪段数据检验”。**

## 从行情面板到数据集

在官方工作流中，通常会先从 `AlphaLab` 读取指数成分对应的日频行情，并得到一个 Polars DataFrame。这个表至少会包含：

- `datetime`：交易日期
- `vt_symbol`：标的编码，例如 `600000.SSE`
- `open`、`high`、`low`、`close`、`volume`、`turnover`、`vwap` 等行情字段

随后将这个表传入 `AlphaDataset`，并同时指定训练、验证、测试三段时间：

```python
from vnpy.alpha import AlphaDataset

dataset = AlphaDataset(
    df=df,
    train_period=("2008-01-01", "2018-12-31"),
    valid_period=("2019-01-01", "2020-12-31"),
    test_period=("2021-01-01", "2023-12-31"),
)
```

这里的三段时间由 **`Segment`** 统一表示。`Segment.TRAIN` 表示训练集，`Segment.VALID` 表示验证集，`Segment.TEST` 表示测试集。后续模型训练、预测和结果检查时，都会围绕这三个区间取数。

`AlphaDataset` 构造完成时，还只是保存原始行情表、三段日期区间，以及后续要用到的因子表达式、标签表达式和预处理器。因子和标签的实际计算，会在后面的 `prepare_data` 和 `process_data` 中完成。

## 因子与标签

`AlphaDataset` 中最常用的两个入口是 `add_feature` 和 `set_label`。

**因子**可以理解为模型的输入特征。例如过去 5 日收益、均线偏离、成交量变化、截面排名等，都可以作为特征列加入数据集：

```python
dataset.add_feature("roc_5", "ts_delay(close, 5) / close")
dataset.add_feature("ma_20", "ts_mean(close, 20) / close")
```

这里的字符串表达式会在 `vnpy.alpha` 提供的时序函数、截面函数和数学函数环境里执行。常见前缀可以按直觉理解：

- `ts_`：时间序列方向的计算，例如滚动均值、延迟、相关系数
- `cs_`：同一交易日截面方向的计算，例如截面排名、截面标准化
- `ta_`：部分常用技术指标

除了字符串表达式，`add_feature` 也可以接收 Polars 表达式，适合直接使用 Polars 原生写法的场景。

对于已经在外部算好的因子，也可以通过 `result=` 传入一个包含 `datetime`、`vt_symbol` 和因子值的结果表，`prepare_data` 时会按日期和标的合并。

**标签**则是模型要学习的目标，通常表示未来一段时间的收益或排序目标。例如内置 `Alpha158` 中的标签写法是：

```python
dataset.set_label("ts_delay(close, -3) / ts_delay(close, -1) - 1")
```

它表达的是一个向未来看的收益目标。实际研究时，标签的定义要和后续持仓周期、调仓频率保持一致；如果标签和策略持有逻辑完全脱节，模型训练出来的预测值就很难直接转化为可解释的交易信号。

## prepare_data：计算并合并

因子和标签定义好之后，下一步调用 `prepare_data`：

```python
filters = lab.load_component_filters(index_symbol, start, end)
dataset.prepare_data(filters=filters, max_workers=6)
```

这一阶段主要完成三件事。

1. **并行计算表达式因子**：`add_feature` 中登记的字符串表达式或 Polars 表达式，会被批量计算成新的因子列；如果设置了 `label`，标签列也会在这一步生成。
2. **合并外部因子结果**：通过 `result=` 传入的外部因子，会按 `datetime` 和 `vt_symbol` 左连接到结果表中。
3. **按指数成分过滤样本**：若传入 `filters`，则只保留某只股票在指数成分存续区间内的样本，避免把非成分期的数据混入研究池。

可以把 `prepare_data` 理解为：**把“怎么计算”落实成一张原始因子与标签表。**

完成后，`AlphaDataset` 内部会形成 `raw_df`。它保留 `datetime`、`vt_symbol`，以及新计算出来的因子列和 `label`。这张表处在预处理之前，适合用来检查因子是否算出来、列名是否正确、缺失值是否集中在预期窗口。

## process_data：生成训练与预测用表

`prepare_data` 之后，还需要调用 `process_data` 完成预处理：

```python
dataset.process_data()
```

这里要理解 `AlphaDataset` 中的两条数据链：

- **`infer_df`**：用于预测或推理的数据
- **`learn_df`**：用于训练和验证的数据

二者最初都来自 `raw_df`，但可以挂不同的处理器。通过 `add_processor("infer", processor)` 添加的是预测链处理器；通过 `add_processor("learn", processor)` 添加的是训练链处理器。

默认 `process_type="append"` 时，`AlphaDataset` 会先按 `infer` 处理器生成 `infer_df`，再把它作为 `learn_df` 的起点，继续执行 `learn` 处理器。这样做的直觉是：**训练和预测都需要一致的特征处理，但训练阶段可能还要额外处理标签或删除无效样本。**

例如，一个常见思路是：

1. 在 `infer` 阶段对特征做标准化或缺失值填充，保证未来预测时也能使用同样流程
2. 在 `learn` 阶段删除标签缺失的行，避免模型训练时读到无效目标

后续模型会通过 `fetch_learn(Segment.TRAIN)`、`fetch_learn(Segment.VALID)` 或 `fetch_infer(Segment.TEST)` 等方法，按指定区间取出对应数据。

## 常用内置处理器

`vnpy.alpha` 在 `dataset.processor` 中提供了一些常见预处理函数，入门阶段不需要记住所有参数，但建议先理解它们各自解决什么问题。

- **`process_drop_na`**：删除指定列存在缺失值的样本，常用于训练前剔除无效因子或标签。
- **`process_fill_na`**：用固定值填充缺失值，适合希望保留样本行、同时让模型能够继续训练或预测的场景。
- **`process_cs_norm`**：按交易日做截面标准化，可选择普通 z-score 或 robust 方法，用于缓和不同因子量纲差异。
- **`process_robust_zscore_norm`**：基于中位数和 MAD 做稳健标准化，并可对极端值截断，适合异常值较多的因子表。
- **`process_cs_rank_norm`**：按交易日做截面排名归一化，适合以相对排序为主要信息的因子。

处理器的选择要服务于模型类型和因子含义。例如线性模型通常更依赖特征尺度稳定，树模型对单调变换相对不敏感，但仍可能受缺失值和异常值影响。

## 开箱因子集

除了手工添加因子，`vnpy.alpha` 还内置了两个常见因子集：

- **`Alpha158`**：参考 Qlib 的基础因子集合，包含 K 线形态、收益变化、均线、波动、量价关系等特征。
- **`Alpha101`**：参考 WorldQuant Alpha 101，包含大量时序与截面组合表达式。

它们提供了一套可直接运行的基线。第一次跑通流程时，可以先用内置因子集完成从数据集、模型、信号到回测的闭环；等确认流程没有问题后，再逐步替换为自己的因子。

这些因子集仍然遵守 `AlphaDataset` 的同一套机制：本质上都是在构造函数里批量调用 `add_feature`，并设置对应的 `label`。理解了 `AlphaDataset` 的基本流程，也就能顺着看懂内置因子集如何接入后续模型。

## 因子分析与回测评价

`AlphaDataset` 还提供了 `show_feature_performance(name)`，用于查看某个因子的表现。它会基于 Alphalens 生成因子分层、前向收益等分析视图。

这里要特别区分两个概念：

- **因子分析**：关注单个因子或特征在截面上的排序能力，例如高分组和低分组未来收益是否有差异。
- **策略回测**：关注模型信号经过组合构建、换仓、费用和撮合之后，最终形成的净值、回撤和交易表现。

`show_feature_performance` 适合回答“这个因子本身有没有研究价值”；后续回测则关注“把信号变成持仓之后，策略整体表现如何”。二者相关，评价视角各不相同。

## 小结

这一篇的重点，是把 `AlphaDataset` 在整个投研链路中的位置讲清楚：它接收 `AlphaLab` 读出的行情面板，通过 `add_feature` 和 `set_label` 定义因子与标签，再通过 `prepare_data` 计算原始结果，通过 `process_data` 生成训练和预测所需的数据表。

这条顺序可以作为本篇的主线：

**行情面板 -> 因子和标签定义 -> `prepare_data` 计算合并 -> `process_data` 预处理 -> 按 `Segment` 取数**

到这里，我们已经有了一张模型可以使用的因子表。**下一篇**将进入 **`AlphaModel`**：模型接口如何设计，`fit(dataset)` 与 `predict(dataset, segment)` 分别做什么，Lasso、LightGBM、MLP 三类示例模型各适合怎样的入门场景，以及训练好的模型如何保存和加载。
