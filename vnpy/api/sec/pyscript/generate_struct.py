# encoding: UTF-8

from __future__ import print_function
from generate_data_type import pre_process

import sec_data_type
DATA_TYPE = sec_data_type.__dict__      # 数据类型字典



#----------------------------------------------------------------------
def main(cpp_filename, py_filename):
    """主函数"""
    # 打开文件
    cpp_f = open(cpp_filename, 'r')
    py_f = open(py_filename, 'w')
    
    # 文件开头
    py_f.write('# encoding: UTF-8\n')
    py_f.write('from collections import OrderedDict')
    
    # 遍历处理
    for n, cpp_line in enumerate(cpp_f):
        cpp_line = pre_process(cpp_line)
        
        # 结构体申明注释
        if cpp_line[0:2] == '//':
            py_line = '#' + cpp_line[2:]
            
        # 结构体申明
        elif 'struct' in cpp_line or 'enum' in cpp_line:
            l = cpp_line.split(' ')
            l = [i for i in l if i]
            struct_name = l[-1]
            py_line = '%s = OrderedDict()' % struct_name
            
        # 结构体开始和结束
        elif '{' in cpp_line or '}' in cpp_line:
            py_line = ''        
        
        # 结构体变量申明
        elif '//' in cpp_line and '#' not in cpp_line:
            l = cpp_line.split(' ')
            l = [i for i in l if i]

            cpp_tp = l[0]
            py_tp = DATA_TYPE[cpp_tp]
            name = l[1]
            
            py_line = '%s[\'%s\'] = \'%s\'' % (struct_name, name, py_tp)
        
        # 其他
        else:
            py_line = ''
            
        # 写入文件
        py_line = py_line + '\n'
        py_line = py_line.decode('gbk').encode('utf-8')
        
        py_f.write(py_line)
        
    # 处理成功
    cpp_f.close()
    py_f.close()
        
    print(u'struct处理完成')
    

if __name__ == '__main__':
    cpp_filename = 'DFITCSECApiStruct.h'
    py_filename = 'sec_struct.py'
    
    main(cpp_filename, py_filename)