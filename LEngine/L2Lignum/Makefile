#To compile "l2lignum" on SGI type 
#    make l2lignum
#To compile with g++ on SGI or on Linux type 
#    make gnu 
#or copy paste
#    make "CCC=g++" "CCCFLAGS=-c" "OPTIMIZE=-O" "AR=ar"  "ARDFLAGS=rv" l2lignum

SRC= main.cc
OBJ  = ${SRC:.cc=.o}

LIBSRC= Turtle.cc
LIBOBJ = ${LIBSRC:.cc=.o}

BIRCHSRC = birch.cc
BIRCHOBJ =  ${BIRCHSRC:.cc=.o}

CCC = CC -64 -LANG:std

#OPTIMIZE = -Ofast=ip28 -IPA
OPTIMIZE   = -g 

AR =  $(CCC) -ar  
ARFLAGS = -o 

SUPPRESS = #-w 1155 -w 1183

CCCFLAGS = -c  #-prelink -ptused   -ptv  #  -fullwarn 

INCLUDE = -I../../c++adt/include -I../../Firmament/include \
          -I../../stl-lignum/include -I../include \
          -I../../Graphics -I/usr/freeware/include

STL     = -I/usr/include/CC

LIBD = lib64
LIBFLAGS = -L../../c++adt/lib -L../../stl-lignum/lib -L../../Firmament/lib \
           -L. -L../lsys -L../../Graphics -L/usr/X11R6/lib -L/usr/freeware/$(LIBD)

LIB1   = libc++adt.a
LIB2   = libLGM.a
LIB3   = libsky.a
LIB4   = libL.a
LIB5   = libVisual.a
LIB6   = liblsys.a

LIBADT = -lc++adt
LIBLGM = -lLGM
LIBSKY = -lsky
LIBL   = -lL
LIBMATH  = -lm 
LIBVISUAL = -lVisual
LIBLSYS = -llsys

LIBOGL =  -lglut -lGL -lGLU -lX11 -lXext -lXmu 

LIBS     =  $(LIBVISUAL) $(LIBLSYS) $(LIBL) $(LIBLGM) $(LIBSKY) $(LIBADT) $(LIBOGL) \
            $(LIBMATH)

LSYS =   bearberry.L pine9bp.L cs-plantA.L cs-plantB.L  cs-plantC.L \
         cs-plantD.L cs-plant.L 

PROGFILES = program-files.html

.SUFFIXES: .o .cc

sinclude Makedepend

l2lignum: $(OBJ) l2c $(LIB1) $(LIB2) $(LIB3)  $(LIB4)  $(LIB5) $(LIB6)   
	$(CCC)  -o $@ $(INCLUDE) $(OPTIMIZE) $(OBJ) $(LIBFLAGS) $(LIBS)

gnu:
	make "CCC=g++" "CCCFLAGS=-c" "OPTIMIZE=-g" \
             "AR=ar"  "ARFLAGS=rv" "LIBD=lib32"  l2lignum
lignux: 
	make "CCC=g++" "CCCFLAGS=-c" "OPTIMIZE=-g" \
             "AR=ar"  "ARFLAGS=rv" "LIBD=lib32" l2lignum

birch:  l2c $(BIRCHOBJ) $(LIB1) $(LIB2) $(LIB3)  $(LIB4) $(LIB5) $(LIB6)   
	$(CCC)  -o $@ $(INCLUDE) $(OPTIMIZE) $(BIRCHOBJ) $(LIBFLAGS) $(LIBS)

gnubirch:
	make "CCC=g++" "CCCFLAGS=-c" "OPTIMIZE=-g" \
             "AR=ar"  "ARFLAGS=rv" "LIBD=lib32" "LSYS=birch.L" birch
l2c:
	(cd ../L2C; make "CCC=$(CCC)" "CCCFLAGS=$(CCCFLAGS)" "OPTIMIZE=$(OPTIMIZE)" \
                          "AR=ar" "ARFLAGS=rv" $@)
$(LIB1):
	(cd ../../c++adt; make "CCC=$(CCC)" "CCCFLAGS=$(CCCFLAGS)" \
                               "OPTIMIZE=$(OPTIMIZE)" "AR=$(AR)" "ARFLAGS=$(ARFLAGS)" $@)
$(LIB2):
	(cd ../../stl-lignum; make "CCC=$(CCC)" "CCCFLAGS=$(CCCFLAGS)" \
                                   "OPTIMIZE=$(OPTIMIZE)" "AR=$(AR)" "ARFLAGS = $(ARFLAGS)" $@)
$(LIB3):
	(cd ../../Firmament; make "CCC=$(CCC)" "CCCFLAGS=$(CCCFLAGS)" \
         "OPTIMIZE=$(OPTIMIZE)"  "AR=$(AR)"  "ARFLAGS = $(ARFLAGS)" $@)
$(LIB4):$(LIBOBJ)
	 $(AR) $(ARFLAGS) $(@) $(LIBOBJ) 
$(LIB5):
	(cd ../../Graphics; make "CCC=$(CCC)" "CCCFLAGS=$(CCCFLAGS)" \
         "OPTIMIZE=$(OPTIMIZE)"  "AR=$(AR)"  "ARFLAGS = $(ARFLAGS)" $@)
$(LIB6):
	(cd ../lsys; make distclean; make "CCC=$(CCC)" "CCCFLAGS=$(CCCFLAGS)" \
         "OPTIMIZE=$(OPTIMIZE)"  "AR=$(AR)"  "ARFLAGS = $(ARFLAGS)" "LSYS=$(LSYS)" $@ )
.cc.o: 
	$(CCC) $(OPTIMIZE) $(CCCFLAGS) $(INCLUDE)  $< -o $@

html:
	enscript -E --color -Whtml --toc -p$(PROGFILES) ./include/*.h ./*/*.cc
changelog:
	rm -rf ChangeLog
	rcs2log . > ChangeLog
clean:
	rm -rf *.o  Makedepend core ii_files
distclean: clean
	rm -rf  l2lignum $(LIB4) Makedepend
	(cd ../../Graphics; make distclean)
	(cd ../L2C; make distclean)
	(cd ../lsys; make distclean)
#When creating dependencies leave out lsys directory.
#lsys directory contains only L-files that are
#to be compiled to C++ with l2c. It does not contain project program files. 
depend:
	(cd ../../Graphics; make "CCC=$(CCC)"  depend)
	(cd ../L2C; make "CCC=$(CCC)"  depend)
	$(CCC) -M $(INCLUDE) $(SRC) $(LIBSRC) $(BIRCHSRC) > Makedepend

