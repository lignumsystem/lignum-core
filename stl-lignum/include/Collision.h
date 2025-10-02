/// \file Collision.h
/// \brief Growth space collision detection 
#ifndef COLLISION_H
#define COLLISION_H

#define C_ANGLE PI_VALUE/4.0  //radians
#define COS_ANGLE cos(C_ANGLE)
#define C_DISTANCE 0.5 //UNIT = meters

#include <Tree.h>

namespace Lignum {

///\brief Evaluate collisions in growth space for buds
///
///Evaluate for all buds in the tree if other buds or tree segments are
///in front (determined by the direction of the bud and angle C_ANGLE
///(the cone with opening angle C_ANGLE) of the bud at distance less
///than or equal to C_DISTANCE.
///
///First functor EvaluateCollisionForAllBuds goes through the tree
///(Lignum::ForEach) and does the checking for all buds.  Second
///EvaluateCollisionForThisBud goes through the tree (Lignum::Accumulate) and
///checks if any Bud or TreeSegment is in the cone of the particular
///Bud.
///
///The algorithm utilizes the cxxadt::Dot product between the vector joining
///the particular Bud and the Segment or Bud that is checked and
///direction vector of the particular bud. This dot product is compared
///to the length of the vector and cosine of the opening angle of the
///cone. It should work also the opening angle of the cone is larger
///than \f$ \pi \f$.
///
///\warning Algorithm makes pairwise comparisons of buds and tree segments
/// and has \f$ \mathcal{O}(n^2) \f$ worst case complexity
template <class TS, class BUD>
class EvaluateCollisionForAllBuds{
 public:
  ///\brief Constructor
  ///\param angle Cone opening angle for collision detection 
  ///\param distance Cone height 
  EvaluateCollisionForAllBuds(LGMdouble angle = PI_VALUE/2.0,
			      LGMdouble distance = 1.0 /* meters */) {
    c_angle = angle;
    c_distance = distance;
  }
  ///\brief Evaluate collision for buds
  ///\param tc Tree compartment
  void operator()(TreeCompartment<TS,BUD>* tc)const;
 private:
  LGMdouble c_angle;///< Cone opening angle
  LGMdouble c_distance;///< Cone height, collision distance in the cone 
};


///\brief Evaluate if a bud or a tree segment collides with this bud.
///\note Calculations are made with half of cone angle
///\sa EvaluateCollisionForAllBuds
template <class TS,class BUD>
class EvaluateCollisionForThisBud{
public:
  ///\brief Constructor
  ///\param angle Cone opening angle
  ///\param distance Collision distance
  EvaluateCollisionForThisBud(LGMdouble angle = PI_VALUE/2.0,
			      LGMdouble distance = 1.0 /* meters */) {
    c_angle = angle;
    c_cos = cos(angle/2.0); //Note: calculations made with half of cone angle
    c_distance = distance;
  }

  ///\brief Detect collision for a bud
  ///\param collision Collision detection
  ///\param tc Tree compartment
  ///\retval collision
  ///\retval 1 Collision detected
  ///\retval 0 No collision
  int& operator()(int& collision, TreeCompartment<TS,BUD>* tc)const;

  Point point;
  PositionVector direction;
  LGMdouble c_angle, c_cos;
  LGMdouble c_distance;
};


}     //END OF NAMESPACE LIGNUM


#include <CollisionI.h>

#endif















