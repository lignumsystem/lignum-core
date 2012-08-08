#ifndef TREE_FUNCTORI_H
#define TREE_FUNCTORI_H

#include <iomanip>
//This file contains implementation of the following functors
//(functions) for Tree. Help functors etc. are not specified. If you
//add a functor-function please update this list.

//   CountCompartments
//   CountCompartmentsReverse
//   PrintTreeInformation
//   PrintTreeInformation2
//   DisplayStructure
//   CheckCoordinates
//   FindCfBoundingBox
//   FindHwBoundingBox
//   CollectFrustumVolume
//   CollectFoliageMass
//   CollectFoliageArea
//   CollectWoodMass
//   CollectStemWoodMass
//   CollectSapwoodMass
//   CollectStemSapwoodMass
//   CollectHeartwoodMass
//   CollectNewSegmentSapwoodMass (LGAage == 0.0)
//   CollectOldSegmentSapwoodMass (LGAage > 0.0)
//   CollectNewFoliageMass        (LGAage == 0.0)
//   CollectQabs
//   MoveTree
//   DeleteDeadBranches
//   PrintTreeSegmentInformationToFile
//   PrintTreeSegmentInformationToFileByAxis
//   DropAllLeaves
//   CrownVolume



//Functors-functions below used in LIGNUM WorkBench are not listed. 

namespace Lignum{

  template <class TS,class BUD>
  int& CountCompartments<TS,BUD>::
  operator()(int& n,TreeCompartment<TS,BUD>* tc)const
  {
    if (dynamic_cast<Axis<TS,BUD>*>(tc)){
      cout << "Hello, I'm Axis ";
    }

    else if (dynamic_cast<BranchingPoint<TS,BUD>*>(tc)){
      cout << "Hello, I'm BranchingPoint ";
    }

    else if (dynamic_cast<TS*>(tc))
      cout << "Hello, I'm TreeSegment ";

    else if (dynamic_cast<Bud<TS,BUD>*>(tc))
      cout << "Hello, I'm Bud ";

    else
      cout << "Who am I??? ";
    //counting them all
    n+=1;
    cout << n << endl;
    return n;
  }


  template <class TS,class BUD>
  int& CountCompartmentsReverse<TS,BUD>::
  operator()(int& n, TreeCompartment<TS,BUD>* tc)const
  {
    if (dynamic_cast<Axis<TS,BUD>*>(tc)){
      cout << "Hello, I'm Axis ";
    }

    else if (dynamic_cast<BranchingPoint<TS,BUD>*>(tc)){
      cout << "Hello, I'm BranchingPoint ";
    }

    else if (dynamic_cast<TS*>(tc))
      cout << "Hello, I'm TreeSegment ";

    else if (dynamic_cast<Bud<TS,BUD>*>(tc))
      cout << "Hello, I'm Bud ";

    else
      cout << "Who am I??? ";

    //counting them all
    n+=1;
    cout << n << endl;
    return n;
  }


  //This functor searches longest distance to stem in four quadrants
  //(they are in vector in counterclockwise order)

  template <class TS,class BUD>
  vector<LGMdouble>& CrownGroundArea<TS,BUD>::operator ()(vector<LGMdouble>& v,TreeCompartment<TS,BUD>* tc) const {
    if (Bud<TS,BUD>* bd = dynamic_cast<Bud<TS,BUD>*>(tc)) {
      Point pos = GetPoint(*bd) - stem_point;
      LGMdouble x = pos.getX();
      LGMdouble y = pos.getY();
      LGMdouble r = sqrt(x*x + y*y);
      int quadrant = 0;
      if(x > 0.0)
	if(y > 0.0)
	  quadrant = 0;
	else
	  quadrant = 3;
      else
	if(y > 0.0)
	  quadrant = 1;
	else
	  quadrant = 2;

      if(r > v[quadrant])
	v[quadrant] = r;

    }

    return v;
  }



  //PrintTreeInformation collects and prints out information about the
  //tree. It uses functor TreeData to collect the information with
  //Accumulate

  template <class TS, class BUD, class STREAM>
  void PrintTreeInformation<TS,BUD,STREAM>::operator() (Tree<TS,BUD>&  tr) {

    TreeDataStruct values;
    TreeData<TS,BUD> getTreeValues;
  
    values = Accumulate(tr, values, getTreeValues);

    //Diameter and heigth at the crown base.
    DCLData dcl;
    AccumulateDown(tr,dcl,AddBranchWf(),
    		   DiameterCrownBase<TS,BUD>());
    LGMdouble d13 = GetValue(tr,LGADbh);
    LGMdouble d13hw = GetValue(tr,LGADbhHw);
    cout << "d13: " << d13 << " d13hw: " << d13hw << endl; 
    if(d13 < R_EPSILON) d13 = 0.0;
    if(d13 < R_EPSILON) d13hw = 0.0;
    LGMdouble  dbhw= GetValue(tr, LGADbaseHw);
    LGMdouble  db= GetValue(tr, LGADbase);

    //out is either equal to cout or a file

    out.precision(2);
    out.setf(ios_base::right,ios_base::fixed);


    out << endl;
    out << "age: " << values.age << "  growth cycles" << endl;
    out << "Tree height: " << values.bolLen << " m,  highest point: "
	<< values.tHeight << " m, Height of crown base: "
	<< values.Hc << "  m" << endl;
    out.precision(1);
    out << "Basal diameter: "  << setw(4) << 100*db
	<< " cm, Heartwood d at base:  " << setw(4) << 100*dbhw
	<< " cm" <<endl;
    out << "Diameter at BH: "  << setw(4) << 100*d13
	<< " cm, Heartwood at BH:      " << setw(4) << 100*d13hw
	<< " cm" <<endl;

    out << "Diameter at CB: "  << setw(4) << 100*dcl.DCrownBase()
	<< " cm, Heartwood at CB:      " << setw(4) << 100*dcl.DHWCrownBase()
	<< " cm" <<endl;
    
    out.precision(4);
    out << "Foliage mass:                       " << values.sum_Wf
	<< "  kg C,  Foliage area:  " << values.sum_Af << " m2" << endl;
    out << "F. mass in new parts:               " << values.sum_Wf_new
	<< "  kg C" << endl;
    out << "Wood m. in new parts:               "
	<< values.sum_wood_in_newparts << "  kg C" << endl;
    out << "Wood .m in new parts & annual ring: " << values.sum_wood_new
	<< "  kg C" << endl;
    out << "Mass of stemwood:                   " << values.sum_Ws
	<< "  kg C" << endl;
    out << "Mass of branchwood:                 " << values.sum_Wb
	<< "  kg C" << endl;
    out << "Mass of sapwood:                    " << values.sum_Wsw
	<< "  kg C" << endl;
    out << "Mass of heartwood:                  " << values.sum_Whw
	<< "  kg C" << endl;

    out.precision(2);

    if(values.sum_Wf+values.sum_Wsw+GetValue(tr,TreeWr) > 0.0)
      out << "Foliage area / Biomass (cm2/g DM):  " << 10.0*values.sum_Af/
	(values.sum_Wf+values.sum_Ws+GetValue(tr,TreeWr)) << endl;
    else
      out << "Foliage area / Biomass (m2/kg C):  " << 0.0 << endl;


    out.precision(1);
    if(db > R_EPSILON) {
      out << "FolA/Cross-sec A at base, m2/m2:  "
	  << setw(6)<< values.sum_Af/(PI_VALUE*db*db/4.0)
	  << " FolA/Sapwood A at base, m2/m2: "
	  << setw(6) <<values.sum_Af/(PI_VALUE*(db*db-
						dbhw*dbhw)/4.0)
	  << endl;
    }
    else {
      out << "FolA/Cross-sec A at base, m2/m2:  "
	  << setw(6)<< 0.0
	  << " FolA/Sapwood A at base, m2/m2: "
	  << setw(6)<< 0.0  << endl;
    }


    if(d13 > R_EPSILON) {
      out << "FolA/Cross-sec A at BH, m2/m2:    "
	  << setw(6)<< values.sum_Af/(PI_VALUE*d13*d13/4.0)
	  << "FolA/Sapwood A at BH, m2/m2:    "
	  << setw(6)<< values.sum_Af/(PI_VALUE*(d13*d13-
						d13hw*d13hw)/4.0)
	  << endl;
    }
    else {
      out << "FolA/Cross-sec A at BH, m2/m2:    "
	  << setw(6)<< 0.0
	  << " FolA/Sapwood A at BH, m2/m2:   "
	  << setw(6)<< 0.0  << endl;
    }

    if(dcl.DCrownBase() > R_EPSILON) {
      out << "FolA/Cross-sec A at CB, m2/m2:    " <<setw(6)
	  << values.sum_Af/(PI_VALUE*dcl.DCrownBase()*dcl.DCrownBase()/4.0)
	  << " FolA/Sapwood A at CB, m2/m2:   " << setw(6)
	  << values.sum_Af/(PI_VALUE*(dcl.DCrownBase()*dcl.DCrownBase()-
				      dcl.DHWCrownBase()*dcl.DHWCrownBase())/4.0)
	  << endl;
    }
    else {
      out << "FolA/Cross-sec A at CB, m2/m2:    "
	  << setw(6)<< 0.0
	  << " FolA/Sapwood A at CB, m2/m2:   "
	  << setw(6)<< 0.0
	  << endl;
    }

    out.precision(2);

    if(values.num_s_fol > 0) {
      out << "Qabs:                               "
	  << values.sum_Qabs <<"  mean_Qabs: " 
	  << values.sum_Qabs/(double)values.num_s_fol << endl;
      out << "QinMax:                             "
	  << values.max_Qin <<  "  mean_Qin: "
	  << values.sum_Qin/(double)values.num_s_fol << endl;
    }

    else {
      out << "Qabs:                               " << values.sum_Qabs 
	  << "  mean_Qabs: " << 0.0 << endl;
      out << "QinMax:                             " << values.sum_Qin
	  << "  mean_Qin: " <<  0.0 << endl;
    }
  
    if(values.sum_Qin > R_EPSILON && values.sum_Wf > R_EPSILON) {
      LGMdouble Qi = GetFirmament(tr).diffuseBallSensor();
      if(Qi > R_EPSILON && values.sum_Af > R_EPSILON)
	out << "Qabs/(Qin*Foliage area) =           "
	    << values.sum_Qabs/(Qi*values.sum_Af)
	    << "    (should be < 1 ?)" << endl;
    }

    out.precision(4);
    out << "Photosynthesis during growth cycle: " <<
      GetValue(tr,TreeP) << " kgC,  Respiration: "
	<< GetValue(tr,TreeM) << "  kgC" << endl;
    out.precision(2);

    out << "Number of buds:                     "
	<< values.num_buds << endl;
    out << "Number of segments:                 "
	<< values.num_segments 
	<<  " Segments w/ foliage: " << values.num_s_fol << endl;
    out << "No. branches,  living:              "
	<< values.num_br_l << "   dead: "
	<< values.num_br_d << endl;
    if(values.num_br_l > 0)
      out << "Mean len of living branches:        "
	  << values.sum_br_len/(double)values.num_br_l << endl;
    else
      out << "Mean len of living branches:        " << 0.0 << endl;
    if(values.num_br_d > 0)
      out << "Mean len of dead branches:          "
	  << values.sum_br_len_d/(double)values.num_br_d << endl;
    else
      out << "Mean len of dead branches:         " << 0.0 << endl;

    out << "   Height, m    Diameter, cm,   HwDiameter, cm" << endl;
    for(unsigned int i1 = 0; i1 < values.taper_hei.size(); i1++) {
      out << "     " << values.taper_hei[i1] << "          " <<
	200.0*values.taper_rad[i1]<< "          " <<
	200.0*values.taper_radhw[i1] << endl;
    }
    out << endl;

    out << "H of whorl, m     Mean branch l, m" << endl;
    out.setf(ios_base::right,ios_base::adjustfield);
    out.precision(2);
    for(unsigned int i1 = 0; i1 < values.mean_br_h.size(); i1++) {
      out << "     " << values.mean_br_h[i1] << "          " <<
	values.mean_brl[i1] << endl;

    }
    out << endl;
  }


