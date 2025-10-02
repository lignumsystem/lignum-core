/// \file LGMUnits.h
/// \brief Units used in Lignum
#ifndef LGMUNITS_H
#define LGMUNITS_H

namespace Lignum{

  ///\defgroup LignumUnits Units used in Lignum
  ///Computations are in double precision, here are synonyms for
  ///for units used in Lignum
  ///@{
  typedef double LGMdouble;  ///<Generic double precision
  typedef double KGC;        ///<Kilogram Carbon (dry weight)
  typedef double METER;      ///<Meter
  typedef double M2;         ///<Square Meter
  typedef double MJ;         ///<Mega Joule (e.g., radiation)
  typedef double PA;         ///<Pressure in Pascal
  typedef unsigned int YEAR; ///<Age of a tree compartment in years
  ///@}
  
  ///\defgroup BudStates The Bud states
  ///The list of possile buds states \sa Lignum::LGAstate
  ///@{
  ///Dead bud
  const LGMdouble DEAD = 0.0;
  ///Alive bud
  const LGMdouble ALIVE = 1.0;
  ///Dormant bud
  const LGMdouble DORMANT = 2.0;
  ///Bud to produce a cone or other reproductive organ 
  const LGMdouble FLOWER = 3.0;
  ///@}
}//closing namespace Lignum
#endif 
