SRC = ../Axis/AxisFriend.cc ../Axis/Axis.cc \
      ../BranchingPoint/BranchingPointFriend.cc \
      ../BranchingPoint/BranchingPoint.cc \
      ../Bud/Bud.cc ../Bud/BudFriend.cc \
      ../Tree/Tree.cc ../Tree/TreeFriend.cc \
      ../TreeMetaFileParser/TreeMetaFileParser.cc \
      ../TreeSegment/TreeSegment.cc \
      ../TreeSegment/TreeSegmentFriend.cc \
      ../TreeCompartment/TreeCompartment.cc \
      ../TreeCompartment/TreeCompartmentFriend.cc
 
OBJ = ../Axis/AxisFriend.o ../Axis/Axis.o \
      ../BranchingPoint/BranchingPointFriend.o \
      ../BranchingPoint/BranchingPoint.o \
      ../Bud/Bud.o ../Bud/BudFriend.o \
      ../Tree/Tree.o  ../Tree/TreeFriend.o \
      ../TreeMetaFileParser/TreeMetaFileParser.o \
      ../TreeSegment/TreeSegment.o \
      ../TreeSegment/TreeSegmentFriend.o \
      ../TreeCompartment/TreeCompartment.o \
      ../TreeCompartment/TreeCompartmentFriend.o

INCLUDE = -I../include  -I../../c++adt/include
STL = -I/usr/include/CC
CCC = CC -64
ETAGS = etags -d -T -C -o

OPTIMIZE = -O
CCCFLAGS =   -c   

.SUFFIXES: .o .cc

