#ifndef TREEMETABOLISMI_H
#define TREEMETABOLISMI_H

namespace Lignum{

template <class TS,class BUD>
  class TreePhotosynthesis{
  public:
  TreeCompartment<TS,BUD>* operator()(TreeCompartment<TS,BUD>* tc)const{
    tc->photosynthesis();
    return tc;
  }
};

template <class TS,class BUD>
void Tree<TS,BUD>::photosynthesis()
{
  //Have TreeCompartments to do photosynthesis

  ForEach(*this, TreePhotosynthesis<TS,BUD>());
 
}


} //Closing namespace Lignum

#endif
































