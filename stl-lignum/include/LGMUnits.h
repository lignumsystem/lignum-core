#ifndef LGMUNITS_H
#define LGMUNITS_H

namespace Lignum{

//Computations are in double precision, here are synonyms for
//for the units used in lignum
  typedef double LGMdouble;  //Generic double precision
  typedef double KGC;        //Kilogram Carbon (dry weight)
  typedef double METER;      //Meter
  typedef double M2;         //Square Meter
  typedef double MJ;         //Mega Joule (e.g., radiation)
  typedef double PA;         //Pressure in
  typedef unsigned int YEAR; //age of the tree compartments in years

  //The states of a bud
  const LGMdouble DEAD = 0.0;
  const LGMdouble ALIVE = 1.0;
  const LGMdouble DORMANT = 2.0;

}//closing namespace Lignum
#endif 
