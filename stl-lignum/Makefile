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
 
CCC = CC  -LANG:std

#OPTIMIZE = -Ofast=ip28 -IPA
OPTIMIZE   = -g 

ARCOMMAND =  $(CCC) -ar  
ARCOMMANDFLAGS = -o 

SUPPRESS = #-w 1155 -w 1183

CCCFLAGS = -c  #-prelink -ptused   -ptv  #  -fullwarn 

INCLUDE = -Iinclude -I../c++adt/include -I../Firmament/include

STL     = -I/usr/include/CC

LIBFLAGS = -L../c++adt/lib -Llib -L../Firmament/lib

LIB1   = libc++adt.a
LIB2   = libLGM.a
LIB3   = libsky.a

LIBADT = -lc++adt
LIBLGM = -lLGM
LIBSKY = -lsky
LIBMATH  = -lC -lm 

LIBS     = $(LIBLGM) $(LIBSKY) $(LIBADT) $(LIBMATH) 

PROGFILES = program-files.html
.SUFFIXES: .o .cc

algorithms: $(ALGOBJ) $(LIB1) $(LIB3)  $(LIB2) 
	$(CCC)  -o $@ $(INCLUDE) $(OPTIMIZE) $(ALGOBJ) $(LIBFLAGS) $(LIBS)

