#ifndef BEARBERRY_H
#define BEARBERRY_H

#include <Lignum.h>
#include <Uniform.h>

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
	Ellipse shape(GetEndPoint(petiole),leaf_normal,a,b); //initial shape of a leaf
	BroadLeaf<Ellipse>* leaf = new BroadLeaf<Ellipse>(shape,
							  petiole,
							  leaf_normal);
	leaf_ls.push_back(leaf);
      }
      //clear the vector; don't create leaves twice
      pd.clear();
    }
};


template <class TS,  class BUD>
  class Aging{
  public:
  TreeCompartment<TS,BUD>* operator()(TreeCompartment<TS,BUD>* tc)const
    {
 
      if (BUD* b = dynamic_cast<BUD*>(tc)){
	SetValue(*b,age,GetValue(*b,age)+1);
      }
      else if (TS* ts =  dynamic_cast<TS*>(tc)){
	SetValue(*ts,age,GetValue(*ts,age)+1);
      }    
      return tc;
    }
};

template <class TS, class BUD>
class ShortenSegment{
 public:
  LGMdouble& operator()(LGMdouble& c, TreeCompartment<TS,BUD>* tc)const;
};

template <class TS, class BUD>
  LGMdouble& ShortenSegment<TS,BUD>::operator()(LGMdouble& c, TreeCompartment<TS,BUD>* tc)const
  {
    if (BUD* b = dynamic_cast<BUD*>(tc)){
      if (GetValue(*b,LGMcollision)==1.0)
	  c = 1.0;
    }
    else if (TS* ts =  dynamic_cast<TS*>(tc)){
      if (c == 0.0){
	cout << "Shorten segment" << endl;
	SetValue(*ts,L,0.00001);
      }
    }
    return c;
  }
		          
template <class TS,  class BUD>
  class KillBud{
  public:
  KillBud(LGMdouble p):seed(19988763),die(p){}
  TreeCompartment<TS,BUD>* operator()(TreeCompartment<TS,BUD>* tc)const;
  private:
  mutable Uniform u;
  int seed;  //seed for 'uniform'
  LGMdouble die; //probability limit for bud to die  
};
  
template<class TS, class BUD>
TreeCompartment<TS,BUD>* KillBud<TS,BUD>::operator()(TreeCompartment<TS,BUD>* tc)const
    {
      if (BUD* b = dynamic_cast<BUD*>(tc)){
	if (GetValue(*b,omega) == 0)
	  return tc;
	int a = static_cast<int>(GetValue(*b,age));
	double r = u(seed); //r=[0,1]
	switch (a){
	case 0:break;
	case 1:break;
	case 2:break;
	default:
	  //After the fourth  year side buds (gravelius >  0) start to
	  //die with  increasing probability.  For  example on sandpit
	  //year 3 = 0.11 + 0*0.11; year 4 = 0.11 + 1*0.11 and so on.
	  if (r < die+(a-3)*die){
	    SetValue(*b,state,DEAD);
	    cout << "Bud dead " << "Age: " << GetValue(*b,age) 
		 << " r: "  << r << " Limit: " << die+(a-3)*die<< endl;
	    SetValue(*b,LGMcollision,1.0);
	  }
	  break;
	}
      }
      return tc;
    }    


#endif
