# setup.py
from distutils.core import setup, Extension

setup(name="_chi",
      ext_modules=[
        Extension("_chi",
                  ["_chi.c", "chi2.c"],
                  include_dirs = ['.'],
                  )
        ]
)
