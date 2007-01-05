#ifndef FIRMAMENT_H
#define FIRMAMENT_H

#include <iostream>
#include <fstream>
#include <math.h>
#include <mathsym.h>
#include <vector>
#include <TMatrix.h>
#include <ParametricCurve.h>
#include <LGMUnits.h>

namespace sky{
using namespace Lignum;
using namespace cxxadt;


#define NUM_OF_AZIM 24
#define NUM_OF_INCL 9
/*=====================================================================================*/
//Class Firmament implements the radiation coming from the sky.
//Both direct (=sun) and diffuse radiation is dealt with separately.
//The intensity of both radiation types can be set (by defining intensity of
//direct and diffuse radiation on a horizontal plane).
//Initially (constructor) direct radiation is set to 0 and diffuse radiation is set
// to 1200 MJ/m2 (from the whole sky).  This corresponds to the radiation sum
//(direct+diffuse) during the growing period in southern Finland (Stenberg).
//
// Setting direct radiation to 0 and defining all radiation as diffuse is the way
// to deal with radiation distribution of the sky over a prolonged period.
// If you want to consider momentary values update direct and diffuse radiation
// components according to your needs.
//
//1) Direct radiation: sun's position and the intensity of radiation can be both set
//   and queried. Initially intensity = 0, direction = (0,0,0)
//
//2) Diffuse radiation. The upper hemisphere is divided into sectors in the follwing way:
//  2.1) number of sectors = (number of inclinations)*(number of azimuths) + 1
//  2.2) area of zenith segment of the sphere = 2*PI/numOfSectors => angle of
//       the zenith segment
//  2.3) width of inclination zone = (PI/2 - angle of zenith segment)/(num of incls)
//  2.4) The (number of inclinations)*(number of azimuths) sectors are divided
//       between (number of inclinations)  zones so that all sectors have as equal solid
//       angle (=area on the surface of the unit sphere) as possible. The variable
//       number of azimuths defines the mean number of sectors the inclination
//       zones contain.
//
//  2.5) The radiation coming from each sector is stored as well as the inclinations
//       and azimuths & some other radiation values
//  2.6) The flux of diffuse radiation coming from the sky is 
//      according to J. Ross 1981 The radiation regime and architecture of plant
//      stands, Dr W. Junk Publishers Eq. II.2.4a which defines the zonal brightness
//      of the standard overcast sky. The brigthness is thus changing only with
//      inclination inc according to the following equation:
//      d(inc)=(6/7)*(1 + 2 * sin(inc)) / (2*PI)
//      This formula is scaled so that the irradiance caused by it on the horizontal
//      plane equals one, that is,
//      integral(from 0, to PI/2) d(x) * sin(x) * 2PI*cos(x)*dx = 1
//      (2PI*cos(x) comes from geometry, da = 2PI*cos(inc) on the surface of the unit
//      sphere) If we know the irradiance on the horizontal plane, Q, we have thus the
//      brightness of the sky as Q * d(inc)


//Public methods:
//(see Firmament.cc for more precise definition of input and output of methods)
/*
1.  Firmament(int no_incl = NUM_OF_INCL, int no_azim = NUM_OF_AZIM )
     Arguments: 
     in: 'no_incl', number of sectors dividing the sky horizontally.
         'no_azim', number of sectors dividing the sky vertically.

2.   void setDiffuseRadiation(const double rad)
     Set the diffuse radiation (rad = radiation coming to horiz. plane)

3.   void setDirectRadiation(const double rad)
     Set the direct radiation (rad = radiation coming to horiz. plane)

4.   void setSunPosition(const vector<double>& v)
     v = direction vector

5.   vector<double>  getSunPosition()
     Get the direction vector

6.  MJ directRadiation(vector<double>& direction)
    Get the intensity (on plane perpendicular to direction vector) and
    the direction of the sun

7.  MJ diffuseRadiationSum( const vector<double>& v)
    Get intensity of diffuse radiation (on plane perpendicular to direction vector)
    from sector input v is poining to.

8.  int numberOfRegions()
    Get number of sectors.

9.  MJ diffuseRegionRadiationSum(int n, vector<double>& direction)
    Get intensity of diffuse radiation (on plane perpendicular to direction vector)
    from sector no n (numbering starts from horizont) and direction of the sector.

10.  MJ diffuseHalfRegionRadiationSum(int n, vector<double>& direction)
     As 9 but the other half of the upper hemisphere gives no radiation.

11.  MJ directHalfRegionRadiationSum(vector<double>& direction)
     As 10 but direct radiation

12.  MJ diffusePlaneSensor(void)
     Intensity of diffuse radiation on a horizontal plane.

13.   MJ diffuseBallSensor(void)
       Intensity of diffuse radiation as recorded by a ball sensor.

14.   MJ diffuseForestRegionRadiationSum(int n, float z, float x,  float la, float ke,
                                         float H, float Hc,vector<double>& direction,
                                         double density)
       As 9. but the point where the radiation is coming to is in a forest.
       INPUT:
          n        number of region
	  z        height of the point from ground, m
          x        distance of the point from the tree stem,  m
	  la       needle area (total area) per tree (= sf * Wf),   m2
	  ke       extinction cofficient  (= 0.14 for Scots pine),  unitless
	  H        height of tree (h. of stand),  m
	  Hc       height of the crown base of the tree (stand), m
          density  Density of the stand (trees/ha)
        OUTPUT:
         The annual radiation sum (MJ) from the nth region of the
         firmament as shaded by the neighboring stand
	 direction  the direction of nth region
         If n < 0 or n > total number of regions - 1, return -1.0
        (see comments in program code for more information about this method)

15.  void outDiff()
       Prints out ( cout << ) the diffuse radiation intensity sector by sector.

16.  void outAz() 
      Prints out azimuths of sector mid points in all inclination zones.

17. double getInclination(int n)
      Returns the inclination (readians, 0...PI/2) of sector (middlepoint) n.
      Returns -1.0, if n is out of bounds.

18. double getAzimuth(int n)
      Returns the azimuth (radians, 0...2PI) of sector (middlepoint) n.
      Returns -1.0, if n is out of bounds.

19. int getInclinationIndex(int n)
     Returns the index of inclination of sector n in TMatrix<double> diffuseRad 
     where radiation is stored. Return -1 if n is out of bounds.

20. int getAzimuthIndex(int n)
    As getInclinationIndex but for azimuth.

21. double getSectorArea(int n)
    returns area of sectors in each inclination class
    Returns -1, if n out of bounds.

22. int getNoOfInclinations()
    Returns number of inclination classes.
=====================================================================================
*/

class Firmament{
public:
  Firmament(int no_incl = NUM_OF_INCL/*9*/, int no_azim = NUM_OF_AZIM /*24*/);
  void resize(int no_incl, int no_azim, double diffuse_rad_plane);
  void setDiffuseRadiation(const double rad);
  void setDirectRadiation(const double rad) { directRadPlane = rad; }
  void setSunPosition(const vector<double>& v);
  vector<double>  getSunPosition() { return sunPosition; }
  MJ directRadiation(vector<double>& direction);
  MJ diffuseRadiationSum( const vector<double>& v);
  int numberOfRegions() const { return numOfSectors; }
  MJ diffuseRegionRadiationSum(int n, vector<double>& direction)const;
  MJ diffuseHalfRegionRadiationSum(int n, vector<double>& direction);
  MJ directHalfRegionRadiationSum(vector<double>& direction);
  MJ diffusePlaneSensor(void) { return diffuseRadPlane; }
  MJ diffuseBallSensor(void) { return diffuseRadBall; }
  MJ diffuseForestRegionRadiationSum(int n, float z, float x,  float la, float ke,
				     float H, float Hc,
				     vector<double>& direction,double density);
  void outDiff() {
    cout << diffuseRad << endl;
  }
  void outAz() {
    cout << zoneAzims << endl;
  }
  double getInclination(int n);
  double getAzimuth(int n);
  int getInclinationIndex(int n) {
    if(n < 0 || n > (numOfSectors - 2) )  // numOfSectors - 1 == zenith
      return -1;
    else
      return inclinationIndex[n];
  }

