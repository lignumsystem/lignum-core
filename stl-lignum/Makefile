MAIN = main.cc
OBJ  = main.o

ALGSRC = algorithms.cc 
ALGOBJ  = algorithms.o 

BLSRC  = broadleaf.cc
BLOBJ  = broadleaf.o
 
CCC = CC -64 

#OPTIMIZE = -Ofast=ip28 -IPA
OPTIMIZE   = -g 

ARCOMMAND =  $(CCC) -ar  
ARCOMMANDFLAGS = -o 

SUPPRESS = #-w 1155 -w 1183

CCCFLAGS = -c -ptv -prelink #-fullwarn 

INCLUDE = -Iinclude -I../c++adt/include -I../Firmament/include

STL     = -I/usr/include/CC

LIBFLAGS = -L../c++adt/lib -Llib -L../Firmament/lib

LIB1   = libc++adt.a
LIB2   = libLGM.a
LIB3   = libsky.a

LIBADT = -lc++adt
LIBLGM = -lLGM
LIBSKY = -lsky
LIBMATH  = -lm 

LIBS     = $(LIBLGM) $(LIBSKY) $(LIBADT) $(LIBMATH)

PROGFILES = program-files.html
.SUFFIXES: .o .cc

lignum: $(OBJ) $(LIB1)  $(LIB2) $(LIB3)
	$(CCC)  -o $@ $(INCLUDE) $(OBJ) $(LIBFLAGS) $(LIBS) 
algorithms: $(ALGOBJ) $(LIB1)  $(LIB2) $(LIB3)
	$(CCC) -ptv  -o $@ $(INCLUDE) $(OPTIMIZE) $(ALGOBJ) $(LIBFLAGS) $(LIBS)

broadleaf: $(BLOBJ) $(LIB1)  $(LIB2) $(LIB3)
	$(CCC) -ptv  -o $@ $(INCLUDE) $(OPTIMIZE) $(BLOBJ) $(LIBFLAGS) $(LIBS)	
$(LIB1):
	(cd ../c++adt/lib; make "CCC=$(CCC)" "CCCFLAGS=$(CCCFLAGS)" \
         "OPTIMIZE=$(OPTIMIZE)" "AR=$(ARCOMMAND)"  "ARFLAGS = $(ARCOMMANDFLAGS)" $@)

$(LIB2):
	(cd lib; make "CCC=$(CCC)" "CCCFLAGS=$(CCCFLAGS)" "OPTIMIZE=$(OPTIMIZE)" "AR=$(ARCOMMAND)" \
         "ARFLAGS = $(ARCOMMANDFLAGS)" $@)

$(LIB3):
	(cd ../Firmament; make "CCC=$(CCC)" "CCCFLAGS=$(CCCFLAGS)" \
         "OPTIMIZE=$(OPTIMIZE)" $@)
.cc.o: 
	$(CCC) $(OPTIMIZE) $(SUPPRESS) $(CCCFLAGS) $(INCLUDE)  $< -o $@

html:
	enscript -E --color -Whtml --toc -p$(PROGFILES) ./include/*.h ./Axis/*.cc  \
                  ./BranchingPoint/*.cc ./Bud/*.cc ./Tree/*.cc ./TreeSegment/*.cc . \
                   ./TreeCompartment/*.cc ./*.cc 
clean:
	(cd lib; make clean)
	rm -rf $(OBJ) $(ALGOBJ) core lignum algorithms broadleaf ii_files
	rm -rf ./*/ii_files
distclean:
	(cd ../c++adt/lib; make distclean)
	(cd ../Firmament; make distclean)
	(cd lib; make distclean)
	rm -rf $(OBJ) $(ALGOBJ) $(BLOBJ) core lignum algorithms broadleaf ii_files 
