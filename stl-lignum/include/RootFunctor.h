#ifndef ROOTFUNCTOR_H
#define ROOTFUNCTOR_H

#include <iostream>
#include <RootSystem.h>

namespace Lignum{

  template <class TREE>
    class EchoCompartmentName{
  public:
    RootCompartment<TREE>* operator()(RootCompartment<TREE>* rc)const;
  };

  template <class TREE>
    RootCompartment<TREE>* EchoCompartmentName<TREE>::operator()(RootCompartment<TREE>* rc)const{
    
    if (RootTip<TREE>* rt = dynamic_cast<RootTip<TREE>*> (rc)){
      cout << "I am RootTip" << endl;
    }
    else if (RootSegment<TREE>* rs = dynamic_cast<RootSegment<TREE>*> (rc)){
      cout << "I am RootSegment" << endl;
    }
    else if (RootBranchingPoint<TREE>* rbp = 
	     dynamic_cast<RootBranchingPoint<TREE>*> (rc)){
      cout << "I am RootBranchingPoint" << endl;
    }
    else if (RootAxis<TREE>* ra = dynamic_cast<RootAxis<TREE>*> (rc)){
      cout << "I am RootAxis" << endl;
    }
    else{
      cout << "Who am I?" << endl;
    }
  }

 
  template <class TREE> void DisplayStructure(RootAxis<TREE>& axis){
    DisplayStructure(&axis);
  }
  
  template <class TREE> void DisplayStructure(RootCompartment<TREE>* rc)
  {
    if (RootAxis<TREE>* axis =  dynamic_cast<RootAxis<TREE>*>(rc)){
      cout << "["; //begin of axis
      list<RootCompartment<TREE>*>& rc_ls = GetRootCompartmentList(*axis);
      typename list<RootCompartment<TREE>*>::iterator first = rc_ls.begin();
      typename list<RootCompartment<TREE>*>::iterator last = rc_ls.end();
      while (first != last)
	DisplayStructure(*first++);
      cout << "]" << flush; //end of axis
    }

    else if (RootBranchingPoint<TREE>* bp = dynamic_cast<RootBranchingPoint<TREE>*>(rc)){
      cout << "{"; //begin of branching point
      list<RootAxis<TREE>*>& axis_ls = GetAxisList(*bp);
      typename list<RootAxis<TREE>*>::iterator first = axis_ls.begin();
      typename list<RootAxis<TREE>*>::iterator last = axis_ls.end();
      for (int i = 0; i <axis_ls.size(); i++){
	DisplayStructure(*first++);
      }
      //the end of the branching point
      //the comma is because at least a bud follows  
      cout << "}," << flush; 
    }

    else if (RootSegment<TREE>* rs = dynamic_cast<RootSegment<TREE>*>(rc)){
      //the comma is because we know that a branching point will follow 
      cout << "RS," << flush;
    
    }

    else if (RootTip<TREE>* rt =  dynamic_cast<RootTip<TREE>*>(rc)){
      cout << "T" << flush;
    }
  }

  template <class TREE, class T>
    class CountRootCompartments{
  public:
    T& operator()(T& init,RootCompartment<TREE>* rc)const{
      init++;
      return init;
    }
  };

  template <class T>
    class AddRootCompartments{
  public:
    T& operator()(T& v1,T& v2)const{
      v1 += v2;
      return v1;
    }
  };

  template <class TREE>
    class PropagateStatusAsReference{
  public:
    LGMdouble operator()(LGMdouble& s,RootCompartment<TREE>* rc)const{
      if (RootTip<TREE>* rt = dynamic_cast<RootTip<TREE>*> (rc)){
	cout << "I am RootTip got status: " << s << endl;
	SetValue(*rt,LGMstatus,s);
      }
      else if (RootBranchingPoint<TREE>* rpb = 
	       dynamic_cast<RootBranchingPoint<TREE>*> (rc)){
	cout << "I am RootBranchingPoint got status: " << s << endl;
	s = s + 1.0;
      }
      return s;
    }
  };

  template <class TREE>
    class PropagateStatusAsValue{
  public:
    LGMdouble operator()(LGMdouble s,RootCompartment<TREE>* rc)const{
      if (RootTip<TREE>* rt = dynamic_cast<RootTip<TREE>*> (rc)){
	cout << "I am RootTip got status: " << s << endl;
	SetValue(*rt,LGMstatus,s);
      }
      else if (RootBranchingPoint<TREE>* rpb = 
	       dynamic_cast<RootBranchingPoint<TREE>*> (rc)){
	cout << "I am RootBranchingPoint got status: " << s << endl;
	s = s + 1.0;
      }
      return s;
    }
  };

}//closing namespace Lignum


#endif
