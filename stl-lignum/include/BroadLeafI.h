#ifndef BROADLEAFI_H
#define BROADLEAFI_H

namespace Lignum{

template <class SHAPE>  
BroadLeaf<SHAPE>::BroadLeaf(LGMdouble sf,LGMdouble tauL,LGMdouble dof,int number_of_sectors,
			    const Petiole& petiole,const PositionVector& leaf_normal,const SHAPE& shape)
  :bla(sf,tauL,dof,petiole,leaf_normal,shape,number_of_sectors)
{

  //calculate and set the center of the leaf ellipse
  Point petiol_proj;    //projection of petiole on leaf ellipse
  Point petiol;         //Petiole as a vector (Point!)
  petiol = GetEndPoint(petiole) - GetStartPoint(petiole);
  vector<double> v = leaf_normal.getVector();
  Point lnp(v[0],v[1],v[2]);
  petiol_proj = petiol - Dot(leaf_normal,PositionVector(petiol)) * lnp;
  double b = (double)shape.getSemiminorAxis();
  double ppl = sqrt((double)Dot(PositionVector(petiol_proj), PositionVector(petiol_proj)));

  if(ppl < 1.0e-10)
    bla.center = GetEndPoint(petiole);  // If petiole perpendicular to leaf ellipse
  // center = end of petiole (this is a bit arbitrary)
  else
    bla.center = GetEndPoint(petiole) + (b/ppl) * petiol_proj;
}

template <class SHAPE>  
BroadLeaf<SHAPE>::BroadLeaf(const SHAPE& shape, const Petiole& petiole, 
			    const PositionVector& leaf_normal)
  :bla(1.0,1.0,1.0,petiole,leaf_normal,shape,10)
{

}

template <class SHAPE>  
BroadLeafAttributes<SHAPE>::BroadLeafAttributes(double sf1, double tauL1, 
						double dof1, const Petiole& petiole1,
						const PositionVector& leaf_normal1, 
						const SHAPE& shape1,
						int number_of_sectors)
  :sf(sf1),tauL(tauL1),degree_of_filling(dof1),P(0.0),M(0.0),Qabs(0.0),Qin(0.0),
     petiole(petiole1),leaf_normal(leaf_normal1),shape(shape1),sv(number_of_sectors)
{
  leaf_normal.normalize();
}

template <class SHAPE>  
LGMdouble GetValue(const BroadLeaf<SHAPE>& bl, const LGMAD name)
{

  if (name == A)
    return  bl.bla.degree_of_filling*bl.bla.shape.getArea(); //true area of the leaf

  else if (name == dof)
    return  bl.bla.degree_of_filling;

  else if (name == sf)
    return bl.bla.sf;

  else if (name == tauL)
    return bl.bla.tauL;
  
  else if (name == P)
    return bl.bla.P;

  else if (name == M)
    return  bl.bla.M;
  
  else if (name == Qabs)
    return  bl.bla.Qabs;
  
  else if (name == Qin)
    return  bl.bla.Qin;

  else if (name == Wf)
    return  bl.bla.degree_of_filling*GetValue(bl,A)/bl.bla.sf;
  else
    cout << "BroadLeaf GetValue unknown attribute: " << name << " returning 0.0" << endl;
 
  return 0.0;
}

template <class SHAPE>  
LGMdouble SetValue(BroadLeaf<SHAPE>& bl, const LGMAD name, const LGMdouble value)
{
  LGMdouble old_value= GetValue(bl,name);

  if (name == A)
    bl.bla.shape.setArea(value/bl.bla.degree_of_filling);  //value=true area of the leaf

  else if (name == dof)
    bl.bla.degree_of_filling = value;

  else if (name == sf)
    bl.bla.sf = value;

  else if (name == tauL)
    bl.bla.tauL = value;
  
  else if (name == P)
    bl.bla.P = value;

  else if (name == M)
    bl.bla.M = value;
  
  else if (name == Qabs)
    bl.bla.Qabs = value;
  
  else if (name == Qin)
    bl.bla.Qin = value;

  else if (name == Wf)
    bl.bla.shape.setArea(bl.bla.sf*value/bl.bla.degree_of_filling);
                  //sf * Wf specifies the true area of the leaf

  else 
    cout << "BroadLeaf SetValue uknown aattribute: " << name << "returning: "
	 << old_value << endl;
 
  return old_value;
}

template <class SHAPE>  
Point GetCenterPoint(const BroadLeaf<SHAPE>& bl)
{
  return bl.bla.center;
}

template <class SHAPE>  
PositionVector GetLeafNormal(const BroadLeaf<SHAPE>& bl)
{
  return bl.bla.leaf_normal;
}

template <class SHAPE>  
PositionVector SetLeafNormal(BroadLeaf<SHAPE>& bl, const PositionVector& n)
{
  PositionVector vv = bl.bla.leaf_normal;
  bl.bla.leaf_normal = n;
  //normalize the normal to unit vector. 
  bl.bla.leaf_normal.normalize();

  return vv;
}

template <class SHAPE>  
Petiole& GetPetiole(BroadLeaf<SHAPE>& bl)
{
  return bl.bla.petiole;
}

template <class SHAPE>  
SHAPE& GetShape(BroadLeaf<SHAPE>& bl)
{
  return bl.bla.shape;
}

template <class SHAPE>  
void SetCenterPoint(BroadLeaf<SHAPE>& bl, const Point& p)
{
  bl.bla.center = p;
}

template <class SHAPE>  
void SetRadiationVector(BroadLeaf<SHAPE>& bl, const vector<LGMdouble>& v)
{
  for(int i = 0; i < bl.bla.sv.size(); i++)
    bl.bla.sv[i] = v[i];
}
   
template <class SHAPE>  
vector<double> GetRadiationVector(BroadLeaf<SHAPE>& bl)
{
  return bl.bla.sv;
}

//Translates BroadLeaf as specified by vector t, orientation not changed
//(= vector t added to all positions, including Petiole)
template <class SHAPE>  
void TranslateLeaf(BroadLeaf<SHAPE>& bl, const PositionVector& t)
{

  const Point t_point = (Point)t;
  Point pnt = GetCenterPoint(bl);

  SetCenterPoint(bl, pnt + t_point);

  pnt = GetStartPoint(bl.bla.petiole);
  SetStartPoint(bl.bla.petiole, pnt + t_point);

  pnt = GetEndPoint(bl.bla.petiole);
  SetEndPoint(bl.bla.petiole, pnt + t_point);
  
}

//Moves leaf from its current position to position where
//the starting point of the petiole is p.
//Orientation does not change
template <class SHAPE>  
void SetLeafPosition(BroadLeaf<SHAPE>& bl, const Point& p)
{
  PositionVector transvct = PositionVector(p - GetStartPoint(bl.bla.petiole));

  TranslateLeaf(bl, transvct);
}


}//closing namespace Lignum

#endif
