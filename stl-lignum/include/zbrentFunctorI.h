
#ifndef ZBRENTFUNCTORI_H
#define ZBRENTFUNCTORI_H


#include <fstream>
#include <mathsym.h>

extern ofstream debug_file;

extern ofstream file_out_pl;


namespace Lignum{

// This functor evaluates the delta-values of variable(s) in segments
// that are necessary when when moving one timestep further
// Set all delta-variables to a meaningful value
template <class TS, class BUD>
TreeCompartment<TS,BUD>* EvaluateDeltas<TS,BUD>::operator()
  (TreeCompartment<TS,BUD>* tc)const
{
  
  return tc;
}




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

				double t = (Asu + PI_VALUE * pow(r_h, 2.0) + dAs + Asr);
				double t2 = sqrt(t / PI_VALUE);
				LGMdouble Rnew = sqrt( ( Asu + PI_VALUE * pow(r_h, 2.0) + dAs + Asr) / PI_VALUE);
				LGMdouble Rold = GetValue(*cfsegment, R);

				
				if (Rnew < GetValue(*cfsegment, R))
					Rnew = GetValue(*cfsegment, R);


				LGMdouble growth = Rnew - GetValue(*cfsegment, R);
				if (growth < 0)
					growth = 0.0;
				cfsegment->AdjustAnnualGrowth(growth); 
			
				r_h = sqrt(pow(GetValue(*cfsegment,Rh), 2) + (dAs / PI_VALUE));
				SetValue(*cfsegment, Rh, r_h);

				#ifdef _MSC_VER
				ASSERT(Rnew >= r_h);
				ASSERT(r_h >= 0);
				#endif

				LGMdouble sapwood_area = PI_VALUE * (Rnew*Rnew - r_h*r_h) - dAs;
			
				As = maximum(sapwood_area, 0.0);
		} //CfTreeSegment
	  }
	  else 
	  {
		  Tree<TS,BUD> &tree = dynamic_cast<Tree<TS,BUD>&>(GetTree(*tts));
		  
		  LGMdouble sapwood_area = GetSapwoodArea(*tts);
		  
		  #ifdef _MSC_VER
		  ASSERT(sapwood_area >= 0);
		  #endif
		  
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
			//	LGMdouble la = GetValue(tree,lambda);

			
				LGMdouble Asu = As; //Sapwood area ylhaalta
				LGMdouble r_h = GetValue(*hwsegment, Rh);  // heartwood radius
				LGMdouble dAs = GetValue(tree, ss) * GetSapwoodArea(*hwsegment);
			
				if (file_out_pl.is_open())
				{
					file_out_pl << "Segmentti:" << "       ikä:" << GetValue(*tts, age) << endl;
					file_out_pl << " paikka: " << GetPoint(*hwsegment);
					file_out_pl << ", suunta:" << GetDirection(*hwsegment) << "  ";
					file_out_pl << "Asu:"<< Asu << "  r_h:" << r_h << "  dAs:" << dAs << endl;
				}


				LGMdouble Rold = GetValue(*hwsegment, R);
				
				//Application of the Functional-Structural... equation 20.
				LGMdouble A_ts = max(Asu + dAs + PI_VALUE * pow(r_h, 2.0), PI_VALUE * pow(Rold, 2.0)); 
				
				LGMdouble Rnew = sqrt(A_ts / PI_VALUE);
				

				if (Rnew < GetValue(*hwsegment, R))
					Rnew = GetValue(*hwsegment, R);


				
				

				LGMdouble growth = Rnew - GetValue(*hwsegment, R);
				
			

				hwsegment->AdjustAnnualGrowth(growth); 
				LGMdouble sapwood_area = PI_VALUE * (Rnew*Rnew - r_h*r_h) - dAs;
			

				As = maximum(sapwood_area, 0.0);

				if (file_out_pl.is_open())
				{
					file_out_pl << "Vanha säde:" << Rold << endl;
					file_out_pl << "Uusi säde: " << Rnew << endl;
					file_out_pl << "Alas valuva sapwood " << As << endl;
				}

				
			} // HwTreeSegment
	  }
	  else 
	  {
		  Tree<TS,BUD> &tree = dynamic_cast<Tree<TS,BUD>&>(GetTree(*tts));
		  
		  LGMdouble sapwood_area = GetSapwoodArea(*tts);
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






//This functor sets necessary dry weight deltavariables after diameter growth
template <class TS, class BUD>
TreeCompartment<TS, BUD>* DiameterGrowthBookkeep<TS,BUD>::operator() (TreeCompartment<TS,BUD>* tc)const
{
  
  return tc;
}




//*****Sven	talleta uuteen segmenttiin arvot a ja b
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
			
			//ASSERT(this->rel_lambda > 0);

			LGMdouble lam = this->rel_lambda;
			if (lam <= 0)
			{
				MessageBox(NULL, "lambda == 0", NULL, NULL);
			}

			
			LGMdouble a_f = GetValue(tree, af);
			LGMdouble x_i = GetValue(tree, xi);
			LGMdouble length = GetValue(*cfts, L)*lam;		  //length
			LGMdouble radius = GetValue(*cfts, R)*lam;		  //radius

			//LGMdouble R_h = GetValue(*cfts,Rh) * lam;
			
			LGMdouble R_h = sqrt(x_i) * radius;
			
			LGMdouble foliage_mass = a_f * 2 * PI_VALUE * radius * length;
			LGMdouble R_f = radius + GetValue(tree, nl) * sin(GetValue(tree, na));

		//	R_h = sqrt(pow(R_h, 2) + (dAs / PI_VALUE));
			

			ASSERT(R_f >= radius);
				
			SetValue(*cfts, L, length);
			SetValue(*cfts, R, radius);
			SetValue(*cfts, Wf, foliage_mass);	
			SetValue(*cfts, Rf, R_f);

			#ifdef _MSC_VER
			
			ASSERT(R_h >= 0);
			ASSERT(radius >= R_h);
			
			#endif
			SetValue(*cfts, Rh, R_h);

		}  // CfTreeSegment
		else if (HwTreeSegment<TS,BUD>* hwts = dynamic_cast<HwTreeSegment<TS,BUD>*>(tts))
		{

		}
	  }
	}
	
	
	
  
  return tc;
}




