
SRCDIR1 = ../src
SRCDIR2 = ../include

SRC = $(SRCDIR1)/CString.cc  $(SRCDIR1)/DList.cc $(SRCDIR1)/DListElement.cc \
      $(SRCDIR1)/Ellipsis.cc $(SRCDIR1)/Lex.cc $(SRCDIR1)/ParametricCurve.cc \
      $(SRCDIR1)/PositionVector.cc $(SRCDIR1)/RMatrix.cc $(SRCDIR1)/HRMatrix.cc

OBJ = $(SRCDIR1)/CString.o $(SRCDIR1)/DList.o $(SRCDIR1)/DListElement.o \
      $(SRCDIR1)/Ellipsis.o $(SRCDIR1)/Lex.o $(SRCDIR1)/ParametricCurve.o \
      $(SRCDIR1)/PositionVector.o $(SRCDIR1)/RMatrix.o $(SRCDIR1)/HRMatrix.o

INCLUDE= -I../include -I/usr/include/CC 

CCC = CC -64
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
# DO NOT DELETE THIS LINE -- make depend depends on it.

../src/CString.o: ../include/CString.h /usr/include/string.h
../src/CString.o: /usr/include/standards.h /usr/include/stdio.h
../src/CString.o: /usr/include/sgidefs.h /usr/include/ctype.h
../src/CString.o: /usr/include/locale_attr.h /usr/include/CC/stream.h
../src/CString.o: /usr/include/CC/iostream.h /usr/include/memory.h
../src/CString.o: /usr/include/stddef.h /usr/include/CC/iomanip.h
../src/CString.o: /usr/include/CC/generic.h /usr/include/CC/stdiostream.h
../src/CString.o: /usr/include/CC/fstream.h
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
../src/Lex.o: ../include/Lex.h /usr/include/CC/fstream.h
../src/Lex.o: /usr/include/CC/iostream.h /usr/include/memory.h
../src/Lex.o: /usr/include/stddef.h /usr/include/sgidefs.h ../include/DList.h
../src/Lex.o: ../include/DListElement.h ../include/boolean.h
../src/Lex.o: /usr/include/CC/string /usr/include/CC/stl_config.h
../src/Lex.o: /usr/include/standards.h /usr/include/CC/stl_string_fwd.h
../src/Lex.o: /usr/include/CC/stl_alloc.h /usr/include/stdio.h
../src/Lex.o: /usr/include/stdlib.h /usr/include/string.h
../src/Lex.o: /usr/include/assert.h /usr/include/CC/stl_threads.h
../src/Lex.o: /usr/include/mutex.h /usr/include/time.h /usr/include/ctype.h
../src/Lex.o: /usr/include/locale_attr.h /usr/include/CC/functional
../src/Lex.o: /usr/include/CC/stl_function.h /usr/include/CC/stdexcept
../src/Lex.o: /usr/include/CC/stl_exception.h
../src/Lex.o: /usr/include/CC/stl_iterator_base.h /usr/include/CC/memory
../src/Lex.o: /usr/include/CC/stl_algobase.h /usr/include/CC/stl_relops.h
../src/Lex.o: /usr/include/CC/stl_pair.h /usr/include/CC/type_traits.h
../src/Lex.o: /usr/include/limits.h /usr/include/CC/new.h
../src/Lex.o: /usr/include/CC/stl_iterator.h /usr/include/CC/stl_construct.h
../src/Lex.o: /usr/include/CC/stl_tempbuf.h
../src/Lex.o: /usr/include/CC/stl_uninitialized.h
../src/Lex.o: /usr/include/CC/stl_raw_storage_iter.h
../src/Lex.o: /usr/include/CC/algorithm /usr/include/CC/stl_algo.h
../src/Lex.o: /usr/include/CC/stl_heap.h /usr/include/CC/char_traits.h
../src/Lex.o: /usr/include/wchar.h /usr/include/CC/stl_hash_fun.h
../src/ParametricCurve.o: ../include/ParametricCurve.h /usr/include/CC/vector
../src/ParametricCurve.o: /usr/include/CC/stl_range_errors.h
../src/ParametricCurve.o: /usr/include/CC/stl_config.h
../src/ParametricCurve.o: /usr/include/standards.h
../src/ParametricCurve.o: /usr/include/CC/stl_algobase.h
../src/ParametricCurve.o: /usr/include/CC/stl_relops.h
../src/ParametricCurve.o: /usr/include/CC/stl_pair.h
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
../src/ParametricCurve.o: /usr/include/CC/fstream.h /usr/include/float.h
../src/ParametricCurve.o: /usr/include/CC/string
../src/ParametricCurve.o: /usr/include/CC/stl_string_fwd.h
../src/ParametricCurve.o: /usr/include/ctype.h /usr/include/locale_attr.h
../src/ParametricCurve.o: /usr/include/CC/functional
../src/ParametricCurve.o: /usr/include/CC/stl_function.h
../src/ParametricCurve.o: /usr/include/CC/stdexcept
../src/ParametricCurve.o: /usr/include/CC/stl_exception.h
../src/ParametricCurve.o: /usr/include/CC/memory
../src/ParametricCurve.o: /usr/include/CC/stl_tempbuf.h
../src/ParametricCurve.o: /usr/include/CC/stl_raw_storage_iter.h
../src/ParametricCurve.o: /usr/include/CC/algorithm
../src/ParametricCurve.o: /usr/include/CC/stl_algo.h
../src/ParametricCurve.o: /usr/include/CC/stl_heap.h
../src/ParametricCurve.o: /usr/include/CC/char_traits.h /usr/include/wchar.h
../src/ParametricCurve.o: /usr/include/CC/stl_hash_fun.h
../src/PositionVector.o: ../include/PositionVector.h /usr/include/math.h
../src/PositionVector.o: /usr/include/sgidefs.h /usr/include/standards.h
../src/PositionVector.o: ../include/mathsym.h /usr/include/CC/vector
../src/PositionVector.o: /usr/include/CC/stl_range_errors.h
../src/PositionVector.o: /usr/include/CC/stl_config.h
../src/PositionVector.o: /usr/include/CC/stl_algobase.h
../src/PositionVector.o: /usr/include/CC/stl_relops.h
../src/PositionVector.o: /usr/include/CC/stl_pair.h
../src/PositionVector.o: /usr/include/CC/type_traits.h /usr/include/string.h
../src/PositionVector.o: /usr/include/limits.h /usr/include/stdlib.h
../src/PositionVector.o: /usr/include/stddef.h /usr/include/CC/new.h
../src/PositionVector.o: /usr/include/CC/iostream.h /usr/include/memory.h
../src/PositionVector.o: /usr/include/CC/stl_iterator_base.h
../src/PositionVector.o: /usr/include/CC/stl_iterator.h
../src/PositionVector.o: /usr/include/CC/stl_alloc.h /usr/include/stdio.h
../src/PositionVector.o: /usr/include/assert.h /usr/include/CC/stl_threads.h
../src/PositionVector.o: /usr/include/mutex.h /usr/include/time.h
../src/PositionVector.o: /usr/include/CC/stl_construct.h
../src/PositionVector.o: /usr/include/CC/stl_uninitialized.h
../src/PositionVector.o: /usr/include/CC/stl_vector.h
../src/PositionVector.o: /usr/include/CC/stl_bvector.h ../include/Point.h
../src/PositionVector.o: ../include/PointI.h ../include/RMatrix.h
../src/PositionVector.o: ../include/Rotation.h ../include/TMatrix.h
../src/PositionVector.o: /usr/include/CC/stream.h /usr/include/CC/iomanip.h
../src/PositionVector.o: /usr/include/CC/generic.h
../src/PositionVector.o: /usr/include/CC/stdiostream.h
../src/PositionVector.o: /usr/include/CC/fstream.h ../include/TMatrixI.h
../src/RMatrix.o: ../include/RMatrix.h /usr/include/math.h
../src/RMatrix.o: /usr/include/sgidefs.h /usr/include/standards.h
../src/RMatrix.o: ../include/mathsym.h ../include/Rotation.h
../src/RMatrix.o: ../include/TMatrix.h /usr/include/CC/stream.h
../src/RMatrix.o: /usr/include/CC/iostream.h /usr/include/memory.h
../src/RMatrix.o: /usr/include/stddef.h /usr/include/CC/iomanip.h
../src/RMatrix.o: /usr/include/CC/generic.h /usr/include/CC/stdiostream.h
../src/RMatrix.o: /usr/include/stdio.h /usr/include/CC/fstream.h
../src/RMatrix.o: /usr/include/CC/vector /usr/include/CC/stl_range_errors.h
../src/RMatrix.o: /usr/include/CC/stl_config.h /usr/include/CC/stl_algobase.h
../src/RMatrix.o: /usr/include/CC/stl_relops.h /usr/include/CC/stl_pair.h
../src/RMatrix.o: /usr/include/CC/type_traits.h /usr/include/string.h
../src/RMatrix.o: /usr/include/limits.h /usr/include/stdlib.h
../src/RMatrix.o: /usr/include/CC/new.h /usr/include/CC/stl_iterator_base.h
../src/RMatrix.o: /usr/include/CC/stl_iterator.h /usr/include/CC/stl_alloc.h
../src/RMatrix.o: /usr/include/assert.h /usr/include/CC/stl_threads.h
../src/RMatrix.o: /usr/include/mutex.h /usr/include/time.h
../src/RMatrix.o: /usr/include/CC/stl_construct.h
../src/RMatrix.o: /usr/include/CC/stl_uninitialized.h
../src/RMatrix.o: /usr/include/CC/stl_vector.h /usr/include/CC/stl_bvector.h
../src/RMatrix.o: ../include/TMatrixI.h
../src/HRMatrix.o: ../include/HRMatrix.h /usr/include/CC/vector.h
../src/HRMatrix.o: /usr/include/CC/stl_range_errors.h
../src/HRMatrix.o: /usr/include/CC/stl_config.h /usr/include/standards.h
../src/HRMatrix.o: /usr/include/CC/algobase.h /usr/include/CC/pair.h
../src/HRMatrix.o: /usr/include/CC/stl_relops.h /usr/include/CC/stl_pair.h
../src/HRMatrix.o: /usr/include/CC/iterator.h /usr/include/CC/function.h
../src/HRMatrix.o: /usr/include/stddef.h /usr/include/sgidefs.h
../src/HRMatrix.o: /usr/include/CC/stl_function.h /usr/include/CC/iostream.h
../src/HRMatrix.o: /usr/include/memory.h /usr/include/CC/stl_iterator_base.h
../src/HRMatrix.o: /usr/include/CC/stl_iterator.h
../src/HRMatrix.o: /usr/include/CC/type_traits.h
../src/HRMatrix.o: /usr/include/CC/stl_construct.h /usr/include/CC/new.h
../src/HRMatrix.o: /usr/include/CC/stl_raw_storage_iter.h
../src/HRMatrix.o: /usr/include/CC/stl_algobase.h /usr/include/string.h
../src/HRMatrix.o: /usr/include/limits.h /usr/include/stdlib.h
../src/HRMatrix.o: /usr/include/CC/stl_uninitialized.h
../src/HRMatrix.o: /usr/include/CC/alloc.h /usr/include/CC/stl_alloc.h
../src/HRMatrix.o: /usr/include/stdio.h /usr/include/assert.h
../src/HRMatrix.o: /usr/include/CC/stl_threads.h /usr/include/mutex.h
../src/HRMatrix.o: /usr/include/time.h /usr/include/CC/stl_vector.h
../src/HRMatrix.o: ../include/Rotation.h ../include/mathsym.h
../src/HRMatrix.o: /usr/include/math.h ../include/Point.h
../src/HRMatrix.o: ../include/PositionVector.h /usr/include/CC/vector
../src/HRMatrix.o: /usr/include/CC/stl_bvector.h ../include/RMatrix.h
../src/HRMatrix.o: ../include/TMatrix.h /usr/include/CC/stream.h
../src/HRMatrix.o: /usr/include/CC/iomanip.h /usr/include/CC/generic.h
../src/HRMatrix.o: /usr/include/CC/stdiostream.h /usr/include/CC/fstream.h
../src/HRMatrix.o: ../include/TMatrixI.h ../include/PointI.h
../src/hrmatrix.o: /usr/include/stdlib.h /usr/include/standards.h
../src/hrmatrix.o: /usr/include/sgidefs.h /usr/include/CC/iostream.h
../src/hrmatrix.o: /usr/include/memory.h /usr/include/stddef.h
../src/hrmatrix.o: /usr/include/CC/algorithm /usr/include/CC/stl_algobase.h
../src/hrmatrix.o: /usr/include/CC/stl_relops.h /usr/include/CC/stl_pair.h
../src/hrmatrix.o: /usr/include/CC/type_traits.h /usr/include/string.h
../src/hrmatrix.o: /usr/include/limits.h /usr/include/CC/new.h
../src/hrmatrix.o: /usr/include/CC/stl_iterator_base.h
../src/hrmatrix.o: /usr/include/CC/stl_iterator.h
../src/hrmatrix.o: /usr/include/CC/stl_construct.h
../src/hrmatrix.o: /usr/include/CC/stl_uninitialized.h
../src/hrmatrix.o: /usr/include/CC/stl_tempbuf.h /usr/include/CC/stl_algo.h
../src/hrmatrix.o: /usr/include/CC/stl_heap.h ../include/HRMatrix.h
../src/hrmatrix.o: /usr/include/CC/vector.h
../src/hrmatrix.o: /usr/include/CC/stl_range_errors.h
../src/hrmatrix.o: /usr/include/CC/stl_config.h /usr/include/CC/algobase.h
../src/hrmatrix.o: /usr/include/CC/pair.h /usr/include/CC/iterator.h
../src/hrmatrix.o: /usr/include/CC/function.h /usr/include/CC/stl_function.h
../src/hrmatrix.o: /usr/include/CC/stl_raw_storage_iter.h
../src/hrmatrix.o: /usr/include/CC/alloc.h /usr/include/CC/stl_alloc.h
../src/hrmatrix.o: /usr/include/stdio.h /usr/include/assert.h
../src/hrmatrix.o: /usr/include/CC/stl_threads.h /usr/include/mutex.h
../src/hrmatrix.o: /usr/include/time.h /usr/include/CC/stl_vector.h
../src/hrmatrix.o: ../include/Rotation.h ../include/mathsym.h
../src/hrmatrix.o: /usr/include/math.h ../include/Point.h
../src/hrmatrix.o: ../include/PositionVector.h /usr/include/CC/vector
../src/hrmatrix.o: /usr/include/CC/stl_bvector.h ../include/RMatrix.h
../src/hrmatrix.o: ../include/TMatrix.h /usr/include/CC/stream.h
../src/hrmatrix.o: /usr/include/CC/iomanip.h /usr/include/CC/generic.h
../src/hrmatrix.o: /usr/include/CC/stdiostream.h /usr/include/CC/fstream.h
../src/hrmatrix.o: ../include/TMatrixI.h ../include/PointI.h
