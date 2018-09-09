# encoding: UTF-8

from __future__ import print_function
__author__ = 'CHENXY'

from string import join
from xtp_struct_oms import structDict
from xtp_struct_common import structDict as structDict2

structDict.update(structDict2)

#----------------------------------------------------------------------
def replaceTabs(f):
    """把Tab用4个空格替代"""
    l = []
    for line in f:
        line = line.replace('\t', '    ')
        l.append(line)
    return l


def processCallBack(line):
    orignalLine = line
    line = line.replace('    virtual void ', '')      # 删除行首的无效内容
    line = line.replace('{};\n', '')                # 删除行尾的无效内容

    content = line.split('(')
    cbName = content[0]                             # 回调函数名称
    cbName = cbName.strip()
    
    cbArgs = content[1]                             # 回调函数参数
    if cbArgs[-1] == ' ':
        cbArgs = cbArgs.replace(') ', '')
    else:
        cbArgs = cbArgs.replace(')', '')

    cbArgsList = cbArgs.split(', ')                 # 将每个参数转化为列表

    cbArgsTypeList = []
    cbArgsValueList = []

    for arg in cbArgsList:                          # 开始处理参数
        content = arg.split(' ')
        if len(content) > 1:
            cbArgsTypeList.append(content[0])           # 参数类型列表
            cbArgsValueList.append(content[1])          # 参数数据列表

    createTask(cbName, cbArgsTypeList, cbArgsValueList, orignalLine)
    createProcess(cbName, cbArgsTypeList, cbArgsValueList)
    
    # 生成.h文件中的process部分
    process_line = 'void process' + cbName[2:] + '(Task *task);\n'
    fheaderprocess.write(process_line)
    fheaderprocess.write('\n')

    # 生成.h文件中的on部分
    #if 'OnRspError' in cbName:
        #on_line = 'virtual void on' + cbName[2:] + '(dict error, int id, bool last) {};\n'
    #elif 'OnRsp' in cbName:
        #on_line = 'virtual void on' + cbName[2:] + '(dict data, dict error, int id, bool last) {};\n'
    #elif 'OnRtn' in cbName:
        #on_line = 'virtual void on' + cbName[2:] + '(dict data) {};\n'
    #elif 'OnErrRtn' in cbName:
        #on_line = 'virtual void on' + cbName[2:] + '(dict data, dict error) {};\n'
    #else:
        #on_line = ''
        
    if line.count('*') == 1:
        on_line = 'virtual void on' + cbName[2:] + '(dict data) {};\n'       
    elif line.count('*') == 2:
        if 'is_last' in line:
            on_line = 'virtual void on' + cbName[2:] + '(dict data, dict error, int reqid, bool last) {};\n' 
        else:
            on_line = 'virtual void on' + cbName[2:] + '(dict data, dict error) {};\n'
    elif line.count('*') == 0:
        on_line = 'virtual void on' + cbName[2:] + '() {};\n'
    else:
        on_line = ''   
        
    fheaderon.write(on_line)
    fheaderon.write('\n')
    
    # 生成封装部分
    createWrap(cbName, line)
    

#----------------------------------------------------------------------
def createWrap(cbName, line):
    """在Python封装段代码中进行处理"""
    # 生成.h文件中的on部分
    #if 'OnRspError' in cbName:
        #on_line = 'virtual void on' + cbName[2:] + '(dict error, int id, bool last)\n'    
        #override_line = '("on' + cbName[2:] + '")(error, id, last);\n' 
    #elif 'OnRsp' in cbName:
        #on_line = 'virtual void on' + cbName[2:] + '(dict data, dict error, int id, bool last)\n'
        #override_line = '("on' + cbName[2:] + '")(data, error, id, last);\n' 
    #elif 'OnRtn' in cbName:
        #on_line = 'virtual void on' + cbName[2:] + '(dict data)\n'
        #override_line = '("on' + cbName[2:] + '")(data);\n'
    #elif 'OnErrRtn' in cbName:
        #on_line = 'virtual void on' + cbName[2:] + '(dict data, dict error)\n'
        #override_line = '("on' + cbName[2:] + '")(data, error);\n'
    #else:
        #on_line = ''
        
    if line.count('*') == 1:
        on_line = 'virtual void on' + cbName[2:] + '(dict data)\n'    
        override_line = '("on' + cbName[2:] + '")(data);\n'    
    elif line.count('*') == 2:
        if "int" in line:
            on_line = 'virtual void on' + cbName[2:] + '(dict data, dict error, int id, bool last)\n'
            override_line = '("on' + cbName[2:] + '")(data, error, id, last);\n'  
        else:
            on_line = 'virtual void on' + cbName[2:] + '(dict data, dict error)\n'
            override_line = '("on' + cbName[2:] + '")(data, error);\n'  
    elif line.count('*') == 0:
        on_line = 'virtual void on' + cbName[2:] + '()\n'
        override_line = '("on' + cbName[2:] + '")();\n'
    else:
        on_line = ''
        
    if on_line is not '':
        fwrap.write(on_line)
        fwrap.write('{\n')
        fwrap.write('    try\n')
        fwrap.write('    {\n')
        fwrap.write('        this->get_override'+override_line)
        fwrap.write('    }\n')
        fwrap.write('    catch (error_already_set const &)\n')
        fwrap.write('    {\n')
        fwrap.write('        PyErr_Print();\n')
        fwrap.write('    }\n')
        fwrap.write('};\n')
        fwrap.write('\n')
    
    

