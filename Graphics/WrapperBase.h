
#ifndef WRAPPERBASE
#define WRAPPERBASE

#include <Lignum.h>

namespace Lignum{

class WrapperBase
{
public:

  
};


class CfWrapper: public WrapperBase 
{
public:
  CfWrapper(const Tree& t):tree(t){}


  Tree& tree;
};


class HwWrapper: public WrapperBase 
{
public:
  HwWrapper(const Tree& t):tree(t){}


  Tree& tree;
};


}

#endif
