import sys
import subprocess
from pathlib import Path
from setuptools import setup


# Generate i18n mo files
python_path: Path = Path(sys.executable)
msgfmt_path: Path = python_path.parent.joinpath("Tools", "i18n", "msgfmt.py")

generate_mo_cmd = [
    str(python_path),
    str(msgfmt_path),
    "-o",
    ".\\vnpy\\trader\\locale\\en\\LC_MESSAGES\\vnpy.mo",
    ".\\vnpy\\trader\\locale\\en\\LC_MESSAGES\\vnpy"
]

subprocess.run(generate_mo_cmd)


# Run setup
setup()
