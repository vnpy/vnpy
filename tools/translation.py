import subprocess
from pathlib import Path

import click
from vnpy.utility.path import vnpy_source_path

from vnpy.trader.translation import Language, locale_dir_name, translation_domain


@click.group()
def cli():
    pass


@cli.command("compile")
def cli_compile():
    pass


@cli.command("update")
def cli_update():
    ensure_locale_dir()
    # extract_all()


def _ensure_locale_dir(path: Path):
    locale_path = path.joinpath(locale_dir_name)
    if not locale_path.exists():
        locale_path.mkdir()
    for language in Language:
        language_path = locale_path.joinpath(language.value)
        if not language_path.exists():
            language_path.mkdir()

        po_file = language_path.joinpath(f'{translation_domain}.po')
        if not po_file.exists():
            init(locale_path, language_path)


def _ensure_sub_locale_dir(path: Path):
    for d in path.glob("*"):
        if d.is_dir():
            _ensure_locale_dir(d)


def ensure_locale_dir():
    _ensure_locale_dir(vnpy_source_path.joinpath("trader"))
    _ensure_sub_locale_dir(vnpy_source_path.joinpath("gateway"))
    _ensure_sub_locale_dir(vnpy_source_path.joinpath("app"))


def extract_all():
    for locale_path in vnpy_source_path.glob(f"**/{locale_dir_name}"):
        path = locale_path.parent
        files = path.glob("**/*.py")
        for file in files:
            extract(file, locale_dir=locale_path.name)


def extract(file: str, locale_dir: str):
    return subprocess.run(
        args=["xgettext",
              "--from-code", "utf-8",
              "-L", "Python",
              "-o", "message.pot",
              "-k_",
              file,
              ],
        cwd=locale_dir,
    )


def update_all():
    for locale_path in vnpy_source_path.glob(f"**/{locale_dir_name}"):
        path = locale_path.parent
        files = path.glob("**/*.py")
        for file in files:
            update(file, locale_dir=locale_path.name)


def update(file: str, locale_dir: str, language: Language):
    return subprocess.run(
        args=["msgmerge",
              "--from-code", "utf-8",
              "-L", "Python",
              "-o", "message.pot",
              "-k_",
              file],
        cwd=locale_dir,
    )


def init(locale_path: Path, language_path: Path):
    cwd = str(locale_path)
    output = str(locale_path.joinpath(language_path, f"{translation_domain}.po"))
    return subprocess.run(
        args=["msginit",
              "-i", f"{translation_domain}.pot",
              "-o", output
              ],
        cwd=cwd,
    )


if __name__ == '__main__':
    cli()
