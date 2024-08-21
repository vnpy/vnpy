from pathlib import Path
import gettext

localedir = Path(__file__).parent
translations = gettext.translation('vnpy_portfoliostrategy', localedir=localedir, fallback=True)

_ = translations.gettext
