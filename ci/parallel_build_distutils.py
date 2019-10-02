"""
monkey patch distutils to use multi-core to build single extension.
these code is based on:
https://stackoverflow.com/a/13176803/4797109
"""

import multiprocessing.pool

parallel: int = 1


# monkey-patch for parallel compilation
def parallel_compile(self,
                     sources,
                     output_dir=None,
                     macros=None,
                     include_dirs=None,
                     debug=0,
                     extra_preargs=None,
                     extra_postargs=None,
                     depends=None,
                     ):
    # those lines are copied from distutils.ccompiler.CCompiler directly
    macros, objects, extra_postargs, pp_opts, build = self._setup_compile(
        output_dir, macros, include_dirs, sources, depends, extra_postargs
    )
    cc_args = self._get_cc_args(pp_opts, debug, extra_preargs)

    def _single_compile(obj):
        try:
            src, ext = build[obj]
        except KeyError:
            return
        self._compile(obj, src, ext, cc_args, extra_postargs, pp_opts)

    # convert to list, imap is evaluated on-demand
    list(multiprocessing.pool.ThreadPool(parallel).imap(_single_compile, objects))
    return objects


def patch_distutils(jobs: int = None):
    if jobs:
        global parallel
        parallel = jobs
    import distutils.ccompiler
    distutils.ccompiler.CCompiler.compile = parallel_compile
