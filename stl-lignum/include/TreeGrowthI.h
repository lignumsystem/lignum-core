#ifndef TREEGROWTHI_H
#define TREEGROWTHI_H


#include "TreeCompartment.h"
#include "zbrentFunctor.h"

extern float minLimitForSecBud[];

extern ofstream file_out_pl;
extern ParametricCurve nol_fun;
extern LGMdouble wSum_Lambda0; // = 0.0;


template <class TS, class BUD, class F>
bool Growth(Tree<TS,BUD>& tree, F& f) 
{	
	//Structural growth possible only if photosynthesis > respiration

	LGMdouble photo = GetValue(tree, LGAP);
	LGMdouble respi = GetValue(tree, M);
	
	LGMdouble P_avail = photo - respi;

	if(!(P_avail > 0.0))
	{
		MessageBox(NULL, "  photosynthesis =< respiration " , NULL, NULL);
		return false;
	}
	
	
	f(tree);
	return true;
}




//This constructor for the case when functions for number of buds
//(bud_fun) and degree of interaction (doi_fun) are read from file

template<class F, class TS, class BUD>
WrapGrowth<F,TS,BUD>::WrapGrowth(std::string sbud, std::string sdoi):bud_fun(sbud),doi_fun(sdoi)
{
    growth_functor.setBud_fun(bud_fun);
    growth_functor.setDoi_fun(doi_fun);
}

template<class F, class TS, class BUD>
WrapGrowth<F,TS,BUD>::WrapGrowth(ParametricCurve sbud, ParametricCurve sdoi)
{
    bud_fun = sbud;
	doi_fun = sdoi;
	growth_functor.setBud_fun(bud_fun);
    growth_functor.setDoi_fun(doi_fun);
}


template<class F, class TS, class BUD>
WrapGrowth<F,TS,BUD>::WrapGrowth()
{
}


template <class F, class TS, class BUD>
bool WrapGrowth<F,TS,BUD>::operator()(Tree<TS, BUD>& tree)
{
  bool result;
  result = growth_functor(tree);


  
  return result;	
}


template <class TS, class BUD>
GrowthOfPineTree<TS,BUD>::GrowthOfPineTree()
{
	
}


//This functor GrowthOfPineTree evaluates growth of tree consisting of
//CfTreeSegments
template <class TS, class BUD>
bool GrowthOfPineTree<TS,BUD>::operator()(Tree<TS,BUD>& tree)
{
  
	// Asetetaan uusi annual_ring
	LGMdouble AsIni = 0.0;
	SetNewRing<TS,BUD> NewRing;
	AccumulateDown(tree, AsIni, NewRing);

	// Lasketaan arvo uudelle sateelle. Uusia oksia ei viela lisatty
	AsIni = 0.0;
	AdjustDiameterCfGrowth<TS,BUD> adDiamGrowth; 
	AsIni = AccumulateDown(tree, AsIni, adDiamGrowth);
  
	//Lasketaan kasvuenergia kun lambda = 0
	LGMdouble identity = 0.0;
	CollectDWAfterGrowth<TS,BUD> collectDW;
	wSum_Lambda0 = Accumulate(tree,  identity, collectDW);


	Axis<TS,BUD>& main_stem = GetAxis(tree);


    TreeSegment<TS, BUD> *tmp = NULL;
	StructuralPineGrowth(main_stem, bud_fun, tmp);	

	return true;
}




//This functor GrowthOfHwTree evaluates growth of tree consisting of
//CfTreeSegments
template <class TS, class BUD>
bool GrowthOfHwTree<TS,BUD>::operator()(Tree<TS,BUD>& tree)
{
	// Asetetaan uusi annual_ring
	LGMdouble AsIni = 0.0;
	SetNewRing<TS,BUD> NewRing;
	AccumulateDown(tree, AsIni, NewRing);

	// Lasketaan arvo uudelle sateelle. Uusia oksia ei viela lisatty
	AsIni = 0.0;
	AdjustDiameterHwGrowth<TS,BUD> adDiamGrowth; 
	AsIni = AccumulateDown(tree, AsIni, adDiamGrowth);
  
	//Lasketaan kasvuenergia kun lambda = 0
	LGMdouble identity = 0.0;
	CollectDWAfterGrowth<TS,BUD> collectDW;
	wSum_Lambda0 = Accumulate(tree,  identity, collectDW);

	
	Axis<TS,BUD>& main_stem = GetAxis(tree);
	Firmament& f = GetFirmament(tree);
	LGMdouble B = f.diffuseBallSensor();

	MotherInfo init;
	init.vi = 1.0;
	init.Qin = 0.0;
	init.B = B;

	AddSugarMapleSegments<TS,BUD> functor;
	functor.bud_fun = bud_fun;
	PropagateUp(tree, init, functor);

	return true;
}


