#ifndef INITIALIZE_TREE_H
#define INITIALIZE_TREE_H

#include <string>
#include <map>
#include <iostream>
#include <stringutils.h>
#include <LGMSymbols.h>
#include <DefaultBud.h>
#include <MapParameterType.h>
using namespace std;
using namespace cxxadt;


namespace Lignum{

	
  template <class TS, class BUD=DefaultBud<TS> >
    class InitializeTree{
      public:
      InitializeTree(const string& file, const LGMVERBOSE verb = QUIET)
      :tmfp(file),verbose(verb)
      {
	//Parse the configuration file (meta file) for a tree/forest
	//tmfp will contain name of the files 
	//where the actual parameters/configuration are
	tmfp.parse();
      }
      void initialize(Tree<TS,BUD>& t);
      private:
      TreeMetaFileParser tmfp; //tree configuration file parser
      MapParameterType<LGMPD> maplgmpd; //map parameter name to LGMPD
                                       //enumeration  
      LGMVERBOSE verbose;   //echo intialiazation process and its result
    };

}//closing namespace Lignum

#endif
  
#include <InitializeTreeI.h>


