SRC = ../Axis/AxisFriend.cc  \
      ../BetulaWithFlow/BetulaWithFlow.cc \
      ../BranchingPoint/BranchingPointFriend.cc \
      ../Bud/BudFriend.cc \
      ../Bud/Bud.cc \
      ../TreeMetaFileParser/TreeMetaFileParser.cc \
      ../TreeSegment/BroadLeaf.cc \
      ../TreeSegment/TreeSegmentFriend.cc \
      ../TreeSegment/TreeSegment.cc \
      ../TreeCompartment/TreeCompartmentFriend.cc\
      ../Tree/TreeFriend.cc \
      ../Tree/Tree.cc 
  
OBJ = ../Axis/AxisFriend.o \
      ../BetulaWithFlow/BetulaWithFlow.o \
      ../BranchingPoint/BranchingPointFriend.o \
      ../Bud/BudFriend.o \
      ../Bud/Bud.o \
      ../TreeMetaFileParser/TreeMetaFileParser.o \
      ../TreeSegment/BroadLeaf.o \
      ../TreeSegment/TreeSegmentFriend.o \
      ../TreeSegment/TreeSegment.o \
      ../TreeCompartment/TreeCompartmentFriend.o \
      ../Tree/TreeFriend.o \
      ../Tree/Tree.o 

INCLUDE = -I../include  -I../../c++adt/include -I../../Firmament/include
STL = -I/usr/include/CC
CCC = CC -64
ETAGS = etags -d -T -C -o

OPTIMIZE = -O
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
# DO NOT DELETE THIS LINE -- make depend depends on it.

