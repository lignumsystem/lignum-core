#ifndef CONNECTION_MATRIX_H
#define CONNECTION_MATRIX_H

template <class TS,class BUD>
class ConnectionMatrix{
public:
  ConnectionMatrix(Axis<TS,BUD>& axis);    
  void print()const;
  int getSize()const{return size;}
  TreeSegment<TS,BUD>* getTreeSegment(int,int)const;
  TreeSegment<TS,BUD>* getTreeSegment(int i)const{ return pointer[i][i];}
private:
  TreeSegment<TS,BUD> ***pointer;
  int size;
  int CountTreeSegments(Axis<TS,BUD> &ax) const;
  void TraverseAxis(Axis<TS,BUD> &ax, TreeSegment<TS,BUD> *ts);
  void addConnection(TreeSegment<TS,BUD> *ts1, TreeSegment<TS,BUD> *ts2);
};
#endif
