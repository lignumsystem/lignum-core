#To compile "algorithms" on SGI type 
#    make algorithms
#To compile with g++ in Linux type (or copy paste)
#    make "CCC=g++" "CCCFLAGS=-c" "OPTIMIZE=-O" "ARCOMMAND=ar"  "ARCOMMANDFLAGS=rv" algorithms 

SRC= Turtle.cc main.cc
OBJ  = Turtle.o main.o

CCC = CC  -LANG:std

#OPTIMIZE = -Ofast=ip28 -IPA
OPTIMIZE   = -g 

ARCOMMAND =  $(CCC) -ar  
ARCOMMANDFLAGS = -o 

SUPPRESS = #-w 1155 -w 1183

CCCFLAGS = -c  #-prelink -ptused   -ptv  #  -fullwarn 

INCLUDE = -I. -I../../c++adt/include -I../../Firmament/include \
          -I../../stl-lignum/include -I../Generate -I../Globals

STL     = -I/usr/include/CC

LIBFLAGS = -L../../c++adt/lib -L../../stl-lignum/lib -L../../Firmament/lib -L../Generate/Linux.out

LIB1   = libc++adt.a
LIB2   = libLGM.a
LIB3   = libsky.a
LIB4   = liblengine.a

LIBADT = -lc++adt
LIBLGM = -lLGM
LIBSKY = -lsky
LIBMATH  = -lm 
LIBLENGINE = -llengine 

LIBS     = $(LIBLGM) $(LIBSKY) $(LIBADT) $(LIBMATH) $(LIBLENGINE)

PROGFILES = program-files.html

.SUFFIXES: .o .cc

l2lignum: $(OBJ) ../lsys/lsys.o $(LIB1) $(LIB3)  $(LIB2) 
	$(CCC)  -o $@ $(INCLUDE) $(OPTIMIZE) $(OBJ) ../lsys/lsys.o $(LIBFLAGS) $(LIBS)

lignux: 
	make "CCC=g++" "CCCFLAGS=-c" "OPTIMIZE=-O" "ARCOMMAND=ar"  "ARCOMMANDFLAGS=rv" l2lignum

../lsys/lsys.o:
	(cd ../lsys; make lsys.o)

$(LIB1):
	(cd ../../c++adt/lib; make "CCC=$(CCC)" "CCCFLAGS=$(CCCFLAGS)" \
         "OPTIMIZE=$(OPTIMIZE)" "AR=$(ARCOMMAND)"  "ARFLAGS = $(ARCOMMANDFLAGS)" $@)

$(LIB2):
	(cd ../../stl-lignum/lib; make "CCC=$(CCC)" "CCCFLAGS=$(CCCFLAGS)" "OPTIMIZE=$(OPTIMIZE)" "AR=$(ARCOMMAND)" \
         "ARFLAGS = $(ARCOMMANDFLAGS)" $@)

$(LIB3):
	(cd ../../Firmament; make "CCC=$(CCC)" "CCCFLAGS=$(CCCFLAGS)" \
         "OPTIMIZE=$(OPTIMIZE)"  "AR=$(ARCOMMAND)"  "ARFLAGS = $(ARCOMMANDFLAGS)" $@)
$(LIB4):
	(cd ../Generate; make lib)
.cc.o: 
	$(CCC) $(OPTIMIZE) $(SUPPRESS) $(CCCFLAGS) $(INCLUDE)  $< -o $@

html:
	enscript -E --color -Whtml --toc -p$(PROGFILES) ./include/*.h ./*/*.cc
changelog:
	rm -rf ChangeLog
	rcs2log . > ChangeLog
