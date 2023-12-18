///\file InitializeTree.h
///\brief Initialize tree.
///
///Initiailize tree starting from the main configuration file
///usually named *MetaFile.txt*.
///
///Lignum::InitializeTree reads the first main configuration file (a.k.a *meta file* ) and
///from there the parameter and function file names as well as Firmament configuration file name.
///Then it installs given parameters and functions as well as the Firmament in a tree.
///Initialization can take place user defined times during the simulation.
///
///\anchor NewParamsAndFuncs
///\par Steps to take to add  new parameters and functions
///\par For each new parameter:
///-# New name in Lignum::LGMPD enumeration
///-# New member in class Lignum::TreeParameters
///-# Add the new name to MapParameterType::lgmpd in MapParameterType::MapParameterType() constructor 
///-# Update Lignum::GetValue(const Tree<TS,BUD>&,const LGMPD) and Lignum::SetValue(Tree<TS,BUD>&,const LGMPD,const LGMdouble)
///   for the new parameter name
///\sa Lignum::LGMPD Lignum::TreeParameters Lignum::MapParameterType
///    MapParameterType::MapParameterType()
///
///\par For each new function:
///-# New name in Lignum::LGMF enumeration
///-# New member in class Lignum::TreeFunctions
///-# Update Lignum::GetFunction() and Lignum::SetFunction() for the new function name
///-# Update InitializeTree::initialize() in section 3. Parse functions. Add ParametricCurve::install call
///   via Tree::tf for the new function.
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
    ///\brief Initialize tree.
    ///
    /// Initialize tree with parameters, Firmament and functions.
    /// Initialization can happen user defined times during the simulation.
    ///\sa \link NewParamsAndFuncs Steps to take to add new parameters and functions \endlink
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


