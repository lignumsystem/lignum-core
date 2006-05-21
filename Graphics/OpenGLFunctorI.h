#ifndef OPENGLFUNCTORI_H
#define OPENGLFUNCTORI_H

#include <vector>
#include <Point.h>
#include <LGMUnits.h>
#include "OpenGL.h"
#include "OpenGLSymbols.h"
			
void MakeCylinder(float radius, float rad_top, float length, 
		  float rad_limit, float xx, float yy);
namespace Lignum{



  template <class TS, class BUD>
    TreeCompartment<TS,BUD>* DrawBudFunctor<TS,BUD>::operator()(TreeCompartment<TS,BUD>* tc)const
    {
      if (Bud<TS,BUD>* mybud = dynamic_cast<Bud<TS, BUD>*>(tc))
	{
	  if (GetValue(*mybud,LGAstate) == ALIVE && mode == buds_alive)
	    drawBud(mybud, mode);
	  if (GetValue(*mybud,LGAstate) == DEAD && mode == buds_dead)
	    drawBud(mybud, mode);
	} 

      return tc;
    }



  template <class TS, class BUD>
    TreeCompartment<TS,BUD>* DrawStemFunctor<TS,BUD>::operator()(TreeCompartment<TS,BUD>* tc)const
    {
      if (TS* ts = dynamic_cast<TS *>(tc))
	{  			
	  LGMdouble radius = GetValue(*ts, LGAR);
	  if (radius > min_rad && radius<=max_rad)	
	    {
	      double length;
	      double radius_top;
	      double rot_x;
	      double rot_y;
	      double rot_angle;

	      Point position;
	      PositionVector direction = GetDirection(*ts);

	      length = GetValue(*ts, LGAL); 
			
	      radius_top = GetValue(*ts, LGARTop);
	      position = GetPoint(*ts);
	
	      //   cout << position.getX() << "  " << position.getY() << endl;
	
	      direction.normalize();
	      rot_x = -1*direction.getVector()[1];
	      rot_y =    direction.getVector()[0];
	      rot_angle = (360/(2*PI_VALUE))*acos((double)direction.getVector()[2]);
	      glPushMatrix();
	      glTranslatef(position.getX(), position.getY(), position.getZ());
	      if (rot_angle == 180.0){
		rot_y = 1.0;
	      }
	      glRotatef( rot_angle, rot_x, rot_y, 0);
	      float rad_limit = 0.05;
              MakeCylinder(radius, radius, length, rad_limit,0.0,0.0); 
	      glPopMatrix();
			
	    }
		
	} 
      return tc;
    }

 template <class TR>
 RootCompartment<TR>* DrawRootFunctor<TR>::operator()(RootCompartment<TR>* rc)const
    {
      if (RootSegment<TR>* rs = dynamic_cast<RootSegment<TR> *>(rc))
	{  			
	  LGMdouble radius = GetValue(*rs, LGAR);
	 
	  double length;
	  double radius_top;
	  double rot_x;
	  double rot_y;
	  double rot_angle;
	      
	  Point position;
	  PositionVector direction = GetDirection(*rs);

	  length = GetValue(*rs, LGAL);
	  position = GetPoint(*rs);
	  
	  direction.normalize();

	  rot_x = -1*direction.getVector()[1];
	  rot_y =    direction.getVector()[0];
	  rot_angle = (360/(2*PI_VALUE))*acos((double)direction.getVector()[2]);
	  glPushMatrix();
	  glTranslatef(position.getX(), position.getY(), position.getZ());
	  if (rot_angle == 180.0){
	    rot_y = 1.0;
	  }
	  glRotatef( rot_angle, rot_x, rot_y, 0);
	  float rad_limit = 0.05;
	  MakeCylinder(radius, radius, length, rad_limit,0.0,0.0);
	  glPopMatrix();
			
	    
	       
	} 
      return rc;
    }


