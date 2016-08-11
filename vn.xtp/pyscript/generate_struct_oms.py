# encoding: UTF-8

__author__ = 'CHENXY'

from xtp_data_type import *

type_dict = {
    'uint64_t': 'int',
    'uint32_t': 'int',
    'int64_t': 'int',
    'char': 'string',
    'double': 'float'
}

typedefDict.update(type_dict)


def main():
    """主函数"""
    fcpp = open('xoms_api_struct.h', 'r')
    fpy = open('xtp_struct_oms.py', 'w')

    fpy.write('# encoding: UTF-8\n')
    fpy.write('\n')
    fpy.write('structDict = {}\n')
    fpy.write('\n')

    for line in fcpp:
        # 结构体申明注释
        if '///' in line and '\t' not in line:
            py_line = '#' + line[3:]

        # 结构体变量注释
        elif '\t///' in line:
            py_line = '#' + line[4:]

        # 结构体申明
        elif 'struct ' in line:
            content = line.split(' ')
            name = content[1].replace('\n','')
            py_line = '%s = {}\n' % name

        # 结构体变量
        elif '    ' == line[0:4] or '\t' == line[0]:
            content = line.split(' ')
            content = [k for k in content if k]
            print content
            typedef = content[0].replace('\t', '')
            type_ = typedefDict[typedef]

            variable = content[1]
            variable = variable.replace(';', "")
            variable = variable.replace('\n', "")
            if '[' in variable:
                k = variable.index('[')
                variable = variable[0:k]
            
            py_line = '%s["%s"] = "%s"\n' % (name, variable, type_)

        # 结构体结束
        elif '}' in line:
            py_line = "structDict['%s'] = %s\n\n" % (name, name)

        # 结构体开始
        elif '{' in line:
            py_line = ''

        # 其他
        else:
            py_line = '\n'

        fpy.write(py_line.decode('gbk').encode('utf-8'))


if __name__ == '__main__':
    main()