#include <array>
#include <LGMHDF5File.h>
/// \file LGMHDF5File.cc
/// \brief LGMHDF5File implementation with examples to save Lignum simulations to HDF5 file.


namespace cxxadt{
  TMatrix2D<double> LGMHDF5::getLignumFnData(const vector<double>& v)
  {
    //Check if function is defined
    if (!v.empty()){
      /// The ParametricCurve is defined by (x,f(x)) pairs.<br>
      /// Return value TMatrix2D[N][2] is 2D data arrray where N = number of (x,f(x)) pairs. <br>
      /// Note the last element in the vector `v` is FLT_MAX to denote the end of function.
      /// Thus the number of N (i.e. rows) is:
      /// \internal
      /// \snippet{lineno} LGMHDF5File.cc Rows
      // [Rows]
      int rows = static_cast<int>((v.size()-1)/2.0);
      // [Rows]
      /// \endinternal
      TMatrix2D<double> fn_data(rows,2,0.0);
      //Note we raise loop index by two to the next (x,f(x)) pair
      //Note we must stop when the last x value has been found (the v.size()-2)
      for (unsigned int i=0,j=0; i < v.size()-2; i+=2,j++){
	fn_data[j][0] = v[i];
	fn_data[j][1] = v[i+1];
      }
      return fn_data;
  }
    else{
      /// `std::nan` denotes function not defined
      TMatrix2D<double> fn_data(1,2,std::nan(""));
      return fn_data;
    }
  }
  
  LGMHDF5File::LGMHDF5File(const string& file_name)
    :hdf5_file(file_name,H5F_ACC_TRUNC)
  {
  }

  LGMHDF5File::~LGMHDF5File()
  {
    hdf5_file.close();
  }
  
  int LGMHDF5File::createGroup(const string& name)
  {
    try{
      Exception::dontPrint();
      Group group(hdf5_file.createGroup(name));
    }
    // File operations
    catch (FileIException error){
        error.printErrorStack();
        return -1;
    }
    //Group operations
    catch (GroupIException error){
        error.printErrorStack();
        return -1;
    }
    return  0;
  }
  int LGMHDF5File::createDataSet(const string& dataset_name, int years, int rows, int cols, const TMatrix3D<double>& data)
  {
    ///Copy TMatrix<3D> `data` to 3D array of double type 
    double data_array3D[years][rows][cols];
    for (int i = 0; i < years; i++){
      for (int j = 0; j < rows; j++){
	for (int k = 0; k < cols; k++){
	  data_array3D[i][j][k] = data[i][j][k];
	}
      }
    }
    ///After that create HDF5 dataset NATIVE_DOUBLE
    return createDataSet(dataset_name,years,rows,cols,data_array3D);
  }

  int LGMHDF5File::createDataSet(const string& dataset_name, int years, int cols, const TMatrix2D<double>& data)
  {
    ///Copy TMatrix<2D> `data` to 2D array of double type 
    double data_array2D[years][cols];
    for (int i = 0; i < years; i++){
      for (int j = 0; j < cols; j++){
	  data_array2D[i][j] = data[i][j];
      }
    }
    ///After that create HDF5 dataset NATIVE_DOUBLE
    return createDataSet(dataset_name,years,cols,data_array2D);
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
      DataSpace dspace(DSPACE_RANK3,dspace_dims);
      DataSet dset = hdf5_file.createDataSet(dataset_name,datatype,dspace);
      writeDataSet(dset, data);
      dspace.close();
      dset.close();
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
      DataSpace dspace(DSPACE_RANK2,dspace_dims);
      DataSet dset = hdf5_file.createDataSet(dataset_name,datatype,dspace);
      writeDataSet(dset, data);
      dspace.close();
      dset.close();
    }
    catch (DataSetIException error){
      error.printErrorStack();
      return -1;
    }
    return 0;
  }

  int LGMHDF5File::createDataSet(const string& dataset_name, const string& data)
  {
    //The vector to store the string
    vector<const char*> v_cstr;
    //There might not be a way a dataset to be a single string
    //but the string must be in a vector
    v_cstr.push_back(data.c_str());
    //Variable length string (command line length varies)
    StrType str_type(PredType::C_S1, H5T_VARIABLE);
    const int rank = 1;
    hsize_t dims[rank];
    //In practice vector length is 1.
    dims[0]=v_cstr.size();
    //Dataspace for the dataset
    DataSpace  dspace(rank,dims);
    //Dataset itself
    DataSet dset = hdf5_file.createDataSet(dataset_name, str_type, dspace);
    //Write the conent of the vector to dataset
    dset.write(v_cstr.data(),str_type);
    dspace.close();
    dset.close();
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
      attr_dspace.close();
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

  int LGMHDF5File::createFnDataSetsFromDir(const string& pattern, const string& hdf5_group, const string& attr_name,
					   const vector<string>& col_names)
  {
    glob_t glob_result;
    glob(pattern.c_str(),GLOB_TILDE,NULL,&glob_result);
    vector<string> files;
    int res=0;
    for(unsigned int i=0;i<glob_result.gl_pathc;++i){
      string fname = glob_result.gl_pathv[i];
      ParametricCurve fn(fname);
      cout << fname <<endl;
      TMatrix2D<double> hdf5data = getLignumFnData(fn.getVector());
      res=createDataSet(hdf5_group+fname,hdf5data.rows(),hdf5data.cols(),hdf5data);
      res=createColumnNames(hdf5_group+fname,attr_name,col_names);
    }
    globfree(&glob_result);
    return res;
  }
    
  void LGMHDF5File::close()
  {
    hdf5_file.close();
  }
}//namespace cxxadt

