
#ifndef ZBRENTI_H
#define ZBRENTI_H

#define ITMAX 100

#include <fstream>
#include "WhiteBirch.h"
#include "SugarMaple.h"


//The value of wsum when lambda = 0
extern LGMdouble wSum_Lambda0;


extern ParametricCurve nol_fun;




using namespace Lignum;

template <class TS,class BUD>
LGMdouble BracketFunction(LGMdouble& a, LGMdouble& b, LGMdouble& fa, LGMdouble& fb, Tree<TS,BUD>& tree)
{
  adjustSegmentSizeLambda<TS,BUD> adjustSizeL;
  LGMdouble a_r = GetValue(tree, ar);


  a = 0.0;
  b = GetValue(tree, lambda);
  
  // deltaiW
  LGMdouble deltaiW = GetValue(tree, LGAP) - GetValue(tree, M);  

  debug_file << "photosynteesi: " << GetValue(tree, LGAP) << endl;
  debug_file << "Hengitys     : " << GetValue(tree, M) << endl;
  debug_file << "photosynteesi-hengitys: " << deltaiW << endl;	
  debug_file << "Kasvuun kuluva energia kun(lambda==0) " << wSum_Lambda0 << endl;



  fa = deltaiW - wSum_Lambda0;


  LGMdouble AsIni = 0.0;
  AdjustDiameterCfGrowth<TS,BUD> diamGrowth; 
  AsIni = AccumulateDown(tree, AsIni, diamGrowth);
  
  LGMdouble identity = 0.0;
  CollectDWAfterGrowth<TS,BUD> collectDW;
  LGMdouble  WSum = Accumulate(tree,  identity, collectDW);

  LGMdouble sum_nfol = 0.0f;
  CollectNewCfFoliageMass<TS,BUD> collectNFM;
  sum_nfol = Accumulate(tree,  sum_nfol, collectNFM);
  
  fb = deltaiW - WSum - (sum_nfol * a_r);
  
  debug_file << "fa " << fa << "   fb " << fb << '\n';	
  debug_file << "iteroidaan..." << '\n';

  while ((fb) > 0.0)
  {
    a = b;
    fa = fb;
    b = b * 1.30 + 0.1;
	ASSERT(b/a > 0);
	adjustSizeL.rel_lambda = b / a;

	
    SetValue(tree, lambda, b);
    ForEach(tree, adjustSizeL);

    AsIni = 0.0;
    AccumulateDown(tree, AsIni, diamGrowth);
    
	identity = 0.0;
    WSum = Accumulate(tree,  identity, collectDW);

	debug_file << "lambda " << b << "   rel_lambda " << b/a << "   Wsum " << WSum << '\n';
	
	sum_nfol = 0;
	sum_nfol = Accumulate(tree,  sum_nfol, collectNFM);
    fb = deltaiW - WSum - (sum_nfol * a_r);

	debug_file << "fa " << fa << "   fb " << fb << '\n';
  }

  debug_file << "Nolla-arvo löytyy väliltä [" << a << "," << b << "]" << '\n'; 

  return fb;
}








// BracketFunction for HwTree
template <class TS,class BUD>
LGMdouble HwBracketFunction(LGMdouble& a, LGMdouble& b,
				  LGMdouble& fa, LGMdouble& fb, Tree<TS,BUD>& tree)
{
  LGMdouble a_r = GetValue(tree, ar);
  LGMdouble AsIni = 0.0;

  AdjustDiameterHwGrowth<TS,BUD> diamGrowth;

  a = 0.0;
  b = GetValue(tree, lambda);
  

  LGMdouble deltaiW = GetValue(tree, LGAP) - GetValue(tree, LGAM); 

  fa = deltaiW - wSum_Lambda0;
  
  AsIni = 0.0;
  AsIni = AccumulateDown(tree, AsIni, diamGrowth);
  
  LGMdouble identity = 0.0;
  CollectDWAfterGrowth<TS,BUD> collectDW;
  LGMdouble  WSum = Accumulate(tree,  identity, collectDW);

  LGMdouble sum_nfol = 0.0f;
  CollectNewHwFoliageMass<TS,BUD> collectNFM;
  sum_nfol = Accumulate(tree,  sum_nfol, collectNFM);

  fb = deltaiW - WSum - sum_nfol - (sum_nfol * a_r);
  
  while ((fb) > 0.0)
  {
    a = b;
    fa = fb;
    b = b * 1.30 + 0.1;
    LGMassert(b/a > 0);
	
    SetValue(tree, lambda, b);
    AdjustNewLambda(tree);
 

    AsIni = 0.0;
    AccumulateDown(tree, AsIni, diamGrowth);
    
    identity = 0.0;
    WSum = Accumulate(tree,  identity, collectDW);

    sum_nfol = 0;
    sum_nfol = Accumulate(tree,  sum_nfol, collectNFM);

    fb = deltaiW - WSum - sum_nfol - (sum_nfol * a_r);

  }

  return fb;
}





