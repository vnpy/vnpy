import logging
from collections import defaultdict
from dataclasses import dataclass, field
from typing import Any, Dict, List, Optional, Sequence

from .clang.cindex import (
    Config,
    Cursor,
    CursorKind,
    Index,
    Token,
    TranslationUnit,
)

logger = logging.getLogger(__file__)
logging.basicConfig(level=logging.INFO)


@dataclass
class Variable:
    name: str
    type: str
    parent: Any = None
    constant: bool = False
    static: bool = False
    default: Any = None


@dataclass
class LiteralVariable(Variable):
    literal: str = None
    literal_valid: bool = True


@dataclass
class Enum:
    name: str
    type: str
    parent: "Namespace" = None
    values: Dict[str, Variable] = field(default_factory=dict)
    is_strong_typed: bool = False

    @property
    def full_name(self):
        if self.parent is None:
            # return "::" + self.name
            return self.name
        return self.parent.full_name + "::" + self.name

    def full_name_of(self, v: Variable):
        return self.full_name + "::" + v.name


@dataclass
class Function:
    name: str
    ret_type: str
    parent: "Namespace" = None
    args: List[Variable] = field(default_factory=list)
    calling_convention: str = "__cdecl"

    @property
    def type(self, show_calling_convention: bool = False):
        args = ",".join([i.type for i in self.args])
        calling = (
            self.calling_convention + " " if show_calling_convention else ""
        )
        return f"{self.ret_type}({calling} *)({args})"

    @property
    def full_name(self):
        return f"::{self.name}"

    @property
    def full_signature(self):
        s = f"{self.name} ("
        for arg in self.args:
            s += arg.type + " " + arg.name + ","
        s = s[:-2] + ")"
        return s

    def __str__(self):
        return self.full_signature


@dataclass
class Namespace:
    name: str = ""
    parent: "Namespace" = None
    enums: Dict[str, Enum] = field(default_factory=dict)
    typedefs: Dict[str, str] = field(default_factory=dict)
    classes: Dict[str, "Class"] = field(default_factory=dict)
    variables: Dict[str, Variable] = field(default_factory=dict)
    functions: Dict[str, List[Function]] = field(
        default_factory=(lambda: defaultdict(list))
    )

    @property
    def full_name(self):
        if self.parent is None:
            return self.name
        return self.parent.full_name + "::" + self.name


@dataclass
class Class(Namespace):
    functions: Dict[str, List["Method"]] = field(
        default_factory=(lambda: defaultdict(list))
    )
    constructors: List["Method"] = field(default_factory=list)
    destructor: "Method" = None

    is_polymorphic: bool = False

    def __str__(self):
        return "class " + self.name

    # without this, PyCharm will crash
    def __repr__(self):
        return "class" + self.name


@dataclass
class Method(Function):
    name: str
    ret_type: str
    parent: Class = None
    access: str = "public"
    is_virtual: bool = False
    is_pure_virtual: bool = False
    is_static: bool = False
    is_final: bool = False

    @property
    def type(self, show_calling_convention: bool = False):
        args = ",".join([i.type for i in self.args])
        calling = (
            self.calling_convention + " " if show_calling_convention else ""
        )
        parent_prefix = ""
        if not self.is_static:
            parent_prefix = f"{self.parent.full_name}::"
        return f"{self.ret_type}({calling}{parent_prefix}*)({args})"

    @property
    def full_name(self):
        return f"{self.parent.name}::{self.name}"

    @property
    def full_signature(self):
        return (
            "{} {}{} {}::".format(
                self.access,
                "virtual" if self.is_virtual else "",
                "static" if self.is_static else "",
                self.parent.name,
            )
            + super().full_signature
            + (" = 0" if self.is_pure_virtual else "")
        )

    def __str__(self):
        return self.full_signature


@dataclass()
class CXXParseResult(Namespace):
    macros: Dict[str, str] = field(default_factory=dict)


