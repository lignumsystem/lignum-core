#ifndef BROADLEAF_H
#define BROADLEAF_H

#include <Point.h>
#include <PositionVector.h>
#include <Ellipse.h>
#include <LGMdecl.h>

namespace Lignum{

using namespace cxxadt;

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
  Point begin;
  Point end;
};

template <class SHAPE>
class BroadLeafAttributes{
public:
  BroadLeafAttributes(const BroadLeafAttributes& bla);
  BroadLeafAttributes(double sf1,double tauL1,double dof1, const Petiole& petiole1, const SHAPE& shape1, 
		      int number_of_sectors);
  double degree_of_filling; //The real leaf is only  part of the shape
  double sf;                //specific leaf area
  double tauL;              //transmission coefficient
  KGC P;                    //photosynthetic production
  KGC M;                    //respiration 
  KGC Qin;                  //incoming radiation
  KGC Qabs;                 //absorbed radiation
  Petiole petiole;          //leaf is at the end of petiole in 3D space
  SHAPE shape;           //the form  of the  leaf is modelled  as some
			 //SHAPE, see e.g Triangle and Ellipse 
  //vector for shading (must be synchronized with firmament)
  vector<LGMdouble>  sv; //the length of the vector == number of sectors 
};

template <class SHAPE>
class BroadLeaf{
  template <class S>
  friend LGMdouble GetValue(const BroadLeaf<S>& bl, const LGMAD name);

  template <class S>
  friend LGMdouble SetValue(BroadLeaf<S>& bl, const LGMAD name, 
			    const LGMdouble value);

  template <class S>
  friend const Point GetCenterPoint(const BroadLeaf<S>& bl);

  template <class S>
  friend void SetCenterPoint(BroadLeaf<S>& bl, const Point& p);

  template <class S>
  friend const PositionVector GetLeafNormal(const BroadLeaf<S>& bl);

  template <class S>
  friend const Petiole& GetPetiole(const BroadLeaf<S>& bl);

  template <class S>
  friend const S& GetShape(const BroadLeaf<S>& bl);

  template <class S>
  friend const vector<double>& GetRadiationVector(const BroadLeaf<S>& bl);

  template <class S>
  friend void SetRadiationVector(BroadLeaf<S>& bl, const vector<LGMdouble>& v);

  template <class S>
  friend void TranslateLeaf(BroadLeaf<S>& bl, const PositionVector& t);

  template <class S>
  friend void SetLeafPosition(BroadLeaf<S>& bl, const Point& p);

  template <class S>
  friend void Roll(BroadLeaf<S>& bl, const double& angle);

  template <class S>
  friend void Pitch(BroadLeaf<S>& bl, const double& angle);

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
private:
  BroadLeafAttributes<SHAPE> bla;
};


template <class S>
void BroadLeaf<S>::photosynthesis(const LGMdouble& p0)
{

  bla.P = p0 * bla.Qabs;
}




}//closing namespace Lignum 

#endif

#include <BroadLeafI.h>


