#ifndef BROADLEAF_H
#define BROADLEAF_H

#include <Point.h>
#include <PositionVector.h>
#include <Ellipsis.h>

#include <LGMdecl.h>

namespace Lignum{

using namespace cxxadt;

class Petiole{
  friend Point<> GetStartPoint(const Petiole& p);
  friend Point<> GetEndPoint(const Petiole& p);
  friend void SetStartPoint(Petiole& p, const Point<>& pnt);
  friend void SetEndPoint(Petiole& p, const Point<>& pnt);
  friend PositionVector GetDirection(const Petiole& p);
public:
  Petiole(const Point<>& begin, const Point<>& end);
private:
  Point<> begin;
  Point<> end;
};

class BroadLeafAttributes{
public:
  BroadLeafAttributes(double sf1,double tauL1,double dof1, const Petiole& petiole1,
		      const PositionVector& leaf_normal, const Ellipsis& shape1, 
		      int number_of_sectors);
  double degree_of_filling; //ellipsis covers the form of the maple leaf only partially
  double sf;                //specific leaf area
  double tauL;              //transmission coefficient
  KGC P;                    //photosynthetic production
  KGC M;                    //respiration 
  KGC Qin;                  //incoming radiation
  KGC Qabs;                 //absorbed radiation
  Petiole petiole;          //leaf is at the end of petiole in 3D space
  PositionVector leaf_normal;    //the leaf normal in 3D space
  Ellipsis shape;           //the form of the leaf is modelled as an ellipsis
  Point<> center;             //the center point of the leaf

  //vector for shading (must be synchronized with firmament)
  vector<LGMdouble>  sv; //the length of the vector == number of sectors 
};

class BroadLeaf{
  friend LGMdouble GetValue(const BroadLeaf& bl, const LGMAD name);
  friend LGMdouble SetValue(BroadLeaf& bl, const LGMAD name, const LGMdouble value);
  friend Point<> GetCenterPoint(const BroadLeaf& bl);
  friend void SetCenterPoint(BroadLeaf& bl, const Point<>& p);
  friend PositionVector GetLeafNormal(const BroadLeaf& bl);
  friend Petiole& GetPetiole(BroadLeaf& bl);
  friend Ellipsis& GetEllipsis(BroadLeaf& bl);
  friend vector<double> GetRadiationVector(BroadLeaf& bl);
  friend void SetRadiationVector(BroadLeaf& bl, const vector<LGMdouble>& v);
  friend void TranslateLeaf(BroadLeaf& bl, const PositionVector& t);
  friend void SetLeafPosition(BroadLeaf& bl, const Point<>& p);
public:
  BroadLeaf(LGMdouble sf,LGMdouble tauL,LGMdouble dof,int number_of_sectors,
	    const Petiole& petiole, const PositionVector& leaf_normal,
	    const Ellipsis& shape);
  void photosynthesis(const LGMdouble& p0);
private:
  //  void initsv(){for (int i = 0; i < bla.sv.size(); i++)bla.sv[i] = 1.0;}
  BroadLeafAttributes bla;
};


}//closing namespace Lignum 

#endif



