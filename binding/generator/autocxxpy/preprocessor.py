#encoding: utf-8

import ast
import re
from collections import defaultdict
from dataclasses import dataclass, field
from enum import Enum
from typing import Dict, List, Optional, Set

from .cxxparser import CXXParser, CXXParseResult, Class, LiteralVariable, Method, Variable
from .type import array_base, base_types, is_array_type


class CallbackType(Enum):
    NotCallback = 0  # not a callback
    Direct = 1
    Async = 2


"""
42          - dec
0b101010    - bin
052         - oct
0xaa        - hex
0Xaa        - hex
1234u       - suffix
1234ull     - suffix
145'920     - with single quotes
1.0         - double
1.0f        - float

ignore:
5.9604644775390625e-8F16
'123123'

unsuportted:
1e10        - science
1E10        - science
1e+10
1e-10
1E-10
1E+10

"""
cpp_digit_re = re.compile(
    "(0b[01]+|0[0-7]+|0[Xx][0-9a-fA-F]+|[0-9']*[0-9]+)((ull)|(ULL)|(llu)|(LLU)|(ul)|(UL)|(ll)|(LL)|[UuLl])?$")

cpp_digit_suffix_types = {
    'u': 'unsigned int',
    'l': 'long',
    'ul': 'usngined long',
    'll': 'long long',
    'ull': 'unsigned long long',
    'llu': 'unsigned long long',
    'f': 'float'
}
cpp_digit_suffix_types.update({k.upper(): v for k, v in cpp_digit_suffix_types.items()})


@dataclass
class PreprocessedMethod(Method):
    has_overload: bool = False


@dataclass
class PreprocessedClass(Class):
    functions: Dict[str, List[PreprocessedMethod]] = field(
        default_factory=(lambda: defaultdict(list)))
    need_wrap: bool = False  # if need_wrap is true, wrap this to dict
    is_pure_virtual: bool = False  # generator will not assign python constructor for pure virtual


class PreProcessorResult:

    def __init__(self):
        super().__init__()
        self.dict_classes: Set[str] = set()
        self.const_macros: Dict[str, Variable] = {}
        self.classes: Dict[str, PreprocessedClass] = {}


class PreProcessor:

    def __init__(self, parse_result: CXXParseResult):
        self.parser_result = parse_result

    def process(self)->PreProcessorResult:
        result = PreProcessorResult()

        # all pod struct to dict
        # todo: generator doesn't support dict class currently
        # result.dict_classes = self._find_dict_classes()

        # all error written macros to constant
        result.const_macros = self._pre_process_constant_macros()

        result.classes = self._pre_process_classes(result.dict_classes)
        return result

    def _pre_process_classes(self, dict_classes: Set[str]):
        classes: Dict[str, PreprocessedClass] = {}
        for c in self.parser_result.classes.values():
            gc = PreprocessedClass(**c.__dict__)
            gc.functions = {
                name: [PreprocessedMethod(**m.__dict__) for m in ms]
                for name, ms in gc.functions.items()
            }
            if c.is_polymorphic:
                gc.need_wrap = True
            classes[gc.name] = gc
        for c in classes.values():
            for ms in c.functions.values():

                # check overload
                if len(ms) >= 2:
                    for m in ms:
                        m.has_overload = True

                # check pure virtual
                for m in ms:
                    if m.is_pure_virtual:
                        c.is_pure_virtual = True

        return classes

    def _pre_process_constant_macros(self):
        macros = {}
        for name, definition in self.parser_result.macros.items():
            value = PreProcessor._try_convert_to_constant(definition)
            if value is not None:
                value.name = name
                macros[name] = value
        return macros

    def _find_dict_classes(self):
        dict_classes = set()
        for c in self.parser_result.classes.values():
            if self._can_convert_to_dict(c):
                dict_classes.add(c.name)
        return dict_classes

    def _to_basic_type_combination(self, t: str):
        try:
            return self._to_basic_type_combination(self.parser_result.typedefs[t])
        except KeyError:
            return t

    def _is_basic_type(self, t: str):
        basic_combination = self._to_basic_type_combination(t)

        # just a basic type, such as int, char, short, double etc.
        if basic_combination in base_types:
            return True

        # array of basic type, such as int[], char[]
        if is_array_type(basic_combination) \
                and array_base(basic_combination) in base_types:
            return True

        print(basic_combination)
        return False

    def _can_convert_to_dict(self, c: Class):
        # first: no functions
        if c.functions:
            return False

        # second: all variables are basic
        for v in c.variables.values():
            if not self._is_basic_type(v.type):
                return False

        return True

    @staticmethod
    def _try_parse_cpp_digit_literal(literal: str):
        m = cpp_digit_re.match(literal)
        if m:
            digit = m.group(1)
            suffix = m.group(2)
            val = ast.literal_eval(digit.replace("'", ""))
            t = 'int'
            if suffix:
                t = cpp_digit_suffix_types[suffix]
            return LiteralVariable(name='', type=t, default=val, literal=literal)
        return None

    @staticmethod
    def _try_convert_to_constant(definition: str) -> Optional[Variable]:
        definition = definition.strip()
        try:
            if definition:
                var = PreProcessor._try_parse_cpp_digit_literal(definition)
                if var:
                    return var
                val = None
                if definition.startswith('"') and definition.endswith('"'):
                    val = ast.literal_eval(definition)
                    return LiteralVariable(name='',
                                           type='const char *',
                                           default=val,
                                           literal=definition)
                if definition.startswith("'") and definition.endswith("'"):
                    val = CXXParser.character_literal_to_int(definition[1:-1])
                    t = 'unsigned'
                    valid = True
                    if len(definition) >= 6:
                        t = 'unsigned long long'
                        valid = False
                    return LiteralVariable(name='',
                                           type='int',
                                           default=val,
                                           literal=definition,
                                           literal_valid=valid)
        except SyntaxError:
            pass
        return None
