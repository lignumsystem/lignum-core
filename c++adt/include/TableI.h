/// \file TableI.h
/// \brief Deprecated look up table
///
/// Implementation file.
#ifndef TABLEI_H
#define TABLEI_H

namespace cxxadt{

template <class K,class D>
TableElmt<K,D>::TableElmt(const K& new_key,const D& new_data)
  :key(new_key),data(new_data)
{
}

template <class K,class D>
Table<K,D>::~Table()
{
  TableElmt<K,D> *te_ptr;

  data_ls.goFirst();
  while(!data_ls.isEmpty()){
    te_ptr = (TableElmt<K,D>*)data_ls.getData();
    delete te_ptr;
    data_ls.deleteCurrent();
  }
}

//insert new data with key into the table
//delete previous occurence of data with the same key
//(duplicates are not allowed in a table)
template <class K,class D>
Table<K,D>& Table<K,D>::insert(const K& new_key,const D& new_data)
{
  TableElmt<K,D> *te_ptr;

  this->remove(new_key);

  data_ls.goLast();
  te_ptr = new TableElmt<K,D>(new_key,new_data);
  data_ls.insertRight(te_ptr);

  data_ls.goFirst();

  return *this;
}

template <class K,class D>
Table<K,D>& Table<K,D>::remove(const K& new_key)
{
  TableElmt<K,D> *te_ptr;
  for (data_ls.goFirst();!data_ls.isOffright();data_ls.forth()){
    te_ptr = (TableElmt<K,D>*)data_ls.getData();
    if (te_ptr->key == new_key){
      delete te_ptr;
      data_ls.deleteCurrent();
      break;
    }
  }

  data_ls.goFirst();
  return *this;
}

//find the data associated with key
//throw Lookup -exception if key not found
template <class K,class D>
D& Table<K,D>::lookup(const K& new_key)
{
  TableElmt<K,D> *te_ptr;

  for (data_ls.goFirst();!data_ls.isOffright();data_ls.forth()){
    te_ptr = (TableElmt<K,D>*)data_ls.getData();
    if (te_ptr->key == new_key){
      return te_ptr->data;
    }
  }
  
  //exception handling (by the user of this class)
  throw Lookup(); 
  
}
    
}//namespace cxxadt

#endif //TABLEI_H

#ifdef TABLE
#include <CString.h>
#include <stdlib.h>
int main()
{
  Table<CString,int> t1;
  CString a("a"),b("b"),c("c");

  t1.insert(a,1).insert(b,2).insert(c,3);

  cout << t1.lookup(a)<< " " << t1.lookup(b) << " " << t1.lookup(c)<< endl;
  try{
     t1.lookup("d");
  }
  catch (Table<CString,int>::Lookup){
    cout << "exception caught"<<endl;
  }
  
  exit(0);
}

#endif

  

