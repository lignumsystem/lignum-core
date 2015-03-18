#ifndef DEBUG_TREE_SEGMENT_H
#define DEBUG_TREE_SEGMENT_H
#include <fstream>
#include <iomanip>
#include <TreeCompartment.h>
using namespace std;

//'Manipulator' is the  type of 'flush' and  'endl' manipulators (More
//precisely, flush  and endl are  in fact templates  to be able  to be
//used with all kinds of streams)
typedef ostream& (*Manipulator) (ostream&);

//Print all TreeSegment variables to a file
//Usage: DebugTreeSegment<TS,BUD> debug("File.txt",endl)
//       debug.writeHeader()
//       ForEachTree(t,debug);
//       debug.close()
//DebugTreeSegment is  designed to be  expandable, i.e. to serve  as a
//base class for  similar classes to write data to  a file for further
//analysis.  For  example DebugCfTreeSegment  needs only  to implement
//output for variables in CfTreeSegment.
namespace Lignum{
  template <class TS,class BUD>
  class DebugTreeSegment{
  public:
    //By default  the stream  manipulator flushes  the output  so that
    //classes inhereting from  this class can append data  to the same
    //line
    DebugTreeSegment(fstream& f, Manipulator m = flush)
      :file(f),manip(m){}
    DebugTreeSegment(const DebugTreeSegment& db)
      :file(db.file),manip(db.manip){}
    DebugTreeSegment& operator=(const DebugTreeSegment& db){
      file=db.file;manip=db.manip;
    }
    //~DebugTreeSegment(){file.close();}
    //Write the titles for the data columns 
    void writeHeader();
    void operator()(TreeCompartment<TS,BUD>* tc)const;
    void close(){file.close();}
  protected:
    fstream& file;
    Manipulator manip;
  };
}//Closing namespace
#include <DebugTreeSegmentI.h>
#endif

