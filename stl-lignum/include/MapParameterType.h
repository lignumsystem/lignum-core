///\file MapParameterType.h
///\brief Map parameter name string to parameter name enumeration 
#ifndef MAP_PARAMETERTYPE_H
#define MAP_PARAMETERTYPE_H

#include <map>
using namespace std;
#include <stringutils.h>
using namespace cxxadt;

namespace Lignum{
  ///\brief Map the  name of the parameter to its enumeration.
  ///
  ///The class can be instantiated with different enumerations 
  ///found in LGMSymbols.h (for template T).
  ///The constructor must be a specialization enlisting the mappings.
  ///The current specializations are in TreeFriend.cc. Please remember to update
  ///current ones if new parameters emerge.
  ///\tparam T Parameter type enumeration
  template <class T>
  class MapParameterType{
  public:
    MapParameterType();
    typename map<string,T,Cmpstring>::iterator begin();
    typename map<string,T,Cmpstring>::iterator end();
    ///Find the Parameter enumeration corresponding the search string
    ///\param l Search string
    typename map<string,T,Cmpstring>::iterator find(const string& l);
  private:
    map<string,T,Cmpstring> lgmpd;
  };
  template <class T>
  typename map<string,T,Cmpstring>::iterator MapParameterType<T>::begin()
    {
      return lgmpd.begin();
    }

  template <class T>
  typename map<string,T,Cmpstring>::iterator MapParameterType<T>::end()
    {
      return lgmpd.end();
    }
  
  template <class T>
  typename map<string,T,Cmpstring>::iterator MapParameterType<T>::find(const string& l)
    {
      return lgmpd.find(l);
    }


  
}

#endif
