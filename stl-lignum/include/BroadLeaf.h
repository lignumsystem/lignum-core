/// \file BroadLeaf.h
/// \brief Model for leaves.
///
/// Model for broad leaf trees consists of
/// template class BroadLeaf, class BroadLeaf attributes  and class Petiole
#ifndef BROADLEAF_H
#define BROADLEAF_H

#include <Point.h>
#include <PositionVector.h>
#include <Ellipse.h>
#include <LGMdecl.h>

namespace Lignum{

using namespace cxxadt;

///\brief Petiole consists of start and end points 
class Petiole{
  friend Point GetStartPoint(const Petiole& p);
  friend Point GetEndPoint(const Petiole& p);
  friend void SetStartPoint(Petiole& p, const Point& pnt);
  friend void SetEndPoint(Petiole& p, const Point& pnt);
  friend PositionVector GetDirection(const Petiole& p);
public:
  Petiole(const Petiole& p)
    :begin(p.begin),end(p.end){}
  Petiole(const Point& begin, const Point& end);
  void setBegin(const Point& b) {begin = b;}
  void setEnd(const Point& e) {end = e;}
  Point getBegin() {return begin;}
  Point getEnd() {return end;}

private:
  Point begin;///< Petiole start point
  Point end; ///< Petiole end point
};

///\brief Broad leaf attributes.
///
///Broad leaf attributes for metabolic processes, petiole and leaf shape
///\tparam SHAPE Leaf shape 
template <class SHAPE>
class BroadLeafAttributes{
public:
  BroadLeafAttributes(const BroadLeafAttributes& bla);
  BroadLeafAttributes(double sf1,double tauL1,double dof1, const Petiole& petiole1, const SHAPE& shape1, 
		      int number_of_sectors);
  double degree_of_filling; ///< The real leaf is only  part of the shape
  double sf;                ///< Specific leaf area
  double tauL;              ///< Transmission coefficient
  KGC P;                    ///< Photosynthetic production
  KGC M;                    ///< Respiration 
  KGC Qin;                  ///< Incoming radiation
  KGC Qabs;                 ///< Absorbed radiation
  Petiole petiole;          ///< Leaf is at the end of petiole in 3D space
  ///The form  of the  leaf as template SHAPE
  ///\sa  cxxadt::Triangle  cxxadt::Ellipse cxxadt::Kite 
  SHAPE shape;              
  ///Vector for shading calculations
  ///The length of the vector \p sv == number of sky::Firmament sectors
  ///\note The vector \p sv must be synchronized with sky::Firmament sectors
  vector<LGMdouble>  sv; 
};

///\brief Leaf model.
///
///Leaf model for broadleaved trees.
///\tparam SHAPE Leaf shape \sa cxxadt::Ellipse cxxadt::Triangle cxxadt::Kite
template <class SHAPE>
class BroadLeaf{
  ///\brief Get one of named attribute values
  ///\param bl The broadleaf
  ///\param name The parameter name
  ///\return Value of the named attribute
  ///\note The name LGAA returns true leaf area \f$\mathrm{A_{leaf}}\f$ that is
  ///based on the area of the geometric leaf \e shape and the degree of filling (\e dof):
  ///\f$\mathrm{A_{leaf} = A_{shape}\times dof}\f$. If \e dof is 1 then leaf area
  ///equals the area of the geometric shape of the leaf. The value of \f$\mathrm{dof \in [0,1]}\f$.
  template <class S>
  friend LGMdouble GetValue(const BroadLeaf<S>& bl, const LGMAD name);
  ///\brief Set one of named attribute values
  ///\param bl The broadleaf
  ///\param name The parameter name
  ///\param value Value of the parameter \p name
  ///\return Previous value of the parameter \p name
  template <class S>
  friend LGMdouble SetValue(BroadLeaf<S>& bl, const LGMAD name, 
			    const LGMdouble value);
  ///\brief Leaf center point
  ///\param bl Leaf
  ///\return Center point of the shaoe \p S
  template <class S>
  friend const Point GetCenterPoint(const BroadLeaf<S>& bl);
  ///\brief Set new center point of the shape \p S
  ///\tparam S Leaf shape
  ///\param bl Leaf
  ///\param p New center point
  template <class S>
  friend void SetCenterPoint(BroadLeaf<S>& bl, const Point& p);

  ///\brief Get normal vector of the shape \p S
  ///\tparam S Leaf shape
  ///\param bl Leaf
  ///return Normal vector of the shape \p S
  template <class S>
  friend const PositionVector GetLeafNormal(const BroadLeaf<S>& bl);

