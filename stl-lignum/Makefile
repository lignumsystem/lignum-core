MAIN = main.cc
OBJ  = main.o

ALGSRC = algorithms.cc 
ALGOBJ  = algorithms.o 

CCC = CC -64 

#OPTIMIZE = -Ofast=ip28 -IPA
OPTIMIZE   = -g 

SUPPRESS = #-w 1155 -w 1183

CCCFLAGS = -c -ptv -prelink #-fullwarn 

INCLUDE = -Iinclude -I../c++adt/include 

STL     = -I/usr/include/CC

LIBFLAGS = -L../c++adt/lib -Llib

LIB1   = libc++adt.a
LIB2   = libLGM.a

LIBADT = -lc++adt
LIBLGM = -lLGM
LIBMATH  = -lm 

LIBS     = $(LIBLGM) $(LIBADT) $(LIBMATH)


.SUFFIXES: .o .cc

lignum: $(OBJ) $(LIB1)  $(LIB2)  
	$(CCC)  -o $@ $(INLUDE) $(OBJ) $(LIBFLAGS) $(LIBS) 
algorithms: $(ALGOBJ) $(LIB1)  $(LIB2)
	$(CCC) -ptv  -o $@ $(INLUDE) $(OPTIMIZE) $(ALGOBJ) $(LIBFLAGS) $(LIBS)

$(LIB1):
	(cd ../c++adt/lib; make "CCC=$(CCC)" "CCCFLAGS=$(CCCFLAGS)" "OPTIMIZE=$(OPTIMIZE)" $@)

$(LIB2):
	(cd lib; make "CCC=$(CCC)" "CCCFLAGS=$(CCCFLAGS)" "OPTIMIZE=$(OPTIMIZE)" $@)

.cc.o: 
	$(CCC) $(OPTIMIZE) $(SUPPRESS) $(CCCFLAGS) $(INCLUDE)  $< -o $@

clean:
	(cd lib; make clean)
	rm -rf $(OBJ) $(ALGOBJ) core lignum algorithms ii_files
distclean:
	(cd ../c++adt/lib; make distclean)
	(cd lib; make distclean)
	rm -rf $(OBJ) $(ALGOBJ) core lignum algorithms ii_files 

depend: 
	makedepend $(INCLUDE) $(CCCINCLUDE) $(STL) $(MAIN) $(ALGSRC) 
# DO NOT DELETE

