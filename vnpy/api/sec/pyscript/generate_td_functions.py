# encoding: UTF-8

from generate_data_type import pre_process

import sec_struct
STRUCT_DICT = sec_struct.__dict__

API_NAME = 'TdApi'
FILE_PREFIX = 'sec_td_'
ERROR_STRUCT = 'DFITCSECRspInfoField'

#----------------------------------------------------------------------
def process_callback(cpp_line):
    '''处理回调'''
    # 预处理
    new_line = cpp_line.replace('    virtual void ', '')
    
    # 获取回调函数名
    cb_name = new_line[:new_line.index('(')]
    
    # 获取回调参数
    args_line = new_line[(new_line.index('(')+1):new_line.index(')')]
    args_line = args_line.replace('struct ', '')
    args_line = args_line.replace('*', '')
    
    if not args_line:
        return
    
    args_list = args_line.split(',')    # 参数列表
    args_type_list = []                 # 参数类型
    args_name_list = []                 # 参数名
    
    for arg in args_list:
        l = arg.split(' ')
        l = [i for i in l if i]
        
        args_type_list.append(l[0])
        args_name_list.append(l[1])
        
    create_task(cb_name, args_type_list, args_name_list, cpp_line)
    create_process(cb_name, args_type_list, args_name_list)
    create_callback(cb_name, args_type_list)

#----------------------------------------------------------------------
def process_function(cpp_line):
    '''处理主动'''
    new_line = cpp_line.replace('     virtual int ', '')       
    new_line = new_line.replace(') = 0;\n', '')                

    # 获取主动函数名
    fc_name = new_line[:new_line.index('(')]
    
    # 获取主动参数
    args_line = new_line[(new_line.index('(')+1):new_line.index(')')]
    args_line = args_line.replace('*', '')
    args_line = args_line.replace('struct', '')
    
    if not args_line:
        return
    
    args_list = args_line.split(',')    # 参数列表
    args_type_list = []                 # 参数类型
    args_name_list = []                 # 参数名
    
    for arg in args_list:
        l = arg.split(' ')
        l = [i for i in l if i]
        
        args_type_list.append(l[0])
        args_name_list.append(l[1])    

    print args_type_list
    if args_type_list and args_type_list[0] in STRUCT_DICT:
        create_function(fc_name, args_type_list, args_name_list)
    
#----------------------------------------------------------------------
def create_task(cb_name, args_type_list, args_name_list, cpp_line):
    '''创建任务部分'''
    # 从回调函数生成任务对象，并放入队列
    new_cb_line = cpp_line.replace('    virtual void ', 'void ' + API_NAME + '::')
    new_cb_line = new_cb_line.replace('{}', '')

    source_task_f.write(new_cb_line + '\n')
    source_task_f.write('{\n')
    source_task_f.write('\tTask *task = new Task();\n')
    source_task_f.write('\ttask->task_name = %s;\n' %cb_name.upper())
    
    for i, arg_type in enumerate(args_type_list):
        arg_name = args_name_list[i]
        
        if arg_type == 'bool':
            source_task_f.write('\ttask->task_last = %s;\n' %arg_name)

        elif ERROR_STRUCT in arg_type:
            source_task_f.write('\n')
            source_task_f.write('\tif (%s)\n' %arg_name)
            source_task_f.write('\t{\n')
            source_task_f.write('\t\t%s *task_error = new %s();\n' %(arg_type, arg_type))
            source_task_f.write('\t\t *task_error = *%s;\n' %arg_name)
            source_task_f.write('\t\ttask->task_error = task_error;\n')
            source_task_f.write('\t}\n')
            source_task_f.write('\n')                

        else:
            source_task_f.write('\n')
            source_task_f.write('\tif (%s)\n' %arg_name)
            source_task_f.write('\t{\n')
        
            source_task_f.write('\t\t%s *task_data = new %s();\n' %(arg_type, arg_type))
            source_task_f.write('\t\t *task_data = *%s;\n' %arg_name)
            source_task_f.write('\t\ttask->task_data = task_data;\n')
            source_task_f.write('\t}\n')             

    source_task_f.write('\tthis->task_queue.push(task);\n')
    source_task_f.write('};\n')
    source_task_f.write('\n')
    
    # define常量
    global define_count
    define_count += 1
    header_define_f.write('#define %s %s\n' %(cb_name.upper(), define_count))

    # switch段代码
    source_switch_f.write('case %s:\n' %cb_name.upper())
    source_switch_f.write('{\n')
    source_switch_f.write('\tthis->%s(task);\n' %cb_name.replace('On', 'process'))
    source_switch_f.write('\tbreak;\n')
    source_switch_f.write('}\n')
    source_switch_f.write('\n')

