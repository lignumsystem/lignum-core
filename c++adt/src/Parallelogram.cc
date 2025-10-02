#include <Parallelogram.h>
/// \file Parallelogram.cc
/// Implementation of Parallelogram.

namespace cxxadt{
  
  Parallelogram::Parallelogram(const Point& a1, const Point& b1, const Point& c1, const Point& d1)
    :a(a1),b(b1),c(c1),d(d1)
  
  {
    PositionVector a0(a);
    PositionVector b0(b);
    PositionVector d0(d);
    PositionVector ab = b0-a0;
    PositionVector ad = d0-a0;
    double cos_alpha = Dot(ab.normalize(),ad.normalize());
    double alpha = acos(cos_alpha);
    A = lengthAB()*lengthAD()*sin(alpha);
    N = Cross(ad,ab);
    N.normalize();
  }

  Parallelogram::Parallelogram(const Point& a1, const Point& b1, const Point& d1)
    :a(a1),b(b1),d(d1)
  {
    PositionVector a0(a);
    PositionVector b0(b);
    PositionVector d0(d);
    PositionVector ab = b0-a0;
    PositionVector ad = d0-a0;
    PositionVector c0 = b0+ad;
    this->c=Point(c0);
    double cos_alpha = Dot(ab.normalize(),ad.normalize());
    double alpha = acos(cos_alpha);
    A = lengthAB()*lengthAD()*sin(alpha);
    N = Cross(ad,ab);
    N.normalize();
  }

