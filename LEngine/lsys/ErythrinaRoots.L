/********************************************************
	 *	Generation de systeme racinaire de Erythrina    *
	 *	modele fracroot, Ozier-Lafontaine et al, 2000	*
	 *	C02                                             *
	 ********************************************************/

#include <math.h>
#include <pair>
#include <lengine.h>
#include <Uniform.h>

inline double Da(double Db)
{
   return sqrt((Q/ALPHA)*pow(Db,2.0));
}

inline double Dr(double Db, double nbr)
{
   return sqrt((((1.0-Q)/nbr)/ALPHA)*pow(Db,2.0));
}

inline double Long(double D)
{
   return (D >0.035) ? (6.961*D) : 0.1;
}

inline pair<double,double> RandomRollAndPitch(double d,int RAMorAXE)
{
  pair<double,double> p(1.0,1.0);
  return p;
}

open Erythrina;

#include <lsys.h>


const int STEPS=30;
const double ALPHA=0.99;
const double Q=0.72;
const double DMIN=0.1; //minimum diameter

const int RAM=0;
const int AXE=1;

Uniform u;
int seed = 1;



module B(double,double);
module F(double);
module Pitch(double);
module Roll(double);

derivation length: STEPS;

Start: 
{ 
   seed = 1;
   produce B(0.25,0.50);
}



B(d,l):
{
  if (d > DMIN){ 
   double u1 = u(seed);
   pair<double,double> p1 = RandomRollAndPitch(d,AXE);
   pair<double,double> p2 = RandomRollAndPitch(d,RAM);
   if (u1 =< 0.9){ 
     double dr1 = Dr(d,1.0);
     double longdr1 = Long(Dr(d,1.0));
     double da1 = Da(d,1.0);
     double longdad = Long(Da(d));
     produce F(l) SB()  Roll(p1.first) Pitch(p1.second) B(dr1,longdr1) EB() 
             Roll(p2.first) Pitch(p2.second) B(da1,longdad);
   }
   else{
     double dr2 = Dr(d,2.0);
     double longdr2 = Long(Dr(d,2.0));
     double da1 = Da(d,1.0);
     double longdad = Long(Da(d));
     produce F(l) SB()  Roll(p1.first) Pitch(p1.second) B(dr2,londr2) EB() 
                  SB()  Roll(p3.first) Pitch(p3.second) B(dr2,longdr2) EB() 
             Roll(p2.first) Pitch(p2.second) B(da1,longdad); 
  }
  else{ 
    produce B(d,l);
  }
}
     
interpretation:

F(s) :
{
  ;
}

close Erythrina;
