#To compile "algorithms" on SGI type 
#    make algorithms
#To compile with g++ on SGI or on  Linux type
#    make gnu  
#or  (using copy paste)
#    make "CCC=g++" "CCCFLAGS=-c" "OPTIMIZE=-O" "AR=ar"  "ARFLAGS=rv" algorithms 


ALGSRC = algorithms.cc 
ALGOBJ  = ${ALGSRC:.cc=.o} 

CCC = CC  -64 -LANG:std

#OPTIMIZE = -Ofast=ip28 -IPA
OPTIMIZE   = -g 

AR =  $(CCC) -ar  
ARFLAGS = -o 

SUPPRESS = #-w 1155 -w 1183

CCCFLAGS = -c  #-prelink -ptused   -ptv  #  -fullwarn 

INCLUDE = -Iinclude -I../c++adt/include -I../Firmament/include -I../ScotsPine/include

LIBFLAGS = -L../c++adt/lib -Llib -L../Firmament/lib

LIB1   = libc++adt.a
LIB2   = libLGM.a
LIB3   = libsky.a

LIBADT = -lc++adt
LIBLGM = -lLGM
LIBSKY = -lsky
LIBMATH  = -lm 

LIBS     = $(LIBLGM) $(LIBSKY) $(LIBADT) $(LIBMATH) 

PROGFILES = program-files.html
.SUFFIXES: .o .cc

algorithms: $(ALGOBJ) $(LIB1) $(LIB3)  $(LIB2) 
	$(CCC)  -o $@ $(INCLUDE) $(OPTIMIZE) $(ALGOBJ) $(LIBFLAGS) $(LIBS)
gnu:
	make "CCC=g++" "CCCFLAGS=-c" "OPTIMIZE=-g" "AR=ar" "ARFLAGS=rv" algorithms
lignux: 
	make "CCC=g++" "CCCFLAGS=-c" "OPTIMIZE=-g" "AR=ar" "ARFLAGS=rv" algorithms

lignum: $(OBJ) $(LIB1)  $(LIB2) $(LIB3)
	$(CCC)  -o $@ $(INCLUDE) $(OBJ) $(LIBFLAGS) $(LIBS) 

broadleaf: $(BLOBJ) $(LIB1)  $(LIB2) $(LIB3)
	$(CCC)   -o $@ $(INCLUDE) $(OPTIMIZE) $(BLOBJ) $(LIBFLAGS) $(LIBS)	
$(LIB1):
	(cd ../c++adt/; make "CCC=$(CCC)" "CCCFLAGS=$(CCCFLAGS)" \
         "OPTIMIZE=$(OPTIMIZE)" "AR=$(AR)"  "ARFLAGS = $(ARFLAGS)" $@)

$(LIB2):
	(cd lib; make "CCC=$(CCC)" "CCCFLAGS=$(CCCFLAGS)" "OPTIMIZE=$(OPTIMIZE)" \
         "AR=$(AR)" "ARFLAGS = $(ARFLAGS)" $@)

$(LIB3):
	(cd ../Firmament; make "CCC=$(CCC)" "CCCFLAGS=$(CCCFLAGS)" \
         "OPTIMIZE=$(OPTIMIZE)"  "AR=$(AR)"  "ARFLAGS = $(ARFLAGS)" $@)
.cc.o: 
	$(CCC) $(OPTIMIZE) $(SUPPRESS) $(CCCFLAGS) $(INCLUDE)  $< -o $@

html:
	enscript -E --color -Whtml --toc -p$(PROGFILES) ./include/*.h ./*/*.cc
clean:
	(cd lib; make clean)
	rm -rf $(OBJ) $(ALGOBJ) $(BLOBJ) core  ii_files
	rm -rf ./*/ii_files
distclean: clean
	rm -rf algorithms Makedepend
	(cd ../c++adt; make distclean)
	(cd ../Firmament; make distclean)
	(cd lib; make distclean)
depend:
	$(CCC) -M  $(INCLUDE) $(ALGSRC)  > Makedepend
	(cd ../c++adt; make "CCC=$(CCC)"  depend)
	(cd ../Firmament; make "CCC=$(CCC)"  depend)
	(cd lib; make "CCC=$(CCC)" depend)

#Do not delete this line -- make depend adds dependencies at the end of it
#If committing Makefile to cvs please remove the dependencies first

