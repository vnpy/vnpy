"""
Script for generating .mo translation files.

Can be run directly as a command-line tool or called by the build system.
"""

import sys
import subprocess
from pathlib import Path


def find_msgfmt_path() -> Path:
    """Attempt to find the msgfmt.py tool path based on current Python executable.

    Returns:
        Path: The path to the msgfmt.py tool
    """
    python_path: Path = Path(sys.executable)
    tools_path: Path = python_path.parent.joinpath("Tools", "i18n", "msgfmt.py")
    return tools_path


def generate_mo_files() -> None:
    """Generate .mo translation files.

    Finds the msgfmt tool and runs it to convert .po files to .mo files.
    Exits with error code 1 if the generation fails.
    """
    print("Generating i18n mo files...")

    # Find the msgfmt tool path
    msgfmt_path: Path = find_msgfmt_path()

    # Get the current script directory
    script_dir: Path = Path(__file__).parent

    # Set input and output paths
    mo_output: Path = script_dir.joinpath("en", "LC_MESSAGES", "vnpy.mo")
    po_input: Path = script_dir.joinpath("en", "LC_MESSAGES", "vnpy")

    # Run command to generate .mo file
    cmd: list[str] = [
        sys.executable,
        str(msgfmt_path),
        "-o",
        str(mo_output),
        str(po_input)
    ]

    result: subprocess.CompletedProcess = subprocess.run(cmd, capture_output=True, text=True)

    if result.returncode == 0:
        print("i18n mo files generated successfully!")
    else:
        print("i18n mo file generation failed!")
        print(f"Error output: {result.stderr}")
        sys.exit(1)


if __name__ == "__main__":
    generate_mo_files()
