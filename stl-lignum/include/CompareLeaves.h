#ifndef COMPARELEAVES_H
#define COMPARELEAVES_H

#include <BroadLeaf.h>
#include <HwTreeSegment.h>
#include <cmath>

/*********************************************************************
 *This  file implements pairwise  comparison of  leaves in  a hardwood
 *tree to compute radiation climate in a tree crown. 
 *Essentially the algorithms  consists of two ForEach calls. The
 *first, ForEach(tree,ForEachLeafComputeQabs<TS,BUD,SH>()), makes one pass
 *tree calling  the second, ForEach(tree,ForEachLeafIntersect<TS,BUD,SH>(l)), 
 *for each leaf 'l' in a tree found in the first ForEach call.
 *This should work for any leaf shape with the same interface as Triangle and 
 *Ellipse has.
 *********************************************************************/

namespace Lignum{

  //The entry point to pairwise comparison of leaves
  template<class TS, class BUD,class SH>
  class ForEachLeafComputeQabs{
  public:
    TreeCompartment<TS,BUD>* operator()(TreeCompartment<TS,BUD>* tc)const;
  };


  //Called by ForEachLeafComputeQabs to traverse the leaf list in a HwTreeSegment 
  //to compare each leaf 'l' from that list to other leaves in the tree.
  template <class TS, class BUD, class SH>
  class LeafComputeQabs{
  public:
    LeafComputeQabs(Tree<TS,BUD>& t):tree(t){}
    void operator()(BroadLeaf<SH>* l);
  private:
    Tree<TS,BUD>& tree;
  };

  //Called by HwTreeSegmentLeafCompare to compare leaf 'l' to other leaves in the tree.
  template<class TS,class BUD,class SH>
  class ForEachLeafComputeAttenuation{
    friend const BroadLeaf<SH>& GetLeaf(const ForEachLeafComputeAttenuation<TS,BUD,SH>& f){
      return f.leaf;
    }
  public:
    ForEachLeafComputeAttenuation(const BroadLeaf<SH>& l):leaf(l){}
    TreeCompartment<TS,BUD>* operator()(TreeCompartment<TS,BUD>* tc)const;
  private:
    const BroadLeaf<SH>& leaf;
  };

  //Called by ForEachLeafComputeAttenuation and does the actual comparison. 
  template<class SH>
  class LeafComputeAttenuation{
  public:
    //Begin by initializing radiation vector to 1
    LeafComputeAttenuation(const BroadLeaf<SH>& l,Firmament& sky):leaf(l),f(sky){
      vector<LGMdouble>& v = const_cast<vector<LGMdouble>&>(GetRadiationVector(l));
      fill(v.begin(),v.end(),1.0);
    }
    void operator()(BroadLeaf<SH>* l);
  private:
    const BroadLeaf<SH>& leaf;
    Firmament& f;
  };

  //Given the sky, the  vector of radiation attenuation, calculate the
  //Qabs  for the  leaf. This  is as  in LeafComputeQabs,  but  in the
  //pairwise     comparison     there     is     first     call     to
  //ForEachLeafComputeAttenuation.   There are now  many possibilities
  //to calculate  the attenuation.  So I  thought it might  be good to
  //separate this  Qabs to  its own functor.  NOTE that the  vrad must
  //contain Qin from each sector (not just the attenuation coefficients)
  template <class SH>
  class LeafQabs{
  public:
    double calculateLeafQabs(const Firmament& f,vector<double>& vrad, BroadLeaf<SH>& leaf)const{
      for (int i = 0; i < f.numberOfRegions();i++){
	//'v' direction of the light beam
	//'Io' radiant intensity from the sector 'i'
	vector<double> v(3); 
	//Take the direction to the i'th sector 
	f.diffuseRegionRadiationSum(i,v);
	//Leaf normal
	const PositionVector& n1 = GetLeafNormal(leaf);
	//The light beam direction
	const PositionVector d1(v[0],v[1],v[2]);
	//The lengths of the vectors n1 and d1 are 1.
	//fabs: take the accute angle.
	LGMdouble alpha = acos(fabs(Dot(n1,d1)));
	//Qabs
	vrad[i] = vrad[i]*cos(alpha)*GetValue(leaf,LGAA);
      }
      //Store values of Qabs of the leaf
      LGMdouble QabsSum = accumulate(vrad.begin(),vrad.end(),0.0);
      SetValue(leaf, LGAQabs, QabsSum);
      return QabsSum;
    }
  };

  //Implementation of function operators of the functors follows

