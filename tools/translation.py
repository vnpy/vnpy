import subprocess
from pathlib import Path
from typing import Iterable

import click

from vnpy.trader.translation import Language, LOCALE_DIR_NAME, TRANSLATION_DOMAIN, LC_NAME
from vnpy.utility.path import vnpy_source_path


@click.group()
def cli():
    pass


@cli.command("compile")
def cli_compile():
    pos = vnpy_source_path.glob("**/vnpy.po")
    for po in pos:
        mo = po.parent.joinpath("vnpy.mo")
        subprocess.run(
            args=["msgfmt",
                  str(po),
                  "-o", str(mo),
                  ]
        )


@cli.command("update")
def cli_update():
    ensure_locale_dir()

    extract_all()
    update_all()


def _ensure_locale_dir(root: Path):
    locale_path = root.joinpath(LOCALE_DIR_NAME)
    if not locale_path.exists():
        locale_path.mkdir()

    for language in Language:
        language_path = locale_path.joinpath(language.value)
        if not language_path.exists():
            language_path.mkdir()
        lc_path = language_path.joinpath(LC_NAME)
        if not lc_path.exists():
            lc_path.mkdir()


def _ensure_sub_locale_dir(path: Path):
    for d in path.glob("*"):
        if d.is_dir():
            _ensure_locale_dir(d)


def ensure_locale_dir():
    _ensure_locale_dir(vnpy_source_path.joinpath("trader"))
    _ensure_sub_locale_dir(vnpy_source_path.joinpath("gateway"))
    _ensure_sub_locale_dir(vnpy_source_path.joinpath("app"))


def extract_all():
    for locale_path in vnpy_source_path.glob(f"**/{LOCALE_DIR_NAME}"):
        root = locale_path.parent
        files = root.glob("**/*.py")
        extract(files, locale_path=locale_path)


def extract(py_files: Iterable[Path], locale_path: Path):
    inputs = [str(i) for i in py_files]
    if inputs:
        return subprocess.run(
            args=["xgettext",
                  "-o", f"{get_pot_path(locale_path)}",
                  "--from-code", "utf-8",
                  # "--omit-header",
                  "-L", "Python",
                  "-k_",
                  "-l", f"{Language.CHINESE.value}",
                  *inputs,
                  ],
        )


def update_all():
    for pot_files in vnpy_source_path.glob(f"**/{LOCALE_DIR_NAME}/{TRANSLATION_DOMAIN}.pot"):
        root: Path = pot_files.parent.parent
        locale_path: Path = root.joinpath(LOCALE_DIR_NAME)
        for language in Language:
            update(locale_path=locale_path, language=language)


def get_pot_path(locale_path: Path):
    return locale_path.joinpath(f'{TRANSLATION_DOMAIN}.pot')


def get_po_path(locale_path: Path, language: Language):
    return locale_path.joinpath(language.value, LC_NAME, f"{TRANSLATION_DOMAIN}.po")


def update(locale_path: Path, language: Language):
    pot_path = get_pot_path(locale_path=locale_path)
    po_path = get_po_path(locale_path=locale_path, language=language)
    if not po_path.exists():
        init(locale_path=locale_path, language=language)
    return subprocess.run(
        args=["msgmerge",
              str(po_path),
              str(pot_path),
              "-o", str(po_path),
              ],
    )


def init(locale_path: Path, language: Language):
    pot_path = get_pot_path(locale_path=locale_path)
    po_path = get_po_path(locale_path=locale_path, language=language)
    return subprocess.run(
        args=["msginit",
              "--no-translator",  # no prompt for email
              "-i", str(pot_path),
              "-o", str(po_path),
              "-l", f"{language.value}",
              ],
    )


if __name__ == '__main__':
    cli()
