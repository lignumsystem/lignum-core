#To compile "algorithms" on SGI type 
#    make algorithms
#To compile with g++ in Linux type (or copy paste)
#    make "CCC=g++" "CCCFLAGS=-c" "OPTIMIZE=-O" "ARCOMMAND=ar"  "ARCOMMANDFLAGS=rv" algorithms 

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
	$(CCC)  -o $@ $(INCLUDE) $(OPTIMIZE) $(ALGOBJ) $(LIBFLAGS) $(LIBS)
lignux: 
	make "CCC=g++" "CCCFLAGS=-c" "OPTIMIZE=-O" "ARCOMMAND=ar"  "ARCOMMANDFLAGS=rv" algorithms

broadleaf: $(BLOBJ) $(LIB1)  $(LIB2) $(LIB3)
	$(CCC)   -o $@ $(INCLUDE) $(OPTIMIZE) $(BLOBJ) $(LIBFLAGS) $(LIBS)	
$(LIB1):
	(cd ../c++adt/lib; make "CCC=$(CCC)" "CCCFLAGS=$(CCCFLAGS)" \
         "OPTIMIZE=$(OPTIMIZE)" "AR=$(ARCOMMAND)"  "ARFLAGS = $(ARCOMMANDFLAGS)" $@)

$(LIB2):
	(cd lib; make "CCC=$(CCC)" "CCCFLAGS=$(CCCFLAGS)" "OPTIMIZE=$(OPTIMIZE)" "AR=$(ARCOMMAND)" \
         "ARFLAGS = $(ARCOMMANDFLAGS)" $@)

$(LIB3):
	(cd ../Firmament; make "CCC=$(CCC)" "CCCFLAGS=$(CCCFLAGS)" \
         "OPTIMIZE=$(OPTIMIZE)"  "AR=$(ARCOMMAND)"  "ARFLAGS = $(ARCOMMANDFLAGS)" $@)
.cc.o: 
	$(CCC) $(OPTIMIZE) $(SUPPRESS) $(CCCFLAGS) $(INCLUDE)  $< -o $@

html:
	enscript -E --color -Whtml --toc -p$(PROGFILES) ./include/*.h ./*/*.cc
