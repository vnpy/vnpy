# tests/runner.py
import unittest

import app
# import your test modules
import test_import_all
import trader

# initialize the test suite
loader = unittest.TestLoader()
suite = unittest.TestSuite()

# add tests to the test suite
suite.addTests(loader.loadTestsFromModule(test_import_all))
suite.addTests(loader.loadTestsFromModule(trader))
suite.addTests(loader.loadTestsFromModule(app))


# initialize a runner, pass it your suite and run it
def main():
    runner = unittest.TextTestRunner(verbosity=3)
    result = runner.run(suite)
    return result


if __name__ == '__main__':
    result = main()
    if result.failures or result.errors:
        exit(1)
    else:
        exit(0)