class CXXParser:
    def __init__(
        self,
        file_path: Optional[str],
        unsaved_files: Sequence[Sequence[str]] = None,
        args: List[str] = None,
    ):
        if args is None:
            args = []
        self.unsaved_files = unsaved_files
        self.file_path = file_path
        self.args = args
        if "-std=c++11" not in self.args:
            self.args.append("-std=c++11")

    def parse(self) -> CXXParseResult:
        idx = Index.create()
        rs = idx.parse(
            self.file_path,
            args=self.args,
            unsaved_files=self.unsaved_files,
            options=(
                TranslationUnit.PARSE_DETAILED_PROCESSING_RECORD
                | TranslationUnit.PARSE_SKIP_FUNCTION_BODIES
                | TranslationUnit.PARSE_INCLUDE_BRIEF_COMMENTS_IN_CODE_COMPLETION
            ),
        )
        result = CXXParseResult()
        # todo: parse namespace
        for c in rs.cursor.walk_preorder():
            if c.kind == CursorKind.FUNCTION_DECL:
                func = CXXParser._process_function(c)
                result.functions[func.name] = func
            elif c.kind == CursorKind.ENUM_DECL:
                e = CXXParser._process_enum(c)
                result.enums[e.name] = e
            elif (
                c.kind == CursorKind.CLASS_DECL
                or c.kind == CursorKind.STRUCT_DECL
            ):
                class_ = CXXParser._process_class(c)
                cname = class_.name
                result.classes[cname] = class_
            elif c.kind == CursorKind.VAR_DECL:
                name, value = CXXParser._process_variable(c)
                if value:
                    result.variables[name] = value
            elif c.kind == CursorKind.TYPEDEF_DECL:
                name, target = CXXParser._process_typedef(c)
                result.typedefs[name] = target
            elif c.kind == CursorKind.MACRO_DEFINITION:
                name, definition = CXXParser._process_macro_definition(c)
                result.macros[name] = definition
            elif (
                False
                or c.kind == CursorKind.ENUM_CONSTANT_DECL
                or c.kind == CursorKind.CXX_METHOD
                or c.kind == CursorKind.CXX_FINAL_ATTR
                or c.kind == CursorKind.DESTRUCTOR
                or c.kind == CursorKind.PARM_DECL
                or c.kind == CursorKind.CXX_ACCESS_SPEC_DECL
                or c.kind == CursorKind.FIELD_DECL
            ):
                pass
            elif c.kind == CursorKind.COMPOUND_STMT:
                # ignore any body
                pass
            elif (
                CXXParser._is_literal_cursor(c)
                or c.kind == CursorKind.MACRO_INSTANTIATION
                or c.kind == CursorKind.INCLUSION_DIRECTIVE
            ):
                # just not need to process
                pass
            elif (
                c.kind == CursorKind.TYPE_REF
                or c.kind == CursorKind.UNEXPOSED_EXPR
                or c.kind == CursorKind.TRANSLATION_UNIT
            ):
                # i don't know what those are
                pass
            else:
                logging.warning(
                    "unrecognized cursor kind: %s, %s, %s",
                    c.kind,
                    c.spelling,
                    c.extent,
                )
        return result

    @staticmethod
    def _process_function(c: Cursor):
        func = Function(
            name=c.displayname,
            ret_type=c.result_type.spelling,
            args=[
                Variable(name=ac.displayname, type=ac.type.spelling)
                for ac in c.get_children()
            ],
        )
        return func

    @staticmethod
    def _process_method(c: Cursor, class_):
        func = Method(
            parent=class_,
            name=c.spelling,
            ret_type=c.result_type.spelling,
            access=c.access_specifier.name.lower(),
            is_virtual=c.is_virtual_method(),
            is_pure_virtual=c.is_pure_virtual_method(),
            is_static=c.is_static_method(),
        )
        for ac in c.get_children():
            if ac.kind == CursorKind.PARM_DECL:
                arg = Variable(ac.displayname, ac.type.spelling)
                func.args.append(arg)
            elif ac.kind == CursorKind.CXX_FINAL_ATTR:
                func.is_final = True
            elif ac.kind == CursorKind.COMPOUND_STMT:
                # we don't care about the function body
                pass
            elif ac.kind == CursorKind.TYPE_REF:
                # I don't what this is, maybe a mistake of clang?
                pass
            else:
                logger.warning(
                    "unknown kind in cxx_method child: %s %s",
                    ac.kind,
                    ac.extent,
                )
        return func

    @staticmethod
    def _process_class(c: Cursor):
        # noinspection PyArgumentList
        class_ = Class(name=c.displayname)
        for ac in c.get_children():
            if ac.kind == CursorKind.CONSTRUCTOR:
                func = CXXParser._process_method(ac, class_)
                if func.is_virtual:
                    class_.is_polymorphic = True
                class_.constructors = func
            elif ac.kind == CursorKind.DESTRUCTOR:
                func = CXXParser._process_method(ac, class_)
                if func.is_virtual:
                    class_.is_polymorphic = True
                class_.destructor = func
            elif ac.kind == CursorKind.FIELD_DECL:
                v = Variable(ac.spelling, ac.type.spelling)
                class_.variables[v.name] = v
            elif ac.kind == CursorKind.CXX_METHOD:
                func = CXXParser._process_method(ac, class_)
                if func.is_virtual:
                    class_.is_polymorphic = True
                class_.functions[func.name].append(func)
            elif ac.kind == CursorKind.CXX_ACCESS_SPEC_DECL:
                pass
            else:
                logger.warning(
                    "unknown kind in class child, and not handled: %s %s",
                    ac.kind,
                    ac.extent,
                )
        return class_

    @staticmethod
    def _process_enum(c: Cursor):
        e = Enum(name=c.spelling, type=c.enum_type.spelling)
        for i in list(c.get_children()):
            e.values[i.spelling] = Variable(
                name=i.spelling, type=e.name, default=i.enum_value
            )
        return e

    @staticmethod
    def _process_variable(c: Cursor):
        children = list(c.get_children())
        length = len(children)
        if length == 1:
            child = children[0]
            if CXXParser._is_literal_cursor(child):
                value = CXXParser._process_literal(child)
                return c.spelling, value
        logger.warning(
            "unable to process variable : %s %s", c.spelling, c.extent
        )
        return c.spelling, None

    @staticmethod
    def _process_typedef(c: Cursor):
        return c.spelling, c.underlying_typedef_type.spelling

    @staticmethod
    def _process_macro_definition(c: Cursor):
        name = c.spelling
        tokens = list(c.get_tokens())
        length = len(tokens)
        if length == 1:
            return name, ""
        return name, " ".join([i.spelling for i in tokens[1:]])

    @staticmethod
    def _get_source_from_file(file, start, end, encoding="utf-8"):
        with open(file, "rb") as f:
            f.seek(start)
            return f.read(end - start).decode(encoding=encoding)

    @staticmethod
    def _get_source(token: Token, encoding="utf-8"):
        return CXXParser._get_source_from_file(
            token.location.file.name,
            token.extent.start.offset,
            token.extent.end.offset,
            encoding,
        )

    LITERAL_KINDS = {
        CursorKind.INTEGER_LITERAL,
        CursorKind.STRING_LITERAL,
        CursorKind.CHARACTER_LITERAL,
        CursorKind.CXX_NULL_PTR_LITERAL_EXPR,
        CursorKind.FLOATING_LITERAL,
        CursorKind.IMAGINARY_LITERAL,
        CursorKind.CXX_BOOL_LITERAL_EXPR,
        # CursorKind.OBJC_STRING_LITERAL,
        # CursorKind.OBJ_BOOL_LITERAL_EXPR,
        # CursorKind.COMPOUND_LITERAL_EXPR,
    }

    @staticmethod
    def _is_literal_cursor(c: Cursor):
        return c.kind in CXXParser.LITERAL_KINDS
        # return str(c)[-9:-1] == 'LITERAL'

    @staticmethod
    def _process_literal(c):
        tokens = list(c.get_tokens())
        if len(tokens) == 1:
            spelling = tokens[0].spelling
            if c.kind == CursorKind.INTEGER_LITERAL:
                return int(spelling)
            elif c.kind == CursorKind.STRING_LITERAL:
                return str(spelling)
            elif c.kind == CursorKind.CHARACTER_LITERAL:
                return CXXParser.character_literal_to_int(spelling)
            elif c.kind == CursorKind.FLOATING_LITERAL:
                return float(spelling)
        logger.warning(
            "unknown literal : %s, %s %s", c.kind, c.spelling, c.extent
        )
        return None

    @staticmethod
    def character_literal_to_int(string):
        s = 0
        for i in string.encode():
            s = s * 255 + i
        return s

    pass


class CXXFileParser(CXXParser):
    def __init__(
        self,
        files: Sequence[str],
        include_paths: Sequence[str] = None,
        args: List[str] = None,
    ):
        if args is None:
            args = []
        if include_paths:
            for include_path in include_paths:
                args.append("-I" + include_path)
        dummy_code = ""
        for file in files:
            dummy_code += f'#include "{file}"\n'

        dummy_name = "dummy.cpp"
        super().__init__(
            dummy_name, unsaved_files=[[dummy_name, dummy_code]], args=args
        )


Config.set_library_path("")
