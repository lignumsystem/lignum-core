/// \file  CreateLeaves.h
/// \brief Create Ellipse and Triangle leaves
#ifndef CREATE_LEAVES_H
#define CREATE_LEAVES_H

#include <PositionVector.h>
#include <Sequence.h>
#include <Ellipse.h>
#include <Triangle.h>
using namespace cxxadt;

namespace Lignum{
  
  ///\brief Ellipse leaves
  ///
  ///Two  functors to be  used with  AccumulateDown to  create leaves.
  ///CreateLeaves  create  the   Ellipse  leaves  and  AppendDirections
  ///appends the  directions of the  buds in branching  points.  Usage:
  ///\code{.cc}
  ///AccumulateDown(tree,vector<PositionVector>(),
  ///               AppendSequence<vector<PositionVector> >(),
  ///               CreateLeaves<TS,BUD>())
  ///\endcode
  ///CreateLeaves uses LGMstatus of 1 for bud to create leaves.            
  ///Collect directions from buds if they will create a leaves
  template <class TS, class BUD, class E>
    class CreateLeaves{
    public:
      ///\brief constructor
      ///\param l Petiole length
      ///\param semi_major Ellipse semimajor axis
      ///\param semi_minor Ellipse semiminor axis
      CreateLeaves(METER l, METER semi_major, METER semi_minor)
	:pl(l),a(semi_major),b(semi_minor){}
      ///\brief Create Ellipse leaves
      ///\param v Petiole direction vectors from buds  
      ///\param tc Tree compartment
      ///\retval v Filled with directon vectors from buds or empty after leaves created in tree segment
      ///\pre Bud has LGAstatus = 1 to create a leaf
      ///\post Leaf normal is random but pointing to upper hemisphere
      vector<PositionVector>& operator()(vector<PositionVector>& v,
					 TreeCompartment<TS,BUD>* tc)const;
      METER pl;///<Petiole length
      METER a; ///<semi major axis of leaf ellips
      METER b; ///<semi minor axis od leaf ellips
    };
  
  template <class TS, class BUD, class E>
  vector<PositionVector>& CreateLeaves<TS,BUD,E>::operator()(vector<PositionVector>& pdv,
							     TreeCompartment<TS,BUD>* tc)const
  {
    if (BUD* bud = dynamic_cast<BUD*>(tc)){
      if (GetValue(*bud,LGAstatus) == 1){
	//Leaf to be created
	pdv.push_back(GetDirection(*bud));
	//Leaf created, set status to 0 	
	SetValue(*bud,LGAstatus,0);
      }
    }
    else if (TS* ts = dynamic_cast<TS*>(tc)){
      Point origo(0,0,0);
      Point point = GetEndPoint(*ts);
      PositionVector up(0,0,1);	
      static Uniform u; //uniform random number [0,1] for setting leaf
			//normals;  static makes it  common throughout
			//the  program and  not reinitialized  in each
			//call.
      int seed = 3267;
      for (unsigned int i = 0; i <pdv.size(); i++){
	PositionVector pdir = pdv[i];
	//Leaves are  created at the end  of the segment  where the buds
	//are, second argument is the intial length of the petiole
	Petiole petiole(point,point + pl*(Point)pdir);
	//Randomize  the leaf blade  normal by  rotating in  around axis
	//that lies in the horizontal plane defined by cross product of
	//petiole direction and up-vector
	PositionVector plane = Cross(pdir,up);
	//limit the rotation  of the leaf normal to  [-90,90] degrees so
	//that the leaf normal does not point downwards
	double ran = (-90.0 +180.0*u(seed))*2.0*PI_VALUE/360.0; //(radians)
	PositionVector leaf_normal(0,0,1);
	leaf_normal.rotate(origo,plane,ran);
	const PositionVector petiole_end = 
	  static_cast<const PositionVector>(GetEndPoint(petiole));
	E shape(petiole_end,leaf_normal,a,b); //shape of a leaf is Ellips
	BroadLeaf<E>* leaf = 
	  new BroadLeaf<E>(shape,petiole,leaf_normal,
			   GetFirmament(GetTree(*tc)).numberOfRegions());
	//Set parameters for radiation calculation.
	SetValue(*leaf,LGAdof,GetValue(GetTree(*tc),LGPdof));
	SetValue(*leaf,LGAtauL,GetValue(GetTree(*tc),LGPtauL));
	SetValue(*leaf,LGAsf,GetValue(GetTree(*tc),LGPsf));
	//Insert leaf
	ts->addLeaf(leaf);
      }
      //clear the vector; don't create leaves twice
      pdv.clear();
    }
    return pdv;
  }