//This functor GrowthOfPineTree evaluates growth of tree consisting of
//CfTreeSegments
template <class TS, class BUD>
bool GrowthOfWhiteBirch<TS,BUD>::operator()(Tree<TS,BUD>& tree)
{

	//Asetetaan uusi annual_ring
	LGMdouble AsIni = 0.0;
	SetNewRing<TS,BUD> NewRing;
	AccumulateDown(tree, AsIni, NewRing);

	//Lasketaan arvo uudelle sateelle. Uusia oksia ei viela lisatty
	AsIni = 0.0;
	AdjustDiameterHwGrowth<TS,BUD> adDiamGrowth; 	
	AsIni = AccumulateDown(tree, AsIni, adDiamGrowth);

	//Lasketaan kasvuenergia kun lambda = 0
	LGMdouble identity = 0.0;
	CollectDWAfterGrowth<TS,BUD> collectDW;
	wSum_Lambda0 = Accumulate(tree,  identity, collectDW);

/*
	file_out_pl.open("paksuusdebug.txt");
	file_out_pl << "edellisen kierroksen lambda " << GetValue(tree, lambda) << endl;
	file_out_pl << "KULUNUT KASVUENERGIA " << wSum_Lambda0 << endl;
	*/
	LGMdouble photo = GetValue(tree, LGAP);
	LGMdouble respi = GetValue(tree, M);
	LGMdouble P_avail = photo - respi;

		
	Axis<TS,BUD>& main_stem = GetAxis(tree);

    
	Firmament& f = GetFirmament(tree);
	LGMdouble B = f.diffuseBallSensor();

	MotherInfo init;
	init.vi = 1.0;
	init.Qin = 0.0;
	init.B = B;

	AddWhiteBirchSegments<TS,BUD> functor;
	PropagateUp(tree, init, functor);

	/*
	file_out_pl << "Photos " << photo << endl;
	file_out_pl << "respi  " << respi << endl;
	file_out_pl << "Energiaa kasvuun " << (P_avail - wSum_Lambda0) << endl;
		
	file_out_pl.close();
*/
	//WinExec("notepad paksuusdebug.txt", SW_SHOW);
	//Sleep(200);

	//WinExec("del paksuusdebug.txt", SW_SHOW);

	return true;
}




