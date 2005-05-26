#ifndef FIRMAMENT_WITH_MASK
#define FIRMAMENT_WITH_MASK

#include <list>
using namespace std;
#include <Firmament.h>
#include <string>
#include <Lex.h>

using namespace cxxadt;
namespace sky{

  class FindNextMask{
  public:
    FindNextMask(int i):iter(i){}
    bool operator()(const pair<int,string>& p)const{
      if (iter <= p.first)
	return true;
      else
	return false;

    }
  private:
    int iter;
  };
//This class tries to model a gap in a forest.
//The gaps are often (?) analyzed by foresters
//by taking photograhs  with fish-eye lenses.
//The size and the form of the gap is further
//analyzed by marking the path of the sun 
//in the photograph and the effect of the direct and 
//diffuse radiation can be estimated (somehow).
//The idea of this class is simply to mimic such
//fish-eye photograph and to model the effect
//of the blocked incoming radiation, direct and diffuse.
//Thus the name FirmamentWithMask.
//Ideally the user could define the gap (i.e., the photograph)
//in a file, though in a somewhat simplified manner.    
//Methods:
//1. readMaskFile
//   Read the mask file and adjust radiation
//2.  setMask
//   This naive approach: in a file for each inclination 
//   the percentage of remaining radiation is given
//   100% means gap, less than 100% means obstacle.
class FirmamentWithMask:public Firmament{
public: 
  FirmamentWithMask(int no_incl = NUM_OF_INCL/*9*/, int no_azim = NUM_OF_AZIM /*24*/);
  void configure(const string& file);
  void configure(int iter, bool verbose = false);
  void readAllMasks(const string& file);
  void readMaskFile(const string& file);
  LGMdouble getBallChange() {return  ballChange; }
  LGMdouble getPlaneChange() {return  planeChange; }
protected:
  void readMask(Lex& file);
  void setMask(int incl_index,double percentage);
 private:
  LGMdouble ballChange;    //Change to diffuseRadBall caused by SetMask
  LGMdouble planeChange;   //Change to diffuseRadPlane  caused by SetMask
  LGMdouble drp_orig; //The original plane sensor radiation of the sky 
  list<pair<int,string> > gap_ls; //List of gap files 
};

}//closing namespace sky
#endif
