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
- **范围边界**：各篇开头或小结处可重申本系列止于 **回测**、数据默认读者自采、品种为 **A 股指数成分日频**，与营销/实盘内容划界；每篇须有一句「本篇不展开什么」。
- **代码与路径**：文件、类名、Notebook 名用反引号；大段代码少贴，以「与官方 `examples/alpha_research/xxx.ipynb` 某节一致」指代即可，控制篇幅。
- **依赖**：包名级别列举（Polars、sklearn、LightGBM、Alphalens、Plotly、tqdm 等），不写逐步安装教程，除非单篇主题为环境排错。
- **人称**：公众号为公司账号，第一人称统一用「我们」（团队/社区视角），不使用单数「我」作者自称；读者内心独白中的「我」不受此限。
- **篇末**：小结（3～5 条）+ 下一篇预告（一句话说清下篇解决什么问题）；系列内前后篇预告用词与后篇开篇/标题口径保持一致。

### 反「AI 味」与用语规范（全系列强制）

读者对模板化句式、过度工整结构、空洞强调反感强烈。以下配额与用语要求纳入篇末验收；`article/fusion` 通关系列亦按同一套执行（Fusion 另有产品演示 80/20 等专项规则，见该系列大纲）。

#### 1. 句式配额（每篇硬性限制）

- 「不是 X，而是 Y」及其变体（「并非…而是…」「不在于…而在于…」「而不是…」作对照收束）：**全篇不超过 1 处**；「而非」视为同类硬拐，优先改成「跟…不是一回事」「…是另一回事」等自然说法。
- 「值得注意的是」「需要强调的是」「更重要的是」「换句话说」「综上所述」：**禁用**（可用「更关键的是下一步」等指向具体动作的说法，且慎用）。
- 「真正的 X」「X 的本质」「底层逻辑」：全篇不超过 1 处。
- 三项并列排比（「更快、更稳、更省心」式）：全篇不超过 2 处；对照表已承担选型/对比功能时，不要再叠一句三项口诀。
- 自问自答（「为什么？因为…」）：全篇不超过 2 处。
- 相邻两段不得都以连接词（然而 / 此外 / 同时 / 事实上）开头。

#### 2. 排版与强调

- **加粗 ≤5 处**：只留给钩子句和关键认知，不用于普通强调；同一交付物名称（如「策略逻辑说明书」）不要反复加粗占额度。
- **钩子句**：每篇宜有一句可单独转发的观点，用引用块（`>`）放在开篇显著位置；加粗可以只包钩子，不必再给同义句二次加粗。
- **列表**：知识讲解默认用叙述段落；列表仅用于真正可枚举的步骤与清单；两个列表之间至少隔一段叙述（表格、配图、提示框不受此限）。
- **单段 ≤150 字**（手机端约 4 行），长段必须拆分；「一是 / 二是」若单段压线，拆成两段。
- 不强制每节末小结，只在篇末统一小结；避免各节长度过分均匀的「对称感」。
- 金句与硬纪律可用引用块呈现，作为加粗之外的强调手段。
- **大纲本文是规格书风格**（列表与加粗密集），正文不得照搬这种排版。

#### 3. 用语自然（朗读时别扭的优先改）

意思对但读着紧、文白夹杂、程序员黑话过重时，按下列方向改（示例，不限于此）：

| 宜避免 | 优先改为 |
|--------|----------|
| 译成 | 翻译成 |
| 而非… | 跟…不是一回事 / …是另一回事 |
| 写死（规则/参数） | 写清楚 / 固定 |
| 动手（下单义） | 下单 |
| 逼到纸面上 | 落到纸面上 |
| 改到可执行 | 改成可以执行的表述 |
| 归拢起来 | 归纳成 |
| 闭合（规则齐备义） | 完整 |
| 粒度（行情粗细） | 更细行情 / 说清「决策频率」即可 |
| 为锚 | 为基准 |
| 则相反 | 正好反过来 |

- 系列内**同一概念用同一说法**（如「真实交易过的那张合约」），后篇小结不要换回近义旧词造成口径分裂。
- 给执笔看的生产纪律（「以实跑产物为准」「截图打码」等）放在 HTML 注释 `<!-- -->`，**不要写进读者可见正文或长括号**。

#### 4. 活人感（每篇至少两条）

