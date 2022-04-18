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
#include <cmath>
#include <iostream>
#include <string>
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
  /// Base class containing one method to create TMatrix2D from Lignum function files
  /// TMatrix2D can be stored in HDF5 file
  class LGMHDF5{
  public:
    /// Create TMatrix2D representation from Lignum function files
    /// \param v Function definition as for ParametricCurve.
    /// \return TMatrix2D[N][2] where N is the number of (x,f(x)) points for  ParametricCurve
    /// \exception Undefined vector (i.e. v.size()==0) results TMatrxi2D[1][2] with the row [NaN NaN]
    /// \sa ParametricCurve
    TMatrix2D<double> getLignumFnData(const vector<double>& v);
  };
  /// \brief Create HDF5 dataset file from 2D or 3D data arrays, or from a STL string.
  ///
  /// After Lignum simulation all data is assumed to be in 2D or 3D arrays. LGMHDF5File can
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
  /// \note In C/C++ array indexing starts from 0. In the data analysis the indexing
  /// depends on the tool. For example R starts indexing from 1.
  /// \note R seems to use Fortran column-major ordering when reproducing dataframes from HDF5 file.
  /// Either accept this in data analysis or use matrix transposes to get the original dataset dimensions.
  /// \sa TMatrix2D TMatrix3D for 2D and 3D data arrays.
  class LGMHDF5File:public LGMHDF5{
  public:
    /// Constructor prepares the file `file_name` for datasets by creating HDF5 file.
    /// Previous existing file will be truncated.
    /// \exception DataSpaceIException
    /// \sa hdf5_file
    LGMHDF5File(const string& file_name);
    /// Close the H5File `hdf5_file`.
    /// \sa hdf5_file
    ~LGMHDF5File();
    /// Create group in HDF5 file
    /// \param name Group name
    /// \return -1 if error 0 otherwise 
    /// \exception FileIException GroupIException
    /// \note The group name is a Linux/Unix style directory path string. e.g. "/Groups/GroupA"
    int createGroup(const string& name);
    /// Create dataset form TMatrix3D<double>
    /// \param dataset_name Name of the dataset
    /// \param years Years dimension
    /// \param rows Rows (trees) dimension
    /// \param cols Columns (data) dimension
    /// \param data The 3D array of type *double*
    /// \return -1 if error 0 otherwise
    /// \exception DataSetIException
    int createDataSet(const string& dataset_name, int years, int rows, int cols, const TMatrix3D<double>& data);
    /// Create dataset from TMatrix2D<double> (e.g. stand level data)
    /// \param dataset_name Name of the dataset
    /// \param years Years  (rows) dimension
    /// \param cols Columns (data) dimension
    /// \param data The 3D array of type *double*
    /// \return -1 if error 0 otherwise
    /// \exception DataSetIException
    int createDataSet(const string& dataset_name, int years, int cols, const TMatrix2D<double>& data);
    /// Create 3D array DataSet by giving explicitely the 3 dimensions and `data`
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
    /// Create 2D array DataSet by giving explicitely the 2 dimensions and the `data`
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
    /// Create dataset of containg one variable length string, for example content of a command line.
    /// \param dataset_name Dataset name
    /// \param data Dataset string
    /// \return -1 if error 0 otherwise
    /// \exception DataSetIException
    int createDataSet(const string& dataset_name, const string& data);
    /// Create column names as HDF5 attribute. Column names can be of variable length strings.
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
    /// Create datasets from files that have data for ParametricCurve. Wild card search
    /// \pre The file format is as used in Lignum functions 
    /// \param pattern Wild card pattern string for `glob` (in glob.h)
    /// \param hdf5_group HDF5 group
    /// \param attr_name Attribute name for the column names
    ///	\param col_names Column names
    /// \note Traditionally the files for ParametricCurve have *.fun* suffix
    /// \sa glob
    int createFnDataSetsFromDir(const string& pattern, const string& hdf5_group, const string& attr_name, const vector<string>& col_names);
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
}//namepace cxxadt
#endif
