#ifndef COMPARELEAVES_H
#define COMPARELEAVES_H

#include <BroadLeaf.h>
#include <HwTreeSegment.h>
/*********************************************************************
 *This  file implements pairwise  comparison of  leaves in  a hardwood
 *tree. Essentially the algorithms  consists of two ForEach calls. The
 *first,  ForEach(tree,ForEachLeafCompare()), makes  one  pass of  the
 *tree calling  the second, ForEach(tree,ForEachLeafIntersect(l)), for
 *each leaf 'l' in a tree found in the first ForEach call.
 *********************************************************************/

namespace Lignum{

  //The entry point to pairwise comparison of leaves
  template<class TS, class BUD,class SHAPE>
  class ForEachLeafCompare{
  public:
    TreeCompartment<TS,BUD>* operator()(TreeCompartment<TS,BUD>* tc)const;
  };


  //Called by ForEachLeafCompare to traverse the leaf list in a HwTreeSegment 
  //to compare each leaf 'l' from that list to other leaves in the tree.
  template <class TS, class BUD, class SHAPE>
  class HwTreeSegmentLeafCompare{
  public:
    HwTreeSegmentLeafCompare(Tree<TS,BUD>& t):tree(t){}
    void operator()(BroadLeaf<SHAPE>* l);
  private:
    Tree<TS,BUD>& tree;
  };

  //Called by HwTreeSegmentLeafCompare to compare leaf 'l' to other leaves in the tree.
  template<class TS,class BUD,class SHAPE>
  class ForEachLeafIntersect{
    friend const BroadLeaf<SHAPE>& GetLeaf(const ForEachLeafIntersect<TS,BUD,SHAPE>& f){return f.leaf;}
  public:
    ForEachLeafIntersect(const BroadLeaf<SHAPE>& l):leaf(l){}
    TreeCompartment<TS,BUD>* operator()(TreeCompartment<TS,BUD>* tc)const;
  private:
    const BroadLeaf<SHAPE>& leaf;
  };

  //Called by ForEachLeafIntersect and does the actual comparison. 
  template<class SHAPE>
  class HwTreeSegmentLeafIntersect{
  public:
    HwTreeSegmentLeafIntersect(const BroadLeaf<SHAPE>& l,Firmament& sky):leaf(l),f(sky){}
    void operator()(BroadLeaf<SHAPE>* l);
  private:
    const BroadLeaf<SHAPE>& leaf;
    Firmament& f;
  };


  //Implementation of function operators of the functors follows

  //Implementation of the entry point of pairwise comparison. In each
  //HwTreeSegment traverse its leaf list with HwTreeSegmentLeafCompare
  //to compare leaves in the segment to other leaves in a tree.
  template<class TS, class BUD, class SHAPE> TreeCompartment<TS,BUD>* 
  ForEachLeafCompare<TS,BUD,SHAPE>::operator()(TreeCompartment<TS,BUD>* tc)const
  {
    if (HwTreeSegment<TS,BUD,SHAPE>* ts = dynamic_cast<HwTreeSegment<TS,BUD,SHAPE>*>(tc)){
      list<BroadLeaf<SHAPE>*>& ls = GetLeafList(*ts);
      for_each(ls.begin(),ls.end(),HwTreeSegmentLeafCompare<TS,BUD,SHAPE>(GetTree(*ts)));
    }
    return tc;
  }

  //Called by ForEachLeafCompare. For the leaf 'l' traverse the tree and 
  //compare to other leaves.
  template <class TS, class BUD, class SHAPE>
  void HwTreeSegmentLeafCompare<TS,BUD,SHAPE>::operator()(BroadLeaf<SHAPE>* l)
  {
    ForEach(tree,ForEachLeafIntersect<TS,BUD,SHAPE>(*l));
  }
  
  //Called by HwTreeSegmentLeafCompare. In each HwTreeSegment compare the leaf 
  //(returned by 'GetLeaf') to the leaves in the leaf list.
  template<class TS,class BUD,class SHAPE> TreeCompartment<TS,BUD>*
  ForEachLeafIntersect<TS,BUD,SHAPE>::operator()(TreeCompartment<TS,BUD>* tc)const
  {
    if (HwTreeSegment<TS,BUD,SHAPE>* ts = dynamic_cast<HwTreeSegment<TS,BUD,SHAPE>*>(tc)){
      list<BroadLeaf<SHAPE>*>& ls = GetLeafList(*ts);
      for_each(ls.begin(),ls.end(),HwTreeSegmentLeafIntersect<SHAPE>(GetLeaf(*this),
								     GetFirmament(GetTree(*ts))));
    }

    return tc;
  }
  
  //Finally, the actual comparison called by ForEachLeafIntersect. 
  //In this case  go through each sector in the  firmament and 1. Find
  //out    the   light    beam    direction   to    a   sector    with
  //'diffuseRadiationSum'. 2. Then go to  the center point in the leaf
  //'leaf' 3.Create the second point on the light beam and 4. Check if
  //the light beam hits the leaf 'l'.
  template<class SHAPE>
  void HwTreeSegmentLeafIntersect<SHAPE>::operator()(BroadLeaf<SHAPE>* l)
  {
    vector<double> v(3);
    for (int i = 0; i < f.numberOfRegions();i++){
      f.diffuseRegionRadiationSum(i,v); //direction of the light beam
      Point p1 = GetCenterPoint(leaf);  //center point of the leaf
      Point p2 = p1 + 1.0*(Point)PositionVector(v[0],v[1],v[2]); //second point on the light beam
      if (GetShape(*l).intersectEllipse(p1,p2)){//now check if the light beam hits the leaf 'l'.
	cout << "HIT" << endl;
      }
      else{
	cout << "NOT HIT" << endl;
      }
      //I suggest common interface to all shapes: Triangle, Ellipse and Polygon.
      //I  propose   method  'intersectShape(const  Point&   p,  const
      //PositionVector& d)' where 'p' is  the center point of the leaf
      //and 'd'  the direction of  the light beam.   Naturally nothing
      //prevents  to implement  also 'intersectShape(const  Point& p1,
      //const Point& p2)'
    }
  }
        
}//closing namespace Lignum


#endif
