#ifndef TREEI_H
#define TREEI_H
using namespace sky;
namespace Lignum{

template <class TS,class BUD>
Tree<TS,BUD>::Tree()
{
  tree = NULL;
}

//Construct a tree at a certain position to a certain direction
//with one terminating bud in the main axis
template <class TS,class BUD>
Tree<TS,BUD>::Tree(const Point& p, const PositionVector& d)
  :TreeCompartment<TS,BUD>(p,d,this),axis(p,d,this),f(5,5)
{
  //force the instantiation of BranchingPoint
  BranchingPoint<TS,BUD>(p,d,this);
}




//The initialization of the tree.
//Install parameters and functions.
//TreeMetaFileParser  parsers the 'meta_file'
//and after that the file names for the parameters and functions 
//are known. 
//Parameters: Then the lexer 'lex' can tokenize the parameter files
//to a list of: [name,value,name,value,...,name,value,ENDFILE]
//Then install the parameters.
//Functions: Functions are represented as parametric curves
//that are given as (x,y) pairs in an ASCII file
//ParametricCurve can read and create internal representation
//for a parametric curve and evaluate it in any point.
template <class TS,class BUD>
void InitializeTree(Tree<TS,BUD>& tree, const string& meta_file)
{
  LGMdouble p;
  string file;
  Lex lex;
  Token name,value;
  TreeMetaFileParser tmfp(meta_file);
  MapTPD maptpd;

  tmfp.parse();

  file = tmfp.getParameterFile("Tree");
  cout << "Reading parameters for tree from: " << file << endl;
  lex.scan(file);

  name = lex.getToken();
  while (name.getType() != ENDFILE){
    value = lex.getToken(); 
    p = (LGMdouble) atof(value.getValue().c_str());
    cout << " Parameter: " << name.getValue() << " = " << p << endl;
    if (name.getValue() == string("lambda"))
      SetValue(tree,lambda,p);
    else{
      string str = name.getValue();
      map<string,LGMPD,cmpstr>::iterator tpd = maptpd.tpd.find(str.c_str());
      SetValue(tree,(*tpd).second,p);
    }
    name = lex.getToken();
  }

  file = tmfp.getFunctionFile(string("Buds"));
  cout << "Reading function for number of new buds from: " << file << endl;
  tree.tf.nb.install(file.c_str());

  file = tmfp.getFunctionFile(string("DoI"));
  cout << "Reading function for DoI from: " << file << endl;
  tree.tf.ip.install(file.c_str());

  file = tmfp.getFunctionFile(string("FoliageMortality"));
  cout << "Reading function for foliage mortality from: " << file << endl;
  tree.tf.fm.install(file.c_str());

  file = tmfp.getTreeInitializationFile(string("Tree"));
  cout << "Reading tree initialization file from: " << file << endl;
  tree.tif.install(file.c_str());

}

//Get a parameter value 
template <class TS,class BUD>
LGMdouble GetValue(const Tree<TS,BUD>& tree, const LGMPD name)
{
  if (name == af)
    return tree.tp.af;

  else if (name == ar)
     return tree.tp.ar;

  else if (name == lr)
    return tree.tp.lr;
  
  else if (name == mf)
    return tree.tp.mf;

  else if (name == mr)
    return tree.tp.mr;

  else if (name == ms)
    return tree.tp.ms;

  else if (name == na)
    return tree.tp.na;

  else if (name == nl)
    return tree.tp.nl;

  else if (name == pr)
    return tree.tp.pr;

  else if (name == q)
    return tree.tp.q;

  else if (name == sr)
    return tree.tp.sr;

  else if (name == ss)
    return tree.tp.ss;

  else if (name == rho)
    return tree.tp.rho;

  else if (name == xi)
     return tree.tp.xi;

  else if (name == zbrentEpsilon)
     return tree.tp.zbrentEpsilon;

  else{
    cerr << "GetValue() uknown parameter: " << name << " returning 0.0" 
	 << endl;
  }
  return 0.0;
}

//Change a parameter value, return the old value
template <class TS,class BUD>
LGMdouble SetValue(Tree<TS,BUD>& tree, const LGMPD name, const LGMdouble value)
{
  LGMdouble old_value = GetValue(tree,name);

  if (name == af)
    tree.tp.af = value;

  else if (name == ar)
    tree.tp.ar = value;

  else if (name == lr)
    tree.tp.lr = value;
  
  else if (name == mf)
    tree.tp.mf = value;

  else if (name == mr)
    tree.tp.mr = value;

  else if (name == ms)
    tree.tp.ms = value;

  else if (name == na)
    tree.tp.na = value;

  else if (name == nl)
    tree.tp.nl = value;

  else if (name == pr)
    tree.tp.pr = value;

  else if (name == q)
    tree.tp.q = value;

  else if (name == sr)
    tree.tp.sr = value;

  else if (name == ss)
    tree.tp.ss = value;

  else if (name == rho)
    tree.tp.rho = value;

  else if (name == xi)
    tree.tp.xi = value;

  else if (name == zbrentEpsilon)
    tree.tp.zbrentEpsilon = value;

  else{
    cerr << "SetValue unknown parameter: " << name << " returning 0.0" 
	 << endl;
  }
  return old_value;
}

template <class TS,class BUD>
LGMdouble GetValue(const Tree<TS,BUD>& tree, const LGMTD name)
{
  if (name == lambda)
    return tree.ttp.lambda;
  
  else{
    cerr << "GetValue unknown parameter: " << name << " returning 0.0" 
	 << endl;
  }

  return 0.0;
}

template <class TS,class BUD>
LGMdouble SetValue(Tree<TS,BUD>& tree, const LGMTD name, const LGMdouble value)
{
  LGMdouble old_value = GetValue(tree,name);
  
  if (name == lambda)
    tree.ttp.lambda = value;
  else{
    cerr << "SetValue unknown parameter: " << name << " returning "
	 << old_value << endl;
  }
  return old_value;
}

template <class TS,class BUD>
LGMdouble GetValue(const Tree<TS,BUD>& tree, const LGMAD name)
{ 
  if (name == lb)
    return tree.ta.lb;

  else if (name == P)
     return tree.ta.P;

  else if (name == M)
     return tree.ta.M;

  else if (name == Wr)
     return tree.ta.Wr;

  else {
    //    cerr << "GetValue  unknown attribute: " << name << " returning 0.0" 
    //	 << endl;
    return GetValue(dynamic_cast<const TreeCompartment<TS,BUD>&>(tree), name);
  }

  //  return 0.0;
}

template <class TS,class BUD>
LGMdouble SetValue(Tree<TS,BUD>& tree, const LGMAD name, const LGMdouble value)
{
  LGMdouble old_value = GetValue(tree,name);

  if (name == lb)
    tree.ta.lb = value;

  else if (name == P)
    tree.ta.P = value;

  else if (name == M)
     tree.ta.M = value;
 
  else if (name == Wr)
    tree.ta.Wr = value;

  else{
//      cerr << "SetValue unknown attribute: " << name << " returning " 
//  	 << old_value << endl;
    old_value=SetValue(dynamic_cast<TreeCompartment<TS,BUD>&>(tree),name,value);
  }

  return old_value;
}
  

template <class TS,class BUD>
Axis<TS,BUD>& GetAxis(Tree<TS,BUD>& t)
{
  return t.axis;
}

//At the moment returns the name of the only (ASCII) file that contains
//the definition of the initial tree. Later - maybe - several such files.
template<class TS, class BUD>
string GetTreeInitializationFile(Tree<TS,BUD>& tree) {
  return tree.tif.treeFile;
}


template <class TS,class BUD>
void SetFirmament(const Tree<TS,BUD>& tree, const FirmamentWithMask& frmnt)
{
  tree.f = frmnt;
}
 
template <class TS,class BUD>
FirmamentWithMask& GetFirmament(Tree<TS,BUD>& tree) {
  return tree.f;
}




} //close namespace Lignum

#endif //TREEI_H



#ifdef TREE
#include <stdlib.h>
#include <iostream>

int main()
{
  cout << "OK" << endl;
  exit(0);
}


#endif

