#include <Tree.h>

bool cmpstr::operator () (const char* s1,const char* s2)
{
  return strcmp(s1,s2) < 0;
}

MapTPD::MapTPD()
{
  tpd["af"] = af;
  tpd["ar"] = ar;
  tpd["lr"] = lr;
  tpd["mf"] = mf;
  tpd["mr"] = mr;
  tpd["ms"] = ms;
  tpd["na"] = na;
  tpd["nl"] = nl;
  tpd["pr"] = pr;
  tpd["q"] = q;
  tpd["sr"] = sr;
  tpd["ss"] = ss;
  tpd["rho"] = rho;
  tpd["xi"] = xi;
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
void InitializeTree(Tree& tree, const CString& meta_file)
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
TP GetParameterValue(const Tree& tree, const TPD name)
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
TP SetParameterValue(Tree& tree, const TPD name, const TP value)
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
    tree.tp.rho = value;

  else{
    cerr << "SetParameterValue unknown parameter: " << name << " returning 0.0" 
	 << endl;
  }
  return old_value;
}


TP GetTransitVariableValue(const Tree& tree, const TTD name)
{
  if (name == lambda)
    return tree.ttp.lambda;
  
  else{
    cerr << "GetTransitVariableValue unknown parameter: " << name << " returning 0.0" 
	 << endl;
  }

  return 0.0;
}

TP SetTransitVariableValue(Tree& tree, const TTD name, const TP value)
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


TP GetAttributeValue(const Tree& tree, const TAD name)
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
    cerr << "GetAttributeValue unknown attribute: " << name << " returning 0.0" 
	 << endl;
  }

  return 0.0;
}

YEAR GetAttributeValue(const Tree& tree, const TAI name)
{
  if (name == age)
    return  tree.ta.age;
  else{
     cerr << "GetAttributeValue unknown attribute: " << name << " returning 0.0"
	  << endl;
  }

  return 0;
}

template <class T1,class T2>
T2 SetAttributeValue(Tree& tree, const T1 name, const T2 value)
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
  
YEAR SetAttributeValue(Tree& tree, const TAI name, const YEAR value)
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