template <class TS, class BUD>
LGMdouble&  CollectDWAfterGrowth<TS,BUD>::operator()(LGMdouble& WSum, TreeCompartment<TS,BUD>* tc)const
{
	if (TreeSegment<TS,BUD>* tts = dynamic_cast<TreeSegment<TS,BUD>*>(tc))
	{
		if (CfTreeSegment<TS,BUD>* cfts = dynamic_cast<CfTreeSegment<TS,BUD>*>(tts))
		{
			Tree<TS,BUD>& tt = dynamic_cast<Tree<TS,BUD>&>(GetTree(*cfts));
			
			if(GetValue(*cfts, age) < R_EPSILON)
			{
				WSum += GetValue(*cfts,Wf) + (GetValue(tt, rho) * PI_VALUE * pow(GetValue(*cfts, R),2))*GetValue(*cfts, L); //GetSapwoodArea(*cfts) + GetValue(*cfts,Wh);
			}
			else
			{
				LGMdouble old_rad = GetValue(*cfts,R);
				LGMdouble new_rad = GetLastAnnualIncrement(*cfts) + old_rad; 

				if (new_rad < old_rad)
					MessageBox(NULL, "newrad<oldrad", NULL, NULL);
	
                LGMdouble w_rho = GetValue(tt,rho);
				WSum += w_rho * (pow(new_rad,2) - pow(old_rad,2)) * PI_VALUE * GetValue(*cfts, L);
			
			}
		}
		else if (HwTreeSegment<TS,BUD>* hwts = dynamic_cast<HwTreeSegment<TS,BUD>*>(tts))
		{
			Tree<TS,BUD>& tt = dynamic_cast<Tree<TS,BUD>&>(GetTree(*hwts));
			
			if(GetValue(*hwts, age) < R_EPSILON)
			{
				WSum += GetValue(*hwts,Wf) + (GetValue(tt, rho) * PI_VALUE * pow(GetValue(*hwts, R),2))*GetValue(*hwts, L); //GetSapwoodArea(*hwts) + GetValue(*hwts,Wh);
			}
			else
			{
				LGMdouble old_rad = GetValue(*hwts,R);
				LGMdouble new_rad = GetLastAnnualIncrement(*hwts) + old_rad; 

				if (new_rad < old_rad)
					MessageBox(NULL, "newrad<oldrad", NULL, NULL);
	
                LGMdouble w_rho = GetValue(tt,rho);
				WSum += w_rho * (pow(new_rad,2) - pow(old_rad,2)) * PI_VALUE * GetValue(*hwts, L);
			}
		}
	} 
	
	

  return WSum;
}

// Bookkeep after distributing the growth
// NOTE: new segment updated in adjustSegmentSizeLambda
template <class TS, class BUD>
TreeCompartment<TS,BUD>* BookkeepAfterZbrent<TS,BUD>::operator ()(TreeCompartment<TS,BUD>* tc)const
{
 

  return tc;      
}



}

#endif