#ifndef OPENGLFUNCTORI_H
#define OPENGLFUNCTORI_H

#include <vector>
#include <Point.h>
#include <LGMUnits.h>
#include "OpenGL.h"
#include "OpenGLSymbols.h"

namespace Lignum{



template <class TS, class BUD>
TreeCompartment<TS,BUD>* DrawBudFunctor<TS,BUD>::operator()(TreeCompartment<TS,BUD>* tc)const
{
  if (Bud<TS,BUD>* mybud = dynamic_cast<Bud<TS, BUD>*>(tc))
    {
      //cout << "Budi!" << endl;
      drawBud(mybud, mode);
    } 

  return tc;
}



template <class TS, class BUD>
TreeCompartment<TS,BUD>* DrawStemFunctor<TS,BUD>::operator()(TreeCompartment<TS,BUD>* tc)const
{
	if (TreeSegment<TS, BUD>* ts = dynamic_cast<TreeSegment<TS, BUD>*>(tc))
	{  			
		LGMdouble radius = GetValue(*ts, R);
		if (radius > min_rad && radius<=max_rad)	
		{

			float length;
			float radius_top;
			float rot_x;
			float rot_y;
			float rot_angle;

			Point position;
			PositionVector direction = GetDirection(*ts);

			length = GetValue(*ts, L); 
			
			radius_top = GetValue(*ts, RTop);
			position = GetPoint(*ts);
		
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
			MakeCylinder(radius, radius, length, rad_limit); 
			glPopMatrix();
			
		}
		
	} 
	return tc;
}




template <class TS, class BUD>
TreeCompartment<TS,BUD>* DrawLeavesFunctor<TS,BUD>::operator()(TreeCompartment<TS,BUD>* tc)const
{
	if (TreeSegment<TS, BUD>* ts = dynamic_cast<TreeSegment<TS, BUD>*>(tc))
	{  			
		if (HwTreeSegment<TS,BUD>* hwts = dynamic_cast<HwTreeSegment<TS,BUD>*>(ts))
		{
			float length;
			float radius_top;
			float rot_x;
			float rot_y;
			float rot_angle;

			Point position;
			PositionVector direction = GetDirection(*ts);

			LGMdouble radius = GetValue(*ts, R);
			length = GetValue(*ts, L); 
			radius_top = GetValue(*ts, RTop);
			position = GetPoint(*ts);
			
			rot_x = -1*direction.getVector()[1];
			rot_y =    direction.getVector()[0];
			rot_angle = (360/(2*PI_VALUE))*acos((double)direction.getVector()[2]);
			
			float xx = direction.getX() * length;
			float yy = direction.getY() * length;
			float zz = direction.getZ() * length;

			Point np(position.getX()+xx, position.getY()+yy, position.getZ()+zz);		

			std::list<BroadLeaf*>& leaf_list = GetLeafList(*hwts);
			std::list<BroadLeaf*>::iterator I;
				
			for(I = leaf_list.begin(); I != leaf_list.end(); I++) 
			{
				LGMdouble area = GetValue(**I, A);   //BroadLeaf returns true area of the leaf
				
				Petiole pet = GetPetiole(**I);

				LGMdouble rx = sqrt(area / 3.14);
				LGMdouble ry = sqrt(area / 3.14);

				PositionVector pv(GetEndPoint(pet)-GetStartPoint(pet));
				pv.getVector()[2] = 0.0;
				pv.normalize();

				LGMdouble ang = (360/(2*PI_VALUE))*acos((double)pv.getVector()[1]);

				glPushMatrix();  
				glTranslatef(np.getX(), np.getY(), np.getZ());          
				glRotatef( ang, 0, 0, 1); 			
							
				// sivuttaiskallistus
				glRotatef( rand()%30-15, 0, 1, 0);
				Make3DLeave( rx*leave_size_x, ry*leave_size_y, radius+0.01); 
				glPopMatrix();    	
			}
		}
	} 
	return tc;
}


}



template <class TS, class BUD>
TreeCompartment<TS,BUD>* DrawNeedlesFunctor<TS,BUD>::operator()(TreeCompartment<TS,BUD>* tc)const
{
  if (TreeSegment<TS, BUD>* ts = dynamic_cast<TreeSegment<TS, BUD>*>(tc))
    {                       
      if (CfTreeSegment<TS,BUD>* cfts = dynamic_cast<CfTreeSegment<TS,BUD>*>(ts))
	{
	  float length;
	  float radius_top;
	  float radius;
	  float rot_x;
	  float rot_y;
	  float rot_angle;
	  
	  Point position;
	  PositionVector direction = GetDirection(*ts);
	  
	  length = GetValue(*ts, L); 
	  radius_top = GetValue(*ts, RTop);
	  position = GetPoint(*ts);
	  
	  rot_x = -1*direction.getVector()[1];
	  rot_y =    direction.getVector()[0];
	  rot_angle = (360/(2*PI_VALUE))*acos((double)direction.getVector()[2]);
	  radius = GetValue(*ts, R);
	  
	  if (GetValue(*cfts, Wf) > 0)
	    {               
	      
	      glPushMatrix();
	      glTranslatef(position.getX(), position.getY(), position.getZ());
	      if (rot_angle > 0.01)
		glRotatef( rot_angle, rot_x, rot_y, 0);
	      draw_texfoliage_planes(length, radius, GetValue(*cfts, Wf), GetValue(*ts, age));         
	      glPopMatrix();
	    }                       
	}
      
    } 
  return tc;
}










#endif
