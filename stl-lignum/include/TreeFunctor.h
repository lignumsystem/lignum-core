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

//This file declares the following functors (functions) for Tree. Help
//functors etc. are not specified. If you add a functor-function
//please update this list.

//   CountTreeSegments
//   ForwardQin (for coniferous)
//   PrintTreeInformation
//   PrintTreeInformation2
//   CountCompartments
//   CountCompartmentsReverse
//   SetGraveliusOrder
//   DisplayStructure
//   CheckCoordinates
//   FindCfBoundingBox
//   FindHwBoundingBox
//   CollectFrustumVolume
//   CollectFoliageMass
//   CollectFoliageArea
//   CollectWoodMass
//   CollectSapwoodMass
//   CollectStemSapwoodMass
//   CollectHeartwoodMass
//   CollectNewSegmentSapwoodMass (LGAage == 0.0)
//   CollectOldSegmentSapwoodMass (LGAage > 0.0)
//   CollectNewFoliageMass        (LGAage == 0.0)
//   CollectQabs
//   CollectQin
//   GetQinMax
//   MoveTree
//   DeleteDeadBranches
//   PrintTreeSegmentInformationToFile
//   PrintTreeSegmentInformationToFileByAxis
//   DropAllLeaves
//   CollectLeaves: return a 'list<BroadLeaf<SH>*> ls' of leaves in a tree
//                  Usage: Accumulate(t,ls,CollectLeaves<TS,BUD,SH>());
//   SortLeaves: sort leaves (returned by CollectLeaves), leaves closest to the 
//               point 'p' appear first
//               Usage: Point p(0,0,0);
//                      SortLeaves<SH> sorter(p);
//                      ls.sort(sorter);
//   SortLeavesHeight:  sort  leaves  (returned by  CollectLeaves)  in
//               height defined by BinaryPredicate (see STL)
//             Usage:
//               SortLeavesHeight<SH,BinaryPredicate>           sorter; 
//               ls.sort(sorter);
//             To sort in descending order (lowest leaf first)
//               SortLeavesHeight<Ellipse,less_equal<double> > sorter;
//             To sort in ascending order
//               SortLeavesHeight<Ellipse,greater_equal<double> > sorter;
//   CrownVolume
//   MainAxisVolume: Usage MainAxisVolume vol; double v = vol(tree);
//   SetRTopToR: Set LGARTop to LGAR: SetValue(ts,LGARTop, GetValue(*ts,LGAR)). 
//               Usage: ForEach(tree, SetRTopToR<TS,BUD>()).  
//               There is  LGARTop that used in  visualiztion.  It may
//               or may not  have the desired value. In  most cases in
//               growth simulations only LGAR  is used.  This may have
//               unwanted results in visualization.
//  Functors-functions below used in LIGNUM WorkBench are not listed.

namespace Lignum{

   template <class TS,class BUD>
     class CountTreeSegments {
     public:
     int& operator()(int& n,TreeCompartment<TS,BUD>* tc)const
       {
	 if (dynamic_cast<TS*>(tc)!=NULL)
	   n+=1;
	 return n;
       }
   };

  //PrintTreeInformation collects and prints out information about the
  //tree. It uses functor TreeData to collect the information with
  //Accumulate

   //PrintTreeInformation prints either to file or to console. The
   //stream is given as a template.
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
    else
      ;
    
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
    Point getMin() { return minxyz; }
    Point getMax() { return maxxyz; }
    void setMinX(const LGMdouble x) { minxyz.setX(x); }
    void setMinY(const LGMdouble y) { minxyz.setY(y); }
    void setMinZ(const LGMdouble z) { minxyz.setZ(z); }
    void setMaxX(const LGMdouble x) { maxxyz.setX(x); }
    void setMaxY(const LGMdouble y) { maxxyz.setY(y); }
    void setMaxZ(const LGMdouble z) { maxxyz.setZ(z); }
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
    BoundingBox& operator ()(BoundingBox& b_box,
			     TreeCompartment<TS,BUD>* tc)const;
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

  template <class TS,class BUD>
    class CollectFoliageMass
    { 
    public:
      LGMdouble& operator()(LGMdouble &sum, TreeCompartment<TS,BUD>* tc)const;
    };

  template <class TS,class BUD>
    class CollectFoliageArea
    { 
    public:
      LGMdouble& operator()(LGMdouble &sum, TreeCompartment<TS,BUD>* tc)const;
    };

  template <class TS,class BUD>
    class CollectWoodMass
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


  //This functor is used (ForEach) to move a tree (=all its
  //TreeCompartments) to a new location.

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
      Point& setPoint(const Point& new_point) {
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
  
//   CrownVolume
// For explanation how it works, look for TreeFunctorI.h

// Helper functor for CrownVolume

  template <class TS, class BUD>
    class findRFunctor {
    public:
    findRFunctor(const double& miH,const double& maH, const double& dire,
		 const double& ang, const Point& tb):
      minH(miH), maxH(maH), dir(dire), angle(ang)
      {treeBase = PositionVector(tb.getX(),tb.getY(),0.0); }
      //Center of stem in xy-plane 
    double& operator ()(double& R, TreeCompartment<TS,BUD>* tc)const;
    PositionVector& getTreeBase() {return treeBase;}
    private:
    double minH, maxH, dir, angle;
    PositionVector treeBase;  //Center of stem in xy-plane
  };



  template <class TS, class BUD> 
    class CrownVolume { 
    public: 
    CrownVolume(double hstep = 0.2): step(hstep) {;}
    double operator()(Tree<TS,BUD>&  tr)const;
    private:
    double step;
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

}//closing namespace Lignum
#include <TreeFunctorI.h>

#endif

















