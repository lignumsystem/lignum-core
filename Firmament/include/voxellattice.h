#ifndef _VOXELLATTICE_H_
#define _VOXELLATTICE_H_
 
#include "interlen.h"

#include <math.h>
/*****************************************************************************
 * extinction calculation                                                    *
 *****************************************************************************/

/* This class implements functor that can be passed to interLen and
 * its purpose is to calculate extinction of a ray traveling through
 * voxels. */
template<class T> 
class Ext
{
  template <class T1>
  friend float interExt(T1& getExt, double edgelen, const PositionVector& v, 
			const PositionVector& w);
public:
  void operator()(const PositionVector& v, float l) 
  { 
 	  ext += getExt(v)*l; 
  }
  
  
  Ext(T& getExt_) : ext(0), getExt(getExt_) { }
  float ext;
  T& getExt;
};


/* Reports extinction of a ray going throug voxels. The parameter
 * getExt is a functor of type voxel coordinates -> extinction
 * coefficient. */
template<class T> 
float interExt(T& getExt, double edgelen, const PositionVector& v, const PositionVector& w)
{
  Ext<T> e(getExt);
  interLen(e, v, w);
  return exp((double)-e.ext*edgelen);
}



#endif
