
SRCDIR1 = ../src
SRCDIR2 = ../include

SRC = $(SRCDIR1)/CString.cc  $(SRCDIR1)/DList.cc $(SRCDIR1)/DListElement.cc \
      $(SRCDIR1)/Ellipsis.cc $(SRCDIR1)/Lex.cc $(SRCDIR1)/ParametricCurve.cc \
      $(SRCDIR1)/PositionVector.cc $(SRCDIR1)/RMatrix.cc $(SRCDIR1)/HRMatrix.cc

OBJ = $(SRCDIR1)/CString.o $(SRCDIR1)/DList.o $(SRCDIR1)/DListElement.o \
      $(SRCDIR1)/Ellipsis.o $(SRCDIR1)/Lex.o $(SRCDIR1)/ParametricCurve.o \
      $(SRCDIR1)/PositionVector.o $(SRCDIR1)/RMatrix.o $(SRCDIR1)/HRMatrix.o

INCLUDE= -I../include -I/usr/include/CC 

CCC = CC -64 -LANG:std
ETAGS = etags -d -T -C -o

OPTIMIZE = -O
CCCFLAGS =   -c 

.SUFFIXES: .o .cc
ARCOMMAND=$(CCC) -ar 
ARCOMMANDFLAGS = -o
AR =  $(ARCOMMAND)
ARFLAGS =  $(ARCOMMANDFLAGS)
ARFILE = libc++adt.a


$(ARFILE): $(OBJ)
	$(AR) $(ARFLAGS) $(ARFILE) $(OBJ)

hrmatrix: $(ARFILE)
	$(CCC)  ../src/hrmatrix.cc -o $@ $(INCLUDE) -L. -lc++adt -lm 
.cc.o: 
	$(CCC)  $(OPTIMIZE) $(CCCFLAGS) $(INCLUDE) $<  -o $@  

touch:
	touch $(SRC)

clean:
	rm -f $(OBJ) hrmatrix core

distclean: clean
	rm -rf ../src/ii_files ../include/ii_files ii_files $(ARFILE)