//This method implements the Van Wijngaarden, Dekker and Brent method for root finding. 
//Arguments:
//       In: x1 which brackets the function P-R-F(L) on the left
//           x2 which brackets the function P-R-F(L) on the right
//           fa value of P-R-F(x1)
//           fb value of P-R-F(x2)
//           tol the tolerance 
//   return: the root of the  P-R-F(L) 
//Note: instead of 'b' the L_factor brackets the function P-R-F(L) on the right
//and finally denotes the root of the function
template <class TS,class BUD>
LGMdouble HwZbrent(LGMdouble x1,LGMdouble x2,LGMdouble fa, LGMdouble fb, LGMdouble tol, Tree<TS,BUD>& tree)
{
  	
  int iter;
  LGMdouble a=x1,c,d,e,min1,min2;
  LGMdouble fc,p,q,r,s,tol1,xm;
  //  DGrowthInfo dgi,dgi_ident;
  
  
  LGMdouble last_lambda = GetValue(tree,lambda);

  if (last_lambda == 0)
			debug_file << "kohta1: last lambda == 0 !!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;

  

  LGMdouble b = x2; // GetValue(tree,lambda);
 
  LGMdouble AsIni = 0.0, WSum;
  AdjustDiameterHwGrowth<TS,BUD> diamGrowth;


  //DiameterGrowthBookkeep<TS,BUD> bookkeep;
  LGMdouble identity = 0.0;
  CollectDWAfterGrowth<TS,BUD> collectDW;

  LGMdouble deltaiW = GetValue(tree,LGAP)-GetValue(tree,LGAM); // - wSum_LambdaO;
    
  fc=fb;
  for (iter=1;iter<=ITMAX;iter++) 
  {
		if (fb*fc > 0.0) 
		{
			c=a;
			fc=fa;
			e=d= b - a;
		}

		if (fabs(fc) < fabs(fb)) 
		{
			a= b; //GetValue(tree,lambda);
			b= c; //SetValue(tree,lambda,c);
			c=a;
			fa=fb;
			fb=fc;
			fc=fa;
		}


		tol1=2.0*EPS*fabs(GetValue(tree,lambda))+0.5*tol;
		xm=0.5*(c-b);
    
		if (fabs(xm) <= tol1 || fb == 0.0)
		{
			SetValue(tree,lambda, b);
			AdjustNewLambda(tree);

			debug_file << " Lopullinen lambda=" << b << '\n';
			return GetValue(tree,lambda);
		}

		if (fabs(e) >= tol1 && fabs(fa) > fabs(fb)) 
		{
			s=fb/fa;
			if (a == c) 
			{
				p=2.0*xm*s;
				q=1.0-s;
			} 
			else 
			{
				q=fa/fc;
				r=fb/fc;
				//  	p=s*(2.0*xm*q*(q-r)-((this->tree_attributes).L_factor-a)*(r-1.0));
				p=s*(2.0*xm*q*(q-r)-(b-a)*(r-1.0));
				q=(q-1.0)*(r-1.0)*(s-1.0);
			}
			if (p > 0.0)  
				q = -q;
			p=fabs(p);
			min1=3.0*xm*q-fabs(tol1*q);
			min2=fabs(e*q);
			if (2.0*p < (min1 < min2 ? min1 : min2)) 
			{
				e=d;
				d=p/q;
			} 
			else
			{
				d=xm;
				e=d;
			}
		} 
		else 
		{
			d=xm;
			e=d;
		}

		a=b; //GetValue(tree, lambda);
		fa=fb;

		if (fabs(d) > tol1)
			b += d; //SetValue(tree,lambda,GetValue(tree,lambda)+d);
		else
			b += (xm > 0.0 ? fabs(tol1) : -fabs(tol1));
	

		SetValue(tree,lambda, b);
		AdjustNewLambda(tree);

		AsIni = 0.0;
		LGMdouble result = AccumulateDown(tree, AsIni, diamGrowth);

		identity = 0.0;
		WSum = Accumulate(tree,  identity, collectDW);


		LGMdouble a_r = GetValue(tree, ar);

		LGMdouble sum_nfol = 0.0;
		CollectNewHwFoliageMass<TS,BUD> collectHwWB;
		LGMdouble rootGrowth = Accumulate(tree,  sum_nfol, collectHwWB) * a_r;	
		fb = deltaiW - WSum - rootGrowth;
	}

  MessageBox(NULL, "Maximum number of iterations", NULL, NULL);
  return GetValue(tree, lambda);	
  
}








