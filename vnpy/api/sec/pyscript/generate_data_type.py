# encoding: UTF-8


# C++和Python类型映射
from __future__ import print_function
type_map = {
    'int': 'int',
    'long': 'long', 
    '__int64': 'long',
    'double': 'float',
    'char': 'string',
}

#----------------------------------------------------------------------
def pre_process(cpp_line):
    """预处理"""
    # 预处理
    cpp_line = cpp_line.replace('\t', ' ')
    cpp_line = cpp_line.replace('\n', '')
    cpp_line = cpp_line.replace(';', '')    
    
    return cpp_line
    

#----------------------------------------------------------------------
def process_line(cpp_line):
    """处理每行代码"""
    cpp_line = pre_process(cpp_line)
    
    # 根据类型处理
    if '///' in cpp_line:
        py_line = process_comment(cpp_line)
    elif 'typedef' in cpp_line:
        py_line = process_typedef(cpp_line)
    elif '#define' in cpp_line:
        py_line = process_define(cpp_line)
    else:
        py_line = ''
        
    # 格式处理
    py_line = py_line + '\n'
    py_line = py_line.decode('gbk').encode('utf-8')
    
    # 返回
    return py_line
    
#----------------------------------------------------------------------
def process_comment(cpp_line):
    """注释"""
    py_line = '#' + cpp_line[3:]
    return py_line

#----------------------------------------------------------------------
def process_typedef(cpp_line):
    """类型申明"""
    l = cpp_line.split(' ')
    
    # 确定Python数据类型
    cpp_tp = l[1]
    py_tp = type_map[cpp_tp]
    
    # 确定关键词
    name = l[-1]
    if '[' in name:
        name = name[:name.index('[')]
    
    py_line = '%s = \'%s\'' %(name, py_tp)

    return py_line

#----------------------------------------------------------------------
def process_define(cpp_line):
    """常量定义"""
    l = cpp_line.split(' ')
    l = [i for i in l if i]
    
    if len(l) < 3:
        return ''
    
    name = l[1]
    value = l[2]
    py_line = '%s = %s' %(name, value)
    
    return py_line
    
#----------------------------------------------------------------------
def main(cpp_filename, py_filename):
    """主函数"""
    cpp_f = open(cpp_filename, 'r')
    py_f = open(py_filename, 'w')
    
    py_f.write('# encoding: UTF-8\n')
    
    for n, cpp_line in enumerate(cpp_f):
        py_line = process_line(cpp_line)
        py_f.write(py_line)
        
    cpp_f.close()
    py_f.close()
        
    print(u'data_type处理完成')
    

if __name__ == '__main__':
    cpp_filename = 'DFITCSECApiDataType.h'
    py_filename = 'sec_data_type.py'
    
    main(cpp_filename, py_filename)
    
    
    