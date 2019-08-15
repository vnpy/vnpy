import gettext as py_gettext
from enum import Enum
from pathlib import Path

from vnpy.utility.path import vnpy_source_path

translation_domain = 'vnpy'
locale_dir_name = 'locale'

translation = None


class Language(Enum):
    CHINESE = 'zh_Hans_CN'
    ENGLISH = 'en'


def _get_translation(directory: Path, languages):
    gateway_locale_root = directory.joinpath("locale").name
    trader_translation = py_gettext.translation(
        translation_domain,
        localedir=gateway_locale_root,
        languages=languages,
        fallback=False,
    )
    return trader_translation


def set_language(lang: Language):
    languages = [lang.value]

    # read translations from */locale
    translations = [
        py_gettext.translation(translation_domain,
                               localedir=d,
                               languages=languages,
                               fallback=False,
                               )
        for d in vnpy_source_path.glob(f"**/{locale_dir_name}")
    ]

    # chain all translations
    assert len(translations) > 0
    head_translation = translations[0]
    for t in translations[1:]:
        head_translation.add_fallback(t)

    # fallback to NullTranslations if no translations present
    head_translation.add_fallback(py_gettext.NullTranslations)

    # assign singleton
    global translation
    translation = head_translation

    return head_translation


def gettext(message):
    return translation.gettext(message)


_ = gettext  # noqa
