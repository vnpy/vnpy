import gettext
from pathlib import Path

localedir = Path(__file__).parent
translations = gettext.translation('vnpy', localedir=localedir, fallback=True)

_ = translations.gettext
