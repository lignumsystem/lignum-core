#ifndef BROADLEAF_H
#define BROADLEAF_H

#include <Point.h>
#include <PositionVector.h>
#include <Ellipsis.h>

#include <LGMdecl.h>

class Petiole{
  friend Point<> GetStartPoint(const Petiole& p);
  friend Point<> GetEndPoint(const Petiole& p);
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
		      double lw, int number_of_sectors);
  double degree_of_filling; //ellipsis covers the form of the maple leaf only partially
  double lw;                 //the leaf weight per m2
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
  vector<double>  sv; //the length of the vector == number of sectors 
};


class BroadLeaf{
  friend BLD GetAttributeValue(const BroadLeaf& bl, const BLA name);
  friend BLD SetAttributeValue(BroadLeaf& bl, const BLA name, const BLD value);
  friend Point<> GetCenterPoint(const BroadLeaf& bl);
  friend void SetCenterPoint(BroadLeaf& bl, const Point<>& p);
  friend PositionVector GetLeafNormal(const BroadLeaf& bl);
  friend Petiole& GetPetiole(BroadLeaf& bl);
public:
  BroadLeaf(BLD sf,BLD tauL,BLD dof,BLD lw,int number_of_sectors,
	    const Petiole& petiole, const PositionVector& leaf_normal,
	    const Ellipsis& shape);
private:
  void initsv(){for (int i = 0; i < bla.sv.size(); i++)bla.sv[i] = 1.0;}
  BroadLeafAttributes bla;
};

#endif



