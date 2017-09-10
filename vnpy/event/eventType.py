# encoding: UTF-8

'''
本文件仅用于存放对于事件类型常量的定义。

由于python中不存在真正的常量概念，因此选择使用全大写的变量名来代替常量。
这里设计的命名规则以EVENT_前缀开头。

常量的内容通常选择一个能够代表真实意义的字符串（便于理解）。

建议将所有的常量定义放在该文件中，便于检查是否存在重复的现象。
'''


EVENT_TIMER = 'eTimer'                  # 计时器事件，每隔1秒发送一次
 


#----------------------------------------------------------------------
def test():
    """检查是否存在内容重复的常量定义"""
    check_dict = {}
    
    global_dict = globals()    
    
    for key, value in global_dict.items():
        if '__' not in key:                       # 不检查python内置对象
            if value in check_dict:
                check_dict[value].append(key)
            else:
                check_dict[value] = [key]
            
    for key, value in check_dict.items():
        if len(value)>1:
            print u'存在重复的常量定义:' + str(key) 
            for name in value:
                print name
            print ''
        
    print u'测试完毕'
    

# 直接运行脚本可以进行测试
if __name__ == '__main__':
    test()