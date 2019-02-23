import logging
import os

from yapf.yapflib.yapf_api import FormatFile

logger = logging.Logger(__file__)

if __name__ == "__main__":
    has_changed = False
    for root, dir, filenames in os.walk("vnpy"):
        for filename in filenames:
            basename, ext = os.path.splitext(filename)
            if ext == ".py":
                path = os.path.join(root, filename)
                reformatted_code, encoding, changed = FormatFile(
                    filename=path,
                    style_config=".style.yapf",
                    print_diff=True,
                    verify=False,
                    in_place=False,
                    logger=None,
                )
                if changed:
                    has_changed = True
                    logger.warning("File {} not formatted!".format(path))
                else:
                    logger.info("File {} is formatted!".format(path))
    exit(has_changed)
