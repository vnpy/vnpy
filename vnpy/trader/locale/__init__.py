import gettext
from pathlib import Path


localedir: Path = Path(__file__).parent

# Cache for translation objects
_translation_cache: dict[str, gettext.GNUTranslations | gettext.NullTranslations] = {}
_current_language: str | None = None

def get_translation() -> gettext.GNUTranslations | gettext.NullTranslations:
    """Get translation object, loading it lazily."""
    global _current_language
    
    # Load language setting at runtime
    try:
        from ..setting import SETTINGS
        language: str = SETTINGS.get("language", "zh_CN")
    except ImportError:
        language: str = "zh_CN"
    
    # Return cached translation if language hasn't changed
    if language == _current_language and language in _translation_cache:
        return _translation_cache[language]
    
    # Initialize translations based on language setting
    if language == "en_US":
        # Load English translations
        translation = gettext.translation(
            "vnpy", 
            localedir=localedir, 
            languages=["en"],
            fallback=True
        )
    else:
        # Use Chinese (default)
        translation = gettext.NullTranslations()
    
    # Cache the translation
    _translation_cache[language] = translation
    _current_language = language
    
    return translation

class LazyTranslation:
    """Lazy translation callable."""
    def __call__(self, message: str) -> str:
        return get_translation().gettext(message)

_ = LazyTranslation()
