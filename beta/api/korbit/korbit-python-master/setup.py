
try:
    from setuptools import setup
except ImportError:
    from distutils.core import setup

setup(
    name='korbit-python',
    packages=['korbit'],
    version='0.5.0',
    description='korbit API wrapper for Python',
    url='http://github.com/Hoonjin/korbit-python/',
    author='Daniel Ji',
    author_email='bwjhj1030@gmail.com',
    install_requires=['requests'],
    classifiers=[
        "Programming Language :: Python",
        "Programming Language :: Python :: 3",
        "License :: OSI Approved :: MIT License",
        "Operating System :: OS Independent",
        "Topic :: Software Development :: Libraries :: Python Modules"
    ],
    license='MIT',
)