AR = ar  
ARFLAGS = cvr
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
../Axis/AxisFriend.o: /usr/include/CC/stl_config.h
../Axis/AxisFriend.o: /usr/include/CC/stl_relops.h /usr/include/CC/stl_pair.h
../Axis/AxisFriend.o: /usr/include/CC/type_traits.h /usr/include/string.h
../Axis/AxisFriend.o: /usr/include/standards.h /usr/include/limits.h
../Axis/AxisFriend.o: /usr/include/sgidefs.h /usr/include/stdlib.h
../Axis/AxisFriend.o: /usr/include/stddef.h /usr/include/CC/new.h
../Axis/AxisFriend.o: /usr/include/CC/iostream.h /usr/include/memory.h
../Axis/AxisFriend.o: /usr/include/CC/stl_iterator.h
../Axis/AxisFriend.o: /usr/include/CC/stl_alloc.h /usr/include/assert.h
../Axis/AxisFriend.o: /usr/include/mutex.h /usr/include/time.h
../Axis/AxisFriend.o: /usr/include/CC/stl_construct.h
../Axis/AxisFriend.o: /usr/include/CC/stl_uninitialized.h
../Axis/AxisFriend.o: /usr/include/CC/stl_list.h ../../c++adt/include/Point.h
../Axis/AxisFriend.o: /usr/include/math.h
../Axis/AxisFriend.o: ../../c++adt/include/PositionVector.h
../Axis/AxisFriend.o: ../../c++adt/include/mathsym.h /usr/include/CC/vector
../Axis/AxisFriend.o: /usr/include/CC/stl_vector.h
../Axis/AxisFriend.o: /usr/include/CC/stl_bvector.h
../Axis/AxisFriend.o: ../../c++adt/include/RMatrix.h
../Axis/AxisFriend.o: ../../c++adt/include/TMatrix.h /usr/include/CC/stream.h
../Axis/AxisFriend.o: /usr/include/CC/iomanip.h /usr/include/CC/generic.h
../Axis/AxisFriend.o: /usr/include/CC/stdiostream.h /usr/include/stdio.h
../Axis/AxisFriend.o: /usr/include/CC/fstream.h ../include/TreeCompartment.h
../Axis/AxisFriend.o: ../include/LGMUnits.h ../include/Bud.h
../Axis/AxisFriend.o: ../include/LGMSymbols.h /usr/include/CC/map
../Axis/AxisFriend.o: /usr/include/CC/stl_tree.h
../Axis/AxisFriend.o: /usr/include/CC/stl_function.h
../Axis/AxisFriend.o: /usr/include/CC/stl_map.h
../Axis/AxisFriend.o: /usr/include/CC/stl_multimap.h ../include/TreeSegment.h
../Axis/Axis.o: ../include/Axis.h /usr/include/CC/list
../Axis/Axis.o: /usr/include/CC/stl_algobase.h /usr/include/CC/stl_config.h
../Axis/Axis.o: /usr/include/CC/stl_relops.h /usr/include/CC/stl_pair.h
../Axis/Axis.o: /usr/include/CC/type_traits.h /usr/include/string.h
../Axis/Axis.o: /usr/include/standards.h /usr/include/limits.h
../Axis/Axis.o: /usr/include/sgidefs.h /usr/include/stdlib.h
../Axis/Axis.o: /usr/include/stddef.h /usr/include/CC/new.h
../Axis/Axis.o: /usr/include/CC/iostream.h /usr/include/memory.h
../Axis/Axis.o: /usr/include/CC/stl_iterator.h /usr/include/CC/stl_alloc.h
../Axis/Axis.o: /usr/include/assert.h /usr/include/mutex.h
../Axis/Axis.o: /usr/include/time.h /usr/include/CC/stl_construct.h
../Axis/Axis.o: /usr/include/CC/stl_uninitialized.h
../Axis/Axis.o: /usr/include/CC/stl_list.h ../../c++adt/include/Point.h
../Axis/Axis.o: /usr/include/math.h ../../c++adt/include/PositionVector.h
../Axis/Axis.o: ../../c++adt/include/mathsym.h /usr/include/CC/vector
../Axis/Axis.o: /usr/include/CC/stl_vector.h /usr/include/CC/stl_bvector.h
../Axis/Axis.o: ../../c++adt/include/RMatrix.h ../../c++adt/include/TMatrix.h
../Axis/Axis.o: /usr/include/CC/stream.h /usr/include/CC/iomanip.h
../Axis/Axis.o: /usr/include/CC/generic.h /usr/include/CC/stdiostream.h
../Axis/Axis.o: /usr/include/stdio.h /usr/include/CC/fstream.h
../Axis/Axis.o: ../include/TreeCompartment.h ../include/LGMUnits.h
../Axis/Axis.o: ../include/Bud.h ../include/LGMSymbols.h /usr/include/CC/map
../Axis/Axis.o: /usr/include/CC/stl_tree.h /usr/include/CC/stl_function.h
../Axis/Axis.o: /usr/include/CC/stl_map.h /usr/include/CC/stl_multimap.h
../Axis/Axis.o: ../include/TreeSegment.h
../BranchingPoint/BranchingPointFriend.o: ../include/BranchingPoint.h
../BranchingPoint/BranchingPointFriend.o: /usr/include/CC/list
../BranchingPoint/BranchingPointFriend.o: /usr/include/CC/stl_algobase.h
../BranchingPoint/BranchingPointFriend.o: /usr/include/CC/stl_config.h
../BranchingPoint/BranchingPointFriend.o: /usr/include/CC/stl_relops.h
../BranchingPoint/BranchingPointFriend.o: /usr/include/CC/stl_pair.h
../BranchingPoint/BranchingPointFriend.o: /usr/include/CC/type_traits.h
../BranchingPoint/BranchingPointFriend.o: /usr/include/string.h
../BranchingPoint/BranchingPointFriend.o: /usr/include/standards.h
../BranchingPoint/BranchingPointFriend.o: /usr/include/limits.h
../BranchingPoint/BranchingPointFriend.o: /usr/include/sgidefs.h
../BranchingPoint/BranchingPointFriend.o: /usr/include/stdlib.h
../BranchingPoint/BranchingPointFriend.o: /usr/include/stddef.h
../BranchingPoint/BranchingPointFriend.o: /usr/include/CC/new.h
../BranchingPoint/BranchingPointFriend.o: /usr/include/CC/iostream.h
../BranchingPoint/BranchingPointFriend.o: /usr/include/memory.h
../BranchingPoint/BranchingPointFriend.o: /usr/include/CC/stl_iterator.h
../BranchingPoint/BranchingPointFriend.o: /usr/include/CC/stl_alloc.h
../BranchingPoint/BranchingPointFriend.o: /usr/include/assert.h
../BranchingPoint/BranchingPointFriend.o: /usr/include/mutex.h
../BranchingPoint/BranchingPointFriend.o: /usr/include/time.h
../BranchingPoint/BranchingPointFriend.o: /usr/include/CC/stl_construct.h
../BranchingPoint/BranchingPointFriend.o: /usr/include/CC/stl_uninitialized.h
../BranchingPoint/BranchingPointFriend.o: /usr/include/CC/stl_list.h
../BranchingPoint/BranchingPointFriend.o: ../include/TreeCompartment.h
../BranchingPoint/BranchingPointFriend.o: ../include/LGMUnits.h
../BranchingPoint/BranchingPointFriend.o: ../../c++adt/include/Point.h
../BranchingPoint/BranchingPointFriend.o: /usr/include/math.h
../BranchingPoint/BranchingPointFriend.o: ../../c++adt/include/PositionVector.h
../BranchingPoint/BranchingPointFriend.o: ../../c++adt/include/mathsym.h
../BranchingPoint/BranchingPointFriend.o: /usr/include/CC/vector
../BranchingPoint/BranchingPointFriend.o: /usr/include/CC/stl_vector.h
../BranchingPoint/BranchingPointFriend.o: /usr/include/CC/stl_bvector.h
../BranchingPoint/BranchingPointFriend.o: ../../c++adt/include/RMatrix.h
../BranchingPoint/BranchingPointFriend.o: ../../c++adt/include/TMatrix.h
../BranchingPoint/BranchingPointFriend.o: /usr/include/CC/stream.h
../BranchingPoint/BranchingPointFriend.o: /usr/include/CC/iomanip.h
../BranchingPoint/BranchingPointFriend.o: /usr/include/CC/generic.h
../BranchingPoint/BranchingPointFriend.o: /usr/include/CC/stdiostream.h
../BranchingPoint/BranchingPointFriend.o: /usr/include/stdio.h
../BranchingPoint/BranchingPointFriend.o: /usr/include/CC/fstream.h
../BranchingPoint/BranchingPointFriend.o: ../include/Axis.h ../include/Bud.h
../BranchingPoint/BranchingPointFriend.o: ../include/LGMSymbols.h
../BranchingPoint/BranchingPointFriend.o: /usr/include/CC/map
../BranchingPoint/BranchingPointFriend.o: /usr/include/CC/stl_tree.h
../BranchingPoint/BranchingPointFriend.o: /usr/include/CC/stl_function.h
../BranchingPoint/BranchingPointFriend.o: /usr/include/CC/stl_map.h
../BranchingPoint/BranchingPointFriend.o: /usr/include/CC/stl_multimap.h
../BranchingPoint/BranchingPointFriend.o: ../include/TreeSegment.h
../BranchingPoint/BranchingPoint.o: ../include/BranchingPoint.h
../BranchingPoint/BranchingPoint.o: /usr/include/CC/list
../BranchingPoint/BranchingPoint.o: /usr/include/CC/stl_algobase.h
../BranchingPoint/BranchingPoint.o: /usr/include/CC/stl_config.h
../BranchingPoint/BranchingPoint.o: /usr/include/CC/stl_relops.h
../BranchingPoint/BranchingPoint.o: /usr/include/CC/stl_pair.h
../BranchingPoint/BranchingPoint.o: /usr/include/CC/type_traits.h
../BranchingPoint/BranchingPoint.o: /usr/include/string.h
../BranchingPoint/BranchingPoint.o: /usr/include/standards.h
../BranchingPoint/BranchingPoint.o: /usr/include/limits.h
../BranchingPoint/BranchingPoint.o: /usr/include/sgidefs.h
../BranchingPoint/BranchingPoint.o: /usr/include/stdlib.h
../BranchingPoint/BranchingPoint.o: /usr/include/stddef.h
../BranchingPoint/BranchingPoint.o: /usr/include/CC/new.h
../BranchingPoint/BranchingPoint.o: /usr/include/CC/iostream.h
../BranchingPoint/BranchingPoint.o: /usr/include/memory.h
../BranchingPoint/BranchingPoint.o: /usr/include/CC/stl_iterator.h
../BranchingPoint/BranchingPoint.o: /usr/include/CC/stl_alloc.h
../BranchingPoint/BranchingPoint.o: /usr/include/assert.h
../BranchingPoint/BranchingPoint.o: /usr/include/mutex.h /usr/include/time.h
../BranchingPoint/BranchingPoint.o: /usr/include/CC/stl_construct.h
../BranchingPoint/BranchingPoint.o: /usr/include/CC/stl_uninitialized.h
../BranchingPoint/BranchingPoint.o: /usr/include/CC/stl_list.h
../BranchingPoint/BranchingPoint.o: ../include/TreeCompartment.h
../BranchingPoint/BranchingPoint.o: ../include/LGMUnits.h
../BranchingPoint/BranchingPoint.o: ../../c++adt/include/Point.h
../BranchingPoint/BranchingPoint.o: /usr/include/math.h
../BranchingPoint/BranchingPoint.o: ../../c++adt/include/PositionVector.h
../BranchingPoint/BranchingPoint.o: ../../c++adt/include/mathsym.h
../BranchingPoint/BranchingPoint.o: /usr/include/CC/vector
../BranchingPoint/BranchingPoint.o: /usr/include/CC/stl_vector.h
../BranchingPoint/BranchingPoint.o: /usr/include/CC/stl_bvector.h
../BranchingPoint/BranchingPoint.o: ../../c++adt/include/RMatrix.h
../BranchingPoint/BranchingPoint.o: ../../c++adt/include/TMatrix.h
../BranchingPoint/BranchingPoint.o: /usr/include/CC/stream.h
../BranchingPoint/BranchingPoint.o: /usr/include/CC/iomanip.h
../BranchingPoint/BranchingPoint.o: /usr/include/CC/generic.h
../BranchingPoint/BranchingPoint.o: /usr/include/CC/stdiostream.h
../BranchingPoint/BranchingPoint.o: /usr/include/stdio.h
../BranchingPoint/BranchingPoint.o: /usr/include/CC/fstream.h
../BranchingPoint/BranchingPoint.o: ../include/Axis.h ../include/Bud.h
../BranchingPoint/BranchingPoint.o: ../include/LGMSymbols.h
../BranchingPoint/BranchingPoint.o: /usr/include/CC/map
../BranchingPoint/BranchingPoint.o: /usr/include/CC/stl_tree.h
../BranchingPoint/BranchingPoint.o: /usr/include/CC/stl_function.h
../BranchingPoint/BranchingPoint.o: /usr/include/CC/stl_map.h
../BranchingPoint/BranchingPoint.o: /usr/include/CC/stl_multimap.h
../BranchingPoint/BranchingPoint.o: ../include/TreeSegment.h
../Bud/Bud.o: ../include/Tree.h /usr/include/CC/list
../Bud/Bud.o: /usr/include/CC/stl_algobase.h /usr/include/CC/stl_config.h
../Bud/Bud.o: /usr/include/CC/stl_relops.h /usr/include/CC/stl_pair.h
../Bud/Bud.o: /usr/include/CC/type_traits.h /usr/include/string.h
../Bud/Bud.o: /usr/include/standards.h /usr/include/limits.h
../Bud/Bud.o: /usr/include/sgidefs.h /usr/include/stdlib.h
../Bud/Bud.o: /usr/include/stddef.h /usr/include/CC/new.h
../Bud/Bud.o: /usr/include/CC/iostream.h /usr/include/memory.h
../Bud/Bud.o: /usr/include/CC/stl_iterator.h /usr/include/CC/stl_alloc.h
../Bud/Bud.o: /usr/include/assert.h /usr/include/mutex.h /usr/include/time.h
../Bud/Bud.o: /usr/include/CC/stl_construct.h
../Bud/Bud.o: /usr/include/CC/stl_uninitialized.h /usr/include/CC/stl_list.h
../Bud/Bud.o: ../../c++adt/include/CString.h /usr/include/stdio.h
../Bud/Bud.o: /usr/include/ctype.h /usr/include/locale_attr.h
../Bud/Bud.o: /usr/include/CC/stream.h /usr/include/CC/iomanip.h
../Bud/Bud.o: /usr/include/CC/generic.h /usr/include/CC/stdiostream.h
../Bud/Bud.o: /usr/include/CC/fstream.h
../Bud/Bud.o: ../../c++adt/include/ParametricCurve.h /usr/include/CC/vector
../Bud/Bud.o: /usr/include/CC/stl_vector.h /usr/include/CC/stl_bvector.h
../Bud/Bud.o: /usr/include/float.h ../../c++adt/include/Point.h
../Bud/Bud.o: /usr/include/math.h ../include/LGMSymbols.h /usr/include/CC/map
../Bud/Bud.o: /usr/include/CC/stl_tree.h /usr/include/CC/stl_function.h
../Bud/Bud.o: /usr/include/CC/stl_map.h /usr/include/CC/stl_multimap.h
../Bud/Bud.o: ../include/LGMUnits.h ../include/TreeMetaFileParser.h
../Bud/Bud.o: ../../c++adt/include/Table.h ../../c++adt/include/DList.h
../Bud/Bud.o: ../../c++adt/include/DListElement.h
../Bud/Bud.o: ../../c++adt/include/boolean.h ../../c++adt/include/Lex.h
../Bud/Bud.o: ../include/TreeCompartment.h
../Bud/Bud.o: ../../c++adt/include/PositionVector.h
../Bud/Bud.o: ../../c++adt/include/mathsym.h ../../c++adt/include/RMatrix.h
../Bud/Bud.o: ../../c++adt/include/TMatrix.h ../include/Axis.h
../Bud/Bud.o: ../include/Bud.h ../include/TreeSegment.h
../Bud/Bud.o: ../include/BranchingPoint.h ../include/RootSystem.h
../Bud/BudFriend.o: ../include/Bud.h ../include/LGMSymbols.h
../Bud/BudFriend.o: /usr/include/CC/map /usr/include/CC/stl_tree.h
../Bud/BudFriend.o: /usr/include/CC/stl_algobase.h
../Bud/BudFriend.o: /usr/include/CC/stl_config.h /usr/include/CC/stl_relops.h
../Bud/BudFriend.o: /usr/include/CC/stl_pair.h /usr/include/CC/type_traits.h
../Bud/BudFriend.o: /usr/include/string.h /usr/include/standards.h
../Bud/BudFriend.o: /usr/include/limits.h /usr/include/sgidefs.h
../Bud/BudFriend.o: /usr/include/stdlib.h /usr/include/stddef.h
../Bud/BudFriend.o: /usr/include/CC/new.h /usr/include/CC/iostream.h
../Bud/BudFriend.o: /usr/include/memory.h /usr/include/CC/stl_iterator.h
../Bud/BudFriend.o: /usr/include/CC/stl_alloc.h /usr/include/assert.h
../Bud/BudFriend.o: /usr/include/mutex.h /usr/include/time.h
../Bud/BudFriend.o: /usr/include/CC/stl_construct.h
../Bud/BudFriend.o: /usr/include/CC/stl_function.h /usr/include/CC/stl_map.h
../Bud/BudFriend.o: /usr/include/CC/stl_multimap.h ../include/LGMUnits.h
../Bud/BudFriend.o: ../include/TreeCompartment.h ../../c++adt/include/Point.h
../Bud/BudFriend.o: /usr/include/math.h ../../c++adt/include/PositionVector.h
../Bud/BudFriend.o: ../../c++adt/include/mathsym.h /usr/include/CC/vector
../Bud/BudFriend.o: /usr/include/CC/stl_uninitialized.h
../Bud/BudFriend.o: /usr/include/CC/stl_vector.h
../Bud/BudFriend.o: /usr/include/CC/stl_bvector.h
../Bud/BudFriend.o: ../../c++adt/include/RMatrix.h
../Bud/BudFriend.o: ../../c++adt/include/TMatrix.h /usr/include/CC/stream.h
../Bud/BudFriend.o: /usr/include/CC/iomanip.h /usr/include/CC/generic.h
../Bud/BudFriend.o: /usr/include/CC/stdiostream.h /usr/include/stdio.h
../Bud/BudFriend.o: /usr/include/CC/fstream.h ../include/TreeSegment.h
../Bud/BudFriend.o: /usr/include/CC/list /usr/include/CC/stl_list.h
../Tree/Tree.o: ../include/Tree.h /usr/include/CC/list
../Tree/Tree.o: /usr/include/CC/stl_algobase.h /usr/include/CC/stl_config.h
../Tree/Tree.o: /usr/include/CC/stl_relops.h /usr/include/CC/stl_pair.h
../Tree/Tree.o: /usr/include/CC/type_traits.h /usr/include/string.h
../Tree/Tree.o: /usr/include/standards.h /usr/include/limits.h
../Tree/Tree.o: /usr/include/sgidefs.h /usr/include/stdlib.h
../Tree/Tree.o: /usr/include/stddef.h /usr/include/CC/new.h
../Tree/Tree.o: /usr/include/CC/iostream.h /usr/include/memory.h
../Tree/Tree.o: /usr/include/CC/stl_iterator.h /usr/include/CC/stl_alloc.h
../Tree/Tree.o: /usr/include/assert.h /usr/include/mutex.h
../Tree/Tree.o: /usr/include/time.h /usr/include/CC/stl_construct.h
../Tree/Tree.o: /usr/include/CC/stl_uninitialized.h
../Tree/Tree.o: /usr/include/CC/stl_list.h ../../c++adt/include/CString.h
../Tree/Tree.o: /usr/include/stdio.h /usr/include/ctype.h
../Tree/Tree.o: /usr/include/locale_attr.h /usr/include/CC/stream.h
../Tree/Tree.o: /usr/include/CC/iomanip.h /usr/include/CC/generic.h
../Tree/Tree.o: /usr/include/CC/stdiostream.h /usr/include/CC/fstream.h
../Tree/Tree.o: ../../c++adt/include/ParametricCurve.h /usr/include/CC/vector
../Tree/Tree.o: /usr/include/CC/stl_vector.h /usr/include/CC/stl_bvector.h
../Tree/Tree.o: /usr/include/float.h ../../c++adt/include/Point.h
../Tree/Tree.o: /usr/include/math.h ../include/LGMSymbols.h
../Tree/Tree.o: /usr/include/CC/map /usr/include/CC/stl_tree.h
../Tree/Tree.o: /usr/include/CC/stl_function.h /usr/include/CC/stl_map.h
../Tree/Tree.o: /usr/include/CC/stl_multimap.h ../include/LGMUnits.h
../Tree/Tree.o: ../include/TreeMetaFileParser.h ../../c++adt/include/Table.h
../Tree/Tree.o: ../../c++adt/include/DList.h
../Tree/Tree.o: ../../c++adt/include/DListElement.h
../Tree/Tree.o: ../../c++adt/include/boolean.h ../../c++adt/include/Lex.h
../Tree/Tree.o: ../include/TreeCompartment.h
../Tree/Tree.o: ../../c++adt/include/PositionVector.h
../Tree/Tree.o: ../../c++adt/include/mathsym.h ../../c++adt/include/RMatrix.h
../Tree/Tree.o: ../../c++adt/include/TMatrix.h ../include/Axis.h
../Tree/Tree.o: ../include/Bud.h ../include/TreeSegment.h
../Tree/Tree.o: ../include/BranchingPoint.h ../include/RootSystem.h
../Tree/TreeFriend.o: ../include/Tree.h /usr/include/CC/list
../Tree/TreeFriend.o: /usr/include/CC/stl_algobase.h
../Tree/TreeFriend.o: /usr/include/CC/stl_config.h
../Tree/TreeFriend.o: /usr/include/CC/stl_relops.h /usr/include/CC/stl_pair.h
../Tree/TreeFriend.o: /usr/include/CC/type_traits.h /usr/include/string.h
../Tree/TreeFriend.o: /usr/include/standards.h /usr/include/limits.h
../Tree/TreeFriend.o: /usr/include/sgidefs.h /usr/include/stdlib.h
../Tree/TreeFriend.o: /usr/include/stddef.h /usr/include/CC/new.h
../Tree/TreeFriend.o: /usr/include/CC/iostream.h /usr/include/memory.h
../Tree/TreeFriend.o: /usr/include/CC/stl_iterator.h
../Tree/TreeFriend.o: /usr/include/CC/stl_alloc.h /usr/include/assert.h
../Tree/TreeFriend.o: /usr/include/mutex.h /usr/include/time.h
../Tree/TreeFriend.o: /usr/include/CC/stl_construct.h
../Tree/TreeFriend.o: /usr/include/CC/stl_uninitialized.h
../Tree/TreeFriend.o: /usr/include/CC/stl_list.h
../Tree/TreeFriend.o: ../../c++adt/include/CString.h /usr/include/stdio.h
../Tree/TreeFriend.o: /usr/include/ctype.h /usr/include/locale_attr.h
../Tree/TreeFriend.o: /usr/include/CC/stream.h /usr/include/CC/iomanip.h
../Tree/TreeFriend.o: /usr/include/CC/generic.h /usr/include/CC/stdiostream.h
../Tree/TreeFriend.o: /usr/include/CC/fstream.h
../Tree/TreeFriend.o: ../../c++adt/include/ParametricCurve.h
../Tree/TreeFriend.o: /usr/include/CC/vector /usr/include/CC/stl_vector.h
../Tree/TreeFriend.o: /usr/include/CC/stl_bvector.h /usr/include/float.h
../Tree/TreeFriend.o: ../../c++adt/include/Point.h /usr/include/math.h
../Tree/TreeFriend.o: ../include/LGMSymbols.h /usr/include/CC/map
../Tree/TreeFriend.o: /usr/include/CC/stl_tree.h
../Tree/TreeFriend.o: /usr/include/CC/stl_function.h
../Tree/TreeFriend.o: /usr/include/CC/stl_map.h
../Tree/TreeFriend.o: /usr/include/CC/stl_multimap.h ../include/LGMUnits.h
../Tree/TreeFriend.o: ../include/TreeMetaFileParser.h
../Tree/TreeFriend.o: ../../c++adt/include/Table.h
../Tree/TreeFriend.o: ../../c++adt/include/DList.h
../Tree/TreeFriend.o: ../../c++adt/include/DListElement.h
../Tree/TreeFriend.o: ../../c++adt/include/boolean.h
../Tree/TreeFriend.o: ../../c++adt/include/Lex.h ../include/TreeCompartment.h
../Tree/TreeFriend.o: ../../c++adt/include/PositionVector.h
../Tree/TreeFriend.o: ../../c++adt/include/mathsym.h
../Tree/TreeFriend.o: ../../c++adt/include/RMatrix.h
../Tree/TreeFriend.o: ../../c++adt/include/TMatrix.h ../include/Axis.h
../Tree/TreeFriend.o: ../include/Bud.h ../include/TreeSegment.h
../Tree/TreeFriend.o: ../include/BranchingPoint.h ../include/RootSystem.h
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
../TreeSegment/TreeSegment.o: ../include/TreeSegment.h /usr/include/CC/list
../TreeSegment/TreeSegment.o: /usr/include/CC/stl_algobase.h
../TreeSegment/TreeSegment.o: /usr/include/CC/stl_config.h
../TreeSegment/TreeSegment.o: /usr/include/CC/stl_relops.h
../TreeSegment/TreeSegment.o: /usr/include/CC/stl_pair.h
../TreeSegment/TreeSegment.o: /usr/include/CC/type_traits.h
../TreeSegment/TreeSegment.o: /usr/include/string.h /usr/include/standards.h
../TreeSegment/TreeSegment.o: /usr/include/limits.h /usr/include/sgidefs.h
../TreeSegment/TreeSegment.o: /usr/include/stdlib.h /usr/include/stddef.h
../TreeSegment/TreeSegment.o: /usr/include/CC/new.h
../TreeSegment/TreeSegment.o: /usr/include/CC/iostream.h
../TreeSegment/TreeSegment.o: /usr/include/memory.h
../TreeSegment/TreeSegment.o: /usr/include/CC/stl_iterator.h
../TreeSegment/TreeSegment.o: /usr/include/CC/stl_alloc.h
../TreeSegment/TreeSegment.o: /usr/include/assert.h /usr/include/mutex.h
../TreeSegment/TreeSegment.o: /usr/include/time.h
../TreeSegment/TreeSegment.o: /usr/include/CC/stl_construct.h
../TreeSegment/TreeSegment.o: /usr/include/CC/stl_uninitialized.h
../TreeSegment/TreeSegment.o: /usr/include/CC/stl_list.h
../TreeSegment/TreeSegment.o: ../include/LGMSymbols.h /usr/include/CC/map
../TreeSegment/TreeSegment.o: /usr/include/CC/stl_tree.h
../TreeSegment/TreeSegment.o: /usr/include/CC/stl_function.h
../TreeSegment/TreeSegment.o: /usr/include/CC/stl_map.h
../TreeSegment/TreeSegment.o: /usr/include/CC/stl_multimap.h
../TreeSegment/TreeSegment.o: ../include/LGMUnits.h
../TreeSegment/TreeSegment.o: ../../c++adt/include/Point.h
../TreeSegment/TreeSegment.o: /usr/include/math.h
../TreeSegment/TreeSegment.o: ../include/TreeCompartment.h
../TreeSegment/TreeSegment.o: ../../c++adt/include/PositionVector.h
../TreeSegment/TreeSegment.o: ../../c++adt/include/mathsym.h
../TreeSegment/TreeSegment.o: /usr/include/CC/vector
../TreeSegment/TreeSegment.o: /usr/include/CC/stl_vector.h
../TreeSegment/TreeSegment.o: /usr/include/CC/stl_bvector.h
../TreeSegment/TreeSegment.o: ../../c++adt/include/RMatrix.h
../TreeSegment/TreeSegment.o: ../../c++adt/include/TMatrix.h
../TreeSegment/TreeSegment.o: /usr/include/CC/stream.h
../TreeSegment/TreeSegment.o: /usr/include/CC/iomanip.h
../TreeSegment/TreeSegment.o: /usr/include/CC/generic.h
../TreeSegment/TreeSegment.o: /usr/include/CC/stdiostream.h
../TreeSegment/TreeSegment.o: /usr/include/stdio.h /usr/include/CC/fstream.h
../TreeSegment/TreeSegment.o: ../include/Tree.h
../TreeSegment/TreeSegment.o: ../../c++adt/include/CString.h
../TreeSegment/TreeSegment.o: /usr/include/ctype.h /usr/include/locale_attr.h
../TreeSegment/TreeSegment.o: ../../c++adt/include/ParametricCurve.h
../TreeSegment/TreeSegment.o: /usr/include/float.h
../TreeSegment/TreeSegment.o: ../include/TreeMetaFileParser.h
../TreeSegment/TreeSegment.o: ../../c++adt/include/Table.h
../TreeSegment/TreeSegment.o: ../../c++adt/include/DList.h
../TreeSegment/TreeSegment.o: ../../c++adt/include/DListElement.h
../TreeSegment/TreeSegment.o: ../../c++adt/include/boolean.h
../TreeSegment/TreeSegment.o: ../../c++adt/include/Lex.h ../include/Axis.h
../TreeSegment/TreeSegment.o: ../include/Bud.h ../include/BranchingPoint.h
../TreeSegment/TreeSegment.o: ../include/RootSystem.h
../TreeSegment/TreeSegmentFriend.o: ../include/TreeSegment.h
../TreeSegment/TreeSegmentFriend.o: /usr/include/CC/list
../TreeSegment/TreeSegmentFriend.o: /usr/include/CC/stl_algobase.h
../TreeSegment/TreeSegmentFriend.o: /usr/include/CC/stl_config.h
../TreeSegment/TreeSegmentFriend.o: /usr/include/CC/stl_relops.h
../TreeSegment/TreeSegmentFriend.o: /usr/include/CC/stl_pair.h
../TreeSegment/TreeSegmentFriend.o: /usr/include/CC/type_traits.h
../TreeSegment/TreeSegmentFriend.o: /usr/include/string.h
../TreeSegment/TreeSegmentFriend.o: /usr/include/standards.h
../TreeSegment/TreeSegmentFriend.o: /usr/include/limits.h
../TreeSegment/TreeSegmentFriend.o: /usr/include/sgidefs.h
../TreeSegment/TreeSegmentFriend.o: /usr/include/stdlib.h
../TreeSegment/TreeSegmentFriend.o: /usr/include/stddef.h
../TreeSegment/TreeSegmentFriend.o: /usr/include/CC/new.h
../TreeSegment/TreeSegmentFriend.o: /usr/include/CC/iostream.h
../TreeSegment/TreeSegmentFriend.o: /usr/include/memory.h
../TreeSegment/TreeSegmentFriend.o: /usr/include/CC/stl_iterator.h
../TreeSegment/TreeSegmentFriend.o: /usr/include/CC/stl_alloc.h
../TreeSegment/TreeSegmentFriend.o: /usr/include/assert.h
../TreeSegment/TreeSegmentFriend.o: /usr/include/mutex.h /usr/include/time.h
../TreeSegment/TreeSegmentFriend.o: /usr/include/CC/stl_construct.h
../TreeSegment/TreeSegmentFriend.o: /usr/include/CC/stl_uninitialized.h
../TreeSegment/TreeSegmentFriend.o: /usr/include/CC/stl_list.h
../TreeSegment/TreeSegmentFriend.o: ../include/LGMSymbols.h
../TreeSegment/TreeSegmentFriend.o: /usr/include/CC/map
../TreeSegment/TreeSegmentFriend.o: /usr/include/CC/stl_tree.h
../TreeSegment/TreeSegmentFriend.o: /usr/include/CC/stl_function.h
../TreeSegment/TreeSegmentFriend.o: /usr/include/CC/stl_map.h
../TreeSegment/TreeSegmentFriend.o: /usr/include/CC/stl_multimap.h
../TreeSegment/TreeSegmentFriend.o: ../include/LGMUnits.h
../TreeSegment/TreeSegmentFriend.o: ../../c++adt/include/Point.h
../TreeSegment/TreeSegmentFriend.o: /usr/include/math.h
../TreeSegment/TreeSegmentFriend.o: ../include/TreeCompartment.h
../TreeSegment/TreeSegmentFriend.o: ../../c++adt/include/PositionVector.h
../TreeSegment/TreeSegmentFriend.o: ../../c++adt/include/mathsym.h
../TreeSegment/TreeSegmentFriend.o: /usr/include/CC/vector
../TreeSegment/TreeSegmentFriend.o: /usr/include/CC/stl_vector.h
../TreeSegment/TreeSegmentFriend.o: /usr/include/CC/stl_bvector.h
../TreeSegment/TreeSegmentFriend.o: ../../c++adt/include/RMatrix.h
../TreeSegment/TreeSegmentFriend.o: ../../c++adt/include/TMatrix.h
../TreeSegment/TreeSegmentFriend.o: /usr/include/CC/stream.h
../TreeSegment/TreeSegmentFriend.o: /usr/include/CC/iomanip.h
../TreeSegment/TreeSegmentFriend.o: /usr/include/CC/generic.h
../TreeSegment/TreeSegmentFriend.o: /usr/include/CC/stdiostream.h
../TreeSegment/TreeSegmentFriend.o: /usr/include/stdio.h
../TreeSegment/TreeSegmentFriend.o: /usr/include/CC/fstream.h
../TreeSegment/TreeSegmentFriend.o: ../include/Tree.h
../TreeSegment/TreeSegmentFriend.o: ../../c++adt/include/CString.h
../TreeSegment/TreeSegmentFriend.o: /usr/include/ctype.h
../TreeSegment/TreeSegmentFriend.o: /usr/include/locale_attr.h
../TreeSegment/TreeSegmentFriend.o: ../../c++adt/include/ParametricCurve.h
../TreeSegment/TreeSegmentFriend.o: /usr/include/float.h
../TreeSegment/TreeSegmentFriend.o: ../include/TreeMetaFileParser.h
../TreeSegment/TreeSegmentFriend.o: ../../c++adt/include/Table.h
../TreeSegment/TreeSegmentFriend.o: ../../c++adt/include/DList.h
../TreeSegment/TreeSegmentFriend.o: ../../c++adt/include/DListElement.h
../TreeSegment/TreeSegmentFriend.o: ../../c++adt/include/boolean.h
../TreeSegment/TreeSegmentFriend.o: ../../c++adt/include/Lex.h
../TreeSegment/TreeSegmentFriend.o: ../include/Axis.h ../include/Bud.h
../TreeSegment/TreeSegmentFriend.o: ../include/BranchingPoint.h
../TreeSegment/TreeSegmentFriend.o: ../include/RootSystem.h
../TreeCompartment/TreeCompartment.o: ../include/TreeCompartment.h
../TreeCompartment/TreeCompartment.o: ../include/LGMUnits.h
../TreeCompartment/TreeCompartment.o: ../../c++adt/include/Point.h
../TreeCompartment/TreeCompartment.o: /usr/include/math.h
../TreeCompartment/TreeCompartment.o: /usr/include/sgidefs.h
../TreeCompartment/TreeCompartment.o: /usr/include/standards.h
../TreeCompartment/TreeCompartment.o: /usr/include/CC/iostream.h
../TreeCompartment/TreeCompartment.o: /usr/include/memory.h
../TreeCompartment/TreeCompartment.o: /usr/include/stddef.h
../TreeCompartment/TreeCompartment.o: ../../c++adt/include/PositionVector.h
../TreeCompartment/TreeCompartment.o: ../../c++adt/include/mathsym.h
../TreeCompartment/TreeCompartment.o: /usr/include/CC/vector
../TreeCompartment/TreeCompartment.o: /usr/include/CC/stl_algobase.h
../TreeCompartment/TreeCompartment.o: /usr/include/CC/stl_config.h
../TreeCompartment/TreeCompartment.o: /usr/include/CC/stl_relops.h
../TreeCompartment/TreeCompartment.o: /usr/include/CC/stl_pair.h
../TreeCompartment/TreeCompartment.o: /usr/include/CC/type_traits.h
../TreeCompartment/TreeCompartment.o: /usr/include/string.h
../TreeCompartment/TreeCompartment.o: /usr/include/limits.h
../TreeCompartment/TreeCompartment.o: /usr/include/stdlib.h
../TreeCompartment/TreeCompartment.o: /usr/include/CC/new.h
../TreeCompartment/TreeCompartment.o: /usr/include/CC/stl_iterator.h
../TreeCompartment/TreeCompartment.o: /usr/include/CC/stl_alloc.h
../TreeCompartment/TreeCompartment.o: /usr/include/assert.h
../TreeCompartment/TreeCompartment.o: /usr/include/mutex.h
../TreeCompartment/TreeCompartment.o: /usr/include/time.h
../TreeCompartment/TreeCompartment.o: /usr/include/CC/stl_construct.h
../TreeCompartment/TreeCompartment.o: /usr/include/CC/stl_uninitialized.h
../TreeCompartment/TreeCompartment.o: /usr/include/CC/stl_vector.h
../TreeCompartment/TreeCompartment.o: /usr/include/CC/stl_bvector.h
../TreeCompartment/TreeCompartment.o: ../../c++adt/include/RMatrix.h
../TreeCompartment/TreeCompartment.o: ../../c++adt/include/TMatrix.h
../TreeCompartment/TreeCompartment.o: /usr/include/CC/stream.h
../TreeCompartment/TreeCompartment.o: /usr/include/CC/iomanip.h
../TreeCompartment/TreeCompartment.o: /usr/include/CC/generic.h
../TreeCompartment/TreeCompartment.o: /usr/include/CC/stdiostream.h
../TreeCompartment/TreeCompartment.o: /usr/include/stdio.h
../TreeCompartment/TreeCompartment.o: /usr/include/CC/fstream.h
../TreeCompartment/TreeCompartmentFriend.o: ../include/TreeCompartment.h
../TreeCompartment/TreeCompartmentFriend.o: ../include/LGMUnits.h
../TreeCompartment/TreeCompartmentFriend.o: ../../c++adt/include/Point.h
../TreeCompartment/TreeCompartmentFriend.o: /usr/include/math.h
../TreeCompartment/TreeCompartmentFriend.o: /usr/include/sgidefs.h
../TreeCompartment/TreeCompartmentFriend.o: /usr/include/standards.h
../TreeCompartment/TreeCompartmentFriend.o: /usr/include/CC/iostream.h
../TreeCompartment/TreeCompartmentFriend.o: /usr/include/memory.h
../TreeCompartment/TreeCompartmentFriend.o: /usr/include/stddef.h
../TreeCompartment/TreeCompartmentFriend.o: ../../c++adt/include/PositionVector.h
../TreeCompartment/TreeCompartmentFriend.o: ../../c++adt/include/mathsym.h
../TreeCompartment/TreeCompartmentFriend.o: /usr/include/CC/vector
../TreeCompartment/TreeCompartmentFriend.o: /usr/include/CC/stl_algobase.h
../TreeCompartment/TreeCompartmentFriend.o: /usr/include/CC/stl_config.h
../TreeCompartment/TreeCompartmentFriend.o: /usr/include/CC/stl_relops.h
../TreeCompartment/TreeCompartmentFriend.o: /usr/include/CC/stl_pair.h
../TreeCompartment/TreeCompartmentFriend.o: /usr/include/CC/type_traits.h
../TreeCompartment/TreeCompartmentFriend.o: /usr/include/string.h
../TreeCompartment/TreeCompartmentFriend.o: /usr/include/limits.h
../TreeCompartment/TreeCompartmentFriend.o: /usr/include/stdlib.h
../TreeCompartment/TreeCompartmentFriend.o: /usr/include/CC/new.h
../TreeCompartment/TreeCompartmentFriend.o: /usr/include/CC/stl_iterator.h
../TreeCompartment/TreeCompartmentFriend.o: /usr/include/CC/stl_alloc.h
../TreeCompartment/TreeCompartmentFriend.o: /usr/include/assert.h
../TreeCompartment/TreeCompartmentFriend.o: /usr/include/mutex.h
../TreeCompartment/TreeCompartmentFriend.o: /usr/include/time.h
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
../TreeCompartment/TreeCompartmentFriend.o: /usr/include/stdio.h
../TreeCompartment/TreeCompartmentFriend.o: /usr/include/CC/fstream.h
