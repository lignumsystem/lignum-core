//Polygon.cc


namespace cxxadt{

   PolygonAreaFunctor::PolygonAreaFunctor(const Point& p)
	:xi(p.getX()),yi(p.getY())
	{
	}

    double PolygonAreaFunctor::operator()(double id, const Point& p)
	{
	    double a = xi * p.getY() - yi * p.getX();
	    xi = p.getX();
	    yi = p.getY();
	    return id + a;
	}

    PolygonCentroidFunctor::PolygonCentroidFunctor(const Point& p)
	:xi(p.getX()),yi(p.getY())
	{
	}

    Point& PolygonCentroidFunctor::operator()(Point& center, const Point& p)
	{
	    double a = xi * p.getY() - yi * p.getX();
	    
	    center.setX(center.getX() + (xi + p.getX())*a);
	    center.setY(center.getY() + (yi + p.getY())*a);
	   
	    xi = p.getX();
	    yi = p.getY();
	    
	    return center;
	}

}//closing namespace cxxadt

#ifdef POLYGON

#include <list>
#include <iostream>
using namespace std;
using namespace cxxadt;

int main()
{
    list<Point> l1;
    list<Point> l2;
    list<Point> l3;
    const Point p1(4,6,0);
    const Point p2(4,2,0);
    const Point p3(0,8,0);
    const Point p4(4,6,0);
    const Point p5(0,0,0);
    const Point p6(0,4,0);
    const Point p7(4,4,0);
    const Point p8(4,0,0);
    l1.push_back(p1);
    l1.push_back(p2);
    l1.push_back(p3);
    l2.push_back(p1);
    l2.push_back(p2);
    l2.push_back(p3);
    l2.push_back(p4);
    l3.push_back(p5);
    l3.push_back(p6);
    l3.push_back(p7);
    l3.push_back(p8);
    cout << "Area: " << PolygonArea(l1) << endl;
    cout << "Area: " << PolygonArea(l2) << endl;
    cout << "Area: " << PolygonArea(l3) << endl;
    cout << "Centroid: " << PolygonCentroid(l1) << endl;
    cout << "Centroid: " << PolygonCentroid(l2) << endl;
    cout << "Centroid: " << PolygonCentroid(l3) << endl;
    return 0;
}

#endif
