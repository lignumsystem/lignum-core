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
	
}

template <class TS, class BUD>
void HwWrapper<TS,BUD>::VisualizeStem(int &active_texture)
{
	
}

template <class TS, class BUD>
void HwWrapper<TS,BUD>::VisualizeFoliage(int &active_texture)
{
	
}

template <class TS, class BUD>
void CfWrapper<TS,BUD>::VisualizeTree()
{
  cout << "Visualize cf-tree" << endl;
	
}

template <class TS, class BUD>
void HwWrapper<TS,BUD>::VisualizeTree()
{
  cout << "Visualize hw-tree" << endl;
  
  
  DrawStemFunctor<TS,BUD> stemfunctor;
  stemfunctor.min_rad = -99;
  stemfunctor.max_rad = 999;
  ForEach(tree, stemfunctor);
  
}


template <class TS, class BUD>
void HwWrapper<TS,BUD>::MakeStemDisplayList()
{
  if (glIsList(intDisplaylistStem))
    {
      glDeleteLists(intDisplaylistStem,1);
    }

  glGenTextures(1, &intDisplaylistStem);
 
  glPushMatrix();
  //glNewList(intDisplaylistStem);
  VisualizeTree();
  glEndList();
  glPopMatrix();
}

template <class TS, class BUD>
void CfWrapper<TS,BUD>::MakeStemDisplayList()
{
}


template <class TS, class BUD>
void CfWrapper<TS,BUD>::DrawTree()
{

}

template <class TS, class BUD>
void HwWrapper<TS,BUD>::DrawTree()
{
  GLfloat mat_amb[] = { 0.2, 0.3, 0.4, 1.0 }; 
  GLfloat mat_dif[] = { 0.2, 0.4, 0.4, 1.0 }; 
  
  GLfloat mat_amb2[] = { 1.0, 0.5, 0.4, 1.0 }; 
  //  GLfloat mat_dif2[] = { 1.0, 0.7, 0.0, 0.8 };
  glMaterialfv(GL_FRONT, GL_AMBIENT, mat_amb); 
  glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_dif);
  
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_BLEND);  

  glCallList(intDisplaylistStem);
}



}

#endif
