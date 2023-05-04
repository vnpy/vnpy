__version__ = "2023.05.05"
WORK_DIR = '.wc-vntrader'

def set_work_dir(dir_name):
    global WORK_DIR
    if dir_name:
        WORK_DIR = dir_name
