#To compile "algorithms" on SGI type 
#    make algorithms
#To compile with g++ in Linux type (or copy paste)
#    make "CCC=g++" "CCCFLAGS=-c" "OPTIMIZE=-O" "ARCOMMAND=ar"  "ARCOMMANDFLAGS=rv" algorithms 

SRC= Turtle.cc main.cc
OBJ  = Turtle.o main.o

CCC = CC -64 -LANG:std

#OPTIMIZE = -Ofast=ip28 -IPA
OPTIMIZE   = -g 

ARCOMMAND =  $(CCC) -ar  
ARCOMMANDFLAGS = -o 

SUPPRESS = #-w 1155 -w 1183

CCCFLAGS = -c  #-prelink -ptused   -ptv  #  -fullwarn 

INCLUDE = -I. -I../../c++adt/include -I../../Firmament/include \
          -I../../stl-lignum/include -I../Generate -I../Globals \
           -I../../Graphics

STL     = -I/usr/include/CC

LIBFLAGS = -L../../c++adt/lib -L../../stl-lignum/lib -L../../Firmament/lib \
           -L../Generate/IRIX64.out -L../Generate/Linux.out \
           -L../../Graphics -L/usr/X11R6/lib

LIB1   = libc++adt.a
LIB2   = libLGM.a
LIB3   = libsky.a
LIB4   = liblengine.a
LIB5   = libVisual.a

LIBADT = -lc++adt
LIBLGM = -lLGM
LIBSKY = -lsky
LIBMATH  = -lm 
LIBLENGINE = -llengine 
LIBVISUAL = -lVisual

LIBOGL =  -lglut -lGL -lGLU -lX11 -lXext -lXmu 
LIBS     =  $(LIBVISUAL) $(LIBLGM) $(LIBSKY) $(LIBADT) $(LIBOGL) \
            $(LIBMATH) $(LIBLENGINE) 

PROGFILES = program-files.html

.SUFFIXES: .o .cc

l2lignum: $(OBJ) ../lsys/lsys.o $(LIB1) $(LIB3)  $(LIB2) 
	$(CCC)  -o $@ $(INCLUDE) $(OPTIMIZE) $(OBJ) ../lsys/lsys.o $(LIBFLAGS) $(LIBS)

lignux: 
	make "CCC=g++" "CCCFLAGS=-c" "OPTIMIZE=-O" "ARCOMMAND=ar"  "ARCOMMANDFLAGS=rv" l2lignum

../lsys/lsys.o: ../lsys/lsys.l
	(cd ../lsys;make clean; make)
../lsys/lsys.l:
	 (cd ../lsys;make clean; make)
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