  template <class TS, class BUD,class S>
  TreeCompartment<TS,BUD>* DrawLeavesFunctor<TS,BUD,S>::operator()(TreeCompartment<TS,BUD>* tc)const
  {
    if (TS* ts = dynamic_cast<TS*>(tc)){ 
      double length;
      double radius_top;
      double rot_x;
      double rot_y;
      double rot_angle;

      Point position;
      PositionVector direction = GetDirection(*ts);

      LGMdouble radius = GetValue(*ts, LGAR);
      length = GetValue(*ts,  LGAL); 
      radius_top = GetValue(*ts, LGARTop);
      position = GetPoint(*ts);
			
      rot_x = -1*direction.getVector()[1];
      rot_y =    direction.getVector()[0];
      rot_angle = (360/(2*PI_VALUE))*acos((double)direction.getVector()[2]);
			
      double xx = direction.getX() * length;
      double yy = direction.getY() * length;
      double zz = direction.getZ() * length;

      Point np(position.getX()+xx, position.getY()+yy, position.getZ()+zz);		

      std::list<BroadLeaf<S>*>& leaf_list = GetLeafList(*ts);
      typename std::list<BroadLeaf<S>*>::iterator I;

      for(I = leaf_list.begin(); I != leaf_list.end(); I++) {
	LGMdouble area = GetValue(**I, LGAA);   //BroadLeaf returns true area of the leaf
		
	std::vector<Point> points;
	GetShape(**I).getVertexVector(points);

	int aa = points.size();
		
	double minx = 9999;
	double miny = 9999;
	double maxx = -9999;
	double maxy = -9999;
	for (int bb =0; bb<aa; bb++){
	  Point p = points[bb];
	  if (p.getX() < minx) minx = p.getX();
	  if (p.getX() > maxx) maxx = p.getX();
	  if (p.getY() < miny) miny = p.getY();
	  if (p.getY() > maxy) maxy = p.getY();

	}
		  
	Point p1 = GetStartPoint(GetPetiole(**I));
	Point p2 = GetEndPoint(GetPetiole(**I));
	//Drawing  the  petiole.    Note  we  must  disable  textures,
	//otherwise the  subsequent leaves with  texture would prevent
	//them appearing
	glDisable(GL_TEXTURE_2D);
	glColor3f(0.0f,1.0f,0.0f);		
	glPushMatrix();  
	glLineWidth(1);
	glBegin(GL_LINES);
	glVertex3f(p1.getX(), p1.getY(), p1.getZ());
	glVertex3f(p2.getX(), p2.getY(), p2.getZ());
	glEnd();
	glPopMatrix();
	glColor3f(1.0f,1.0f,1.0f);
	glEnable(GL_TEXTURE_2D);
	
	glBegin(GL_POLYGON);
	glPushMatrix();
	glNormal3f(0,0,1);
	for (int bb =0; bb<aa; bb++){
	  Point p = points[bb];

	  double texx = (p.getX()-minx) / (maxx-minx);
	  double texy = (p.getY()-miny) / (maxy-miny);
	  //Scaling the texture
	  glTexCoord2f(0.5+0.5*sin(2*PI_VALUE*bb/aa), 
		       0.5+0.5*cos(2*PI_VALUE*bb/aa));
	  //  glTexCoord2f(texx, texy);		
	  glVertex3f(p.getX(), p.getY(), p.getZ());
	}
	glPopMatrix();
	glEnd();
      }
    }
    return tc;
  }

// Uusi funktori joka piirtää lehdet pyytämällä pistejoukon
template <class TS, class BUD,class S>
TreeCompartment<TS,BUD>* DrawLignumLeavesFunctor<TS,BUD,S>::operator()(TreeCompartment<TS,BUD>* tc)const
{
   			
  if (TS* hwts = dynamic_cast<TS *>(tc))
    {
      std::list<BroadLeaf<S>*>& leaf_list = GetLeafList(*hwts);
      typename std::list<BroadLeaf<S>*>::iterator I;
      for(I = leaf_list.begin(); I != leaf_list.end(); I++)
	{
	   LGMdouble area = GetValue(**I,LGAA);   //BroadLeaf returns true area of the leaf
	      
	  Petiole pet = GetPetiole(**I);
	      
	  const S& shape = GetShape(**I);
	  vector<Point> points;
	  shape.getVertexVector(points);
	      
	  int size = points.size();
	  glPushMatrix();
	  glBegin(GL_POLYGON);
	  for (int i=0; i<size; i++)
	    {
	      Point p = points[i];
	      PositionVector dir = shape.getNormal();
	      glNormal3f(dir.getX(), dir.getY(), dir.getZ());
	      glTexCoord2f(p.getX(), p.getY()); glVertex3f(p.getX(), p.getY(), p.getZ());

	      
	    }
	  glEnd();
	  glPopMatrix();
	      
	      
	}
    }
     
  return tc;
}


template <class TS, class BUD>
TreeCompartment<TS,BUD>* DrawNeedlesFunctor<TS,BUD>::operator()(TreeCompartment<TS,BUD>* tc)const
{
  if (TS* cfts = dynamic_cast<TS* >(tc))
    {
      double length;
      double radius_top;
      double radius;
      double rot_x;
      double rot_y;
      double rot_angle;
	  
      Point position;
      PositionVector direction = GetDirection(*cfts);
	  
      length = GetValue(*cfts, LGAL); 
      radius_top = GetValue(*cfts, LGARTop);
      position = GetPoint(*cfts);
	  
      rot_x = -1*direction.getVector()[1];
      rot_y =    direction.getVector()[0];
      rot_angle = (360/(2*PI_VALUE))*acos((double)direction.getVector()[2]);
      radius = GetValue(*cfts, LGAR);

      //  cout << "neulasmassa " << GetValue(*cfts, LGAWf) << endl;
      //SetValue(*cfts, LGAWf, 40);

      //if a very short segment do not visualize foliage
      //it just eats up memory
      //  cout << " testi " << endl;
      if (GetValue(*cfts, LGAWf) > R_EPSILON && (GetValue(*cfts,LGAL) > 0.01))
	{  
	    // cout << "LEHTIÄÄÄ" << endl;
	      
	  glPushMatrix();
	  glTranslatef(position.getX(), position.getY(), position.getZ());
	  if (rot_angle > 0.01)
	    glRotatef( rot_angle, rot_x, rot_y, 0);
	  
	  glDisable(GL_LIGHTING);
	  draw_texfoliage_planes(length, radius, GetValue(*cfts, LGAWf), 
				 static_cast<int>(GetValue(*cfts, LGAage)));
	  glEnable(GL_LIGHTING);
	  glPopMatrix();
	}                       
    }
  return tc;
}

}







#endif
