SRC = ../Axis/AxisFriend.cc  \
      ../BranchingPoint/BranchingPointFriend.cc \
      ../Bud/BudFriend.cc \
      ../Bud/Bud.cc \
      ../TreeMetaFileParser/TreeMetaFileParser.cc \
      ../TreeSegment/TreeSegmentFriend.cc \
      ../TreeSegment/TreeSegment.cc \
      ../TreeCompartment/TreeCompartmentFriend.cc\
      ../Tree/TreeFriend.cc \
      ../Tree/Tree.cc 
  
OBJ = ../Axis/AxisFriend.o \
      ../BranchingPoint/BranchingPointFriend.o \
      ../Bud/BudFriend.o \
      ../Bud/Bud.o \
      ../TreeMetaFileParser/TreeMetaFileParser.o \
      ../TreeSegment/TreeSegmentFriend.o \
      ../TreeSegment/TreeSegment.o \
      ../TreeCompartment/TreeCompartmentFriend.o \
      ../Tree/TreeFriend.o \
      ../Tree/Tree.o 

INCLUDE = -I../include  -I../../c++adt/include
STL = -I/usr/include/CC
CCC = CC -64
ETAGS = etags -d -T -C -o

OPTIMIZE = -O
CCCFLAGS =   -c   

.SUFFIXES: .o .cc

