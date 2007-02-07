#ifndef VOBOOKKEEPER_H
#define VOBOOKKEEPER_H
#include <vector>
#include <algorithm>
using namespace std;
#include <mathsym.h>
using namespace cxxadt;
class VOBookKeeper{
public:
  VOBookKeeper():tag(0){}
  long_size newTag();//Return a (unique) tag for object
  bool rayHit(long_size tag)const;//Return true if light beam hit (v[tag] == true)
  void setRayHit(long_size tag);//Set v[tag] = true if light beam hit
  void resetVector();//Call before each light beam (v[i] must be false)
  void reset(); //Call  before InsertVoxelObjects  (v.size() ==  0 and
		//tag = 0)
  void init();//Call after InsertVoxelObjects
  void initVector();//Call after InsertVoxelObjects (v.size() == tag
		    //and v[i] == false
private:
  long_size tag;//A tag  for each voxel object. If  two objects denote
		//the same segment, they  have the same tag. Note that
		//we may  have a lot of objects.  long_size is defined
		//in mathsym.h as unsigned long int.
  vector<bool> v;//Vector to mark voxel object computed
};
#endif
