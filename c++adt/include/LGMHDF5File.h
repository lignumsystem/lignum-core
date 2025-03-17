/// \file LGMHDF5File.h
/// \brief The interface to HDF5 c++ library
///
/// The interface to HDF5 c++ library to create HDF5 files for Lignum simulations.
/// The further analysis of data is meant to be made with R, Python or some other
/// high level tool supporting HDF5 files. To retrieve information from a HDF5
/// file one can also use utility tools from HDF5 installation, e.g.:
/// + h5ls: List the objects (datasets, groups etc.) in a HDF5 file
/// + h5dump: Dump the content of a HDF5 file
/// + h5cc, h5c++, h5fc: Compile HDF5 applications
///
/// See also:
/// + HDFView: Tool for browsing and editing HDF5 files
#ifndef LGMHDF5FILE_H
#define LGMHDF5FILE_H
#include <cmath>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <glob.h>
#include <ParametricCurve.h>
#include <TMatrix3D.h>
#include <H5Cpp.h>
using namespace H5;
using namespace std;
using namespace cxxadt;

namespace cxxadt{
  /// DataSpace RANKS for 2D and 3D arrays
  const int DSPACE_RANK3 = 3; ///< DataSpace rank 3D array
  const int DSPACE_RANK2 = 2; ///< DataSpace rank 2D array (matrix)
  /// \brief Base class to create TMatrix2D from Lignum functions and parameters.
  ///
  /// \sa LGMHDF5File
  class LGMHDF5{
  public:
    /// \brief Lignum function vector
    ///
    /// Create TMatrix2D representation from Lignum function vector
    /// \param v Function definition vector from ParametricCurve
    /// \exception Undefined vector (i.e. v.size()==0) results TMatrix2D[1][2] with the row [std::nan std::nan]
    /// \return TMatrix2D[N][2] where N is the number of (x,f(x)) points for  ParametricCurve
    /// \sa ParametricCurve
    TMatrix2D<double> getLignumFnData(const vector<double>& v)const;
    /// \brief Lignum parameter files
    ///
    /// Create TMarix2D representation from Lignum parameter files (usually Tree*.txt)
    /// \param fname Tree parameter file name
    /// \exception If cannot open file return TMatrix2D[1][2] with the row [NULL NULL]
    /// \return  TMatrix2D<string>[N][2] where N is the number of parameters in the file
    /// \note Parameter values are also returned as strings
    TMatrix2D<string> getLignumParameterData(const string& fname)const;
  };
  /// \brief Create HDF5 datasets file
  ///
  /// Create HDF5 datasets file from 2D or 3D data arrays, or from a STL string.
  /// After Lignum simulation all simulation data is assumed to be in 2D or 3D arrays. LGMHDF5File can
  /// create HDF5 datasets from the simulation data and produce a single HDF5 file.
  /// Future analysis can be done with R, python or other HDF5 compatible tool.
  /// Thus the LGMHDF5File class  does not (yet) have methods to read HDF5 files.
  ///
  /// The datasets will be of NATIVE_DOUBLE type defined in HDF5. Thus user provides 2D or 3D arrays
  /// of *double* type. Column names are implemented as HDF5 attributes.
  ///
  /// The 3D data should be organised as `array[years][rows][columns]` where the
  /// `rows` are Lignum trees, `columns` are data for a tree and `years` are simulation iterations.
  /// For example `array[4][5]` retrieves data row for the `5`th tree on the iteration `4`.
  /// The 2D data is up to user, usually `array[years][columns]` for aggreate annual data.
  /// 
  /// \important In C/C++ and Python array indexing starts from 0 but for example R starts indexing from 1.
  /// \important C/C++ (consequently LGMHDF5File implementation) and Python use row-first ordering
  /// for storing multidimensinal vectors in linear continous storage. R uses Fortran style column-first ordering.
  /// Use for example matrix transposes to get the original dataset dimensions in R.
  ///
  /// \warning HDF5 does not *enforce* UTF-8. Using UTF-8 charactiers (like scandinavian alphabet)
  /// may be OK on one platform but not on some others.
  /// \sa TMatrix2D TMatrix3D for 2D and 3D data arrays.
  class LGMHDF5File:public LGMHDF5{
  public:
    /// Constructor prepares the file `file_name` for datasets by creating HDF5 file.
    /// Previous existing file will be truncated.
    /// \param file_name HDF5 file name
    /// \exception DataSpaceIException
    /// \sa hdf5_file
    LGMHDF5File(const string& file_name);
    /// Close the H5File `hdf5_file`.
    /// \sa hdf5_file
    ~LGMHDF5File();
    /// \brief Create group in HDF5 file
    /// \param name Group name
    /// \return -1 if error 0 otherwise 
    /// \exception FileIException GroupIException
    /// \note The group name is a Linux/Unix style directory path string. e.g. "/Groups/GroupA"
    int createGroup(const string& name);
    /// \brief Create 3D dataset from a struct T type 
    ///
    /// Create dataset from a struct T datatype. User defines \p comp_type that contains
    /// the names, offsets and HDF5 datatypes of the struct members.
    /// \tparam T struct datatype in the dataset
    /// \param name Name of the dataset
    /// \param comp_type HDF5 CompType describing the struct T members
    /// \param x X dimension
    /// \param y Y dimension
    /// \param z Z dimension
    /// \param data The 3D data matrix
    /// \return -1 if error 0 otherwise
    /// \exception DataSetIException
    /// \note This method can be used to save data collected from VoxelSpace and VoxelBoxes
    /// \sa createDataSet(const string&,int,int,int,const TMatrix3D<double>&)
    template <class T>
    int createDataSet(const string& name, const CompType& comp_type, int x, int y, int z, const TMatrix3D<T>& data);
    /// \brief Create dataset form TMatrix3D
    /// \param name Name of the dataset
    /// \param years Simulation years dimension
    /// \param rows Number of data rows dimension
    /// \param cols Number of data columns dimension
    /// \param data The 3D matrix of double
    /// \return -1 if error 0 otherwise
    /// \exception DataSetIException
    int createDataSet(const string& name, int years, int rows, int cols, const TMatrix3D<double>& data);
    /// \brief Create dataset from TMatrix2D<double> (e.g. stand level data)
    /// \param name Name of the dataset
    /// \param years Years  (rows) dimension
    /// \param cols Columns (data) dimension
    /// \param data The 2D array of type *double*
    /// \return -1 if error 0 otherwise
    /// \exception DataSetIException
    int createDataSet(const string& name, int years, int cols, const TMatrix2D<double>& data);
    /// \brief Create dataset from TMatrix2D<string>, usually Tree parameter files
    /// \param dataset_name Name of the dataset
    /// \param rows Rows (years) dimension
    /// \param cols Columns (data) dimension
    /// \param data The 2D array of type *string*
    /// \return -1 if error 0 otherwise
    /// \exception DataSetIException
    int createDataSet(const string& dataset_name, int rows, int cols, const TMatrix2D<string>& data);
    /// \brief Create dataset of containg one string, for example the content of a command line.
    /// \param dataset_name Dataset name
    /// \param data Dataset string
    /// \return -1 if error 0 otherwise
    /// \exception DataSetIException
    int createDataSet(const string& dataset_name, const string& data);
    /// \brief Create column names as HDF5 attribute. Column names can be of variable length strings.
    /// \param dset_name DataSet name for  which the column names will be given 
    /// \param attr_name Attribute name for the column names 
    /// \param col_names vector of column names 
    /// \return -1 if error 0 otherwise
    /// \exception AttributeIException
    /// \note HDF5 C++ interface does not (yet) support dimension scales which would be a more natural way to describe
    /// the meaning of each N dimensional array dimension.
    /// \warning You can try to use UTF-8 characters in column names (including Scandinavian alphabet) but
    /// not recommended. HDF5 does not *enforce* UTF-8. May be OK on one platform but not on some others.
    int createColumnNames(const string& dset_name, const string& attr_name,const vector<string>& col_names);
    /// Retrieve object names known to `hdf5_file`
    /// \return vector of object names 
    /// \note Object names include groups, dataspaces, datasets etc.
    /// \sa hdf5_file
    vector<string> getObjectNames();
    /// \brief Create datasets from files that have data for ParametricCurve. Wild card search
    /// \pre The file format is as used in Lignum functions 
    /// \param pattern Wild card pattern string for `glob` (in glob.h)
    /// \param hdf5_group HDF5 group
    /// \param attr_name Attribute name for the column names
    ///	\param col_names Column names
    /// \note Traditionally the files for ParametricCurve have *.fun* suffix
    /// \sa glob
    int createFnDataSetsFromDir(const string& pattern, const string& hdf5_group, const string& attr_name, const vector<string>& col_names);
    /// \brief Create datasets from files that have Tree parameters. Wild card search.
    /// \pre The file format is as used in tree parameters for Lignum
    /// \param pattern Wild card pattern string for `glob` (in glob.h)
    /// \param hdf5_group HDF5 group
    /// \param attr_name Attribute name for the column names
    ///	\param col_names Column names
    /// \note Traditionally parameter files are named Tree*.txt.
    int createParameterDataSetsFromDir(const string& pattern, const string& hdf5_group, const string& attr_name,const vector<string>& col_names);
    /// \brief Create datasets from files that are Metafiles. Wild card search
    /// \pre The file format is as used in Metafiles for Lignum
    /// \param pattern Wild card pattern string for `glob` (in glob.h)
    /// \param hdf5_group HDF5 group
    /// \note Traditionally parameter files are named in *MetaFile*.txt.
    int createFileDataSetsFromDir(const string& pattern, const string& hdf5_group);
    /// \brief Close the H5File `hdf5_file`. \sa hdf5_file
    void close();
  protected:
    /// \brief Create 3D array DataSet by giving explicitely the 3 dimensions and `data`
    /// \param dataset_name Name of the dataset
    /// \param years Years dimension
    /// \param rows Rows (trees) dimension
    /// \param cols Columns (data) dimension
    /// \param data The 3D array of type *double*
    /// \return -1 if error 0 otherwise
    /// \exception DataSetIException
    /// \note Technically 3D arrray `data` must be void*. It will be converted to
    /// 3D array of NATIVE_DOUBLE HDF5 dataset of given dimensions. 
    /// \sa writeDataSet
    int createDataSet(const string& dataset_name, int years, int rows, int cols, void* data);
    /// \brief Create 2D array DataSet by giving explicitely the 2 dimensions and the `data`
    /// \param dataset_name Name of the dataset
    /// \param rows Rows dimension
    /// \param cols Columns dimension
    /// \param data The 2D array of type *double*
    /// \return -1 if error 0 otherwise
    /// \exception DataSetIException
    /// \note Technically 2D arrray `data` must be void*. It will be converted to
    /// 2D array of NATIVE_DOUBLE  dataset of given dimensions.  
    /// \sa writeDataSet
    int createDataSet(const string& dataset_name, int rows, int cols, void* data);
    /// \brief Write the dataset to dataspace
    /// \param dset DataSet 
    /// \param data Lignum simulation data
    /// \return -1 if error 0 otherwise
    /// \exception DataSetIException
    /// \sa createDataSet
    int writeDataSet(const DataSet& dset, void* data);
  private:
    H5File hdf5_file; ///< HDF5 file containing simulation results
  };