  //Functor PrintTreeInformation2 prints out tree information to a
  //file (given as a parameter to constructor (a ofstream)) one row in
  //each growth cycle for plotting purposes etc.  Calculates the
  //values with the same methods as PrintTreeInformation.

  template <class TS, class BUD>
  void PrintTreeInformation2<TS,BUD>::operator() (Tree<TS,BUD>&  tr) {

    TreeDataStruct values;
    TreeData<TS,BUD> getTreeValues;
  
    values = Accumulate(tr, values, getTreeValues);

    //Diameter and heigth at the crown base.
    DCLData dcl;
    AccumulateDown(tr,dcl,AddBranchWf(),
    		   DiameterCrownBase<TS,BUD>());
    LGMdouble d13 = GetValue(tr,LGADbh);
    LGMdouble d13hw = GetValue(tr,LGADbh);
    if(d13 < R_EPSILON) d13 = 0.0;
    if(d13 < R_EPSILON) d13hw = 0.0;
    //Unused variable dbhw
    //LGMdouble  dbhw= GetValue(tr, LGADbaseHw);
    LGMdouble  db= GetValue(tr, LGADbase);

    int noSeg0 = 0;
    noSeg0 = Accumulate(tr,noSeg0,GetNewZeroSegments<TS,BUD>());
    int noSegAll = 0;
    noSegAll = Accumulate(tr,noSegAll,GetNewSegments<TS,BUD>());

    out << values.age << " " << 100*db << " " << 100*d13 << " "
	<< values.bolLen << " " << values.Hc << " " << values.sum_Wf
	<< " "
	<< values.sum_Ws << " " << values.sum_Wb << " " << values.sum_Af
	<< " "
	<< 10.0*values.sum_Af/(values.sum_Wf+values.sum_Wb+values.sum_Ws+
			       GetValue(tr,TreeWr))
	<< " " << values.max_Qin << " " <<  values.sum_Qabs << " "
      //Note that TreeP and TreeM must be set/updated before GetValue
  	<< GetValue(tr,TreeP) << " " << GetValue(tr,TreeM)
	<< " " <<  values.num_segments << " " << values.num_buds
	<< " " << noSegAll << " " << noSeg0 << " " << values.num_br_l 
	<< " " << GetValue(tr,TreeWr) << endl;
  }


  template <class TS,class BUD> void DisplayStructure(Tree<TS,BUD>& t)
  {
    DisplayStructure(&GetAxis(t));
    cout <<endl;
  }

  template <class TS,class BUD> void DisplayStructure(TreeCompartment<TS,
						      BUD>* tc)
  {
    if (Axis<TS,BUD>* myaxis =  dynamic_cast<Axis<TS,BUD>*>(tc)){
      cout << "["; //begin of axis
      list<TreeCompartment<TS,BUD>*>& tc_ls =
	GetTreeCompartmentList(*myaxis);
      typename list<TreeCompartment<TS,BUD>*>::iterator first =
	tc_ls.begin();
      typename list<TreeCompartment<TS,BUD>*>::iterator last = tc_ls.end();
      while (first != last)
	DisplayStructure(*first++);
      cout << "]" << flush; //end of axis
    }

    else if (BranchingPoint<TS,BUD>* mybp =
	     dynamic_cast<BranchingPoint<TS,BUD>*>(tc)){
      cout << "{"; //begin of branching point
      list<Axis<TS,BUD>*>& axis_ls = GetAxisList(*mybp);
      typename list<Axis<TS,BUD>*>::iterator first = axis_ls.begin();
      typename list<Axis<TS,BUD>*>::iterator last = axis_ls.end();
      for (unsigned int i = 0; i <axis_ls.size(); i++){
	DisplayStructure(*first++);
      }
      //the end of the branching point
      //the comma is because at least a bud follows  
      cout << "}," << flush; 
    }

    else if (dynamic_cast<TS*>(tc)){
      //the comma is because we know that a branching point will follow 
      cout << "TS," << flush;
    
    }

    else if (dynamic_cast<Bud<TS,BUD>*>(tc)){
      cout << "B" << flush;
    }
  }

