#ifndef TREE_FUNCTORI_H
#define TREE_FUNCTORI_H

namespace Lignum{

  //Use built-in operator dynamic_cast
  //to resolve the data_type of a tree compartment
  template <class TS,class BUD>
    TreeCompartment<TS,BUD>*  DisplayType<TS,BUD>::operator ()(TreeCompartment<TS,BUD>*tc)const
    {
      if (Axis<TS,BUD>* myaxis =  dynamic_cast<Axis<TS,BUD>*>(tc)){
	cout << "Hello, I'm Axis" << endl;
      }

      else if (BranchingPoint<TS,BUD>* mybp = dynamic_cast<BranchingPoint<TS,BUD>*>(tc)){
	cout << "Hello, I'm BranchingPoint" << endl;
      }

      else if (TreeSegment<TS,BUD>* myts = dynamic_cast<TreeSegment<TS,BUD>*>(tc))
	cout << "Hello, I'm TreeSegment" << endl;

      else if (Bud<TS,BUD>* mybud =  dynamic_cast<Bud<TS,BUD>*>(tc))
	cout << "Hello, I'm Bud" << endl;

      else
	cout << "Who am I???" << endl;

      return tc;
    }

  template <class TS,class BUD>
    TreeCompartment<TS,BUD>* DisplayType2<TS,BUD>::operator()(TreeCompartment<TS,BUD>* tc)const
    {
      if (Axis<TS,BUD>* myaxis =  dynamic_cast<Axis<TS,BUD>*>(tc)){
	cout << "Hello, I'm Axis" << endl;
      }

      else if (BranchingPoint<TS,BUD>* mybp = dynamic_cast<BranchingPoint<TS,BUD>*>(tc)){
	cout << "Hello, I'm BranchingPoint" << endl;
      }

      else if (TreeSegment<TS,BUD>* myts = dynamic_cast<TreeSegment<TS,BUD>*>(tc))
	cout << "Hello, I'm TreeSegment" << endl;

      else if (Bud<TS,BUD>* mybud =  dynamic_cast<Bud<TS,BUD>*>(tc))
	cout << "Hello, I'm Bud" << endl;

      else
	cout << "Who am I???" << endl;

      return tc;
    }

  template <class TS,class BUD>
    int& CountTreeSegments<TS,BUD>::operator()(int& n,TreeCompartment<TS,BUD>* tc)const
    {
      if (TreeSegment<TS,BUD>* myts = dynamic_cast<TreeSegment<TS,BUD>*>(tc))
	n+=1;
  
      return n;
    }



