#ifndef TREEFUNCTOR_H
#define TREEFUNCTOR_H

#include <iostream>
#include <fstream>
using namespace std;


#include <LGMdecl.h>
#include <LGMSymbols.h>
#include <TreeCompartment.h>
#include <BroadLeaf.h>
#include <Algorithms.h>
#include <TreeCharacteristics.h>
#include <TreeMetabolism.h>
#include <LGMGeometry.h>
/// \file TreeFunctor.h
/// \brief Tree functors and functions.
///
/// If you add a functor or function please update this list.
/// Helper functors etc. are not listed here.
/// \arg \c  ConnectTree
/// \arg \c  CountAxes
/// \arg \c  CountAxesProper  (no. of axes with at least one TreeSegment)
/// \arg \c  IsConnected
/// \arg \c  CountBuds
/// \arg \c  CountTreeSegments
/// \arg \c  CountBranchingPoints
/// \arg \c  CountBranches
/// \arg \c  CountCfTreeSegmentsWithFoliage
/// \arg \c  CountHwTreeSegmentsWithFoliage
/// \arg \c  CountLeavesHw
/// \arg \c  TotalSegmentLength
/// \arg \c  ForwardQin (for coniferous)
/// \arg \c  PrintTreeInformation
/// \arg \c  PrintTreeInformation2
/// \arg \c  CountCompartments 
/// \arg \c  CountCompartmentsReverse
/// \arg \c  CrownGroundArea
/// \arg \c  SetGraveliusOrder
/// \arg \c  DisplayStructure
/// \arg \c  CheckCoordinates
/// \arg \c  FindCfBoundingBox
/// \arg \c  FindHwBoundingBox
/// \arg \c  FindLongestDistanceToStem  Find longest distance to to stem
///                                     and its direction
/// \arg \c  FindRFunctor Find largest distance to stem in a crown slice
///                       in a quadrant around given direction
/// \arg \c  FindRFunctorF Find mean by foliage weighted distance to stem in a crown slice
///                        between heights minH and maxH in an angle around
///                        given direction
/// \arg \c  CollectFrustumVolume 
/// \arg \c  CollectFoliageMass (Either whole tree or by Gravelius order)
/// \arg \c  CollectFoliageArea (Either whole tree or by Gravelius order)
/// \arg \c  CollectLeafArea    (Either whole tree or by Gravelius order)
/// \arg \c  CollectWoodMass (Either whole tree or by Gravelius order)
/// \arg \c  CollectSegmentLengths (Either whole tree or by Gravelius order)
/// \arg \c  CollectStemWoodMass
/// \arg \c  CollectSapwoodMass
/// \arg \c  CollectStemSapwoodMass
/// \arg \c  CollectHeartwoodMass
/// \arg \c  CollectNewSegmentSapwoodMass (LGAage == 0.0)
/// \arg \c  CollectOldSegmentSapwoodMass (LGAage > 0.0)
/// \arg \c  CollectNewFoliageMass        (LGAage == 0.0)
/// \arg \c  CollectQabs
/// \arg \c  CollectQin
/// \arg \c  CollectMantleArea
/// \arg \c  GetQinMax
/// \arg \c  MoveHwTree (does MoveTree + moves leaves also)
/// \arg \c  MoveTree
/// \arg \c  DeleteDeadBranches
/// \arg \c  PrintTreeSegmentInformationToFile
/// \arg \c  PrintTreeSegmentInformationToFileByAxis
/// \arg \c  DropAllLeaves
/// \arg \c  ResetQinQabs
/// \arg \c  CollectLeaves: Return a 'list<BroadLeaf<SH>*> ls' of leaves in a tree<br>
/// Usage:
/// \code{.cc}
///    Accumulate(t,ls,CollectLeaves<TS,BUD,SH>());
/// \endcode
/// \arg \c  SortLeaves Sort leaves (returned by CollectLeaves), leaves closest to the 
///                      point \p p appear first<br>
/// Usage:
/// \code{.cc}
///    Point p(0,0,0);
///    SortLeaves<SH> sorter(p);
///    ls.sort(sorter);
/// \endcode
/// \arg \c   SortLeavesHeight  Sort  leaves  (returned by  CollectLeaves)  in
///                              height defined by a binary predicate <br>
/// Usage:
/// \code{.cc}
///    SortLeavesHeight<SH,BinaryPredicate> sorter; 
///    ls.sort(sorter);
/// \endcode
/// To sort in descending order (lowest leaf first):
/// \code{.cc}
///    SortLeavesHeight<Ellipse,less_equal<double> > sorter;
/// \endcode
/// To sort in ascending order:
/// \code{.cc}
///    SortLeavesHeight<Ellipse,greater_equal<double> > sorter;
/// \endcode
/// \arg \c  CrownVolume
/// \arg \c  MainAxisVolume Usage:
/// \code{.cc}
///    MainAxisVolume main_axis_volume;
///    double v = main_axis_volume(tree);
/// \endcode
/// \arg \c   SetRTopToR Set LGARTop to LGAR<br>
/// Usage:
/// \code{.cc}
///    ForEach(tree, SetRTopToR<TS,BUD>()).
/// \endcode
/// \note LGARTop is used in for example visualiztion.  It may
///  or may not  have the desired value. In  most cases in
///  growth simulations only LGAR  is used.  This may have
///  unwanted results in visualization.
///
/// \arg \c CrownExtension Returns instead of crown volume mean distance crown surface from stem in different heights
///
///  The following functors return start or end point (whichever
///  is higher or lower) of segments. With foliage for conifers. Useful, since
///  there may be segments higher than tree top or lower than crown
///  base, which are evaluated on the basis on the main axis (stem).
///  \note In the case of LowestSegmentExcludingStem stem segments are *not*
///  considered since the lowest segment is by definition the first in the
///  main axis (stem). In other functors stem is also included.
///
/// \arg \c LowestSegmentExcludingStem
/// \arg \c LowestCfSegmentWithFoliage
/// \arg \c HighestSegment
/// \arg \c HighestCfSegmentWithFoliage
///
/// Dump tree (woody parts) to STL format (writes to the console).
/// \arg \c STL_Triangularize
/// \arg \c Triangularize
///
/// \arg \c DaVinciTaperCurve  Implements the taper curve according to Da Vinci rule
//                             Needs 1) Radius of the first segments 2) The exponent 
//
//  Vertical leaf area disrtribution
//  Functors-functions below used in LIGNUM WorkBench are not listed.


namespace Lignum{


  //Sets coordinates so that the base of the next = base_previous + length * direction
  //Run this with propagate up
  template <class TS, class BUD>
    class ConnectTree{
  public:
    Point& 
      operator()(Point& p, TreeCompartment<TS,BUD>* tc)const
      {
	if(TS* ts = dynamic_cast<TS*>(tc)) {
	  SetPoint(*ts, p);
	  LGMdouble l = GetValue(*ts, LGAL);
	  PositionVector direction = GetDirection(*ts);
	  Point end = p + Point(l*direction);
	  p = end;
	}
	else
	  SetPoint(*tc, p);

	return p;
      }
  };