  Parallelogram::Parallelogram(double A1,const Point& a1, const PositionVector& dp, double alpha, double ratio_ab, bool ndir)
    :a(a1),A(A1)
  {
    PositionVector up(0,0,1);
    PositionVector dir_tmp(dp);
    PositionVector d1; 
    PositionVector ab0;
    PositionVector ad0;

    /// **Find Parallelogram orientation**    
    /// 1. Parameter *ndir* = *true*:   
    /// Use parameter \f$ \overrightarrow{dp} \f$  as Parallelogram (leaf) normal
    /// 2. Parameter *ndir* = *false*:
    /// Interpret \f$ \overrightarrow{dp} \f$  as bud or leaf petiole direction (for example).   
    /// Orient Parallelogram normal: \f$ \vec{N}  \perp \overrightarrow{dp} \f$:   
    /// Find horizontal vector \f$ \overrightarrow{d_1} = \overrightarrow{dp} \times \overrightarrow{up} \f$.   
    /// Find \f$ \vec{N} \f$ by rotating \f$ \overrightarrow{dp} \f$ around \f$ \overrightarrow{d_1}\f$ by \f$ -\pi/2 \f$.     
    /// 3.  Find directions \f$ \hat{a_b} \f$ *and* \f$ \hat{a_d} \f$:     
    /// Rotate \f$ \overrightarrow{dp} \f$ symmetrically \f$ (\alpha/2,-\alpha/2) \f$ around \f$\vec{N}\f$.
    /// 4. Special cases:    
    /// 4.1 Vector \f$ \overrightarrow{dp} \parallel \overrightarrow{up} \Rightarrow\f$ Use parameter *a1* as direction. We know the quadrant.    
    /// 4.2 Parameter *a1* also on Z-axis \f$ \Rightarrow \f$ Choose X-axis as horixontal axis. No information to work with.
   if (ndir == false){
      double a1z_eps = (1.0-fabs(PositionVector(a1).normalize().getZ()));
      double dirz_eps = (1.0-fabs(PositionVector(dp).normalize().getZ()));
      //Very special case: no reference to use as direction
      if (a1z_eps <= R_EPSILON && dirz_eps <= R_EPSILON){
	//Choose reference (X-axis)
	dir_tmp = PositionVector(1,0,0);
      }
      //Use *a1* as reference 
      else if (dirz_eps <= R_EPSILON){
	dir_tmp = PositionVector(a1);
      }
      /// \internal
      /// \snippet{lineno} Parallelogram.cc Normal
      // [Normal]
      //Finding parallelogram normal
      d1 = Cross(up,dir_tmp);
      //Parallelogram normal d90 is pointing up perpendicular to **dir** and **up** vectors
      PositionVector d90 = PositionVector(dir_tmp).normalize().rotate(Point(0,0,0),d1,-PI_VALUE/2.0);
      // [Normal]
      /// \endinternal
      PositionVector tmp1(dir_tmp);
      /// \internal
      /// \snippet{lineno} Parallelogram.cc ab0ad0
      // [ab0ad0]
      //Unit vectors ab0 and ad0
      //Left turn
      ab0 = tmp1.normalize().rotate(Point(0,0,0),d90,alpha/2.0);
      PositionVector tmp2(dir_tmp);
      //Right turn
      ad0 = tmp2.normalize().rotate(Point(0,0,0),d90,-alpha/2.0);
      // [ab0ad0]
      /// \endinternal
    }
    else{
      //ndir=true then *dp* is interpreted as leaf normal
      //User *a1* as the symmetry of rotation, at least we know the quadrant
      PositionVector tmp1(dir_tmp);
      //Left turn
      ab0 = tmp1.normalize().rotate(Point(0,0,0),a1,alpha/2.0);
      PositionVector tmp2(dir_tmp);
      //Right turn
      ad0 = tmp2.normalize().rotate(Point(0,0,0),a1,-alpha/2.0);
    }
    /// **Solution for** \f$ \overrightarrow{ab} \f$ **and** \f$ \overrightarrow{ad} \f$:  
    /// 1. Denote \f$ \mathit{L1} = |\overrightarrow{ab}| \f$ and \f$\mathit{L2} = |\overrightarrow{ad}| \f$.  
    /// 2. Let \f$ r = \mathit{L1}/\mathit{L2} \f$ then \f$ \mathit{L1} = r\mathit{L2} \f$ and \f$ \mathit{L2}=\mathit{L1}/r \f$.   
    /// 3. \f$ A = \mathit{L1L2}\sin(\alpha) = \mathit{rL2^2}\sin(\alpha) \f$.   
    /// \f$ \mathit{L2}^2 = A/(r\sin(\alpha)) \f$.         
    /// \f$ \mathit{L2} = \sqrt{A/(r\sin(\alpha))} \f$.   
    /// 4. Similarly \f$ \mathit{L1} = \sqrt{rA/\sin(\alpha)} \f$.   
    /// \internal
    /// \snippet{lineno} Parallelogram.cc L1L2
    // [L1L2]
    double L1 = sqrt(A1*ratio_ab/sin(alpha));
    double L2 = sqrt(A1/(ratio_ab*sin(alpha)));
    PositionVector ab = L1*ab0;
    PositionVector ad = L2*ad0;
    // [L1L2]
    /// \endinternal
    
    // Point *b* is defined by **a**+**ab**
    this->b = Point(PositionVector(a)+ab);
    // Point *d* is defined by vector **a**+**ad**
    this->d = Point(PositionVector(a)+ad);
    // Point *c* is defined by vector **b**+**ad**
    this->c = Point(PositionVector(b)+ad);
    // Parallelogram (leaf) normal as Cross(**ad**,**ab**) makes the vector pointing up
    N = Cross(ad,ab);
    N.normalize();
  }

  Parallelogram& Parallelogram::rotate(const Point& p, const PositionVector& dir,double angle)
  {
    PositionVector av(this->a);
    PositionVector bv(this->b);
    PositionVector cv(this->c);
    PositionVector dv(this->d);
    av.rotate(p,dir,angle);
    bv.rotate(p,dir,angle);
    cv.rotate(p,dir,angle);
    dv.rotate(p,dir,angle);
    this->a = Point(av);
    this->b = Point(bv);
    this->c = Point(cv);
    this->d = Point(dv);
    PositionVector ab = PositionVector(b)-PositionVector(a);
    PositionVector ad = PositionVector(d)-PositionVector(a);
    N = Cross(ad,ab);
    N.normalize();
    return *this;
  }

  Parallelogram& Parallelogram::pitch(double angle)
  {
    PositionVector bd = PositionVector(b)-PositionVector(d);
    rotate(this->a,bd,angle);
    return *this;
  }

