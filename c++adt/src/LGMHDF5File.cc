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


