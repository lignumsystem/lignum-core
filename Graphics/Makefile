#To compile "algorithms" on SGI type 
#    make algorithms
#To compile with g++ in Linux type (or copy paste)
#    make "CCC=g++" "CCCFLAGS=-c" "OPTIMIZE=-O" "ARCOMMAND=ar"  "ARCOMMANDFLAGS=rv" algorithms 

SRC=OpenGL.cc  OpenGLUnix.cc OpenGLfunctions.cc  OpenGLinterface.cc texture.cc 
OBJ=OpenGL.o  OpenGLUnix.o OpenGLfunctions.o  OpenGLinterface.o texture.o 

ALGSRC = algorithms.cc 
ALGOBJ  = algorithms.o 

 
CCC = CC -64 -LANG:std

#OPTIMIZE = -Ofast=ip28 -IPA
OPTIMIZE   = -g 

ARCOMMAND =  $(CCC) -ar  
ARCOMMANDFLAGS = -o 
AR = $(ARCOMMAND)

SUPPRESS = #-w 1155 -w 1183

CCCFLAGS = -c  #-prelink -ptused   -ptv  #  -fullwarn 

INCLUDE = -I. -I../stl-lignum/include -I../c++adt/include -I../Firmament/include \
          -I/usr/freeware/include

STL     = -I/usr/include/CC

LIBFLAGS = -L. -L../c++adt/lib -L../stl-lignum/lib -L../Firmament/lib \
           -L/usr/freeware/lib64 -L/usr/freeware/lib32

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

algorithms: $(ALGOBJ) $(LIB4) $(LIB1) $(LIB3)  $(LIB2) 
	$(CCC)  -o $@ $(INCLUDE) $(OPTIMIZE) $(ALGOBJ) $(LIBFLAGS) $(LIBS)

lignux: 
	make "CCC=g++" "CCCFLAGS=-c" "OPTIMIZE=-O" "ARCOMMAND=ar"  "ARCOMMANDFLAGS=rv" algorithms


$(LIB1):
	(cd ../c++adt/lib; make "CCC=$(CCC)" "CCCFLAGS=$(CCCFLAGS)" \
         "OPTIMIZE=$(OPTIMIZE)" "AR=$(ARCOMMAND)"  "ARFLAGS = $(ARCOMMANDFLAGS)" $@)

$(LIB2):
	(cd ../stl-lignum/lib; make "CCC=$(CCC)" "CCCFLAGS=$(CCCFLAGS)" "OPTIMIZE=$(OPTIMIZE)" "AR=$(ARCOMMAND)" \
         "ARFLAGS = $(ARCOMMANDFLAGS)" $@)

$(LIB3):
	(cd ../Firmament; make "CCC=$(CCC)" "CCCFLAGS=$(CCCFLAGS)" \
         "OPTIMIZE=$(OPTIMIZE)"  "AR=$(ARCOMMAND)"  "ARFLAGS = $(ARCOMMANDFLAGS)" $@)

$(LIB4):$(OBJ)
	$(AR) $(ARCOMMANDFLAGS) $(LIB4) $(OBJ)

.cc.o: 
	$(CCC) $(OPTIMIZE) $(SUPPRESS) $(CCCFLAGS) $(INCLUDE)  $< -o $@

html:
	enscript -E --color -Whtml --toc -p$(PROGFILES) ./include/*.h ./*/*.cc
changelog:
	rm -rf ChangeLog
	rcs2log . > ChangeLog
clean:
	rm -rf $(OBJ) $(ALGOBJ) $(BLOBJ) core lignum algorithms broadleaf ii_files
	rm -rf ./*/ii_files
distclean: clean
	(cd ../c++adt/lib; make distclean)
	(cd ../Firmament; make distclean)
	(cd ../stl-lignum; make distclean)
depend:
	(cd ../c++adt; make depend)
	(cd ../Firmament; make depend)
	(cd ../stl-lignum; make depend)
	makedepend $(INCLUDE) $(CCCINCLUDE) $(STL) $(MAIN) $(ALGSRC) $(BLSRC)  

# DO NOT DELETE
