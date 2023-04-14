///\file VOBookKeeper.h
///\brief Helper class for VoxelObject.
///
///Generate unique tags, keep track computed voxel objects.
#ifndef VOBOOKKEEPER_H
#define VOBOOKKEEPER_H
#include <vector>
#include <algorithm>
using namespace std;
#include <mathsym.h>
using namespace cxxadt;

///\brief Helper class in radiation interception computations
class VOBookKeeper{
public:
  VOBookKeeper():tag(0){}
  ///\return a unique tag for object
  long_size newTag();
  ///\return true if light beam hit (i.e. v[tag] == true) else false \sa v
  bool rayHit(long_size tag)const;
  ///Set v[tag] = true if light beam hit
  ///\param tag VoxelObject tag
  void setRayHit(long_size tag);
  ///Reset vector `v` 
  ///\pre Call before each light beam (each v[i] must be false)
  ///\post Each `v[i]` == false \sa v
  void resetVector();
  ///Reset VOBookKeeper
  ///\pre Call  before InsertVoxelObjects
  ///\post (v.size() ==  0 and tag = 0) \sa tag v
  void reset();
  ///\pre Call after InsertVoxelObjects
  ///\post Calls initVector \sa initVector 
  void init();
  ///Call after InsertVoxelObjects
  ///\post v.size() == tag and v[i] == false
  void initVector();
  ///\retval v The vector `v`
  vector<bool>& getVector(){return v;}
private:
  ///A tag  for each voxel object. If  two objects denote
  ///the same segment, they  have the same tag. Note that
  ///we may  have a lot of objects.  long_size is defined
  ///in mathsym.h as unsigned long int.
  long_size tag;
  ///Vector to mark voxel object computed
  vector<bool> v;
};
#endif
