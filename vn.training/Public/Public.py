# -*- coding: utf-8 -*-



import os
import copy
import itertools
import math
import datetime
import logging
import logging.handlers





class IndentLogger:
	'''

	'''

	def __init__(self, logger, indent):
		self._logger= logger
		self._indent= indent



	def indent_levelup(self, level=1):
		self._indent= self._indent - level

	def indent_leveldown(self, level=1):
		self._indent= self._indent + level

	def set_indent_level(self, level):
		self._indent= level

	#---------------------------------------------------------------

	def set_critical(self):
		self._logger.setLevel(logging.CRITICAL)

	def set_error(self):
		self._logger.setLevel(logging.ERROR)

	def set_warning(self):
		self._logger.setLevel(logging.WARNING)

	def set_info(self):
		self._logger.setLevel(logging.INFO)

	def set_debug(self):
		self._logger.setLevel(logging.DEBUG)

	def set_notset(self):
		self._logger.setLevel(logging.NOTSET)

	#---------------------------------------------------------------

	def critical(self, message):
		self._logger.critical('\t' * self._indent + message)

	def error(self, message):
		self._logger.error('\t' * self._indent + message)

	def warning(self, message):
		self._logger.warning('\t' * self._indent + message)

	def info(self, message):
		self._logger.info('\t' * self._indent + message)

	def debug(self, message):
		self._logger.debug('\t' * self._indent + message)

	def noset(self, message):
		self._logger.noset('\t' * self._indent + message)



def TempLogger(loggername, filename=None, taskdir=None):
	'''

	'''

	if not taskdir:
		taskdir= __dir_tmpfiles__

	if not os.path.exists(taskdir):
		os.mkdir(taskdir, 0o700)

	if not filename:
		timestamp= datetime.datetime.now()
		filename= os.path.join(taskdir, loggername + '_' + timestamp.strftime('%Y-%m-%d_%H:%M:%S,%f'))
	else:
		filename= os.path.join(taskdir, filename)

	if not os.path.exists(filename):
		os.mknod(filename, 0o700)

	myformatstr= "%(asctime)s %(levelname)-9s>> %(message)s"
	myformatter= logging.Formatter(myformatstr)
	
	myhandler= logging.handlers.RotatingFileHandler(filename=filename, mode='a', encoding='utf-8')
	myhandler.setFormatter(myformatter)
	
	mylogger= logging.getLogger(name=loggername)
	mylogger.setLevel(level=logging.DEBUG)
	mylogger.addHandler(myhandler)
	
	ilogger= IndentLogger(logger=mylogger, indent=0)
	return ilogger



def 计算个股换手率(个股行情, 个股股本变更记录):
	'''

	'''
	个股股本变更列表= [rec for rec in 个股股本变更记录 if rec['流通股'] != 0 and rec['变更日期'] <= 个股行情['日期'][-1]]

	个股股本变更字典= {}
	for rec in 个股股本变更列表:
		if rec['变更日期'] in 个股行情['日期']:
			个股股本变更字典[rec['变更日期']]= rec
		else:
			个股股本变更字典[ [ds for ds in 个股行情['日期'] if ds > rec['变更日期']][0] ]= rec

	当前流通股= 个股股本变更字典[min(个股股本变更字典.keys())]['流通股']

	换手率= []
	for ds, vol in zip(个股行情['日期'], 个股行情['成交量']):
		if ds in 个股股本变更字典:
			当前流通股= 个股股本变更字典[ds]['流通股']
		换手率.append( vol*100000/当前流通股 )
	个股行情['换手率']= 换手率