  template <class TS,class BUD> DisplayStructureData&
  DisplayStructureFunctor<TS,BUD>:: operator
  ()(DisplayStructureData& id, TreeCompartment<TS,BUD>* tc)const
  {
    //collect data: number of compartments in an axis and tell the
    //first segment it is the first segment in that axis
    if (Axis<TS,BUD>* axis = dynamic_cast<Axis<TS,BUD>*>(tc)){
      list<TreeCompartment<TS,BUD>*> ls = GetTreeCompartmentList(*axis);
      id.number_of_compartments = ls.size();
      id.first_segment = true;
      cout <<  "[" << flush;
      if (ls.empty())
	cout <<  "]" << flush;
    }

    else if (BranchingPoint<TS,BUD>* bp =
	     dynamic_cast<BranchingPoint<TS,BUD>*>(tc)){
      cout <<  "{" << flush; 
    }

    else if (TS* ts = dynamic_cast<TS*>(tc)){
      //if not the first segment, ending a branching point
      if (!id.first_segment){
	cout << "}," << flush;
      }
      //tell the next segment it is not the first segment
      id.first_segment = false;
      //a branching point follows
      cout << "TS," << flush; 
    }

    else if (Bud<TS,BUD>* bud = dynamic_cast<Bud<TS,BUD>*>(tc)){
      //if only one bud in an axis it ends that axis
      if (id.number_of_compartments == 1)
	cout << "B]" << flush;
      else 
	//otherwise ending a branching point and that axis
	cout << "},B]" << flush;
    }
    return id;
  }


  template <class TS,class BUD>
  CheckCoordinates<TS,BUD>::CheckCoordinates(double e)
    :epsilon(e)
  {
  }

  //Check coordinates: Each tree compartment should match
  //the "id" given. Segment changes the "id" to its end point 
  template <class TS,class BUD> TreeCompartment<TS,BUD>* 
  CheckCoordinates<TS,BUD>::operator ()(Point& id,
					TreeCompartment<TS,BUD>* tc)const
  {
    Point p = GetPoint(*tc);

    if (Axis<TS,BUD>* axis = dynamic_cast<Axis<TS,BUD>*>(tc)){
      if (id != p && (p || id) > epsilon)
	cout << "A: p || id " << (p || id) << endl;
    }

    else if (BranchingPoint<TS,BUD>* bp =
	     dynamic_cast<BranchingPoint<TS,BUD>*>(tc)){
      if (id != p && (p || id) > epsilon)
	cout <<  "BP: p || id " << (p || id) << endl;
    }

    else if (TS* ts = dynamic_cast<TS*>(tc)){
      if (id != p && (p || id) > epsilon)
	cout << "TS: p || id " << (p || id) << endl; 
      id = GetEndPoint(*ts);
    }

    else if (Bud<TS,BUD>* bud = dynamic_cast<Bud<TS,BUD>*>(tc)){
      if (id != p && (p || id) > epsilon)
	cout << "B: p || id " << (p || id) << endl; 
    }
    return tc;
  }


  //Find the boundig box for a tree, i.e. inside which the tree lies
  //Only those segments that carry foliage are considered. This has to
  //be checked separately for coniferous (CfTreeSegment) and deciduous
  //(HwTreeSegment) segments.

  template <class TS,class BUD>
    BoundingBox&
    FindCfBoundingBox<TS,BUD>::operator ()(BoundingBox& b_box,
					   TreeCompartment<TS,BUD>* tc)const
    {
      if(TS* ts = dynamic_cast<TS*>(tc)){
	if(foliage) {
	  if(GetValue(*ts, LGAWf) < R_EPSILON)
	    return b_box;
	}
      
	Point base = GetPoint(*ts);
	Point top = GetEndPoint(*ts);
	double rSh = GetValue(*ts,LGARf); //max dist of needle tip from woody part	
	if(b_box.getMin().getX() > base.getX()-rSh) b_box.setMinX(base.getX()-rSh);
	if(b_box.getMin().getY() > base.getY()-rSh) b_box.setMinY(base.getY()-rSh);
	if(b_box.getMin().getZ() > base.getZ()-rSh) b_box.setMinZ(base.getZ()-rSh);
	if(b_box.getMin().getX() > top.getX()-rSh) b_box.setMinX(top.getX()-rSh);
	if(b_box.getMin().getY() > top.getY()-rSh) b_box.setMinY(top.getY()-rSh);
	if(b_box.getMin().getZ() > top.getZ()-rSh) b_box.setMinZ(top.getZ()-rSh);
	if(b_box.getMax().getX() < base.getX()+rSh) b_box.setMaxX(base.getX()+rSh);
	if(b_box.getMax().getY() < base.getY()+rSh) b_box.setMaxY(base.getY()+rSh);
	if(b_box.getMax().getZ() < base.getZ()+rSh) b_box.setMaxZ(base.getZ()+rSh);
	if(b_box.getMax().getX() < top.getX()+rSh) b_box.setMaxX(top.getX()+rSh);
	if(b_box.getMax().getY() < top.getY()+rSh) b_box.setMaxY(top.getY()+rSh);
	if(b_box.getMax().getZ() < top.getZ()+rSh) b_box.setMaxZ(top.getZ()+rSh);
      }

      return b_box;
      
    }

  template <class TS,class BUD,class SHAPE>
  BoundingBox&
  FindHwBoundingBox<TS,BUD,SHAPE>::operator ()(BoundingBox& b_box,
					       TreeCompartment<TS,BUD>* tc)const
  {
    if(TS* ts = dynamic_cast<TS*>(tc)){
      if(GetValue(*ts,LGAWf) > R_EPSILON) {
	list<BroadLeaf<SHAPE>*>& leaf_list = GetLeafList(*ts);
	typename list<BroadLeaf<SHAPE>*>::iterator I;
	for(I = leaf_list.begin(); I != leaf_list.end(); I++) {
	  Point p = GetCenterPoint(**I);
	  double A = GetValue(**I, LGAA);
	  double d = sqrt(A/(0.5*PI_VALUE));
	  //max distance from center of leaf is approximated by
	  //assuming it is an ellipse with minor axis half of length of major axis
	    
	  if(b_box.getMin().getX() > p.getX()-d) b_box.setMinX(p.getX()-d);
	  if(b_box.getMin().getY() > p.getY()-d) b_box.setMinY(p.getY()-d);
	  if(b_box.getMin().getZ() > p.getZ()-d) b_box.setMinZ(p.getZ()-d);
	  if(b_box.getMax().getX() < p.getX()+d) b_box.setMaxX(p.getX()+d);
	  if(b_box.getMax().getY() < p.getY()+d) b_box.setMaxY(p.getY()+d);
	  if(b_box.getMax().getZ() < p.getZ()+d) b_box.setMaxZ(p.getZ()+d);
	}
      }
    }

    return b_box;
      
  }