lignum: $(OBJ) $(LIB1)  $(LIB2) $(LIB3)
	$(CCC)  -o $@ $(INCLUDE) $(OBJ) $(LIBFLAGS) $(LIBS) 

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
	rm -rf $(OBJ) $(ALGOBJ) $(BLOBJ) core lignum algorithms broadleaf ii_files
	rm -rf ./*/ii_files
distclean: clean
	(cd ../c++adt/lib; make distclean)
	(cd ../Firmament; make distclean)
	(cd lib; make distclean)
depend:
	(cd ../c++adt; make depend)
	(cd ../Firmament; make depend)
	(cd lib; make depend)
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
main.o: /usr/include/CC/iostream /usr/include/CC/iosfwd
main.o: /usr/include/CC/istream /usr/include/CC/ostream /usr/include/CC/ios
main.o: /usr/include/CC/utility /usr/include/CC/stl_locale.h
main.o: /usr/include/CC/typeinfo /usr/include/CC/exception
main.o: /usr/include/CC/stl_ctype.h /usr/include/CC/c_locale.h
main.o: /usr/include/CC/streambuf /usr/include/CC/stl_stdio_file.h
main.o: /usr/include/CC/stl_numeric_facets.h /usr/include/CC/limits
main.o: /usr/include/float.h ../c++adt/include/ParametricCurve.h
main.o: /usr/include/CC/vector /usr/include/CC/stl_range_errors.h
main.o: /usr/include/CC/stl_vector.h /usr/include/CC/stl_bvector.h
main.o: /usr/include/CC/fstream /usr/include/CC/stl_codecvt.h
main.o: ../c++adt/include/Point.h /usr/include/math.h
main.o: ../c++adt/include/PositionVector.h ../c++adt/include/mathsym.h
main.o: ../c++adt/include/RMatrix.h ../c++adt/include/Rotation.h
main.o: ../c++adt/include/TMatrix.h ../c++adt/include/TMatrixI.h
main.o: ../c++adt/include/PointI.h include/LGMdecl.h include/LGMSymbols.h
main.o: /usr/include/CC/map /usr/include/CC/stl_tree.h
main.o: /usr/include/CC/stl_map.h /usr/include/CC/stl_multimap.h
main.o: include/LGMUnits.h include/Algorithms.h include/AlgorithmsI.h
main.o: include/TreeFunctor.h include/TreeCompartment.h
main.o: include/TreeCompartmentI.h include/TreeFunctorI.h
main.o: include/TreeMetaFileParser.h ../c++adt/include/Table.h
main.o: ../c++adt/include/DList.h ../c++adt/include/DListElement.h
main.o: ../c++adt/include/boolean.h ../c++adt/include/TableI.h
main.o: ../c++adt/include/Lex.h include/RootSystem.h include/Bud.h
main.o: include/BudI.h include/DefaultBud.h include/BranchingPoint.h
main.o: include/BranchingPointI.h include/TreeSegment.h
main.o: include/TreeSegmentI.h include/HwTreeSegment.h include/BroadLeaf.h
main.o: ../c++adt/include/Ellipsis.h ../Firmament/include/FirmamentWithMask.h
main.o: ../Firmament/include/Firmament.h include/HwTreeSegmentI.h
main.o: include/HwTreeSegmentMetabolismI.h include/CfTreeSegment.h
main.o: include/CfTreeSegmentI.h include/CfTreeSegmentMetabolismI.h
main.o: include/Axis.h include/AxisI.h ../c++adt/include/ConnectionMatrix.h
main.o: ../c++adt/include/ConnectionMatrixI.h include/TreeRadiation.h
main.o: include/TreeI.h include/TreeMetabolismI.h include/TreeMetabolism.h
main.o: include/TreeRadiationI.h include/MyTreeSegment.h include/MyBud.h
algorithms.o: /usr/include/stdlib.h /usr/include/standards.h
algorithms.o: /usr/include/sgidefs.h /usr/include/CC/iostream
algorithms.o: /usr/include/CC/iosfwd /usr/include/CC/stl_config.h
algorithms.o: /usr/include/wchar.h /usr/include/locale_attr.h
algorithms.o: /usr/include/stdio.h /usr/include/ctype.h /usr/include/time.h
algorithms.o: /usr/include/stddef.h /usr/include/CC/istream
algorithms.o: /usr/include/CC/ostream /usr/include/CC/ios
algorithms.o: /usr/include/CC/stl_string_fwd.h /usr/include/CC/stl_alloc.h
algorithms.o: /usr/include/string.h /usr/include/assert.h
algorithms.o: /usr/include/CC/stl_threads.h /usr/include/mutex.h
algorithms.o: /usr/include/CC/stl_exception.h /usr/include/CC/utility
algorithms.o: /usr/include/CC/stl_relops.h /usr/include/CC/stl_pair.h
algorithms.o: /usr/include/CC/stl_locale.h /usr/include/CC/typeinfo
algorithms.o: /usr/include/CC/exception /usr/include/CC/string
algorithms.o: /usr/include/CC/functional /usr/include/CC/stl_function.h
algorithms.o: /usr/include/CC/stdexcept /usr/include/CC/stl_iterator_base.h
algorithms.o: /usr/include/CC/memory /usr/include/CC/stl_algobase.h
algorithms.o: /usr/include/CC/type_traits.h /usr/include/limits.h
algorithms.o: /usr/include/CC/new.h /usr/include/CC/iostream.h
algorithms.o: /usr/include/memory.h /usr/include/CC/stl_iterator.h
algorithms.o: /usr/include/CC/stl_construct.h /usr/include/CC/stl_tempbuf.h
algorithms.o: /usr/include/CC/stl_uninitialized.h
algorithms.o: /usr/include/CC/stl_raw_storage_iter.h
algorithms.o: /usr/include/CC/algorithm /usr/include/CC/stl_algo.h
algorithms.o: /usr/include/CC/stl_heap.h /usr/include/CC/char_traits.h
algorithms.o: /usr/include/CC/stl_hash_fun.h /usr/include/CC/stl_ctype.h
algorithms.o: /usr/include/CC/c_locale.h /usr/include/CC/streambuf
algorithms.o: /usr/include/CC/stl_stdio_file.h
algorithms.o: /usr/include/CC/stl_numeric_facets.h /usr/include/CC/limits
algorithms.o: /usr/include/float.h /usr/include/CC/list
algorithms.o: /usr/include/CC/stl_list.h include/MyTreeSegment.h
algorithms.o: include/HwTreeSegment.h include/TreeSegment.h
algorithms.o: ../c++adt/include/mathsym.h /usr/include/math.h
algorithms.o: ../c++adt/include/Point.h ../c++adt/include/PositionVector.h
algorithms.o: /usr/include/CC/vector /usr/include/CC/stl_range_errors.h
algorithms.o: /usr/include/CC/stl_vector.h /usr/include/CC/stl_bvector.h
algorithms.o: ../c++adt/include/RMatrix.h ../c++adt/include/Rotation.h
algorithms.o: ../c++adt/include/TMatrix.h ../c++adt/include/TMatrixI.h
algorithms.o: ../c++adt/include/PointI.h include/LGMdecl.h
algorithms.o: include/LGMSymbols.h /usr/include/CC/map
algorithms.o: /usr/include/CC/stl_tree.h /usr/include/CC/stl_map.h
algorithms.o: /usr/include/CC/stl_multimap.h include/LGMUnits.h
algorithms.o: include/TreeCompartment.h include/TreeCompartmentI.h
algorithms.o: include/TreeSegmentI.h include/BroadLeaf.h
algorithms.o: ../c++adt/include/Ellipsis.h
algorithms.o: ../Firmament/include/FirmamentWithMask.h
algorithms.o: ../Firmament/include/Firmament.h /usr/include/CC/fstream
algorithms.o: /usr/include/CC/stl_codecvt.h include/HwTreeSegmentI.h
algorithms.o: include/HwTreeSegmentMetabolismI.h include/CfTreeSegment.h
algorithms.o: include/CfTreeSegmentI.h include/CfTreeSegmentMetabolismI.h
algorithms.o: include/MyBud.h include/Bud.h include/BudI.h include/Tree.h
algorithms.o: /usr/include/CC/numeric /usr/include/CC/stl_numeric.h
algorithms.o: ../c++adt/include/ParametricCurve.h include/Algorithms.h
algorithms.o: include/AlgorithmsI.h include/TreeFunctor.h
algorithms.o: include/TreeFunctorI.h include/TreeMetaFileParser.h
algorithms.o: ../c++adt/include/Table.h ../c++adt/include/DList.h
algorithms.o: ../c++adt/include/DListElement.h ../c++adt/include/boolean.h
algorithms.o: ../c++adt/include/TableI.h ../c++adt/include/Lex.h
algorithms.o: include/RootSystem.h include/DefaultBud.h
algorithms.o: include/BranchingPoint.h include/BranchingPointI.h
algorithms.o: include/Axis.h include/AxisI.h
algorithms.o: ../c++adt/include/ConnectionMatrix.h
algorithms.o: ../c++adt/include/ConnectionMatrixI.h include/TreeRadiation.h
algorithms.o: include/TreeI.h include/TreeMetabolismI.h
algorithms.o: include/TreeMetabolism.h include/TreeRadiationI.h
algorithms.o: include/Shading.h include/ShadingI.h
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
broadleaf.o: /usr/include/CC/iostream /usr/include/CC/iosfwd
broadleaf.o: /usr/include/CC/istream /usr/include/CC/ostream
broadleaf.o: /usr/include/CC/ios /usr/include/CC/utility
broadleaf.o: /usr/include/CC/stl_locale.h /usr/include/CC/typeinfo
broadleaf.o: /usr/include/CC/exception /usr/include/CC/stl_ctype.h
broadleaf.o: /usr/include/CC/c_locale.h /usr/include/CC/streambuf
broadleaf.o: /usr/include/CC/stl_stdio_file.h
broadleaf.o: /usr/include/CC/stl_numeric_facets.h /usr/include/CC/limits
broadleaf.o: /usr/include/float.h ../c++adt/include/ParametricCurve.h
broadleaf.o: /usr/include/CC/vector /usr/include/CC/stl_range_errors.h
broadleaf.o: /usr/include/CC/stl_vector.h /usr/include/CC/stl_bvector.h
broadleaf.o: /usr/include/CC/fstream /usr/include/CC/stl_codecvt.h
broadleaf.o: ../c++adt/include/Point.h /usr/include/math.h
broadleaf.o: ../c++adt/include/PositionVector.h ../c++adt/include/mathsym.h
broadleaf.o: ../c++adt/include/RMatrix.h ../c++adt/include/Rotation.h
broadleaf.o: ../c++adt/include/TMatrix.h ../c++adt/include/TMatrixI.h
broadleaf.o: ../c++adt/include/PointI.h include/LGMdecl.h
broadleaf.o: include/LGMSymbols.h /usr/include/CC/map
broadleaf.o: /usr/include/CC/stl_tree.h /usr/include/CC/stl_map.h
broadleaf.o: /usr/include/CC/stl_multimap.h include/LGMUnits.h
broadleaf.o: include/Algorithms.h include/AlgorithmsI.h include/TreeFunctor.h
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
broadleaf.o: ../Firmament/include/FirmamentWithMask.h
broadleaf.o: ../Firmament/include/Firmament.h include/HwTreeSegmentI.h
broadleaf.o: include/HwTreeSegmentMetabolismI.h include/CfTreeSegment.h
broadleaf.o: include/CfTreeSegmentI.h include/CfTreeSegmentMetabolismI.h
broadleaf.o: include/Axis.h include/AxisI.h
broadleaf.o: ../c++adt/include/ConnectionMatrix.h
broadleaf.o: ../c++adt/include/ConnectionMatrixI.h include/TreeRadiation.h
broadleaf.o: include/TreeI.h include/TreeMetabolismI.h
broadleaf.o: include/TreeMetabolism.h include/TreeRadiationI.h
broadleaf.o: include/MyTreeSegment.h include/MyBud.h
