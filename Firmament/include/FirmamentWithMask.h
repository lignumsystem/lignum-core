#ifndef FIRMAMENT_WITH_MASK
#define FIRMAMENT_WITH_MASK

#include <Firmament.h>
#include <string>
#include <Lex.h>
using namespace cxxadt;
namespace sky{

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
  void readMaskFile(const string& file);
protected:
  void readMask(Lex& file);
  void setMask(int incl_index,double percentage);
};

}//closing namespace sky
#endif
