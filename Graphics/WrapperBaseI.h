#ifndef WRAPPERBASEI_H
#define WRAPPERBASEI_H

namespace Lignum
{

template <class TS, class BUD>
void CfWrapper<TS,BUD>::GetTreeMetrics(Point &pos, LGMdouble &h)
    {
	pos = GetPoint(tree);
	h = GetValue(tree, LGAH);
    }

template <class TS, class BUD, class SHAPE>
void HwWrapper<TS,BUD,SHAPE>::GetTreeMetrics(Point &pos, LGMdouble &h)
    {
	pos = GetPoint(tree);
	h = GetValue(tree, LGAH);
    }

// Number of active is given as a parameter
template <class TS, class BUD>
void CfWrapper<TS,BUD>::VisualizeStem(int &active_texture)
{
	
}

template <class TS, class BUD>
void CfWrapper<TS,BUD>::VisualizeFoliage(int &active_texture)
{
    // cout << "lehti tekstuuri " << intFoliageTexture << endl;
    glEnable(GL_BLEND);
    glEnable(GL_TEXTURE_2D);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glBindTexture(GL_TEXTURE_2D, intFoliageTexture );
    glDisable(GL_LIGHTING);
    
    glPushMatrix();
    glEnable(GL_CULL_FACE);
    DrawNeedlesFunctor<TS, BUD> func;
    glCullFace(GL_FRONT);
    ForEach(tree, func);    
  
    glCullFace(GL_BACK);     	 
    ForEach(tree, func);
    glDisable(GL_CULL_FACE);
    glPopMatrix();
    glDisable(GL_BLEND);
    	
}

template <class TS, class BUD>
void CfWrapper<TS,BUD>::VisualizeWireModel()
{
  DrawWireModelFunctor<TS,BUD> stemfunctor;
  ForEach(tree, stemfunctor);
  
}

template <class TS, class BUD, class SHAPE>
void HwWrapper<TS,BUD,SHAPE>::VisualizeWireModel()
{
  DrawWireModelFunctor<TS,BUD> stemfunctor;
  ForEach(tree, stemfunctor);
  
}



template <class TS, class BUD, class SHAPE>
void HwWrapper<TS,BUD,SHAPE>::VisualizeStem(int &active_texture)
{
	
}

template <class TS, class BUD, class SHAPE>
void HwWrapper<TS,BUD,SHAPE>::VisualizeFoliage(int &active_texture)
{
    if (bmpImage)
    {
	glBindTexture(GL_TEXTURE_2D, intFoliageTexture );
	glPushMatrix();
	DrawLeavesFunctor<TS, BUD,SHAPE> func(1, 1);
	ForEach(tree, func);    
	glPopMatrix();
    }
    else
    {
	glEnable(GL_BLEND);
	glEnable(GL_TEXTURE_2D);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBindTexture(GL_TEXTURE_2D, intFoliageTexture );
	glDisable(GL_LIGHTING);
	
	glPushMatrix();
	glEnable(GL_CULL_FACE);
	DrawLeavesFunctor<TS, BUD,SHAPE> func(1, 1);
	glCullFace(GL_FRONT);
	ForEach(tree, func);    

	glCullFace(GL_BACK);     	 
	ForEach(tree, func);
	glDisable(GL_CULL_FACE);
	glPopMatrix();
    }
 	
}



template <class TS, class BUD,class SHAPE>
void HwWrapper<TS,BUD,SHAPE>::MakeWireModelLists()
{
  if (glIsList(intDisplaylistStem))
    {
      glDeleteLists(intDisplaylistStem,1);
    }
  
  glGenTextures(1, (GLuint*)&intDisplaylistStem);
  glPushMatrix();
  glNewList(intDisplaylistStem, GL_COMPILE);
  VisualizeWireModel();
  glEndList();
  glPopMatrix();


}



template <class TS, class BUD>
void CfWrapper<TS,BUD>::MakeWireModelLists()
{
    if (glIsList(intDisplaylistStem))
    {
	glDeleteLists(intDisplaylistStem,1);
    }
    glGenTextures(1, (GLuint*)&intDisplaylistStem);
    
    glPushMatrix();
    glNewList(intDisplaylistStem, GL_COMPILE);
    VisualizeWireModel();
    glEndList();
    glPopMatrix();
}



template <class TS, class BUD>
void CfWrapper<TS,BUD>::VisualizeTree()
{
    glBindTexture(GL_TEXTURE_2D,  intStemTexture);
    DrawStemFunctor<TS,BUD> stemfunctor;
    stemfunctor.min_rad = -99;
    stemfunctor.max_rad = 999;
    ForEach(tree, stemfunctor);   
}

template <class TS, class BUD, class SHAPE>
void HwWrapper<TS,BUD,SHAPE>::VisualizeTree()
{
  
  DrawStemFunctor<TS,BUD> stemfunctor;
  stemfunctor.min_rad = -99;
  stemfunctor.max_rad = 999;
  ForEach(tree, stemfunctor);
 
}


template <class TS, class BUD, class SHAPE>
void HwWrapper<TS,BUD,SHAPE>::MakeDisplayLists(bool orderfoliage)
{
    ordfoliage =  orderfoliage;
    
    if (glIsList(intDisplaylistStem))
    {
	glDeleteLists(intDisplaylistStem,1);
    }
    
    intDisplaylistStem = glGenLists(1);
    
    glPushMatrix();
    glNewList(intDisplaylistStem, GL_COMPILE);
    
    VisualizeTree();
    glEndList();
    glPopMatrix();
  
    //Problem with leaves it that they should be drawed ordered by the distance
    // from the camera
    
    if (ordfoliage == false)
    {
	intDisplaylistFoliage = glGenLists(1);
	glPushMatrix();
	glNewList(intDisplaylistFoliage, GL_COMPILE);
	int num = -1;
	VisualizeFoliage(num);
	glEndList();
	glPopMatrix();
    }
    
   
}


// Draws distance-ordered leaves one by one 
template <class TS, class BUD, class SHAPE>
void HwWrapper<TS,BUD,SHAPE>::DrawOrderedLeaves(float x, float y, float z)
{
  // cout << "cam  " << " " << x << " " << y << " " << z << endl; 
  //Collect leaves from the tree
  CollectLeaves<TS,BUD, SHAPE> collector;
  list<BroadLeaf<SHAPE>*> leaf_list;
  Accumulate(tree,leaf_list,collector);
  //Leaves are in  the leaf_list, sort them
  SortLeaves<SHAPE> sorter(Point(x,y,z));
  leaf_list.sort(sorter);
  leaf_list.reverse();
  //Leaves are now sorted, the leaves closest
  //to the Point(x,y,z) appear first.
  typename list<BroadLeaf<SHAPE>*>::iterator I;
  for(I = leaf_list.begin(); I != leaf_list.end(); I++) 
    {
       
      glEnable(GL_BLEND);
      glEnable(GL_TEXTURE_2D);
      glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
      glBindTexture(GL_TEXTURE_2D, intFoliageTexture );
      glDisable(GL_LIGHTING);
       
      glPushMatrix();
      glEnable(GL_CULL_FACE);
      glCullFace(GL_FRONT);

      vector<Point> points;
      SHAPE e =  GetShape(**I);
      // GetShape(**I)
      e.getVertexVector(points);
       
      int aa = points.size();
       
       
      float minx = 9999;
      float miny = 9999;
      float maxx = -9999;
      float maxy = -9999;
      for (int bb =0; bb<aa; bb++)
	{
	  Point p = points[bb];
	  if (p.getX() < minx) minx = p.getX();
	  if (p.getX() > maxx) maxx = p.getX();
	  if (p.getY() < miny) miny = p.getY();
	  if (p.getY() > maxy) maxy = p.getY();
	}
       
      glBegin(GL_POLYGON);
      glPushMatrix();
      glNormal3f(0,0,1);
      for (int bb =0; bb<aa; bb++)
	{
	  Point p = points[bb];
	   
	  float texx = (p.getX()-minx) / (maxx-minx);
	  float texy = (p.getY()-miny) / (maxy-miny);
	  glTexCoord2f(texx, texy);		
	  glVertex3f(p.getX(), p.getY(), p.getZ());   
	}
      glPopMatrix();
      glEnd();
      glCullFace(GL_BACK);     	 
      for (int bb =0; bb<aa; bb++)
	{
	  Point p = points[bb];
	   
	  float texx = (p.getX()-minx) / (maxx-minx);
	  float texy = (p.getY()-miny) / (maxy-miny);
	  glTexCoord2f(texx, texy);		
	  glVertex3f(p.getX(), p.getY(), p.getZ());   
	}
      glDisable(GL_CULL_FACE);
      glPopMatrix();
    }     
}

template <class TS, class BUD>
void CfWrapper<TS,BUD>::MakeDisplayLists(bool orderfoliage)
{
    ordfoliage =  orderfoliage;
    if (glIsList(intDisplaylistStem))
    {
	glDeleteLists(intDisplaylistStem,1);
    }
    
    glGenTextures(1, (GLuint*)&intDisplaylistStem);
    
    glPushMatrix();
    glNewList(intDisplaylistStem, GL_COMPILE);
    VisualizeTree();
    glEndList();
    glPopMatrix();

//    cout << "tehdään lehti-lista..." << endl;
    intDisplaylistFoliage = glGenLists(1);
    glPushMatrix();
    glNewList(intDisplaylistFoliage, GL_COMPILE);
    int num = -1;
    VisualizeFoliage(num);
    glEndList();
    glPopMatrix();
}


template <class TS, class BUD>
void CfWrapper<TS,BUD>::DrawTree(float x, float y, float z)
{
    //   cout << " drawing cftree " << endl;
    
    GLfloat mat_amb[] = { 0.2, 0.3, 0.4, 1.0 }; 
    GLfloat mat_dif[] = { 0.2, 0.4, 0.4, 1.0 }; 
    
    GLfloat mat_amb2[] = { 1.0, 0.5, 0.4, 1.0 }; 
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_amb); 
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_dif);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_BLEND);  
    
    //stem_texture.
    glBindTexture(GL_TEXTURE_2D,  intStemTexture);
    glDisable(GL_BLEND);
    glDisable(GL_LIGHTING);
    glCallList(intDisplaylistStem);
    
    
    // cout << "lehdet.." << endl;
    // Lehdet
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexEnvf(GL_TEXTURE_2D, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_BLEND);
    glCallList(intDisplaylistFoliage);
    
}