  //Check each tree segment is connected: end point is the start point
  //Start with the point of the first tree segment
  template <class TS, class BUD>
  class IsConnected{
  public:
    IsConnected(double accuracy=R_EPSILON):acc(accuracy),connected(true){}
    Point& operator()(Point& previous, TreeCompartment<TS,BUD>* tc)const
    {
      if(TS* ts = dynamic_cast<TS*>(tc)) {
	Point pcurrent=GetPoint(*ts);
	if ((pcurrent || previous) > acc){
	  cout << "Previous point: " << previous.getX() << " " << previous.getY() << " "
	       << previous.getZ() <<endl;
	  cout << "Current point:  " << pcurrent.getX() << " " << pcurrent.getY() << " "
	       << pcurrent.getZ() <<endl;
	  cout << "Distance: " << (pcurrent || previous)<<endl<<endl;
	  connected = false;
	}
	Point pend = GetEndPoint(*ts);
	previous = pend;
      }
      return previous;
    }
  private:
    double acc;
    mutable bool connected;
  };
  

//   CountAxes counts all axes

  template <class TS,class BUD>
    class CountAxes {
  public:
    int& operator()(int& n,TreeCompartment<TS,BUD>* tc)const
    {
      if(Axis<TS,BUD>* ax = dynamic_cast<Axis<TS, BUD>*>(tc)) {
	n+=1;
      }
      return n; 
    }
  };


//   CountAxesProper counts Axes that have at least one TreeSegment
//   Note that Number of Axes (Proper) =  Number of Apexes

   template <class TS,class BUD>
     class CountAxesProper {
     public:
     int& operator()(int& n,TreeCompartment<TS,BUD>* tc)const
       {
	 if(Axis<TS,BUD>* ax = dynamic_cast<Axis<TS, BUD>*>(tc)) {
	     list<TreeCompartment<TS,BUD>*>& lscmp = GetTreeCompartmentList(*ax);
	     if((int)lscmp.size() >= 3) {  //At least one TreeSegment
	       n+=1;
	     }
	 }
	 return n; 
       }
     unsigned int& operator()(unsigned int& n,TreeCompartment<TS,BUD>* tc)const
       {
	 if(Axis<TS,BUD>* ax = dynamic_cast<Axis<TS, BUD>*>(tc)) {
	     list<TreeCompartment<TS,BUD>*>& lscmp = GetTreeCompartmentList(*ax);
	     if((int)lscmp.size() >= 3) {  //At least one TreeSegment
	       n+=1;
	     }
	 }
	 return n; 
       }

   };

     //CountBUDS
   template <class TS,class BUD>
     class CountBuds {
     public:
     int& operator()(int& n,TreeCompartment<TS,BUD>* tc)const
       {
	 if (dynamic_cast<BUD*>(tc)!=NULL)
	   n+=1;
	 return n;
       }
     unsigned int& operator()(unsigned int& n,TreeCompartment<TS,BUD>* tc)const
     {
	 if (dynamic_cast<BUD*>(tc)!=NULL)
	   n+=1;
	 return n;
     }
   };


     //CountTreeSegments
   template <class TS,class BUD>
     class CountTreeSegments {
     public:
     int& operator()(int& n,TreeCompartment<TS,BUD>* tc)const
       {
	 if (dynamic_cast<TS*>(tc)!=NULL)
	   n+=1;
	 return n;
       }
     unsigned int& operator()(unsigned int& n,TreeCompartment<TS,BUD>* tc)const
     {
	 if (dynamic_cast<TS*>(tc)!=NULL)
	   n+=1;
	 return n;
     }
   };

  template <class TS, class BUD>
  class CountBranchingPoints{
  public:
    int operator()(int& n, TreeCompartment<TS,BUD>* tc)const
    {
      if (dynamic_cast<BranchingPoint<TS,BUD>*>(tc) != NULL){
	n = n+1;
      }
      return n;
    }
  };

  template <class TS, class BUD>
  class CountBranches{
  public:
    int operator()(int& n, TreeCompartment<TS,BUD>* tc)const
    {
      if (BranchingPoint<TS,BUD>*bp = dynamic_cast<BranchingPoint<TS,BUD>*>(tc)){
	list<Axis<TS,BUD>*>& axisls = GetAxisList(*bp);
	  n = n+axisls.size();
      }
      return n;
    }
  };

      
   template <class TS,class BUD>
     class CountCfTreeSegmentsWithFoliage {
     public:
     int& operator()(int& n,TreeCompartment<TS,BUD>* tc)const
       {
	 if(CfTreeSegment<TS,BUD>* ts = dynamic_cast<CfTreeSegment<TS,BUD>*>(tc))
	   if(GetValue(*ts,LGAWf)>R_EPSILON)
	     n+=1;
	 return n;
       }
   };

   template <class TS,class BUD, class SHAPE>
     class CountHwTreeSegmentsWithFoliage {
     public:
     int& operator()(int& n,TreeCompartment<TS,BUD>* tc)const
       {
	 if(HwTreeSegment<TS,BUD,SHAPE>* ts = dynamic_cast<HwTreeSegment<TS,BUD,SHAPE>*>(tc))
	   if(GetValue(*ts,LGAWf)>R_EPSILON)
	     n+=1;
	 return n;
       }
   };

   template <class TS,class BUD, class SHAPE>
     class CountLeavesHw {
     public:
     int& operator()(int& n,TreeCompartment<TS,BUD>* tc)const
       {
	 if(HwTreeSegment<TS,BUD,SHAPE>* ts = dynamic_cast<HwTreeSegment<TS,BUD,SHAPE>*>(tc)) {
	   list<BroadLeaf<SHAPE>*>& leaf_list = 
	     GetLeafList(*ts);
	   n += static_cast<int>(leaf_list.size());
	 }
	 return n;
       }
   };

  //The sum of the segments in a tree
  template <class TS, class BUD>
  class TotalSegmentLength{
  public:
    double operator()(double& length,TreeCompartment<TS,BUD>* tc)const
    {
      if (TS* ts = dynamic_cast<TS*>(tc)){
	length = length+GetValue(*ts,LGAL);
      }
      return length;
    }
  };
  
  //PrintTreeInformation collects and prints out information about the
  //tree. It uses functor TreeData to collect the information with
  //Accumulate

   //PrintTreeInformation prints either to file or to console. The

   //Call constructor basically in two ways:
   //1) PrintTreeInformation<TS,BUD,ostream> print -- prints to cout
   //2) PrintTreeInformation<TS,BUD,ofstream> print(const ofstream&)
   //    -- prints to the file given as parameter.
   //(print is then the name of the functor)

  template <class TS, class BUD, class STREAM>
    class PrintTreeInformation {
    public:
      PrintTreeInformation(): out(cout) {}
      PrintTreeInformation(ofstream& file):
    out(file) {}
      void operator() (Tree<TS,BUD>&  tr);
    private:
      STREAM& out; 
  };


  template <class TS,class BUD>
  class ForwardQin{
  public:
    double operator()(double& qin, TreeCompartment<TS,BUD>* tc)const
    {
      if (TS* ts = dynamic_cast<TS*>(tc)){
	double ts_qin = GetValue(*ts,LGAQin);
	if (GetValue(*ts,LGAage) == 0.0){//pass qin to this segment
	  SetValue(*ts,LGAQin,qin);
	}
	else{ //computed
	  qin = ts_qin;
	}
      }
      return qin;
    }
  };

