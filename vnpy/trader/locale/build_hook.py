"""
Hatch build hook that compiles gettext catalogs to mo files.
"""

from pathlib import Path
from typing import BinaryIO, TextIO

from hatchling.builders.hooks.plugin.interface import BuildHookInterface
from babel.messages.mofile import write_mo
from babel.messages.pofile import read_po


class LocaleBuildHook(BuildHookInterface):
    """Custom build hook for generating .mo files."""

    def initialize(self, version: str, build_data: dict) -> None:
        """Initialize the build hook"""
        # Only generate mo file when building wheel
        if "pure_python" not in build_data:
            return

        self.locale_path: Path = Path(self.root).joinpath("vnpy", "trader", "locale")
        self.mo_path: Path = self.locale_path.joinpath("en", "LC_MESSAGES", "vnpy.mo")
        self.po_path: Path = self.locale_path.joinpath("en", "LC_MESSAGES", "vnpy.po")

        mo_f: BinaryIO
        with open(self.mo_path, "wb") as mo_f:
            po_f: TextIO
            with open(self.po_path, encoding="utf-8") as po_f:
                write_mo(mo_f, read_po(po_f))
