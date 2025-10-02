/// \file MineSet.h
/// \brief No longer in use
///
/// Create output file for MineSet program
#ifndef MINESET_H
#define MINESET_H
#include <stdlib.h>
#include <string>
#include <Lex.h>
#include <Firmament.h>
#include <FirmamentWithMask.h>

using namespace sky;

vector<double>  anglesToVector(double incl, double azim);
void vectorToAngles(vector<double> direction, double& incl, double& azim);
///\brief Create output file for MineSet program 
void CreateOutPutFile(Firmament& f,string& name);

#endif