template <class TS, class BUD,class SHAPE>
void HwWrapper<TS,BUD,SHAPE>::DrawTree(float x, float y, float z)
{ 
  GLfloat mat_amb[] = { 0.2, 0.3, 0.4, 1.0 }; 
  GLfloat mat_dif[] = { 0.2, 0.4, 0.4, 1.0 }; 

  //GLfloat mat_amb2[] = { 1.0, 0.5, 0.4, 1.0 }; 
    
  //GLfloat mat_dif2[] = { 1.0, 0.7, 0.0, 0.8 };
  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_amb); 
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_dif);
  
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_BLEND);  
  
  glBindTexture(GL_TEXTURE_2D,  intStemTexture);
  glDisable(GL_BLEND);
 
  glDisable(GL_LIGHTING);
  glCallList(intDisplaylistStem);
 
  if (ordfoliage)
  {
    DrawOrderedLeaves(x,y,z);
  }
  else
  {
    //Lehdet
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexEnvf(GL_TEXTURE_2D, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_BLEND);
    glCallList(intDisplaylistFoliage);
  }
 
}

  template <class TS, class BUD>
  void CfWrapper<TS,BUD>::DrawTreeMetrics()
  {
    Point p = GetPoint(tree);
    double h = GetValue(tree,LGAH);
    double dbh = GetValue(tree,LGADbh)*100.0;
    ostringstream os1;
    ostringstream os2;
    os1 << setprecision(3) << "H="<<h;
    os2 << setprecision(2) << "D=" << dbh;
    LGMTextOutput(p.getX(),p.getY()+0.2,h,GLUT_BITMAP_HELVETICA_10,
		  os1.str());
    if (dbh > 0.0)
      LGMTextOutput(p.getX(),p.getY()+0.2,1.3,GLUT_BITMAP_HELVETICA_10,
		    os2.str());
  }


  template <class TS, class BUD, class SHAPE>
  void HwWrapper<TS,BUD,SHAPE>::DrawTreeMetrics()
  {
    Point p = GetPoint(tree);
    double h = GetValue(tree,LGAH);
    double dbh = GetValue(tree,LGADbh)*100.0;
    ostringstream os1;
    ostringstream os2;
    os1 << setprecision(3) << "H="<<h;
    os2 << setprecision(2) << "D=" << dbh;
    LGMTextOutput(p.getX(),p.getY()+0.2,h,GLUT_BITMAP_HELVETICA_10,
		  os1.str());
    if (dbh > 0.0)
      LGMTextOutput(p.getX(),p.getY()+0.2,1.3,GLUT_BITMAP_HELVETICA_10,
		    os2.str());
  }


}

#endif
