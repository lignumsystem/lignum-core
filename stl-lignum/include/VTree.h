/// \file VTree.h
/// \brief Experimental virtual tree in Lignum::Forest not active
#ifndef VTREE_H
#define VTREE_H

namespace Lignum{

  ///\brief Experimental virtual base class for trees
  ///
  ///Inheriting VTree multiple species can be stored in
  ///a container of type VTree.
  class VTree{
  public:
    //Make one public dummy constructor to avoid compiler warnings.
    VTree(){}
  private:
    //Dummy creates virtual function tables so that we can use dynamic
    //casts.
    virtual void dummy(){}
  };

}//closing namepspace
#endif
