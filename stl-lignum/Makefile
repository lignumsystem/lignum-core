MAIN = main.cc
OBJ  = main.o

CCC = CC -64  -ptv -ptused -prelink

SUPPRESS = #-w 1155 -w 1183

CCCFLAGS = -c #-fullwarn 

INCLUDE = -Iinclude -I../c++adt/include

STL     = -I/usr/include/CC

LIBFLAGS = -L../c++adt/lib -Llib

LIB1   = libc++adt.a
LIB2   = libLGM.a

LIBADT = -lc++adt
LIBLGM = -lLGM
LIBMATH  = -lm 

LIBS     = $(LIBLGM) $(LIBADT) $(LIBMATH)

OPTIMIZE   = -g 

.SUFFIXES: .o .cc

lignum: $(LIB1)  $(LIB2) $(OBJ)
	$(CCC) -o $@ $(OBJ) $(LIBFLAGS) $(LIBS) 

$(LIB1):
	(cd ../c++adt/lib; make "CCC=$(CCC)" "CCCFLAGS=$(CCCFLAGS)" "OPTIMIZE=$(OPTIMIZE)" $@)

$(LIB2):
	(cd lib; make "CCC=$(CCC)" "CCCFLAGS=$(CCCFLAGS)" "OPTIMIZE=$(OPTIMIZE)" $@)

.cc.o: 
	$(CCC) $(OPTIMIZE) $(SUPPRESS) $(CCCFLAGS) $(INCLUDE) $(STL) $(OPTIMIZE) $< -o $@
clean:
	(cd ../c++adt/lib; make clean)
	(cd lib; make clean)
	rm -rf $(OBJ) core lignum ii_files
distclean:
	(cd ../c++adt/lib; make distclean)
	(cd lib; make distclean)
	rm -rf $(OBJ) core lignum ii_files 

depend: 
	makedepend $(INCLUDE) $(CCCINCLUDE) $(STL) $(MAIN) 
# DO NOT DELETE

main.o: /usr/include/stdlib.h /usr/include/standards.h /usr/include/sgidefs.h
main.o: /usr/include/CC/iostream.h /usr/include/memory.h
main.o: /usr/include/stddef.h /usr/include/CC/list
main.o: /usr/include/CC/stl_algobase.h /usr/include/CC/stl_config.h
main.o: /usr/include/CC/stl_relops.h /usr/include/CC/stl_pair.h
main.o: /usr/include/CC/type_traits.h /usr/include/string.h
main.o: /usr/include/limits.h /usr/include/CC/new.h
main.o: /usr/include/CC/stl_iterator.h /usr/include/CC/stl_alloc.h
main.o: /usr/include/assert.h /usr/include/mutex.h /usr/include/time.h
main.o: /usr/include/CC/stl_construct.h /usr/include/CC/stl_uninitialized.h
main.o: /usr/include/CC/stl_list.h include/Tree.h ../c++adt/include/CString.h
main.o: /usr/include/stdio.h /usr/include/ctype.h /usr/include/locale_attr.h
main.o: /usr/include/CC/stream.h /usr/include/CC/iomanip.h
main.o: /usr/include/CC/generic.h /usr/include/CC/stdiostream.h
main.o: /usr/include/CC/fstream.h ../c++adt/include/ParametricCurve.h
main.o: /usr/include/CC/vector /usr/include/CC/stl_vector.h
main.o: /usr/include/CC/stl_bvector.h /usr/include/float.h
main.o: ../c++adt/include/Point.h /usr/include/math.h include/LGMSymbols.h
main.o: /usr/include/CC/map /usr/include/CC/stl_tree.h
main.o: /usr/include/CC/stl_function.h /usr/include/CC/stl_map.h
main.o: /usr/include/CC/stl_multimap.h include/LGMUnits.h
main.o: include/TreeMetaFileParser.h ../c++adt/include/Table.h
main.o: ../c++adt/include/DList.h ../c++adt/include/DListElement.h
main.o: ../c++adt/include/boolean.h ../c++adt/include/Lex.h
main.o: include/TreeCompartment.h ../c++adt/include/PositionVector.h
main.o: ../c++adt/include/mathsym.h ../c++adt/include/RMatrix.h
main.o: ../c++adt/include/TMatrix.h include/Axis.h include/Bud.h
main.o: include/TreeSegment.h include/BranchingPoint.h include/RootSystem.h
