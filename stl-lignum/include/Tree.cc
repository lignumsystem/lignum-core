#include <Tree.h>

//Constructor of connection matrix reserves memory
//for n * n matrix.
ConnectionMatrix::ConnectionMatrix(int n)
{
  size = n;
  pointer = new long int*[n];
  for (int i=0; i<n; i++)
    pointer[i] = new long int[n];

  for (int x=0; x<n; x++)
    for (int y=0; y<n; y++)
      pointer[x][y] = 0;

}

bool ConnectionMatrix::setValue(int r, int c, long int value)
{
  if (r>size-1 || c>size-1)
    return false;
  pointer[r][c] = value;
  return true;
}

void  ConnectionMatrix::AddConnection(long int s, long int t)
{ 
  pointer[GetRow(s)][GetRow(t)] = t;
}

void  ConnectionMatrix::print()
{
 for(int i=0; i<size; i++)
    {
      for(int a=0; a<size; a++)
	{
	  if (pointer[i][a]==0)
	    cout << "     -     ";
	  else cout << "  " << pointer[i][a];
	}
      cout << endl;
    }
}

  

int ConnectionMatrix::GetRow(long int a)
{
  for(int i=0; i<size; i++)
    {
      if (pointer[i][i] == 0)
	{
	  pointer[i][i]=a;
	  return i;
	}
      if (pointer[i][i] == a)
	return i;
    }
  return -1;
}

TreeParameters::TreeParameters()
{
  af = ar = lr = mf = 0.0;
  mr = ms = na = nl = pr = q = sr = ss = rho = xi = 0.0;
}

TreeAttributes::TreeAttributes()
{
  age = 0; lb = 0.0;
  P = M = Wr = 0.0;
}

TreeTransitVariables::TreeTransitVariables()
{
  lambda = 0.0;
}

template <class TS>
Tree<TS>::Tree()
{
  tree = NULL;
  cm = NULL;
}

//Construct a tree at a certain position to a certain direction
//with one terminating bud in the main axis
template <class TS>
Tree<TS>::Tree(const Point<METER>& p, const PositionVector& d)
  :TreeCompartment<TS>(p,d,this),axis(p,d,this)
{
  cm = NULL;
}




template <class TS>
TreeSegment<TS>* Tree<TS>::GetTreeSegment(Axis<TS> &ax, long int add)
{
  list<TreeCompartment<MyTreeSegment>*>& ls = GetTreeCompartmentList(ax);
  list<TreeCompartment<MyTreeSegment>*>::iterator I = ls.begin();
  
  while(I != ls.end())
    {
      if (TreeSegment<MyTreeSegment>* myts = dynamic_cast<TreeSegment<MyTreeSegment>*>(*I))
	{
	  if ((long int &)myts == add)
	    return myts;
	}
      if (BranchingPoint<MyTreeSegment>* mybp = dynamic_cast<BranchingPoint<MyTreeSegment>*>(*I))
      	{	 
	  list<Axis<TS>*>& axis_ls = GetAxisList(*mybp);  	  
	  list<Axis<TS>*>::iterator I = axis_ls.begin();
	  while(I != axis_ls.end())
	    {
	      Axis<MyTreeSegment> *axis = *I;
	      TreeSegment<MyTreeSegment> *ts = GetTreeSegment(*axis, add);
	      if (ts != NULL)
		return ts;
	      I++;	    
	    }
	}      
      I++;
    }
  return NULL;
}