changelog:
	rm -rf ChangeLog
	rcs2log . > ChangeLog
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
main.o: /usr/include/assert.h /usr/include/CC/stl_threads.h
main.o: /usr/include/mutex.h /usr/include/time.h
main.o: /usr/include/CC/stl_construct.h /usr/include/CC/stl_uninitialized.h
main.o: /usr/include/CC/stl_list.h /usr/include/CC/algorithm
main.o: /usr/include/CC/stl_tempbuf.h /usr/include/CC/stl_algo.h
main.o: /usr/include/CC/stl_heap.h /usr/include/CC/string
main.o: /usr/include/CC/stl_string_fwd.h /usr/include/ctype.h
main.o: /usr/include/locale_attr.h /usr/include/CC/functional
main.o: /usr/include/CC/stl_function.h /usr/include/CC/stdexcept
main.o: /usr/include/CC/stl_exception.h /usr/include/CC/memory
main.o: /usr/include/CC/stl_raw_storage_iter.h /usr/include/CC/char_traits.h
main.o: /usr/include/wchar.h /usr/include/CC/stl_hash_fun.h include/Tree.h
main.o: /usr/include/CC/numeric /usr/include/CC/stl_numeric.h
main.o: /usr/include/CC/stream.h /usr/include/CC/iomanip.h
main.o: /usr/include/CC/generic.h /usr/include/CC/stdiostream.h
main.o: /usr/include/CC/fstream.h ../c++adt/include/ParametricCurve.h
main.o: /usr/include/CC/vector /usr/include/CC/stl_range_errors.h
main.o: /usr/include/CC/stl_vector.h /usr/include/CC/stl_bvector.h
main.o: /usr/include/float.h ../c++adt/include/Point.h /usr/include/math.h
main.o: ../c++adt/include/mathsym.h ../c++adt/include/PointI.h
main.o: ../c++adt/include/PositionVector.h ../c++adt/include/RMatrix.h
main.o: ../c++adt/include/TMatrix.h ../c++adt/include/TMatrixI.h
main.o: include/Algorithms.h include/LGMdecl.h include/LGMSymbols.h
main.o: /usr/include/CC/map /usr/include/CC/stl_tree.h
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
main.o: include/TreeSegmentI.h include/HwTreeSegment.h include/BroadLeaf.h
main.o: ../c++adt/include/Ellipsis.h ../Firmament/include/Firmament.h
main.o: /usr/include/CC/vector.h /usr/include/CC/algobase.h
main.o: /usr/include/CC/pair.h /usr/include/CC/iterator.h
main.o: /usr/include/CC/function.h /usr/include/CC/alloc.h
main.o: include/HwTreeSegmentI.h include/HwTreeSegmentMetabolismI.h
main.o: include/CfTreeSegment.h include/CfTreeSegmentI.h
main.o: include/CfTreeSegmentMetabolismI.h include/Axis.h include/AxisI.h
main.o: ../c++adt/include/ConnectionMatrix.h
main.o: ../c++adt/include/ConnectionMatrixI.h include/TreeI.h
main.o: include/TreeMetabolismI.h include/TreeBookkeepingI.h
main.o: include/MyTreeSegment.h include/MyBud.h
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
algorithms.o: /usr/include/CC/stl_threads.h /usr/include/mutex.h
algorithms.o: /usr/include/time.h /usr/include/CC/stl_construct.h
algorithms.o: /usr/include/CC/stl_uninitialized.h /usr/include/CC/stl_list.h
algorithms.o: /usr/include/CC/algorithm /usr/include/CC/stl_tempbuf.h
algorithms.o: /usr/include/CC/stl_algo.h /usr/include/CC/stl_heap.h
algorithms.o: include/Tree.h /usr/include/CC/numeric
algorithms.o: /usr/include/CC/stl_function.h /usr/include/CC/stl_numeric.h
algorithms.o: /usr/include/CC/stream.h /usr/include/CC/iomanip.h
algorithms.o: /usr/include/CC/generic.h /usr/include/CC/stdiostream.h
algorithms.o: /usr/include/CC/fstream.h /usr/include/CC/string
algorithms.o: /usr/include/CC/stl_string_fwd.h /usr/include/ctype.h
algorithms.o: /usr/include/locale_attr.h /usr/include/CC/functional
algorithms.o: /usr/include/CC/stdexcept /usr/include/CC/stl_exception.h
algorithms.o: /usr/include/CC/memory /usr/include/CC/stl_raw_storage_iter.h
algorithms.o: /usr/include/CC/char_traits.h /usr/include/wchar.h
algorithms.o: /usr/include/CC/stl_hash_fun.h
algorithms.o: ../c++adt/include/ParametricCurve.h /usr/include/CC/vector
algorithms.o: /usr/include/CC/stl_range_errors.h /usr/include/CC/stl_vector.h
algorithms.o: /usr/include/CC/stl_bvector.h /usr/include/float.h
algorithms.o: ../c++adt/include/Point.h /usr/include/math.h
algorithms.o: ../c++adt/include/mathsym.h ../c++adt/include/PointI.h
algorithms.o: ../c++adt/include/PositionVector.h ../c++adt/include/RMatrix.h
algorithms.o: ../c++adt/include/TMatrix.h ../c++adt/include/TMatrixI.h
algorithms.o: include/Algorithms.h include/LGMdecl.h include/LGMSymbols.h
algorithms.o: /usr/include/CC/map /usr/include/CC/stl_tree.h
algorithms.o: /usr/include/CC/stl_map.h /usr/include/CC/stl_multimap.h
algorithms.o: include/LGMUnits.h include/AlgorithmsI.h include/TreeFunctor.h
algorithms.o: include/TreeCompartment.h include/TreeCompartmentI.h
algorithms.o: include/TreeFunctorI.h include/TreeMetaFileParser.h
algorithms.o: ../c++adt/include/Table.h ../c++adt/include/DList.h
algorithms.o: ../c++adt/include/DListElement.h ../c++adt/include/boolean.h
algorithms.o: ../c++adt/include/TableI.h ../c++adt/include/Lex.h
algorithms.o: include/RootSystem.h include/Bud.h include/BudI.h
algorithms.o: include/DefaultBud.h include/BranchingPoint.h
algorithms.o: include/BranchingPointI.h include/TreeSegment.h
algorithms.o: include/TreeSegmentI.h include/HwTreeSegment.h
algorithms.o: include/BroadLeaf.h ../c++adt/include/Ellipsis.h
algorithms.o: ../Firmament/include/Firmament.h /usr/include/CC/vector.h
algorithms.o: /usr/include/CC/algobase.h /usr/include/CC/pair.h
algorithms.o: /usr/include/CC/iterator.h /usr/include/CC/function.h
algorithms.o: /usr/include/CC/alloc.h include/HwTreeSegmentI.h
algorithms.o: include/HwTreeSegmentMetabolismI.h include/CfTreeSegment.h
algorithms.o: include/CfTreeSegmentI.h include/CfTreeSegmentMetabolismI.h
algorithms.o: include/Axis.h include/AxisI.h
algorithms.o: ../c++adt/include/ConnectionMatrix.h
algorithms.o: ../c++adt/include/ConnectionMatrixI.h include/TreeI.h
algorithms.o: include/TreeMetabolismI.h include/TreeBookkeepingI.h
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
broadleaf.o: /usr/include/CC/stl_threads.h /usr/include/mutex.h
broadleaf.o: /usr/include/time.h /usr/include/CC/stl_construct.h
broadleaf.o: /usr/include/CC/stl_uninitialized.h /usr/include/CC/stl_list.h
broadleaf.o: /usr/include/CC/algorithm /usr/include/CC/stl_tempbuf.h
broadleaf.o: /usr/include/CC/stl_algo.h /usr/include/CC/stl_heap.h
broadleaf.o: /usr/include/CC/string /usr/include/CC/stl_string_fwd.h
broadleaf.o: /usr/include/ctype.h /usr/include/locale_attr.h
broadleaf.o: /usr/include/CC/functional /usr/include/CC/stl_function.h
broadleaf.o: /usr/include/CC/stdexcept /usr/include/CC/stl_exception.h
broadleaf.o: /usr/include/CC/memory /usr/include/CC/stl_raw_storage_iter.h
broadleaf.o: /usr/include/CC/char_traits.h /usr/include/wchar.h
broadleaf.o: /usr/include/CC/stl_hash_fun.h include/Tree.h
broadleaf.o: /usr/include/CC/numeric /usr/include/CC/stl_numeric.h
broadleaf.o: /usr/include/CC/stream.h /usr/include/CC/iomanip.h
broadleaf.o: /usr/include/CC/generic.h /usr/include/CC/stdiostream.h
broadleaf.o: /usr/include/CC/fstream.h ../c++adt/include/ParametricCurve.h
broadleaf.o: /usr/include/CC/vector /usr/include/CC/stl_range_errors.h
broadleaf.o: /usr/include/CC/stl_vector.h /usr/include/CC/stl_bvector.h
broadleaf.o: /usr/include/float.h ../c++adt/include/Point.h
broadleaf.o: /usr/include/math.h ../c++adt/include/mathsym.h
broadleaf.o: ../c++adt/include/PointI.h ../c++adt/include/PositionVector.h
broadleaf.o: ../c++adt/include/RMatrix.h ../c++adt/include/TMatrix.h
broadleaf.o: ../c++adt/include/TMatrixI.h include/Algorithms.h
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
broadleaf.o: include/TreeSegmentI.h include/HwTreeSegment.h
broadleaf.o: include/BroadLeaf.h ../c++adt/include/Ellipsis.h
broadleaf.o: ../Firmament/include/Firmament.h /usr/include/CC/vector.h
broadleaf.o: /usr/include/CC/algobase.h /usr/include/CC/pair.h
broadleaf.o: /usr/include/CC/iterator.h /usr/include/CC/function.h
broadleaf.o: /usr/include/CC/alloc.h include/HwTreeSegmentI.h
broadleaf.o: include/HwTreeSegmentMetabolismI.h include/CfTreeSegment.h
broadleaf.o: include/CfTreeSegmentI.h include/CfTreeSegmentMetabolismI.h
broadleaf.o: include/Axis.h include/AxisI.h
broadleaf.o: ../c++adt/include/ConnectionMatrix.h
broadleaf.o: ../c++adt/include/ConnectionMatrixI.h include/TreeI.h
broadleaf.o: include/TreeMetabolismI.h include/TreeBookkeepingI.h
broadleaf.o: include/MyTreeSegment.h include/MyBud.h
