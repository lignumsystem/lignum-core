#ifndef VOXELBOXI_H
#define VOXELBOXI_H

namespace Lignum {


//
//	Dumps a conifer segment to the VoxelBox given as a parameter.
//	Updates also the star value
//
template <class TS,class BUD>
void DumpCfSegmentFoliage(VoxelBox &b, const CfTreeSegment<TS,BUD>& ts,
                          int num_parts)
{
    LGMdouble fmass = GetValue(ts, LGAWf);

    //LGMdouble r_f = GetValue(ts, LGARf);
    LGMdouble lenght = GetValue(ts, LGAL);

    LGMdouble farea = GetValue(ts, LGAAf);
    b.addNeedleArea(farea/(double)num_parts);
    b.addNeedleMass(fmass/(double)num_parts);

    vector<LGMdouble> starDirectional(8);
    LGMdouble needle_rad = GetValue(ts, LGARf);
    LGMdouble S_f;
    LGMdouble weight;
    if(fmass > R_EPSILON)
        S_f = farea/fmass;
    else
        S_f = 28.0;

    LGMdouble starS = 0.0;
    //This for loop is executed 8 times!!!!
    for (double phi=0; phi<PI_VALUE/2.0; phi+=PI_VALUE/16)
    {
        starS += b.S(phi, S_f, fmass, needle_rad, lenght);
    }


    starS /= 8.0;
    b.addStarSum(starS * farea/(double)num_parts);  //Note: weighted by needle area
    //of the part of seg that is in question.
    b.addWeight(farea/(double)num_parts);

    b.increaseNumberOfSegments();  //This is a bit problematic with num_parts
    b.addNumberOfSegmentsReal(1.0/(double)num_parts);
    b.addVector((farea/(double)num_parts)*GetDirection(ts));
    //Code added by KV************************************************************************************
    //To get the directions of the shoot and the incident rays. A vector is generated as a result using the
    //function CalcDirectionalStar and stored for the different 8 values.

    weight = farea/(double)num_parts;  // weight is used to get the weighted part of the calulcation
    starDirectional= calcDirectionalStar(b,ts,fmass,lenght,needle_rad,S_f);
    std::transform(starDirectional.begin(),starDirectional.end(),starDirectional.begin(),std::bind1st(std::multiplies<LGMdouble>(),weight));//multiply the vector with the weighted foliage
    //area and use to add up all the vectors
    b.addDirectionalStarSum( starDirectional);
    //********************************************************************************************************
}

// This converts the entire starS to a vector STL class and gives out the vector class.
// Written : K.V.Gopalkrishnan

template <class TS,class BUD>
std::vector<LGMdouble> calcDirectionalStar(VoxelBox &b,const CfTreeSegment<TS,BUD> &ts,
                                           LGMdouble fmass,LGMdouble lenght,LGMdouble needle_rad,
                                           LGMdouble S_f)
{
    LGMdouble newStar=0.0;
    LGMdouble x,y,z;
    LGMdouble a_dot_b;
    LGMdouble inclination;
    vector<LGMdouble>directionalStar(8);
    int counter = 0;

    fmass = 0.00151205;
    lenght = 0.18 ;
    needle_rad = 0.017;
    S_f = 25 ;


    //    ********************************************************************************************************
    //     phi  is the inclination angle of the shoot and theta is the azimuth angle of the incident ray of light.
    //     lets consider inclination going from 0 to PI/2 with increments of PI/14 (gives 8 values in total i.e.
    //     loop runs atleast 8 time  and  then the inclination angles total to 12 ands the loop runs 12 times
    //     that of the azimuth angle goes from 0 to 2*PI with increments of PI/6
    //    ********************************************************************************************************

    for (double phi=0; phi<=PI_VALUE/2.0; phi+=PI_VALUE/14.0)
    {   newStar =0.0;
        for(double theta =0; theta<2*PI_VALUE; theta+= PI_VALUE/6.0)
        {
            //Spherical Coordinates described
            x           = cos(phi)*cos(theta);
            y           = cos(phi)*sin(theta);
            z           = sin(phi);
            // Get the directions of the shoot and that of the incident rays using PositionVectors
            // and GetDirections and calculate the dot product using the Dot function
            a_dot_b     = Dot(GetDirection(ts), PositionVector(x,y,z));
            // inclination angle is calculated with BigPhi = PI/2 - acos(a_dot_b)
            inclination = (PI_VALUE/2.0) - acos(fabs(a_dot_b));
            newStar    += b.S(inclination,S_f,fmass,needle_rad,lenght);

        }
        directionalStar[counter]  = newStar/12.0;
        counter+=1;
    }
    return directionalStar;

}


//  Woody part
//
//    Dumps wood information to the VoxelBox given as a parameter.
//
//
template <class TS,class BUD>
void DumpSegmentWood(VoxelBox &b, const TreeSegment<TS,BUD>& ts,
                     int num_parts)
{
    LGMdouble r = GetValue(ts, LGAR);
    LGMdouble length = GetValue(ts, LGAL) / (double)num_parts;
    LGMdouble mass = GetValue(ts, LGAWood) / (double)num_parts;
    LGMdouble area = 2.0*PI_VALUE*r*length;
    b.addWoodMass(mass);
    b.addWoodArea(area);
}



template <class OBJ>
void InsertVoxelObject(VoxelBox& b, OBJ* obj)
{
    b.objects.push_back(obj);
}

//Dump one leaf of a deciduous tree - corresponds to DumpSegment of
//coniferous segments (CfTreeSegment)

template <class S>
void DumpLeaf(VoxelBox &b, const BroadLeaf<S> &leaf)
{
    LGMdouble xx = GetValue(leaf, LGAA);   //LGAA is defined in LGMSymbols.h
    b.addLeafArea(xx);
    b.addOneLeaf(); //increase the number of leaves by one
    xx = GetValue(leaf, LGAWf);
    b.addLeafMass(xx);

    //The weighted sum of the  leaf normals. Bigger leaf has more to
    //say to  the direction  of the "big  leaf" normal  than smaller
    //leaf
    b.big_leaf_normal=b.big_leaf_normal+GetLeafNormal(leaf)*GetValue(leaf,
                                                                     LGAA);
}


//
//	Calculates the Qabs value to the CfTreeSegment
//
template <class TS,class BUD>
void SetSegmentQabs(VoxelBox &b, CfTreeSegment<TS,BUD>& ts, double num_parts)
{

    LGMdouble S_f = GetValue(GetTree(ts), LGPsf);
    LGMdouble farea = S_f * GetValue(ts, LGAWf) / num_parts;
    LGMdouble qabs = 0.0;

    //Qabs computetd based on Qin, mean star and foliage area.
    qabs = b.getQin()*GetValue(ts,LGAstarm)*(GetValue(GetTree(ts), LGPsf)*GetValue(ts, LGAWf));

    SetValue(ts, LGAQabs, GetValue(ts, LGAQabs)+qabs);
    SetValue(ts, LGAQin, GetValue(ts, LGAQin)+b.getQin()/num_parts);
}



//Accumulate (multiply) the extinctions of the objects in the voxel
class AccumulateObjectExtinction{
public:
    AccumulateObjectExtinction(const Point& point,const PositionVector& direction,
                               const ParametricCurve& Kfun)
        :p0(point),dir(direction),K(Kfun){}
    LGMdouble operator()(LGMdouble tau, VoxelObject* object){
        tau = tau*(object->getExtinction(p0,dir,K));
        return tau;
    }
private:
    const Point& p0;//Start of the light beam
    const PositionVector& dir;//Direction of th light beam
    const ParametricCurve& K;//The extinction function
};

} //namespace Lignum


#endif




