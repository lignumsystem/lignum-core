#ifndef ROOTSYSTEMI_H
#define ROOTSYSTEMI_H

#include <iostream>

namespace Lignum{
  template <class TREE>
  LGMdouble GetValue(const RootSegment<TREE>& rs, LGMAD name)
  {
    //Getting values, first basic simple attributes
    switch (name){
    case LGAL:
      return rs.rsa.L;     //Length
    case R:
      return rs.rsa.R;     //Radius (sapwood)
    case LGARTop:
      return rs.rsa.RTop;  //Radius at top (sapwood)
    case Rh:
      return rs.rsa.Rh;    //Radius heartwood
    case LGARhair:
      return rs.rsa.Rhair; //Radius root hair
    case LGAomega:
      return rs.rsa.omega;
      //Compound attributes, areas
    case LGAA:                //Segment area based on R
      return PI_VALUE*pow(GetValue(rs,R),2.0);
    case LGAAh:               //Heartwood area
      return PI_VALUE*pow(GetValue(rs,Rh),2.0);
    case LGAAs:               //Sapwood Area
      return GetValue(rs,LGAA) - GetValue(rs,LGAAh);
    case LGAAhair:            //Root hair area
      return PI_VALUE*pow(GetValue(rs,LGARhair),2.0) - GetValue(rs,LGAA);
      //Compound attributes, volumes
    case LGAV:                //Segment volume based on A
      return GetValue(rs,LGAA)*GetValue(rs,LGAL);
    case LGAVh:               //Heartwood volume
      return GetValue(rs,LGAAh)*GetValue(rs,LGAL);
    case LGAVs:               //Sapwood volume
      return GetValue(rs,LGAV) - GetValue(rs,LGAVh);
    case LGAVhair:            //Root hair volume
      return GetValue(rs,LGAAhair)*GetValue(rs,LGAL) - GetValue(rs,LGAV);
      //Compound attributes, weights
    case LGAWs:               //sapwood weight
      return GetValue(GetTree(rs),rho_root)*GetValue(rs,LGAVs);
    case LGAWhair:            //root hair weight
      return GetValue(GetTree(rs),rho_hair)*GetValue(rs,LGAVhair);
    default:
      cout << "RootSegment GetValue unknown attribute: " << name << endl;
      return -1.0;
    }
  }

  //Setting values for root segment. Note: only simple values are set.
  template <class TREE>
  LGMdouble SetValue(RootSegment<TREE>& rs, LGMAD name, LGMdouble value)
  {
    LGMdouble old_value = GetValue(rs,name);
    
    switch (name){
    case LGAL:
      rs.rsa.L = value;
      break;
    case R:
      rs.rsa.R = value;
      break;
    case LGARTop:
      rs.rsa.RTop = value;
      break;
    case Rh:
      rs.rsa.Rh = value;
      break;
    case LGARhair:
      rs.rsa.Rhair = value;
      break;
    case LGAomega:
      rs.rsa.omega = value;
      break;
    default:
      cout << "RootSegment SetValue unknown (simple) attribute:"
	   << name << endl;
    }
    return old_value;
  }

   template <class TR>
   Point GetEndPoint(RootSegment<TR>& rs)
   {
      return GetPoint(rs)+GetValue(rs,LGAL)*(Point)GetDirection(rs);
   }

  //GetValue and SetValue  for RootTip. Attributes  status and  state feel
  //confusing, try  to rename them.  I believe  the enumeration STATUS
  //for state is the reason for confusion.
  template <class TREE>
  LGMdouble GetValue(const RootTip<TREE>& rt, LGMAD name)
  {
    switch (name){
    case LGAcollision:
       return rt.rta.collision;
    case LGMstatus:
       return rt.rta.status;
    case LGAomega:
       return rt.rta.omega;
    default:
       cout << "RootTip GetValue unknown attribute: " << name << endl;
       return -1.0;
    }
  }
  
  template <class TREE>
  LGMdouble SetValue(RootTip<TREE>& rt, LGMAD name, LGMdouble value)
  {
    LGMdouble old_value = GetValue(rt,name);
    switch (name){
    case LGAcollision:
      rt.rta.collision = value;
      break;
    case LGMstatus:
      rt.rta.status = value;
      break;
    case LGAomega:
      rt.rta.omega = value;
      break;
    default:
      cout << "RootTip SetValue unknown attribute: " << name << endl;
    }
 
    return old_value;
  }

  template <class TREE>
  STATUS GetValue(const RootTip<TREE>& rt, LGMAS name)
  {
     if (name == state){
       return rt.rta.state;
     }
     else{
       cout << "RootTip GetValue unknown status: " << name << endl;
       return rt.rta.state;
     }
  }

  template <class TREE>
  STATUS SetValue(RootTip<TREE>& rt, LGMAS name, STATUS value)
  {
    STATUS old_value = GetValue(rt,name);
    
    if (name == state){
      rt.rta.state = value;
    }

    return old_value;
  }

  template <class TREE>
    list<RootCompartment<TREE>*>& GetRootCompartmentList(RootAxis<TREE>& ra){
    return ra.rc_ls;
  }
  template <class TREE>
    void InsertRootCompartment(RootAxis<TREE>& ra,
			       const RootCompartment<TREE>* rpb){
    ra.rc_ls.push_back(rpb);
  }
  template <class TREE>
    list<RootAxis<TREE>*>& GetAxisList(RootBranchingPoint<TREE>& rbp){
    return rbp.ra_ls;
  }
  template <class TREE>
    void InsertAxis(RootBranchingPoint<TREE>& rbp,
		    const RootAxis<TREE>* ra){
    rpb.ra_ls.push_back(ra);
  }

  //Deleting cleanly RootAxis: delete RootCompartments in the list
  template <class TREE>
    class DeleteRootCompartment{
  public:
    void operator()(RootCompartment<TREE>* rc)const
    {
      delete rc;
    }
  };
  
  //Deleting cleanly RootBranchingPoint: delete RootAxes in the list
  template <class TREE>
    class DeleteAxis{
  public:
    void operator()(RootAxis<TREE>* ra)const
    {
      delete ra;
    }
  };
  
  template <class TREE> RootAxis<TREE>::~RootAxis()
  {
    //Looks g++  3.1 on Mac  requires that variable/object  ('drc') is
    //created explicitely.
    DeleteRootCompartment<TREE> drc;
    for_each(rc_ls.begin(),rc_ls.end(),drc);
  }

  template <class TREE> RootBranchingPoint<TREE>::~RootBranchingPoint()
  {
    //Looks  g++ 3.1 on  Mac requires  that variable/object  ('da') is
    //created explicitely.
    DeleteAxis<TREE> da;
    for_each(ra_ls.begin(),ra_ls.end(),da);
  }
  
}//closing namespace Lignum

#endif
