#ifndef BROADLEAF_H
#define BROADLEAF_H
#include <PositionVector.h>
#include <Ellipsis.h>

class Petiole{
public:
  Petiole(const PositionVector& d, const Point& begin, const Point& end);
  PositionVector d;
  Point begin;
  Point end;
};

class BroadLeafAttributes{
public:
  BroadLeafAttributes(double sf1,double tauL1,double dof1, const Petiole& petiole1,
		      const PositionVector& leaf_normal, const Ellipsis& shape1, 
		      double lw, int number_of_sectors);
  double sf;                //specific leaf area
  double tauL;              //transmission coefficient
  double degree_of_filling; //ellipsis covers the form of the maple leaf only partially
  Petiole petiole;          //leaf is at the end of petiole in 3D space
  PositionVector leaf_normal;    //the leaf normal in 3D space
  Ellipsis shape;           //the form of the leaf is modelled as an ellipsis
  Point center;             //the center point of the leaf
  double lw;                 //the leaf weight per m2
  KGC P;                    //photosynthetic production
  KGC M;                    //respiration 
  KGC Qin;                  //incoming radiation
  KGC Qabs;                 //absorbed radiation
  //vector for shading (must be synchronized with firmament)
  vector<double>  sv; //the length of the vector == number of sectors 
};


class BroadLeaf{
public:
  BroadLeaf(double sf,double tauL,double dof, const Petiole& petiole,
	    const PosVector& leaf_normal, const Ellipsis& shape,float lw,
	    int number_of_sectors);
  SQUAREMETER getFoliageArea()const{return bla.shape.getArea();}
  KGC getFoliageMass()const{return bla.lw*getFoliageArea();}
  KGC getQin()const{return bla.Qin;}
  KGC getQabs()const{return bla.Qabs;}
  KGC doPhotosynthesis(float ppf){return bla.P = ppf*bla.Qabs;}
  KGC doRespiration(float frf){return bla.M = (KGC)frf*getFoliageMass();}
  void initsv(){for (int i = 0; i < bla.sv.size(); i++)bla.sv[i] = 1.0;}
  BroadLeafAttributes bla;
};

#endif



