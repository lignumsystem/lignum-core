#include <DListElement.h>
#include <stdlib.h>

namespace cxxadt{

DListElement::DListElement(void *data)
{
    data_element = data;
    nextElmt = previousElmt = NULL;
}

//Set a new data into a list element 
//Return the previous data 
//It is the users responsibility to delete it
void *DListElement::setData(void *data)
{
    void *tmp = data_element;
    data_element = data;
    return tmp;
}

void *DListElement::getData()
{
    return data_element;
}

DListElement *DListElement::setNext(DListElement *element)
{
    nextElmt  = element;
    return nextElmt;
}

DListElement *DListElement::next()
{
    return nextElmt;
}

DListElement *DListElement::setPrevious(DListElement *element)
{
    previousElmt = element;
    return previousElmt;
}

DListElement *DListElement::previous()
{
    return previousElmt;
}

} //closing namespace cxxadt