template <class TS, class BUD>
void StructuralPineGrowth(Axis<TS,BUD> &ax, const ParametricCurve& bud_fun, TreeSegment<TS,BUD> *treesegment)
{
	Bud<TS,BUD>* bud = dynamic_cast<Bud<TS,BUD> *>(GetTerminatingBud(ax));
	Tree<TS,BUD>& tree = dynamic_cast<Tree<TS,BUD>&>(GetTree(*bud));

	int index=1;
	BranchingPoint<TS,BUD>* bp;
	Axis<TS,BUD> *new_axes[20];

	TreeSegment<TS,BUD> *tmp = GetLastTreeSegment(ax);
	if (tmp != NULL)
		treesegment = tmp;


	//the number of new buds
	int number_of_new_buds = 0;

	//secondarybuds?
	if (treesegment)
	{
		LGMdouble tswf = 0.0;
		if (CfTreeSegment<TS,BUD>* cfts = dynamic_cast<CfTreeSegment<TS,BUD>*>(treesegment))
		{
			tswf = GetValue(*cfts, LGAWf);
		}
		//MessageBox(NULL, "grammoja "+GetStr(tswf*1000, 3), NULL, NULL);
		

		number_of_new_buds = (int)bud_fun(tswf); 
		Point point = GetPoint(*bud);
		PositionVector posvec = GetDirection(*bud);


		LGMdouble lda = GetValue(tree, Treelambda);

		ASSERT(lda>0);

		Firmament& f = GetFirmament(tree);
		LGMdouble B = f.diffuseBallSensor();
		LGMdouble I = 0.0;

		if (CfTreeSegment<TS,BUD>* cfts = dynamic_cast<CfTreeSegment<TS,BUD>*>(treesegment))
		{
			I = GetValue(*cfts, LGAQin);
		}

		LGMdouble i_p = I / B;
		
		if(i_p>0);
		{
			LGMdouble omeg = GetValue(*bud, LGAomega);

			LGMdouble _q = GetValue(tree, q);
			
			Tree<TS,BUD> &tree = GetTree(*treesegment);
			ParametricCurve doi_fun = tree.tf.ip;
			
			if (i_p < 0.1)
				i_p = 0.1;

			LGMdouble f_l = doi_fun(ip); 
				//**f_l = 1.1* i_p - 0.1;
			LGMdouble f_w = 1 - (omeg-1) * _q;		//***Sven   korvaa lyhenemistekijällä

			if (f_w < 0)
				f_w = 0.0;

			if (f_l < 0.01)
				f_l = 0.01;

			LGMdouble l_r = GetValue(tree, LGPlr);
			LGMdouble a_f = GetValue(tree, LGPaf);
			LGMdouble x_i = GetValue(tree, LGPxi);

			LGMdouble length = lda * f_w * f_l;		  //length
			LGMdouble radius = length / l_r;		  //radius
			LGMdouble foliage_mass =  a_f * 2 * PI_VALUE * radius * length;
			LGMdouble R_h = sqrt(x_i) * radius;
			
			#ifdef _MSC_VER
			ASSERT(R_h >= 0);
			ASSERT(R_h <= radius);
			#endif

			LGMdouble R_f = radius + GetValue(tree, nl) * sin(GetValue(tree, na));

			TS* ts = new TS(point, posvec, 0, length, radius, 0, &tree);

			SetValue(*ts, LGAomega, 1);
			SetValue(*ts, LGAage, 0);
			SetValue(*ts, LGAWf, foliage_mass);	
			SetValue(*ts, LGARf, R_f);
			SetValue(*ts, LGARh, R_h);
			

			ASSERT(GetSapwoodArea(*ts) >= 0);

			InsertTreeCompartmentSecondLast(ax, ts);
			
			Point p = point + posvec;
			bp = new BranchingPoint<TS,BUD>(p, posvec, &tree);	
			
			PositionVector buddir[10];
			if (GetDirection(*bud).getZ() != 1.0)
				buddir[1] = Cross(GetDirection(*bud), PositionVector(0,0,1));	
			else buddir[1] = Cross(GetDirection(*bud), PositionVector(0,1,0));


			PositionVector direction = GetDirection(*bud);
			PositionVector up(0,0,1);
			PositionVector v1 = Cross(up, direction);

			if (direction.getZ() == 1)
			{
				v1 = PositionVector(1,0,0);
			}
		
			v1.normalize();
			direction.normalize();
			PositionVector v2 = v1 + direction;
			v2.normalize();

			LGMdouble delta_angle = 2 * PI_VALUE / number_of_new_buds;

		

			bud->move(posvec, length);		
			while(number_of_new_buds > 1)		//***Sven	budien suunta
			{
				new_axes[index] = new Axis<TS,BUD>();

				v2.rotate(Point(0,0,0), direction, delta_angle);
				Bud<TS,BUD> *new_bud = new Bud<TS,BUD>(GetPoint(*bud), v2, GetValue(*bud, LGAomega)+1, &tree);
				SetValue(*new_bud, LGAage, 0);
				SetValue(*new_bud, state, ALIVE);

				InsertTreeCompartment(*new_axes[index], new_bud);
				index++;
				number_of_new_buds--;
			}

			
			InsertTreeCompartmentSecondLast(ax, bp);
		}
	}

	std::list<TreeCompartment<TS, BUD>*>& ls = GetTreeCompartmentList(ax);
	std::list<TreeCompartment<TS, BUD>*>::iterator I = ls.begin();
	while(I != ls.end())
	{
		if (TreeSegment<TS, BUD>* myts = dynamic_cast<TreeSegment<TS, BUD>*>(*I))
		{
			treesegment = myts;
			

		}
		if (BranchingPoint<TS, BUD>* mybp = dynamic_cast<BranchingPoint<TS, BUD>*>(*I))
		{ 
			std::list<Axis<TS, BUD>*>& axis_ls = GetAxisList(*mybp);  	  
			std::list<Axis<TS, BUD>*>::iterator II = axis_ls.begin();
			
			while(II != axis_ls.end())
			{
				Axis<TS,BUD> *axis = *II;	
				StructuralPineGrowth(*axis, bud_fun, treesegment); 
				II++;	
			}			
		}
		I++;
	}
	while(index>1)
	{
		index--;
		InsertAxis(*bp, new_axes[index]);
	}
}



