#ifndef TREERADIATIONI_H
#define TREERADIATIONI_H



#include <string>
#include <list>


extern bool FOREST;

extern LGMdouble tree__height;
extern LGMdouble foliage_height;
extern LGMdouble total_needle_area;

extern int random_limit;

namespace Lignum{



template <class TS,class BUD, class F>
void EvaluateRadiationForTree(Tree<TS,BUD>& tree, const F& f) 
{
	FOREST = false;
	int num_seg = 0;
	Accumulate(tree,num_seg,CountTreeSegments<TS,BUD>());

	if (num_seg > 100)
	{
		random_limit = 100 - sqrt(250000.0 / num_seg);
	}
	else random_limit = 0;
	
	if (FOREST)
	{
		//Latvusrajan korkeus
		TreeDataStruct values;
		TreeData<TS,BUD> getTreeValues;
		values = Accumulate(tree, values, getTreeValues);
		foliage_height = values.Hc;

		int s = 1;
		if (foliage_height > 0.1)
			s=2;


		LGMdouble sum = 0.0;
		sum = 0.0; // Lasketaan tama muualla...
		AccumulateDown(tree, sum, CollectFoliageMass<TS,BUD>());
		total_needle_area = 28 * sum;   //*******korjaaa 28 GetValue(*ts, sw);

		LGMdouble max_height = 0.0;
		std::list<TreeCompartment<TS, BUD>*>& ls = GetTreeCompartmentList(GetAxis(tree));
		std::list<TreeCompartment<TS, BUD>*>::iterator I = ls.begin();
		while(I != ls.end())
		{
			if (TreeSegment<ScotsPineVisual,ScotsBud>* ts = dynamic_cast<TreeSegment<ScotsPineVisual,ScotsBud>*>(*I))
			{
				Point p = GetPoint(*ts);
				if (p.getX() == 0 && p.getY()== 0)
				{
					LGMdouble len = GetValue(*ts, L);
					LGMdouble hei = len + p.getZ();
					if (max_height < hei)
						max_height = hei;
				}
			}
			I++;
		}
		
		tree__height = max_height;

	}
	ForEach(tree,f);
}

//This constructor is for hardwoods that require the extinction
//function: it is read from file s
template<class F, class TS, class BUD>
WrapRadiationEvaluations<F,TS,BUD>::WrapRadiationEvaluations(std::string s):K(s)
{
    radiation_functor.setExtinction(K);
}

template <class F, class TS, class BUD>
TreeCompartment<TS,BUD>*  WrapRadiationEvaluations<F,TS,BUD>::operator()
  (TreeCompartment<TS, BUD>* tc)const
{

  if(TreeSegment<TS,BUD>* ts = dynamic_cast<TreeSegment<TS,BUD>*>(tc)) 
  {
     radiation_functor(ts);
  }
  return tc;
}


}


#endif
