  //TreeData is used to collect (Accumulate) data on a tree.
  //it uses TreeDataStruct

  class TreeDataStruct
      {
  public:
      TreeDataStruct():
	age(0), sum_Wf(0.0), sum_Wf_new(0.0), sum_wood_in_newparts(0.0),
	sum_wood_new(0.0), sum_Ws(0.0), sum_Wb(0.0), sum_Wsw(0.0),
	sum_Whw(0.0), sum_Af(0.0), sum_Qabs(0.0), max_Qin(0.0), sum_Qin(0.0), 
	num_buds(0), num_segments(0),tHeight(0.0), bolLen(0.0), 
	bottom_rad(0.0),Hc(R_HUGE), num_s_fol(0),
	num_br_l(0), num_br_d(0),
	sum_br_len(0.0),sum_br_len_d(0.0), sum_br_As(0.0),sum_br_Ac(0.0)
	  { }
	
	int age;
	LGMdouble sum_Wf;          //All foliage
	LGMdouble sum_Wf_new;      //Foliage in segments (int)age == 0
	LGMdouble sum_wood_in_newparts; //Wood in segments (int)age == 0
	LGMdouble sum_wood_new;    //sum_wood_in_newparts+last ring
	LGMdouble sum_Ws;          // Stemwood
	LGMdouble sum_Wb;          // Branchwood
	LGMdouble sum_Wsw;         // Sapwood (in all segments)
	LGMdouble sum_Whw;         // Heartwood (in all segments)
	LGMdouble sum_Af;          // Sum leaf area
	LGMdouble sum_Qabs;         // Absorbed radiation
	LGMdouble max_Qin;         // Max Incoming radiation
	LGMdouble sum_Qin;         // Incoming radiation for mean value calc.
	int num_buds;
	int num_segments;
	LGMdouble tHeight;         //Tree height = highest point from ground
	LGMdouble bolLen;           //bole length = length of main axis (stem)
	LGMdouble bottom_rad;
	LGMdouble Hc;               //Height of grown base
	int num_s_fol;              //number of segments with foliage
	int num_br_l;               //number of branches living
	int num_br_d;               //number of branches dead
	LGMdouble sum_br_len;       //total length of branches, living
	LGMdouble sum_br_len_d;     //total length of branches, dead
	LGMdouble sum_br_As;
	LGMdouble sum_br_Ac; 
	vector<LGMdouble> taper_rad;
	vector<LGMdouble> taper_hei;
	vector<LGMdouble> taper_radhw;
	vector<LGMdouble> mean_brl;
	vector<LGMdouble> mean_br_h;
	vector<LGMdouble> taper_radh;
	double height;
      };
  
  
  template <class TS,class BUD>
    class TreeData
    { 
    public:
      TreeDataStruct& operator()(TreeDataStruct& stru,
				 TreeCompartment<TS,BUD>* tc)const;
    };


  //Functor PrintTreeInformation2 prints out tree information to a
  //file (given as a parameter to constructor (a ofstream)) one row in
  //each growth cycle for plotting purposes etc.  Calculates the
  //values with the same methods as PrintTreeInformation.

  template <class TS, class BUD>
    class PrintTreeInformation2 {
    public:
    PrintTreeInformation2(ofstream& out):
    out(out)
      {
     out << "age db d13 H Hc Wf Ws Wb Af LAR QinM Qabs P M NoSeg NoBud"
       " NoSegN NSegNZ NBranches Wr"
	<< endl;
      }
    void operator() (Tree<TS,BUD>&  tr);
    private:
    ofstream& out;
  };

  
  template <class TS,class BUD=DefaultBud<TS> >
    class GetNewZeroSegments{
      public:
      int& operator ()(int& id,TreeCompartment<TS,BUD>* tc)const {
	if (TS* ts = dynamic_cast<TS*>(tc)) {
	  if(GetValue(*ts, LGAage) < R_EPSILON &&
	     GetValue(*ts,LGAL) < R_EPSILON) {
	       id++;
	     }
	}
	
	return id;
      }
      
    };
  
  template <class TS,class BUD=DefaultBud<TS> >
    class GetNewSegments{
      public:
      int& operator ()(int& id,TreeCompartment<TS,BUD>* tc)const {
	if (TS* ts = dynamic_cast<TS*>(tc)) {
	  if(GetValue(*ts, LGAage) < R_EPSILON) {
	    id++;
	  }
	}
	
	return id;
      }
      
    };
    
  template <class TS,class BUD=DefaultBud<TS> >
    class CountCompartments{
    public:
    int& operator ()(int& id,TreeCompartment<TS,BUD>* ts)const;
  };

  template <class TS,class BUD=DefaultBud<TS> >
    class CountCompartmentsReverse{
      public:
      int& operator ()(int& id,TreeCompartment<TS,BUD>* ts)const;
    };


  //This functor searches shortest distance to stem in four quadrants
  //(they are in vector in counterclockwise order)
  //NOTE that the tree is given as argument in constructor
  //NOTE that the initial values of vector elements must be = 0.0

  template <class TS,class BUD=DefaultBud<TS> >
    class CrownGroundArea{
      public:
      CrownGroundArea(Tree<TS,BUD>& tree) {
	Axis<TS,BUD>& my_ax = GetAxis(tree);
	stem_point = GetPoint(*GetFirstTreeCompartment(my_ax));
      }

      vector<LGMdouble>& operator ()(vector<LGMdouble>& ,TreeCompartment<TS,BUD>* tc)const;
      private:
      Point stem_point;
    };


  //Sets the Gravelius order of Segments, BranchingPoints and Buds so
  //that these parts belonging to an axis forking off from the present one
  //get order one higher. Use this functor as
  //PropagateUp(tree,iniGo,SetGraveliusOrder<TS>()), where iniGo = 0 quarantees
  //that the main stem gets Gravelius order equal to 1. (= LIGNUM convention).

template <class TS,class BUD> 
class SetGraveliusOrder {
public:
  int& operator()(int& g_o,TreeCompartment<TS,BUD>* tc)const {
    
    if(Axis<TS, BUD>* ax =
       dynamic_cast<Axis<TS, BUD>*>(tc))
      g_o++;
    else if(TS* ts = dynamic_cast<TS*>(tc))
      SetValue(*ts,LGAomega,(double)g_o);
    else if(BranchingPoint<TS, BUD>* bp
	    = dynamic_cast<BranchingPoint<TS, BUD>*>(tc))
      SetValue(*bp,LGAomega,(double)g_o);
    else if(BUD* bd = dynamic_cast<BUD*>(tc)) 
      SetValue(*bd,LGAomega,(double)g_o);
    else{
      //Empty statement
      ;
    }
    return g_o;
  }
};



  template <class TS,class BUD> void DisplayStructure(Tree<TS,BUD>& t);
  template <class TS,class BUD> void DisplayStructure(TreeCompartment<TS,BUD>* tc);

  class DisplayStructureData{
  public:
    DisplayStructureData()
      :first_segment(true),number_of_compartments(0){}
    bool first_segment;
    int number_of_compartments;
  };
    
