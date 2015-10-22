# -*- coding: utf-8 -*-





import matplotlib.ticker as ticker
import matplotlib.font_manager as font_manager 



__font_properties__= font_manager.FontProperties(fname='/usr/share/fonts/truetype/wqy/wqy-zenhei.ttc')



__横轴倍率__= 10.0 / 230.0
__纵轴倍率__= 0.3





class 公司信息子图:
	'''
	公司的基本信息
	'''

	def __init__(self, parent, 绘图数据):
		self._parent= parent
		self._公司信息= 绘图数据['公司信息']

		self._Axes= None

		self._横轴尺寸, \
		self._纵轴尺寸= self.计算本图尺寸()

		self._横轴宽度= self._横轴尺寸 * __横轴倍率__
		self._纵轴高度= self._纵轴尺寸 * __纵轴倍率__



	def 计算本图尺寸(self):
		return (300.0, 1.8)



	def 返回本图大小(self):
		return (self._横轴尺寸*__横轴倍率__, self._纵轴尺寸*__纵轴倍率__)



	def 平面初始化(self, 图片对象, 子图偏移, 全图大小):
		子图横移, \
		子图纵移= 子图偏移

		本图宽度= self._横轴宽度
		本图高度= self._纵轴高度

		全图宽度, \
		全图高度= 全图大小

		布局参数= ( 子图横移/全图宽度, 子图纵移/全图高度, 本图宽度/全图宽度, 本图高度/全图高度 )

		axes= 图片对象.add_axes(布局参数)
		axes.set_frame_on(False)
		self._Axes= axes

		self.设置横轴参数()
		self.设置纵轴参数()



	def 设置横轴参数(self):
		axes= self._Axes
		xaxis= axes.get_xaxis()

		#	设定 X 轴坐标的范围 
		#==================================================================================================================================================
		axes.set_xlim(0, self._横轴尺寸)

		xaxis.set_major_locator(ticker.NullLocator())

		for mal in axes.get_xticklabels(minor=False):
			mal.set_visible(False)

		for mil in axes.get_xticklabels(minor=True):
			mil.set_visible(False)



	def 设置纵轴参数(self):
		axes= self._Axes
		yaxis= axes.get_yaxis()

		#	设定 X 轴坐标的范围 
		#==================================================================================================================================================
		axes.set_ylim(0, self._纵轴尺寸)

		yaxis.set_major_locator(ticker.NullLocator())

		for mal in axes.get_yticklabels(minor=False):
			mal.set_visible(False)

		for mil in axes.get_yticklabels(minor=True):
			mil.set_visible(False)



	def 绘图(self):
		self.绘制公司代码简称(xbase=0.0, ybase=self._纵轴尺寸)
		self.绘制指数简称(xbase=self._横轴尺寸, ybase=self._纵轴尺寸)
		self.绘制公司名称(xbase=0.0, ybase=self._纵轴尺寸-0.8)
		self.绘制公司地域行业(xbase=48.0, ybase=self._纵轴尺寸)
		self.绘制公司主营业务(xbase=48.0, ybase=self._纵轴尺寸)
		self.绘制公司简介(xbase=90.0, ybase=self._纵轴尺寸)
		self.绘制公司分类信息(xbase=165.0, ybase=self._纵轴尺寸)



	def 绘制公司代码简称(self, xbase, ybase):
		'''
		交易代码、公司简称
		'''

		txtstr= self._公司信息['个股代码'] + '   ' + self._公司信息['个股简称']
		label= self._Axes.text(xbase, ybase, txtstr, fontproperties=__font_properties__, verticalalignment='top', horizontalalignment='left')
		label.set_fontsize(16.0)



	def 绘制指数简称(self, xbase, ybase):
		txtstr= self._公司信息['指数简称']
		label= self._Axes.text(xbase, ybase, txtstr, fontproperties=__font_properties__, verticalalignment='top', horizontalalignment='right')
		label.set_fontsize(16.0)



	def 绘制公司名称(self, xbase, ybase):
		'''
		曾用名、全名、英文名
		'''

		txtstr= self._公司信息['基本情况']['曾用名']
		txtlist= txtstr.split('->')
		if len(txtlist) > 15:
			txtstr= ' -> '.join(txtlist[:5]) + ' ->\n' + ' -> '.join(txtlist[5:10]) + ' ->\n' + ' -> '.join(txtlist[10:15]) + ' ->\n' + ' -> '.join(txtlist[15:]) + '\n'
		elif len(txtlist) > 10:
			txtstr= ' -> '.join(txtlist[:5]) + ' ->\n' + ' -> '.join(txtlist[5:10]) + ' ->\n' + ' -> '.join(txtlist[10:]) + '\n'
		elif len(txtlist) > 5:
			txtstr= ' -> '.join(txtlist[:5]) + ' ->\n' + ' -> '.join(txtlist[5:]) + '\n'
		else:
			txtstr= ' -> '.join(txtlist) + '\n'
		txtstr += self._公司信息['基本情况']['公司名称'] + '\n'
		txtstr += self._公司信息['基本情况']['英文名称']

		label= self._Axes.text(xbase, ybase, txtstr, fontproperties=__font_properties__, verticalalignment='top', horizontalalignment='left')
		label.set_fontsize(4.5)



	def 绘制公司地域行业(self, xbase, ybase):
		'''
		地域、所属行业、上市日期
		'''

		txtstr= self._公司信息['公司概况']['区域'] + '   ' + self._公司信息['公司概况']['所属行业'] + '   ' + self._公司信息['发行相关']['上市日期']

		label= self._Axes.text(xbase, ybase, txtstr, fontproperties=__font_properties__, verticalalignment='top', horizontalalignment='left')
		label.set_fontsize(6.5)



	def 绘制公司主营业务(self, xbase, ybase):
		'''
		主营业务
		'''
		# 查找表: (<文字长度>, <每行字数>, <字体大小>, <Y轴偏移量>)
		lookups= (
			(20, 10, 12.0, 0.5), 
			(45, 15, 8.2, 0.5), 
			(80, 20, 6.2, 0.5), 
			(125, 25, 5.0, 0.5), 
			(180, 30, 4.1, 0.5),
			(245, 35, 3.5, 0.4),
			(999999, 37, 3.4, 0.4)
		)

		txtstr= self._公司信息['基本情况']['主营业务']
		length= len(txtstr)
		for sizelimit, linelimit, fontsize, yshift in lookups:
			if length <= sizelimit:
				txtstr= '\n'.join([txtstr[linelimit*idx : linelimit*(idx+1)] for idx in range(length//linelimit + 1)])
				fsize= fontsize
				ycoord= ybase - yshift
				break

		label= self._Axes.text(xbase, ycoord, txtstr, fontproperties=__font_properties__, verticalalignment='top', horizontalalignment='left', color='blue')
		label.set_fontsize(fsize)



	def 绘制公司简介(self, xbase, ybase):
		'''
		公司简介
		'''
		# 查找表: (<文字长度>, <每行字数>, <字体大小>)
		lookups= (
			(150, 30, 7.0),
			(240, 40, 5.6),
			(329, 47, 4.8),
			(432, 54, 4.2),
			(576, 64, 3.5),
			(670, 67, 3.4),
			(792, 72, 3.1),
			(960, 80, 2.8),
			(1222, 94, 2.4),
			(1428, 102, 2.26),
			(1620, 108, 2.12),
			(1938, 114, 2.00),
			(999999, 130, 1.75)
		)

		txtstr= self._公司信息['公司概况']['公司简介']		# 26 ~ 2600 字符
		length= len(txtstr)

		for sizelimit, linelimit, fontsize in lookups:
			if length <= sizelimit:
				txtstr= '\n'.join([txtstr[linelimit*idx : linelimit*(idx+1)] for idx in range(length//linelimit + 1)])
				fsize= fontsize
				break

		label= self._Axes.text(xbase, ybase, txtstr, fontproperties=__font_properties__, verticalalignment='top', horizontalalignment='left')
		label.set_fontsize(fsize)



	def 绘制公司分类信息(self, xbase, ybase):
		'''
		行业板块信息
		'''
		infolist= self._公司信息['行业板块']

		for idx in range(len(infolist)//10 + 1):
			txtstr= '\n'.join(infolist[10*idx : 10*(idx+1)])
			if not txtstr:
				break
			xcoord= xbase + 25.0*idx
			label= self._Axes.text(xcoord, ybase, txtstr, fontproperties=__font_properties__, verticalalignment='top', horizontalalignment='left', color='blue')
			label.set_fontsize(3.4)



































