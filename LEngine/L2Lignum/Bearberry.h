#include <Lignum.h>

#ifndef BEARBERRY_H
#define BEARBERRY_H

class BearberrySegment;

class BearberryBud: public Bud<BearberrySegment,BearberryBud>
{
 public:
  BearberryBud(const Point& p, const PositionVector& d, 
	       const LGMdouble omega, 
	       Tree<BearberrySegment,BearberryBud>* tree)
    :Bud<BearberrySegment,BearberryBud>(p,d,omega,tree){}

};

class BearberrySegment: public HwTreeSegment<BearberrySegment,BearberryBud>
{
 public:
  BearberrySegment(const Point& p,const PositionVector& pv,
		   const LGMdouble go, const METER l, const METER r,
		   const METER rn,Tree<BearberrySegment,BearberryBud>* tree)
    :HwTreeSegment<BearberrySegment,BearberryBud>(p,pv,go,l,r,rn,tree){}
  void createLeaves(vector<PositionVector>& pd,
		    METER pl, METER a, METER b)
    {
      Point origo(0,0,0);
      Point point = GetEndPoint(*this);
      PositionVector up(0,0,1);
      Ellipsis shape(a,b); //initial shape of a leaf
      static Uniform u; //uniform random number [0,1] for setting leaf
			//normals;  static makes it  common throughout
			//the  program and  not reinitialized  in each
			//call.
      int seed = 3267;
      for (int i = 0; i < pd.size(); i++){
	PositionVector pdir = pd[i];
	//Leaves are  created at the end  of the segment  where the buds
	//are, second argument is the intial length of the petiole
	Petiole petiole(point,point + pl*(Point)pdir);
	//Bearberry leaves are on the ground
	PositionVector leaf_normal(0,1,0);
	leaf_normal.normalize();
	BroadLeaf* leaf = new BroadLeaf(shape,petiole,leaf_normal);
	leaf_ls.push_back(leaf);
      }
      //clear the vector; don't create leaves twice
      pd.clear();
    }
};

#endif