  template <class TS,class BUD=DefaultBud<TS> >
    class DisplayStructureFunctor{
      public:
      DisplayStructureData&  operator ()(DisplayStructureData& id,
					 TreeCompartment<TS,BUD>* ts)const;


    };

  template <class TS,class BUD=DefaultBud<TS> >
    class CheckCoordinates{
      public:
      CheckCoordinates(double e = 1.0e-20);
      TreeCompartment<TS,BUD>* operator ()(Point& id,
					   TreeCompartment<TS,BUD>* ts)const;
      double epsilon;

    };


  //This class holds the values of the coordinates that define box that
  //holds the tree - or several trees.

  class BoundingBox { 
    inline friend ostream& operator << (ostream& os,
					const BoundingBox& bb) {
      os << "BoundingBox:" << '\n' << "Min -  x: " << bb.minxyz.getX() 
	 <<" y: " << bb.minxyz.getY()  << " z: " << bb.minxyz.getZ()
	 << '\n' << flush;
      os << "Max -  x: " << bb.maxxyz.getX() <<" y: " <<
	bb.maxxyz.getY()  << " z: " << bb.maxxyz.getZ() << '\n' << flush;
      return os;
    }

  public:
    BoundingBox() { minxyz = Point(R_HUGE, R_HUGE, R_HUGE); 
    maxxyz = Point(-R_HUGE, -R_HUGE, -R_HUGE); }

    //Addition of a BoundingBox to this. It finds the (smallest) big one containing
    //both of them (mathematically: intersection of all BoundingBoxes that contain
    //this and the other BoundingBox).
    BoundingBox& operator += (const BoundingBox& add_this) {
      minxyz.setX(min(minxyz.getX(),add_this.getMin().getX()));
      minxyz.setY(min(minxyz.getY(),add_this.getMin().getY()));
      minxyz.setZ(min(minxyz.getZ(),add_this.getMin().getZ()));
      maxxyz.setX(max(maxxyz.getX(),add_this.getMax().getX()));
      maxxyz.setY(max(maxxyz.getY(),add_this.getMax().getY()));
      maxxyz.setZ(max(maxxyz.getZ(),add_this.getMax().getZ()));
      return *this;
   }

    Point getMin() const { return minxyz; }
    Point getMax() const { return maxxyz; }
    void setMin(const Point& p){minxyz=p;}
    void setMax(const Point& p){maxxyz=p;}
    void setMinX(const LGMdouble x) { minxyz.setX(x); }
    void setMinY(const LGMdouble y) { minxyz.setY(y); }
    void setMinZ(const LGMdouble z) { minxyz.setZ(z); }
    void setMaxX(const LGMdouble x) { maxxyz.setX(x); }
    void setMaxY(const LGMdouble y) { maxxyz.setY(y); }
    void setMaxZ(const LGMdouble z) { maxxyz.setZ(z); }
    void addPoint(const Point p) {     //if Point is not in BBox, it is enlarged to contain
      minxyz.setX(min(minxyz.getX(),p.getX()-R_EPSILON)); //R_EPSILON to make sure that
      minxyz.setY(min(minxyz.getY(),p.getY()-R_EPSILON)); //the enlagement goes over the Point
      minxyz.setZ(min(minxyz.getZ(),p.getZ()-R_EPSILON));
      maxxyz.setX(max(maxxyz.getX(),p.getX()+R_EPSILON));
      maxxyz.setY(max(maxxyz.getY(),p.getY()+R_EPSILON));
      maxxyz.setZ(max(maxxyz.getZ(),p.getZ()+R_EPSILON));
    }
  private:
    Point minxyz;
    Point maxxyz;
  };


  //This functor runs (Accumulate) through tree and finds the bounding
  //box for it.  Conifers and deciduous TreeSegments (i.e. Trees)
  //separately, since deciduoous are dealt with leaf by leaf and
  //conifers by segments.

  template <class TS,class BUD>
    class FindCfBoundingBox{
    public:
    FindCfBoundingBox() : foliage(false) {}
    FindCfBoundingBox(bool fol) : foliage(fol) {}
    BoundingBox& operator ()(BoundingBox& b_box,
			     TreeCompartment<TS,BUD>* tc)const;
  private:
    bool foliage;
  };

  template<class TS, class BUD, class SHAPE>
    class FindHwBoundingBox{
    public:
    BoundingBox& operator ()(BoundingBox& b_box,
			     TreeCompartment<TS,BUD>* tc)const;
  };

  template <class TS,class BUD>
    class CollectFrustumVolume
    { 
    public:
      LGMdouble& operator()(LGMdouble &sum, TreeCompartment<TS,BUD>* tc)const;
    };

  //Either whole tree: construct CollectFoliageMass() or by Gravelius order:
  // construct CollectFoliageMass(order)
  template <class TS,class BUD>
    class CollectFoliageMass
    { 
    public:
      CollectFoliageMass():my_order(-1.0) {}
      CollectFoliageMass(const LGMdouble order):my_order(order){}
      LGMdouble& operator()(LGMdouble &sum, TreeCompartment<TS,BUD>* tc)const;
      void setOrder(const int order) {my_order = static_cast<double>(order); }
    private:
      LGMdouble my_order;
    };

  //Either whole tree: construct CollectFoliageArea() or by Gravelius order:
  // construct CollectFoliageArea(order)
  //THIS WORKS WITH Conifers
  template <class TS,class BUD>
    class CollectFoliageArea
    { 
    public:
      CollectFoliageArea():my_order(-1.0) {}
      CollectFoliageArea(const LGMdouble order):my_order(order){}

      LGMdouble& operator()(LGMdouble &sum, TreeCompartment<TS,BUD>* tc)const;
    private:
      LGMdouble my_order;
    };

  //Either whole tree: construct CollectLeafArea() or by Gravelius order:
  // construct CollectLeafArea(order)
  template <class TS,class BUD, class SHAPE>
  class CollectLeafArea
  { 
  public:
    CollectLeafArea():my_order(-1.0) {}
    CollectLeafArea(const LGMdouble order):my_order(order){}
    LGMdouble& 
    operator()(LGMdouble &sum,TreeCompartment<TS,BUD>* tc)const;
  private:
    LGMdouble my_order;
  };

  //Either whole tree: construct CollectFoliageMass() or by Gravelius order:
  // construct CollectFoliageMass(order)
  template <class TS,class BUD>
    class CollectWoodMass
    { 
    public:
      CollectWoodMass():my_order(-1.0) {}
      CollectWoodMass(const LGMdouble order):
      my_order(static_cast<double>(order)){}
      LGMdouble& operator()(LGMdouble &sum, TreeCompartment<TS,BUD>* tc)const;
      void setOrder(const int order) {my_order = static_cast<double>(order);}
    private:
      LGMdouble my_order;
    };

  //Either whole tree: construct CollectSegmentLengths() or by Gravelius order:
  // construct CollectSegmentLengths(order)
  template <class TS,class BUD>
    class CollectSegmentLengths
    { 
    public:
      CollectSegmentLengths():my_order(-1.0) {}
      CollectSegmentLengths(const LGMdouble order):
      my_order(static_cast<double>(order)){}
      LGMdouble& operator()(LGMdouble &sum, TreeCompartment<TS,BUD>* tc)const;
      void setOrder(const int order) {my_order = static_cast<double>(order);}
    private:
      LGMdouble my_order;
    };