def 计算复权行情(个股行情, 均线参数=None):
	'''

	'''
	日期= 个股行情['日期']

	复权开盘= copy.copy(个股行情['开盘'])
	复权最高= copy.copy(个股行情['最高'])
	复权收盘= copy.copy(个股行情['收盘'])
	复权最低= copy.copy(个股行情['最低'])
	复权开收中= copy.copy(个股行情['开收中'])

	复权记录= []

	sidx= 1
	done= False
	while not done:
		done= True

		for idx, date in enumerate(日期[sidx:], start=sidx):
			涨幅= (复权开盘[idx] - 复权收盘[idx-1]) / 复权收盘[idx-1]
			if 涨幅 <= -0.12:
				复权因子= round(复权收盘[idx-1]/复权开盘[idx], 2)
				调整因子= round(复权因子, 1)
				if abs(round(复权因子-调整因子, 2)) <= 0.01:
					复权因子= 调整因子
				复权开盘[:idx]= [nr/复权因子 for nr in 复权开盘[:idx]]
				复权最高[:idx]= [nr/复权因子 for nr in 复权最高[:idx]]
				复权收盘[:idx]= [nr/复权因子 for nr in 复权收盘[:idx]]
				复权最低[:idx]= [nr/复权因子 for nr in 复权最低[:idx]]
				复权开收中[:idx]= [nr/复权因子 for nr in 复权开收中[:idx]]

				复权记录.append( (date, 复权因子) )
				sidx= idx
				done= False
				break

	复权行情= {}
	复权行情['复权记录']= 复权记录

	复权行情['日期']= copy.copy(日期)
	复权行情['开盘']= 复权开盘
	复权行情['最高']= 复权最高
	复权行情['收盘']= 复权收盘
	复权行情['最低']= 复权最低
	复权行情['开收中']= 复权开收中
	if 均线参数:
		复权行情['均线集']= { n : 计算序列加权均线(复权开盘, 复权最高, 复权收盘, 复权最低, n) for n in 均线参数 }

	return 复权行情



def 计算序列加权均线(开盘序列, 最高序列, 收盘序列, 最低序列, n):
	'''

	'''
	length= len(开盘序列)
	if length < n:
		return [None] * length

	sumhilo= sum(最高序列[:n]) + sum(最低序列[:n])
	sumopen= sum(开盘序列[:n])
	sumclose= sum(收盘序列[:n])

	输出序列= [ ((sumhilo / 2 + sumopen) / 2 + sumclose) / (2*n) ]

	for idx in range(n, length):
		sumhilo= sumhilo - 最高序列[idx-n] - 最低序列[idx-n] + 最高序列[idx] + 最低序列[idx]
		sumopen= sumopen - 开盘序列[idx-n] + 开盘序列[idx]
		sumclose= sumclose - 收盘序列[idx-n] + 收盘序列[idx]
		输出序列.append( ((sumhilo / 2 + sumopen) / 2 + sumclose) / (2*n) )

	return [None] * (n-1) + 输出序列



def 补全个股行情(完整日期, 个股行情):
	'''

	'''
	代码= 个股行情.pop('代码') if '代码' in 个股行情 else None
	日期= 个股行情.pop('日期')

	for idx, dstr in enumerate(完整日期):
		if dstr not in 日期:
			日期.insert(idx, dstr)
			for seq in 个股行情.values():
				seq.insert(idx, None)

	if 代码:
		个股行情['代码']= 代码
	个股行情['日期']= 日期



def 计算个股行情衍生数据(ilogger, 个股行情, 均线参数=None):
	'''

	'''
	length= len(个股行情['开盘'])

	开盘= 个股行情['开盘']
	最高= 个股行情['最高']
	收盘= 个股行情['收盘']
	最低= 个股行情['最低']

	if 均线参数 and '均线集' not in 个股行情:
		个股行情['均线集']= {n : 计算序列加权均线(开盘, 最高, 收盘, 最低, n) for n in 均线参数}
	if '均线集' in 个股行情:
		个股行情['均线走势标记集']= {n : [None]*(n-1)+计算走势标记(序列=序列[n-1:]) if length>=n else [None]*length for n, 序列 in 个股行情['均线集'].items()}

	开收中= 个股行情['开收中']

	开收中线走势标记= 计算走势标记(序列=开收中)

	个股行情['开收中线走势标记']= 开收中线走势标记

	最小长度= 个股行情.pop('目标偏移') if '目标偏移' in 个股行情 else 0
	截去行情头部无效片断(行情数据=个股行情, 最小长度=最小长度)

	开收中线走势拐点= 计算走势拐点(目标序列=开收中, 走势标记=开收中线走势标记)
	个股行情['开收中线走势拐点']= 开收中线走势拐点



