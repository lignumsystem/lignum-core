#ifndef DLIST_H
#define DLIST_H

#include <DListElement.h>

namespace cxxadt{
/*=============================================================
** DList is a two-way list. The elements of list are linked together
** with pointers to previous and next element. Each list element
** can carry data.
** There are three specific elements in the list
** The first, the last and the current element:
**
*/
class DList{
public:
  DList();
  DList(void *data);
  virtual ~DList();
  DList& insertPosition(int position,void *data);
  DList& insertLeft(void *data);
  DList& insertRight(void *data);
  DList& append(DList *list);
  DList& map(void *(*map_fn)(void *));
  DList& mapWithData(void *(*map_fn)(void *,void *),void *data);
  DList& reverseMap(void *(*map_fn)(void *));
  void*  reduce(void *(*reduce_fn)(void *,void *),void *identity);
  void*  reverseReduce(void *(*reduce_fn)(void *,void *),void *identity);
  void*  booleanReduce(void *(*reduce_fn)(bool (*bfn)(void*,void*),
					  void *fst_arg_2_bfn,
					  void* data, void *id),
		       bool (*bool_fn)(void*,void*),
		       void *fst_arg_to_bfn,
		       void *identity);
  void*  booleanReverseReduce(void *(*reduce_fn)(bool (*bfn)(void*,void*),
						   void *fst_arg_2_bfn,
						   void* data, void *id),
				bool (*bool_fn)(void*,void*),
				void *fst_arg_to_bfn,
				void *identity);
  DList&  reverse();
  void*   getData();
  void*   setData(void *data);
  DList&  deleteCurrent();
  inline bool isEmpty();
  inline bool isOffleft();
  inline bool isOffright();
  inline DListElement* first();
  inline DListElement* last();
  inline DListElement* current();
  DListElement* back();
  DListElement* forth();
  DListElement* go(int position);
  DListElement* goFirst();
  DListElement* goLast();
  inline int    length();
  inline int    currentPosition();
private:
  DListElement *firstElmt;
  DListElement *lastElmt;
  DListElement *currentElmt;
  int currentPos;
  int listLength;
};



//Check if the list is empty
//Observe that this requires a real object
//if DList *ptr == NULL, ptr is NOT empty
inline bool  DList::isEmpty()
{
    return (bool)(listLength == 0);
}


//Check if pointer to current element
//is to the right of the current element
inline bool DList::isOffright()
{
    //The last position in the list is listLength - 1 !!
    return (bool)(isEmpty() || (currentPos == listLength));
}

//Check if pointer to current element 
//is to the left of the current element
inline bool DList::isOffleft()
{
    return (bool)(isEmpty() || (currentPos < 0));
}

//Return the first element of the list
inline DListElement *DList::first()
{
    return firstElmt;
}

//Return the last element of the list
inline DListElement *DList::last()
{
    return lastElmt;
}

//Return the current element of the list
inline DListElement *DList::current()
{
    return currentElmt;
}

//Return the current position of the list
inline int DList::currentPosition()
{
    return currentPos;
}

//Return the list length
inline int DList::length()
{
  return listLength;
}

} //closing namespace cxxadt

#endif /*DList*/
