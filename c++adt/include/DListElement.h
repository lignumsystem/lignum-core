
#ifndef DLIST_ELEMENT_H
#define DLIST_ELEMENT_H

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


#endif