def 截去行情头部无效片断(行情数据, 最小长度):
	'''

	'''
	length= len(行情数据['开盘'])

	dirlists= [seq for seq in 行情数据.values() if (type(seq) is list) and (len(seq)==length)]
	subkeys= ('均线集', '均线走势标记集')
	sublists= [行情数据[key].values() for key in subkeys if key in 行情数据]

	cntlist= [seq.count(None) for seq in dirlists]
	itor= itertools.chain.from_iterable(seq for seq in sublists)
	cntlist.extend( [seq.count(None) for seq in itor] )
	截去长度= max(最小长度, max(cntlist))

	for seq in dirlists:
		del seq[:截去长度]
	itor= itertools.chain.from_iterable(seq for seq in sublists)
	for seq in itor:
		del seq[:截去长度]



def 计算均值(序列):
	'''
	
	'''
	if not 序列:
		return None
	长度= len(序列)
	均值= sum(序列)/长度
	最大值= max(序列)
	最小值= min(序列)
	标准差= math.sqrt(sum([(nr-均值)**2 for nr in 序列]) / 长度)

	return (均值, 最大值, 最小值, 标准差, 长度)



def 计算日内定时均线(价格序列, 调整时间序列, 格点粒度, 间隔点数, 定时点数, 需要规整=True):
	'''

	'''
	日期对象= 调整时间序列[0].date()

	datetime_0925= datetime.datetime.combine(日期对象, datetime.time(hour=9, minute=25))

	格点序列= [datetime_0925 + datetime.timedelta(seconds=格点粒度*i) for i in range(int((3600*4+1000)/格点粒度))]

	if 需要规整:
		规整时间序列= []
		格点当前位置= 0
		for 时间 in 调整时间序列:
			while 格点序列[格点当前位置] < 时间:
				格点当前位置 += 1
			前方格点= 格点序列[格点当前位置]
			后方格点= 格点序列[格点当前位置-1]
			规整时间= 前方格点 if 前方格点-时间 <= 时间-后方格点 else 后方格点
			规整时间序列.append(规整时间)
	else:
		规整时间序列= 调整时间序列

	目标格点序列= [时间 for 时间 in 格点序列 if 时间>=规整时间序列[0] and 时间<=规整时间序列[-1]]

	补全价格序列= []
	当前价格= 价格序列[0]
	for 格点 in 目标格点序列:
		if 格点 in 规整时间序列:
			当前价格= 价格序列[规整时间序列.index(格点)]
		补全价格序列.append(当前价格)

	定时均线= {}
	for 点数 in 定时点数:
		偏移序列= range(点数-1, len(目标格点序列), 间隔点数)
		时间序列= [目标格点序列[偏移] for 偏移 in 偏移序列]
		均线序列= [ sum(补全价格序列[偏移-点数+1 : 偏移+1]) / 点数 for 偏移 in 偏移序列 ]
		定时均线[点数]= {
			'时间序列': 时间序列,
			'均线序列': 均线序列,
		}

	return 定时均线



