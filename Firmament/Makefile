MAIN = Firmament.cc
OBJ  = Firmament.o

 
CCC = CC -64

AR = $(CCC) -ar  
ARFLAGS = -o 
ARFILE = lib/libsky.a

#OPTIMIZE = -Ofast=ip28 -IPA
OPTIMIZE   = -g 

SUPPRESS = #-w 1155 -w 1183

CCCFLAGS = -c -ptv -prelink #-fullwarn 

INCLUDE =  -Iinclude -I../c++adt/include -I../stl-lignum/include 
STL     = -I/usr/include/CC

LIBFLAGS = -L../c++adt/lib -L../stl-lignum/lib 

#LIB1   = libc++adt.a

#LIBADT = -lc++adt
LIBMATH  = -lm 
LIBS     = $(LIBMATH)

.SUFFIXES: .o .cc

libsky.a:  $(OBJ)
	$(AR) $(ARFLAGS) $(ARFILE) $(OBJ)
sky: $(MAIN)  
	$(CCC) -DFIRMAMENT -g  -o $@  $(INCLUDE)  $(MAIN)  \
	$(LIBFLAGS) $(LIBS) 

#$(LIB1): 
#	(cd ../c++adt/lib; make "CCC=$(CCC)" "CCCFLAGS=$(CCCFLAGS)" \
#        "OPTIMIZE=$(OPTIMIZE)" $@)


.cc.o: 
	$(CCC) $(OPTIMIZE) $(SUPPRESS) $(CCCFLAGS) $(INCLUDE) $< -o $@

clean:
	rm -rf $(OBJ) core sky ii_files
	rm -rf $(ARFILE)
distclean:
	(cd ../c++adt/lib; make distclean)
	rm -rf $(OBJ)  core sky ii_files 
	rm -rf $(ARFILE)
depend: 
	makedepend $(INCLUDE) $(STL) $(MAIN)
# DO NOT DELETE

Firmament.o: include/Firmament.h /usr/include/math.h /usr/include/sgidefs.h
Firmament.o: /usr/include/standards.h ../c++adt/include/mathsym.h
Firmament.o: /usr/include/CC/vector /usr/include/CC/stl_range_errors.h
Firmament.o: /usr/include/CC/stl_config.h /usr/include/CC/stl_algobase.h
Firmament.o: /usr/include/CC/stl_relops.h /usr/include/CC/stl_pair.h
Firmament.o: /usr/include/CC/type_traits.h /usr/include/string.h
Firmament.o: /usr/include/limits.h /usr/include/stdlib.h
Firmament.o: /usr/include/stddef.h /usr/include/CC/new.h
Firmament.o: /usr/include/CC/iostream.h /usr/include/memory.h
Firmament.o: /usr/include/CC/stl_iterator_base.h
Firmament.o: /usr/include/CC/stl_iterator.h /usr/include/CC/stl_alloc.h
Firmament.o: /usr/include/stdio.h /usr/include/assert.h
Firmament.o: /usr/include/CC/stl_construct.h
Firmament.o: /usr/include/CC/stl_uninitialized.h /usr/include/CC/stl_vector.h
Firmament.o: /usr/include/CC/stl_bvector.h ../c++adt/include/TMatrix.h
Firmament.o: /usr/include/CC/stream.h /usr/include/CC/iomanip.h
Firmament.o: /usr/include/CC/generic.h /usr/include/CC/stdiostream.h
Firmament.o: /usr/include/CC/fstream.h ../c++adt/include/TMatrixI.h
Firmament.o: ../stl-lignum/include/LGMUnits.h
