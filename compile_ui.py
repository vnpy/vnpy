import subprocess
from argparse import ArgumentParser

import os
import logging


def is_ui_file(path):
    return os.path.splitext(path)[1] == '.ui'


def is_py_file(path):
    return os.path.splitext(path)[1] == '.py'


def seek_files(root, comp):  # type(str)->list[str]
    results = []
    for root, dirs, files in os.walk(root, followlinks=True):
        for filename in files:
            try:
                path = os.path.join(root, filename)
                if comp(path):
                    results.append(path)
            except:  # noqa
                pass
    return results


class UICompiler(object):

    def __init__(self, root, uic_bin_path, lupdate_bin_path, ts_output,
                 strip_ui_prefix,
                 ):  # type: (str, str, str, str, bool)->UICompiler
        self.root = root
        self.lupdate_bin_path = lupdate_bin_path
        self.uic_bin_path = uic_bin_path
        self.ts_output = ts_output
        self.strip_ui_prefix = strip_ui_prefix

        self.ui_files = []

    def collect_ui(self, path):  # type(str)->None
        self.ui_files.append(path)

    def compile_ui(self, path, out_path):  # type: (str, any)->int
        if out_path is None:
            dir, filename = os.path.split(path)
            basename, ext = os.path.splitext(filename)
            out_path = [os.path.join(dir, 'uic/uic_{}.py'.format(basename))]
            if self.strip_ui_prefix and basename.startswith('ui'):
                out_path[0] = os.path.join(dir, 'uic/uic_{}.py'.format(basename[2:]))
            out_path = out_path[0]
        uic_dir = os.path.dirname(out_path)
        if not os.path.exists(uic_dir):
            os.mkdir(uic_dir)
        res = subprocess.check_call('{} {} -o {} -x'.format(self.uic_bin_path, path, out_path))

        logging.info('ui compiled : {}', path)
        return res

    def lupdate(self, py_files, ts_output):  # type: (list[str], str)->int
        uis = " ".join(py_files)
        return subprocess.check_call('{} {} -ts {}'.format(self.lupdate_bin_path, uis, ts_output))

    def compile_all_ui(self):
        for ui_file in self.ui_files:
            self.compile_ui(ui_file, None)

    def exec_(self):
        self.ui_files = seek_files(self.root, comp=is_ui_file)
        self.compile_all_ui()

        # translation is not needed currently
        # py_files = seek_files(self.root, comp=is_py_file)
        # self.lupdate(py_files=py_files, ts_output=self.ts_output)


if __name__ == "__main__":
    parser = ArgumentParser()
    parser.add_argument('--root', default='.')
    parser.add_argument('--strip-ui-prefix', type=bool, default=True)
    parser.add_argument('--uic', default='pyuic5.exe')
    parser.add_argument('--lupdate', default='pylupdate5.exe')
    parser.add_argument('--ts-output', default='CryptoTrader/translate.ts')

    args = parser.parse_args()
    compiler = UICompiler(root=args.root, uic_bin_path=args.uic, lupdate_bin_path=args.lupdate, ts_output=args.ts_output,
                          strip_ui_prefix=args.strip_ui_prefix)
    compiler.exec_()
