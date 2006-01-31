#ifndef FOREST_DESCRIPTOR_H
#define FOREST_DESCRIPTOR_H

#include <LGMSymbols.h>
using namespace Lignum;


//ForestDescriptor collects descriptive statistics and indices for the
//forest in the voxel space. The natural place to insert data 
class ForestDescriptor{
  friend double SetValue(ForestDescriptor& fd, LGMAD name, double value);
  friend double GetValue(const ForestDescriptor& fd, LGMAD name);
public:
  ForestDescriptor()
    :afb(0.0),afc(0.0),laib(0.0),laic(0.0),h(-1.0),cbase(R_HUGE){}
  //Update LAI, A is the area of the voxel space in  meters
  //Call after  the last call to InsertVoxelObjects
  double updateLAI(double A){laic = afc/A;laib = afb/A;}
  //Reset by VoxelSpace::reset()
  void reset(){
    afb=0.0;afc=0.0;laib=0.0;
    laic=0.0;h=-1.0;cbase=R_HUGE;
  }
private:
  double afb;//leaf area, broad leaved
  double afc;//needle area, conifers
  double laib;//leaf area index for broad leaved
  double laic;//leaf area index for conifers
  double h;//height of the tallest tree 
  double cbase;//lower limit  for tree crowns (defined  as the smallest
	      //z-coord of all segments that have foliage)
};

inline double SetValue(ForestDescriptor& fd, LGMAD name, double value)
{
  double val = GetValue(fd,name);
  if (name == LGAAfb){
    fd.afb = value;
  }
  if (name == LGAAfc){
    fd.afc = value;
  }
  //The lowest segment having foliage
  else if (name == LGAcbase){
    if (value < fd.cbase)
      fd.cbase = value;
  }
   else if (name == LGAH){
    if (value > fd.h)
      fd.h = value;
  }
  else{
    cerr << "ForestDescriptor SetValue Unknown name " << name <<endl;
    cerr << "Returning " << val <<endl;
  }

  return val;
}
    
inline double GetValue(const ForestDescriptor& fd, LGMAD name)
{
  if (name == LGAAfb){
    return fd.afb;
  }
  if (name == LGAAfc){
    return fd.afc;
  }
  else if (name == LGAcbase){
    return fd.cbase;
  }
  else if (name == LGAH){
    return fd.h;
  }
  else if (name == LGALAIb){
    return fd.laib;
  }
  else if (name == LGALAIc){
    return fd.laic;
  }
  else{
    cerr << "ForestDescriptor GetValue Unknown name " << name << endl;
    cerr << "Returning " << 0.0 <<endl;
  }
  return 0.0;
}
    

#endif
