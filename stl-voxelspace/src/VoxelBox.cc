#include "stdafx.h"

#include <VoxelBox.h>
#include <VoxelSpace.h>

namespace Lignum {
//
//	Constructor of the class VoxelBox
//
VoxelBox::VoxelBox(VoxelSpace *s)
{ 
	space = s; 
	init();
}


//
//	Default constructor of the class VoxelBox
//
VoxelBox::VoxelBox()
{ 
	space = NULL; 
	init();
}

void VoxelBox::init()
{ 
	space = NULL; 
	needleArea = 0.0;
	leafArea = 0.0;
	Q_in = 0.0;
	Q_abs = 0.0;
	star = 0.0;
	starSum = 0.0;
	needleMass = 0.0;

	number_of_segments = 0;
	interceptedRadiation = 0.0;
}


//
//	VoxelSpace and the corner point corner1 given with
//	function setVoxelSpace.
//
void VoxelBox::setVoxelSpace(VoxelSpace *s, Point c)
{ 
	space = s; 
	corner1 = c;

	UpdateValues();
}



//
//	Updates  the values after  every tree  segment being  added to
//	this VoxelBox. 
//
//NOTE: k_b is hard coded  to 0.5, STAR to 0.14 and val_b to 0.14!!!!!!!!
void VoxelBox::UpdateValues()
{
	LGMassert(space->Xbox>0);
	LGMassert(space->Ybox>0);
	LGMassert(space->Zbox>0);

	star = 0.0;
	if (number_of_segments > 0)
		star = starSum / number_of_segments;

	k_b = 0.5;
	star = 0.14; //FOR NEEDLES
	//DO NOT FORGET TO RESET!!!
	val_c = star * (needleArea / (space->Xbox * space->Ybox * space->Zbox));
	//val_b = k_b * (leafArea / (space->Xbox * space->Ybox * space->Zbox));
	val_b = 0.0;        //FOR TESTING ONLY!!!!

}




//
//	Returns the extinction of the light traveling distance l inside
//	this VoxelBox.
//
LGMdouble VoxelBox::extinction(LGMdouble l)
{
  //val_c conifers, val_b broad-leaves  
  double tmp = -val_c*l - val_b*l;
  return exp(tmp);
}





//
//	With this function the needle and leaf area can be set
//  absolutely 
//
void VoxelBox::setArea(M2 larea, M2 narea)
{
	needleArea = narea;
	leafArea = larea;
	UpdateValues();
}


//
//	return the boolean value  whether or not the VoxelBox contains
//	any foliage. This assumes starSum is computed and indeed has a
//	value!!!!
//
bool VoxelBox::isEmpty()
{
	
	return (starSum==0); // && leafArea==0);
}



//
//	Adds the incoming radiation
//
void VoxelBox::addRadiation(LGMdouble r)
{
	Q_in += r;
}



//
//	returns the center point of the VoxelBox
//
Point& VoxelBox::getCenterPoint(Point &point)
{
	point = corner1 + Point(space->Xbox/2.0, space->Ybox/2.0, space->Zbox/2.0);
	return point;
}




//
// Returns the corner point of the VoxelBox
//
Point VoxelBox::getCornerPoint()
{
	return corner1;
}




//
// returns the area density of the VoxelBox
//
LGMdouble VoxelBox::getAreaDen()
{
	UpdateValues();
	return star + val_b;
}




//
//
//
LGMdouble VoxelBox::SAc(LGMdouble phi, LGMdouble r, LGMdouble l)
{
  return 2 * l * cos(phi) * r + PI_VALUE * r * r * sin(phi);
}





//
//
//
LGMdouble VoxelBox::S(LGMdouble phi, LGMdouble Sf, LGMdouble Wf, LGMdouble r, LGMdouble l)
{
  
	
	if (Sf * Wf == 0)
		return 0;
	if (SAc(phi, r, l) == 0)
		return 0;
	
	return SAc(phi, r, l)*(1 - exp(-K(phi)*Sf*Wf/SAc(phi, r, l)))/(Sf*Wf);
}






//
//
//
LGMdouble VoxelBox::K(LGMdouble phi)
{
  LGMdouble inclination;

  inclination = phi * 180 / PI_VALUE;

  if (inclination <= 9.9)
    return 0.23;
  if (inclination <= 19.9)
    return 0.215;
  if (inclination <= 29.9)
    return 0.2;
  if (inclination <= 39.9)
    return 0.19;
  if (inclination <= 49.9)
    return 0.18;
  if (inclination <= 59.9)
    return 0.172;
  if (inclination <= 69.9)
    return 0.168;
  if (inclination <= 79.9)
    return 0.170;
  if (inclination <= 90)
    return 0.184;
  
  return 0;
}





ostream& operator << (ostream& os, VoxelBox &b)
{
  //os << "Qabs(Intercepted ratiation)" <<  "    Qin " << "     star " << "   needleArea " << "     leafArea " << endl;
	
  os << "Qabs: " <<  b.Q_abs << " Q_in: " << b.Q_in 
     << " star: " << b.star << " needleArea: " << b.needleArea 
     << " leafArea: " << b.leafArea << " : ";
	
	return os;
}



}  //namespace Lignum


