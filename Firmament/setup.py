## \file setup.py
## \brief Python extension package for sky::Firmament
##
##Python interface is defined in Firmament.pyx and Firmament.pxd files 
from setuptools import Extension, setup
from Cython.Build import cythonize


#sourcels: Cython and additional C++ source files.
#A Python interface is defined in *.pyx and *.pxd files 
sourcels=["Firmament.pyx"]

#extra_compile_args=["-I. "]

#The Python extension package for Firmament C++ class.
#The first name *pyfirmament* is for the project, how it is listed on PyPi if installed.
setup(name="pyfirmament",
      ext_modules = cythonize(
          Extension(
          #The extension name
          name="firmament",
          #Search C++ header files (with angle brackets) in current directory
          include_dirs=["include","../c++adt/include","../stl-lignum/include"],
          #libc++adt.a
          libraries=["cxxadt"],
          library_dirs=["../c++adt/lib"],
          #extra_link_args=["-L../c++adt/lib","-lcxxadt"],
          sources=sourcels,
          #Generate and compile C++ code
          language="c++",                        
       ),
          #This directive requires python3
          compiler_directives={'language_level' : "3str"}
      ))
