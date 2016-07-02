# -*- coding: utf-8 -*-



import itertools
import numpy

import matplotlib.spines as spines
import matplotlib.ticker as ticker
import matplotlib.font_manager as font_manager 



import Public.Public as Public



__color_gold__= '#FDDB05'
__font_properties__= font_manager.FontProperties(fname='/usr/share/fonts/truetype/wqy/wqy-zenhei.ttc')



__横轴倍率__= 10.0 / 230.0
__纵轴倍率__= 0.3





class 日线换手子图:

	def __init__(self, parent, 绘图数据):
		'''

		'''
		self._parent= parent
		self._ilogger= Public.IndentLogger(logger=parent._ilogger._logger, indent=parent._ilogger._indent+1)

		# 原始数据
		self._任务参数= 绘图数据['任务参数']

		# 行情数据
		日线价格子图= parent._日线价格子图

		日线行情= 日线价格子图.返回目标日线数据()

		self._目标指数日线= 日线行情['目标指数日线']
		self._目标绘图日线= 日线行情['目标绘图日线']

		self._目标指数换手= self._目标指数日线['换手率']
		self._目标绘图换手= self._目标绘图日线['换手率']

		# 行情衍生数据
		附加行情= 日线价格子图.返回行情附加数据()

		self._横轴坐标序列= 附加行情['横轴坐标序列']
		self._目标行情长度= 附加行情['目标行情长度']
                                                  
		self._目标指数上涨= 附加行情['目标指数上涨']
		self._目标指数下跌= 附加行情['目标指数下跌']
		self._目标指数平盘= 附加行情['目标指数平盘']
                                                  
		self._目标绘图上涨= 附加行情['目标绘图上涨']
		self._目标绘图下跌= 附加行情['目标绘图下跌']
		self._目标绘图平盘= 附加行情['目标绘图平盘']

		# 平面对象
		self._指数平面= None
		self._指数横轴= None
		self._指数纵轴= None

		self._个股平面= None
		self._个股横轴= None
		self._个股纵轴= None

		# 横轴参数、纵轴参数
		self._横轴参数= 日线价格子图.返回横轴参数()
		self._纵轴参数= self.计算纵轴参数()



	def 计算纵轴参数(self):
		'''

		'''

		def _compute_torange(maxto, tostep):
			return int(round((maxto + tostep/2.0 - 1) / float(tostep), 0))
		
		def _compute_tostep(maxto):
			'''
			maxto 是 换手率 最大值。返回每格单位（最小 500, 代表 0.5%）以及格数
			'''
			for i in range(9):
				if maxto > (4 * 500 * (2**i)):	# 换手率最大是 100000, 代表 100%
					continue
				else:
					tostep= 500 * (2**i)
					torange= _compute_torange(maxto, tostep)
					break
			return (tostep, torange)

		指数换手= self._目标指数换手
		个股换手= self._目标绘图换手

		个股最大= max( [nr for nr in 个股换手 if nr is not None] )
		个股步进, \
		个股格数= _compute_tostep(个股最大)

		指数最大= max(指数换手)
		指数步进, \
		指数格数= _compute_tostep(指数最大)

		纵轴格数= max(个股格数, 指数格数)
		纵轴尺寸= 纵轴格数 * 1.0

		指数坐标终点= 指数步进 * 纵轴格数
		个股坐标终点= 个股步进 * 纵轴格数

		指数主坐标值= [指数步进*i for i in range(纵轴格数)]
		指数副坐标值= list( itertools.chain.from_iterable( mi for mi in [[ma + (指数步进/4.0)*i for i in range(1, 4)] for ma in 指数主坐标值] ) )

		个股主坐标值= [个股步进*i for i in range(纵轴格数)]
		个股副坐标值= list( itertools.chain.from_iterable( mi for mi in [[ma + (个股步进/4.0)*i for i in range(1, 4)] for ma in 个股主坐标值] ) )

		纵轴参数= {
			'指数步进': 指数步进,
			'个股步进': 个股步进,
			'纵轴格数': 纵轴格数,
			'纵轴尺寸': 纵轴尺寸,
			'纵轴高度': 纵轴尺寸 * __纵轴倍率__,
			'指数坐标终点': 指数坐标终点,
			'个股坐标终点': 个股坐标终点,
			'指数主坐标值': 指数主坐标值,
			'指数副坐标值': 指数副坐标值,
			'个股主坐标值': 个股主坐标值,
			'个股副坐标值': 个股副坐标值,
		}

		return 纵轴参数



	def 返回纵轴高度(self):
		'''

		'''
		return self._纵轴参数['纵轴高度']



	def 平面初始化(self, 图片对象, 子图偏移, 全图大小, sharex):
		'''

		'''
		#	计算 布局参数
		#==================================================================================================================================================
		子图横移, \
		子图纵移= 子图偏移
		
		全图宽度, \
		全图高度= 全图大小

		本图宽度= self._横轴参数['横轴宽度']
		本图高度= self._纵轴参数['纵轴高度']

		布局参数= ( 子图横移/全图宽度, 子图纵移/全图高度, 本图宽度/全图宽度, 本图高度/全图高度 )

		#	指数部分
		#==================================================================================================================================================
		指数平面= 图片对象.add_axes(布局参数, axis_bgcolor='black', sharex=sharex)
		指数平面.set_axisbelow(True)	# 网格线放在底层

		for 方位, 边框 in 指数平面.spines.items():	# 方位: 'left' | 'right' | 'top' | 'bottom'
			边框.set_color(__color_gold__)

		指数横轴= 指数平面.get_xaxis()
		指数纵轴= 指数平面.get_yaxis()

		self._指数平面= 指数平面
		self._指数横轴= 指数横轴
		self._指数纵轴= 指数纵轴

		self.设置指数横轴()
		self.设置指数纵轴()

		#	个股部分
		#==================================================================================================================================================
		个股平面= 指数平面.twinx()
		个股平面.set_axis_bgcolor('black')
		个股平面.set_axisbelow(True)	# 网格线放在底层

		#	for 方位, 边框 in 个股平面.spines.items():	# 方位: 'left' | 'right' | 'top' | 'bottom'
		#		边框.set_color(__color_gold__)

		个股横轴= 个股平面.get_xaxis()
		个股纵轴= 个股平面.get_yaxis()

		self._个股平面= 个股平面
		self._个股横轴= 个股横轴
		self._个股纵轴= 个股纵轴

		self.设置个股横轴()
		self.设置个股纵轴()



	def 设置指数横轴(self):
		'''

		'''
		任务参数= self._任务参数

		指数平面= self._指数平面
		指数横轴= self._指数横轴

		横轴参数= self._横轴参数
		坐标起点= 横轴参数['坐标起点']
		坐标终点= 横轴参数['坐标终点']

		指数横轴.grid(True, 'major', color='0.3', linestyle='solid', linewidth=0.2)
		指数横轴.grid(True, 'minor', color='0.3', linestyle='dotted', linewidth=0.15)

		指数平面.set_xlim(坐标起点, 坐标终点)

		xMajorLocator= 横轴参数['xMajorLocator']
		xMinorLocator= 横轴参数['xMinorLocator']
		xMajorFormatter= 横轴参数['xMajorFormatter']
		xMinorFormatter= 横轴参数['xMinorFormatter']

		指数横轴.set_major_locator(xMajorLocator)
		指数横轴.set_minor_locator(xMinorLocator)

		指数横轴.set_major_formatter(xMajorFormatter)
		指数横轴.set_minor_formatter(xMinorFormatter)

		if 任务参数['绘制实盘']:
			# 设为不可见
			for 主坐标 in axes.get_xticklabels(minor=False):
				主坐标.set_visible(False)

			for 副坐标 in axes.get_xticklabels(minor=True):
				副坐标.set_visible(False)
		else:
			for 主坐标 in 指数平面.get_xticklabels(minor=False):
				主坐标.set_fontsize(4)
				主坐标.set_horizontalalignment('right')
				主坐标.set_rotation('45')

			for 副坐标 in 指数平面.get_xticklabels(minor=True):
				副坐标.set_fontsize(4)
				副坐标.set_color('blue')
				副坐标.set_horizontalalignment('right')
				副坐标.set_rotation('45')


	def 设置指数纵轴(self):
		'''

		'''
		平面对象= self._指数平面
		指数纵轴= self._指数纵轴
		纵轴参数= self._纵轴参数

		主坐标值= 纵轴参数['指数主坐标值']
		副坐标值= 纵轴参数['指数副坐标值']
		坐标终点= 纵轴参数['指数坐标终点']

		指数纵轴.grid(True, 'major', color='0.3', linestyle='solid', linewidth=0.2)
		指数纵轴.grid(True, 'minor', color='0.3', linestyle='solid', linewidth=0.1)

		平面对象.set_ylim(0, 坐标终点)

		yMajorLocator= ticker.FixedLocator(numpy.array(主坐标值))
		def y_major_formatter(num, pos=None):
			return str(round(num/1000.0, 2)) + '%'
		yMajorFormatter= ticker.FuncFormatter(y_major_formatter)

		指数纵轴.set_major_locator(yMajorLocator)
		指数纵轴.set_major_formatter(yMajorFormatter)

		for 主坐标 in 平面对象.get_yticklabels(minor=False):
			主坐标.set_font_properties(__font_properties__)
			主坐标.set_fontsize(5)	# 这个必须放在前一句后面，否则作用会被覆盖


		yMinorLocator= ticker.FixedLocator(numpy.array(副坐标值))
		def y_minor_formatter(num, pos=None):
			return str(round(num/1000.0, 3)) + '%'
		yMinorFormatter= ticker.FuncFormatter(y_minor_formatter)

		指数纵轴.set_minor_locator(yMinorLocator)
		指数纵轴.set_minor_formatter(yMinorFormatter)

		for 副坐标 in 平面对象.get_yticklabels(minor=True):
			副坐标.set_font_properties(__font_properties__)
			副坐标.set_fontsize(4)	# 这个必须放在前一句后面，否则作用会被覆盖



	def 设置个股横轴(self):
		'''

		'''
		个股平面= self._个股平面
		个股横轴= self._个股横轴

		横轴参数= self._横轴参数
		坐标起点= 横轴参数['坐标起点']
		坐标终点= 横轴参数['坐标终点']

		#	个股横轴.grid(True, 'major', color='0.3', linestyle='solid', linewidth=0.2)
		#	个股横轴.grid(True, 'minor', color='0.3', linestyle='dotted', linewidth=0.15)

		个股平面.set_xlim(坐标起点, 坐标终点)

		xMajorLocator= 横轴参数['xMajorLocator']
		xMinorLocator= 横轴参数['xMinorLocator']

		个股横轴.set_major_locator(xMajorLocator)
		个股横轴.set_minor_locator(xMinorLocator)

		for 主坐标 in 个股平面.get_xticklabels(minor=False):
			主坐标.set_visible(False)

		for 副坐标 in 个股平面.get_xticklabels(minor=True):
			副坐标.set_visible(False)



	def 设置个股纵轴(self):
		'''

		'''

		平面对象= self._个股平面
		个股纵轴= self._个股纵轴
		纵轴参数= self._纵轴参数

		主坐标值= 纵轴参数['个股主坐标值']
		副坐标值= 纵轴参数['个股副坐标值']
		坐标终点= 纵轴参数['个股坐标终点']

		# 坐标线
		#	个股纵轴.grid(True, 'major', color='0.3', linestyle='solid', linewidth=0.2)
		#	个股纵轴.grid(True, 'minor', color='0.3', linestyle='solid', linewidth=0.1)

		# 设置坐标范围
		平面对象.set_ylim(0, 坐标终点)

		# 主坐标点
		yMajorLocator= ticker.FixedLocator(numpy.array(主坐标值))
		def y_major_formatter(num, pos=None):
			return str(round(num/1000.0, 2)) + '%'
		yMajorFormatter= ticker.FuncFormatter(y_major_formatter)

		个股纵轴.set_major_locator(yMajorLocator)
		个股纵轴.set_major_formatter(yMajorFormatter)

		for 主坐标 in 平面对象.get_yticklabels(minor=False):
			主坐标.set_font_properties(__font_properties__)
			主坐标.set_fontsize(5)	# 这个必须放在前一句后面，否则作用会被覆盖

		# 副坐标点
		yMinorLocator= ticker.FixedLocator(numpy.array(副坐标值))
		def y_minor_formatter(num, pos=None):
			return str(round(num/1000.0, 3)) + '%'
		yMinorFormatter= ticker.FuncFormatter(y_minor_formatter)

		个股纵轴.set_minor_locator(yMinorLocator)
		个股纵轴.set_minor_formatter(yMinorFormatter)

		for 副坐标 in 平面对象.get_yticklabels(minor=True):
			副坐标.set_font_properties(__font_properties__)
			副坐标.set_fontsize(4)	# 这个必须放在前一句后面，否则作用会被覆盖



	def 绘制指数换手(self):
		'''

		'''
		横轴坐标序列= self._横轴坐标序列
		平面对象= self._指数平面

		行情长度= self._目标行情长度
		上涨序列= self._目标指数上涨
		下跌序列= self._目标指数下跌
		平盘序列= self._目标指数平盘
		换手序列= self._目标指数换手

		换手阵列= numpy.array(换手序列)
		起点阵列= numpy.zeros(行情长度)

		lwidth, alpha= (0.7, 0.5)

		if True in 上涨序列:
			平面对象.vlines(横轴坐标序列[上涨序列], 起点阵列[上涨序列], 换手阵列[上涨序列], edgecolor='0.7', linewidth=lwidth, label='_nolegend_', alpha=alpha)
		if True in 下跌序列:
			平面对象.vlines(横轴坐标序列[下跌序列], 起点阵列[下跌序列], 换手阵列[下跌序列], edgecolor='0.3', linewidth=lwidth, label='_nolegend_', alpha=alpha)
		if True in 平盘序列:
			平面对象.vlines(横轴坐标序列[平盘序列], 起点阵列[平盘序列], 换手阵列[平盘序列], edgecolor='0.7', linewidth=lwidth, label='_nolegend_', alpha=1.0)



	def 绘制个股换手(self):
		'''

		'''
		横轴坐标序列= self._横轴坐标序列
		平面对象= self._个股平面

		行情长度= self._目标行情长度
		上涨序列= self._目标绘图上涨
		下跌序列= self._目标绘图下跌
		平盘序列= self._目标绘图平盘
		换手序列= self._目标绘图换手

		横轴参数= self._横轴参数
		横标起点= 横轴参数['坐标起点']
		横标终点= 横轴参数['坐标终点']
		每月首日偏移= 横轴参数['每月首日偏移']

		换手阵列= numpy.array(换手序列)
		起点阵列= numpy.zeros(行情长度)

		lwidth= 3.0

		if True in 上涨序列:
			平面对象.vlines(横轴坐标序列[上涨序列], 起点阵列[上涨序列], 换手阵列[上涨序列], edgecolor='red', linewidth=lwidth, label='_nolegend_', alpha=0.5)
		if True in 下跌序列:
			平面对象.vlines(横轴坐标序列[下跌序列], 起点阵列[下跌序列], 换手阵列[下跌序列], edgecolor='green', linewidth=lwidth, label='_nolegend_', alpha=0.5)
		if True in 平盘序列:
			平面对象.vlines(横轴坐标序列[平盘序列], 起点阵列[平盘序列], 换手阵列[平盘序列], edgecolor='0.7', linewidth=lwidth, label='_nolegend_', alpha=1.0)

		# 绘制 平均换手数值（直线）
		个股换手= [nr for nr in 换手序列 if nr is not None]
		平均换手= sum(个股换手) / float(len(个股换手))
		平面对象.plot([横标起点, 横标终点], [平均换手, 平均换手], '-', color='yellow', linewidth=0.2, alpha=0.7)

		# 平均换手率数值在图中间的显示
		for ix in 每月首日偏移[2:-1:3]:
			newlab= 平面对象.text(ix+8, 平均换手, str(round(平均换手/1000.0, 2)) + '%')
			newlab.set_font_properties(__font_properties__)
			newlab.set_color('yellow')
			newlab.set_fontsize(3)



	def 绘制换手提示(self):
		'''

		'''
		def formatter(nr):
			return str(round(nr/1000.0, 2)) + '%'

		平面对象= self._指数平面
		纵轴参数= self._纵轴参数

		指数步进= 纵轴参数['指数步进']
		个股步进= 纵轴参数['个股步进']
		纵轴格数= 纵轴参数['纵轴格数']

		shift= 7
		横轴参数= self._横轴参数
		每月首日偏移= 横轴参数['每月首日偏移']
		for iy, iy2 in zip( range(int(指数步进/2.0), 指数步进*纵轴格数, int(指数步进/2.0)), range(int(个股步进/2.0), 个股步进*纵轴格数, int(个股步进/2.0)) ):
			for ix in 每月首日偏移[1:-1:3]:
				newlab= 平面对象.text(ix+shift, iy, formatter(iy2) + ' / ' + formatter(iy))
				newlab.set_font_properties(__font_properties__)
				newlab.set_color('0.3')
				newlab.set_fontsize(3)
				newlab.set_zorder(0)		# XXX: 放在底层



	def 绘图(self):
		'''

		'''
		self.绘制指数换手()
		self.绘制个股换手()
		self.绘制换手提示()





