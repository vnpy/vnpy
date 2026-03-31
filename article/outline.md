# vnpy.alpha 入门系列文章大纲

## 写作约束（已定）

- **范围**：A 股、指数成分截面、日频（与 `examples/alpha_research` 一致）。
- **数据**：默认读者已会使用 RQData / 迅投等拉数；正文只说明数据需落到 `AlphaLab` 目录及 Notebook 中的典型路径。
- **终点**：信号生成 + 回测；不展开实盘、网关、组合模块对接。
- **读者**：会 Python、略懂量化；`vt_symbol`、`Interval`、`BarData` 等 VeighNa 概念首次出现时简短解释。
- **篇幅**：计划 4–6 篇，按主题分篇，**每篇不超过 3000 字**。

---

## 文风与质量指引（公众号「VeighNa开源量化」）

撰写时与既有推文保持同一语体，便于读者从年度报告、版本说明平滑过渡到本系列。

### 参考篇目（语体与结构）

- [2026年VeighNa项目计划](https://mp.weixin.qq.com/s/gr5fWsPNGMPjrNyOE7iIHA)
- [2025年VeighNa回顾总结](https://mp.weixin.qq.com/s/FxfxzUVTD20LvJrHooh8IQ)
- [VeighNa 发布 v4.3.0](https://mp.weixin.qq.com/s/nw9MYYADO3n1sFh2tp9Whg)

### 既有习惯（归纳）

- **开篇**：先交代背景或与主项目的衔接（版本、年度计划、读者常见痛点），用「因此」「与此同时」等收束到本篇主题；语气正式、可读，避免堆砌口号。
- **结构**：`##` / `###` 层级清楚；技术说明多用 **编号列表**（1. 2. 3.）或 **短横线分点**；长文可用「一、二、」式大段分层（参见年度回顾类文章）。
- **中英混排**：产品名、模块名保留英文（VeighNa、`vnpy.alpha`、`AlphaLab`、`dataset` 等），紧接中文解释；与 VeighNa 官方介绍中 alpha 四段分工保持一致即可。
- **读者导向**：说明「默认读者已具备 XX」与「本篇不展开 XX」；必要时写清与 Notebook、文档的对应关系，降低跳读成本。
- **收尾**：小结 + **明确预告下一篇**；可附文档与论坛链接（见下）；邀请留言按公众号固定栏位自行增删。

### 全系列通用写法

- **统一对外链接**（文末或「扩展阅读」按需出现）：
  - 文档：<https://www.vnpy.com/docs/cn/index.html>
  - 论坛：<https://www.vnpy.com/forum/>
- **术语**：`vt_symbol`、`Interval`、`BarData`、`Segment` 等 VeighNa / alpha 专有名词，**首次出现**用一句话定义或举例（如 `600000.SSE`、`Interval.DAILY`），后文可直呼其名。
- **范围边界**：各篇开头或小结处可重申本系列止于 **回测**、数据默认读者自采、品种为 **A 股指数成分日频**，与营销/实盘内容划界。
- **代码与路径**：文件、类名、Notebook 名用反引号；大段代码少贴，以「与官方 `examples/alpha_research/xxx.ipynb` 某节一致」指代即可，控制篇幅。
- **依赖**：包名级别列举（Polars、sklearn、LightGBM、Alphalens、Plotly、tqdm 等），不写逐步安装教程，除非单篇主题为环境排错。

### 第 1 篇成稿结构参考（供第 2～6 篇类比）

第 1 篇建议章节顺序与字数感（总字数仍须 ≤3000）：

1. **开篇**：为何单独讲 `vnpy.alpha`（与 4.0 / 回顾文衔接）+ 系列范围（A 股指数、日频）+ 本篇任务（架构、四块、环境示例）。
2. **一句话定位**：本地数据 + 因子表 + 模型 + 信号 + 回测；与主程序行情/交易解耦。
3. **四块功能**：`dataset` / `model` / `strategy`+回测 / `AlphaLab`；可给记忆链「数据 → 因子表 → 模型 → 信号 → 回测」。
4. **动手前准备**：Python 3.10+；`vt_symbol`、`Interval` 简释；依赖列名级别。
5. **官方示例地图**：`download_data_rq` / `download_data_xt`；三条 `research_workflow_*`；`research_workflow_alpha101.ipynb`。
6. **小结 + 下一篇预告**：点出第 2 篇主题为 `AlphaLab` 目录与数据就绪自检。

第 2～6 篇建议在篇首用两三句话承接上一篇，篇末用同格式预告下一篇，形成连载阅读节奏。

---

## 总体定位（建议写在第 1 篇开头）

`vnpy.alpha` 提供：本地数据管理 + 因子/标签数据集 + 机器学习模型 + 预测信号 + 回测引擎的完整投研链路。扩展与排错以官方 Notebook 与 `vnpy/alpha` 源码为准。

---

## 第 1 篇：模块是干什么的、你要准备什么

（成稿时章节顺序与字数分配见上文 **「第 1 篇成稿结构参考」**。）

- 一句话定位：`vnpy.alpha` = 本地数据 + 因子表 + 模型 + 信号 + 回测。
- 四块功能：`AlphaLab`、`AlphaDataset`、`AlphaModel`、`BacktestingEngine` + 策略类。
- **环境**：Python 版本与常见依赖（Polars、sklearn、可选 LightGBM、Notebook 中 Alphalens / Plotly 等）— 列名即可。
- **示例地图**：
  - `download_data_rq.ipynb`、`download_data_xt.ipynb`
  - `research_workflow_lasso.ipynb`、`research_workflow_lgb.ipynb`、`research_workflow_mlp.ipynb`
  - `research_workflow_alpha101.ipynb`

---

## 第 2 篇：`AlphaLab` 目录与「数据就绪」检查清单

- `AlphaLab(".../某指数目录")` 创建后的子目录：`daily`、`minute`、`component`、`dataset`、`model`、`signal`、`contract.json`。
- K 线：按 `vt_symbol` 存 parquet；日频为主；`load_bar_df` 与 `load_bar_data` 的差异；`extended_days`、多标的合并、停牌处理（通俗解释「为何需要额外历史窗口」）。
- 成分股：`component` 存储含义；`load_component_symbols`、`load_component_filters` 与后续 `AlphaDataset.prepare_data(filters=...)` 的衔接。
- **合约配置**：`add_contract_setting` / `contract.json` 与回测引擎的关系；缺失时的表现（引擎 warning）。
- **篇末自检**：成分数据是否齐、各标的 parquet 是否存在、`contract.json` 是否配置。

---

## 第 3 篇：`AlphaDataset`：训练 / 验证 / 测试、因子、标签、预处理

- `Segment` 与三段日期区间；数据列约定：`datetime`、`vt_symbol`、特征列、`label`。
- `add_feature`：字符串表达式或 Polars 表达式；`result=` 合并外部因子；`set_label`。
- `prepare_data`（并行计算因子）→ `process_data`：`infer` / `learn` 处理器、`process_type`（如 `append`）。
- 内置处理器：`process_drop_na`、`process_fill_na`、`process_cs_norm`、`process_robust_zscore_norm`、`process_cs_rank_norm` — 各用一句话说明适用场景。
- `Alpha158`、`Alpha101`：作为开箱因子集介绍，不展开每个因子公式。
- **Alphalens**：`show_feature_performance` 属于因子研究视图，与回测收益评价区分，避免读者混淆。

---

## 第 4 篇：`AlphaModel`：训练、预测与 `Segment`

- 抽象接口：`fit(dataset)`、`predict(dataset, segment)`、`detail()`。
- 结合 `LassoModel`：训练常合并 TRAIN + VALID（与实现一致），测试使用 `Segment.TEST`。
- Lasso / LightGBM / MLP：用表格或短列表对比（可解释性、数据量、调参成本），分别对应三份 `research_workflow_*` Notebook。
- `lab.save_model` / `load_model`；各模型 `detail()` 能展示的信息（按实现撰写）。

---

## 第 5 篇：预测信号、信号评价、与回测衔接

- 信号表字段：`datetime`、`vt_symbol`、`signal`。
- `show_signal_performance`：对预测信号做 Alphalens 类分析；与第 3 篇因子评价并列说明差异。
- `save_signal` / `load_signal`。
- `BacktestingEngine`：`set_parameters`、`add_strategy`、传入 `signal_df`；`load_data`、`run_backtesting` 的推荐顺序。
- 不涉及实盘；可一句说明成交与费用假设由回测引擎处理。

---

## 第 6 篇：读懂 `EquityDemoStrategy`、参数与排错

- 从 `on_bars` 读起：取信号 → 排序 → 换仓逻辑（面向基础读者）。
- 参数直觉：`top_k`、`n_drop`、`min_days`、`cash_ratio`、`price_add` 对换手与稳定性的影响。
- `set_target` 与 `execute_trading`：目标仓位与引擎撮合的关系（概念层）。
- 回测结果：日志、净值与图表类输出（撰写时核对 `backtesting.py` 对外方法名）。
- **常见问题**：contract 缺失、某标的无 bar、信号日期与 bar 日期对齐 — 各给一句排查方向。

---

## 若压缩篇数

- **5 篇**：将第 6 篇缩入第 5 篇末尾（策略参数 + 读结果 + 排错），注意控制第 5 篇总字数。
- **4 篇**：通常需牺牲深度；可将「模型 + 信号 + 回测」合并为流程速览篇，或把第 1 篇缩短、环境与示例地图并入第 2 篇开头。

---

## 写作时可引用的代码锚点（内部备忘）

- 公开 API：`vnpy/alpha/__init__.py`
- 实验室与路径：`vnpy/alpha/lab.py`
- 数据集：`vnpy/alpha/dataset/template.py`、`vnpy/alpha/dataset/processor.py`、`vnpy/alpha/dataset/datasets/`
- 模型模板与实现：`vnpy/alpha/model/template.py`、`vnpy/alpha/model/models/`
- 策略与回测：`vnpy/alpha/strategy/template.py`、`vnpy/alpha/strategy/backtesting.py`、`vnpy/alpha/strategy/strategies/equity_demo_strategy.py`
- 示例：`examples/alpha_research/*.ipynb`
