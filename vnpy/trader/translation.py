import gettext as py_gettext
from enum import Enum

from vnpy.utility.path import vnpy_source_path

LOCALE_DIR_NAME = 'locale'
TRANSLATION_DOMAIN = 'vnpy'
LC_NAME = "LC_MESSAGES"

translation: py_gettext.NullTranslations = py_gettext.NullTranslations()


class Language(Enum):
    CHINESE = 'zh_CN'
    ENGLISH = 'en'


def get_locale_paths():
    return [
        pot.parent
        for pot in vnpy_source_path.glob("**/locale/*.pot")
    ]


def set_language(language: Language):
    translations = [
        py_gettext.translation(TRANSLATION_DOMAIN,
                               localedir=str(locale_path),
                               languages=[language.value],
                               fallback=False,
                               )
        for locale_path in get_locale_paths()
    ]

    # chain all translations
    head_translation = translations[0]
    for t in translations[1:]:
        head_translation.add_fallback(t)

    # fallback to NullTranslations if no translation available
    head_translation.add_fallback(py_gettext.NullTranslations())

    # set global singleton
    global translation
    translation = head_translation

    return head_translation


def gettext(msg):
    return translation.gettext(msg)


_ = gettext  # noqa
