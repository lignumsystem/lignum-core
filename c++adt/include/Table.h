#ifndef TABLE_H
#define TABLE_H

#include <DList.h>
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
  class Lookup{};
private:
  DList data_ls;
};
#endif