  template <class T>
  int LGMHDF5File::createDataSet(const string& dataset_name, const CompType& comp_type, int x, int y, int z, const TMatrix3D<T>& data)
  {
    ///\par Function stack and heap 
    ///The maximum function stack may be a limiting factor (use the Terminal shell command `ulimit -Hs`).
    ///In macOS it seems to be 65520 kbytes, default value looks to be 8176.
    ///For the most of the 2D data arrays it can be enough.
    ///With 3D data arrays the stack limit is easily exceeded.
    ///To copy tree data for HDF5 storage reserve contiguous memory dynamically
    ///from the heap instead.
    //
    /// \snippet{lineno} LGMHDF5File.h HeapAllocation3D
    //  [HeapAllocation3D]
    T* v = new T[x * y * z];
    // [HeapAllocation3D]

    ///\par Row first indexing vector as 3D matrix 
    ///To index row first the contiguous memory use the indexing scheme compiler uses.
    ///If you want to understand the row first indexing scheme take a piece of grid paper
    ///and draw for example three 4x5 2D data arrays to represent 3x4x5 data array.
    ///Then plugin numbers to the indexing scheme and see how it lands on the right
    ///array cell on a right 2D array. The `v` denotes first cell (i=j=k=0).
    for (int i = 0; i < x; i++){
      for (int j = 0; j < y; j++){
	for (int k = 0; k < z; k++){
	  /// \snippet{lineno} LGMHDF5File.h HeapIndexing3D
	  // [HeapIndexing3D]
	  *(v + i * y * z + j * z + k) = data[i][j][k];
	  // [HeapIndexing3D]
	}
      }
    }
    try{
      Exception::dontPrint();
      // DataSpace needs dimensions and rank
      hsize_t dspace_dims[DSPACE_RANK3];
      dspace_dims[0] = x;
      dspace_dims[1] = y;
      dspace_dims[2] = z;
      DataSpace dspace(DSPACE_RANK3,dspace_dims);
      DataSet dset = hdf5_file.createDataSet(dataset_name,comp_type,dspace);
      dset.write((void*) v,comp_type);
    }
    catch (DataSetIException error){
      error.printErrorStack();
      return -1;
    }
    //Note the us of [] operator to delete vector 
    delete [] v;
    return 0;
  }
  
}//namepace cxxadt
#endif
