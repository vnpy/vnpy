import importlib
import os
from pathlib import Path
from typing import Dict, Type, List

from .template import CtaTemplate

VNPY_SOURCE_ROOT = Path(__file__).parents[2]


class StrategyLoadFailure:
    def __init__(self, module_name: str, exception: Exception):
        self.module_name = module_name
        self.exception = exception


class StrategyLoader:
    def __init__(self):
        self.classes: Dict[str, Type[CtaTemplate]] = {}
        self.failures: List[StrategyLoadFailure] = []

    def _clear(self):
        self.classes.clear()
        self.failures.clear()

    def load_all(self):
        """
        Load strategy class from source code.
        Loaded class is stored into self.classes
        if load failed, detail is stored into self.failures.
        """
        self._clear()

        path1 = VNPY_SOURCE_ROOT.joinpath("app", "cta_strategy", "strategies")
        self.load_strategy_class_from_folder(
            path1, "vnpy.app.cta_strategy.strategies")

        path2 = Path.cwd().joinpath("strategies")
        self.load_strategy_class_from_folder(path2, "strategies")

    def load_strategy_class_from_folder(self, path: Path, module_name: str = ""):
        """
        Load strategy class from certain folder.
        if load failed, detail is stored into self.failures.
        """
        for dirpath, dirnames, filenames in os.walk(str(path)):
            for filename in filenames:
                if filename.endswith(".py"):
                    strategy_module_name = ".".join(
                        [module_name, filename.replace(".py", "")])
                elif filename.endswith(".pyd"):
                    strategy_module_name = ".".join(
                        [module_name, filename.split(".")[0]])
                else:
                    continue
                self.load_strategy_class_from_module(strategy_module_name)

    def load_strategy_class_from_module(self, module_name: str):
        """
        Load strategy class from module file.
        if load failed, detail is stored into self.failures.
        """
        try:
            module = importlib.import_module(module_name)

            for name in dir(module):
                value = getattr(module, name)
                if (isinstance(value, type)
                    and issubclass(value, CtaTemplate)
                    and value is not CtaTemplate
                ):
                    self.classes[value.__name__] = value
        except Exception as e:
            self.failures.append(StrategyLoadFailure(module_name=module_name, exception=e))