  template <class TS,class BUD>
  TreeDataStruct& TreeData<TS,BUD>::operator()
    (TreeDataStruct& stru, TreeCompartment<TS,BUD>* tc)const {
    
    if (TS* ts = dynamic_cast<TS *>(tc))
      {
	Tree<TS,BUD>& tt = GetTree(*tc);
	
	stru.num_segments++;
	LGMdouble r_ = GetValue(*ts, LGAR);
	LGMdouble l_ = GetValue(*ts, LGAL);
	//Unused variable
	//LGMdouble rh_ = GetValue(*ts, LGARh);
	
	Point ep = GetEndPoint(*ts);
	if (stru.tHeight < ep.getZ())
	  stru.tHeight = ep.getZ();
	
	int _age = (int)GetValue(*ts, LGAage);
	if (_age > stru.age)
	  stru.age = _age;
      
	stru.sum_Wf += GetValue(*ts, LGAWf);
	if(GetValue(*ts, LGAWf) > R_EPSILON) {
	  stru.num_s_fol++;
	  stru.sum_Qabs += GetValue(*ts, LGAQabs);
	  if(stru.max_Qin < GetValue(*ts, LGAQin))
	    stru.max_Qin = GetValue(*ts, LGAQin);
	  stru.sum_Qin += GetValue(*ts, LGAQin);
	}
  
	if(_age == 0) {
	  stru.sum_Wf_new += GetValue(*ts, LGAWf);
	  stru.sum_wood_in_newparts += GetValue(*ts,LGAWs)+GetValue(*ts,LGAWh);
	  stru.sum_wood_new += GetValue(*ts,LGAWs)+GetValue(*ts,LGAWh);
	}

	stru.sum_Wsw += GetValue(*ts, LGAWs);
	stru.sum_Whw += GetValue(*ts, LGAWh);
	stru.sum_Af += GetValue(*ts, LGAAf);

	LGMdouble rho_ = GetValue(tt, LGPrhoW);
	stru.sum_wood_new += rho_*l_*2.0*PI_VALUE*
	  (r_*r_ - pow(r_-GetLastAnnualIncrement(*ts),2.0));

	// if TreeSegment of main axis
	if(GetValue(*ts, LGAomega) == 1)
	  stru.sum_Ws += GetValue(*ts,LGAWs)+GetValue(*ts,LGAWh);
	else
	  stru.sum_Wb += GetValue(*ts,LGAWs)+GetValue(*ts,LGAWh);
		
      }
    else if (dynamic_cast<Bud<TS,BUD>*>(tc))
      {
	stru.num_buds++;
      }

    else if(Axis<TS, BUD>* ax = dynamic_cast<Axis<TS,BUD>*>(tc)) {
      TreeSegment<TS,BUD>* fs = GetFirstTreeSegment(*ax);
      if(fs != NULL) {
	if(GetValue(*fs, LGAomega) == 1) //Main axis = stem
	  {
	    
	    stru.bottom_rad = GetValue(*fs, LGAR);
	    
	    //Set the taper curve & bole lenght
	    //Taper curve argument (taper_hei) along the bole!
	    LGMdouble bl = 0.0;
	    list<TreeCompartment<TS,BUD>*>& tc_ls =
	      GetTreeCompartmentList(*ax);
	    typename list<TreeCompartment<TS,BUD>*>::iterator first =
	      tc_ls.begin();
	    typename list<TreeCompartment<TS,BUD>*>::iterator last =
	      tc_ls.end();
	    while (first != last) {
	      if(TS* se = dynamic_cast<TS*>(*first)){
		stru.taper_rad.push_back(GetValue(*se, LGAR)); 
		stru.taper_hei.push_back(bl);
		stru.taper_radhw.push_back(GetValue(*se, LGARh));
		bl += GetValue(*se, LGAL);
	      }
	      first++;
	    }
	    //Conditions at the tip of the bole
	    TreeSegment<TS,BUD>* ls = GetLastTreeSegment(*ax);
	    stru.taper_hei.push_back(bl);
	    stru.taper_rad.push_back(GetValue(*ls, LGARTop));
	    Tree<TS,BUD>& tt = GetTree(*ls);
	    stru.taper_radhw.push_back(
				       GetValue(tt,LGPxi)*GetValue(*ls, LGARh));
	    stru.bolLen = bl;
	  }


	if(GetValue(*fs, LGAomega) == 2) {
	  //is main branch, does it have foliage, i.e. is it living?
	  LGMdouble fol = GetBranchFoliage(*ax);
	  if(fol > R_EPSILON) {
	    stru.num_br_l++;
	    stru.sum_br_len += GetValue(*ax, LGAL);
	    if(GetPoint(*fs).getZ() < stru.Hc)
	      stru.Hc = GetPoint(*fs).getZ();
	  }
	  else {
	    stru.num_br_d++;  
	    stru.sum_br_len_d += GetValue(*ax, LGAL);
	  }
	}
      }   //if(fs != NULL)
    }

    //calculate mean length of main branches in their whorls
    else if(BranchingPoint<TS, BUD>* bp =
	    dynamic_cast<BranchingPoint<TS,BUD>*>(tc)) {
      std::list<Axis<TS, BUD>*>& axis_ls = GetAxisList(*bp);
      if(axis_ls.size() > 0) {
	typename std::list<Axis<TS, BUD>*>::iterator II = axis_ls.begin();
	Axis<TS,BUD>* ax = *II;
	TreeSegment<TS,BUD>* fs = GetFirstTreeSegment(*ax);
	if(fs != NULL) {
	  if(GetValue(*fs, LGAomega) == 2) {
	    int num_ax = 0;
	    LGMdouble tot_len = 0.0;
	  
	    while(II != axis_ls.end()) {
	      ax = *II;       
	      tot_len += GetValue(*ax, LGAL);
	      num_ax++;
	      II++;   
	    }
	    if(num_ax == 0)
	      stru.mean_brl.push_back(0.0);
	    else
	      stru.mean_brl.push_back(tot_len/(double)num_ax);
	  
	    stru.mean_br_h.push_back(GetPoint(*bp).getZ());
	  }
	}
      }
    }   //If branching point

    return stru;
  }


  template <class TS, class BUD>
  LGMdouble& CollectFrustumVolume<TS,BUD>::
  operator()(LGMdouble& sum, TreeCompartment<TS,BUD>* tc)const
  {
    if(TS *segment = dynamic_cast<TS *>(tc))
      {
	sum += GetValue(*segment, LGAVfrustum);
      }
    return sum;
  }


  //Either whole tree: construct CollectFoliageMass() or by Gravelius order:
  // construct CollectFoliageMass(order)

  template <class TS, class BUD>
  LGMdouble& CollectFoliageMass<TS,BUD>::
  operator()(LGMdouble &sum, TreeCompartment<TS,BUD>* tc)const
  {
    if(TS *segment = dynamic_cast<TS *>(tc))
      {
	if(my_order < 0.0)
	  sum += GetValue(*segment, LGAWf);
	else {
	  LGMdouble order = GetValue(*segment,LGAomega);
	  if(order - 0.1 < my_order && order + 0.1 > my_order) 
	    sum += GetValue(*segment, LGAWf);
	} 
      }
    return sum;
  }


  //Either whole tree: construct CollectFoliageArea() or by Gravelius order:
  // construct CollectFoliageArea(order)

  template <class TS, class BUD>
  LGMdouble& CollectFoliageArea<TS,BUD>::
  operator()(LGMdouble &sum,TreeCompartment<TS,BUD>* tc)const
  {
    if(TS *segment = dynamic_cast<TS *>(tc))
      {
	if(my_order < 0.0)
	  sum += GetValue(*segment, LGAAf);
	else {
	  LGMdouble order = GetValue(*segment,LGAomega);
	  if(order - 0.1 < my_order && order + 0.1 > my_order)
	    sum += GetValue(*segment, LGAAf);
	}
      }
    return sum;
  }

  template <class TS, class BUD>
  LGMdouble& CollectWoodMass<TS,BUD>::
  operator()(LGMdouble &sum, TreeCompartment<TS,BUD>* tc)const
  {
    if(TS *segment = dynamic_cast<TS *>(tc)){
      sum += GetValue(*segment, LGAWood);
    }
    return sum;
  }

  template <class TS, class BUD>
  LGMdouble& CollectStemWoodMass<TS,BUD>::
  operator()(LGMdouble &sum, TreeCompartment<TS,BUD>* tc)const
  {
    if(TS *segment = dynamic_cast<TS *>(tc)){
      if(GetValue(*segment, LGAomega) == 1.0) 
	sum += GetValue(*segment, LGAWood);
    }
    return sum;
  }

  template <class TS, class BUD>
  LGMdouble& CollectSapwoodMass<TS,BUD>::
  operator()(LGMdouble &sum, TreeCompartment<TS,BUD>* tc)const
  {
    if(TS *segment = dynamic_cast<TS *>(tc)){
      sum += GetValue(*segment, LGAWs);
    }
    return sum;
  }

  template <class TS, class BUD>
  LGMdouble& CollectStemSapwoodMass<TS,BUD>::
  operator()(LGMdouble &sum, TreeCompartment<TS,BUD>* tc)const
  {
    if(TS *segment = dynamic_cast<TS *>(tc)){
      if(GetValue(*segment, LGAomega) == 1.0) 
	sum += GetValue(*segment, LGAWs);
    }
    return sum;
  }


  template <class TS, class BUD>
  LGMdouble& CollectHeartwoodMass<TS,BUD>::
  operator()(LGMdouble &sum, TreeCompartment<TS,BUD>* tc)const
  {
    if(TS *segment = dynamic_cast<TS *>(tc)){
      sum += GetValue(*segment, LGAWh);
    }
    return sum;
  }
  
