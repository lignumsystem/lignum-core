#include <iostream>
using namespace std;
#include <stdlib.h>

#include <DList.h>

namespace cxxadt{

//Create an empty list 
DList::DList()
{
    currentElmt = firstElmt = lastElmt = NULL;
    currentPos = -1;
    listLength = 0; 
}

//Create a list with one element
DList::DList(void *data)
{
    currentElmt = firstElmt = lastElmt = new DListElement(data);
    currentPos = 0;
    listLength = 1;
}

//Delete the list: go to the first
//element in the list and delete the first element 
//until the list is empty.
//Observe that it is the users
//responsibility to delete all the data first
//(to delete the list one has to travers it twice)
DList::~DList()
{
    this->goFirst();
    while (!(this->isEmpty())){
	this->deleteCurrent();
    }
     
}


//Go backward one element in the list 
//If the list is offleft raise an error
DListElement *DList::back()
{

    if (isOffleft()){
	cout << "DList::back applied when List is offleft\n"
	     << "Aborting ..."<< '\n' << flush;
	exit(-1);
    }
    else if (isOffright()){
	currentElmt = lastElmt;
    }
    else{
	currentElmt = currentElmt->previous();
    }

    currentPos--;
    return currentElmt;
}

//Go forward one element in the list
//If the list is offright raise an error
DListElement *DList::forth()
{
    if (isOffright()){
	cout << "DList::forth applied when offright\n"
	     << "Aborting ....\n";
	exit(-1);
    }
    else if(isOffleft()){
	currentElmt = firstElmt;
	currentPos = 0;
    }
    else{
	currentElmt = currentElmt->next();
	currentPos++;
    }
    return currentElmt;
}

//Go to given position in the list
//The given position must exist
//The element at that position will be the
//new currentElmt
DListElement *DList::go(int position)
{
    if (isEmpty()){
	cout << "DList::go applied to an empty list\n"
	     << "Aborting ....\n";
	exit(-1);
    }
    else if (currentPos > position){
	while (currentPos > position)
	    back();
    }
    else{
	while (currentPos < position)
	    forth();
    }
     
    return currentElmt;
}

//Go to the first element in the list
//If the list is empty return NULL
DListElement *DList::goFirst()
{
    if (isEmpty()){
	return NULL;
    }
    else{
	currentElmt = firstElmt;
	currentPos = 0;
	return currentElmt;
    }
}

//Go to the last element in the list
//If the list is empty return NULL
DListElement *DList::goLast()
{
    if (isEmpty()){
	return NULL;
    }
    else{
	currentElmt = lastElmt;
	currentPos = listLength - 1;
	return currentElmt;
    }
}

//Insert a new element into the given position in the list
//The given position must exist
//A new element is created into the given position
//and the rest of the list is pushed to the right
//The newly inserted element will be the new currentElmt
DList &DList::insertPosition(int position,void *data)
{
    go(position);
    return insertLeft(data);
}

//Insert a new element to the left of the
//current position in the list
//The new element becomes the current element
//Return the reference to the modified list
DList &DList::insertLeft(void *data)
{
    DListElement *newElmt      = new DListElement(data);
    DListElement *previousElmt;

    if (isEmpty()){
	firstElmt = lastElmt = currentElmt = newElmt;
	currentPos = 0;
	listLength = 1;
	return *this;
    }
    else{
	//Set the links:
	//previous element points to new element,
	//current element points to new element
	//and the new element points to both previous
	//and current element
	previousElmt = currentElmt->previous();
	if (previousElmt)
	    previousElmt->setNext(newElmt);
	newElmt->setNext(currentElmt);
	newElmt->setPrevious(previousElmt);
	currentElmt->setPrevious(newElmt);
    }
  
    //Check if the new element also becomes a new first element 
    if (firstElmt == currentElmt){
	firstElmt = currentElmt = newElmt;
    }
    else
	//The new element becomes the current element 
	currentElmt = newElmt;

    listLength++;

    return *this;
}

//Insert a new element to the right of the
//current position in the list
//The new element becomes the current element
//Return the reference to the modified list
DList &DList::insertRight(void *data)
{
    DListElement *newElmt      = new DListElement(data);
    DListElement *nextElmt;

    if (isEmpty()){
        firstElmt = lastElmt = currentElmt = newElmt;
        currentPos = 0;
        listLength = 1;
        return *this;
    }
    else{  
        //Set the links:
        //next element points to new element,
        //current element points to new element
        //and the new element points to both next 
        //and current element
        nextElmt =  currentElmt->next();
	if (nextElmt)
            nextElmt->setPrevious(newElmt);
	newElmt->setNext(nextElmt);
	newElmt->setPrevious(currentElmt);
	currentElmt->setNext(newElmt);
     }

     //Check if the new element also becomes a new last element
     if (lastElmt == currentElmt){
         lastElmt = currentElmt = newElmt;
     }
     else
        //The new element becomes the current element
        currentElmt = newElmt;
     
     //increment both current position and list length
     currentPos++;
     listLength++;

     return *this;
} 

void *DList::getData()
{
    if (!isEmpty())
	return currentElmt->getData();
    else
	return NULL;
}

//Set the data in the current position in the list
//Return the previous data. 
//It is the users responsibility to delete the current
void *DList::setData(void *data)
{
    if (!isEmpty()){
	return currentElmt->setData(data);
    }
    else{
	insertRight(data);
	return NULL;
    }
}

//Delete the current list element of the list
//The new current element will be the element
//to the right of the deleted element
//If it is the last element to be deleted
//the last and the current will be the element to the left
DList& DList::deleteCurrent()
{
    DListElement *tmp = currentElmt;
    DListElement *previousElmt; 
    DListElement *nextElmt;

    if (currentElmt){
	nextElmt = currentElmt->next();
	previousElmt = currentElmt->previous();
    }
    else{
	cout << "DList::deleteCurrent() applied to an empty list\n"
	     << "aborting... \n" ;
	exit(-1);
    }

    //Set the previous element to point the next element
    if (previousElmt)
	previousElmt->setNext(nextElmt);
    //Set the next element to point previous element
    if (nextElmt)
	nextElmt->setPrevious(previousElmt);

    
    if (lastElmt  == currentElmt){
	lastElmt = currentElmt = previousElmt;
	currentPos--;
    }
    else if (firstElmt == currentElmt){
	firstElmt = currentElmt = nextElmt;
    }
    else 
	currentElmt = nextElmt;

    delete tmp;
    listLength--;
    return *this;
}


//Reverse the list
//Go to the last element, move all elements one at a time
//to the right side of the lastElmt of the original list.
//The original lastElmt will be the new firstElmt.
//The new current element in the reversed list will be the element which
//takes the currentPosition of the original list.
//The original firstElmt will be the new lastElmt
DList& DList::reverse()
{
  int pos_tmp = currentPos;
  DListElement *tmp1,*last_tmp;
  DListElement *tmp2;

  //Reversing an empty list is th list itself
  if (isEmpty())
    return *this;

  tmp1 = last_tmp = goLast();

  //Start traversing the list backwards
  //until tmp1 has passed the first element
  while (tmp1){
    tmp2 = tmp1;
    tmp1 = tmp1->previous();

    //Clean up pointers before inserting
    tmp2->setNext(NULL);
    tmp2->setPrevious(NULL);
    
    //Set the pointers and new last element 
    lastElmt->setNext(tmp2);
    tmp2->setPrevious(lastElmt);
    lastElmt = tmp2;
  }

  //Update the firstElmt pointer, it is the original last element
  firstElmt = last_tmp;
  firstElmt->setPrevious(NULL);

  //Go to the current position of the original list
  //Set the currentElmt to point to the firstElmt
  //and the currentPosition to 0
  currentPos = 0;
  currentElmt = firstElmt;
  go(pos_tmp);

  //Finally return the list itself
  return *this;
}

//Append a list.
//ls2 is appended to this list.
//This list is destructively modified by creating a list element 
//for each element in ls2
//It is the users responsibility to delete ls2
//if it is not needed after append.
//Note that the list data is not copied,
//only the pointers to data elements are inserted into this list.
DList& DList::append(DList *ls2)
{
  int tmp_current_position1 = this->currentPosition();
  int tmp_current_position2 = ls2->currentPosition();
  void *data = NULL;

  if (ls2 == NULL){
    cout << "DList::append applied to NULL list\n";
    cout << "Aborting ....\n";
    exit(-1);
  }

  //check if ls2 is empty
  if (ls2->isEmpty())
    return *this;

  this->goLast();
  ls2->goFirst();

  while (!ls2->isOffright()){
    data = ls2->getData();
    this->insertRight(data);
    ls2->forth();
  }

  this->go(tmp_current_position1);
  ls2->go(tmp_current_position2);

  return *this;
}

//List map.
//Map the function map_fn to each element in a list
//After the map currentElmt points the firstElmt
DList& DList::map(void * (*map_fn)(void *))
{
  void *data;

  goFirst();

  while (! isOffright()){
    data = getData();
    data = (*map_fn)(data);
    forth();
  }
  
  goFirst();

  return *this;
}

//Lisp map with data
//Map the function 'map_fn' with 'data' to each element 
//in the list. 
DList& DList::mapWithData(void *(*map_fn)(void *,void *),void *data)
{
  void *list_data= NULL;
  
  goFirst();

  while (! isOffright()){
    list_data = getData();
    list_data = (*map_fn)(list_data,data);
    forth();
  }

  goFirst();

  return *this;
}

//List reverse_map
//Like list map but the mapping is done
//from last element to the first
//After the operations currentElmt points the firstElmt
DList& DList::reverseMap(void * (*map_fn)(void *))
{
  void *data;

  goLast();

  while (! isOffleft()){
    data = getData();
    data = (*map_fn)(data);
    back();
  }
  
  goLast();

  return *this;
}

//List reduce
//The list is reduced from the firstElmt
//to the end of the list. The user of this method
//The reduction function must be of the form 
//"void* (*reduce_fn)(void *list_data,void *identity)"
//and the identity element must hold enough space 
//to store the result of recursive calls of reduce_fn
//and it must initially be the 0-element
//The currentElmt will point the firstElmt after reduction
//The elements of the list remain unaltered
void* DList::reduce(void *(*reduce_fn)(void *,void *),void *identity)
{
  void *data;

  goFirst();

  while (!isOffright()){
    data = getData();
    identity = (*reduce_fn)(data,identity);
    forth();
  }

  goFirst();

  return identity;
}

//List reverse_reduce
//Like list reverse but the reducing happens
//lastElmt towards the first element.
//The currentElmt will point the lastElmt after reducing.
//The list elements will remain unaltered.
void* DList::reverseReduce(void *(*reduce_fn)(void *,void *),void *identity)
{
  void *data;

  goLast();

  while (!isOffleft()){
    data = getData();
    identity = (*reduce_fn)(data,identity);
    back();
  }

  goLast();

  return identity;
}

//Boolean list reduce 
//The method is like reduce above
//but the form of the reduce function must be 
//"void*  (*reduce_fn)(BOOLEAN (*bool_fn)(void *, void*),
//                  void *fst_arg_2_bool_fn, void *list_data,void *identity)"
//the "bool_fn" is applied to the list data_element
//and if "bool_fn" returns TRUE list data will be taken to reduction
//"fst_arg_2_bool_fn" is the first argument to boolean function
//(like a simulation of "partially applicable functions")
//"lista_data" is the data_element in a list 
//"identity" is the identity element and must hold enough space to store the final result
//and it must initially be the 0-element
//The currentElmt will point the firstElmt after reduction
void* DList::booleanReduce(void *(*reduce_fn)(BOOLEAN (*b_fn)(void *,void *),
					      void*,void *,void*),
			   BOOLEAN (*bool_fn)(void *,void *),void *fst_arg_2_bool_fn,
			   void* identity)
{
  void *data;
  
  goFirst();

  while(! isOffright()){
    data = getData();
    identity = (*reduce_fn)(bool_fn,fst_arg_2_bool_fn,data,identity);
    forth();
  }

  goFirst();

  return identity;
} 

//Boolean list reverse_reduce
//Like boolean reduce but the reducing will happen
//from the lastElmt towards the first element
//The currentElmt will point the lastElmt  after reduction
//The elements of the list will remain unaltered
void* DList::booleanReverseReduce(void *(*reduce_fn)(BOOLEAN (*b_fn)(void *,void *),
						     void*,void *,void*),
				  BOOLEAN (*bool_fn)(void *,void *),void *fst_arg_2_bool_fn,
				  void* identity)
{
  void *data;

  goLast();

  while(! isOffleft()){
    data = getData();
    identity = (*reduce_fn)(bool_fn,fst_arg_2_bool_fn,data,identity);
    back();
  }

  goLast();

  return identity;
} 

}//closing namespace cxxadt

