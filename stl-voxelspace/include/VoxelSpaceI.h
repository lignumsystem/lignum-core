#ifndef VOXELSPACEI_H
#define VOXELSPACEI_H

namespace Lignum {
    inline 
    LGMdouble GetValue(const VoxelSpace& s,VAD LGAkb){
      return s.k_b;
    }
  //First CfTree & CfTreeSegment==========================

  template <class TS,class BUD>
    void DumpCfTree(VoxelSpace &s, Tree<TS, BUD> &tree,int num_parts)
    {
      DumpCfTreeFunctor<TS,BUD> f(num_parts);
      f.space = &s;
      ForEach(tree, f);
    }

  template <class TS, class BUD>
    TreeCompartment<TS,BUD>* DumpCfTreeFunctor<TS,BUD>::
    operator ()(TreeCompartment<TS,BUD>* tc)const
    {
      if (TS* cfts = dynamic_cast<TS*>(tc))
	{
	  DumpCfTreeSegment(*space,*cfts,num_parts);
	} 
      return tc;
    }

  template <class TS,class BUD>
  void DumpCfTreeSegment(VoxelSpace &s, CfTreeSegment<TS, BUD> &ts,double num_parts)
  {
    Point p = GetPoint(ts);
    PositionVector pv = GetDirection(ts);
    LGMdouble length = GetValue(ts, LGAL);

    for (int i=1; i<(num_parts+1.0); i++)
      {
	Point p1 = p + (Point)(length * (i/(num_parts+1.0)) * pv);
	DumpSegment(s.getVoxelBox(p1), ts, num_parts);
      }
  }
  
  template <class TS,class BUD>
    void SetCfTreeQabs(VoxelSpace &s, Tree<TS, BUD> &tree, int num_parts)
    {
      SetCfTreeQabsFunctor<TS,BUD> f(num_parts);
      f.space = &s;
      ForEach(tree, f);
    }


  template <class TS, class BUD>
    TreeCompartment<TS,BUD>* SetCfTreeQabsFunctor<TS,BUD>::
    operator ()(TreeCompartment<TS,BUD>* tc)const
    {
      if (CfTreeSegment<TS,BUD>* cfts = 
	  dynamic_cast<CfTreeSegment<TS,BUD>*>(tc))
	{
	  LGMdouble fmass = GetValue(*cfts, LGAWf);
	  //Reset Qabs Qin  here
	  SetValue(*cfts, LGAQabs, 0.0);
	  SetValue(*cfts, LGAQin, 0.0);
	  if (fmass > R_EPSILON)
	    {
	      Point p = GetPoint(*cfts);
	      PositionVector pv = GetDirection(*cfts);
	      LGMdouble length = GetValue(*cfts, LGAL);
	      //if the user wants 1 part (whole segment), the loop is executed
	      //once  and the midpoint  of the  segment is  used; if  the user
	      //wants 2 parts,  the loop is executed twice  and the points 1/3
	      //and 2/3 of the segment length are used, and so on
	      for (int i=1; i<(num_parts+1.0); i++)
		{
		  Point p1 = p + (Point)(length * (i/(num_parts+1.0)) * pv);
		  VoxelBox box = space->getVoxelBox(p1);
		  SetSegmentQabs(box, *cfts, num_parts);
		}		
	    }
	}
      return tc;    
    }

  //When 'copying'  the tree to voxel  space, we cannot  in the single
  //tree case use the segments  themselves; they are pointers and each
  //time  we change the  segment location  previous insertion  will be
  //lost. Instead  we need a  CfCylinder VoxelObject that has  all the
  //information  of the  segment to  calculate the  shading  (i.e. the
  //attenuation of light)
  //'d': the direction to the new location, NOTE it is assumed |d|=1 
  //'t': the distance to the new location
  //'beam_start': position  on the segment [0:1] where  the light beam
  //              starts (needed to avoid comparison of a segment with 
  //              itself)
  //parts: number of parts the segment will be divived  
  template <class TS>
  void InsertVoxelObject(VoxelSpace& s, const TS& ts, 
			 const PositionVector& d, 
			 double t, double beam_start, int parts)
  {
    //If the  user wants 1  part, we take  the mid point of the  segment. 
    //2 parts means 1/3 and 2/3. 3 parts means 1/4, 2/4 and 3/4 etc.
    double points = static_cast<double>(parts+1);
    parts = parts+1;
    double length = GetValue(ts,LGAL);
    double next_pos = 0.0;
    int x1,y1,z1,x2,y2,z2;
    x1=y1=z1=0;
    x2=y2=z2=-INT_MAX;//at least one point will be inserted
    //Start point of the virtual segment
    PositionVector d0 = PositionVector(GetPoint(ts))+t*d;
    for (int i=1; i < parts; i++){
      //Calculate the new location based  on the direction 'd' and the
      //distance 't'  to the location  from the segment  point. Assume
      //|d| = 1
      PositionVector d1 = PositionVector(GetPoint(ts,i/points))+t*d;
      x1=s.getXindex(d1.getX());
      y1=s.getYindex(d1.getY());
      z1=s.getZindex(d1.getZ());
      //cout << GetPoint(ts);
      //cout << Point(d0);
      //cout << GetPoint(ts,i/points) << i << " " << points << " " 
      //   << i/points << endl;      
      //cout << x1 << " " << y1 << " " << z1 <<endl <<endl;
      //check that the box has changed
      if (!(x1==x2 && y1==y2 && z1==z2)){
	//Virtual segment point as the start point 
	CfCylinder* cfo = new CfCylinder(Point(d0),GetDirection(ts),
					 GetValue(ts,LGAL),GetValue(ts,LGAR),
					 GetValue(ts,LGARf),GetValue(ts,LGAAf),
					 GetValue(ts,LGAVf),beam_start);
	InsertVoxelObject(s.voxboxes[x1][y1][z1],cfo);
      }
      x2=x1;
      y2=y1;
      z2=z1;
    }
    s.sgmnt = s.sgmnt + 1;
  }

    
  template <class TS,class BUD>
    void DumpHwTree(VoxelSpace &s, Tree<TS, BUD> &tree)
  {
      DumpHwTreeFunctor<TS,BUD> f;
      f.space = &s;
      ForEach(tree, f);
    }

