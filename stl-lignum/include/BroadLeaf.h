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
  Petiole(const Point& begin, const Point& end);
private:
  Point begin;
  Point end;
};

template <class SHAPE>
class BroadLeafAttributes{
public:
  BroadLeafAttributes(double sf1,double tauL1,double dof1, const Petiole& petiole1,
		      const PositionVector& leaf_normal, const SHAPE& shape1, 
		      int number_of_sectors);
  double degree_of_filling; //Ellipse covers the form of the maple leaf only partially
  double sf;                //specific leaf area
  double tauL;              //transmission coefficient
  KGC P;                    //photosynthetic production
  KGC M;                    //respiration 
  KGC Qin;                  //incoming radiation
  KGC Qabs;                 //absorbed radiation
  Petiole petiole;          //leaf is at the end of petiole in 3D space
  PositionVector leaf_normal;    //the leaf normal in 3D space
  SHAPE shape;           //the form of the leaf is modelled as an Ellipse
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
  friend Point GetCenterPoint(const BroadLeaf<S>& bl);

  template <class S>
  friend void SetCenterPoint(BroadLeaf<S>& bl, const Point& p);

  template <class S>
  friend PositionVector GetLeafNormal(const BroadLeaf<S>& bl);

  template <class S>
  friend PositionVector SetLeafNormal(BroadLeaf<S>& bl, 
				      const PositionVector& n);
  template <class S>
  friend Petiole& GetPetiole(BroadLeaf<S>& bl);

  template <class S>
  friend S& GetShape(BroadLeaf<S>& bl);

  template <class S>
  friend vector<double> GetRadiationVector(BroadLeaf<S>& bl);

  template <class S>
  friend void SetRadiationVector(BroadLeaf<S>& bl, const vector<LGMdouble>& v);

  template <class S>
  friend void TranslateLeaf(BroadLeaf<S>& bl, const PositionVector& t);

  template <class S>
  friend void SetLeafPosition(BroadLeaf<S>& bl, const Point& p);
public:
  BroadLeaf(LGMdouble sf,LGMdouble tauL,LGMdouble dof,int number_of_sectors,
	    const Petiole& petiole, const PositionVector& leaf_normal,
	    const SHAPE& shape);
  BroadLeaf(const SHAPE& shape, const Petiole& petiole, 
	    const PositionVector& leaf_normal);
  void photosynthesis(const LGMdouble& p0);
private:
  //  void initsv(){for (int i = 0; i < bla.sv.size(); i++)bla.sv[i] = 1.0;}
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