depend: 
	makedepend $(INCLUDE) $(CCCINCLUDE) $(STL) $(MAIN) $(ALGSRC) $(BLSRC)  
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
main.o: /usr/include/CC/stl_algo.h /usr/include/CC/stl_heap.h include/Tree.h
main.o: /usr/include/CC/numeric /usr/include/CC/stl_function.h
main.o: /usr/include/CC/stl_numeric.h /usr/include/CC/stream.h
main.o: /usr/include/CC/iomanip.h /usr/include/CC/generic.h
main.o: /usr/include/CC/stdiostream.h /usr/include/CC/fstream.h
main.o: ../c++adt/include/CString.h /usr/include/ctype.h
main.o: /usr/include/locale_attr.h ../c++adt/include/ParametricCurve.h
main.o: /usr/include/CC/vector /usr/include/CC/stl_range_errors.h
main.o: /usr/include/CC/stl_vector.h /usr/include/CC/stl_bvector.h
main.o: /usr/include/float.h ../c++adt/include/Point.h /usr/include/math.h
main.o: ../c++adt/include/PointI.h ../c++adt/include/PositionVector.h
main.o: ../c++adt/include/mathsym.h ../c++adt/include/RMatrix.h
main.o: ../c++adt/include/TMatrix.h ../c++adt/include/TMatrixI.h
main.o: include/Algorithms.h /usr/include/CC/functional include/LGMdecl.h
main.o: include/LGMSymbols.h /usr/include/CC/map /usr/include/CC/stl_tree.h
main.o: /usr/include/CC/stl_map.h /usr/include/CC/stl_multimap.h
main.o: include/LGMUnits.h include/AlgorithmsI.h include/TreeFunctor.h
main.o: include/TreeCompartment.h include/TreeCompartmentI.h
main.o: include/TreeFunctorI.h include/TreeMetaFileParser.h
main.o: ../c++adt/include/Table.h ../c++adt/include/DList.h
main.o: ../c++adt/include/DListElement.h ../c++adt/include/boolean.h
main.o: ../c++adt/include/TableI.h ../c++adt/include/Lex.h
main.o: include/RootSystem.h include/Bud.h include/BudI.h
main.o: include/DefaultBud.h include/BranchingPoint.h
main.o: include/BranchingPointI.h include/TreeSegment.h
main.o: include/TreeSegmentI.h include/TreeSegmentMetabolismI.h
main.o: include/HwTreeSegment.h include/BroadLeaf.h
main.o: ../c++adt/include/Ellipsis.h ../Firmament/include/Firmament.h
main.o: include/HwTreeSegmentI.h include/CfTreeSegment.h include/Axis.h
main.o: include/AxisI.h ../c++adt/include/ConnectionMatrix.h include/TreeI.h
main.o: include/TreeMetabolismI.h include/MyTreeSegment.h include/MyBud.h
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
algorithms.o: include/Tree.h /usr/include/CC/numeric
algorithms.o: /usr/include/CC/stl_function.h /usr/include/CC/stl_numeric.h
algorithms.o: /usr/include/CC/stream.h /usr/include/CC/iomanip.h
algorithms.o: /usr/include/CC/generic.h /usr/include/CC/stdiostream.h
algorithms.o: /usr/include/CC/fstream.h ../c++adt/include/CString.h
algorithms.o: /usr/include/ctype.h /usr/include/locale_attr.h
algorithms.o: ../c++adt/include/ParametricCurve.h /usr/include/CC/vector
algorithms.o: /usr/include/CC/stl_range_errors.h /usr/include/CC/stl_vector.h
algorithms.o: /usr/include/CC/stl_bvector.h /usr/include/float.h
algorithms.o: ../c++adt/include/Point.h /usr/include/math.h
algorithms.o: ../c++adt/include/PointI.h ../c++adt/include/PositionVector.h
algorithms.o: ../c++adt/include/mathsym.h ../c++adt/include/RMatrix.h
algorithms.o: ../c++adt/include/TMatrix.h ../c++adt/include/TMatrixI.h
algorithms.o: include/Algorithms.h /usr/include/CC/functional
algorithms.o: include/LGMdecl.h include/LGMSymbols.h /usr/include/CC/map
algorithms.o: /usr/include/CC/stl_tree.h /usr/include/CC/stl_map.h
algorithms.o: /usr/include/CC/stl_multimap.h include/LGMUnits.h
algorithms.o: include/AlgorithmsI.h include/TreeFunctor.h
algorithms.o: include/TreeCompartment.h include/TreeCompartmentI.h
algorithms.o: include/TreeFunctorI.h include/TreeMetaFileParser.h
algorithms.o: ../c++adt/include/Table.h ../c++adt/include/DList.h
algorithms.o: ../c++adt/include/DListElement.h ../c++adt/include/boolean.h
algorithms.o: ../c++adt/include/TableI.h ../c++adt/include/Lex.h
algorithms.o: include/RootSystem.h include/Bud.h include/BudI.h
algorithms.o: include/DefaultBud.h include/BranchingPoint.h
algorithms.o: include/BranchingPointI.h include/TreeSegment.h
algorithms.o: include/TreeSegmentI.h include/TreeSegmentMetabolismI.h
algorithms.o: include/HwTreeSegment.h include/BroadLeaf.h
algorithms.o: ../c++adt/include/Ellipsis.h ../Firmament/include/Firmament.h
algorithms.o: include/HwTreeSegmentI.h include/CfTreeSegment.h include/Axis.h
algorithms.o: include/AxisI.h ../c++adt/include/ConnectionMatrix.h
algorithms.o: include/TreeI.h include/TreeMetabolismI.h
algorithms.o: include/MyTreeSegment.h include/MyBud.h
broadleaf.o: /usr/include/stdlib.h /usr/include/standards.h
broadleaf.o: /usr/include/sgidefs.h /usr/include/CC/iostream.h
broadleaf.o: /usr/include/memory.h /usr/include/stddef.h /usr/include/CC/list
broadleaf.o: /usr/include/CC/stl_algobase.h /usr/include/CC/stl_config.h
broadleaf.o: /usr/include/CC/stl_relops.h /usr/include/CC/stl_pair.h
broadleaf.o: /usr/include/CC/type_traits.h /usr/include/string.h
broadleaf.o: /usr/include/limits.h /usr/include/CC/new.h
broadleaf.o: /usr/include/CC/stl_iterator_base.h
broadleaf.o: /usr/include/CC/stl_iterator.h /usr/include/CC/stl_alloc.h
broadleaf.o: /usr/include/stdio.h /usr/include/assert.h
broadleaf.o: /usr/include/CC/stl_construct.h
broadleaf.o: /usr/include/CC/stl_uninitialized.h /usr/include/CC/stl_list.h
broadleaf.o: /usr/include/CC/algorithm /usr/include/CC/stl_tempbuf.h
broadleaf.o: /usr/include/CC/stl_algo.h /usr/include/CC/stl_heap.h
broadleaf.o: include/Tree.h /usr/include/CC/numeric
broadleaf.o: /usr/include/CC/stl_function.h /usr/include/CC/stl_numeric.h
broadleaf.o: /usr/include/CC/stream.h /usr/include/CC/iomanip.h
broadleaf.o: /usr/include/CC/generic.h /usr/include/CC/stdiostream.h
broadleaf.o: /usr/include/CC/fstream.h ../c++adt/include/CString.h
broadleaf.o: /usr/include/ctype.h /usr/include/locale_attr.h
broadleaf.o: ../c++adt/include/ParametricCurve.h /usr/include/CC/vector
broadleaf.o: /usr/include/CC/stl_range_errors.h /usr/include/CC/stl_vector.h
broadleaf.o: /usr/include/CC/stl_bvector.h /usr/include/float.h
broadleaf.o: ../c++adt/include/Point.h /usr/include/math.h
broadleaf.o: ../c++adt/include/PointI.h ../c++adt/include/PositionVector.h
broadleaf.o: ../c++adt/include/mathsym.h ../c++adt/include/RMatrix.h
broadleaf.o: ../c++adt/include/TMatrix.h ../c++adt/include/TMatrixI.h
broadleaf.o: include/Algorithms.h /usr/include/CC/functional
broadleaf.o: include/LGMdecl.h include/LGMSymbols.h /usr/include/CC/map
broadleaf.o: /usr/include/CC/stl_tree.h /usr/include/CC/stl_map.h
broadleaf.o: /usr/include/CC/stl_multimap.h include/LGMUnits.h
broadleaf.o: include/AlgorithmsI.h include/TreeFunctor.h
broadleaf.o: include/TreeCompartment.h include/TreeCompartmentI.h
broadleaf.o: include/TreeFunctorI.h include/TreeMetaFileParser.h
broadleaf.o: ../c++adt/include/Table.h ../c++adt/include/DList.h
broadleaf.o: ../c++adt/include/DListElement.h ../c++adt/include/boolean.h
broadleaf.o: ../c++adt/include/TableI.h ../c++adt/include/Lex.h
broadleaf.o: include/RootSystem.h include/Bud.h include/BudI.h
broadleaf.o: include/DefaultBud.h include/BranchingPoint.h
broadleaf.o: include/BranchingPointI.h include/TreeSegment.h
broadleaf.o: include/TreeSegmentI.h include/TreeSegmentMetabolismI.h
broadleaf.o: include/HwTreeSegment.h include/BroadLeaf.h
broadleaf.o: ../c++adt/include/Ellipsis.h ../Firmament/include/Firmament.h
broadleaf.o: include/HwTreeSegmentI.h include/CfTreeSegment.h include/Axis.h
broadleaf.o: include/AxisI.h ../c++adt/include/ConnectionMatrix.h
broadleaf.o: include/TreeI.h include/TreeMetabolismI.h
broadleaf.o: include/MyTreeSegment.h include/MyBud.h
