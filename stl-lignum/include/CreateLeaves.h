#ifndef CREATE_LEAVES_H
#define CREATE_LEAVES_H

#include <PositionVector.h>
#include <Sequence.h>

using namespace cxxadt;

namespace Lignum{
  /********************************************************************
   *Two  functors to  be uses  with AccumulateDown  to  create leaves.*
   *CreateLeaves  created the leaves and AppendDirections  appends the*
   *directions   of    the   buds   in    branching   points.   
   *Usage:
   *AccumulateDown(tree,vector<PositionVector>(),AppendSequence<TS,BUD>(),*
   *                                             CreateLeaves<TS,BUD>())    *
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
    vector<PositionVector>& CreateLeaves<TS,BUD>::operator()(vector<PositionVector>& pdv,
							     TreeCompartment<TS,BUD>* tc)const
    {
      if (BUD* b = dynamic_cast<BUD*>(tc)){
	if (GetValue(*b,LGMstatus) == 1){
	  pdv.push_back(GetDirection(*b));
	  //Leaf created, set status to 0 	
	  SetValue(*b,LGMstatus,0);
	}
      }
      if (TS* ts = dynamic_cast<TS*>(tc)){
	Point origo(0,0,0);
	Point point = GetEndPoint(*ts);
	PositionVector up(0,0,1);
	Ellipsis shape(a,b); //initial shape of a leaf is Ellips
	static Uniform u; //uniform random number [0,1] for setting leaf
	                  //normals;  static makes it  common throughout
	                  //the  program and  not reinitialized  in each
           	          //call.
	int seed = 3267;
	for (unsigned int i = 0; i <pdv.size(); i++){
	  PositionVector pdir = pdv[i];
	  //Leaves are  created at the end  of the segment  where the buds
	  //are, second argument is the intial length of the petiole
	  Petiole petiole(point,point + pl*(Point)pdir);
	  //Randomize  the leaf blade  normal by  rotating in  around axis
	  //that lies in the horizontal plane defined by cross product of
	  //petiole direction and up-vector
	  PositionVector plane = Cross(pdir,up);
	  //limit the rotation  of the leaf normal to  [-90,90] degrees so
	  //that the leaf normal does not point downwards
	  double ran = (-90.0 +180.0*u(seed))*2.0*PI_VALUE/360; //(radians)
	  PositionVector leaf_normal(0,0,1);
	  leaf_normal.rotate(origo,plane,ran);
	  BroadLeaf<Ellipsis>* leaf = new BroadLeaf<Ellipsis>(shape,petiole,leaf_normal);
	  //Insert leaf
	  ts->addLeaf(leaf);
	}
	//clear the vector; don't create leaves twice
	pdv.clear();
      }
      return pdv;
    }



}//closing namespce




#endif
