#ifndef FIRMAMENT_WITH_MASK
#define FIRMAMENT_WITH_MASK

#include <list>
using namespace std;
#include <Firmament.h>
#include <string>
#include <sstream>
#include <Lex.h>
#include <vector>
#include<iterator>
#include<algorithm> 

using namespace cxxadt;
namespace sky{
  ///\brief Functor to find a mask based on i:th time step
  class FindNextMask{
  public:
    ///\brief Default constructor
    FindNextMask():iter(0) {};
    ///\brief Constructor to find i:th mask (e.g. for the i:th time step)
    ///\param i the i:th mask
    FindNextMask(int i):iter(i){}
    ///\brief Functor to locate i:th mask
    ///\param p Pair containing position and the name of the mask file
    ///\return True if i:th mask is located, False otherwise
    bool operator()(const pair<int,string>& p)const{
      if (iter <= p.first)
	return true;
      else
	return false;

    }
  private:
    int iter; ///< The i:th mask to be found
  };

///\brief FirmamentWithMask models a gap in a forest.
///
///The gaps in a forest are often analyzed by foresters
///by taking photograhs  with fish-eye lenses.
///The size and the form of the gap is further
///analyzed by marking the path of the sun 
///in the photograph and the effect of the direct and 
///diffuse radiation can be estimated (somehow).
///The idea of this class is simply to mimic such
///fish-eye photograph and to model the effect
///of the blocked incoming radiation, direct and diffuse.
///Thus the name FirmamentWithMask.
///Ideally the user could define the gap (i.e., the photograph)
///in a file, though in a somewhat simplified manner.    
///Methods:
/// -# readMaskFile
///   - Read the mask file and adjust radiation
/// -# setMask
///   - Naive approach: in a file for each inclination  the percentage of remaining radiation is given
///   100% means gap, less than 100% means obstacle.
class FirmamentWithMask:public Firmament{
public:
  ///\brief Default constructor
  ///
  ///The Lignum model uses Firmament as source of photosynthetic active radiation (PAR).
  ///The incoming radiation in a tree canopy is modelled using ray casting (not ray tracing)
  ///assuming no reflections of the light rays. This assumption can be made assuming PAR is used.
  ///Leaves are assumed black bodies regarding the PAR; it is either used in foliage or
  ///transmitted through.
  ///\param no_incl Number of inclinations
  ///\param no_azim Number of azimuths
  ///\param rad_plane Incoming PAR radiation on the plane (for example forest canopy),  
  FirmamentWithMask(int no_incl = NUM_OF_INCL/*9*/, int no_azim = NUM_OF_AZIM /*24*/,double rad_plane=1200.0);
  ///\brief Resize the firmament
  ///
  ///To use the masks correctly the original radiation to plane is saved
  ///\sa Firmament::configure.
  void resize(int no_incl,int no_azim, double rad);
  ///\brief Initialize firmament
  ///
  ///Intializing the firmament from a file that contains
  ///size (inclinations and azimuths), radiation intensity
  ///and an optional mask for the firmament
  ///\param file File containing specification for the firmament
  ///\par Configuration file format with mask
  ///Configure firmament from  a file with  a sequence of
  ///mask  files. The  file format is as follows:
  ///
  ///ConfigurationFile.txt | Notes
  ///:-------------------- | :-------
  /// <tt># Some comment</tt>| Comment line
  ///9                     | 9 inclinations + zenith sector
  ///10                    | 10 azimuth sectors
  ///1200                  | Incoming radiation on plane (e.g. 1200MJ PAR)
  ///0      100.0     | 1st inclination 100% mask
  ///1      100.0     | 2nd inclination 100% mask
  ///2       99.0     |  99% mask
  ///3       99.0     |    - "" -
  ///4       99.0     |    - "" -
  ///5       98.5     |  98.5% mask
  ///6       50.0     | 50% mask
  ///7       30.0     | 30% mask
  ///8        0.0     | 9th inclination No mask
  ///zenith   0.0     | No mask
  ///
  ////Each mask defines a mask for all azimuth sectors in an inclination.
  ///\important Masks must match the number of inclinations in the firmament
  ///and define number of inclinations and the zenith sector even if no masking.
  ///\note the mask is optional
  ///\note The quanta (amount) of incoming radiation in PAR and the units used depend on application.  
  void configure(const string& file);
  ///\brief Reconfigure firmament with a new mask
  ///
  ///Use this in the growth loop to install mask file for the 'i:th' iteration.
  void configure(int iter, bool verbose = false);
  ///\brief Read configuration file
  ///
  ///\param file File for firmament configuration including mask file names
  ///
  ///\par Configuration file format with a mask
  ///Configure firmament from  a file with  a sequence of
  ///mask  files. The  file format is as follows:
  ///
  ///ConfigurationFile.txt | Notes  
  ///:-------------------- | :-------
  /// <tt># Some comment</tt>| Comment line
  ///9                     | 9 inclinations + zenith sector
  ///10                    | 10 azimuth sectors
  ///1200                  | Incoming radiation on plane (1200MJ PAR)
  ///5  MaskFile1.txt      | Mask file for iterations 0-5
  ///10 MaskFile2.txt      | Mask file for iterations 6-10
  ///20 MaskFile3.txt      | Mask file for iterations 11-20
  ///
  ///\par Mask file format
  ///Each mask file defines a mask for all azimuth sectors in an inclination:
  ///
  ///MaskFile.txt     | Notes
  ///:--------------- | :-------:
  /// <tt># Some comment</tt>| Comment line 
  ///0      100.0     | 1st inclination 100% mask
  ///1      100.0     | 2nd inclination 100% mask
  ///2       99.0     |  99% mask
  ///3       99.0     |    - "" -
  ///4       99.0     |    - "" -
  ///5       98.5     |  98.5% mask
  ///6       50.0     | 50% mask
  ///7       30.0     | 30% mask
  ///8        0.0     | 9th inclination No mask
  ///zenith   0.0     | No mask
  ///
  ///\important Mask file must match the number of inclinations in the firmament
  ///and define number of inclinations and the zenith sector even if no masking. 
  void readAllMasks(const string& file);
  ///\brief Read a single mask file
  ///\sa Firmament::readAllMasks
  void readMaskFile(const string& file);
  ///\brief Reduce incoming radiation in firmament sector-wise
  ///
  ///Read file setting mask according to azimuth and inclination angles.
  ///The two angles are given in degrees.
  ///
  ///\par Configuration file format with a mask
  ///Configure firmament from  a file with azimuth and inclination masks
  ///
  ///ConfugurationFile.txt   | Notes
  ///----------------------- |------
  /// <tt># Some comment</tt>| Comment line
  ///10                      | 10 inclinations
  ///20                      | 20 azimuths
  ///1200                    | Incoming radiation on plane (1200MJ PAR)
  ///0 10 100                | Azimuth  0 degrees, inclination 10 degrees, mask 100%
  ///50 20 60                | Azimuth 50 degrees, inclination 20 degrees, mask 60%
  ///120 50 30               | Azimuth 120 degrees, inclination 50 degrees, mask 30%
  ///\warning Experimental and not tested fully. 
  void readAzimuthInclinationMaskFile(const string& file);
  ///\brief The same as Firmament::setMask
  void getMask(int incl_index,double percentage){return  setMask(incl_index, percentage);}
  ///\brief The same as Firmament::readMaskFile
  void getreadMask(Lex& file){ return readMask(file);}
  ///\brief Ball sensor value change
  ///\retval ballChange Ball sensor value change due to mask 
  LGMdouble getBallChange() {return  ballChange; }
  ///\brief Plane  sensor value change
  ///\retval plaveChange Plane  sensor value change due to a mask
  LGMdouble getPlaneChange() {return  planeChange; }
  ///\brief The original plane sensor value in firmament
  ///\retval drp_orig The original plane sensor value in firmament
  LGMdouble getDrp_orig() {return  drp_orig; }
  ///\brief Get mask files
  ///\return The list of mask files as vector 
  std::vector<std::pair<int,std::string> > getResultVector() const{
    std::vector<std::pair<int, std::string> > result( gap_ls.begin(), gap_ls.end() );
    return result;
   }
protected:
  void readMask(Lex& file);
  void setMask(int incl_index,double percentage);
  void setRegionMask(int region,double mask_percentage);
 private:
  LGMdouble ballChange;    ///<Change to diffuseRadBall caused by SetMask
  LGMdouble planeChange;   ///<Change to diffuseRadPlane  caused by SetMask
  LGMdouble drp_orig; ///<The original plane sensor radiation of the sky 
  list<pair<int,string> > gap_ls; ///<List of masks or gap files 
  vector<pair<int,string> > result;///<List of masks gap files as vector \sa getResultVector()

};

}//closing namespace sky
#endif
