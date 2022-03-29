#ifndef MATRIX3D_H
#define MATRIX3D_H

#include <vector>
#include <algorithm>

using namespace std;

/**********************************************************************
 *TMatrix3D implements 3D matrix where  indexing goes in C style. Thus*
 *given  TMatrix3D<T> m3,  m[x][y][z] gives  the element  T in  a cell*
 *indexed by  x,y and  z. The implementation  is inspired  by Breymann*
 *(Chapter  9.). At  first  user  may wonder  where  are the  indexing*
 *operators but  they are  provided by inheritance.   Indexed checking*
 *indexing is provided  by at() method. With the  class TMatrix3D<T> I*
 *want to demonstrate the use  of STL, its classes and algorithms, and*
 *the  importance  of  clear  understandable  implementations  at  the*
 *possible cost of small runtime efficiency. A correct program is more*
 *important  than a  fast program.   The approach  here can  be easily*
 *expanded  to N dimensional  matrices.  To  test the  TMatrix3D class*
 *there is a "matrix3d.cc" file in src-directory.                     *
 *********************************************************************/
namespace cxxadt{

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
    /// Resize clears the matrix first, i.e. data will be  lost
    /// \post No data in the matrix
    /// \sa TMatrix2D::init
    TMatrix2D<T>& resize(int x, int y);
    private:
    int xd,yd; //rows and columns
  };
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
    int xd,yd,zd; //rows (submatrix), columns and z-dimension
  };

}
#include <TMatrix3DI.h>
#endif


