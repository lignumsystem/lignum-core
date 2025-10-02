/// \file DebugTreeSegmentI.h
/// \brief Debug file output for TreeSegment implementation
#ifndef DEBUG_TREE_SEGMENTI_H
#define DEBUG_TREE_SEGMENTI_H

namespace Lignum{
  template <class TS, class BUD>
  void DebugTreeSegment<TS,BUD>::writeHeader()
  { 
    file << setw(14) << "X1" << setw(14) << "Y1" << setw(14) << "Z1"
	 << setw(14) << "X2" << setw(14) << "Y2" << setw(14) << "Z2"
	 << setw(14) << "DX" << setw(14) << "DY" << setw(14) << "DZ"
	 << setw(4)  << "GO" << setw(14) << "L"  << setw(14) << "Rbase"
	 << setw(14) << "Rtop" << setw(14) << "Dbase" << setw(14) << "Dtop"
	 << setw(14) << "Rhw" << " " << manip;
  }

  template <class TS, class BUD>
  void DebugTreeSegment<TS,BUD>::operator()(TreeCompartment<TS,BUD>* tc)const
  {
    if (TreeSegment<TS,BUD>* ts=dynamic_cast<TreeSegment<TS,BUD>*>(tc)){
      Point p1 = GetPoint(*ts);
      Point p2 = GetEndPoint(*ts);
      PositionVector d = GetDirection(*ts);
      double go = GetValue(*ts,LGAomega);
      double l = GetValue(*ts,LGAL);
      double rbase = GetValue(*ts,LGAR);
      double rtop = GetValue(*ts,LGARTop);
      double rhw = GetValue(*ts,LGARh);
      //Write the data
      //Base point
      double x1 = p1.getX();double y1 = p1.getY(); double z1 = p1.getZ();
      //End point
      double x2 = p2.getX();double y2 = p2.getY(); double z2 = p2.getZ();
      //Direction
      double dx1 = d.getX();double dy1 = d.getY(); double dz1 = d.getZ();
      file << setw(14) << x1 << setw(14) << y1 << setw(14) << z1
	   << setw(14) << x2 << setw(14) << y2 << setw(14) << z2
	   << setw(14) << dx1 << setw(14) << dy1 << setw(14) << dz1
	   << setw(4)  << go << setw(14) << l << setw(14) << rbase
	   << setw(14) << rtop << setw(14) << 2.0*rbase << setw(14) << 2.0*rtop
	   << setw(14) << rhw << " " << manip;
    }
  }
}//Closing namespace
#endif
