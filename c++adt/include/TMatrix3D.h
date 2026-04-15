/// \file TMatrix3D.h
/// \brief TMatrix2D and TMatrix3D matrices
///
///**TMatrix2D** implements 2D matrix *m* as a vector of rows where
///each row is a vector of elements. C style indexing of the matrix
///elements is realised with inheritance, both with bracket notation and
///with \c at method that checks the validity of indexing.
///For example the matrix element \c e is retrieved  \c e = \c m2D[i][j].
///
///**TMatrix3D** implements 3D matrix as a vector of TMatrix2D elements.
///The matrix element \c e is retrieved as \c e = \c m3D[i][j][k].
///
///Note that there are only matrix dimensions as data members in
///TMatrix2D and TMatrix3D. These two classes *are* vectors of vectors using inheritance. 
///This approach  can  be expanded  to N-dimensional  matrices.
///
///The implementation  is inspired  by Breymann (Chapter  9).
///The  classes TMatrix2D and  TMatrix3D demonstrate the use  of STL, its classes and algorithms,
///and the  importance  of  clear  understandable  implementations  at  the
///possible small cost of runtime efficiency.
///
///To  test the  TMatrix3D class there is a *matrix3d.cc* file in src-directory.

#ifndef MATRIX3D_H
#define MATRIX3D_H

#include <sstream>
#include <vector>
#include <algorithm>
#include <exception>

using namespace std;
///\file TMatrix3D.h


namespace cxxadt{
  ///\brief Throw and catch exceptions in matrix append operation
  class AppendException:public std::exception{
  public:
    ///\brief Construct matrix append exception
    ///\param msg User defined message string
    ///\param r Number of rows in matrix
    ///\param c Number of columns in matrix
    ///\param l Length of the vector to be appended
    AppendException(const string& msg,int r, int c, int l)
    :rows(r),cols(c),length(l),message(msg){
      constructMessage();
    }
    ///\brief Message string
    ///\return Character string of user defined exception message
    virtual const char* what() const noexcept{
      return message.c_str();
    }
    virtual ~AppendException() noexcept{}
  private:
    ///User defined message
    void constructMessage(){
       std::stringstream ss;
       ss << " Rows " << std::to_string(rows) << " Cols " << std::to_string(cols)
	  << " Vector length " << std::to_string(length) <<endl;
       message+=ss.str();
    }
    int rows;
    int cols;
    int length;
    string message;
  };

  class TMatrixInitSizeError{
  public:
    TMatrixInitSizeError(const vector<int>& v)
    :vdim(v){}
  private:
    std::vector<int> vdim;
  };
  
  ///2D Matrix of rows and columns
  template <class T>
  ///\brief 2D matrix
    class TMatrix2D: public vector<vector<T> >{
    public:
    ///\brief Constructor, empty matrix
    TMatrix2D();
    ///\brief Constructor, dimensions only
    ///\param x Rows
    ///\param y Columns
    TMatrix2D(int x, int y);
    ///\brief Constructor, initialize with copies of 't'
    ///\param x Rows
    ///\param y Columns
    ///\param t Vector element
    TMatrix2D(int x, int y, const T& t);
    ///\brief Constructor, initialize from vector \p v
    ///\param x Rows
    ///\param y Cols
    ///\param v Data vector
    ///\pre \f$ x \times y = |v|\f$
    ///\pre \f$ y = |v| \div x \f$ (Rows and columns must match the size of the vector \p v)
    ///\exception TMatrixInitSizeError if preconditon violation
    TMatrix2D(int x, int y, const vector<T>& v);
    ///\brief Number of rows
    ///\retval xd Number of rows
    int rows()const {return xd;}
    ///\brief Number of columns
    ///\retval yd Number of columns
    int cols()const {return yd;}
    ///\brief Initialize matrix with copies of \p t.
    ///\retval self Initialized matrix
    TMatrix2D<T>& init(const T& t);
    ///Resize clears the matrix first, i.e. data will be  lost
    ///\param x The number of the rows
    ///\param y The number of new columns
    ///\post No data in the matrix
    ///\retval self Resized matrix
    ///\sa TMatrix2D::init TMatrix2D::append
    TMatrix2D<T>& resize(int x, int y);
    ///\brief Append one row to the matrix
    ///\param v The new row as vector
    ///\pre The length of `v` must be the number of vector columns
    ///\retval self Resized matrix with new row
    ///\exception AppendException If length of \p v != \p yd throw AppendException
    TMatrix2D<T>& append(const vector<T>& v);
    private:
    ///\brief Rows and columns
    int xd,yd;
  };
  ///\brief 3D Matrix
  ///
  ///A stack of 2D matrices with rows, columns and depth (or layers).
  template <class T>
    class TMatrix3D: public vector<TMatrix2D<T> >{
    public:
    ///\brief Constructor, empty 3D matrix
    TMatrix3D();
    ///\brief Constructor, dimensions only
    ///\param x Rows
    ///\param y Columns
    ///\param z Depth
    TMatrix3D(int x, int y, int z);
    ///\brief Constructior, initialize with copies of \p t
    ///\param x Rows
    ///\param y Columns
    ///\param z Depth
    ///\param t Matrix element
    TMatrix3D(int x, int y, int z, const T& t);
    //\brief Constructor, intialize with vector \p v
    ///\param x Rows
    ///\param y Columns
    ///\param z Depth
    ///\param v Vector
    ///\pre \f$ x \times y \times z  = |v|\f$
    ///\pre \f$ |v| \bmod x = 0 \f$
    ///\pre \f$ y*z \bmod (|v| \div x) = 0\f$
    ///\exception TMatrixInitSizeError if preconditon violation
    TMatrix3D(int x, int y, int z,const vector<T>& v);
    ///\brief Number of rows (1st dimension)
    ///\retval xd 1st dimension
    int rows()const {return xd;}
    ///\brief Number of columns (2nd dimension)
    ///\retval yd 2nd dimension
    int cols()const {return yd;}
    ///\brief Number of layers (3rd dimension)
    ///\retval zd 3rd dimension
    int zdim()const {return zd;}
    ///\brief Number of layers (3rd dimension)
    ///
    ///Alias for zdim()
    ///\retval zd 3rd dimension
    int layers()const{return zdim();}
    ///\brief Initialize the matrix with copies of \p t.
    ///\pre Matrix must have dimensions defined 
    ///\retval self Initialized matrix
    TMatrix3D<T>& init(const T& t);
    ///\brief Resize matrix
    ///
    ///Clear data first, i.e. data will be lost
    ///\retval self Initialized matrix
    ///\post Data undefined in the 3D matrix
    ///\sa TMarix3D::init()
    TMatrix3D<T>& resize(int x, int y, int z);
    private:
    int xd; ///< 1st dimension, slices to 2D matrices
    int yd; ///< 2nd dimension, rows in 2D matrices
    int zd; ///< 3rd dimension, columns in 2D matrices
  };

}
#include <TMatrix3DI.h>
#endif