#ifdef DLIST
#define NL '\n'

void traverse_list(DList &ls)
{
    ls.go(0);
    cout << NL;
    cout << "Length : " << ls.length() << NL << NL;
    cout << "Forth:\n";
    while (!ls.isOffright()){
	cout << "Current: " << *((int *)ls.getData()) << '\n' << flush;
	ls.forth();
    }
    cout << NL;
    ls.back();
    cout << "Back:\n";
    while (!ls.isOffleft()){
	cout << "Current: " << *((int *)ls.getData()) << '\n' << flush;
	ls.back();
    }
    cout << NL;
    ls.goFirst();
}

//For testing map-method
void *my_square(void *data)
{
  *(int *)data = (*(int *)data) * (*(int *)data);
  return data;
}

void *my_add_constant(void *list_data,void *data)
{
  
  *(int *)list_data =  (*(int *)list_data) +  (*(int *)data);

  return list_data;
}

//For testing reduce-method
void *my_add(void * data1,void *id2)
{
  *(int *)id2 = (*(int *)data1) + (*(int *)id2);
  return id2;
}

//For testing boolean_reduce-method
void *my_bool_add(BOOLEAN (*fn)(void*,void*),void *fst_arg,void* data,void *id)
{
  if ((*fn)(fst_arg,data)){
    *(int *)id = (*(int *)data) + (*(int *)id);
    return id;
  }
  else
    return id;
}
//boolean function to test boolean_reduce-method
//return TRUE if arg1 < arg2
BOOLEAN gt(void *arg1,void *arg2)
{
  return (BOOLEAN)(*(int *)arg1 < * (int *)arg2);
}

