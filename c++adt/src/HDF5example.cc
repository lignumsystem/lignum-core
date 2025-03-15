/// \example{lineno} HDF5example.cc
/// Examples how to use  the class `LGMHDF5File`.
/// Generate  HDF5 datasets and save them to a file.
/// To compile in this directory type:
///
/// `h5c++ -I../include -L../lib -DHDF5MAIN  LGMHDF5File.cc HDF5example.cc  -lcxxadt  -o h5file`
///
/// Run `fileh5` without command line parameters.
/// The output file *HDF5Test.h5* will contain sample datasets for 2D and 3D matrices
/// as well as an example with C/C++ data structure as the dataset element. 
/// To install HDF5 toolkit use for example MacPorts: `sudo port install hdf5`.

#include <array>
#include <vector>
#include <algorithm>
#include <LGMHDF5File.h>
using namespace std;
using namespace cxxadt;

#ifdef HDF5MAIN

#include <TMatrix3D.h>
using namespace cxxadt;
int main()
{
  //Data structure
  struct H5TestStruct{
    int a;
    float b;
    double c;
  };
  //Corresponding CompType for H5TestStruct
  H5::CompType comp_data(sizeof(H5TestStruct));
  comp_data.insertMember("A",HOFFSET(H5TestStruct,a),H5::PredType::NATIVE_INT);
  comp_data.insertMember("B",HOFFSET(H5TestStruct,b),H5::PredType::NATIVE_FLOAT);
  comp_data.insertMember("C",HOFFSET(H5TestStruct,c),H5::PredType::NATIVE_DOUBLE);
  
  LGMHDF5File h5file("HDF5Test.h5");
  cout << "Output file " <<  "HDF5Test.h5" << endl;

  //Create 2D matrix
  TMatrix2D<double> m2d(5,7);
  for (int i=0; i < 5; i++){
    for (int j=0; j < 7; j++){
      m2d[i][j]= i+j;
    }
  }
  
  //Create 3D matrix
  TMatrix3D<double> m3d(5,6,7);
  for (int i=0; i < 5; i++){
    for (int j=0; j < 6; j++){
      for (int k=0; k < 7; k++){
       m3d[i][j][k] = i+j+k;
      }
    }
  }
  //Create 3D matrix with H5TestStruct data structure
  TMatrix3D<H5TestStruct> mh5struct(3,4,5);
  for (int i=0; i < 3; i++){
    for (int j=0; j < 4; j++){
      for (int k=0; k < 5; k++){
	mh5struct[i][j][k].a = i+j+k;
	mh5struct[i][j][k].b = static_cast<float>(10.0*(i+j+k));
	mh5struct[i][j][k].c = static_cast<double>(20.0*(i+j+k));
      }
    }
  }
  //Create datasets
  h5file.createDataSet("H5MATRIX2D",5,7,m2d);
  h5file.createDataSet("H5MATRIX3D",5,6,7,m3d);
  h5file.createDataSet("H5STRUCT",comp_data,3,4,5,mh5struct);
  
  h5file.close();
  exit(0);
}

#endif
