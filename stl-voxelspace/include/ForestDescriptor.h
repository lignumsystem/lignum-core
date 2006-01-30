#ifndef FOREST_DESCRIPTOR_H
#define FOREST_DESCRIPTOR_H

#include <LGMSymbols.h>
using namespace Lignum;


//ForestDescriptor collects descriptive statistics and indices for the
//forest in the voxel space. The natural place to insert data 
class ForestDescriptor{
  friend double SetValue(ForestDescriptor& fd, LGMAD name, double value);
  friend double GetValue(ForestDescriptor& fd, LGMAD name);
public:
  ForestDescriptor():af(0.0),lai(0.0),cbase(R_HUGE){}
  //update LAI, A is the area of the voxel space in  meters
  double updateLAI(double A){lai = af/A;}//call after the last call to InsertVoxelObject
  void reset(){af=0.0,lai=0.0,cbase=R_HUGE;}//Reset by VoxelSpace::reset()
private:
  double af;//needle area
  double lai;//leaf area index for coniferous
  double cbase;//lower limit  for tree crowns (defined  as the smallest
	      //z-coord of all segments that have foliage)
};

inline double SetValue(ForestDescriptor& fd, LGMAD name, double value)
{
  double val = GetValue(fd,name);
  if (name == LGAAf){
    fd.af = value;
  }
  //The lowest segment having foliage
  else if (name == LGAcbase){
    if (value < fd.cbase)
      fd.cbase = value;
  }
  else{
    cerr << "ForestDescriptor SetValue Unknown name " << name <<endl;
    cerr << "Returning " << val <<endl;
  }

  return val;
}
    
inline double GetValue(ForestDescriptor& fd, LGMAD name)
{
  if (name == LGAAf){
    return fd.af;
  }
  else if (name == LGAcbase){
    return fd.cbase;
  }
  else if (name == LGAlai){
    return fd.lai;
  }
  else{
    cerr << "ForestDescriptor GetValue Unknown name " << name << endl;
    cerr << "Returning " << 0.0 <<endl;
  }
  return 0.0;
}
    

#endif
