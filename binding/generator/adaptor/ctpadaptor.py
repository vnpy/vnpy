import logging
import os

from autocxxpy.cxxparser import CXXParser, CXXParseResult
from autocxxpy.generator import GeneratorOptions
from autocxxpy.preprocessor import PreProcessorResult, PreProcessor

logger = logging.getLogger(__file__)


def clear_dir(path: str):
    for file in os.listdir(path):
        os.unlink(os.path.join(path, file))


class CtpAdaptor:
    def __init__(self, td_header, md_header):
        self.td_header = td_header
        self.md_header = md_header

    def parse(self) -> GeneratorOptions:
        r0: CXXParseResult = CXXParser(
            [self.md_header, self.td_header]
        ).parse()
        r1: PreProcessorResult = PreProcessor(r0).process()

        constants = r0.variables
        constants.update(r1.const_macros)
        constants = {
            k: v for k, v in constants.items() if not k.startswith("_")
        }

        functions = r0.functions
        classes = r1.classes

        # make all api "final" to improve performance
        for c in classes.values():
            type = c.name[-3:]
            if type == "Api":
                for ms in c.functions.values():
                    for m in ms:
                        if m.is_virtual:
                            m.is_pure_virtual = False
                            m.is_final = True
            elif type == "Spi":
                for ms in c.functions.values():
                    for m in ms:
                        m.is_virtual = True
                        # m.is_pure_virtual = True
                        m.is_final = False

        options = GeneratorOptions(
            typedefs=r0.typedefs,
            constants=constants,
            functions=functions,
            classes=classes,
            dict_classes=r1.dict_classes,
            enums=r0.enums,
        )
        options.includes = ["custom_wrappers/spi.hpp"]
        return options