  int getAzimuthIndex(int n) {
    if(n < 0 || n > (numOfSectors - 2) ) // numOfSectors - 1 == zenith
      return -1;
    else
      return azimuthIndex[n];
  }
  double getSectorArea(int n) {
    if(n < 0 || n > num_of_incl - 1)
      return -1.0;
    else
      return areasByInclination[n];
  }
 
  int getAzimDivision(int n)
{
    if(n < 0 || n > num_of_incl - 1)
      return -1;
    else
      return azimDivisions[n];
}
  

  int getNoOfAzimuths() { return num_of_azim; }
  int getNoOfInclinations() { return num_of_incl; }

protected:
  int num_of_incl;
  int num_of_azim;
  double diffuseRadScale;
  MJ directRadPlane, diffuseRadPlane, diffuseRadBall;
  MJ diffuseRadZenith;
  vector<double> sunPosition;

  TMatrix<double> zoneAzims;
  vector<double> inclinations;
  vector<int> azimDivisions;
  TMatrix<double> diffuseRad; //stores the radiation of sectors
  vector<int> inclinationIndex;   //tabulation of index of inclination in
                                   //diffuseRad as a function of running segment no.
  vector<int> azimuthIndex;       //as inclinationIndex but for azimuths;
  vector<double> dir_x;           //x-component of vector pointing to center
                                  //of ith sector (indexed by number of sector)
  vector<double> dir_y;          //as dir_x but for y
  vector<double> dir_z;          //as dir_x but for z
  vector<double> areasByInclination; //areas sectors in for each inclination
  double thetZ;
  int numOfSectors;
  double deltaIncl, halfDeltaIncl;
  double standDensity;
};

}//closing namespace sky
#endif






