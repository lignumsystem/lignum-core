#ifndef LGMUNITS_H
#define LGMUNITS_H

//Computations are in double precision, here are synonyms for
//for the units used in lignum
typedef double BLD;        //Braod Leaf Double precision
typedef double KGC;        //Kilogram Carbon (dry weight)
typedef double METER;      //Meter
typedef double M2;         //Square Meter
typedef double MJ;         //Mega Joule (e.g., radiation)
typedef double PA;         //Pressure in
typedef double TP;         //TreeParameter values are in double precision
typedef unsigned int YEAR; //age of the tree compartments in years

enum STATUS {DEAD,ALIVE,DORMANT};    //States of the bud 

#endif 
