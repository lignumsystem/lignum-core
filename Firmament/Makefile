MAIN = Firmament.cc FirmamentWithMask.cc MineSet.cc Interlen.cc Voxel.cc voxellattice.cc voxelmatrix.cc
OBJ  = Firmament.o  FirmamentWithMask.o MineSet.o Interlen.o Voxel.o voxellattice.o voxelmatrix.o 
 
CCC = CC -64 -LANG:std

ARCOMMAND=$(CCC) -ar
ARCOMMANDFLAGS= -o
AR = $(ARCOMMAND)  
ARFLAGS = $(ARCOMMANDFLAGS) 
ARFILE = lib/libsky.a


#OPTIMIZE = -Ofast=ip28 -IPA
OPTIMIZE   = -g 

SUPPRESS = #-w 1155 -w 1183

CCCFLAGS = -c #-ptv -prelink -fullwarn 

INCLUDE =  -Iinclude -I../c++adt/include -I../stl-lignum/include -I../ScotsPine/include 
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
MineSet.o: /usr/include/CC/iostream ../c++adt/include/DList.h
MineSet.o: ../c++adt/include/DListElement.h ../c++adt/include/boolean.h
MineSet.o: include/Firmament.h /usr/include/math.h
MineSet.o: ../c++adt/include/mathsym.h /usr/include/CC/vector
MineSet.o: /usr/include/CC/stl_range_errors.h /usr/include/CC/stl_vector.h
MineSet.o: /usr/include/CC/stl_bvector.h ../c++adt/include/TMatrix.h
MineSet.o: ../c++adt/include/TMatrixI.h ../stl-lignum/include/LGMUnits.h
MineSet.o: include/FirmamentWithMask.h
Interlen.o: ../c++adt/include/stdafx.h /usr/include/math.h
Interlen.o: /usr/include/sgidefs.h /usr/include/standards.h
Interlen.o: include/interlen.h ../c++adt/include/PositionVector.h
Interlen.o: ../c++adt/include/mathsym.h ../c++adt/include/RMatrix.h
Interlen.o: ../c++adt/include/Rotation.h ../c++adt/include/TMatrix.h
Interlen.o: /usr/include/CC/iostream /usr/include/CC/iosfwd
Interlen.o: /usr/include/CC/stl_config.h /usr/include/wchar.h
Interlen.o: /usr/include/locale_attr.h /usr/include/stdio.h
Interlen.o: /usr/include/ctype.h /usr/include/time.h /usr/include/stddef.h
Interlen.o: /usr/include/CC/functional /usr/include/CC/stl_function.h
Interlen.o: /usr/include/CC/char_traits.h /usr/include/string.h
Interlen.o: /usr/include/CC/istream /usr/include/CC/ostream
Interlen.o: /usr/include/CC/ios /usr/include/CC/stl_string_fwd.h
Interlen.o: /usr/include/CC/stl_alloc.h /usr/include/stdlib.h
Interlen.o: /usr/include/assert.h /usr/include/CC/stl_threads.h
Interlen.o: /usr/include/mutex.h /usr/include/CC/stl_exception.h
Interlen.o: /usr/include/CC/utility /usr/include/CC/stl_relops.h
Interlen.o: /usr/include/CC/stl_pair.h /usr/include/CC/stl_locale.h
Interlen.o: /usr/include/CC/typeinfo /usr/include/CC/exception
Interlen.o: /usr/include/CC/string /usr/include/CC/stdexcept
Interlen.o: /usr/include/CC/stl_iterator_base.h /usr/include/CC/memory
Interlen.o: /usr/include/CC/stl_algobase.h /usr/include/CC/type_traits.h
Interlen.o: /usr/include/limits.h /usr/include/CC/new.h
Interlen.o: /usr/include/CC/iostream.h /usr/include/memory.h
Interlen.o: /usr/include/CC/stl_iterator.h /usr/include/CC/stl_construct.h
Interlen.o: /usr/include/CC/stl_tempbuf.h /usr/include/CC/stl_uninitialized.h
Interlen.o: /usr/include/CC/stl_raw_storage_iter.h /usr/include/CC/algorithm
Interlen.o: /usr/include/CC/stl_algo.h /usr/include/CC/stl_heap.h
Interlen.o: /usr/include/CC/stl_hash_fun.h /usr/include/CC/stl_ctype.h
Interlen.o: /usr/include/CC/c_locale.h /usr/include/CC/streambuf
Interlen.o: /usr/include/CC/stl_stdio_file.h
Interlen.o: /usr/include/CC/stl_numeric_facets.h /usr/include/CC/limits
Interlen.o: /usr/include/float.h /usr/include/CC/vector
Interlen.o: /usr/include/CC/stl_range_errors.h /usr/include/CC/stl_vector.h
Interlen.o: /usr/include/CC/stl_bvector.h ../c++adt/include/TMatrixI.h
Interlen.o: /usr/include/CC/fstream /usr/include/CC/stl_codecvt.h
Voxel.o: ../c++adt/include/stdafx.h include/Voxel.h /usr/include/CC/iostream
Voxel.o: /usr/include/CC/iosfwd /usr/include/CC/stl_config.h
Voxel.o: /usr/include/standards.h /usr/include/wchar.h /usr/include/sgidefs.h
Voxel.o: /usr/include/locale_attr.h /usr/include/stdio.h /usr/include/ctype.h
Voxel.o: /usr/include/time.h /usr/include/stddef.h /usr/include/CC/functional
Voxel.o: /usr/include/CC/stl_function.h /usr/include/CC/char_traits.h
Voxel.o: /usr/include/string.h /usr/include/CC/istream
Voxel.o: /usr/include/CC/ostream /usr/include/CC/ios
Voxel.o: /usr/include/CC/stl_string_fwd.h /usr/include/CC/stl_alloc.h
Voxel.o: /usr/include/stdlib.h /usr/include/assert.h
Voxel.o: /usr/include/CC/stl_threads.h /usr/include/mutex.h
Voxel.o: /usr/include/CC/stl_exception.h /usr/include/CC/utility
Voxel.o: /usr/include/CC/stl_relops.h /usr/include/CC/stl_pair.h
Voxel.o: /usr/include/CC/stl_locale.h /usr/include/CC/typeinfo
Voxel.o: /usr/include/CC/exception /usr/include/CC/string
Voxel.o: /usr/include/CC/stdexcept /usr/include/CC/stl_iterator_base.h
Voxel.o: /usr/include/CC/memory /usr/include/CC/stl_algobase.h
Voxel.o: /usr/include/CC/type_traits.h /usr/include/limits.h
Voxel.o: /usr/include/CC/new.h /usr/include/CC/iostream.h
Voxel.o: /usr/include/memory.h /usr/include/CC/stl_iterator.h
Voxel.o: /usr/include/CC/stl_construct.h /usr/include/CC/stl_tempbuf.h
Voxel.o: /usr/include/CC/stl_uninitialized.h
Voxel.o: /usr/include/CC/stl_raw_storage_iter.h /usr/include/CC/algorithm
Voxel.o: /usr/include/CC/stl_algo.h /usr/include/CC/stl_heap.h
Voxel.o: /usr/include/CC/stl_hash_fun.h /usr/include/CC/stl_ctype.h
Voxel.o: /usr/include/CC/c_locale.h /usr/include/CC/streambuf
Voxel.o: /usr/include/CC/stl_stdio_file.h
Voxel.o: /usr/include/CC/stl_numeric_facets.h /usr/include/CC/limits
Voxel.o: /usr/include/float.h ../c++adt/include/Point.h /usr/include/math.h
Voxel.o: ../c++adt/include/PositionVector.h ../c++adt/include/mathsym.h
Voxel.o: ../c++adt/include/RMatrix.h ../c++adt/include/Rotation.h
Voxel.o: ../c++adt/include/TMatrix.h /usr/include/CC/vector
Voxel.o: /usr/include/CC/stl_range_errors.h /usr/include/CC/stl_vector.h
Voxel.o: /usr/include/CC/stl_bvector.h ../c++adt/include/TMatrixI.h
Voxel.o: /usr/include/CC/fstream /usr/include/CC/stl_codecvt.h
Voxel.o: ../c++adt/include/PointI.h
voxellattice.o: ../c++adt/include/stdafx.h /usr/include/math.h
voxellattice.o: /usr/include/sgidefs.h /usr/include/standards.h
voxellattice.o: include/interlen.h ../c++adt/include/PositionVector.h
voxellattice.o: ../c++adt/include/mathsym.h ../c++adt/include/RMatrix.h
voxellattice.o: ../c++adt/include/Rotation.h ../c++adt/include/TMatrix.h
voxellattice.o: /usr/include/CC/iostream /usr/include/CC/iosfwd
voxellattice.o: /usr/include/CC/stl_config.h /usr/include/wchar.h
voxellattice.o: /usr/include/locale_attr.h /usr/include/stdio.h
voxellattice.o: /usr/include/ctype.h /usr/include/time.h
voxellattice.o: /usr/include/stddef.h /usr/include/CC/functional
voxellattice.o: /usr/include/CC/stl_function.h /usr/include/CC/char_traits.h
voxellattice.o: /usr/include/string.h /usr/include/CC/istream
voxellattice.o: /usr/include/CC/ostream /usr/include/CC/ios
voxellattice.o: /usr/include/CC/stl_string_fwd.h /usr/include/CC/stl_alloc.h
voxellattice.o: /usr/include/stdlib.h /usr/include/assert.h
voxellattice.o: /usr/include/CC/stl_threads.h /usr/include/mutex.h
voxellattice.o: /usr/include/CC/stl_exception.h /usr/include/CC/utility
voxellattice.o: /usr/include/CC/stl_relops.h /usr/include/CC/stl_pair.h
voxellattice.o: /usr/include/CC/stl_locale.h /usr/include/CC/typeinfo
voxellattice.o: /usr/include/CC/exception /usr/include/CC/string
voxellattice.o: /usr/include/CC/stdexcept /usr/include/CC/stl_iterator_base.h
voxellattice.o: /usr/include/CC/memory /usr/include/CC/stl_algobase.h
voxellattice.o: /usr/include/CC/type_traits.h /usr/include/limits.h
voxellattice.o: /usr/include/CC/new.h /usr/include/CC/iostream.h
voxellattice.o: /usr/include/memory.h /usr/include/CC/stl_iterator.h
voxellattice.o: /usr/include/CC/stl_construct.h /usr/include/CC/stl_tempbuf.h
voxellattice.o: /usr/include/CC/stl_uninitialized.h
voxellattice.o: /usr/include/CC/stl_raw_storage_iter.h
voxellattice.o: /usr/include/CC/algorithm /usr/include/CC/stl_algo.h
voxellattice.o: /usr/include/CC/stl_heap.h /usr/include/CC/stl_hash_fun.h
voxellattice.o: /usr/include/CC/stl_ctype.h /usr/include/CC/c_locale.h
voxellattice.o: /usr/include/CC/streambuf /usr/include/CC/stl_stdio_file.h
voxellattice.o: /usr/include/CC/stl_numeric_facets.h /usr/include/CC/limits
voxellattice.o: /usr/include/float.h /usr/include/CC/vector
voxellattice.o: /usr/include/CC/stl_range_errors.h
voxellattice.o: /usr/include/CC/stl_vector.h /usr/include/CC/stl_bvector.h
voxellattice.o: ../c++adt/include/TMatrixI.h /usr/include/CC/fstream
voxellattice.o: /usr/include/CC/stl_codecvt.h include/voxellattice.h
voxelmatrix.o: ../c++adt/include/stdafx.h /usr/include/math.h
voxelmatrix.o: /usr/include/sgidefs.h /usr/include/standards.h
voxelmatrix.o: include/voxelmatrix.h include/VoxelSpace.h include/interlen.h
voxelmatrix.o: ../c++adt/include/PositionVector.h ../c++adt/include/mathsym.h
voxelmatrix.o: ../c++adt/include/RMatrix.h ../c++adt/include/Rotation.h
voxelmatrix.o: ../c++adt/include/TMatrix.h /usr/include/CC/iostream
voxelmatrix.o: /usr/include/CC/iosfwd /usr/include/CC/stl_config.h
voxelmatrix.o: /usr/include/wchar.h /usr/include/locale_attr.h
voxelmatrix.o: /usr/include/stdio.h /usr/include/ctype.h /usr/include/time.h
voxelmatrix.o: /usr/include/stddef.h /usr/include/CC/functional
voxelmatrix.o: /usr/include/CC/stl_function.h /usr/include/CC/char_traits.h
voxelmatrix.o: /usr/include/string.h /usr/include/CC/istream
voxelmatrix.o: /usr/include/CC/ostream /usr/include/CC/ios
voxelmatrix.o: /usr/include/CC/stl_string_fwd.h /usr/include/CC/stl_alloc.h
voxelmatrix.o: /usr/include/stdlib.h /usr/include/assert.h
voxelmatrix.o: /usr/include/CC/stl_threads.h /usr/include/mutex.h
voxelmatrix.o: /usr/include/CC/stl_exception.h /usr/include/CC/utility
voxelmatrix.o: /usr/include/CC/stl_relops.h /usr/include/CC/stl_pair.h
voxelmatrix.o: /usr/include/CC/stl_locale.h /usr/include/CC/typeinfo
voxelmatrix.o: /usr/include/CC/exception /usr/include/CC/string
voxelmatrix.o: /usr/include/CC/stdexcept /usr/include/CC/stl_iterator_base.h
voxelmatrix.o: /usr/include/CC/memory /usr/include/CC/stl_algobase.h
voxelmatrix.o: /usr/include/CC/type_traits.h /usr/include/limits.h
voxelmatrix.o: /usr/include/CC/new.h /usr/include/CC/iostream.h
voxelmatrix.o: /usr/include/memory.h /usr/include/CC/stl_iterator.h
voxelmatrix.o: /usr/include/CC/stl_construct.h /usr/include/CC/stl_tempbuf.h
voxelmatrix.o: /usr/include/CC/stl_uninitialized.h
voxelmatrix.o: /usr/include/CC/stl_raw_storage_iter.h
voxelmatrix.o: /usr/include/CC/algorithm /usr/include/CC/stl_algo.h
voxelmatrix.o: /usr/include/CC/stl_heap.h /usr/include/CC/stl_hash_fun.h
voxelmatrix.o: /usr/include/CC/stl_ctype.h /usr/include/CC/c_locale.h
voxelmatrix.o: /usr/include/CC/streambuf /usr/include/CC/stl_stdio_file.h
voxelmatrix.o: /usr/include/CC/stl_numeric_facets.h /usr/include/CC/limits
voxelmatrix.o: /usr/include/float.h /usr/include/CC/vector
voxelmatrix.o: /usr/include/CC/stl_range_errors.h
voxelmatrix.o: /usr/include/CC/stl_vector.h /usr/include/CC/stl_bvector.h
voxelmatrix.o: ../c++adt/include/TMatrixI.h /usr/include/CC/fstream
voxelmatrix.o: /usr/include/CC/stl_codecvt.h include/voxellattice.h
voxelmatrix.o: include/Voxel.h ../c++adt/include/Point.h
voxelmatrix.o: ../c++adt/include/PointI.h ../stl-lignum/include/Tree.h
voxelmatrix.o: /usr/include/CC/numeric /usr/include/CC/stl_numeric.h
voxelmatrix.o: /usr/include/CC/list /usr/include/CC/stl_list.h
voxelmatrix.o: ../c++adt/include/ParametricCurve.h
voxelmatrix.o: ../stl-lignum/include/LGMdecl.h
voxelmatrix.o: ../stl-lignum/include/LGMSymbols.h
voxelmatrix.o: ../stl-lignum/include/LGMUnits.h
voxelmatrix.o: ../stl-lignum/include/Algorithms.h
voxelmatrix.o: ../stl-lignum/include/AlgorithmsI.h
voxelmatrix.o: ../stl-lignum/include/TreeFunctor.h
voxelmatrix.o: ../stl-lignum/include/TreeCompartment.h
voxelmatrix.o: ../stl-lignum/include/TreeCompartmentI.h
voxelmatrix.o: ../stl-lignum/include/TreeFunctorI.h
voxelmatrix.o: ../stl-lignum/include/TreeMetaFileParser.h
voxelmatrix.o: ../c++adt/include/Table.h ../c++adt/include/DList.h
voxelmatrix.o: ../c++adt/include/DListElement.h ../c++adt/include/boolean.h
voxelmatrix.o: ../c++adt/include/TableI.h ../c++adt/include/Lex.h
voxelmatrix.o: ../stl-lignum/include/RootSystem.h ../stl-lignum/include/Bud.h
voxelmatrix.o: ../stl-lignum/include/BudI.h
voxelmatrix.o: ../stl-lignum/include/DefaultBud.h
voxelmatrix.o: ../stl-lignum/include/BranchingPoint.h
voxelmatrix.o: ../stl-lignum/include/BranchingPointI.h
voxelmatrix.o: ../stl-lignum/include/TreeSegment.h
voxelmatrix.o: ../stl-lignum/include/TreeSegmentWithFlow.h
voxelmatrix.o: ../stl-lignum/include/TreeSegmentI.h
voxelmatrix.o: ../stl-lignum/include/HwTreeSegment.h
voxelmatrix.o: ../stl-lignum/include/BroadLeaf.h ../c++adt/include/Ellipsis.h
voxelmatrix.o: ../stl-lignum/include/HwTreeSegmentI.h
voxelmatrix.o: ../stl-lignum/include/HwTreeSegmentMetabolismI.h
voxelmatrix.o: ../stl-lignum/include/CfTreeSegment.h
voxelmatrix.o: ../stl-lignum/include/CfTreeFunctor.h
voxelmatrix.o: ../stl-lignum/include/CfTreeFunctorI.h
voxelmatrix.o: ../stl-lignum/include/CfTreeSegmentI.h
voxelmatrix.o: ../stl-lignum/include/CfTreeSegmentMetabolismI.h
voxelmatrix.o: ../stl-lignum/include/Axis.h ../stl-lignum/include/AxisI.h
voxelmatrix.o: ../c++adt/include/ConnectionMatrix.h
voxelmatrix.o: ../c++adt/include/ConnectionMatrixI.h
voxelmatrix.o: include/FirmamentWithMask.h include/Firmament.h
voxelmatrix.o: ../stl-lignum/include/TreeRadiation.h
voxelmatrix.o: ../stl-lignum/include/TreeBookkeeping.h
voxelmatrix.o: ../stl-lignum/include/TreeBookkeepingI.h
voxelmatrix.o: ../stl-lignum/include/InitializeTree.h /usr/include/CC/map
voxelmatrix.o: /usr/include/CC/stl_tree.h /usr/include/CC/stl_map.h
voxelmatrix.o: /usr/include/CC/stl_multimap.h ../c++adt/include/stringutils.h
voxelmatrix.o: ../stl-lignum/include/InitializeTreeI.h
voxelmatrix.o: ../stl-lignum/include/TreeI.h
voxelmatrix.o: ../stl-lignum/include/TreeMetabolismI.h
voxelmatrix.o: ../stl-lignum/include/TreeMetabolism.h
voxelmatrix.o: ../stl-lignum/include/TreeRadiationI.h
voxelmatrix.o: ../ScotsPine/include/ScotsPineVisual.h include/voxelmatrixI.h
