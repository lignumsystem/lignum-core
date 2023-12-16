///\file InitializeTree.h
///\brief Initialize tree starting from the main configuration file
///usually named *MetaFile.txt*.
///
///Lignum::InitializeTree reads the first configuration file *meta file* and
///from there the parameter and function files. Then it installs parameters and functions in a tree.
///It also reads and configures Firmament.
///
///\anchor Reminder
///\par Reminder and to do list for new parameters and functions
///\par For each new parameter
///-# New name in Lignum::LGMPD enumeration
///-# New member in class TreeParameters
///-# Add name to MapParameterType::lgmpd in MapParameterType constructor 
///-# GetValue and SetValue for the new parameter name
///\sa Lignum::LGMPD Lignum::TreeParameters Lignum::MapParameterType
///    Lignum::MapParameterType::MapParameterType()
///
///\par For each new function
///-# New name in LGMF enumeration
///-# New member in class TreeFunctions
///-# GetFunction and SetFunction for the new name
///-# Add query for the new function for InitializeTree::tmfp
///   in InitializeTree::initialize(). Section 3 for functions.
///\sa Lignum::LGMF Lignum::TreeFunctions Lignum::InitializeTree
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
    ///Initialize tree with parameters, Firmament and functions.
    ///\sa \ref Reminder and to do list for new items
    ///\tparam TS tree segment
    ///\tparam BUD bud
    class InitializeTree{
      public:
      ///Parse the main configuration file called MetaFile
      ///\param file MetaFile
      ///\param verb Verbose mode QUIET or VERBOSE
      InitializeTree(const string& file, const LGMVERBOSE verb = QUIET)
      :tmfp(file),verbose(verb)
      {
	//Parse the configuration file (meta file) for a tree/forest
	//tmfp will contain name of the files 
	//where the actual parameters/configuration are
	tmfp.parse();
      }
      ///Read and install parameters and functions for the tree
      ///-# Read and install tree parameters
      ///-# Read and configure Firmament
      ///-# Read and install functions
      ///To view the list of known functions see LGMFM enumeration.
      ///\param t Tree
      ///\param style Initialization mode OLD_INIT or NEW_INIT.
      ///             OLD_INIT: single mask file for Firmament,
      ///             NEW_INIT: sequence of mask files for Firmament
      ///\sa Lignum::LGMFM
      void initialize(Tree<TS,BUD>& t, LGMINITSTYLE style = OLD_INIT);
      private:
      TreeMetaFileParser tmfp; ///< Tree configuration file parser
      MapParameterType<LGMPD> maplgmpd; ///< Map parameter name to LGMPD enumeration  
      LGMVERBOSE verbose;   ///< Echo intialiazation process and its result
    };

}//closing namespace Lignum

#endif
  
#include <InitializeTreeI.h>


