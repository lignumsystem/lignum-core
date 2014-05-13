#include "stdafx.h"

#include <VoxelBox.h>
#include <VoxelSpace.h>

namespace Lignum {
//
//      Constructor of the class VoxelBox
//
VoxelBox::VoxelBox(VoxelSpace *s):
    needleArea(0.0),leafArea(0.0), Q_in(0.0), Q_abs(0.0), Qin_mean(0.0),Qabs_mean(0.0),star(0.0),
    starSum(0.0),weight(0.0),Q_inStdDiffuse(0.0),interceptedRadiation(0.0),
    needleMass(0.0),leafMass(0.0),number_of_segments(0),number_of_leaves(0),
    big_leaf_normal(0,0,0),val_c(0.0),val_b(0.0),woodMass(0.0),woodArea(0.0),
    number_of_segments_real(0.0),starDirSum(7,0.0),starDir(7,0.0)
{
    space = s;
}


//
//      Default constructor of the class VoxelBox
//
VoxelBox::VoxelBox():
    needleArea(0.0),leafArea(0.0),Q_in(0.0),Q_abs(0.0),Qin_mean(0.0),Qabs_mean(0.0),star(0.0),
    starSum(0.0),weight(0.0),Q_inStdDiffuse(0.0),interceptedRadiation(0.0),
    needleMass(0.0), leafMass(0.0),number_of_segments(0),number_of_leaves(0),
    big_leaf_normal(0,0,0),val_c(0.0),val_b(0.0),woodMass(0.0),woodArea(0.0),
    number_of_segments_real(0.0), starDirSum(7,0.0),starDir(7,0.0)
{
    space = NULL;
}

void VoxelBox::reset()
{
    resetQinQabs();
    resetCfData();
    resetHwData();
    //clear the vector elements, i.e object wrappers
    vector<VoxelObject*>::iterator it;
    for (it = objects.begin(); it != objects.end(); it++){
        delete *it;//delete wrapper
    }
    objects.clear();

    woodMass = 0.0;
    woodArea = 0.0;
}

void VoxelBox::init()
{ 
    needleArea = 0.0;
    leafArea = 0.0;
    Q_in = 0.0;
    Q_abs = 0.0;
    Qin_mean = 0.0;
    Qabs_mean = 0.0;
    star = 0.0;
    starSum = 0.0;
    needleMass = 0.0;
    starDir[0] = 0.0;
    starDir[1] = 0.0;
    starDir[2] = 0.0;
    starDir[3] = 0.0;
    starDir[4] = 0.0;
    starDir[5] = 0.0;
    starDir[6] = 0.0;


    starDirSum[0] = 0.0;
    starDirSum[1] = 0.0;
    starDirSum[2] = 0.0;
    starDirSum[3] = 0.0;
    starDirSum[4] = 0.0;
    starDirSum[5] = 0.0;
    starDirSum[6] = 0.0;


    number_of_segments = 0;
    number_of_leaves = 0;
    interceptedRadiation = 0.0;
    weight = 0.0;
    objects.clear();
    big_leaf_normal = PositionVector(0,0,0);

    needleArea = 0.0;
    leafArea = 0.0;
    Q_in = 0.0;
    Q_abs = 0.0;
    Qin_mean = 0.0;
    Qabs_mean = 0.0;
    star = 0.0;
    starSum = 0.0;
    needleMass = 0.0;

    number_of_segments = 0;
    number_of_leaves = 0;
    interceptedRadiation = 0.0;
    weight = 0.0;
    objects.clear();
    big_leaf_normal = PositionVector(0,0,0);
}


//
//      VoxelSpace and the corner point corner1 given with
//      function setVoxelSpace.
//
void VoxelBox::setVoxelSpace(VoxelSpace *s, Point c)
{ 
    space = s;
    corner1 = c;

    //    updateValues();
}


//
//      Updates  the values after  every tree  segment being  added to
//      this VoxelBox. 
//
void VoxelBox::updateValues()
{


    LGMassert(space->Xbox>0);
    LGMassert(space->Ybox>0);
    LGMassert(space->Zbox>0);

    star = 0.0;


    //Check DumpScotsPineSegment (or any DumpCfSegment) that there
    //the star mean is weighted  with foliage area of the segment:
    //e.g. b.addStarSum(GetValue(ts,LGAstarm)*farea);
    if (number_of_segments_real > 0.0){
        if (weight > 0.0)
        //weighted star mean
         star = starSum / weight;

        else
     {
            star = 0.0;
           }

    }

    //It might be good enough to use star 0.14
    //star = 0.14;
    LGMdouble k_b = GetValue(*space,LGAkb);


    //star  for needles


    val_c = star * (needleArea / (space->Xbox * space->Ybox *space->Zbox));
    val_b = k_b * (leafArea / (space->Xbox * space->Ybox * space->Zbox));

    //Note that mean_direction is not normalized
    //      if(mean_direction.length() > R_EPSILON)
    //        mean_direction.normalize();
    //      else
    //        mean_direction = PositionVector(0.0,0.0,1.0);    //arbitrary direction

    updateValuesDirectionalStar();

   // for (int i= 0;i<=6;i++){cout<<" starDir in update "<<starDir[i]<<endl;}exit(0);
}




//*********************************************************************************************************



void VoxelBox::updateValuesDirectionalStar()
{

    vector<LGMdouble> wtsum(7,0.0);
    LGMdouble coeff;

    if (number_of_segments_real > 0.0){
      if (weight > 0.0)
        {
	  coeff = 1/getWeight();
	  wtsum = starDirSum;
	  std::transform(wtsum.begin(),wtsum.end(),starDir.begin(),std::bind1st(std::multiplies<LGMdouble>(),coeff));
        }
      else
        {
	  starDir[0] = 0.0;
	  starDir[1] = 0.0;
	  starDir[2] = 0.0;
	  starDir[3] = 0.0;
	  starDir[4] = 0.0;
	  starDir[5] = 0.0;
	  starDir[6] = 0.0;
        }

    }

  } // the end of updateValuesDirectionalStar function


////**************************************/***********************************************************************




//*********************************************************************************************************

//      Returns the extinction of the light traveling distance l inside
//      this VoxelBox.
//
LGMdouble VoxelBox::extinction(LGMdouble l)const
{
    //val_c conifers, val_b broad-leaves
    double tmp = -val_c*l - val_b*l;
    return exp(tmp);
}


//
//      With this function the needle and leaf area can be set
//  absolutely 
//
void VoxelBox::setArea(M2 narea, M2 larea)
{
    needleArea = narea;
    leafArea = larea;
    updateValues();
}


//
//      return the boolean value  whether or not the VoxelBox contains
//      any foliage. This assumes starSum is computed and indeed has a
//      value!!!!
//
bool VoxelBox::isEmpty()const
{
    if(needleArea < R_EPSILON && leafArea < R_EPSILON)
        return true;
    else
        return false;
}

//
//      Adds the incoming radiation
//
void VoxelBox::addRadiation(LGMdouble r)
{
    Q_in += r;
}



//
//      returns the center point of the VoxelBox
//
Point VoxelBox::getCenterPoint()const
{
    Point point = corner1 + Point(space->Xbox/2.0, space->Ybox/2.0, space->Zbox/2.0);
    return point;
}


//
// Returns the corner  point (=lower left) of the VoxelBox
//
Point VoxelBox::getCornerPoint()const
{
    return corner1;
}

//
// Returns the upper right corner point of the VoxelBox
//
Point VoxelBox::getUpperRightPoint()const
{
    Point point = corner1 + Point(space->Xbox, space->Ybox, space->Zbox);
    return point;
}

//
// returns the area density of the VoxelBox
//
LGMdouble VoxelBox::getAreaDensity()
{
    updateValues();
    return star + val_b;
}

//Return the  extinction of the objects  in the voxel. p0  and d are
//the start and  the direction of the light  beam respectively. Kfun
//is  the  extinction  function  (as  an inclination  of  the  light
//beam). Checking the  voxel object tag. If the tag  is set to true,
//this means  the beam  has hit the  foliage and  we do not  have to
//(must not!) compute the extinction.
LGMdouble VoxelBox::getExtinction(const Point& p0, const PositionVector& d,
                                  const ParametricCurve& Kfun)const
{
    // I could  use accumulate, but I  want to collect  data and break
    // the computation if wood hit
    double tau = 1.0;
    vector<VoxelObject*>::const_iterator it;
    for (it=objects.begin(); it != objects.end(); it++){
        long_size tag = (*it)->getTag();
        bool ray_hit = (space->getBookKeeper()).rayHit(tag);
        if (ray_hit == false){//no ray hit to foliage
            //If  no ray hit yet --> compute
            double tmp_tau = (*it)->getExtinction(p0,d,Kfun);
            //cout << "VoxelBox::getExtinction loop " << tmp_tau << endl;
            if ((*it)->hit_self == true){
                //Ray hits self, mark ray hit. A copy may be in another voxel.
                (space->getBookKeeper()).setRayHit(tag);
                space->hitself = space->hitself + 1;
            }
            if (tmp_tau == 0.0){//wood
                tau = 0.0;
                space->hitw = space->hitw + 1;
                //      cout << "BLOCKED" << endl;
                break;//sector blocked
            }
            else if (tmp_tau == 1.0){//no hit
                space->nohit = space->nohit + 1;
            }
            else{//Foliage hit
                //Mark the segment computed
                (space->getBookKeeper()).setRayHit(tag);
                space->hitfol = space->hitfol + 1;
                tau = tau*tmp_tau;
            }
        }//if (tag == false)
    }
    return tau;
}
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

    os << b.getCornerPoint().getX() << " " << b.getCornerPoint().getY() << " "
       << b.getCornerPoint().getZ() << " " <<  (b.Q_abs > R_EPSILON ? b.Q_abs : 0.0) << " "
       << (b.Q_in > R_EPSILON ? b.Q_in : 0.0) << " " << (b.star > R_EPSILON ?  b.star : 0.0)
       << " " << (b.needleArea > R_EPSILON ? b.needleArea : 0.0)
       << " " << (b.leafArea > R_EPSILON ? b.leafArea : 0.0)
       << " " << (b.woodMass > R_EPSILON ? b.woodMass : 0.0)
       << " " << (b.woodArea > R_EPSILON ? b.woodArea : 0.0);

    return os;
}



}  //namespace Lignum


