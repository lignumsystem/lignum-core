# distutils: language = c++

cdef extern from "Firmament.cc":
    pass

from libcpp.vector cimport vector

cdef extern from "Firmament.h" namespace "sky":
     cdef cppclass Firmament:
           Firmament(int,int,double) except +
           void resize(int no_incl, int no_azim, double diffuse_rad_plane) except +
           int numberOfRegions()
           double getSectorArea(int incl)
           int getNoOfInclinations()
           vector[double] getDirectionAsVector(int sec);
           void setDiffuseRadiation(double)
           void setSunPosition(const vector[double]& v)
           void setDirectRadiation(const double rad)
           double directRadiation(vector[double]& dir)
           double diffuseRadiationSum(const vector[double]& dir)
           double diffuseRegionRadiationSum(int sec,vector[double]& dir)    
           double diffusePlaneSensor()
           double diffuseBallSensor()
           double getDiffuseRadZenith()
