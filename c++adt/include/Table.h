/// \file Table.h
/// \brief Deprecated look up table
///
/// The Standard C++ version is available.
#ifndef TABLE_H
#define TABLE_H

#include <DList.h>

namespace cxxadt{

template <class K,class D> class Table;

template <class K,class D>
class TableElmt{
  friend class Table<K,D>;
  TableElmt(const K& new_key,const D& new_data);
private:
  const K key;
  D data;
};

template <class K,class D>
class Table{
public:
  ~Table();
  Table<K,D>& insert(const K& key,const D& data);
  D& lookup(const K& key);
  Table<K,D>& remove(const K& key);
  class Lookup{};//for exception
private:
  DList data_ls;
};

}//closing namespace cxxadt 

#include <TableI.h>

#endif
