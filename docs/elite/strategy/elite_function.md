# 指标计算函数

VeighNa Elite Trader的CTA策略模块内置了以下计算函数供策略调用：

**sma** ：简单移动平均

* 入参
  * close: np.ndarray
  * time_period: int=30

* 出参
  * sma_array: np.ndarray

**ema** ：指数滑动平均

* 入参
  * close: np.ndarray
  * time_period: int=30

* 出参
  * ema_array: np.ndarray

**kama** ：适应性移动平均

* 入参
  * close: np.ndarray
  * time_period: int=30

* 出参
  * atr_array: np.ndarray

**wma** ：加权移动平均

* 入参
  * close: np.ndarray
  * time_period: int=30

* 出参
  * wma_array: np.ndarray

**apo**：绝对价格振荡器

* 入参
  * close: np.ndarray
  * fast_period: int=12
  * slow_period: int=26
  * matype: int=0

* 出参
  * apo_array: np.ndarray

请注意，matype分别对应：0=SMA, 1=EMA, 2=WMA, 3=DEMA, 4=TEMA, 5=TRIMA, 6=KAMA, 7=MAMA, 8=T3

**cmo**：钱德动量摆动指标

* 入参
  * close: np.ndarray
  * time_period: int=14

* 出参
  * cmo_array: np.ndarray

**mom**：上升动向值

* 入参
  * close: np.ndarray
  * time_period: int=10

* 出参
  * mom_array: np.ndarray

**ppo**：价格震荡百分比指数

* 入参
  * close: np.ndarray
  * fast_period: int=12
  * slow_period: int=26
  * matype: int=0

* 出参
  * ppo_array: np.ndarray

**roc**：变动率指标

* 入参
  * close: np.ndarray
  * time_period: int=10

* 出参
  * roc_array: np.ndarray

**rocr**：变动率比率

* 入参
  * close: np.ndarray
  * time_period: int=10

* 出参
  * rocr_array: np.ndarray

**rocp**：变动率百分比

* 入参
  * close: np.ndarray
  * time_period: int=10

* 出参
  * rocp_array: np.ndarray

**trix**：三次平滑EMA的一天变化率

* 入参
  * close: np.ndarray
  * time_period: int=30

* 出参
  * trix_array: np.ndarray

**stddev**：标准偏差

* 入参
  * close: np.ndarray
  * time_period: int=5
  * nbdev: float=1

* 出参
  * stddev_array: np.ndarray

**std**：标准偏差

* 入参
  * close: np.ndarray
  * time_period: int=5
  * nbdev: float=1

* 出参
  * std_array: np.ndarray

**obv**：能量潮

* 入参
  * close: np.ndarray
  * volume: np.ndarray

* 出参
  * obv_array: np.ndarray

**cci**：顺势指标

* 入参
  * high: np.ndarray
  * low: np.ndarray
  * close: np.ndarray
  * time_period: int=14

* 出参
  * cci_array: np.ndarray

**atr**：真实波动幅度均值

* 入参
  * high: np.ndarray
  * low: np.ndarray
  * close: np.ndarray
  * time_period: int=14

* 出参
  * atr_array: np.ndarray

**natr**：归一化波动幅度均值

* 入参
  * high: np.ndarray
  * low: np.ndarray
  * close: np.ndarray
  * time_period: int=14

* 出参
  * natr_array: np.ndarray

**rsi**：相对强弱指数

* 入参
  * close: np.ndarray
  * time_period: int=14

* 出参
  * rsi_array: np.ndarray

**macd**：平均异同移动平均线

* 入参
  * close: np.ndarray
  * fast_period: int=12
  * slow_period: int=26
  * signal_period: int=9

* 出参
  * macd_array: np.ndarray
  * macdsignal_array: np.ndarray
  * macdhist_array: np.ndarray

**adx**：平均趋向指数

* 入参
  * high: np.ndarray
  * low: np.ndarray
  * close: np.ndarray
  * time_period: int=14

* 出参
  * adx_array: np.ndarray

**adxr**：平均趋向指数的趋向指数

* 入参
  * high: np.ndarray
  * low: np.ndarray
  * close: np.ndarray
  * time_period: int=14

* 出参
  * adxr_array: np.ndarray

**minus_di**：负趋向指标

* 入参
  * high: np.ndarray
  * low: np.ndarray
  * close: np.ndarray
  * time_period: int=14

* 出参
  * minusdi_array: np.ndarray

**plus_di**：正趋向指标

* 入参
  * high: np.ndarray
  * low: np.ndarray
  * close: np.ndarray
  * time_period: int=14

