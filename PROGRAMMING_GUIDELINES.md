# Programming guidelines
There are profound and detailed programming guidelines for various C/C++ projects
for a reason[^JSF]. Another way to proceed is to establish a small set of principles
and practices to eliminate programming conventions difficult to review. 
Using minimum number of directives and requirements cannot be all encompassing 
but can be beneficial by restricting the use of complex language features, 
encouraging the use of a compiler for static analysis, verifying control flows 
and paying attention to memory management.

This guideline is based on the renowned
[Nasa's Power of 10 Rules](https://en.wikipedia.org/wiki/The_Power_of_10:_Rules_for_Developing_Safety-Critical_Code)
that capture in a nutshell some C/C++ programming conventions for good programming
practices and make program verification and maintenance easier.

## Avoid complex program flow constructs
C/C++ language allows notoriously complex constructs with function pointers and 
pointer dereferencing which are strongly discouraged. In practice these are unnecessary.

Simple and easy to follow control flows enables easier analysis of program correctness
and improve code clarity. Archaic control statements like *goto* are considered 
detrimental and deterred since 1970's. 

## Remove all compiler warnings
From the very beginning the program should be compiled with as many compiler 
warnings flags on as feasible. Software build systems like CMake provide this automatically.
*All compiler warnings should be removed*. There is no rationale not to do this. Some
day in the future or in another compiler a warning may be an error preventing
compilation. Ideally the software should be compiled in different operating systems and 
with compilers from different vendors.

## Verify all loops have fixed bounds
Use verifiable loop bounds for all loops. Explicit bounds prevent runaway code 
and static program analysing tools can detect suspicous loops. Recursions can provide
elegant programming solutions but their termination and memory (stack) use can
be difficult to verify.

Prefer generic container classes and algorithms in the C++ standard library 
with user defined functors[^F] instead of loops.

## Functions and methods should be a single logical unit.
Each function or class method should be understandable and verifiable as a single logical entity. 
Clear purpose of a function  or method translates directly to easier program verification.
From these basic building blocks larger entities can be built.

If a function or  method exceeds one A4 page (about 60 lines) it is 
a sign of a poor program design.

## Contract programming
Based on the theoretical work in formal program verification and specification as well as 
[Hoare logic](https://en.wikipedia.org/wiki/Hoare_logic).
the upcoming *contracts* in the standard C++ library (C++26) is the latest development
supporting contract programming. In contracts software defines formal, precise 
and verifiable interface specifications for its components with preconditions, 
postconditions and invariants.

## The scope of variables should be restricted to minimum
The principle of information hiding means that if an object is not in the scope
then it is not possible to change it. If an object has too wide scope
it can be changed incompatible ways by unrelated parts of a program.
Especially if a global variable is needed enclose it with namespace.

## Use exception handling discreetly
The exception handling mechanism in C/C++ can provide means to recover from
anomalous or abnormal situations during program execution. There should be 
a real meaningful possibility to continue program execution after an exception is
detected. Otherwise simple assertion followed by program abortion can be a better solution.

## Use references instead of pointers
A reference provides the benefits of a pointer without its drawbacks. 
Reference is an alias always assigned to an object. Unlike a pointer it cannot
be reassigned. 

It is not possible to avoid pointers completely. For example C++ standard 
library containers (e.g. vectors and lists) cannot have reference type as 
members.

## Avoid macros
Instead of macros use inline functions and constant variables.

## Conditional compilation
Conditional compilation with preprocessor directives (e.g. `#ifndef ... #endif`) 
should be kept simple. The mandatory use case is to prevent header file inclusions
multiple times. Do not use preprocessor directives to enable or disable program features. 
Do not define debugging statements with conditional compilaitons. Use proper debugger. 
Do not make assumptions about compiler vendors or compiler versions. 
A compiler should comply with the C/C++ language standard.

## Practice const correctness
The keyword *const* expresses a program entity is constant that cannot be changed or does not change anything. 
Using the keyword extensively whenever this is true amounts to what is called *const correctness*. 
This is a form of type safety. It prevents unintentional modification of something that is not meant to be changed.
Any violation of the constness of an abject will result compile time error.

## Do not misuse auto keyword
The keyword *auto* is a placeholder type that will be replaced later. It lets the compiler to
determine the type of an object. One use case is in the context of container iterators
where it can increase the readability of a program. Container iterators can have long type names but
the *auto* kewyord transfers the burden to a compiler. Do not overuse the *auto* keyword. 
Type information is useful for automated compiler type control and understanding the program flow.

## Make documentation part of the work
[Doxygen](https:://www.doxygen.org) is an example of tools that can generate software documentation 
using comments in the  software. Adding comment notes to a program entity just created does 
not increase the work load. If you try to save time here easily spends time elsewhere.
A program is more often read by others than made by the author.

Doxygen has a rich set of special markup commands to highlight different program features. 
For example users of the program components are mostly are interested in function parameters, 
restrictions in usage and return values. For this Doxygen provides typesetting commands 
for parameters, their preconditions as well as function return values and postconditions. 
This supports contract programming in the documentation level until *contracts* become available
in C++26.

C/C++ namespaces help in navigating the documentation as Doxygen creates document sections
for them.

It is recommended to come back to the work after a few weeks. A clear program flow
usually shows by itself how it runs and what it does. If you cannot understand looking afresh 
the program flow it is time to improve the comments to make the work transparent for all developers. 

## Study the C++ Standard Library
The C/C++ language has matured but the [C++ Standard Library](https://en.wikipedia.org/wiki/C%2B%2B_Standard_Library) 
keeps evolving. It is based on reserach in generic programming and conventions introduced in the
[Standard Temmplate Library](https://en.wikipedia.org/wiki/Standard_Template_Library).

The [C++ reference site](https://en.cppreference.com) presents the library with examples. 
It also shows the C++ version when an approved language feature or a library component
will be available.

It is always better to use standardized tested components than reinventing the wheel.

[^JSF]: See for example [JSF Air Vehicle C++ coding standards](https://www.stroustrup.com/JSF-AV-rules.pdf)
[^F]: A functor is a C++ class with an overloaded function operator. 
