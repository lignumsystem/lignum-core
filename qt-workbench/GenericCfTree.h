#ifndef GENERICCFTREE 
#define GENERICCFTREE

#include <Lignum.h>
#include <../Pine/Pine.h>
class GenericCfBud;
class GenericCfTreeSegment : public CfTreeSegment<GenericCfTreeSegment, GenericCfBud> {
 public:
  GenericCfTreeSegment(const Point& p, const PositionVector& d,
		       const LGMdouble go, const METER l,
		       const METER r, const METER rh, Tree<GenericCfTreeSegment, GenericCfBud>* tree)
    : CfTreeSegment<GenericCfTreeSegment, GenericCfBud>(p,d,go,l,r,rh,tree) { }
    
};

class GenericCfBud : public Bud<GenericCfTreeSegment, GenericCfBud> {
 public: GenericCfBud(const Point& p, const PositionVector& d,
		      const LGMdouble go, Tree<GenericCfTreeSegment, GenericCfBud>* tree)
			 :Bud<GenericCfTreeSegment, GenericCfBud>(p,d,go,tree) { }
};
			 
#endif
