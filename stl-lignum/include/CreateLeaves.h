#ifndef CREATE_LEAVES_H
#define CREATE_LEAVES_H

#include <PositionVector.h>
using namespace cxxadt;

namespace Lignum{
  /********************************************************************
   *Two  functors to  be uses  with AccumulateDown  to  create leaves.*
   *CreateLeaves  created the leaves and AppendDirections  appends the*
   *directions   of    the   buds   in    branching   points.   Usage:*******
   *AccumulateDown(tree,vector<PositionVector>(),AppendDirections<Ts,Bud>(),*
   *                                             CreateLeaves<Ts,Bud>())    *
   *CreateLeaves uses LGMstatus of 1 for bud to create leaves.              *
   **************************************************************************/
  //From buds collect directions if they will create a leaf,
  //if segment then create the leaves.
  template <class TS, class BUD>
    class CreateLeaves{
    public:
    CreateLeaves(METER l, METER semi_major, METER semi_minor):pl(l),a(semi_major),b(semi_minor){}
    vector<PositionVector>& operator()(vector<PositionVector>& v,
				       TreeCompartment<TS,BUD>* tc)const;
    METER pl;//Petiole length
    METER a; //semi major axis of leaf ellips
    METER b; //semi minor axis od leaf ellips
  };

  template <class TS, class BUD>
    vector<PositionVector>& CreateLeaves<TS,BUD>::operator()(vector<PositionVector>& v,
							     TreeCompartment<TS,BUD>* tc)const
    {
      if (BUD* b = dynamic_cast<BUD*>(tc)){
	if (GetValue(*b,LGMstatus) == 1){
	  v.push_back(GetDirection(*b));
	  //Leaf created, set status to 0 	
	  SetValue(*b,LGMstatus,0);
	}
      }
      if (TS* ts = dynamic_cast<TS*>(tc)){
	ts->createLeaves(v,pl,a,b);
      }
      return v;
    }


  /********************************************************************
   *Append the contents of sequence s1  to the end of sequence s2. s2 *
   *can an empty sequence. Return s2.                                 *
   ********************************************************************/
  template <class T>
    class AppendSequence{
    public:
    T& operator()(T& s1, T& s2)const;

  };
  //use back_insert_iterator to add elements of s1 to the end of s2.
  template <class T>
    T& AppendSequence<T>::operator()(T& s1, T& s2)const
    {
      typename T::iterator first = s1.begin();
      typename T::iterator last = s1.end();
      back_insert_iterator<T> back(s2);

      while (first != last)
	*back++ = *first++;
      
      return s2;
    }
}//closing namespce




#endif
