#ifndef VTREE_H
#define VTREE_H

namespace Lignum{

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
