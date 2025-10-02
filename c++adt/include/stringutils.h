/// \file stringutils.h
/// \brief String utilities
#ifndef STRINGUTILS_H
#define STRINGUTILS_H
#include <string>
using namespace std;

namespace cxxadt{

///\brief String producer: s --> "s" 
#define Stringy (s) #s

  ///\brief Compare two strings.
  ///
  ///Compare two string with '<' operator.
  ///To be used for example to instantiate  std::map
  ///\code{.cc}
  ///map<string,valuetype,Cmpstring>
  ///\endcode
  class Cmpstring{
  public:
    ///\brief Compare two strings
    ///\param s1 First string
    ///\param s2 Second string
    ///\retval true  s1 <  s2
    ///\retval false s1 >= s2
    inline bool operator () (const string& s1,const string& s2)const;
  };

  
  inline bool Cmpstring::operator () (const string& s1,const string& s2)const
    {
      return s1 < s2;
    }
}//closing namespace cxxadt

#endif
