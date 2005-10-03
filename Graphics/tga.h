/*
   Copyright (C) 2000 Nate Miller nkmiller@calpoly.edu

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public License
   as published by the Free Software Foundation; either version 2
   of the License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

   See gpl.txt for more information regarding the GNU General Public License.
*/
/*
   CHANGES
      03/19/00 - i now check image size on upload...
*/
#ifndef TGA_H
#define TGA_H

//#include "utility.h"
#define WIN32_LEAN_AND_MEAN

#ifdef WIN32
#include <windows.h>
#else
#include <stdio.h>
typedef unsigned char byte;
#endif

#include <OpenGLHFiles.h>

struct tga_t
{
   tga_t();
   tga_t(const char *name);
   tga_t(const char *name, int texId, int upload = uploadYes, GLenum nf = 0);
   int Load(const char *name);
   int Load(const char *name, int texId, int upload = uploadYes, GLenum nf = 0);
   void Free(void)        {delete [] data;}
   void Id(int texId)     {id = texId;}
   int Upload(void);
   void Reset(void);
   int LastError(void)    {return lastError;}
   int Width(void)        {return width;}
   int Height(void)       {return height;}
   int Bits(void)         {return bits;}
   int Id(void)           {return id;}
   void Format(GLenum nf) {format = nf;}
   GLenum Format(void)    {return format;}
   byte *Data(void) {return data;}
   byte operator[](int ndx) {return data[ndx];}
   int GenId(void)     
  {GLuint temp; glGenTextures(1, &temp); return static_cast<int>(temp);}

   enum
   {
      notFound = 1000,
      badType,
      badDimension,
      badBits,    
      badData,    
      badUpload,
      uploadNo = 1,
      uploadYes = 0,    
      maxTexSize = 512
   };

protected:
   int Error(int errNum, FILE *strm);
   int CheckSize(int x);
   byte *GetRGB(FILE *strm, int size);
   byte *GetRGBA(FILE *strm, int size);
   byte *GetGray(FILE *strm, int size);
   byte *GrabData(FILE *strm, int size);

   int lastError;
   int bits;
   int width;
   int height;
   int id;
   int size;
   GLenum format;
   byte *data;
   
};
#endif