  template <class TS,class BUD>
    class CollectStemWoodMass
    { 
    public:
      LGMdouble& operator()(LGMdouble &sum, TreeCompartment<TS,BUD>* tc)const;
    };

  template <class TS,class BUD>
    class CollectSapwoodMass
    { 
    public:
      LGMdouble& operator()(LGMdouble &sum, TreeCompartment<TS,BUD>* tc)const;
    };

  template <class TS,class BUD>
    class CollectStemSapwoodMass
    { 
    public:
      LGMdouble& operator()(LGMdouble &sum, TreeCompartment<TS,BUD>* tc)const;
    };

  template <class TS,class BUD>
    class CollectHeartwoodMass
  { 
    public:
      LGMdouble& operator()(LGMdouble &sum, TreeCompartment<TS,BUD>* tc)const;
    };
  template <class TS,class BUD>
  class CollectNewSegmentSapwoodMass{ 
  public:
    LGMdouble& operator()(LGMdouble &sum, TreeCompartment<TS,BUD>* tc)const;
  };

  template <class TS,class BUD>
  class CollectOldSegmentSapwoodMass{ 
  public:
    LGMdouble& operator()(LGMdouble &sum, TreeCompartment<TS,BUD>* tc)const;
  };

  template <class TS,class BUD>
  class CollectNewFoliageMass{
  public:
    LGMdouble& operator()(LGMdouble& wf, TreeCompartment<TS,BUD>* tc)const;
  };

  //This sums up absorbed radiation for tree
  template <class TS,class BUD>
    class CollectQabs
    { 
    public:
      LGMdouble& operator()(LGMdouble &sum, TreeCompartment<TS,BUD>* tc)const;
    };

  //This sums up Qin for the tree
  template <class TS,class BUD>
    class CollectQin
    { 
    public:
      LGMdouble& operator()(LGMdouble &sum, TreeCompartment<TS,BUD>* tc)const;
    };

  //This fuctor evaluates the maximum Qin of all TreeSegments in a Tree

  template <class TS, class BUD>
    class GetQinMax{
    public:
    LGMdouble& operator()(LGMdouble& qin, TreeCompartment<TS,BUD>* tc)const{
      if (TS* ts = dynamic_cast<TS*>(tc)){
	LGMdouble qin_ts = GetValue(*ts,LGAQin);
	qin = max(qin,qin_ts);
      }
      return qin;
    }

  };

  //======================================================================================
  // This functor collects (Accumulate) the surface area of Segments (without end disks).
  // If top diameter > 0 the area is calculated as one of frustum, if top diameter == 0, 
  // Segment is regarded as a cylinder.

  //If my_order < 0, the mantle area of only segments that have order == -my_order are collected
  //If my_order > 0 the mantle area of segments with order >= my_order are collected
  //If foliage == true, also segments with foliage are included, otherwise not
  //If crown == true, only segments that are higher than crown base are included

  template <class TS, class BUD>
    class CollectMantleArea{
  public:
  CollectMantleArea(int order, bool w_fol): my_order(order), foliage(w_fol), crown_base(-1.0) {}
  CollectMantleArea(int order, bool w_fol, const LGMdouble cb): my_order(order), foliage(w_fol),
      crown_base(cb) {}

    LGMdouble& operator()(LGMdouble& sum, TreeCompartment<TS, BUD>* tc)const{
      if(TS* ds = dynamic_cast<TS*>(tc)) {

	if((int)GetValue(*ds,LGAomega) != my_order) {
	  return sum;
	}

	if(!foliage) {
	  if(GetValue(*ds,LGAWf) > R_EPSILON)
	    return sum;
	}

	if(crown_base > 0.0) {
	  LGMdouble z = GetPoint(*tc).getZ();
	  if(z < crown_base) {
	    return sum;
	  }
	}
	LGMdouble r = GetValue(*ds, LGAR);
	LGMdouble rt = GetValue(*ds,LGARTop);
	if(rt < R_EPSILON) 
	  rt = r;
	LGMdouble l = GetValue(*ds,LGAL);
      
	LGMdouble s = sqrt(l*l+(r-rt)*(r-rt));
	sum += PI_VALUE*(r + rt)*s;
      }
      return sum;
    }
  private:
    int my_order;
    bool foliage;
    LGMdouble crown_base;
  };



  //This functor is used (ForEach) to move a hardwood tree (=all its
  //TreeCompartments) and leaves to a new location. 
  //See MoveTree for conifers.
  //Note that a vector (Point) is added to the current position
  //(vector, i.e. Point). Hence, if you want to move a tree from
  //location (Point) b, you should call the constructor
  //of MoveTree with argument b - a, where a is the current
  //position of the tree. 

  template <class TS, class BUD, class S>
    class MoveHwTree{
  public:
  MoveHwTree(const MoveHwTree& move, Tree<TS,BUD>& t)
  :move_to(move.move_to){SetPoint(t,GetPoint(t)+move_to);}
  MoveHwTree(const MoveHwTree& move):move_to(move.move_to){}
  //This   constructor  ensures   that  also   the   tree  itself,
  //i.e. GetPoint(tree), is moved.
  MoveHwTree(const Point& point,Tree<TS,BUD>& t)
  :move_to(point){SetPoint(t,GetPoint(t)+move_to);} 
  MoveHwTree(const Point& point):move_to(point) {} 
  Point setPoint(const Point& new_point) {
    Point tmp = move_to;
    move_to = new_point;
    return tmp;
  }
  TreeCompartment<TS,BUD>* operator()(TreeCompartment<TS,BUD>* tc)const
    {
      //Move first the compartment and if it is a TS also its leaves
      SetPoint(*tc, GetPoint(*tc)+move_to);

      if(TS* ts = dynamic_cast<TS*>(tc)){
	list<BroadLeaf<S>*>& leaf_list = GetLeafList(*ts);
	typename list<BroadLeaf<S>*>::iterator I;
	for(I = leaf_list.begin(); I != leaf_list.end(); I++) {
/* 	  cout << "Left " << (GetShape(**I)).getLeftCorner(); */
/* 	  cout << "move_to " << move_to << endl; */
/* 	  //	  TranslateLeaf(**I, PositionVector(move_to)); */
/* 	  //	  Point tmp = (GetShape(**I)).getLeftCorner() + move_to; */
/* 	  cout << "Center " << (GetShape(**I)).getCenterPoint(); */
/* 	  cout << "Pet " << GetStartPoint(GetPetiole(**I)); */

	  (**I).move(move_to);
/* 	  cout << "Left " << (GetShape(**I)).getLeftCorner(); */
/* 	  cout << "Center " << (GetShape(**I)).getCenterPoint(); */
/* 	  cout << "Pet " << GetStartPoint(GetPetiole(**I)); */
/* 	  exit(0); */
	}
      }
      return tc;
    }

  private:
  const Point& move_to;
  };



  //IMPLEMENTATION is in TreeFunctorI.h


