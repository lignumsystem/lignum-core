MAIN = Firmament.cc FirmamentWithMask.cc MineSet.cc
OBJ  = Firmament.o  FirmamentWithMask.o MineSet.o
 
CCC = CC -64 -LANG:std

AR = $(CCC) -ar  
ARFLAGS = -o 
ARFILE = lib/libsky.a

#OPTIMIZE = -Ofast=ip28 -IPA
OPTIMIZE   = -g 

SUPPRESS = #-w 1155 -w 1183

CCCFLAGS = -c #-ptv -prelink -fullwarn 

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

Firmament.o: include/Firmament.h /usr/include/CC/iostream
Firmament.o: /usr/include/CC/iosfwd /usr/include/CC/stl_config.h
Firmament.o: /usr/include/standards.h /usr/include/wchar.h
Firmament.o: /usr/include/sgidefs.h /usr/include/locale_attr.h
Firmament.o: /usr/include/stdio.h /usr/include/ctype.h /usr/include/time.h
Firmament.o: /usr/include/stddef.h /usr/include/CC/functional
Firmament.o: /usr/include/CC/stl_function.h /usr/include/CC/char_traits.h
Firmament.o: /usr/include/string.h /usr/include/CC/istream
Firmament.o: /usr/include/CC/ostream /usr/include/CC/ios
Firmament.o: /usr/include/CC/stl_string_fwd.h /usr/include/CC/stl_alloc.h
Firmament.o: /usr/include/stdlib.h /usr/include/assert.h
Firmament.o: /usr/include/CC/stl_threads.h /usr/include/mutex.h
Firmament.o: /usr/include/CC/stl_exception.h /usr/include/CC/utility
Firmament.o: /usr/include/CC/stl_relops.h /usr/include/CC/stl_pair.h
Firmament.o: /usr/include/CC/stl_locale.h /usr/include/CC/typeinfo
Firmament.o: /usr/include/CC/exception /usr/include/CC/string
Firmament.o: /usr/include/CC/stdexcept /usr/include/CC/stl_iterator_base.h
Firmament.o: /usr/include/CC/memory /usr/include/CC/stl_algobase.h
Firmament.o: /usr/include/CC/type_traits.h /usr/include/limits.h
Firmament.o: /usr/include/CC/new.h /usr/include/CC/iostream.h
Firmament.o: /usr/include/memory.h /usr/include/CC/stl_iterator.h
Firmament.o: /usr/include/CC/stl_construct.h /usr/include/CC/stl_tempbuf.h
Firmament.o: /usr/include/CC/stl_uninitialized.h
Firmament.o: /usr/include/CC/stl_raw_storage_iter.h /usr/include/CC/algorithm
Firmament.o: /usr/include/CC/stl_algo.h /usr/include/CC/stl_heap.h
Firmament.o: /usr/include/CC/stl_hash_fun.h /usr/include/CC/stl_ctype.h
Firmament.o: /usr/include/CC/c_locale.h /usr/include/CC/streambuf
Firmament.o: /usr/include/CC/stl_stdio_file.h
Firmament.o: /usr/include/CC/stl_numeric_facets.h /usr/include/CC/limits
Firmament.o: /usr/include/float.h /usr/include/CC/fstream
Firmament.o: /usr/include/CC/stl_codecvt.h /usr/include/math.h
Firmament.o: ../c++adt/include/mathsym.h /usr/include/CC/vector
Firmament.o: /usr/include/CC/stl_range_errors.h /usr/include/CC/stl_vector.h
Firmament.o: /usr/include/CC/stl_bvector.h ../c++adt/include/TMatrix.h
Firmament.o: ../c++adt/include/TMatrixI.h ../stl-lignum/include/LGMUnits.h
FirmamentWithMask.o: /usr/include/stdlib.h /usr/include/standards.h
FirmamentWithMask.o: /usr/include/sgidefs.h include/FirmamentWithMask.h
FirmamentWithMask.o: include/Firmament.h /usr/include/CC/iostream
FirmamentWithMask.o: /usr/include/CC/iosfwd /usr/include/CC/stl_config.h
FirmamentWithMask.o: /usr/include/wchar.h /usr/include/locale_attr.h
FirmamentWithMask.o: /usr/include/stdio.h /usr/include/ctype.h
FirmamentWithMask.o: /usr/include/time.h /usr/include/stddef.h
FirmamentWithMask.o: /usr/include/CC/functional
FirmamentWithMask.o: /usr/include/CC/stl_function.h
FirmamentWithMask.o: /usr/include/CC/char_traits.h /usr/include/string.h
FirmamentWithMask.o: /usr/include/CC/istream /usr/include/CC/ostream
FirmamentWithMask.o: /usr/include/CC/ios /usr/include/CC/stl_string_fwd.h
FirmamentWithMask.o: /usr/include/CC/stl_alloc.h /usr/include/assert.h
FirmamentWithMask.o: /usr/include/CC/stl_threads.h /usr/include/mutex.h
FirmamentWithMask.o: /usr/include/CC/stl_exception.h /usr/include/CC/utility
FirmamentWithMask.o: /usr/include/CC/stl_relops.h /usr/include/CC/stl_pair.h
FirmamentWithMask.o: /usr/include/CC/stl_locale.h /usr/include/CC/typeinfo
FirmamentWithMask.o: /usr/include/CC/exception /usr/include/CC/string
FirmamentWithMask.o: /usr/include/CC/stdexcept
FirmamentWithMask.o: /usr/include/CC/stl_iterator_base.h
FirmamentWithMask.o: /usr/include/CC/memory /usr/include/CC/stl_algobase.h
FirmamentWithMask.o: /usr/include/CC/type_traits.h /usr/include/limits.h
FirmamentWithMask.o: /usr/include/CC/new.h /usr/include/CC/iostream.h
FirmamentWithMask.o: /usr/include/memory.h /usr/include/CC/stl_iterator.h
FirmamentWithMask.o: /usr/include/CC/stl_construct.h
FirmamentWithMask.o: /usr/include/CC/stl_tempbuf.h
FirmamentWithMask.o: /usr/include/CC/stl_uninitialized.h
FirmamentWithMask.o: /usr/include/CC/stl_raw_storage_iter.h
FirmamentWithMask.o: /usr/include/CC/algorithm /usr/include/CC/stl_algo.h
FirmamentWithMask.o: /usr/include/CC/stl_heap.h
FirmamentWithMask.o: /usr/include/CC/stl_hash_fun.h
FirmamentWithMask.o: /usr/include/CC/stl_ctype.h /usr/include/CC/c_locale.h
FirmamentWithMask.o: /usr/include/CC/streambuf
FirmamentWithMask.o: /usr/include/CC/stl_stdio_file.h
FirmamentWithMask.o: /usr/include/CC/stl_numeric_facets.h
FirmamentWithMask.o: /usr/include/CC/limits /usr/include/float.h
FirmamentWithMask.o: /usr/include/CC/fstream /usr/include/CC/stl_codecvt.h
FirmamentWithMask.o: /usr/include/math.h ../c++adt/include/mathsym.h
FirmamentWithMask.o: /usr/include/CC/vector
FirmamentWithMask.o: /usr/include/CC/stl_range_errors.h
FirmamentWithMask.o: /usr/include/CC/stl_vector.h
FirmamentWithMask.o: /usr/include/CC/stl_bvector.h
FirmamentWithMask.o: ../c++adt/include/TMatrix.h ../c++adt/include/TMatrixI.h
FirmamentWithMask.o: ../stl-lignum/include/LGMUnits.h ../c++adt/include/Lex.h
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
MineSet.o: /usr/include/CC/stl_iterator.h /usr/include/CC/stl_construct.h
MineSet.o: /usr/include/CC/stl_tempbuf.h /usr/include/CC/stl_uninitialized.h
MineSet.o: /usr/include/CC/stl_raw_storage_iter.h /usr/include/CC/algorithm
MineSet.o: /usr/include/CC/stl_algo.h /usr/include/CC/stl_heap.h
MineSet.o: /usr/include/CC/char_traits.h /usr/include/wchar.h
MineSet.o: /usr/include/CC/stl_hash_fun.h ../c++adt/include/Lex.h
MineSet.o: /usr/include/CC/fstream /usr/include/CC/istream
MineSet.o: /usr/include/CC/ostream /usr/include/CC/ios
MineSet.o: /usr/include/CC/utility /usr/include/CC/stl_relops.h
MineSet.o: /usr/include/CC/stl_pair.h /usr/include/CC/iosfwd
MineSet.o: /usr/include/CC/stl_locale.h /usr/include/CC/typeinfo
MineSet.o: /usr/include/CC/exception /usr/include/CC/stl_ctype.h
MineSet.o: /usr/include/CC/c_locale.h /usr/include/CC/streambuf
MineSet.o: /usr/include/CC/stl_stdio_file.h
MineSet.o: /usr/include/CC/stl_numeric_facets.h /usr/include/CC/limits
MineSet.o: /usr/include/float.h /usr/include/CC/stl_codecvt.h
MineSet.o: ../c++adt/include/DList.h ../c++adt/include/DListElement.h
MineSet.o: ../c++adt/include/boolean.h include/Firmament.h
MineSet.o: /usr/include/CC/iostream /usr/include/math.h
MineSet.o: ../c++adt/include/mathsym.h /usr/include/CC/vector
MineSet.o: /usr/include/CC/stl_range_errors.h /usr/include/CC/stl_vector.h
MineSet.o: /usr/include/CC/stl_bvector.h ../c++adt/include/TMatrix.h
MineSet.o: ../c++adt/include/TMatrixI.h ../stl-lignum/include/LGMUnits.h
MineSet.o: include/FirmamentWithMask.h
