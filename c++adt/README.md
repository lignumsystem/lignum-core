# C++adt project classes

This project contains ubuiquitous classes used in the Lignum system development
dating back from a longer period of time. Some of them are now obsolete
due to the STL library, for example DList implementation.

We have tried to document the relevant ones (e.g. PositionVector, Parallelogram)
with Doxygen but there are still potentially useful classes undocumented.

Due to their mathematical nature some of the classes (e.g.Parallelogarm)
use \f( \LaTeX \f) typesetting. To install \f( \LaTeX \f) for example MacPorts
has \f( \TeX \f) Live. When installed Doxygen should be able to render
\f( \LaTeX \f) automatically.

To generate Doxygen documentation type (zsh shell):

    doxygen Doxyfile 2> errors.txt
    
Errors will appear in *errors.txt* file.