def createTask(cbName, cbArgsTypeList, cbArgsValueList, orignalLine):
    # 从回调函数生成任务对象，并放入队列
    funcline = orignalLine.replace('            virtual void ', 'void ' + apiName + '::')
    funcline = funcline.replace('{};', '')

    ftask.write(funcline)
    ftask.write('{\n')
    ftask.write("    Task* task = new Task();\n")

    ftask.write("    task->task_name = " + cbName.upper() + ";\n")

    # define常量
    global define_count
    fdefine.write("#define " + cbName.upper() + ' ' + str(define_count) + '\n')
    define_count = define_count + 1

    # switch段代码
    fswitch.write("case " + cbName.upper() + ':\n')
    fswitch.write("{\n")
    fswitch.write("    this->" + cbName.replace('On', 'process') + '(task);\n')
    fswitch.write("    break;\n")
    fswitch.write("}\n")
    fswitch.write("\n")

    for i, type_ in enumerate(cbArgsTypeList):
        if type_ == 'int':
            ftask.write("    task->task_id = " + cbArgsValueList[i] + ";\n")
        elif type_ == 'bool':
            ftask.write("    task->task_last = " + cbArgsValueList[i] + ";\n")
        elif 'XTPRI' in type_:
            ftask.write("\n")
            ftask.write("    if (error_info)\n")
            ftask.write("    {\n")
            ftask.write("        " + type_ + ' *task_error = new ' + type_ + '();\n')
            ftask.write("        " + '*task_error = ' + cbArgsValueList[i] + ';\n')
            ftask.write("        task->task_error = task_error;\n")
            ftask.write("    }\n")
            ftask.write("\n")    
        else:
            ftask.write("\n")
            ftask.write("    if (" + cbArgsValueList[i][1:] + ")\n")
            ftask.write("    {\n")
            
            ftask.write("        " + type_ + ' *task_data = new ' + type_ + '();\n')
            ftask.write("        " + '*task_data = ' + cbArgsValueList[i] + ';\n')
            ftask.write("        task->task_data = task_data;\n")
            ftask.write("    }\n")        

    ftask.write("    this->task_queue.push(task);\n")
    ftask.write("};\n")
    ftask.write("\n")


def createProcess(cbName, cbArgsTypeList, cbArgsValueList):
    # 从队列中提取任务，并转化为python字典
    fprocess.write("void " + apiName + '::' + cbName.replace('On', 'process') + '(Task *task)' + "\n")
    fprocess.write("{\n")
    fprocess.write("    PyLock lock;\n")

    onArgsList = []
    print(cbName, cbArgsTypeList)
    
    for i, type_ in enumerate(cbArgsTypeList):
        if 'XTPRI' in type_:
            fprocess.write("    "+ "dict error;\n")
            fprocess.write("    if (task->task_error)\n")
            fprocess.write("    {\n")
            fprocess.write("        "+ type_ + ' *task_error = (' + type_ + '*) task->task_error;\n')
            
            struct = structDict[type_]
            for key in struct.keys():
                fprocess.write("        "+ 'error["' + key + '"] = task_error->' + key + ';\n')

            fprocess.write("        delete task->task_error;\n")
            fprocess.write("    }\n")
            fprocess.write("\n")

            onArgsList.append('error')

        elif type_ in structDict:
            fprocess.write("    "+ "dict data;\n")
            fprocess.write("    if (task->task_data)\n")
            fprocess.write("    {\n")
            fprocess.write("        "+ type_ + ' *task_data = (' + type_ + '*) task->task_data;\n')
            
            struct = structDict[type_]
            for key, value in struct.items():
                if value != 'enum':
                    fprocess.write("        "+ 'data["' + key + '"] = task_data->' + key + ';\n')
                else:
                    fprocess.write("        "+ 'data["' + key + '"] = (int)task_data->' + key + ';\n')

            fprocess.write("        delete task->task_data;\n")
            fprocess.write("    }\n")
            fprocess.write("\n")

            onArgsList.append('data')

        elif type_ == 'bool':
            onArgsList.append('task->task_last')

        elif type_ == 'int':
            onArgsList.append('task->task_id')

    onArgs = join(onArgsList, ', ')
    fprocess.write('    this->' + cbName.replace('On', 'on') + '(' + onArgs +');\n')
    fprocess.write('    delete task;\n')

    fprocess.write("};\n")
    fprocess.write("\n")


