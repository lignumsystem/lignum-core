#include <stdlib.h>
#include <ParametricCurve.h>
#include <FirmamentWithMask.h>


namespace sky{

  FirmamentWithMask::FirmamentWithMask(int no_incl,int no_azim)
    :drp_orig(0.0),Firmament(no_incl,no_azim)
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

  //This method  configures the sky from  the file with  a sequence of
  //mask  files.  The  file format  is:  
  //INCL  #e.g.  9 
  //AZIM  #e.g.  9
  //RAD_PLANE #e.g.  1200 
  //ITER1 MaskFile1.fun #e.g. 5   Mask1.fun 
  //ITER2 MaskFile2.fun #e.g. 10  Mask2.fun 
  //ITERN MaskFileN.fun #e.g. 100 Mask3.fun  

  //After  giving the  size and  radiant intensity,  N mask  files may
  //follow.   In  the example  above  the  iterations  [0:5] will  use
  //Mask1.fun,   the   iterations   [6:10]   Mask2.fun   and   [11:100]
  //Mask3.fun. I decided to separate this from the configure() method,
  //because otherwise  configure() would become difficult  to read and
  //understand, and it  is easier to read a file  when the file format
  //is unambiguosly  known.  Note  that no mask  is installed  at this
  //point. It is up to the  user of the class to call 
  //        configure(int i, bool verbose)
  //in the growth loop to reconfigure the sky.
  void FirmamentWithMask::readAllMasks(const string& file)
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
    //read the mask files
    t = lex.getToken(); //iterations
    while (t.getType() != VC_ENDFILE){
      Token t2 = lex.getToken(); //the mask file
      int iteration = atoi(t.getValue().c_str());
      string file = t2.getValue();
      pair<int,string> p(iteration,file);
      gap_ls.push_back(p);//The mask files are  in the list where they
			  //can be found
      t = lex.getToken();
    }
    drp_orig = drp;//remeber the original radiation to plane
  }

  //Use this in the growth loop to install mask file for the 'i:th' iteration.
  void FirmamentWithMask::configure(int i, bool verbose)
  {
    //Find the mask matching the i:th iteration 
    list<pair<int,string> >::iterator it = find_if(gap_ls.begin(),
						   gap_ls.end(),
						   FindNextMask(i));
    if (it != gap_ls.end()){
      //Reset the sky
      resize(getNoOfInclinations(),getNoOfAzimuths(),drp_orig);
      ParametricCurve fgap((*it).second);
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
      if (verbose){
	cout << "Azimuths: "  << getNoOfAzimuths() 
	     << " Inclinations: " 
	     << getNoOfInclinations() << endl;
	cout << "Radiation (Ball sensor): " 
	     << diffuseBallSensor()
	     << " Radiation (Plane sensor): " 
	     << diffusePlaneSensor()
	     << endl;
	cout << "Change of radiation due this mask, Planesensor: " <<
		 getPlaneChange() << "  Ballsensor:  " <<
		 getBallChange() << endl;
      }
      return;
    }
    else if (verbose){
      cout << "Iterator out of maximum value, no new mask available" <<endl;
    }
    return;
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
