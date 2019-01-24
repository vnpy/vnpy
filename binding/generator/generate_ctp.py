import logging
import os

from adaptor.ctpadaptor import CtpAdaptor
from autocxxpy.generator import GeneratorOptions, Generator

logger = logging.getLogger(__file__)


def clear_dir(path: str):
    for file in os.listdir(path):
        os.unlink(os.path.join(path, file))


def main():
    options: GeneratorOptions = CtpAdaptor(
        "../source/ctp/api/ThostFtdcMdApi.h",
        "../source/ctp/api/ThostFtdcTraderApi.h",
    ).parse()

    options.includes.append("api/ThostFtdcTraderApi.h")
    options.includes.append("api/ThostFtdcMdApi.h")
    options.split_in_files = True
    options.module_name = "vnctp"
    options.max_classes_in_one_file = 100

    saved_files = Generator(options=options).generate()
    output_dir = "./generated_files"
    # clear output dir
    if not os.path.exists(output_dir):
        os.mkdir(output_dir)
    clear_dir(output_dir)

    for name, data in saved_files.items():
        with open(f"{output_dir}/{name}", "wt") as f:
            f.write(data)


if __name__ == "__main__":
    main()
