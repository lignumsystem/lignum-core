#To compile "algorithms" on SGI type 
#    make algorithms
#To compile with g++ in Linux type (or copy paste)
#    make "CCC=g++" "CCCFLAGS=-c" "OPTIMIZE=-O" "ARCOMMAND=ar"  "ARCOMMANDFLAGS=rv" algorithms 

MAIN = Turtle.cc
OBJ  = Turtle.o
 
CCC = CC  -LANG:std

#OPTIMIZE = -Ofast=ip28 -IPA
OPTIMIZE   = -g 

ARCOMMAND =  $(CCC) -ar  
ARCOMMANDFLAGS = -o 

SUPPRESS = #-w 1155 -w 1183

CCCFLAGS = -c  #-prelink -ptused   -ptv  #  -fullwarn 

INCLUDE = -I../../stl-lignum/include  -I../../c++adt/include -I../../Firmament/include -I.

STL     = -I/usr/include/CC

LIBFLAGS = -L../../stl-lignum/lib -L../../c++adt/lib -Llib -L../../Firmament/lib

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

lignux: 
	make "CCC=g++" "CCCFLAGS=-c" "OPTIMIZE=-O" "ARCOMMAND=ar"  "ARCOMMANDFLAGS=rv" turtle

turtle: $(OBJ) $(LIB1) $(LIB3)  $(LIB2)
	$(CCC)  -DTURTLE -o $@ $(INCLUDE) $(OPTIMIZE) $(OBJ) $(LIBFLAGS) $(LIBS)

$(LIB1):
	(cd ../../c++adt/lib; make "CCC=$(CCC)" "CCCFLAGS=$(CCCFLAGS)" \
         "OPTIMIZE=$(OPTIMIZE)" "AR=$(ARCOMMAND)"  "ARFLAGS = $(ARCOMMANDFLAGS)" $@)

$(LIB2):
	(cd ../../stl-lignum/lib; make "CCC=$(CCC)" "CCCFLAGS=$(CCCFLAGS)" "OPTIMIZE=$(OPTIMIZE)" "AR=$(ARCOMMAND)" \
         "ARFLAGS = $(ARCOMMANDFLAGS)" $@)

$(LIB3):
	(cd ../../Firmament; make "CCC=$(CCC)" "CCCFLAGS=$(CCCFLAGS)" \
         "OPTIMIZE=$(OPTIMIZE)"  "AR=$(ARCOMMAND)"  "ARFLAGS = $(ARCOMMANDFLAGS)" $@)
.cc.o: 
	$(CCC) -DTURTLE $(OPTIMIZE) $(SUPPRESS) $(CCCFLAGS) $(INCLUDE)  $< -o $@

html:
	enscript -E --color -Whtml --toc -p$(PROGFILES) ./include/*.h ./*/*.cc
changelog:
	rm -rf ChangeLog
	rcs2log . > ChangeLog
clean:
	rm -rf  core turtle Turtle.o ii_files
	rm -rf ./*/ii_files
distclean: clean
	(cd ../../c++adt/lib; make distclean)
	(cd ../../Firmament; make distclean)
	(cd ../../stl-lignum/lib; make distclean)
depend:
	(cd ../../stl-lignum/; make depend)
	makedepend $(INCLUDE) $(CCCINCLUDE) $(STL) $(MAIN) $(ALGSRC) $(BLSRC)  

# DO NOT DELETE


Turtle..o: ../../c++adt/include/mathsym.h ../../c++adt/include/Point.h
Turtle..o: ../../c++adt/include/PointI.h ../../c++adt/include/PositionVector.h
Turtle..o: ../../c++adt/include/RMatrix.h ../../c++adt/include/Rotation.h
Turtle..o: ../../c++adt/include/TMatrix.h ../../c++adt/include/TMatrixI.h
Turtle..o: Turtle.h /usr/include/alloca.h /usr/include/assert.h
Turtle..o: /usr/include/bits/huge_val.h /usr/include/bits/local_lim.h
Turtle..o: /usr/include/bits/mathcalls.h /usr/include/bits/mathdef.h
Turtle..o: /usr/include/bits/nan.h /usr/include/bits/posix1_lim.h
Turtle..o: /usr/include/bits/pthreadtypes.h /usr/include/bits/sched.h
Turtle..o: /usr/include/bits/sigset.h /usr/include/bits/types.h
Turtle..o: /usr/include/bits/waitstatus.h /usr/include/bits/xopen_lim.h
Turtle..o: /usr/include/endian.h /usr/include/features.h
Turtle..o: /usr/include/g++-3/iostream /usr/include/g++-3/iostream.h
Turtle..o: /usr/include/g++-3/stl_algobase.h /usr/include/g++-3/stl_alloc.h
Turtle..o: /usr/include/g++-3/stl_bvector.h /usr/include/g++-3/stl_construct.h
Turtle..o: /usr/include/g++-3/stl_iterator.h /usr/include/g++-3/stl_pair.h
Turtle..o: /usr/include/g++-3/stl_relops.h
Turtle..o: /usr/include/g++-3/stl_uninitialized.h
Turtle..o: /usr/include/g++-3/stl_vector.h /usr/include/g++-3/streambuf.h
Turtle..o: /usr/include/g++-3/type_traits.h /usr/include/g++-3/vector
Turtle..o: /usr/include/_G_config.h /usr/include/gconv.h /usr/include/libio.h
Turtle..o: /usr/include/limits.h /usr/include/math.h /usr/include/stdlib.h
Turtle..o: /usr/include/string.h /usr/include/sys/select.h
Turtle..o: /usr/include/sys/types.h /usr/include/time.h /usr/include/wchar.h
Turtle..o: /usr/include/xlocale.h
Turtle..o: /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/exception
Turtle..o: /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/float.h
Turtle..o: /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/limits.h
Turtle..o: /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/new
Turtle..o: /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/new.h
Turtle..o: /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/stdarg.h
Turtle..o: /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/stddef.h
Turtle..o: /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/syslimits.h
