#ifndef INITIALIZE_TREE_H
#define INITIALIZE_TREE_H
#include <string>
#include <map>
#include <stringutils.h>
#include <LGMSymbols.h>
#include <DefaultBud.h>

using namespace std;
using namespace cxxadt;

namespace Lignum{
  //MapParameterType maps name of the parameter to its enumeration.
  //The class can be instantiated with different enumerations 
  //found in LGMSymbols.h (for template T).
  //The constructor must be a specialization enlisting the mappings.
  //The current specializations are in TreeFriend.cc. Please remember to update
  //current ones if new parameters emerge. 
  template <class T>
  class MapParameterType{
  public:
    MapParameterType();
    typename map<string,T,Cmpstring>::iterator begin();
    typename map<string,T,Cmpstring>::iterator end();
    typename map<string,T,Cmpstring>::iterator find(const string& l);
  private:
    map<string,T,Cmpstring> lgmpd;
  };

  template <class T>
  inline typename map<string,T,Cmpstring>::iterator MapParameterType<T>::begin()
    {
      return lgmpd.begin();
    }

  template <class T>
  inline typename map<string,T,Cmpstring>::iterator MapParameterType<T>::end()
    {
      return lgmpd.end();
    }
  
  template <class T>
  inline typename map<string,T,Cmpstring>::iterator MapParameterType<T>::find(const string& l)
    {
      return lgmpd.find(l);
    }

  template <class TS, class BUD = DefaultBud<TS> >
    class InitializeTree{
      public:
      InitializeTree(const string& file, const LGMVERBOSE verbose = QUIET);
      void initialize(Tree<TS,BUD>& t);
      private:
      TreeMetaFileParser tmfp; //tree configuration file parser
      MapParameterType<LGMPD> maplgmpd; //map parameter name to LGMPD enumeration  
      MapParameterType<LGMTD> maplgmtd; //map transit variable to LGMTD enumeration
      LGMVERBOSE verbose;   //echo intialiazation process and its result
    };
}//closing namespace Lignum
  
#include <InitializeTreeI.h>

#endif