#----------------------------------------------------------------------
def create_process(cb_name, args_type_list, args_name_list):
    '''创建处理部分'''
    source_process_f.write('void %s::%s(Task *task)\n' %(API_NAME, cb_name.replace('On', 'process')))
    source_process_f.write('{\n')
    source_process_f.write('\tPyLock lock;\n')

    new_args_list = []

    for i, arg_type in enumerate(args_type_list):
        if ERROR_STRUCT in arg_type:
            source_process_f.write('\tdict error;\n')
            source_process_f.write('\tif (task->task_error)\n')
            source_process_f.write('\t{\n')
            source_process_f.write('\t\t%s *task_error = (%s*)task->task_error;\n' %(arg_type, arg_type))
            
            struct = STRUCT_DICT[arg_type]
            for key in struct.keys():
                source_process_f.write('\t\terror[\"%s\"] = task_error->%s;\n' %(key, key))

            source_process_f.write('\t\tdelete task->task_error;\n')
            source_process_f.write('\t}\n')
            source_process_f.write('\n')

            new_args_list.append('error')

        elif arg_type in STRUCT_DICT:
            source_process_f.write('\tdict data;\n')
            source_process_f.write('\tif (task->task_data)\n')
            source_process_f.write('\t{\n')
            source_process_f.write('\t\t%s *task_data = (%s*)task->task_data;\n' %(arg_type, arg_type))
            
            struct = STRUCT_DICT[arg_type]
            for key in struct.keys():
                source_process_f.write('\t\tdata[\"%s\"] = task_data->%s;\n' %(key, key))

            source_process_f.write('\t\tdelete task->task_data;\n')
            source_process_f.write('\t}\n')
            source_process_f.write('\n')

            new_args_list.append('data')

        elif arg_type == 'bool':
            new_args_list.append('task->task_last')
            
    new_args = ', '.join(new_args_list)
    
    source_process_f.write('\tthis->%s(%s);\n' %(cb_name.replace('On', 'on'), new_args))
    source_process_f.write('\tdelete task;\n')
    source_process_f.write('};\n')
    source_process_f.write('\n')
    
    # 生成.h文件中的process部分
    process_line = 'void %s (Task *task);\n' %(cb_name.replace('On', 'process'))
    header_process_f.write(process_line)
    header_process_f.write('\n')    

#----------------------------------------------------------------------
def create_callback(cb_name, args_type_list):
    '''创建回调部分'''
    # 生成.h文件中的on部分        
    new_args_list = []
    new_names_list = []
    
    for arg_type in args_type_list:
        if arg_type == 'bool':
            new_args_list.append('bool flag')
            new_names_list.append('flag')
        elif arg_type == ERROR_STRUCT:
            new_args_list.append('dict error')
            new_names_list.append('error')
        elif arg_type in STRUCT_DICT:
            new_args_list.append('dict data')
            new_names_list.append('data')
    
    new_args_line = ', '.join(new_args_list)
    new_line = 'virtual void %s(%s){};\n' %(cb_name.replace('On', 'on'), new_args_line)
    header_on_f.write(new_line)
    header_on_f.write('\n')
    
    # 生成.cpp中的封装部分
    override_line = '("%s")(%s)' %(cb_name.replace('On', 'on'), ', '.join(new_names_list))
    
    source_wrap_f.write(new_line.replace('{};', ''))
    source_wrap_f.write('{\n')
    source_wrap_f.write('\ttry\n')
    source_wrap_f.write('\t{\n')
    source_wrap_f.write('\t\tthis->get_override%s;\n' %override_line)
    source_wrap_f.write('\t}\n')
    source_wrap_f.write('\tcatch (error_already_set const &)\n')
    source_wrap_f.write('\t{\n')
    source_wrap_f.write('\t\tPyErr_Print();\n')
    source_wrap_f.write('\t}\n')
    source_wrap_f.write('};\n')
    source_wrap_f.write('\n')
    

#----------------------------------------------------------------------
def create_function(fc_name, args_type_list, args_name_list):
    '''创建主动函数部分'''
    # 生成.cpp文件中的主动函数部分
    arg_type = args_type_list[0]
    struct = STRUCT_DICT[arg_type]
    
    source_function_f.write('int %s::%s(dict req)\n' %(API_NAME, fc_name.replace('Req', 'req')))
    source_function_f.write('{\n')
    source_function_f.write('\t%s myreq = %s();\n' %(arg_type, arg_type))
    source_function_f.write('\tmemset(&myreq, 0, sizeof(myreq));\n')

    for key, value in struct.items():
        if value == 'string':
            line = '\tgetString(req, "%s", myreq.%s);\n' %(key, key)
        elif value == 'int':
            line = '\tgetInt(req, "%s", &myreq.%s);\n' %(key, key)
        elif value == 'long':
            line = '\tgetLong(req, "%s", &myreq.%s);\n' %(key, key)
        elif value == 'double':
            line = '\tgetDouble(req, "%s", &myreq.%s);\n' %(key, key)
        source_function_f.write(line)

    source_function_f.write('\tint i = this->api->%s(&myreq);\n' %fc_name)
    source_function_f.write('\treturn i;\n')
    source_function_f.write('};\n')
    source_function_f.write('\n')    
    
    # 生成.h文件中的主动函数部分
    if 'Req' in fc_name:
        req_line = 'int %s(dict req);\n' %fc_name.replace('Req', 'req')
        header_function_f.write(req_line)
        header_function_f.write('\n')
    

# 打开文件
cpp_f = open('DFITCSECTraderApi.h', 'r')

source_task_f = open(FILE_PREFIX + 'task.cpp', 'w')
source_process_f = open(FILE_PREFIX + 'process.cpp', 'w')
source_function_f = open(FILE_PREFIX + 'function.cpp', 'w')
source_switch_f = open(FILE_PREFIX + 'switch.cpp', 'w')
source_wrap_f = open(FILE_PREFIX + 'wrap.cpp', 'w')

header_define_f = open(FILE_PREFIX + 'define.h', 'w')
header_process_f = open(FILE_PREFIX + 'header_process.h', 'w')
header_on_f = open(FILE_PREFIX + 'header_on.h', 'w')
header_function_f = open(FILE_PREFIX + 'header_function.h', 'w')

# 常量技术
define_count = 0

# 遍历处理
for n, cpp_line in enumerate(cpp_f):
    cpp_line = pre_process(cpp_line)
    
    if 'virtual void On' in cpp_line:
        process_callback(cpp_line)
    elif 'virtual int' in cpp_line:
        process_function(cpp_line)

# 退出
cpp_f.close()
source_task_f.close()
source_process_f.close()
source_function_f.close()
source_switch_f.close()
source_wrap_f.close()
header_define_f.close()
header_process_f.close()
header_on_f.close()
header_function_f.close()

print API_NAME + u'处理完成'