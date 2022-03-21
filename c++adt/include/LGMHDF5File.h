/// \file LGMHDF5File.h
/// \brief The interface to HDF5 c++ library to create HDF5 files for Lignum simulations.
///
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
#include <iostream>
#include <string>
#include <vector>
#include <H5Cpp.h>
using namespace H5;
using namespace std;

// DataSpace RANKS for 2D and 3D arrays
const int DSPACE_RANK3 = 3; ///< DataSpace rank 3D array
const int DSPACE_RANK2 = 2; ///< DataSpace rank 2D array (matrix) 
/// \brief Create HDF5 file from 2D or 3D data arrays.
///
/// After Lignum simulation all data is assumed toi be in 2D or 3D arrays. LGMHDF5File can
/// then take that data and create a single HDF5 file for future analysis with R, python
/// or other HDF5 compatible tool. Thus LGMHDF5 does not (yet) have methods to read HDF5 files.
///
/// The datasets will be of NATIVE_DOUBLE type defined in HDF5. Thus user provides 2D or 3D arrays
/// of *double* type. Future versions may support HDF5 compound types. Column names are implemented
/// as HDF5 attributes.
///
/// The 3D data should be organised as `array[years][rows][columns]` where the
/// `rows` are Lignum trees, `columns` are data for a tree and `years` are simulation years.
/// For example `array[i][j]` retrieves data row for the `j`:th tree on the year ì`.
/// The 2D data is up to user. 
class LGMHDF5File{
public:
  /// Constructor prepares for datasets by creating HDF5 file. Previous existing file will be truncated.
  /// \exception DataSpaceIException
  /// \sa hdf5_file
  LGMHDF5File(const string& file_name);
  /// Close the H5File `hdf5_file`. \sa hdf5_file
  ~LGMHDF5File();  
  /// Create 3D array DataSet by giving explicitely the 3 dimensions and `data`
  /// \param years Years dimension
  /// \param rows Rows (trees) dimension
  /// \param cols Columns (data) dimension
  /// \param data The 3D array of type *double*
  /// \return -1 if error 0 otherwise
  /// \exception DataSetIException
  /// \note Technically 3D arrray `data` must be void*. It will be converted to 3D array of NATIVE_DOUBLE HDF5 dataset of given dimensions. 
  /// \sa writeDataSet
  int createDataSet(const string& dataset_name, int years, int rows, int cols, void* data);
  /// Create 2D array DataSet by giving explicitely the 2 dimensions and the `data`
  /// \param rows Rows dimension
  /// \param cols Columns dimension
  /// \param data The 2D array of type *double*
  /// \return -1 if error 0 otherwise
  /// \exception DataSetIException
  /// \note Technically 2D arrray `data` must be void*. It will be converted to 2D array of NATIVE_DOUBLE  HDF5 dataset of given dimensions.  
  /// \sa writeDataSet
  int createDataSet(const string& dataset_name, int rows, int cols, void* data);
  /// Create column names as HDF5 attribute. Column names can be of variable length strings.
  /// \param dset_name DataSet name for  which the column names will be given 
  /// \param attr_name Attribute name for the column names 
  /// \param col_names vector of column names 
  /// \return -1 if error 0 otherwise
  /// \exception AttributeIException
  /// \note HDF5 C++ interface does not (yet) support dimension scales which would be a more natural way to describe
  /// the meaning of each N dimensional array dimension.
  int createColumnNames(const string& dset_name, const string& attr_name,const vector<string>& col_names);
  /// Retrieve object names known to `hdf5_file`
  /// \return vector of object names 
  /// \note Object names include groups, dataspaces, datasets etc.
  /// \sa hdf5_file
  vector<string> getObjectNames();
  /// Close the H5File `hdf5_file`. \sa hdf5_file
  void close();
protected:
  /// Write the dataset to dataspace
  /// \param dset DataSet 
  /// \param data Lignum simulation data
  /// \return -1 if error 0 otherwise
  /// \exception DataSetIException
  /// \sa createDataSet
  int writeDataSet(const DataSet& dset, void* data);
private:
  H5File hdf5_file; /// HDF5 file containing simulation results
};
#endif