  template <class TS, class BUD>
  LGMdouble& CollectNewSegmentSapwoodMass<TS,BUD>::
  operator()(LGMdouble &sum, TreeCompartment<TS,BUD>* tc)const
  {
    if(TS *segment = dynamic_cast<TS *>(tc)){
      if (GetValue(*segment,LGAage) == 0.0){
	sum += GetValue(*segment, LGAWs);
      }
    }
    return sum;
  }

  template <class TS, class BUD>
  LGMdouble& CollectOldSegmentSapwoodMass<TS,BUD>::
  operator()(LGMdouble &sum, TreeCompartment<TS,BUD>* tc)const
  {
    if(TS *segment = dynamic_cast<TS *>(tc)){
      if (GetValue(*segment,LGAage) > 0.0){
	sum += GetValue(*segment, LGAWs);
      }
    }
    return sum;
  }

  template <class TS,class BUD>
  LGMdouble& CollectNewFoliageMass<TS,BUD>::
  operator()(LGMdouble& wf,TreeCompartment<TS,BUD>* tc)const
  {
    if (TS* ts = dynamic_cast<TS*>(tc)){
      if (GetValue(*ts,LGAage) == 0.0){
	wf += GetValue(*ts,LGAWf);
      }
    }
    return wf;
  }


  template <class TS, class BUD>
  LGMdouble& CollectQabs<TS,BUD>::
  operator()(LGMdouble &sum,TreeCompartment<TS,BUD>* tc)const
  {
    if(TS *ts = dynamic_cast<TS *>(tc))
      {
	sum += GetValue(*ts, LGAQabs);
	if (GetValue(*ts, LGAQabs) < 0.0){
	  cerr << "CollectQabs Qabs < 0.0 " << GetValue(*ts, LGAQabs) <<endl;
	}
      }
    return sum;
  }

  template <class TS, class BUD>
  LGMdouble& CollectQin<TS,BUD>::
  operator()(LGMdouble &sum,TreeCompartment<TS,BUD>* tc)const
  {
    if(TS *ts = dynamic_cast<TS *>(tc))
      {
	sum += GetValue(*ts, LGAQin);
	if (GetValue(*ts, LGAQin) < 0.0){
	  cerr << "CollectQin Qin < 0.0 " << GetValue(*ts, LGAQin) <<endl;
	}
      }
    return sum;
  }

  /*********************************************************************
 The functor to delete axes (branches)  in the tree.  Axis: If an axis
 can be deleted  mark it dead.  BranchingPoint: Delete  the dead axes:
 In an axis delete tree  compartments and set the tre compartment list
 size to 0.  But do not remove  the axis itself from the list of axes.
 We need  to keep  synchronised with L-systems.   TreeSegment: Collect
 foliage mass,  the criteria to  delete axes.  Algorithm  ensures that
 'delete'  is not  applied to  main  axis. After  the destruction  the
 deleted axes exist  in the tree structure but they  are (i.e. list of
 tree compartments are) empty.

 There are a  couple of caveats in deleting  axes and branching points
 in a  tree this way.   Due to the  fact that the  main axis is  not a
 pointer, we cannot  simply apply 'delete' on axes.   That would cause
 an error if delete is called on the main axis.  Also if explicit call
 to ~Axis() is  used this can result problems  on program exit: (main)
 axis may already have been  destroyed inclusive the list of branching
 points. This means  that the list does not  have any methods availabe
 either! Naturally  call to any list  method in such  case will result
 runtime error. Note  also that destruction and erasing  the axes must
 be done at the same  place (BranchingPoint). Once deleted there is no
 way to check  afterwards (in some other place) if  an axis is deleted
 or not; using/checking deleted pointer results unspecified behaviour.
 Sometimes I just love C++...
  *********************************************************************/ 
  template <class TS, class BUD> 
  class DestroyTreeCompartments{
  public:
    void operator()(TreeCompartment<TS,BUD>* tc)const
    {
      delete tc;
    }
  };

  template <class TS, class BUD>
  class DestroyAxes{
  public:
    void operator()(Axis<TS,BUD>* axis)
    {
      if (GetValue(*axis,LGAstate) == DEAD){
	list<TreeCompartment<TS,BUD>*>& ls = GetTreeCompartmentList(*axis);
	//Destroy tree compartments
	for_each(ls.begin(),ls.end(),DestroyTreeCompartments<TS,BUD>());
	//Set the list size to 0 but do not remove the list
	ls.resize(0);
      }
    }
  };
  //The axis or branch is dead if the buds are dead and there is no foliage
  template <class TS, class BUD>
  LGMdouble& DeleteDeadBranches<TS,BUD>::operator()(LGMdouble& foliage, 
						    TreeCompartment<TS,BUD>* tc)const
  {
    if (BUD* bud =  dynamic_cast<BUD*>(tc)){
      if (GetValue(*bud,LGAstate) != DEAD)
	foliage = 100.0;
    }
    //Collect foliage
    else if (TS* ts = dynamic_cast<TS*>(tc)){
      foliage = foliage + GetValue(*ts,LGAWf);
    }
    //If axis received no foliage it can be deleted.
    else if (Axis<TS,BUD>* axis =  dynamic_cast<Axis<TS,BUD>*>(tc)){
      if (foliage < R_EPSILON){
	SetValue(*axis,LGAstate,DEAD);
      }
    }
    else if (BranchingPoint<TS,BUD>* bp =  
	     dynamic_cast<BranchingPoint<TS,BUD>*>(tc)){
      list<Axis<TS,BUD>*>& axis_ls = GetAxisList(*bp);
      //Delete the tree compartments and  set the size of axis_ls to
      //0.
      for_each(axis_ls.begin(),axis_ls.end(),DestroyAxes<TS,BUD>());
    }
    return foliage;
  }


  template <class TS,class BUD>
  TreeCompartment<TS,BUD>*
  PrintTreeSegmentInformationToFile<TS,BUD>::operator()
    (TreeCompartment<TS,BUD>* tc)const {

    if(TS* ts = dynamic_cast<TS*>(tc)) {
      ofstream f(fname.c_str(),ofstream::app);
      Tree<TS,BUD>& tree = GetTree(*tc); 
      LGMdouble ballRad = GetFirmament(tree).diffuseBallSensor();
      LGMdouble maxQin = GetValue(tree, TreeQinMax);

      LGMdouble rQin = 0.0, rTQin = 0.0;
      if(ballRad > R_EPSILON)
	rQin = GetValue(*ts,LGAQin)/ballRad;
      if(maxQin > R_EPSILON)
	rTQin = GetValue(*ts,LGAQin)/maxQin;

      Point r = GetPoint(*tc);
      PositionVector di = GetDirection(*tc);

      f << r.getX() << ":" <<
	r.getY() << ":" <<
	r.getZ() << ":" <<
	di.getX() << ":" <<
	di.getY() << ":" <<
	di.getZ() << ":" <<
	GetValue(*ts, LGAage) << ":" <<
	GetValue(*ts,LGAomega) << ":" <<
	GetValue(*ts,LGAR) << ":" <<
	GetValue(*ts,LGARTop) << ":" <<
	GetValue(*ts,LGARh) << ":" <<
	GetValue(*ts,LGAL) << ":" <<
	GetLastAnnualIncrement(*ts) << ":" <<
	GetValue(*ts,LGAWs) << ":" <<
	GetValue(*ts,LGAWh) << ":" <<
	GetValue(*ts,LGAWf) << ":" <<
	GetValue(*ts,LGAWh)+GetValue(*ts,LGAWs)+GetValue(*ts,LGAWf) << ":" <<
	GetValue(*ts,LGAAf) << ":" <<
	GetValue(*ts,LGAAs0) << ":" <<
	GetValue(*ts,LGAAs) << ":" <<
	GetValue(*ts,LGAQin) << ":" <<
	rTQin << ":" <<
	rQin << ":" <<
	GetValue(*ts,LGAQabs) << ":" <<
	GetValue(*ts,LGAP) << ":" <<
	GetValue(*ts,LGAM) << ":" <<
	GetValue(*ts,LGAvi) <<
	endl;

      f.close();

    } 
    return tc; 
  }

