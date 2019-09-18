# encoding: UTF-8
# modified by 华富资产.李来佳.28888502 in 20190104

from __future__ import print_function
__author__ = 'CHENXY'

import os,sys
XTP_API_PATH = os.path.abspath(os.path.join(os.path.dirname(__file__), '..'))
sys.path.append(XTP_API_PATH)

from xtp_data_type import *

type_dict = {
    'uint64_t': 'uint64_t',
    'uint32_t': 'uint32_t',
    'int64_t': 'int64_t',
    'int32_t': 'int32_t',
    'uint8_t': 'int',
    'char': 'string',
    'double': 'float'
}

typedefDict.update(type_dict)

#----------------------------------------------------------------------
def replaceTabs(f):
    """把Tab用4个空格替代"""
    l = []
    import chardet
    for line in f:
        charset = chardet.detect(line)
        line = line.decode(charset.get('encoding','ascii'))

        line = line.replace('\t', '    ')
        l.append(line)

    return l

def main():
    """主函数"""
    source_c_xoms_api_struct_file = os.path.join(os.getcwd(), '..', 'xtpapi', 'xoms_api_struct.h')
    target_py_xtp_struct_oms_file = os.path.join(os.getcwd(), '..', 'xtp_struct_oms.py')

    fcpp = open(source_c_xoms_api_struct_file, 'rb')
    fpy = open(target_py_xtp_struct_oms_file, 'w',encoding='utf-8')

    fpy.write('# encoding: UTF-8\n')
    fpy.write('\n')
    fpy.write('structDict = {}\n')
    fpy.write('\n')
    print(u'开始分析:{}'.format(source_c_xoms_api_struct_file))
    lcpp = replaceTabs(fcpp)
    for row, line in enumerate(lcpp):

        # 结构体申明注释
        if '///' in line and '\t' not in line:
            py_line = '#' + line[3:]

        # 结构体变量注释
        elif '\t///' in line:
            py_line = '#' + line[4:]

        # 结构体申明
        elif 'struct ' in line:
            print(line)

            content = line.split(' ')
            if 'typedef' in line:
                struct_name = content[2].replace('\n', '')
            else:
                struct_name = content[1].replace('\n', '')

            struct_name = struct_name.replace('\r', '')
            if len(struct_name) > 0:
                print(u'{}发现新结构体:{}'.format(row,struct_name))
                name = struct_name
                py_line = '%s = {}\n' % name

        # 结构体变量
        elif ('    ' == line[0:4] or '\t' == line[0]) and '()' not in line and '{' not in line and '}' not in line and '=' not in line:
            line = line.replace('\t', ' ')
            content = line.split(' ')
            content = [k for k in content if k]
            
            typedef = content[0].replace('\t', '')
            typedef = typedef.replace('()', '')
            typedef = typedef.replace('\r', '')
            typedef = typedef.replace('\n', '')
            try:
                type_ = typedefDict[typedef]
            except Exception as ex:
                print(u'not found {} in typedefDict.{}'.format(typedef,str(ex)))
                continue

            variable = content[1]
            variable = variable.replace(';', "")
            variable = variable.replace('\n', "")
            variable = variable.replace('\r', "")
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

        fpy.write(py_line)

    fpy.write("structDict['%s'] = %s\n\n" % ('XTPQueryOrderRsp', 'XTPOrderInfo'))
    fpy.write("structDict['%s'] = %s\n\n" % ('XTPQueryTradeRsp', 'XTPTradeReport'))
    print(u'{}生成过程完成'.format(target_py_xtp_struct_oms_file))
if __name__ == '__main__':
    main()