template <class TS>
void Tree<TS>::UpdateWaterFlow()
{
  if (cm == NULL)
    this->BuiltConnectionMatrix();
  cm->print();


  for (int i=0; i<cm->size; i++)
    {
      TreeSegment<MyTreeSegment> *out;
      if(cm->pointer[i][i] != 0)  
	out = GetTreeSegment(this->axis, cm->pointer[i][i]);
      if (out == NULL)
	cout << "ei l;ytynyt" << endl;
      else for (int a=0; a<cm->size; a++)
	{
	  if (i != a && cm->pointer[i][a]!=0)
	    {
	      TreeSegment<MyTreeSegment> *in = GetTreeSegment(this->axis, cm->pointer[i][a]);
	      SetTSAttributeValue(*in, Pr, CountFlow(*in, *out));
	    }
	}
	
    }
  for (i=0; i<cm->size; i++)
    {
      TreeSegment<MyTreeSegment> *out;
      if(cm->pointer[i][i] != 0)  
	out = GetTreeSegment(this->axis, cm->pointer[i][i]);
      for (int a=0; a<cm->size; a++)
	{
	  if (i != a && cm->pointer[i][a]!=0)
	    {
	      TreeSegment<MyTreeSegment> *in = GetTreeSegment(this->axis, cm->pointer[i][a]);
	      SetTSAttributeValue(*out, Pr, GetTSAttributeValue(*out, fout)+GetTSAttributeValue(*in, fin));
	    }
	}
      
    }
}

template <class TS>
TP Tree<TS>::CountFlow(TreeSegment<TS> &in, TreeSegment<TS> &out)
{
  TP gravity = 9.81;
  TP viscosity = 1;
  TP permiability = 1;
  TP density = 1000;

  TP ar = GetTSAttributeValue(out, area);
  TP le = GetTSAttributeValue(out, L);
  TP he = GetTSAttributeValue(out, H);
  TP pr_out = GetTSAttributeValue(out, Pr);
  TP pr_in = GetTSAttributeValue(in, Pr);
 
  return (density * permiability / viscosity) * (ar / le) * (pr_out - pr_in - density*gravity*he);
}


template <class TS>
int Tree<TS>::CountTreeSegments(Axis<TS> &ax)
{
  int count = 0; 
  list<TreeCompartment<MyTreeSegment>*>& ls = GetTreeCompartmentList(ax);
  list<TreeCompartment<MyTreeSegment>*>::iterator I = ls.begin();
  
  while(I != ls.end())
    {
      if (TreeSegment<MyTreeSegment>* myts = dynamic_cast<TreeSegment<MyTreeSegment>*>(*I))
	{
	  count++;
	}
      if (BranchingPoint<MyTreeSegment>* mybp = dynamic_cast<BranchingPoint<MyTreeSegment>*>(*I))
      	{	 
	  list<Axis<TS>*>& axis_ls = GetAxisList(*mybp);  	  
	  list<Axis<TS>*>::iterator I = axis_ls.begin();
	  while(I != axis_ls.end())
	    {
	      Axis<MyTreeSegment> *axis = *I;
	      count = count + CountTreeSegments(*axis);
	      I++;	    
	    }
	}      
      I++;
    }
  return count;
}



template <class TS>
void Tree<TS>::BuiltConnectionMatrix()
{  
  TreeSegment<MyTreeSegment> *lastSegment = NULL;
  list<TreeCompartment<MyTreeSegment>*>& ls = GetTreeCompartmentList(axis);
  list<TreeCompartment<MyTreeSegment>*>::iterator I = ls.begin();
  cm = new ConnectionMatrix(CountTreeSegments(this->axis));

  while(I != ls.end())
    {
      if (TreeSegment<MyTreeSegment>* myts = dynamic_cast<TreeSegment<MyTreeSegment>*>(*I))
      	{	  	  
	  cm->AddConnection((long int &)myts, (long int &)lastSegment);
	  lastSegment = myts;
	}
      if (BranchingPoint<MyTreeSegment>* mybp = dynamic_cast<BranchingPoint<MyTreeSegment>*>(*I))
	{	 
	  list<Axis<TS>*>& axis_ls = GetAxisList(*mybp);  	  
	  list<Axis<TS>*>::iterator I = axis_ls.begin();
	  while(I != axis_ls.end())
	    {	      
	      Axis<MyTreeSegment> *axis = *I;
	      makeAxis(*axis, *lastSegment);
	      I++;
	    }
	  
	}
      I++;
    }
}