  template <class TS,class BUD>
  TreeCompartment<TS,BUD>*
  PrintTreeSegmentInformationToFileByAxis<TS,BUD>::operator()
    (TreeCompartment<TS,BUD>* tc)const {

    if(Axis<TS,BUD>* ax = dynamic_cast<Axis<TS,BUD>*>(tc)) {
      PrintTreeSegmentInformationToFile<TS,BUD> print(fname,false);
      list<TreeCompartment<TS,BUD>*>& ls = GetTreeCompartmentList(*ax);
      for_each(ls.begin(), ls.end(),print);
    }
    
    return tc;
  }


  

  template <class TS,class BUD>
  int& SetOmega<TS,BUD>::operator()(int& oomega,
				    TreeCompartment<TS,BUD>* tc)const
  {

    if (TS* ts = dynamic_cast<TS *>(tc))
      {
	SetValue(*ts, LGAomega, oomega);
      }
    else if (BUD* bud = dynamic_cast<BUD *>(tc))
      {
	SetValue(*bud, LGAomega, oomega);
      }
    else if(Axis<TS, BUD>* ax =
	    dynamic_cast<Axis<TS,BUD>*>(tc))
      {
	oomega += 1;
      }

    return oomega;
  }



  template <class TS,class BUD>
  InfoStruct& TreeInfo<TS,BUD>::operator()(InfoStruct& stru, TreeCompartment<TS,BUD>* tc)const
  {
    if (TreeSegment<TS,BUD>* ts = dynamic_cast<TreeSegment<TS,BUD>*>(tc))
      {
	stru.num_segments++;
	Point ep = GetEndPoint(*ts);
	if (stru.height < ep.getZ())
	  stru.height = ep.getZ();

	if (GetPoint(*ts).getZ() == 0)
	  {
	    stru.bottom_rad = GetValue(*ts, LGAR);
	  }

	int _age = GetValue(*ts, LGAage);
	if (_age > stru.age)
	  stru.age = _age;
	/*You can't type cast to *both* Cf *and* Hw trees.
	 *Choose either or. Secondly, the first type cast 
	 *then directly casted to segment type one wants.
	 if(CfTreeSegment<TS,BUD>* cfts = dynamic_cast<CfTreeSegment<TS,BUD>*>(ts))
	 {
	 stru.sum_Qabs += GetValue(*cfts, LGAQabs);
	 stru.sum_Qin  += GetValue(*cfts, Qin);
	 stru.sum_Wf += GetValue(*cfts, LGAWf);
	 stru.sum_needle_area += 28 * GetValue(*cfts, LGAWf);
	 stru.sum_QinNA += GetValue(*cfts, LGAQin) * 28 * GetValue(*cfts, LGAWf);
	 stru.sum_QabsNA += GetValue(*cfts, LGAQabs) * 28 * GetValue(*cfts, LGAWf);
	 }

	 if(HwTreeSegment<TS,BUD>* hwts = dynamic_cast<HwTreeSegment<TS,BUD>*>(ts))
	 {
	 stru.sum_Qabs += GetValue(*hwts, LGAQabs);
	 stru.sum_Qin  += GetValue(*hwts, LGAQin);
	 stru.sum_Wf += GetValue(*hwts, LGAWf);
	 }
	*/

	// if main axis
	if (ep.getX() == 0 && ep.getY() == 0)
	  {
	    stru.taper_rad.push_back(GetValue(*ts, LGAR));
	    stru.taper_hei.push_back(ep.getZ());
	  }



      }
    else if (Bud<TS,BUD>* bud = dynamic_cast<Bud<TS,BUD>*>(tc))
      {
	stru.num_buds++;
      }
    return stru;
  }


  template <class TS,class BUD>
  InfoStruct& TreePartInfo<TS,BUD>::operator()(InfoStruct& stru, TreeCompartment<TS,BUD>* tc)const
  {
    if (TreeSegment<TS,BUD>* ts = dynamic_cast<TreeSegment<TS,BUD>*>(tc))
      {
	Point sp = GetPoint(*ts);
	if (sp.getZ() > minh && sp.getZ()<=maxh)
	  {
			
	    Point ep = GetEndPoint(*ts);
	    if (stru.height < ep.getZ())
	      stru.height = ep.getZ();

	    if (GetPoint(*ts).getZ() == 0)
	      {
		stru.bottom_rad = GetValue(*ts, LGAR);
	      }

	    int _age = GetValue(*ts, LGAage);
	    if (_age > stru.age)
	      stru.age = _age;
	    /*You can't type cast to both Cf and Hw segment 
	     *Choose either or.
	     if(CfTreeSegment<TS,BUD>* cfts = dynamic_cast<CfTreeSegment<TS,BUD>*>(ts))
	     {
	     LGMdouble wf = GetValue(*cfts, LGAWf);
	     if (wf > 0.0)
	     {
	     ofstream file("debugsegments.txt", ios::app);
					
	     stru.num_segments++;
	     LGMdouble qinnn = GetValue(*cfts, LGAQin); 				
	     stru.sum_Qabs += GetValue(*cfts, LGAQabs);
	     stru.sum_Qin  += GetValue(*cfts, LGAQin);
	     stru.sum_Wf += GetValue(*cfts, LGAWf);
	     stru.sum_needle_area += 28 * GetValue(*cfts, LGAWf);
	     stru.sum_QinNA += GetValue(*cfts, Qin) * 28 * GetValue(*cfts, LGAWf);
	     stru.sum_QabsNA += GetValue(*cfts, LGAQabs) * 28 * GetValue(*cfts, LGAWf);
	     file << GetValue(*cfts, LGAQin) << " : " << GetValue(*cfts, LGAQabs) << " : ";
	     file << 28 * GetValue(*cfts, Wf) << ":" << GetPoint(*ts);
	     file.close();
	     }
				
	     }

	     if(HwTreeSegment<TS,BUD>* hwts = dynamic_cast<HwTreeSegment<TS,BUD>*>(ts))
	     {
	     stru.sum_Qabs += GetValue(*hwts, LGAQabs);
	     stru.sum_Qin  += GetValue(*hwts, LGAQin);
	     stru.sum_Wf += GetValue(*hwts, LGAWf);
	     }
	    */
	    // if main axis
	    if (ep.getX() == 0 && ep.getY() == 0)
	      {
		stru.taper_rad.push_back(GetValue(*ts, LGAR));
		stru.taper_hei.push_back(ep.getZ());
	      }
	  }
      }
    else if (Bud<TS,BUD>* bud = dynamic_cast<Bud<TS,BUD>*>(tc))
      {
	Point sp = GetPoint(*tc);
	if (sp.getZ() > minh && sp.getZ() < maxh)
	  {
	    stru.num_buds++;
	  }
      }
    return stru;
  }


  template <class TS, class BUD, class SHAPE>
  void SaveLeafInfo(Axis<TS,BUD> &ax, std::ofstream& file)
  {  	
    list<TreeCompartment<TS, BUD>*>& ls = GetTreeCompartmentList(ax);
    typename list<TreeCompartment<TS, BUD>*>::iterator I = ls.begin();
	
    while(I != ls.end())
      {   		
	if (HwTreeSegment<TS,BUD,SHAPE>* myts = dynamic_cast<HwTreeSegment<TS,BUD,SHAPE>*>(*I))
	  {  
	    {
	      list<BroadLeaf<SHAPE> *>& leaves = GetLeafList(*myts);
	      typename list<BroadLeaf<SHAPE> *>::iterator I = leaves.begin();
		
	      for (I = leaves.begin(); I != leaves.end(); I++) 
		{
		  file << "Wf:" << GetValue(**I, LGAWf) 
		       << "  Area:" << GetValue(**I, LGAA) << "   Qin:" 
		       << GetValue(**I, LGAQin) << "   Qabs:" 
		       << GetValue(**I, LGAQabs) << endl;
		} 
	    }
	  } 
      
	if (BranchingPoint<TS, BUD>* mybp = dynamic_cast<BranchingPoint<TS, BUD>*>(*I))
	  { 
	    list<Axis<TS, BUD>*>& axis_ls = GetAxisList(*mybp);  	  
	    typename list<Axis<TS, BUD>*>::iterator II = axis_ls.begin();
			
	    while(II != axis_ls.end())
	      {
		Axis<TS,BUD> *axis = *II;	
		SaveLeafInfo<TS,BUD,SHAPE>(*axis, file);			 
		II++;	
	      }
		
	  }

    
	I++;
      }
  }



