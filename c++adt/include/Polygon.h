#ifndef POLYGON_H
#define POLYGON_H
#include <math.h>
#include <numeric>
using namespace std;
#include <Point.h>


namespace cxxadt{ 

    class PolygonAreaFunctor{  
    public:
	PolygonAreaFunctor(const Point& p);
	double operator()(double id,const Point& p);
    private:
	double xi;
	double yi;
    };
 
    class PolygonCentroidFunctor{
    public:
	PolygonCentroidFunctor(const Point& p);
	Point& operator()(Point& id,const Point& p);
    private:
	double xi;
	double yi;
    };

    /*****************************************************************
     *Compute the area of a  closed planar polygon chain.  The points*
     *of  the   polygon  must  be   Point  class  (where  z   is  now*
     *redundant). The polygon itself can  be any STL sequence: a list*
     *or a vector.  Note the algorithm checks if the polygon chain is*
     *closed or not. If not the first element will be inserted as the*
     *last  element.    As  an  example   given  a  list   of  points*
     *[(4,6,0),(4,2,0),(0,8,0)]  or [(4,6,0),(4,2,0),(0,8,0),(4,6,0)]*
     *the area will be 8.                                            *
     *****************************************************************/
    template <class Polygon>
	double PolygonArea(Polygon& plgn)
	{
	    const Point& p1 = plgn.front();
	    const Point& p2 = plgn.back();
	    //To implement a straightforward algorithm ensure that the
	    //polygon is closed (i.e., first == last)
	    if (p1 != p2){
		plgn.push_back(p1);
	    }
	    PolygonAreaFunctor f(p1);
	    //depending  orientation of the  polygon chain  the result
	    //can  be   positive  or  negative   (counterclockwise  or
	    //clockwise respectively) 
	    return 0.5*fabs(accumulate(plgn.begin(),plgn.end(),0.0,f));
	}

    /*****************************************************************
     *Compute the center of the  polygon (center of mass). In general*
     *the centroid coordinates (x,y)  of the closed planar region are*
     *x=IIxdxdy/A and y=IIydxdy/A where the integrals II are over the*
     *(polygon) region of size A.                                    *
     *****************************************************************/
    template <class Polygon>
	Point PolygonCentroid(Polygon& plgn)
	{
	    const Point& p1 = plgn.front();
	    const Point& p2 = plgn.back();
	    //To implement a straightforward algorithm ensure that the
	    //polygon is closed (i.e., first == last)
	    if (p1 != p2){
		plgn.push_back(p1);
	    }
	    
	    //Note that the area  can be negative (clockwise chain) so
	    //keep the sign of the area. Otherwise we would get mirror
	    //ceneter coordinates (wrong sign for x and y).
	    PolygonAreaFunctor f1(p1);
	    double area = 0.5*accumulate(plgn.begin(),plgn.end(),0.0,f1);
	    PolygonCentroidFunctor f2(p1);
	    Point center(0,0,0);
	    center = accumulate(plgn.begin(),plgn.end(),center,f2);

	    return Point(center.getX()/(6.0*area),center.getY()/(6.0*area),
			 0.0);
	}
}

#endif
