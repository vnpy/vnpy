# -*- coding: utf-8 -*-





import numpy



#	import matplotlib.spines as spines
import matplotlib.ticker as ticker



import Public.Public as Public







class 分时手数子图:

	def __init__(self, parent, 目标日期, 绘图数据):
		'''

		'''
		self._parent= parent
		self._ilogger= Public.IndentLogger(logger=parent._ilogger._logger, indent=parent._ilogger._indent+1)

		# 原始数据
		任务参数= 绘图数据['任务参数']

		# 当日数据
		当日数据= 绘图数据['分时数据'][目标日期]
		self._本图日期= 目标日期
		#	self._日期对象= 当日数据['日期对象']
		#	self._时间常数= 当日数据['时间常数']

		#	个股行情
		#===================================================================================================

		# 分时行情是否存在
		self._个股行情有效= 当日数据['个股行情有效']

		# 日线数据
		self._个股平均成交= 当日数据['个股平均成交']	# 格式: 行情['平均手数']= {Public.计算均值(个股成交量[-n:]) for n in 个股量均参数}

		if self._个股行情有效:
			# 分时数据
			个股分时行情= 当日数据['个股分时行情']
			self._个股手数序列= 个股分时行情['手数序列']
			self._个股金额序列= 个股分时行情['金额序列']
			self._个股备注序列= 个股分时行情['备注序列']

			#	self._个股上涨标记= 个股分时行情['上涨标记']
			#	self._个股下跌标记= 个股分时行情['下跌标记']
			#	self._个股平盘标记= 个股分时行情['平盘标记']

			self._个股买盘标记= [True if 备注.startswith('买') else False for 备注 in self._个股备注序列]
			self._个股卖盘标记= [True if 备注.startswith('卖') else False for 备注 in self._个股备注序列]
			self._个股中性标记= [True if 备注.startswith('中') else False for 备注 in self._个股备注序列]

			# 分时衍生数据（均线等）
			self._个股坐标序列= parent._个股坐标序列
			self._个股平均手数= Public.计算均值(序列=[nr for nr in self._个股手数序列 if nr>0])

		#	TODO: 指数行情
		#===================================================================================================



		#	横轴参数、纵轴参数
		#===================================================================================================
		self._横轴参数= parent._横轴参数
		self._纵轴参数= None

		#	平面对象，留待后面初始化
		#===================================================================================================
		self._个股布局参数= None
		self._指数布局参数= None
		
		self._指数平面= None
		self._指数横轴= None
		self._指数纵轴= None

		self._个股平面= None
		self._个股横轴= None
		self._个股纵轴= None



	def 计算成交步进记录(self):
		'''
		本函数是 naive 的，只考虑本图。
		'''
		if self._个股行情有效:
			# 决定个股步进值
			个股平均手数= self._个股平均手数[0]
			个股步进= 25	# 步进代表主坐标的间隔距离

			while 个股平均手数/个股步进 > 1.0:
				个股步进= 个股步进*2
		else:
			个股步进= 25

		return {'个股步进': 个股步进}



	def 计算纵轴参数(self, 步进记录=None):
		'''

		'''
		纵轴参数= {}

		#	大小固定
		#=======================================================================================
		纵轴尺寸= 4.0
		纵轴倍率= 0.3
		纵轴参数['纵轴倍率']= 纵轴倍率
		纵轴参数['纵轴高度']= 纵轴尺寸 * 纵轴倍率

		if 步进记录 is None:
			步进记录= self.计算成交步进记录()

		#	个股部分
		#=======================================================================================
		步进= 步进记录['个股步进']

		# 坐标起点 与 坐标终点
		个股坐标起点= 0.0
		个股坐标终点= max(self._个股手数序列) if self._个股行情有效 else 步进*纵轴尺寸
		纵轴参数['个股坐标起点']= 个股坐标起点
		纵轴参数['个股坐标终点']= 个股坐标终点

		个股纵轴尺寸= max(个股坐标终点/步进, 纵轴尺寸)
		纵轴参数['个股纵轴尺寸']= 个股纵轴尺寸
		纵轴参数['个股纵轴高度']= 个股纵轴尺寸 * 纵轴倍率

		# 计算 坐标值 与 坐标点
		个股主坐标值= [步进 * i for i in range(1, 4)]
		个股副坐标值= [(步进/2.0) + 步进*i for i in range(4)]
		if 个股副坐标值[-1] > 纵轴参数['个股坐标终点']: del 个股副坐标值[-1]
		
		纵轴参数['个股主坐标值']= 个股主坐标值
		纵轴参数['个股副坐标值']= 个股副坐标值

		self._纵轴参数= 纵轴参数



	def 返回纵轴高度(self):
		'''

		'''
		return self._纵轴参数['纵轴高度']



	def 返回指数平面(self):
		'''

		'''
		return self._指数平面



	def 平面初始化(self, 图片对象, 子图偏移, 全图大小):
		'''

		'''
		子图横移, \
		子图纵移= 子图偏移
		
		全图宽度, \
		全图高度= 全图大小
		
		本图宽度= self._横轴参数['横轴宽度']
		指数平面高度= self._纵轴参数['纵轴高度']	# XXX: 以后指数平面可以有自己的高度
		个股平面高度= self._纵轴参数['个股纵轴高度']

		指数布局参数= (子图横移/全图宽度, 子图纵移/全图高度, 本图宽度/全图宽度, 指数平面高度/全图高度)
		个股布局参数= (子图横移/全图宽度, 子图纵移/全图高度, 本图宽度/全图宽度, 个股平面高度/全图高度)

		self._指数布局参数= 指数布局参数
		self._个股布局参数= 个股布局参数

		#	指数部分
		#=======================================================================================
		指数平面= 图片对象.add_axes(指数布局参数, axis_bgcolor='black')
		指数平面.set_frame_on(False)	# XXX
		指数平面.set_axisbelow(True)	# 网格线放在底层

		指数横轴= 指数平面.get_xaxis()
		指数纵轴= 指数平面.get_yaxis()

		self._指数平面= 指数平面
		self._指数横轴= 指数横轴
		self._指数纵轴= 指数纵轴

		self.设置指数横轴()
		self.设置指数纵轴()

		#	个股部分
		#=======================================================================================

		# XXX: 不用 twinx()，原因见分时价格子图。
		个股平面= 图片对象.add_axes(个股布局参数, axis_bgcolor='black')
		个股平面.set_frame_on(False)	# XXX
		个股平面.set_axisbelow(True)	# 网格线放在底层

		for 方位, 边框 in 个股平面.spines.items():
			边框.set_color(None)

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

		指数横轴.grid(True, 'major', color='0.3', linestyle='solid', linewidth=0.2)
		指数横轴.grid(True, 'minor', color='0.3', linestyle='dotted', linewidth=0.15)

		指数横轴.set_ticks_position('none')

		坐标起点= 横轴参数['坐标起点']
		坐标终点= 横轴参数['坐标终点']

		xMajorLocator= 横轴参数['xMajorLocator']
		xMinorLocator= 横轴参数['xMinorLocator']

		指数平面.set_xlim(坐标起点, 坐标终点)
		指数横轴.set_major_locator(xMajorLocator)
		指数横轴.set_minor_locator(xMinorLocator)

		for 主坐标 in 指数平面.get_xticklabels(minor=False):
			主坐标.set_visible(False)
		for 副坐标 in 指数平面.get_xticklabels(minor=True):
			副坐标.set_visible(False)



	def 设置指数纵轴(self):
		'''

		'''
		指数平面= self._指数平面
		指数纵轴= self._指数纵轴

		#	指数纵轴.set_label_position('right')	# XXX: 不顶用
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

		xMajorLocator= 横轴参数['xMajorLocator']
		xMinorLocator= 横轴参数['xMinorLocator']
		xMajorFormatter= 横轴参数['xMajorFormatter']
		xMinorFormatter= 横轴参数['xMinorFormatter']

		个股平面.set_xlim(坐标起点, 坐标终点)
		个股横轴.set_major_locator(xMajorLocator)
		个股横轴.set_minor_locator(xMinorLocator)

		个股横轴.set_major_formatter(xMajorFormatter)
		个股横轴.set_minor_formatter(xMinorFormatter)

		for 主坐标 in 个股平面.get_xticklabels(minor=False):
			主坐标.set_fontsize(5)
			主坐标.set_horizontalalignment('right')
			主坐标.set_rotation('45')

		for 副坐标 in 个股平面.get_xticklabels(minor=True):
			副坐标.set_fontsize(4)
			副坐标.set_color('blue')
			副坐标.set_horizontalalignment('right')
			副坐标.set_rotation('45')



	def 设置个股纵轴(self):
		'''

		'''
		平面对象= self._个股平面
		个股纵轴= self._个股纵轴
		纵轴参数= self._纵轴参数

		#	个股纵轴.set_label_position('right')	# XXX: 不顶用
		个股纵轴.set_ticks_position('none')

		个股纵轴.grid(True, 'major', color='0.3', linestyle='solid', linewidth=0.2)
		个股纵轴.grid(True, 'minor', color='0.3', linestyle='dotted', linewidth=0.15)

		坐标起点= 纵轴参数['个股坐标起点']
		坐标终点= 纵轴参数['个股坐标终点']

		平面对象.set_ylim(坐标起点, 坐标终点)

		#	主坐标点
		#======================================================================================
		主坐标值= 纵轴参数['个股主坐标值']
		yMajorLocator= ticker.FixedLocator(numpy.array(主坐标值))
		个股纵轴.set_major_locator(yMajorLocator)

		#	def y_major_formatter(num, pos=None):
		#		return str(num)
		#	yMajorFormatter= ticker.FuncFormatter(y_major_formatter)
		#	个股纵轴.set_major_formatter(yMajorFormatter)

		for 主坐标 in 平面对象.get_yticklabels(minor=False):
			主坐标.set_visible(False)

		#	副坐标点
		#======================================================================================
		副坐标值= 纵轴参数['个股副坐标值']
		yMinorLocator= ticker.FixedLocator(numpy.array(副坐标值))
		个股纵轴.set_minor_locator(yMinorLocator)

		#	def y_minor_formatter(num, pos=None):
		#		return str(num)
		#	yMinorFormatter= ticker.FuncFormatter(y_minor_formatter)
		#	个股纵轴.set_minor_formatter(yMinorFormatter)

		for 副坐标 in 平面对象.get_yticklabels(minor=True):
			副坐标.set_visible(False)



	def 绘图(self):
		'''

		'''
		self.绘制辅助标记()
		self.绘制个股手数()



	def 绘制辅助标记(self):
		'''

		'''
		个股平面= self._个股平面

		标注位置组一= self._横轴参数['标注位置组一']
		主标手数= self._纵轴参数['个股主坐标值']
		副标手数= self._纵轴参数['个股副坐标值']

		for 横标 in 标注位置组一:
			for 纵标 in 主标手数:
				个股平面.text(横标+30.0, 纵标, str(int(纵标)), color='0.3', fontsize=5.0, zorder=0)
			for 纵标 in 副标手数:
				个股平面.text(横标+30.0, 纵标, str(int(纵标)), color='0.3', fontsize=5.0, zorder=0)



	def 绘制个股手数(self):
		'''

		'''
		个股平面= self._个股平面

		if self._个股行情有效:
			坐标序列= numpy.array(self._个股坐标序列)
			手数序列= numpy.array(self._个股手数序列)
			序列长度= len(手数序列)
			起点序列= numpy.zeros(序列长度)

			#	正向标记= numpy.array(self._个股上涨标记)
			#	负向标记= numpy.array(self._个股下跌标记)
			#	中性标记= numpy.array(self._个股平盘标记)

			正向标记= numpy.array(self._个股买盘标记)
			负向标记= numpy.array(self._个股卖盘标记)
			中性标记= numpy.array(self._个股中性标记)

			lwidth, alpha= (0.15, 1.0)

			if True in 正向标记:
				个股平面.vlines(坐标序列[正向标记], 起点序列[正向标记], 手数序列[正向标记], edgecolor='red', linewidth=lwidth, label='_nolegend_', alpha=alpha)
			if True in 负向标记:
				个股平面.vlines(坐标序列[负向标记], 起点序列[负向标记], 手数序列[负向标记], edgecolor='green', linewidth=lwidth, label='_nolegend_', alpha=alpha)
			if True in 中性标记:
				个股平面.vlines(坐标序列[中性标记], 起点序列[中性标记], 手数序列[中性标记], edgecolor='white', linewidth=lwidth, label='_nolegend_', alpha=alpha)

			# 绘制平均手数数值（直线）
			平均手数= self._个股平均手数[0]
			横轴参数= self._横轴参数
			横标起点= 横轴参数['坐标起点']
			横标终点= 横轴参数['坐标终点']

			个股平面.plot([横标起点, 横标终点], [平均手数, 平均手数], '-', color='yellow', linewidth=0.2, alpha=0.7)










