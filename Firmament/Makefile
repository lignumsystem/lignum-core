MAIN = Firmament.cc FirmamentWithMask.cc MineSet.cc
OBJ  = Firmament.o  FirmamentWithMask.o MineSet.o
 
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

LIBFLAGS = -L../c++adt/lib -L../stl-lignum/lib -Llib 

#LIB1   = libc++adt.a

#LIBADT = -lc++adt
LIBMATH  = -lm 
LIBS     = -lsky -lc++adt $(LIBMATH)

.SUFFIXES: .o .cc

libsky.a:  $(OBJ)
	$(AR) $(ARFLAGS) $(ARFILE) $(OBJ)
libc++adt.a:
	(cd ../c++adt/lib; make "CCC=$(CCC)" "CCCFLAGS=$(CCCFLAGS)" \
         "OPTIMIZE=$(OPTIMIZE)" "AR=$(AR)"  "ARFLAGS = $(ARFLAGS)" $@)
sky: $(MAIN)  
	$(CCC) -DFIRMAMENT -g  -o $@  $(INCLUDE)  $(MAIN)  \
	$(LIBFLAGS) $(LIBS) 
sky-dump: sky-dump.o libsky.a libc++adt.a
	$(CCC) sky-dump.o  $(OPTIMIZE)  $(INCLUDE) \
        $(LIBFLAGS) $(LIBS)  -o $@
.cc.o: 
	$(CCC) $(OPTIMIZE) $(SUPPRESS) $(CCCFLAGS) $(INCLUDE) $< -o $@

clean:
	rm -rf $(OBJ) sky sky-dump sky-dump.o core sky ii_files
	rm -rf $(ARFILE)
distclean:
	(cd ../c++adt/lib; make distclean)
	make clean

depend: 
	makedepend $(INCLUDE) $(STL) $(MAIN)
# DO NOT DELETE

