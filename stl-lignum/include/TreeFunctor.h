#ifndef TREEFUNCTOR_H
#define TREEFUNCTOR_H

#include <iostream>

#include <LGMdecl.h>
#include <TreeCompartment.h>
#include <BroadLeaf.h>
#include <Algorithms.h>

namespace Lignum{

  //PrintTreeInformation collects and prints out information about the
  //tree. It uses functor TreeData to collect the information with
  //Accumulate

  template <class TS, class BUD>
    class PrintTreeInformation {
    public:
    void operator() (Tree<TS,BUD>&  tr);
  };

  //TreeData is used to collect (Accumulate) data on a tree.
  //it uses TreeDataStruct

  class TreeDataStruct {
  public:
    TreeDataStruct() {
      age = 0;
      sum_Wf = 0.0;
      sum_Wf_new = 0.0;
      sum_wood_in_newparts = 0.0;
      sum_wood_new = 0.0;
      sum_Ws = 0.0;
      sum_Wb = 0.0;
      sum_Wsw = 0.0;
      sum_Whw = 0.0;
      sum_Qabs = 0.0;
      sum_Qin = 0.0;
      num_buds = 0;
      num_segments = 0;
      height = 0.0;
      bottom_rad = 0.0;
      Hc = R_HUGE;
      num_s_fol = 0;
      num_br_l = 0;
      num_br_d = 0;
      sum_br_len = 0.0;
      sum_br_len_d = 0.0;

      sum_br_As = 0.0;
      sum_br_Ac = 0.0;

    }

    TreeDataStruct& operator += (const TreeDataStruct& s) {
      if(this->age < s.age)
	this->age = s.age;
      this->sum_Wf += s.sum_Wf;
      this->sum_Wf_new += s.sum_Wf_new;
      this->sum_wood_in_newparts += s.sum_wood_in_newparts;
      this->sum_wood_new += s.sum_wood_new;
      this->sum_Ws += s.sum_Ws;
      this->sum_Wb += s.sum_Wb;
      this->sum_Wsw += s.sum_Wsw;
      this->sum_Whw += s.sum_Whw;
      this->sum_Qabs += s.sum_Qabs;
      this->sum_Qin += s.sum_Qin;
      this->num_buds += s.num_buds;
      this->num_segments += s.num_segments;
      if(this->height < s.height)
	this->height =  s.height;
      if(this->bottom_rad < s.bottom_rad)
	this->bottom_rad = s.bottom_rad;
      if(this->Hc > s.Hc)
	this->Hc = s.Hc;
      this->num_s_fol += s.num_s_fol;
      this->num_br_l += s.num_br_l;
      this->num_br_d += s.num_br_d;
      this->sum_br_len += s.sum_br_len;
      this->sum_br_len_d += s.sum_br_len_d;
      return *this;
    }


    int age;
    LGMdouble sum_Wf;          //All foliage
    LGMdouble sum_Wf_new;      //Foliage in segments (int)age == 0
    LGMdouble sum_wood_in_newparts; //Wood in segments (int)age == 0
    LGMdouble sum_wood_new;    //sum_wood_in_newparts+last ring
    LGMdouble sum_Ws;          // Stemwood
    LGMdouble sum_Wb;          // Branchwood
    LGMdouble sum_Wsw;         // Sapwood (in all segments)
    LGMdouble sum_Whw;         // Heartwood (in all segments)
    LGMdouble sum_Qabs;         // Absorbed radiation
    LGMdouble sum_Qin;         // Incoming radiation
    LGMdouble sum_br_As;
    LGMdouble sum_br_Ac; 
    int num_buds;
    int num_segments;
    LGMdouble height;
    LGMdouble bottom_rad;
    LGMdouble Hc;               //Height of grown base
    int num_s_fol;              //number of segments with foliage
    int num_br_l;               //number of branches living
    int num_br_d;               //number of branches dead
    LGMdouble sum_br_len;       //total length of branches, living
    LGMdouble sum_br_len_d;     //total length of branches, dead
    std::vector<LGMdouble> taper_rad;
    std::vector<LGMdouble> taper_hei;
    std::vector<LGMdouble> taper_radhw;
    std::vector<LGMdouble> mean_brl;
    std::vector<LGMdouble> mean_br_h;