  ///\brief Triangle leaf
  ///
  ///Create triangle  leaves in the  same way as ellipse  shaped leaves
  ///We need  petiole length,  and the shape  of the triangle  given by
  ///base length and height of the triangle.
  ///\sa CreateLeaves
  template <class TS, class BUD, class T>
    class CreateTriangleLeaves{
    public:
    ///\brief Constructor
    ///\param l Petiole length
    ///\param b Triangle base length
    ///\param h Triangle height
    CreateTriangleLeaves(METER l, METER b, METER h):pl(l),base(b),height(h){}
    ///\brief Create Triangle leaves
    ///\param v Petiole direction vectors from buds
    ///\param tc Tree compartment
    ///\retval v Filled with directon vectors from buds or empty after leaves created in tree segment
    ///\pre Bud has LGAstatus = 1 to create a leaf
    ///\post Leaf normal is random but pointing to upper hemisphere
    vector<PositionVector>& operator()(vector<PositionVector>& v,
				       TreeCompartment<TS,BUD>* tc)const;
    METER pl;///<Petiole length
    METER base; ///<Triangle base length
    METER height; ///<Triangle height
  };

  template <class TS, class BUD, class T>  vector<PositionVector>& 
    CreateTriangleLeaves<TS,BUD,T>::operator()(vector<PositionVector>& pdv,
					       TreeCompartment<TS,BUD>* tc)const
    {
      double rlsize=1.0;
      if (BUD* b = dynamic_cast<BUD*>(tc)){
	if (GetValue(*b,LGAstatus) == 1){
	  pdv.push_back(GetDirection(*b));
          rlsize = GetValue(*b, LGAstatus);
	  //Leaf created, set status to 0 	
	  SetValue(*b,LGAstatus,0);
	}
      }
      if (TS* ts = dynamic_cast<TS*>(tc)){
	Point origo(0,0,0);
	Point point = GetEndPoint(*ts);
	PositionVector up(0,0,1);
	PositionVector down(0,0,-1);
	
	static Uniform u; //uniform random number [0,1] for setting leaf
	                  //normals;  static makes it  common throughout
	                  //the  program and  not reinitialized  in each
           	          //call.
	int seed = 3267;
	for (unsigned int i = 0; i <pdv.size(); i++){
	  PositionVector pdir = pdv[i];
	  //Leaves are  created at the end  of the segment  where the buds
	  //are, second argument is the intial length of the petiole
	  Petiole petiole(point,point + pl*(Point)pdir);
	  //Randomize  the leaf blade  normal by  rotating in  around axis
	  //that lies in the horizontal plane defined by cross product of
	  //petiole direction and up-vector. Also it is direction towards  
	  //right corner of the triangle
	  PositionVector axis1 = Cross(pdir,up).normalize();
	  //limit the rotation  of the leaf normal to  [-90,90] degrees so
	  //that the leaf normal does not point downwards
	  double ran = (-90.0 +180.0*u(seed))*2.0*PI_VALUE/360.0; //(radians)
	  PositionVector leaf_normal(0,0,1);
	  leaf_normal.rotate(origo,axis1,ran);
	  //We need also the left corner of the triangle. Create a vector
	  //towards it.
	  PositionVector axis2 = Cross(pdir,down).normalize();
	  //We yet need the direction towards the apex of the triangle
	  //to set the apex point
	  PositionVector axis3 = Cross(leaf_normal,axis1).normalize();
	  //I hope I got the cross  products right, but we will see in
	  //the visualization how the leaves settle themselves
	  Point right = point + base*0.5*(Point)axis1;
	  Point left  = point + base*0.5*(Point)axis2;
	  Point apex  = point + height*(Point)axis3;
	  T shape(left,right,apex);
	  BroadLeaf<T>* leaf = new BroadLeaf<T>(shape,petiole,leaf_normal);
	
          SetValue(*leaf, LGAdof, GetValue(GetTree(*tc), LGPdof));
          SetValue(*leaf, LGAtauL, GetValue(GetTree(*tc), LGPtauL));
          SetValue(*leaf, LGAsf, GetValue(GetTree(*tc), LGPsf));

  
	  //	  double Af = rlsize * 0.08; //GetValue(GetTree(*ts), LGPaleafmax);
	    //  cout<<"LGPaleafmax value: "<<GetValue(GetTree(*ts), LGPaleafmax)<<endl;
         
	    SetValue(*leaf, LGAA, 0.1);   //set the leaf area value, which is used in DumpLeaf()

	  //Insert leaf
	  ts->addLeaf(leaf);
	  //**cout << "Leaf inserted" << endl;
	}
	//clear the vector; don't create leaves twice
	pdv.clear();
      }
      return pdv;
    }
}//closing namespce




#endif
