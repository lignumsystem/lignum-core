#ifndef PARALLELOGRAM_H
#define PARALLELOGRAM_H
#include <cstdlib>
#include <algorithm>
#include <Point.h>
#include <PositionVector.h>
using namespace cxxadt;
/// \file Parallelogram.h
/// \brief Leaf shape as Parallelogram.
///
/// Implements Parallelogram for a "diamond shape" leaf.
/// The interface includes constructors, resizing the Parallelogram area,
/// rotations in 3D space and detection of line (light ray) - Parallelogram (leaf) intersection.
/// The inteface is compatible with BroadLeaf.
/// \sa cxxadt::Triangle cxxadt::Ellipse Lignum::BroadLeaf
/// \note Parts of the documentation contain basic LaTeX mathematical typesetting.
/// If \f(\LaTeX \f) is installed Doxygen should automatically render those parts in the final document.
/// MacPorts has \f(\TeX \f) Live package.
/// \todo Check for Lignum::BroadLeaf compatibilty.

namespace cxxadt{
  ///\brief Parallelogram for diamond shaped leaves.
  ///
  ///Parallelogram area \f$A = |\overrightarrow{ab}||\overrightarrow{ad}\sin(\alpha) \f$  and \f$ \alpha = \overrightarrow{ab} \angle \overrightarrow{ad} \f$   
  ///The Parallelogram normal \f$\vec{N} = \overrightarrow{ad} \times \overrightarrow{ab} \f$ pointing upwards and normalised.  
  class Parallelogram{
  public:
    ///\brief Create parallelogram with four clockwise corner points
    ///\pre The points a,b,c and d are in clockwise order
    ///\param a nadir point (leaf petiole end)
    ///\param b 2nd point
    ///\param c apex point
    ///\param d 4th point
    Parallelogram(const Point& a,const Point& b, const Point& c, const Point& d);
    ///\brief Create parallelogram with three clockwise corner points
    ///\pre The points a,b,and d are in clockwise order
    ///\param a nadir point (leaf petiole end)
    ///\param b 2nd point
    ///\param d 4th point
    ///\post Point \f$ c =  \vec{b}+\overrightarrow{ad} \f$
    Parallelogram(const Point& a,const Point& b,const Point& d);
    ///\brief Create parallelogram given intial (leaf) area.
    ///\param A parallelogram area
    ///\param a parallelogram nadir point (leaf petiole end)
    ///\param dp direction (of a petiole) 
    ///\param alpha The angle \f$ \alpha = \overrightarrow{ab} \angle \overrightarrow{ad} \f$
    ///\param ratio length ratio \f$ |\overrightarrow{ab}| / |\overrightarrow{ad}| \f$.
    ///\remark For symmetry the \p ratio is 1 which is probably the best choice for a diamond leaf.
    ///\param is_leaf_normal Default *true*.  
    ///\remark If *true* set \f$ \vec{N} = \overrightarrow{d_p} \f$. If *false* set \f$\ \vec{N} \perp \overrightarrow{d_p} \f$ and pointing upwards.  
    ///In the latter case \f$\overrightarrow{d_p} \f$ is e.g. petiole or bud direction.
    ///
    ///\post The angle \f$ \alpha = \overrightarrow{ab} \angle \overrightarrow{ad} \f$, symmetrically by \f$ (\alpha/2,-\alpha/2) \f$
    ///away from \f$\overrightarrow{ac} \f$
    ///\note The final orientation of Parallelogram (leaf) is implementation depended \sa pitch roll turn
    Parallelogram(double A,const Point& a, const PositionVector& dp, double alpha, double ratio, bool is_leaf_normal=true);
    ///\brief Rotation around \f$\overrightarrow{bd} \f$ axis (pitch up or down) at nadir point a 
    ///\param angle Magnitude of rotation in radians
    ///\note Convenience method to Parallelogram::rotate
    ///\sa rotate
    Parallelogram& pitch(double angle);
    ///\brief Rotation around \f$\overrightarrow{ac} \f$ axis (roll left or right) at nadir point *a*
    ///\param angle Magnitude of rotation in radians
    ///\note Convenience method to Paeallelogram::rotate
    ///\sa rotate
    Parallelogram& roll(double angle);
    ///\brief Rotation around Parallelogram normal \f$\vec{N} \f$ (turn left or right) at nadir point *a*
    ///\param angle Magnitude of rotation in radians
    ///\note Convenience method to Parallelogram::rotate
    ///\sa rotate
    Parallelogram& turn(double angle);
    ///\brief Resize Parallelogram.
    ///
    ///See Parallelogram 3rd constructor to set Parallelogram dimensions.
    ///\param A New size
    ///\post The nadir point *a* remains in place.
    ///\note Convenience method to Parallelogram::resize
    ///\sa resize 
    Parallelogram& setArea(double A);
    ///Parallelogram area
    double getArea()const{return A;}
    ///Parallelogram normal vector
    PositionVector getNormal()const{return N;}
    ///Center point
    Point getCenterPoint()const;
    ///\brief Line (light beam) intersection with parallelogram (leaf).
    ///
    ///The algorithm works in three steps:
    ///-# Simple heuristics:   
    ///  -# For out purposes check observation point is strictly below Parallelogram (leaf) maximum height.    
    ///  -# Check if intersection point exists (line not parallel with plane).    
    ///-# Calculate line - plane intersection point.
    ///-# Check if the plane intersection point is inside the parallelogram.
    ///\param o Observer point (center point of a another leaf)
    ///\param b The line (light beam) direction in 3D space
    ///\return *true* if Parallelogram intersection, *false* if no intersction 
    bool intersectShape(const Point& o, const PositionVector& b)const;
    ///\brief Calculate line (light beam) - plane intersection point.
    ///\pre The intersection point with the line (light beam) - plane (defined by the Parallelogram) must exist.
    ///\param o the observation point
    ///\param b the line direction in 3D space
    ///\return The intersection point
    ///\sa intersectShape
    Point intersectionPoint(const Point& o, const PositionVector& b)const;
    ///The angle in radians between vectors \f$\overrightarrow{ab} \f$ and \f$\overrightarrow{ad} \f$
    double getAlpha()const;
    ///Retrieve the nadir point *a*
    ///\sa getB getC getD
    Point getA()const{return a;}
    Point getB()const{return b;}
    Point getC()const{return c;}
    Point getD()const{return d;}
    ///Maximum Z-coordinate of corner points 
    double getMaxZ()const;
  private:
    ///\brief Determine if a point is inside Parallelogram.
    ///\pre The intersection point with  line (beam) - plane (defined by the Parallelogram) must exist.
    ///\param p Point in the plane defined by the Parallelogram
    ///\return *true* if *p* inside Parallelogram, *false* if not
    ///\sa intersectShape
    bool insideShape(const Point& p)const;
    ///Resize parallelogram
    ///\param A New area
    ///\param alpha The angle in radians between vectors \f$\overrightarrow{ab} \f$ and \f$\overrightarrow{ad} \f$
    ///\param ratio The ratio \f$|\overrightarrow{ab}| / |\overrightarrow{ad}| \f$
    Parallelogram&  resize(double A,double alpha, double ratio);
    ///Rotation in 3D space
    ///\param p Point in 3D space 
    ///\param d Direction vector
    ///\param angle Magnitude of rotation in radian
    ///\note Point *p* (most likely the nadir point *a*) and \f$|\vec{d}|  \f$ define the axis of rotation
    Parallelogram& rotate(const Point& p, const PositionVector& d,double angle);
    ///\f$|\overrightarrow{ab}|\f$ (vector length) 
    double lengthAB(){return (a||b);}
    ///\f$|\overrightarrow{ad}|\f$ (vector length)
    double lengthAD(){return (a||d);}
    Point a;///< The parallelogram nadir point where petiole will be attached 
    Point b;///< Second corner point clockwise
    Point c;///< Third (apex) corner point clockwise (\f$ c = \overrightarrow{ab} + \overrightarrow{ad} \f$)
    Point d;///< Fourth corner point clockwise
    double A;///< Parallelogram area 
    PositionVector N;///< Parallelogram normal (\f$ \vec{N} = \overrightarrow{ad} \times \overrightarrow{ab},|\vec{N}| = 1 \f$)
  };
}//end namespace
#endif