Turtle.o: ./Turtle.h /usr/include/CC/iostream /usr/include/CC/iosfwd
Turtle.o: /usr/include/CC/stl_config.h /usr/include/standards.h
Turtle.o: /usr/include/wchar.h /usr/include/sgidefs.h
Turtle.o: /usr/include/locale_attr.h /usr/include/stdio.h
Turtle.o: /usr/include/ctype.h /usr/include/time.h /usr/include/stddef.h
Turtle.o: /usr/include/CC/functional /usr/include/CC/stl_function.h
Turtle.o: /usr/include/CC/char_traits.h /usr/include/string.h
Turtle.o: /usr/include/CC/istream /usr/include/CC/ostream /usr/include/CC/ios
Turtle.o: /usr/include/CC/stl_string_fwd.h /usr/include/CC/stl_alloc.h
Turtle.o: /usr/include/stdlib.h /usr/include/assert.h
Turtle.o: /usr/include/CC/stl_threads.h /usr/include/mutex.h
Turtle.o: /usr/include/CC/stl_exception.h /usr/include/CC/utility
Turtle.o: /usr/include/CC/stl_relops.h /usr/include/CC/stl_pair.h
Turtle.o: /usr/include/CC/stl_locale.h /usr/include/CC/typeinfo
Turtle.o: /usr/include/CC/exception /usr/include/CC/string
Turtle.o: /usr/include/CC/stdexcept /usr/include/CC/stl_iterator_base.h
Turtle.o: /usr/include/CC/memory /usr/include/CC/stl_algobase.h
Turtle.o: /usr/include/CC/type_traits.h /usr/include/limits.h
Turtle.o: /usr/include/CC/new.h /usr/include/CC/iostream.h
Turtle.o: /usr/include/memory.h /usr/include/CC/stl_iterator.h
Turtle.o: /usr/include/CC/stl_construct.h /usr/include/CC/stl_tempbuf.h
Turtle.o: /usr/include/CC/stl_uninitialized.h
Turtle.o: /usr/include/CC/stl_raw_storage_iter.h /usr/include/CC/algorithm
Turtle.o: /usr/include/CC/stl_algo.h /usr/include/CC/stl_heap.h
Turtle.o: /usr/include/CC/stl_hash_fun.h /usr/include/CC/stl_ctype.h
Turtle.o: /usr/include/CC/c_locale.h /usr/include/CC/streambuf
Turtle.o: /usr/include/CC/stl_stdio_file.h
Turtle.o: /usr/include/CC/stl_numeric_facets.h /usr/include/CC/limits
Turtle.o: /usr/include/float.h ../../c++adt/include/mathsym.h
Turtle.o: /usr/include/math.h ../../c++adt/include/Point.h
Turtle.o: ../../c++adt/include/PositionVector.h /usr/include/CC/vector
Turtle.o: /usr/include/CC/stl_range_errors.h /usr/include/CC/stl_vector.h
Turtle.o: /usr/include/CC/stl_bvector.h ../../c++adt/include/RMatrix.h
Turtle.o: ../../c++adt/include/Rotation.h ../../c++adt/include/TMatrix.h
Turtle.o: ../../c++adt/include/TMatrixI.h ../../c++adt/include/PointI.h
main.o: /usr/include/assert.h /usr/include/stdio.h /usr/include/standards.h
main.o: /usr/include/sgidefs.h /usr/include/string.h /usr/include/limits.h
main.o: /usr/include/stdlib.h /usr/include/unistd.h ../Globals/lglobal.h
main.o: ../Globals/lsysintrfc.h ../Generate/succstor.h
main.o: /usr/include/CC/iostream /usr/include/CC/iosfwd
main.o: /usr/include/CC/stl_config.h /usr/include/wchar.h
main.o: /usr/include/locale_attr.h /usr/include/ctype.h /usr/include/time.h
main.o: /usr/include/stddef.h /usr/include/CC/functional
main.o: /usr/include/CC/stl_function.h /usr/include/CC/char_traits.h
main.o: /usr/include/CC/istream /usr/include/CC/ostream /usr/include/CC/ios
main.o: /usr/include/CC/stl_string_fwd.h /usr/include/CC/stl_alloc.h
main.o: /usr/include/CC/stl_threads.h /usr/include/mutex.h
main.o: /usr/include/CC/stl_exception.h /usr/include/CC/utility
main.o: /usr/include/CC/stl_relops.h /usr/include/CC/stl_pair.h
main.o: /usr/include/CC/stl_locale.h /usr/include/CC/typeinfo
main.o: /usr/include/CC/exception /usr/include/CC/string
main.o: /usr/include/CC/stdexcept /usr/include/CC/stl_iterator_base.h
main.o: /usr/include/CC/memory /usr/include/CC/stl_algobase.h
main.o: /usr/include/CC/type_traits.h /usr/include/CC/new.h
main.o: /usr/include/CC/iostream.h /usr/include/memory.h
main.o: /usr/include/CC/stl_iterator.h /usr/include/CC/stl_construct.h
main.o: /usr/include/CC/stl_tempbuf.h /usr/include/CC/stl_uninitialized.h
main.o: /usr/include/CC/stl_raw_storage_iter.h /usr/include/CC/algorithm
main.o: /usr/include/CC/stl_algo.h /usr/include/CC/stl_heap.h
main.o: /usr/include/CC/stl_hash_fun.h /usr/include/CC/stl_ctype.h
main.o: /usr/include/CC/c_locale.h /usr/include/CC/streambuf
main.o: /usr/include/CC/stl_stdio_file.h /usr/include/CC/stl_numeric_facets.h
main.o: /usr/include/CC/limits /usr/include/float.h ./L2Lignum.h ./Turtle.h
main.o: ../../c++adt/include/mathsym.h /usr/include/math.h
main.o: ../../c++adt/include/Point.h ../../c++adt/include/PositionVector.h
main.o: /usr/include/CC/vector /usr/include/CC/stl_range_errors.h
main.o: /usr/include/CC/stl_vector.h /usr/include/CC/stl_bvector.h
main.o: ../../c++adt/include/RMatrix.h ../../c++adt/include/Rotation.h
main.o: ../../c++adt/include/TMatrix.h ../../c++adt/include/TMatrixI.h
main.o: ../../c++adt/include/PointI.h /usr/include/CC/stack
main.o: /usr/include/CC/stl_deque.h /usr/include/CC/stl_stack.h
main.o: ../../stl-lignum/include/Lignum.h ../../stl-lignum/include/Tree.h
main.o: /usr/include/CC/numeric /usr/include/CC/stl_numeric.h
main.o: /usr/include/CC/list /usr/include/CC/stl_list.h
main.o: ../../c++adt/include/ParametricCurve.h /usr/include/CC/fstream
main.o: /usr/include/CC/stl_codecvt.h ../../stl-lignum/include/LGMdecl.h
main.o: ../../stl-lignum/include/LGMSymbols.h /usr/include/CC/map
main.o: /usr/include/CC/stl_tree.h /usr/include/CC/stl_map.h
main.o: /usr/include/CC/stl_multimap.h ../../stl-lignum/include/LGMUnits.h
main.o: ../../stl-lignum/include/Algorithms.h
main.o: ../../stl-lignum/include/AlgorithmsI.h
main.o: ../../stl-lignum/include/TreeFunctor.h
main.o: ../../stl-lignum/include/TreeCompartment.h
main.o: ../../stl-lignum/include/TreeCompartmentI.h
main.o: ../../stl-lignum/include/TreeFunctorI.h
main.o: ../../stl-lignum/include/TreeMetaFileParser.h
main.o: ../../c++adt/include/Table.h ../../c++adt/include/DList.h
main.o: ../../c++adt/include/DListElement.h ../../c++adt/include/boolean.h
main.o: ../../c++adt/include/TableI.h ../../c++adt/include/Lex.h
main.o: ../../stl-lignum/include/RootSystem.h ../../stl-lignum/include/Bud.h
main.o: ../../stl-lignum/include/BudI.h ../../stl-lignum/include/DefaultBud.h
main.o: ../../stl-lignum/include/BranchingPoint.h
main.o: ../../stl-lignum/include/BranchingPointI.h
main.o: ../../stl-lignum/include/TreeSegment.h
main.o: ../../stl-lignum/include/TreeSegmentWithFlow.h
main.o: ../../stl-lignum/include/TreeSegmentI.h
main.o: ../../stl-lignum/include/HwTreeSegment.h
main.o: ../../stl-lignum/include/BroadLeaf.h ../../c++adt/include/Ellipsis.h
main.o: ../../stl-lignum/include/HwTreeSegmentI.h
main.o: ../../stl-lignum/include/HwTreeSegmentMetabolismI.h
main.o: ../../stl-lignum/include/CfTreeSegment.h
main.o: ../../stl-lignum/include/CfTreeFunctor.h
main.o: ../../stl-lignum/include/CfTreeFunctorI.h
main.o: ../../stl-lignum/include/CfTreeSegmentI.h
main.o: ../../stl-lignum/include/CfTreeSegmentMetabolismI.h
main.o: ../../stl-lignum/include/Axis.h ../../stl-lignum/include/AxisI.h
main.o: ../../c++adt/include/ConnectionMatrix.h
main.o: ../../c++adt/include/ConnectionMatrixI.h
main.o: ../../Firmament/include/FirmamentWithMask.h
main.o: ../../Firmament/include/Firmament.h
main.o: ../../stl-lignum/include/TreeRadiation.h
main.o: ../../stl-lignum/include/TreeBookkeeping.h
main.o: ../../stl-lignum/include/TreeBookkeepingI.h
main.o: ../../stl-lignum/include/TreeI.h
main.o: ../../stl-lignum/include/TreeMetabolismI.h
main.o: ../../stl-lignum/include/TreeMetabolism.h
main.o: ../../stl-lignum/include/TreeRadiationI.h ../Generate/lstring.h
main.o: ../Generate/lstriter.h ./Lstring2Lignum.h ./Lignum2Lstring.h
main.o: ../../stl-lignum/include/MyTreeSegment.h
main.o: ../../stl-lignum/include/MyBud.h ../../Graphics/OpenGLUnix.h
main.o: ../../Graphics/OpenGLUnixI.h ../../Graphics/OpenGL.h
main.o: ../../Graphics/OpenGLSymbols.h ../../Graphics/OpenGLinterface.h
main.o: /usr/include/GL/gl.h /usr/include/GL/glu.h
main.o: ../../Graphics/OpenGLinterfaceI.h ../../Graphics/OpenGLfunctions.h
main.o: ../../Graphics/OpenGLFunctor.h ../../Graphics/OpenGLFunctorI.h
main.o: /usr/include/GL/glx.h /usr/include/X11/Xlib.h
main.o: /usr/include/sys/types.h /usr/include/X11/X.h
main.o: /usr/include/X11/Xfuncproto.h /usr/include/X11/Xosdefs.h
main.o: /usr/include/X11/Xutil.h /usr/include/X11/Xmd.h
main.o: /usr/include/GL/glxtokens.h /usr/include/GL/glut.h
