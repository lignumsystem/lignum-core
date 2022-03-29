#include <array>
/// \file LGMHDF5File.cc
/// \brief LGMHDF5File implementation with examples to save Lignum simulations to HDF5 file.
#include <LGMHDF5File.h>


LGMHDF5File::LGMHDF5File(const string& file_name)
  :hdf5_file(file_name,H5F_ACC_TRUNC)
{
}

LGMHDF5File::~LGMHDF5File()
{
  hdf5_file.close();
}

int LGMHDF5File::createDataSet(const string& dataset_name, int years, int rows, int cols, const TMatrix3D<double>& data)
{
  double data_array3D[years][rows][cols];
  for (int i = 0; i < years; i++){
    for (int j = 0; j < rows; j++){
      for (int k=0; k < cols; k++){
	data_array3D[i][j][k] = data[i][j][k];
      }
    }
  }
  return createDataSet(dataset_name,years,rows,cols,data_array3D);
}

int LGMHDF5File::createDataSet(const string& dataset_name, int years, int rows, int cols, void* data)
{
  FloatType datatype(PredType::NATIVE_DOUBLE);
  try{
    Exception::dontPrint();
    /// DataSpace needs dimensions and rank
    hsize_t dspace_dims[DSPACE_RANK3];
    dspace_dims[0] = years;
    dspace_dims[1] = rows;
    dspace_dims[2] = cols;
    DataSpace dataspace(DSPACE_RANK3,dspace_dims);
    DataSet dset = hdf5_file.createDataSet(dataset_name,datatype,dataspace);
    writeDataSet(dset, data);
  }
  catch (DataSetIException error){
    error.printErrorStack();
    return -1;
  }
  return 0;
}

int LGMHDF5File::createDataSet(const string& dataset_name, int rows, int cols, void* data)
{
  FloatType datatype(PredType::NATIVE_DOUBLE);
  try{
    Exception::dontPrint();
    /// DataSpace needs dimensions and rank
    hsize_t dspace_dims[DSPACE_RANK2];
    dspace_dims[0] = rows;
    dspace_dims[1] = cols;
    DataSpace dataspace(DSPACE_RANK2,dspace_dims);
    DataSet dset = hdf5_file.createDataSet(dataset_name,datatype,dataspace);
    writeDataSet(dset, data);
  }
  catch (DataSetIException error){
    error.printErrorStack();
    return -1;
  }
  return 0;
}

int LGMHDF5File::createColumnNames(const string& dset_name, const string& attr_name, const vector<string>& col_names)
{
  ///Use variable length string type
  StrType str_type(PredType::C_S1, H5T_VARIABLE);
  const int rank = 1;
  hsize_t dims[rank];
  ///Reserve space for the string vector
  dims[0]=col_names.size();
  try{
    Exception::dontPrint();
    ///Create atribute dataspace
    DataSpace attr_dspace(rank,dims);
    DataSet dset = hdf5_file.openDataSet(dset_name);
    Attribute attr(dset.createAttribute(attr_name,str_type,attr_dspace));
    ///Convert `vector<string>& col_names ` to char* vector. Required by HDF5
    vector<const char*> c_vector;
    for (vector<std::string>::size_type i = 0; i < col_names.size(); i++){
      c_vector.push_back(col_names[i].c_str());
    }
    ///Finally write string to attribute 
    attr.write(str_type,c_vector.data());
    dset.close();
  }
  catch (AttributeIException error) {
        error.printErrorStack();
        return -1;
  }
  return 0;
}

int LGMHDF5File::writeDataSet(const DataSet& dset, void* data)
{
  try{
    Exception::dontPrint();
    dset.write(data,PredType::NATIVE_DOUBLE);
  }
  catch (DataSetIException error){
    error.printErrorStack();
    return -1;
  }
  return 0;
}

vector<string> LGMHDF5File::getObjectNames()
{
  ssize_t nobj = hdf5_file.getNumObjs();
  vector<string> v;
  cout << "Num objects: " << nobj <<endl;
  for (ssize_t i = 0; i < nobj; i++){
    string str = hdf5_file.getObjnameByIdx(i);
    v.push_back(str);
  }
  return v;
}

void LGMHDF5File::close()
{
  hdf5_file.close();
}

/// \example{lineno} LGMHDF5File.cc
/// The main() has an example how to use  LGMHDF5File to generate  HDF5 file. To compile in this directory type:
///
/// `h5c++ -I../include  -DHDF5MAIN  LGMHDF5File.cc -o fileh5`
///
/// Adjust -I for the location of LGMHDF5File.h. Run `fileh5` without command line parameters.
/// The output file *HDF5Test.h5* will contain two Datasets: 2D and 3D arrays *DataArray2D* and *DataArray3D* respectively.
///
/// To install HDF5 toolkit use for example MacPorts: `sudo port install hdf5`.
#ifdef HDF5MAIN
#include <algorithm>
#include <TMatrix3D.h>
using namespace cxxadt;
int main()
{
  /// Create 10 x 30 x 20  3D array
  const int YEARS = 10;
  const int ROWS = 30;
  const int COLS = 20;
  /// Initialization syntax for array should be possible also for vectors in C++11
  array<string,20> n3D = {"a","b","c","d","e","f","g","h","i","j","k","l","m","n","o","p","q","r","s","t"};
  /// Otherwise this traditional vector initialization is needed.
  vector<string> names3D(n3D.begin(),n3D.end());
  array<string,20> n2D = {"aa","bbbb","ccc","ddd","e","f","gggg","hhhhhh","i","j","kk","ll","m","n","oooo","p","q","rrr","ss","ttttttt"};
  vector<string> names2D(n2D.begin(),n2D.end());

   /// Create 10 x 30 x 20  3D array
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
   /// Create 30 x 20  3D array
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
  vector<string> v = file.getObjectNames();
  copy(v.begin(), v.end(),std::ostream_iterator<string>(std::cout, "\n"));
  
  TMatrix3D<double> tm3d(4,3,6,0);
  
  for (int i=0; i < 4; i++){
    for (int j=0; j < 3; j++){
      for (int k=0; k < 6; k++){
	tm3d[i][j][k] = static_cast<double>(i+j+k);
	cout << endl;
      }
    }
    cout <<endl;
  }
  array<double,6> a6={111,222,333,444,555,666};
  copy(a6.begin(),a6.end(),tm3d[1][2].begin());
  std::reverse(a6.begin(),a6.end());
  copy(a6.begin(),a6.end(),tm3d[2][1].begin());
  for (int i=0; i < 4; i++){
    for (int j=0; j < 3; j++){
      copy(tm3d[i][j].begin(),tm3d[i][j].end(),std::ostream_iterator<double>(std::cout, " "));
      cout << endl;
    }
    cout <<endl;
  }
  cout << endl;
  array<string,6> colsa={"A","B","C","D","E","F"};
  vector<string> colsv(colsa.begin(),colsa.end());
  int res = file.createDataSet("DataArrayTMatrix3D",4,3,6,tm3d);
  file.createColumnNames("DataArrayTMatrix3D","ColumnNamesTMatrix3D",colsv);
  file.close();  
  exit(0);
}

#endif

