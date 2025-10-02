/// \file Shape.h
/// \brief Abstract Shape base class 
#ifndef SHAPE_H
#define SHAPE_H
#include <iostream>
namespace cxxadt {
  ///\interface Shape 
  ///\brief Shape base class with  minimum interface 
  class Shape {
  public:
    virtual ~Shape(){};
    ///\brief Intersection of a shape and (infinite) vector
    ///\param o Obseevation point
    ///\param l Direction of the vector
    ///\retval *true* if intersection, *false* otherwise
    virtual bool  intersectShape(const Point& o,const PositionVector& l)const{
      cout << "Not implemented"<< endl;
	return false;
    }
  };
}
 

#endif
