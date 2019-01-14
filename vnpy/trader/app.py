from abc import ABC


class BaseApp(ABC):
    """
    Abstract class for app.
    """
    app_name = ''
    app_engine = None
    app_ui = None
