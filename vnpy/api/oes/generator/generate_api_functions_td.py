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
        self.subs = {}
        self.final = {}
        self.final_structs = {}

        self.structs = {}

    def load_struct_todo(self):
        """加载Struct"""
        self.load_base_model()
        self.load_packets()
        self.load_qry_packets()

    def load_packets(self):
        """"""
        module_name = "oes_struct_packets_td"
        module = importlib.import_module(module_name)

        for name in dir(module):
            if "__" not in name:
                self.final_structs[name] = getattr(module, name)

    def load_qry_packets(self):
        """"""
        module_name = "oes_struct_qry_packets_td"
        module = importlib.import_module(module_name)

        for name in dir(module):
            if "__" not in name:
                self.structs[name] = getattr(module, name)

        module_name_ = "oes_substruct_base_model_td"
        module_ = importlib.import_module(module_name_)

        for name_ in dir(module_):
            self.subs[name_] = getattr(module_, name_)

        for struct_name, fields in self.structs.items():
            if not fields:
                continue

            d = {}

            for name, type_ in fields.items():
                if type_ != "dict":
                    d[name] = type_
                else:
                    value = self.subs[name]
                    d.update(value)

            self.final[struct_name] = d

        for struct_name, fields in self.final.items():
            if not fields:
                continue

            d = {}

            for name, type_ in fields.items():
                if type_ != "dict":
                    d[name] = type_
                else:
                    value = self.subs[name]
                    d.update(value)

            self.final_structs[struct_name] = d

    def load_base_model(self):
        """"""
        module_name = "oes_struct_base_model_td"
        module = importlib.import_module(module_name)

        for name in dir(module):
            if "__" not in name:
                self.structs[name] = getattr(module, name)

        module_name_ = "oes_substruct_base_model_td"
        module_ = importlib.import_module(module_name_)

        for name_ in dir(module_):
            self.subs[name_] = getattr(module_, name_)
        # 1 times
        for struct_name, fields in self.structs.items():
            if not fields:
                continue

            d = {}

            for name, type_ in fields.items():
                if type_ != "dict":
                    d[name] = type_
                else:
                    value = self.subs[name]
                    d.update(value)

            self.final[struct_name] = d
        # 2 times
        for struct_name, fields in self.final.items():
            if not fields:
                continue

            d = {}

            for name, type_ in fields.items():
                if type_ != "dict":
                    d[name] = type_
                else:
                    value = self.subs[name]
                    d.update(value)

            self.final_structs[struct_name] = d

    def run(self):
        """运行生成"""
        self.load_struct_todo()
        self.f_cpp = open(self.filename, "r", encoding="UTF-8")

        for line in self.f_cpp:
            self.process_line(line)

        self.f_cpp.close()
        # print(self.functions, "\n")
        # print(self.callbacks, "\n")

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

        print("API生成成功")

    def process_line(self, line: str):
        """处理每行"""
        line = line.replace(";", "")
        line = line.replace("\n", "")
        line = line.replace("\t", "")
        line = line.replace("{}", "")

        if "virtual void        On" in line or "virtual int32       On" in line:
            self.process_callback(line)
        elif "int32               Query" in line:
            self.process_function(line)

    def process_callback(self, line: str):
        """处理回掉函数"""
        name = line[line.index("On"):line.index("(")]
        self.lines[name] = line

        d = self.generate_arg_dict(line)
        self.callbacks[name] = d

    def process_function(self, line: str):
        """处理主动函数"""
        name = line[line.index("Query"):line.index("(")]

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
            arg = arg.replace("const", "")
            words = arg.split(" ")
            words = [word for word in words if word]
            d[words[1].replace("*", "")] = words[0]
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
            for name, d in self.callbacks.items():
                name = name.replace("On", "on")

                args_list = []
                for type_ in d.values():
                    if type_ == "int32":
                        args_list.append("int reqid")
                    elif type_ == "OesRptMsgHeadT" or type_ == "OesQryCursorT":
                        args_list.append("const dict &error")
                    else:
                        args_list.append("const dict &data")

                args_str = ", ".join(args_list)
                line = f"virtual void {name}({args_str}) {{}};\n\n"

                f.write(line)

    def generate_header_function(self):
        """"""
        filename = f"{self.prefix}_{self.name}_header_function.h"
        with open(filename, "w") as f:
            for name in self.functions.keys():
                name = name.replace("Query", "query")
                line = f"int {name}(const dict &req, int reqid);\n\n"
                f.write(line)

    def generate_source_task(self):
        """"""
        filename = f"{self.prefix}_{self.name}_source_task.cpp"
        with open(filename, "w") as f:
            for name, d in self.callbacks.items():
                line = self.lines[name]

                f.write(line.replace("virtual void        ",
                                     f"void {self.class_name}::") + "\n")
                f.write("{\n")
                f.write("\tTask task = Task();\n")
                f.write(f"\ttask.task_name = {name.upper()};\n")

                for field, type_ in d.items():
                    if type_ == "int32":
                        f.write(f"\ttask.task_id = {field};\n")
                    elif type_ == "OesRptMsgHeadT" or type_ == "OesQryCursorT":
                        f.write(f"\tif ({field})\n")
                        f.write("\t{\n")
                        f.write(f"\t\t{type_} *task_error = new {type_}();\n")
                        f.write(f"\t\t*task_error = *{field};\n")
                        f.write(f"\t\ttask.task_error = task_error;\n")
                        f.write("\t}\n")
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
                f.write("\tgil_scoped_acquire acquire;\n")

                args = []

                for field, type_ in d.items():
                    if type_ == "int32":
                        args.append("task->task_id")
                    elif type_ == "OesRptMsgHeadT" or type_ == "OesQryCursorT":
                        args.append("error")

                        f.write("\tdict error;\n")
                        f.write("\tif (task->task_error)\n")
                        f.write("\t{\n")
                        f.write(
                            f"\t\t{type_} *task_error = ({type_}*)task->task_error;\n")

                        struct_fields = self.final_structs[type_]
                        for struct_field, struct_type in struct_fields.items():
                            if struct_type == "string":
                                f.write(
                                    f"\t\terror[\"{struct_field}\"] = toUtf(task_error->{struct_field});\n")
                            else:
                                f.write(
                                    f"\t\terror[\"{struct_field}\"] = task_error->{struct_field};\n")

                        f.write("\t\tdelete task_error;\n")
                        f.write("\t}\n")
                    else:
                        args.append("data")

                        f.write("\tdict data;\n")
                        f.write("\tif (task->task_data)\n")
                        f.write("\t{\n")
                        f.write(
                            f"\t\t{type_} *task_data = ({type_}*)task->task_data;\n")

                        if type_ not in [
                            "OesMarketStateItemT", "OesTrdItemT", "OesLotWinningItemT",
                            "OesOrdItemT", "OesCustItemT", "OesFundTransferSerialItemT",
                            "OesIssueItemT", "OesStockItemT", "OesOptExerciseAssignItemT",
                            "OesEtfItemT", "OesOptionItemT", "OesOptUnderlyingHoldingItemT",
                            "OesNotifyInfoItemT", "eOesApiChannelTypeT", "OesApiSessionInfoT",
                            "pSubscribeInfo", "OesApiSubscribeInfoT"
                        ]:
                            struct_fields = self.final_structs[type_]
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
                req_name = name.replace("Query", "query")
                type_ = list(d.values())[0]

                f.write(
                    f"int {self.class_name}::{req_name}(const dict &req, int reqid)\n")
                f.write("{\n")
                f.write(f"\t{type_} myreq = {type_}();\n")
                f.write("\tmemset(&myreq, 0, sizeof(myreq));\n")

                struct_fields = self.final_structs.get(type_, None)
                if not struct_fields:
                    line = f"\tgetString(req, \"{type_}\", myreq.{type_});\n"
                    f.write(line)
                else:

                    for struct_field, struct_type in struct_fields.items():
                        if struct_type == "string":
                            line = f"\tgetString(req, \"{struct_field}\", myreq.{struct_field});\n"
                        else:
                            line = f"\tget{struct_type.capitalize()}(req, \"{struct_field}\", &myreq.{struct_field});\n"
                        f.write(line)

                f.write(f"\tint i = this->api->{name}(&myreq, reqid);\n")
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
                    if type_ == "int32":
                        args.append("int reqid")
                        bind_args.append("reqid")
                    elif type_ == "OesRptMsgHeadT" or type_ == "OesQryCursorT":
                        args.append("const dict &error")
                        bind_args.append("error")
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
                name = name.replace("Query", "query")
                f.write(f".def(\"{name}\", &{self.class_name}::{name})\n")

            f.write("\n")

            for name in self.callbacks.keys():
                name = name.replace("On", "on")
                f.write(f".def(\"{name}\", &{self.class_name}::{name})\n")

            f.write(";\n")


if __name__ == "__main__":
    td_generator = ApiGenerator("../include_for_generator/oes/oes_client_sample.h", "oes", "td", "TdApi")
    td_generator.run()