  //This functor is used (ForEach) to move a tree (=all its
  //TreeCompartments) to a new location.
  //Note that a vector (Point) is added to the current position
  //(vector, i.e. Point). Hence, if you want to move a tree from
  //location (Point) b, you should call the constructor
  //of MoveTree with argument b - a, where a is the current
  //position of the tree. 

  template <class TS,class BUD=DefaultBud<TS> >
    class MoveTree{
  public:
  MoveTree(const MoveTree& move, Tree<TS,BUD>& t)
  :move_to(move.move_to){SetPoint(t,GetPoint(t)+move_to);}
  MoveTree(const MoveTree& move):move_to(move.move_to){}
  //This   constructor  ensures   that  also   the   tree  itself,
  //i.e. GetPoint(tree), is moved.
  MoveTree(const Point& point,Tree<TS,BUD>& t)
  :move_to(point){SetPoint(t,GetPoint(t)+move_to);} 
  MoveTree(const Point& point):move_to(point) {} 
  Point setPoint(const Point& new_point) {
    Point tmp = move_to;
    move_to = new_point;
    return tmp;
  }
  TreeCompartment<TS,BUD>* operator()(TreeCompartment<TS,BUD>* tc)const
  {
    SetPoint(*tc, GetPoint(*tc)+move_to);
    return tc;
  }
  
  private:
  const Point& move_to;
  };


  template <class TS, class BUD=DefaultBud<TS> >
    class DeleteDeadBranches{
      public:
      LGMdouble& operator()(LGMdouble& foliage, TreeCompartment<TS,BUD>* tc)const;
    };


  //Functors for printing information on TreeSegments to file

  template <class TS,class BUD=DefaultBud<TS> >
    class PrintTreeSegmentInformationToFile {
      public:

      PrintTreeSegmentInformationToFile(const string& filename,
					const bool& title)
      :fname(filename)
      {
	if(title) {
	  ofstream f(fname.c_str(),ofstream::app);
	  f << "TIME: no time stamp specified" << endl;
	  f  << "X:Y:Z:diX:diY:diZ:age:omega:R:RTop:Rh:L:Ring:Ws:Wh:"
	  "Wf:W:Af:As0:As:Qin:rTQin:rQin:Qabs:P:M:vigour" << endl;
	  f.close();
	}
      }
      
      PrintTreeSegmentInformationToFile(const string& filename, const int&
					timeStamp, const bool title)
      : fname(filename)
      {
	if(title) {
	  ofstream f(filename.c_str() , ofstream::app);
	  f << "TIME: " << timeStamp << endl;
	  f  << "X:Y:Z:diX:diY:diZ:age:omega:R:RTop:Rh:L:Ring:Ws:Wh:"
	  "Wf:W:Af:As0:As:Qin:rTQin:rQin:Qabs:P:M:vigour" << endl;
	  f.close();
	}
      }
      
      TreeCompartment<TS,BUD>* operator ()(TreeCompartment<TS,BUD>* tc)const;
      
      private:
      string fname;
    };
  
  
  template <class TS,class BUD=DefaultBud<TS> >
      class PrintTreeSegmentInformationToFileByAxis {
	public:
	PrintTreeSegmentInformationToFileByAxis(const string& filename,
						const bool& title)
	:fname(filename)
	{
	  if(title) {
	    ofstream f(fname.c_str(),ofstream::app);
	    f << "By Axis - TIME: no time stamp specified" << endl;
	    f  << "X:Y:Z:diX:diY:diZ:age:omega:R:RTop:Rh:L:Ring:Ws:Wh:"
	    "Wf:W:Af:As0:As:Qin:rTQin:rQin:Qabs:P:M:vigour" << endl;
	    f.close();
	  }
	}
	
	PrintTreeSegmentInformationToFileByAxis(const string& filename, int&
						timeStamp, const bool& title)
	: fname(filename)
	{
	  if(title) {
	    ofstream f(filename.c_str() , ofstream::app);
	    f << "By Axis - TIME: " << timeStamp << endl;
	    f  << "X:Y:Z:diX:diY:diZ:age:omega:R:RTop:Rh:L:Ring:Ws:Wh:"
	    "Wf:W:Af:As0:As:Qin:rTQin:rQin:Qabs:P:M:vigour" << endl;
	    f.close();
	  }
      }
	
	TreeCompartment<TS,BUD>* operator ()(TreeCompartment<TS,BUD>* tc)const;
	
	private:
	string fname;
      };

      



  //cvs update: LignumWB:n käytössä olevat funktorit

  class InfoStruct
    {
    public:
	

      int age;
      LGMdouble sum_QinNA;
      LGMdouble sum_QabsNA;
      LGMdouble sum_Wf;
      LGMdouble sum_Qabs;
      LGMdouble sum_Qin;
      LGMdouble sum_needle_area;
      int num_buds;
      int num_segments;
      LGMdouble height;
      LGMdouble bottom_rad;
      std::vector<LGMdouble> taper_rad;
      std::vector<LGMdouble> taper_hei;
    };



  template <class TS, class BUD>
    class SetOmega
    {
    public:
      int& operator()(int& oomega, TreeCompartment<TS,BUD>* tc)const;
    };



  template <class TS,class BUD>
    class TreeInfo
    { 
    public:
      InfoStruct& operator()(InfoStruct &stru, TreeCompartment<TS,BUD>* tc)const;
    };



  template <class TS,class BUD>
    class TreePartInfo
    { 
    public:
      InfoStruct& operator()(InfoStruct &stru, TreeCompartment<TS,BUD>* tc)const;
      float maxh;
      float minh;
    };



  template <class TS, class BUD, class SHAPE>
    void SaveLeafInfo(Axis<TS,BUD> &ax, ofstream& file);


  template <class TS, class BUD>
    void SaveTree(Axis<TS,BUD> &tr, const string& file_name, 
		  const string& treetype);


  template <class TS, class BUD>
    void WriteTreeInformation(Tree<TS,BUD>&  tr, ofstream& file);




  template <class TS, class BUD>
    class PrintTreeInformationToFile {
    public:
    void operator() (Tree<TS,BUD>&  tr, ostream& os);
  };


  template <class TS, class BUD>
    void SaveAxis(Axis<TS,BUD> &ax, ofstream& file, bool only_segents);


  template <class TS,class BUD>
    class TreeHeight
    {
    public:
      LGMdouble& operator ()(LGMdouble& max_height, TreeCompartment<TS,BUD>* tc)const;
  
    };


  template <class SH>
  class DestroyLeaves{
  public:
    void operator()(BroadLeaf<SH>* leaf){
      delete leaf;
    }
  };

  template <class TS, class BUD,class SH>
  class DropAllLeaves{
  public:
    TreeCompartment<TS,BUD>* operator ()(TreeCompartment<TS,BUD>* tc)const;
  };

  //Collect all leaves in a tree into one list
  template <class TS, class BUD, class SH>
  class CollectLeaves{
  public:
    list<BroadLeaf<SH>*>& operator()(list<BroadLeaf<SH>*>& ls,
				     TreeCompartment<TS,BUD>* tc)const;
  };

