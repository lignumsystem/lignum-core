#ifndef CONNECTION_MATRIX_H
#define CONNECTION_MATRIX_H

#include <vector>

namespace Lignum{

template <class TS,class BUD>
class ConnectionMatrix{
public:
  ConnectionMatrix(Axis<TS,BUD>& axis);    
  void print()const;
  int getSize()const{return size;}
  int getNumberOfAxes(void)const;
  bool lastTreeSegment(TreeSegment<TS,BUD> *ts)const;
  TreeSegment<TS,BUD>* getTreeSegment(int,int)const;
  void saveDeltaPressure(TreeSegment<TS,BUD> *ts, LGMdouble delta_pressure);
  LGMdouble getDeltaPressure(TreeSegment<TS,BUD> *ts);
  TreeSegment<TS,BUD>* getTreeSegment(int i)const{ return pointer[i][i];}
private:
  TreeSegment<TS,BUD> ***pointer;
  vector<double> pressure;
  int size;
  int CountTreeSegments(Axis<TS,BUD> &ax) const;
  void TraverseAxis(Axis<TS,BUD> &ax, TreeSegment<TS,BUD> *ts);
  void addConnection(TreeSegment<TS,BUD> *ts1, TreeSegment<TS,BUD> *ts2);
};

}//close namespace Lignum
#endif