AR = $(CCC) -ar  
ARFLAGS = -o 
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
../Axis/AxisFriend.o: /usr/include/math.h
../Axis/AxisFriend.o: ../../c++adt/include/PositionVector.h
../Axis/AxisFriend.o: ../../c++adt/include/mathsym.h /usr/include/CC/vector
../Axis/AxisFriend.o: /usr/include/CC/stl_range_errors.h
../Axis/AxisFriend.o: /usr/include/CC/stl_vector.h
../Axis/AxisFriend.o: /usr/include/CC/stl_bvector.h
../Axis/AxisFriend.o: ../../c++adt/include/RMatrix.h
../Axis/AxisFriend.o: ../../c++adt/include/TMatrix.h /usr/include/CC/stream.h
../Axis/AxisFriend.o: /usr/include/CC/iomanip.h /usr/include/CC/generic.h
../Axis/AxisFriend.o: /usr/include/CC/stdiostream.h /usr/include/CC/fstream.h
../Axis/AxisFriend.o: ../include/TreeCompartment.h ../include/LGMdecl.h
../Axis/AxisFriend.o: ../include/LGMSymbols.h /usr/include/CC/map
../Axis/AxisFriend.o: /usr/include/CC/stl_tree.h
../Axis/AxisFriend.o: /usr/include/CC/stl_function.h
../Axis/AxisFriend.o: /usr/include/CC/stl_map.h
../Axis/AxisFriend.o: /usr/include/CC/stl_multimap.h ../include/LGMUnits.h
../Axis/AxisFriend.o: ../include/Bud.h ../include/TreeSegment.h
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
../BranchingPoint/BranchingPointFriend.o: ../include/TreeCompartment.h
../BranchingPoint/BranchingPointFriend.o: ../include/LGMdecl.h
../BranchingPoint/BranchingPointFriend.o: ../include/LGMSymbols.h
../BranchingPoint/BranchingPointFriend.o: /usr/include/CC/map
../BranchingPoint/BranchingPointFriend.o: /usr/include/CC/stl_tree.h
../BranchingPoint/BranchingPointFriend.o: /usr/include/CC/stl_function.h
../BranchingPoint/BranchingPointFriend.o: /usr/include/CC/stl_map.h
../BranchingPoint/BranchingPointFriend.o: /usr/include/CC/stl_multimap.h
../BranchingPoint/BranchingPointFriend.o: ../include/LGMUnits.h
../BranchingPoint/BranchingPointFriend.o: ../../c++adt/include/Point.h
../BranchingPoint/BranchingPointFriend.o: /usr/include/math.h
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
../BranchingPoint/BranchingPointFriend.o: ../include/Axis.h ../include/Bud.h
../BranchingPoint/BranchingPointFriend.o: ../include/TreeSegment.h
../Bud/BudFriend.o: ../include/Bud.h ../include/TreeSegment.h
../Bud/BudFriend.o: /usr/include/CC/list /usr/include/CC/stl_algobase.h
../Bud/BudFriend.o: /usr/include/CC/stl_config.h /usr/include/standards.h
../Bud/BudFriend.o: /usr/include/CC/stl_relops.h /usr/include/CC/stl_pair.h
../Bud/BudFriend.o: /usr/include/CC/type_traits.h /usr/include/string.h
../Bud/BudFriend.o: /usr/include/limits.h /usr/include/sgidefs.h
../Bud/BudFriend.o: /usr/include/stdlib.h /usr/include/stddef.h
../Bud/BudFriend.o: /usr/include/CC/new.h /usr/include/CC/iostream.h
../Bud/BudFriend.o: /usr/include/memory.h /usr/include/CC/stl_iterator_base.h
../Bud/BudFriend.o: /usr/include/CC/stl_iterator.h
../Bud/BudFriend.o: /usr/include/CC/stl_alloc.h /usr/include/stdio.h
../Bud/BudFriend.o: /usr/include/assert.h /usr/include/CC/stl_construct.h
../Bud/BudFriend.o: /usr/include/CC/stl_uninitialized.h
../Bud/BudFriend.o: /usr/include/CC/stl_list.h ../../c++adt/include/Point.h
../Bud/BudFriend.o: /usr/include/math.h ../include/TreeCompartment.h
../Bud/BudFriend.o: ../include/LGMdecl.h ../include/LGMSymbols.h
../Bud/BudFriend.o: /usr/include/CC/map /usr/include/CC/stl_tree.h
../Bud/BudFriend.o: /usr/include/CC/stl_function.h /usr/include/CC/stl_map.h
../Bud/BudFriend.o: /usr/include/CC/stl_multimap.h ../include/LGMUnits.h
../Bud/BudFriend.o: ../../c++adt/include/PositionVector.h
../Bud/BudFriend.o: ../../c++adt/include/mathsym.h /usr/include/CC/vector
../Bud/BudFriend.o: /usr/include/CC/stl_range_errors.h
../Bud/BudFriend.o: /usr/include/CC/stl_vector.h
../Bud/BudFriend.o: /usr/include/CC/stl_bvector.h
../Bud/BudFriend.o: ../../c++adt/include/RMatrix.h
../Bud/BudFriend.o: ../../c++adt/include/TMatrix.h /usr/include/CC/stream.h
../Bud/BudFriend.o: /usr/include/CC/iomanip.h /usr/include/CC/generic.h
../Bud/BudFriend.o: /usr/include/CC/stdiostream.h /usr/include/CC/fstream.h
../TreeMetaFileParser/TreeMetaFileParser.o: ../include/TreeMetaFileParser.h
../TreeMetaFileParser/TreeMetaFileParser.o: /usr/include/stdlib.h
../TreeMetaFileParser/TreeMetaFileParser.o: /usr/include/standards.h
../TreeMetaFileParser/TreeMetaFileParser.o: /usr/include/sgidefs.h
../TreeMetaFileParser/TreeMetaFileParser.o: ../../c++adt/include/Table.h
../TreeMetaFileParser/TreeMetaFileParser.o: ../../c++adt/include/DList.h
../TreeMetaFileParser/TreeMetaFileParser.o: ../../c++adt/include/DListElement.h
../TreeMetaFileParser/TreeMetaFileParser.o: ../../c++adt/include/boolean.h
../TreeMetaFileParser/TreeMetaFileParser.o: ../../c++adt/include/Lex.h
../TreeMetaFileParser/TreeMetaFileParser.o: ../../c++adt/include/CString.h
../TreeMetaFileParser/TreeMetaFileParser.o: /usr/include/string.h
../TreeMetaFileParser/TreeMetaFileParser.o: /usr/include/stdio.h
../TreeMetaFileParser/TreeMetaFileParser.o: /usr/include/ctype.h
../TreeMetaFileParser/TreeMetaFileParser.o: /usr/include/locale_attr.h
../TreeMetaFileParser/TreeMetaFileParser.o: /usr/include/CC/stream.h
../TreeMetaFileParser/TreeMetaFileParser.o: /usr/include/CC/iostream.h
../TreeMetaFileParser/TreeMetaFileParser.o: /usr/include/memory.h
../TreeMetaFileParser/TreeMetaFileParser.o: /usr/include/stddef.h
../TreeMetaFileParser/TreeMetaFileParser.o: /usr/include/CC/iomanip.h
../TreeMetaFileParser/TreeMetaFileParser.o: /usr/include/CC/generic.h
../TreeMetaFileParser/TreeMetaFileParser.o: /usr/include/CC/stdiostream.h
../TreeMetaFileParser/TreeMetaFileParser.o: /usr/include/CC/fstream.h
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
../TreeSegment/TreeSegmentFriend.o: ../../c++adt/include/Point.h
../TreeSegment/TreeSegmentFriend.o: /usr/include/math.h
../TreeSegment/TreeSegmentFriend.o: ../include/TreeCompartment.h
../TreeSegment/TreeSegmentFriend.o: ../include/LGMdecl.h
../TreeSegment/TreeSegmentFriend.o: ../include/LGMSymbols.h
../TreeSegment/TreeSegmentFriend.o: /usr/include/CC/map
../TreeSegment/TreeSegmentFriend.o: /usr/include/CC/stl_tree.h
../TreeSegment/TreeSegmentFriend.o: /usr/include/CC/stl_function.h
../TreeSegment/TreeSegmentFriend.o: /usr/include/CC/stl_map.h
../TreeSegment/TreeSegmentFriend.o: /usr/include/CC/stl_multimap.h
../TreeSegment/TreeSegmentFriend.o: ../include/LGMUnits.h
../TreeSegment/TreeSegmentFriend.o: ../../c++adt/include/PositionVector.h
../TreeSegment/TreeSegmentFriend.o: ../../c++adt/include/mathsym.h
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
../TreeCompartment/TreeCompartmentFriend.o: ../include/TreeCompartment.h
../TreeCompartment/TreeCompartmentFriend.o: ../include/LGMdecl.h
../TreeCompartment/TreeCompartmentFriend.o: ../include/LGMSymbols.h
../TreeCompartment/TreeCompartmentFriend.o: /usr/include/CC/map
../TreeCompartment/TreeCompartmentFriend.o: /usr/include/CC/stl_tree.h
../TreeCompartment/TreeCompartmentFriend.o: /usr/include/CC/stl_algobase.h
../TreeCompartment/TreeCompartmentFriend.o: /usr/include/CC/stl_config.h
../TreeCompartment/TreeCompartmentFriend.o: /usr/include/standards.h
../TreeCompartment/TreeCompartmentFriend.o: /usr/include/CC/stl_relops.h
../TreeCompartment/TreeCompartmentFriend.o: /usr/include/CC/stl_pair.h
../TreeCompartment/TreeCompartmentFriend.o: /usr/include/CC/type_traits.h
../TreeCompartment/TreeCompartmentFriend.o: /usr/include/string.h
../TreeCompartment/TreeCompartmentFriend.o: /usr/include/limits.h
../TreeCompartment/TreeCompartmentFriend.o: /usr/include/sgidefs.h
../TreeCompartment/TreeCompartmentFriend.o: /usr/include/stdlib.h
../TreeCompartment/TreeCompartmentFriend.o: /usr/include/stddef.h
../TreeCompartment/TreeCompartmentFriend.o: /usr/include/CC/new.h
../TreeCompartment/TreeCompartmentFriend.o: /usr/include/CC/iostream.h
../TreeCompartment/TreeCompartmentFriend.o: /usr/include/memory.h
../TreeCompartment/TreeCompartmentFriend.o: /usr/include/CC/stl_iterator_base.h
../TreeCompartment/TreeCompartmentFriend.o: /usr/include/CC/stl_iterator.h
../TreeCompartment/TreeCompartmentFriend.o: /usr/include/CC/stl_alloc.h
../TreeCompartment/TreeCompartmentFriend.o: /usr/include/stdio.h
../TreeCompartment/TreeCompartmentFriend.o: /usr/include/assert.h
../TreeCompartment/TreeCompartmentFriend.o: /usr/include/CC/stl_construct.h
../TreeCompartment/TreeCompartmentFriend.o: /usr/include/CC/stl_function.h
../TreeCompartment/TreeCompartmentFriend.o: /usr/include/CC/stl_map.h
../TreeCompartment/TreeCompartmentFriend.o: /usr/include/CC/stl_multimap.h
../TreeCompartment/TreeCompartmentFriend.o: ../include/LGMUnits.h
../TreeCompartment/TreeCompartmentFriend.o: ../../c++adt/include/Point.h
../TreeCompartment/TreeCompartmentFriend.o: /usr/include/math.h
../TreeCompartment/TreeCompartmentFriend.o: ../../c++adt/include/PositionVector.h
../TreeCompartment/TreeCompartmentFriend.o: ../../c++adt/include/mathsym.h
../TreeCompartment/TreeCompartmentFriend.o: /usr/include/CC/vector
../TreeCompartment/TreeCompartmentFriend.o: /usr/include/CC/stl_range_errors.h
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
../Tree/TreeFriend.o: ../include/Tree.h /usr/include/CC/list
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
../Tree/TreeFriend.o: /usr/include/CC/stl_alloc.h /usr/include/stdio.h
../Tree/TreeFriend.o: /usr/include/assert.h /usr/include/CC/stl_construct.h
../Tree/TreeFriend.o: /usr/include/CC/stl_uninitialized.h
../Tree/TreeFriend.o: /usr/include/CC/stl_list.h
../Tree/TreeFriend.o: ../../c++adt/include/CString.h /usr/include/ctype.h
../Tree/TreeFriend.o: /usr/include/locale_attr.h /usr/include/CC/stream.h
../Tree/TreeFriend.o: /usr/include/CC/iomanip.h /usr/include/CC/generic.h
../Tree/TreeFriend.o: /usr/include/CC/stdiostream.h /usr/include/CC/fstream.h
../Tree/TreeFriend.o: ../../c++adt/include/ParametricCurve.h
../Tree/TreeFriend.o: /usr/include/CC/vector
../Tree/TreeFriend.o: /usr/include/CC/stl_range_errors.h
../Tree/TreeFriend.o: /usr/include/CC/stl_vector.h
../Tree/TreeFriend.o: /usr/include/CC/stl_bvector.h /usr/include/float.h
../Tree/TreeFriend.o: ../include/TreeMetaFileParser.h
../Tree/TreeFriend.o: ../../c++adt/include/Table.h
../Tree/TreeFriend.o: ../../c++adt/include/DList.h
../Tree/TreeFriend.o: ../../c++adt/include/DListElement.h
../Tree/TreeFriend.o: ../../c++adt/include/boolean.h
../Tree/TreeFriend.o: ../../c++adt/include/Lex.h ../include/RootSystem.h
../Tree/TreeFriend.o: ../include/LGMSymbols.h /usr/include/CC/map
../Tree/TreeFriend.o: /usr/include/CC/stl_tree.h
../Tree/TreeFriend.o: /usr/include/CC/stl_function.h
../Tree/TreeFriend.o: /usr/include/CC/stl_map.h
../Tree/TreeFriend.o: /usr/include/CC/stl_multimap.h ../include/Bud.h
../Tree/TreeFriend.o: ../include/TreeSegment.h ../../c++adt/include/Point.h
../Tree/TreeFriend.o: /usr/include/math.h ../include/TreeCompartment.h
../Tree/TreeFriend.o: ../include/LGMdecl.h ../include/LGMUnits.h
../Tree/TreeFriend.o: ../../c++adt/include/PositionVector.h
../Tree/TreeFriend.o: ../../c++adt/include/mathsym.h
../Tree/TreeFriend.o: ../../c++adt/include/RMatrix.h
../Tree/TreeFriend.o: ../../c++adt/include/TMatrix.h
../Tree/TreeFriend.o: ../include/BranchingPoint.h ../include/Axis.h
