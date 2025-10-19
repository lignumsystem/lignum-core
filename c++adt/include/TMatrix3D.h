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
    
  ///2D Matrix 
  template <class T>
    class TMatrix2D: public vector<vector<T> >{
    public:
    ///Default constructor, empty matrix
    TMatrix2D();
    ///Constructor, dimensions only 
    TMatrix2D(int x, int y);
    ///Constructior, initialize with copies of 't'
    TMatrix2D(int x, int y, const T& t);
    int rows()const {return xd;}
    int cols()const {return yd;}
    TMatrix2D<T>& init(const T& t);
    ///Resize clears the matrix first, i.e. data will be  lost
    ///\param x The number of the rows
    ///\param y The number of new columns
    ///\post No data in the matrix
    ///\return The new matrix
    ///\sa TMatrix2D::init TMatrix2D::append
    TMatrix2D<T>& resize(int x, int y);
    ///Append one row to the matrix
    ///\param v The new row as vector
    ///\pre The length of `v` must be the number of vector columns
    ///\return The new matrix
    ///\exception AppendException
    ///If length of \p v != \p yd throw AppendException
    TMatrix2D<T>& append(const vector<T>& v);
    private:
    int xd,yd; //rows and columns
  };
  ///3D Matrix
  template <class T>
    class TMatrix3D: public vector<TMatrix2D<T> >{
    public:
    ///Default constructor, empty 3D array
    TMatrix3D();
    ///Constructor, dimensions only 
    TMatrix3D(int x, int y, int z);
    ///Constructior, initialize with copies of 't'
    TMatrix3D(int x, int y, int z, const T& t);
    int rows()const {return xd;}
    int cols()const {return yd;}
    int zdim()const {return zd;}
    TMatrix3D<T>& init(const T& t);
    ///Clear the data first, i.e. data will be lost
    /// \post No data in the 3D array
    /// \sa TMarix3D::init
    TMatrix3D<T>& resize(int x, int y, int z);
    private:
    int xd; ///< Slices to 2D matrices
    int yd; ///< Rows in 2D matrices
    int zd; ///< Columns in 2D matrices
  };

}
#include <TMatrix3DI.h>
#endif