../Axis/AxisFriend.o: ../include/Axis.h /usr/include/CC/list
../Axis/AxisFriend.o: /usr/include/CC/stl_algobase.h
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
../Axis/AxisFriend.o: /usr/include/assert.h /usr/include/CC/stl_construct.h
../Axis/AxisFriend.o: /usr/include/CC/stl_uninitialized.h
../Axis/AxisFriend.o: /usr/include/CC/stl_list.h ../../c++adt/include/Point.h
../Axis/AxisFriend.o: /usr/include/math.h ../../c++adt/include/PointI.h
../Axis/AxisFriend.o: ../../c++adt/include/PositionVector.h
../Axis/AxisFriend.o: ../../c++adt/include/mathsym.h /usr/include/CC/vector
../Axis/AxisFriend.o: /usr/include/CC/stl_range_errors.h
../Axis/AxisFriend.o: /usr/include/CC/stl_vector.h
../Axis/AxisFriend.o: /usr/include/CC/stl_bvector.h
../Axis/AxisFriend.o: ../../c++adt/include/RMatrix.h
../Axis/AxisFriend.o: ../../c++adt/include/TMatrix.h /usr/include/CC/stream.h
../Axis/AxisFriend.o: /usr/include/CC/iomanip.h /usr/include/CC/generic.h
../Axis/AxisFriend.o: /usr/include/CC/stdiostream.h /usr/include/CC/fstream.h
../Axis/AxisFriend.o: ../../c++adt/include/TMatrixI.h ../include/LGMdecl.h
../Axis/AxisFriend.o: ../include/LGMSymbols.h /usr/include/CC/map
../Axis/AxisFriend.o: /usr/include/CC/stl_tree.h
../Axis/AxisFriend.o: /usr/include/CC/stl_function.h
../Axis/AxisFriend.o: /usr/include/CC/stl_map.h
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
../BetulaWithFlow/BetulaWithFlow.o: /usr/include/CC/stl_list.h
../BetulaWithFlow/BetulaWithFlow.o: /usr/include/CC/stream.h
../BetulaWithFlow/BetulaWithFlow.o: /usr/include/CC/iomanip.h
../BetulaWithFlow/BetulaWithFlow.o: /usr/include/CC/generic.h
../BetulaWithFlow/BetulaWithFlow.o: /usr/include/CC/stdiostream.h
../BetulaWithFlow/BetulaWithFlow.o: /usr/include/CC/fstream.h
../BetulaWithFlow/BetulaWithFlow.o: ../../c++adt/include/CString.h
../BetulaWithFlow/BetulaWithFlow.o: /usr/include/ctype.h
../BetulaWithFlow/BetulaWithFlow.o: /usr/include/locale_attr.h
../BetulaWithFlow/BetulaWithFlow.o: ../../c++adt/include/ParametricCurve.h
../BetulaWithFlow/BetulaWithFlow.o: /usr/include/CC/vector
../BetulaWithFlow/BetulaWithFlow.o: /usr/include/CC/stl_range_errors.h
../BetulaWithFlow/BetulaWithFlow.o: /usr/include/CC/stl_vector.h
../BetulaWithFlow/BetulaWithFlow.o: /usr/include/CC/stl_bvector.h
../BetulaWithFlow/BetulaWithFlow.o: /usr/include/float.h
../BetulaWithFlow/BetulaWithFlow.o: ../../c++adt/include/Point.h
../BetulaWithFlow/BetulaWithFlow.o: /usr/include/math.h
../BetulaWithFlow/BetulaWithFlow.o: ../../c++adt/include/PointI.h
../BetulaWithFlow/BetulaWithFlow.o: ../../c++adt/include/PositionVector.h
../BetulaWithFlow/BetulaWithFlow.o: ../../c++adt/include/mathsym.h
../BetulaWithFlow/BetulaWithFlow.o: ../../c++adt/include/RMatrix.h
../BetulaWithFlow/BetulaWithFlow.o: ../../c++adt/include/TMatrix.h
../BetulaWithFlow/BetulaWithFlow.o: ../../c++adt/include/TMatrixI.h
../BetulaWithFlow/BetulaWithFlow.o: ../include/Algorithms.h
../BetulaWithFlow/BetulaWithFlow.o: /usr/include/CC/functional
../BetulaWithFlow/BetulaWithFlow.o: ../include/LGMdecl.h
../BetulaWithFlow/BetulaWithFlow.o: ../include/LGMSymbols.h
../BetulaWithFlow/BetulaWithFlow.o: /usr/include/CC/map
../BetulaWithFlow/BetulaWithFlow.o: /usr/include/CC/stl_tree.h
../BetulaWithFlow/BetulaWithFlow.o: /usr/include/CC/stl_map.h
../BetulaWithFlow/BetulaWithFlow.o: /usr/include/CC/stl_multimap.h
../BetulaWithFlow/BetulaWithFlow.o: ../include/LGMUnits.h
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
../BetulaWithFlow/BetulaWithFlow.o: ../include/TreeSegmentMetabolismI.h
../BetulaWithFlow/BetulaWithFlow.o: ../include/HwTreeSegment.h
../BetulaWithFlow/BetulaWithFlow.o: ../include/BroadLeaf.h
../BetulaWithFlow/BetulaWithFlow.o: ../../c++adt/include/Ellipsis.h
../BetulaWithFlow/BetulaWithFlow.o: ../../Firmament/include/Firmament.h
../BetulaWithFlow/BetulaWithFlow.o: ../include/HwTreeSegmentI.h
../BetulaWithFlow/BetulaWithFlow.o: ../include/CfTreeSegment.h
../BetulaWithFlow/BetulaWithFlow.o: ../include/Axis.h ../include/AxisI.h
../BetulaWithFlow/BetulaWithFlow.o: ../../c++adt/include/ConnectionMatrix.h
../BetulaWithFlow/BetulaWithFlow.o: ../../c++adt/include/ConnectionMatrixI.h
../BetulaWithFlow/BetulaWithFlow.o: ../include/TreeI.h
../BetulaWithFlow/BetulaWithFlow.o: ../include/TreeMetabolismI.h
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
../BranchingPoint/BranchingPointFriend.o: ../../c++adt/include/PointI.h
../BranchingPoint/BranchingPointFriend.o: ../../c++adt/include/PositionVector.h
../BranchingPoint/BranchingPointFriend.o: ../../c++adt/include/mathsym.h
../BranchingPoint/BranchingPointFriend.o: /usr/include/CC/vector
../BranchingPoint/BranchingPointFriend.o: /usr/include/CC/stl_range_errors.h
../BranchingPoint/BranchingPointFriend.o: /usr/include/CC/stl_vector.h
../BranchingPoint/BranchingPointFriend.o: /usr/include/CC/stl_bvector.h
../BranchingPoint/BranchingPointFriend.o: ../../c++adt/include/RMatrix.h
../BranchingPoint/BranchingPointFriend.o: ../../c++adt/include/TMatrix.h
../BranchingPoint/BranchingPointFriend.o: /usr/include/CC/stream.h
../BranchingPoint/BranchingPointFriend.o: /usr/include/CC/iomanip.h
../BranchingPoint/BranchingPointFriend.o: /usr/include/CC/generic.h
../BranchingPoint/BranchingPointFriend.o: /usr/include/CC/stdiostream.h
../BranchingPoint/BranchingPointFriend.o: /usr/include/CC/fstream.h
../BranchingPoint/BranchingPointFriend.o: ../../c++adt/include/TMatrixI.h
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
../Bud/BudFriend.o: /usr/include/standards.h /usr/include/CC/iostream.h
../Bud/BudFriend.o: /usr/include/memory.h /usr/include/stddef.h
../Bud/BudFriend.o: ../../c++adt/include/PointI.h
../Bud/BudFriend.o: ../../c++adt/include/PositionVector.h
../Bud/BudFriend.o: ../../c++adt/include/mathsym.h /usr/include/CC/vector
../Bud/BudFriend.o: /usr/include/CC/stl_range_errors.h
../Bud/BudFriend.o: /usr/include/CC/stl_config.h
../Bud/BudFriend.o: /usr/include/CC/stl_algobase.h
../Bud/BudFriend.o: /usr/include/CC/stl_relops.h /usr/include/CC/stl_pair.h
../Bud/BudFriend.o: /usr/include/CC/type_traits.h /usr/include/string.h
../Bud/BudFriend.o: /usr/include/limits.h /usr/include/stdlib.h
../Bud/BudFriend.o: /usr/include/CC/new.h /usr/include/CC/stl_iterator_base.h
../Bud/BudFriend.o: /usr/include/CC/stl_iterator.h
../Bud/BudFriend.o: /usr/include/CC/stl_alloc.h /usr/include/stdio.h
../Bud/BudFriend.o: /usr/include/assert.h /usr/include/CC/stl_construct.h
../Bud/BudFriend.o: /usr/include/CC/stl_uninitialized.h
../Bud/BudFriend.o: /usr/include/CC/stl_vector.h
../Bud/BudFriend.o: /usr/include/CC/stl_bvector.h
../Bud/BudFriend.o: ../../c++adt/include/RMatrix.h
../Bud/BudFriend.o: ../../c++adt/include/TMatrix.h /usr/include/CC/stream.h
../Bud/BudFriend.o: /usr/include/CC/iomanip.h /usr/include/CC/generic.h
../Bud/BudFriend.o: /usr/include/CC/stdiostream.h /usr/include/CC/fstream.h
../Bud/BudFriend.o: ../../c++adt/include/TMatrixI.h ../include/LGMdecl.h
../Bud/BudFriend.o: ../include/LGMSymbols.h /usr/include/CC/map
../Bud/BudFriend.o: /usr/include/CC/stl_tree.h /usr/include/CC/stl_function.h
../Bud/BudFriend.o: /usr/include/CC/stl_map.h /usr/include/CC/stl_multimap.h
../Bud/BudFriend.o: ../include/LGMUnits.h ../include/BudI.h
../Bud/Bud.o: ../include/Bud.h ../../c++adt/include/Point.h
../Bud/Bud.o: /usr/include/math.h /usr/include/sgidefs.h
../Bud/Bud.o: /usr/include/standards.h /usr/include/CC/iostream.h
../Bud/Bud.o: /usr/include/memory.h /usr/include/stddef.h
../Bud/Bud.o: ../../c++adt/include/PointI.h
../Bud/Bud.o: ../../c++adt/include/PositionVector.h
../Bud/Bud.o: ../../c++adt/include/mathsym.h /usr/include/CC/vector
../Bud/Bud.o: /usr/include/CC/stl_range_errors.h /usr/include/CC/stl_config.h
../Bud/Bud.o: /usr/include/CC/stl_algobase.h /usr/include/CC/stl_relops.h
../Bud/Bud.o: /usr/include/CC/stl_pair.h /usr/include/CC/type_traits.h
../Bud/Bud.o: /usr/include/string.h /usr/include/limits.h
../Bud/Bud.o: /usr/include/stdlib.h /usr/include/CC/new.h
../Bud/Bud.o: /usr/include/CC/stl_iterator_base.h
../Bud/Bud.o: /usr/include/CC/stl_iterator.h /usr/include/CC/stl_alloc.h
../Bud/Bud.o: /usr/include/stdio.h /usr/include/assert.h
../Bud/Bud.o: /usr/include/CC/stl_construct.h
../Bud/Bud.o: /usr/include/CC/stl_uninitialized.h
../Bud/Bud.o: /usr/include/CC/stl_vector.h /usr/include/CC/stl_bvector.h
../Bud/Bud.o: ../../c++adt/include/RMatrix.h ../../c++adt/include/TMatrix.h
../Bud/Bud.o: /usr/include/CC/stream.h /usr/include/CC/iomanip.h
../Bud/Bud.o: /usr/include/CC/generic.h /usr/include/CC/stdiostream.h
../Bud/Bud.o: /usr/include/CC/fstream.h ../../c++adt/include/TMatrixI.h
../Bud/Bud.o: ../include/LGMdecl.h ../include/LGMSymbols.h
../Bud/Bud.o: /usr/include/CC/map /usr/include/CC/stl_tree.h
../Bud/Bud.o: /usr/include/CC/stl_function.h /usr/include/CC/stl_map.h
../Bud/Bud.o: /usr/include/CC/stl_multimap.h ../include/LGMUnits.h
../Bud/Bud.o: ../include/BudI.h
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
../TreeMetaFileParser/TreeMetaFileParser.o: /usr/include/CC/fstream.h
../TreeMetaFileParser/TreeMetaFileParser.o: /usr/include/CC/iostream.h
../TreeMetaFileParser/TreeMetaFileParser.o: /usr/include/memory.h
../TreeMetaFileParser/TreeMetaFileParser.o: /usr/include/stddef.h
../TreeMetaFileParser/TreeMetaFileParser.o: ../../c++adt/include/CString.h
../TreeMetaFileParser/TreeMetaFileParser.o: /usr/include/string.h
../TreeMetaFileParser/TreeMetaFileParser.o: /usr/include/stdio.h
../TreeMetaFileParser/TreeMetaFileParser.o: /usr/include/ctype.h
../TreeMetaFileParser/TreeMetaFileParser.o: /usr/include/locale_attr.h
../TreeMetaFileParser/TreeMetaFileParser.o: /usr/include/CC/stream.h
../TreeMetaFileParser/TreeMetaFileParser.o: /usr/include/CC/iomanip.h
../TreeMetaFileParser/TreeMetaFileParser.o: /usr/include/CC/generic.h
../TreeMetaFileParser/TreeMetaFileParser.o: /usr/include/CC/stdiostream.h
../TreeSegment/BroadLeaf.o: ../include/BroadLeaf.h
../TreeSegment/BroadLeaf.o: ../../c++adt/include/Point.h /usr/include/math.h
../TreeSegment/BroadLeaf.o: /usr/include/sgidefs.h /usr/include/standards.h
../TreeSegment/BroadLeaf.o: /usr/include/CC/iostream.h /usr/include/memory.h
../TreeSegment/BroadLeaf.o: /usr/include/stddef.h
../TreeSegment/BroadLeaf.o: ../../c++adt/include/PointI.h
../TreeSegment/BroadLeaf.o: ../../c++adt/include/PositionVector.h
../TreeSegment/BroadLeaf.o: ../../c++adt/include/mathsym.h
../TreeSegment/BroadLeaf.o: /usr/include/CC/vector
../TreeSegment/BroadLeaf.o: /usr/include/CC/stl_range_errors.h
../TreeSegment/BroadLeaf.o: /usr/include/CC/stl_config.h
../TreeSegment/BroadLeaf.o: /usr/include/CC/stl_algobase.h
../TreeSegment/BroadLeaf.o: /usr/include/CC/stl_relops.h
../TreeSegment/BroadLeaf.o: /usr/include/CC/stl_pair.h
../TreeSegment/BroadLeaf.o: /usr/include/CC/type_traits.h
../TreeSegment/BroadLeaf.o: /usr/include/string.h /usr/include/limits.h
../TreeSegment/BroadLeaf.o: /usr/include/stdlib.h /usr/include/CC/new.h
../TreeSegment/BroadLeaf.o: /usr/include/CC/stl_iterator_base.h
../TreeSegment/BroadLeaf.o: /usr/include/CC/stl_iterator.h
../TreeSegment/BroadLeaf.o: /usr/include/CC/stl_alloc.h /usr/include/stdio.h
../TreeSegment/BroadLeaf.o: /usr/include/assert.h
../TreeSegment/BroadLeaf.o: /usr/include/CC/stl_construct.h
../TreeSegment/BroadLeaf.o: /usr/include/CC/stl_uninitialized.h
../TreeSegment/BroadLeaf.o: /usr/include/CC/stl_vector.h
../TreeSegment/BroadLeaf.o: /usr/include/CC/stl_bvector.h
../TreeSegment/BroadLeaf.o: ../../c++adt/include/RMatrix.h
../TreeSegment/BroadLeaf.o: ../../c++adt/include/TMatrix.h
../TreeSegment/BroadLeaf.o: /usr/include/CC/stream.h
../TreeSegment/BroadLeaf.o: /usr/include/CC/iomanip.h
../TreeSegment/BroadLeaf.o: /usr/include/CC/generic.h
../TreeSegment/BroadLeaf.o: /usr/include/CC/stdiostream.h
../TreeSegment/BroadLeaf.o: /usr/include/CC/fstream.h
../TreeSegment/BroadLeaf.o: ../../c++adt/include/TMatrixI.h
../TreeSegment/BroadLeaf.o: ../../c++adt/include/Ellipsis.h
../TreeSegment/BroadLeaf.o: ../include/LGMdecl.h ../include/LGMSymbols.h
../TreeSegment/BroadLeaf.o: /usr/include/CC/map /usr/include/CC/stl_tree.h
../TreeSegment/BroadLeaf.o: /usr/include/CC/stl_function.h
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
../TreeSegment/TreeSegmentFriend.o: /usr/include/CC/stl_construct.h
../TreeSegment/TreeSegmentFriend.o: /usr/include/CC/stl_uninitialized.h
../TreeSegment/TreeSegmentFriend.o: /usr/include/CC/stl_list.h
../TreeSegment/TreeSegmentFriend.o: ../../c++adt/include/mathsym.h
../TreeSegment/TreeSegmentFriend.o: ../../c++adt/include/Point.h
../TreeSegment/TreeSegmentFriend.o: /usr/include/math.h
../TreeSegment/TreeSegmentFriend.o: ../../c++adt/include/PointI.h
../TreeSegment/TreeSegmentFriend.o: ../../c++adt/include/PositionVector.h
../TreeSegment/TreeSegmentFriend.o: /usr/include/CC/vector
../TreeSegment/TreeSegmentFriend.o: /usr/include/CC/stl_range_errors.h
../TreeSegment/TreeSegmentFriend.o: /usr/include/CC/stl_vector.h
../TreeSegment/TreeSegmentFriend.o: /usr/include/CC/stl_bvector.h
../TreeSegment/TreeSegmentFriend.o: ../../c++adt/include/RMatrix.h
../TreeSegment/TreeSegmentFriend.o: ../../c++adt/include/TMatrix.h
../TreeSegment/TreeSegmentFriend.o: /usr/include/CC/stream.h
../TreeSegment/TreeSegmentFriend.o: /usr/include/CC/iomanip.h
../TreeSegment/TreeSegmentFriend.o: /usr/include/CC/generic.h
../TreeSegment/TreeSegmentFriend.o: /usr/include/CC/stdiostream.h
../TreeSegment/TreeSegmentFriend.o: /usr/include/CC/fstream.h
../TreeSegment/TreeSegmentFriend.o: ../../c++adt/include/TMatrixI.h
../TreeSegment/TreeSegmentFriend.o: ../include/LGMdecl.h
../TreeSegment/TreeSegmentFriend.o: ../include/LGMSymbols.h
../TreeSegment/TreeSegmentFriend.o: /usr/include/CC/map
../TreeSegment/TreeSegmentFriend.o: /usr/include/CC/stl_tree.h
../TreeSegment/TreeSegmentFriend.o: /usr/include/CC/stl_function.h
../TreeSegment/TreeSegmentFriend.o: /usr/include/CC/stl_map.h
../TreeSegment/TreeSegmentFriend.o: /usr/include/CC/stl_multimap.h
../TreeSegment/TreeSegmentFriend.o: ../include/LGMUnits.h
../TreeSegment/TreeSegmentFriend.o: ../include/TreeSegmentI.h
../TreeSegment/TreeSegmentFriend.o: ../include/TreeSegmentMetabolismI.h
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
../TreeSegment/TreeSegment.o: /usr/include/CC/stl_construct.h
../TreeSegment/TreeSegment.o: /usr/include/CC/stl_uninitialized.h
../TreeSegment/TreeSegment.o: /usr/include/CC/stl_list.h
../TreeSegment/TreeSegment.o: ../../c++adt/include/mathsym.h
../TreeSegment/TreeSegment.o: ../../c++adt/include/Point.h
../TreeSegment/TreeSegment.o: /usr/include/math.h
../TreeSegment/TreeSegment.o: ../../c++adt/include/PointI.h
../TreeSegment/TreeSegment.o: ../../c++adt/include/PositionVector.h
../TreeSegment/TreeSegment.o: /usr/include/CC/vector
../TreeSegment/TreeSegment.o: /usr/include/CC/stl_range_errors.h
../TreeSegment/TreeSegment.o: /usr/include/CC/stl_vector.h
../TreeSegment/TreeSegment.o: /usr/include/CC/stl_bvector.h
../TreeSegment/TreeSegment.o: ../../c++adt/include/RMatrix.h
../TreeSegment/TreeSegment.o: ../../c++adt/include/TMatrix.h
../TreeSegment/TreeSegment.o: /usr/include/CC/stream.h
../TreeSegment/TreeSegment.o: /usr/include/CC/iomanip.h
../TreeSegment/TreeSegment.o: /usr/include/CC/generic.h
../TreeSegment/TreeSegment.o: /usr/include/CC/stdiostream.h
../TreeSegment/TreeSegment.o: /usr/include/CC/fstream.h
../TreeSegment/TreeSegment.o: ../../c++adt/include/TMatrixI.h
../TreeSegment/TreeSegment.o: ../include/LGMdecl.h ../include/LGMSymbols.h
../TreeSegment/TreeSegment.o: /usr/include/CC/map /usr/include/CC/stl_tree.h
../TreeSegment/TreeSegment.o: /usr/include/CC/stl_function.h
../TreeSegment/TreeSegment.o: /usr/include/CC/stl_map.h
../TreeSegment/TreeSegment.o: /usr/include/CC/stl_multimap.h
../TreeSegment/TreeSegment.o: ../include/LGMUnits.h ../include/TreeSegmentI.h
../TreeSegment/TreeSegment.o: ../include/TreeSegmentMetabolismI.h
../TreeCompartment/TreeCompartmentFriend.o: ../include/TreeCompartment.h
../TreeCompartment/TreeCompartmentFriend.o: ../../c++adt/include/Point.h
../TreeCompartment/TreeCompartmentFriend.o: /usr/include/math.h
../TreeCompartment/TreeCompartmentFriend.o: /usr/include/sgidefs.h
../TreeCompartment/TreeCompartmentFriend.o: /usr/include/standards.h
../TreeCompartment/TreeCompartmentFriend.o: /usr/include/CC/iostream.h
../TreeCompartment/TreeCompartmentFriend.o: /usr/include/memory.h
../TreeCompartment/TreeCompartmentFriend.o: /usr/include/stddef.h
../TreeCompartment/TreeCompartmentFriend.o: ../../c++adt/include/PointI.h
../TreeCompartment/TreeCompartmentFriend.o: ../../c++adt/include/PositionVector.h
../TreeCompartment/TreeCompartmentFriend.o: ../../c++adt/include/mathsym.h
../TreeCompartment/TreeCompartmentFriend.o: /usr/include/CC/vector
../TreeCompartment/TreeCompartmentFriend.o: /usr/include/CC/stl_range_errors.h
../TreeCompartment/TreeCompartmentFriend.o: /usr/include/CC/stl_config.h
../TreeCompartment/TreeCompartmentFriend.o: /usr/include/CC/stl_algobase.h
../TreeCompartment/TreeCompartmentFriend.o: /usr/include/CC/stl_relops.h
../TreeCompartment/TreeCompartmentFriend.o: /usr/include/CC/stl_pair.h
../TreeCompartment/TreeCompartmentFriend.o: /usr/include/CC/type_traits.h
../TreeCompartment/TreeCompartmentFriend.o: /usr/include/string.h
../TreeCompartment/TreeCompartmentFriend.o: /usr/include/limits.h
../TreeCompartment/TreeCompartmentFriend.o: /usr/include/stdlib.h
../TreeCompartment/TreeCompartmentFriend.o: /usr/include/CC/new.h
../TreeCompartment/TreeCompartmentFriend.o: /usr/include/CC/stl_iterator_base.h
../TreeCompartment/TreeCompartmentFriend.o: /usr/include/CC/stl_iterator.h
../TreeCompartment/TreeCompartmentFriend.o: /usr/include/CC/stl_alloc.h
../TreeCompartment/TreeCompartmentFriend.o: /usr/include/stdio.h
../TreeCompartment/TreeCompartmentFriend.o: /usr/include/assert.h
../TreeCompartment/TreeCompartmentFriend.o: /usr/include/CC/stl_construct.h
../TreeCompartment/TreeCompartmentFriend.o: /usr/include/CC/stl_uninitialized.h
../TreeCompartment/TreeCompartmentFriend.o: /usr/include/CC/stl_vector.h
../TreeCompartment/TreeCompartmentFriend.o: /usr/include/CC/stl_bvector.h
../TreeCompartment/TreeCompartmentFriend.o: ../../c++adt/include/RMatrix.h
../TreeCompartment/TreeCompartmentFriend.o: ../../c++adt/include/TMatrix.h
../TreeCompartment/TreeCompartmentFriend.o: /usr/include/CC/stream.h
../TreeCompartment/TreeCompartmentFriend.o: /usr/include/CC/iomanip.h
../TreeCompartment/TreeCompartmentFriend.o: /usr/include/CC/generic.h
../TreeCompartment/TreeCompartmentFriend.o: /usr/include/CC/stdiostream.h
../TreeCompartment/TreeCompartmentFriend.o: /usr/include/CC/fstream.h
../TreeCompartment/TreeCompartmentFriend.o: ../../c++adt/include/TMatrixI.h
../TreeCompartment/TreeCompartmentFriend.o: ../include/LGMdecl.h
../TreeCompartment/TreeCompartmentFriend.o: ../include/LGMSymbols.h
../TreeCompartment/TreeCompartmentFriend.o: /usr/include/CC/map
../TreeCompartment/TreeCompartmentFriend.o: /usr/include/CC/stl_tree.h
../TreeCompartment/TreeCompartmentFriend.o: /usr/include/CC/stl_function.h
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
../Tree/TreeFriend.o: /usr/include/assert.h /usr/include/CC/stl_list.h
../Tree/TreeFriend.o: /usr/include/CC/stream.h /usr/include/CC/iomanip.h
../Tree/TreeFriend.o: /usr/include/CC/generic.h /usr/include/CC/stdiostream.h
../Tree/TreeFriend.o: /usr/include/CC/fstream.h
../Tree/TreeFriend.o: ../../c++adt/include/CString.h /usr/include/ctype.h
../Tree/TreeFriend.o: /usr/include/locale_attr.h
../Tree/TreeFriend.o: ../../c++adt/include/ParametricCurve.h
../Tree/TreeFriend.o: /usr/include/CC/vector
../Tree/TreeFriend.o: /usr/include/CC/stl_range_errors.h
../Tree/TreeFriend.o: /usr/include/CC/stl_vector.h
../Tree/TreeFriend.o: /usr/include/CC/stl_bvector.h /usr/include/float.h
../Tree/TreeFriend.o: ../../c++adt/include/Point.h /usr/include/math.h
../Tree/TreeFriend.o: ../../c++adt/include/PointI.h
../Tree/TreeFriend.o: ../../c++adt/include/PositionVector.h
../Tree/TreeFriend.o: ../../c++adt/include/mathsym.h
../Tree/TreeFriend.o: ../../c++adt/include/RMatrix.h
../Tree/TreeFriend.o: ../../c++adt/include/TMatrix.h
../Tree/TreeFriend.o: ../../c++adt/include/TMatrixI.h ../include/Algorithms.h
../Tree/TreeFriend.o: /usr/include/CC/functional ../include/LGMdecl.h
../Tree/TreeFriend.o: ../include/LGMSymbols.h /usr/include/CC/map
../Tree/TreeFriend.o: /usr/include/CC/stl_tree.h /usr/include/CC/stl_map.h
../Tree/TreeFriend.o: /usr/include/CC/stl_multimap.h ../include/LGMUnits.h
../Tree/TreeFriend.o: ../include/AlgorithmsI.h ../include/TreeFunctor.h
../Tree/TreeFriend.o: ../include/TreeCompartment.h
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
../Tree/TreeFriend.o: ../include/TreeSegmentI.h
../Tree/TreeFriend.o: ../include/TreeSegmentMetabolismI.h
../Tree/TreeFriend.o: ../include/HwTreeSegment.h ../include/BroadLeaf.h
../Tree/TreeFriend.o: ../../c++adt/include/Ellipsis.h
../Tree/TreeFriend.o: ../../Firmament/include/Firmament.h
../Tree/TreeFriend.o: ../include/HwTreeSegmentI.h ../include/CfTreeSegment.h
../Tree/TreeFriend.o: ../include/Axis.h ../include/AxisI.h
../Tree/TreeFriend.o: ../../c++adt/include/ConnectionMatrix.h
../Tree/TreeFriend.o: ../../c++adt/include/ConnectionMatrixI.h
../Tree/TreeFriend.o: ../include/TreeI.h ../include/TreeMetabolismI.h
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
../Tree/Tree.o: /usr/include/CC/stl_list.h /usr/include/CC/stream.h
../Tree/Tree.o: /usr/include/CC/iomanip.h /usr/include/CC/generic.h
../Tree/Tree.o: /usr/include/CC/stdiostream.h /usr/include/CC/fstream.h
../Tree/Tree.o: ../../c++adt/include/CString.h /usr/include/ctype.h
../Tree/Tree.o: /usr/include/locale_attr.h
../Tree/Tree.o: ../../c++adt/include/ParametricCurve.h /usr/include/CC/vector
../Tree/Tree.o: /usr/include/CC/stl_range_errors.h
../Tree/Tree.o: /usr/include/CC/stl_vector.h /usr/include/CC/stl_bvector.h
../Tree/Tree.o: /usr/include/float.h ../../c++adt/include/Point.h
../Tree/Tree.o: /usr/include/math.h ../../c++adt/include/PointI.h
../Tree/Tree.o: ../../c++adt/include/PositionVector.h
../Tree/Tree.o: ../../c++adt/include/mathsym.h ../../c++adt/include/RMatrix.h
../Tree/Tree.o: ../../c++adt/include/TMatrix.h
../Tree/Tree.o: ../../c++adt/include/TMatrixI.h ../include/Algorithms.h
../Tree/Tree.o: /usr/include/CC/functional ../include/LGMdecl.h
../Tree/Tree.o: ../include/LGMSymbols.h /usr/include/CC/map
../Tree/Tree.o: /usr/include/CC/stl_tree.h /usr/include/CC/stl_map.h
../Tree/Tree.o: /usr/include/CC/stl_multimap.h ../include/LGMUnits.h
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
../Tree/Tree.o: ../include/TreeSegmentMetabolismI.h
../Tree/Tree.o: ../include/HwTreeSegment.h ../include/BroadLeaf.h
../Tree/Tree.o: ../../c++adt/include/Ellipsis.h
../Tree/Tree.o: ../../Firmament/include/Firmament.h
../Tree/Tree.o: ../include/HwTreeSegmentI.h ../include/CfTreeSegment.h
../Tree/Tree.o: ../include/Axis.h ../include/AxisI.h
../Tree/Tree.o: ../../c++adt/include/ConnectionMatrix.h
../Tree/Tree.o: ../../c++adt/include/ConnectionMatrixI.h ../include/TreeI.h
../Tree/Tree.o: ../include/TreeMetabolismI.h