//This method implements the Van Wijngaarden, Dekker and Brent method for root finding. 
//Arguments:
//       In: x1 which brackets the function P-R-F(L) on the left
//           x2 which brackets the function P-R-F(L) on the right
//           fa value of P-R-F(x1)
//           fb value of P-R-F(x2)
//           tol the tolerance 
//   return: the root of the  P-R-F(L) 
//Note: instead of 'b' the L_factor brackets the function P-R-F(L) on the right
//and finally denotes the root of the function
template <class TS,class BUD>
LGMdouble Zbrent(LGMdouble x1,LGMdouble x2,LGMdouble fa, LGMdouble fb, LGMdouble tol, Tree<TS,BUD>& tree)
{
  LGMdouble a_r = GetValue(tree, ar);	

  
  LGMdouble a,c,d,e,min1,min2;
  LGMdouble fc,p,q,r,s,tol1,xm;

  a = x1;
  c = 0;
  d = 0;
  e = 0;

  //  DGrowthInfo dgi,dgi_ident;
  adjustSegmentSizeLambda<TS,BUD> adjustSizeL;
  
  LGMdouble last_lambda = GetValue(tree,lambda);

  if (last_lambda == 0)
			debug_file << "kohta1: last lambda == 0 !!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;

  adjustSizeL.rel_lambda = 1;

  LGMdouble b = x2; // GetValue(tree,lambda);
 
  LGMdouble AsIni = 0.0, WSum;
  AdjustDiameterCfGrowth<TS,BUD> diamGrowth;


  //DiameterGrowthBookkeep<TS,BUD> bookkeep;
  LGMdouble identity = 0.0;
  CollectDWAfterGrowth<TS,BUD> collectDW;

  LGMdouble sum_nfol = 0.0f;
  CollectNewCfFoliageMass<TS,BUD> collectNFM;
  sum_nfol = Accumulate(tree,  sum_nfol, collectNFM);

  LGMdouble deltaiW = GetValue(tree,LGAP)-GetValue(tree,LGAM); // - wSum_LambdaO - (sum_nfol * a_r);
  
  // **********************
  fc=fb;
  for (int iter=1;iter<=ITMAX;iter++) 
  {
	  
		if (fb*fc > 0.0) 
		{
			
			c=a;
			fc=fa;
			d = b - a;
			e = d;
			
		}
		
		if (fc < fb) //fabs(fc) < fabs(fb)) 
		{
			a= b; //GetValue(tree,lambda);
			b= c; //SetValue(tree,lambda,c);
			c= a;
			fa=fb;
			fb=fc;
			fc=fa;		
		}
	

		tol1=2.0*EPS*fabs(GetValue(tree,lambda))+0.5*tol;
		xm=0.5*(c-b);
    
		if (fabs(xm) <= tol1 || fb == 0.0)
		{
			SetValue(tree,lambda, b);

			if (b==0)
				debug_file << "kohta2: b == 0 !!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;

		//	debug_file << "rel_lambda " << (GetValue(tree,lambda) / last_lambda) << '\n';
			adjustSizeL.rel_lambda = GetValue(tree,lambda) / last_lambda; 
			ForEach(tree, adjustSizeL);

			debug_file << " Lopullinen lambda=" << b << '\n';
			return GetValue(tree,lambda);
		}

		if (fabs(e) >= tol1 && fabs(fa) > fabs(fb)) 
		{
			s=fb/fa;
			if (a == c) 
			{
				p=2.0*xm*s;
				q=1.0-s;
			} 
			else 
			{
				q=fa/fc;
				r=fb/fc;
				//  	p=s*(2.0*xm*q*(q-r)-((this->tree_attributes).L_factor-a)*(r-1.0));
				p=s*(2.0*xm*q*(q-r)-(b-a)*(r-1.0));
				q=(q-1.0)*(r-1.0)*(s-1.0);
			}
			if (p > 0.0)  
				q = -q;
			p=fabs(p);
			min1=3.0*xm*q-fabs(tol1*q);
			min2=fabs(e*q);
			if (2.0*p < (min1 < min2 ? min1 : min2)) 
			{
				e=d;
				d=p/q;
			} 
			else
			{
				d=xm;
				e=d;
			}
		} 
		else 
		{
			d=xm;
			e=d;
		}

		a=b; //GetValue(tree, lambda);
		fa=fb;

		if (fabs(d) > tol1)
			b += d; //SetValue(tree,lambda,GetValue(tree,lambda)+d);
		else
			b += (xm > 0.0 ? fabs(tol1) : -fabs(tol1));
	

		SetValue(tree,lambda, b);
		LGMdouble odd = GetValue(tree,lambda) / last_lambda;
		adjustSizeL.rel_lambda =  odd;

	//	debug_file << "rel_lambda " << odd << '\n';

		last_lambda = GetValue(tree,lambda);
		if (last_lambda == 0)
			debug_file << " last lambda == 0 !!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;


		ForEach(tree, adjustSizeL);


		AsIni = 0.0;
		LGMdouble result = AccumulateDown(tree, AsIni, diamGrowth);

		identity = 0.0;
		WSum = Accumulate(tree,  identity, collectDW);

		sum_nfol = 0.0f;
		sum_nfol = Accumulate(tree,  sum_nfol, collectNFM);
		fb = deltaiW - WSum -   sum_nfol * a_r;
		
	}

  MessageBox(NULL, "Maximum number of iterations", NULL, NULL);
  return GetValue(tree, lambda);	
  
}