def processFunction(line):
    line = line.replace('    virtual int ', '')       # 删除行首的无效内容
    line = line.replace('    virtual uint64_t ', '')       # 删除行首的无效内容
    line = line.replace(') = 0;\n', '')                # 删除行尾的无效内容

    content = line.split('(')
    fcName = content[0]                             # 回调函数名称

    fcArgs = content[1]                             # 回调函数参数
    fcArgs = fcArgs.replace(')', '')

    fcArgsList = fcArgs.split(', ')                 # 将每个参数转化为列表
    print(fcArgsList)
    fcArgsTypeList = []
    fcArgsValueList = []

    for arg in fcArgsList:                          # 开始处理参数
        content = arg.split(' ')
        if 'const' in content:
            content.remove('const')
        if len(content) > 1:
            #print content
            fcArgsTypeList.append(content[0])           # 参数类型列表
            fcArgsValueList.append(content[1])          # 参数数据列表

    if len(fcArgsTypeList)>0 and fcArgsTypeList[0] in structDict:
        createFunction(fcName, fcArgsTypeList, fcArgsValueList)
        
    # 生成.h文件中的主动函数部分
    if 'Req' in fcName:
        req_line = 'int req' + fcName[3:] + '(dict req, int reqid);\n'
        fheaderfunction.write(req_line)
        fheaderfunction.write('\n')


def createFunction(fcName, fcArgsTypeList, fcArgsValueList):
    type_ = fcArgsTypeList[0]
    struct = structDict[type_]
    
    fcName = fcName.strip()

    ffunction.write('int TraderApi::' + fcName[0].lower() + fcName[1:] + '(dict req, int reqid)\n')
    ffunction.write('{\n')
    ffunction.write('    ' + type_ +' myreq = ' + type_ + '();\n')
    ffunction.write('    memset(&myreq, 0, sizeof(myreq));\n')

    for key, value in struct.items():
        if value == 'string':
            line = '    getString(req, "' + key + '", myreq.' + key + ');\n'
        elif value == 'char':
            line = '    getChar(req, "' + key + '", &myreq.' + key + ');\n'
        elif value == 'int':
            line = '    getInt(req, "' + key + '", &myreq.' + key + ');\n'
        elif value == 'double':
            line = '    getDouble(req, "' + key + '", &myreq.' + key + ');\n'
        elif value == 'float':
            line = '    getDouble(req, "' + key + '", &myreq.' + key + ');\n'     
        elif value == 'enum':
            line = '    getEnum(req, "' + key + '", &myreq.' + key + ');\n'     

        ffunction.write(line)

    ffunction.write('    int i = this->api->' + fcName + '(&myreq, reqid);\n')
    ffunction.write('    return i;\n')

    ffunction.write('};\n')
    ffunction.write('\n')




#########################################################
apiName = 'TraderApi'

fcpp = open('xtp_trader_api.h', 'r')
ftask = open('xtp_td_task.cpp', 'w')
fprocess = open('xtp_td_process.cpp', 'w')
ffunction = open('xtp_td_function.cpp', 'w')
fdefine = open('xtp_td_define.cpp', 'w')
fswitch = open('xtp_td_switch.cpp', 'w')
fheaderprocess = open('xtp_td_header_process.h', 'w')
fheaderon = open('xtp_td_header_on.h', 'w')
fheaderfunction = open('xtp_td_header_function.h', 'w')
fwrap = open('xtp_td_wrap.cpp', 'w')

define_count = 1

for line in replaceTabs(fcpp):
    if "virtual void On" in line:
        processCallBack(line)
    elif "virtual int" in line:
        processFunction(line)
    elif "virtual uint64_t" in line:
        processFunction(line)

fcpp.close()
ftask.close()
fprocess.close()
ffunction.close()
fswitch.close()
fdefine.close()
fheaderprocess.close()
fheaderon.close()
fheaderfunction.close()
fwrap.close()

print('td functions done')