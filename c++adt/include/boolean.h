
#ifndef BOOLEAN_H
#define BOOLEAN_H

namespace cxxadt{

#ifdef FALSE
#undef FALSE
#endif
#ifdef TRUE
#undef TRUE
#endif

enum BOOLEAN {FALSE,TRUE};

}//closing namespace cxxadt

#endif
