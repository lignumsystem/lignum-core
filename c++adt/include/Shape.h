#ifndef SHAPE_H
#define SHAPE_H
#include <iostream>
namespace cxxadt {
  class Shape {
  public:
    virtual ~Shape(){};
    virtual bool  intersectShape(const Point& o,const PositionVector& l)const{
      cout << "Not implemented"<< endl;
	return false;
    }
  };
}
 

#endif
