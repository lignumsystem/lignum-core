# Programming guidelines
Although there are thorough and detailed programming guidelines for various C/C++ projects[^JSF] 
restricting  the number of rules can provide an effective guideline for project in hand.  The minimum
number of rules cannot be all encompassing but can be beneficial by restricting the use of complex 
language features, encouraging the use of compiler for static analysis, verifying control
flows and paying attention to memory management.

These advice and guidelines are based on 
[Nasa's Power of 10 Rules](https://en.wikipedia.org/wiki/The_Power_of_10:_Rules_for_Developing_Safety-Critical_Code)
that capture in a nutshell some C/C++ programming conventions that strive towards good programming
practices and easier program verification and maintenance.

## Avoid complex program flow constructs
Simple control flows allows easier analysis of program correctness.
Archaic control statements like *goto* are considered detrimental since 1970's.

## Verify all loops have fixed upper bound
Loops that have explicit upper bound prevent runaway code. 

## All functions and methods should do one thing
Clear purpose of a function or method translates to easier program verification.
If a function or  method exceeds one A4 page (about 60 lines) it is time to rethink
the implementation.

## The scope of variables should be restricted to minimum
The principle of information hiding means that if an object is not in scope
then it is not possible to change its value. If an object has a too wide scope
it can be changed incompatible ways by unrelated parts of a program.
Especially if a global variable is needed enclose it to namespace. Then the
variable is less global.

## Use references instead of pointers
A reference provides the benefits of a pointer without drawbacks. 
Reference is an alias to an object. Unlike a pointer it cannot
be reassigned. 

Sometimes it is not possible to avoid pointers. For example C++ template
libray containers (like vectors and lists) cannot have reference type as 
members. Consider using generic container algorithms with functors,
a class with overloaded function operator, instead of loops.

## Remove all compiler warnings
From the very beginning the program should be compiled with as many compiler 
warnings flags on as feasible. Software build systems like CMake provides this automatically.
All compiler warnings should be removed. There is no rationale not to do this. Some
day in the future or in another compiler a warning may be an compiler error preventing
compilation. Ideally the software should be compiled in different operating systems and 
with compilers from different vendors.

## Practice const correctness
The keyword *const* expresses a program entity is constant and cannot be changed or does not change anything. 
Using the keyword extensively whenever this is true amounts to whatis called *const correctness*. 
This is a form of type safety. It prevents inadvertently modification of something that is not meant to be changed.
Any violation of the constness of an abject results compile time error.

## Do not misuse auto keyword
The keyword *auto* is a placeholder type that will be replaced later. It lets the compiler to
determine the type of an object. One use case that can increase the readability of a program
is in the context of container iterators. Container iterators can have long type names but
the *auto* kewyord transfers the burden to a compiler. Do not overuse the *auto* keyword. 
Type information can be useful to analyse the progam flow.

## Document as you go
[Doxygen](https:://www.doxygen.org) is an example of tools that can generate software documentation 
using comments in the  software. The special commands in Doxygen gives wide variety of possibilities 
to highlight different program features.  For example users of the program components
are mostly interested in them as black boxes. They are interested in function parameters, restrictions 
in usage and return values. For this Doxygen provides documentation keywords for parameters, 
their preconditions as well as function return values and postconditions.

It is recommended to come back to the work after a few days. A clear program flow
usually shows by itself how it runs. If you cannot understand the your own program flow 
it is time to make notes to make it transparent for all developers. 

Use C/C++ namespaces because Doxygen creates document sections based on namespaces. This helps
in navigating the document.

## Study the C++ Standard Library
The C/C++ language has matured but the [C++ Standard Library](https://en.wikipedia.org/wiki/C%2B%2B_Standard_Library) keeps evolving. 
It is based on reserach in generic programming and conventions introduced in 
[Standard Temmplate Library](https://en.wikipedia.org/wiki/Standard_Template_Library).

The [C++ reference site](https://en.cppreference.com) presents the library with examples. 
It also shows the version of the C++ standard the library component should be part of.

It is always better to use standardized tested components than reinventing the wheel yourself.

[^JSF]: See for example [JSF Air Vehicle C++ coding standards](https://www.stroustrup.com/JSF-AV-rules.pdf)

