# tests/runner.py
import unittest

# import your test modules
import test_import_all
import trader
import app

# initialize the test suite
loader = unittest.TestLoader()
suite = unittest.TestSuite()

# add tests to the test suite
suite.addTests(loader.loadTestsFromModule(test_import_all))
suite.addTests(loader.loadTestsFromModule(trader))
suite.addTests(loader.loadTestsFromModule(app))

# initialize a runner, pass it your suite and run it
runner = unittest.TextTestRunner(verbosity=3)
result = runner.run(suite)
