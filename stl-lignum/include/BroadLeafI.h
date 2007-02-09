#ifndef BROADLEAFI_H
#define BROADLEAFI_H

namespace Lignum{
  template <class SHAPE>
  BroadLeafAttributes<SHAPE>::BroadLeafAttributes(const BroadLeafAttributes& bla)
    :degree_of_filling(bla.degree_of_filling),sf(bla.sf),tauL(bla.tauL),
     P(bla.P),M(bla.M),Qin(bla.Qin),Qabs(bla.Qabs),petiole(bla.petiole),
     shape(bla.shape),sv(bla.sv)
  {
  }

template <class SHAPE>  
BroadLeaf<SHAPE>::BroadLeaf(LGMdouble sf,LGMdouble tauL,LGMdouble dof,int number_of_sectors,
			    const Petiole& petiole,const SHAPE& shape)
  :bla(sf,tauL,dof,petiole,shape,number_of_sectors)
{

}

template <class SHAPE>  
BroadLeaf<SHAPE>::BroadLeaf(const SHAPE& shape, const Petiole& petiole)
  :bla(1.0,1.0,1.0,petiole,shape,10)
{
}

 
template <class SHAPE>  
BroadLeaf<SHAPE>::BroadLeaf(const SHAPE& shape, const Petiole& petiole, 
			    int sky_sectors)
  :bla(1.0,1.0,1.0,petiole,shape,sky_sectors)
{

}

template <class SHAPE>  
BroadLeafAttributes<SHAPE>::BroadLeafAttributes(double sf1, double tauL1, 
						double dof1, const Petiole& petiole1,
						const SHAPE& shape1,
						int number_of_sectors)
  :degree_of_filling(dof1),sf(sf1),tauL(tauL1),P(0.0),M(0.0),Qin(0.0),Qabs(0.0),
     petiole(petiole1),shape(shape1),sv(number_of_sectors)
{

}

template <class SHAPE>  
LGMdouble GetValue(const BroadLeaf<SHAPE>& bl, const LGMAD name)
{

  if (name == LGAA)
    //true area of the leaf
    return  GetShape(bl).getArea()*GetValue(bl,LGAdof); 

  else if (name == LGAdof)
    return  bl.bla.degree_of_filling;

  else if (name == LGAtauL)
    return bl.bla.tauL;
  
  else if (name == LGAP)
    return bl.bla.P;

  else if (name == LGAM)
    return  bl.bla.M;
  
  else if (name == LGAQabs)
    return  bl.bla.Qabs;
  
  else if (name == LGAQin)
    return  bl.bla.Qin;

  else if (name == LGAsf)
    return  bl.bla.sf;

  else if (name == LGAWf)
    //Wf = A/SLA (i.e., kgC = m2/(m2/kgC) ) 
    return  GetValue(bl,LGAA)/GetValue(bl,LGAsf);

  else
    cout << "BroadLeaf GetValue unknown attribute: " 
	 << name << " returning 0.0" << endl;
 
  return 0.0;
}

template <class SHAPE>  
LGMdouble SetValue(BroadLeaf<SHAPE>& bl, const LGMAD name, const LGMdouble value)
{
  LGMdouble old_value= GetValue(bl,name);

  if (name == LGAA) 
    //Given the true area of the leaf, set the shape area, the scaling
    //center is the petiole end
     bl.bla.shape.setArea(value/GetValue(bl,LGAdof), 
			 GetEndPoint(GetPetiole(bl)));  
  else if (name == LGAdof)
    bl.bla.degree_of_filling = value;

  else if (name == LGAtauL)
    bl.bla.tauL = value;
  
  else if (name == LGAP)
    bl.bla.P = value;

  else if (name == LGAM)
    bl.bla.M = value;
  
  else if (name == LGAQabs)
    bl.bla.Qabs = value;
  
  else if (name == LGAQin)
    bl.bla.Qin = value;

  else if (name == LGAsf)
    bl.bla.sf = value;

  else if (name == LGAWf)
    //Given the Wf, set the shape area using SLA: 
    //LeafA = SLA*Wf, i.e m2 = (m2/kgC)*kgC
    //ShapeA = LeafA/dof
    bl.bla.shape.setArea(GetValue(bl,LGAsf)*value/GetValue(bl,LGAdof));
  else 
    cout << "BroadLeaf SetValue uknown attribute: " << name << "returning: "
	 << old_value << endl;
 
  return old_value;
}

template <class SHAPE>  
const Point GetCenterPoint(const BroadLeaf<SHAPE>& bl)
{
  return bl.bla.shape.getCenterPoint();
}

template <class SHAPE>  
const PositionVector& GetLeafNormal(const BroadLeaf<SHAPE>& bl)
{
  return bl.bla.shape.getNormal();
}

template <class SHAPE>  
const Petiole& GetPetiole(const BroadLeaf<SHAPE>& bl)
{
  return bl.bla.petiole;
}

template <class SHAPE>  
const SHAPE& GetShape(const BroadLeaf<SHAPE>& bl)
{
  return bl.bla.shape;
}

template <class SHAPE>  
void SetCenterPoint(BroadLeaf<SHAPE>& bl, const Point& p)
{
  bl.bla.shape.setCenterPoint(p);
}

template <class SHAPE>  
void SetRadiationVector(BroadLeaf<SHAPE>& bl, const vector<LGMdouble>& v)
{
  for(unsigned int i = 0; i < bl.bla.sv.size(); i++)
    bl.bla.sv[i] = v[i];
}
   
template <class SHAPE>  
const vector<double>& GetRadiationVector(const BroadLeaf<SHAPE>& bl)
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