  ///\brief Get leaf petiole
  ///\param bl Leaf
  ///\return Leaf petiole
  template <class S>
  friend const Petiole& GetPetiole(const BroadLeaf<S>& bl);

  ///\brief Get the geometric leaf shape
  ///\tparam S Leaf shape
  ///\param bl Leaf
  ///\return The geometric leaf shape type \p S
  template <class S>
  friend const S& GetShape(const BroadLeaf<S>& bl);

  ///\brief Get the vector for shading calculations
  ///\param bl Leaf
  ///\retval BroadLeafAttributes::sv Vector for shading calculations
  template <class S>
  friend const vector<double>& GetRadiationVector(const BroadLeaf<S>& bl);

  ///\brief Copy the content of \p v to BroadLeafAttributes::sv
  ///\param bl Leaf
  ///\param v Vector of new shading values
  template <class S>
  friend void SetRadiationVector(BroadLeaf<S>& bl, const vector<LGMdouble>& v);

  ///\brief Translate leaf.
  ///
  ///Translates BroadLeaf as specified by vector \p t, leaf orientation not changed
  ///Vector \p t is added to all positions, including Petiole.
  ///\param bl Leaf
  ///\param t Vector defining direction and magnitude of the movement
  template <class S>
  friend void TranslateLeaf(BroadLeaf<S>& bl, const PositionVector& t);

  ///\brief Set new leaf position
  ///
  ///Move the leaf from its current position to the position where
  ///the starting point of the petiole is \p p.
  ///\post Leaf orientation does not change
  ///\sa TranslateLeaf
  template <class S>
  friend void SetLeafPosition(BroadLeaf<S>& bl, const Point& p);

  ///\brief Roll leaf as the Turtle::roll()
  ///\param bl Leaf
  ///\param angle Roll angle in radians
  template <class S>
  friend void Roll(BroadLeaf<S>& bl, const double& angle);

  ///\brief Pitch leaf as the Turtle::pitch()
  ///\param bl Leaf
  ///\param angle Pitch angle in radians
  template <class S>
  friend void Pitch(BroadLeaf<S>& bl, const double& angle);

  ///\brief Turn leaf as the Turtle::turn()
  ///\param bl Leaf
  ///\param angle Turn angle in radians
  template <class S>
  friend void Turn(BroadLeaf<S>& bl, const double& angle);

/*   This friend function uses the same logic (add a vector, i.e. Point) */
/*   as MoveTree in TreeFunctor.h (stl-lignum) */
/*   This friend function is used by MoveHwTree */
/*   template <class S> */
/*     friend void Move(BroadLeaf<S>& bl, const Point& mov) { */
/*     Point tmp = (bla.petiole).getBegin() + mov; */
/*     bla.petiole.setBegin(tmp); */
/*     tmp  = (bla.petiole).getEnd() + mov; */
/*     bla.petiole.setEnd(tmp); */
/*     (bla.shape).move(mov); */
/*   } */


public:
  BroadLeaf(LGMdouble sf,LGMdouble tauL,LGMdouble dof,int number_of_sectors,
	    const Petiole& petiole,const SHAPE& shape);
  BroadLeaf(const SHAPE& shape, const Petiole& petiole);
  BroadLeaf(const  SHAPE& shape, const Petiole& petiole, int sky_sectors);
  BroadLeaf(const BroadLeaf& bl):bla(bl.bla) {}
  void photosynthesis(const LGMdouble& p0);
  void move(const Point& mov) {
    Point tmp = (bla.petiole).getBegin() + mov;
    bla.petiole.setBegin(tmp);
    tmp = (bla.petiole).getEnd() + mov;
    bla.petiole.setEnd(tmp);
    bla.shape.move(mov);
  }
  //This is analogous to rotate of PositionVector
  //Rotation about an arbitrary axis in space according to
  //Rogers&Adams: mathematical Elements for Computer Graphics p. 121-128
  void rotate(const Point& p, const PositionVector& ra,
	      const LGMdouble& an) {
  Point pos = bla.petiole.getBegin();
  PositionVector pv(p);
  pv.rotate(p,ra,an);
  bla.petiole.setBegin(Point(pv));

  pos = bla.petiole.getEnd();
  pv = PositionVector(p);
  pv.rotate(p,ra,an);
  bla.petiole.setEnd(Point(pv));

  bla.shape.rotate(p,ra,an);
}


private:
  BroadLeafAttributes<SHAPE> bla;///< Leaf attributes
};


template <class S>
void BroadLeaf<S>::photosynthesis(const LGMdouble& p0)
{

  bla.P = p0 * bla.Qabs;
}




}//closing namespace Lignum 

#endif

#include <BroadLeafI.h>


