
SRCDIR1 = ../src
SRCDIR2 = ../include

SRC = $(SRCDIR1)/CString.cc  $(SRCDIR1)/DList.cc $(SRCDIR1)/DListElement.cc \
      $(SRCDIR1)/Ellipsis.cc $(SRCDIR1)/Lex.cc $(SRCDIR1)/ParametricCurve.cc \
      $(SRCDIR1)/PositionVector.cc $(SRCDIR1)/RMatrix.cc 

OBJ = $(SRCDIR1)/CString.o $(SRCDIR1)/DList.o $(SRCDIR1)/DListElement.o \
      $(SRCDIR1)/Ellipsis.o $(SRCDIR1)/Lex.o $(SRCDIR1)/ParametricCurve.o \
      $(SRCDIR1)/PositionVector.o $(SRCDIR1)/RMatrix.o 

INCLUDE= -I../include -I/usr/include/CC 

CCC = CC -64
ETAGS = etags -d -T -C -o

OPTIMIZE = -O
CCCFLAGS =   -c 

.SUFFIXES: .o .cc

AR =  $(ARCOMMAND)
ARFLAGS =  $(ARCOMMANDFLAGS)
ARFILE = libc++adt.a


$(ARFILE): $(OBJ)
	$(AR) $(ARFLAGS) $(ARFILE) $(OBJ)

.cc.o: 
	$(CCC)  $(OPTIMIZE) $(CCCFLAGS) $(INCLUDE) $<  -o $@  

touch:
	touch $(SRC)

clean:
	rm -f $(OBJ) core

distclean: clean
	rm -rf ../src/ii_files ../include/ii_files ii_files $(ARFILE)

etags:
	$(ETAGS)   TAGSFILE ../src/*.cc ../include/*.h
depend:
	makedepend $(INCLUDE) $(SRC)
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
../src/Lex.o: ../include/Lex.h ../include/DList.h ../include/DListElement.h
../src/Lex.o: ../include/boolean.h ../include/CString.h /usr/include/string.h
../src/Lex.o: /usr/include/standards.h /usr/include/stdio.h
../src/Lex.o: /usr/include/sgidefs.h /usr/include/ctype.h
../src/Lex.o: /usr/include/locale_attr.h /usr/include/CC/stream.h
../src/Lex.o: /usr/include/CC/iostream.h /usr/include/memory.h
../src/Lex.o: /usr/include/stddef.h /usr/include/CC/iomanip.h
../src/Lex.o: /usr/include/CC/generic.h /usr/include/CC/stdiostream.h
../src/Lex.o: /usr/include/CC/fstream.h /usr/include/stdlib.h
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
../src/ParametricCurve.o: /usr/include/assert.h
../src/ParametricCurve.o: /usr/include/CC/stl_construct.h
../src/ParametricCurve.o: /usr/include/CC/stl_uninitialized.h
../src/ParametricCurve.o: /usr/include/CC/stl_vector.h
../src/ParametricCurve.o: /usr/include/CC/stl_bvector.h
../src/ParametricCurve.o: /usr/include/CC/fstream.h /usr/include/float.h
../src/ParametricCurve.o: ../include/CString.h /usr/include/ctype.h
../src/ParametricCurve.o: /usr/include/locale_attr.h /usr/include/CC/stream.h
../src/ParametricCurve.o: /usr/include/CC/iomanip.h /usr/include/CC/generic.h
../src/ParametricCurve.o: /usr/include/CC/stdiostream.h
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
../src/PositionVector.o: /usr/include/assert.h
../src/PositionVector.o: /usr/include/CC/stl_construct.h
../src/PositionVector.o: /usr/include/CC/stl_uninitialized.h
../src/PositionVector.o: /usr/include/CC/stl_vector.h
../src/PositionVector.o: /usr/include/CC/stl_bvector.h ../include/Point.h
../src/PositionVector.o: ../include/PointI.h ../include/RMatrix.h
../src/PositionVector.o: ../include/TMatrix.h /usr/include/CC/stream.h
../src/PositionVector.o: /usr/include/CC/iomanip.h /usr/include/CC/generic.h
../src/PositionVector.o: /usr/include/CC/stdiostream.h
../src/PositionVector.o: /usr/include/CC/fstream.h ../include/TMatrixI.h
../src/RMatrix.o: ../include/RMatrix.h /usr/include/math.h
../src/RMatrix.o: /usr/include/sgidefs.h /usr/include/standards.h
../src/RMatrix.o: ../include/mathsym.h ../include/TMatrix.h
../src/RMatrix.o: /usr/include/CC/stream.h /usr/include/CC/iostream.h
../src/RMatrix.o: /usr/include/memory.h /usr/include/stddef.h
../src/RMatrix.o: /usr/include/CC/iomanip.h /usr/include/CC/generic.h
../src/RMatrix.o: /usr/include/CC/stdiostream.h /usr/include/stdio.h
../src/RMatrix.o: /usr/include/CC/fstream.h /usr/include/CC/vector
../src/RMatrix.o: /usr/include/CC/stl_range_errors.h
../src/RMatrix.o: /usr/include/CC/stl_config.h /usr/include/CC/stl_algobase.h
../src/RMatrix.o: /usr/include/CC/stl_relops.h /usr/include/CC/stl_pair.h
../src/RMatrix.o: /usr/include/CC/type_traits.h /usr/include/string.h
../src/RMatrix.o: /usr/include/limits.h /usr/include/stdlib.h
../src/RMatrix.o: /usr/include/CC/new.h /usr/include/CC/stl_iterator_base.h
../src/RMatrix.o: /usr/include/CC/stl_iterator.h /usr/include/CC/stl_alloc.h
../src/RMatrix.o: /usr/include/assert.h /usr/include/CC/stl_construct.h
../src/RMatrix.o: /usr/include/CC/stl_uninitialized.h
../src/RMatrix.o: /usr/include/CC/stl_vector.h /usr/include/CC/stl_bvector.h
../src/RMatrix.o: ../include/TMatrixI.h
