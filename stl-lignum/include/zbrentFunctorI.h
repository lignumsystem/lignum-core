#ifndef ZBRENTFUNCTORI_H
#define ZBRENTFUNCTORI_H


#include <fstream>
#include <mathsym.h>



//double diam_hana = 1.0;  //!!!!!!!!!!!!!!!!


namespace Lignum{





template <class TS, class BUD>
LGMdouble& AdjustDiameterCfGrowth<TS,BUD>::operator()(LGMdouble& As, TreeCompartment<TS, BUD>* tc)const
{
	if (TreeSegment<TS,BUD>* tts = dynamic_cast<TreeSegment<TS,BUD>*>(tc))
	{
		if(GetValue(*tts, age) > R_EPSILON)
		{
			if(CfTreeSegment<TS,BUD> *cfsegment = dynamic_cast<CfTreeSegment<TS,BUD>*>(tts))
			{	
				Tree<TS,BUD> &tree = dynamic_cast<Tree<TS,BUD>&>(GetTree(*tts));
				LGMdouble la = GetValue(tree,lambda);

			
				LGMdouble Asu = As; //Sapwood area ylhaalta
				LGMdouble r_h = GetValue(*cfsegment, Rh);  // heartwood radius
				LGMdouble dAs = GetValue(tree, ss) * PI_VALUE * (pow(GetValue(*cfsegment, R), 2) - pow(r_h, 2));
			
				//From equation 14 in Ann Bot 1996
				LGMdouble Asr = ( 1.0 - GetValue(tree, xi)) * GetValue(*cfsegment, Wf) / (2.0 * GetValue(tree, af) * GetValue(tree, lr)); 

				LGMdouble Rnew = sqrt( ( Asu + PI_VALUE * pow(r_h, 2.0) + dAs + Asr) / PI_VALUE);
				LGMdouble Rold = GetValue(*cfsegment, R);

				
				if (Rnew < GetValue(*cfsegment, R))
					Rnew = GetValue(*cfsegment, R);


				LGMdouble growth = Rnew - GetValue(*cfsegment, R);
				cfsegment->AdjustAnnualGrowth(growth); 
			

				LGMdouble sapwood_area = PI_VALUE * (Rnew*Rnew - r_h*r_h) - dAs;
				sapwood_area = sapwood_area;

				As = maximum(sapwood_area, 0.0);
		} //CfTreeSegment
	  }
	  else 
	  {
		  Tree<TS,BUD> &tree = dynamic_cast<Tree<TS,BUD>&>(GetTree(*tts));
		  
		  LGMdouble sapwood_area = GetSapwoodArea(*tts);
		  sapwood_area = sapwood_area;   
		  As = sapwood_area;
		   
	  }
	}
	return As;
}




template <class TS, class BUD>
LGMdouble& AdjustDiameterHwGrowth<TS,BUD>::operator()(LGMdouble& As, TreeCompartment<TS, BUD>* tc)const
{
	if (TreeSegment<TS,BUD>* tts = dynamic_cast<TreeSegment<TS,BUD>*>(tc))
	{
		if(GetValue(*tts, age) > R_EPSILON)
		{
			if(HwTreeSegment<TS,BUD> *hwsegment = dynamic_cast<HwTreeSegment<TS,BUD>*>(tts))
			{
				Tree<TS,BUD> &tree = dynamic_cast<Tree<TS,BUD>&>(GetTree(*tts));
				LGMdouble la = GetValue(tree,lambda);

			
				LGMdouble Asu = As; //Sapwood area ylhaalta
				LGMdouble r_h = GetValue(*hwsegment, Rh);  // heartwood radius
				LGMdouble dAs = GetValue(tree, ss) * PI_VALUE * (pow(GetValue(*hwsegment, R), 2) - pow(r_h, 2));
			
				//From equation 14 in Ann Bot 1996
				LGMdouble Asr = ( 1.0 - GetValue(tree, xi)) * GetValue(*hwsegment, Wf) / (2.0 * GetValue(tree, af) * GetValue(tree, lr)); 

				LGMdouble Rnew = sqrt( ( Asu + PI_VALUE * pow(r_h, 2.0) + dAs + Asr) / PI_VALUE);
				LGMdouble Rold = GetValue(*hwsegment, R);

				if (Rnew < GetValue(*hwsegment, R))
					Rnew = GetValue(*hwsegment, R);


				LGMdouble growth = Rnew - GetValue(*hwsegment, R);	
				hwsegment->AdjustAnnualGrowth(growth); 
				LGMdouble sapwood_area = PI_VALUE * (Rnew*Rnew - r_h*r_h) - dAs;
				sapwood_area = sapwood_area;

				As = maximum(sapwood_area, 0.0);
			} // HwTreeSegment
	  }
	  else 
	  {
		  Tree<TS,BUD> &tree = dynamic_cast<Tree<TS,BUD>&>(GetTree(*tts));
		  
		  LGMdouble sapwood_area = GetSapwoodArea(*tts);
		  sapwood_area = sapwood_area;
		  As = sapwood_area;
		   
	  }
	}
	return As;
}


// DiameterGrowth 
template <class TS, class BUD>
LGMdouble& SetNewRing<TS,BUD>::operator()(LGMdouble& As, TreeCompartment<TS, BUD>* tc)const
{
	if (TreeSegment<TS,BUD>* tts = dynamic_cast<TreeSegment<TS,BUD>*>(tc))
	{
	   if(GetValue(*tts, age) > R_EPSILON)
	   {	
			tts->SetAnnualGrowth(-1); 
	   }
	}  
  return As;
}










// This functor sets the dimensions of the new segments (age = 0) as a function
// of lambda (radius = lambda). It sets also the other necessary variables, leaf
// size, masses etc)
template <class TS, class BUD>
TreeCompartment<TS,BUD>* adjustSegmentSizeLambda<TS,BUD>::operator()
  (TreeCompartment<TS,BUD>* tc)const
{
	if (TreeSegment<TS,BUD>* tts = dynamic_cast<TreeSegment<TS,BUD>*>(tc))
	{
	  if(GetValue(*tts, age) < R_EPSILON) 
	  {

		if (CfTreeSegment<TS,BUD>* cfts = dynamic_cast<CfTreeSegment<TS,BUD>*>(tts))
		{
			Tree<TS,BUD>& tree = dynamic_cast<Tree<TS,BUD>&>(GetTree(*cfts));
			
			

			LGMdouble lam = this->rel_lambda;
			if (lam <= 0)
			{
				
				lam = 0.01;
			
			}

			
			LGMdouble a_f = GetValue(tree, af);
			LGMdouble x_i = GetValue(tree, xi);
			LGMdouble length = GetValue(*cfts, L)*lam;		  //length
			LGMdouble radius = GetValue(*cfts, R)*lam;		  //radius

			
			LGMdouble foliage_mass = a_f * 2 * PI_VALUE * radius * length;
			LGMdouble R_h = sqrt(x_i) * radius;
			LGMdouble R_f = radius + GetValue(tree, nl) * sin(GetValue(tree, na));


			assert(R_f > radius);
				
			SetValue(*cfts, L, length);
			SetValue(*cfts, R, radius);
			SetValue(*cfts, Wf, foliage_mass);	
			SetValue(*cfts, Rf, R_f);
			SetValue(*cfts, Rh, R_h);
		}  // CfTreeSegment
		
	  }
	}
	
	
	
  
  return tc;
}




template <class TS, class BUD>
LGMdouble&  CollectCfDWAfterGrowth<TS,BUD>::operator()(LGMdouble& WSum, TreeCompartment<TS,BUD>* tc)const
{
  
	if (TreeSegment<TS,BUD>* tts = dynamic_cast<TreeSegment<TS,BUD>*>(tc))
	{
	  
	  if (CfTreeSegment<TS,BUD>* cfts = dynamic_cast<CfTreeSegment<TS,BUD>*>(tc))
		{
		  
		  Tree<TS,BUD>& tt = dynamic_cast<Tree<TS,BUD>&>(GetTree(*cfts));
			
			if(GetValue(*cfts, age) < R_EPSILON)
			{
				WSum += GetValue(*cfts,Wf) + (GetValue(tt, rho) * PI_VALUE * 
							      pow(GetValue(*cfts, R),2))*GetValue(*cfts, L); 
				//GetSapwoodArea(*cfts) + GetValue(*cfts,Wh);
			}
			else
			{
				LGMdouble old_rad = GetValue(*cfts,R);
				LGMdouble new_rad = GetLastAnnualIncrement(*cfts) + old_rad; 

				LGMdouble w_rho = GetValue(tt,rho);
				WSum += w_rho * (pow(new_rad,2) - pow(old_rad,2)) * PI_VALUE * GetValue(*cfts, L);
			
			}
		  
		}
	
		
	} 
  
  return WSum;
}


template <class TS, class BUD>
LGMdouble&  CollectHwDWAfterGrowth<TS,BUD>::operator()(LGMdouble& WSum, TreeCompartment<TS,BUD>* tc)const
{
	if (TreeSegment<TS,BUD>* tts = dynamic_cast<TreeSegment<TS,BUD>*>(tc))
	{
		 if (HwTreeSegment<TS,BUD>* hwts = dynamic_cast<HwTreeSegment<TS,BUD>*>(tts))
		{
			Tree<TS,BUD>& tt = dynamic_cast<Tree<TS,BUD>&>(GetTree(*hwts));
			
			if(GetValue(*hwts, age) < R_EPSILON)
			{
				WSum += GetValue(*hwts,Wf) + (GetValue(tt, rho) * PI_VALUE 
							      * pow(GetValue(*hwts, R),2))*GetValue(*hwts, L);
			}
			else
			{
				LGMdouble old_rad = GetValue(*hwts,R);
				LGMdouble new_rad = GetLastAnnualIncrement(*hwts) + old_rad; 

				
	
				LGMdouble w_rho = GetValue(tt,rho);
				WSum += w_rho * (pow(new_rad,2) - pow(old_rad,2)) * PI_VALUE * GetValue(*hwts, L);
			}
		}
	} 
  return WSum;
}





}

#endif
