#ifndef TREEI_H
#define TREEI_H

namespace Lignum{

template <class TS,class BUD>
Tree<TS,BUD>::Tree()
{
  tree = NULL;
}

//Construct a tree at a certain position to a certain direction
//with one terminating bud in the main axis
template <class TS,class BUD>
Tree<TS,BUD>::Tree(const Point<METER>& p, const PositionVector& d)
  :TreeCompartment<TS,BUD>(p,d,this),axis(p,d,this)
{
}


template <class TS,class BUD>
void Tree<TS,BUD>::UpdateWaterFlow(LGMdouble time_step, const ConnectionMatrix<TS,BUD> &cm)
{
  // This counts the flow in for every segment
  for (int i=0; i<cm.getSize(); i++){
    TreeSegment<TS,BUD> *out;
    if(cm.getTreeSegment(i) != NULL)  
      out = cm.getTreeSegment(i);
    
    for (int a=0; a<cm.getSize(); a++){
      if (i != a && cm.getTreeSegment(i, a) != 0){

	TreeSegment<TS,BUD> *in = cm.getTreeSegment(i,a);	
	SetValue(*in, fin, CountFlow(*in, *out));
      }
      SetValue(*out, fout, 0);   
    }	
  }

  TreeSegment<TS,BUD> *in = cm.getTreeSegment(0);
  SetValue(*in, fin, cm.getSize() * 0.12e-9);
  
  // This counts the flow out for every segment
  for (i=0; i<cm.getSize(); i++){
    TreeSegment<TS,BUD> *out;
    if(cm.getTreeSegment(i) != 0)  
      out = cm.getTreeSegment(i);
    for (int a=0; a<cm.getSize(); a++){
      if (i != a && cm.getTreeSegment(i,a) != 0){
	TreeSegment<TS,BUD> *in = cm.getTreeSegment(i,a);
	SetValue(*out, fout, GetValue(*out, fout)+GetValue(*in, fin));
      }
    }

    LGMdouble Dw = GetValue(*out, R);  //diameter of sapwood
    
    LGMdouble new_pressure = GetValue(*out, Pr) + time_step * ttp.Er / Dw * 2  /
      (ttp.rhow * PI_VALUE *  GetValue(*out, L) *  GetValue(*out, R)) *
      ( GetValue(*out, fin) - GetValue(*out, fout) - 
	out->GetTranspiration(time_step));  
    
   
     cout << i << ":virtaus sisään " <<  GetValue(*out, fin)*time_step << " ; ulos " 
	  << GetValue(*out, fout)*time_step << " haihdunta:" << out->GetTranspiration(time_step)*time_step;
    cout << "SUMMA = " <<  (GetValue(*out, fin) - GetValue(*out, fout) -  out->GetTranspiration(time_step))*time_step 
	 << endl;
   
        
    SetValue(*out, Pr, new_pressure);         
    SetValue(*out, Wm, GetValue(*out, Wm) + (GetValue(*out, fin)-  GetValue(*out, fout) - out->GetTranspiration(0.0))* time_step); 
  }
  cout << endl; 
}



// This method counts the flow from the TreeSegment below (out) to the TreeSegment above.

template <class TS,class BUD>
LGMdouble Tree<TS,BUD>::CountFlow(TreeSegment<TS,BUD> &in, TreeSegment<TS,BUD> &out)

{
  LGMdouble ar = GetValue(out, A);
  LGMdouble le = GetValue(out, L);
  LGMdouble he = GetValue(in, Hm) - GetValue(out, Hm);

  LGMdouble pr_out = GetValue(out, Pr);  // Pressure in the element above
  LGMdouble pr_in = GetValue(in, Pr);    // Pressure in the element below
 
  return ttp.rhow * (ttp.k/ ttp.eta) * (ar / le) * (pr_out - pr_in - (ttp.rhow * ttp.g * he));
}


template <class TS,class BUD>
sky::Firmament& GetFirmament(Tree<TS,BUD>& tree)
{
  return tree.f;
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
void InitializeTree(Tree<TS,BUD>& tree, const CString& meta_file)
{
  LGMdouble p;
  CString file;
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
    p = (LGMdouble) atof((const char *)value.getValue());
    cout << " Parameter: " << name.getValue() << " = " << p << endl;
    if (name.getValue() == CString("lambda"))
      SetValue(tree,lambda,p);
    else{
      CString str = name.getValue();
      map<const char*,LGMPD,cmpstr>::iterator tpd = maptpd.tpd.find(str);
      SetValue(tree,(*tpd).second,p);
    }
    name = lex.getToken();
  }

  file = tmfp.getFunctionFile(CString("Buds"));
  cout << "Reading function for number of new buds from: " << file << endl;
  tree.tf.nb.install(file);

  file = tmfp.getFunctionFile(CString("DoI"));
  cout << "Reading function for DoI from: " << file << endl;
  tree.tf.ip.install(file);

  file = tmfp.getFunctionFile(CString("FoliageMortality"));
  cout << "Reading function for foliage mortality from: " << file << endl;
  tree.tf.fm.install(file);

  file = tmfp.getTreeInitializationFile(CString("Tree"));
  cout << "Reading tree initialization file from: " << file << endl;
  tree.tif.install(file);

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
  if (name == age)
    return tree.ta.age;

  else if (name == lb)
    return tree.ta.lb;

  else if (name == P)
     return tree.ta.P;

  else if (name == M)
     return tree.ta.M;

  else if (name == Wr)
     return tree.ta.Wr;

  else {
    cerr << "GetValue  unknown attribute: " << name << " returning 0.0" 
	 << endl;
  }

  return 0.0;
}

template <class TS,class BUD>
LGMdouble SetValue(Tree<TS,BUD>& tree, const LGMAD name, const LGMdouble value)
{
  LGMdouble old_value = GetValue(tree,name);

  if (name == age)
    return tree.ta.lb = value;

  if (name == lb)
    tree.ta.lb = value;

  else if (name == P)
    tree.ta.P = value;

  else if (name == M)
     tree.ta.M = value;
 
  else if (name == Wr)
    tree.ta.Wr = value;

  else{
    cerr << "SetValue unknown attribute: " << name << " returning " 
	 << old_value << endl;
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
CString GetTreeInitializationFile(Tree<TS,BUD>& tree) {
  return tree.tif.treeFile;
}


//  template <class TS,class BUD>
//  Firmament& GetFirmament(const Tree<TS,BUD>& tree) {
//    return tree.f;
//  }




} //close namespace Lignum

#endif //TREEI_H



#ifdef TREE
#include <stdlib.h>
#include <iostream.h>

int main()
{
  cout << "OK" << endl;
  exit(0);
}


#endif

