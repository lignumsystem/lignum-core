#ifndef TREESEGMENT_WITH_FLOW_H
#define TREESEGMENT_WITH_FLOW_H

#include <LGMdecl.h>
#include <LGMUnits.h>
#include <LGMSymbols.h>


namespace Lignum{

class TreeSegmentWithFlowAttributes{
public:
  TreeSegmentWithFlowAttributes()
    :Pr(1.0),fin(0.0),fout(0.0),Wm(0) {}
  PA Pr;                  //Pressure
  LGMdouble fin;          //Amount of water coming in
  LGMdouble fout;         //Amount of water going out
  KGC Wm;                 //Water mass of the tree segment 
  
};


template <class TS,class BUD=DefaultBud<TS> > 
class TreeSegmentWithFlow
{
  template <class TS1, class BUD1>
  friend LGMdouble GetValue(const TreeSegmentWithFlow<TS1,BUD1>& tc, const LGMFLOW name);
  template <class TS1, class BUD1>
  friend LGMdouble SetValue(TreeSegmentWithFlow<TS1,BUD1>& tc, const LGMFLOW name,
			    const LGMdouble value);
  private:
  LGMdouble wm;
  TreeSegmentWithFlowAttributes tswf;
  
  public:
  TreeSegmentWithFlow();
};

template <class TS,class BUD>
TreeSegmentWithFlow<TS,BUD>::TreeSegmentWithFlow()
{
	wm = 0;
}


template <class TS,class BUD>
LGMdouble GetValue(const TreeSegmentWithFlow<TS,BUD>& ts, const LGMFLOW name)
{
	if (name == fin)
		return ts.tswf.fin;
  
	else if (name == fout)
		return ts.tswf.fout;

	else if (name == Pr)
		return ts.tswf.Pr;

	else if (name == Wm)
		return ts.tswf.Wm;

	return 0.0;
}


template <class TS,class BUD>
LGMdouble SetValue(TreeSegmentWithFlow<TS,BUD>& ts, const LGMFLOW name,
				const LGMdouble value)
{
	LGMdouble old_value = GetValue(ts,name);
  
	if (name == fin)
		ts.tswf.fin = value;
  
	else if (name == fout)
		ts.tswf.fout = value;

	else if (name == Pr)
		ts.tswf.Pr = value;

	else if (name == Wm)
		ts.tswf.Wm = value;


  return old_value;
}

}

#endif

