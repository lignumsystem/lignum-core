#ifndef WRAPPERBASEI_H
#define WRAPPERBASEI_H



namespace Lignum
{

// Number of active is given as a parameter
template <class TS, class BUD>
void CfWrapper<TS,BUD>::VisualizeStem(int &active_texture)
{
	
}

template <class TS, class BUD>
void CfWrapper<TS,BUD>::VisualizeFoliage(int &active_texture)
{
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
  cout << "Visualize WireModel cf-tree" << endl;
  
  
  DrawWireModelFunctor<TS,BUD> stemfunctor;
  ForEach(tree, stemfunctor);
  
}

template <class TS, class BUD>
void HwWrapper<TS,BUD>::VisualizeWireModel()
{
  cout << "Visualize wiremodel of hw-tree" << endl;
   
  DrawWireModelFunctor<TS,BUD> stemfunctor;
  ForEach(tree, stemfunctor);
  
}



template <class TS, class BUD>
void HwWrapper<TS,BUD>::VisualizeStem(int &active_texture)
{
	
}

template <class TS, class BUD>
void HwWrapper<TS,BUD>::VisualizeFoliage(int &active_texture)
{
    glBindTexture(GL_TEXTURE_2D, intFoliageTexture );
    glPushMatrix();
    DrawLeavesFunctor<TS, BUD> func(1, 1);
    ForEach(tree, func);    
    glPopMatrix();



/*
    cout << "visualisoidaan lehdet " << endl;
  glEnable(GL_BLEND);
  glEnable(GL_TEXTURE_2D);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glBindTexture(GL_TEXTURE_2D, intFoliageTexture );
  glDisable(GL_LIGHTING);
  
  glPushMatrix();
  glEnable(GL_CULL_FACE);
  DrawLeavesFunctor<TS, BUD> func(1, 1);
  glCullFace(GL_FRONT);
  ForEach(tree, func);    
  // glPopMatrix();

  //glPushMatrix();
  glCullFace(GL_BACK);     	 
  ForEach(tree, func);
  glDisable(GL_CULL_FACE);
  glPopMatrix();
*/	
}



template <class TS, class BUD>
void HwWrapper<TS,BUD>::MakeWireModelLists()
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

template <class TS, class BUD>
void HwWrapper<TS,BUD>::VisualizeTree()
{
  DrawStemFunctor<TS,BUD> stemfunctor;
  stemfunctor.min_rad = -99;
  stemfunctor.max_rad = 999;
  ForEach(tree, stemfunctor);
}


template <class TS, class BUD>
void HwWrapper<TS,BUD>::MakeDisplayLists()
{
   
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
 
  intDisplaylistFoliage = glGenLists(1);
  glPushMatrix();
  glNewList(intDisplaylistFoliage, GL_COMPILE);
  int num = -1.0;
  VisualizeFoliage(num);
  glEndList();
  glPopMatrix();
}

template <class TS, class BUD>
void CfWrapper<TS,BUD>::MakeDisplayLists()
{
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

    intDisplaylistFoliage = glGenLists(1);
    glPushMatrix();
    glNewList(intDisplaylistFoliage, GL_COMPILE);
    int num = -1.0;
    VisualizeFoliage(num);
    glEndList();
    glPopMatrix();
}


template <class TS, class BUD>
void CfWrapper<TS,BUD>::DrawTree()
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
    
    
    // Lehdet
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexEnvf(GL_TEXTURE_2D, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_BLEND);
    glCallList(intDisplaylistFoliage);
    
}

template <class TS, class BUD>
void HwWrapper<TS,BUD>::DrawTree()
{
  GLfloat mat_amb[] = { 0.2, 0.3, 0.4, 1.0 }; 
  GLfloat mat_dif[] = { 0.2, 0.4, 0.4, 1.0 }; 
  
  GLfloat mat_amb2[] = { 1.0, 0.5, 0.4, 1.0 }; 
  //  GLfloat mat_dif2[] = { 1.0, 0.7, 0.0, 0.8 };
  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_amb); 
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_dif);
  
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_BLEND);  

  glBindTexture(GL_TEXTURE_2D,  intStemTexture);
  glDisable(GL_BLEND);

  //Valaistus ei toimi joten se pois p��lt�
  glDisable(GL_LIGHTING);
  glCallList(intDisplaylistStem);
 
  // Lehdet
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexEnvf(GL_TEXTURE_2D, GL_TEXTURE_ENV_MODE, GL_REPLACE);
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_BLEND);
  glCallList(intDisplaylistFoliage);
  
}



}

#endif