etags:
	$(ETAGS)   TAGSFILE ../src/*.cc ../include/*.h
depend:
	makedepend $(INCLUDE) $(SRC) ../src/hrmatrix.cc
# DO NOT DELETE

../src/CString.o: ../include/CString.h /usr/include/string.h
../src/CString.o: /usr/include/standards.h /usr/include/stdio.h
../src/CString.o: /usr/include/sgidefs.h /usr/include/ctype.h
../src/CString.o: /usr/include/locale_attr.h /usr/include/CC/iostream
../src/CString.o: /usr/include/CC/iosfwd /usr/include/CC/stl_config.h
../src/CString.o: /usr/include/wchar.h /usr/include/time.h
../src/CString.o: /usr/include/stddef.h /usr/include/CC/functional
../src/CString.o: /usr/include/CC/stl_function.h
../src/CString.o: /usr/include/CC/char_traits.h /usr/include/CC/istream
../src/CString.o: /usr/include/CC/ostream /usr/include/CC/ios
../src/CString.o: /usr/include/CC/stl_string_fwd.h
../src/CString.o: /usr/include/CC/stl_alloc.h /usr/include/stdlib.h
../src/CString.o: /usr/include/assert.h /usr/include/CC/stl_threads.h
../src/CString.o: /usr/include/mutex.h /usr/include/CC/stl_exception.h
../src/CString.o: /usr/include/CC/utility /usr/include/CC/stl_relops.h
../src/CString.o: /usr/include/CC/stl_pair.h /usr/include/CC/stl_locale.h
../src/CString.o: /usr/include/CC/typeinfo /usr/include/CC/exception
../src/CString.o: /usr/include/CC/string /usr/include/CC/stdexcept
../src/CString.o: /usr/include/CC/stl_iterator_base.h /usr/include/CC/memory
../src/CString.o: /usr/include/CC/stl_algobase.h
../src/CString.o: /usr/include/CC/type_traits.h /usr/include/limits.h
../src/CString.o: /usr/include/CC/new.h /usr/include/CC/iostream.h
../src/CString.o: /usr/include/memory.h /usr/include/CC/stl_iterator.h
../src/CString.o: /usr/include/CC/stl_construct.h
../src/CString.o: /usr/include/CC/stl_tempbuf.h
../src/CString.o: /usr/include/CC/stl_uninitialized.h
../src/CString.o: /usr/include/CC/stl_raw_storage_iter.h
../src/CString.o: /usr/include/CC/algorithm /usr/include/CC/stl_algo.h
../src/CString.o: /usr/include/CC/stl_heap.h /usr/include/CC/stl_hash_fun.h
../src/CString.o: /usr/include/CC/stl_ctype.h /usr/include/CC/c_locale.h
../src/CString.o: /usr/include/CC/streambuf /usr/include/CC/stl_stdio_file.h
../src/CString.o: /usr/include/CC/stl_numeric_facets.h /usr/include/CC/limits
../src/CString.o: /usr/include/float.h
../src/DList.o: /usr/include/CC/iostream.h /usr/include/memory.h
../src/DList.o: /usr/include/stddef.h /usr/include/sgidefs.h
../src/DList.o: /usr/include/stdlib.h /usr/include/standards.h
../src/DList.o: ../include/DList.h ../include/DListElement.h
../src/DList.o: ../include/boolean.h
../src/DListElement.o: ../include/DListElement.h /usr/include/stdlib.h
../src/DListElement.o: /usr/include/standards.h /usr/include/sgidefs.h
../src/Ellipsis.o: ../include/Ellipsis.h /usr/include/math.h
../src/Ellipsis.o: /usr/include/sgidefs.h /usr/include/standards.h
../src/Ellipsis.o: ../include/mathsym.h
../src/Lex.o: ../include/Lex.h /usr/include/CC/fstream
../src/Lex.o: /usr/include/CC/istream /usr/include/CC/ostream
../src/Lex.o: /usr/include/CC/ios /usr/include/CC/stl_config.h
../src/Lex.o: /usr/include/standards.h /usr/include/CC/stl_string_fwd.h
../src/Lex.o: /usr/include/stddef.h /usr/include/sgidefs.h
../src/Lex.o: /usr/include/CC/stl_alloc.h /usr/include/stdio.h
../src/Lex.o: /usr/include/stdlib.h /usr/include/string.h
../src/Lex.o: /usr/include/assert.h /usr/include/CC/stl_threads.h
../src/Lex.o: /usr/include/mutex.h /usr/include/time.h
../src/Lex.o: /usr/include/CC/stl_exception.h /usr/include/CC/utility
../src/Lex.o: /usr/include/CC/stl_relops.h /usr/include/CC/stl_pair.h
../src/Lex.o: /usr/include/CC/iosfwd /usr/include/wchar.h
../src/Lex.o: /usr/include/locale_attr.h /usr/include/ctype.h
../src/Lex.o: /usr/include/CC/functional /usr/include/CC/stl_function.h
../src/Lex.o: /usr/include/CC/char_traits.h /usr/include/CC/stl_locale.h
../src/Lex.o: /usr/include/CC/typeinfo /usr/include/CC/exception
../src/Lex.o: /usr/include/CC/string /usr/include/CC/stdexcept
../src/Lex.o: /usr/include/CC/stl_iterator_base.h /usr/include/CC/memory
../src/Lex.o: /usr/include/CC/stl_algobase.h /usr/include/CC/type_traits.h
../src/Lex.o: /usr/include/limits.h /usr/include/CC/new.h
../src/Lex.o: /usr/include/CC/iostream.h /usr/include/memory.h
../src/Lex.o: /usr/include/CC/stl_iterator.h /usr/include/CC/stl_construct.h
../src/Lex.o: /usr/include/CC/stl_tempbuf.h
../src/Lex.o: /usr/include/CC/stl_uninitialized.h
../src/Lex.o: /usr/include/CC/stl_raw_storage_iter.h
../src/Lex.o: /usr/include/CC/algorithm /usr/include/CC/stl_algo.h
../src/Lex.o: /usr/include/CC/stl_heap.h /usr/include/CC/stl_hash_fun.h
../src/Lex.o: /usr/include/CC/stl_ctype.h /usr/include/CC/c_locale.h
../src/Lex.o: /usr/include/CC/streambuf /usr/include/CC/stl_stdio_file.h
../src/Lex.o: /usr/include/CC/stl_numeric_facets.h /usr/include/CC/limits
../src/Lex.o: /usr/include/float.h /usr/include/CC/stl_codecvt.h
../src/Lex.o: ../include/DList.h ../include/DListElement.h
../src/Lex.o: ../include/boolean.h /usr/include/CC/fstream.h
../src/ParametricCurve.o: ../include/ParametricCurve.h /usr/include/CC/vector
../src/ParametricCurve.o: /usr/include/CC/stl_range_errors.h
../src/ParametricCurve.o: /usr/include/CC/stl_config.h
../src/ParametricCurve.o: /usr/include/standards.h
../src/ParametricCurve.o: /usr/include/CC/stl_algobase.h
../src/ParametricCurve.o: /usr/include/CC/type_traits.h /usr/include/string.h
../src/ParametricCurve.o: /usr/include/limits.h /usr/include/sgidefs.h
../src/ParametricCurve.o: /usr/include/stdlib.h /usr/include/stddef.h
../src/ParametricCurve.o: /usr/include/CC/new.h /usr/include/CC/iostream.h
../src/ParametricCurve.o: /usr/include/memory.h
../src/ParametricCurve.o: /usr/include/CC/stl_iterator_base.h
../src/ParametricCurve.o: /usr/include/CC/stl_iterator.h
../src/ParametricCurve.o: /usr/include/CC/stl_alloc.h /usr/include/stdio.h
../src/ParametricCurve.o: /usr/include/assert.h /usr/include/CC/stl_threads.h
../src/ParametricCurve.o: /usr/include/mutex.h /usr/include/time.h
../src/ParametricCurve.o: /usr/include/CC/stl_construct.h
../src/ParametricCurve.o: /usr/include/CC/stl_uninitialized.h
../src/ParametricCurve.o: /usr/include/CC/stl_vector.h
../src/ParametricCurve.o: /usr/include/CC/stl_bvector.h
../src/ParametricCurve.o: /usr/include/CC/fstream /usr/include/CC/istream
../src/ParametricCurve.o: /usr/include/CC/ostream /usr/include/CC/ios
../src/ParametricCurve.o: /usr/include/CC/stl_string_fwd.h
../src/ParametricCurve.o: /usr/include/CC/stl_exception.h
../src/ParametricCurve.o: /usr/include/CC/utility
../src/ParametricCurve.o: /usr/include/CC/stl_relops.h
../src/ParametricCurve.o: /usr/include/CC/stl_pair.h /usr/include/CC/iosfwd
../src/ParametricCurve.o: /usr/include/wchar.h /usr/include/locale_attr.h
../src/ParametricCurve.o: /usr/include/ctype.h /usr/include/CC/functional
../src/ParametricCurve.o: /usr/include/CC/stl_function.h
../src/ParametricCurve.o: /usr/include/CC/char_traits.h
../src/ParametricCurve.o: /usr/include/CC/stl_locale.h
../src/ParametricCurve.o: /usr/include/CC/typeinfo /usr/include/CC/exception
../src/ParametricCurve.o: /usr/include/CC/string /usr/include/CC/stdexcept
../src/ParametricCurve.o: /usr/include/CC/memory
../src/ParametricCurve.o: /usr/include/CC/stl_tempbuf.h
../src/ParametricCurve.o: /usr/include/CC/stl_raw_storage_iter.h
../src/ParametricCurve.o: /usr/include/CC/algorithm
../src/ParametricCurve.o: /usr/include/CC/stl_algo.h
../src/ParametricCurve.o: /usr/include/CC/stl_heap.h
../src/ParametricCurve.o: /usr/include/CC/stl_hash_fun.h
../src/ParametricCurve.o: /usr/include/CC/stl_ctype.h
../src/ParametricCurve.o: /usr/include/CC/c_locale.h
../src/ParametricCurve.o: /usr/include/CC/streambuf
../src/ParametricCurve.o: /usr/include/CC/stl_stdio_file.h
../src/ParametricCurve.o: /usr/include/CC/stl_numeric_facets.h
../src/ParametricCurve.o: /usr/include/CC/limits /usr/include/float.h
../src/ParametricCurve.o: /usr/include/CC/stl_codecvt.h
../src/ParametricCurve.o: /usr/include/CC/iostream
../src/PositionVector.o: ../include/Point.h /usr/include/math.h
../src/PositionVector.o: /usr/include/sgidefs.h /usr/include/standards.h
../src/PositionVector.o: /usr/include/CC/iostream /usr/include/CC/iosfwd
../src/PositionVector.o: /usr/include/CC/stl_config.h /usr/include/wchar.h
../src/PositionVector.o: /usr/include/locale_attr.h /usr/include/stdio.h
../src/PositionVector.o: /usr/include/ctype.h /usr/include/time.h
../src/PositionVector.o: /usr/include/stddef.h /usr/include/CC/functional
../src/PositionVector.o: /usr/include/CC/stl_function.h
../src/PositionVector.o: /usr/include/CC/char_traits.h /usr/include/string.h
../src/PositionVector.o: /usr/include/CC/istream /usr/include/CC/ostream
../src/PositionVector.o: /usr/include/CC/ios /usr/include/CC/stl_string_fwd.h
../src/PositionVector.o: /usr/include/CC/stl_alloc.h /usr/include/stdlib.h
../src/PositionVector.o: /usr/include/assert.h /usr/include/CC/stl_threads.h
../src/PositionVector.o: /usr/include/mutex.h /usr/include/CC/stl_exception.h
../src/PositionVector.o: /usr/include/CC/utility /usr/include/CC/stl_relops.h
../src/PositionVector.o: /usr/include/CC/stl_pair.h
../src/PositionVector.o: /usr/include/CC/stl_locale.h
../src/PositionVector.o: /usr/include/CC/typeinfo /usr/include/CC/exception
../src/PositionVector.o: /usr/include/CC/string /usr/include/CC/stdexcept
../src/PositionVector.o: /usr/include/CC/stl_iterator_base.h
../src/PositionVector.o: /usr/include/CC/memory
../src/PositionVector.o: /usr/include/CC/stl_algobase.h
../src/PositionVector.o: /usr/include/CC/type_traits.h /usr/include/limits.h
../src/PositionVector.o: /usr/include/CC/new.h /usr/include/CC/iostream.h
../src/PositionVector.o: /usr/include/memory.h /usr/include/CC/stl_iterator.h
../src/PositionVector.o: /usr/include/CC/stl_construct.h
../src/PositionVector.o: /usr/include/CC/stl_tempbuf.h
../src/PositionVector.o: /usr/include/CC/stl_uninitialized.h
../src/PositionVector.o: /usr/include/CC/stl_raw_storage_iter.h
../src/PositionVector.o: /usr/include/CC/algorithm /usr/include/CC/stl_algo.h
../src/PositionVector.o: /usr/include/CC/stl_heap.h
../src/PositionVector.o: /usr/include/CC/stl_hash_fun.h
../src/PositionVector.o: /usr/include/CC/stl_ctype.h
../src/PositionVector.o: /usr/include/CC/c_locale.h /usr/include/CC/streambuf
../src/PositionVector.o: /usr/include/CC/stl_stdio_file.h
../src/PositionVector.o: /usr/include/CC/stl_numeric_facets.h
../src/PositionVector.o: /usr/include/CC/limits /usr/include/float.h
../src/PositionVector.o: ../include/PositionVector.h ../include/mathsym.h
../src/PositionVector.o: /usr/include/CC/vector
../src/PositionVector.o: /usr/include/CC/stl_range_errors.h
../src/PositionVector.o: /usr/include/CC/stl_vector.h
../src/PositionVector.o: /usr/include/CC/stl_bvector.h ../include/RMatrix.h
../src/PositionVector.o: ../include/Rotation.h ../include/TMatrix.h
../src/PositionVector.o: ../include/TMatrixI.h ../include/PointI.h
../src/RMatrix.o: ../include/RMatrix.h /usr/include/math.h
../src/RMatrix.o: /usr/include/sgidefs.h /usr/include/standards.h
../src/RMatrix.o: ../include/mathsym.h ../include/Rotation.h
../src/RMatrix.o: ../include/TMatrix.h /usr/include/CC/iostream
../src/RMatrix.o: /usr/include/CC/iosfwd /usr/include/CC/stl_config.h
../src/RMatrix.o: /usr/include/wchar.h /usr/include/locale_attr.h
../src/RMatrix.o: /usr/include/stdio.h /usr/include/ctype.h
../src/RMatrix.o: /usr/include/time.h /usr/include/stddef.h
../src/RMatrix.o: /usr/include/CC/functional /usr/include/CC/stl_function.h
../src/RMatrix.o: /usr/include/CC/char_traits.h /usr/include/string.h
../src/RMatrix.o: /usr/include/CC/istream /usr/include/CC/ostream
../src/RMatrix.o: /usr/include/CC/ios /usr/include/CC/stl_string_fwd.h
../src/RMatrix.o: /usr/include/CC/stl_alloc.h /usr/include/stdlib.h
../src/RMatrix.o: /usr/include/assert.h /usr/include/CC/stl_threads.h
../src/RMatrix.o: /usr/include/mutex.h /usr/include/CC/stl_exception.h
../src/RMatrix.o: /usr/include/CC/utility /usr/include/CC/stl_relops.h
../src/RMatrix.o: /usr/include/CC/stl_pair.h /usr/include/CC/stl_locale.h
../src/RMatrix.o: /usr/include/CC/typeinfo /usr/include/CC/exception
../src/RMatrix.o: /usr/include/CC/string /usr/include/CC/stdexcept
../src/RMatrix.o: /usr/include/CC/stl_iterator_base.h /usr/include/CC/memory
../src/RMatrix.o: /usr/include/CC/stl_algobase.h
../src/RMatrix.o: /usr/include/CC/type_traits.h /usr/include/limits.h
../src/RMatrix.o: /usr/include/CC/new.h /usr/include/CC/iostream.h
../src/RMatrix.o: /usr/include/memory.h /usr/include/CC/stl_iterator.h
../src/RMatrix.o: /usr/include/CC/stl_construct.h
../src/RMatrix.o: /usr/include/CC/stl_tempbuf.h
../src/RMatrix.o: /usr/include/CC/stl_uninitialized.h
../src/RMatrix.o: /usr/include/CC/stl_raw_storage_iter.h
../src/RMatrix.o: /usr/include/CC/algorithm /usr/include/CC/stl_algo.h
../src/RMatrix.o: /usr/include/CC/stl_heap.h /usr/include/CC/stl_hash_fun.h
../src/RMatrix.o: /usr/include/CC/stl_ctype.h /usr/include/CC/c_locale.h
../src/RMatrix.o: /usr/include/CC/streambuf /usr/include/CC/stl_stdio_file.h
../src/RMatrix.o: /usr/include/CC/stl_numeric_facets.h /usr/include/CC/limits
../src/RMatrix.o: /usr/include/float.h /usr/include/CC/vector
../src/RMatrix.o: /usr/include/CC/stl_range_errors.h
../src/RMatrix.o: /usr/include/CC/stl_vector.h /usr/include/CC/stl_bvector.h
../src/RMatrix.o: ../include/TMatrixI.h
../src/HRMatrix.o: ../include/HRMatrix.h /usr/include/CC/vector
../src/HRMatrix.o: /usr/include/CC/stl_range_errors.h
../src/HRMatrix.o: /usr/include/CC/stl_config.h /usr/include/standards.h
../src/HRMatrix.o: /usr/include/CC/stl_algobase.h
../src/HRMatrix.o: /usr/include/CC/type_traits.h /usr/include/string.h
../src/HRMatrix.o: /usr/include/limits.h /usr/include/sgidefs.h
../src/HRMatrix.o: /usr/include/stdlib.h /usr/include/stddef.h
../src/HRMatrix.o: /usr/include/CC/new.h /usr/include/CC/iostream.h
../src/HRMatrix.o: /usr/include/memory.h /usr/include/CC/stl_iterator_base.h
../src/HRMatrix.o: /usr/include/CC/stl_iterator.h /usr/include/CC/stl_alloc.h
../src/HRMatrix.o: /usr/include/stdio.h /usr/include/assert.h
../src/HRMatrix.o: /usr/include/CC/stl_threads.h /usr/include/mutex.h
../src/HRMatrix.o: /usr/include/time.h /usr/include/CC/stl_construct.h
../src/HRMatrix.o: /usr/include/CC/stl_uninitialized.h
../src/HRMatrix.o: /usr/include/CC/stl_vector.h /usr/include/CC/stl_bvector.h
../src/HRMatrix.o: ../include/Rotation.h ../include/mathsym.h
../src/HRMatrix.o: /usr/include/math.h ../include/Point.h
../src/HRMatrix.o: /usr/include/CC/iostream /usr/include/CC/iosfwd
../src/HRMatrix.o: /usr/include/wchar.h /usr/include/locale_attr.h
../src/HRMatrix.o: /usr/include/ctype.h /usr/include/CC/functional
../src/HRMatrix.o: /usr/include/CC/stl_function.h
../src/HRMatrix.o: /usr/include/CC/char_traits.h /usr/include/CC/istream
../src/HRMatrix.o: /usr/include/CC/ostream /usr/include/CC/ios
../src/HRMatrix.o: /usr/include/CC/stl_string_fwd.h
../src/HRMatrix.o: /usr/include/CC/stl_exception.h /usr/include/CC/utility
../src/HRMatrix.o: /usr/include/CC/stl_relops.h /usr/include/CC/stl_pair.h
../src/HRMatrix.o: /usr/include/CC/stl_locale.h /usr/include/CC/typeinfo
../src/HRMatrix.o: /usr/include/CC/exception /usr/include/CC/string
../src/HRMatrix.o: /usr/include/CC/stdexcept /usr/include/CC/memory
../src/HRMatrix.o: /usr/include/CC/stl_tempbuf.h
../src/HRMatrix.o: /usr/include/CC/stl_raw_storage_iter.h
../src/HRMatrix.o: /usr/include/CC/algorithm /usr/include/CC/stl_algo.h
../src/HRMatrix.o: /usr/include/CC/stl_heap.h /usr/include/CC/stl_hash_fun.h
../src/HRMatrix.o: /usr/include/CC/stl_ctype.h /usr/include/CC/c_locale.h
../src/HRMatrix.o: /usr/include/CC/streambuf /usr/include/CC/stl_stdio_file.h
../src/HRMatrix.o: /usr/include/CC/stl_numeric_facets.h
../src/HRMatrix.o: /usr/include/CC/limits /usr/include/float.h
../src/HRMatrix.o: ../include/PositionVector.h ../include/RMatrix.h
../src/HRMatrix.o: ../include/TMatrix.h ../include/TMatrixI.h
../src/HRMatrix.o: ../include/PointI.h
../src/hrmatrix.o: /usr/include/stdlib.h /usr/include/standards.h
../src/hrmatrix.o: /usr/include/sgidefs.h /usr/include/CC/iostream.h
../src/hrmatrix.o: /usr/include/memory.h /usr/include/stddef.h
../src/hrmatrix.o: /usr/include/CC/algorithm /usr/include/CC/stl_algobase.h
../src/hrmatrix.o: /usr/include/CC/type_traits.h /usr/include/string.h
../src/hrmatrix.o: /usr/include/limits.h /usr/include/CC/new.h
../src/hrmatrix.o: /usr/include/CC/stl_iterator_base.h
../src/hrmatrix.o: /usr/include/CC/stl_iterator.h
../src/hrmatrix.o: /usr/include/CC/stl_construct.h
../src/hrmatrix.o: /usr/include/CC/stl_uninitialized.h
../src/hrmatrix.o: /usr/include/CC/stl_tempbuf.h /usr/include/CC/stl_algo.h
../src/hrmatrix.o: /usr/include/CC/stl_heap.h ../include/HRMatrix.h
../src/hrmatrix.o: /usr/include/CC/vector /usr/include/CC/stl_range_errors.h
../src/hrmatrix.o: /usr/include/CC/stl_config.h /usr/include/CC/stl_alloc.h
../src/hrmatrix.o: /usr/include/stdio.h /usr/include/assert.h
../src/hrmatrix.o: /usr/include/CC/stl_threads.h /usr/include/mutex.h
../src/hrmatrix.o: /usr/include/time.h /usr/include/CC/stl_vector.h
../src/hrmatrix.o: /usr/include/CC/stl_bvector.h ../include/Rotation.h
../src/hrmatrix.o: ../include/mathsym.h /usr/include/math.h
../src/hrmatrix.o: ../include/Point.h /usr/include/CC/iostream
../src/hrmatrix.o: /usr/include/CC/iosfwd /usr/include/wchar.h
../src/hrmatrix.o: /usr/include/locale_attr.h /usr/include/ctype.h
../src/hrmatrix.o: /usr/include/CC/functional /usr/include/CC/stl_function.h
../src/hrmatrix.o: /usr/include/CC/char_traits.h /usr/include/CC/istream
../src/hrmatrix.o: /usr/include/CC/ostream /usr/include/CC/ios
../src/hrmatrix.o: /usr/include/CC/stl_string_fwd.h
../src/hrmatrix.o: /usr/include/CC/stl_exception.h /usr/include/CC/utility
../src/hrmatrix.o: /usr/include/CC/stl_relops.h /usr/include/CC/stl_pair.h
../src/hrmatrix.o: /usr/include/CC/stl_locale.h /usr/include/CC/typeinfo
../src/hrmatrix.o: /usr/include/CC/exception /usr/include/CC/string
../src/hrmatrix.o: /usr/include/CC/stdexcept /usr/include/CC/memory
../src/hrmatrix.o: /usr/include/CC/stl_raw_storage_iter.h
../src/hrmatrix.o: /usr/include/CC/stl_hash_fun.h /usr/include/CC/stl_ctype.h
../src/hrmatrix.o: /usr/include/CC/c_locale.h /usr/include/CC/streambuf
../src/hrmatrix.o: /usr/include/CC/stl_stdio_file.h
../src/hrmatrix.o: /usr/include/CC/stl_numeric_facets.h
../src/hrmatrix.o: /usr/include/CC/limits /usr/include/float.h
../src/hrmatrix.o: ../include/PositionVector.h ../include/RMatrix.h
../src/hrmatrix.o: ../include/TMatrix.h ../include/TMatrixI.h
../src/hrmatrix.o: ../include/PointI.h
