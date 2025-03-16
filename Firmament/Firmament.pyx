# distutils: language = c++

from libcpp.vector cimport vector
from Firmament cimport Firmament
import numpy as np

cdef class PyFirmament:
      cdef Firmament* f
      
      def __cinit__(self,int incl,int azim,double rad):
          """
          Constructor: create SOC with given number of inclinations, azimuths and total incoming radiation.
          The total incoming radiation can be seen as the radiation on plane just above the forest canopy 
          @param incl Number of inclinations
          @param azim Number of azimuths: defines the mean number of sectors the inclination
                      zones contain. 
          @param rad Total incoming radiation, plane sensor reading
          @post Number of sectors = incl*azim+zenith
          """
          self.f = new Firmament(incl,azim,rad)

      def resize(self,int incl,int azim,double rad):
          """
          Resize the firmament with new total radiation
          @param incl New number of inclinations
          @param azim New number of azimuths
          @param rad  New total incoming radiation on plane
          """
          self.f.resize(incl,azim,rad)
          
      def number_of_regions(self):
          """
          Query the number of sectors including zenith
          @return  Number of sectors in the Firmament
          """
          return self.f.numberOfRegions()

      def get_number_of_inclinations(self):
          """
          Query number of inclination zones
          @return Number of inclinations
          """
          return self.f.getNoOfInclinations()
          
      def get_sector_area(self, int incl):
          """
          Return sector area in each inclination class
          @param  incl Inclination class
          @return Sector area of inclination class *n*
          @exception Return -1.0  if n > getNoOfInclinations()
          """
          return self.f.getSectorArea(incl)
          
      def get_direction(self,int sec):
          """
          Query the direction of the n:th sector
          @param sec Sector number
          @return Unit vector pointing to the sector `n`
          """
          
          return self.f.getDirectionAsVector(sec)
      
      def set_diffuse_radiation(self,rad):
          """
          Set the total incoming radiation for the SOC
          @param rad Total incoming radiation, plane sensor reading.
          """
          self.f.setDiffuseRadiation(rad)

      def set_sun_position(self,dir):
          """
          Set sun to the sky sector pointed to by *dir*
          @param dir Sequence container direction to the sun
          """
          self.f.setSunPosition(dir)

      def set_direct_radiation(self,rad):
          """
          Set the direct radiation coming from the sun
          @pre Sun position with set_sun_position() must be set
          @param rad The direct radiation
          @sa set_sun_position()
          """
          return self.f.setDirectRadiation(rad)

      def direct_radiation(self,dir=np.array(3*[0])):
          """
          Return direct radiation from the direction of the sun.
          @note Radiant intensity *perpedicular* to directios vector 
          @param dir Sequence container of length 3. 
          @return rad  where *rad* is the direct radiation
          """
          return self.f.directRadiation(dir)
                           
      def diffuse_radiation_sum(self,dir):
          """
          Query the diffuse radiation from the sky sector pointed to by  *dir*
          @param dir Sequence container with length 3 for sky sector direction
          @return Diffuse radiation from the sector in direction *dir*
          """
          return self.f.diffuseRadiationSum(dir)
      
      def diffuse_region_radiation_sum(self,sec:int,dir=np.array(3*[0])):
          """
          Query diffuse radiation from the sector with number *sec*.
	      The sector numbering starts from 0.
	      @pre 0 <= sec < number_of_regions()
          @param sec Sector number
          @param dir Sequence container to contain the direction of the sector *sec*
          @return rad  where *rad* is the diffuse radiation of the sector 
          @exception Return -1.0 if sec >= number_of_regions()
          """
          return self.f.diffuseRegionRadiationSum(sec,dir)

      def diffuse_plane_sensor(self):
          """
          Query the total incoming diffuse radiation plane sensor reading
          @return Total incoming diffuse radiation, plane sensor
          @sa diffuse_ball_sensor()
          """
          return self.f.diffusePlaneSensor()

      def diffuse_ball_sensor(self):
          """
          Query the total incoming diffuse radiation ball sensor reading
          @return Total incoming diffuse radiation, ball sensor
          @sa diffuse_plane_sensor
          """
          return self.f.diffuseBallSensor()
      def diffuse_rad_zenith(self):
          """
          Diffuse radiation from the zenith sector
          @return Zenith sector diffusde radiation
          """
          return self.f.getDiffuseRadZenith()
      
      def __dealloc__(self):
          """
          Destructor to free allocated memory
          """
          del self.f
