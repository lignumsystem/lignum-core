/// \file interlen.h
/// \brief Line-voxel intersection length
#ifndef _INTERLEN_H_
#define _INTERLEN_H_

#include <PositionVector.h>

using namespace cxxadt;


int startvoxel(float a, float b);

///\brief Line-voxel intersection
///
///InterLen reports line-voxel intersection length
///for each voxel a line intersects.
///
///Parameters v and w specify line end points. 
///A voxel (v1, v2, v3) confines all such locations (x1, x2, x3) for
///which vi <= xi < vi + 1, i = 1, 2, 3.  For each intersection
///functor setLen is called with voxel coordinates and 
///voxel coordinates and intersection length. This is really a
///wrapper of InterLen constructor. 
///\note This class exists only to allow the members funtions to share
///common data.
template<class T>
class InterLen
{

public:
	//template<class T>
    InterLen(T& setLen, PositionVector &v, PositionVector &w);
	//template<class T>
    void step(T& setLen, float delta, float ydelta, float zdelta);
	//template<class T>
    void interLen(T& setLen, const PositionVector& v, const PositionVector& w);

private:
	PositionVector vox, ux, uy, uz;  //nama tyyppia int
	float yfactor, zfactor, ypos, zpos;
};




template<class T>
InterLen<T>::InterLen(T& setLen, PositionVector &v, PositionVector &w)
{
  PositionVector d = w - v;

  // -- record start voxel's coordinates
  vox = PositionVector((int)(startvoxel(v.getX(), w.getX())),
						(int)(startvoxel(v.getY(), w.getY())),
						(int)(startvoxel(v.getZ(), w.getZ())));
		
 

  // -- find main direction
  int n;
  if(fabs(d.getX()) > fabs(d.getY()) && fabs(d.getX()) > fabs(d.getZ())) 
	  n = 0;
  else if(fabs(d.getY()) > fabs(d.getZ())) 
	  n = 1;
  else 
	  n = 2;

  for(int i=0; i<n; i++)
    {
      v = PositionVector(v.getY(), v.getZ(), v.getX());
      w = PositionVector(w.getY(), w.getZ(), w.getX());
      d = PositionVector(d.getY(), d.getZ(), d.getX());
    }

  
  ux = PositionVector(1,0,0);
  uy = PositionVector(0,1,0);
  uz = PositionVector(0,0,1);

  for(int i=0; i<n; i++)
  {
	  ux = PositionVector(ux.getZ(), ux.getX(), ux.getY());
	  uy = PositionVector(uy.getZ(), uy.getX(), uy.getY());
	  uz = PositionVector(uz.getZ(), uz.getX(), uz.getY());

  }

  if(d.getX() == 0) return; // zero length

  // -- find axial directions

  if(d.getX() < 0) 
  { 
	  v = PositionVector(-v.getX(), v.getY(), v.getZ());
	  w = PositionVector(-w.getX(), w.getY(), w.getZ());
	  d = PositionVector(-d.getX(), d.getY(), d.getZ());
	 
	  ux *= -1; 
  }
  if(d.getY() < 0) 
  { 
	  v = PositionVector(v.getX(), -v.getY(), v.getZ());
	  w = PositionVector(w.getX(), -w.getY(), w.getZ());
	  d = PositionVector(d.getX(), -d.getY(), d.getZ());
	  uy *= -1; 
  }
  if(d.getZ() < 0) 
  { 
	  v = PositionVector(v.getX(), v.getY(), -v.getZ());
	  w = PositionVector(w.getX(), w.getY(), -w.getZ());
	  d = PositionVector(d.getX(), d.getY(), -d.getZ());
	  uz *= -1; 
  }

  // -- find traversal parameters

  ypos = v.getY() - floorf(v.getY()) - 1.0;
  zpos = v.getZ() - floorf(v.getZ()) - 1.0;

  yfactor = d.length()/d.getY();
  zfactor = d.length()/d.getZ();

  // -- go through line

  if(ceilf(w.getX()) - floorf(v.getX()) > 1.0 ) 
  { // multiple voxels

    PositionVector inc(1, d.getY()/d.getX(), d.getZ()/d.getX()); // voxel coordinates delta

    PositionVector startinc = ((float)1.0 - (v.getX() - floorf(v.getX())))*inc;
    step(setLen, startinc.length(), startinc.getY(), startinc.getZ());

    for(int i = floorf(v.getX()) + 1.0; i < ceilf(w.getX()) - 1.0; i++)
      step(setLen, inc.length(), inc.getY(), inc.getZ());

    PositionVector endinc = ((float)1.0 - (ceilf(w.getX()) - w.getX()))*inc;
    step(setLen, endinc.length(), endinc.getY(), endinc.getZ());
  }
  else
    step(setLen, d.length(), d.getY(), d.getZ());
}




template<class T>
void InterLen<T>::step(T& setLen, float lendelta, float ydelta, float zdelta)
{
  float ylen, zlen;

  ypos += ydelta;
  zpos += zdelta;

  

  if (vox.getX() >1 || vox.getY() >1 || vox.getZ() >1)
  {
    //int a=1;
  }

  if(ypos >= 0 && zpos >= 0) { // go over y- and z-planes
    ylen = yfactor*ypos;
    zlen = zfactor*zpos;
    if(ylen > zlen) 
	{
		
	  setLen(vox, lendelta - ylen); // y-plane first
      vox += uy;
	  if (vox.getX() >1 || vox.getY() >1 || vox.getZ() >1)
	    //int a=1;
	
      setLen(vox, ylen - zlen);
      vox += uz;
	  if (vox.getX() >1 || vox.getY() >1 || vox.getZ() >1)
	    //int a=1;
      setLen(vox, zlen);
    }
    else {
      setLen(vox, lendelta - zlen); // z-plane first
      vox += uz;
      
      setLen(vox, zlen - ylen);
      vox += uy;

      setLen(vox, ylen);
    }
    ypos -= 1.0;
    zpos -= 1.0;
  }
  else if(ypos >= 0) { // go over y-plane
    ylen = yfactor*ypos;
    setLen(vox, lendelta - ylen);
    vox += uy;

    setLen(vox, ylen);
    ypos -= 1.0;
  }
  else if(zpos >= 0) { // go over z-plane
    zlen = zfactor*zpos;
    setLen(vox, lendelta - zlen);
    vox += uz;

    setLen(vox, zlen);
    zpos -= 1.0;
  }
  else // don't go over y- or z-planes
    setLen(vox, lendelta);

  vox += ux;
 
}


template<class T>
void interLen(T& setLen, const PositionVector& v, const PositionVector& w)
{
  PositionVector v1(v);
  PositionVector w1(w);
  InterLen<T>(setLen,v1,w1);
}

  
#endif
