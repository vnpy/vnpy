# encoding: UTF-8

from argparse import ArgumentParser

if __name__ == '__main__':
    # 加载默认参数
    opt = ArgumentParser(
        prog="vnpy",
        description="Args of vnpy.",
    )
    opt = ArgumentParser()

    # UI开关
    opt.add_argument("--no-ui", dest="ui", action="store_false", help="Not use UI")
    opt.set_defaults(ui=True)

    args = opt.parse_args()
    print(args)