  template <class TS, class BUD>
  void SaveTree(Axis<TS,BUD> &ax, const string& file_name, 
		const string& treetype)
  {
      
    string tmp = file_name;		  

    ofstream file(tmp.c_str());
    file << treetype << endl;
    SaveAxis(ax, file, false);
    file.close();
  }


  //WriteTreeInformation collects and prints out information about the
  //tree. It uses functor TreeData to collect the information with
  //Accumulate
  template <class TS, class BUD>
  void WriteTreeInformation(Tree<TS,BUD>&  tr, std::ofstream& file) 
  {
    TreeDataStruct values;
    TreeData<TS,BUD> getTreeValues;
  
    values = Accumulate(tr, values, getTreeValues);
 
    file << "P: " << GetValue(tr,LGAP) << " M: "
	 << GetValue(tr,LGAM) << endl;
    file << "age: " << values.age << endl;
    file << "Height: " << values.height << "Height of CB: " <<
      values.Hc << endl;
    file << "sum_Wf: " << values.sum_Wf << endl;
    file << "sum_Wf_new: " << values.sum_Wf_new << endl;
    file << "sum_wood_in_newparts: " << values.sum_wood_in_newparts
	 << endl;
    file << "sum_wood_new: " << values.sum_wood_new << endl;
    file << "sum_Ws: " << values.sum_Ws << endl;
    file << "sum_Wb: " << values.sum_Wb << endl;
    file << "sum_Wsw: " << values.sum_Wsw << endl;
    file << "sum_Whw: " << values.sum_Whw << endl;
    if(values.num_segments > 0) {
      file << "mean_Qabs: " << values.sum_Qabs/(double)values.num_segments
	   << endl;
    }

    else {
      file << "mean_Qabs: " << 0.0 << endl;
    }
    if(values.num_segments > 0) {
      file << "mean_Qin: " << values.sum_Qin/(double)values.num_segments
	   << endl;
    }
    else {
      file << "mean_Qin: " <<  0.0 << endl;
    }
    if(values.num_s_fol > 0)
      file << "mean_Qabs: " << values.sum_Qabs/(double)values.num_s_fol << endl;
    else
      file << "mean_Qabs: " << 0.0 << endl;

    file << "num_buds: " << values.num_buds << endl;
    file << "num_segments: " << values.num_segments << 
      "  no. segments w/ foliage: " << values.num_s_fol << endl;
    file << "No. branches,  living: " << values.num_br_l << " dead: "
	 << values.num_br_l << endl;
    if(values.num_br_l > 0)
      file << "Mean len of living branches: " <<
	values.sum_br_len/(double)values.num_br_l << endl;
    else
      file << "Mean len of living branches: " << 0.0 << endl;

    file << "height: " << values.height << endl;
    file << "bottom_rad: " << values.bottom_rad << endl << endl;
    file << "Height, m    Radius, cm,   HwRadius, cm" << endl;
    for(int i1 = 0; i1 < static_cast<int>(values.taper_hei.size()); i1++) {
      file << values.taper_hei[i1] << " " <<
	100.0*values.taper_rad[i1]<< " " <<
	100.0*values.taper_radh[i1] << endl;
    }
    file << endl;  
  }






  template <class TS, class BUD>
  void PrintTreeInformationToFile<TS,BUD>::operator() (Tree<TS,BUD>&  tr, ostream& os) 
  {
    TreeDataStruct values;
    TreeData<TS,BUD> getTreeValues;
  
    values = Accumulate(tr, values, getTreeValues);
  
    //os << "P: " << GetValue(tr,TreeP) << " M: " << endl;
    //*******     << GetValue(tr,TreeM) << endl;
    os << "age: " << values.age << endl;
    os << "Height: " << values.height << " Height of crown base: " <<
      values.Hc << endl;
    os << "Basal diameter, cm: " << 200*values.bottom_rad << endl;
    os << "sum_Wf: " << values.sum_Wf << endl;
    os << "sum_Wf_new: " << values.sum_Wf_new << endl;
    os << "sum_wood_in_newparts: " << values.sum_wood_in_newparts
       << endl;
    os << "sum_wood_new: " << values.sum_wood_new << endl;
    os << "sum_Ws: " << values.sum_Ws << endl;
    os << "sum_Wb: " << values.sum_Wb << endl;
    os << "sum_Wsw: " << values.sum_Wsw << endl;
    os << "sum_Whw: " << values.sum_Whw << endl;
    if(values.num_s_fol > 0) {
      os << "Qabs: " << values.sum_Qabs <<"  mean_Qabs: " 
	 << values.sum_Qabs/(double)values.num_s_fol << endl;
      os << "Qin: " << values.sum_Qin <<  "  mean_Qin: "
	 << values.sum_Qin/(double)values.num_s_fol << endl;
    }

    else {
      os << "Qabs: " << values.sum_Qabs  << "  mean_Qabs: " << 0.0 << endl;
      os << "Qin: " << values.sum_Qin  << "  mean_Qin: " <<  0.0 << endl;
    }
  
    if(values.sum_Qin > R_EPSILON && values.sum_Wf > R_EPSILON) {
      LGMdouble Qi = GetFirmament(tr).diffuseBallSensor();
      if(Qi > R_EPSILON)
	os << "Qabs/(Qin*Wf) = " << values.sum_Qabs/(Qi*values.sum_Wf)
	   << "    (should be 2...3)" << endl;
    }

    os << "num_buds: " << values.num_buds << endl;
    os << "num_segments: " << values.num_segments << 
      "  no. segments w/ foliage: " << values.num_s_fol << endl;
    os << "No. branches,  living: " << values.num_br_l << " dead: "
       << values.num_br_d << endl;
    if(values.num_br_l > 0)
      os << "Mean len of living branches: " <<
	values.sum_br_len/(double)values.num_br_l << endl;
    else
      os << "Mean len of living branches: " << 0.0 << endl;
    if(values.num_br_d > 0)
      os << "Mean len of dead branches: " <<
	values.sum_br_len_d/(double)values.num_br_d << endl;
    else
      os << "Mean len of dead branches: " << 0.0 << endl;

    if(values.num_br_l > 0) {
      os << "Cross-sectional area at branch base: " <<
	values.sum_br_Ac/(double)values.num_br_l << endl;
      os << "Cross-sectional area of sapwood at branch base: " <<
	values.sum_br_As/(double)values.num_br_l << endl;
    }
    else {
      os << "Cross-sectional area at branch base: " << 0.0 << endl;
      os << "Cross-sectional area of sapwood at branch base: " << 0.0 << endl;
    }

    os << "Height, m    Diameter, cm,   HwDiameter, cm" << endl;
    for(int i1 = 0; i1 < static_cast<int>(values.taper_hei.size()); i1++) {
      os << values.taper_hei[i1] << " " <<
	200.0*values.taper_rad[i1]<< " " <<
	200.0*values.taper_radhw[i1] << endl;
    }
    os << endl;

    os << "Height of whorl, m     Mean branch length, m" << endl;
    for(int i1 = 0; i1 < static_cast<int>(values.mean_br_h.size()); i1++) {
      os << values.mean_br_h[i1] << " " <<
	values.mean_brl[i1] << endl;

    }
  }



