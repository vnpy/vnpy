""""""
import importlib


class ApiGenerator:
    """API生成器"""""

    def __init__(self, filename: str, prefix: str, name: str, class_name: str):
        """Constructor"""
        self.filename = filename
        self.prefix = prefix
        self.name = name
        self.class_name = class_name

        self.callbacks = {}
        self.functions = {}
        self.lines = {}

        self.structs = {}
        self.typedefs = {}
        self.load_constant()
        self.load_struct()

    def load_constant(self) -> None:
        """"""
        if self.name == "md":
            module_names = ["tap_md_commen_typedef", "tap_md_data_typedef"]
        elif self.name == "td":
            module_names = ["tap_td_commen_typedef", "tap_td_data_typedef"]

        for module_name in module_names:
            module = importlib.import_module(module_name)

            for name in dir(module):
                if "__" not in name:
                    self.typedefs[name] = getattr(module, name)

    def load_struct(self):
        """加载Struct"""
        module_names = ["tap_md_data_struct", "tap_md_commen_struct", "tap_td_data_struct", "tap_td_commen_struct"]

        for module_name in module_names:
            module = importlib.import_module(module_name)

            for name in dir(module):
                if "__" not in name:
                    self.structs[name] = getattr(module, name)

    def run(self):
        """运行生成"""
        self.f_cpp = open(self.filename, "r", encoding="UTF-8")

        for line in self.f_cpp:
            self.process_line(line)

        self.f_cpp.close()
        # print("self.callbacks=",self.callbacks,"\n\n")
        # print("self.functions=", self.functions,"\n\n")
        # print("self.lines=", self.lines,"\n\n")

        # print("self.structs=", self.structs,"\n\n")
        # print("self.typedefs=", self.typedefs,"\n\n")

        self.generate_header_define()
        self.generate_header_process()
        self.generate_header_on()
        self.generate_header_function()

        self.generate_source_task()
        self.generate_source_switch()
        self.generate_source_process()
        self.generate_source_function()
        self.generate_source_on()
        self.generate_source_module()

        print(f"{self.name}_API生成成功")

    def process_line(self, line: str):
        """处理每行"""
        line = line.replace(";", "")
        line = line.replace("\n", "")
        line = line.replace("\t", "")
        line = line.replace("{}", "")

        if "virtual void TAP_CDECL On" in line:
            self.process_callback(line)
        elif "virtual ITapTrade::TAPIINT32 TAP_CDECL Qry" in line:
            self.process_function(line)
        elif "virtual TAPIINT32 TAP_CDECL Qry" in line:
            self.process_function(line)

    def process_callback(self, line: str):
        """处理回掉函数"""
        name = line[line.index("On"):line.index("(")]
        line = line.replace("        ", "")
        new_line = self.standard_format(line)
        self.lines[name] = new_line

        d = self.generate_arg_dict(line)
        self.callbacks[name] = d

    def standard_format(self, line: str):
        """"""
        line = line.split("=")[0]
        line = line.replace("virtual void TAP_CDECL", "virtual void")
        header = line.split("(")[0]

        args_str = line[line.index("(") + 1:line.index(")")]
        if not args_str:
            f_content = ""
        else:
            args = args_str.split(",")
            content = ""
            for arg in args:
                words = arg.split(" ")
                if len(words) > 2:
                    tap_type = words[-2]
                    name = words[-1]

                    if "::" in tap_type:
                        tap_type = tap_type.split("::")[1]

                    cpp_type = self.typedefs.get(tap_type, "dict")
                    if cpp_type == "dict":
                        cpp_type = tap_type

                    item = f"{cpp_type} {name}, "
                    content = content + item
                elif len(words) == 2:
                    tap_type = words[0]
                    name = words[1]

                    if "::" in tap_type:
                        tap_type = tap_type.split("::")[1]
                    cpp_type = self.typedefs[tap_type]

                    item = f"{cpp_type} {name}, "
                    content = content + item
            f_content = content[:-2]

        new_line = f"{header}({f_content})"
        return new_line

    def process_function(self, line: str):
        """处理主动函数"""
        name = line[line.index("Qry"):line.index("(")]

        d = self.generate_arg_dict(line)
        self.functions[name] = d

    def generate_arg_dict(self, line: str):
        """生成参数字典"""
        args_str = line[line.index("(") + 1:line.index(")")]
        if not args_str:
            return {}
        args = args_str.split(",")

        d = {}
        for arg in args:
            words = arg.split(" ")
            words = [word for word in words if word]

            tap_type = words[-2].replace("*", "")
            name = words[-1].replace("*", "")
            if "::" in tap_type:
                tap_type = tap_type.split("::")[1]

            cpp_type = self.typedefs.get(tap_type, tap_type)
            if cpp_type == "dict":
                cpp_type = tap_type
            d[name] = cpp_type
        return d

    def generate_header_define(self):
        """"""
        filename = f"{self.prefix}_{self.name}_header_define.h"
        with open(filename, "w") as f:
            for n, name in enumerate(self.callbacks.keys()):
                line = f"#define {name.upper()} {n}\n"
                f.write(line)

    def generate_header_process(self):
        """"""
        filename = f"{self.prefix}_{self.name}_header_process.h"
        with open(filename, "w") as f:
            for name in self.callbacks.keys():
                name = name.replace("On", "process")
                line = f"void {name}(Task *task);\n\n"
                f.write(line)

    def generate_header_on(self):
        """"""
        filename = f"{self.prefix}_{self.name}_header_on.h"
        with open(filename, "w") as f:
            for function_name, d in self.callbacks.items():
                function_name = function_name.replace("On", "on")

                args_list = []
                for name, type_ in d.items():
                    if type_ == "unsigned int":
                        args_list.append("unsigned int session")
                    elif type_ == "int":
                        if name == "errorCode":
                            args_list.append("int error")
                        elif name == "reasonCode":
                            args_list.append("int reason")
                        else:
                            args_list.append(f"int {name}")
                    elif type_ == "char":
                        args_list.append("char last")
                    elif type_ == "string":
                        args_list.append(f"string {name}")
                    else:
                        args_list.append("const dict &data")

                args_str = ", ".join(args_list)
                line = f"virtual void {function_name}({args_str}) {{}};\n\n"

                f.write(line)

    def generate_header_function(self):
        """"""
        filename = f"{self.prefix}_{self.name}_header_function.h"
        with open(filename, "w") as f:
            for function_name, d in self.functions.items():
                function_name = function_name.replace("Qry", "qry")

                args_list = []
                for name, type_ in d.items():
                    if type_ == "unsigned int":
                        args_list.append("unsigned int session")
                    else:
                        args_list.append("const dict &data")

                args_str = ", ".join(args_list)
                line = f"int {function_name}({args_str});\n\n"
                f.write(line)

    def generate_source_task(self):
        """"""
        filename = f"{self.prefix}_{self.name}_source_task.cpp"
        with open(filename, "w") as f:
            for name, d in self.callbacks.items():
                line = self.lines[name]

                f.write(line.replace("virtual void ",
                                     f"void {self.class_name}::") + "\n")
                f.write("{\n")
                f.write("\tTask task = Task();\n")
                f.write(f"\ttask.task_name = {name.upper()};\n")

                for field, type_ in d.items():
                    if type_ == "unsigned int":
                        f.write(f"\ttask.task_id = {field};\n")
                    elif type_ == "int":
                        f.write(f"\ttask.task_int = {field};\n")
                    elif type_ == "char":
                        f.write(f"\ttask.task_last = {field};\n")
                    elif type_ == "string":
                        f.write(f"\ttask.task_string = {field};\n")
                    else:
                        f.write(f"\tif ({field})\n")
                        f.write("\t{\n")
                        f.write(f"\t\t{type_} *task_data = new {type_}();\n")
                        f.write(f"\t\t*task_data = *{field};\n")
                        f.write(f"\t\ttask.task_data = task_data;\n")
                        f.write("\t}\n")

                f.write(f"\tthis->task_queue.push(task);\n")
                f.write("};\n\n")

    def generate_source_switch(self):
        """"""
        filename = f"{self.prefix}_{self.name}_source_switch.cpp"
        with open(filename, "w") as f:
            for name in self.callbacks.keys():
                process_name = name.replace("On", "process")
                f.write(f"case {name.upper()}:\n")
                f.write("{\n")
                f.write(f"\tthis->{process_name}(&task);\n")
                f.write(f"\tbreak;\n")
                f.write("}\n\n")

    def generate_source_process(self):
        """"""
        filename = f"{self.prefix}_{self.name}_source_process.cpp"
        with open(filename, "w") as f:
            for name, d in self.callbacks.items():
                process_name = name.replace("On", "process")
                on_name = name.replace("On", "on")

                f.write(
                    f"void {self.class_name}::{process_name}(Task *task)\n")
                f.write("{\n")
                if len(d.keys()) == 0:
                    f.write(f"\tthis->{on_name}();\n")
                    f.write("};\n\n")
                else:
                    f.write("\tgil_scoped_acquire acquire;\n")
                    args = []
                    for field, type_ in d.items():
                        if type_ == "unsigned int":
                            args.append("task->task_id")
                        elif type_ == "int":
                            args.append("task->task_int")
                        elif type_ == "string":
                            args.append("task->task_string")
                        elif type_ == "char":
                            args.append("task->task_last")
                        else:
                            args.append("data")
                            f.write("\tdict data;\n")
                            f.write("\tif (task->task_data)\n")
                            f.write("\t{\n")
                            f.write(
                                f"\t\t{type_} *task_data = ({type_}*)task->task_data;\n")

                            struct_fields = self.structs[type_]
                            for struct_field, struct_type in struct_fields.items():
                                if struct_type == "string":
                                    f.write(
                                        f"\t\tdata[\"{struct_field}\"] = toUtf(task_data->{struct_field});\n")
                                else:
                                    f.write(
                                        f"\t\tdata[\"{struct_field}\"] = task_data->{struct_field};\n")

                            f.write("\t\tdelete task_data;\n")
                            f.write("\t}\n")

                    args_str = ", ".join(args)
                    f.write(f"\tthis->{on_name}({args_str});\n")
                    f.write("};\n\n")

    def generate_source_function(self):
        """"""
        filename = f"{self.prefix}_{self.name}_source_function.cpp"
        with open(filename, "w") as f:
            for name, d in self.functions.items():
                req_name = name.replace("Qry", "qry")

                length = len(d.keys())
                if length == 1:
                    f.write(f"int {self.class_name}::{req_name}(unsigned int session)\n")
                    f.write("{\n")
                    f.write(f"\tint i = this->api->{name}(session);\n")
                    f.write("\treturn i;\n")
                    f.write("};\n\n")
                else:
                    type_ = list(d.values())[1]
                    f.write(
                        f"int {self.class_name}::{req_name}(unsigned int session, const dict &req)\n")
                    f.write("{\n")
                    f.write(f"\t{type_} myreq = {type_}();\n")
                    f.write("\tmemset(&myreq, 0, sizeof(myreq));\n")

                    struct_fields = self.structs[type_]
                    for struct_field, struct_type in struct_fields.items():
                        if struct_type == "string":
                            line = f"\tgetString(req, \"{struct_field}\", myreq.{struct_field});\n"
                        else:
                            line = f"\tget{struct_type.capitalize()}(req, \"{struct_field}\", &myreq.{struct_field});\n"
                        f.write(line)

                    f.write(f"\tint i = this->api->{name}(session, &myreq);\n")
                    f.write("\treturn i;\n")
                    f.write("};\n\n")

    def generate_source_on(self):
        """"""
        filename = f"{self.prefix}_{self.name}_source_on.cpp"
        with open(filename, "w") as f:
            for name, d in self.callbacks.items():
                on_name = name.replace("On", "on")

                args = []
                bind_args = ["void", self.class_name, on_name]
                for field, type_ in d.items():
                    if type_ == "unsigned int":
                        args.append("int session")
                        bind_args.append("session")
                    elif type_ == "char":
                        args.append("bool last")
                        bind_args.append("last")
                    elif type_ == "int":
                        if field == "errorCode":
                            args.append("int error")
                            bind_args.append("error")
                        else:
                            args.append(f"int {field}")
                            bind_args.append(f"{field}")
                    elif type_ == "string":
                        args.append(f"string {field}")
                        bind_args.append(f"{field}")
                    else:
                        args.append("const dict &data")
                        bind_args.append("data")

                args_str = ", ".join(args)
                bind_args_str = ", ".join(bind_args)

                f.write(f"void {on_name}({args_str}) override\n")
                f.write("{\n")
                f.write("\ttry\n")
                f.write("\t{\n")
                f.write(f"\t\tPYBIND11_OVERLOAD({bind_args_str});\n")
                f.write("\t}\n")
                f.write("\tcatch (const error_already_set &e)\n")
                f.write("\t{\n")
                f.write(f"\t\tcout << e.what() << endl;\n")
                f.write("\t}\n")
                f.write("};\n\n")

    def generate_source_module(self):
        """"""
        filename = f"{self.prefix}_{self.name}_source_module.cpp"
        with open(filename, "w") as f:
            for name in self.functions.keys():
                name = name.replace("Qry", "qry")
                f.write(f".def(\"{name}\", &{self.class_name}::{name})\n")

            f.write("\n")

            for name in self.callbacks.keys():
                name = name.replace("On", "on")
                f.write(f".def(\"{name}\", &{self.class_name}::{name})\n")

            f.write(";\n")


if __name__ == "__main__":
    md_generator = ApiGenerator("../include/tap/TapQuoteAPI.h", "tap", "md", "MdApi")
    md_generator.run()

    td_generator = ApiGenerator("../include/tap/iTapTradeAPI.h", "tap", "td", "TdApi")
    td_generator.run()
