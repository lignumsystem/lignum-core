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
      ../Tree/Tree.cc \
      ../TreeSegment/CfTreeSegment.cc \
      ../TreeSegment/BroadLeafMetabolism.cc
  
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
      ../Tree/Tree.o \
      ../TreeSegment/CfTreeSegment.o \
      ../TreeSegment/BroadLeafMetabolism.o


INCLUDE = -I../include  -I../../c++adt/include -I../../Firmament/include
STL = -I/usr/include/CC
CCC = CC -64
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


../Axis/AxisFriend..o: ../include/Axis.h ../include/AxisI.h
../Axis/AxisFriend..o: ../include/LGMdecl.h ../include/LGMSymbols.h
../Axis/AxisFriend..o: ../include/LGMUnits.h ../include/TreeCompartment.h
../Axis/AxisFriend..o: ../include/TreeCompartmentI.h /usr/include/alloca.h
../Axis/AxisFriend..o: /usr/include/assert.h /usr/include/bits/huge_val.h
../Axis/AxisFriend..o: /usr/include/bits/local_lim.h
../Axis/AxisFriend..o: /usr/include/bits/mathcalls.h
../Axis/AxisFriend..o: /usr/include/bits/mathdef.h /usr/include/bits/nan.h
../Axis/AxisFriend..o: /usr/include/bits/posix1_lim.h
../Axis/AxisFriend..o: /usr/include/bits/pthreadtypes.h
../Axis/AxisFriend..o: /usr/include/bits/sched.h /usr/include/bits/sigset.h
../Axis/AxisFriend..o: /usr/include/bits/types.h
../Axis/AxisFriend..o: /usr/include/bits/waitstatus.h
../Axis/AxisFriend..o: /usr/include/bits/xopen_lim.h /usr/include/endian.h
../Axis/AxisFriend..o: /usr/include/features.h /usr/include/g++-3/iostream.h
../Axis/AxisFriend..o: /usr/include/g++-3/list /usr/include/g++-3/map
../Axis/AxisFriend..o: /usr/include/g++-3/stl_algobase.h
../Axis/AxisFriend..o: /usr/include/g++-3/stl_alloc.h
../Axis/AxisFriend..o: /usr/include/g++-3/stl_bvector.h
../Axis/AxisFriend..o: /usr/include/g++-3/stl_construct.h
../Axis/AxisFriend..o: /usr/include/g++-3/stl_function.h
../Axis/AxisFriend..o: /usr/include/g++-3/stl_iterator.h
../Axis/AxisFriend..o: /usr/include/g++-3/stl_list.h
../Axis/AxisFriend..o: /usr/include/g++-3/stl_map.h
../Axis/AxisFriend..o: /usr/include/g++-3/stl_multimap.h
../Axis/AxisFriend..o: /usr/include/g++-3/stl_pair.h
../Axis/AxisFriend..o: /usr/include/g++-3/stl_relops.h
../Axis/AxisFriend..o: /usr/include/g++-3/stl_tree.h
../Axis/AxisFriend..o: /usr/include/g++-3/stl_uninitialized.h
../Axis/AxisFriend..o: /usr/include/g++-3/stl_vector.h
../Axis/AxisFriend..o: /usr/include/g++-3/streambuf.h
../Axis/AxisFriend..o: /usr/include/g++-3/stream.h
../Axis/AxisFriend..o: /usr/include/g++-3/type_traits.h
../Axis/AxisFriend..o: /usr/include/g++-3/vector /usr/include/_G_config.h
../Axis/AxisFriend..o: /usr/include/gconv.h /usr/include/libio.h
../Axis/AxisFriend..o: /usr/include/limits.h /usr/include/math.h
../Axis/AxisFriend..o: /usr/include/stdlib.h /usr/include/string.h
../Axis/AxisFriend..o: /usr/include/sys/select.h /usr/include/sys/types.h
../Axis/AxisFriend..o: /usr/include/time.h /usr/include/wchar.h
../Axis/AxisFriend..o: /usr/include/xlocale.h
../Axis/AxisFriend..o: /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/exception
../Axis/AxisFriend..o: /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/float.h
../Axis/AxisFriend..o: /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/limits.h
../Axis/AxisFriend..o: /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/new
../Axis/AxisFriend..o: /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/new.h
../Axis/AxisFriend..o: /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/stdarg.h
../Axis/AxisFriend..o: /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/stddef.h
../Axis/AxisFriend..o: /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/syslimits.h
../BetulaWithFlow/BetulaWithFlow..o: ../include/Algorithms.h
../BetulaWithFlow/BetulaWithFlow..o: ../include/AlgorithmsI.h
../BetulaWithFlow/BetulaWithFlow..o: ../include/Axis.h ../include/AxisI.h
../BetulaWithFlow/BetulaWithFlow..o: ../include/BetulaWithFlow.h
../BetulaWithFlow/BetulaWithFlow..o: ../include/BranchingPoint.h
../BetulaWithFlow/BetulaWithFlow..o: ../include/BranchingPointI.h
../BetulaWithFlow/BetulaWithFlow..o: ../include/BroadLeaf.h ../include/Bud.h
../BetulaWithFlow/BetulaWithFlow..o: ../include/BudI.h
../BetulaWithFlow/BetulaWithFlow..o: ../include/CfTreeSegment.h
../BetulaWithFlow/BetulaWithFlow..o: ../include/CfTreeSegmentI.h
../BetulaWithFlow/BetulaWithFlow..o: ../include/CfTreeSegmentMetabolismI.h
../BetulaWithFlow/BetulaWithFlow..o: ../include/DefaultBud.h
../BetulaWithFlow/BetulaWithFlow..o: ../include/HwTreeSegment.h
../BetulaWithFlow/BetulaWithFlow..o: ../include/HwTreeSegmentI.h
../BetulaWithFlow/BetulaWithFlow..o: ../include/HwTreeSegmentMetabolismI.h
../BetulaWithFlow/BetulaWithFlow..o: ../include/LGMdecl.h
../BetulaWithFlow/BetulaWithFlow..o: ../include/LGMSymbols.h
../BetulaWithFlow/BetulaWithFlow..o: ../include/LGMUnits.h
../BetulaWithFlow/BetulaWithFlow..o: ../include/RootSystem.h
../BetulaWithFlow/BetulaWithFlow..o: ../include/TreeBookkeepingI.h
../BetulaWithFlow/BetulaWithFlow..o: ../include/TreeCompartment.h
../BetulaWithFlow/BetulaWithFlow..o: ../include/TreeCompartmentI.h
../BetulaWithFlow/BetulaWithFlow..o: ../include/TreeFunctor.h
../BetulaWithFlow/BetulaWithFlow..o: ../include/TreeFunctorI.h
../BetulaWithFlow/BetulaWithFlow..o: ../include/Tree.h ../include/TreeI.h
../BetulaWithFlow/BetulaWithFlow..o: ../include/TreeMetabolismI.h
../BetulaWithFlow/BetulaWithFlow..o: ../include/TreeMetaFileParser.h
../BetulaWithFlow/BetulaWithFlow..o: ../include/TreeSegment.h
../BetulaWithFlow/BetulaWithFlow..o: ../include/TreeSegmentI.h
../BetulaWithFlow/BetulaWithFlow..o: /usr/include/alloca.h
../BetulaWithFlow/BetulaWithFlow..o: /usr/include/assert.h
../BetulaWithFlow/BetulaWithFlow..o: /usr/include/bits/huge_val.h
../BetulaWithFlow/BetulaWithFlow..o: /usr/include/bits/local_lim.h
../BetulaWithFlow/BetulaWithFlow..o: /usr/include/bits/mathcalls.h
../BetulaWithFlow/BetulaWithFlow..o: /usr/include/bits/mathdef.h
../BetulaWithFlow/BetulaWithFlow..o: /usr/include/bits/nan.h
../BetulaWithFlow/BetulaWithFlow..o: /usr/include/bits/posix1_lim.h
../BetulaWithFlow/BetulaWithFlow..o: /usr/include/bits/pthreadtypes.h
../BetulaWithFlow/BetulaWithFlow..o: /usr/include/bits/sched.h
../BetulaWithFlow/BetulaWithFlow..o: /usr/include/bits/sigset.h
../BetulaWithFlow/BetulaWithFlow..o: /usr/include/bits/types.h
../BetulaWithFlow/BetulaWithFlow..o: /usr/include/bits/waitstatus.h
../BetulaWithFlow/BetulaWithFlow..o: /usr/include/bits/xopen_lim.h
../BetulaWithFlow/BetulaWithFlow..o: /usr/include/ctype.h
../BetulaWithFlow/BetulaWithFlow..o: /usr/include/endian.h
../BetulaWithFlow/BetulaWithFlow..o: /usr/include/features.h
../BetulaWithFlow/BetulaWithFlow..o: /usr/include/g++-3/algobase.h
../BetulaWithFlow/BetulaWithFlow..o: /usr/include/g++-3/algorithm
../BetulaWithFlow/BetulaWithFlow..o: /usr/include/g++-3/cassert
../BetulaWithFlow/BetulaWithFlow..o: /usr/include/g++-3/cctype
../BetulaWithFlow/BetulaWithFlow..o: /usr/include/g++-3/cstddef
../BetulaWithFlow/BetulaWithFlow..o: /usr/include/g++-3/fstream.h
../BetulaWithFlow/BetulaWithFlow..o: /usr/include/g++-3/functional
../BetulaWithFlow/BetulaWithFlow..o: /usr/include/g++-3/function.h
../BetulaWithFlow/BetulaWithFlow..o: /usr/include/g++-3/iostream.h
../BetulaWithFlow/BetulaWithFlow..o: /usr/include/g++-3/iterator
../BetulaWithFlow/BetulaWithFlow..o: /usr/include/g++-3/iterator.h
../BetulaWithFlow/BetulaWithFlow..o: /usr/include/g++-3/list
../BetulaWithFlow/BetulaWithFlow..o: /usr/include/g++-3/map
../BetulaWithFlow/BetulaWithFlow..o: /usr/include/g++-3/numeric
../BetulaWithFlow/BetulaWithFlow..o: /usr/include/g++-3/std/bastring.cc
../BetulaWithFlow/BetulaWithFlow..o: /usr/include/g++-3/std/bastring.h
../BetulaWithFlow/BetulaWithFlow..o: /usr/include/g++-3/std/straits.h
../BetulaWithFlow/BetulaWithFlow..o: /usr/include/g++-3/stl_algobase.h
../BetulaWithFlow/BetulaWithFlow..o: /usr/include/g++-3/stl_algo.h
../BetulaWithFlow/BetulaWithFlow..o: /usr/include/g++-3/stl_alloc.h
../BetulaWithFlow/BetulaWithFlow..o: /usr/include/g++-3/stl_bvector.h
../BetulaWithFlow/BetulaWithFlow..o: /usr/include/g++-3/stl_construct.h
../BetulaWithFlow/BetulaWithFlow..o: /usr/include/g++-3/stl_function.h
../BetulaWithFlow/BetulaWithFlow..o: /usr/include/g++-3/stl_heap.h
../BetulaWithFlow/BetulaWithFlow..o: /usr/include/g++-3/stl_iterator.h
../BetulaWithFlow/BetulaWithFlow..o: /usr/include/g++-3/stl_list.h
../BetulaWithFlow/BetulaWithFlow..o: /usr/include/g++-3/stl_map.h
../BetulaWithFlow/BetulaWithFlow..o: /usr/include/g++-3/stl_multimap.h
../BetulaWithFlow/BetulaWithFlow..o: /usr/include/g++-3/stl_numeric.h
../BetulaWithFlow/BetulaWithFlow..o: /usr/include/g++-3/stl_pair.h
../BetulaWithFlow/BetulaWithFlow..o: /usr/include/g++-3/stl_raw_storage_iter.h
../BetulaWithFlow/BetulaWithFlow..o: /usr/include/g++-3/stl_relops.h
../BetulaWithFlow/BetulaWithFlow..o: /usr/include/g++-3/stl_tempbuf.h
../BetulaWithFlow/BetulaWithFlow..o: /usr/include/g++-3/stl_tree.h
../BetulaWithFlow/BetulaWithFlow..o: /usr/include/g++-3/stl_uninitialized.h
../BetulaWithFlow/BetulaWithFlow..o: /usr/include/g++-3/stl_vector.h
../BetulaWithFlow/BetulaWithFlow..o: /usr/include/g++-3/streambuf.h
../BetulaWithFlow/BetulaWithFlow..o: /usr/include/g++-3/stream.h
../BetulaWithFlow/BetulaWithFlow..o: /usr/include/g++-3/string
../BetulaWithFlow/BetulaWithFlow..o: /usr/include/g++-3/type_traits.h
../BetulaWithFlow/BetulaWithFlow..o: /usr/include/g++-3/vector
../BetulaWithFlow/BetulaWithFlow..o: /usr/include/g++-3/vector.h
../BetulaWithFlow/BetulaWithFlow..o: /usr/include/_G_config.h
../BetulaWithFlow/BetulaWithFlow..o: /usr/include/gconv.h /usr/include/libio.h
../BetulaWithFlow/BetulaWithFlow..o: /usr/include/limits.h /usr/include/math.h
../BetulaWithFlow/BetulaWithFlow..o: /usr/include/stdio.h
../BetulaWithFlow/BetulaWithFlow..o: /usr/include/stdlib.h
../BetulaWithFlow/BetulaWithFlow..o: /usr/include/string.h
../BetulaWithFlow/BetulaWithFlow..o: /usr/include/sys/select.h
../BetulaWithFlow/BetulaWithFlow..o: /usr/include/sys/types.h
../BetulaWithFlow/BetulaWithFlow..o: /usr/include/time.h /usr/include/wchar.h
../BetulaWithFlow/BetulaWithFlow..o: /usr/include/xlocale.h
../BetulaWithFlow/BetulaWithFlow..o: /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/exception
../BetulaWithFlow/BetulaWithFlow..o: /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/float.h
../BetulaWithFlow/BetulaWithFlow..o: /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/limits.h
../BetulaWithFlow/BetulaWithFlow..o: /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/new
../BetulaWithFlow/BetulaWithFlow..o: /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/new.h
../BetulaWithFlow/BetulaWithFlow..o: /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/stdarg.h
../BetulaWithFlow/BetulaWithFlow..o: /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/stddef.h
../BetulaWithFlow/BetulaWithFlow..o: /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/syslimits.h
../BetulaWithFlow/BetulaWithFlow..o: /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/typeinfo
../BranchingPoint/BranchingPointFriend..o: ../include/BranchingPoint.h
../BranchingPoint/BranchingPointFriend..o: ../include/BranchingPointI.h
../BranchingPoint/BranchingPointFriend..o: ../include/LGMdecl.h
../BranchingPoint/BranchingPointFriend..o: ../include/LGMSymbols.h
../BranchingPoint/BranchingPointFriend..o: ../include/LGMUnits.h
../BranchingPoint/BranchingPointFriend..o: /usr/include/alloca.h
../BranchingPoint/BranchingPointFriend..o: /usr/include/assert.h
../BranchingPoint/BranchingPointFriend..o: /usr/include/bits/huge_val.h
../BranchingPoint/BranchingPointFriend..o: /usr/include/bits/local_lim.h
../BranchingPoint/BranchingPointFriend..o: /usr/include/bits/mathcalls.h
../BranchingPoint/BranchingPointFriend..o: /usr/include/bits/mathdef.h
../BranchingPoint/BranchingPointFriend..o: /usr/include/bits/nan.h
../BranchingPoint/BranchingPointFriend..o: /usr/include/bits/posix1_lim.h
../BranchingPoint/BranchingPointFriend..o: /usr/include/bits/pthreadtypes.h
../BranchingPoint/BranchingPointFriend..o: /usr/include/bits/sched.h
../BranchingPoint/BranchingPointFriend..o: /usr/include/bits/sigset.h
../BranchingPoint/BranchingPointFriend..o: /usr/include/bits/types.h
../BranchingPoint/BranchingPointFriend..o: /usr/include/bits/waitstatus.h
../BranchingPoint/BranchingPointFriend..o: /usr/include/bits/xopen_lim.h
../BranchingPoint/BranchingPointFriend..o: /usr/include/endian.h
../BranchingPoint/BranchingPointFriend..o: /usr/include/features.h
../BranchingPoint/BranchingPointFriend..o: /usr/include/g++-3/algorithm
../BranchingPoint/BranchingPointFriend..o: /usr/include/g++-3/iostream.h
../BranchingPoint/BranchingPointFriend..o: /usr/include/g++-3/list
../BranchingPoint/BranchingPointFriend..o: /usr/include/g++-3/map
../BranchingPoint/BranchingPointFriend..o: /usr/include/g++-3/numeric
../BranchingPoint/BranchingPointFriend..o: /usr/include/g++-3/stl_algobase.h
../BranchingPoint/BranchingPointFriend..o: /usr/include/g++-3/stl_algo.h
../BranchingPoint/BranchingPointFriend..o: /usr/include/g++-3/stl_alloc.h
../BranchingPoint/BranchingPointFriend..o: /usr/include/g++-3/stl_bvector.h
../BranchingPoint/BranchingPointFriend..o: /usr/include/g++-3/stl_construct.h
../BranchingPoint/BranchingPointFriend..o: /usr/include/g++-3/stl_function.h
../BranchingPoint/BranchingPointFriend..o: /usr/include/g++-3/stl_heap.h
../BranchingPoint/BranchingPointFriend..o: /usr/include/g++-3/stl_iterator.h
../BranchingPoint/BranchingPointFriend..o: /usr/include/g++-3/stl_list.h
../BranchingPoint/BranchingPointFriend..o: /usr/include/g++-3/stl_map.h
../BranchingPoint/BranchingPointFriend..o: /usr/include/g++-3/stl_multimap.h
../BranchingPoint/BranchingPointFriend..o: /usr/include/g++-3/stl_numeric.h
../BranchingPoint/BranchingPointFriend..o: /usr/include/g++-3/stl_pair.h
../BranchingPoint/BranchingPointFriend..o: /usr/include/g++-3/stl_relops.h
../BranchingPoint/BranchingPointFriend..o: /usr/include/g++-3/stl_tempbuf.h
../BranchingPoint/BranchingPointFriend..o: /usr/include/g++-3/stl_tree.h
../BranchingPoint/BranchingPointFriend..o: /usr/include/g++-3/stl_uninitialized.h
../BranchingPoint/BranchingPointFriend..o: /usr/include/g++-3/stl_vector.h
../BranchingPoint/BranchingPointFriend..o: /usr/include/g++-3/streambuf.h
../BranchingPoint/BranchingPointFriend..o: /usr/include/g++-3/stream.h
../BranchingPoint/BranchingPointFriend..o: /usr/include/g++-3/type_traits.h
../BranchingPoint/BranchingPointFriend..o: /usr/include/g++-3/vector
../BranchingPoint/BranchingPointFriend..o: /usr/include/_G_config.h
../BranchingPoint/BranchingPointFriend..o: /usr/include/gconv.h
../BranchingPoint/BranchingPointFriend..o: /usr/include/libio.h
../BranchingPoint/BranchingPointFriend..o: /usr/include/limits.h
../BranchingPoint/BranchingPointFriend..o: /usr/include/math.h
../BranchingPoint/BranchingPointFriend..o: /usr/include/stdlib.h
../BranchingPoint/BranchingPointFriend..o: /usr/include/string.h
../BranchingPoint/BranchingPointFriend..o: /usr/include/sys/select.h
../BranchingPoint/BranchingPointFriend..o: /usr/include/sys/types.h
../BranchingPoint/BranchingPointFriend..o: /usr/include/time.h
../BranchingPoint/BranchingPointFriend..o: /usr/include/wchar.h
../BranchingPoint/BranchingPointFriend..o: /usr/include/xlocale.h
../BranchingPoint/BranchingPointFriend..o: /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/exception
../BranchingPoint/BranchingPointFriend..o: /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/float.h
../BranchingPoint/BranchingPointFriend..o: /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/limits.h
../BranchingPoint/BranchingPointFriend..o: /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/new
../BranchingPoint/BranchingPointFriend..o: /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/new.h
../BranchingPoint/BranchingPointFriend..o: /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/stdarg.h
../BranchingPoint/BranchingPointFriend..o: /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/stddef.h
../BranchingPoint/BranchingPointFriend..o: /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/syslimits.h
../Bud/BudFriend..o: ../include/Bud.h ../include/BudI.h ../include/LGMdecl.h
../Bud/BudFriend..o: ../include/LGMSymbols.h ../include/LGMUnits.h
../Bud/BudFriend..o: ../include/TreeCompartment.h
../Bud/BudFriend..o: ../include/TreeCompartmentI.h /usr/include/alloca.h
../Bud/BudFriend..o: /usr/include/assert.h /usr/include/bits/huge_val.h
../Bud/BudFriend..o: /usr/include/bits/local_lim.h
../Bud/BudFriend..o: /usr/include/bits/mathcalls.h /usr/include/bits/mathdef.h
../Bud/BudFriend..o: /usr/include/bits/nan.h /usr/include/bits/posix1_lim.h
../Bud/BudFriend..o: /usr/include/bits/pthreadtypes.h
../Bud/BudFriend..o: /usr/include/bits/sched.h /usr/include/bits/sigset.h
../Bud/BudFriend..o: /usr/include/bits/types.h /usr/include/bits/waitstatus.h
../Bud/BudFriend..o: /usr/include/bits/xopen_lim.h /usr/include/endian.h
../Bud/BudFriend..o: /usr/include/features.h /usr/include/g++-3/iostream.h
../Bud/BudFriend..o: /usr/include/g++-3/map /usr/include/g++-3/stl_algobase.h
../Bud/BudFriend..o: /usr/include/g++-3/stl_alloc.h
../Bud/BudFriend..o: /usr/include/g++-3/stl_bvector.h
../Bud/BudFriend..o: /usr/include/g++-3/stl_construct.h
../Bud/BudFriend..o: /usr/include/g++-3/stl_function.h
../Bud/BudFriend..o: /usr/include/g++-3/stl_iterator.h
../Bud/BudFriend..o: /usr/include/g++-3/stl_map.h
../Bud/BudFriend..o: /usr/include/g++-3/stl_multimap.h
../Bud/BudFriend..o: /usr/include/g++-3/stl_pair.h
../Bud/BudFriend..o: /usr/include/g++-3/stl_relops.h
../Bud/BudFriend..o: /usr/include/g++-3/stl_tree.h
../Bud/BudFriend..o: /usr/include/g++-3/stl_uninitialized.h
../Bud/BudFriend..o: /usr/include/g++-3/stl_vector.h
../Bud/BudFriend..o: /usr/include/g++-3/streambuf.h
../Bud/BudFriend..o: /usr/include/g++-3/stream.h
../Bud/BudFriend..o: /usr/include/g++-3/type_traits.h
../Bud/BudFriend..o: /usr/include/g++-3/vector /usr/include/_G_config.h
../Bud/BudFriend..o: /usr/include/gconv.h /usr/include/libio.h
../Bud/BudFriend..o: /usr/include/limits.h /usr/include/math.h
../Bud/BudFriend..o: /usr/include/stdlib.h /usr/include/string.h
../Bud/BudFriend..o: /usr/include/sys/select.h /usr/include/sys/types.h
../Bud/BudFriend..o: /usr/include/time.h /usr/include/wchar.h
../Bud/BudFriend..o: /usr/include/xlocale.h
../Bud/BudFriend..o: /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/exception
../Bud/BudFriend..o: /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/float.h
../Bud/BudFriend..o: /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/limits.h
../Bud/BudFriend..o: /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/new
../Bud/BudFriend..o: /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/new.h
../Bud/BudFriend..o: /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/stdarg.h
../Bud/BudFriend..o: /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/stddef.h
../Bud/BudFriend..o: /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/syslimits.h
../Bud/Bud..o: ../include/Bud.h ../include/BudI.h ../include/LGMdecl.h
../Bud/Bud..o: ../include/LGMSymbols.h ../include/LGMUnits.h
../Bud/Bud..o: ../include/TreeCompartment.h ../include/TreeCompartmentI.h
../Bud/Bud..o: /usr/include/alloca.h /usr/include/assert.h
../Bud/Bud..o: /usr/include/bits/huge_val.h /usr/include/bits/local_lim.h
../Bud/Bud..o: /usr/include/bits/mathcalls.h /usr/include/bits/mathdef.h
../Bud/Bud..o: /usr/include/bits/nan.h /usr/include/bits/posix1_lim.h
../Bud/Bud..o: /usr/include/bits/pthreadtypes.h /usr/include/bits/sched.h
../Bud/Bud..o: /usr/include/bits/sigset.h /usr/include/bits/types.h
../Bud/Bud..o: /usr/include/bits/waitstatus.h /usr/include/bits/xopen_lim.h
../Bud/Bud..o: /usr/include/endian.h /usr/include/features.h
../Bud/Bud..o: /usr/include/g++-3/iostream.h /usr/include/g++-3/map
../Bud/Bud..o: /usr/include/g++-3/stl_algobase.h
../Bud/Bud..o: /usr/include/g++-3/stl_alloc.h /usr/include/g++-3/stl_bvector.h
../Bud/Bud..o: /usr/include/g++-3/stl_construct.h
../Bud/Bud..o: /usr/include/g++-3/stl_function.h
../Bud/Bud..o: /usr/include/g++-3/stl_iterator.h /usr/include/g++-3/stl_map.h
../Bud/Bud..o: /usr/include/g++-3/stl_multimap.h /usr/include/g++-3/stl_pair.h
../Bud/Bud..o: /usr/include/g++-3/stl_relops.h /usr/include/g++-3/stl_tree.h
../Bud/Bud..o: /usr/include/g++-3/stl_uninitialized.h
../Bud/Bud..o: /usr/include/g++-3/stl_vector.h /usr/include/g++-3/streambuf.h
../Bud/Bud..o: /usr/include/g++-3/stream.h /usr/include/g++-3/type_traits.h
../Bud/Bud..o: /usr/include/g++-3/vector /usr/include/_G_config.h
../Bud/Bud..o: /usr/include/gconv.h /usr/include/libio.h /usr/include/limits.h
../Bud/Bud..o: /usr/include/math.h /usr/include/stdlib.h /usr/include/string.h
../Bud/Bud..o: /usr/include/sys/select.h /usr/include/sys/types.h
../Bud/Bud..o: /usr/include/time.h /usr/include/wchar.h /usr/include/xlocale.h
../Bud/Bud..o: /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/exception
../Bud/Bud..o: /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/float.h
../Bud/Bud..o: /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/limits.h
../Bud/Bud..o: /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/new
../Bud/Bud..o: /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/new.h
../Bud/Bud..o: /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/stdarg.h
../Bud/Bud..o: /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/stddef.h
../Bud/Bud..o: /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/syslimits.h
../TreeCompartment/TreeCompartmentFriend..o: ../include/LGMdecl.h
../TreeCompartment/TreeCompartmentFriend..o: ../include/LGMSymbols.h
../TreeCompartment/TreeCompartmentFriend..o: ../include/LGMUnits.h
../TreeCompartment/TreeCompartmentFriend..o: ../include/TreeCompartment.h
../TreeCompartment/TreeCompartmentFriend..o: ../include/TreeCompartmentI.h
../TreeCompartment/TreeCompartmentFriend..o: /usr/include/alloca.h
../TreeCompartment/TreeCompartmentFriend..o: /usr/include/assert.h
../TreeCompartment/TreeCompartmentFriend..o: /usr/include/bits/huge_val.h
../TreeCompartment/TreeCompartmentFriend..o: /usr/include/bits/local_lim.h
../TreeCompartment/TreeCompartmentFriend..o: /usr/include/bits/mathcalls.h
../TreeCompartment/TreeCompartmentFriend..o: /usr/include/bits/mathdef.h
../TreeCompartment/TreeCompartmentFriend..o: /usr/include/bits/nan.h
../TreeCompartment/TreeCompartmentFriend..o: /usr/include/bits/posix1_lim.h
../TreeCompartment/TreeCompartmentFriend..o: /usr/include/bits/pthreadtypes.h
../TreeCompartment/TreeCompartmentFriend..o: /usr/include/bits/sched.h
../TreeCompartment/TreeCompartmentFriend..o: /usr/include/bits/sigset.h
../TreeCompartment/TreeCompartmentFriend..o: /usr/include/bits/types.h
../TreeCompartment/TreeCompartmentFriend..o: /usr/include/bits/waitstatus.h
../TreeCompartment/TreeCompartmentFriend..o: /usr/include/bits/xopen_lim.h
../TreeCompartment/TreeCompartmentFriend..o: /usr/include/endian.h
../TreeCompartment/TreeCompartmentFriend..o: /usr/include/features.h
../TreeCompartment/TreeCompartmentFriend..o: /usr/include/g++-3/iostream.h
../TreeCompartment/TreeCompartmentFriend..o: /usr/include/g++-3/map
../TreeCompartment/TreeCompartmentFriend..o: /usr/include/g++-3/stl_algobase.h
../TreeCompartment/TreeCompartmentFriend..o: /usr/include/g++-3/stl_alloc.h
../TreeCompartment/TreeCompartmentFriend..o: /usr/include/g++-3/stl_bvector.h
../TreeCompartment/TreeCompartmentFriend..o: /usr/include/g++-3/stl_construct.h
../TreeCompartment/TreeCompartmentFriend..o: /usr/include/g++-3/stl_function.h
../TreeCompartment/TreeCompartmentFriend..o: /usr/include/g++-3/stl_iterator.h
../TreeCompartment/TreeCompartmentFriend..o: /usr/include/g++-3/stl_map.h
../TreeCompartment/TreeCompartmentFriend..o: /usr/include/g++-3/stl_multimap.h
../TreeCompartment/TreeCompartmentFriend..o: /usr/include/g++-3/stl_pair.h
../TreeCompartment/TreeCompartmentFriend..o: /usr/include/g++-3/stl_relops.h
../TreeCompartment/TreeCompartmentFriend..o: /usr/include/g++-3/stl_tree.h
../TreeCompartment/TreeCompartmentFriend..o: /usr/include/g++-3/stl_uninitialized.h
../TreeCompartment/TreeCompartmentFriend..o: /usr/include/g++-3/stl_vector.h
../TreeCompartment/TreeCompartmentFriend..o: /usr/include/g++-3/streambuf.h
../TreeCompartment/TreeCompartmentFriend..o: /usr/include/g++-3/stream.h
../TreeCompartment/TreeCompartmentFriend..o: /usr/include/g++-3/type_traits.h
../TreeCompartment/TreeCompartmentFriend..o: /usr/include/g++-3/vector
../TreeCompartment/TreeCompartmentFriend..o: /usr/include/_G_config.h
../TreeCompartment/TreeCompartmentFriend..o: /usr/include/gconv.h
../TreeCompartment/TreeCompartmentFriend..o: /usr/include/libio.h
../TreeCompartment/TreeCompartmentFriend..o: /usr/include/limits.h
../TreeCompartment/TreeCompartmentFriend..o: /usr/include/math.h
../TreeCompartment/TreeCompartmentFriend..o: /usr/include/stdlib.h
../TreeCompartment/TreeCompartmentFriend..o: /usr/include/string.h
../TreeCompartment/TreeCompartmentFriend..o: /usr/include/sys/select.h
../TreeCompartment/TreeCompartmentFriend..o: /usr/include/sys/types.h
../TreeCompartment/TreeCompartmentFriend..o: /usr/include/time.h
../TreeCompartment/TreeCompartmentFriend..o: /usr/include/wchar.h
../TreeCompartment/TreeCompartmentFriend..o: /usr/include/xlocale.h
../TreeCompartment/TreeCompartmentFriend..o: /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/exception
../TreeCompartment/TreeCompartmentFriend..o: /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/float.h
../TreeCompartment/TreeCompartmentFriend..o: /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/limits.h
../TreeCompartment/TreeCompartmentFriend..o: /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/new
../TreeCompartment/TreeCompartmentFriend..o: /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/new.h
../TreeCompartment/TreeCompartmentFriend..o: /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/stdarg.h
../TreeCompartment/TreeCompartmentFriend..o: /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/stddef.h
../TreeCompartment/TreeCompartmentFriend..o: /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/syslimits.h
../TreeMetaFileParser/TreeMetaFileParser..o: ../include/TreeMetaFileParser.h
../TreeMetaFileParser/TreeMetaFileParser..o: /usr/include/alloca.h
../TreeMetaFileParser/TreeMetaFileParser..o: /usr/include/assert.h
../TreeMetaFileParser/TreeMetaFileParser..o: /usr/include/bits/pthreadtypes.h
../TreeMetaFileParser/TreeMetaFileParser..o: /usr/include/bits/sched.h
../TreeMetaFileParser/TreeMetaFileParser..o: /usr/include/bits/sigset.h
../TreeMetaFileParser/TreeMetaFileParser..o: /usr/include/bits/types.h
../TreeMetaFileParser/TreeMetaFileParser..o: /usr/include/bits/waitstatus.h
../TreeMetaFileParser/TreeMetaFileParser..o: /usr/include/ctype.h
../TreeMetaFileParser/TreeMetaFileParser..o: /usr/include/endian.h
../TreeMetaFileParser/TreeMetaFileParser..o: /usr/include/features.h
../TreeMetaFileParser/TreeMetaFileParser..o: /usr/include/g++-3/alloc.h
../TreeMetaFileParser/TreeMetaFileParser..o: /usr/include/g++-3/cassert
../TreeMetaFileParser/TreeMetaFileParser..o: /usr/include/g++-3/cctype
../TreeMetaFileParser/TreeMetaFileParser..o: /usr/include/g++-3/cstddef
../TreeMetaFileParser/TreeMetaFileParser..o: /usr/include/g++-3/cstring
../TreeMetaFileParser/TreeMetaFileParser..o: /usr/include/g++-3/fstream.h
../TreeMetaFileParser/TreeMetaFileParser..o: /usr/include/g++-3/iostream.h
../TreeMetaFileParser/TreeMetaFileParser..o: /usr/include/g++-3/iterator
../TreeMetaFileParser/TreeMetaFileParser..o: /usr/include/g++-3/std/bastring.cc
../TreeMetaFileParser/TreeMetaFileParser..o: /usr/include/g++-3/std/bastring.h
../TreeMetaFileParser/TreeMetaFileParser..o: /usr/include/g++-3/std/straits.h
../TreeMetaFileParser/TreeMetaFileParser..o: /usr/include/g++-3/stl_alloc.h
../TreeMetaFileParser/TreeMetaFileParser..o: /usr/include/g++-3/stl_iterator.h
../TreeMetaFileParser/TreeMetaFileParser..o: /usr/include/g++-3/stl_relops.h
../TreeMetaFileParser/TreeMetaFileParser..o: /usr/include/g++-3/streambuf.h
../TreeMetaFileParser/TreeMetaFileParser..o: /usr/include/g++-3/string
../TreeMetaFileParser/TreeMetaFileParser..o: /usr/include/_G_config.h
../TreeMetaFileParser/TreeMetaFileParser..o: /usr/include/gconv.h
../TreeMetaFileParser/TreeMetaFileParser..o: /usr/include/libio.h
../TreeMetaFileParser/TreeMetaFileParser..o: /usr/include/stdlib.h
../TreeMetaFileParser/TreeMetaFileParser..o: /usr/include/string.h
../TreeMetaFileParser/TreeMetaFileParser..o: /usr/include/sys/select.h
../TreeMetaFileParser/TreeMetaFileParser..o: /usr/include/sys/types.h
../TreeMetaFileParser/TreeMetaFileParser..o: /usr/include/time.h
../TreeMetaFileParser/TreeMetaFileParser..o: /usr/include/wchar.h
../TreeMetaFileParser/TreeMetaFileParser..o: /usr/include/xlocale.h
../TreeMetaFileParser/TreeMetaFileParser..o: /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/stdarg.h
../TreeMetaFileParser/TreeMetaFileParser..o: /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/stddef.h
../TreeSegment/BroadLeafMetabolism..o: ../include/BroadLeaf.h
../TreeSegment/BroadLeafMetabolism..o: ../include/LGMdecl.h
../TreeSegment/BroadLeafMetabolism..o: ../include/LGMSymbols.h
../TreeSegment/BroadLeafMetabolism..o: ../include/LGMUnits.h
../TreeSegment/BroadLeafMetabolism..o: /usr/include/alloca.h
../TreeSegment/BroadLeafMetabolism..o: /usr/include/assert.h
../TreeSegment/BroadLeafMetabolism..o: /usr/include/bits/huge_val.h
../TreeSegment/BroadLeafMetabolism..o: /usr/include/bits/local_lim.h
../TreeSegment/BroadLeafMetabolism..o: /usr/include/bits/mathcalls.h
../TreeSegment/BroadLeafMetabolism..o: /usr/include/bits/mathdef.h
../TreeSegment/BroadLeafMetabolism..o: /usr/include/bits/nan.h
../TreeSegment/BroadLeafMetabolism..o: /usr/include/bits/posix1_lim.h
../TreeSegment/BroadLeafMetabolism..o: /usr/include/bits/pthreadtypes.h
../TreeSegment/BroadLeafMetabolism..o: /usr/include/bits/sched.h
../TreeSegment/BroadLeafMetabolism..o: /usr/include/bits/sigset.h
../TreeSegment/BroadLeafMetabolism..o: /usr/include/bits/types.h
../TreeSegment/BroadLeafMetabolism..o: /usr/include/bits/waitstatus.h
../TreeSegment/BroadLeafMetabolism..o: /usr/include/bits/xopen_lim.h
../TreeSegment/BroadLeafMetabolism..o: /usr/include/endian.h
../TreeSegment/BroadLeafMetabolism..o: /usr/include/features.h
../TreeSegment/BroadLeafMetabolism..o: /usr/include/g++-3/iostream.h
../TreeSegment/BroadLeafMetabolism..o: /usr/include/g++-3/map
../TreeSegment/BroadLeafMetabolism..o: /usr/include/g++-3/stl_algobase.h
../TreeSegment/BroadLeafMetabolism..o: /usr/include/g++-3/stl_alloc.h
../TreeSegment/BroadLeafMetabolism..o: /usr/include/g++-3/stl_bvector.h
../TreeSegment/BroadLeafMetabolism..o: /usr/include/g++-3/stl_construct.h
../TreeSegment/BroadLeafMetabolism..o: /usr/include/g++-3/stl_function.h
../TreeSegment/BroadLeafMetabolism..o: /usr/include/g++-3/stl_iterator.h
../TreeSegment/BroadLeafMetabolism..o: /usr/include/g++-3/stl_map.h
../TreeSegment/BroadLeafMetabolism..o: /usr/include/g++-3/stl_multimap.h
../TreeSegment/BroadLeafMetabolism..o: /usr/include/g++-3/stl_pair.h
../TreeSegment/BroadLeafMetabolism..o: /usr/include/g++-3/stl_relops.h
../TreeSegment/BroadLeafMetabolism..o: /usr/include/g++-3/stl_tree.h
../TreeSegment/BroadLeafMetabolism..o: /usr/include/g++-3/stl_uninitialized.h
../TreeSegment/BroadLeafMetabolism..o: /usr/include/g++-3/stl_vector.h
../TreeSegment/BroadLeafMetabolism..o: /usr/include/g++-3/streambuf.h
../TreeSegment/BroadLeafMetabolism..o: /usr/include/g++-3/stream.h
../TreeSegment/BroadLeafMetabolism..o: /usr/include/g++-3/type_traits.h
../TreeSegment/BroadLeafMetabolism..o: /usr/include/g++-3/vector
../TreeSegment/BroadLeafMetabolism..o: /usr/include/_G_config.h
../TreeSegment/BroadLeafMetabolism..o: /usr/include/gconv.h
../TreeSegment/BroadLeafMetabolism..o: /usr/include/libio.h
../TreeSegment/BroadLeafMetabolism..o: /usr/include/limits.h
../TreeSegment/BroadLeafMetabolism..o: /usr/include/math.h
../TreeSegment/BroadLeafMetabolism..o: /usr/include/stdlib.h
../TreeSegment/BroadLeafMetabolism..o: /usr/include/string.h
../TreeSegment/BroadLeafMetabolism..o: /usr/include/sys/select.h
../TreeSegment/BroadLeafMetabolism..o: /usr/include/sys/types.h
../TreeSegment/BroadLeafMetabolism..o: /usr/include/time.h
../TreeSegment/BroadLeafMetabolism..o: /usr/include/wchar.h
../TreeSegment/BroadLeafMetabolism..o: /usr/include/xlocale.h
../TreeSegment/BroadLeafMetabolism..o: /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/exception
../TreeSegment/BroadLeafMetabolism..o: /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/float.h
../TreeSegment/BroadLeafMetabolism..o: /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/limits.h
../TreeSegment/BroadLeafMetabolism..o: /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/new
../TreeSegment/BroadLeafMetabolism..o: /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/new.h
../TreeSegment/BroadLeafMetabolism..o: /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/stdarg.h
../TreeSegment/BroadLeafMetabolism..o: /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/stddef.h
../TreeSegment/BroadLeafMetabolism..o: /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/syslimits.h
../TreeSegment/BroadLeaf..o: ../include/BroadLeaf.h ../include/LGMdecl.h
../TreeSegment/BroadLeaf..o: ../include/LGMSymbols.h ../include/LGMUnits.h
../TreeSegment/BroadLeaf..o: /usr/include/alloca.h /usr/include/assert.h
../TreeSegment/BroadLeaf..o: /usr/include/bits/huge_val.h
../TreeSegment/BroadLeaf..o: /usr/include/bits/local_lim.h
../TreeSegment/BroadLeaf..o: /usr/include/bits/mathcalls.h
../TreeSegment/BroadLeaf..o: /usr/include/bits/mathdef.h
../TreeSegment/BroadLeaf..o: /usr/include/bits/nan.h
../TreeSegment/BroadLeaf..o: /usr/include/bits/posix1_lim.h
../TreeSegment/BroadLeaf..o: /usr/include/bits/pthreadtypes.h
../TreeSegment/BroadLeaf..o: /usr/include/bits/sched.h
../TreeSegment/BroadLeaf..o: /usr/include/bits/sigset.h
../TreeSegment/BroadLeaf..o: /usr/include/bits/types.h
../TreeSegment/BroadLeaf..o: /usr/include/bits/waitstatus.h
../TreeSegment/BroadLeaf..o: /usr/include/bits/xopen_lim.h
../TreeSegment/BroadLeaf..o: /usr/include/endian.h /usr/include/features.h
../TreeSegment/BroadLeaf..o: /usr/include/g++-3/iostream.h
../TreeSegment/BroadLeaf..o: /usr/include/g++-3/map
../TreeSegment/BroadLeaf..o: /usr/include/g++-3/stl_algobase.h
../TreeSegment/BroadLeaf..o: /usr/include/g++-3/stl_alloc.h
../TreeSegment/BroadLeaf..o: /usr/include/g++-3/stl_bvector.h
../TreeSegment/BroadLeaf..o: /usr/include/g++-3/stl_construct.h
../TreeSegment/BroadLeaf..o: /usr/include/g++-3/stl_function.h
../TreeSegment/BroadLeaf..o: /usr/include/g++-3/stl_iterator.h
../TreeSegment/BroadLeaf..o: /usr/include/g++-3/stl_map.h
../TreeSegment/BroadLeaf..o: /usr/include/g++-3/stl_multimap.h
../TreeSegment/BroadLeaf..o: /usr/include/g++-3/stl_pair.h
../TreeSegment/BroadLeaf..o: /usr/include/g++-3/stl_relops.h
../TreeSegment/BroadLeaf..o: /usr/include/g++-3/stl_tree.h
../TreeSegment/BroadLeaf..o: /usr/include/g++-3/stl_uninitialized.h
../TreeSegment/BroadLeaf..o: /usr/include/g++-3/stl_vector.h
../TreeSegment/BroadLeaf..o: /usr/include/g++-3/streambuf.h
../TreeSegment/BroadLeaf..o: /usr/include/g++-3/stream.h
../TreeSegment/BroadLeaf..o: /usr/include/g++-3/type_traits.h
../TreeSegment/BroadLeaf..o: /usr/include/g++-3/vector
../TreeSegment/BroadLeaf..o: /usr/include/_G_config.h /usr/include/gconv.h
../TreeSegment/BroadLeaf..o: /usr/include/libio.h /usr/include/limits.h
../TreeSegment/BroadLeaf..o: /usr/include/math.h /usr/include/stdlib.h
../TreeSegment/BroadLeaf..o: /usr/include/string.h /usr/include/sys/select.h
../TreeSegment/BroadLeaf..o: /usr/include/sys/types.h /usr/include/time.h
../TreeSegment/BroadLeaf..o: /usr/include/wchar.h /usr/include/xlocale.h
../TreeSegment/BroadLeaf..o: /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/exception
../TreeSegment/BroadLeaf..o: /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/float.h
../TreeSegment/BroadLeaf..o: /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/limits.h
../TreeSegment/BroadLeaf..o: /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/new
../TreeSegment/BroadLeaf..o: /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/new.h
../TreeSegment/BroadLeaf..o: /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/stdarg.h
../TreeSegment/BroadLeaf..o: /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/stddef.h
../TreeSegment/BroadLeaf..o: /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/syslimits.h
../TreeSegment/CfTreeSegment..o: ../include/CfTreeSegment.h
../TreeSegment/CfTreeSegment..o: ../include/CfTreeSegmentI.h
../TreeSegment/CfTreeSegment..o: ../include/CfTreeSegmentMetabolismI.h
../TreeSegment/CfTreeSegment..o: ../include/LGMdecl.h ../include/LGMSymbols.h
../TreeSegment/CfTreeSegment..o: ../include/LGMUnits.h
../TreeSegment/CfTreeSegment..o: ../include/TreeCompartment.h
../TreeSegment/CfTreeSegment..o: ../include/TreeCompartmentI.h
../TreeSegment/CfTreeSegment..o: ../include/TreeSegment.h
../TreeSegment/CfTreeSegment..o: ../include/TreeSegmentI.h
../TreeSegment/CfTreeSegment..o: /usr/include/alloca.h /usr/include/assert.h
../TreeSegment/CfTreeSegment..o: /usr/include/bits/huge_val.h
../TreeSegment/CfTreeSegment..o: /usr/include/bits/local_lim.h
../TreeSegment/CfTreeSegment..o: /usr/include/bits/mathcalls.h
../TreeSegment/CfTreeSegment..o: /usr/include/bits/mathdef.h
../TreeSegment/CfTreeSegment..o: /usr/include/bits/nan.h
../TreeSegment/CfTreeSegment..o: /usr/include/bits/posix1_lim.h
../TreeSegment/CfTreeSegment..o: /usr/include/bits/pthreadtypes.h
../TreeSegment/CfTreeSegment..o: /usr/include/bits/sched.h
../TreeSegment/CfTreeSegment..o: /usr/include/bits/sigset.h
../TreeSegment/CfTreeSegment..o: /usr/include/bits/types.h
../TreeSegment/CfTreeSegment..o: /usr/include/bits/waitstatus.h
../TreeSegment/CfTreeSegment..o: /usr/include/bits/xopen_lim.h
../TreeSegment/CfTreeSegment..o: /usr/include/endian.h /usr/include/features.h
../TreeSegment/CfTreeSegment..o: /usr/include/g++-3/iostream.h
../TreeSegment/CfTreeSegment..o: /usr/include/g++-3/list
../TreeSegment/CfTreeSegment..o: /usr/include/g++-3/map
../TreeSegment/CfTreeSegment..o: /usr/include/g++-3/stl_algobase.h
../TreeSegment/CfTreeSegment..o: /usr/include/g++-3/stl_alloc.h
../TreeSegment/CfTreeSegment..o: /usr/include/g++-3/stl_bvector.h
../TreeSegment/CfTreeSegment..o: /usr/include/g++-3/stl_construct.h
../TreeSegment/CfTreeSegment..o: /usr/include/g++-3/stl_function.h
../TreeSegment/CfTreeSegment..o: /usr/include/g++-3/stl_iterator.h
../TreeSegment/CfTreeSegment..o: /usr/include/g++-3/stl_list.h
../TreeSegment/CfTreeSegment..o: /usr/include/g++-3/stl_map.h
../TreeSegment/CfTreeSegment..o: /usr/include/g++-3/stl_multimap.h
../TreeSegment/CfTreeSegment..o: /usr/include/g++-3/stl_pair.h
../TreeSegment/CfTreeSegment..o: /usr/include/g++-3/stl_relops.h
../TreeSegment/CfTreeSegment..o: /usr/include/g++-3/stl_tree.h
../TreeSegment/CfTreeSegment..o: /usr/include/g++-3/stl_uninitialized.h
../TreeSegment/CfTreeSegment..o: /usr/include/g++-3/stl_vector.h
../TreeSegment/CfTreeSegment..o: /usr/include/g++-3/streambuf.h
../TreeSegment/CfTreeSegment..o: /usr/include/g++-3/stream.h
../TreeSegment/CfTreeSegment..o: /usr/include/g++-3/type_traits.h
../TreeSegment/CfTreeSegment..o: /usr/include/g++-3/vector
../TreeSegment/CfTreeSegment..o: /usr/include/_G_config.h /usr/include/gconv.h
../TreeSegment/CfTreeSegment..o: /usr/include/libio.h /usr/include/limits.h
../TreeSegment/CfTreeSegment..o: /usr/include/math.h /usr/include/stdlib.h
../TreeSegment/CfTreeSegment..o: /usr/include/string.h
../TreeSegment/CfTreeSegment..o: /usr/include/sys/select.h
../TreeSegment/CfTreeSegment..o: /usr/include/sys/types.h /usr/include/time.h
../TreeSegment/CfTreeSegment..o: /usr/include/wchar.h /usr/include/xlocale.h
../TreeSegment/CfTreeSegment..o: /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/exception
../TreeSegment/CfTreeSegment..o: /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/float.h
../TreeSegment/CfTreeSegment..o: /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/limits.h
../TreeSegment/CfTreeSegment..o: /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/new
../TreeSegment/CfTreeSegment..o: /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/new.h
../TreeSegment/CfTreeSegment..o: /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/stdarg.h
../TreeSegment/CfTreeSegment..o: /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/stddef.h
../TreeSegment/CfTreeSegment..o: /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/syslimits.h
../TreeSegment/TreeSegmentFriend..o: ../include/LGMdecl.h
../TreeSegment/TreeSegmentFriend..o: ../include/LGMSymbols.h
../TreeSegment/TreeSegmentFriend..o: ../include/LGMUnits.h
../TreeSegment/TreeSegmentFriend..o: ../include/TreeCompartment.h
../TreeSegment/TreeSegmentFriend..o: ../include/TreeCompartmentI.h
../TreeSegment/TreeSegmentFriend..o: ../include/TreeSegment.h
../TreeSegment/TreeSegmentFriend..o: ../include/TreeSegmentI.h
../TreeSegment/TreeSegmentFriend..o: /usr/include/alloca.h
../TreeSegment/TreeSegmentFriend..o: /usr/include/assert.h
../TreeSegment/TreeSegmentFriend..o: /usr/include/bits/huge_val.h
../TreeSegment/TreeSegmentFriend..o: /usr/include/bits/local_lim.h
../TreeSegment/TreeSegmentFriend..o: /usr/include/bits/mathcalls.h
../TreeSegment/TreeSegmentFriend..o: /usr/include/bits/mathdef.h
../TreeSegment/TreeSegmentFriend..o: /usr/include/bits/nan.h
../TreeSegment/TreeSegmentFriend..o: /usr/include/bits/posix1_lim.h
../TreeSegment/TreeSegmentFriend..o: /usr/include/bits/pthreadtypes.h
../TreeSegment/TreeSegmentFriend..o: /usr/include/bits/sched.h
../TreeSegment/TreeSegmentFriend..o: /usr/include/bits/sigset.h
../TreeSegment/TreeSegmentFriend..o: /usr/include/bits/types.h
../TreeSegment/TreeSegmentFriend..o: /usr/include/bits/waitstatus.h
../TreeSegment/TreeSegmentFriend..o: /usr/include/bits/xopen_lim.h
../TreeSegment/TreeSegmentFriend..o: /usr/include/endian.h
../TreeSegment/TreeSegmentFriend..o: /usr/include/features.h
../TreeSegment/TreeSegmentFriend..o: /usr/include/g++-3/iostream.h
../TreeSegment/TreeSegmentFriend..o: /usr/include/g++-3/list
../TreeSegment/TreeSegmentFriend..o: /usr/include/g++-3/map
../TreeSegment/TreeSegmentFriend..o: /usr/include/g++-3/stl_algobase.h
../TreeSegment/TreeSegmentFriend..o: /usr/include/g++-3/stl_alloc.h
../TreeSegment/TreeSegmentFriend..o: /usr/include/g++-3/stl_bvector.h
../TreeSegment/TreeSegmentFriend..o: /usr/include/g++-3/stl_construct.h
../TreeSegment/TreeSegmentFriend..o: /usr/include/g++-3/stl_function.h
../TreeSegment/TreeSegmentFriend..o: /usr/include/g++-3/stl_iterator.h
../TreeSegment/TreeSegmentFriend..o: /usr/include/g++-3/stl_list.h
../TreeSegment/TreeSegmentFriend..o: /usr/include/g++-3/stl_map.h
../TreeSegment/TreeSegmentFriend..o: /usr/include/g++-3/stl_multimap.h
../TreeSegment/TreeSegmentFriend..o: /usr/include/g++-3/stl_pair.h
../TreeSegment/TreeSegmentFriend..o: /usr/include/g++-3/stl_relops.h
../TreeSegment/TreeSegmentFriend..o: /usr/include/g++-3/stl_tree.h
../TreeSegment/TreeSegmentFriend..o: /usr/include/g++-3/stl_uninitialized.h
../TreeSegment/TreeSegmentFriend..o: /usr/include/g++-3/stl_vector.h
../TreeSegment/TreeSegmentFriend..o: /usr/include/g++-3/streambuf.h
../TreeSegment/TreeSegmentFriend..o: /usr/include/g++-3/stream.h
../TreeSegment/TreeSegmentFriend..o: /usr/include/g++-3/type_traits.h
../TreeSegment/TreeSegmentFriend..o: /usr/include/g++-3/vector
../TreeSegment/TreeSegmentFriend..o: /usr/include/_G_config.h
../TreeSegment/TreeSegmentFriend..o: /usr/include/gconv.h /usr/include/libio.h
../TreeSegment/TreeSegmentFriend..o: /usr/include/limits.h /usr/include/math.h
../TreeSegment/TreeSegmentFriend..o: /usr/include/stdlib.h
../TreeSegment/TreeSegmentFriend..o: /usr/include/string.h
../TreeSegment/TreeSegmentFriend..o: /usr/include/sys/select.h
../TreeSegment/TreeSegmentFriend..o: /usr/include/sys/types.h
../TreeSegment/TreeSegmentFriend..o: /usr/include/time.h /usr/include/wchar.h
../TreeSegment/TreeSegmentFriend..o: /usr/include/xlocale.h
../TreeSegment/TreeSegmentFriend..o: /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/exception
../TreeSegment/TreeSegmentFriend..o: /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/float.h
../TreeSegment/TreeSegmentFriend..o: /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/limits.h
../TreeSegment/TreeSegmentFriend..o: /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/new
../TreeSegment/TreeSegmentFriend..o: /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/new.h
../TreeSegment/TreeSegmentFriend..o: /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/stdarg.h
../TreeSegment/TreeSegmentFriend..o: /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/stddef.h
../TreeSegment/TreeSegmentFriend..o: /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/syslimits.h
../TreeSegment/TreeSegment..o: ../include/LGMdecl.h ../include/LGMSymbols.h
../TreeSegment/TreeSegment..o: ../include/LGMUnits.h
../TreeSegment/TreeSegment..o: ../include/TreeCompartment.h
../TreeSegment/TreeSegment..o: ../include/TreeCompartmentI.h
../TreeSegment/TreeSegment..o: ../include/TreeSegment.h
../TreeSegment/TreeSegment..o: ../include/TreeSegmentI.h /usr/include/alloca.h
../TreeSegment/TreeSegment..o: /usr/include/assert.h
../TreeSegment/TreeSegment..o: /usr/include/bits/huge_val.h
../TreeSegment/TreeSegment..o: /usr/include/bits/local_lim.h
../TreeSegment/TreeSegment..o: /usr/include/bits/mathcalls.h
../TreeSegment/TreeSegment..o: /usr/include/bits/mathdef.h
../TreeSegment/TreeSegment..o: /usr/include/bits/nan.h
../TreeSegment/TreeSegment..o: /usr/include/bits/posix1_lim.h
../TreeSegment/TreeSegment..o: /usr/include/bits/pthreadtypes.h
../TreeSegment/TreeSegment..o: /usr/include/bits/sched.h
../TreeSegment/TreeSegment..o: /usr/include/bits/sigset.h
../TreeSegment/TreeSegment..o: /usr/include/bits/types.h
../TreeSegment/TreeSegment..o: /usr/include/bits/waitstatus.h
../TreeSegment/TreeSegment..o: /usr/include/bits/xopen_lim.h
../TreeSegment/TreeSegment..o: /usr/include/endian.h /usr/include/features.h
../TreeSegment/TreeSegment..o: /usr/include/g++-3/iostream.h
../TreeSegment/TreeSegment..o: /usr/include/g++-3/list /usr/include/g++-3/map
../TreeSegment/TreeSegment..o: /usr/include/g++-3/stl_algobase.h
../TreeSegment/TreeSegment..o: /usr/include/g++-3/stl_alloc.h
../TreeSegment/TreeSegment..o: /usr/include/g++-3/stl_bvector.h
../TreeSegment/TreeSegment..o: /usr/include/g++-3/stl_construct.h
../TreeSegment/TreeSegment..o: /usr/include/g++-3/stl_function.h
../TreeSegment/TreeSegment..o: /usr/include/g++-3/stl_iterator.h
../TreeSegment/TreeSegment..o: /usr/include/g++-3/stl_list.h
../TreeSegment/TreeSegment..o: /usr/include/g++-3/stl_map.h
../TreeSegment/TreeSegment..o: /usr/include/g++-3/stl_multimap.h
../TreeSegment/TreeSegment..o: /usr/include/g++-3/stl_pair.h
../TreeSegment/TreeSegment..o: /usr/include/g++-3/stl_relops.h
../TreeSegment/TreeSegment..o: /usr/include/g++-3/stl_tree.h
../TreeSegment/TreeSegment..o: /usr/include/g++-3/stl_uninitialized.h
../TreeSegment/TreeSegment..o: /usr/include/g++-3/stl_vector.h
../TreeSegment/TreeSegment..o: /usr/include/g++-3/streambuf.h
../TreeSegment/TreeSegment..o: /usr/include/g++-3/stream.h
../TreeSegment/TreeSegment..o: /usr/include/g++-3/type_traits.h
../TreeSegment/TreeSegment..o: /usr/include/g++-3/vector
../TreeSegment/TreeSegment..o: /usr/include/_G_config.h /usr/include/gconv.h
../TreeSegment/TreeSegment..o: /usr/include/libio.h /usr/include/limits.h
../TreeSegment/TreeSegment..o: /usr/include/math.h /usr/include/stdlib.h
../TreeSegment/TreeSegment..o: /usr/include/string.h /usr/include/sys/select.h
../TreeSegment/TreeSegment..o: /usr/include/sys/types.h /usr/include/time.h
../TreeSegment/TreeSegment..o: /usr/include/wchar.h /usr/include/xlocale.h
../TreeSegment/TreeSegment..o: /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/exception
../TreeSegment/TreeSegment..o: /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/float.h
../TreeSegment/TreeSegment..o: /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/limits.h
../TreeSegment/TreeSegment..o: /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/new
../TreeSegment/TreeSegment..o: /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/new.h
../TreeSegment/TreeSegment..o: /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/stdarg.h
../TreeSegment/TreeSegment..o: /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/stddef.h
../TreeSegment/TreeSegment..o: /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/syslimits.h
../Tree/TreeFriend..o: ../include/Algorithms.h ../include/AlgorithmsI.h
../Tree/TreeFriend..o: ../include/Axis.h ../include/AxisI.h
../Tree/TreeFriend..o: ../include/BranchingPoint.h
../Tree/TreeFriend..o: ../include/BranchingPointI.h ../include/BroadLeaf.h
../Tree/TreeFriend..o: ../include/Bud.h ../include/BudI.h
../Tree/TreeFriend..o: ../include/CfTreeSegment.h ../include/CfTreeSegmentI.h
../Tree/TreeFriend..o: ../include/CfTreeSegmentMetabolismI.h
../Tree/TreeFriend..o: ../include/DefaultBud.h ../include/HwTreeSegment.h
../Tree/TreeFriend..o: ../include/HwTreeSegmentI.h
../Tree/TreeFriend..o: ../include/HwTreeSegmentMetabolismI.h
../Tree/TreeFriend..o: ../include/LGMdecl.h ../include/LGMSymbols.h
../Tree/TreeFriend..o: ../include/LGMUnits.h ../include/RootSystem.h
../Tree/TreeFriend..o: ../include/TreeBookkeepingI.h
../Tree/TreeFriend..o: ../include/TreeCompartment.h
../Tree/TreeFriend..o: ../include/TreeCompartmentI.h ../include/TreeFunctor.h
../Tree/TreeFriend..o: ../include/TreeFunctorI.h ../include/Tree.h
../Tree/TreeFriend..o: ../include/TreeI.h ../include/TreeMetabolismI.h
../Tree/TreeFriend..o: ../include/TreeMetaFileParser.h
../Tree/TreeFriend..o: ../include/TreeSegment.h ../include/TreeSegmentI.h
../Tree/TreeFriend..o: /usr/include/alloca.h /usr/include/assert.h
../Tree/TreeFriend..o: /usr/include/bits/huge_val.h
../Tree/TreeFriend..o: /usr/include/bits/local_lim.h
../Tree/TreeFriend..o: /usr/include/bits/mathcalls.h
../Tree/TreeFriend..o: /usr/include/bits/mathdef.h /usr/include/bits/nan.h
../Tree/TreeFriend..o: /usr/include/bits/posix1_lim.h
../Tree/TreeFriend..o: /usr/include/bits/pthreadtypes.h
../Tree/TreeFriend..o: /usr/include/bits/sched.h /usr/include/bits/sigset.h
../Tree/TreeFriend..o: /usr/include/bits/types.h
../Tree/TreeFriend..o: /usr/include/bits/waitstatus.h
../Tree/TreeFriend..o: /usr/include/bits/xopen_lim.h /usr/include/ctype.h
../Tree/TreeFriend..o: /usr/include/endian.h /usr/include/features.h
../Tree/TreeFriend..o: /usr/include/g++-3/algobase.h
../Tree/TreeFriend..o: /usr/include/g++-3/algorithm /usr/include/g++-3/cassert
../Tree/TreeFriend..o: /usr/include/g++-3/cctype /usr/include/g++-3/cstddef
../Tree/TreeFriend..o: /usr/include/g++-3/fstream.h
../Tree/TreeFriend..o: /usr/include/g++-3/functional
../Tree/TreeFriend..o: /usr/include/g++-3/function.h
../Tree/TreeFriend..o: /usr/include/g++-3/iostream.h
../Tree/TreeFriend..o: /usr/include/g++-3/iterator
../Tree/TreeFriend..o: /usr/include/g++-3/iterator.h /usr/include/g++-3/list
../Tree/TreeFriend..o: /usr/include/g++-3/map /usr/include/g++-3/numeric
../Tree/TreeFriend..o: /usr/include/g++-3/std/bastring.cc
../Tree/TreeFriend..o: /usr/include/g++-3/std/bastring.h
../Tree/TreeFriend..o: /usr/include/g++-3/std/straits.h
../Tree/TreeFriend..o: /usr/include/g++-3/stl_algobase.h
../Tree/TreeFriend..o: /usr/include/g++-3/stl_algo.h
../Tree/TreeFriend..o: /usr/include/g++-3/stl_alloc.h
../Tree/TreeFriend..o: /usr/include/g++-3/stl_bvector.h
../Tree/TreeFriend..o: /usr/include/g++-3/stl_construct.h
../Tree/TreeFriend..o: /usr/include/g++-3/stl_function.h
../Tree/TreeFriend..o: /usr/include/g++-3/stl_heap.h
../Tree/TreeFriend..o: /usr/include/g++-3/stl_iterator.h
../Tree/TreeFriend..o: /usr/include/g++-3/stl_list.h
../Tree/TreeFriend..o: /usr/include/g++-3/stl_map.h
../Tree/TreeFriend..o: /usr/include/g++-3/stl_multimap.h
../Tree/TreeFriend..o: /usr/include/g++-3/stl_numeric.h
../Tree/TreeFriend..o: /usr/include/g++-3/stl_pair.h
../Tree/TreeFriend..o: /usr/include/g++-3/stl_raw_storage_iter.h
../Tree/TreeFriend..o: /usr/include/g++-3/stl_relops.h
../Tree/TreeFriend..o: /usr/include/g++-3/stl_tempbuf.h
../Tree/TreeFriend..o: /usr/include/g++-3/stl_tree.h
../Tree/TreeFriend..o: /usr/include/g++-3/stl_uninitialized.h
../Tree/TreeFriend..o: /usr/include/g++-3/stl_vector.h
../Tree/TreeFriend..o: /usr/include/g++-3/streambuf.h
../Tree/TreeFriend..o: /usr/include/g++-3/stream.h /usr/include/g++-3/string
../Tree/TreeFriend..o: /usr/include/g++-3/type_traits.h
../Tree/TreeFriend..o: /usr/include/g++-3/vector /usr/include/g++-3/vector.h
../Tree/TreeFriend..o: /usr/include/_G_config.h /usr/include/gconv.h
../Tree/TreeFriend..o: /usr/include/libio.h /usr/include/limits.h
../Tree/TreeFriend..o: /usr/include/math.h /usr/include/stdio.h
../Tree/TreeFriend..o: /usr/include/stdlib.h /usr/include/string.h
../Tree/TreeFriend..o: /usr/include/sys/select.h /usr/include/sys/types.h
../Tree/TreeFriend..o: /usr/include/time.h /usr/include/wchar.h
../Tree/TreeFriend..o: /usr/include/xlocale.h
../Tree/TreeFriend..o: /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/exception
../Tree/TreeFriend..o: /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/float.h
../Tree/TreeFriend..o: /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/limits.h
../Tree/TreeFriend..o: /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/new
../Tree/TreeFriend..o: /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/new.h
../Tree/TreeFriend..o: /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/stdarg.h
../Tree/TreeFriend..o: /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/stddef.h
../Tree/TreeFriend..o: /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/syslimits.h
../Tree/TreeFriend..o: /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/typeinfo
../Tree/Tree..o: ../include/Algorithms.h ../include/AlgorithmsI.h
../Tree/Tree..o: ../include/Axis.h ../include/AxisI.h
../Tree/Tree..o: ../include/BranchingPoint.h ../include/BranchingPointI.h
../Tree/Tree..o: ../include/BroadLeaf.h ../include/Bud.h ../include/BudI.h
../Tree/Tree..o: ../include/CfTreeSegment.h ../include/CfTreeSegmentI.h
../Tree/Tree..o: ../include/CfTreeSegmentMetabolismI.h ../include/DefaultBud.h
../Tree/Tree..o: ../include/HwTreeSegment.h ../include/HwTreeSegmentI.h
../Tree/Tree..o: ../include/HwTreeSegmentMetabolismI.h ../include/LGMdecl.h
../Tree/Tree..o: ../include/LGMSymbols.h ../include/LGMUnits.h
../Tree/Tree..o: ../include/RootSystem.h ../include/TreeBookkeepingI.h
../Tree/Tree..o: ../include/TreeCompartment.h ../include/TreeCompartmentI.h
../Tree/Tree..o: ../include/TreeFunctor.h ../include/TreeFunctorI.h
../Tree/Tree..o: ../include/Tree.h ../include/TreeI.h
../Tree/Tree..o: ../include/TreeMetabolismI.h ../include/TreeMetaFileParser.h
../Tree/Tree..o: ../include/TreeSegment.h ../include/TreeSegmentI.h
../Tree/Tree..o: /usr/include/alloca.h /usr/include/assert.h
../Tree/Tree..o: /usr/include/bits/huge_val.h /usr/include/bits/local_lim.h
../Tree/Tree..o: /usr/include/bits/mathcalls.h /usr/include/bits/mathdef.h
../Tree/Tree..o: /usr/include/bits/nan.h /usr/include/bits/posix1_lim.h
../Tree/Tree..o: /usr/include/bits/pthreadtypes.h /usr/include/bits/sched.h
../Tree/Tree..o: /usr/include/bits/sigset.h /usr/include/bits/types.h
../Tree/Tree..o: /usr/include/bits/waitstatus.h /usr/include/bits/xopen_lim.h
../Tree/Tree..o: /usr/include/ctype.h /usr/include/endian.h
../Tree/Tree..o: /usr/include/features.h /usr/include/g++-3/algobase.h
../Tree/Tree..o: /usr/include/g++-3/algorithm /usr/include/g++-3/cassert
../Tree/Tree..o: /usr/include/g++-3/cctype /usr/include/g++-3/cstddef
../Tree/Tree..o: /usr/include/g++-3/fstream.h /usr/include/g++-3/functional
../Tree/Tree..o: /usr/include/g++-3/function.h /usr/include/g++-3/iostream.h
../Tree/Tree..o: /usr/include/g++-3/iterator /usr/include/g++-3/iterator.h
../Tree/Tree..o: /usr/include/g++-3/list /usr/include/g++-3/map
../Tree/Tree..o: /usr/include/g++-3/numeric /usr/include/g++-3/std/bastring.cc
../Tree/Tree..o: /usr/include/g++-3/std/bastring.h
../Tree/Tree..o: /usr/include/g++-3/std/straits.h
../Tree/Tree..o: /usr/include/g++-3/stl_algobase.h
../Tree/Tree..o: /usr/include/g++-3/stl_algo.h /usr/include/g++-3/stl_alloc.h
../Tree/Tree..o: /usr/include/g++-3/stl_bvector.h
../Tree/Tree..o: /usr/include/g++-3/stl_construct.h
../Tree/Tree..o: /usr/include/g++-3/stl_function.h
../Tree/Tree..o: /usr/include/g++-3/stl_heap.h
../Tree/Tree..o: /usr/include/g++-3/stl_iterator.h
../Tree/Tree..o: /usr/include/g++-3/stl_list.h /usr/include/g++-3/stl_map.h
../Tree/Tree..o: /usr/include/g++-3/stl_multimap.h
../Tree/Tree..o: /usr/include/g++-3/stl_numeric.h
../Tree/Tree..o: /usr/include/g++-3/stl_pair.h
../Tree/Tree..o: /usr/include/g++-3/stl_raw_storage_iter.h
../Tree/Tree..o: /usr/include/g++-3/stl_relops.h
../Tree/Tree..o: /usr/include/g++-3/stl_tempbuf.h
../Tree/Tree..o: /usr/include/g++-3/stl_tree.h
../Tree/Tree..o: /usr/include/g++-3/stl_uninitialized.h
../Tree/Tree..o: /usr/include/g++-3/stl_vector.h
../Tree/Tree..o: /usr/include/g++-3/streambuf.h /usr/include/g++-3/stream.h
../Tree/Tree..o: /usr/include/g++-3/string /usr/include/g++-3/type_traits.h
../Tree/Tree..o: /usr/include/g++-3/vector /usr/include/g++-3/vector.h
../Tree/Tree..o: /usr/include/_G_config.h /usr/include/gconv.h
../Tree/Tree..o: /usr/include/libio.h /usr/include/limits.h
../Tree/Tree..o: /usr/include/math.h /usr/include/stdio.h
../Tree/Tree..o: /usr/include/stdlib.h /usr/include/string.h
../Tree/Tree..o: /usr/include/sys/select.h /usr/include/sys/types.h
../Tree/Tree..o: /usr/include/time.h /usr/include/wchar.h
../Tree/Tree..o: /usr/include/xlocale.h
../Tree/Tree..o: /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/exception
../Tree/Tree..o: /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/float.h
../Tree/Tree..o: /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/limits.h
../Tree/Tree..o: /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/new
../Tree/Tree..o: /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/new.h
../Tree/Tree..o: /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/stdarg.h
../Tree/Tree..o: /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/stddef.h
../Tree/Tree..o: /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/syslimits.h
../Tree/Tree..o: /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/typeinfo
