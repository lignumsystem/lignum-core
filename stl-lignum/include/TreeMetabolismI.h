#ifndef TREEMETABOLISMI_H
#define TREEMETABOLISMI_H

namespace Lignum{

template <class TS,class BUD>
TreeCompartment<TS,BUD>* TreePhotosynthesis(TreeCompartment<TS,BUD>* tc)
{
  tc->photosynthesis();
  return tc;
}



template <class TS,class BUD>
void Tree<TS,BUD>::photosynthesis()
{
  TreeCompartment<TS,BUD>* TreePhotosynthesis(TreeCompartment<TS,BUD>* tc);

  //Have TreeCompartments to do photosynthesis

  ForEach(*this, TreePhotosynthesis);
 
}


} //Closing namespace Lignum

#endif
































