#ifndef TREE_FUNCTORI_H
#define TREE_FUNCTORI_H


//This file contains implementation of the following functors
//(functions) for Tree. Help functors etc. are not specified. If you
//add a functor-function please update this list.

//   CountCompartments
//   CountCompartmentsReverse
//   PrintTreeInformation
//   DisplayStructure
//   CheckCoordinates
//   GetBoundingBox     ****is this obsolete?
//   FindCfBoundingBox
//   FindHwBoundingBox
//   CollectFoliageMass
//   CollectFoliageArea
//   CollectQabs
//   MoveTree
//   DeleteDeadBranches
//   PrintTreeSegmentInformationToFile
//   PrintTreeSegmentInformationToFileByAxis

//Functors-functions below used in LIGNUM WorkBench are not listed. 


namespace Lignum{

  template <class TS,class BUD>
    int& CountCompartments<TS,BUD>::
    operator()(int& n,TreeCompartment<TS,BUD>* tc)const
    {
      if (Axis<TS,BUD>* myaxis =  dynamic_cast<Axis<TS,BUD>*>(tc)){
	cout << "Hello, I'm Axis ";
      }

      else if (BranchingPoint<TS,BUD>* mybp =
	       dynamic_cast<BranchingPoint<TS,BUD>*>(tc)){
	cout << "Hello, I'm BranchingPoint ";
      }

      else if (TS* myts = dynamic_cast<TS*>(tc))
	cout << "Hello, I'm TreeSegment ";

      else if (Bud<TS,BUD>* mybud =  dynamic_cast<Bud<TS,BUD>*>(tc))
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
      if (Axis<TS,BUD>* myaxis =  dynamic_cast<Axis<TS,BUD>*>(tc)){
	cout << "Hello, I'm Axis ";
      }

      else if (BranchingPoint<TS,BUD>* mybp =
	       dynamic_cast<BranchingPoint<TS,BUD>*>(tc)){
	cout << "Hello, I'm BranchingPoint ";
      }

      else if (TS* myts = dynamic_cast<TS*>(tc))
	cout << "Hello, I'm TreeSegment ";

      else if (Bud<TS,BUD>* mybud =  dynamic_cast<Bud<TS,BUD>*>(tc))
	cout << "Hello, I'm Bud ";

      else
	cout << "Who am I??? ";

      //counting them all
      n+=1;
      cout << n << endl;
      return n;
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

    out.setf(ios_base::fixed,ios_base::floatfield);
    out.precision(2);

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
    for(int i1 = 0; i1 < values.taper_hei.size(); i1++) {
      out << "     " << values.taper_hei[i1] << "          " <<
	200.0*values.taper_rad[i1]<< "          " <<
	200.0*values.taper_radhw[i1] << endl;
    }
    out << endl;

    out << "H of whorl, m     Mean branch l, m" << endl;
    out.setf(ios_base::fixed,ios_base::floatfield);
    out.precision(2);
    for(int i1 = 0; i1 < values.mean_br_h.size(); i1++) {
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
    LGMdouble  dbhw= GetValue(tr, LGADbaseHw);
    LGMdouble  db= GetValue(tr, LGADbase);

    out << values.age << " " << 100*db << " " << 100*d13 << " "
	<< values.bolLen << " " << values.Hc << " " << values.sum_Wf
	<< " "
	<< values.sum_Ws << " " << values.sum_Wb << " " << values.sum_Af
	<< " "
	<< 10.0*values.sum_Af/(values.sum_Wf+values.sum_Ws+GetValue(tr,TreeWr))
	<< " " << values.max_Qin << " " <<  values.sum_Qabs << " "
	<< GetValue(tr,TreeP) << " " << GetValue(tr,TreeM)
	<< " " <<  values.num_segments << " " << values.num_buds
	<< endl;
  }


  template <class TS,class BUD> void DisplayStructure(Tree<TS,BUD>& t)
    {
      DisplayStructure(&GetAxis(t));
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
	for (int i = 0; i <axis_ls.size(); i++){
	  DisplayStructure(*first++);
	}
	//the end of the branching point
	//the comma is because at least a bud follows  
	cout << "}," << flush; 
      }

      else if (TS* myts = dynamic_cast<TS*>(tc)){
	//the comma is because we know that a branching point will follow 
	cout << "TS," << flush;
    
      }

      else if (Bud<TS,BUD>* mybud =  dynamic_cast<Bud<TS,BUD>*>(tc)){
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




  template <class TS, class BUD>
    Point GetBoundingBox(Tree<TS,BUD> &tree, Point &p)
    {
      return GetBoundingBox(GetAxis(tree), p);
    }




  template <class TS, class BUD>
    Point GetBoundingBox(Axis<TS,BUD> &ax, Point &p)
    {
      std::list<TreeCompartment<TS, BUD>*>& ls = GetTreeCompartmentList(ax);
      typename std::list<TreeCompartment<TS, BUD>*>::iterator I = ls.begin();

        
        
      while(I != ls.end())
	{                   
	  TreeSegment<TS, BUD>* myts = dynamic_cast<TreeSegment<TS, BUD>*>(*I);   
      
	  if (TreeSegment<TS, BUD>* myts = dynamic_cast<TreeSegment<TS, BUD>*>(*I))
	    {  
	      Point pp = GetPoint(*myts);     
	      PositionVector dir = GetDirection(*myts);
	      LGMdouble l = GetValue(*myts, L);
			
	      pp = pp + Point(dir.getX()*l, dir.getY()*l, dir.getZ()*l);
	  
	      double x = pp.getX();
	      double y = pp.getY();
	      double z = pp.getZ();
	  
	      x = sqrt(x*x);
	      y = sqrt(y*y);
	      z = sqrt(z*z);
	  
	      if (x > p.getX())
		p += Point(x - p.getX(),0,0);
	  
	      if (y > p.getY())
		p += Point(0, y - p.getY(), 0);
	  
	      if (z > p.getZ())
		p += Point(0, 0, z - p.getZ());
	    } 
      
	  if (BranchingPoint<TS, BUD>* mybp = dynamic_cast<BranchingPoint<TS, BUD>*>(*I))
	    { 
	      std::list<Axis<TS, BUD>*>& axis_ls = GetAxisList(*mybp);          
	      typename std::list<Axis<TS, BUD>*>::iterator II = axis_ls.begin();
	  
	  
	      while(II != axis_ls.end())
		{
		  Axis<TS,BUD> *axis = *II;       
		  p = GetBoundingBox(*axis, p);                     
		  II++;   
		}
	  
	    }
	  I++;
	}
      return p;
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
	if(GetValue(*ts,LGAWf) > R_EPSILON) {
	  Point base = GetPoint(*ts);
	  Point top = GetEndPoint(*ts);
	  
	  if(b_box.getMin().getX() > base.getX()) b_box.setMinX(base.getX());
	  if(b_box.getMin().getY() > base.getY()) b_box.setMinY(base.getY());
	  if(b_box.getMin().getZ() > base.getZ()) b_box.setMinZ(base.getZ());
	  if(b_box.getMin().getX() > top.getX()) b_box.setMinX(top.getX());
	  if(b_box.getMin().getY() > top.getY()) b_box.setMinY(top.getY());
	  if(b_box.getMin().getZ() > top.getZ()) b_box.setMinZ(top.getZ());
	  if(b_box.getMax().getX() < base.getX()) b_box.setMaxX(base.getX());
	  if(b_box.getMax().getY() < base.getY()) b_box.setMaxY(base.getY());
	  if(b_box.getMax().getZ() < base.getZ()) b_box.setMaxZ(base.getZ());
	  if(b_box.getMax().getX() < top.getX()) b_box.setMaxX(top.getX());
	  if(b_box.getMax().getY() < top.getY()) b_box.setMaxY(top.getY());
	  if(b_box.getMax().getZ() < top.getZ()) b_box.setMaxZ(top.getZ());
	}
      }

      return b_box;
      
    }

  template <class TS,class BUD,class SHAPE>
    BoundingBox&
    FindHwBoundingBox<TS,BUD,SHAPE>::operator ()(BoundingBox& b_box,
					 TreeCompartment<TS,BUD>* tc)const
    {
      if(HwTreeSegment<TS,BUD,SHAPE>* ts = 
	 dynamic_cast<HwTreeSegment<TS,BUD,SHAPE>*>(tc)){
	if(GetValue(*ts,LGAWf) > R_EPSILON) {
	  list<BroadLeaf<SHAPE>*>& leaf_list = GetLeafList(*ts);
	  typename list<BroadLeaf<SHAPE>*>::iterator I;
	  for(I = leaf_list.begin(); I != leaf_list.end(); I++) {
	    Point p = GetCenterPoint(**I);
	    
	    if(b_box.getMin().getX() > p.getX()) b_box.setMinX(p.getX());
	    if(b_box.getMin().getY() > p.getY()) b_box.setMinY(p.getY());
	    if(b_box.getMin().getZ() > p.getZ()) b_box.setMinZ(p.getZ());
	    if(b_box.getMax().getX() < p.getX()) b_box.setMaxX(p.getX());
	    if(b_box.getMax().getY() < p.getY()) b_box.setMaxY(p.getY());
	    if(b_box.getMax().getZ() < p.getZ()) b_box.setMaxZ(p.getZ());
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
	LGMdouble rh_ = GetValue(*ts, LGARh);
	
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
    else if (Bud<TS,BUD>* bud = dynamic_cast<Bud<TS,BUD>*>(tc))
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
    LGMdouble& CollectFoliageMass<TS,BUD>::
    operator()(LGMdouble &sum, TreeCompartment<TS,BUD>* tc)const
    {
      if(TS *segment = dynamic_cast<TS *>(tc))
	{
	  sum += GetValue(*segment, LGAWf);
	}
      return sum;
    }

  template <class TS, class BUD>
    LGMdouble& CollectFoliageArea<TS,BUD>::
    operator()(LGMdouble &sum,TreeCompartment<TS,BUD>* tc)const
    {
      if(TS *segment = dynamic_cast<TS *>(tc))
	{
	  sum += GetValue(*segment, LGAAf);
	}
      return sum;
    }

  template <class TS, class BUD>
    LGMdouble& CollectQabs<TS,BUD>::
    operator()(LGMdouble &sum,TreeCompartment<TS,BUD>* tc)const
    {
      if(TS *segment = dynamic_cast<TS *>(tc))
	{
	  sum += GetValue(*segment, LGAQabs);
	}
      return sum;
    }


  /*********************************************************************
 Sample functor  to delete axes (branches)  in the tree.   Axis: If an
 axis can  be deleted mark  it dead.  BranchingPoint: Delete  the dead
 axes and erase them from  the the list.  TreeSegment: Collect foliage
 mass, the  criteria to delete axes.  Algorithm  ensures that 'delete'
 is not applied to main axis.

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
    LGMdouble& DeleteDeadBranches<TS,BUD>::operator()(LGMdouble& foliage, 
						      TreeCompartment<TS,BUD>* tc)const
    {
      //Collect foliage
      if (TS* ts = dynamic_cast<TS*>(tc)){
	foliage = foliage + GetValue(*ts,LGAWf);
      }
      //If received no foliage  axis can be deleted.
      else if (Axis<TS,BUD>* axis =  dynamic_cast<Axis<TS,BUD>*>(tc)){
	if (foliage < R_EPSILON){
	  SetValue(*axis,LGAstate,DEAD);
	}
      }
      else if (BranchingPoint<TS,BUD>* bp =  
	       dynamic_cast<BranchingPoint<TS,BUD>*>(tc)){
	list<Axis<TS,BUD>*>& axis_ls = GetAxisList(*bp);
	typename list<Axis<TS,BUD>*>::iterator first = axis_ls.begin();
	//All deleted axes are now explicitely DEAD
	while (first != axis_ls.end()){
	  //Find them
	  if (GetValue(**first,LGAstate) == DEAD){
	    //delete and  erase them from the list
	    out << "BranchingPoint erasing axis" << endl;
	    delete *first;
	    first = axis_ls.erase(first);
	  }
	  else{
	    out << "Something behind first" << endl;
	    first++;
	  }
	}
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
		    file << "Wf:" << GetValue(**I, Wf) 
			 << "  Area:" << GetValue(**I, A) << "   Qin:" 
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
		/*
#ifdef _MSC_VER
		const CString st = treetype.c_str;
	  const char *tmp = LPCTSTR(st);
#else
	  const char *tmp = LPCTSTR(treetype);
#endif
	 */

	 string tmp = file_name;		  

	 ofstream file(tmp.c_str());
      file << treetype << endl;
      SaveAxis(ax, file, false);
      file << "Lehtia puussa " << num_of_leaves << '\n';
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
      for(int i1 = 0; i1 < values.taper_hei.size(); i1++) {
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
      for(int i1 = 0; i1 < values.taper_hei.size(); i1++) {
	os << values.taper_hei[i1] << " " <<
	  200.0*values.taper_rad[i1]<< " " <<
	  200.0*values.taper_radhw[i1] << endl;
      }
      os << endl;

      os << "Height of whorl, m     Mean branch length, m" << endl;
      for(int i1 = 0; i1 < values.mean_br_h.size(); i1++) {
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
      if (TreeSegment<TS,BUD>* ts = dynamic_cast<TreeSegment<TS,BUD>*>(tc))
	{
	  Point p = GetPoint(*ts);
	  LGMdouble length = GetValue(*ts, L);
	  PositionVector dir = GetDirection(*ts);
	  dir.normalize;

	  LGMdouble h = p.getZ() + dir.getZ()*length;
	  if (h> max_height)
	    max_height = h;
	}
      return max_height;
    }

  template <class TS, class BUD, class SH>
  TreeCompartment<TS,BUD>* DropAllLeaves<TS,BUD,SH>::operator ()(TreeCompartment<TS,BUD>* tc)const
{
  if (HwTreeSegment<TS,BUD,SH>* hwts = dynamic_cast<HwTreeSegment<TS,BUD,SH>*>(tc)){
    list<BroadLeaf<SH>*>& ls = GetLeafList(*hwts);
    //Destroy leaves before clearing the list 
    for_each(ls.begin(),ls.end(),DestroyLeaves<SH>());
    //Now clear the list
    ls.clear();
  }
  return tc;
}


}//closing namespace Lignum

#endif


