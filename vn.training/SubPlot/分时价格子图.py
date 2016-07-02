# -*- coding: utf-8 -*-





import datetime
import numpy
import math



import matplotlib.ticker as ticker
import matplotlib.font_manager as font_manager 



import Public.Public as Public





__font_properties__= font_manager.FontProperties(fname='/usr/share/fonts/truetype/wqy/wqy-zenhei.ttc')

__纵轴倍率__= 3.0





class 分时价格子图:
	
	def __init__(self, parent, 目标日期, 绘图数据):
		'''

		'''
		self._parent= parent
		self._ilogger= Public.IndentLogger(logger=parent._ilogger._logger, indent=parent._ilogger._indent+1)

		# 原始数据
		任务参数= 绘图数据['任务参数']
		self._公司信息= 绘图数据['公司信息']

		# 当日数据
		当日数据= 绘图数据['分时数据'][目标日期]
		self._目标日期= 目标日期
		#	self._日期对象= 当日数据['日期对象']
		#	self._时间常数= 当日数据['时间常数']

		#	横轴参数（需放在前面）
		#===================================================================================================
		self._横轴参数= parent._横轴参数
		self._纵轴参数= None	# XXX: 现在还不能计算，因为上下限与其他子图有关。
		self._坐标底数= 1.1

		#	个股行情
		#===================================================================================================

		# 分时行情是否存在
		self._个股行情有效= 当日数据['个股行情有效']

		# 日线数据
		self._个股当日开盘= 当日数据['个股当日开盘']
		self._个股当日最高= 当日数据['个股当日最高']
		self._个股前日收盘= 当日数据['个股前日收盘']	# 前日收盘可能是 None
		self._个股当日最低= 当日数据['个股当日最低']

		if self._个股行情有效:
			# 分时数据
			个股分时行情= 当日数据['个股分时行情']
			self._个股价格序列= 个股分时行情['价格序列']

			# 分时行情坐标序列
			self._个股调整时间= parent._个股调整时间
			self._个股坐标序列= parent._个股坐标序列

			# 分时衍生数据（均线等）
			self._分时格点粒度= 格点粒度= 任务参数['分时格点粒度']
			间隔点数= 任务参数['均线间隔点数']
			定时点数= 任务参数['均线定时点数']
			self._个股定时均线= Public.计算日内定时均线( \
				价格序列=self._个股价格序列, \
				调整时间序列=self._个股调整时间, \
				格点粒度=格点粒度, \
				间隔点数=间隔点数, \
				定时点数=定时点数, \
				需要规整=False \
			)
			for 均线 in self._个股定时均线.values():
				均线['坐标序列']= self._parent.计算调整时间序列坐标(调整时间序列=均线['时间序列'])
				均线['走势标记']= Public.计算走势标记(序列=均线['均线序列'])

		#	TODO: 指数行情
		#===================================================================================================

		# 日线数据
		self._指数当日开盘= 当日数据['指数当日开盘']
		self._指数当日最高= 当日数据['指数当日最高']
		self._指数前日收盘= 当日数据['指数前日收盘']	# 前日收盘可能是 None
		self._指数当日最低= 当日数据['指数当日最低']



		#	平面对象，留待后面初始化
		#===================================================================================================
		self._布局参数= None
		
		self._指数平面= None
		self._指数横轴= None
		self._指数纵轴= None

		self._个股平面= None
		self._个股横轴= None
		self._个股纵轴= None



	def 计算纵轴坐标区间(self):
		'''

		'''
		个股开盘= self._个股当日开盘
		指数开盘= self._指数当日开盘
		
		个股最高= max(self._个股前日收盘, self._个股当日最高) * 1.01 if self._个股前日收盘 else self._个股当日最高 * 1.01
		个股最低= min(self._个股前日收盘, self._个股当日最低) * 0.99 if self._个股前日收盘 else self._个股当日最低 * 0.99
		
		指数最高= self._指数当日最高 * 1.01
		指数最低= self._指数当日最低 * 0.99

		个股综合最高= max(个股最高, 指数最高*个股开盘/指数开盘)
		个股综合最低= min(个股最低, 指数最低*个股开盘/指数开盘)

		指数综合最高= max(指数最高, 个股最高*指数开盘/个股开盘)
		指数综合最低= min(指数最低, 个股最低*指数开盘/个股开盘)

		纵标区间= {}
		纵标区间['个股最高']= 个股综合最高
		纵标区间['个股最低']= 个股综合最低
		纵标区间['指数最高']= 指数综合最高
		纵标区间['指数最低']= 指数综合最低

		return 纵标区间



	def 计算纵轴参数(self, 坐标区间=None):
		'''

		'''
		def 计算个股坐标参数(基准价格, 坐标起点, 坐标终点):
			'''

			'''
			# 计算主坐标值
			步进= 基准价格 / 100.0
			主坐标值= [基准价格]

			当前价格= 基准价格 + 步进
			while 当前价格 < 坐标终点:
				主坐标值.append( round(当前价格, -1) )
				当前价格= 当前价格 + 步进

			当前价格= 基准价格 - 步进
			while 当前价格 > 坐标起点:
				主坐标值.append( round(当前价格, -1) )
				当前价格= 当前价格 - 步进

			主坐标值= sorted(set(主坐标值))

			# 计算副坐标值
			步进= max(round(基准价格*0.01/4.0, -1), 10.0)	# 选择一个步进值，10.0 代表最小刻度: 0.01元
			副坐标值= []
			当前价格= round(坐标起点+5.0, -1)
			while 当前价格 < 坐标终点:
				副坐标值.append(当前价格)
				当前价格= 当前价格 + 步进
			副坐标值= [价格 for 价格 in 副坐标值 if 价格 not in 主坐标值]

			坐标参数= {
				'个股主坐标值': 主坐标值,
				'个股副坐标值': 副坐标值,
			}

			return 坐标参数

		if 坐标区间 is None:
			坐标区间= self.计算纵轴坐标区间()

		个股坐标起点= 坐标区间['个股最低']
		个股坐标终点= 坐标区间['个股最高']
		纵轴尺寸= math.log(个股坐标终点, self._坐标底数) - math.log(个股坐标起点, self._坐标底数)
		纵轴高度= 纵轴尺寸 * __纵轴倍率__

		纵轴参数= {}
		纵轴参数['个股坐标起点']= 个股坐标起点
		纵轴参数['个股坐标终点']= 个股坐标终点
		纵轴参数['纵轴尺寸']= 纵轴尺寸
		纵轴参数['纵轴高度']= 纵轴高度

		# 指数部分，暂时这样
		纵轴参数['指数坐标起点']= 坐标区间['指数最低']
		纵轴参数['指数坐标终点']= 坐标区间['指数最高']

		基准价格= self._个股前日收盘 if self._个股前日收盘 else self._个股当日开盘
		纵轴参数['基准价格']= 基准价格
		纵轴参数.update( 计算个股坐标参数(基准价格=基准价格, 坐标起点=个股坐标起点, 坐标终点=个股坐标终点) )

		self._纵轴参数= 纵轴参数



	def 返回纵轴高度(self):
		'''

		'''
		return self._纵轴参数['纵轴高度']



	def 返回指数平面(self):
		'''

		'''
		return self._指数平面



	def 平面初始化(self, 图片对象, 子图偏移, 全图大小, sharex):
		'''

		'''
		# 计算自身的布局参数
		子图横移, \
		子图纵移= 子图偏移
		
		全图宽度, \
		全图高度= 全图大小
		
		本图宽度= self._横轴参数['横轴宽度']
		本图高度= self._纵轴参数['纵轴高度']

		布局参数= (子图横移/全图宽度, 子图纵移/全图高度, 本图宽度/全图宽度, 本图高度/全图高度)

		self._布局参数= 布局参数
		坐标底数= self._坐标底数

		#	指数部分
		#=======================================================================================

		# XXX: 指数与个股布局参数一样的话，label 一定要设成不一样，见 add_axes() 官方文档。
		指数平面= 图片对象.add_axes(布局参数, axis_bgcolor='none', label='指数平面', sharex=sharex)	
		指数平面.set_frame_on(False)
		指数平面.set_axisbelow(True)			# 网格线放在底层
		指数平面.set_yscale('log', basey=坐标底数)	# 使用对数坐标

		指数横轴= 指数平面.get_xaxis()
		指数纵轴= 指数平面.get_yaxis()

		self._指数平面= 指数平面
		self._指数横轴= 指数横轴
		self._指数纵轴= 指数纵轴

		self.设置指数横轴()
		self.设置指数纵轴()

		#	个股部分
		#=======================================================================================
		#	个股平面= 指数平面.twinx()	# XXX: twinx 有问题，使用了以后指数的 ticks 就关不掉。可能是 bug

		# XXX: 指数与个股布局参数一样的话，label 一定要设成不一样，见 add_axes() 官方文档。
		个股平面= 图片对象.add_axes(布局参数, axis_bgcolor='none', label='个股平面', sharex=sharex)
		个股平面.set_frame_on(False)
		个股平面.set_axisbelow(True)		# 网格线放在底层
		个股平面.set_yscale('log', basey=坐标底数)		# 使用对数坐标

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
		指数平面= self._指数平面
		指数横轴= self._指数横轴
		横轴参数= self._横轴参数

		指数横轴.set_ticks_position('none')

		#=================================================================================
		坐标起点= 横轴参数['坐标起点']
		坐标终点= 横轴参数['坐标终点']

		xMajorLocator= 横轴参数['xMajorLocator']
		xMinorLocator= 横轴参数['xMinorLocator']
		xMajorFormatter= 横轴参数['xMajorFormatter']
		xMinorFormatter= 横轴参数['xMinorFormatter']

		指数横轴.grid(True, 'major', color='0.3', linestyle='solid', linewidth=0.2)
		指数横轴.grid(True, 'minor', color='0.3', linestyle='dotted', linewidth=0.15)

		指数平面.set_xlim(坐标起点, 坐标终点)
		指数横轴.set_major_locator(xMajorLocator)
		指数横轴.set_minor_locator(xMinorLocator)
		#=================================================================================

		for 主坐标 in 指数平面.get_xticklabels(minor=False):
			主坐标.set_visible(False)
		for 副坐标 in 指数平面.get_xticklabels(minor=True):
			副坐标.set_visible(False)



	def 设置指数纵轴(self):
		'''

		'''
		指数平面= self._指数平面
		指数纵轴= self._指数纵轴
		纵轴参数= self._纵轴参数

		坐标起点= 纵轴参数['指数坐标起点']
		坐标终点= 纵轴参数['指数坐标终点']

		指数平面.set_ylim(坐标起点, 坐标终点)
		#	指数纵轴.set_label_position('left')	# XXX: 不顶用
		指数纵轴.set_ticks_position('none')

		for 主坐标 in 指数平面.get_yticklabels(minor=False):
			主坐标.set_visible(False)
		for 副坐标 in 指数平面.get_yticklabels(minor=True):
			副坐标.set_visible(False)



	def 设置个股横轴(self):
		'''

		'''
		个股平面= self._个股平面
		个股横轴= self._个股横轴
		横轴参数= self._横轴参数

		个股横轴.set_ticks_position('none')

		坐标起点= 横轴参数['坐标起点']
		坐标终点= 横轴参数['坐标终点']

		个股平面.set_xlim(坐标起点, 坐标终点)

		#	xMajorLocator= 横轴参数['xMajorLocator']
		#	xMinorLocator= 横轴参数['xMinorLocator']
		#	xMajorFormatter= 横轴参数['xMajorFormatter']
		#	xMinorFormatter= 横轴参数['xMinorFormatter']

		#	个股横轴.grid(True, 'major', color='0.3', linestyle='solid', linewidth=0.2)
		#	个股横轴.grid(True, 'minor', color='0.3', linestyle='dotted', linewidth=0.15)

		#	个股横轴.set_major_locator(xMajorLocator)
		#	个股横轴.set_minor_locator(xMinorLocator)

		for 主坐标 in 个股平面.get_xticklabels(minor=False):
			主坐标.set_visible(False)
		for 副坐标 in 个股平面.get_xticklabels(minor=True):
			副坐标.set_visible(False)



	def 设置个股纵轴(self):
		'''

		'''
		个股平面= self._个股平面
		个股纵轴= self._个股纵轴
		纵轴参数= self._纵轴参数

		个股纵轴.set_ticks_position('none')

		坐标起点= 纵轴参数['个股坐标起点']
		坐标终点= 纵轴参数['个股坐标终点']

		主坐标值= 纵轴参数['个股主坐标值']
		副坐标值= 纵轴参数['个股副坐标值']

		#	个股纵轴.set_label_position('right')	# XXX: 不顶用

		个股纵轴.grid(True, 'major', color='0.3', linestyle='solid', linewidth=0.2)
		个股纵轴.grid(True, 'minor', color='0.3', linestyle='dotted', linewidth=0.15)

		个股平面.set_ylim(坐标起点, 坐标终点)

		# 主坐标点
		yMajorLocator= ticker.FixedLocator( numpy.array(主坐标值) )
		个股纵轴.set_major_locator(yMajorLocator)
		
		#	def y_major_formatter(num, pos=None):
		#		return str(round(num/1000.0, 3))
		#	yMajorFormatter= ticker.FuncFormatter(y_major_formatter)
		#	个股纵轴.set_major_formatter(yMajorFormatter)

		for 主坐标 in 个股平面.get_yticklabels(minor=False):
			主坐标.set_visible(False)

		# 副坐标点
		yMinorLocator= ticker.FixedLocator( numpy.array(副坐标值) )
		个股纵轴.set_minor_locator(yMinorLocator)

		#	def y_minor_formatter(num, pos=None):
		#		return str(round(num/1000.0, 3))
		#	yMinorFormatter= ticker.FuncFormatter(y_minor_formatter)
		#	个股纵轴.set_minor_formatter(yMinorFormatter)

		for 副坐标 in 个股平面.get_yticklabels(minor=True):
			副坐标.set_visible(False)



	def 绘图(self):
		'''

		'''
		self.绘制辅助标记()
		self.绘制个股价格走势()

		if self._个股行情有效:
			self.绘制个股价格均线()



	def 绘制个股价格走势(self):
		'''

		'''
		个股平面= self._个股平面

		# 特征价格
		横标起点, 横标终点= self._横轴参数['坐标起点'], self._横轴参数['坐标终点']

		if self._个股前日收盘:
			个股平面.plot((横标起点, 横标终点), (self._个股前日收盘, self._个股前日收盘), '-', color='lightblue', linewidth=0.7, alpha=0.5)
		个股平面.plot((横标起点, 横标终点), (self._个股当日开盘, self._个股当日开盘), '-', color='yellow', linewidth=0.7, alpha=0.5)
		个股平面.plot((横标起点, 横标终点), (self._个股当日最高, self._个股当日最高), '-', color='red', linewidth=0.7, alpha=0.3)
		个股平面.plot((横标起点, 横标终点), (self._个股当日最低, self._个股当日最低), '-', color='green', linewidth=0.7, alpha=0.5)

		if self._个股行情有效:
			坐标阵列= numpy.array(self._个股坐标序列)
			价格阵列= numpy.array(self._个股价格序列)
			# 价格走势
			个股平面.plot(坐标阵列, 价格阵列, 'o-', color='white', linewidth=0.15, label='_nolegend_', \
				markersize=0.3, markeredgecolor='white', markeredgewidth=0.1, alpha=1.0)





	def 绘制个股价格均线(self):
		'''

		'''
		个股平面= self._个股平面
		格点粒度= self._分时格点粒度
		定时均线= self._个股定时均线

		for 类别, 均线 in 定时均线.items():
			坐标序列= 均线['坐标序列']
			均线序列= 均线['均线序列']
			走势标记= 均线['走势标记']

			# 绘制均线
			坐标阵列= numpy.array(坐标序列)
			均线阵列= numpy.array(均线序列)

			lcolor= 'yellow'  if 类别*格点粒度 <= 300 else \
				'cyan'    if 类别*格点粒度 <= 600 else \
				'magenta'

			个股平面.plot(坐标阵列, 均线阵列, 'o-', color=lcolor, linewidth=0.1, label='_nolegend_', \
				markersize=0.2, markeredgecolor=lcolor, markeredgewidth=0.1, alpha=0.7)

			# 绘制均线拐点
			底点阵列= numpy.array([均值 if 标记=='v' else None for 均值, 标记 in zip(均线序列, 走势标记)])
			顶点阵列= numpy.array([均值 if 标记=='^' else None for 均值, 标记 in zip(均线序列, 走势标记)])

			个股平面.plot(坐标阵列, 底点阵列, '^', color=lcolor, label='均线底点', \
				markersize=1.5, markeredgecolor=lcolor, markeredgewidth=0.0, alpha=1.0)

			个股平面.plot(坐标阵列, 顶点阵列, 'v', color=lcolor, label='均线顶点', \
				markersize=1.5, markeredgecolor=lcolor, markeredgewidth=0.0, alpha=1.0)



	def 绘制辅助标记(self):
		'''

		'''
		指数平面= self._指数平面
		个股平面= self._个股平面
		横轴参数= self._横轴参数
		纵轴参数= self._纵轴参数
		公司信息= self._公司信息

		目标日期= self._目标日期

		指数纵标起点= 纵轴参数['指数坐标起点']
		指数纵标终点= 纵轴参数['指数坐标终点']

		个股纵标起点= 纵轴参数['个股坐标起点']
		个股纵标终点= 纵轴参数['个股坐标终点']

		标注位置= 横轴参数['标注位置']

		#	画公司名称、目标日期
		#============================================================================================================
		标注内容= 公司信息['个股代码'] + ' ' + 公司信息['个股简称'] + ' ' + 目标日期

		纵标= (指数纵标起点*指数纵标终点)**0.5
		指数平面.text( 标注位置['09:30'], 纵标, 标注内容, fontproperties=__font_properties__, \
			color='0.3', fontsize=27, alpha=0.3, verticalalignment='center')
		指数平面.text( 标注位置['15:00']-300.0, 纵标, 标注内容, fontproperties=__font_properties__, \
			color='0.3', fontsize=27, alpha=0.3, horizontalalignment='right', verticalalignment='center')

		#	画时间标记
		#============================================================================================================
		# 15 分钟主时间点
		for iy in [指数纵标起点*1.004, 指数纵标终点*0.993]:
			for ix, 时间, 表示 in zip(横轴参数['主坐标值'], 横轴参数['主标时间'], 横轴参数['主标表示']):
				标注= 指数平面.text(ix, iy, 表示, color='0.3', fontsize=8, zorder=0)
				if 表示 in ('11:30', '15:00'): 标注.set_horizontalalignment('right')

		# 5 分钟副时间点
		for iy in [指数纵标起点*1.001, 指数纵标终点*0.997]:
			for ix, 时间, 表示 in zip(横轴参数['副坐标值'], 横轴参数['副标时间'], 横轴参数['副标表示']):
				指数平面.text(ix, iy, 表示, color='0.3', fontsize=5, zorder=0)

		#	画价格标记
		#============================================================================================================
		标注位置组一= 横轴参数['标注位置组一']

		主标价格= [nr for nr in 纵轴参数['个股主坐标值'] if nr > 个股纵标起点*1.01 and nr < 个股纵标终点*0.99]
		副标价格= [nr for nr in 纵轴参数['个股副坐标值'] if nr > 个股纵标起点*1.01 and nr < 个股纵标终点*0.99]
		for 横标 in 标注位置组一:
			for 纵标 in 主标价格:
				个股平面.text(横标-30.0, 纵标, str(纵标/1000.0), color='0.3', fontsize=3.0, horizontalalignment='right', zorder=0)
			for 纵标 in 副标价格:
				个股平面.text(横标+30.0, 纵标, str(纵标/1000.0), color='0.3', fontsize=3.0, zorder=0)

		#	画档位标记
		#============================================================================================================
		标注位置组二= 横轴参数['标注位置组二']
		基准价格= 纵轴参数['基准价格']

		正向档位= [nr for nr in 纵轴参数['个股主坐标值'] if nr >= 基准价格 and nr < 个股纵标终点*0.99]
		负向档位= list(reversed([nr for nr in 纵轴参数['个股主坐标值'] if nr <  基准价格 and nr > 个股纵标起点]))

		for 横标 in 标注位置组二:
			for 档位, 纵标 in enumerate(正向档位, start=1):
				个股平面.text(横标+30.0, 纵标*1.001, str(档位), color='red', fontsize=25, alpha=0.17, zorder=0)
			for 档位, 纵标 in enumerate(负向档位, start=1):
				个股平面.text(横标+30.0, 纵标*1.001, str(档位), color='green', fontsize=25, alpha=0.2, zorder=0)