//Adjust the length of the size of the new segments. First bracket the function P-R-F(L)
//and then find the root using the Van Wijngaarden, Dekker and Brent method.
template <class TS,class BUD>
bool AdjustIncrementZbrent(Tree<TS,BUD>& tree)
{
 
  //Check first if production - consumption is enough to maintain the
  //the tree. That is, if deltaW(lambda=0) < P - M
  //The case deltaW(0) > P - M arises in the cases 1) P - M < 0
  // 2) sapwood senescence is high and dry matter investments are needed to counteract
  //it, i.e. deltaW(0) = large.
  LGMdouble balance = GetValue(tree, LGAP) - GetValue(tree, M);
  if(balance <= 0.0) 
  {
		cerr << "M>P, growth not possible" << endl;
		return false;
  }

  if (debug_file.is_open() == false)
	debug_file.open("debug.txt");

  debug_file << "\n\n\n\nUusi kasvatus......" << endl;

  LGMdouble a=0,b=0,fa=0,fb=0;
  
  BracketFunction(a,b,fa,fb,tree);

  LGMdouble zBe = 0.001; //GetValue(tree, zbrentEpsilon);
  Zbrent(a,b,fa,fb, zBe, tree );


  //debug_file.close();
  return true;
}



//Adjust the length of the size of the new segments. First bracket the function P-R-F(L)
//and then find the root using the Van Wijngaarden, Dekker and Brent method.
template <class TS,class BUD>
bool AdjustIncrementHwZbrent(Tree<TS,BUD>& tree)
{
 
  //Check first if production - consumption is enough to maintain the
  //the tree. That is, if deltaW(lambda=0) < P - M
  //The case deltaW(0) > P - M arises in the cases 1) P - M < 0
  // 2) sapwood senescence is high and dry matter investments are needed to counteract
  //it, i.e. deltaW(0) = large.
  LGMdouble balance = GetValue(tree, LGAP) - GetValue(tree, M);
  if(balance <= 0.0) 
  {
		cerr << "M>P, growth not possible" << endl;
		return false;
  }

  if (debug_file.is_open() == false)
	debug_file.open("debug.txt");

  debug_file << "\n\n\n\nUusi kasvatus......" << endl;

  LGMdouble a=0,b=0,fa=0,fb=0;
  
  HwBracketFunction(a,b,fa,fb,tree);

  LGMdouble zBe = 0.001; // GetValue(tree, zbrentEpsilon);
  HwZbrent(a,b,fa,fb, zBe, tree );


  //debug_file.close();
  return true;
}


template <class TS,class BUD>
void AdjustNewLambda(Tree<TS,BUD> &tree)
{
	Axis<TS,BUD> &axis = GetAxis(tree);

	int i=0;
	Accumulate(tree,i,CountTreeSegments<TS,BUD>());
	RemoveNewComparments(axis);


	i=0;
	Accumulate(tree,i,CountTreeSegments<TS,BUD>());
	Firmament& f = GetFirmament(tree);
	LGMdouble B = f.diffuseBallSensor();

	MotherInfo init;
	init.vi = 1.0;
	init.Qin = 0.0;
	init.B = B;
		

	//******** tee zbrent abstarktisti ja tämän voi sitten poistaa.. class zbrent..
	TS *tse = new TS(Point(0,0,0),PositionVector(0,0,1), 0, 0, 0, 0, &tree);
	if (WhiteBirch *wb = dynamic_cast<WhiteBirch *>(tse))
	{
		AddWhiteBirchSegments<TS,BUD> functor;
		PropagateUp(tree, init, functor);
		
	}
	if (SugarMaple* wb = dynamic_cast<SugarMaple *>(tse))
	{
		AddSugarMapleSegments<TS,BUD> functor;
		functor.bud_fun = nol_fun;
		PropagateUp(tree, init, functor);
		
	}
	delete tse;
}




#undef ITMAX

#endif