template <class TS, class BUD>
TreeCompartment<TS,BUD>* FoliageLossOfPineTree<TS,BUD>::operator()(TreeCompartment<TS,BUD>* tc)const
{
	
	if (TreeSegment<TS,BUD>* tts = dynamic_cast<TreeSegment<TS,BUD>*>(tc))
	{ 
		if (CfTreeSegment<TS,BUD>* cfts = dynamic_cast<CfTreeSegment<TS,BUD>*>(tts))
		{
			

			LGMdouble foliage_mass = GetValue(*cfts, LGAWf); 
			int ag = GetValue(*cfts, LGAage);
			if (foliage_mass > 0 && ag>0)
			{
				LGMdouble pre = 1.0;
				LGMdouble next = 1.0;
				pre = fol_mor(ag-1);
				next = fol_mor(ag);

				foliage_mass = foliage_mass * next/pre;
				SetValue(*cfts, LGAWf, foliage_mass); 
			}
		}
	}
	return tc;
}







template <class TS, class BUD>
void StructuralHwTreeGrowth(Axis<TS,BUD> &ax, const ParametricCurve& bud_fun)
{
	
}




/// removes all TreeComparments of age 0)
template <class TS, class BUD>
Axis<TS,BUD>& RemoveNewComparments(Axis<TS,BUD> &axis)
{
	Bud<TS,BUD>* bud = dynamic_cast<Bud<TS,BUD> *>(GetTerminatingBud(axis));
	bool move_bud =  true;

	std::list<TreeCompartment<TS, BUD>*>& ls = GetTreeCompartmentList(axis);
	std::list<TreeCompartment<TS, BUD>*>::iterator I = ls.begin();

	while(I != ls.end())
	{
		 
		TreeCompartment<TS,BUD> *tc = dynamic_cast<TreeCompartment<TS,BUD>*>(*I);
		
		int age_ = GetValue(*tc, LGAage);
		if (age_ == 0)
		{
			//Moving terminating bud to the first removed treesegment
			if (HwTreeSegment<TS, BUD>* myts = dynamic_cast<HwTreeSegment<TS, BUD>*>(*I))
			{
				if (move_bud)
				{
					SetPoint(*bud, GetPoint(*myts));
					move_bud = false;
				}
			}
			ls.remove(tc);
			//delete tc;
			ls = GetTreeCompartmentList(axis);
			I = ls.begin();
		}
		
		else if(BranchingPoint<TS,BUD>* bp = dynamic_cast<BranchingPoint<TS,BUD>*>(*I)) 
		{
			std::list<Axis<TS, BUD>*>& axis_ls = GetAxisList(*bp);  	  
			std::list<Axis<TS, BUD>*>::iterator II = axis_ls.begin();
	  
			while(II != axis_ls.end())
			{	      
				Axis<TS,BUD> *axis = *II;		     
				RemoveNewComparments(*axis);	      
				II++;	
			}
			I++;
		}
		else 
			I++;
		
	}
	return axis;
}




