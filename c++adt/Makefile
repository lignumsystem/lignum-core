
SRCDIR1 = ./src
SRCDIR2 = ./include

SRC = $(SRCDIR1)/CString.cc  $(SRCDIR1)/DList.cc $(SRCDIR1)/DListElement.cc \
      $(SRCDIR1)/Ellipsis.cc $(SRCDIR1)/Lex.cc $(SRCDIR1)/ParametricCurve.cc \
      $(SRCDIR1)/PositionVector.cc $(SRCDIR1)/RMatrix.cc 

OBJ = $(SRCDIR1)/CString.o $(SRCDIR1)/DList.o $(SRCDIR1)/DListElement.o \
      $(SRCDIR1)/Ellipsis.o $(SRCDIR1)/Lex.o $(SRCDIR1)/ParametricCurve.o \
      $(SRCDIR1)/PositionVector.o $(SRCDIR1)/RMatrix.o 

INCLUDE= -Iinclude -I/usr/include/CC 

CCC = CC -64 -LANG:std
ETAGS = etags -d -T -C -o

OPTIMIZE = -O
CCCFLAGS =   -c 

.SUFFIXES: .o .cc
ARCOMMAND = $(CCC) -ar  
ARCOMMANDFLAGS = -o
AR = $(ARCOMMAND)
ARFLAGS = $(ARCOMMANDFLAGS)
ARFILE = lib/libc++adt.a

PROGFILES = program-files.html

$(ARFILE): $(OBJ)
	$(AR) $(ARFLAGS) $(ARFILE) $(OBJ)

.cc.o: 
	$(CCC)  $(OPTIMIZE) $(CCCFLAGS) $(INCLUDE) $<  -o $@  

touch:
	touch $(SRC)

