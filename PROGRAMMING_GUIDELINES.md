# Programming guidelines
There are detailed and rigorous programming guidelines for various C/C++ projects
for good reasons[^c++][^vtk][^jsf]. Large and long-term projects with many participants
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

## 6. Use exception handling sparingly
The exception handling mechanism in C++ provides a way to recover from abnormal
situations during execution. There should be a genuine possibility of continuing
the program after an exception is caught; otherwise, a simple assertion followed
by termination may be a better solution.

## 7. Use references instead of pointers
A reference provides the benefits of a pointer without its drawbacks. 
Reference is an alias always assigned to an object. Unlike a pointer it cannot
be reassigned. 

Pointers are sometimes unavoidable. For example, C++ Standard Library containers,
such as `std::vector`, cannot store references.

## 8. Avoid macros
Prefer inline functions and constant variables over macros. Macros tend to make 
the program harder to read and a compiler cannot type check macros. Avoid
macros whenever there is an alternative in C/C++.

## 9. Conditional compilation
Keep conditional compilation (like `#ifndef ... #endif`) with preprocessor directives simple.
Its mandatory use case is preventing a header file from being included multiple times. 
Do not use preprocessor directives to enable features, manage debug statements, or assume 
specific C/C++ standards. Use debugger and development environment for testing, and set
language standards within a build system like CMake.

## 10. Const correctness
The keyword `const` identifies a program entity that is immutable or does not modify other data.
Adhering to this principle consistently is known as *const correctness*. As a form of type safety,
it prevents the accidental modification of data and ensures that any violation of an object's
"constness" results in a compile-time error.

## 11. The auto keyword
The keyword `auto` is a placeholder type and its value will be determined  by a compiler. 
It is especially useful when a type is obvious or of little  importance. 
One use case is to improve readability in the context of container iterators that can have 
long and noisy type names:

	vector<int> v{1,2,3,4};
	auto iter = v.begin();
	
The iterator type is clear from the contex deduced by the compiler as `vector<int>::iterator`.

Do not use the `auto` keyword in the context of braced initializer lists. For example:

	auto a = {1,2,3};//Do not use
	
A brace-enclosed initializer list has no type. As a special case `auto a` is deduced as 
`std::initializer_list<int>`, not as an array of three integers as one inadvertently 
might expect.

Do not overuse the `auto` keyword. Type information is useful for automated compiler type control,
understanding the program flow and using the software components.

## 12. Type safe enumerations
Adopt the new scoped and type safe `enum class` instead of the old `enum`. For example:

	enum class RGBCOLOR {RED,GREEN,BLUE};
	RGBCOLOR color = RGBCOLOR::RED; //Mandatory scope resolution
	
The values in an `enum class` are encapsulated and require explicit scope resolution.

The `enum class` was introduced in C++11. Changing the old `enum` to the new `enum class`
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
of complex large-scale software systems.

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

### 15.1 Random numbers
Defined in the *&lt;random&gt;* header, the C++ Standard Library has provided a versatile set of random number generators
since C++11. This eliminates the need for ad hoc implementations; specifically, `ran3` in lignum-core can be replaced
by `std::uniform_real_distribution`.


[^c++]: See [C++ core guidelines](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines).

[^vtk]: See [VTK](https://docs.vtk.org/en/latest/developers_guide/coding_conventions.html).

[^jsf]: See [JSF Air Vehicle](https://www.stroustrup.com/JSF-AV-rules.pdf).

[^fnctr]: A functor is a C++ class with an overloaded function operator. 