  //Implementation of the entry point of pairwise comparison. In each
  //HwTreeSegment traverse its leaf list with LeafComputeQabs
  //to compare leaves in the segment to other leaves in a tree.
  template<class TS, class BUD, class SH> TreeCompartment<TS,BUD>* 
  ForEachLeafComputeQabs<TS,BUD,SH>::operator()(TreeCompartment<TS,BUD>* tc)const
  {
    if (TS* ts = dynamic_cast<TS*>(tc)){
      //Compute Qabs for each leaf in this segment
      list<BroadLeaf<SH>*>& ls = GetLeafList(*ts);
      for_each(ls.begin(),ls.end(),LeafComputeQabs<TS,BUD,SH>(GetTree(*ts)));
    }
    return tc;
  }

  //Called by ForEachLeafComputeQin. For the leaf 'l' traverse the tree and 
  //compare to all other leaves.
  template <class TS, class BUD, class SH>
  void LeafComputeQabs<TS,BUD,SH>::operator()(BroadLeaf<SH>* leaf)
  {
    //Compute the attenuation of radiation for 'l' 
    ForEach(tree,ForEachLeafComputeAttenuation<TS,BUD,SH>(*leaf));
    //'leaf' has attenuation in the radiation vector
    //We need to go through the sky, take the radiant intensities,
    //compute the actual Qin and then Qabs
    Firmament& f = GetFirmament(tree);
    vector<LGMdouble>& vrad = const_cast<vector<LGMdouble>&>
      (GetRadiationVector(*leaf));
    LGMdouble QinSum = 0.0;
    for (int i = 0; i < f.numberOfRegions();i++){
      //'v' direction of the light beam
      //'Io' radiant intensity from the sector 'i'
      vector<double> v(3); 
      MJ Io = f.diffuseRegionRadiationSum(i,v);
      //Qin
      vrad[i] = vrad[i]*Io;
      QinSum += vrad[i];
      //Leaf normal
      const PositionVector& n1 = GetLeafNormal(*leaf);
      //the second parameter - the light beam
      const PositionVector d1(v[0],v[1],v[2]);
      //The lengths of the vectors n1 and d1 are 1.
      //fabs: take the accute angle.
      LGMdouble alpha = acos(fabs(Dot(n1,d1)));
      //Qabs
      vrad[i] = vrad[i]*cos(alpha)*GetValue(*leaf,LGAA);
    }
    //Store values of Qin and Qabs of the leaf
    LGMdouble QabsSum = accumulate(vrad.begin(),vrad.end(),0.0);
    SetValue(*leaf, LGAQin, QinSum);
    SetValue(*leaf, LGAQabs, QabsSum);
  }
  
  //Called by LeafComputeQin. In each HwTreeSegment compare the leaf 
  //(returned by 'GetLeaf') to the leaves in the leaf list.
  template<class TS,class BUD,class SH> TreeCompartment<TS,BUD>*
  ForEachLeafComputeAttenuation<TS,BUD,SH>::operator()(TreeCompartment<TS,BUD>* tc)const
  {
    if (TS* ts = dynamic_cast<TS*>(tc)){
      list<BroadLeaf<SH>*>& ls = GetLeafList(*ts);
      for_each(ls.begin(),ls.end(),
	       LeafComputeAttenuation<SH>(GetLeaf(*this),
					  GetFirmament(GetTree(*ts))));
    }
    return tc;
  }
  
  //Finally, the actual comparison called by ForEachLeafAttenuation. 
  //In this case  go through each sector in the  firmament and 1. Find
  //out    the   light    beam    direction   to    a   sector    with
  //'diffuseRadiationSum'. 2. Then go to  the center point in the leaf
  //'leaf' 3.Create the second point on the light beam and 4. Check if
  //the light beam hits the leaf 'l'.
  template<class SH>
  void LeafComputeAttenuation<SH>::operator()(BroadLeaf<SH>* l)
  {
    //the leaf itself (compare physical pointers rather than the leaves themselves) 
    if (l == &leaf)
      return;

    for (int i = 0; i < f.numberOfRegions();i++){
      //'v' direction of the light beam
      vector<double> v(3); 
      f.diffuseRegionRadiationSum(i,v); 

      //the center point of the leaf
      const Point p1 = GetCenterPoint(leaf);  

      //the second parameter - the light beam
      const PositionVector d1(v[0],v[1],v[2]);
 
      //now check if the light beam hits the leaf 'l'.
      if (GetShape(*l).intersectShape(p1,d1)){
	  //transmission 'mu': (1-leafshape) + leafshape*transmission
	  LGMdouble mu = 1-GetValue(*l,LGAdof) + GetValue(*l,LGAdof)*GetValue(*l,LGAtauL);
	  vector<LGMdouble>& v = const_cast<vector<LGMdouble>&>(GetRadiationVector(leaf));
	  v[i] = v[i]*mu;
      }
    }
  }
        
}//closing namespace Lignum


#endif
