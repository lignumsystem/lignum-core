#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <stdlib.h>
#include <stdarg.h>

#include <lglobal.h>
#include <lsysintrfc.h>

#include <succstor.h>

#include <iostream>
#include <Lignum.h>
#include <Collision.h>
#include <Lstring2Lignum.h>
#include <Lignum2Lstring.h>
#include <MyTreeSegment.h>
#include <MyBud.h>
#include <OpenGLUnix.h>

using namespace std;

Lstring mainstring;
Lstring derivedstring;

SuccessorStorage succstrg;
FILE* fOut;

void PrintLString(Lstring& s);

void _Add(const void* pX, int size)
{
  succstrg.Add(pX, size);
}

void Derive();
void Draw(int);
ProdCaller FindIMatch(const LstringIterator&, CallerData&);

ProdCaller  ContextMatch(const LstringIterator& pos,CallerData& caller_data,int& prod);

ProdCaller TryIMatch
  (const LstringIterator&, CallerData&, const ProductionPrototype&);
bool Considered(ModuleIdType);

char outputpth[PATH_MAX+1];

template <class TS, class BUD>
void SaveTree(Axis<TS,BUD> &ax, char* file_name, char* treetype)
{
  ofstream file(file_name);
  file << treetype << endl;
  SaveAxis(ax, file);
  file.close();
}

template <class TS, class BUD >
void SaveAxis(Axis<TS,BUD> &ax, ofstream& file)
{
   bool min_save = false;

   std::list<TreeCompartment<TS, BUD>*>& ls = GetTreeCompartmentList(ax);
   std::list<TreeCompartment<TS, BUD>*>::iterator I = ls.begin();

   if (!min_save)
     file << "AXIS"<< endl;

   while(I != ls.end())
     {
       TreeSegment<TS, BUD>* myts = dynamic_cast<TreeSegment<TS, BUD>*>(*I);
       
       if (TreeSegment<TS, BUD>* myts = dynamic_cast<TreeSegment<TS,BUD>*>(*I))
	 {
	   if (TreeSegment<TS, BUD> *ts = dynamic_cast<TreeSegment<TS,BUD>*>(*I))
	     {
	       if (!min_save)
		 file << "TS"<< " ";
	       file << *ts;    //* otettu en
	     }
	 }
       
       if (BranchingPoint<TS, BUD>* mybp = dynamic_cast<BranchingPoint<TS,
	   BUD>*>(*I))
	 {
	   std::list<Axis<TS, BUD>*>& axis_ls = GetAxisList(*mybp);
	   std::list<Axis<TS, BUD>*>::iterator II = axis_ls.begin();
	   
	   BranchingPoint<TS, BUD>* bp = dynamic_cast<BranchingPoint<TS,
	     BUD>*>(*I);
	   if (!min_save)
	     {
	       file << "BP"<< " ";
	       file << *bp << endl;
	     }
	   while(II != axis_ls.end())
	     {
	       Axis<TS,BUD> *axis = *II;
	       SaveAxis(*axis, file);
	       II++;
	     }
	   if (!min_save)
	     file << "BP_END"<< endl;
	 }

       if (Bud<TS, BUD>* mybud = dynamic_cast<Bud<TS, BUD>*>(*I))
	 {
	   Bud<TS, BUD>* bud = dynamic_cast<Bud<TS, BUD>*>(*I);
	   if(!min_save)
	     {
	       file << "BUD"<< " ";
	       file << *bud << endl;
	     }
	 }
       I++;
     }
   if (!min_save)
     
     file << "AXIS_END"<< endl;
}

int main(int argc, char** argv)
{
  //ios::sync_with_stdio();
  Tree<MyTreeSegment,MyBud> t1(Point(0,0,0),
				 PositionVector(0,0,1.0));
  if (2==argc)
    strcpy(outputpth, argv[1]);
  else
    outputpth[0] = 0;
  
  Start();
  mainstring.Add(succstrg);
  Lstring2Lignum<MyTreeSegment,MyBud,LGMAD,LGMdouble>(t1,mainstring,3,LGMtype,LGMstatus,LGMcollision);

  for (int i=0; i<DerivationLength(); i++)
  {
    ForEach(t1,EvaluateCollisionForAllBuds<MyTreeSegment,MyBud>(90.0*2.0*PI_VALUE/360.0,0.10));
    Lignum2Lstring<MyTreeSegment,MyBud,LGMAD,LGMdouble>(t1,mainstring,3,LGMtype,LGMstatus,LGMcollision);    
    Derive();
    Lstring2Lignum<MyTreeSegment,MyBud,LGMAD,LGMdouble>(t1,mainstring,3,LGMtype,LGMstatus,LGMcollision);
  }
  End();  

  VisualizeLGMTree(t1);

}

void PrintLString(Lstring& s)
{
  LstringIterator iterator(s);
  CallerData caller_data;
  double arg1;
  while (!iterator.AtEnd()){
    const char* name = iterator.GetCurrentModuleName();
    fprintf(stdout,"%s ",name);
    if (strcmp(name,"F") == 0){
      caller_data.Reset();
      caller_data.Strct.AddModuleAddr(iterator.Ptr());
      memcpy(&arg1,caller_data.Strct.pArg(0),sizeof(double));
      fprintf(stdout,"(%f)",arg1);
    }
    iterator++;
  }
}


void Draw(int i)
{
  LstringIterator iterator(mainstring);
  fOut = fopen(outputpth[0] ? outputpth : "dump.txt", "w");
  while (!iterator.AtEnd())
  {
    CallerData cd;
    ProdCaller pCaller = FindIMatch(iterator, cd);
    if (NULL != pCaller)
      pCaller(&cd);
    iterator++;
  }
  fclose(fOut);
  char bf[128];
/*
  sprintf(bf, "cp %s str%03d", outputpth, i);
  system(bf);
*/
  //system("echo \"Input|String|text|Input from *\" | command_client 3000");
}

void Derive()
{
  StartEach();
  LstringIterator iterator(mainstring);
  derivedstring.Clear();

  while (!iterator.AtEnd())
  {
    CallerData cd;
    int i;
    //ProdCaller pCaller = FindMatch(iterator, cd);
    ProdCaller pCaller = ContextMatch(iterator, cd, i);
    if (NULL == pCaller)
    {
      iterator.AppendCurrent(succstrg);
      iterator++;
    }
    else
    {
      pCaller(&cd);
      iterator+=cd.Strct.Count();
    }
    derivedstring.Add(succstrg);
  }
  mainstring.Swap(derivedstring);
  EndEach();
}


ProdCaller FindIMatch(const LstringIterator& citer, CallerData& cd)
{
  for (int i=0; i<NumOfIProductions(); i++)
  {
    ProdCaller res = TryIMatch(citer, cd, GetIProductionPrototype(i));
    if (NULL != res)
      return res;
  }
  return NULL;
}

ProdCaller TryIMatch
  (
  const LstringIterator& citer,
  CallerData& cd,
  const ProductionPrototype& proto
  )
{
  assert(proto.Strct.count==1);
  assert(proto.LCntxt.count==0);
  assert(proto.RCntxt.count==0);
  if (citer.GetModuleId() == proto.Strct.arr[0])
  {
    cd.Strct.AddModuleAddr(citer.Ptr());
    return proto.pCaller;
  }
  else
    return NULL;
}
