SRC = ../Axis/AxisFriend.cc  \
      ../BranchingPoint/BranchingPointFriend.cc \
      ../Bud/BudFriend.cc \
      ../Bud/Bud.cc \
      ../TreeMetaFileParser/TreeMetaFileParser.cc \
      ../TreeSegment/BroadLeaf.cc \
      ../TreeSegment/TreeSegmentFriend.cc \
      ../TreeSegment/TreeSegment.cc \
      ../TreeCompartment/TreeCompartmentFriend.cc\
      ../Tree/TreeFriend.cc \
      ../Tree/Tree.cc \
      ../TreeSegment/BeamShading.cc \
      ../TreeSegment/BroadLeafMetabolism.cc \
      ../TreeSegment/CfTreeSegment.cc

OBJ = ../Axis/AxisFriend.o \
      ../BranchingPoint/BranchingPointFriend.o \
      ../Bud/BudFriend.o \
      ../Bud/Bud.o \
      ../TreeMetaFileParser/TreeMetaFileParser.o \
      ../TreeSegment/BroadLeaf.o \
      ../TreeSegment/TreeSegmentFriend.o \
      ../TreeSegment/TreeSegment.o \
      ../TreeCompartment/TreeCompartmentFriend.o \
      ../Tree/TreeFriend.o \
      ../Tree/Tree.o \
      ../TreeSegment/BeamShading.o \
      ../TreeSegment/BroadLeafMetabolism.o \
      ../TreeSegment/CfTreeSegment.o


INCLUDE = -I../include  -I../../c++adt/include -I../../Firmament/include
STL = -I/usr/include/CC

CCC = CC -64 -LANG:std

ETAGS = etags -d -T -C -o

OPTIMIZE = -g
CCCFLAGS =   -c   

.SUFFIXES: .o .cc
ARCOMMAND=$(CCC) -ar
ARCOMMANDFLAGS= -o
AR = $(ARCOMMAND)
ARFLAGS = $(ARCOMMANDFLAGS)
ARFILE = libLGM.a


$(ARFILE): $(OBJ)
	$(AR) $(ARFLAGS) $(ARFILE) $(OBJ)

.cc.o: 
	$(CCC)  $(OPTIMIZE) $(CCCFLAGS) $(INCLUDE) $(STL) $<  -o $@  

touch:
	touch $(SRC)

clean:
	rm -rf $(OBJ) core 

distclean: clean
	rm -rf $(OBJ) core $(ARFILE)
	rm -rf ../Axis/ii_files ../BranchingPoint/ii_files
	rm -rf ../Bud/ii_files ../Tree/ii_files 
	rm -rf ../TreeMetaFileParser/ii_files
	rm -rf ../TreeCompartment/ii_files ../TreeSegment/ii_files

