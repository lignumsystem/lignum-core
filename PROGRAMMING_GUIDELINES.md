# Programming guidelines
There are detaild and rigorous programming guidelines for various C/C++ projects
for good reasons[^vtk][^jsf]. Large and long-term projects with many participants
require effective management and shared standards for success. 

Another viable approach, especially for projects with limited contributors, 
is to establish a small set of practices that eliminate difficult to review programming
practices.  Minimal number of principles cannot be all encompassing but they can 
prevent the use of complex language features, encourage the use of a compiler for static analysis, 
emphasise (formal) program verification and pay attention to memory management.

This guideline for LIGNUM projects is based on the renowned
[Nasa's Power of 10 Rules](https://en.wikipedia.org/wiki/The_Power_of_10:_Rules_for_Developing_Safety-Critical_Code)
that capture in a nutshell some C/C++ conventions for good programming
practices, program verification and maintenance.

## 1. Remove all compiler warnings
Programs should be compiled with as many compiler warnings flags as feasible. 
CMake software build system provides this automatically. CMake can also enforce 
the required C/C++ standard. *All compiler warnings should be removed*. There is 
no rationale not to do this. Ideally software should be compiled in different 
operating systems, hardware and with compilers from different vendors.

## 2. Avoid complex program flow constructs
Simple and easy to follow control flows simplify program correctness analysis
and improve code clarity. Archaic control statements like *goto* obscure
program's logical excecution path and are discouraged since the 1970s.

The C/C++ language allows notoriously complex language constructs with function pointers 
and pointer dereferencing. In practice these are unnecessary.

Nowadays much of the responsibility to create efficient program executable 
from the source files is assigned to compiler automata, formal mathematical 
models to ensure source code is correctly parsed, validated, translated to machine 
code and optimized. Programmers should focus on writing clear, verified and 
correct code. 

## 3. Loops
Instead of loops prefer The C++ Standard Library container classes 
(like vectors, queues and lists) and generic algorithms with user defined 
functions or functors[^fnctr]. All loops should have verifiable loop bounds. 
Explicit bounds prevent runaway code and static program analysing tools can 
detect suspicous loops. Recursions can provide elegant problem solutions 
but their termination and memory (stack) use can be difficult to verify.

## 4. Functions and methods should be independent logical units
Each function or C++ class method should be understandable and verifiable 
as a single logical entity. Clear purpose of a function  or method 
translates directly to easier program verification. Larger-scale 
entities can be constructed from these basic building blocks.

A function or method exceeding a single A4 page (about 60 lines) 
suggests redesign of the implementation.

## 5. The scope of variables should be restricted to minimum
The principle of information hiding means that if an object is not in the scope
then it is not possible to change it. If an object has too wide scope it can be 
changed incompatible ways by unrelated parts of a program. If a global 
variable is needed enclose it with namespace.

## 6. Use exception handling discreetly
The exception handling mechanism in C/C++ can provide means to recover from
abnormal situations during program execution. There should be 
a real possibility to continue program execution after an exception is
detected and catched. Otherwise simple assertion followed by program abortion 
can be a better solution.

## 7. Use references instead of pointers
A reference provides the benefits of a pointer without its drawbacks. 
Reference is an alias always assigned to an object. Unlike a pointer it cannot
be reassigned. 

It is not possible to avoid pointers completely. For example the C/C++ vectors
and The C++ Standard Library containers cannot have reference type as members.

## 8. Avoid macros
Prefer inline functions and constant variables over macros. Macros tend to make 
the program harder to read and a compiler cannot type check macros. Avoid
macros whenever there is an alternative in C/C++.

## 9. Conditional compilation
Conditional compilation with preprocessor directives (e.g., `#ifndef ... #endif`) 
should be kept simple. The mandatory use case is to prevent a header file to 
include multiple times.

Do not use preprocessor directives to enable or disable program features,
for debugging satements or assume C/C++ language standards. Use debugger 
and development environment. Set language standard in a build system like CMake.

## 10. Const correctness
The keyword *const* expresses a program entity that cannot be changed 
or does not change anything. Using the keyword consistently whenever this is true 
amounts to what is called *const correctness*. It is a form of type safety. 
It prevents unintentional modification of something that is not meant to be changed.
Any violation of the constness of an abject will result compile time error.

## 11. The auto keyword
The keyword *auto* is a placeholder type and its value will be determined  by a compiler. 
It is especially useful when a type is obvious or of little  importance. 
One use case is to improve readability in the context of container iterators that can have 
long and noisy type names:

	vector<int> v{1,2,3,4};
	auto iter = v.begin();
	
The iterator type is clear from the contex deduced by the compiler as vector<int>::iterator.

Do not use the *auto* keyword in the context of braced initializer lists. For example:

	auto a = {1,2,3};//Do not use
	
A brace-enclosed initializer list has no type. As a special case `auto a` is deduced as 
std::initializer_list<int>, not as a list or a vector as one might expect.

Do not overuse the *auto* keyword. Type information is useful for automated compiler type control 
and understanding the program flow.

## 12. Type safe enumerations
Adopt the new scoped and type safe *enum class* instead of the old *enum*. For example:

	enum class RGBCOLOR {RED,GREEN,BLUE};
	RGBOLOR color = RGBCOLOR::RED; //Mandatory scope resolution
	
The values in an *enum class* are encapsulated and require explicit scope resolution.

The *enum class* was introduced in C++11. Changing the old *enum* to the new *enum class*
can be laborous in older projects, trigger cascade of incompatibility effects that disrupt 
dependent projects.

## 13. Programming paradigms
Programming paradigms or methodologies are the results from the research 
into practices of software development. These discoveries allow for comparison
of program design, programming practices and languages. 

The choice and use of programming paradigms should be part of program design, 
not a retrospective activity. One need not be restricted to a single paradigm 
but programming language traits can be utilized.

C++ as a multi-paradigm language supports object-oriented, generic and contract programming. 

### 13.1 Object-oriented programming
The C++ was originally as an improvement of general-purpose, widely used and portable C 
by adding  object-oriented features like classes with methods, derived classes and strong typing. 

Object-oriented paradigm is based on software entities called objects, 
that encapsulate both data and methods defining the object's behaviour 
and interactions with other entities. This simplifies the design and management 
of complex large-scale sofware systems.

### 13.2 Generic programming 
In generic programming algorithms are written in terms of parameterised types 
that are instantiated with concrete types as neeeded. This reduces for example need 
for multiple code for each required concrete type. In C++ the generalization mechanism 
is called templates.

Generic programming has become important design principle when implementing 
proficient programming libraries such as The C++ Standard Library.

### 13.3 Contract programming
The upcoming *contracts* in The Standard C++ Library (C++26) is based on the theoretical 
work in formal program specification and verification as well as 
[Hoare logic](https://en.wikipedia.org/wiki/Hoare_logic). In contracts software defines 
formal and verifiable interface specifications with preconditions, postconditions and invariants.

## 14. Doxygen documentation
[Doxygen](https:://www.doxygen.org) can generate software documentation using special comments 
in the  software. Adding comment notes to a program entity does not increase the workload even if
the component might change. Shortcuts here easily exploits the time of others later. 
Software is read far more frequently than written.

Doxygen's rich set of special markup commands highlight C/C++ language entities
such as classes, templates, functions, namespaces, enumerations and types.
Each C/C++ namespace maps to its own section to improve the document navigation. 
Doxygen outputs the final software documentation in various formats including HTML, LaTeX and PDF.

Review the implementation after some time. If the program flow is now confusing redesign 
the implementation and improve the documentation to ensure transparency for all developers and users. 

## 15. The C++ Standard Library
Prefer [The C++ Standard Library](https://en.wikipedia.org/wiki/C%2B%2B_Standard_Library) over custom implementations.
The C/C++ as a programming language has matured but The C++ Standard Library advances steadily with every ISO standard update. 
It is based on reserach in generic programming and influenced by concepts introduced in 
[STL](https://en.wikipedia.org/wiki/Standard_Template_Library) and [Boost](https://www.boost.org).

The [C++ reference site](https://en.cppreference.com) presents the library with examples. 
It also identifies the C++ language version in which an approved language feature or a library component
is first available. 

[^vtk]: See [VTK](https://docs.vtk.org/en/latest/developers_guide/coding_conventions.html).
[^jsf]: See [JSF Air Vehicle](https://www.stroustrup.com/JSF-AV-rules.pdf).
[^fnctr]: A functor is a C++ class with an overloaded function operator. 