def 计算走势标记(序列):
	'''

	'''
	length= len(序列)
	if length < 2:
		return ['-'] * length

	标记序列= []
	当前方向= '/'  if 序列[1] > 序列[0] else \
		  '\\' if 序列[1] < 序列[0] else \
		  '-'

	for idx in range(1, length-1):
		sign=	'/'  if 序列[idx] >  序列[idx-1] and 序列[idx+1] >= 序列[idx] else \
			'\\' if 序列[idx] <  序列[idx-1] and 序列[idx+1] <= 序列[idx] else \
			'^'  if 序列[idx] >  序列[idx-1] and 序列[idx+1] <  序列[idx] else \
			'v'  if 序列[idx] <  序列[idx-1] and 序列[idx+1] >  序列[idx] else \
			'/'  if 当前方向  in '/-'	 and 序列[idx+1] >  序列[idx] else \
			'\\' if 当前方向  in '\\-'	 and 序列[idx+1] <  序列[idx] else \
			'^'  if 当前方向  == '/'	 and 序列[idx+1] <  序列[idx] else \
			'v'  if 当前方向  == '\\'	 and 序列[idx+1] >  序列[idx] else \
			'-'

		当前方向= '/'  if sign in '/v'  else \
			  '\\' if sign in '\\^' else \
			当前方向  

		标记序列.append(sign)

	return ['-'] + 标记序列 + ['/' if 序列[-1] > 序列[-2] else '\\' if 序列[-1] < 序列[-2] else '-']



def 计算走势拐点(目标序列, 走势标记, 扩展=True):
	'''

	'''

	length= len(目标序列)
	if length <= 2:
		return []
	
	走势拐点= []
	
	for idx, sign in [(i, s) for i, s in enumerate(走势标记) if s in ('^', 'v')]:
		拐点记录= {}
		拐点记录['偏移']= idx
		拐点记录['类型']= sign
		if 扩展:
			# 计算关键度
			拐点记录['关键度']= 计算最新极点关键度(序列=目标序列[:idx+1], 类型=sign)['关键度']

		走势拐点.append(拐点记录)

	return 走势拐点



def 计算最新极点关键度(序列, 类型=None):
	'''

	'''
	长度= len(序列)

	if 类型 is None:
		for i in range(1, 长度):
			if 序列[-i] > 序列[-(i+1)]:
				类型= '^'
				break
			elif 序列[-i] < 序列[-(i+1)]:
				类型= 'v'
				break

	结果= {
		'类型': 类型,
		'关键度': 长度,
		'偏移': 长度-1,
	}

	if 长度 < 2:
		return 结果

	if 类型 == '^':
		chunk= [idx for idx, item in enumerate(reversed(序列)) if item > 序列[-1]]
	elif 类型 == 'v':
		chunk= [idx for idx, item in enumerate(reversed(序列)) if item < 序列[-1]]
	else:
		return 长度

	结果['关键度']= chunk[0] if chunk else 长度

	return 结果



def repr_data(data, indent=0):
	'''

	'''
	tlist= (list, dict, set, tuple)
	dtype= type(data)

	if dtype is list:
		head= '\t'*indent + '['
		body= ',\n'.join( [repr_data(data=item, indent=indent+1) for item in data] )
		tail= '\n' + '\t'*indent + ']'
		return head + '\t' + body.lstrip() + tail

	elif dtype is dict:
		head= '\t'*indent + '{'
		body= ',\n'.join( ['\t'*(indent+1) + str(key) + ' :' + ( ('\n' + repr_data(data=val, indent=indent+1)) if type(val) in tlist else ('\t' + str(val)) ) for key, val in sorted(data.items())] )
		tail= '\n' + '\t'*indent + '}'
		return head + '\t' + body.lstrip() + tail

	elif dtype is set:
		head= '\t'*indent + '{'
		body= ',\n'.join( [repr_data(data=item, indent=indent+1) for item in sorted(data)] )
		tail= '\n' + '\t'*indent + '}'
		return head + '\t' + body.lstrip() + tail

	elif dtype is tuple:
		head= '\t'*indent + '('
		body= ',\n'.join( [repr_data(data=item, indent=indent+1) for item in data] )
		tail= '\n' + '\t'*indent + ')'
		return head + '\t' + body.lstrip() + tail

	else:
		return '\t'*indent + str(data)



