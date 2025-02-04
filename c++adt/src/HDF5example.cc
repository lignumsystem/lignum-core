/// \example{lineno} HDF5example.cc
/// Examples how to use  the class `LGMHDF5File`.
/// Generate  HDF5 datasets and save them to a file.
/// To compile in this directory type:
///
/// `h5c++ -I../include  -DHDF5MAIN  LGMHDF5File.cc HDF5example.cc -o fileh5`
///
/// Run `fileh5` without command line parameters.
/// The output file *HDF5Test.h5* will contain three Datasets: 2D data array *DataArray2D*,
/// 3D data array *DataArray3D* and 3D data array *DataArrayTMatrix3D* created with TMatrix3D<double>.
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
  // Create 10 x 30 x 20  3D array
  const int YEARS = 10;
  const int ROWS = 30;
  const int COLS = 20;
  // Column names 
  // Initialization syntax for array should be possible also for vectors in C++11
  array<string,20> n3D = {"a","b","c","d","e","f","g","h","i","j","k","l","m","n","o","p","q","r","s","t"};
  // Otherwise this traditional vector initialization is needed.
  vector<string> names3D(n3D.begin(),n3D.end());
  array<string,20> n2D = {"aa","bbbb","ccc","ddd","e","f","gggg","hhhhhh","i","j","kk","ll","m","n","oooo","p","q","rrr","ss","ttttttt"};
  vector<string> names2D(n2D.begin(),n2D.end());

   // Create 10 x 30 x 20  3D array
  double data_array3D[YEARS][ROWS][COLS];
  /// Data (k=0,k=1,k=2....)
  /// 0 1 2 3 4 ...
  /// 1 2 3 4 5 ...
  /// 2 3 4 5 6
  for (int i = 0; i < YEARS; i++){
    for (int j = 0; j < ROWS; j++){
      for (int k = 0; k < COLS; k++){
	data_array3D[i][j][k]= static_cast<double>(i+j+k);
      }
    }
  }
   // Create 30 x 20  2D array
  double data_array2D[ROWS][COLS];
  for (int j = 0; j < ROWS; j++){
    for (int k = 0; k < COLS; k++){
      data_array2D[j][k]= static_cast<double>(j+k);
    }
  }
  LGMHDF5File file("HDF5Test.h5");
  cout << "Output file " <<  "HDF5Test.h5" << endl;
  file.createDataSet("DataArray3D",YEARS,ROWS,COLS,data_array3D);
  file.createColumnNames("DataArray3D","ColumnNames3D",names3D);
  file.createDataSet("DataArray2D",ROWS,COLS,data_array2D);
  file.createColumnNames("DataArray2D","ColumnNames2D",names2D);

  //Create 4 x 3 x 6 3D Dataset intialized with zeroes using TMatrix<double>
  TMatrix3D<double> tm3d(4,3,6,0);  
  for (int i=0; i < 4; i++){
    for (int j=0; j < 3; j++){
      for (int k=0; k < 6; k++){
	tm3d[i][j][k] = static_cast<double>(i+j+k);
      }
    }
  }
  //Replace some rows in some 2D arrays with new values
  array<double,6> a6={111,222,333,444,555,666};
  copy(a6.begin(),a6.end(),tm3d[1][2].begin());
  std::reverse(a6.begin(),a6.end());
  copy(a6.begin(),a6.end(),tm3d[2][1].begin());
  array<string,6> colsa={"A","B","C","D","E","F"};
  vector<string> colsv(colsa.begin(),colsa.end());

  int res = file.createDataSet("DataArrayTMatrix3D",4,3,6,tm3d);
  file.createColumnNames("DataArrayTMatrix3D","ColumnNamesTMatrix3D",colsv);
  vector<string> v = file.getObjectNames();
  cout << "Datasets in the file" <<endl;
  copy(v.begin(), v.end(),std::ostream_iterator<string>(std::cout, "\n"));
  file.close();
  exit(0);
}

#endif
