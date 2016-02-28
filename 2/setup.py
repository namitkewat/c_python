# setup.py
from distutils.core import setup, Extension

setup(name="_nkmath",
      ext_modules=[
        Extension("_nkmath",
                  ["nkmath.c", "_nkmath.c"],
                  include_dirs = ['.'],
                  )
        ]
)