  template <class TS, class BUD >
  void SaveAxis(Axis<TS,BUD> &ax, std::ofstream& file, bool only_segments)
  {  	
    bool min_save = false;
	
    list<TreeCompartment<TS, BUD>*>& ls = GetTreeCompartmentList(ax);
    typename list<TreeCompartment<TS, BUD>*>::iterator I = ls.begin();

    if (!min_save && only_segments==false)
      file << "AXIS"<< endl;
	
    while(I != ls.end())
      {   		
	TreeSegment<TS, BUD>* myts = dynamic_cast<TreeSegment<TS, BUD>*>(*I);	
      
	if (TreeSegment<TS, BUD>* myts = dynamic_cast<TreeSegment<TS, BUD>*>(*I))
	  {  
	    if (TreeSegment<TS, BUD> *ts = dynamic_cast<TreeSegment<TS, BUD>*>(*I))
	      {
		if (!min_save)
		  file << "TS"<< " ";
		file << *ts;    //* otettu en
	      }
	  } 
      
	if (BranchingPoint<TS, BUD>* mybp = dynamic_cast<BranchingPoint<TS, BUD>*>(*I))
	  { 
	    list<Axis<TS, BUD>*>& axis_ls = GetAxisList(*mybp);  	  
	    typename list<Axis<TS, BUD>*>::iterator II = axis_ls.begin();

	    BranchingPoint<TS, BUD>* bp = dynamic_cast<BranchingPoint<TS, BUD>*>(*I);
	    if (!min_save && only_segments==false)
	      {
		file << "BP"<< " ";
		file << *bp << endl;
	      }
	    while(II != axis_ls.end())
	      {
		Axis<TS,BUD> *axis = *II;	
		SaveAxis(*axis, file, only_segments);			 
		II++;	
	      }
	    if (!min_save && only_segments==false)
	      file << "BP_END"<< endl;
	  }

	if (Bud<TS, BUD>* mybud = dynamic_cast<Bud<TS, BUD>*>(*I))
	  {
	    Bud<TS, BUD>* bud = dynamic_cast<Bud<TS, BUD>*>(*I);
	    if(!min_save && only_segments==false)
	      {
		file << "BUD"<< " ";
		file << *bud << endl;
	      }
	  }
		
	I++;
      }
    if (!min_save && only_segments==false)
      file << "AXIS_END"<< endl;
  }




  template <class TS, class BUD>
  LGMdouble& TreeHeight<TS,BUD>::operator()(LGMdouble &max_height, TreeCompartment<TS,BUD>* tc)const
  {
    if (TS* ts = dynamic_cast<TS*>(tc))
      {
	Point p = GetPoint(*ts);
	LGMdouble length = GetValue(*ts, LGAL);
	PositionVector dir = GetDirection(*ts);
	dir.normalize();

	LGMdouble h = p.getZ() + dir.getZ()*length;
	if (h> max_height)
	  max_height = h;
      }
    return max_height;
  }

  template <class TS, class BUD, class SH>
  TreeCompartment<TS,BUD>* DropAllLeaves<TS,BUD,SH>::operator ()(TreeCompartment<TS,BUD>* tc)const
  {
    if (TS* hwts = dynamic_cast<TS*>(tc)){
      list<BroadLeaf<SH>*>& ls = GetLeafList(*hwts);
      //Destroy leaves before clearing the list 
      for_each(ls.begin(),ls.end(),DestroyLeaves<SH>());
      //Now clear the list
      ls.clear();
    }
    return tc;
  }

  //Collect leaves from segments
  template <class TS, class BUD, class SH>
  list<BroadLeaf<SH>*>& 
  CollectLeaves<TS,BUD,SH>::operator()(list<BroadLeaf<SH>*>& ls,
				       TreeCompartment<TS,BUD>* tc)const
  {
    if (TS* ts = dynamic_cast<TS*>(tc)){
      list<BroadLeaf<SH>*>& leaf_ls = GetLeafList(*ts);
      typename list<BroadLeaf<SH>*>::iterator it = leaf_ls.begin();
      //STL accumulate takes real objects, not references; so avoid
      //it now because we have a list of leaves.
      while (it != leaf_ls.end()){
	//insert the leaf to the list of leaves
	ls.push_back(*it);
	advance(it,1);
      }
    }
    return ls;
  }


  //   CrownVolume

  // Crown (between carown base and top of tree) is divided into
  // horizontal slices, the height of which is determined by the
  // attribute step. Each slice is divided into four quadrants (angle
  // PI/2, center directions: 0, PI/2, PI, 3PI/2), and maximum distance
  // from stem to segment (middle) that has foliage is determined. The
  // crown volume is calculated as the sum of the quadrants of the
  // slices.

  template <class TS, class BUD>
  double CrownVolume<TS,BUD>::operator ()(Tree<TS,BUD>&  tr)const 
  {
    DCLData     dcl;
    AccumulateDown(tr,dcl,AddBranchWf(),DiameterCrownBase<TS,BUD>());
    LGMdouble Hc = dcl.HCrownBase();

    LGMdouble H = GetValue(tr, LGAH);

    if(Hc >= H) return -1.0;

    LGMdouble dist = H - Hc;

    int layers = (int)(dist/step) + 1;

    TMatrix<double> radii(layers, 4);

    Axis<TS,BUD>& ax = GetAxis(tr);
    Point treeBase = GetPoint(*GetFirstTreeCompartment(ax));

    for(int i = 0; i < layers; i++) {
      double minH = (double)i * step + Hc;
      double maxH = minH + step;
      double angle = PI_VALUE / 2.0;
      for(int j = 0; j < 4; j++) {
	double dir = (double)j * angle;
	findRFunctor<TS,BUD>  findR(minH, maxH, dir, angle,
				    treeBase);
	double R = 0.0;
	radii[i][j] = Accumulate(tr, R, findR);
      }
    }

    double volume = 0.0;
    double h = step;  
    for(int i = 0; i < layers; i++) {
      for(int j = 0; j < 4; j++) {
	volume += PI_VALUE*radii[i][j]*radii[i][j]*h/4.0;
      }
    }
    return volume;
  }


  // Helper functor for CrownVolume
  //It tests if either base or top of segment with foliage is in the
  //quadrant of a slice and determines whichever is farthest from the
  //stem, and if > R, updates R.
  template <class TS, class BUD>
  double& findRFunctor<TS,BUD>::operator ()
    (double& R, TreeCompartment<TS,BUD>* tc)const {
    if (TS* ts = dynamic_cast<TS*>(tc)){
      if(GetValue(*ts, LGAWf) < R_EPSILON) return R;
      Point base = GetPoint(*ts);
       //      Point midP(base + 0.5 *(top-base));
      if(base.getZ() > minH && base.getZ() < maxH) {
	//note that treeBase is a PositionVector that has only x- and y-components
	PositionVector r = PositionVector(base.getX(),base.getY(),0.0)
	  - treeBase;
	PositionVector middle(cos(dir+angle/2.0),sin(dir+angle/2.0),0.0);
	if(Dot(r,middle)/r.length() > cos(angle/2.0)) {
	  if(r.length() > R) R = r.length();
	}
      }

     Point top = GetEndPoint(*ts);
      if(top.getZ() > minH && top.getZ() < maxH) {
	//note that treeBase is a PositionVector that has only x- and y-components
	PositionVector r = PositionVector(top.getX(),top.getY(),0.0)
	  - treeBase;
	PositionVector middle(cos(dir+angle/2.0),sin(dir+angle/2.0),0.0);
	if(Dot(r,middle)/r.length() > cos(angle/2.0)) {
	  if(r.length() > R) R = r.length();
	}
      }

    }
    return R;
  }

  //CrownExtension
  //Works like CrownVolume but returns crown extensions in quadrants of slices
  //Here end point of segment with foliage is used instead of midpoint.

  

  template <class TS, class BUD>
    void CrownExtension<TS,BUD>::operator ()(Tree<TS,BUD>&  tr,
					     vector<pair<double,double> >& ext)const 
  {
    Point ex_point(0.0,0.0,R_HUGE);
    ex_point = Accumulate(tr,ex_point,LowestCfSegmentWithFoliage<TS,BUD>());
    LGMdouble H_low = ex_point.getZ();
    ex_point = Point(0.0,0.0,-R_HUGE);
    ex_point = Accumulate(tr,ex_point,HighestCfSegmentWithFoliage<TS,BUD>());
    LGMdouble H_high = ex_point.getZ();

    if(H_low >= H_high)
      return;

    LGMdouble dist = H_high - H_low;

    int layers = (int)(dist/step) + 1;

    ext.resize(layers);

    Axis<TS,BUD>& ax = GetAxis(tr);
    Point treeBase = GetPoint(*GetFirstTreeCompartment(ax));

    for(int i = 0; i < layers; i++) {
      double minH = (double)i * step + H_low;
      double maxH = minH + step;
      double angle = PI_VALUE / 2.0;
      double r_sum = 0.0;
      for(int j = 0; j < 4; j++) {
	double dir = (double)j * angle;
	findRFunctor<TS,BUD>  findR(minH, maxH, dir, angle,
				    treeBase);
	double R = 0.0;
	r_sum += Accumulate(tr, R, findR);
      }
      ext[i].first = (minH + maxH)/2.0;
      ext[i].second = r_sum/4.0;
    }

    return;
  }


}//closing namespace Lignum

#endif


