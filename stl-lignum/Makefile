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

CCCFLAGS = -c -ptv -ptused #-fullwarn 

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
	rm -rf $(OBJ) $(ALGOBJ) $(BLOBJ) core lignum algorithms broadleaf ii_files
	rm -rf ./*/ii_files
distclean: clean
	(cd ../c++adt/lib; make distclean)
	(cd ../Firmament; make distclean)
	(cd lib; make distclean)
depend: 
	makedepend $(INCLUDE) $(CCCINCLUDE) $(STL) $(MAIN) $(ALGSRC) $(BLSRC)  
# DO NOT DELETE


algorithms..o: ../c++adt/include/boolean.h
algorithms..o: ../c++adt/include/ConnectionMatrix.h
algorithms..o: ../c++adt/include/ConnectionMatrixI.h
algorithms..o: ../c++adt/include/DListElement.h ../c++adt/include/DList.h
algorithms..o: ../c++adt/include/Ellipsis.h ../c++adt/include/Lex.h
algorithms..o: ../c++adt/include/mathsym.h ../c++adt/include/ParametricCurve.h
algorithms..o: ../c++adt/include/Point.h ../c++adt/include/PointI.h
algorithms..o: ../c++adt/include/PositionVector.h ../c++adt/include/RMatrix.h
algorithms..o: ../c++adt/include/Rotation.h ../c++adt/include/Table.h
algorithms..o: ../c++adt/include/TableI.h ../c++adt/include/TMatrix.h
algorithms..o: ../c++adt/include/TMatrixI.h ../Firmament/include/Firmament.h
algorithms..o: include/Algorithms.h include/AlgorithmsI.h include/Axis.h
algorithms..o: include/AxisI.h include/BranchingPoint.h
algorithms..o: include/BranchingPointI.h include/BroadLeaf.h include/Bud.h
algorithms..o: include/BudI.h include/CfTreeSegment.h include/CfTreeSegmentI.h
algorithms..o: include/CfTreeSegmentMetabolismI.h include/DefaultBud.h
algorithms..o: include/HwTreeSegment.h include/HwTreeSegmentI.h
algorithms..o: include/HwTreeSegmentMetabolismI.h include/LGMdecl.h
algorithms..o: include/LGMSymbols.h include/LGMUnits.h include/MyBud.h
algorithms..o: include/MyTreeSegment.h include/RootSystem.h
algorithms..o: include/TreeBookkeepingI.h include/TreeCompartment.h
algorithms..o: include/TreeCompartmentI.h include/TreeFunctor.h
algorithms..o: include/TreeFunctorI.h include/Tree.h include/TreeI.h
algorithms..o: include/TreeMetabolismI.h include/TreeMetaFileParser.h
algorithms..o: include/TreeSegment.h include/TreeSegmentI.h
algorithms..o: /usr/include/alloca.h /usr/include/assert.h
algorithms..o: /usr/include/bits/huge_val.h /usr/include/bits/local_lim.h
algorithms..o: /usr/include/bits/mathcalls.h /usr/include/bits/mathdef.h
algorithms..o: /usr/include/bits/nan.h /usr/include/bits/posix1_lim.h
algorithms..o: /usr/include/bits/pthreadtypes.h /usr/include/bits/sched.h
algorithms..o: /usr/include/bits/sigset.h /usr/include/bits/types.h
algorithms..o: /usr/include/bits/waitstatus.h /usr/include/bits/xopen_lim.h
algorithms..o: /usr/include/ctype.h /usr/include/endian.h
algorithms..o: /usr/include/features.h /usr/include/g++-3/algobase.h
algorithms..o: /usr/include/g++-3/algorithm /usr/include/g++-3/cassert
algorithms..o: /usr/include/g++-3/cctype /usr/include/g++-3/cstddef
algorithms..o: /usr/include/g++-3/fstream.h /usr/include/g++-3/functional
algorithms..o: /usr/include/g++-3/function.h /usr/include/g++-3/iostream.h
algorithms..o: /usr/include/g++-3/iterator /usr/include/g++-3/iterator.h
algorithms..o: /usr/include/g++-3/list /usr/include/g++-3/map
algorithms..o: /usr/include/g++-3/numeric /usr/include/g++-3/std/bastring.cc
algorithms..o: /usr/include/g++-3/std/bastring.h
algorithms..o: /usr/include/g++-3/std/straits.h
algorithms..o: /usr/include/g++-3/stl_algobase.h /usr/include/g++-3/stl_algo.h
algorithms..o: /usr/include/g++-3/stl_alloc.h /usr/include/g++-3/stl_bvector.h
algorithms..o: /usr/include/g++-3/stl_construct.h
algorithms..o: /usr/include/g++-3/stl_function.h /usr/include/g++-3/stl_heap.h
algorithms..o: /usr/include/g++-3/stl_iterator.h /usr/include/g++-3/stl_list.h
algorithms..o: /usr/include/g++-3/stl_map.h /usr/include/g++-3/stl_multimap.h
algorithms..o: /usr/include/g++-3/stl_numeric.h /usr/include/g++-3/stl_pair.h
algorithms..o: /usr/include/g++-3/stl_raw_storage_iter.h
algorithms..o: /usr/include/g++-3/stl_relops.h
algorithms..o: /usr/include/g++-3/stl_tempbuf.h /usr/include/g++-3/stl_tree.h
algorithms..o: /usr/include/g++-3/stl_uninitialized.h
algorithms..o: /usr/include/g++-3/stl_vector.h /usr/include/g++-3/streambuf.h
algorithms..o: /usr/include/g++-3/stream.h /usr/include/g++-3/string
algorithms..o: /usr/include/g++-3/type_traits.h /usr/include/g++-3/vector
algorithms..o: /usr/include/g++-3/vector.h /usr/include/_G_config.h
algorithms..o: /usr/include/gconv.h /usr/include/libio.h /usr/include/limits.h
algorithms..o: /usr/include/math.h /usr/include/stdio.h /usr/include/stdlib.h
algorithms..o: /usr/include/string.h /usr/include/sys/select.h
algorithms..o: /usr/include/sys/types.h /usr/include/time.h
algorithms..o: /usr/include/wchar.h /usr/include/xlocale.h
algorithms..o: /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/exception
algorithms..o: /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/float.h
algorithms..o: /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/limits.h
algorithms..o: /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/new
algorithms..o: /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/new.h
algorithms..o: /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/stdarg.h
algorithms..o: /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/stddef.h
algorithms..o: /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/syslimits.h
algorithms..o: /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/typeinfo
broadleaf..o: ../c++adt/include/boolean.h ../c++adt/include/ConnectionMatrix.h
broadleaf..o: ../c++adt/include/ConnectionMatrixI.h
broadleaf..o: ../c++adt/include/DListElement.h ../c++adt/include/DList.h
broadleaf..o: ../c++adt/include/Ellipsis.h ../c++adt/include/Lex.h
broadleaf..o: ../c++adt/include/mathsym.h ../c++adt/include/ParametricCurve.h
broadleaf..o: ../c++adt/include/Point.h ../c++adt/include/PointI.h
broadleaf..o: ../c++adt/include/PositionVector.h ../c++adt/include/RMatrix.h
broadleaf..o: ../c++adt/include/Rotation.h ../c++adt/include/Table.h
broadleaf..o: ../c++adt/include/TableI.h ../c++adt/include/TMatrix.h
broadleaf..o: ../c++adt/include/TMatrixI.h ../Firmament/include/Firmament.h
broadleaf..o: include/Algorithms.h include/AlgorithmsI.h include/Axis.h
broadleaf..o: include/AxisI.h include/BranchingPoint.h
broadleaf..o: include/BranchingPointI.h include/BroadLeaf.h include/Bud.h
broadleaf..o: include/BudI.h include/CfTreeSegment.h include/CfTreeSegmentI.h
broadleaf..o: include/CfTreeSegmentMetabolismI.h include/DefaultBud.h
broadleaf..o: include/HwTreeSegment.h include/HwTreeSegmentI.h
broadleaf..o: include/HwTreeSegmentMetabolismI.h include/LGMdecl.h
broadleaf..o: include/LGMSymbols.h include/LGMUnits.h include/MyBud.h
broadleaf..o: include/MyTreeSegment.h include/RootSystem.h
broadleaf..o: include/TreeBookkeepingI.h include/TreeCompartment.h
broadleaf..o: include/TreeCompartmentI.h include/TreeFunctor.h
broadleaf..o: include/TreeFunctorI.h include/Tree.h include/TreeI.h
broadleaf..o: include/TreeMetabolismI.h include/TreeMetaFileParser.h
broadleaf..o: include/TreeSegment.h include/TreeSegmentI.h
broadleaf..o: /usr/include/alloca.h /usr/include/assert.h
broadleaf..o: /usr/include/bits/huge_val.h /usr/include/bits/local_lim.h
broadleaf..o: /usr/include/bits/mathcalls.h /usr/include/bits/mathdef.h
broadleaf..o: /usr/include/bits/nan.h /usr/include/bits/posix1_lim.h
broadleaf..o: /usr/include/bits/pthreadtypes.h /usr/include/bits/sched.h
broadleaf..o: /usr/include/bits/sigset.h /usr/include/bits/types.h
broadleaf..o: /usr/include/bits/waitstatus.h /usr/include/bits/xopen_lim.h
broadleaf..o: /usr/include/ctype.h /usr/include/endian.h
broadleaf..o: /usr/include/features.h /usr/include/g++-3/algobase.h
broadleaf..o: /usr/include/g++-3/algorithm /usr/include/g++-3/cassert
broadleaf..o: /usr/include/g++-3/cctype /usr/include/g++-3/cstddef
broadleaf..o: /usr/include/g++-3/fstream.h /usr/include/g++-3/functional
broadleaf..o: /usr/include/g++-3/function.h /usr/include/g++-3/iostream.h
broadleaf..o: /usr/include/g++-3/iterator /usr/include/g++-3/iterator.h
broadleaf..o: /usr/include/g++-3/list /usr/include/g++-3/map
broadleaf..o: /usr/include/g++-3/numeric /usr/include/g++-3/std/bastring.cc
broadleaf..o: /usr/include/g++-3/std/bastring.h
broadleaf..o: /usr/include/g++-3/std/straits.h
broadleaf..o: /usr/include/g++-3/stl_algobase.h /usr/include/g++-3/stl_algo.h
broadleaf..o: /usr/include/g++-3/stl_alloc.h /usr/include/g++-3/stl_bvector.h
broadleaf..o: /usr/include/g++-3/stl_construct.h
broadleaf..o: /usr/include/g++-3/stl_function.h /usr/include/g++-3/stl_heap.h
broadleaf..o: /usr/include/g++-3/stl_iterator.h /usr/include/g++-3/stl_list.h
broadleaf..o: /usr/include/g++-3/stl_map.h /usr/include/g++-3/stl_multimap.h
broadleaf..o: /usr/include/g++-3/stl_numeric.h /usr/include/g++-3/stl_pair.h
broadleaf..o: /usr/include/g++-3/stl_raw_storage_iter.h
broadleaf..o: /usr/include/g++-3/stl_relops.h /usr/include/g++-3/stl_tempbuf.h
broadleaf..o: /usr/include/g++-3/stl_tree.h
broadleaf..o: /usr/include/g++-3/stl_uninitialized.h
broadleaf..o: /usr/include/g++-3/stl_vector.h /usr/include/g++-3/streambuf.h
broadleaf..o: /usr/include/g++-3/stream.h /usr/include/g++-3/string
broadleaf..o: /usr/include/g++-3/type_traits.h /usr/include/g++-3/vector
broadleaf..o: /usr/include/g++-3/vector.h /usr/include/_G_config.h
broadleaf..o: /usr/include/gconv.h /usr/include/libio.h /usr/include/limits.h
broadleaf..o: /usr/include/math.h /usr/include/stdio.h /usr/include/stdlib.h
broadleaf..o: /usr/include/string.h /usr/include/sys/select.h
broadleaf..o: /usr/include/sys/types.h /usr/include/time.h
broadleaf..o: /usr/include/wchar.h /usr/include/xlocale.h
broadleaf..o: /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/exception
broadleaf..o: /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/float.h
broadleaf..o: /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/limits.h
broadleaf..o: /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/new
broadleaf..o: /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/new.h
broadleaf..o: /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/stdarg.h
broadleaf..o: /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/stddef.h
broadleaf..o: /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/syslimits.h
broadleaf..o: /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/typeinfo
main..o: ../c++adt/include/boolean.h ../c++adt/include/ConnectionMatrix.h
main..o: ../c++adt/include/ConnectionMatrixI.h
main..o: ../c++adt/include/DListElement.h ../c++adt/include/DList.h
main..o: ../c++adt/include/Ellipsis.h ../c++adt/include/Lex.h
main..o: ../c++adt/include/mathsym.h ../c++adt/include/ParametricCurve.h
main..o: ../c++adt/include/Point.h ../c++adt/include/PointI.h
main..o: ../c++adt/include/PositionVector.h ../c++adt/include/RMatrix.h
main..o: ../c++adt/include/Rotation.h ../c++adt/include/Table.h
main..o: ../c++adt/include/TableI.h ../c++adt/include/TMatrix.h
main..o: ../c++adt/include/TMatrixI.h ../Firmament/include/Firmament.h
main..o: include/Algorithms.h include/AlgorithmsI.h include/Axis.h
main..o: include/AxisI.h include/BranchingPoint.h include/BranchingPointI.h
main..o: include/BroadLeaf.h include/Bud.h include/BudI.h
main..o: include/CfTreeSegment.h include/CfTreeSegmentI.h
main..o: include/CfTreeSegmentMetabolismI.h include/DefaultBud.h
main..o: include/HwTreeSegment.h include/HwTreeSegmentI.h
main..o: include/HwTreeSegmentMetabolismI.h include/LGMdecl.h
main..o: include/LGMSymbols.h include/LGMUnits.h include/MyBud.h
main..o: include/MyTreeSegment.h include/RootSystem.h
main..o: include/TreeBookkeepingI.h include/TreeCompartment.h
main..o: include/TreeCompartmentI.h include/TreeFunctor.h
main..o: include/TreeFunctorI.h include/Tree.h include/TreeI.h
main..o: include/TreeMetabolismI.h include/TreeMetaFileParser.h
main..o: include/TreeSegment.h include/TreeSegmentI.h /usr/include/alloca.h
main..o: /usr/include/assert.h /usr/include/bits/huge_val.h
main..o: /usr/include/bits/local_lim.h /usr/include/bits/mathcalls.h
main..o: /usr/include/bits/mathdef.h /usr/include/bits/nan.h
main..o: /usr/include/bits/posix1_lim.h /usr/include/bits/pthreadtypes.h
main..o: /usr/include/bits/sched.h /usr/include/bits/sigset.h
main..o: /usr/include/bits/types.h /usr/include/bits/waitstatus.h
main..o: /usr/include/bits/xopen_lim.h /usr/include/ctype.h
main..o: /usr/include/endian.h /usr/include/features.h
main..o: /usr/include/g++-3/algobase.h /usr/include/g++-3/algorithm
main..o: /usr/include/g++-3/cassert /usr/include/g++-3/cctype
main..o: /usr/include/g++-3/cstddef /usr/include/g++-3/fstream.h
main..o: /usr/include/g++-3/functional /usr/include/g++-3/function.h
main..o: /usr/include/g++-3/iostream.h /usr/include/g++-3/iterator
main..o: /usr/include/g++-3/iterator.h /usr/include/g++-3/list
main..o: /usr/include/g++-3/map /usr/include/g++-3/numeric
main..o: /usr/include/g++-3/std/bastring.cc /usr/include/g++-3/std/bastring.h
main..o: /usr/include/g++-3/std/straits.h /usr/include/g++-3/stl_algobase.h
main..o: /usr/include/g++-3/stl_algo.h /usr/include/g++-3/stl_alloc.h
main..o: /usr/include/g++-3/stl_bvector.h /usr/include/g++-3/stl_construct.h
main..o: /usr/include/g++-3/stl_function.h /usr/include/g++-3/stl_heap.h
main..o: /usr/include/g++-3/stl_iterator.h /usr/include/g++-3/stl_list.h
main..o: /usr/include/g++-3/stl_map.h /usr/include/g++-3/stl_multimap.h
main..o: /usr/include/g++-3/stl_numeric.h /usr/include/g++-3/stl_pair.h
main..o: /usr/include/g++-3/stl_raw_storage_iter.h
main..o: /usr/include/g++-3/stl_relops.h /usr/include/g++-3/stl_tempbuf.h
main..o: /usr/include/g++-3/stl_tree.h /usr/include/g++-3/stl_uninitialized.h
main..o: /usr/include/g++-3/stl_vector.h /usr/include/g++-3/streambuf.h
main..o: /usr/include/g++-3/stream.h /usr/include/g++-3/string
main..o: /usr/include/g++-3/type_traits.h /usr/include/g++-3/vector
main..o: /usr/include/g++-3/vector.h /usr/include/_G_config.h
main..o: /usr/include/gconv.h /usr/include/libio.h /usr/include/limits.h
main..o: /usr/include/math.h /usr/include/stdio.h /usr/include/stdlib.h
main..o: /usr/include/string.h /usr/include/sys/select.h
main..o: /usr/include/sys/types.h /usr/include/time.h /usr/include/wchar.h
main..o: /usr/include/xlocale.h
main..o: /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/exception
main..o: /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/float.h
main..o: /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/limits.h
main..o: /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/new
main..o: /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/new.h
main..o: /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/stdarg.h
main..o: /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/stddef.h
main..o: /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/syslimits.h
main..o: /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/typeinfo