etags:
	$(ETAGS)   TAGSFILE ../src/*.cc ../include/*.h
depend:
	makedepend $(INCLUDE) $(STL) $(SRC)
# DO NOT DELETE

../Axis/AxisFriend.o: ../../c++adt/include/stdafx.h ../include/Axis.h
../Axis/AxisFriend.o: /usr/include/CC/list /usr/include/CC/stl_algobase.h
../Axis/AxisFriend.o: /usr/include/CC/stl_config.h /usr/include/standards.h
../Axis/AxisFriend.o: /usr/include/CC/stl_relops.h /usr/include/CC/stl_pair.h
../Axis/AxisFriend.o: /usr/include/CC/type_traits.h /usr/include/string.h
../Axis/AxisFriend.o: /usr/include/limits.h /usr/include/sgidefs.h
../Axis/AxisFriend.o: /usr/include/stdlib.h /usr/include/stddef.h
../Axis/AxisFriend.o: /usr/include/CC/new.h /usr/include/CC/iostream.h
../Axis/AxisFriend.o: /usr/include/memory.h
../Axis/AxisFriend.o: /usr/include/CC/stl_iterator_base.h
../Axis/AxisFriend.o: /usr/include/CC/stl_iterator.h
../Axis/AxisFriend.o: /usr/include/CC/stl_alloc.h /usr/include/stdio.h
../Axis/AxisFriend.o: /usr/include/assert.h /usr/include/CC/stl_threads.h
../Axis/AxisFriend.o: /usr/include/mutex.h /usr/include/time.h
../Axis/AxisFriend.o: /usr/include/CC/stl_construct.h
../Axis/AxisFriend.o: /usr/include/CC/stl_uninitialized.h
../Axis/AxisFriend.o: /usr/include/CC/stl_list.h ../../c++adt/include/Point.h
../Axis/AxisFriend.o: /usr/include/math.h /usr/include/CC/iostream
../Axis/AxisFriend.o: /usr/include/CC/iosfwd /usr/include/wchar.h
../Axis/AxisFriend.o: /usr/include/locale_attr.h /usr/include/ctype.h
../Axis/AxisFriend.o: /usr/include/CC/functional
../Axis/AxisFriend.o: /usr/include/CC/stl_function.h
../Axis/AxisFriend.o: /usr/include/CC/char_traits.h /usr/include/CC/istream
../Axis/AxisFriend.o: /usr/include/CC/ostream /usr/include/CC/ios
../Axis/AxisFriend.o: /usr/include/CC/stl_string_fwd.h
../Axis/AxisFriend.o: /usr/include/CC/stl_exception.h /usr/include/CC/utility
../Axis/AxisFriend.o: /usr/include/CC/stl_locale.h /usr/include/CC/typeinfo
../Axis/AxisFriend.o: /usr/include/CC/exception /usr/include/CC/string
../Axis/AxisFriend.o: /usr/include/CC/stdexcept /usr/include/CC/memory
../Axis/AxisFriend.o: /usr/include/CC/stl_tempbuf.h
../Axis/AxisFriend.o: /usr/include/CC/stl_raw_storage_iter.h
../Axis/AxisFriend.o: /usr/include/CC/algorithm /usr/include/CC/stl_algo.h
../Axis/AxisFriend.o: /usr/include/CC/stl_heap.h
../Axis/AxisFriend.o: /usr/include/CC/stl_hash_fun.h
../Axis/AxisFriend.o: /usr/include/CC/stl_ctype.h /usr/include/CC/c_locale.h
../Axis/AxisFriend.o: /usr/include/CC/streambuf
../Axis/AxisFriend.o: /usr/include/CC/stl_stdio_file.h
../Axis/AxisFriend.o: /usr/include/CC/stl_numeric_facets.h
../Axis/AxisFriend.o: /usr/include/CC/limits /usr/include/float.h
../Axis/AxisFriend.o: ../../c++adt/include/PositionVector.h
../Axis/AxisFriend.o: ../../c++adt/include/mathsym.h /usr/include/CC/vector
../Axis/AxisFriend.o: /usr/include/CC/stl_range_errors.h
../Axis/AxisFriend.o: /usr/include/CC/stl_vector.h
../Axis/AxisFriend.o: /usr/include/CC/stl_bvector.h
../Axis/AxisFriend.o: ../../c++adt/include/RMatrix.h
../Axis/AxisFriend.o: ../../c++adt/include/Rotation.h
../Axis/AxisFriend.o: ../../c++adt/include/TMatrix.h
../Axis/AxisFriend.o: ../../c++adt/include/TMatrixI.h
../Axis/AxisFriend.o: ../../c++adt/include/PointI.h ../include/LGMdecl.h
../Axis/AxisFriend.o: ../include/LGMSymbols.h /usr/include/CC/map
../Axis/AxisFriend.o: /usr/include/CC/stl_tree.h /usr/include/CC/stl_map.h
../Axis/AxisFriend.o: /usr/include/CC/stl_multimap.h ../include/LGMUnits.h
../Axis/AxisFriend.o: ../include/AxisI.h
../BetulaWithFlow/BetulaWithFlow.o: ../include/BetulaWithFlow.h
../BetulaWithFlow/BetulaWithFlow.o: ../include/Tree.h
../BetulaWithFlow/BetulaWithFlow.o: /usr/include/CC/algorithm
../BetulaWithFlow/BetulaWithFlow.o: /usr/include/CC/stl_algobase.h
../BetulaWithFlow/BetulaWithFlow.o: /usr/include/CC/stl_config.h
../BetulaWithFlow/BetulaWithFlow.o: /usr/include/standards.h
../BetulaWithFlow/BetulaWithFlow.o: /usr/include/CC/stl_relops.h
../BetulaWithFlow/BetulaWithFlow.o: /usr/include/CC/stl_pair.h
../BetulaWithFlow/BetulaWithFlow.o: /usr/include/CC/type_traits.h
../BetulaWithFlow/BetulaWithFlow.o: /usr/include/string.h
../BetulaWithFlow/BetulaWithFlow.o: /usr/include/limits.h
../BetulaWithFlow/BetulaWithFlow.o: /usr/include/sgidefs.h
../BetulaWithFlow/BetulaWithFlow.o: /usr/include/stdlib.h
../BetulaWithFlow/BetulaWithFlow.o: /usr/include/stddef.h
../BetulaWithFlow/BetulaWithFlow.o: /usr/include/CC/new.h
../BetulaWithFlow/BetulaWithFlow.o: /usr/include/CC/iostream.h
../BetulaWithFlow/BetulaWithFlow.o: /usr/include/memory.h
../BetulaWithFlow/BetulaWithFlow.o: /usr/include/CC/stl_iterator_base.h
../BetulaWithFlow/BetulaWithFlow.o: /usr/include/CC/stl_iterator.h
../BetulaWithFlow/BetulaWithFlow.o: /usr/include/CC/stl_construct.h
../BetulaWithFlow/BetulaWithFlow.o: /usr/include/CC/stl_uninitialized.h
../BetulaWithFlow/BetulaWithFlow.o: /usr/include/CC/stl_tempbuf.h
../BetulaWithFlow/BetulaWithFlow.o: /usr/include/CC/stl_algo.h
../BetulaWithFlow/BetulaWithFlow.o: /usr/include/CC/stl_heap.h
../BetulaWithFlow/BetulaWithFlow.o: /usr/include/CC/numeric
../BetulaWithFlow/BetulaWithFlow.o: /usr/include/CC/stl_function.h
../BetulaWithFlow/BetulaWithFlow.o: /usr/include/CC/stl_numeric.h
../BetulaWithFlow/BetulaWithFlow.o: /usr/include/CC/list
../BetulaWithFlow/BetulaWithFlow.o: /usr/include/CC/stl_alloc.h
../BetulaWithFlow/BetulaWithFlow.o: /usr/include/stdio.h
../BetulaWithFlow/BetulaWithFlow.o: /usr/include/assert.h
../BetulaWithFlow/BetulaWithFlow.o: /usr/include/CC/stl_threads.h
../BetulaWithFlow/BetulaWithFlow.o: /usr/include/mutex.h /usr/include/time.h
../BetulaWithFlow/BetulaWithFlow.o: /usr/include/CC/stl_list.h
../BetulaWithFlow/BetulaWithFlow.o: /usr/include/CC/iostream
../BetulaWithFlow/BetulaWithFlow.o: /usr/include/CC/iosfwd
../BetulaWithFlow/BetulaWithFlow.o: /usr/include/wchar.h
../BetulaWithFlow/BetulaWithFlow.o: /usr/include/locale_attr.h
../BetulaWithFlow/BetulaWithFlow.o: /usr/include/ctype.h
../BetulaWithFlow/BetulaWithFlow.o: /usr/include/CC/functional
../BetulaWithFlow/BetulaWithFlow.o: /usr/include/CC/char_traits.h
../BetulaWithFlow/BetulaWithFlow.o: /usr/include/CC/istream
../BetulaWithFlow/BetulaWithFlow.o: /usr/include/CC/ostream
../BetulaWithFlow/BetulaWithFlow.o: /usr/include/CC/ios
../BetulaWithFlow/BetulaWithFlow.o: /usr/include/CC/stl_string_fwd.h
../BetulaWithFlow/BetulaWithFlow.o: /usr/include/CC/stl_exception.h
../BetulaWithFlow/BetulaWithFlow.o: /usr/include/CC/utility
../BetulaWithFlow/BetulaWithFlow.o: /usr/include/CC/stl_locale.h
../BetulaWithFlow/BetulaWithFlow.o: /usr/include/CC/typeinfo
../BetulaWithFlow/BetulaWithFlow.o: /usr/include/CC/exception
../BetulaWithFlow/BetulaWithFlow.o: /usr/include/CC/string
../BetulaWithFlow/BetulaWithFlow.o: /usr/include/CC/stdexcept
../BetulaWithFlow/BetulaWithFlow.o: /usr/include/CC/memory
../BetulaWithFlow/BetulaWithFlow.o: /usr/include/CC/stl_raw_storage_iter.h
../BetulaWithFlow/BetulaWithFlow.o: /usr/include/CC/stl_hash_fun.h
../BetulaWithFlow/BetulaWithFlow.o: /usr/include/CC/stl_ctype.h
../BetulaWithFlow/BetulaWithFlow.o: /usr/include/CC/c_locale.h
../BetulaWithFlow/BetulaWithFlow.o: /usr/include/CC/streambuf
../BetulaWithFlow/BetulaWithFlow.o: /usr/include/CC/stl_stdio_file.h
../BetulaWithFlow/BetulaWithFlow.o: /usr/include/CC/stl_numeric_facets.h
../BetulaWithFlow/BetulaWithFlow.o: /usr/include/CC/limits
../BetulaWithFlow/BetulaWithFlow.o: /usr/include/float.h
../BetulaWithFlow/BetulaWithFlow.o: ../../c++adt/include/ParametricCurve.h
../BetulaWithFlow/BetulaWithFlow.o: /usr/include/CC/vector
../BetulaWithFlow/BetulaWithFlow.o: /usr/include/CC/stl_range_errors.h
../BetulaWithFlow/BetulaWithFlow.o: /usr/include/CC/stl_vector.h
../BetulaWithFlow/BetulaWithFlow.o: /usr/include/CC/stl_bvector.h
../BetulaWithFlow/BetulaWithFlow.o: /usr/include/CC/fstream
../BetulaWithFlow/BetulaWithFlow.o: /usr/include/CC/stl_codecvt.h
../BetulaWithFlow/BetulaWithFlow.o: ../../c++adt/include/Point.h
../BetulaWithFlow/BetulaWithFlow.o: /usr/include/math.h
../BetulaWithFlow/BetulaWithFlow.o: ../../c++adt/include/PositionVector.h
../BetulaWithFlow/BetulaWithFlow.o: ../../c++adt/include/mathsym.h
../BetulaWithFlow/BetulaWithFlow.o: ../../c++adt/include/RMatrix.h
../BetulaWithFlow/BetulaWithFlow.o: ../../c++adt/include/Rotation.h
../BetulaWithFlow/BetulaWithFlow.o: ../../c++adt/include/TMatrix.h
../BetulaWithFlow/BetulaWithFlow.o: ../../c++adt/include/TMatrixI.h
../BetulaWithFlow/BetulaWithFlow.o: ../../c++adt/include/PointI.h
../BetulaWithFlow/BetulaWithFlow.o: ../include/LGMdecl.h
../BetulaWithFlow/BetulaWithFlow.o: ../include/LGMSymbols.h
../BetulaWithFlow/BetulaWithFlow.o: /usr/include/CC/map
../BetulaWithFlow/BetulaWithFlow.o: /usr/include/CC/stl_tree.h
../BetulaWithFlow/BetulaWithFlow.o: /usr/include/CC/stl_map.h
../BetulaWithFlow/BetulaWithFlow.o: /usr/include/CC/stl_multimap.h
../BetulaWithFlow/BetulaWithFlow.o: ../include/LGMUnits.h
../BetulaWithFlow/BetulaWithFlow.o: ../include/Algorithms.h
../BetulaWithFlow/BetulaWithFlow.o: ../include/AlgorithmsI.h
../BetulaWithFlow/BetulaWithFlow.o: ../include/TreeFunctor.h
../BetulaWithFlow/BetulaWithFlow.o: ../include/TreeCompartment.h
../BetulaWithFlow/BetulaWithFlow.o: ../include/TreeCompartmentI.h
../BetulaWithFlow/BetulaWithFlow.o: ../include/TreeFunctorI.h
../BetulaWithFlow/BetulaWithFlow.o: ../include/TreeMetaFileParser.h
../BetulaWithFlow/BetulaWithFlow.o: ../../c++adt/include/Table.h
../BetulaWithFlow/BetulaWithFlow.o: ../../c++adt/include/DList.h
../BetulaWithFlow/BetulaWithFlow.o: ../../c++adt/include/DListElement.h
../BetulaWithFlow/BetulaWithFlow.o: ../../c++adt/include/boolean.h
../BetulaWithFlow/BetulaWithFlow.o: ../../c++adt/include/TableI.h
../BetulaWithFlow/BetulaWithFlow.o: ../../c++adt/include/Lex.h
../BetulaWithFlow/BetulaWithFlow.o: ../include/RootSystem.h ../include/Bud.h
../BetulaWithFlow/BetulaWithFlow.o: ../include/BudI.h ../include/DefaultBud.h
../BetulaWithFlow/BetulaWithFlow.o: ../include/BranchingPoint.h
../BetulaWithFlow/BetulaWithFlow.o: ../include/BranchingPointI.h
../BetulaWithFlow/BetulaWithFlow.o: ../include/TreeSegment.h
../BetulaWithFlow/BetulaWithFlow.o: ../include/TreeSegmentI.h
../BetulaWithFlow/BetulaWithFlow.o: ../include/HwTreeSegment.h
../BetulaWithFlow/BetulaWithFlow.o: ../include/BroadLeaf.h
../BetulaWithFlow/BetulaWithFlow.o: ../../c++adt/include/Ellipsis.h
../BetulaWithFlow/BetulaWithFlow.o: ../../Firmament/include/FirmamentWithMask.h
../BetulaWithFlow/BetulaWithFlow.o: ../../Firmament/include/Firmament.h
../BetulaWithFlow/BetulaWithFlow.o: ../include/HwTreeSegmentI.h
../BetulaWithFlow/BetulaWithFlow.o: ../include/HwTreeSegmentMetabolismI.h
../BetulaWithFlow/BetulaWithFlow.o: ../include/CfTreeSegment.h
../BetulaWithFlow/BetulaWithFlow.o: ../include/CfTreeSegmentI.h
../BetulaWithFlow/BetulaWithFlow.o: ../include/CfTreeSegmentMetabolismI.h
../BetulaWithFlow/BetulaWithFlow.o: ../include/Axis.h ../include/AxisI.h
../BetulaWithFlow/BetulaWithFlow.o: ../../c++adt/include/ConnectionMatrix.h
../BetulaWithFlow/BetulaWithFlow.o: ../../c++adt/include/ConnectionMatrixI.h
../BetulaWithFlow/BetulaWithFlow.o: ../include/TreeRadiation.h
../BetulaWithFlow/BetulaWithFlow.o: ../include/TreeI.h
../BetulaWithFlow/BetulaWithFlow.o: ../include/TreeMetabolismI.h
../BetulaWithFlow/BetulaWithFlow.o: ../include/TreeMetabolism.h
../BetulaWithFlow/BetulaWithFlow.o: ../include/TreeRadiationI.h
../BetulaWithFlow/BetulaWithFlow.o: ../include/BetulaWithFlowI.h
../BranchingPoint/BranchingPointFriend.o: ../include/BranchingPoint.h
../BranchingPoint/BranchingPointFriend.o: /usr/include/CC/list
../BranchingPoint/BranchingPointFriend.o: /usr/include/CC/stl_algobase.h
../BranchingPoint/BranchingPointFriend.o: /usr/include/CC/stl_config.h
../BranchingPoint/BranchingPointFriend.o: /usr/include/standards.h
../BranchingPoint/BranchingPointFriend.o: /usr/include/CC/stl_relops.h
../BranchingPoint/BranchingPointFriend.o: /usr/include/CC/stl_pair.h
../BranchingPoint/BranchingPointFriend.o: /usr/include/CC/type_traits.h
../BranchingPoint/BranchingPointFriend.o: /usr/include/string.h
../BranchingPoint/BranchingPointFriend.o: /usr/include/limits.h
../BranchingPoint/BranchingPointFriend.o: /usr/include/sgidefs.h
../BranchingPoint/BranchingPointFriend.o: /usr/include/stdlib.h
../BranchingPoint/BranchingPointFriend.o: /usr/include/stddef.h
../BranchingPoint/BranchingPointFriend.o: /usr/include/CC/new.h
../BranchingPoint/BranchingPointFriend.o: /usr/include/CC/iostream.h
../BranchingPoint/BranchingPointFriend.o: /usr/include/memory.h
../BranchingPoint/BranchingPointFriend.o: /usr/include/CC/stl_iterator_base.h
../BranchingPoint/BranchingPointFriend.o: /usr/include/CC/stl_iterator.h
../BranchingPoint/BranchingPointFriend.o: /usr/include/CC/stl_alloc.h
../BranchingPoint/BranchingPointFriend.o: /usr/include/stdio.h
../BranchingPoint/BranchingPointFriend.o: /usr/include/assert.h
../BranchingPoint/BranchingPointFriend.o: /usr/include/CC/stl_threads.h
../BranchingPoint/BranchingPointFriend.o: /usr/include/mutex.h
../BranchingPoint/BranchingPointFriend.o: /usr/include/time.h
../BranchingPoint/BranchingPointFriend.o: /usr/include/CC/stl_construct.h
../BranchingPoint/BranchingPointFriend.o: /usr/include/CC/stl_uninitialized.h
../BranchingPoint/BranchingPointFriend.o: /usr/include/CC/stl_list.h
../BranchingPoint/BranchingPointFriend.o: /usr/include/CC/algorithm
../BranchingPoint/BranchingPointFriend.o: /usr/include/CC/stl_tempbuf.h
../BranchingPoint/BranchingPointFriend.o: /usr/include/CC/stl_algo.h
../BranchingPoint/BranchingPointFriend.o: /usr/include/CC/stl_heap.h
../BranchingPoint/BranchingPointFriend.o: /usr/include/CC/numeric
../BranchingPoint/BranchingPointFriend.o: /usr/include/CC/stl_function.h
../BranchingPoint/BranchingPointFriend.o: /usr/include/CC/stl_numeric.h
../BranchingPoint/BranchingPointFriend.o: ../../c++adt/include/Point.h
../BranchingPoint/BranchingPointFriend.o: /usr/include/math.h
../BranchingPoint/BranchingPointFriend.o: /usr/include/CC/iostream
../BranchingPoint/BranchingPointFriend.o: /usr/include/CC/iosfwd
../BranchingPoint/BranchingPointFriend.o: /usr/include/wchar.h
../BranchingPoint/BranchingPointFriend.o: /usr/include/locale_attr.h
../BranchingPoint/BranchingPointFriend.o: /usr/include/ctype.h
../BranchingPoint/BranchingPointFriend.o: /usr/include/CC/functional
../BranchingPoint/BranchingPointFriend.o: /usr/include/CC/char_traits.h
../BranchingPoint/BranchingPointFriend.o: /usr/include/CC/istream
../BranchingPoint/BranchingPointFriend.o: /usr/include/CC/ostream
../BranchingPoint/BranchingPointFriend.o: /usr/include/CC/ios
../BranchingPoint/BranchingPointFriend.o: /usr/include/CC/stl_string_fwd.h
../BranchingPoint/BranchingPointFriend.o: /usr/include/CC/stl_exception.h
../BranchingPoint/BranchingPointFriend.o: /usr/include/CC/utility
../BranchingPoint/BranchingPointFriend.o: /usr/include/CC/stl_locale.h
../BranchingPoint/BranchingPointFriend.o: /usr/include/CC/typeinfo
../BranchingPoint/BranchingPointFriend.o: /usr/include/CC/exception
../BranchingPoint/BranchingPointFriend.o: /usr/include/CC/string
../BranchingPoint/BranchingPointFriend.o: /usr/include/CC/stdexcept
../BranchingPoint/BranchingPointFriend.o: /usr/include/CC/memory
../BranchingPoint/BranchingPointFriend.o: /usr/include/CC/stl_raw_storage_iter.h
../BranchingPoint/BranchingPointFriend.o: /usr/include/CC/stl_hash_fun.h
../BranchingPoint/BranchingPointFriend.o: /usr/include/CC/stl_ctype.h
../BranchingPoint/BranchingPointFriend.o: /usr/include/CC/c_locale.h
../BranchingPoint/BranchingPointFriend.o: /usr/include/CC/streambuf
../BranchingPoint/BranchingPointFriend.o: /usr/include/CC/stl_stdio_file.h
../BranchingPoint/BranchingPointFriend.o: /usr/include/CC/stl_numeric_facets.h
../BranchingPoint/BranchingPointFriend.o: /usr/include/CC/limits
../BranchingPoint/BranchingPointFriend.o: /usr/include/float.h
../BranchingPoint/BranchingPointFriend.o: ../../c++adt/include/PositionVector.h
../BranchingPoint/BranchingPointFriend.o: ../../c++adt/include/mathsym.h
../BranchingPoint/BranchingPointFriend.o: /usr/include/CC/vector
../BranchingPoint/BranchingPointFriend.o: /usr/include/CC/stl_range_errors.h
../BranchingPoint/BranchingPointFriend.o: /usr/include/CC/stl_vector.h
../BranchingPoint/BranchingPointFriend.o: /usr/include/CC/stl_bvector.h
../BranchingPoint/BranchingPointFriend.o: ../../c++adt/include/RMatrix.h
../BranchingPoint/BranchingPointFriend.o: ../../c++adt/include/Rotation.h
../BranchingPoint/BranchingPointFriend.o: ../../c++adt/include/TMatrix.h
../BranchingPoint/BranchingPointFriend.o: ../../c++adt/include/TMatrixI.h
../BranchingPoint/BranchingPointFriend.o: ../../c++adt/include/PointI.h
../BranchingPoint/BranchingPointFriend.o: ../include/LGMdecl.h
../BranchingPoint/BranchingPointFriend.o: ../include/LGMSymbols.h
../BranchingPoint/BranchingPointFriend.o: /usr/include/CC/map
../BranchingPoint/BranchingPointFriend.o: /usr/include/CC/stl_tree.h
../BranchingPoint/BranchingPointFriend.o: /usr/include/CC/stl_map.h
../BranchingPoint/BranchingPointFriend.o: /usr/include/CC/stl_multimap.h
../BranchingPoint/BranchingPointFriend.o: ../include/LGMUnits.h
../BranchingPoint/BranchingPointFriend.o: ../include/BranchingPointI.h
../Bud/BudFriend.o: ../include/Bud.h ../../c++adt/include/Point.h
../Bud/BudFriend.o: /usr/include/math.h /usr/include/sgidefs.h
../Bud/BudFriend.o: /usr/include/standards.h /usr/include/CC/iostream
../Bud/BudFriend.o: /usr/include/CC/iosfwd /usr/include/CC/stl_config.h
../Bud/BudFriend.o: /usr/include/wchar.h /usr/include/locale_attr.h
../Bud/BudFriend.o: /usr/include/stdio.h /usr/include/ctype.h
../Bud/BudFriend.o: /usr/include/time.h /usr/include/stddef.h
../Bud/BudFriend.o: /usr/include/CC/functional /usr/include/CC/stl_function.h
../Bud/BudFriend.o: /usr/include/CC/char_traits.h /usr/include/string.h
../Bud/BudFriend.o: /usr/include/CC/istream /usr/include/CC/ostream
../Bud/BudFriend.o: /usr/include/CC/ios /usr/include/CC/stl_string_fwd.h
../Bud/BudFriend.o: /usr/include/CC/stl_alloc.h /usr/include/stdlib.h
../Bud/BudFriend.o: /usr/include/assert.h /usr/include/CC/stl_threads.h
../Bud/BudFriend.o: /usr/include/mutex.h /usr/include/CC/stl_exception.h
../Bud/BudFriend.o: /usr/include/CC/utility /usr/include/CC/stl_relops.h
../Bud/BudFriend.o: /usr/include/CC/stl_pair.h /usr/include/CC/stl_locale.h
../Bud/BudFriend.o: /usr/include/CC/typeinfo /usr/include/CC/exception
../Bud/BudFriend.o: /usr/include/CC/string /usr/include/CC/stdexcept
../Bud/BudFriend.o: /usr/include/CC/stl_iterator_base.h
../Bud/BudFriend.o: /usr/include/CC/memory /usr/include/CC/stl_algobase.h
../Bud/BudFriend.o: /usr/include/CC/type_traits.h /usr/include/limits.h
../Bud/BudFriend.o: /usr/include/CC/new.h /usr/include/CC/iostream.h
../Bud/BudFriend.o: /usr/include/memory.h /usr/include/CC/stl_iterator.h
../Bud/BudFriend.o: /usr/include/CC/stl_construct.h
../Bud/BudFriend.o: /usr/include/CC/stl_tempbuf.h
../Bud/BudFriend.o: /usr/include/CC/stl_uninitialized.h
../Bud/BudFriend.o: /usr/include/CC/stl_raw_storage_iter.h
../Bud/BudFriend.o: /usr/include/CC/algorithm /usr/include/CC/stl_algo.h
../Bud/BudFriend.o: /usr/include/CC/stl_heap.h /usr/include/CC/stl_hash_fun.h
../Bud/BudFriend.o: /usr/include/CC/stl_ctype.h /usr/include/CC/c_locale.h
../Bud/BudFriend.o: /usr/include/CC/streambuf
../Bud/BudFriend.o: /usr/include/CC/stl_stdio_file.h
../Bud/BudFriend.o: /usr/include/CC/stl_numeric_facets.h
../Bud/BudFriend.o: /usr/include/CC/limits /usr/include/float.h
../Bud/BudFriend.o: ../../c++adt/include/PositionVector.h
../Bud/BudFriend.o: ../../c++adt/include/mathsym.h /usr/include/CC/vector
../Bud/BudFriend.o: /usr/include/CC/stl_range_errors.h
../Bud/BudFriend.o: /usr/include/CC/stl_vector.h
../Bud/BudFriend.o: /usr/include/CC/stl_bvector.h
../Bud/BudFriend.o: ../../c++adt/include/RMatrix.h
../Bud/BudFriend.o: ../../c++adt/include/Rotation.h
../Bud/BudFriend.o: ../../c++adt/include/TMatrix.h
../Bud/BudFriend.o: ../../c++adt/include/TMatrixI.h
../Bud/BudFriend.o: ../../c++adt/include/PointI.h ../include/LGMdecl.h
../Bud/BudFriend.o: ../include/LGMSymbols.h /usr/include/CC/map
../Bud/BudFriend.o: /usr/include/CC/stl_tree.h /usr/include/CC/stl_map.h
../Bud/BudFriend.o: /usr/include/CC/stl_multimap.h ../include/LGMUnits.h
../Bud/BudFriend.o: ../include/TreeCompartment.h
../Bud/BudFriend.o: ../include/TreeCompartmentI.h ../include/BudI.h
../Bud/Bud.o: ../include/Bud.h ../../c++adt/include/Point.h
../Bud/Bud.o: /usr/include/math.h /usr/include/sgidefs.h
../Bud/Bud.o: /usr/include/standards.h /usr/include/CC/iostream
../Bud/Bud.o: /usr/include/CC/iosfwd /usr/include/CC/stl_config.h
../Bud/Bud.o: /usr/include/wchar.h /usr/include/locale_attr.h
../Bud/Bud.o: /usr/include/stdio.h /usr/include/ctype.h /usr/include/time.h
../Bud/Bud.o: /usr/include/stddef.h /usr/include/CC/functional
../Bud/Bud.o: /usr/include/CC/stl_function.h /usr/include/CC/char_traits.h
../Bud/Bud.o: /usr/include/string.h /usr/include/CC/istream
../Bud/Bud.o: /usr/include/CC/ostream /usr/include/CC/ios
../Bud/Bud.o: /usr/include/CC/stl_string_fwd.h /usr/include/CC/stl_alloc.h
../Bud/Bud.o: /usr/include/stdlib.h /usr/include/assert.h
../Bud/Bud.o: /usr/include/CC/stl_threads.h /usr/include/mutex.h
../Bud/Bud.o: /usr/include/CC/stl_exception.h /usr/include/CC/utility
../Bud/Bud.o: /usr/include/CC/stl_relops.h /usr/include/CC/stl_pair.h
../Bud/Bud.o: /usr/include/CC/stl_locale.h /usr/include/CC/typeinfo
../Bud/Bud.o: /usr/include/CC/exception /usr/include/CC/string
../Bud/Bud.o: /usr/include/CC/stdexcept /usr/include/CC/stl_iterator_base.h
../Bud/Bud.o: /usr/include/CC/memory /usr/include/CC/stl_algobase.h
../Bud/Bud.o: /usr/include/CC/type_traits.h /usr/include/limits.h
../Bud/Bud.o: /usr/include/CC/new.h /usr/include/CC/iostream.h
../Bud/Bud.o: /usr/include/memory.h /usr/include/CC/stl_iterator.h
../Bud/Bud.o: /usr/include/CC/stl_construct.h /usr/include/CC/stl_tempbuf.h
../Bud/Bud.o: /usr/include/CC/stl_uninitialized.h
../Bud/Bud.o: /usr/include/CC/stl_raw_storage_iter.h
../Bud/Bud.o: /usr/include/CC/algorithm /usr/include/CC/stl_algo.h
../Bud/Bud.o: /usr/include/CC/stl_heap.h /usr/include/CC/stl_hash_fun.h
../Bud/Bud.o: /usr/include/CC/stl_ctype.h /usr/include/CC/c_locale.h
../Bud/Bud.o: /usr/include/CC/streambuf /usr/include/CC/stl_stdio_file.h
../Bud/Bud.o: /usr/include/CC/stl_numeric_facets.h /usr/include/CC/limits
../Bud/Bud.o: /usr/include/float.h ../../c++adt/include/PositionVector.h
../Bud/Bud.o: ../../c++adt/include/mathsym.h /usr/include/CC/vector
../Bud/Bud.o: /usr/include/CC/stl_range_errors.h /usr/include/CC/stl_vector.h
../Bud/Bud.o: /usr/include/CC/stl_bvector.h ../../c++adt/include/RMatrix.h
../Bud/Bud.o: ../../c++adt/include/Rotation.h ../../c++adt/include/TMatrix.h
../Bud/Bud.o: ../../c++adt/include/TMatrixI.h ../../c++adt/include/PointI.h
../Bud/Bud.o: ../include/LGMdecl.h ../include/LGMSymbols.h
../Bud/Bud.o: /usr/include/CC/map /usr/include/CC/stl_tree.h
../Bud/Bud.o: /usr/include/CC/stl_map.h /usr/include/CC/stl_multimap.h
../Bud/Bud.o: ../include/LGMUnits.h ../include/TreeCompartment.h
../Bud/Bud.o: ../include/TreeCompartmentI.h ../include/BudI.h
../TreeMetaFileParser/TreeMetaFileParser.o: ../include/TreeMetaFileParser.h
../TreeMetaFileParser/TreeMetaFileParser.o: /usr/include/stdlib.h
../TreeMetaFileParser/TreeMetaFileParser.o: /usr/include/standards.h
../TreeMetaFileParser/TreeMetaFileParser.o: /usr/include/sgidefs.h
../TreeMetaFileParser/TreeMetaFileParser.o: ../../c++adt/include/Table.h
../TreeMetaFileParser/TreeMetaFileParser.o: ../../c++adt/include/DList.h
../TreeMetaFileParser/TreeMetaFileParser.o: ../../c++adt/include/DListElement.h
../TreeMetaFileParser/TreeMetaFileParser.o: ../../c++adt/include/boolean.h
../TreeMetaFileParser/TreeMetaFileParser.o: ../../c++adt/include/TableI.h
../TreeMetaFileParser/TreeMetaFileParser.o: ../../c++adt/include/Lex.h
../TreeMetaFileParser/TreeMetaFileParser.o: /usr/include/CC/fstream
../TreeMetaFileParser/TreeMetaFileParser.o: /usr/include/CC/istream
../TreeMetaFileParser/TreeMetaFileParser.o: /usr/include/CC/ostream
../TreeMetaFileParser/TreeMetaFileParser.o: /usr/include/CC/ios
../TreeMetaFileParser/TreeMetaFileParser.o: /usr/include/CC/stl_config.h
../TreeMetaFileParser/TreeMetaFileParser.o: /usr/include/CC/stl_string_fwd.h
../TreeMetaFileParser/TreeMetaFileParser.o: /usr/include/stddef.h
../TreeMetaFileParser/TreeMetaFileParser.o: /usr/include/CC/stl_alloc.h
../TreeMetaFileParser/TreeMetaFileParser.o: /usr/include/stdio.h
../TreeMetaFileParser/TreeMetaFileParser.o: /usr/include/string.h
../TreeMetaFileParser/TreeMetaFileParser.o: /usr/include/assert.h
../TreeMetaFileParser/TreeMetaFileParser.o: /usr/include/CC/stl_threads.h
../TreeMetaFileParser/TreeMetaFileParser.o: /usr/include/mutex.h
../TreeMetaFileParser/TreeMetaFileParser.o: /usr/include/time.h
../TreeMetaFileParser/TreeMetaFileParser.o: /usr/include/CC/stl_exception.h
../TreeMetaFileParser/TreeMetaFileParser.o: /usr/include/CC/utility
../TreeMetaFileParser/TreeMetaFileParser.o: /usr/include/CC/stl_relops.h
../TreeMetaFileParser/TreeMetaFileParser.o: /usr/include/CC/stl_pair.h
../TreeMetaFileParser/TreeMetaFileParser.o: /usr/include/CC/iosfwd
../TreeMetaFileParser/TreeMetaFileParser.o: /usr/include/wchar.h
../TreeMetaFileParser/TreeMetaFileParser.o: /usr/include/locale_attr.h
../TreeMetaFileParser/TreeMetaFileParser.o: /usr/include/ctype.h
../TreeMetaFileParser/TreeMetaFileParser.o: /usr/include/CC/functional
../TreeMetaFileParser/TreeMetaFileParser.o: /usr/include/CC/stl_function.h
../TreeMetaFileParser/TreeMetaFileParser.o: /usr/include/CC/char_traits.h
../TreeMetaFileParser/TreeMetaFileParser.o: /usr/include/CC/stl_locale.h
../TreeMetaFileParser/TreeMetaFileParser.o: /usr/include/CC/typeinfo
../TreeMetaFileParser/TreeMetaFileParser.o: /usr/include/CC/exception
../TreeMetaFileParser/TreeMetaFileParser.o: /usr/include/CC/string
../TreeMetaFileParser/TreeMetaFileParser.o: /usr/include/CC/stdexcept
../TreeMetaFileParser/TreeMetaFileParser.o: /usr/include/CC/stl_iterator_base.h
../TreeMetaFileParser/TreeMetaFileParser.o: /usr/include/CC/memory
../TreeMetaFileParser/TreeMetaFileParser.o: /usr/include/CC/stl_algobase.h
../TreeMetaFileParser/TreeMetaFileParser.o: /usr/include/CC/type_traits.h
../TreeMetaFileParser/TreeMetaFileParser.o: /usr/include/limits.h
../TreeMetaFileParser/TreeMetaFileParser.o: /usr/include/CC/new.h
../TreeMetaFileParser/TreeMetaFileParser.o: /usr/include/CC/iostream.h
../TreeMetaFileParser/TreeMetaFileParser.o: /usr/include/memory.h
../TreeMetaFileParser/TreeMetaFileParser.o: /usr/include/CC/stl_iterator.h
../TreeMetaFileParser/TreeMetaFileParser.o: /usr/include/CC/stl_construct.h
../TreeMetaFileParser/TreeMetaFileParser.o: /usr/include/CC/stl_tempbuf.h
../TreeMetaFileParser/TreeMetaFileParser.o: /usr/include/CC/stl_uninitialized.h
../TreeMetaFileParser/TreeMetaFileParser.o: /usr/include/CC/stl_raw_storage_iter.h
../TreeMetaFileParser/TreeMetaFileParser.o: /usr/include/CC/algorithm
../TreeMetaFileParser/TreeMetaFileParser.o: /usr/include/CC/stl_algo.h
../TreeMetaFileParser/TreeMetaFileParser.o: /usr/include/CC/stl_heap.h
../TreeMetaFileParser/TreeMetaFileParser.o: /usr/include/CC/stl_hash_fun.h
../TreeMetaFileParser/TreeMetaFileParser.o: /usr/include/CC/stl_ctype.h
../TreeMetaFileParser/TreeMetaFileParser.o: /usr/include/CC/c_locale.h
../TreeMetaFileParser/TreeMetaFileParser.o: /usr/include/CC/streambuf
../TreeMetaFileParser/TreeMetaFileParser.o: /usr/include/CC/stl_stdio_file.h
../TreeMetaFileParser/TreeMetaFileParser.o: /usr/include/CC/stl_numeric_facets.h
../TreeMetaFileParser/TreeMetaFileParser.o: /usr/include/CC/limits
../TreeMetaFileParser/TreeMetaFileParser.o: /usr/include/float.h
../TreeMetaFileParser/TreeMetaFileParser.o: /usr/include/CC/stl_codecvt.h
../TreeSegment/BroadLeaf.o: ../include/BroadLeaf.h
../TreeSegment/BroadLeaf.o: ../../c++adt/include/Point.h /usr/include/math.h
../TreeSegment/BroadLeaf.o: /usr/include/sgidefs.h /usr/include/standards.h
../TreeSegment/BroadLeaf.o: /usr/include/CC/iostream /usr/include/CC/iosfwd
../TreeSegment/BroadLeaf.o: /usr/include/CC/stl_config.h /usr/include/wchar.h
../TreeSegment/BroadLeaf.o: /usr/include/locale_attr.h /usr/include/stdio.h
../TreeSegment/BroadLeaf.o: /usr/include/ctype.h /usr/include/time.h
../TreeSegment/BroadLeaf.o: /usr/include/stddef.h /usr/include/CC/functional
../TreeSegment/BroadLeaf.o: /usr/include/CC/stl_function.h
../TreeSegment/BroadLeaf.o: /usr/include/CC/char_traits.h
../TreeSegment/BroadLeaf.o: /usr/include/string.h /usr/include/CC/istream
../TreeSegment/BroadLeaf.o: /usr/include/CC/ostream /usr/include/CC/ios
../TreeSegment/BroadLeaf.o: /usr/include/CC/stl_string_fwd.h
../TreeSegment/BroadLeaf.o: /usr/include/CC/stl_alloc.h /usr/include/stdlib.h
../TreeSegment/BroadLeaf.o: /usr/include/assert.h
../TreeSegment/BroadLeaf.o: /usr/include/CC/stl_threads.h
../TreeSegment/BroadLeaf.o: /usr/include/mutex.h
../TreeSegment/BroadLeaf.o: /usr/include/CC/stl_exception.h
../TreeSegment/BroadLeaf.o: /usr/include/CC/utility
../TreeSegment/BroadLeaf.o: /usr/include/CC/stl_relops.h
../TreeSegment/BroadLeaf.o: /usr/include/CC/stl_pair.h
../TreeSegment/BroadLeaf.o: /usr/include/CC/stl_locale.h
../TreeSegment/BroadLeaf.o: /usr/include/CC/typeinfo
../TreeSegment/BroadLeaf.o: /usr/include/CC/exception /usr/include/CC/string
../TreeSegment/BroadLeaf.o: /usr/include/CC/stdexcept
../TreeSegment/BroadLeaf.o: /usr/include/CC/stl_iterator_base.h
../TreeSegment/BroadLeaf.o: /usr/include/CC/memory
../TreeSegment/BroadLeaf.o: /usr/include/CC/stl_algobase.h
../TreeSegment/BroadLeaf.o: /usr/include/CC/type_traits.h
../TreeSegment/BroadLeaf.o: /usr/include/limits.h /usr/include/CC/new.h
../TreeSegment/BroadLeaf.o: /usr/include/CC/iostream.h /usr/include/memory.h
../TreeSegment/BroadLeaf.o: /usr/include/CC/stl_iterator.h
../TreeSegment/BroadLeaf.o: /usr/include/CC/stl_construct.h
../TreeSegment/BroadLeaf.o: /usr/include/CC/stl_tempbuf.h
../TreeSegment/BroadLeaf.o: /usr/include/CC/stl_uninitialized.h
../TreeSegment/BroadLeaf.o: /usr/include/CC/stl_raw_storage_iter.h
../TreeSegment/BroadLeaf.o: /usr/include/CC/algorithm
../TreeSegment/BroadLeaf.o: /usr/include/CC/stl_algo.h
../TreeSegment/BroadLeaf.o: /usr/include/CC/stl_heap.h
../TreeSegment/BroadLeaf.o: /usr/include/CC/stl_hash_fun.h
../TreeSegment/BroadLeaf.o: /usr/include/CC/stl_ctype.h
../TreeSegment/BroadLeaf.o: /usr/include/CC/c_locale.h
../TreeSegment/BroadLeaf.o: /usr/include/CC/streambuf
../TreeSegment/BroadLeaf.o: /usr/include/CC/stl_stdio_file.h
../TreeSegment/BroadLeaf.o: /usr/include/CC/stl_numeric_facets.h
../TreeSegment/BroadLeaf.o: /usr/include/CC/limits /usr/include/float.h
../TreeSegment/BroadLeaf.o: ../../c++adt/include/PositionVector.h
../TreeSegment/BroadLeaf.o: ../../c++adt/include/mathsym.h
../TreeSegment/BroadLeaf.o: /usr/include/CC/vector
../TreeSegment/BroadLeaf.o: /usr/include/CC/stl_range_errors.h
../TreeSegment/BroadLeaf.o: /usr/include/CC/stl_vector.h
../TreeSegment/BroadLeaf.o: /usr/include/CC/stl_bvector.h
../TreeSegment/BroadLeaf.o: ../../c++adt/include/RMatrix.h
../TreeSegment/BroadLeaf.o: ../../c++adt/include/Rotation.h
../TreeSegment/BroadLeaf.o: ../../c++adt/include/TMatrix.h
../TreeSegment/BroadLeaf.o: ../../c++adt/include/TMatrixI.h
../TreeSegment/BroadLeaf.o: ../../c++adt/include/PointI.h
../TreeSegment/BroadLeaf.o: ../../c++adt/include/Ellipsis.h
../TreeSegment/BroadLeaf.o: ../include/LGMdecl.h ../include/LGMSymbols.h
../TreeSegment/BroadLeaf.o: /usr/include/CC/map /usr/include/CC/stl_tree.h
../TreeSegment/BroadLeaf.o: /usr/include/CC/stl_map.h
../TreeSegment/BroadLeaf.o: /usr/include/CC/stl_multimap.h
../TreeSegment/BroadLeaf.o: ../include/LGMUnits.h
../TreeSegment/TreeSegmentFriend.o: ../include/TreeSegment.h
../TreeSegment/TreeSegmentFriend.o: /usr/include/CC/list
../TreeSegment/TreeSegmentFriend.o: /usr/include/CC/stl_algobase.h
../TreeSegment/TreeSegmentFriend.o: /usr/include/CC/stl_config.h
../TreeSegment/TreeSegmentFriend.o: /usr/include/standards.h
../TreeSegment/TreeSegmentFriend.o: /usr/include/CC/stl_relops.h
../TreeSegment/TreeSegmentFriend.o: /usr/include/CC/stl_pair.h
../TreeSegment/TreeSegmentFriend.o: /usr/include/CC/type_traits.h
../TreeSegment/TreeSegmentFriend.o: /usr/include/string.h
../TreeSegment/TreeSegmentFriend.o: /usr/include/limits.h
../TreeSegment/TreeSegmentFriend.o: /usr/include/sgidefs.h
../TreeSegment/TreeSegmentFriend.o: /usr/include/stdlib.h
../TreeSegment/TreeSegmentFriend.o: /usr/include/stddef.h
../TreeSegment/TreeSegmentFriend.o: /usr/include/CC/new.h
../TreeSegment/TreeSegmentFriend.o: /usr/include/CC/iostream.h
../TreeSegment/TreeSegmentFriend.o: /usr/include/memory.h
../TreeSegment/TreeSegmentFriend.o: /usr/include/CC/stl_iterator_base.h
../TreeSegment/TreeSegmentFriend.o: /usr/include/CC/stl_iterator.h
../TreeSegment/TreeSegmentFriend.o: /usr/include/CC/stl_alloc.h
../TreeSegment/TreeSegmentFriend.o: /usr/include/stdio.h
../TreeSegment/TreeSegmentFriend.o: /usr/include/assert.h
../TreeSegment/TreeSegmentFriend.o: /usr/include/CC/stl_threads.h
../TreeSegment/TreeSegmentFriend.o: /usr/include/mutex.h /usr/include/time.h
../TreeSegment/TreeSegmentFriend.o: /usr/include/CC/stl_construct.h
../TreeSegment/TreeSegmentFriend.o: /usr/include/CC/stl_uninitialized.h
../TreeSegment/TreeSegmentFriend.o: /usr/include/CC/stl_list.h
../TreeSegment/TreeSegmentFriend.o: ../../c++adt/include/mathsym.h
../TreeSegment/TreeSegmentFriend.o: /usr/include/math.h
../TreeSegment/TreeSegmentFriend.o: ../../c++adt/include/Point.h
../TreeSegment/TreeSegmentFriend.o: /usr/include/CC/iostream
../TreeSegment/TreeSegmentFriend.o: /usr/include/CC/iosfwd
../TreeSegment/TreeSegmentFriend.o: /usr/include/wchar.h
../TreeSegment/TreeSegmentFriend.o: /usr/include/locale_attr.h
../TreeSegment/TreeSegmentFriend.o: /usr/include/ctype.h
../TreeSegment/TreeSegmentFriend.o: /usr/include/CC/functional
../TreeSegment/TreeSegmentFriend.o: /usr/include/CC/stl_function.h
../TreeSegment/TreeSegmentFriend.o: /usr/include/CC/char_traits.h
../TreeSegment/TreeSegmentFriend.o: /usr/include/CC/istream
../TreeSegment/TreeSegmentFriend.o: /usr/include/CC/ostream
../TreeSegment/TreeSegmentFriend.o: /usr/include/CC/ios
../TreeSegment/TreeSegmentFriend.o: /usr/include/CC/stl_string_fwd.h
../TreeSegment/TreeSegmentFriend.o: /usr/include/CC/stl_exception.h
../TreeSegment/TreeSegmentFriend.o: /usr/include/CC/utility
../TreeSegment/TreeSegmentFriend.o: /usr/include/CC/stl_locale.h
../TreeSegment/TreeSegmentFriend.o: /usr/include/CC/typeinfo
../TreeSegment/TreeSegmentFriend.o: /usr/include/CC/exception
../TreeSegment/TreeSegmentFriend.o: /usr/include/CC/string
../TreeSegment/TreeSegmentFriend.o: /usr/include/CC/stdexcept
../TreeSegment/TreeSegmentFriend.o: /usr/include/CC/memory
../TreeSegment/TreeSegmentFriend.o: /usr/include/CC/stl_tempbuf.h
../TreeSegment/TreeSegmentFriend.o: /usr/include/CC/stl_raw_storage_iter.h
../TreeSegment/TreeSegmentFriend.o: /usr/include/CC/algorithm
../TreeSegment/TreeSegmentFriend.o: /usr/include/CC/stl_algo.h
../TreeSegment/TreeSegmentFriend.o: /usr/include/CC/stl_heap.h
../TreeSegment/TreeSegmentFriend.o: /usr/include/CC/stl_hash_fun.h
../TreeSegment/TreeSegmentFriend.o: /usr/include/CC/stl_ctype.h
../TreeSegment/TreeSegmentFriend.o: /usr/include/CC/c_locale.h
../TreeSegment/TreeSegmentFriend.o: /usr/include/CC/streambuf
../TreeSegment/TreeSegmentFriend.o: /usr/include/CC/stl_stdio_file.h
../TreeSegment/TreeSegmentFriend.o: /usr/include/CC/stl_numeric_facets.h
../TreeSegment/TreeSegmentFriend.o: /usr/include/CC/limits
../TreeSegment/TreeSegmentFriend.o: /usr/include/float.h
../TreeSegment/TreeSegmentFriend.o: ../../c++adt/include/PositionVector.h
../TreeSegment/TreeSegmentFriend.o: /usr/include/CC/vector
../TreeSegment/TreeSegmentFriend.o: /usr/include/CC/stl_range_errors.h
../TreeSegment/TreeSegmentFriend.o: /usr/include/CC/stl_vector.h
../TreeSegment/TreeSegmentFriend.o: /usr/include/CC/stl_bvector.h
../TreeSegment/TreeSegmentFriend.o: ../../c++adt/include/RMatrix.h
../TreeSegment/TreeSegmentFriend.o: ../../c++adt/include/Rotation.h
../TreeSegment/TreeSegmentFriend.o: ../../c++adt/include/TMatrix.h
../TreeSegment/TreeSegmentFriend.o: ../../c++adt/include/TMatrixI.h
../TreeSegment/TreeSegmentFriend.o: ../../c++adt/include/PointI.h
../TreeSegment/TreeSegmentFriend.o: ../include/LGMdecl.h
../TreeSegment/TreeSegmentFriend.o: ../include/LGMSymbols.h
../TreeSegment/TreeSegmentFriend.o: /usr/include/CC/map
../TreeSegment/TreeSegmentFriend.o: /usr/include/CC/stl_tree.h
../TreeSegment/TreeSegmentFriend.o: /usr/include/CC/stl_map.h
../TreeSegment/TreeSegmentFriend.o: /usr/include/CC/stl_multimap.h
../TreeSegment/TreeSegmentFriend.o: ../include/LGMUnits.h
../TreeSegment/TreeSegmentFriend.o: ../include/TreeCompartment.h
../TreeSegment/TreeSegmentFriend.o: ../include/TreeCompartmentI.h
../TreeSegment/TreeSegmentFriend.o: ../include/TreeSegmentI.h
../TreeSegment/TreeSegment.o: ../include/TreeSegment.h /usr/include/CC/list
../TreeSegment/TreeSegment.o: /usr/include/CC/stl_algobase.h
../TreeSegment/TreeSegment.o: /usr/include/CC/stl_config.h
../TreeSegment/TreeSegment.o: /usr/include/standards.h
../TreeSegment/TreeSegment.o: /usr/include/CC/stl_relops.h
../TreeSegment/TreeSegment.o: /usr/include/CC/stl_pair.h
../TreeSegment/TreeSegment.o: /usr/include/CC/type_traits.h
../TreeSegment/TreeSegment.o: /usr/include/string.h /usr/include/limits.h
../TreeSegment/TreeSegment.o: /usr/include/sgidefs.h /usr/include/stdlib.h
../TreeSegment/TreeSegment.o: /usr/include/stddef.h /usr/include/CC/new.h
../TreeSegment/TreeSegment.o: /usr/include/CC/iostream.h
../TreeSegment/TreeSegment.o: /usr/include/memory.h
../TreeSegment/TreeSegment.o: /usr/include/CC/stl_iterator_base.h
../TreeSegment/TreeSegment.o: /usr/include/CC/stl_iterator.h
../TreeSegment/TreeSegment.o: /usr/include/CC/stl_alloc.h
../TreeSegment/TreeSegment.o: /usr/include/stdio.h /usr/include/assert.h
../TreeSegment/TreeSegment.o: /usr/include/CC/stl_threads.h
../TreeSegment/TreeSegment.o: /usr/include/mutex.h /usr/include/time.h
../TreeSegment/TreeSegment.o: /usr/include/CC/stl_construct.h
../TreeSegment/TreeSegment.o: /usr/include/CC/stl_uninitialized.h
../TreeSegment/TreeSegment.o: /usr/include/CC/stl_list.h
../TreeSegment/TreeSegment.o: ../../c++adt/include/mathsym.h
../TreeSegment/TreeSegment.o: /usr/include/math.h
../TreeSegment/TreeSegment.o: ../../c++adt/include/Point.h
../TreeSegment/TreeSegment.o: /usr/include/CC/iostream /usr/include/CC/iosfwd
../TreeSegment/TreeSegment.o: /usr/include/wchar.h /usr/include/locale_attr.h
../TreeSegment/TreeSegment.o: /usr/include/ctype.h /usr/include/CC/functional
../TreeSegment/TreeSegment.o: /usr/include/CC/stl_function.h
../TreeSegment/TreeSegment.o: /usr/include/CC/char_traits.h
../TreeSegment/TreeSegment.o: /usr/include/CC/istream /usr/include/CC/ostream
../TreeSegment/TreeSegment.o: /usr/include/CC/ios
../TreeSegment/TreeSegment.o: /usr/include/CC/stl_string_fwd.h
../TreeSegment/TreeSegment.o: /usr/include/CC/stl_exception.h
../TreeSegment/TreeSegment.o: /usr/include/CC/utility
../TreeSegment/TreeSegment.o: /usr/include/CC/stl_locale.h
../TreeSegment/TreeSegment.o: /usr/include/CC/typeinfo
../TreeSegment/TreeSegment.o: /usr/include/CC/exception
../TreeSegment/TreeSegment.o: /usr/include/CC/string
../TreeSegment/TreeSegment.o: /usr/include/CC/stdexcept
../TreeSegment/TreeSegment.o: /usr/include/CC/memory
../TreeSegment/TreeSegment.o: /usr/include/CC/stl_tempbuf.h
../TreeSegment/TreeSegment.o: /usr/include/CC/stl_raw_storage_iter.h
../TreeSegment/TreeSegment.o: /usr/include/CC/algorithm
../TreeSegment/TreeSegment.o: /usr/include/CC/stl_algo.h
../TreeSegment/TreeSegment.o: /usr/include/CC/stl_heap.h
../TreeSegment/TreeSegment.o: /usr/include/CC/stl_hash_fun.h
../TreeSegment/TreeSegment.o: /usr/include/CC/stl_ctype.h
../TreeSegment/TreeSegment.o: /usr/include/CC/c_locale.h
../TreeSegment/TreeSegment.o: /usr/include/CC/streambuf
../TreeSegment/TreeSegment.o: /usr/include/CC/stl_stdio_file.h
../TreeSegment/TreeSegment.o: /usr/include/CC/stl_numeric_facets.h
../TreeSegment/TreeSegment.o: /usr/include/CC/limits /usr/include/float.h
../TreeSegment/TreeSegment.o: ../../c++adt/include/PositionVector.h
../TreeSegment/TreeSegment.o: /usr/include/CC/vector
../TreeSegment/TreeSegment.o: /usr/include/CC/stl_range_errors.h
../TreeSegment/TreeSegment.o: /usr/include/CC/stl_vector.h
../TreeSegment/TreeSegment.o: /usr/include/CC/stl_bvector.h
../TreeSegment/TreeSegment.o: ../../c++adt/include/RMatrix.h
../TreeSegment/TreeSegment.o: ../../c++adt/include/Rotation.h
../TreeSegment/TreeSegment.o: ../../c++adt/include/TMatrix.h
../TreeSegment/TreeSegment.o: ../../c++adt/include/TMatrixI.h
../TreeSegment/TreeSegment.o: ../../c++adt/include/PointI.h
../TreeSegment/TreeSegment.o: ../include/LGMdecl.h ../include/LGMSymbols.h
../TreeSegment/TreeSegment.o: /usr/include/CC/map /usr/include/CC/stl_tree.h
../TreeSegment/TreeSegment.o: /usr/include/CC/stl_map.h
../TreeSegment/TreeSegment.o: /usr/include/CC/stl_multimap.h
../TreeSegment/TreeSegment.o: ../include/LGMUnits.h
../TreeSegment/TreeSegment.o: ../include/TreeCompartment.h
../TreeSegment/TreeSegment.o: ../include/TreeCompartmentI.h
../TreeSegment/TreeSegment.o: ../include/TreeSegmentI.h
../TreeCompartment/TreeCompartmentFriend.o: ../include/TreeCompartment.h
../TreeCompartment/TreeCompartmentFriend.o: ../../c++adt/include/Point.h
../TreeCompartment/TreeCompartmentFriend.o: /usr/include/math.h
../TreeCompartment/TreeCompartmentFriend.o: /usr/include/sgidefs.h
../TreeCompartment/TreeCompartmentFriend.o: /usr/include/standards.h
../TreeCompartment/TreeCompartmentFriend.o: /usr/include/CC/iostream
../TreeCompartment/TreeCompartmentFriend.o: /usr/include/CC/iosfwd
../TreeCompartment/TreeCompartmentFriend.o: /usr/include/CC/stl_config.h
../TreeCompartment/TreeCompartmentFriend.o: /usr/include/wchar.h
../TreeCompartment/TreeCompartmentFriend.o: /usr/include/locale_attr.h
../TreeCompartment/TreeCompartmentFriend.o: /usr/include/stdio.h
../TreeCompartment/TreeCompartmentFriend.o: /usr/include/ctype.h
../TreeCompartment/TreeCompartmentFriend.o: /usr/include/time.h
../TreeCompartment/TreeCompartmentFriend.o: /usr/include/stddef.h
../TreeCompartment/TreeCompartmentFriend.o: /usr/include/CC/functional
../TreeCompartment/TreeCompartmentFriend.o: /usr/include/CC/stl_function.h
../TreeCompartment/TreeCompartmentFriend.o: /usr/include/CC/char_traits.h
../TreeCompartment/TreeCompartmentFriend.o: /usr/include/string.h
../TreeCompartment/TreeCompartmentFriend.o: /usr/include/CC/istream
../TreeCompartment/TreeCompartmentFriend.o: /usr/include/CC/ostream
../TreeCompartment/TreeCompartmentFriend.o: /usr/include/CC/ios
../TreeCompartment/TreeCompartmentFriend.o: /usr/include/CC/stl_string_fwd.h
../TreeCompartment/TreeCompartmentFriend.o: /usr/include/CC/stl_alloc.h
../TreeCompartment/TreeCompartmentFriend.o: /usr/include/stdlib.h
../TreeCompartment/TreeCompartmentFriend.o: /usr/include/assert.h
../TreeCompartment/TreeCompartmentFriend.o: /usr/include/CC/stl_threads.h
../TreeCompartment/TreeCompartmentFriend.o: /usr/include/mutex.h
../TreeCompartment/TreeCompartmentFriend.o: /usr/include/CC/stl_exception.h
../TreeCompartment/TreeCompartmentFriend.o: /usr/include/CC/utility
../TreeCompartment/TreeCompartmentFriend.o: /usr/include/CC/stl_relops.h
../TreeCompartment/TreeCompartmentFriend.o: /usr/include/CC/stl_pair.h
../TreeCompartment/TreeCompartmentFriend.o: /usr/include/CC/stl_locale.h
../TreeCompartment/TreeCompartmentFriend.o: /usr/include/CC/typeinfo
../TreeCompartment/TreeCompartmentFriend.o: /usr/include/CC/exception
../TreeCompartment/TreeCompartmentFriend.o: /usr/include/CC/string
../TreeCompartment/TreeCompartmentFriend.o: /usr/include/CC/stdexcept
../TreeCompartment/TreeCompartmentFriend.o: /usr/include/CC/stl_iterator_base.h
../TreeCompartment/TreeCompartmentFriend.o: /usr/include/CC/memory
../TreeCompartment/TreeCompartmentFriend.o: /usr/include/CC/stl_algobase.h
../TreeCompartment/TreeCompartmentFriend.o: /usr/include/CC/type_traits.h
../TreeCompartment/TreeCompartmentFriend.o: /usr/include/limits.h
../TreeCompartment/TreeCompartmentFriend.o: /usr/include/CC/new.h
../TreeCompartment/TreeCompartmentFriend.o: /usr/include/CC/iostream.h
../TreeCompartment/TreeCompartmentFriend.o: /usr/include/memory.h
../TreeCompartment/TreeCompartmentFriend.o: /usr/include/CC/stl_iterator.h
../TreeCompartment/TreeCompartmentFriend.o: /usr/include/CC/stl_construct.h
../TreeCompartment/TreeCompartmentFriend.o: /usr/include/CC/stl_tempbuf.h
../TreeCompartment/TreeCompartmentFriend.o: /usr/include/CC/stl_uninitialized.h
../TreeCompartment/TreeCompartmentFriend.o: /usr/include/CC/stl_raw_storage_iter.h
../TreeCompartment/TreeCompartmentFriend.o: /usr/include/CC/algorithm
../TreeCompartment/TreeCompartmentFriend.o: /usr/include/CC/stl_algo.h
../TreeCompartment/TreeCompartmentFriend.o: /usr/include/CC/stl_heap.h
../TreeCompartment/TreeCompartmentFriend.o: /usr/include/CC/stl_hash_fun.h
../TreeCompartment/TreeCompartmentFriend.o: /usr/include/CC/stl_ctype.h
../TreeCompartment/TreeCompartmentFriend.o: /usr/include/CC/c_locale.h
../TreeCompartment/TreeCompartmentFriend.o: /usr/include/CC/streambuf
../TreeCompartment/TreeCompartmentFriend.o: /usr/include/CC/stl_stdio_file.h
../TreeCompartment/TreeCompartmentFriend.o: /usr/include/CC/stl_numeric_facets.h
../TreeCompartment/TreeCompartmentFriend.o: /usr/include/CC/limits
../TreeCompartment/TreeCompartmentFriend.o: /usr/include/float.h
../TreeCompartment/TreeCompartmentFriend.o: ../../c++adt/include/PositionVector.h
../TreeCompartment/TreeCompartmentFriend.o: ../../c++adt/include/mathsym.h
../TreeCompartment/TreeCompartmentFriend.o: /usr/include/CC/vector
../TreeCompartment/TreeCompartmentFriend.o: /usr/include/CC/stl_range_errors.h
../TreeCompartment/TreeCompartmentFriend.o: /usr/include/CC/stl_vector.h
../TreeCompartment/TreeCompartmentFriend.o: /usr/include/CC/stl_bvector.h
../TreeCompartment/TreeCompartmentFriend.o: ../../c++adt/include/RMatrix.h
../TreeCompartment/TreeCompartmentFriend.o: ../../c++adt/include/Rotation.h
../TreeCompartment/TreeCompartmentFriend.o: ../../c++adt/include/TMatrix.h
../TreeCompartment/TreeCompartmentFriend.o: ../../c++adt/include/TMatrixI.h
../TreeCompartment/TreeCompartmentFriend.o: ../../c++adt/include/PointI.h
../TreeCompartment/TreeCompartmentFriend.o: ../include/LGMdecl.h
../TreeCompartment/TreeCompartmentFriend.o: ../include/LGMSymbols.h
../TreeCompartment/TreeCompartmentFriend.o: /usr/include/CC/map
../TreeCompartment/TreeCompartmentFriend.o: /usr/include/CC/stl_tree.h
../TreeCompartment/TreeCompartmentFriend.o: /usr/include/CC/stl_map.h
../TreeCompartment/TreeCompartmentFriend.o: /usr/include/CC/stl_multimap.h
../TreeCompartment/TreeCompartmentFriend.o: ../include/LGMUnits.h
../TreeCompartment/TreeCompartmentFriend.o: ../include/TreeCompartmentI.h
../Tree/TreeFriend.o: ../include/Tree.h /usr/include/CC/algorithm
../Tree/TreeFriend.o: /usr/include/CC/stl_algobase.h
../Tree/TreeFriend.o: /usr/include/CC/stl_config.h /usr/include/standards.h
../Tree/TreeFriend.o: /usr/include/CC/stl_relops.h /usr/include/CC/stl_pair.h
../Tree/TreeFriend.o: /usr/include/CC/type_traits.h /usr/include/string.h
../Tree/TreeFriend.o: /usr/include/limits.h /usr/include/sgidefs.h
../Tree/TreeFriend.o: /usr/include/stdlib.h /usr/include/stddef.h
../Tree/TreeFriend.o: /usr/include/CC/new.h /usr/include/CC/iostream.h
../Tree/TreeFriend.o: /usr/include/memory.h
../Tree/TreeFriend.o: /usr/include/CC/stl_iterator_base.h
../Tree/TreeFriend.o: /usr/include/CC/stl_iterator.h
../Tree/TreeFriend.o: /usr/include/CC/stl_construct.h
../Tree/TreeFriend.o: /usr/include/CC/stl_uninitialized.h
../Tree/TreeFriend.o: /usr/include/CC/stl_tempbuf.h
../Tree/TreeFriend.o: /usr/include/CC/stl_algo.h /usr/include/CC/stl_heap.h
../Tree/TreeFriend.o: /usr/include/CC/numeric /usr/include/CC/stl_function.h
../Tree/TreeFriend.o: /usr/include/CC/stl_numeric.h /usr/include/CC/list
../Tree/TreeFriend.o: /usr/include/CC/stl_alloc.h /usr/include/stdio.h
../Tree/TreeFriend.o: /usr/include/assert.h /usr/include/CC/stl_threads.h
../Tree/TreeFriend.o: /usr/include/mutex.h /usr/include/time.h
../Tree/TreeFriend.o: /usr/include/CC/stl_list.h /usr/include/CC/iostream
../Tree/TreeFriend.o: /usr/include/CC/iosfwd /usr/include/wchar.h
../Tree/TreeFriend.o: /usr/include/locale_attr.h /usr/include/ctype.h
../Tree/TreeFriend.o: /usr/include/CC/functional
../Tree/TreeFriend.o: /usr/include/CC/char_traits.h /usr/include/CC/istream
../Tree/TreeFriend.o: /usr/include/CC/ostream /usr/include/CC/ios
../Tree/TreeFriend.o: /usr/include/CC/stl_string_fwd.h
../Tree/TreeFriend.o: /usr/include/CC/stl_exception.h /usr/include/CC/utility
../Tree/TreeFriend.o: /usr/include/CC/stl_locale.h /usr/include/CC/typeinfo
../Tree/TreeFriend.o: /usr/include/CC/exception /usr/include/CC/string
../Tree/TreeFriend.o: /usr/include/CC/stdexcept /usr/include/CC/memory
../Tree/TreeFriend.o: /usr/include/CC/stl_raw_storage_iter.h
../Tree/TreeFriend.o: /usr/include/CC/stl_hash_fun.h
../Tree/TreeFriend.o: /usr/include/CC/stl_ctype.h /usr/include/CC/c_locale.h
../Tree/TreeFriend.o: /usr/include/CC/streambuf
../Tree/TreeFriend.o: /usr/include/CC/stl_stdio_file.h
../Tree/TreeFriend.o: /usr/include/CC/stl_numeric_facets.h
../Tree/TreeFriend.o: /usr/include/CC/limits /usr/include/float.h
../Tree/TreeFriend.o: ../../c++adt/include/ParametricCurve.h
../Tree/TreeFriend.o: /usr/include/CC/vector
../Tree/TreeFriend.o: /usr/include/CC/stl_range_errors.h
../Tree/TreeFriend.o: /usr/include/CC/stl_vector.h
../Tree/TreeFriend.o: /usr/include/CC/stl_bvector.h /usr/include/CC/fstream
../Tree/TreeFriend.o: /usr/include/CC/stl_codecvt.h
../Tree/TreeFriend.o: ../../c++adt/include/Point.h /usr/include/math.h
../Tree/TreeFriend.o: ../../c++adt/include/PositionVector.h
../Tree/TreeFriend.o: ../../c++adt/include/mathsym.h
../Tree/TreeFriend.o: ../../c++adt/include/RMatrix.h
../Tree/TreeFriend.o: ../../c++adt/include/Rotation.h
../Tree/TreeFriend.o: ../../c++adt/include/TMatrix.h
../Tree/TreeFriend.o: ../../c++adt/include/TMatrixI.h
../Tree/TreeFriend.o: ../../c++adt/include/PointI.h ../include/LGMdecl.h
../Tree/TreeFriend.o: ../include/LGMSymbols.h /usr/include/CC/map
../Tree/TreeFriend.o: /usr/include/CC/stl_tree.h /usr/include/CC/stl_map.h
../Tree/TreeFriend.o: /usr/include/CC/stl_multimap.h ../include/LGMUnits.h
../Tree/TreeFriend.o: ../include/Algorithms.h ../include/AlgorithmsI.h
../Tree/TreeFriend.o: ../include/TreeFunctor.h ../include/TreeCompartment.h
../Tree/TreeFriend.o: ../include/TreeCompartmentI.h ../include/TreeFunctorI.h
../Tree/TreeFriend.o: ../include/TreeMetaFileParser.h
../Tree/TreeFriend.o: ../../c++adt/include/Table.h
../Tree/TreeFriend.o: ../../c++adt/include/DList.h
../Tree/TreeFriend.o: ../../c++adt/include/DListElement.h
../Tree/TreeFriend.o: ../../c++adt/include/boolean.h
../Tree/TreeFriend.o: ../../c++adt/include/TableI.h
../Tree/TreeFriend.o: ../../c++adt/include/Lex.h ../include/RootSystem.h
../Tree/TreeFriend.o: ../include/Bud.h ../include/BudI.h
../Tree/TreeFriend.o: ../include/DefaultBud.h ../include/BranchingPoint.h
../Tree/TreeFriend.o: ../include/BranchingPointI.h ../include/TreeSegment.h
../Tree/TreeFriend.o: ../include/TreeSegmentI.h ../include/HwTreeSegment.h
../Tree/TreeFriend.o: ../include/BroadLeaf.h ../../c++adt/include/Ellipsis.h
../Tree/TreeFriend.o: ../../Firmament/include/FirmamentWithMask.h
../Tree/TreeFriend.o: ../../Firmament/include/Firmament.h
../Tree/TreeFriend.o: ../include/HwTreeSegmentI.h
../Tree/TreeFriend.o: ../include/HwTreeSegmentMetabolismI.h
../Tree/TreeFriend.o: ../include/CfTreeSegment.h ../include/CfTreeSegmentI.h
../Tree/TreeFriend.o: ../include/CfTreeSegmentMetabolismI.h ../include/Axis.h
../Tree/TreeFriend.o: ../include/AxisI.h
../Tree/TreeFriend.o: ../../c++adt/include/ConnectionMatrix.h
../Tree/TreeFriend.o: ../../c++adt/include/ConnectionMatrixI.h
../Tree/TreeFriend.o: ../include/TreeRadiation.h ../include/TreeI.h
../Tree/TreeFriend.o: ../include/TreeMetabolismI.h
../Tree/TreeFriend.o: ../include/TreeMetabolism.h ../include/TreeRadiationI.h
../Tree/Tree.o: ../include/Tree.h /usr/include/CC/algorithm
../Tree/Tree.o: /usr/include/CC/stl_algobase.h /usr/include/CC/stl_config.h
../Tree/Tree.o: /usr/include/standards.h /usr/include/CC/stl_relops.h
../Tree/Tree.o: /usr/include/CC/stl_pair.h /usr/include/CC/type_traits.h
../Tree/Tree.o: /usr/include/string.h /usr/include/limits.h
../Tree/Tree.o: /usr/include/sgidefs.h /usr/include/stdlib.h
../Tree/Tree.o: /usr/include/stddef.h /usr/include/CC/new.h
../Tree/Tree.o: /usr/include/CC/iostream.h /usr/include/memory.h
../Tree/Tree.o: /usr/include/CC/stl_iterator_base.h
../Tree/Tree.o: /usr/include/CC/stl_iterator.h
../Tree/Tree.o: /usr/include/CC/stl_construct.h
../Tree/Tree.o: /usr/include/CC/stl_uninitialized.h
../Tree/Tree.o: /usr/include/CC/stl_tempbuf.h /usr/include/CC/stl_algo.h
../Tree/Tree.o: /usr/include/CC/stl_heap.h /usr/include/CC/numeric
../Tree/Tree.o: /usr/include/CC/stl_function.h /usr/include/CC/stl_numeric.h
../Tree/Tree.o: /usr/include/CC/list /usr/include/CC/stl_alloc.h
../Tree/Tree.o: /usr/include/stdio.h /usr/include/assert.h
../Tree/Tree.o: /usr/include/CC/stl_threads.h /usr/include/mutex.h
../Tree/Tree.o: /usr/include/time.h /usr/include/CC/stl_list.h
../Tree/Tree.o: /usr/include/CC/iostream /usr/include/CC/iosfwd
../Tree/Tree.o: /usr/include/wchar.h /usr/include/locale_attr.h
../Tree/Tree.o: /usr/include/ctype.h /usr/include/CC/functional
../Tree/Tree.o: /usr/include/CC/char_traits.h /usr/include/CC/istream
../Tree/Tree.o: /usr/include/CC/ostream /usr/include/CC/ios
../Tree/Tree.o: /usr/include/CC/stl_string_fwd.h
../Tree/Tree.o: /usr/include/CC/stl_exception.h /usr/include/CC/utility
../Tree/Tree.o: /usr/include/CC/stl_locale.h /usr/include/CC/typeinfo
../Tree/Tree.o: /usr/include/CC/exception /usr/include/CC/string
../Tree/Tree.o: /usr/include/CC/stdexcept /usr/include/CC/memory
../Tree/Tree.o: /usr/include/CC/stl_raw_storage_iter.h
../Tree/Tree.o: /usr/include/CC/stl_hash_fun.h /usr/include/CC/stl_ctype.h
../Tree/Tree.o: /usr/include/CC/c_locale.h /usr/include/CC/streambuf
../Tree/Tree.o: /usr/include/CC/stl_stdio_file.h
../Tree/Tree.o: /usr/include/CC/stl_numeric_facets.h /usr/include/CC/limits
../Tree/Tree.o: /usr/include/float.h ../../c++adt/include/ParametricCurve.h
../Tree/Tree.o: /usr/include/CC/vector /usr/include/CC/stl_range_errors.h
../Tree/Tree.o: /usr/include/CC/stl_vector.h /usr/include/CC/stl_bvector.h
../Tree/Tree.o: /usr/include/CC/fstream /usr/include/CC/stl_codecvt.h
../Tree/Tree.o: ../../c++adt/include/Point.h /usr/include/math.h
../Tree/Tree.o: ../../c++adt/include/PositionVector.h
../Tree/Tree.o: ../../c++adt/include/mathsym.h ../../c++adt/include/RMatrix.h
../Tree/Tree.o: ../../c++adt/include/Rotation.h
../Tree/Tree.o: ../../c++adt/include/TMatrix.h
../Tree/Tree.o: ../../c++adt/include/TMatrixI.h ../../c++adt/include/PointI.h
../Tree/Tree.o: ../include/LGMdecl.h ../include/LGMSymbols.h
../Tree/Tree.o: /usr/include/CC/map /usr/include/CC/stl_tree.h
../Tree/Tree.o: /usr/include/CC/stl_map.h /usr/include/CC/stl_multimap.h
../Tree/Tree.o: ../include/LGMUnits.h ../include/Algorithms.h
../Tree/Tree.o: ../include/AlgorithmsI.h ../include/TreeFunctor.h
../Tree/Tree.o: ../include/TreeCompartment.h ../include/TreeCompartmentI.h
../Tree/Tree.o: ../include/TreeFunctorI.h ../include/TreeMetaFileParser.h
../Tree/Tree.o: ../../c++adt/include/Table.h ../../c++adt/include/DList.h
../Tree/Tree.o: ../../c++adt/include/DListElement.h
../Tree/Tree.o: ../../c++adt/include/boolean.h ../../c++adt/include/TableI.h
../Tree/Tree.o: ../../c++adt/include/Lex.h ../include/RootSystem.h
../Tree/Tree.o: ../include/Bud.h ../include/BudI.h ../include/DefaultBud.h
../Tree/Tree.o: ../include/BranchingPoint.h ../include/BranchingPointI.h
../Tree/Tree.o: ../include/TreeSegment.h ../include/TreeSegmentI.h
../Tree/Tree.o: ../include/HwTreeSegment.h ../include/BroadLeaf.h
../Tree/Tree.o: ../../c++adt/include/Ellipsis.h
../Tree/Tree.o: ../../Firmament/include/FirmamentWithMask.h
../Tree/Tree.o: ../../Firmament/include/Firmament.h
../Tree/Tree.o: ../include/HwTreeSegmentI.h
../Tree/Tree.o: ../include/HwTreeSegmentMetabolismI.h
../Tree/Tree.o: ../include/CfTreeSegment.h ../include/CfTreeSegmentI.h
../Tree/Tree.o: ../include/CfTreeSegmentMetabolismI.h ../include/Axis.h
../Tree/Tree.o: ../include/AxisI.h ../../c++adt/include/ConnectionMatrix.h
../Tree/Tree.o: ../../c++adt/include/ConnectionMatrixI.h
../Tree/Tree.o: ../include/TreeRadiation.h ../include/TreeI.h
../Tree/Tree.o: ../include/TreeMetabolismI.h ../include/TreeMetabolism.h
../Tree/Tree.o: ../include/TreeRadiationI.h
../TreeSegment/BeamShading.o: ../include/Shading.h ../include/Tree.h
../TreeSegment/BeamShading.o: /usr/include/CC/algorithm
../TreeSegment/BeamShading.o: /usr/include/CC/stl_algobase.h
../TreeSegment/BeamShading.o: /usr/include/CC/stl_config.h
../TreeSegment/BeamShading.o: /usr/include/standards.h
../TreeSegment/BeamShading.o: /usr/include/CC/stl_relops.h
../TreeSegment/BeamShading.o: /usr/include/CC/stl_pair.h
../TreeSegment/BeamShading.o: /usr/include/CC/type_traits.h
../TreeSegment/BeamShading.o: /usr/include/string.h /usr/include/limits.h
../TreeSegment/BeamShading.o: /usr/include/sgidefs.h /usr/include/stdlib.h
../TreeSegment/BeamShading.o: /usr/include/stddef.h /usr/include/CC/new.h
../TreeSegment/BeamShading.o: /usr/include/CC/iostream.h
../TreeSegment/BeamShading.o: /usr/include/memory.h
../TreeSegment/BeamShading.o: /usr/include/CC/stl_iterator_base.h
../TreeSegment/BeamShading.o: /usr/include/CC/stl_iterator.h
../TreeSegment/BeamShading.o: /usr/include/CC/stl_construct.h
../TreeSegment/BeamShading.o: /usr/include/CC/stl_uninitialized.h
../TreeSegment/BeamShading.o: /usr/include/CC/stl_tempbuf.h
../TreeSegment/BeamShading.o: /usr/include/CC/stl_algo.h
../TreeSegment/BeamShading.o: /usr/include/CC/stl_heap.h
../TreeSegment/BeamShading.o: /usr/include/CC/numeric
../TreeSegment/BeamShading.o: /usr/include/CC/stl_function.h
../TreeSegment/BeamShading.o: /usr/include/CC/stl_numeric.h
../TreeSegment/BeamShading.o: /usr/include/CC/list
../TreeSegment/BeamShading.o: /usr/include/CC/stl_alloc.h
../TreeSegment/BeamShading.o: /usr/include/stdio.h /usr/include/assert.h
../TreeSegment/BeamShading.o: /usr/include/CC/stl_threads.h
../TreeSegment/BeamShading.o: /usr/include/mutex.h /usr/include/time.h
../TreeSegment/BeamShading.o: /usr/include/CC/stl_list.h
../TreeSegment/BeamShading.o: /usr/include/CC/iostream /usr/include/CC/iosfwd
../TreeSegment/BeamShading.o: /usr/include/wchar.h /usr/include/locale_attr.h
../TreeSegment/BeamShading.o: /usr/include/ctype.h /usr/include/CC/functional
../TreeSegment/BeamShading.o: /usr/include/CC/char_traits.h
../TreeSegment/BeamShading.o: /usr/include/CC/istream /usr/include/CC/ostream
../TreeSegment/BeamShading.o: /usr/include/CC/ios
../TreeSegment/BeamShading.o: /usr/include/CC/stl_string_fwd.h
../TreeSegment/BeamShading.o: /usr/include/CC/stl_exception.h
../TreeSegment/BeamShading.o: /usr/include/CC/utility
../TreeSegment/BeamShading.o: /usr/include/CC/stl_locale.h
../TreeSegment/BeamShading.o: /usr/include/CC/typeinfo
../TreeSegment/BeamShading.o: /usr/include/CC/exception
../TreeSegment/BeamShading.o: /usr/include/CC/string
../TreeSegment/BeamShading.o: /usr/include/CC/stdexcept
../TreeSegment/BeamShading.o: /usr/include/CC/memory
../TreeSegment/BeamShading.o: /usr/include/CC/stl_raw_storage_iter.h
../TreeSegment/BeamShading.o: /usr/include/CC/stl_hash_fun.h
../TreeSegment/BeamShading.o: /usr/include/CC/stl_ctype.h
../TreeSegment/BeamShading.o: /usr/include/CC/c_locale.h
../TreeSegment/BeamShading.o: /usr/include/CC/streambuf
../TreeSegment/BeamShading.o: /usr/include/CC/stl_stdio_file.h
../TreeSegment/BeamShading.o: /usr/include/CC/stl_numeric_facets.h
../TreeSegment/BeamShading.o: /usr/include/CC/limits /usr/include/float.h
../TreeSegment/BeamShading.o: ../../c++adt/include/ParametricCurve.h
../TreeSegment/BeamShading.o: /usr/include/CC/vector
../TreeSegment/BeamShading.o: /usr/include/CC/stl_range_errors.h
../TreeSegment/BeamShading.o: /usr/include/CC/stl_vector.h
../TreeSegment/BeamShading.o: /usr/include/CC/stl_bvector.h
../TreeSegment/BeamShading.o: /usr/include/CC/fstream
../TreeSegment/BeamShading.o: /usr/include/CC/stl_codecvt.h
../TreeSegment/BeamShading.o: ../../c++adt/include/Point.h
../TreeSegment/BeamShading.o: /usr/include/math.h
../TreeSegment/BeamShading.o: ../../c++adt/include/PositionVector.h
../TreeSegment/BeamShading.o: ../../c++adt/include/mathsym.h
../TreeSegment/BeamShading.o: ../../c++adt/include/RMatrix.h
../TreeSegment/BeamShading.o: ../../c++adt/include/Rotation.h
../TreeSegment/BeamShading.o: ../../c++adt/include/TMatrix.h
../TreeSegment/BeamShading.o: ../../c++adt/include/TMatrixI.h
../TreeSegment/BeamShading.o: ../../c++adt/include/PointI.h
../TreeSegment/BeamShading.o: ../include/LGMdecl.h ../include/LGMSymbols.h
../TreeSegment/BeamShading.o: /usr/include/CC/map /usr/include/CC/stl_tree.h
../TreeSegment/BeamShading.o: /usr/include/CC/stl_map.h
../TreeSegment/BeamShading.o: /usr/include/CC/stl_multimap.h
../TreeSegment/BeamShading.o: ../include/LGMUnits.h ../include/Algorithms.h
../TreeSegment/BeamShading.o: ../include/AlgorithmsI.h
../TreeSegment/BeamShading.o: ../include/TreeFunctor.h
../TreeSegment/BeamShading.o: ../include/TreeCompartment.h
../TreeSegment/BeamShading.o: ../include/TreeCompartmentI.h
../TreeSegment/BeamShading.o: ../include/TreeFunctorI.h
../TreeSegment/BeamShading.o: ../include/TreeMetaFileParser.h
../TreeSegment/BeamShading.o: ../../c++adt/include/Table.h
../TreeSegment/BeamShading.o: ../../c++adt/include/DList.h
../TreeSegment/BeamShading.o: ../../c++adt/include/DListElement.h
../TreeSegment/BeamShading.o: ../../c++adt/include/boolean.h
../TreeSegment/BeamShading.o: ../../c++adt/include/TableI.h
../TreeSegment/BeamShading.o: ../../c++adt/include/Lex.h
../TreeSegment/BeamShading.o: ../include/RootSystem.h ../include/Bud.h
../TreeSegment/BeamShading.o: ../include/BudI.h ../include/DefaultBud.h
../TreeSegment/BeamShading.o: ../include/BranchingPoint.h
../TreeSegment/BeamShading.o: ../include/BranchingPointI.h
../TreeSegment/BeamShading.o: ../include/TreeSegment.h
../TreeSegment/BeamShading.o: ../include/TreeSegmentI.h
../TreeSegment/BeamShading.o: ../include/HwTreeSegment.h
../TreeSegment/BeamShading.o: ../include/BroadLeaf.h
../TreeSegment/BeamShading.o: ../../c++adt/include/Ellipsis.h
../TreeSegment/BeamShading.o: ../../Firmament/include/FirmamentWithMask.h
../TreeSegment/BeamShading.o: ../../Firmament/include/Firmament.h
../TreeSegment/BeamShading.o: ../include/HwTreeSegmentI.h
../TreeSegment/BeamShading.o: ../include/HwTreeSegmentMetabolismI.h
../TreeSegment/BeamShading.o: ../include/CfTreeSegment.h
../TreeSegment/BeamShading.o: ../include/CfTreeSegmentI.h
../TreeSegment/BeamShading.o: ../include/CfTreeSegmentMetabolismI.h
../TreeSegment/BeamShading.o: ../include/Axis.h ../include/AxisI.h
../TreeSegment/BeamShading.o: ../../c++adt/include/ConnectionMatrix.h
../TreeSegment/BeamShading.o: ../../c++adt/include/ConnectionMatrixI.h
../TreeSegment/BeamShading.o: ../include/TreeRadiation.h ../include/TreeI.h
../TreeSegment/BeamShading.o: ../include/TreeMetabolismI.h
../TreeSegment/BeamShading.o: ../include/TreeMetabolism.h
../TreeSegment/BeamShading.o: ../include/TreeRadiationI.h
../TreeSegment/BeamShading.o: ../include/ShadingI.h
../TreeSegment/BroadLeafMetabolism.o: ../include/BroadLeaf.h
../TreeSegment/BroadLeafMetabolism.o: ../../c++adt/include/Point.h
../TreeSegment/BroadLeafMetabolism.o: /usr/include/math.h
../TreeSegment/BroadLeafMetabolism.o: /usr/include/sgidefs.h
../TreeSegment/BroadLeafMetabolism.o: /usr/include/standards.h
../TreeSegment/BroadLeafMetabolism.o: /usr/include/CC/iostream
../TreeSegment/BroadLeafMetabolism.o: /usr/include/CC/iosfwd
../TreeSegment/BroadLeafMetabolism.o: /usr/include/CC/stl_config.h
../TreeSegment/BroadLeafMetabolism.o: /usr/include/wchar.h
../TreeSegment/BroadLeafMetabolism.o: /usr/include/locale_attr.h
../TreeSegment/BroadLeafMetabolism.o: /usr/include/stdio.h
../TreeSegment/BroadLeafMetabolism.o: /usr/include/ctype.h
../TreeSegment/BroadLeafMetabolism.o: /usr/include/time.h
../TreeSegment/BroadLeafMetabolism.o: /usr/include/stddef.h
../TreeSegment/BroadLeafMetabolism.o: /usr/include/CC/functional
../TreeSegment/BroadLeafMetabolism.o: /usr/include/CC/stl_function.h
../TreeSegment/BroadLeafMetabolism.o: /usr/include/CC/char_traits.h
../TreeSegment/BroadLeafMetabolism.o: /usr/include/string.h
../TreeSegment/BroadLeafMetabolism.o: /usr/include/CC/istream
../TreeSegment/BroadLeafMetabolism.o: /usr/include/CC/ostream
../TreeSegment/BroadLeafMetabolism.o: /usr/include/CC/ios
../TreeSegment/BroadLeafMetabolism.o: /usr/include/CC/stl_string_fwd.h
../TreeSegment/BroadLeafMetabolism.o: /usr/include/CC/stl_alloc.h
../TreeSegment/BroadLeafMetabolism.o: /usr/include/stdlib.h
../TreeSegment/BroadLeafMetabolism.o: /usr/include/assert.h
../TreeSegment/BroadLeafMetabolism.o: /usr/include/CC/stl_threads.h
../TreeSegment/BroadLeafMetabolism.o: /usr/include/mutex.h
../TreeSegment/BroadLeafMetabolism.o: /usr/include/CC/stl_exception.h
../TreeSegment/BroadLeafMetabolism.o: /usr/include/CC/utility
../TreeSegment/BroadLeafMetabolism.o: /usr/include/CC/stl_relops.h
../TreeSegment/BroadLeafMetabolism.o: /usr/include/CC/stl_pair.h
../TreeSegment/BroadLeafMetabolism.o: /usr/include/CC/stl_locale.h
../TreeSegment/BroadLeafMetabolism.o: /usr/include/CC/typeinfo
../TreeSegment/BroadLeafMetabolism.o: /usr/include/CC/exception
../TreeSegment/BroadLeafMetabolism.o: /usr/include/CC/string
../TreeSegment/BroadLeafMetabolism.o: /usr/include/CC/stdexcept
../TreeSegment/BroadLeafMetabolism.o: /usr/include/CC/stl_iterator_base.h
../TreeSegment/BroadLeafMetabolism.o: /usr/include/CC/memory
../TreeSegment/BroadLeafMetabolism.o: /usr/include/CC/stl_algobase.h
../TreeSegment/BroadLeafMetabolism.o: /usr/include/CC/type_traits.h
../TreeSegment/BroadLeafMetabolism.o: /usr/include/limits.h
../TreeSegment/BroadLeafMetabolism.o: /usr/include/CC/new.h
../TreeSegment/BroadLeafMetabolism.o: /usr/include/CC/iostream.h
../TreeSegment/BroadLeafMetabolism.o: /usr/include/memory.h
../TreeSegment/BroadLeafMetabolism.o: /usr/include/CC/stl_iterator.h
../TreeSegment/BroadLeafMetabolism.o: /usr/include/CC/stl_construct.h
../TreeSegment/BroadLeafMetabolism.o: /usr/include/CC/stl_tempbuf.h
../TreeSegment/BroadLeafMetabolism.o: /usr/include/CC/stl_uninitialized.h
../TreeSegment/BroadLeafMetabolism.o: /usr/include/CC/stl_raw_storage_iter.h
../TreeSegment/BroadLeafMetabolism.o: /usr/include/CC/algorithm
../TreeSegment/BroadLeafMetabolism.o: /usr/include/CC/stl_algo.h
../TreeSegment/BroadLeafMetabolism.o: /usr/include/CC/stl_heap.h
../TreeSegment/BroadLeafMetabolism.o: /usr/include/CC/stl_hash_fun.h
../TreeSegment/BroadLeafMetabolism.o: /usr/include/CC/stl_ctype.h
../TreeSegment/BroadLeafMetabolism.o: /usr/include/CC/c_locale.h
../TreeSegment/BroadLeafMetabolism.o: /usr/include/CC/streambuf
../TreeSegment/BroadLeafMetabolism.o: /usr/include/CC/stl_stdio_file.h
../TreeSegment/BroadLeafMetabolism.o: /usr/include/CC/stl_numeric_facets.h
../TreeSegment/BroadLeafMetabolism.o: /usr/include/CC/limits
../TreeSegment/BroadLeafMetabolism.o: /usr/include/float.h
../TreeSegment/BroadLeafMetabolism.o: ../../c++adt/include/PositionVector.h
../TreeSegment/BroadLeafMetabolism.o: ../../c++adt/include/mathsym.h
../TreeSegment/BroadLeafMetabolism.o: /usr/include/CC/vector
../TreeSegment/BroadLeafMetabolism.o: /usr/include/CC/stl_range_errors.h
../TreeSegment/BroadLeafMetabolism.o: /usr/include/CC/stl_vector.h
../TreeSegment/BroadLeafMetabolism.o: /usr/include/CC/stl_bvector.h
../TreeSegment/BroadLeafMetabolism.o: ../../c++adt/include/RMatrix.h
../TreeSegment/BroadLeafMetabolism.o: ../../c++adt/include/Rotation.h
../TreeSegment/BroadLeafMetabolism.o: ../../c++adt/include/TMatrix.h
../TreeSegment/BroadLeafMetabolism.o: ../../c++adt/include/TMatrixI.h
../TreeSegment/BroadLeafMetabolism.o: ../../c++adt/include/PointI.h
../TreeSegment/BroadLeafMetabolism.o: ../../c++adt/include/Ellipsis.h
../TreeSegment/BroadLeafMetabolism.o: ../include/LGMdecl.h
../TreeSegment/BroadLeafMetabolism.o: ../include/LGMSymbols.h
../TreeSegment/BroadLeafMetabolism.o: /usr/include/CC/map
../TreeSegment/BroadLeafMetabolism.o: /usr/include/CC/stl_tree.h
../TreeSegment/BroadLeafMetabolism.o: /usr/include/CC/stl_map.h
../TreeSegment/BroadLeafMetabolism.o: /usr/include/CC/stl_multimap.h
../TreeSegment/BroadLeafMetabolism.o: ../include/LGMUnits.h
../TreeSegment/CfTreeSegment.o: ../include/CfTreeSegment.h
../TreeSegment/CfTreeSegment.o: /usr/include/CC/list
../TreeSegment/CfTreeSegment.o: /usr/include/CC/stl_algobase.h
../TreeSegment/CfTreeSegment.o: /usr/include/CC/stl_config.h
../TreeSegment/CfTreeSegment.o: /usr/include/standards.h
../TreeSegment/CfTreeSegment.o: /usr/include/CC/stl_relops.h
../TreeSegment/CfTreeSegment.o: /usr/include/CC/stl_pair.h
../TreeSegment/CfTreeSegment.o: /usr/include/CC/type_traits.h
../TreeSegment/CfTreeSegment.o: /usr/include/string.h /usr/include/limits.h
../TreeSegment/CfTreeSegment.o: /usr/include/sgidefs.h /usr/include/stdlib.h
../TreeSegment/CfTreeSegment.o: /usr/include/stddef.h /usr/include/CC/new.h
../TreeSegment/CfTreeSegment.o: /usr/include/CC/iostream.h
../TreeSegment/CfTreeSegment.o: /usr/include/memory.h
../TreeSegment/CfTreeSegment.o: /usr/include/CC/stl_iterator_base.h
../TreeSegment/CfTreeSegment.o: /usr/include/CC/stl_iterator.h
../TreeSegment/CfTreeSegment.o: /usr/include/CC/stl_alloc.h
../TreeSegment/CfTreeSegment.o: /usr/include/stdio.h /usr/include/assert.h
../TreeSegment/CfTreeSegment.o: /usr/include/CC/stl_threads.h
../TreeSegment/CfTreeSegment.o: /usr/include/mutex.h /usr/include/time.h
../TreeSegment/CfTreeSegment.o: /usr/include/CC/stl_construct.h
../TreeSegment/CfTreeSegment.o: /usr/include/CC/stl_uninitialized.h
../TreeSegment/CfTreeSegment.o: /usr/include/CC/stl_list.h
../TreeSegment/CfTreeSegment.o: ../../c++adt/include/mathsym.h
../TreeSegment/CfTreeSegment.o: /usr/include/math.h
../TreeSegment/CfTreeSegment.o: ../../c++adt/include/Point.h
../TreeSegment/CfTreeSegment.o: /usr/include/CC/iostream
../TreeSegment/CfTreeSegment.o: /usr/include/CC/iosfwd /usr/include/wchar.h
../TreeSegment/CfTreeSegment.o: /usr/include/locale_attr.h
../TreeSegment/CfTreeSegment.o: /usr/include/ctype.h
../TreeSegment/CfTreeSegment.o: /usr/include/CC/functional
../TreeSegment/CfTreeSegment.o: /usr/include/CC/stl_function.h
../TreeSegment/CfTreeSegment.o: /usr/include/CC/char_traits.h
../TreeSegment/CfTreeSegment.o: /usr/include/CC/istream
../TreeSegment/CfTreeSegment.o: /usr/include/CC/ostream /usr/include/CC/ios
../TreeSegment/CfTreeSegment.o: /usr/include/CC/stl_string_fwd.h
../TreeSegment/CfTreeSegment.o: /usr/include/CC/stl_exception.h
../TreeSegment/CfTreeSegment.o: /usr/include/CC/utility
../TreeSegment/CfTreeSegment.o: /usr/include/CC/stl_locale.h
../TreeSegment/CfTreeSegment.o: /usr/include/CC/typeinfo
../TreeSegment/CfTreeSegment.o: /usr/include/CC/exception
../TreeSegment/CfTreeSegment.o: /usr/include/CC/string
../TreeSegment/CfTreeSegment.o: /usr/include/CC/stdexcept
../TreeSegment/CfTreeSegment.o: /usr/include/CC/memory
../TreeSegment/CfTreeSegment.o: /usr/include/CC/stl_tempbuf.h
../TreeSegment/CfTreeSegment.o: /usr/include/CC/stl_raw_storage_iter.h
../TreeSegment/CfTreeSegment.o: /usr/include/CC/algorithm
../TreeSegment/CfTreeSegment.o: /usr/include/CC/stl_algo.h
../TreeSegment/CfTreeSegment.o: /usr/include/CC/stl_heap.h
../TreeSegment/CfTreeSegment.o: /usr/include/CC/stl_hash_fun.h
../TreeSegment/CfTreeSegment.o: /usr/include/CC/stl_ctype.h
../TreeSegment/CfTreeSegment.o: /usr/include/CC/c_locale.h
../TreeSegment/CfTreeSegment.o: /usr/include/CC/streambuf
../TreeSegment/CfTreeSegment.o: /usr/include/CC/stl_stdio_file.h
../TreeSegment/CfTreeSegment.o: /usr/include/CC/stl_numeric_facets.h
../TreeSegment/CfTreeSegment.o: /usr/include/CC/limits /usr/include/float.h
../TreeSegment/CfTreeSegment.o: ../../c++adt/include/PositionVector.h
../TreeSegment/CfTreeSegment.o: /usr/include/CC/vector
../TreeSegment/CfTreeSegment.o: /usr/include/CC/stl_range_errors.h
../TreeSegment/CfTreeSegment.o: /usr/include/CC/stl_vector.h
../TreeSegment/CfTreeSegment.o: /usr/include/CC/stl_bvector.h
../TreeSegment/CfTreeSegment.o: ../../c++adt/include/RMatrix.h
../TreeSegment/CfTreeSegment.o: ../../c++adt/include/Rotation.h
../TreeSegment/CfTreeSegment.o: ../../c++adt/include/TMatrix.h
../TreeSegment/CfTreeSegment.o: ../../c++adt/include/TMatrixI.h
../TreeSegment/CfTreeSegment.o: ../../c++adt/include/PointI.h
../TreeSegment/CfTreeSegment.o: ../include/LGMdecl.h ../include/LGMSymbols.h
../TreeSegment/CfTreeSegment.o: /usr/include/CC/map
../TreeSegment/CfTreeSegment.o: /usr/include/CC/stl_tree.h
../TreeSegment/CfTreeSegment.o: /usr/include/CC/stl_map.h
../TreeSegment/CfTreeSegment.o: /usr/include/CC/stl_multimap.h
../TreeSegment/CfTreeSegment.o: ../include/LGMUnits.h
../TreeSegment/CfTreeSegment.o: ../include/TreeSegment.h
../TreeSegment/CfTreeSegment.o: ../include/TreeCompartment.h
../TreeSegment/CfTreeSegment.o: ../include/TreeCompartmentI.h
../TreeSegment/CfTreeSegment.o: ../include/TreeSegmentI.h
../TreeSegment/CfTreeSegment.o: ../include/CfTreeSegmentI.h
../TreeSegment/CfTreeSegment.o: ../include/CfTreeSegmentMetabolismI.h