Firmament.o: include/Firmament.h /usr/include/math.h /usr/include/sgidefs.h
Firmament.o: /usr/include/standards.h ../c++adt/include/mathsym.h
Firmament.o: /usr/include/CC/vector.h /usr/include/CC/stl_range_errors.h
Firmament.o: /usr/include/CC/stl_config.h /usr/include/CC/algobase.h
Firmament.o: /usr/include/CC/pair.h /usr/include/CC/stl_relops.h
Firmament.o: /usr/include/CC/stl_pair.h /usr/include/CC/iterator.h
Firmament.o: /usr/include/CC/function.h /usr/include/stddef.h
Firmament.o: /usr/include/CC/stl_function.h /usr/include/CC/iostream.h
Firmament.o: /usr/include/memory.h /usr/include/CC/stl_iterator_base.h
Firmament.o: /usr/include/CC/stl_iterator.h /usr/include/CC/type_traits.h
Firmament.o: /usr/include/CC/stl_construct.h /usr/include/CC/new.h
Firmament.o: /usr/include/CC/stl_raw_storage_iter.h
Firmament.o: /usr/include/CC/stl_algobase.h /usr/include/string.h
Firmament.o: /usr/include/limits.h /usr/include/stdlib.h
Firmament.o: /usr/include/CC/stl_uninitialized.h /usr/include/CC/alloc.h
Firmament.o: /usr/include/CC/stl_alloc.h /usr/include/stdio.h
Firmament.o: /usr/include/assert.h /usr/include/CC/stl_threads.h
Firmament.o: /usr/include/mutex.h /usr/include/time.h
Firmament.o: /usr/include/CC/stl_vector.h ../c++adt/include/TMatrix.h
Firmament.o: /usr/include/CC/stream.h /usr/include/CC/iomanip.h
Firmament.o: /usr/include/CC/generic.h /usr/include/CC/stdiostream.h
Firmament.o: /usr/include/CC/fstream.h /usr/include/CC/vector
Firmament.o: /usr/include/CC/stl_bvector.h ../c++adt/include/TMatrixI.h
Firmament.o: ../stl-lignum/include/LGMUnits.h
FirmamentWithMask.o: /usr/include/stdlib.h /usr/include/standards.h
FirmamentWithMask.o: /usr/include/sgidefs.h include/FirmamentWithMask.h
FirmamentWithMask.o: include/Firmament.h /usr/include/math.h
FirmamentWithMask.o: ../c++adt/include/mathsym.h /usr/include/CC/vector.h
FirmamentWithMask.o: /usr/include/CC/stl_range_errors.h
FirmamentWithMask.o: /usr/include/CC/stl_config.h /usr/include/CC/algobase.h
FirmamentWithMask.o: /usr/include/CC/pair.h /usr/include/CC/stl_relops.h
FirmamentWithMask.o: /usr/include/CC/stl_pair.h /usr/include/CC/iterator.h
FirmamentWithMask.o: /usr/include/CC/function.h /usr/include/stddef.h
FirmamentWithMask.o: /usr/include/CC/stl_function.h
FirmamentWithMask.o: /usr/include/CC/iostream.h /usr/include/memory.h
FirmamentWithMask.o: /usr/include/CC/stl_iterator_base.h
FirmamentWithMask.o: /usr/include/CC/stl_iterator.h
FirmamentWithMask.o: /usr/include/CC/type_traits.h
FirmamentWithMask.o: /usr/include/CC/stl_construct.h /usr/include/CC/new.h
FirmamentWithMask.o: /usr/include/CC/stl_raw_storage_iter.h
FirmamentWithMask.o: /usr/include/CC/stl_algobase.h /usr/include/string.h
FirmamentWithMask.o: /usr/include/limits.h
FirmamentWithMask.o: /usr/include/CC/stl_uninitialized.h
FirmamentWithMask.o: /usr/include/CC/alloc.h /usr/include/CC/stl_alloc.h
FirmamentWithMask.o: /usr/include/stdio.h /usr/include/assert.h
FirmamentWithMask.o: /usr/include/CC/stl_threads.h /usr/include/mutex.h
FirmamentWithMask.o: /usr/include/time.h /usr/include/CC/stl_vector.h
FirmamentWithMask.o: ../c++adt/include/TMatrix.h /usr/include/CC/stream.h
FirmamentWithMask.o: /usr/include/CC/iomanip.h /usr/include/CC/generic.h
FirmamentWithMask.o: /usr/include/CC/stdiostream.h /usr/include/CC/fstream.h
FirmamentWithMask.o: /usr/include/CC/vector /usr/include/CC/stl_bvector.h
FirmamentWithMask.o: ../c++adt/include/TMatrixI.h
FirmamentWithMask.o: ../stl-lignum/include/LGMUnits.h /usr/include/CC/string
FirmamentWithMask.o: /usr/include/CC/stl_string_fwd.h /usr/include/ctype.h
FirmamentWithMask.o: /usr/include/locale_attr.h /usr/include/CC/functional
FirmamentWithMask.o: /usr/include/CC/stdexcept
FirmamentWithMask.o: /usr/include/CC/stl_exception.h /usr/include/CC/memory
FirmamentWithMask.o: /usr/include/CC/stl_tempbuf.h /usr/include/CC/algorithm
FirmamentWithMask.o: /usr/include/CC/stl_algo.h /usr/include/CC/stl_heap.h
FirmamentWithMask.o: /usr/include/CC/char_traits.h /usr/include/wchar.h
FirmamentWithMask.o: /usr/include/CC/stl_hash_fun.h ../c++adt/include/Lex.h
FirmamentWithMask.o: ../c++adt/include/DList.h
FirmamentWithMask.o: ../c++adt/include/DListElement.h
FirmamentWithMask.o: ../c++adt/include/boolean.h
MineSet.o: /usr/include/stdlib.h /usr/include/standards.h
MineSet.o: /usr/include/sgidefs.h /usr/include/CC/string
MineSet.o: /usr/include/CC/stl_config.h /usr/include/CC/stl_string_fwd.h
MineSet.o: /usr/include/stddef.h /usr/include/CC/stl_alloc.h
MineSet.o: /usr/include/stdio.h /usr/include/string.h /usr/include/assert.h
MineSet.o: /usr/include/CC/stl_threads.h /usr/include/mutex.h
MineSet.o: /usr/include/time.h /usr/include/ctype.h
MineSet.o: /usr/include/locale_attr.h /usr/include/CC/functional
MineSet.o: /usr/include/CC/stl_function.h /usr/include/CC/stdexcept
MineSet.o: /usr/include/CC/stl_exception.h
MineSet.o: /usr/include/CC/stl_iterator_base.h /usr/include/CC/memory
MineSet.o: /usr/include/CC/stl_algobase.h /usr/include/CC/type_traits.h
MineSet.o: /usr/include/limits.h /usr/include/CC/new.h
MineSet.o: /usr/include/CC/iostream.h /usr/include/memory.h
MineSet.o: /usr/include/CC/stl_construct.h /usr/include/CC/stl_tempbuf.h
MineSet.o: /usr/include/CC/stl_uninitialized.h
MineSet.o: /usr/include/CC/stl_raw_storage_iter.h /usr/include/CC/algorithm
MineSet.o: /usr/include/CC/stl_algo.h /usr/include/CC/stl_heap.h
MineSet.o: /usr/include/CC/char_traits.h /usr/include/wchar.h
MineSet.o: /usr/include/CC/stl_hash_fun.h ../c++adt/include/Lex.h
MineSet.o: /usr/include/CC/fstream.h ../c++adt/include/DList.h
MineSet.o: ../c++adt/include/DListElement.h ../c++adt/include/boolean.h
MineSet.o: include/Firmament.h /usr/include/math.h
MineSet.o: ../c++adt/include/mathsym.h /usr/include/CC/vector.h
MineSet.o: /usr/include/CC/stl_range_errors.h /usr/include/CC/algobase.h
MineSet.o: /usr/include/CC/pair.h /usr/include/CC/stl_relops.h
MineSet.o: /usr/include/CC/stl_pair.h /usr/include/CC/iterator.h
MineSet.o: /usr/include/CC/function.h /usr/include/CC/stl_iterator.h
MineSet.o: /usr/include/CC/alloc.h /usr/include/CC/stl_vector.h
MineSet.o: ../c++adt/include/TMatrix.h /usr/include/CC/stream.h
MineSet.o: /usr/include/CC/iomanip.h /usr/include/CC/generic.h
MineSet.o: /usr/include/CC/stdiostream.h /usr/include/CC/vector
MineSet.o: /usr/include/CC/stl_bvector.h ../c++adt/include/TMatrixI.h
MineSet.o: ../stl-lignum/include/LGMUnits.h include/FirmamentWithMask.h
