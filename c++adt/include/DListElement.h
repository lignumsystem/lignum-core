/// \file DListElement.h
/// \brief Deprecated list class
#ifndef DLIST_ELEMENT_H
#define DLIST_ELEMENT_H

namespace cxxadt{

class DListElement{
public:
  DListElement(void *data);
  void *setData(void *data);
  void *getData();
  DListElement *setNext(DListElement *element);
  DListElement *next();
  DListElement *setPrevious(DListElement *element);
  DListElement *previous();
private:
  void *data_element;
  DListElement *nextElmt;
  DListElement *previousElmt;
};

}//closing cxxadt

#endif