  //Sort leaves, leaves closest to the point 'p' appear first
  template <class SH>
  class SortLeaves{
  public:
    SortLeaves(const Point& point):p(point){}
    bool operator()(const BroadLeaf<SH>* l1, const BroadLeaf<SH>* l2){
      const Point& p1 = GetCenterPoint(*l1);
      const Point& p2 = GetCenterPoint(*l2);
      return (p1 || p) < (p2 || p);
    }
    Point p;
  };

  //Sort leaves, leaf with smallest midpoint 'z' first
  template <class SH,class BinaryPredicate>
  class SortLeavesHeight{
  public:
    SortLeavesHeight():f(BinaryPredicate()){}
    bool operator()(const BroadLeaf<SH>* l1, const BroadLeaf<SH>* l2){
      const Point& p1 = GetCenterPoint(*l1);
      const Point& p2 = GetCenterPoint(*l2);
      return f(p1.getZ(),p2.getZ());
    }
  private:
    const BinaryPredicate f;
  };
  

  template <class TS, class BUD> 
    class CrownVolume { 
  public: 
  CrownVolume(double hstep = 0.2): step(hstep) {;}
    double operator()(Tree<TS,BUD>&  tr)const;
  private:
    double step;
  };


  //This finds longest distance of a conifer shoot with foliage
  //to stem and its direction with respect of tree stem
  //Default is that only TreeSegments  that carry foliage (shoots)
  //are tested, this can be overruled with the second argument of
  //constructor.

  template <class TS, class BUD> 
    class FindLongestDistanceToStem {
  public:
  FindLongestDistanceToStem(const Point& st_point, const bool& wwp = false) : 
    stem_point(st_point), with_woody_parts(wwp) {}
    pair<double,PositionVector>& operator() (pair<double,PositionVector>& dat,
					     TreeCompartment<TS,BUD>* tc)const
      {
	if (TS* ts = dynamic_cast<TS*>(tc)){
	  //Exit if no foliage & foliage required 
	  if(!with_woody_parts) {
	    if(GetValue(*ts, LGAWf) <= R_EPSILON)
	      return dat;
	  }
  
	  Point base = GetPoint(*ts);
	  PositionVector d(base.getX()-stem_point.getX(),base.getY()-stem_point.getY(),0.0);
	  double r = d.length();
	  if(r > dat.first) {
	    dat.first = r;
	    d.normalize();
	    dat.second = d;
	  }

	  Point top = GetEndPoint(*ts);
	  d = PositionVector(top.getX()-stem_point.getX(),top.getY()-stem_point.getY(),0.0);
	  r = d.length();
	  if(r > dat.first) {
	    dat.first = r;
	    d.normalize();
	    dat.second = d;
	  }
	}    //is TreeSegment
	return dat;
      }

  private:
    Point stem_point;
    bool with_woody_parts;  //if distance also with parts that
                            //don't carry foliage
  };


//   FindRFunctor         find largest distance to stem in a crown slice
//                        between heights minH and maxH in an angle around
//                        given direction
  //Default is that only TreeSegments  that carry foliage (shoots)
  //are tested, this can be overruled with the last argument of
  //constructor.

  template <class TS, class BUD>
    class FindRFunctor {
    public:
    FindRFunctor(const double& miH,const double& maH, const double& dire,
		 const double& ang, const Point& tb, const bool& wwp = false):
    minH(miH), maxH(maH), dir(dire), angle(ang),  with_woody_parts(wwp)
      {treeBase = PositionVector(tb.getX(),tb.getY(),0.0);}
      //Center of stem in xy-plane 
    double& operator ()(double& R, TreeCompartment<TS,BUD>* tc)const;
    PositionVector& getTreeBase() {return treeBase;}
    private:
    double minH, maxH, dir, angle;
    PositionVector treeBase;  //Center of stem in xy-plane
    bool with_woody_parts;  //if distance also with parts that
                            //don't carry foliage
 };

//   FindRFunctorF        Find mean by foliage weighted distance to stem in a crown slice
//                        between heights minH and maxH in an angle around
//                        given direction
//   Is a modification of FindRFunctor

  template <class TS, class BUD>
    class FindRFunctorF {
    public:
    FindRFunctorF(const double& miH,const double& maH, const double& dire,
		 const double& ang, const Point& tb):
    minH(miH), maxH(maH), dir(dire), angle(ang)
      {treeBase = PositionVector(tb.getX(),tb.getY(),0.0);}
      //Center of stem in xy-plane 
    pair<double, double>& operator ()(pair<double, double>& sums, TreeCompartment<TS,BUD>* tc)const;
    PositionVector& getTreeBase() {return treeBase;}
    private:
    double minH, maxH, dir, angle;
    PositionVector treeBase;  //Center of stem in xy-plane
  };


  template <class TS, class BUD> 
    class CrownExtension { 
    public: 
    CrownExtension(double hstep = 0.2): step(hstep) {;}
    void operator()(Tree<TS,BUD>&  tr, vector<pair<double,vector<double> > >& ext)const;
    private:
    double step;
  };


//  LowestSegmentExcludingStem
//  LowestCfSegmentWithFoliage
//  HighestSegment
//  HighestCfSegmentWithFoliage

  template <class TS, class BUD>
    class LowestSegmentExcludingStem {
  public:
    Point&  operator()(Point& extreme, TreeCompartment<TS,BUD>* tc)const
      {
	if(TS* ts = dynamic_cast<TS*>(tc)){
	  if(GetValue(*ts, LGAomega) > 1.0) {
	    Point p = GetEndPoint(*ts);
	    LGMdouble z = p.getZ();
	    if(z < extreme.getZ())
	      extreme = p;
	    p = GetPoint(*ts);
	    z = p.getZ();
	    if(z < extreme.getZ())
	      extreme = p;
	  }
	}
	return extreme;
      }
  };

  template <class TS, class BUD>
    class LowestCfSegmentWithFoliage {
  public:
    Point&  operator()(Point& extreme, TreeCompartment<TS,BUD>* tc)const
      {
	if(TS* ts = dynamic_cast<TS*>(tc)) {
	  if(GetValue(*ts,LGAWf) > R_EPSILON) {
	    Point p = GetEndPoint(*ts);
	    LGMdouble z = p.getZ();
	    if(z < extreme.getZ())
	      extreme = p;
	    p = GetPoint(*ts);
	    z = p.getZ();
	    if(z < extreme.getZ())
	      extreme = p;
	  }
	}
	return extreme;
      }
  };

  template <class TS, class BUD>
    class HighestSegment {
  public:
    Point&  operator()(Point& extreme, TreeCompartment<TS,BUD>* tc)const
      {
	if(TS* ts = dynamic_cast<TS*>(tc)){
	  Point p = GetEndPoint(*ts);
	  LGMdouble z = p.getZ();
	  if(z > extreme.getZ())
	    extreme = p;
	  p = GetPoint(*ts);
	  z = p.getZ();
	  if(z > extreme.getZ())
	    extreme = p;
	}
	return extreme;
      }
  };

