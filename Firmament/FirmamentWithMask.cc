#include <stdlib.h>
#include <ParametricCurve.h>
#include <FirmamentWithMask.h>


namespace sky{

  FirmamentWithMask::FirmamentWithMask(int no_incl,int no_azim)
    :Firmament(no_incl,no_azim)
  {
    /*empty*/
  }

  //Intializing the firmament from a file that contains
  //size (inclinations and azimuths), radiation intensity
  //and an optional mask for the firmament
  void FirmamentWithMask::configure(const string& file)
  {
    Lex lex;
    lex.scan(file);

    Token t = lex.getToken();
    int incl = atoi(t.getValue().c_str());
    t = lex.getToken();
    int azim = atoi(t.getValue().c_str());
    t = lex.getToken();
    double drp = atof(t.getValue().c_str());
    //size and radiation intensity
    resize(incl,azim,drp);
    //optional mask
    readMask(lex);

    //Update sensor readings diffuseRadBall and diffuseRadPlne

    LGMdouble sumB = 0.0,sumP = 0.0;
    vector<double> radiation_direction(3);
    for (int j = 0; j < numberOfRegions(); j++){
      sumB += diffuseRegionRadiationSum(j,radiation_direction);
      LGMdouble sinIn = radiation_direction[2];
      sumP += diffuseRegionRadiationSum(j,radiation_direction) * sinIn;
    }

    ballChange = sumB/diffuseRadBall;
    diffuseRadBall = sumB;
    planeChange = sumP/diffuseRadPlane;
    diffuseRadPlane = sumP;
  }
    
  void FirmamentWithMask::readMask(Lex& lex)
  {
    //get the first inclinatation
    Token t1 = lex.getToken();
    //There are two options: the user  has described the gap in a file
    //as   ParametricCurve   or  listed   the   gap   data  for   each
    //inclination.  The  former  is  recommended, the  latter  is  for
    //backward compatibility.
    //The mask is in a file
    if (t1.getType() == VC_ID){
      //The mask is in a ParametricCurve
      ParametricCurve fgap(t1.getValue());
      int nincl = getNoOfInclinations();
      //The inclinations  are expressed in  degrees, the horizon  is 0
      //and  the zenith  is 90.  The  mask value  is [0:100]  (0 =  no
      //mask,100 = full mask).
      for (int i=0; i < nincl; i++){
	//Now we need to match [0:90) with [0:nincl], e.g. 45 degrees is nincl/2.
	double x = 90.0*i/nincl;
	double val = fgap(x);
	setMask(i,val);
      }
      //The zenith
      double val = fgap(90.0);
      diffuseRadZenith = diffuseRadZenith*((100.0-val)/100.0);
      return;
    }
    //There will be a mask explicitely fo each inclination. Backward compatibility
    else{
      while (t1.getType() != VC_ENDFILE){
	string v1str =  t1.getValue();
	//there will be value for inclination (blocking)
	Token t2 = lex.getToken();
	string v2str = t2.getValue();
	//percentage
	double val = atof(v2str.c_str()); 
	if (t1.getType() == VC_ID){//zenith sector, keyword "zenith"
	  diffuseRadZenith = diffuseRadZenith*((100.0-val)/100.0);
	}
	else{
	  //index
	  int index = atoi(v1str.c_str());
	  //loop through one inclination denoted by index
	  setMask(index,val);
	}
	t1 = lex.getToken();
      }//while
    }//else
  }
  void FirmamentWithMask::readMaskFile(const string& file)
  {
    Lex lex;
    lex.scan(file);
  
    //get the first inclinatation
    Token t1 = lex.getToken();
    while (t1.getType() != VC_ENDFILE){
      string v1str =  t1.getValue();
      //there will be value for inclination (blocking)
      Token t2 = lex.getToken();
      string v2str = t2.getValue();
      //percentage
      double val = atof(v2str.c_str()); 
      if (t1.getType() == VC_ID){//zenith sector, keyword "zenith"
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


  }

} //closing namespace sky

#ifdef FWM
#include <iostream>

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
