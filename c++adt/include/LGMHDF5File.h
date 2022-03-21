/// \file LGMHDF5File.h
/// The interface to HDF5 c++ library to create HDF5 files for Lignum simulations.
///
/// The further analysis of data is meant to be made with R, Python or some other
/// high level tool supporting HDF5 files. To retrieve information from a HDF5
/// file one can also use utility tools from HDF5 installation, e.g.:
/// + h5ls: List the objects (datasets, groups etc.) in a HDF5 file
/// + h5dump: Dump the content of a HDF5 file
/// + h5cc, h5c++, h5fc: Compile HDF5 applications
/// Also:
/// + HDFView: Tool for browsing and editing HDF5 files 
#ifndef LGMHDF5FILE_H
#define LGMHDF5FILE_H
#include <iostream>
#include <string>
#include <vector>
#include <H5Cpp.h>
using namespace H5;
using namespace std;

/// DataSpace RANKS
const int DSPACE_RANK3 = 3; /// 3D array
const int DSPACE_RANK2 = 2; /// 2D array (matrix) 
/// After Lignum simulation all data is assumed toi be in 2D or 3D array. LGMHDF5File can
/// then take that data and create HDF5 file for future analysis.
/// For ease of implementation and use with HDF5 the dataset must be of NATIVE_DOUBLE
/// type defined in HDF5. Thus user provides 2D or 3D array of double type.
/// Future versions may support HDF5 compound types.
/// The 3D data should be organised as `array[years][rows][columns]` where the
/// `rows` are trees, `columns` data for a tree and `years` are simulation years.
/// For example `array[i][j]` retrieves data row for the `j`:th tree on the year ì`.
/// The 2D data is up to user.
class LGMHDF5File{
public:
  /// Constructor prepares for dataset by creating corresponding dataspace.
  /// The previous existing file will be truncated.
  /// \exception DataSpaceIException
  LGMHDF5File(const string& file_name);
  /// Close H5File `hdf5_file. \sa hdf5_file
  ~LGMHDF5File();  
  /// Create 3D array DataSet by giving explicitely the 3 dimensions and `data`
  /// \param years Years dimension
  /// \param rows Rows (trees) dimension
  /// \param cols Columns (data) dimension
  /// \param data The 3D array of type *double*
  /// \return -1 if error 0 otherwise
  /// \exception DataSetIException
  /// \sa writeDataSet
  int createDataSet(const string& dataset_name, int years, int rows, int cols, void* data);
  /// Create 2D array DataSet by giving explicitely the 2 dimensions and the `data`
  /// \param rows Rows dimension
  /// \param cols Columns dimension
  /// \param data The 2D array of type *double*
  /// \return -1 if error 0 otherwise
  /// \exception DataSetIException
  /// \sa writeDataSet
  int createDataSet(const string& dataset_name, int rows, int cols, void* data);
  /// Create column names as HDF5 attribute
  /// \param dset_name DataSet name
  /// \param attr_name Attribute name
  /// \param col_names vector of column names (column names can be of variable length strings)
  /// \return -1 if error 0 otherwise
  /// \exception AttributeIException
  /// \note HDF5 C++ interface does not (yet) support dimension scales which would be more natural way to describe
  /// meaning of N dimensional array dimensions.
  int createColumnNames(const string& dset_name, const string& attr_name,const vector<string>& col_names);
  /// Retrieve object names known to `hdf5_file`
  /// \return vector of object names 
  /// \note Object names include groups, dataspaces, datasets etc.
  /// \sa hdf5_file
  vector<string> getObjectNames();
  /// Close H5File `hdf5_file`. \sa hdf5_file
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