  template <class TS, class BUD>
    class HighestCfSegmentWithFoliage {
  public:
    Point&  operator()(Point& extreme, TreeCompartment<TS,BUD>* tc)const
      {
	if(TS* ts = dynamic_cast<TS*>(tc)){
	  if(GetValue(*ts,LGAWf) > R_EPSILON) {
	    Point p = GetEndPoint(*ts);
	    LGMdouble z = p.getZ();
	    if(z > extreme.getZ())
	      extreme = p;
	    p = GetPoint(*ts);
	    z = p.getZ();
	    if(z > extreme.getZ())
	      extreme = p;
	  }
	}
	return extreme;
      }
  };

  template <class TS,class BUD>
  class AccumulateAxisVolume{
    public:
    double operator()(double v,TreeCompartment<TS,BUD>* tc)const
    {
      if (TS* ts = dynamic_cast<TS*>(tc)){
	v = v + GetValue(*ts,LGAV);
      }
      return v;
    }
  };

  template <class TS,class BUD>
  class MainAxisVolume{
  public:
    double operator()(Tree<TS,BUD>& t)const
    {
      Axis<TS,BUD>& axis = GetAxis(t);
      list<TreeCompartment<TS,BUD>*>& tc_ls = GetTreeCompartmentList(axis);
      double vol = accumulate(tc_ls.begin(),tc_ls.end(),0.0,AccumulateAxisVolume<TS,BUD>());
      return vol;
    }
  };

  template <class TS,class BUD>
  class SetRTopToR{
  public:
    void operator()(TreeCompartment<TS,BUD>* tc)const{
      if (TS* ts = dynamic_cast<TS*>(tc)){
	SetValue(*ts,LGARTop, GetValue(*ts,LGAR));
      }
    }
  };

  template <class TS, class BUD> 
  class ResetQinQabs{
  public:
    TreeCompartment<TS,BUD>* operator()(TreeCompartment<TS,BUD>* tc)const{
      if (TS* ts = dynamic_cast<TS*>(tc)){
	SetValue(*ts,LGAQin,0.0);
	SetValue(*ts,LGAQabs,0.0);
      }
      return tc;
    }
  };

  //This functor writes to the console the tree (the woody parts) in the STL format
  //(set of triangles). "STL files describe only the surface geometry of a three dimensional
  //object without any representation of color, texture or other common CAD model attributes.
  //The functor treats TreeSegments cylinders as consisting of rectangles (facets). One rectangle
  //consists of two triangles. The number of facets and the minimum length of a TreeSegment
  //that is considered are the optional parameters. Default values are 6 and 0.001 m. 

  template <class TS,class BUD>
  class STL_Triangularize{
  public:
  STL_Triangularize(int n_rot = 6, LGMdouble mL = 0.001) : n_rotation(n_rot),
      minL(mL) {}

    TreeCompartment<TS,BUD>* operator()(TreeCompartment<TS,BUD>* tc)const{
      if (TS* ts = dynamic_cast<TS*>(tc)){
	LGMdouble length = GetValue(*ts,LGAL);
	if(length < minL)
	  return tc;

	LGMdouble R = GetValue(*ts, LGAR);
	LGMdouble Rt = GetValue(*ts, LGARTop);
	if(Rt < 1.0e-10)
	  Rt = R;

	PositionVector dir = GetDirection(*ts);
	dir.normalize();

	Point p_b = GetPoint(*ts);

	list<LGMTriangle> triangles = LGMTriangularize(n_rotation, p_b, dir, length, R, Rt);

	cout.setf(ios_base::scientific, ios_base::floatfield);

       	list<LGMTriangle>::iterator it;
	for(it = triangles.begin(); it != triangles.end(); it++) {
	  PositionVector norm = (*it).getNormal();
	  Point left = (*it).getA();
	  Point right = (*it).getB();
	  Point apex = (*it).getC();

	  cout << "facet normal " << norm.getX() << " " << norm.getY() << " " << norm.getZ()
	       << endl;
	  cout << "   outer loop" << endl;
	  cout << "      vertex " << left.getX() << " " << left.getY() << " " << left.getZ()
	       << endl;
	  cout << "      vertex " << right.getX() << " " << right.getY() << " " << right.getZ()
	       << endl;
	  cout << "      vertex " << apex.getX() << " " << apex.getY() << " " << apex.getZ() <<
	    endl;
	  cout << scientific << "   endloop" << endl;
	  cout << scientific << "endfacet" << endl;
	}
	cout.setf(ios_base::fmtflags(0), ios_base::floatfield);

      }   //if (TS* ts = dynamic_cast<TS
      return tc;
    }
  private:
    int n_rotation;
    LGMdouble minL;          //segments shorter than minimum length are not triangularized
  };

  //Implements Da Vinci rule tapering: R_base^exp = R_1^exp+R_2^exp+...+R_n^exp
  //Usually the exponent is 2.0.
  //Usage: AccumulateDown(tree,0.0,DaVinciTaperCurve(init_radius,exponent))
  template <class TS, class BUD>     
  class DaVinciTaperCurve{
  public:
    DaVinciTaperCurve(const DaVinciTaperCurve& dv)
      :init_radius(dv.init_radius),exponent(dv.exponent){}
    DaVinciTaperCurve(double r, double e)
      :init_radius(r),exponent(e){}
    double operator()(double radius_e, TreeCompartment<TS,BUD>* tc)const;
  private:
    mutable double init_radius;//The initial radius for the first segments
    double exponent;//The exponent defining tapering, usually 2.0
  };


//  Vertical leaf area disrtribution
  template <class TS, class BUD>     
  class VerticalLeafAreaDistribution{
  public:
  VerticalLeafAreaDistribution(const double mi_z, const double ma_z, const double stp):
    min_z(mi_z), max_z(ma_z), step(stp) {}
    vector<double>& operator() (vector<double>& distn, TreeCompartment<TS,BUD>* tc)const{
    if (TS* ts = dynamic_cast<TS*>(tc)){
      double Af = GetValue(*ts, LGAAf);
      if(Af > 0) {
	double z = GetMidPoint(*ts).getZ();
	if(z < min_z || z > max_z) {
	  return distn;
	}
	int i = static_cast<int>((z-min_z)/step);
	distn[i] += Af;
      }
    }
    return distn;
    }

  private:
    double min_z;
    double max_z;
    double step;
  };

  ///\brief Cancel new growth.
  ///
  ///Set new tree segments dimensions to 0.0.
  ///\pre LGAage == 0.0
  ///\param tc TreeCompartment
  ///\post LGAWf == 0.0;
  ///\post LGAL == 0.0;
  ///\post LGAR == 0.0;
  ///\post LGARh == 0.0;
  ///\retval tc TreeCompartment
  ///\note Use with ForEach 
  template <class TS, class BUD> 
  class CancelNewGrowth{
  public:
    TreeCompartment<TS,BUD>* operator()(TreeCompartment<TS,BUD>* tc)const
    {
      if (TS* ts = dynamic_cast<TS*>(tc)){
	if (GetValue(*ts,LGAage) == 0.0){
	  SetValue(*ts,LGAWf,0.0);
	  SetValue(*ts,LGAL,0.0);
	  SetValue(*ts,LGAR,0.0);
	  SetValue(*ts,LGARh,0.0);
	}
      }
      return tc;
    }
  };
}//closing namespace Lignum
#include <TreeFunctorI.h>

#endif

















