import tushare as ts
import pandas as pd

# 设置做大显示列和行，中间不显示省略号
pd.set_option('display.max_rows', 1000)  # 设置最大行数
pd.set_option('display.max_columns', 1000)  # 设置最大列数
pd.set_option('display.max_colwidth', 1000)  # 最大列宽度
pd.set_option('expand_frame_repr', False)  # 当列太多时不换行

pro = ts.pro_api("3c9fd39229add7e44caef118a4403cacbccc16f4437817bb08729905")

#获取主力合约TF.CFX每日对应的月合约
df = pro.fut_mapping(ts_code='TF.CFX')

print(df)