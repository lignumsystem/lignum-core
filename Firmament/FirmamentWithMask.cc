#include <stdlib.h>
#include <FirmamentWithMask.h>
#include <Lex.h>

namespace sky{

FirmamentWithMask::FirmamentWithMask(int no_incl,int no_azim)
  :Firmament(no_incl,no_azim)
{
  /*empty*/
}

void FirmamentWithMask::readMaskFile(const string& file)
{
  Lex lex;
  lex.scan(file);
  
  //get the first inclinatation
  Token t1 = lex.getToken();
  while (t1.getType() != ENDFILE){
    string v1str =  t1.getValue();
    //there will be value for inclination (blocking)
    Token t2 = lex.getToken();
    string v2str = t2.getValue();
    //percentage
    double val = atof(v2str.c_str()); 
    if (t1.getType() == ID){//zenith sector, keyword "zenith"
      diffuseRadZenith = diffuseRadZenith*((100.0-val)/100.0);
    }
    else{
      //index
      int index = atoi(v1str.c_str());
      //loop through one inclination denoted by index
      setMask(index,val);
    }
    t1 = lex.getToken();
  }
}

//sets a mask for one inclination by reducing incoming radiation
//by argument percentage
void FirmamentWithMask::setMask(int incl_index,double percentage)
{
  int j = 0;
  for (j = 0; j < azimDivisions[incl_index]; j++){
    diffuseRad[incl_index][j] = diffuseRad[incl_index][j]*((100.0-percentage)/100.0);
  }

  diffuseRadBall = diffuseRadZenith;

  vector<double> radiation_direction(3);
  for (j = 0; j < numberOfRegions(); j++){
    diffuseRadBall += diffuseRegionRadiationSum(j,radiation_direction);
  }
}

} //closing namespace sky

#ifdef FWM
#include <iostream.h>

using namespace sky;
      
int main(int argc, char* argv[])
{
  FirmamentWithMask fwm(9,24);
  fwm.outDiff();
  cout << endl;
  if (argc != 2)
    cout << "Usage: fwm mask-file" << endl;
  fwm.readMaskFile(argv[argc-1]);
  fwm.outDiff();
  exit(0);
}

#endif
