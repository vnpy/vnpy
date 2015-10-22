# -*- coding: utf-8 -*-




import copy
import numpy
import datetime
import math

import matplotlib.spines as spines
import matplotlib.ticker as ticker
import matplotlib.patches as patches
import matplotlib.font_manager as font_manager 



import Public.Public as Public



__color_gold__= '#FDDB05'
__color_gray70__= '0.7'
__font_properties__= font_manager.FontProperties(fname='/usr/share/fonts/truetype/wqy/wqy-zenhei.ttc')

__横轴倍率__= 10.0 / 230.0
__纵轴倍率__= 0.3





class 日线价格子图:

	def __init__(self, parent, 绘图数据):
		'''

		'''
		self._parent= parent
		self._ilogger= Public.IndentLogger(logger=parent._ilogger._logger, indent=parent._ilogger._indent+1)

		# 原始数据
		self._公司信息= 绘图数据['公司信息']
		self._任务参数= 绘图数据['任务参数']
		self._日线数据= 绘图数据['日线数据']
		#	self._实盘数据= 绘图数据['实盘数据']

		self._个股代码= self._公司信息['个股代码']
		self._复权记录= self._日线数据['复权记录']

		# 任务参数数据
		self._复权绘图= self._任务参数['复权绘图']
		self._绘制实盘= self._任务参数['绘制实盘']
		self._绘制个股均线= self._任务参数['绘制个股均线']
		self._绘制指数均线= self._任务参数['绘制指数均线']

		# 全局日线数据
		self._全局指数日线= self._日线数据['指数日线']
		self._全局绘图日线= self._日线数据['绘图日线']		# 绘图日线 就是补全日线，根据任务参数已经选择了是否复权
		self._全局日期序列= self._全局指数日线['日期']

		# 目标日线数据
		self._目标起始偏移= self._日线数据['目标起始偏移']
		self._目标结束偏移= self._日线数据['目标结束偏移']

		self._目标指数日线= { 项目 : 序列[self._目标起始偏移:self._目标结束偏移+1] for 项目, 序列 in self._全局指数日线.items() }
		self._目标绘图日线= { 项目 : 序列[self._目标起始偏移:self._目标结束偏移+1] for 项目, 序列 in self._全局绘图日线.items() }
		
		# 均线数据
		if self._绘制指数均线:
			self._全局指数均线= self._日线数据['指数均线']
			self._目标指数均线= { 项目 : 序列[self._目标起始偏移:self._目标结束偏移+1] for 项目, 序列 in self._全局指数均线.items() }
		if self._绘制个股均线:
			self._全局绘图均线= self._日线数据['绘图均线']
			self._目标绘图均线= { 项目 : 序列[self._目标起始偏移:self._目标结束偏移+1] for 项目, 序列 in self._全局绘图均线.items() }

		self._目标日期序列= self._目标绘图日线['日期']

		self._目标指数开盘= self._目标指数日线['开盘']
		self._目标指数收盘= self._目标指数日线['收盘']
		self._目标指数最高= self._目标指数日线['最高']
		self._目标指数最低= self._目标指数日线['最低']
		self._目标指数中线= self._目标指数日线['开收中']

		self._目标绘图开盘= self._目标绘图日线['开盘']
		self._目标绘图收盘= self._目标绘图日线['收盘']
		self._目标绘图最高= self._目标绘图日线['最高']
		self._目标绘图最低= self._目标绘图日线['最低']
		self._目标绘图中线= self._目标绘图日线['开收中']

		# 行情附加数据
		self._对数坐标底数= 1.1

		self._横轴坐标序列= numpy.arange(self._目标起始偏移, self._目标结束偏移+1)
		self._目标行情长度= len(self._目标日期序列)

		self._目标指数上涨= numpy.array( [True if po is not None and po < pc  else False for po, pc in zip(self._目标指数开盘, self._目标指数收盘)] )	# 标示出该天股价日内上涨的一个序列
		self._目标指数下跌= numpy.array( [True if po is not None and po > pc  else False for po, pc in zip(self._目标指数开盘, self._目标指数收盘)] )	# 标示出该天股价日内下跌的一个序列
		self._目标指数平盘= numpy.array( [True if po is not None and po == pc else False for po, pc in zip(self._目标指数开盘, self._目标指数收盘)] )	# 标示出该天股价日内走平的一个序列

		self._目标绘图上涨= numpy.array( [True if po is not None and po < pc  else False for po, pc in zip(self._目标绘图开盘, self._目标绘图收盘)] )	# 标示出该天股价日内上涨的一个序列
		self._目标绘图下跌= numpy.array( [True if po is not None and po > pc  else False for po, pc in zip(self._目标绘图开盘, self._目标绘图收盘)] )	# 标示出该天股价日内下跌的一个序列
		self._目标绘图平盘= numpy.array( [True if po is not None and po == pc else False for po, pc in zip(self._目标绘图开盘, self._目标绘图收盘)] )	# 标示出该天股价日内走平的一个序列

		# 行情衍生数据
		self._指数衍生行情= self._日线数据['指数衍生行情']
		self._个股衍生行情= self._日线数据['个股衍生行情']

		# 平面对象数据
		self._布局参数= None
		self._指数平面= None
		self._指数横轴= None
		self._指数纵轴= None

		self._个股平面= None
		self._个股横轴= None
		self._个股纵轴= None

		# 横轴参数、纵轴参数
		self._横轴参数= self.计算横轴参数()
		self._纵轴参数= self.计算纵轴参数()

		# 行情衍生数据
		self._定制绘图函数= self._任务参数['定制绘图函数']
		self._定制绘图参数= self._任务参数['定制绘图参数']



	def 返回目标日线数据(self):
		'''
		日线换手子图用
		'''
		日线行情= {}
		日线行情['目标指数日线']= self._目标指数日线
		日线行情['目标绘图日线']= self._目标绘图日线

		return 日线行情



	def 返回行情附加数据(self):
		'''
		日线换手子图用
		'''
		附加行情= {}

		附加行情['横轴坐标序列']= self._横轴坐标序列
		附加行情['目标行情长度']= self._目标行情长度

		附加行情['目标指数上涨']= self._目标指数上涨
		附加行情['目标指数下跌']= self._目标指数下跌
		附加行情['目标指数平盘']= self._目标指数平盘

		附加行情['目标绘图上涨']= self._目标绘图上涨
		附加行情['目标绘图下跌']= self._目标绘图下跌
		附加行情['目标绘图平盘']= self._目标绘图平盘

		return 附加行情



	def 返回本图大小(self):
		'''

		'''
		return (self._横轴参数['横轴宽度'], self._纵轴参数['纵轴高度'])



	def 平面初始化(self, 图片对象, 子图偏移, 全图大小):
		'''

		'''
		
		
		#	计算布局参数
		#=======================================================================================
		子图横移, \
		子图纵移= 子图偏移
		
		全图宽度, \
		全图高度= 全图大小

		本图宽度= self._横轴参数['横轴宽度']
		本图高度= self._纵轴参数['纵轴高度']

		布局参数= ( 子图横移/全图宽度, 子图纵移/全图高度, 本图宽度/全图宽度, 本图高度/全图高度 )

		self._布局参数= 布局参数
		对数坐标底数= self._对数坐标底数

		#	指数部分
		#=======================================================================================
		指数平面= 图片对象.add_axes(布局参数, axis_bgcolor='black')

		指数平面.set_axisbelow(True)	# 网格线放在底层
		指数平面.set_yscale('log', basey=对数坐标底数)		# 使用对数坐标

		# 改变坐标线的颜色
		for 方位, 边框 in 指数平面.spines.items():	# 方位: 'left' | 'right' | 'top' | 'bottom'
			边框.set_color(__color_gold__)

		指数横轴= 指数平面.get_xaxis()
		指数纵轴= 指数平面.get_yaxis()

		#	指数纵轴.set_label_position('left')	# XXX: 不顶用

		self._指数平面= 指数平面
		self._指数横轴= 指数横轴
		self._指数纵轴= 指数纵轴

		self.设置指数横轴()
		self.设置指数纵轴()

		#	个股部分
		#=======================================================================================
		个股平面= 指数平面.twinx()
		个股平面.set_axis_bgcolor('black')
		个股平面.set_axisbelow(True)	# 网格线放在底层
		个股平面.set_yscale('log', basey=对数坐标底数)		# 使用对数坐标

		#	for 方位, 边框 in 个股平面.spines.items():	# 方位: 'left' | 'right' | 'top' | 'bottom'
		#		边框.set_color(__color_gold__)

		个股横轴= 个股平面.get_xaxis()
		个股纵轴= 个股平面.get_yaxis()

		#	个股纵轴.set_label_position('right')	# XXX: 不顶用

		self._个股平面= 个股平面
		self._个股横轴= 个股横轴
		self._个股纵轴= 个股纵轴

		self.设置个股横轴()
		self.设置个股纵轴()



	def 返回指数平面(self):
		'''

		'''
		return self._指数平面



	def 计算横轴余度(self, 横轴裕量):
		'''
		被 计算横轴参数() 调用
		'''
		目标起始偏移= self._目标起始偏移
		目标结束偏移= self._目标结束偏移

		坐标起点= 目标起始偏移 - 横轴裕量
		坐标终点= 目标结束偏移 + 横轴裕量
		横轴尺寸= 坐标终点 - 坐标起点

		横轴余度= {}
		横轴余度['横轴裕量']= 横轴裕量
		横轴余度['坐标起点']= 坐标起点
		横轴余度['坐标终点']= 坐标终点
		横轴余度['横轴尺寸']= 横轴尺寸
		横轴余度['横轴倍率']= __横轴倍率__
		横轴余度['横轴宽度']= 横轴尺寸 * __横轴倍率__

		return 横轴余度



	def 计算纵轴余度(self):
		'''
		被 计算纵轴参数() 调用
		'''
		对数坐标底数= self._对数坐标底数

		个股最高= [nr for nr in self._目标绘图最高 if nr is not None]
		个股最低= [nr for nr in self._目标绘图最低 if nr is not None]
		个股开盘= [nr for nr in self._目标绘图开盘 if nr is not None]

		指数基点= self._目标指数开盘[0]
		个股基点= round(个股开盘[0], -1)	# XXX: 对复权行情来说，基点价格可能不是整数，所以需要取整。

		指数极高= max(self._目标指数最高)
		指数极低= min(self._目标指数最低)

		个股极高= max(个股最高)
		个股极低= min(个股最低)

		指数修正极低= min(指数极低, 个股极低*指数基点/个股基点)
		指数修正极高= max(指数极高, 个股极高*指数基点/个股基点)

		个股修正极低= min(个股极低, 指数极低*个股基点/指数基点)
		个股修正极高= max(个股极高, 指数极高*个股基点/指数基点)

		指数坐标起点= 指数修正极低 / 对数坐标底数
		指数坐标终点= 指数修正极高 * 对数坐标底数
		个股坐标起点= 个股修正极低 / 对数坐标底数
		个股坐标终点= 个股修正极高 * 对数坐标底数

		# 计算 纵轴尺寸。
		# XXX: 注意，用个股坐标或指数坐标计算都可以，其中包含的倍数因子对结果无影响，即:
		#	log(base, n1) - log(base, n2) == 
		#	log(base, n1/n2) ==
		#	log(base, k*n1/k*n2) ==
		#	log(base, k*n1) - log(base, k*n2)
		# ，这是对数运算的性质。
		纵轴尺寸= math.log(个股坐标终点, 对数坐标底数) - math.log(个股坐标起点, 对数坐标底数)

		纵轴余度= {
			'纵轴倍率': __纵轴倍率__,
			'纵轴尺寸': 纵轴尺寸,
			'纵轴高度': 纵轴尺寸 * __纵轴倍率__,
			'个股基点': 个股基点,
			'指数基点': 指数基点,
			'个股坐标起点': 个股坐标起点,
			'个股坐标终点': 个股坐标终点,
			'指数坐标起点': 指数坐标起点,
			'指数坐标终点': 指数坐标终点,
		}

		return 纵轴余度



	def 计算横轴参数(self):
		'''

		'''
		全局日期序列= self._全局日期序列
		目标起始偏移= self._目标起始偏移
		目标结束偏移= self._目标结束偏移

		全局日期列表= [ datetime.date(int(ys), int(ms), int(ds)) for ys, ms, ds in [ dstr.split('-') for dstr in 全局日期序列 ] ]
		目标日期列表= 全局日期列表[目标起始偏移:目标结束偏移+1]

		# 确定 X 轴的 主要坐标点
		每月首日偏移= []	# 每个月第一个交易日在所有日期列表中的 index
		所有年份= sorted(set([d.year for d in 目标日期列表]))

		for 年份 in 所有年份:		
			当年月份= sorted(set([d.month for d in 目标日期列表 if d.year==年份]))	# 当年所有的交易月份
			for 月份 in 当年月份:
				当月首日= min([d for d in 目标日期列表 if d.year==年份 and d.month==月份])		# 当月的第一个交易日
				每月首日偏移.append(全局日期列表.index(当月首日))

		xMajorLocator= ticker.FixedLocator(numpy.array(每月首日偏移))

		# 确定 X 轴的 辅助坐标点
		每周首日偏移= {}	# value: 每周第一个交易日在所有日期列表中的 index; key: 当周的序号 week number（当周是第几周）

		for 日期 in 目标日期列表:
			isoyear, weekno= 日期.isocalendar()[0:2]
			dmark= isoyear*100 + weekno
			if dmark not in 每周首日偏移:
				每周首日偏移[dmark]= 全局日期列表.index(日期)

		每周首日偏移= sorted(每周首日偏移.values())

		xMinorLocator= ticker.FixedLocator(numpy.array(每周首日偏移))

		# 确定 X 轴的 MajorFormatter 和 MinorFormatter
		def x_major_formatter(idx, pos=None):
			return 全局日期列表[idx].strftime('%Y-%m-%d')

		def x_minor_formatter(idx, pos=None):
			return 全局日期列表[idx].strftime('%m-%d')

		xMajorFormatter= ticker.FuncFormatter(x_major_formatter)
		xMinorFormatter= ticker.FuncFormatter(x_minor_formatter)

		# 填充并返回
		横轴参数= {}

		横轴参数['xMajorLocator']= xMajorLocator  
		横轴参数['xMinorLocator']= xMinorLocator  
		横轴参数['xMajorFormatter']= xMajorFormatter
		横轴参数['xMinorFormatter']= xMinorFormatter
		横轴参数['每月首日偏移']= 每月首日偏移   
		横轴参数['每周首日偏移']= 每周首日偏移   

		横轴裕量= 1
		横轴余度= self.计算横轴余度(横轴裕量=横轴裕量)
		横轴参数.update(横轴余度)

		return 横轴参数



	def 返回横轴参数(self):
		'''

		'''
		return self._横轴参数



	def 计算纵轴参数(self):
		'''
		计算纵轴坐标点
		'''
		步进倍率= 1.1

		纵轴余度= self.计算纵轴余度()

		个股坐标起点= 纵轴余度['个股坐标起点']
		个股坐标终点= 纵轴余度['个股坐标终点']

		个股基点= 纵轴余度['个股基点']
		指数基点= 纵轴余度['指数基点']

		#	计算个股主坐标值
		#=====================================================================================================
		个股主坐标值= [个股基点]

		# 往下拓展
		for i in range(1, 999):
			当前坐标= round(个股基点/(步进倍率**i), -1)	# 坐标值 7890 表示 7.89 元
			if 当前坐标 <= 个股坐标起点:
				break
			个股主坐标值.insert(0, 当前坐标)
		# 往上拓展
		for i in range(1, 999):
			当前坐标= round(个股基点*(步进倍率**i), -1)	# 坐标值 7890 表示 7.89 元
			if 当前坐标 >= 个股坐标终点:
				break
			个股主坐标值.append(当前坐标)

		#	计算个股副坐标值
		#=====================================================================================================
		个股副坐标值= [round((curr*next)**0.5, -1) for curr, next in zip(个股主坐标值[:-1], 个股主坐标值[1:])]
		极值= round((个股主坐标值[0]*个股主坐标值[0]/步进倍率)**0.5, -1)
		if 极值 > 个股坐标起点: 个股副坐标值.insert(0, 极值)
		极值= round((个股主坐标值[-1]*个股主坐标值[-1]*步进倍率)**0.5, -1)
		if 极值 < 个股坐标终点: 个股副坐标值.append(极值)

		#	计算指数主、副坐标值
		#=====================================================================================================
		指数主坐标值= [数值*指数基点/个股基点 for 数值 in 个股主坐标值]
		指数副坐标值= [数值*指数基点/个股基点 for 数值 in 个股副坐标值]

		#	生成、返回
		#=====================================================================================================
		纵轴参数= {
			'个股主坐标值': 个股主坐标值,
			'个股副坐标值': 个股副坐标值,
			'指数主坐标值': 指数主坐标值,
			'指数副坐标值': 指数副坐标值,
		}
		纵轴参数.update(纵轴余度)

		return 纵轴参数



	def 设置指数横轴(self):
		'''

		'''
		指数平面= self._指数平面
		横轴对象= self._指数横轴
		横轴参数= self._横轴参数

		横轴裕量= 横轴参数['横轴裕量']
		坐标起点= 横轴参数['坐标起点']
		坐标终点= 横轴参数['坐标终点']
		xMajorLocator= 横轴参数['xMajorLocator']
		xMinorLocator= 横轴参数['xMinorLocator']
		xMajorFormatter= 横轴参数['xMajorFormatter']
		xMinorFormatter= 横轴参数['xMinorFormatter']

		横轴对象.grid(True, 'major', color='0.3', linestyle='solid', linewidth=0.2)
		横轴对象.grid(True, 'minor', color='0.3', linestyle='dotted', linewidth=0.15)
		指数平面.set_xlim(坐标起点, 坐标终点)
		横轴对象.set_major_locator(xMajorLocator)
		横轴对象.set_minor_locator(xMinorLocator)

		for 主坐标 in 指数平面.get_xticklabels(minor=False):
			主坐标.set_visible(False)
		for 副坐标 in 指数平面.get_xticklabels(minor=True):
			副坐标.set_visible(False)



	def 设置个股横轴(self):
		'''

		'''
		个股平面= self._个股平面
		横轴对象= self._个股横轴
		横轴参数= self._横轴参数

		横轴裕量= 横轴参数['横轴裕量']
		坐标起点= 横轴参数['坐标起点']
		坐标终点= 横轴参数['坐标终点']
		xMajorLocator= 横轴参数['xMajorLocator']
		xMinorLocator= 横轴参数['xMinorLocator']
		xMajorFormatter= 横轴参数['xMajorFormatter']
		xMinorFormatter= 横轴参数['xMinorFormatter']

		#	横轴对象.grid(True, 'major', color='0.3', linestyle='solid', linewidth=0.2)
		#	横轴对象.grid(True, 'minor', color='0.3', linestyle='dotted', linewidth=0.15)
		个股平面.set_xlim(坐标起点, 坐标终点)
		横轴对象.set_major_locator(xMajorLocator)
		横轴对象.set_minor_locator(xMinorLocator)

		for 主坐标 in 个股平面.get_xticklabels(minor=False):
			主坐标.set_visible(False)
		for 副坐标 in 个股平面.get_xticklabels(minor=True):
			副坐标.set_visible(False)



	def 设置指数纵轴(self):
		'''

		'''
		指数平面= self._指数平面
		纵轴对象= self._指数纵轴
		纵轴参数= self._纵轴参数
		坐标起点= 纵轴参数['指数坐标起点']
		坐标终点= 纵轴参数['指数坐标终点']

		纵轴对象.grid(True, 'major', color='0.3', linestyle='solid', linewidth=0.2)
		纵轴对象.grid(True, 'minor', color='0.3', linestyle='dotted', linewidth=0.15)
		指数平面.set_ylim(坐标起点, 坐标终点)

		#	主坐标点
		#======================================================================================
		主坐标值= 纵轴参数['指数主坐标值']
		yMajorLocator= ticker.FixedLocator(numpy.array(主坐标值))
		def y_major_formatter(num, pos=None):
			return str(round(num/1000.0, 3))
		yMajorFormatter= ticker.FuncFormatter(y_major_formatter)

		纵轴对象.set_major_locator(yMajorLocator)
		纵轴对象.set_major_formatter(yMajorFormatter)

		for 主坐标 in 指数平面.get_yticklabels(minor=False):
			主坐标.set_fontsize(6)

		#	副坐标点
		#======================================================================================
		副坐标值= 纵轴参数['指数副坐标值']
		yMinorLocator= ticker.FixedLocator(numpy.array(副坐标值))
		def y_minor_formatter(num, pos=None):
			return str(round(num/1000.0, 3))
		yMinorFormatter= ticker.FuncFormatter(y_minor_formatter)

		纵轴对象.set_minor_locator(yMinorLocator)
		纵轴对象.set_minor_formatter(yMinorFormatter)
	
		for 副坐标 in 指数平面.get_yticklabels(minor=True):
			副坐标.set_fontsize(5)
			副坐标.set_color('blue')



	def 设置个股纵轴(self):
		'''

		'''
		个股平面= self._个股平面
		纵轴对象= self._个股纵轴
		纵轴参数= self._纵轴参数
		坐标起点= 纵轴参数['个股坐标起点']
		坐标终点= 纵轴参数['个股坐标终点']

		#	纵轴对象.grid(True, 'major', color='0.3', linestyle='solid', linewidth=0.2)
		#	纵轴对象.grid(True, 'minor', color='0.3', linestyle='dotted', linewidth=0.15)
		个股平面.set_ylim(坐标起点, 坐标终点)

		#	主坐标点
		#======================================================================================
		主坐标值= 纵轴参数['个股主坐标值']
		yMajorLocator= ticker.FixedLocator(numpy.array(主坐标值))
		def y_major_formatter(num, pos=None):
			return str(round(num/1000.0, 3))
		yMajorFormatter= ticker.FuncFormatter(y_major_formatter)

		纵轴对象.set_major_locator(yMajorLocator)
		纵轴对象.set_major_formatter(yMajorFormatter)

		for 主坐标 in 个股平面.get_yticklabels(minor=False):
			主坐标.set_fontsize(6)
		#	副坐标点
		#======================================================================================
		副坐标值= 纵轴参数['个股副坐标值']
		yMinorLocator= ticker.FixedLocator(numpy.array(副坐标值))
		def y_minor_formatter(num, pos=None):
			return str(round(num/1000.0, 3))
		yMinorFormatter= ticker.FuncFormatter(y_minor_formatter)

		纵轴对象.set_minor_locator(yMinorLocator)
		纵轴对象.set_minor_formatter(yMinorFormatter)

		for 副坐标 in 个股平面.get_yticklabels(minor=True):
			副坐标.set_fontsize(5)
			副坐标.set_color('blue')



	def 绘制指数行情走势(self):
		'''
		画 K 线
		'''
		指数平面= self._指数平面
		横轴坐标序列= self._横轴坐标序列

		开盘序列= copy.copy(self._目标指数开盘)
		收盘序列= copy.copy(self._目标指数收盘)
		最高序列= self._目标指数最高
		最低序列= self._目标指数最低

		上涨序列= self._目标指数上涨
		下跌序列= self._目标指数下跌
		平盘序列= self._目标指数平盘

		# 对开收盘价进行视觉修正
		for idx, (po, pc) in enumerate(zip(开盘序列, 收盘序列)):
			if po is not None and po==pc:
				调整= int(po * 0.0005)
				开盘序列[idx]= po + 调整
				收盘序列[idx]= pc - 调整

		开盘阵列= numpy.array(开盘序列)
		收盘阵列= numpy.array(收盘序列)
		最高阵列= numpy.array(最高序列)
		最低阵列= numpy.array(最低序列)

		if True in 上涨序列:
			指数平面.vlines(横轴坐标序列[上涨序列], 最低阵列[上涨序列], 最高阵列[上涨序列], edgecolor='0.7', linewidth=0.6, label='_nolegend_', alpha=0.5)
			指数平面.vlines(横轴坐标序列[上涨序列], 开盘阵列[上涨序列], 收盘阵列[上涨序列], edgecolor='0.7', linewidth=3.0, label='_nolegend_', alpha=0.5)

		if True in 下跌序列:
			指数平面.vlines(横轴坐标序列[下跌序列], 最低阵列[下跌序列], 最高阵列[下跌序列], edgecolor='0.3', linewidth=0.6, label='_nolegend_', alpha=0.5)
			指数平面.vlines(横轴坐标序列[下跌序列], 开盘阵列[下跌序列], 收盘阵列[下跌序列], edgecolor='0.3', linewidth=3.0, label='_nolegend_', alpha=0.5)

		if True in 平盘序列:
			指数平面.vlines(横轴坐标序列[平盘序列], 最低阵列[平盘序列], 最高阵列[平盘序列], edgecolor='1.0', linewidth=0.6, label='_nolegend_', alpha=1.0)
			指数平面.vlines(横轴坐标序列[平盘序列], 开盘阵列[平盘序列], 收盘阵列[平盘序列], edgecolor='1.0', linewidth=3.0, label='_nolegend_', alpha=1.0)



	def 绘制个股行情走势(self):
		'''
		画 K 线
		'''
		个股平面= self._个股平面
		横轴坐标序列= self._横轴坐标序列

		开盘序列= copy.copy(self._目标绘图开盘)
		收盘序列= copy.copy(self._目标绘图收盘)
		最高序列= self._目标绘图最高
		最低序列= self._目标绘图最低

		上涨序列= self._目标绘图上涨
		下跌序列= self._目标绘图下跌
		平盘序列= self._目标绘图平盘

		# 对开收盘价进行视觉修正
		for idx, (po, pc) in enumerate(zip(开盘序列, 收盘序列)):
			if po is not None and po==pc:
				调整= int(po * 0.0005)
				开盘序列[idx]= po + 调整
				收盘序列[idx]= pc - 调整

		开盘阵列= numpy.array(开盘序列)
		收盘阵列= numpy.array(收盘序列)
		最高阵列= numpy.array(最高序列)
		最低阵列= numpy.array(最低序列)

		if True in 上涨序列:
			个股平面.vlines(横轴坐标序列[上涨序列], 最低阵列[上涨序列], 最高阵列[上涨序列], edgecolor='red', linewidth=0.6, label='_nolegend_', alpha=0.5)
			个股平面.vlines(横轴坐标序列[上涨序列], 开盘阵列[上涨序列], 收盘阵列[上涨序列], edgecolor='red', linewidth=3.0, label='_nolegend_', alpha=0.5)

		if True in 下跌序列:
			个股平面.vlines(横轴坐标序列[下跌序列], 最低阵列[下跌序列], 最高阵列[下跌序列], edgecolor='green', linewidth=0.6, label='_nolegend_', alpha=0.5)
			个股平面.vlines(横轴坐标序列[下跌序列], 开盘阵列[下跌序列], 收盘阵列[下跌序列], edgecolor='green', linewidth=3.0, label='_nolegend_', alpha=0.5)

		if True in 平盘序列:
			个股平面.vlines(横轴坐标序列[平盘序列], 最低阵列[平盘序列], 最高阵列[平盘序列], edgecolor='0.7', linewidth=0.6, label='_nolegend_', alpha=0.5)
			个股平面.vlines(横轴坐标序列[平盘序列], 开盘阵列[平盘序列], 收盘阵列[平盘序列], edgecolor='0.7', linewidth=3.0, label='_nolegend_', alpha=0.5)



	def 绘制个股开收中线走势(self):
		'''

		'''
		个股平面= self._个股平面

		横轴坐标序列= self._横轴坐标序列
		目标行情长度= self._目标行情长度
		个股衍生日期= self._个股衍生行情['日期']
		全局日期序列= self._全局日期序列
		目标日期序列= self._目标日期序列
		目标绘图中线= self._目标绘图中线

		目标首日= 目标日期序列[0]
		目标尾日= 目标日期序列[-1]

		中线阈值= 30
		长线阈值= 90

		# 绘制中线
		中线阵列= numpy.array(目标绘图中线)
		个股平面.plot(横轴坐标序列, 中线阵列, 'o-', color='white', linewidth=0.2, label='个股中线', \
			markersize=0.3, markeredgecolor='white', markeredgewidth=0.1, alpha=1.0)

		# 计算拐点位置及关键度
		走势拐点= self._个股衍生行情['开收中线走势拐点']

		顶点序列= [None] * 目标行情长度
		底点序列= [None] * 目标行情长度

		for 拐点 in 走势拐点:
			日期= 个股衍生日期[拐点['偏移']]
			if 日期 < 目标首日 or 日期 > 目标尾日:
				continue
			
			偏移= 目标日期序列.index(日期)
			横标= 全局日期序列.index(日期)
			位置= 目标绘图中线[偏移]
			if 拐点['类型'] == '^':
				顶点序列[偏移]= 位置
				纵标= 位置 * 1.01
				valign= 'bottom'
			else:
				底点序列[偏移]= 位置
				纵标= 位置 / 1.01
				valign= 'top'

			关键度= 拐点['关键度']

			if 关键度 < 中线阈值:
				continue
			
			if 关键度 < 中线阈值:
				fsize= 2.3
				weight= 300
			elif 关键度 < 长线阈值:
				fsize= 2.7
				weight= 600
			else:
				fsize= 3.3
				weight= 900

			注释= 个股平面.text(横标, 纵标, str(关键度), weight=weight, fontsize=fsize, verticalalignment=valign, horizontalalignment='center', color='white', alpha=0.7)

		# 绘制拐点
		底点阵列= numpy.array(底点序列)
		顶点阵列= numpy.array(顶点序列)

		个股平面.plot(横轴坐标序列, 底点阵列, marker=6, color='white', label='个股中线底点', \
			markersize=2.3, markeredgecolor='white', markeredgewidth=0.0, alpha=0.7)

		个股平面.plot(横轴坐标序列, 顶点阵列, marker=7, color='white', label='个股中线顶点', \
			markersize=2.3, markeredgecolor='white', markeredgewidth=0.0, alpha=0.7)



	def 绘制指数均线走势(self):
		'''

		'''
		横轴坐标序列= self._横轴坐标序列
		指数平面= self._指数平面
		均线字典= self._目标指数均线

		widthw= 0.2
		widthn= 0.1
		mksize= 0.3
		mkwidth= 0.1
		alpha= 1.0

		for n, seq in 均线字典.items():
			rarray= numpy.array( seq )
			color=  'white'  if n < 10 else \
				'yellow' if n < 30 else \
				'cyan'   if n < 60 else \
				'magenta'
			
			指数平面.plot(横轴坐标序列, rarray, 'o-', color=color, linewidth=widthw, label='指数均线_'+str(n), \
				markersize=mksize, markeredgecolor=color, markeredgewidth=mkwidth, alpha=alpha)



	def 绘制个股均线走势(self):
		'''

		'''
		横轴坐标序列= self._横轴坐标序列
		个股平面= self._个股平面
		均线字典= self._目标绘图均线

		widthw= 0.2
		widthn= 0.1
		mksize= 0.3
		mkwidth= 0.1
		alpha= 0.7

		for n, seq in 均线字典.items():
			rarray= numpy.array( seq )
			color=  'white'  if n < 10 else \
				'yellow' if n < 30 else \
				'cyan'   if n < 60 else \
				'magenta'

			个股平面.plot(横轴坐标序列, rarray, 'o-', color=color, linewidth=widthw, label='个股均线_'+str(n), \
				markersize=mksize, markeredgecolor=color, markeredgewidth=mkwidth, alpha=alpha)



	def 绘制复权提示(self):
		'''
		
		'''
		个股平面= self._个股平面
		纵轴参数= self._纵轴参数
		目标日期序列= self._目标日期序列
		全局日期序列= self._全局日期序列

		纵标起点= 纵轴参数['个股坐标起点']
		纵标终点= 纵轴参数['个股坐标终点']
		目标首日= 目标日期序列[0]
		目标尾日= 目标日期序列[-1]

		复权记录= self._复权记录

		fsize= 5.0
		ycoord= 纵标终点/1.1
		alpha= 0.7

		for 日期, 比率 in 复权记录:
			if 日期<目标首日 or 日期>目标尾日: continue
			横标= 全局日期序列.index(日期)
			个股平面.plot([横标, 横标], [纵标起点, 纵标终点], '-', color='purple', linewidth=0.1)
			label= 个股平面.text( \
				横标, ycoord, \
				'复权 ' + str(比率) + '\n' + 日期, \
				fontproperties=__font_properties__, \
				horizontalalignment='left', \
				verticalalignment='top', \
				color='purple', \
				alpha=alpha
			)
			label.set_fontsize(fsize)



	def 绘制流通股本变更提示(self):
		'''
		注意两个问题:
			1. 流通股本变更提示中的日期可能不是交易日期
			2. 流通股本变更提示涵盖个股的所有历史，有些内容可能在绘图目标区间以外
		'''
		个股平面= self._个股平面
		纵轴参数= self._纵轴参数
		公司信息= self._公司信息
		目标日期序列= self._目标日期序列
		全局日期序列= self._全局日期序列

		纵标起点= 纵轴参数['个股坐标起点']
		纵标终点= 纵轴参数['个股坐标终点']
		目标首日= 目标日期序列[0]
		目标尾日= 目标日期序列[-1]

		变更记录= [记录 for 记录 in 公司信息['流通股变更'] if 记录['变更日期']>=目标首日 and 记录['变更日期']<=目标尾日]

		fsize= 5.0
		ycoord= 纵标终点/1.05
		alpha= 0.7

		for 记录 in 变更记录:
			变更日期= 记录['变更日期']
			比率= 记录['变更比']
			调整日期= [ds for ds in 目标日期序列 if ds >= 变更日期][0]
			横标= 全局日期序列.index(调整日期)
			个股平面.plot([横标, 横标], [纵标起点, 纵标终点], '-', color='yellow', linewidth=0.1)
			label= 个股平面.text( \
				横标, ycoord, \
				'流通股 ' + str(比率) + '\n' + 变更日期, \
				fontproperties=__font_properties__, \
				horizontalalignment='left', \
				verticalalignment='top', \
				color='yellow', \
				alpha=alpha
			)
			label.set_fontsize(fsize)



	def 绘制首尾股本信息(self):
		'''

		'''
		def 寻找纵轴最大空隙(偏移):
			'''
			找出 X 轴某个位置图中最大的空隙
			'''
			指数基点= 纵轴参数['指数基点']
			指数目标= 全局指数开盘[偏移]

			个股基点= 纵轴参数['个股基点']
			个股目标= 全局绘图开盘[偏移]

			if 个股目标 is None:
				try:
					个股目标= [nr for nr in 全局绘图开盘[:偏移] if nr is not None][-1]
				except IndexError:
					个股目标= [nr for nr in 全局绘图开盘[偏移:] if nr is not None][0]
			调整目标= 指数目标 * 个股基点 / 指数基点

			比较列表= [坐标起点, 个股目标, 调整目标, 坐标终点]
			比较列表.sort()
			差值, 低点, 高点= max( [ (math.log(n2/n1, 对数坐标底数), n1, n2) for n1, n2 in zip(比较列表[:-1], 比较列表[1:]) ] )

			return (低点*高点)**0.5		# 相乘再开平方，在 log 坐标系里看起来就是在中间位置。



		def 整数分位表示(整数):
			'''
			123456789 --> '1,2345,6789'
			'''
			if type(整数) is not int: return str(整数)
			
			if 整数 == 0: return '0'
			
			if 整数 < 0:
				整数= -整数
				为负= True
			else:
				为负= False

			intstr= str(整数)
			intstr= '0'*((4-len(intstr)%4)%4) + intstr
			intlist= [intstr[i:i+4] for i in range(0, len(intstr), 4)]
			
			intlist[0]= intlist[0].lstrip('0')

			return ('-' + ','.join(intlist)) if 为负 else ','.join(intlist)

		纵轴参数= self._纵轴参数
		公司信息= self._公司信息
		对数坐标底数= self._对数坐标底数

		全局指数开盘= self._全局指数日线['开盘']
		全局绘图开盘= self._全局绘图日线['开盘']
		目标日期序列= self._目标日期序列
		目标起始偏移= self._目标起始偏移
		目标结束偏移= self._目标结束偏移

		坐标起点= 纵轴参数['个股坐标起点']
		坐标终点= 纵轴参数['个股坐标终点']
		变更记录= 公司信息['股本变更记录']

		个股平面= self._个股平面

		fsize= 5.0

		#	首日总股本与流通股信息
		#====================================================================================================================================
		目标首日= 目标日期序列[0]
		前期记录= [rec for rec in 变更记录 if rec['变更日期'] <= 目标首日]

		if 前期记录:
			总股本= 整数分位表示(前期记录[-1]['总股本'])
			流通股= 整数分位表示(前期记录[-1]['流通股'])
		else:
			总股本= 'None'
			流通股= 'None'

		显示字串= '总股本: ' + 总股本 + '\n' + '流通股: ' + 流通股

		label= 个股平面.text(目标起始偏移, 寻找纵轴最大空隙(偏移=目标起始偏移), 显示字串, fontproperties=__font_properties__, color='0.7')
		label.set_fontsize(fsize)

		#	尾日总股本与流通股信息
		#====================================================================================================================================
		目标尾日= 目标日期序列[-1]
		前期记录= [rec for rec in 变更记录 if rec['变更日期'] <= 目标尾日]

		if 前期记录:
			总股本= 整数分位表示(前期记录[-1]['总股本'])
			流通股= 整数分位表示(前期记录[-1]['流通股'])
		else:
			总股本= 'None'
			流通股= 'None'

		显示字串= '总股本: ' + 总股本 + '\n' + '流通股: ' + 流通股

		label= 个股平面.text(目标结束偏移, 寻找纵轴最大空隙(偏移=目标结束偏移), 显示字串, fontproperties=__font_properties__, horizontalalignment='right', color='0.7')
		label.set_fontsize(fsize)



	def 绘制日期提示(self):
		'''

		'''
		个股平面= self._个股平面
		横轴参数= self._横轴参数
		纵轴参数= self._纵轴参数
		全局日期序列= self._全局日期序列

		每月首日偏移= 横轴参数['每月首日偏移']
		每周首日偏移= 横轴参数['每周首日偏移']

		坐标起点= 纵轴参数['个股坐标起点']
		坐标终点= 纵轴参数['个股坐标终点']

		# 每月第一个交易日
		for iy in [坐标起点*1.2, 坐标终点/1.12]:
			for ix in 每月首日偏移:
				newlab= 个股平面.text(ix-1, iy, 全局日期序列[ix])
				newlab.set_font_properties(__font_properties__)
				newlab.set_color('0.3')
				newlab.set_fontsize(4)
				newlab.set_rotation('vertical')
				#	newlab.set_horizontalalignment('left')
				#	newlab.set_verticalalignment('center')
				#	newlab.set_verticalalignment('bottom')
				newlab.set_zorder(0)		# XXX: 放在底层

		# 每周第一个交易日，根据这个可以推算出全部确切的日期。
		for iy in [坐标起点*1.08, 坐标终点/1.03]:
			for ix in 每周首日偏移:
				newlab= 个股平面.text(ix-0.8, iy, 全局日期序列[ix])
				newlab.set_font_properties(__font_properties__)
				newlab.set_color('0.3')
				newlab.set_fontsize(3)
				newlab.set_rotation('vertical')
				#	newlab.set_horizontalalignment('left')
				#	newlab.set_verticalalignment('top')	# 不行
				#	newlab.set_verticalalignment('center')
				#	newlab.set_verticalalignment('bottom')
				newlab.set_zorder(0)		# XXX: 放在底层



	def 绘制价格提示(self):
		'''

		'''

		个股平面= self._个股平面
		横轴参数= self._横轴参数
		纵轴参数= self._纵轴参数

		每月首日偏移= 横轴参数['每月首日偏移']

		个股主坐标值= 纵轴参数['个股主坐标值']
		个股副坐标值= 纵轴参数['个股副坐标值']
		指数主坐标值= 纵轴参数['指数主坐标值']
		指数副坐标值= 纵轴参数['指数副坐标值']

		for iy, iy2 in zip(sorted(个股主坐标值[:-1] + 个股副坐标值[1:-1]), sorted(指数主坐标值[:-1] + 指数副坐标值[1:-1])):
			for ix in 每月首日偏移[1:-1:3]:
				newlab= 个股平面.text( ix+6, iy*1.001, str(iy/1000.0) + ' / ' + str(round(iy2/1000.0, 3)) )
				newlab.set_font_properties(__font_properties__)
				newlab.set_color('0.3')
				newlab.set_fontsize(3)
				newlab.set_zorder(0)		# XXX: 放在底层



	def 绘制常用辅助标记(self):
		'''

		'''

		def 绘制指数均线拐点():
			'''

			'''
			均线走势标记= 指数衍生行情['均线走势标记集']

			for n in 指数衍生均线.keys():
				均线序列= 指数衍生均线[n]
				走势标记= 均线走势标记[n]

				拐点序列= [ (目标日期序列.index(日期), 数值, 标记) for 日期, 数值, 标记 in zip(指数衍生日期, 均线序列, 走势标记) \
						if 日期>=目标首日 and 日期<=目标尾日 and 标记 in ('v', '^') ]

				底点序列= [None] * 目标行情长度
				顶点序列= [None] * 目标行情长度
				for 偏移, 数值, 标记 in 拐点序列:
					if 标记=='v':
						底点序列[偏移]= 数值
					elif 标记=='^':
						顶点序列[偏移]= 数值

				底点阵列= numpy.array(底点序列)
				顶点阵列= numpy.array(顶点序列)

				color=  'white'  if n < 10 else \
					'yellow' if n < 30 else \
					'cyan'   if n < 60 else \
					'magenta'

				指数平面.plot(横轴坐标序列, 底点阵列, marker=6, color=color, label='指数均线底点_'+str(n), \
					markersize=2.3, markeredgecolor=color, markeredgewidth=0.0, alpha=0.5)
				指数平面.plot(横轴坐标序列, 顶点阵列, marker=7, color=color, label='指数均线顶点_'+str(n), \
					markersize=2.3, markeredgecolor=color, markeredgewidth=0.0, alpha=0.5)



		def 绘制三日线拐点关键度():
			'''

			'''
			三日线拐点= 个股衍生行情['三日线走势拐点']
			中线阈值= 30
			长线阈值= 90

			for 拐点 in 三日线拐点:
				关键度= 拐点['关键度']
				if 关键度 < 中线阈值:
					continue

				偏移= 拐点['偏移']
				日期= 个股衍生日期[偏移]
				if 日期 < 目标首日 or 日期 > 目标尾日:
					continue

				类型= 拐点['类型']
				位置= 三日线[偏移] if 复权绘图 else 三日线[目标日期序列.index(日期)]

				横标= 全局日期序列.index(日期)
				纵标= 位置*1.01 if 类型=='^' else 位置/1.01

				# 添加文字注释
				文字= str(关键度)
				#	文字= str(关键度) + '(' + str(偏移) + ')'
				valign= 'bottom' if 类型=='^' else 'top'
				if 关键度 < 中线阈值:
					fsize= 2.3
					weight= 300
				elif 关键度 < 长线阈值:
					fsize= 2.7
					weight= 600
				else:
					fsize= 3.3
					weight= 900

				注释= 个股平面.text(横标, 纵标, 文字, weight=weight, verticalalignment=valign, horizontalalignment='left', color='white', alpha=0.7)
				注释.set_fontsize(fsize)



		def 绘制个股均线拐点():
			'''

			'''
			均线走势标记= 个股衍生行情['均线走势标记集']

			for n in 个股衍生均线.keys():
				走势标记= 均线走势标记[n]

				if 复权绘图:
					均线序列= 个股衍生均线[n]	# 使用复权均线
					拐点序列= [ (目标日期序列.index(日期), 数值, 标记) for 日期, 数值, 标记 in zip(个股衍生日期, 均线序列, 走势标记) \
							if 日期>=目标首日 and 日期<=目标尾日 and 标记 in ('v', '^') ]
					底点序列= [None] * 目标行情长度
					顶点序列= [None] * 目标行情长度
					for 偏移, 数值, 标记 in 拐点序列:
						if 标记=='v':
							底点序列[偏移]= 数值
						elif 标记=='^':
							顶点序列[偏移]= 数值
				else:
					均线序列= 目标绘图均线[n]	# 使用未复权的均线
					拐点序列= [ (目标日期序列.index(日期), 日期, 标记) for 日期, 标记 in zip(个股衍生日期, 走势标记) \
							if 日期>=目标首日 and 日期<=目标尾日 and 标记 in ('v', '^') ]
					底点序列= [None] * 目标行情长度
					顶点序列= [None] * 目标行情长度
					for 偏移, 日期, 标记 in 拐点序列:
						if 标记=='v':
							底点序列[偏移]= 均线序列[目标日期序列.index(日期)]
						elif 标记=='^':
							顶点序列[偏移]= 均线序列[目标日期序列.index(日期)]

				底点阵列= numpy.array(底点序列)
				顶点阵列= numpy.array(顶点序列)

				color=  'white'  if n < 10 else \
					'yellow' if n < 30 else \
					'cyan'   if n < 60 else \
					'magenta'

				个股平面.plot(横轴坐标序列, 底点阵列, marker=6, color=color, label='个股均线底点_'+str(n), \
					markersize=2.3, markeredgecolor=color, markeredgewidth=0.0, alpha=0.7)

				个股平面.plot(横轴坐标序列, 顶点阵列, marker=7, color=color, label='个股均线顶点_'+str(n), \
					markersize=2.3, markeredgecolor=color, markeredgewidth=0.0, alpha=0.7)



		def 绘制三日线波段():
			'''

			'''
			阶梯记录= 个股衍生行情['三日线走势阶梯']

			for 记录 in 阶梯记录:
				升幅= 记录['升幅']
				升跨= 记录['升跨']
				降幅= 记录['降幅']
				降跨= 记录['降跨']

				前底偏移= 记录['前底偏移']
				顶点偏移= 记录['顶点偏移']
				后底偏移= 顶点偏移 + 降跨
				前底日期= 个股衍生日期[前底偏移]
				顶点日期= 个股衍生日期[顶点偏移]
				后底日期= 个股衍生日期[后底偏移]

				# 上升波段
				if 前底日期>=目标首日 and 顶点日期<=目标尾日 and 升幅>=900.0:
					横标= 全局日期序列.index(前底日期) + 0.5
					纵标= 三日线[前底偏移] if 复权绘图 else 三日线[目标日期序列.index(前底日期)]
					宽度= 全局日期序列.index(顶点日期) - 横标 + 0.5
					高度= 三日线[顶点偏移]-纵标 if 复权绘图 else 三日线[目标日期序列.index(顶点日期)]-纵标
					rectobj= patches.Rectangle((横标, 纵标), 宽度, 高度, fill=True, edgecolor=None, facecolor='magenta', linewidth=0.3, alpha=0.1)
					rectobj.set_zorder(-1)	# 放在底层
					个股平面.add_patch(rectobj)

					文字 =  str(round(升幅, 2)) 
					文字 += '\n' + str(round(升幅/升跨, 2))
					文字 += '\n' + str(升跨)
					注释= 个股平面.text(横标, 纵标, 文字, fontproperties=__font_properties__, verticalalignment='top', horizontalalignment='left', color=__color_gray70__)
					注释.set_fontsize(2.5)

				# 下降波段
				if 顶点日期>=目标首日 and 后底日期<=目标尾日 and 降幅<=-900.0:
					横标= 全局日期序列.index(顶点日期) + 0.5
					纵标= 三日线[后底偏移] if 复权绘图 else 三日线[目标日期序列.index(后底日期)]
					宽度= 全局日期序列.index(后底日期) - 横标 + 0.5
					高度= 三日线[顶点偏移]-纵标 if 复权绘图 else 三日线[目标日期序列.index(顶点日期)]-纵标
					rectobj= patches.Rectangle((横标, 纵标), 宽度, 高度, fill=True, edgecolor=None, facecolor='cyan', linewidth=0.3, alpha=0.1)
					rectobj.set_zorder(-1)	# 放在底层
					个股平面.add_patch(rectobj)

					文字 =  str(round(降幅, 2)) 
					文字 += '\n' + str(round(降幅/降跨, 2))
					文字 += '\n' + str(降跨)
					注释= 个股平面.text(横标, 纵标, 文字, fontproperties=__font_properties__, verticalalignment='top', horizontalalignment='left', color=__color_gray70__)
					注释.set_fontsize(2.5)



		横轴坐标序列= self._横轴坐标序列
		目标行情长度= self._目标行情长度
		目标日期序列= self._目标日期序列
		全局日期序列= self._全局日期序列
		目标首日= 目标日期序列[0]
		目标尾日= 目标日期序列[-1]

		指数衍生行情= self._指数衍生行情
		个股衍生行情= self._个股衍生行情

		指数衍生日期= 指数衍生行情['日期']
		个股衍生日期= 个股衍生行情['日期']

		复权绘图= self._复权绘图

		#	三日线= 个股衍生均线[3] if 复权绘图 else 目标绘图均线[3]

		指数平面= self._指数平面
		个股平面= self._个股平面

		if self._绘制指数均线:
			指数衍生均线= 指数衍生行情['均线集']
			绘制指数均线拐点()
		if self._绘制个股均线:
			目标绘图均线= self._目标绘图均线
			个股衍生均线= 个股衍生行情['均线集']
			绘制个股均线拐点()

		#	绘制三日线波段()
		#	绘制三日线拐点关键度()



	def 绘图(self):
		'''

		'''
		self.绘制指数行情走势()
		self.绘制个股行情走势()
		if self._绘制指数均线:
			self.绘制指数均线走势()
		if self._绘制个股均线:
			self.绘制个股均线走势()
		
		self.绘制个股开收中线走势()
		
		self.绘制流通股本变更提示()
		self.绘制复权提示()
		self.绘制首尾股本信息()
		self.绘制日期提示()
		self.绘制价格提示()

		self.绘制常用辅助标记()

		if self._定制绘图函数:
			用户参数= self._定制绘图参数
		
			用户参数.update( 
				{	'日线子图': self,
					'ilogger': self._ilogger,
					'Public': Public, 
				}
			)

			self._定制绘图函数(**用户参数)



		#	日线活跃度.绘图(日线子图=self, 环境参数=环境参数)
		#	短线组合形态.绘图(日线子图=self, 环境参数=环境参数)
		#	三日线涨幅差值.绘图(日线子图=self, 环境参数=环境参数)
		#	日线情势判断.绘图(日线子图=self, 环境参数=环境参数)



