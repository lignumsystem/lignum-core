#To compile "algorithms" on SGI type 
#    make algorithms
#To compile with g++ in Linux type (or copy paste)
#    make "CCC=g++" "CCCFLAGS=-c" "OPTIMIZE=-O" "ARCOMMAND=ar"  "ARCOMMANDFLAGS=rv" algorithms 

SRC= Turtle.cc main.cc
OBJ  = Turtle.o main.o

CCC = CC -64 -LANG:std

#OPTIMIZE = -Ofast=ip28 -IPA
OPTIMIZE   = -g 

ARCOMMAND =  $(CCC) -ar  
ARCOMMANDFLAGS = -o 

SUPPRESS = #-w 1155 -w 1183

CCCFLAGS = -c  #-prelink -ptused   -ptv  #  -fullwarn 

INCLUDE = -I. -I../../c++adt/include -I../../Firmament/include \
          -I../../stl-lignum/include -I../Generate -I../Globals \
           -I../../Graphics

STL     = -I/usr/include/CC

LIBFLAGS = -L../../c++adt/lib -L../../stl-lignum/lib -L../../Firmament/lib \
           -L../Generate/IRIX64.out -L../Generate/Linux.out \
	   -L../lsys/IRIX64.out -L../lsys/Linux.out \
           -L../../Graphics -L/usr/X11R6/lib

LIB1   = libc++adt.a
LIB2   = libLGM.a
LIB3   = libsky.a
LIB4   = liblengine.a
LIB5   = libVisual.a
LIB6   = liblsys.a

LIBADT = -lc++adt
LIBLGM = -lLGM
LIBSKY = -lsky
LIBMATH  = -lm 
LIBLENGINE = -llengine 
LIBVISUAL = -lVisual
LIBL = -llsys

LIBOGL =  -lglut -lGL -lGLU -lX11 -lXext -lXmu 
LIBS     =  $(LIBVISUAL) $(LIBLENGINE) $(LIBL) $(LIBLGM) $(LIBSKY) $(LIBADT) $(LIBOGL) \
            $(LIBMATH) 

PROGFILES = program-files.html

.SUFFIXES: .o .cc

l2lignum: $(OBJ) l2c $(LIB1) $(LIB2) $(LIB3)  $(LIB4)  $(LIB5)  $(LIB6) 
	$(CCC)  -o $@ $(INCLUDE) $(OPTIMIZE) $(OBJ) $(LIBFLAGS) $(LIBS)

lignux: 
	make "CCC=g++" "CCCFLAGS=-c" "OPTIMIZE=-O" "ARCOMMAND=ar"  "ARCOMMANDFLAGS=rv" l2lignum

l2c:
	(cd ../L2C; make "CCC=$(CCC)" "CCCFLAGS=$(CCCFLAGS)" \
	 "OPTIMIZE=$(OPTIMIZE)")
$(LIB1):
	(cd ../../c++adt/lib; make "CCC=$(CCC)" "CCCFLAGS=$(CCCFLAGS)" \
         "OPTIMIZE=$(OPTIMIZE)" "AR=$(ARCOMMAND)"  "ARFLAGS = $(ARCOMMANDFLAGS)" $@)
$(LIB2):
	(cd ../../stl-lignum/lib; make "CCC=$(CCC)" "CCCFLAGS=$(CCCFLAGS)" "OPTIMIZE=$(OPTIMIZE)" "AR=$(ARCOMMAND)" \
         "ARFLAGS = $(ARCOMMANDFLAGS)" $@)

$(LIB3):
	(cd ../../Firmament; make "CCC=$(CCC)" "CCCFLAGS=$(CCCFLAGS)" \
         "OPTIMIZE=$(OPTIMIZE)"  "AR=$(ARCOMMAND)"  "ARFLAGS = $(ARCOMMANDFLAGS)" $@)
$(LIB4):
	(cd ../Generate; make "CCC=$(CCC)" "CCCFLAGS=$(CCCFLAGS)" \
         "OPTIMIZE=$(OPTIMIZE)"  "AR=$(ARCOMMAND)"  "ARFLAGS = $(ARCOMMANDFLAGS)")
$(LIB5):
	(cd ../../Graphics; make "CCC=$(CCC)" "CCCFLAGS=$(CCCFLAGS)" \
         "OPTIMIZE=$(OPTIMIZE)"  "AR=$(ARCOMMAND)"  "ARFLAGS = $(ARCOMMANDFLAGS)" )

$(LIB6):
	(cd ../lsys; make "CCC=$(CCC)" "CCCFLAGS=$(CCCFLAGS)" \
         "OPTIMIZE=$(OPTIMIZE)"  "AR=$(ARCOMMAND)"  "ARFLAGS = $(ARCOMMANDFLAGS)" )
.cc.o: 
	$(CCC) $(OPTIMIZE) $(SUPPRESS) $(CCCFLAGS) $(INCLUDE)  $< -o $@

html:
	enscript -E --color -Whtml --toc -p$(PROGFILES) ./include/*.h ./*/*.cc
changelog:
	rm -rf ChangeLog
	rcs2log . > ChangeLog
clean:
	rm -rf $(OBJ)  core l2lignum ii_files
	rm -rf ./*/ii_files
distclean: clean
	(cd ../../stl-lignum/lib; make distclean)
	(cd ../../Graphics; make distclean)
	(cd ../Generate; make clean)
	(cd ../L2C; make clean)
	(cd ../lsys; make clean)
depend:
	makedepend $(INCLUDE) $(CCCINCLUDE) $(STL) $(SRC)  

