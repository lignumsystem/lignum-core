#ifndef TREEI_H
#define TREEI_H

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
void Tree<TS,BUD>::UpdateWaterFlow(TP time_step, const ConnectionMatrix<TS,BUD> &cm)
{
  // This counts the flow in for every segment
  for (int i=0; i<cm.getSize(); i++){
    TreeSegment<TS,BUD> *out;
    if(cm.getTreeSegment(i) != NULL)  
      out = cm.getTreeSegment(i);
    
    for (int a=0; a<cm.getSize(); a++){
      if (i != a && cm.getTreeSegment(i, a) != 0){

	TreeSegment<TS,BUD> *in = cm.getTreeSegment(i,a);	
	SetTSAttributeValue(*in, fin, CountFlow(*in, *out));
      }
      SetTSAttributeValue(*out, fout, 0);   
    }	
  }

  TreeSegment<TS,BUD> *in = cm.getTreeSegment(0);
  SetTSAttributeValue(*in, fin, cm.getSize() * 0.12e-9);
  
  // This counts the flow out for every segment
  for (i=0; i<cm.getSize(); i++){
    TreeSegment<TS,BUD> *out;
    if(cm.getTreeSegment(i) != 0)  
      out = cm.getTreeSegment(i);
    for (int a=0; a<cm.getSize(); a++){
      if (i != a && cm.getTreeSegment(i,a) != 0){
	TreeSegment<TS,BUD> *in = cm.getTreeSegment(i,a);
	SetTSAttributeValue(*out, fout, GetTSAttributeValue(*out, fout)+GetTSAttributeValue(*in, fin));
      }
    }

    TP Dw = GetTSAttributeValue(*out, R);  //diameter of sapwood
    
    TP new_pressure = GetTSAttributeValue(*out, Pr) + time_step * ttp.Er / Dw * 2  /
      (ttp.rhow * PI_VALUE *  GetTSAttributeValue(*out, L) *  GetTSAttributeValue(*out, R)) *
      ( GetTSAttributeValue(*out, fin) - GetTSAttributeValue(*out, fout) - 
	out->GetTranspiration(time_step));  
    
   
     cout << i << ":virtaus sisään " <<  GetTSAttributeValue(*out, fin)*time_step << " ; ulos " 
	  << GetTSAttributeValue(*out, fout)*time_step << " haihdunta:" << out->GetTranspiration(time_step)*time_step;
    cout << "SUMMA = " <<  (GetTSAttributeValue(*out, fin) - GetTSAttributeValue(*out, fout) -  out->GetTranspiration(time_step))*time_step 
	 << endl;
   
        
    SetTSAttributeValue(*out, Pr, new_pressure);         
    SetTSAttributeValue(*out, Wm, GetTSAttributeValue(*out, Wm) + (GetTSAttributeValue(*out, fin)-  GetTSAttributeValue(*out, fout) - out->GetTranspiration(0.0))* time_step); 
  }
  cout << endl; 
}



// This method counts the flow from the TreeSegment below (out) to the TreeSegment above.

template <class TS,class BUD>
TP Tree<TS,BUD>::CountFlow(TreeSegment<TS,BUD> &in, TreeSegment<TS,BUD> &out)

{
  TP ar = GetTSAttributeValue(out, area);
  TP le = GetTSAttributeValue(out, L);
  TP he = GetTSAttributeValue(in, Hm) - GetTSAttributeValue(out, Hm);

  TP pr_out = GetTSAttributeValue(out, Pr);  // Pressure in the element above
  TP pr_in = GetTSAttributeValue(in, Pr);    // Pressure in the element below
 
  return ttp.rhow * (ttp.k/ ttp.eta) * (ar / le) * (pr_out - pr_in - (ttp.rhow * ttp.g * he));
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
  TP p;
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
    p = (TP) atof((const char *)value.getValue());
    cout << " Parameter: " << name.getValue() << " = " << p << endl;
    if (name.getValue() == CString("lambda"))
      SetTransitVariableValue(tree,lambda,p);
    else{
      CString str = name.getValue();
      map<const char*,TPD,cmpstr>::iterator tpd = maptpd.tpd.find(str);
      SetParameterValue(tree,(*tpd).second,p);
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

}

//Get a parameter value 
template <class TS,class BUD>
TP GetParameterValue(const Tree<TS,BUD>& tree, const TPD name)
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

  else{
    cerr << "GetParameterValue() uknown parameter: " << name << " returning 0.0" 
	 << endl;
  }
  return 0.0;
}

//Change a parameter value, return the old value
template <class TS,class BUD>
TP SetParameterValue(Tree<TS,BUD>& tree, const TPD name, const TP value)
{
  TP old_value = GetParameterValue(tree,name);

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

  else{
    cerr << "SetParameterValue unknown parameter: " << name << " returning 0.0" 
	 << endl;
  }
  return old_value;
}

template <class TS,class BUD>
TP GetTransitVariableValue(const Tree<TS,BUD>& tree, const TTD name)
{
  if (name == lambda)
    return tree.ttp.lambda;
  
  else{
    cerr << "GetTransitVariableValue unknown parameter: " << name << " returning 0.0" 
	 << endl;
  }

  return 0.0;
}

template <class TS,class BUD>
TP SetTransitVariableValue(Tree<TS,BUD>& tree, const TTD name, const TP value)
{
  TP old_value = GetTransitVariableValue(tree,name);
  
  if (name == lambda)
    tree.ttp.lambda = value;
  else{
    cerr << "SetTransitVariableValue unknown parameter: " << name << " returning "
	 << old_value << endl;
  }
  return old_value;
}

template <class TS,class BUD>
TP GetAttributeValue(const Tree<TS,BUD>& tree, const TAD name)
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
    cerr << "GetAttributeValue  unknown attribute: " << name << " returning 0.0" 
	 << endl;
  }

  return 0.0;
}

template <class TS,class BUD>
YEAR GetAttributeValue(const Tree<TS,BUD>& tree, const TAI name)
{
  if (name == age)
    return  tree.ta.age;
  else{
     cerr << "GetAttributeValue unknown attribute: " << name << " returning 0.0"
	  << endl;
  }

  return 0;
}

template <class TS,class BUD>
TP SetAttributeValue(Tree<TS,BUD>& tree, const TAD name, const TP value)
{
  TP old_value = GetAttributeValue(tree,name);

  if (name == lb)
    tree.ta.lb = value;

  else if (name == P)
    tree.ta.P = value;

  else if (name == M)
     tree.ta.M = value;
 
  else if (name == Wr)
    tree.ta.Wr = value;

  else{
    cerr << "SetAttributeValue unknown attribute: " << name << " returning " 
	 << old_value << endl;
  }

  return old_value;
}
  
template <class TS,class BUD>
YEAR SetAttributeValue(Tree<TS,BUD>& tree, const TAI name, const YEAR value)
{
  YEAR old_value = GetAttributeValue(tree,name);

  if (name == age)
    tree.ta.age = value;
  else{
    cerr << "SetAttributeValue unknown attribute: " << name << " returning " 
	 << old_value << endl;
  }

  return old_value;
}

#endif

#ifdef TREE
#include <stdlib.h>
#include <iostream.h>

int main()
{
  cout << "OK" << endl;
  exit(0);
}

#endif

