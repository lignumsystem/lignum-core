#ifndef COLLISION_H
#define COLLISION_H

#define C_ANGLE PI_VALUE/4.0  //radians
#define COS_ANGLE cos(C_ANGLE)
#define C_DISTANCE 0.5 //UNIT = meters

#include <Tree.h>

namespace Lignum {

//This set of two functors evaluate for all buds in the tree if other
//Buds or Treesegments are in front (determined by the direction of
//the bud and angle C_ANGLE; that is in the cone with opening angle
//C_ANGLE) of the bud at distance less than or equal to C_DISTANCE.

//First functor EvaluateCollisionForAllBuds goes through the tree
//(ForEach) and does the checking for all buds.  Second
//EvaluateCollisionForThisBud goes through the tree (Accumulate) and
//checks if any Bud or TreeSegment is in the cone of the particular
//Bud.

//The algorithm utilizes the dot product between the vector joining
//the particular Bud and the Segment or Bud that is checked and
//direction vector of the particular bud. This dot product is compared
//to the length of the vector and cosine of the opening angle of the
//cone. It should work also the opening angle of the cone is larger
//than PI.

//WARNING: this leads to pairwise comparison of TreeCompartments


//Evaluation of collision is done for all Buds in the tree with this
//functor.

template <class TS, class BUD>
class EvaluateCollisionForAllBuds{
public:
  void operator()(TreeCompartment<TS,BUD>* ts)const;
};

//This functor EvaluateCollisionForThisBud<TS,BUD> evaluates if other
//Buds or Treesegments are in front of this bud (as explained above).

template <class TS,class BUD>
class EvaluateCollisionForThisBud{
public:
  int& operator()(int& collision, TreeCompartment<TS,BUD>* tc)const;

  Point point;
  PositionVector direction;
};


}     //END OF NAMESPACE LIGNUM


#include <CollisionI.h>

#endif















