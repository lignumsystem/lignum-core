#ifndef MINESET_H
#define MINESET_
#include <stdlib.h>
#include <string>
#include <Lex.h>
#include <Firmament.h>
#include <FirmamentWithMask.h>

using namespace sky;

vector<double>  anglesToVector(double incl, double azim);
void vectorToAngles(vector<double> direction, double& incl, double& azim);
void CreateOutPutFile(Firmament& f,string& name);

#endif
