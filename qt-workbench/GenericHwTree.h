#ifndef GENERICHWTREE
#define GENERICHWTREE

#include "Lignum.h"

class GenericHwTriangleBud;
class GenericHwEllipseBud;

class GenericHwTriangleTreeSegment : public HwTreeSegment<GenericHwTriangleTreeSegment, GenericHwTriangleBud, Triangle> {
 public:
  GenericHwTriangleTreeSegment(const Point& p, const PositionVector& d, const LGMdouble go,
			       const METER l, const METER r, const METER rn,
			       Tree<GenericHwTriangleTreeSegment, GenericHwTriangleBud>* t)
    : HwTreeSegment<GenericHwTriangleTreeSegment, GenericHwTriangleBud, Triangle>(p,d,go,l,r,rn,t) { }
};

class GenericHwTriangleBud : public Bud<GenericHwTriangleTreeSegment, GenericHwTriangleBud> {
 public: GenericHwTriangleBud(const Point& p, const PositionVector& d, const LGMdouble omega,
			      Tree<GenericHwTriangleTreeSegment, GenericHwTriangleBud>* tree)
				 : Bud<GenericHwTriangleTreeSegment, GenericHwTriangleBud>(p,d,omega,tree) { }
};



class GenericHwEllipseTreeSegment : public HwTreeSegment<GenericHwEllipseTreeSegment, GenericHwEllipseBud, Ellipse> {
 public:
  GenericHwEllipseTreeSegment(const Point& p, const PositionVector& d, const LGMdouble go,
			      const METER l, const METER r, const METER rn,
			      Tree<GenericHwEllipseTreeSegment, GenericHwEllipseBud>* t)
    : HwTreeSegment<GenericHwEllipseTreeSegment, GenericHwEllipseBud, Ellipse>(p,d,go,l,r,rn,t) { }
};

class GenericHwEllipseBud : public Bud<GenericHwEllipseTreeSegment, GenericHwEllipseBud> {
 public: GenericHwEllipseBud(const Point& p, const PositionVector& d, const LGMdouble omega,
			      Tree<GenericHwEllipseTreeSegment, GenericHwEllipseBud>* tree)
				 : Bud<GenericHwEllipseTreeSegment, GenericHwEllipseBud>(p,d,omega,tree) { }
};

#endif
