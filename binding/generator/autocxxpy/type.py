#encoding: utf-8
import re

base_types = {'char8_t', 'char16_t', 'char32_t', 'wchar_t',
              'char', 'short', 'int', 'long',
              'long long'
              'unsigned char', 'unsigned short', 'unsigned int',
              'unsigned long', 'unsigned long long',
              'float', 'double',
              }


def is_array_type(t: str):
    return '[' in t


def array_base(t: str):
    """
    :raise ValueError if t is not a array type
    """
    return t[:t.index('[') - 1]


def is_pointer_type(t: str):
    return "*" in t


_remove_pointer_re = re.compile("[ \t]*\*[ \t]*")


def pointer_base(t: str):
    return _remove_pointer_re.sub("", t)


def is_reference_type(t: str):
    return "&" in t


def remove_cvref(t: str):
    return t.replace("const ", "").replace("volatile ", "").replace("&", "").strip()