main.o: /usr/include/stdlib.h /usr/include/standards.h /usr/include/sgidefs.h
main.o: /usr/include/CC/iostream.h /usr/include/memory.h
main.o: /usr/include/stddef.h /usr/include/CC/list
main.o: /usr/include/CC/stl_algobase.h /usr/include/CC/stl_config.h
main.o: /usr/include/CC/stl_relops.h /usr/include/CC/stl_pair.h
main.o: /usr/include/CC/type_traits.h /usr/include/string.h
main.o: /usr/include/limits.h /usr/include/CC/new.h
main.o: /usr/include/CC/stl_iterator_base.h /usr/include/CC/stl_iterator.h
main.o: /usr/include/CC/stl_alloc.h /usr/include/stdio.h
main.o: /usr/include/assert.h /usr/include/CC/stl_construct.h
main.o: /usr/include/CC/stl_uninitialized.h /usr/include/CC/stl_list.h
main.o: /usr/include/CC/algorithm /usr/include/CC/stl_tempbuf.h
main.o: /usr/include/CC/stl_algo.h /usr/include/CC/stl_heap.h
main.o: include/MyTreeSegment.h include/Tree.h ../c++adt/include/CString.h
main.o: /usr/include/ctype.h /usr/include/locale_attr.h
main.o: /usr/include/CC/stream.h /usr/include/CC/iomanip.h
main.o: /usr/include/CC/generic.h /usr/include/CC/stdiostream.h
main.o: /usr/include/CC/fstream.h ../c++adt/include/ParametricCurve.h
main.o: /usr/include/CC/vector /usr/include/CC/stl_range_errors.h
main.o: /usr/include/CC/stl_vector.h /usr/include/CC/stl_bvector.h
main.o: /usr/include/float.h include/TreeMetaFileParser.h
main.o: ../c++adt/include/Table.h ../c++adt/include/DList.h
main.o: ../c++adt/include/DListElement.h ../c++adt/include/boolean.h
main.o: ../c++adt/include/Lex.h include/RootSystem.h include/LGMSymbols.h
main.o: /usr/include/CC/map /usr/include/CC/stl_tree.h
main.o: /usr/include/CC/stl_function.h /usr/include/CC/stl_map.h
main.o: /usr/include/CC/stl_multimap.h include/Bud.h include/TreeSegment.h
main.o: ../c++adt/include/Point.h /usr/include/math.h
main.o: include/TreeCompartment.h include/LGMdecl.h include/LGMUnits.h
main.o: ../c++adt/include/PositionVector.h ../c++adt/include/mathsym.h
main.o: ../c++adt/include/RMatrix.h ../c++adt/include/TMatrix.h
main.o: include/TreeCompartmentI.h include/DefaultBud.h
main.o: include/TreeSegmentI.h include/BudI.h include/BranchingPoint.h
main.o: /usr/include/CC/numeric /usr/include/CC/stl_numeric.h
main.o: include/TreeFunctor.h include/Algorithms.h /usr/include/CC/functional
main.o: include/AlgorithmsI.h include/TreeFunctorI.h include/Axis.h
main.o: include/AxisI.h include/BranchingPointI.h
main.o: ../c++adt/include/ConnectionMatrix.h include/TreeI.h
main.o: include/HwTreeSegment.h include/CfTreeSegment.h include/MyBud.h
algorithms.o: /usr/include/stdlib.h /usr/include/standards.h
algorithms.o: /usr/include/sgidefs.h /usr/include/CC/iostream.h
algorithms.o: /usr/include/memory.h /usr/include/stddef.h
algorithms.o: /usr/include/CC/list /usr/include/CC/stl_algobase.h
algorithms.o: /usr/include/CC/stl_config.h /usr/include/CC/stl_relops.h
algorithms.o: /usr/include/CC/stl_pair.h /usr/include/CC/type_traits.h
algorithms.o: /usr/include/string.h /usr/include/limits.h
algorithms.o: /usr/include/CC/new.h /usr/include/CC/stl_iterator_base.h
algorithms.o: /usr/include/CC/stl_iterator.h /usr/include/CC/stl_alloc.h
algorithms.o: /usr/include/stdio.h /usr/include/assert.h
algorithms.o: /usr/include/CC/stl_construct.h
algorithms.o: /usr/include/CC/stl_uninitialized.h /usr/include/CC/stl_list.h
algorithms.o: /usr/include/CC/algorithm /usr/include/CC/stl_tempbuf.h
algorithms.o: /usr/include/CC/stl_algo.h /usr/include/CC/stl_heap.h
algorithms.o: include/MyTreeSegment.h include/Tree.h
algorithms.o: ../c++adt/include/CString.h /usr/include/ctype.h
algorithms.o: /usr/include/locale_attr.h /usr/include/CC/stream.h
algorithms.o: /usr/include/CC/iomanip.h /usr/include/CC/generic.h
algorithms.o: /usr/include/CC/stdiostream.h /usr/include/CC/fstream.h
algorithms.o: ../c++adt/include/ParametricCurve.h /usr/include/CC/vector
algorithms.o: /usr/include/CC/stl_range_errors.h /usr/include/CC/stl_vector.h
algorithms.o: /usr/include/CC/stl_bvector.h /usr/include/float.h
algorithms.o: include/TreeMetaFileParser.h ../c++adt/include/Table.h
algorithms.o: ../c++adt/include/DList.h ../c++adt/include/DListElement.h
algorithms.o: ../c++adt/include/boolean.h ../c++adt/include/Lex.h
algorithms.o: include/RootSystem.h include/LGMSymbols.h /usr/include/CC/map
algorithms.o: /usr/include/CC/stl_tree.h /usr/include/CC/stl_function.h
algorithms.o: /usr/include/CC/stl_map.h /usr/include/CC/stl_multimap.h
algorithms.o: include/Bud.h include/TreeSegment.h ../c++adt/include/Point.h
algorithms.o: /usr/include/math.h include/TreeCompartment.h include/LGMdecl.h
algorithms.o: include/LGMUnits.h ../c++adt/include/PositionVector.h
algorithms.o: ../c++adt/include/mathsym.h ../c++adt/include/RMatrix.h
algorithms.o: ../c++adt/include/TMatrix.h include/TreeCompartmentI.h
algorithms.o: include/DefaultBud.h include/TreeSegmentI.h include/BudI.h
algorithms.o: include/BranchingPoint.h /usr/include/CC/numeric
algorithms.o: /usr/include/CC/stl_numeric.h include/TreeFunctor.h
algorithms.o: include/Algorithms.h /usr/include/CC/functional
algorithms.o: include/AlgorithmsI.h include/TreeFunctorI.h include/Axis.h
algorithms.o: include/AxisI.h include/BranchingPointI.h
algorithms.o: ../c++adt/include/ConnectionMatrix.h include/TreeI.h
algorithms.o: include/HwTreeSegment.h include/CfTreeSegment.h include/MyBud.h
