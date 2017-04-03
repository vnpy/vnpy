# encoding: UTF-8

'''
此代码为策略提供错误捕获包装器，避免多策略运行时因为一个策略错误而中断事件线程影响其他策略。
'''


def error(func):
    """
    一个装饰器，用于捕获策略代码的错误，以及做相应的处理。
    参数：
      func - 策略实例化对象的函数，如onInit, onStart等
    返回:
      wrapper - 装饰后的函数，注意，需要重新与策略对象绑定
    """
    def wrapper(*args, **kwargs):
        try:
            func(*args, **kwargs)
        except Exception as e:
            strategy = func.im_self  # 通过函数获取与其绑定的策略对象
            strategy.writeCtaLog('策略函数 {:s} 发生错误：{:s}'.format(
                func.__name__, strategy.name, str(e)))
            # 停止策略，修改状态为未初始化
            strategy.trading = False
            strategy.inited = False
    return wrapper


def handler(strategy, func_names=['onInit', 'onStop', 'onStart',
                                  'onTick', 'onBar']):
    """
    调用装饰器的函数，提供一个方便的接口
    参数：
      strategy - 实例化的策略对象
      func_names - 需要包装的函数列表
    返回：
      无
    """
    for func_name in func_names:
        func = strategy.__getattribute__(func_name)  # 根据函数名得到策略函数对象
        func = error(func)  # 进行包装，此时的func对象已改变，并且未与策略对象绑定
        exec('strategy.{:s} = func'.format(func_name))  # 与策略对象绑定