  template <class TS, class BUD>
    TreeCompartment<TS,BUD>* DumpHwTreeFunctor<TS,BUD>::
    operator ()(TreeCompartment<TS,BUD>* tc)const
    { 
      if (TS* hwts = dynamic_cast<TS*>(tc))
	{ 
	  DumpHwTreeSegment(*space, *hwts);
	} 
      return tc;
    }

  //Deciduous TreeSegments are dumped to VoxelBoxes differently than
  //coniferous TreeSegments: all leaves of the segment are considered
  //one by one.

   template <class TS,class BUD, class SH>
   void DumpHwTreeSegment(VoxelSpace &s, HwTreeSegment<TS, BUD, SH> &ts)
    {
      Point p;
      std::list<BroadLeaf<SH>*>& leaf_list = 
	GetLeafList(const_cast<HwTreeSegment<TS,BUD,SH>&>(ts));
      typename std::list<BroadLeaf<SH>*>::iterator I;
      for(I = leaf_list.begin(); I != leaf_list.end(); I++) {  
	p = GetCenterPoint(**I);
	DumpLeaf(s.getVoxelBox(p), **I);
      }
    }


  template <class TS, class BUD>
    void SetHwTreeQabs(VoxelSpace &s, Tree<TS, BUD> &tree)
    {
      SetHwTreeQabsFunctor<TS,BUD> f;
      f.space = &s;
      ForEach(tree, f);
    }

  //HwTreeSegment does not store Qin or Qabs, it is done by its
  //leaves. Hence, the leaves are gone through one by one and their
  //Qabs, Qin values are set. Since the angle between leaf normal
  //(impact angle) and incoming radiation is not known (radiation can
  //come anywhere fron the upper hemisphere), it is assumed that the
  //impact angle is random. Therefore cos(impact angle) = 0.5 in
  //calculation of absorbed radiation. The radiation coming to the
  //voxelbox (Qin) is recorded also as Qin for the leaf.

  template <class TS, class BUD>
    TreeCompartment<TS,BUD>* SetHwTreeQabsFunctor<TS,BUD>::
    operator ()(TreeCompartment<TS,BUD>* tc)const
    {
      if (TS* hwts =  dynamic_cast<TS*>(tc))
	{
	  SetHwTreeSegmentQabs(*space, *hwts);
	} 
      return tc;
    }


  template <class TS, class BUD, class SHAPE>
    void SetHwTreeSegmentQabs(VoxelSpace &space,
			      HwTreeSegment<TS,BUD,SHAPE>& ts)
    {
      Point p;
      LGMdouble la, bQin, lQabs;
      VoxelBox box;
      list<BroadLeaf<SHAPE>*>& leaf_list = GetLeafList(ts);
      typename list<BroadLeaf<SHAPE>*>::iterator I;
      for(I = leaf_list.begin(); I != leaf_list.end(); I++) {
	p = GetCenterPoint(**I);
	box = space.getVoxelBox(p);
	bQin = box.getQin();
	la = GetValue(**I,  LGAA);
	lQabs = GetValue(space,LGAkb) * bQin * la;
	//	cout<<"Qin: "<<bQin<<" Qabs: "<<lQabs<<endl;
	SetValue(**I, LGAQabs, lQabs);
	SetValue(**I, LGAQin, bQin);
      }
    }

} //End of namespace Lignum

#endif