* 出参
  * plusdi_array: np.ndarray

**willr**：威廉指标

* 入参
  * high: np.ndarray
  * low: np.ndarray
  * close: np.ndarray
  * time_period: int=14

* 出参
  * willr_array: np.ndarray

**ultosc**：终极波动指标

* 入参
  * high: np.ndarray
  * low: np.ndarray
  * close: np.ndarray
  * time_period: int=7
  * time_period2: int=14
  * time_period3: int=28

* 出参
  * ultosc_array: np.ndarray

**trange**：真实波幅

* 入参
  * high: np.ndarray
  * low: np.ndarray
  * close: np.ndarray

* 出参
  * trange_array: np.ndarray

**aroon**：阿隆指标

* 入参
  * high: np.ndarray
  * low: np.ndarray
  * time_period: int=14

* 出参
  * aroonup_array: np.ndarray
  * aroondown_array: np.ndarray

**aroonosc**：阿隆震荡

* 入参
  * high: np.ndarray
  * low: np.ndarray
  * time_period: int=14

* 出参
  * aroonosc_array: np.ndarray

**minus_dm**：负趋向变动值

* 入参
  * high: np.ndarray
  * low: np.ndarray
  * time_period: int=14

* 出参
  * minusdm_array: np.ndarray

**plus_dm**：正趋向变动值

* 入参
  * high: np.ndarray
  * low: np.ndarray
  * time_period: int=14

* 出参
  * plusdm_array: np.ndarray

**mfi**：资金流量指标

* 入参
  * high: np.ndarray
  * low: np.ndarray
  * close: np.ndarray
  * volume: np.ndarray
  * time_period: int=14

* 出参
  * mfi_array: np.ndarray

**ad**：平衡交易量指标

* 入参
  * high: np.ndarray
  * low: np.ndarray
  * close: np.ndarray
  * volume: np.ndarray

* 出参
  * ad_array: np.ndarray

**adosc**：震荡指标

* 入参
  * high: np.ndarray
  * low: np.ndarray
  * close: np.ndarray
  * volume: np.ndarray
  * fast_period: int=3
  * slow_period: int=10

* 出参
  * adosc_array: np.ndarray

**bop**：均势指标

* 入参
  * open: np.ndarray
  * high: np.ndarray
  * low: np.ndarray
  * close: np.ndarray

* 出参
  * bop_array: np.ndarray

**stoch**：随机指标

* 入参
  * high: np.ndarray
  * low: np.ndarray
  * close: np.ndarray
  * fastk_period: int=5
  * slowk_period: int=3
  * slowk_matype: int=0
  * slowd_period: int=3
  * slowd_matype: int=0

* 出参
  * slowk_array: np.ndarray
  * slowd_array: np.ndarray

**boll**：布林通道

* 入参
  * data: np.ndarray
  * window: int
  * dev: float

* 出参
  * bollup_array: np.ndarray
  * bolldown_array: np.ndarray

**keltner**：肯特纳通道

* 入参
  * high: np.ndarray
  * low: np.ndarray
  * close: np.ndarray
  * window: int
  * dev: float

* 出参
  * kkup_array: np.ndarray
  * kkdown_array: np.ndarray

**donchian**：唐奇安通道

* 入参
  * high: np.ndarray
  * low: np.ndarray
  * window: int

* 出参
  * donchianup_array: np.ndarray
  * donchiandown_array: np.ndarray

**cross_over**：上穿

* 入参
  * data: np.ndarray
  * level: float

若data上一个值小于等于level以及data最新值大于level，则返回True。

* 出参
  * cross_over: bool

**cross_below**：下穿

* 入参
  * data: np.ndarray
  * level: float

* 出参
  * cross_below: bool

若data上一个值大于等于level以及data最新值小于level，则返回True。

**check_increasing**：检查序列单调上升

* 入参
  * data: np.ndarray

* 出参
  * increasing: bool

**check_decreasing**：检查序列单调下降

* 入参
  * data: np.ndarray

* 出参
  * decreasing: bool

**resample_data**：对K线数据重新取样

* 入参
  * df: pd.DataFrame
  * rule: str

* 出参
  * resampled_df: pd.DataFrame

* 示例

若想要测试resample_data函数的效果，可以在策略的on_history函数收到hm推送的时候先获取K线DataFrame，再调用resample_data函数对K线数据重新取样，如下所示：

```python 3
# 判断实盘trading状态，只有策略启动之后才进行输出
df: pd.DataFrame = hm.to_dataframe()
resampled_df: pd.DataFrame = resample_data(df, "5min")
```