int  main()
{
    DList l1;
    DList *l2 = new DList;
    DList l3;
    DList *l4 = new DList;
    DList l5;
    static int v1[5] = {0,1,2,3,4};
    static int v2[5] = {10,11,12,13,14};
    static int v3[5] = {20,21,22,23,24};
    static int v4[5] = {30,31,32,33,34};
    static int v5[5] = {5,6,7,8,9};
    int i;
    int ident_elmt = 0;
    int gt_than = 2;
    int one = 1;

    for (i = 0; i < 5; i++){
	l1.insertLeft(&v1[i]);
    }

    for (i = 0; i < 5; i++){
	l3.insertLeft(&v3[i]);
    }

    for (i = 0; i < 5; i++){
	l5.insertLeft(&v5[i]);
    }

    
    cout << "Lenght: " << l1.length() << '\n' << flush;

    cout << "Traverse list\n" << flush;
    traverse_list(l1);
    
    cout << "Go last Insert left " << v2[4] << flush;
    l1.goLast();
    l1.insertLeft(&v2[4]);
    traverse_list(l1);

    cout << "Go first Insert left " << v2[0] << NL << flush;
    l1.goFirst();
    l1.insertLeft(&v2[0]);
    traverse_list(l1);
		   
    cout << "Go position " << l1.length() /2 << "Insert left "<< v2[2] << flush;
    l1.goFirst();
    l1.go(l1.length() /2);
    l1.insertLeft(&v2[2]);
    traverse_list(l1);

    cout << "Go last Insert right" << v3[4] << NL << flush;
    l1.goLast();
    l1.insertRight(&v3[4]);
    traverse_list(l1);

    cout << "Go first Insert right" << v3[0] << NL << flush;
    l1.goFirst();
    l1.insertRight(&v3[0]);
    traverse_list(l1);

    cout << "Go position " << l1.length() /2 << "Insert right " << v3[2] << flush;
    l1.goFirst();
    l1.go(l1.length() /2);
    l1.insertRight(&v3[2]);
    traverse_list(l1);

    cout << "Go last Delete current" << NL << flush;
    l1.goLast();
    l1.deleteCurrent();
    traverse_list(l1);

    cout << "Go first  Delete current" << NL << flush;
    l1.goFirst();
    l1.deleteCurrent();
    traverse_list(l1);

    cout << "Go position " << l1.length() /2 << "Delete current" << NL << flush;
    l1.go(l1.length() /2);
    l1.deleteCurrent();
    traverse_list(l1);

    cout << "Go position " << l1.length() - 3 << "Delete current" << NL << flush;
    l1.go(l1.length() -3);
    l1.deleteCurrent();
    traverse_list(l1);

    cout <<  "Insert Position " << l1.length() - 2 << "Element " << v4[4] << NL << flush;
    l1.insertPosition(l1.length() - 2,&v4[4]);
    traverse_list(l1);

    l2 = &l5;
    cout << "Reversing l2" << NL;
    cout << "Before reversing" << NL;
    traverse_list(*l2);
    l2->reverse();
    cout << "After traversing" <<NL;
    traverse_list(*l2);

    cout << "Reversing the l3 3 times" << NL;
    cout << "Before reversing" << NL;
    traverse_list(l3);
    cout << "After reversing" << NL;
    l3.reverse().reverse().reverse();
    traverse_list(l3);


    cout << "Appending list l3 of length " << l3.length()<< " and l2 of length " 
      << l2->length() << NL;
    cout << "l3 before append" << endl;
    traverse_list(l3);
    cout << "l2 before append" << endl;
    traverse_list(*l2);
    l3.append(l2);
    cout << "l3 after append" << endl;
    traverse_list(l3);

    cout << "mapping square to l3" << NL;
    l3.map(my_square);
    traverse_list(l3);

    cout << "Applying reduce with function my_add to l3" << NL;
    ident_elmt = *(int *)l3.reduce(my_add,&ident_elmt);
    cout << ident_elmt << NL;
    cout << "l3 should have remained unaltered" << NL;
    cout << "current position " << l3.currentPosition() << NL;
    l3.goFirst();
    cout << "current position " << l3.currentPosition() << NL;
    traverse_list(l3);

    cout << "Applying boolean_reduce with gt(63,?) to l3" << NL;
    ident_elmt = 0;
    gt_than = 63;
    ident_elmt = *(int *)l3.booleanReduce(my_bool_add,gt,&gt_than,&ident_elmt);
    cout << ident_elmt << NL;
    cout << "The list should have remained unaltered" << NL;
    cout << "current position " << l3.currentPosition() << NL;
    l3.goFirst();
    cout << "current position " << l3.currentPosition() << NL;
    traverse_list(l3);

    cout << "Applying reverse_map with square to list above" << NL;
    l3.reverseMap(my_square);
    traverse_list(l3);

    
    cout << "Applying reverse_reduce with my_add to l3" << NL;
    l3.goLast();
    ident_elmt = 0;
    ident_elmt = *(int *)l3.reverseReduce(my_add,&ident_elmt);
    cout << ident_elmt << NL;
    cout << "The list should have remained unaltered" << NL;
    cout << "current position " << l3.currentPosition() << NL;
    l3.goFirst();
    cout << "current position " << l3.currentPosition() << NL;
    traverse_list(l3);

    cout << "Applying boolean_reverse_reduce with gt(159999,?) to l3" << NL;
    ident_elmt = 0;
    gt_than = 159999;
    l3.goLast();
    ident_elmt = *(int *)l3.booleanReverseReduce(my_bool_add,gt,&gt_than,&ident_elmt);
    cout << ident_elmt << NL;
    cout << "The list should have remained unaltered" << NL;
    cout << "current position " << l3.currentPosition() << NL;
    l3.goFirst();
    cout << "current position " << l3.currentPosition() << NL;
    traverse_list(l3);  

    cout << "Delete List\n";
    //delete l2;
    //l5.~DList();
    delete l2;
    cout << "Is offleft : " << l2->isOffleft() << NL << flush;
    cout << "Is offright: "<< l2->isOffright() << NL << flush;
    cout << "Current position : " << l2->currentPosition() << NL << flush;
    cout << "Length : " << l2->length() << NL << flush;
    cout << "Is empty : " << l2->isEmpty() << NL << flush;

    cout << "Traversing l3 which should be unaltered " << endl;
    traverse_list(l3);

    cout << "Testing mapWithData by adding 1 to each element in l3" << endl;
    l3.mapWithData(my_add_constant,&one);
    cout << "Traversing l3" <<endl;
    traverse_list(l3);
    cout << "Reversing l2 which is empty" << NL;
    l2->reverse();
    exit(0);
}
#endif








