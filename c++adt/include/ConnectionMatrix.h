#ifndef CONNECTION_MATRIX_H
#define CONNECTION_MATRIX_H

template <class TS>
class ConnectionMatrix{
public:
  ConnectionMatrix(Axis<TS>& axis);    
  void print()const;
  int getSize()const{return size;}
  TreeSegment<TS>* getTreeSegment(int,int)const;
  TreeSegment<TS>* getTreeSegment(int i)const{ return pointer[i][i];}
private:
  TreeSegment<TS> ***pointer;
  int size;
  int CountTreeSegments(Axis<TS> &ax) const;
  void TraverseAxis(Axis<TS> &ax, TreeSegment<TS> *ts);
  void addConnection(TreeSegment<TS> *ts1, TreeSegment<TS> *ts2);
};
#endif