  Parallelogram& Parallelogram::roll(double angle)
  {
    PositionVector ac = PositionVector(c)-PositionVector(a);
    rotate(this->a,ac,angle);
    return *this;
  }

  Parallelogram& Parallelogram::turn(double angle)
  {
    rotate(this->a,getNormal(),angle);
    return *this;
  }
  
  Parallelogram& Parallelogram::setArea(double A)
  {
    double alpha = getAlpha();
    double ratio = lengthAB()/lengthAD();
    resize(A,alpha,ratio);
    return *this;
  }

  Parallelogram&  Parallelogram::resize(double A1,double alpha, double ratio)
  {
    PositionVector ab0 = PositionVector(b)-PositionVector(a);
    ab0.normalize();
    PositionVector ad0 = PositionVector(d)-PositionVector(a);
    ad0.normalize();
    // Denote L1 = |**ab**| and L2 = |**ad**|. ratio = L1/L2 then L1 = L2*ratio and L2=L1/ratio
    // A = L1*L2*sin(alpha) = L2*ratio*L2*sin(alpha)
    // L2^2 = A/(ratio*sin(alpha)) and L2 = sqrt(A/ratio*sin(alpha))
    // Equally: A = L1*(L1/ratio)*sin(alpha)
    // L1^2 = A*ratio/sin(alpha) and L1 = sqrt(A*ratio/sin(alpha))
    double L1 = sqrt(A1*ratio/sin(alpha));
    double L2 = sqrt(A1/(ratio*sin(alpha)));
    PositionVector ab = L1*ab0;
    PositionVector ad = L2*ad0;
    // Point *b* is defined by **a**+**ab**
    this->b = Point(PositionVector(a)+ab);
    // Point *d* is defined by vector **a**+**ad**
    this->d = Point(PositionVector(a)+ad);
    // Point *c* is defined by vector **b**+**ad**
    this->c = Point(PositionVector(b)+ad);
    this->A = A1;
    return *this;
  }

  Point Parallelogram::getCenterPoint()const
  {
    Point center = (this->a+this->c)/2.0;
    return center;
  }

  bool Parallelogram::intersectShape(const Point& o, const PositionVector& beam)const
  {
    //Check if the observation point is strictly below above the Parallelogram.
    double o_maxz = o.getZ();
    double maxz = getMaxZ();
    //If above return false
    if (o_maxz > maxz){
      return false;
    }
    //Check if beam direction parallel to the Parallelogram plane
    double cosalpha = Dot(PositionVector(beam).normalize(),N);
    if (fabs(cosalpha)  < EPS15){
      return false;
    } 
    /// \sa intersectionPoint Calculate intersection point
    Point p_intersect = intersectionPoint(o,beam); 
    /// \sa insideShape Check if the point is inside Parallelogram
    bool p_inside = insideShape(p_intersect);
    if (p_inside == true){
      return true;
    }
    else{
      return false;
    }
  }

