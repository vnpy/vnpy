# encoding: UTF-8

__author__ = u'用Python的交易员'

# C++和python类型的映射字典
type_dict = {
    'int': 'int',
    'char': 'string',
    'double': 'float',
    'short': 'int',
    'XTP_EXCHANGE_TYPE': 'int'
}


#----------------------------------------------------------------------
def process_line(line):
    """处理每行"""
    # 注释
    if line[:3] == '///':           # 注释
        py_line = process_comment(line)
    # 枚举
    elif 'enum' in line:
        py_line = process_enum(line)
    # 常量
    elif '#define' in line:
        py_line = process_define(line)
    # 类型定义
    elif 'typedef' in line:                     
        py_line = process_typedef(line)
    # 空行
    elif line == '\n':          
        py_line = line
    # 其他忽略
    else:
        py_line = ''

    return py_line

#----------------------------------------------------------------------
def process_enum(line):
    """处理枚举"""
    content = line.replace('\n', '')
    content = content.replace('\r', '')
    content = content.split(' ')
    type_ = 'enum'
    keyword = content[2]
    py_line = 'typedefDict["%s"] = "%s"\n' % (keyword, type_)

    return py_line

#----------------------------------------------------------------------
def process_comment(line):
    """处理注释"""
    py_line = line.replace('/', '#')
    
    return py_line

#----------------------------------------------------------------------
def process_typedef(line):
    """处理类型定义"""
    content = line.split(' ')
    type_ = type_dict[content[1]]

    keyword = content[2]
    if '[' in keyword:
        i = keyword.index('[')
        keyword = keyword[:i]
    else:
        keyword = keyword.replace('\n', '')  # 删除行末分号
        keyword = keyword.replace('\r', '')  # 删除行末分号
        keyword = keyword.replace(';', '')

    if 'char' in line:
        if '[' in line:
            type_ = 'string'
        else:
            type_ = 'char'

    py_line = 'typedefDict["%s"] = "%s"\n' % (keyword, type_)
    #print keyword, type_

    return py_line

#----------------------------------------------------------------------
def process_define(line):
    """处理常量"""
    content = line.split(' ')
    constant = content[1]

    if len(content)>2:
        value = content[-1]
        #py_line = 'defineDict["%s"] = %s' % (constant, value)
        py_line = '%s = %s' %(constant, value)
    else:
        py_line = ''
        
    py_line = py_line.replace('*/', '')
    py_line = py_line.replace('/*', '')

    return py_line

#----------------------------------------------------------------------
def replaceTabs(f):
    """把Tab用4个空格替代"""
    l = []
    for line in f:
        line = line.replace('\t', '    ')
        l.append(line)
    return l

#----------------------------------------------------------------------
def main():
    """主函数"""
    fcpp = open('xtp_api_data_type.h','r')
    fpy = open('xtp_data_type.py', 'w')

    fpy.write('# encoding: UTF-8\n')
    fpy.write('\n')
    fpy.write('typedefDict = {}\n')
    fpy.write('\n')

    lcpp = replaceTabs(fcpp)
    for n, line in enumerate(lcpp):
        py_line = process_line(line)
        if py_line:
            fpy.write(py_line.decode('gbk').encode('utf-8'))

    fcpp.close()
    fpy.close()

    print u'data_type.py生成过程完成'


if __name__ == '__main__':
    main()


