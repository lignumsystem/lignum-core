#To compile "algorithms" on SGI type 
#    make algorithms
#To compile with g++ on SGI or on  Linux type 
#    make gnu 

SRC=OpenGL.cc  OpenGLUnix.cc OpenGLfunctions.cc  OpenGLinterface.cc tga.cc \
    texture.cc GLSettings.cc LGMVisualization.cc LGMVoxelVisualization.cc 
OBJ=${SRC:.cc=.o}

ALGSRC = algorithms.cc 
ALGOBJ  = ${ALGSRC:.cc=.o} 

 
CCC = CC -64 -LANG:std

#OPTIMIZE = -Ofast=ip28 -IPA
OPTIMIZE   = -g 

AR =  $(CCC) -ar  
ARFLAGS = -o 

SUPPRESS = #-w 1155 -w 1183

CCCFLAGS = -c  #-prelink -ptused   -ptv  #  -fullwarn 


INCLUDE = -I. -I../stl-lignum/include -I../c++adt/include -I../stl-voxelspace \
          -I../Firmament/include -I/usr/freeware/include \
          -I/usr/X11R6/include -I/sw/include -I../stl-voxelspace/include -I../ScotsPine/include

#Glut library comes in 64 and 32 bit versions on SGI.  However neither CC or g++ can 
#automatically search right library but we must explicitelly tell with LIBD where to search.
#On SGI default compilation with CC is 64 bit and with g++ 32 bit.
#This should work fine with Linux where 32 bit Glut library is found by g++ 
#in the system directory. 
LIBD = lib64
LIBFLAGS = -L. -L../c++adt/lib -L../stl-lignum/lib -L../Firmament/lib  -L/usr/freeware/$(LIBD) 


LIB1   = libc++adt.a
LIB2   = libLGM.a
LIB3   = libsky.a
LIB4   = libVisual.a

LIBADT = -lc++adt
LIBLGM = -lLGM
LIBSKY = -lsky
LIBMATH  = -lm 
LIBVISUAL = -lVisual

LIBOGL =  -lglut -lGL -lGLU -lX11 -lXext -lXmu 

LIBS     =  $(LIBVISUAL) $(LIBLGM) $(LIBSKY) $(LIBADT) $(LIBOGL) $(LIBMATH)
 

PROGFILES = program-files.html
.SUFFIXES: .o .cc

sinclude Makedepend

algorithms: $(ALGOBJ) $(LIB4) $(LIB1) $(LIB3)  $(LIB2) 
	$(CCC)  -o $@ $(INCLUDE) $(OPTIMIZE) $(ALGOBJ) $(LIBFLAGS) $(LIBS) 

gnu:
	make "CCC=g++" "CCCFLAGS=-c" "OPTIMIZE=-g" "LIBD=lib32" \
             "AR=ar"  "ARFLAGS=rvs" algorithms
lignux: 
	make "CCC=g++" "CCCFLAGS=-c" "OPTIMIZE=-g" "LIBD=lib32" \
             "AR=ar"  "ARFLAGS=rvs" algorithms

$(LIB1):
	(cd ../c++adt; make "CCC=$(CCC)" "CCCFLAGS=$(CCCFLAGS)" "OPTIMIZE=$(OPTIMIZE)" \
         "AR=$(AR)"  "ARFLAGS = $(ARFLAGS)" $@)

$(LIB2):
	(cd ../stl-lignum; make "CCC=$(CCC)" "CCCFLAGS=$(CCCFLAGS)" "OPTIMIZE=$(OPTIMIZE)" \
         "AR=$(AR)" "ARFLAGS = $(ARFLAGS)" $@)

$(LIB3):
	(cd ../Firmament; make "CCC=$(CCC)" "CCCFLAGS=$(CCCFLAGS)" "OPTIMIZE=$(OPTIMIZE)" \
          "AR=$(AR)"  "ARFLAGS = $(ARFLAGS)" $@)

$(LIB4):$(OBJ)
	$(AR) $(ARFLAGS) $(LIB4) $(OBJ)

.cc.o: 
	$(CCC) $(OPTIMIZE) $(SUPPRESS) $(CCCFLAGS) $(INCLUDE)  $< -o $@

html:
	enscript -E --color -Whtml --toc -p$(PROGFILES) ./include/*.h ./*/*.cc

clean:
	rm -rf $(OBJ) $(ALGOBJ) $(BLOBJ) core  ii_files
distclean: clean
	rm -f $(LIB4) algorithms Makedepend
	(cd ../stl-lignum; make distclean)
depend:
	(cd ../stl-lignum; make  "CCC=$(CCC)" depend)
	$(CCC) -M $(INCLUDE) $(SRC) $(ALGSRC) > Makedepend

#Do not delete this line -- make depend adds dependencies at the end of it
#If committing Makefile to cvs please remove the dependencies first
# DO NOT DELETE
