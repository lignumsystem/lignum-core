/// \file VoxelSpaceI.h
/// \brief Voxel space implementation (needs clean-up)
///
/// Insert foliage as aggregate foliage density data in Voxel space or
/// insert tree segments and leaves as geometric voxel objects.
/// \todo Needs clean-up
#ifndef VOXELSPACEI_H
#define VOXELSPACEI_H

namespace voxelspace {
inline
LGMdouble GetValue(const VoxelSpace& s,VAD name){
    if (name == LGAkb)
        return s.k_b;
    else
        cerr << "GetValue(const VoxcelSpace& vs,VAD name) unknown name " << name <<endl;
    return s.k_b;
}
//First CfTree & CfTreeSegment==========================

//Two versions of function DumpCfTree:
//1) Only foliage information is transferred to VoxelSpace
//2) Also information on woody parts (mass, surface area) is
//dumped; this version of the function has an extra argument.
//These two versions of function make it possible retain the old
//interface in case only foliage is dumped.

template <class TS,class BUD>
void DumpCfTree(VoxelSpace &s, Tree<TS, BUD> &tree, int num_parts)
{
    bool wood = false;
    DumpCfTreeFunctor<TS,BUD> f(num_parts,wood);
    f.space = &s;
    ForEach(tree, f);
}

template <class TS,class BUD>
void DumpCfTree(VoxelSpace &s, Tree<TS, BUD> &tree,int num_parts, bool wood)
{
    //Note that in case wood == false, wood variables are not set
    DumpCfTreeFunctor<TS,BUD> f(num_parts,wood);
    f.space = &s;
    ForEach(tree, f);
    s.updateBoxValues();
}


template <class TS, class BUD>
TreeCompartment<TS,BUD>* DumpCfTreeFunctor<TS,BUD>::
operator ()(TreeCompartment<TS,BUD>* tc)const
{
    if (TS* cfts = dynamic_cast<TS*>(tc))  {
        bool foliage = false;
        if(GetValue(*cfts,LGAWf) > R_EPSILON)
            foliage = true;

        if(foliage || dumpWood) {
            Point p = GetPoint(*cfts);
            PositionVector pv = GetDirection(*cfts);
            LGMdouble length = GetValue(*cfts, LGAL);

            for (int i=1; i<(num_parts+1.0); i++)
            {
                Point p1 = p + (Point)(length * ((double)i/((double)num_parts+1.0)) * pv);
                VoxelBox& this_box = space->getVoxelBox(p1);
                if(foliage)
		  DumpCfSegmentFoliage(this_box, *cfts, num_parts);
                else if(dumpWood) {
                    DumpSegmentWood(this_box, *cfts, num_parts);
                }
            }

        } //if(foliage || ...
    }
    return tc;
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

///\brief Insert coniferous tree segment as geomtric voxel object in
///voxel space
///
///When the tree to voxel space, we cannot  in the single
///tree case use the segments  themselves; they are pointers and each
///time  we change the  segment location  previous insertion  will be
///lost. Instead  we need a  CfCylinder VoxelObject that has  all the
///information  of the  segment to  calculate the  shading  (i.e. the
///attenuation of light)
///\param s Voxel space
///\param ts Coniferous tree segment 
///\param d Direction to the new location
///\param t Distance to the new location
///\param beam_start Relatiove position  on the segment [0:1] where  the light beam
///                   starts. Needed to avoid comparison of a segment with
///                   itself.
///\param parts Number of \p parts the segment will be divived into
///\pre \f$ |d|=1 \f$
template <class TS>
void InsertCfVoxelObject(VoxelSpace& s, const TS& ts,
                         const PositionVector& d,
                         double t, double beam_start, int parts)
{
    //If the  user wants 1  part, we take  the mid point of the  segment.
    //2 parts means 1/3 and 2/3. 3 parts means 1/4, 2/4 and 3/4 etc.
    double points = static_cast<double>(parts+1);
    parts = parts+1;
    int x1,y1,z1,x2,y2,z2;
    x1=y1=z1=0;
    x2=y2=z2=-INT_MAX;//at least one point will be inserted
    //Start point of the virtual segment
    PositionVector d0 = PositionVector(GetPoint(ts))+t*d;
    //New common tag for objects denoting this segment
    long_size tag = s.book_keeper.newTag();
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
        if (x1 >= s.Xn || y1 >= s.Yn || z1 >= s.Zn){
            cerr << "Ignoring element " << d1 << endl
                 << x1 << " " << y1 << " " << z1 <<endl
                 << s.Xn << " "  << s.Yn << " " << s.Zn <<endl;
            return;
        }
        if (!(x1==x2 && y1==y2 && z1==z2)){
            //Virtual segment point as the start point
            CfCylinder* cfo = new CfCylinder(Point(d0),GetDirection(ts),
                                             GetValue(ts,LGAL),GetValue(ts,LGAR),
                                             GetValue(ts,LGARf),GetValue(ts,LGAAf),
                                             GetValue(ts,LGAVf),beam_start,tag);
            InsertVoxelObject(s.voxboxes[x1][y1][z1],cfo);
        }
        x2=x1;
        y2=y1;
        z2=z1;
    }
    //Voxel space book keeping.  Descriptive data for Leaf Area Index:
    //add  needle  area.  Recall  after  last  insertion  to set  LAI:
    //Aftot/Avs (foliage area divided by voxel space area)
    if (GetValue(ts,LGAWf) > R_EPSILON){
        SetValue(s.forest_descriptor,LGAAfc,
                 GetValue(s.forest_descriptor,LGAAfc)+GetValue(ts,LGAAf));
        //Crown limit update
        SetValue(s.forest_descriptor,LGAcbase,GetPoint(ts).getZ());
        //Crown heigth update
        SetValue(s.forest_descriptor,LGAH,GetPoint(ts,1.0).getZ());
    }
    s.sgmnt = s.sgmnt + 1;
}

//Insert HwEllipse voxel  objects for the leaves in  the segments ts
//(c.f. InsertVoxelObject for conifercylinder)
class InsertHwEllipse{
public:
    InsertHwEllipse(VoxelSpace& s1, const PositionVector& d1,
                    double t1, int parts1, bool leaf1)
        :s(s1),d(d1),t(t1),parts(parts1),leaf(leaf1){}
    void operator()(BroadLeaf<Ellipse>* l)
    {
        int x1,y1,z1,x2,y2,z2;
        x1=y1=z1=0;x2=y2=z2=-INT_MAX;
        //We need the ellipse for the ray-ellipse intersection
        Ellipse e(GetShape(*l));
        //The new center point where  the HwEllipse voxel object will be
        //inserted
        PositionVector d0 = PositionVector(e.getCenterPoint())+t*d;
        e.setCenterPoint(Point(d0));
        x1 = s.getXindex(d0.getX());
        y1 = s.getYindex(d0.getY());
        z1 = s.getZindex(d0.getZ());
        //Check for voxel space boundaries
        if (x1 >= s.Xn || y1 >= s.Yn || z1 >= s.Zn || x1 < 0 || y1 < 0 || z1 < 0){
            cerr <<"HwEllipse Ignoring element" << endl
                <<"Center " << e.getCenterPoint()
               <<"Dir " << d0 << endl
              <<"X    " << x1 <<   " Y    " << y1 <<   " Z    " << z1 <<endl
             <<"s.Xn " << s.Xn << " s.Yn " << s.Yn << " s.Zn " << s.Zn <<endl;
            return;
        }
        //Unique id for the HwEllipse objects denoting the same real leaf
        int tag = s.book_keeper.newTag();
        HwEllipse* hwe = NULL;
        if (leaf){
            hwe = new HwEllipse(e,GetValue(*l,LGAdof),
                                GetValue(*l,LGAtauL),tag,l);
        }
        else{
            hwe = new HwEllipse(e,GetValue(*l,LGAdof),
                                GetValue(*l,LGAtauL),tag,NULL);
        }
        InsertVoxelObject(s.voxboxes[x1][y1][z1],hwe);
        vector<Point> v;
        e.getVertexVector(v,parts);
        x2=x1;y2=y1;z2=z1;
        for (unsigned int i = 0; i < v.size(); i++){
            Point p = v[i];
            x1 = s.getXindex(p.getX());
            y1 = s.getYindex(p.getY());
            z1 = s.getZindex(p.getZ());
            //cout << x1 << " "  << y1 << " "  <<z1 <<endl;
            //Check for voxel space boundaries
            if (x1 >= s.Xn || y1 >= s.Yn || z1 >= s.Zn|| x1 < 0 || y1 < 0 || z1 < 0 ){
                cerr << "HwEllipse Ignoring element " << p << " "
                     << x1 << " " << y1 << " " << z1 <<endl;
                return;
            }
            //Check if still in the same box as in the previous case
            if (!(x1==x2 && y1==y2 && z1==z2)){
                if (leaf){//use the leaf itself
                    hwe = new HwEllipse(e,GetValue(*l,LGAdof),
                                        GetValue(*l,LGAtauL),tag,l);
                }
                else{//use only the geometric information
                    hwe = new HwEllipse(e,GetValue(*l,LGAdof),
                                        GetValue(*l,LGAtauL),tag,NULL);
                }
                InsertVoxelObject(s.voxboxes[x1][y1][z1],hwe);
            }
            x2=x1;y2=y1;z2=z1;
        }
        //Update  forest  descriptor.  Descriptive  data  for Leaf  Area
        //Index.   Recall  after last  insertion  to  call updateLAI  to
        //calculate  LAI as  Aftot/Avs  (foliage area  divided by  voxel
        //space area
        //Foliage area in voxel space, take the true area of the leaf
        SetValue(s.forest_descriptor,LGAAfb,
                 GetValue(s.forest_descriptor,LGAAfb)+GetValue(*l,LGAA));
        //Crown limit,take the center point of the leaf ellipse
        SetValue(s.forest_descriptor,LGAcbase,e.getCenterPoint().getZ());
        //Crown height,take the center point of the leaf ellipse
        SetValue(s.forest_descriptor,LGAH,e.getCenterPoint().getZ());
        return;
    }
private:
    VoxelSpace& s;///< Voxel space
    const PositionVector& d;///< direction to the location of the leaf
    double t; ///< Distance to the location of the leaf
    int parts;///< number of points on the  edge of ellipse user wants to
    bool leaf;///< Insert the leaf itself too
};


///\brief Insert hardwood species leaves into  voxel space as HwEllipse voxel objects
///
///\param s Voxel space
///\param ts Tree segment
///\param d Direction  to the new location, 
///\param parts  For broad leaf trees the number of points on the boundary of
///              the ellipse checked
///\param l Distance to  the new location        
///\param leaf Insert the leaf itself too
///\pre \f$ |d|=1 \f$
///\note Ellipse leaf implemented
template <class TS,class BUD,class S>
void InsertHwVoxelObject(VoxelSpace& s,HwTreeSegment<TS,BUD,S>& ts,
                         const PositionVector& d,
                         double l,int parts, bool leaf)
{
    //To expand to Triangle leaves, take out the first leaf. Check its
    //type (Triangle  or Ellipse)  and call either  InsertHwEllipse or
    //InsertHwTriangle)
    for_each(GetLeafList(ts).begin(),GetLeafList(ts).end(),
             InsertHwEllipse(s,d,l,parts,leaf));
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


template <class TS>
void InsertTreeSegmentAsVoxelObject(VoxelSpace& s, TS& ts) {
    Point my_point = GetMidPoint(ts);
    VoxelBox& box = s.getVoxelBox(my_point);
    InsertVoxelObject(box,&ts);
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


template <class TS, class BUD>
void InsertTreeAsVoxelObjects<TS,BUD>::operator()(TreeCompartment<TS,BUD>* tc)const{
    if (TS* ts = dynamic_cast<TS*>(tc)){
        InsertTreeSegmentAsVoxelObject(vs,*ts);
    }
}

template <class TREE, class TS, class BUD>
void InsertForestAsVoxelObjects<TREE,TS,BUD>::operator()(TREE* t)const{
    ForEach(*t,InsertTreeAsVoxelObjects<TS,BUD>(vs));
}



// This functor checks only if woody part of this TreeSegment occupies a VoxelBox and sets 
// variable occupied accordingly 
// Checks only segments that have foliage and are older than 0 years. This is because this is used between
// Lsystem and allocation of growth and the new segments (age 0) are already there with provisional
// dimensions. If they are accounted for, odd results emerge  
template <class TS, class BUD>
  TreeCompartment<TS,BUD>* DumpTreeOccupy<TS,BUD>::
  operator ()(TreeCompartment<TS,BUD>* tc)const
{
  if (TS* ts = dynamic_cast<TS*>(tc))  {
      if(GetValue(*ts, LGAWf) < R_EPSILON) {
	return tc;
      }
    if(GetValue(*ts, LGAage) > 0.0) {
      Point p = GetPoint(*ts);
      PositionVector pv = GetDirection(*ts);
      LGMdouble length = GetValue(*ts, LGAL);

      for (int i=1; i<(num_parts+1.0); i++) {
	Point p1 = p + (Point)(length * ((double)i/((double)num_parts+1.0)) * pv);
	VoxelBox& this_box = space->getVoxelBox(p1);
	this_box.setOccupied(true);
      }
    }
  }
  return tc;
}

// This functor checks if the axis of this TreeSegment in a VoxelBox and sets 
// variable occupied accordingly. Whether TreeSegment has foliage or not does not matter.
template <class TS, class BUD>
  TreeCompartment<TS,BUD>* DumpTreeOccupyTreeSegment<TS,BUD>::
  operator ()(TreeCompartment<TS,BUD>* tc)const
{
  if (TS* ts = dynamic_cast<TS*>(tc))  {
    Point p = GetPoint(*ts);
    PositionVector pv = GetDirection(*ts);
    LGMdouble length = GetValue(*ts, LGAL);

    for (int i=1; i<(num_parts+1.0); i++) {
      Point p1 = p + (Point)(length * ((double)i/((double)num_parts+1.0)) * pv);
      VoxelBox& this_box = space->getVoxelBox(p1);
      this_box.setOccupied(true);
    }
  }
  return tc;
}



} //End of namespace Lignum

#endif
