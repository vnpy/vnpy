import pandas as pd

# 设置做大显示列和行，中间不显示省略号
pd.set_option('display.max_rows', 1000)  # 设置最大行数
pd.set_option('display.max_columns', 1000)  # 设置最大列数
pd.set_option('display.max_colwidth', 1000)  # 最大列宽度
pd.set_option('expand_frame_repr', False)  # 当列太多时不换行

df_json = pd.read_json("C:\\Users\\erikg\\OneDrive\\量化\数据\\db_bar_data.json")
df = pd.DataFrame(df_json)
print(df)