- 用真实运行/答疑细节：具体报错、耗时、第一次踩坑、Notebook 里实际对不上的地方。
- 至少一处「我们在…」式团队经历或判断；**禁止为叙事虚构**未发生的 Agent/回测细节。
- 用具体数字和对象，删除「某些情况下」「很多时候」等无信息量表述。
- 允许承认边界与不确定；正式语体 + 有细节，好过油滑空洞。

#### 5. AI 使用与发布前

- 允许用 AI 做资料核对、事实检查、结构草稿。
- 正文成稿必须人工逐段重写，禁止 AI 段落直接进稿。
- 发布前做**朗读测试**：读起来不像自己说话的句子必须改。
- 回测绩效类表述：无收益承诺/暗示；涉及回测截图时注明「历史回测结果不代表未来表现」。

### 篇末验收清单（发布前勾选）

1. 单篇 ≤3000 字（不含代码块与图注）；有「本篇不展开」边界。
2. 开篇承接上一篇；篇末小结 + 下一篇预告；系列内用词与前后篇对齐。
3. 术语首次出现有一句话解释；第一人称统一为「我们」。
4. 「不是…而是…」类 ≤1 处；禁用套话未出现；三项排比 ≤2；加粗 ≤5；单段 ≤150 字。
5. 列表使用符合「可枚举才列表、列表间有叙述」；无各节对称小结堆砌。
6. 用语已过朗读测试；无「译成 / 而非 / 写死」等别扭压缩词残留（对照上表）。
7. 活人感 ≥2 处且来自真实细节，无虚构。
8. 无 AI 直出段落；无收益承诺暗示。

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

## 第 5 篇：`AlphaStrategy` 策略开发

- 信号表字段：`datetime`、`vt_symbol`、`signal`。
- `show_signal_performance`：对预测信号做 Alphalens 类分析；与第 3 篇因子评价并列说明差异。
- `save_signal` / `load_signal`。
- 重点强调：模型训练输出预测分数，策略开发负责把预测分数变成目标持仓；两者定位和评价结果不同。
- `AlphaStrategy` 模板：`on_init`、`on_bars`、`on_trade`、`get_signal`、`set_target`、`execute_trading`。
- `EquityDemoStrategy` 流水线：取信号 → 排序 → 更新持仓天数 → 生成卖出列表 → 生成买入列表 → 设置目标仓位 → 执行调仓。
- 参数直觉：`top_k`、`n_drop`、`min_days`、`cash_ratio`、`min_volume`、`price_add` 对集中度、换手和成交假设的影响。

---

## 第 6 篇：事件驱动历史回测

- `BacktestingEngine`：`set_parameters`、`add_strategy`、传入 `signal_df`；`load_data`、`run_backtesting`、`calculate_result`、`calculate_statistics`、`show_chart` 的推荐顺序。
- 事件驱动流水线：按日期推进 K 线 → 撮合已有委托 → 触发 `strategy.on_bars` → 策略生成新委托 → 记录每日收盘。
- 信号如何进入回测：`get_signal` 按当前回测日期过滤 `signal_df`；强调信号日期与行情日期必须对齐。
- 撮合与成本假设：`price_add`、`contract.json` 中的费率/乘数/最小变动价位、涨跌停约束；说明历史回测不等于实盘。
- 回测结果：`daily_df`、成交金额、手续费、净盈亏、资金曲线、回撤、Sharpe Ratio、`show_performance`。
- **常见问题**：contract 缺失、某标的无 bar、信号日期与 bar 日期对齐、有信号但没有成交 — 各给一句排查方向。

---

## 若压缩篇数

- **5 篇**：可将第 6 篇缩入第 5 篇末尾（回测引擎使用顺序 + 读结果 + 排错），注意控制第 5 篇总字数。
- **4 篇**：通常需牺牲深度；可将「模型 + 信号 + 回测」合并为流程速览篇，或把第 1 篇缩短、环境与示例地图并入第 2 篇开头。

---

## 写作时可引用的代码锚点（内部备忘）

- 公开 API：`vnpy/alpha/__init__.py`
- 实验室与路径：`vnpy/alpha/lab.py`
- 数据集：`vnpy/alpha/dataset/template.py`、`vnpy/alpha/dataset/processor.py`、`vnpy/alpha/dataset/datasets/`
- 模型模板与实现：`vnpy/alpha/model/template.py`、`vnpy/alpha/model/models/`
- 策略与回测：`vnpy/alpha/strategy/template.py`、`vnpy/alpha/strategy/backtesting.py`、`vnpy/alpha/strategy/strategies/equity_demo_strategy.py`
- 示例：`examples/alpha_research/*.ipynb`