  Point Parallelogram::intersectionPoint(const Point& o, const PositionVector& l)const
  {
    /// \par Calculation line - plane intersection
    ///
    /// Given observation point  \f$ \mathit{o} \f$ is below the Parallelogram (leaf) calculate the intersection point.  
    /// With vector notation a plane is defined by a set of all points \f$ P \f$ that satisfy
    /// the equation \f$ (P - p_0) \cdot \vec{N} \f$  where \f$ p_0 \f$ is
    /// a point in the plane and \f$ \vec{N} \f$ is the normal to the plane.   
    /// The set of all points \f$ P_l \f$ on a line can be defined as \f$ P_l = l_0 + d\hat{l} \f$
    /// where \f$l_0 \f$ is a point on the line, \f$\hat{l} \f$ is a unit vector defining the
    /// direction of the line and \f$ \mathit{d} \f$  is a scalar.
    ///
    /// Substituting \f$ P \f$ for the line equation in the plane equation gives \f$ (l_0 + d\hat{l}-p_0) \cdot \vec{N})=0 \f$.
    /// Expanding gives \f$(\hat{l} \cdot d\vec{N}) + (l_0-p0) \cdot \vec{N} = 0 \f$  and solving for \f$ d \f$ gives
    /// \f$ d = (p_0-l_0) \cdot \vec{N} / \hat{l} \cdot \vec{N} \f$.
    /// When denominator \f$ \hat{l} \cdot \vec{N} \neq 0 \f$ we can solve for \f$ d \f$ and find the line-plane intersection point (Wikipedia).
    ///+ Geometric interpretation: when denominator \f$ \hat{l} \cdot \vec{N} = 0 \f$ then \f$ d \f$ is undefined. The line is perpendicular
    ///  plane normal and parallel with the plane. When the numerator is 0 the line is in the plane.
    ///  For our purposes (Parallelogram as a leaf model) we skip both of these cases.
    ///  

    //Intersection point must exist
    double dot = Dot(N,l);
    //The intersection point with the plane defined by the Parallelogram exists.
    //The nadir point is on the plane
    Point p0(getA());
    //The observation point is on the line
    Point l0(o);
    /// \internal
    /// The distance \f$ \mathit{d} \f$ from the observation point \f$ \mathit{o} \f$ to
    /// the intersection point is \f$ d = (p_0-o)\cdot\vec{N}/\hat{l} \cdot\vec{N} \f$,
    /// where \f$ {p_0} \f$ is the Parallelogram nadir point. Finally, the point of intersection is \f$ p = o+d\hat{l} \f$.
    /// \snippet{lineno} Parallelogram.cc PI
    // [PI]
    PositionVector p1(p0-l0);
    double d =  Dot(N,p1)/dot;
    Point p_intersection = Point(PositionVector(l0)+(d*l));
    // [PI]
    ///\endinternal
    return p_intersection;
  }

  bool Parallelogram::insideShape(const Point& p)const
  { //Move parallelogram and p to origo
    Point b0 = (getB()) - (getA());
    Point d0 = (getD()) - (getA());
    Point p0 = p - (getA());
    ///\internal
    ///The equation \f$ p = t_1\overrightarrow{ab}+t_2\overrightarrow{ad} \f$ defines all the points in Parallelogram.
    ///We can expand the equation :
    ///\f{eqnarray*}{
    /// p_x = t_1\overrightarrow{ab}_x+t_2\overrightarrow{ad}_x\\
    /// p_y = t_1\overrightarrow{ab}_y+t_2\overrightarrow{ad}_y\\
    /// p_z = t_1\overrightarrow{ab}_z+t_2\overrightarrow{ad}_z
    /// \f}
    ///With three equations and two unknowns we can solve for \f$ t_1 \f$ and \f$ t_2 \f$.							       
    ///\snippet{lineno} Parallelogram.cc IN
    // [IN]
    //Solution for t1
    double t1 = (p0.getY()-(p0.getX()*d0.getY()/d0.getX()))/(b0.getY()-((b0.getX()*d0.getY())/d0.getX()));
    //Solution for t2
    double t2 = (p0.getX()-t1*b0.getX())/d0.getX();
    // [IN]
    ///\endinternal
    ///If \f$ t_1 \f$ and \f$ t_2 \in \left[0,1\right] \f$  the point \f$ p \f$ is strictly inside parallelogram.
    ///Note the solutions \f$ t_1 \f$ and \f$ t_2 \f$ for consider the projection of the Parallelogram onto \f$ \mathit{xy} \f$ plane.
    ///If the point \f$ p \f$ is inside the projection then it is inside the parallelogram.
    if ((t1 >= 0.0) && (t1 <= 1.0) && (t2 >= 0.0) && (t2 <= 1.0)){
      return true;
    }
    else{
      return false;
    }
  }
  double Parallelogram::getAlpha()const
  {
    PositionVector ab = PositionVector(b)-PositionVector(a);
    PositionVector ad = PositionVector(d)-PositionVector(a);
    double cos_alpha = Dot(ab.normalize(),ad.normalize());
    double alpha = acos(cos_alpha);
    return alpha;
  }

  double Parallelogram::getMaxZ()const
  {
    double maxz = max(a.getZ(),b.getZ());
    maxz = max(maxz,c.getZ());
    maxz = max(maxz,d.getZ());
    return maxz;
  }
      
}//end namespace