    std::vector<LGMdouble> taper_radh;
  };


  template <class TS,class BUD>
    class TreeData
    { 
    public:
      TreeDataStruct& operator()(TreeDataStruct& stru,
				 TreeCompartment<TS,BUD>* tc)const;
    };


  //A functor to print out the datatype
  //of a tree compartment
  template <class TS,class BUD=DefaultBud<TS> >
    class DisplayType{
      public:
      TreeCompartment<TS,BUD>*  operator ()(TreeCompartment<TS,BUD>* ts)const;
    };

  template <class TS,class BUD=DefaultBud<TS> >
    class DisplayType2: public AdaptableTCFunction<TS,BUD>{
      public:
      TreeCompartment<TS,BUD>* operator ()(TreeCompartment<TS,BUD>* ts)const;
    };

  template <class TS,class BUD=DefaultBud<TS> >
    class CountTreeSegments{
      public:
      int& operator ()(int& id,TreeCompartment<TS,BUD>* ts)const;
    };

	/*

	Tämän totuetus on kadonnut??? 12.6.2003
  template <class TS,class BUD=DefaultBud<TS> >
    class FillWithWater:  public AdaptableTCFunction<TS,BUD>{
      public:
      TreeCompartment<TS,BUD>* operator()(TreeCompartment<TS,BUD>* tc)const;
    };
	*/


  template <class TS,class BUD=DefaultBud<TS> >class CountCompartments{
    public:
    int& operator ()(int& id,TreeCompartment<TS,BUD>* ts)const;
  };



  template <class TS,class BUD=DefaultBud<TS> >
    class CountCompartmentsReverse{
      public:
      int& operator ()(int& id,TreeCompartment<TS,BUD>* ts)const;
    };

  template <class TS,class BUD=DefaultBud<TS> >
    class MyExampleSignal{
      public:
      int operator ()(int id,TreeCompartment<TS,BUD>* ts)const;
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


  template <class TS, class BUD>
    Point GetBoundingBox(Tree<TS,BUD> &tree, Point &p);


  template <class TS, class BUD>
    Point GetBoundingBox(Axis<TS,BUD> &ax, Point &p);



  //This class holds the values of the coordinates that define box that
  //holds the tree - or several trees.

  class BoundingBox { 
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
  //box for it

  template <class TS,class BUD>
    class FindBoundingBox{
    public:
    BoundingBox& operator ()(BoundingBox& b_box,
			     TreeCompartment<TS,BUD>* tc)const;
  };



  



  template <class TS,class BUD>
    class CollectFoliageMass
    { 
    public:
      LGMdouble& operator()(LGMdouble &sum, TreeCompartment<TS,BUD>* tc)const;
    };



  //This functor is used (ForEach) to move a tree (=all its
  //TreeCompartments) to a new location.

  template <class TS,class BUD=DefaultBud<TS> >
    class MoveTree:  public AdaptableTCFunction<TS,BUD>{
      public:
      MoveTree(const Point& point) {move_to = point;} 
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
      Point move_to;
    };


  template <class TS, class BUD=DefaultBud<TS> >
    class DeleteDeadBranches{
      public:
      LGMdouble& operator()(LGMdouble& foliage, TreeCompartment<TS,BUD>* tc)const;
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

/*
	template <class TS, class BUD>
	TreeCompartment<TS,BUD>* DropAllLeaves<TS,BUD>::operator ()(TreeCompartment<TS,BUD>* tc)const;

*/

}//closing namespace Lignum
#include <TreeFunctorI.h>

#endif

