  template <class TS,class BUD>
    int& CountCompartments<TS,BUD>::operator()(int& n,TreeCompartment<TS,BUD>* tc)const
    {
      if (Axis<TS,BUD>* myaxis =  dynamic_cast<Axis<TS,BUD>*>(tc)){
	cout << "Hello, I'm Axis ";
      }

      else if (BranchingPoint<TS,BUD>* mybp = dynamic_cast<BranchingPoint<TS,BUD>*>(tc)){
	cout << "Hello, I'm BranchingPoint ";
      }

      else if (TreeSegment<TS,BUD>* myts = dynamic_cast<TreeSegment<TS,BUD>*>(tc))
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
    int& CountCompartmentsReverse<TS,BUD>::operator()(int& n,
						      TreeCompartment<TS,BUD>* tc)const
    {
      if (Axis<TS,BUD>* myaxis =  dynamic_cast<Axis<TS,BUD>*>(tc)){
	cout << "Hello, I'm Axis ";
      }

      else if (BranchingPoint<TS,BUD>* mybp = dynamic_cast<BranchingPoint<TS,BUD>*>(tc)){
	cout << "Hello, I'm BranchingPoint ";
      }

      else if (TreeSegment<TS,BUD>* myts = dynamic_cast<TreeSegment<TS,BUD>*>(tc))
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
    int MyExampleSignal<TS,BUD>::operator()(int n,
					    TreeCompartment<TS,BUD>* tc)const
    {
      if (Axis<TS,BUD>* myaxis =  dynamic_cast<Axis<TS,BUD>*>(tc)){
	cout << "Hello, I'm Axis ";
      }

      else if (BranchingPoint<TS,BUD>* mybp = dynamic_cast<BranchingPoint<TS,BUD>*>(tc)){
	cout << "Hello, I'm BranchingPoint ";
      }

      else if (TreeSegment<TS,BUD>* myts = dynamic_cast<TreeSegment<TS,BUD>*>(tc))
	cout << "Hello, I'm TreeSegment ";

      else if (Bud<TS,BUD>* mybud =  dynamic_cast<Bud<TS,BUD>*>(tc))
	cout << "Hello, I'm Bud ";

      else
	cout << "Who am I??? ";
 
      n+=1;
      cout << n << endl;
      return n;
    }


  template <class TS,class BUD> void DisplayStructure(Tree<TS,BUD>& t)
    {
      DisplayStructure(&GetAxis(t));
    }

  template <class TS,class BUD> void DisplayStructure(TreeCompartment<TS,BUD>* tc)
    {
      if (Axis<TS,BUD>* myaxis =  dynamic_cast<Axis<TS,BUD>*>(tc)){
	cout << "["; //begin of axis
	list<TreeCompartment<TS,BUD>*>& tc_ls = GetTreeCompartmentList(*myaxis);
	typename list<TreeCompartment<TS,BUD>*>::iterator first = tc_ls.begin();
	typename list<TreeCompartment<TS,BUD>*>::iterator last = tc_ls.end();
	while (first != last)
	  DisplayStructure(*first++);
	cout << "]" << flush; //end of axis
      }

      else if (BranchingPoint<TS,BUD>* mybp = dynamic_cast<BranchingPoint<TS,BUD>*>(tc)){
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

      else if (TreeSegment<TS,BUD>* myts = dynamic_cast<TreeSegment<TS,BUD>*>(tc)){
	//the comma is because we know that a branching point will follow 
	cout << "TS," << flush;
    
      }

      else if (Bud<TS,BUD>* mybud =  dynamic_cast<Bud<TS,BUD>*>(tc)){
	cout << "B" << flush;
      }
    }

  template <class TS,class BUD> DisplayStructureData&
    DisplayStructureFunctor<TS,BUD>:: operator ()(DisplayStructureData& id,
						  TreeCompartment<TS,BUD>* tc)const
    {
      //collect data: number of compartments in an axis and tell the first segment it
      //is the first segment in that axis
      if (Axis<TS,BUD>* axis = dynamic_cast<Axis<TS,BUD>*>(tc)){
	list<TreeCompartment<TS,BUD>*> ls = GetTreeCompartmentList(*axis);
	id.number_of_compartments = ls.size();
	id.first_segment = true;
	cout <<  "[" << flush;
	if (ls.empty())
	  cout <<  "]" << flush;
      }

      else if (BranchingPoint<TS,BUD>* bp = dynamic_cast<BranchingPoint<TS,BUD>*>(tc)){
	cout <<  "{" << flush; 
      }

      else if (TreeSegment<TS,BUD>* ts = dynamic_cast<TreeSegment<TS,BUD>*>(tc)){
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

      else if (BranchingPoint<TS,BUD>* bp = dynamic_cast<BranchingPoint<TS,BUD>*>(tc)){
	if (id != p && (p || id) > epsilon)
	  cout <<  "BP: p || id " << (p || id) << endl;
      }

      else if (TreeSegment<TS,BUD>* ts = dynamic_cast<TreeSegment<TS,BUD>*>(tc)){
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
    FindBoundingBox<TS,BUD>::operator ()(BoundingBox& b_box,
					 TreeCompartment<TS,BUD>* tc)const
    {
      if(TS* ts = dynamic_cast<TS*>(tc)){
	if(GetValue(*ts,Wf) > R_EPSILON) {
	  Point base = GetPoint(*tc);
	  Point top = base + GetValue(*ts, L)*(Point)GetDirection(*ts);
    
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

  //PrintTreeInformation collects and prints out information about the
  //tree. It uses functor TreeData to collect the information with
  //Accumulate

  template <class TS, class BUD>
    void PrintTreeInformation<TS,BUD>::operator() (Tree<TS,BUD>&  tr) {

    TreeDataStruct values;
    TreeData<TS,BUD> getTreeValues;
  
    values = Accumulate(tr, values, getTreeValues);
  
    cout << "P: " << GetValue(tr,TreeP) << " M: "
	 << GetValue(tr,TreeM) << endl;
    cout << "age: " << values.age << endl;
    cout << "Height: " << values.height << " Height of crown base: " <<
      values.Hc << endl;
    cout << "Basal diameter, cm: " << 200*values.bottom_rad << endl;
    cout << "sum_Wf: " << values.sum_Wf << endl;
    cout << "sum_Wf_new: " << values.sum_Wf_new << endl;
    cout << "sum_wood_in_newparts: " << values.sum_wood_in_newparts
	 << endl;
    cout << "sum_wood_new: " << values.sum_wood_new << endl;
    cout << "sum_Ws: " << values.sum_Ws << endl;
    cout << "sum_Wb: " << values.sum_Wb << endl;
    cout << "sum_Wsw: " << values.sum_Wsw << endl;
    cout << "sum_Whw: " << values.sum_Whw << endl;
    if(values.num_s_fol > 0) {
      cout << "Qabs: " << values.sum_Qabs <<"  mean_Qabs: " 
	   << values.sum_Qabs/(double)values.num_s_fol << endl;
      cout << "Qin: " << values.sum_Qin <<  "  mean_Qin: "
	   << values.sum_Qin/(double)values.num_s_fol << endl;
    }

    else {
      cout << "Qabs: " << values.sum_Qabs  << "  mean_Qabs: " << 0.0 << endl;
      cout << "Qin: " << values.sum_Qin  << "  mean_Qin: " <<  0.0 << endl;
    }
  
    if(values.sum_Qin > R_EPSILON && values.sum_Wf > R_EPSILON) {
      LGMdouble Qi = GetFirmament(tr).diffuseBallSensor();
      if(Qi > R_EPSILON)
	cout << "Qabs/(Qin*Wf) = " << values.sum_Qabs/(Qi*values.sum_Wf)
	     << "    (should be 2...3)" << endl;
    }

    cout << "num_buds: " << values.num_buds << endl;
    cout << "num_segments: " << values.num_segments << 
      "  no. segments w/ foliage: " << values.num_s_fol << endl;
    cout << "No. branches,  living: " << values.num_br_l << " dead: "
	 << values.num_br_d << endl;
    if(values.num_br_l > 0)
      cout << "Mean len of living branches: " <<
	values.sum_br_len/(double)values.num_br_l << endl;
    else
      cout << "Mean len of living branches: " << 0.0 << endl;
    if(values.num_br_d > 0)
      cout << "Mean len of dead branches: " <<
	values.sum_br_len_d/(double)values.num_br_d << endl;
    else
      cout << "Mean len of dead branches: " << 0.0 << endl;

    cout << "Height, m    Diameter, cm,   HwDiameter, cm" << endl;
    for(int i1 = 0; i1 < values.taper_hei.size(); i1++) {
      cout << values.taper_hei[i1] << " " <<
	200.0*values.taper_rad[i1]<< " " <<
	200.0*values.taper_radhw[i1] << endl;
    }
    cout << endl;

    cout << "Height of whorl, m     Mean branch length, m" << endl;
    for(int i1 = 0; i1 < values.mean_br_h.size(); i1++) {
      cout << values.mean_br_h[i1] << " " <<
	values.mean_brl[i1] << endl;

    }

  }

  template <class TS,class BUD>
    TreeDataStruct& TreeData<TS,BUD>::operator()
    (TreeDataStruct& stru, TreeCompartment<TS,BUD>* tc)const {

    if (TS* ts = dynamic_cast<TS *>(tc))
      {
	Tree<TS,BUD>& tt = GetTree(*tc);


	stru.num_segments++;
	LGMdouble r_ = GetValue(*ts, R);
	LGMdouble l_ = GetValue(*ts, L);
	LGMdouble rh_ = GetValue(*ts, Rh);


	Point ep = GetEndPoint(*ts);
	if (stru.height < ep.getZ())
	  stru.height = ep.getZ();
      
	if (GetPoint(*ts).getZ() == 0)
	  {
	    stru.bottom_rad = r_;
	  }
      
	int _age = (int)GetValue(*ts, age);
	if (_age > stru.age)
	  stru.age = _age;
      
	stru.sum_Wf += GetValue(*ts, Wf);
	if(GetValue(*ts, Wf) > R_EPSILON) {
	  stru.num_s_fol++;
	  stru.sum_Qabs += GetValue(*ts, Qabs);
	  stru.sum_Qin += GetValue(*ts, Qin);
	}
  
	LGMdouble rho_ = GetValue(tt, rho);

	if(_age == 0) {
	  stru.sum_Wf_new += GetValue(*ts, Wf);
	  stru.sum_wood_in_newparts += rho_*l_*2.0*PI_VALUE*r_*r_;
	  stru.sum_wood_new += rho_*l_*2.0*PI_VALUE*r_*r_;
	}

	stru.sum_Wsw += rho_*l_*2.0*PI_VALUE*(r_*r_-rh_*rh_);
	stru.sum_Whw += rho_*l_*2.0*PI_VALUE*rh_*rh_;

	stru.sum_wood_new += rho_*l_*2.0*PI_VALUE*
	  (r_*r_ - pow(r_-GetLastAnnualIncrement(*ts),2.0));
      

	// if main axis
	if(GetValue(*ts, omega) == 1)
	  {
	    stru.taper_rad.push_back(GetValue(*ts, R)); 
	    stru.taper_hei.push_back(ep.getZ());
	    stru.taper_radhw.push_back(GetValue(*ts, Rh));

	    stru.sum_Ws += rho_*L*2.0*PI_VALUE*r_*r_;

	  }

	else
	  stru.sum_Wb += rho_*L*2.0*PI_VALUE*r_*r_;
		
      }
    else if (Bud<TS,BUD>* bud = dynamic_cast<Bud<TS,BUD>*>(tc))
      {
	stru.num_buds++;
      }

    else if(Axis<TS, BUD>* ax = dynamic_cast<Axis<TS,BUD>*>(tc)) {
      TreeSegment<TS,BUD>* fs = GetFirstTreeSegment(*ax);
      if(fs != NULL)
	if(GetValue(*fs, omega) == 2) {
	  //is main branch, does it have foliage, i.e. is it living?
	  LGMdouble fol = GetBranchFoliage(*ax);
	  if(fol > R_EPSILON) {
	    stru.num_br_l++;
	    stru.sum_br_len += GetValue(*ax, L);
	    if(GetPoint(*fs).getZ() < stru.Hc)
	      stru.Hc = GetPoint(*fs).getZ();
	  }
	  else {
	    stru.num_br_d++;  
	    stru.sum_br_len_d += GetValue(*ax, L);
	  }
	}
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
	  if(GetValue(*fs, omega) == 2) {
	    int num_ax = 0;
	    LGMdouble tot_len = 0.0;
	  
	    while(II != axis_ls.end()) {
	      ax = *II;       
	      tot_len += GetValue(*ax, L);
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
    }

    return stru;
  }



  template <class TS, class BUD>
    LGMdouble& CollectFoliageMass<TS,BUD>::operator()(LGMdouble &sum, 
						      TreeCompartment<TS,BUD>* tc)const
    {
      if(TS *segment = dynamic_cast<TS *>(tc))
	{
	  sum += GetValue(*segment, Wf);
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
	foliage = foliage + GetValue(*ts,Wf);
      }
      //If received no foliage  axis can be deleted.
      else if (Axis<TS,BUD>* axis =  dynamic_cast<Axis<TS,BUD>*>(tc)){
	if (foliage < R_EPSILON){
	  SetValue(*axis,state,DEAD);
	}
      }
      else if (BranchingPoint<TS,BUD>* bp =  
	       dynamic_cast<BranchingPoint<TS,BUD>*>(tc)){
	list<Axis<TS,BUD>*>& axis_ls = GetAxisList(*bp);
	typename list<Axis<TS,BUD>*>::iterator first = axis_ls.begin();
	//All deleted axes are now explicitely DEAD
	while (first != axis_ls.end()){
	  //Find them
	  if (GetValue(**first,state) == DEAD){
	    //delete and  erase them from the list
	    cout << "BranchingPoint erasing axis" << endl;
	    delete *first;
	    first = axis_ls.erase(first);
	  }
	  else{
	    cout << "Something behind first" << endl;
	    first++;
	  }
	}
      }
      return foliage;
    }





  template <class TS,class BUD>
    int& SetOmega<TS,BUD>::operator()(int& oomega,
				      TreeCompartment<TS,BUD>* tc)const
    {

      if (TS* ts = dynamic_cast<TS *>(tc))
	{
	  SetValue(*ts, omega, oomega);
	}
      else if (BUD* bud = dynamic_cast<BUD *>(tc))
	{
	  SetValue(*bud, omega, oomega);
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
	      stru.bottom_rad = GetValue(*ts, R);
	    }

	  int _age = GetValue(*ts, age);
	  if (_age > stru.age)
	    stru.age = _age;
	  /*You can't type cast to *both* Cf *and* Hw trees.
	   *Choose either or. Secondly, the first type cast 
	   *then directly casted to segment type one wants.
	  if(CfTreeSegment<TS,BUD>* cfts = dynamic_cast<CfTreeSegment<TS,BUD>*>(ts))
	    {
	      stru.sum_Qabs += GetValue(*cfts, Qabs);
	      stru.sum_Qin  += GetValue(*cfts, Qin);
	      stru.sum_Wf += GetValue(*cfts, Wf);
	      stru.sum_needle_area += 28 * GetValue(*cfts, Wf);
	      stru.sum_QinNA += GetValue(*cfts, Qin) * 28 * GetValue(*cfts, Wf);
	      stru.sum_QabsNA += GetValue(*cfts, Qabs) * 28 * GetValue(*cfts, Wf);
	    }

	  if(HwTreeSegment<TS,BUD>* hwts = dynamic_cast<HwTreeSegment<TS,BUD>*>(ts))
	    {
	      stru.sum_Qabs += GetValue(*hwts, Qabs);
	      stru.sum_Qin  += GetValue(*hwts, Qin);
	      stru.sum_Wf += GetValue(*hwts, Wf);
	    }
	  */

	  // if main axis
	  if (ep.getX() == 0 && ep.getY() == 0)
	    {
	      stru.taper_rad.push_back(GetValue(*ts, R));
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
		  stru.bottom_rad = GetValue(*ts, R);
		}

	      int _age = GetValue(*ts, age);
	      if (_age > stru.age)
		stru.age = _age;
	      /*You can't type cast to both Cf and Hw segment 
	       *Choose either or.
	      if(CfTreeSegment<TS,BUD>* cfts = dynamic_cast<CfTreeSegment<TS,BUD>*>(ts))
		{
		  LGMdouble wf = GetValue(*cfts, Wf);
		  if (wf > 0.0)
		    {
		      ofstream file("debugsegments.txt", ios::app);
					
		      stru.num_segments++;
		      LGMdouble qinnn = GetValue(*cfts, Qin); 				
		      stru.sum_Qabs += GetValue(*cfts, Qabs);
		      stru.sum_Qin  += GetValue(*cfts, Qin);
		      stru.sum_Wf += GetValue(*cfts, Wf);
		      stru.sum_needle_area += 28 * GetValue(*cfts, Wf);
		      stru.sum_QinNA += GetValue(*cfts, Qin) * 28 * GetValue(*cfts, Wf);
		      stru.sum_QabsNA += GetValue(*cfts, Qabs) * 28 * GetValue(*cfts, Wf);
		      file << GetValue(*cfts, Qin) << " : " << GetValue(*cfts, Qabs) << " : ";
		      file << 28 * GetValue(*cfts, Wf) << ":" << GetPoint(*ts);
		      file.close();
		    }
				
		}

	      if(HwTreeSegment<TS,BUD>* hwts = dynamic_cast<HwTreeSegment<TS,BUD>*>(ts))
		{
		  stru.sum_Qabs += GetValue(*hwts, Qabs);
		  stru.sum_Qin  += GetValue(*hwts, Qin);
		  stru.sum_Wf += GetValue(*hwts, Wf);
		}
	      */
	      // if main axis
	      if (ep.getX() == 0 && ep.getY() == 0)
		{
		  stru.taper_rad.push_back(GetValue(*ts, R));
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
		list<BroadLeaf<SHAPE> *>& leaves = GetLeafList(*hwts);
		typename list<BroadLeaf<SHAPE> *>::iterator I = leaves.begin();
		
		for (I = leaves.begin(); I != leaves.end(); I++) 
		  {
		    file << "Wf:" << GetValue(**I, Wf) 
			 << "  Area:" << GetValue(**I, A) << "   Qin:" 
			 << GetValue(**I, Qin) << "   Qabs:" 
			 << GetValue(**I, Qabs) << endl;
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
		  SaveLeafInfo(*axis, file);			 
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
      const char *tmp = LPCTSTR(treetype);

      ofstream file(file_name);
      file << tmp << endl;
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
  
      file << "P: " << GetValue(tr,P) << " M: "
	   << GetValue(tr,M) << endl;
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




}//closing namespace Lignum

#endif


