# Programming guidelines
There are profound and detailed programming guidelines for various C/C++ projects
for good reasons[^JSF]. Large and long-term projects demand effective management and
common standards for succesful collaboration. Another way to proceed, especially in
projects with limited number of participants, can be to establish a small set of practices 
to eliminate programming conventions difficult to review. 

Using minimum number of guiding principles and requirements cannot be all encompassing 
but can be beneficial by restricting the use of complex language features, 
encouraging the use of a compiler for static analysis, emphasising (formal) verification 
of program flows and paying attention to memory management.

This guideline for LIGNUM projects is based on the renowned
[Nasa's Power of 10 Rules](https://en.wikipedia.org/wiki/The_Power_of_10:_Rules_for_Developing_Safety-Critical_Code)
that capture in a nutshell some C/C++ conventions for good programming
practices and make program verification and maintenance easier.

## 1. Remove all compiler warnings
From the very beginning the program should be compiled with as many compiler 
warnings flags on as feasible. Software build systems like CMake provide this automatically.
*All compiler warnings should be removed*. There is no rationale not to do this. Some
day in the future or in another compiler a warning may be an error preventing
compilation. Ideally the software should be compiled in different operating systems and 
with compilers from different vendors.

## 2. Avoid complex program flow constructs
Simple and easy to follow control flows enables easier analysis of program correctness
and improve code clarity. Archaic control statements like *goto* are considered 
detrimental and deterred since 1970's. 

The C/C++ language allows notoriously complex language constructs for example 
with function pointers and pointer dereferencing which are strongly discouraged. 
In practice these are unnecessary.

## 3. Verify all loops have fixed bounds
Use verifiable loop bounds for all loops. Explicit bounds prevent runaway code 
and static program analysing tools can detect suspicous loops. Recursions can provide
elegant programming solutions but their termination and memory (stack) use can
be difficult to verify.

Prefer generic container classes (like vectors, queues and lists) and algorithms 
in The C++ Standard Library with user defined functors[^F] instead of loops.

## 4. Functions and methods should be independent logical units
Each function or class method should be understandable and verifiable 
as a single logical entity. Clear purpose of a function  or method 
translates directly to easier program verification. From these basic 
building blocks larger entities can be constructed.

A function or method exceeding a single A4 page (about 60 lines) 
suggests redesign of the implementation.

## 5. The scope of variables should be restricted to minimum
The principle of information hiding means that if an object is not in the scope
then it is not possible to change it. If an object has too wide scope
it can be changed incompatible ways by unrelated parts of a program.
Especially if a global variable is needed enclose it with namespace.

## 6. Use exception handling discreetly
The exception handling mechanism in C/C++ can provide means to recover from
anomalous or abnormal situations during program execution. There should be 
a real meaningful possibility to continue program execution after an exception is
detected. Otherwise simple assertion followed by program abortion can be a better solution.

## 7. Use references instead of pointers
A reference provides the benefits of a pointer without its drawbacks. 
Reference is an alias always assigned to an object. Unlike a pointer it cannot
be reassigned. 

It is not possible to avoid pointers completely. For example the C/C++ vectors
and The C++ Standard Library containers cannot have reference type as members.

## 8. Avoid macros
Instead of macros use inline functions and constant variables. In general
do not use a macro if there is an alternative in C/C++. 

Macros tend to make the program harder to read and a compiler cannot type check macros.
Although one can avoid for example function call overheads with macros the
overall gain in program execution speed is likely to be insignificant.

## 9. Conditional compilation
Conditional compilation with preprocessor directives (e.g. `#ifndef ... #endif`) 
should be kept simple. The mandatory use case is to prevent header file inclusions
multiple times. 

Do not use preprocessor directives to enable or disable program features. 
Instead of debugging statements within conditional compilation use proper debugger. 
A compiler should comply with its C/C++ language standard and does not
need assumptions about operating system or compiler vendor.

## 10. Const correctness
The keyword *const* expresses a program entity is constant that cannot be changed or does not change anything. 
Using the keyword extensively whenever this is true amounts to what is called *const correctness*. 
This is a form of type safety. It prevents unintentional modification of something that is not meant to be changed.
Any violation of the constness of an abject will result compile time error.

## 11. The auto keyword
The keyword *auto* is a placeholder type that will be replaced later. It lets the compiler to
determine the type of an object. One use case is in the context of container iterators
where it can increase the readability of a program. Container iterators can have long type names but
the *auto* kewyord transfers the burden to a compiler. Do not overuse the *auto* keyword. 
Type information is useful for automated compiler type control and understanding the program flow.

## 12. Programming paradigms
Programming paradigms or methodologies are the results from the research 
into practices of software development. These discoveries allow comparing program design, 
programming practices and languages used to implement the software. 

The choice and use of programming paradigms should be already part of program design, 
not a retrospective activity. There is no reason to select just one paradigm 
and become trapped by it but the programming language traits can be utilized.

A programming language can support multiple paradigms. In the context of the C++ language three
methodologies can be emphasized: object-oriented, generic programming and contract programming.

### 12.1 Object-oriented programming
The C++ was originally designed by B. Stroustrup as an improvement of general-purpose,
widely used and portable C by adding  object-oriented features like classes with methods, 
derived classes and strong typing. 

Object-oriented paradigm is based on software entities, objects, 
that can encapsulate both data and functions or methods defining the object's behaviour 
and interactions with other entities. This is considered helpful in designing larger 
sofware systems.

### 12.2 Generic programming 
In generic programming algorithms are written in terms of parameterised types 
that are instantiated with concrete types as neeeded. This reduces for example need 
for multiple code for each required concrete type. In C++ the genericity mechanism 
is called templates.

Generic programming has become important design principle when implementing 
proficient programming libraries such as The C++ Standard Library.

### 12.3 Contract programming
Based on the theoretical work in formal program specification and verification as well as 
[Hoare logic](https://en.wikipedia.org/wiki/Hoare_logic) the upcoming *contracts* 
in The Standard C++ Library (C++26) is the latest library development supporting contract programming. 
In contracts software defines formal, precise and verifiable interface specifications 
for its components with preconditions, postconditions and invariants.

## 13. Make documentation part of the work
[Doxygen](https:://www.doxygen.org) is an example of tools that can generate software documentation 
using special comments in the  software. Adding comment notes to a program entity just created does 
not increase the workload even if the component is likely to change. If you try to save time at this point 
easily uses up time aftewards for others. A program is more often read than made.

Doxygen has a rich set of special markup commands to highlight various program features. 
For example users of the program components are mostly interested in function parameters, 
restrictions in usage and return values. For this Doxygen provides typesetting commands 
for function parameters and preconditions as well as for return values, invariants and postconditions. 
This supports contract programming in the documentation until *contracts* become available
also in C++26.

C/C++ namespaces help navigating the documentation because Doxygen creates document sections
for each namespace.

It is recommended to come back to the implementation after a few weeks or months. A clear program flow
usually shows by itself how it runs and what it does. If you cannot understand looking afresh 
the program flow it is time to reconsider the implementation and improve the documentation
to make the work transparent for all developers. 

## 14. Study and use The C++ Standard Library
The C/C++ language has matured but [The C++ Standard Library](https://en.wikipedia.org/wiki/C%2B%2B_Standard_Library) 
keeps evolving. It is based on reserach in generic programming and conventions introduced in the
[Standard Template Library](https://en.wikipedia.org/wiki/Standard_Template_Library).

The [C++ reference site](https://en.cppreference.com) presents the library with examples. 
It also shows the C++ version when an approved language feature or a library component
will be available.

It is always better to use standardized verified program library components than reinventing the wheel.

[^JSF]: See for example [JSF Air Vehicle C++ coding standards](https://www.stroustrup.com/JSF-AV-rules.pdf)
[^F]: A functor is a C++ class with an overloaded function operator. 