template <class TS>
void Tree<TS>::makeAxis(Axis<TS>& ax, TreeSegment<TS>& ts)
{
  TreeSegment<MyTreeSegment> *lastSegment = &ts;
  list<TreeCompartment<MyTreeSegment>*>& ls = GetTreeCompartmentList(ax);
  list<TreeCompartment<MyTreeSegment>*>::iterator I = ls.begin();
  
  while(I != ls.end())
    {
      if (TreeSegment<MyTreeSegment>* myts = dynamic_cast<TreeSegment<MyTreeSegment>*>(*I))
	{
	  cm->AddConnection((long int &)myts, (long int &)lastSegment);
	  lastSegment = myts;
	}
      if (BranchingPoint<MyTreeSegment>* mybp = dynamic_cast<BranchingPoint<MyTreeSegment>*>(*I))
      	{
	  list<Axis<TS>*>& axis_ls = GetAxisList(*mybp);  	  
	  list<Axis<TS>*>::iterator I = axis_ls.begin();
	  while(I != axis_ls.end())
	    {
	      Axis<MyTreeSegment> *axis = *I;
	      makeAxis(*axis, *lastSegment);
	      I++;	    
	    }
	}
      if (Bud<MyTreeSegment>* mybud = dynamic_cast<Bud<MyTreeSegment>*>(*I))
	{
	 
	}
      I++;

    }
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
template <class TS>
void InitializeTree(Tree<TS>& tree, const CString& meta_file)
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
      SetTreeTransitVariableValue(tree,lambda,p);
    else{
      CString str = name.getValue();
      map<const char*,TPD,cmpstr>::iterator tpd = maptpd.tpd.find(str);
      SetTreeParameterValue(tree,(*tpd).second,p);
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
template <class TS>
TP GetTreeParameterValue(const Tree<TS>& tree, const TPD name)
{
  if (name == af)
    return tree.tp.af;


  else if (name == ar)
     return tree.tp.ar;

  else if (name == fin)
    return tree.tp.ar;
  
  else if (name == fout)
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
template <class TS>
TP SetTreeParameterValue(Tree<TS>& tree, const TPD name, const TP value)
{
  TP old_value = GetTreeParameterValue(tree,name);

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

template <class TS>
TP GetTreeTransitVariableValue(const Tree<TS>& tree, const TTD name)
{
 cout << "14"<< endl;
  if (name == lambda)
    return tree.ttp.lambda;
  
  else{
    cerr << "GetTransitVariableValue unknown parameter: " << name << " returning 0.0" 
	 << endl;
  }

  return 0.0;
}

template <class TS>
TP SetTreeTransitVariableValue(Tree<TS>& tree, const TTD name, const TP value)
{
  TP old_value = GetTreeTransitVariableValue(tree,name);
  
  if (name == lambda)
    tree.ttp.lambda = value;
  else{
    cerr << "SetTransitVariableValue unknown parameter: " << name << " returning "
	 << old_value << endl;
  }
  return old_value;
}

template <class TS>
TP GetTreeAttributeValue(const Tree<TS>& tree, const TAD name)
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

template <class TS>
YEAR GetTreeAttributeValue(const Tree<TS>& tree, const TAI name)
{
  if (name == age)
    return  tree.ta.age;
  else{
     cerr << "GetAttributeValue unknown attribute: " << name << " returning 0.0"
	  << endl;
  }

  return 0;
}

template <class TS,class T1,class T2>
T2 SetTreeAttributeValue(Tree<TS>& tree, const T1 name, const T2 value)
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
  
template <class TS>
YEAR SetTreeAttributeValue(Tree<TS>& tree, const TAI name, const YEAR value)
{
  YEAR old_value = GetTreeAttributeValue(tree,name);

  if (name == age)
    tree.ta.age = value;
  else{
    cerr << "SetAttributeValue unknown attribute: " << name << " returning " 
	 << old_value << endl;
  }

  return old_value;
}

#ifdef TREE
#include <stdlib.h>
#include <iostream.h>

int main()
{
  cout << "OK" << endl;
  exit(0);
}

#endif
