#ifndef VOXEL_H
#define VOXEL_H

#include <iostream>
#include <Point.h>

//#include "list.h"
//#include <Tree.h>

using namespace cxxadt;

//------------------------------------------------
//
//  Definition for the class Voxel
//
//------------------------------------------------

class Voxel {
public:
	Voxel();

	
  //
  // Functions to handle the private data
  //
  void setMeanSegment() {
    //meansegment.set_x(sumvector.get_x() / sumlength);
    //meansegment.set_y(sumvector.get_y() / sumlength);
    //meansegment.set_z(sumvector.get_z() / sumlength);

	meansegment = Point(sumvector.getX() / sumlength, sumvector.getY() / sumlength, sumvector.getZ() / sumlength);
  };
  Point getMeanSegment() { return meansegment; };

  double getExtinctionCoefficent() { return STAR*areadensity; }

  void setMeanLength(double l) { meanlength = l; };
  double getMeanLength() { return meanlength; };

  void setMeanWoodRadius() { meanwoodradius = sumwoodradius / sumlength; };
  double getMeanWoodRadius() { return meanwoodradius; };

  void setMeanTotalRadius() { meantotalradius = sumtotalradius / sumlength; };
  double getMeanTotalRadius() { return meantotalradius; };

  void addSumWoodRadius(double radius) { sumwoodradius += radius; };
  double getSumWoodRadius() { return sumwoodradius; };

  void addSumTotalRadius(double radius) { sumtotalradius += radius; };
  double getSumTotalRadius() { return sumtotalradius; };

  Point getSumVector() { return sumvector; };
  void addSumVector(const Point& vector) { sumvector += vector; };
  //void addSumVector(const Point& vector);

  double getPartSum() { 
	  return partsum; 
  };
  void addPartSum(double part) { partsum += part; };

  double getSumLength() { return sumlength; };
  void addSumLength(double length) { sumlength += length; };

  double getFoliageMass() { return totalfoliagemass; };
  void addFoliageMass(double mass) { totalfoliagemass += mass; };

  double getFoliageArea() { return foliagearea; };
  void addFoliageArea(double area) { foliagearea += area; };
  void setFoliageArea(double area) { foliagearea = area; };

  double getAreaDensity() { return areadensity; };
  void setAreaDensity(float density) { areadensity = density; };
 
double getSTAR() 
{ 
	return STAR;
};
  void addSTAR(double coeff) { STAR += coeff; }
  void setSTARabsolute(double s) { STAR = s; }

  double getIncomingRadiation() { return incomingradiation; };
  void addIncomingRadiation(double radiation) { 
    incomingradiation += radiation; 
  };
  void setIncomingRadiation(double a) 
  { 
	  incomingradiation = a; 
  }

  double getRadiationSum() { return radiationsum; };
  void addRadiationSum(double radiation) { radiationsum += radiation; };
  void setRadiationSum(double a) { radiationsum = a; }
  
  //List *segments;                // List of the segments in a voxel
  //  List *intersections;           // List of the intersection points

  void printInfo() const {
     //<< "foliageDensity:    " << foliageDensity    << endl
    cout << "sumvector:         " << sumvector
	 << "meansegment:       " << meansegment
	 << "meanlength:        " << meanlength        << endl
	 << "sumwoodradius:     " << sumwoodradius     << endl
	 << "meanwoodradius:    " << meanwoodradius    << endl
	 << "sumtotalradius:    " << sumtotalradius    << endl
	 << "meantotalradius:   " << meantotalradius   << endl
	 << "partsum:           " << partsum           << endl
	 << "sumlegth:          " << sumlength         << endl
	 << "totalfoliagemass:  " << totalfoliagemass  << endl
	 << "foliagearea:       " << foliagearea       << endl
	 << "areadesity:        " << areadensity       << endl
	 << "STAR               " << STAR              << endl
	 << "wabba wobba" << endl
         << "incomingradiation: " << incomingradiation << endl
	 << "radiationsum:      " << radiationsum      << endl;
  }

  void printIncomingRadiation() const {
    cout << incomingradiation;
  }

private:
  //  double foliageDensity;         // Total foliage density in a voxel
  //                                 // (Total foliage volume / voxel volume)
  Point sumvector;               // Sum vector of the segments in a voxel
                                 // (used for getting the mean segment)
  Point meansegment;             // The meansegment of a voxel
  double meanlength;             // Length of the mean segment
  double sumwoodradius;          // Temporary value for mean segment
  double meanwoodradius;         // Radius of the wood mean segment
  double sumtotalradius;         // Temporary value for the mean segment
  double meantotalradius;        // Total radius of the mean segment
  double partsum;                // Sum of segment parts in a voxel
  double sumlength;              // Total length of segment parts in a voxel
  double totalfoliagemass;       // Total mass of foliage in a voxel
  double foliagearea;            // Total area of the foliage
  double areadensity;            // Foliage area density
  double STAR;                   // STAR value for calculating transmission
                                 // traveling path gives the transmission
  double incomingradiation;      // Sum of the incoming radiation in a voxel
  double radiationsum;           // Amount of light absorbed in a voxel
};


//extern void importTree(Tree);
extern void calculateMeanSegment();
//extern void calculateLight(Firmament *, int, int, int);

#endif
