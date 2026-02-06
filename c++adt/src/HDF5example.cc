/// \example{lineno} HDF5example.cc
/// Examples how to use  the class `LGMHDF5File`.
/// Generate  HDF5 datasets and save them to a file.
/// To compile in this directory type:
///
/// `h5c++ -I../include -DHDF5MAIN  LGMHDF5File.cc HDF5example.cc  -L../lib -lcxxadt  -o h5file`
///
/// Run `fileh5` without command line parameters.
/// The output file *HDF5Test.h5* will contain datasets for 2D and 3D matrices
/// as well as two examples with C/C++ data structure as 2D and 3D dataset element.
///
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
  cout << "Creating matrices" <<endl;
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

  //Create 2D matrix with H5TestStruct data structure
  TMatrix2D<H5TestStruct> mh5_2Dstruct(4,5);
  for (int i=0; i < 4; i++){
    for (int j=0; j < 5; j++){
      mh5_2Dstruct[i][j].a = i+j;
      mh5_2Dstruct[i][j].b = static_cast<float>(10.0*(i+j));
      mh5_2Dstruct[i][j].c = static_cast<double>(20.0*(i+j)+0.0001);
    }
  }
  //Create 3D matrix with H5TestStruct data structure
  TMatrix3D<H5TestStruct> mh5_3Dstruct(3,4,5);
  for (int i=0; i < 3; i++){
    for (int j=0; j < 4; j++){
      for (int k=0; k < 5; k++){
	mh5_3Dstruct[i][j][k].a = i+j+k;
	mh5_3Dstruct[i][j][k].b = static_cast<float>(10.0*(i+j+k));
	mh5_3Dstruct[i][j][k].c = static_cast<double>(20.0*(i+j+k)+0.0001);
      }
    }
  }
  //Create datasets
  cout << "Creating datasets" <<endl;
  h5file.createDataSet("H5MATRIX2D",5,7,m2d);
  h5file.createDataSet("H5MATRIX3D",5,6,7,m3d);
  h5file.createDataSet("H5STRUCT2D",comp_data,4,5,mh5_2Dstruct);
  h5file.createDataSet("H5STRUCT3D",comp_data,3,4,5,mh5_3Dstruct);
  h5file.close();
  cout << "Done" << endl;
  exit(0);
}

#endif
