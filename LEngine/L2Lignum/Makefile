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
           -L../Generate/IRIX64.out  -L../../Graphics

LIB1   = libc++adt.a
LIB2   = libLGM.a
LIB3   = libsky.a
LIB4   = liblengine.a
LIB5   = libVisual.a

LIBADT = -lc++adt
LIBLGM = -lLGM
LIBSKY = -lsky
LIBMATH  = -lm 
LIBLENGINE = -llengine 
LIBVISUAL = -lVisual

LIBOGL =  -lglut -lGL -lGLU -lX11 -lXext -lXmu 
LIBS     =  $(LIBVISUAL) $(LIBLGM) $(LIBSKY) $(LIBADT) $(LIBOGL) \
            $(LIBMATH) $(LIBLENGINE) 

PROGFILES = program-files.html

.SUFFIXES: .o .cc

l2lignum: $(OBJ) ../lsys/lsys.o $(LIB1) $(LIB3)  $(LIB2) 
	$(CCC)  -o $@ $(INCLUDE) $(OPTIMIZE) $(OBJ) ../lsys/lsys.o $(LIBFLAGS) $(LIBS)

lignux: 
	make "CCC=g++" "CCCFLAGS=-c" "OPTIMIZE=-O" "ARCOMMAND=ar"  "ARCOMMANDFLAGS=rv" l2lignum

../lsys/lsys.o:
	(cd ../lsys; make lsys.o)

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
	(cd ../Generate; make lib)
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
	(cd ../c++adt/lib; make distclean)
	(cd ../Firmament; make distclean)
	(cd lib; make distclean)
depend:
	makedepend $(INCLUDE) $(CCCINCLUDE) $(STL) $(SRC)  

