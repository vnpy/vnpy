import pandas as pd

# 设置做大显示列和行，中间不显示省略号
pd.set_option('display.max_rows', 1000)  # 设置最大行数
pd.set_option('display.max_columns', 1000)  # 设置最大列数
pd.set_option('display.max_colwidth', 1000)  # 最大列宽度
pd.set_option('expand_frame_repr', False)  # 当列太多时不换行

df = pd.read_csv("C:\\Users\\NiuBi\\OneDrive\\量化\\数据\\db_bar_data.csv",usecols=["datetime","close_price","high_price","open_price","low_price","volume"],parse_dates=["datetime"])
df =df[["datetime","open_price","high_price","low_price","close_price","volume"]]
print(df)
print(df.dtypes)