html:
	enscript -E --color -Whtml --toc -p$(PROGFILES) include/*.h $(SRC)
clean:
	rm -f $(OBJ) core

distclean: clean
	rm -rf src/ii_files include/ii_files ii_files $(ARFILE)

etags:
	$(ETAGS)   TAGSFILE ../src/*.cc ../include/*.h
depend:
	(cd lib; make depend)
	makedepend $(INCLUDE) $(SRC)
# DO NOT DELETE

./src/CString.o: include/CString.h /usr/include/string.h
./src/CString.o: /usr/include/standards.h /usr/include/stdio.h
./src/CString.o: /usr/include/sgidefs.h /usr/include/ctype.h
./src/CString.o: /usr/include/locale_attr.h /usr/include/CC/iostream
./src/CString.o: /usr/include/CC/iosfwd /usr/include/CC/stl_config.h
./src/CString.o: /usr/include/wchar.h /usr/include/time.h
./src/CString.o: /usr/include/stddef.h /usr/include/CC/functional
./src/CString.o: /usr/include/CC/stl_function.h /usr/include/CC/char_traits.h
./src/CString.o: /usr/include/CC/istream /usr/include/CC/ostream
./src/CString.o: /usr/include/CC/ios /usr/include/CC/stl_string_fwd.h
./src/CString.o: /usr/include/CC/stl_alloc.h /usr/include/stdlib.h
./src/CString.o: /usr/include/assert.h /usr/include/CC/stl_threads.h
./src/CString.o: /usr/include/mutex.h /usr/include/CC/stl_exception.h
./src/CString.o: /usr/include/CC/utility /usr/include/CC/stl_relops.h
./src/CString.o: /usr/include/CC/stl_pair.h /usr/include/CC/stl_locale.h
./src/CString.o: /usr/include/CC/typeinfo /usr/include/CC/exception
./src/CString.o: /usr/include/CC/string /usr/include/CC/stdexcept
./src/CString.o: /usr/include/CC/stl_iterator_base.h /usr/include/CC/memory
./src/CString.o: /usr/include/CC/stl_algobase.h /usr/include/CC/type_traits.h
./src/CString.o: /usr/include/limits.h /usr/include/CC/new.h
./src/CString.o: /usr/include/CC/iostream.h /usr/include/memory.h
./src/CString.o: /usr/include/CC/stl_iterator.h
./src/CString.o: /usr/include/CC/stl_construct.h
./src/CString.o: /usr/include/CC/stl_tempbuf.h
./src/CString.o: /usr/include/CC/stl_uninitialized.h
./src/CString.o: /usr/include/CC/stl_raw_storage_iter.h
./src/CString.o: /usr/include/CC/algorithm /usr/include/CC/stl_algo.h
./src/CString.o: /usr/include/CC/stl_heap.h /usr/include/CC/stl_hash_fun.h
./src/CString.o: /usr/include/CC/stl_ctype.h /usr/include/CC/c_locale.h
./src/CString.o: /usr/include/CC/streambuf /usr/include/CC/stl_stdio_file.h
./src/CString.o: /usr/include/CC/stl_numeric_facets.h /usr/include/CC/limits
./src/CString.o: /usr/include/float.h
./src/DList.o: /usr/include/CC/iostream.h /usr/include/memory.h
./src/DList.o: /usr/include/stddef.h /usr/include/sgidefs.h
./src/DList.o: /usr/include/stdlib.h /usr/include/standards.h include/DList.h
./src/DList.o: include/DListElement.h include/boolean.h
./src/DListElement.o: include/DListElement.h /usr/include/stdlib.h
./src/DListElement.o: /usr/include/standards.h /usr/include/sgidefs.h
./src/Ellipsis.o: include/Ellipsis.h /usr/include/math.h
./src/Ellipsis.o: /usr/include/sgidefs.h /usr/include/standards.h
./src/Ellipsis.o: include/mathsym.h
./src/Lex.o: include/Lex.h /usr/include/CC/fstream /usr/include/CC/istream
./src/Lex.o: /usr/include/CC/ostream /usr/include/CC/ios
./src/Lex.o: /usr/include/CC/stl_config.h /usr/include/standards.h
./src/Lex.o: /usr/include/CC/stl_string_fwd.h /usr/include/stddef.h
./src/Lex.o: /usr/include/sgidefs.h /usr/include/CC/stl_alloc.h
./src/Lex.o: /usr/include/stdio.h /usr/include/stdlib.h /usr/include/string.h
./src/Lex.o: /usr/include/assert.h /usr/include/CC/stl_threads.h
./src/Lex.o: /usr/include/mutex.h /usr/include/time.h
./src/Lex.o: /usr/include/CC/stl_exception.h /usr/include/CC/utility
./src/Lex.o: /usr/include/CC/stl_relops.h /usr/include/CC/stl_pair.h
./src/Lex.o: /usr/include/CC/iosfwd /usr/include/wchar.h
./src/Lex.o: /usr/include/locale_attr.h /usr/include/ctype.h
./src/Lex.o: /usr/include/CC/functional /usr/include/CC/stl_function.h
./src/Lex.o: /usr/include/CC/char_traits.h /usr/include/CC/stl_locale.h
./src/Lex.o: /usr/include/CC/typeinfo /usr/include/CC/exception
./src/Lex.o: /usr/include/CC/string /usr/include/CC/stdexcept
./src/Lex.o: /usr/include/CC/stl_iterator_base.h /usr/include/CC/memory
./src/Lex.o: /usr/include/CC/stl_algobase.h /usr/include/CC/type_traits.h
./src/Lex.o: /usr/include/limits.h /usr/include/CC/new.h
./src/Lex.o: /usr/include/CC/iostream.h /usr/include/memory.h
./src/Lex.o: /usr/include/CC/stl_iterator.h /usr/include/CC/stl_construct.h
./src/Lex.o: /usr/include/CC/stl_tempbuf.h
./src/Lex.o: /usr/include/CC/stl_uninitialized.h
./src/Lex.o: /usr/include/CC/stl_raw_storage_iter.h /usr/include/CC/algorithm
./src/Lex.o: /usr/include/CC/stl_algo.h /usr/include/CC/stl_heap.h
./src/Lex.o: /usr/include/CC/stl_hash_fun.h /usr/include/CC/stl_ctype.h
./src/Lex.o: /usr/include/CC/c_locale.h /usr/include/CC/streambuf
./src/Lex.o: /usr/include/CC/stl_stdio_file.h
./src/Lex.o: /usr/include/CC/stl_numeric_facets.h /usr/include/CC/limits
./src/Lex.o: /usr/include/float.h /usr/include/CC/stl_codecvt.h
./src/Lex.o: include/DList.h include/DListElement.h include/boolean.h
./src/Lex.o: /usr/include/CC/fstream.h
./src/ParametricCurve.o: include/ParametricCurve.h /usr/include/CC/vector
./src/ParametricCurve.o: /usr/include/CC/stl_range_errors.h
./src/ParametricCurve.o: /usr/include/CC/stl_config.h
./src/ParametricCurve.o: /usr/include/standards.h
./src/ParametricCurve.o: /usr/include/CC/stl_algobase.h
./src/ParametricCurve.o: /usr/include/CC/type_traits.h /usr/include/string.h
./src/ParametricCurve.o: /usr/include/limits.h /usr/include/sgidefs.h
./src/ParametricCurve.o: /usr/include/stdlib.h /usr/include/stddef.h
./src/ParametricCurve.o: /usr/include/CC/new.h /usr/include/CC/iostream.h
./src/ParametricCurve.o: /usr/include/memory.h
./src/ParametricCurve.o: /usr/include/CC/stl_iterator_base.h
./src/ParametricCurve.o: /usr/include/CC/stl_iterator.h
./src/ParametricCurve.o: /usr/include/CC/stl_alloc.h /usr/include/stdio.h
./src/ParametricCurve.o: /usr/include/assert.h /usr/include/CC/stl_threads.h
./src/ParametricCurve.o: /usr/include/mutex.h /usr/include/time.h
./src/ParametricCurve.o: /usr/include/CC/stl_construct.h
./src/ParametricCurve.o: /usr/include/CC/stl_uninitialized.h
./src/ParametricCurve.o: /usr/include/CC/stl_vector.h
./src/ParametricCurve.o: /usr/include/CC/stl_bvector.h
./src/ParametricCurve.o: /usr/include/CC/fstream /usr/include/CC/istream
./src/ParametricCurve.o: /usr/include/CC/ostream /usr/include/CC/ios
./src/ParametricCurve.o: /usr/include/CC/stl_string_fwd.h
./src/ParametricCurve.o: /usr/include/CC/stl_exception.h
./src/ParametricCurve.o: /usr/include/CC/utility /usr/include/CC/stl_relops.h
./src/ParametricCurve.o: /usr/include/CC/stl_pair.h /usr/include/CC/iosfwd
./src/ParametricCurve.o: /usr/include/wchar.h /usr/include/locale_attr.h
./src/ParametricCurve.o: /usr/include/ctype.h /usr/include/CC/functional
./src/ParametricCurve.o: /usr/include/CC/stl_function.h
./src/ParametricCurve.o: /usr/include/CC/char_traits.h
./src/ParametricCurve.o: /usr/include/CC/stl_locale.h
./src/ParametricCurve.o: /usr/include/CC/typeinfo /usr/include/CC/exception
./src/ParametricCurve.o: /usr/include/CC/string /usr/include/CC/stdexcept
./src/ParametricCurve.o: /usr/include/CC/memory /usr/include/CC/stl_tempbuf.h
./src/ParametricCurve.o: /usr/include/CC/stl_raw_storage_iter.h
./src/ParametricCurve.o: /usr/include/CC/algorithm /usr/include/CC/stl_algo.h
./src/ParametricCurve.o: /usr/include/CC/stl_heap.h
./src/ParametricCurve.o: /usr/include/CC/stl_hash_fun.h
./src/ParametricCurve.o: /usr/include/CC/stl_ctype.h
./src/ParametricCurve.o: /usr/include/CC/c_locale.h /usr/include/CC/streambuf
./src/ParametricCurve.o: /usr/include/CC/stl_stdio_file.h
./src/ParametricCurve.o: /usr/include/CC/stl_numeric_facets.h
./src/ParametricCurve.o: /usr/include/CC/limits /usr/include/float.h
./src/ParametricCurve.o: /usr/include/CC/stl_codecvt.h
./src/ParametricCurve.o: /usr/include/CC/iostream
./src/PositionVector.o: include/Point.h /usr/include/math.h
./src/PositionVector.o: /usr/include/sgidefs.h /usr/include/standards.h
./src/PositionVector.o: /usr/include/CC/iostream /usr/include/CC/iosfwd
./src/PositionVector.o: /usr/include/CC/stl_config.h /usr/include/wchar.h
./src/PositionVector.o: /usr/include/locale_attr.h /usr/include/stdio.h
./src/PositionVector.o: /usr/include/ctype.h /usr/include/time.h
./src/PositionVector.o: /usr/include/stddef.h /usr/include/CC/functional
./src/PositionVector.o: /usr/include/CC/stl_function.h
./src/PositionVector.o: /usr/include/CC/char_traits.h /usr/include/string.h
./src/PositionVector.o: /usr/include/CC/istream /usr/include/CC/ostream
./src/PositionVector.o: /usr/include/CC/ios /usr/include/CC/stl_string_fwd.h
./src/PositionVector.o: /usr/include/CC/stl_alloc.h /usr/include/stdlib.h
./src/PositionVector.o: /usr/include/assert.h /usr/include/CC/stl_threads.h
./src/PositionVector.o: /usr/include/mutex.h /usr/include/CC/stl_exception.h
./src/PositionVector.o: /usr/include/CC/utility /usr/include/CC/stl_relops.h
./src/PositionVector.o: /usr/include/CC/stl_pair.h
./src/PositionVector.o: /usr/include/CC/stl_locale.h /usr/include/CC/typeinfo
./src/PositionVector.o: /usr/include/CC/exception /usr/include/CC/string
./src/PositionVector.o: /usr/include/CC/stdexcept
./src/PositionVector.o: /usr/include/CC/stl_iterator_base.h
./src/PositionVector.o: /usr/include/CC/memory /usr/include/CC/stl_algobase.h
./src/PositionVector.o: /usr/include/CC/type_traits.h /usr/include/limits.h
./src/PositionVector.o: /usr/include/CC/new.h /usr/include/CC/iostream.h
./src/PositionVector.o: /usr/include/memory.h /usr/include/CC/stl_iterator.h
./src/PositionVector.o: /usr/include/CC/stl_construct.h
./src/PositionVector.o: /usr/include/CC/stl_tempbuf.h
./src/PositionVector.o: /usr/include/CC/stl_uninitialized.h
./src/PositionVector.o: /usr/include/CC/stl_raw_storage_iter.h
./src/PositionVector.o: /usr/include/CC/algorithm /usr/include/CC/stl_algo.h
./src/PositionVector.o: /usr/include/CC/stl_heap.h
./src/PositionVector.o: /usr/include/CC/stl_hash_fun.h
./src/PositionVector.o: /usr/include/CC/stl_ctype.h
./src/PositionVector.o: /usr/include/CC/c_locale.h /usr/include/CC/streambuf
./src/PositionVector.o: /usr/include/CC/stl_stdio_file.h
./src/PositionVector.o: /usr/include/CC/stl_numeric_facets.h
./src/PositionVector.o: /usr/include/CC/limits /usr/include/float.h
./src/PositionVector.o: include/PositionVector.h include/mathsym.h
./src/PositionVector.o: /usr/include/CC/vector
./src/PositionVector.o: /usr/include/CC/stl_range_errors.h
./src/PositionVector.o: /usr/include/CC/stl_vector.h
./src/PositionVector.o: /usr/include/CC/stl_bvector.h include/RMatrix.h
./src/PositionVector.o: include/Rotation.h include/TMatrix.h
./src/PositionVector.o: include/TMatrixI.h include/PointI.h
./src/RMatrix.o: include/RMatrix.h /usr/include/math.h /usr/include/sgidefs.h
./src/RMatrix.o: /usr/include/standards.h include/mathsym.h
./src/RMatrix.o: include/Rotation.h include/TMatrix.h
./src/RMatrix.o: /usr/include/CC/iostream /usr/include/CC/iosfwd
./src/RMatrix.o: /usr/include/CC/stl_config.h /usr/include/wchar.h
./src/RMatrix.o: /usr/include/locale_attr.h /usr/include/stdio.h
./src/RMatrix.o: /usr/include/ctype.h /usr/include/time.h
./src/RMatrix.o: /usr/include/stddef.h /usr/include/CC/functional
./src/RMatrix.o: /usr/include/CC/stl_function.h /usr/include/CC/char_traits.h
./src/RMatrix.o: /usr/include/string.h /usr/include/CC/istream
./src/RMatrix.o: /usr/include/CC/ostream /usr/include/CC/ios
./src/RMatrix.o: /usr/include/CC/stl_string_fwd.h /usr/include/CC/stl_alloc.h
./src/RMatrix.o: /usr/include/stdlib.h /usr/include/assert.h
./src/RMatrix.o: /usr/include/CC/stl_threads.h /usr/include/mutex.h
./src/RMatrix.o: /usr/include/CC/stl_exception.h /usr/include/CC/utility
./src/RMatrix.o: /usr/include/CC/stl_relops.h /usr/include/CC/stl_pair.h
./src/RMatrix.o: /usr/include/CC/stl_locale.h /usr/include/CC/typeinfo
./src/RMatrix.o: /usr/include/CC/exception /usr/include/CC/string
./src/RMatrix.o: /usr/include/CC/stdexcept
./src/RMatrix.o: /usr/include/CC/stl_iterator_base.h /usr/include/CC/memory
./src/RMatrix.o: /usr/include/CC/stl_algobase.h /usr/include/CC/type_traits.h
./src/RMatrix.o: /usr/include/limits.h /usr/include/CC/new.h
./src/RMatrix.o: /usr/include/CC/iostream.h /usr/include/memory.h
./src/RMatrix.o: /usr/include/CC/stl_iterator.h
./src/RMatrix.o: /usr/include/CC/stl_construct.h
./src/RMatrix.o: /usr/include/CC/stl_tempbuf.h
./src/RMatrix.o: /usr/include/CC/stl_uninitialized.h
./src/RMatrix.o: /usr/include/CC/stl_raw_storage_iter.h
./src/RMatrix.o: /usr/include/CC/algorithm /usr/include/CC/stl_algo.h
./src/RMatrix.o: /usr/include/CC/stl_heap.h /usr/include/CC/stl_hash_fun.h
./src/RMatrix.o: /usr/include/CC/stl_ctype.h /usr/include/CC/c_locale.h
./src/RMatrix.o: /usr/include/CC/streambuf /usr/include/CC/stl_stdio_file.h
./src/RMatrix.o: /usr/include/CC/stl_numeric_facets.h /usr/include/CC/limits
./src/RMatrix.o: /usr/include/float.h /usr/include/CC/vector
./src/RMatrix.o: /usr/include/CC/stl_range_errors.h
./src/RMatrix.o: /usr/include/CC/stl_vector.h /usr/include/CC/stl_bvector.h
./src/RMatrix.o: include/TMatrixI.h