clean:
	rm -rf $(OBJ)  core l2lignum ii_files
	rm -rf ./*/ii_files
distclean: clean
	(cd ../c++adt/lib; make distclean)
	(cd ../Firmament; make distclean)
	(cd lib; make distclean)
depend:
	makedepend $(INCLUDE) $(CCCINCLUDE) $(STL) $(SRC)  

# DO NOT DELETE


main..o: ../../c++adt/include/boolean.h
main..o: ../../c++adt/include/ConnectionMatrix.h
main..o: ../../c++adt/include/ConnectionMatrixI.h
main..o: ../../c++adt/include/DListElement.h ../../c++adt/include/DList.h
main..o: ../../c++adt/include/Ellipsis.h ../../c++adt/include/Lex.h
main..o: ../../c++adt/include/mathsym.h ../../c++adt/include/ParametricCurve.h
main..o: ../../c++adt/include/Point.h ../../c++adt/include/PointI.h
main..o: ../../c++adt/include/PositionVector.h ../../c++adt/include/RMatrix.h
main..o: ../../c++adt/include/Rotation.h ../../c++adt/include/Table.h
main..o: ../../c++adt/include/TableI.h ../../c++adt/include/TMatrix.h
main..o: ../../c++adt/include/TMatrixI.h ../../Firmament/include/Firmament.h
main..o: ../../Firmament/include/FirmamentWithMask.h ../Generate/lstring.h
main..o: ../Generate/lstriter.h ../Generate/succstor.h ../Globals/lglobal.h
main..o: ../Globals/lsysintrfc.h L2Lignum.h
main..o: ../../stl-lignum/include/Algorithms.h
main..o: ../../stl-lignum/include/AlgorithmsI.h
main..o: ../../stl-lignum/include/Axis.h ../../stl-lignum/include/AxisI.h
main..o: ../../stl-lignum/include/BranchingPoint.h
main..o: ../../stl-lignum/include/BranchingPointI.h
main..o: ../../stl-lignum/include/BroadLeaf.h ../../stl-lignum/include/Bud.h
main..o: ../../stl-lignum/include/BudI.h
main..o: ../../stl-lignum/include/CfTreeFunctor.h
main..o: ../../stl-lignum/include/CfTreeFunctorI.h
main..o: ../../stl-lignum/include/CfTreeSegment.h
main..o: ../../stl-lignum/include/CfTreeSegmentI.h
main..o: ../../stl-lignum/include/CfTreeSegmentMetabolismI.h
main..o: ../../stl-lignum/include/DefaultBud.h
main..o: ../../stl-lignum/include/HwTreeSegment.h
main..o: ../../stl-lignum/include/HwTreeSegmentI.h
main..o: ../../stl-lignum/include/HwTreeSegmentMetabolismI.h
main..o: ../../stl-lignum/include/LGMdecl.h
main..o: ../../stl-lignum/include/LGMSymbols.h
main..o: ../../stl-lignum/include/LGMUnits.h ../../stl-lignum/include/Lignum.h
main..o: ../../stl-lignum/include/MyTreeSegment.h
main..o: ../../stl-lignum/include/RootSystem.h
main..o: ../../stl-lignum/include/TreeBookkeeping.h
main..o: ../../stl-lignum/include/TreeBookkeepingI.h
main..o: ../../stl-lignum/include/TreeCompartment.h
main..o: ../../stl-lignum/include/TreeCompartmentI.h
main..o: ../../stl-lignum/include/TreeFunctor.h
main..o: ../../stl-lignum/include/TreeFunctorI.h
main..o: ../../stl-lignum/include/Tree.h ../../stl-lignum/include/TreeI.h
main..o: ../../stl-lignum/include/TreeMetabolism.h
main..o: ../../stl-lignum/include/TreeMetabolismI.h
main..o: ../../stl-lignum/include/TreeMetaFileParser.h
main..o: ../../stl-lignum/include/TreeRadiation.h
main..o: ../../stl-lignum/include/TreeRadiationI.h
main..o: ../../stl-lignum/include/TreeSegment.h
main..o: ../../stl-lignum/include/TreeSegmentI.h
main..o: ../../stl-lignum/include/TreeSegmentWithFlow.h Turtle.h
main..o: /usr/include/alloca.h /usr/include/assert.h
main..o: /usr/include/bits/confname.h /usr/include/bits/environments.h
main..o: /usr/include/bits/huge_val.h /usr/include/bits/local_lim.h
main..o: /usr/include/bits/mathcalls.h /usr/include/bits/mathdef.h
main..o: /usr/include/bits/nan.h /usr/include/bits/posix1_lim.h
main..o: /usr/include/bits/pthreadtypes.h /usr/include/bits/sched.h
main..o: /usr/include/bits/sigset.h /usr/include/bits/types.h
main..o: /usr/include/bits/waitstatus.h /usr/include/bits/xopen_lim.h
main..o: /usr/include/ctype.h /usr/include/endian.h /usr/include/features.h
main..o: /usr/include/g++-3/algorithm /usr/include/g++-3/cassert
main..o: /usr/include/g++-3/cctype /usr/include/g++-3/cstddef
main..o: /usr/include/g++-3/fstream /usr/include/g++-3/fstream.h
main..o: /usr/include/g++-3/functional /usr/include/g++-3/iostream
main..o: /usr/include/g++-3/iostream.h /usr/include/g++-3/iterator
main..o: /usr/include/g++-3/list /usr/include/g++-3/map
main..o: /usr/include/g++-3/numeric /usr/include/g++-3/stack
main..o: /usr/include/g++-3/std/bastring.cc /usr/include/g++-3/std/bastring.h
main..o: /usr/include/g++-3/std/straits.h /usr/include/g++-3/stl_algobase.h
main..o: /usr/include/g++-3/stl_algo.h /usr/include/g++-3/stl_alloc.h
main..o: /usr/include/g++-3/stl_bvector.h /usr/include/g++-3/stl_construct.h
main..o: /usr/include/g++-3/stl_deque.h /usr/include/g++-3/stl_function.h
main..o: /usr/include/g++-3/stl_heap.h /usr/include/g++-3/stl_iterator.h
main..o: /usr/include/g++-3/stl_list.h /usr/include/g++-3/stl_map.h
main..o: /usr/include/g++-3/stl_multimap.h /usr/include/g++-3/stl_numeric.h
main..o: /usr/include/g++-3/stl_pair.h /usr/include/g++-3/stl_relops.h
main..o: /usr/include/g++-3/stl_stack.h /usr/include/g++-3/stl_tempbuf.h
main..o: /usr/include/g++-3/stl_tree.h /usr/include/g++-3/stl_uninitialized.h
main..o: /usr/include/g++-3/stl_vector.h /usr/include/g++-3/streambuf.h
main..o: /usr/include/g++-3/string /usr/include/g++-3/type_traits.h
main..o: /usr/include/g++-3/vector /usr/include/_G_config.h
main..o: /usr/include/gconv.h /usr/include/getopt.h /usr/include/libio.h
main..o: /usr/include/limits.h /usr/include/math.h /usr/include/stdio.h
main..o: /usr/include/stdlib.h /usr/include/string.h /usr/include/sys/select.h
main..o: /usr/include/sys/types.h /usr/include/time.h /usr/include/unistd.h
main..o: /usr/include/wchar.h /usr/include/xlocale.h
main..o: /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/exception
main..o: /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/float.h
main..o: /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/limits.h
main..o: /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/new
main..o: /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/new.h
main..o: /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/stdarg.h
main..o: /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/stddef.h
main..o: /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/syslimits.h
main..o: /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/typeinfo
Turtle..o: ../../c++adt/include/mathsym.h ../../c++adt/include/Point.h
Turtle..o: ../../c++adt/include/PointI.h ../../c++adt/include/PositionVector.h
Turtle..o: ../../c++adt/include/RMatrix.h ../../c++adt/include/Rotation.h
Turtle..o: ../../c++adt/include/TMatrix.h ../../c++adt/include/TMatrixI.h
Turtle..o: Turtle.h /usr/include/alloca.h /usr/include/assert.h
Turtle..o: /usr/include/bits/huge_val.h /usr/include/bits/local_lim.h
Turtle..o: /usr/include/bits/mathcalls.h /usr/include/bits/mathdef.h
Turtle..o: /usr/include/bits/nan.h /usr/include/bits/posix1_lim.h
Turtle..o: /usr/include/bits/pthreadtypes.h /usr/include/bits/sched.h
Turtle..o: /usr/include/bits/sigset.h /usr/include/bits/types.h
Turtle..o: /usr/include/bits/waitstatus.h /usr/include/bits/xopen_lim.h
Turtle..o: /usr/include/endian.h /usr/include/features.h
Turtle..o: /usr/include/g++-3/iostream /usr/include/g++-3/iostream.h
Turtle..o: /usr/include/g++-3/stl_algobase.h /usr/include/g++-3/stl_alloc.h
Turtle..o: /usr/include/g++-3/stl_bvector.h /usr/include/g++-3/stl_construct.h
Turtle..o: /usr/include/g++-3/stl_iterator.h /usr/include/g++-3/stl_pair.h
Turtle..o: /usr/include/g++-3/stl_relops.h
Turtle..o: /usr/include/g++-3/stl_uninitialized.h
Turtle..o: /usr/include/g++-3/stl_vector.h /usr/include/g++-3/streambuf.h
Turtle..o: /usr/include/g++-3/type_traits.h /usr/include/g++-3/vector
Turtle..o: /usr/include/_G_config.h /usr/include/gconv.h /usr/include/libio.h
Turtle..o: /usr/include/limits.h /usr/include/math.h /usr/include/stdlib.h
Turtle..o: /usr/include/string.h /usr/include/sys/select.h
Turtle..o: /usr/include/sys/types.h /usr/include/time.h /usr/include/wchar.h
Turtle..o: /usr/include/xlocale.h
Turtle..o: /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/exception
Turtle..o: /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/float.h
Turtle..o: /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/limits.h
Turtle..o: /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/new
Turtle..o: /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/new.h
Turtle..o: /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/stdarg.h
Turtle..o: /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/stddef.h
Turtle..o: /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/syslimits.h