template <class TS,class BUD>
MotherInfo& AddSugarMapleSegments<TS,BUD>::operator()(MotherInfo& mi, TreeCompartment<TS,BUD>* tc)const
{
  LGMdouble motherQin = mi.Qin;
  LGMdouble vigour = mi.vi;

  Axis<TS,BUD>* axis = NULL;
  LGMdouble q_in = 0.0;
  
  if (axis = dynamic_cast<Axis<TS,BUD>*>(tc))
  {
		if (GetValue(*axis, LGAage) == 0)
			return mi;  //mother_in
	  
		q_in = GetSumValue(*axis, LGAQin, 1);
		if (q_in == 0)
			q_in = motherQin;
		else 
			motherQin = q_in;
		Bud<TS,BUD>* bud = dynamic_cast<Bud<TS,BUD> *>(GetTerminatingBud(*axis));

		
		if (GetValue(*bud, state) != ALIVE || GetValue(*bud, LGAage) == 0)
		{
			mi.Qin = motherQin;
			mi.vi = vigour;
			return mi;
		}
		
		BranchingPoint<TS,BUD>* bp;
	

		//the number of new buds
		int number_of_new_buds = 0;
	
		number_of_new_buds = 3; //(int)bud_fun(tswf); 
		Point point = GetPoint(*bud);
		PositionVector posvec = GetDirection(*bud);

		Tree<TS,BUD> &tree = GetTree(*bud);
		LGMdouble lda = GetValue(tree, Treelambda);

		//ASSERT(lda>0);

		Firmament& f = GetFirmament(tree);
		LGMdouble B = f.diffuseBallSensor();
		LGMdouble I = q_in;
	
		LGMdouble i_p = I / B;
		
		ASSERT(i_p>0);

		LGMdouble omeg = GetValue(*bud, LGAomega);

		LGMdouble q = 0.1;
		LGMdouble f_l = 1.1* i_p - 0.1;
		LGMdouble f_w = 1 - (omeg-1) * q;

		if (f_w < 0)
			f_w = 0.0;

		LGMdouble l_r = GetValue(tree, LGPlr);
		LGMdouble a_f = GetValue(tree, LGPaf);
		LGMdouble x_i = GetValue(tree, LGPxi);

		//LGMdouble Irel_b = motherQin / mi.B;
		
		//  Uusi pituus
		ParametricCurve apidom = tree.tf.ip;
		ParametricCurve vigfun = tree.tf.vi;
		ParametricCurve lenfun = tree.tf.al;

		LGMdouble Irel_b = motherQin / mi.B / 100000;
		LGMdouble abidom_ = GetValue(*bud, api);

		
		LGMdouble length = lda * abidom_ * vigfun(vigour) * Irel_b; 
		length = lenfun(length);

		
		if (length == 0)
		{
			mi.Qin = motherQin;
			mi.vi = vigour;
			return mi;
		}
		/// Loppu

		//vanha :LGMdouble length = lda * vigour * Irel_b* 0.8; //f_w * f_l;		  //length
		bud->move(posvec, length);
		int number_of_segments = tree.tf.nb(length);
		length = length / number_of_segments;


		//Segmenttien pituuksien laskeminen
		LGMdouble random_effect = GetValue(tree, rld);
		vector<LGMdouble> odds;
		for(int i=0; i<number_of_segments; i++)
			odds.push_back(1.0);
		if (random_effect<100 && random_effect>0.1)
		{
			for (int i=0; i<number_of_segments; i++)
			{
				int tmp = random_effect*2+1;
				LGMdouble random_value = rand()%tmp; // 0-random_effect
				random_value = random_value / 100.0;// 0.01 - 0.4
				odds[i] = (1.0 - random_effect/100.0) + random_value;
			}

			LGMdouble sum = 0.0;
			for (i=0; i<number_of_segments; i++)
				sum = sum + odds[i];
			sum = sum / number_of_segments;
			for (i=0; i<number_of_segments; i++)
				odds[i] = odds[i] / sum;
		}
	
		PositionVector direction = GetDirection(*bud);
		PositionVector up(0,0,1);
		PositionVector v1 = Cross(up, direction);
		if (direction.getZ() == 1)
		{
			v1 = PositionVector(1,0,0);
		}
		v1.normalize();
		direction.normalize();
		PositionVector v2 = v1 + direction;
		v2.normalize();

	if (direction.getZ() == 1)
	{
		v2.rotate(Point(0,0,0), direction, 2*PI_VALUE*(rand()%360)/360);
	}
	int tot_segments = number_of_segments; 

	while(number_of_segments > 0)
	{
		v2.rotate(Point(0,0,0), direction, PI_VALUE/2);

		LGMdouble dof_p = 0.5;
		LGMdouble sf = 0.0;
		LGMdouble v = 0.06;
		Firmament& f = GetFirmament(tree);
		int number_of_regions = f.numberOfRegions();
		Point end_point = point + Point(0,0, length);
		PositionVector pet_s(end_point);
		PositionVector pet_e1(end_point+Point(0, 0.1, 0.05));
		PositionVector pet_e2(end_point+Point(0, -0.1, 0.05));

		LGMdouble Ellipse_a = sqrt(GetValue(tree, al) / (1.1*PI_VALUE));  ///**************'  
		LGMdouble Ellipse_b = Ellipse_a / 1.1;		
		PositionVector normal(rand()%100, rand()%100, 200);
		normal.normalize();

		BroadLeaf<cxxadt::Ellipse> *leaf1 = new BroadLeaf<cxxadt::Ellipse>(sf, v, dof_p, number_of_regions, Petiole((Point)pet_s,(Point)pet_e1), 
											normal, Ellipse(Ellipse_a, Ellipse_b));
		BroadLeaf<cxxadt::Ellipse> *leaf2 = new BroadLeaf<cxxadt::Ellipse>(sf, v, dof_p, number_of_regions, Petiole((Point)pet_s,(Point)pet_e2), 
											normal, Ellipse(Ellipse_a, Ellipse_b));
		SetValue(*leaf1, LGAsf, 28);
		SetValue(*leaf2, LGAsf, 28);	
	

		LGMdouble A_f = GetValue(*leaf1, A) + GetValue(*leaf2, A);
		LGMdouble SLA_c = GetValue(tree, LGPsf);
		LGMdouble Y_c = GetValue(tree, LGPyc);
		LGMdouble A_sf = A_f / (SLA_c*Y_c);
		LGMdouble x_i = GetValue(tree, LGPxi);
		LGMdouble tot_A = A_sf / (1-x_i);
		 
		LGMdouble rad = sqrt(tot_A / PI_VALUE);
		LGMdouble segment_length = length * odds[number_of_segments-1];


		TS* ts = new TS(point, posvec, 0, segment_length, rad, 0, &tree);

		SetValue(*ts, LGAomega, 1);
		SetValue(*ts, LGAage, 0);
		InsertLeaf(*ts, leaf1);
		InsertLeaf(*ts, leaf2);
		InsertTreeCompartmentSecondLast(*axis, ts);	

		Point p = point + posvec * segment_length;

		bp = new BranchingPoint<TS,BUD>(p, posvec, &tree);
		SetValue(*bp, LGAage, 0);

		Axis<TS,BUD> *new_axis1 = new Axis<TS,BUD>();
		Axis<TS,BUD> *new_axis2 = new Axis<TS,BUD>();


			
		Bud<TS,BUD> *new_bud1 = new Bud<TS,BUD>(GetPoint(*bp), v2, GetValue(*bud, LGAomega)+1, &tree);
		v2.rotate(Point(0,0,0), direction, PI_VALUE);
		Bud<TS,BUD> *new_bud2 = new Bud<TS,BUD>(GetPoint(*bp), v2, GetValue(*bud, LGAomega)+1, &tree);
		SetValue(*new_bud1, LGAage, 0);
		SetValue(*new_bud2, LGAage, 0);
		
		LGMdouble rel_place = ((double)(1+tot_segments - number_of_segments))/tot_segments;
		LGMdouble ad = apidom(rel_place);
		SetValue(*new_bud1, api, ad);
		SetValue(*new_bud2, api, ad);
		
		if (number_of_segments < 6) // || rand()%3 == 0)
		{
			SetValue(*new_bud1, state, ALIVE);
		//	SetValue(*new_bud2, state, ALIVE);
		}
		else
		
		{
			SetValue(*new_bud1, state, DORMANT);
		//	SetValue(*new_bud2, state, DORMANT);
		}

		if (number_of_segments < 6) // || rand()%3 == 0)
		{
		
			SetValue(*new_bud2, state, ALIVE);
		}
		else	
		{	
			SetValue(*new_bud2, state, DORMANT);
		}


		InsertTreeCompartment(*new_axis1, new_bud1);
		InsertTreeCompartment(*new_axis2, new_bud2);

		InsertAxis(*bp, new_axis1);
		InsertAxis(*bp, new_axis2);
			
		InsertTreeCompartmentSecondLast(*axis, bp);


		point = GetEndPoint(*ts);
		//v2.rotate(Point(0,0,0), direction, PI_VALUE/2);

		number_of_segments--;
	}
  }
  mi.Qin = motherQin;
  mi.vi = vigour;
  return mi;
}

template <class TS, class BUD>
LGMdouble& CollectNewCfFoliageMass<TS,BUD>::operator()(LGMdouble &sum, TreeCompartment<TS,BUD>* tc)const
{
	if(CfTreeSegment<TS,BUD> *cfsegment = dynamic_cast<CfTreeSegment<TS,BUD>*>(tc))
	{
		if (GetValue(*cfsegment, LGAage) == 0)
			sum += GetValue(*cfsegment, LGAWf);
	}

	return sum;
}



template <class TS, class BUD>
LGMdouble& CollectNewHwFoliageMass<TS,BUD>::operator()(LGMdouble &sum, TreeCompartment<TS,BUD>* tc)const
{
	if(HwTreeSegment<TS,BUD> *hwsegment = dynamic_cast<HwTreeSegment<TS,BUD>*>(tc))
	{
		if (GetValue(*hwsegment, LGAage) == 0)
			sum += GetValue(*hwsegment, LGAWf);
	}

	return sum;
}



#endif

 
