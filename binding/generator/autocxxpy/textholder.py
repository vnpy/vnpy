#encoding: utf-8
from typing import Optional, Union


class Indent:
    class IdentStart:

        def __init__(self, text):
            self.text = text

    class IdentEnd:

        def __init__(self, text):
            self.text = text

    class IdentEndLater:

        def __init__(self, text):
            self.text = text

    def __init__(self, text: Optional[Union[str, 'TextHolder']] = None):
        self.text = text

    def __add__(self, other: str):
        assert self.text is None
        return Indent(other)

    def __radd__(self, other: str):
        assert self.text is None
        return Indent.IdentStart(other)

    def __rsub__(self, other: str):
        assert self.text is None
        return Indent.IdentEnd(other)


class IndentLater:

    def __rsub__(self, other: str):
        return Indent.IdentEndLater(other)


class TextHolder:

    def __init__(self, text: Optional[str] = None):
        super().__init__()
        if text is None:
            text = ''
        self.text = text
        self.ident_text = "    "
        self._ident = 0

    def __add__(self, other: Union[str, int]):
        if isinstance(other, Indent.IdentStart):
            self.append(other.text)
            self.ident(1)
        elif isinstance(other, Indent.IdentEnd):
            self.ident(-1)
            self.append(other.text)
        elif isinstance(other, Indent.IdentEndLater):
            self.append(other.text)
            self.ident(-1)
        elif isinstance(other, Indent):
            self.append(
                TextHolder(str(other.text)).ident_all(n=self._ident + 1,
                                                      ident_text=self.ident_text),
                add_ident=False)
        elif isinstance(other, str):
            self.append(other)
        elif isinstance(other, TextHolder):
            self.append(
                TextHolder(str(other.text)).ident_all(n=self._ident, ident_text=self.ident_text),
                add_ident=False)
        elif isinstance(other, int):
            self.ident(other)
        else:
            raise TypeError(f"can only add str or int, but {type(other)} got")
        return self

    def __sub__(self, other):
        if isinstance(other, int):
            self.ident(-other)
        else:
            raise TypeError(f"can only add str or int, but {type(other)} got")
        return self

    def __bool__(self):
        return bool(self.text)

    def __str__(self):
        return self.text

    def append(self, text: Union[str, 'TextHolder'], ensure_new_line=True, ignore_empty=True,
               add_ident=True):
        strtext = str(text)
        if ignore_empty and not strtext:
            return self
        if not strtext.endswith('\n') and ensure_new_line:
            strtext += '\n'
        if add_ident:
            self.text += self._ident * self.ident_text + strtext
        else:
            self.text += strtext
        return self

    def ident_all(self, n: int = 1, ident_text: str = None):
        if ident_text is None:
            ident_text = self.ident_text
        text = self.text
        if text.endswith('\n'):
            text = text[:-1]
        return "\n".join([ident_text * n + i for i in text.split('\n')])

    def ident(self, n: int = 1):
        self._ident += n
        return self
