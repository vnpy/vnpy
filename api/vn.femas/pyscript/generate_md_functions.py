# encoding: UTF-8

__author__ = 'CHENXY'

from string import join
from femas_struct import structDict



def processCallBack(line):
    orignalLine = line
    line = line.replace('\tvirtual void ', '')      # 删除行首的无效内容
    line = line.replace('{};\n', '')                # 删除行尾的无效内容

    content = line.split('(')
    cbName = content[0]                             # 回调函数名称

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


def createTask(cbName, cbArgsTypeList, cbArgsValueList, orignalLine):
    # 从回调函数生成任务对象，并放入队列
    funcline = orignalLine.replace('\tvirtual void ', 'void ' + apiName + '::')
    funcline = funcline.replace('{};', '')

    ftask.write(funcline)
    ftask.write('{\n')
    ftask.write("\tTask task = Task();\n")

    ftask.write("\ttask.task_name = " + cbName.upper() + ";\n")

    # define常量
    global define_count
    fdefine.write("#define " + cbName.upper() + ' ' + str(define_count) + '\n')
    define_count = define_count + 1

    # switch段代码
    fswitch.write("case " + cbName.upper() + ':\n')
    fswitch.write("{\n")
    fswitch.write("\tthis->" + cbName.replace('On', 'process') + '(task);\n')
    fswitch.write("\tbreak;\n")
    fswitch.write("}\n")
    fswitch.write("\n")

    for i, type_ in enumerate(cbArgsTypeList):
        if type_ == 'int':
            ftask.write("\ttask.task_id = " + cbArgsValueList[i] + ";\n")
        elif type_ == 'bool':
            ftask.write("\ttask.task_last = " + cbArgsValueList[i] + ";\n")
        elif 'RspInfoField' in type_:
            ftask.write("\tif (pRspInfo)\n")
            ftask.write("\t{\n")
            ftask.write("\t\ttask.task_error = " + cbArgsValueList[i] + ";\n")
            ftask.write("\t}\n")
            ftask.write("\telse\n")
            ftask.write("\t{\n")
            ftask.write("\t\tCSecurityFtdcRspInfoField empty_error = CSecurityFtdcRspInfoField();\n")
            ftask.write("\t\tmemset(&empty_error, 0, sizeof(empty_error));\n")
            ftask.write("\t\ttask.task_error = empty_error;\n")
            ftask.write("\t}\n")
        else:
            ftask.write("\ttask.task_data = " + cbArgsValueList[i] + ";\n")

    ftask.write("\tthis->task_queue.push(task);\n")
    ftask.write("};\n")
    ftask.write("\n")


def createProcess(cbName, cbArgsTypeList, cbArgsValueList):
    # 从队列中提取任务，并转化为python字典
    fprocess.write("void " + apiName + '::' + cbName.replace('On', 'process') + '(Task task)' + "\n")
    fprocess.write("{\n")
    fprocess.write("\tPyLock lock;\n")

    onArgsList = []

    for i, type_ in enumerate(cbArgsTypeList):
        if 'RspInfoField' in type_:
            fprocess.write("\t"+ type_ + ' task_error = any_cast<' + type_ + '>(task.task_error);\n')
            fprocess.write("\t"+ "dict error;\n")

            struct = structDict[type_]
            for key in struct.keys():
                fprocess.write("\t"+ 'error["' + key + '"] = task_error.' + key + ';\n')

            fprocess.write("\n")

            onArgsList.append('error')

        elif type_ in structDict:
            fprocess.write("\t"+ type_ + ' task_data = any_cast<' + type_ + '>(task.task_data);\n')
            fprocess.write("\t"+ "dict data;\n")

            struct = structDict[type_]
            for key in struct.keys():
                fprocess.write("\t"+ 'data["' + key + '"] = task_data.' + key + ';\n')

            fprocess.write("\n")

            onArgsList.append('data')

        elif type_ == 'bool':
            onArgsList.append('task.task_last')

        elif type_ == 'int':
            onArgsList.append('task.task_id')

    onArgs = join(onArgsList, ', ')
    fprocess.write('\tthis->' + cbName.replace('On', 'on') + '(' + onArgs +');\n')

    fprocess.write("};\n")
    fprocess.write("\n")


def processFunction(line):
    line = line.replace('\tvirtual int ', '')       # 删除行首的无效内容
    line = line.replace(') = 0;\n', '')                # 删除行尾的无效内容

    content = line.split('(')
    fcName = content[0]                             # 回调函数名称

    fcArgs = content[1]                             # 回调函数参数
    fcArgs = fcArgs.replace(')', '')

    fcArgsList = fcArgs.split(', ')                 # 将每个参数转化为列表

    fcArgsTypeList = []
    fcArgsValueList = []

    for arg in fcArgsList:                          # 开始处理参数
        content = arg.split(' ')
        if len(content) > 1:
            fcArgsTypeList.append(content[0])           # 参数类型列表
            fcArgsValueList.append(content[1])          # 参数数据列表

    if len(fcArgsTypeList)>0 and fcArgsTypeList[0] in structDict:
        createFunction(fcName, fcArgsTypeList, fcArgsValueList)


def createFunction(fcName, fcArgsTypeList, fcArgsValueList):
    type_ = fcArgsTypeList[0]
    struct = structDict[type_]

    ffunction.write(fcName + '\n')
    ffunction.write('{\n')
    ffunction.write('\t' + type_ +' myreq = ' + type_ + '();\n')
    ffunction.write('\tmemset(&myreq, 0, sizeof(myreq));\n')

    for key, value in struct.items():
        if value == 'string':
            line = '\tgetChar(req, "' + key + '", myreq.' + key + ');\n'
        elif value == 'int':
            line = '\tgetInt(req, "' + key + '", &myreq.' + key + ');\n'
        elif value == 'double':
            line = '\tgetDouble(req, "' + key + '", &myreq.' + key + ');\n'
        ffunction.write(line)

    ffunction.write('\tint i = this->api->' + fcName + '(&myreq, nRequestID);\n')
    ffunction.write('\treturn i;\n')

    ffunction.write('};\n')
    ffunction.write('\n')




#########################################################
apiName = 'MdApi'

fcpp = open('USTPFtdcMduserApi.h', 'r')
ftask = open('femas_md_task.cpp', 'w')
fprocess = open('femas_md_process.cpp', 'w')
ffunction = open('femas_md_function.cpp', 'w')
fdefine = open('femas_md_define.cpp', 'w')
fswitch = open('femas_md_switch.cpp', 'w')

define_count = 1

for line in fcpp:
    if "\tvirtual void On" in line:
        processCallBack(line)
    elif "\tvirtual int" in line:
        processFunction(line)

fcpp.close()
ftask.close()
fprocess.close()
ffunction.close()
fswitch.close()
fdefine.close()