#ifndef STRINGUTILS_H
#define STRINGUTILS_H
#include <string>
using namespace std;

namespace cxxadt{

  //String producer: s --> "s" 
#define Stringy (s) #s

  //class Cmpstring is to compare two strings
  //to be used for example to instantiate STL class map: 
  //map<string,valuetype,Cmpstring> 
  class Cmpstring{
  public:
    inline bool operator () (const string& s1,const string& s2);
  };

  //if equal return true else return false
  inline bool Cmpstring::operator () (const string& s1,const string& s2)
    {
      return s1 < s2;
    }
}//closing namespace cxxadt

#endif
