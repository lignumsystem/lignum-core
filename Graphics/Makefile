#To compile "algorithms" on SGI type 
#    make algorithms
#To compile with g++ in Linux type (or copy paste)
#    make "CCC=g++" "CCCFLAGS=-c" "OPTIMIZE=-O" "ARCOMMAND=ar"  "ARCOMMANDFLAGS=rv" algorithms 

SRC=OpenGL.cc  OpenGLUnix.cc OpenGLfunctions.cc  OpenGLinterface.cc texture.cc 
OBJ=OpenGL.o  OpenGLUnix.o OpenGLfunctions.o  OpenGLinterface.o texture.o 

ALGSRC = algorithms.cc 
ALGOBJ  = algorithms.o 

 
CCC = CC -64 -LANG:std

#OPTIMIZE = -Ofast=ip28 -IPA
OPTIMIZE   = -g 

ARCOMMAND =  $(CCC) -ar  
ARCOMMANDFLAGS = -o 
AR = $(ARCOMMAND)

SUPPRESS = #-w 1155 -w 1183

CCCFLAGS = -c  #-prelink -ptused   -ptv  #  -fullwarn 

INCLUDE = -I. -I../stl-lignum/include -I../c++adt/include -I../Firmament/include

STL     = -I/usr/include/CC

LIBFLAGS = -L. -L../c++adt/lib -L../stl-lignum/lib -L../Firmament/lib

LIB1   = libc++adt.a
LIB2   = libLGM.a
LIB3   = libsky.a
LIB4   = libVisual.a

LIBADT = -lc++adt
LIBLGM = -lLGM
LIBSKY = -lsky
LIBMATH  = -lm 
LIBVISUAL = -lVisual

LIBOGL =  -lglut -lGL -lGLU -lX11 -lXext -lXmu 

LIBS     =  $(LIBVISUAL) $(LIBLGM) $(LIBSKY) $(LIBADT) $(LIBOGL) $(LIBMATH)
 

PROGFILES = program-files.html
.SUFFIXES: .o .cc

algorithms: $(ALGOBJ) $(LIB4) $(LIB1) $(LIB3)  $(LIB2) 
	$(CCC)  -o $@ $(INCLUDE) $(OPTIMIZE) $(ALGOBJ) $(LIBFLAGS) $(LIBS)

lignux: 
	make "CCC=g++" "CCCFLAGS=-c" "OPTIMIZE=-O" "ARCOMMAND=ar"  "ARCOMMANDFLAGS=rv" algorithms


$(LIB1):
	(cd ../c++adt/lib; make "CCC=$(CCC)" "CCCFLAGS=$(CCCFLAGS)" \
         "OPTIMIZE=$(OPTIMIZE)" "AR=$(ARCOMMAND)"  "ARFLAGS = $(ARCOMMANDFLAGS)" $@)

$(LIB2):
	(cd ../stl-lignum/lib; make "CCC=$(CCC)" "CCCFLAGS=$(CCCFLAGS)" "OPTIMIZE=$(OPTIMIZE)" "AR=$(ARCOMMAND)" \
         "ARFLAGS = $(ARCOMMANDFLAGS)" $@)

$(LIB3):
	(cd ../Firmament; make "CCC=$(CCC)" "CCCFLAGS=$(CCCFLAGS)" \
         "OPTIMIZE=$(OPTIMIZE)"  "AR=$(ARCOMMAND)"  "ARFLAGS = $(ARCOMMANDFLAGS)" $@)

$(LIB4):$(OBJ)
	$(AR) $(ARCOMMANDFLAGS) $(LIB4) $(OBJ)

.cc.o: 
	$(CCC) $(OPTIMIZE) $(SUPPRESS) $(CCCFLAGS) $(INCLUDE)  $< -o $@

html:
	enscript -E --color -Whtml --toc -p$(PROGFILES) ./include/*.h ./*/*.cc
changelog:
	rm -rf ChangeLog
	rcs2log . > ChangeLog
clean:
	rm -rf $(OBJ) $(ALGOBJ) $(BLOBJ) core lignum algorithms broadleaf ii_files
	rm -rf ./*/ii_files
distclean: clean
	(cd ../c++adt/lib; make distclean)
	(cd ../Firmament; make distclean)
	(cd ../stl-lignum; make distclean)
depend:
	(cd ../c++adt; make depend)
	(cd ../Firmament; make depend)
	(cd ../stl-lignum; make depend)
	makedepend $(INCLUDE) $(CCCINCLUDE) $(STL) $(MAIN) $(ALGSRC) $(BLSRC)  

# DO NOT DELETE

algorithms.o: ../stl-lignum/include/MyTreeSegment.h
algorithms.o: ../stl-lignum/include/HwTreeSegment.h /usr/include/CC/list
algorithms.o: /usr/include/CC/stl_algobase.h /usr/include/CC/stl_config.h
algorithms.o: /usr/include/standards.h /usr/include/CC/stl_relops.h
algorithms.o: /usr/include/CC/stl_pair.h /usr/include/CC/type_traits.h
algorithms.o: /usr/include/string.h /usr/include/limits.h
algorithms.o: /usr/include/sgidefs.h /usr/include/stdlib.h
algorithms.o: /usr/include/stddef.h /usr/include/CC/new.h
algorithms.o: /usr/include/CC/iostream.h /usr/include/memory.h
algorithms.o: /usr/include/CC/stl_iterator_base.h
algorithms.o: /usr/include/CC/stl_iterator.h /usr/include/CC/stl_alloc.h
algorithms.o: /usr/include/stdio.h /usr/include/assert.h
algorithms.o: /usr/include/CC/stl_threads.h /usr/include/mutex.h
algorithms.o: /usr/include/time.h /usr/include/CC/stl_construct.h
algorithms.o: /usr/include/CC/stl_uninitialized.h /usr/include/CC/stl_list.h
algorithms.o: ../stl-lignum/include/BroadLeaf.h ../c++adt/include/Point.h
algorithms.o: /usr/include/math.h /usr/include/CC/iostream
algorithms.o: /usr/include/CC/iosfwd /usr/include/wchar.h
algorithms.o: /usr/include/locale_attr.h /usr/include/ctype.h
algorithms.o: /usr/include/CC/functional /usr/include/CC/stl_function.h
algorithms.o: /usr/include/CC/char_traits.h /usr/include/CC/istream
algorithms.o: /usr/include/CC/ostream /usr/include/CC/ios
algorithms.o: /usr/include/CC/stl_string_fwd.h
algorithms.o: /usr/include/CC/stl_exception.h /usr/include/CC/utility
algorithms.o: /usr/include/CC/stl_locale.h /usr/include/CC/typeinfo
algorithms.o: /usr/include/CC/exception /usr/include/CC/string
algorithms.o: /usr/include/CC/stdexcept /usr/include/CC/memory
algorithms.o: /usr/include/CC/stl_tempbuf.h
algorithms.o: /usr/include/CC/stl_raw_storage_iter.h
algorithms.o: /usr/include/CC/algorithm /usr/include/CC/stl_algo.h
algorithms.o: /usr/include/CC/stl_heap.h /usr/include/CC/stl_hash_fun.h
algorithms.o: /usr/include/CC/stl_ctype.h /usr/include/CC/c_locale.h
algorithms.o: /usr/include/CC/streambuf /usr/include/CC/stl_stdio_file.h
algorithms.o: /usr/include/CC/stl_numeric_facets.h /usr/include/CC/limits
algorithms.o: /usr/include/float.h ../c++adt/include/PositionVector.h
algorithms.o: ../c++adt/include/mathsym.h /usr/include/CC/vector
algorithms.o: /usr/include/CC/stl_range_errors.h /usr/include/CC/stl_vector.h
algorithms.o: /usr/include/CC/stl_bvector.h ../c++adt/include/RMatrix.h
algorithms.o: ../c++adt/include/Rotation.h ../c++adt/include/TMatrix.h
algorithms.o: ../c++adt/include/TMatrixI.h ../c++adt/include/PointI.h
algorithms.o: ../c++adt/include/Ellipsis.h ../stl-lignum/include/LGMdecl.h
algorithms.o: ../stl-lignum/include/LGMSymbols.h /usr/include/CC/map
algorithms.o: /usr/include/CC/stl_tree.h /usr/include/CC/stl_map.h
algorithms.o: /usr/include/CC/stl_multimap.h ../stl-lignum/include/LGMUnits.h
algorithms.o: ../stl-lignum/include/HwTreeSegmentI.h
algorithms.o: ../stl-lignum/include/HwTreeSegmentMetabolismI.h
algorithms.o: ../stl-lignum/include/CfTreeSegment.h
algorithms.o: ../stl-lignum/include/CfTreeFunctor.h
algorithms.o: ../stl-lignum/include/TreeCompartment.h
algorithms.o: ../stl-lignum/include/TreeCompartmentI.h
algorithms.o: ../stl-lignum/include/Algorithms.h
algorithms.o: ../stl-lignum/include/AlgorithmsI.h
algorithms.o: ../stl-lignum/include/CfTreeFunctorI.h
algorithms.o: ../stl-lignum/include/TreeSegment.h
algorithms.o: ../stl-lignum/include/TreeSegmentWithFlow.h
algorithms.o: ../stl-lignum/include/TreeSegmentI.h
algorithms.o: ../stl-lignum/include/Tree.h /usr/include/CC/numeric
algorithms.o: /usr/include/CC/stl_numeric.h
algorithms.o: ../c++adt/include/ParametricCurve.h /usr/include/CC/fstream
algorithms.o: /usr/include/CC/stl_codecvt.h
algorithms.o: ../stl-lignum/include/TreeFunctor.h
algorithms.o: ../stl-lignum/include/TreeFunctorI.h
algorithms.o: ../stl-lignum/include/TreeMetaFileParser.h
algorithms.o: ../c++adt/include/Table.h ../c++adt/include/DList.h
algorithms.o: ../c++adt/include/DListElement.h ../c++adt/include/boolean.h
algorithms.o: ../c++adt/include/TableI.h ../c++adt/include/Lex.h
algorithms.o: ../stl-lignum/include/RootSystem.h ../stl-lignum/include/Bud.h
algorithms.o: ../stl-lignum/include/BudI.h ../stl-lignum/include/DefaultBud.h
algorithms.o: ../stl-lignum/include/BranchingPoint.h
algorithms.o: ../stl-lignum/include/BranchingPointI.h
algorithms.o: ../stl-lignum/include/Axis.h ../stl-lignum/include/AxisI.h
algorithms.o: ../c++adt/include/ConnectionMatrix.h
algorithms.o: ../c++adt/include/ConnectionMatrixI.h
algorithms.o: ../Firmament/include/FirmamentWithMask.h
algorithms.o: ../Firmament/include/Firmament.h
algorithms.o: ../stl-lignum/include/TreeRadiation.h
algorithms.o: ../stl-lignum/include/TreeBookkeeping.h
algorithms.o: ../stl-lignum/include/TreeBookkeepingI.h
algorithms.o: ../stl-lignum/include/TreeI.h
algorithms.o: ../stl-lignum/include/TreeMetabolismI.h
algorithms.o: ../stl-lignum/include/TreeMetabolism.h
algorithms.o: ../stl-lignum/include/TreeRadiationI.h
algorithms.o: ../stl-lignum/include/CfTreeSegmentI.h
algorithms.o: ../stl-lignum/include/CfTreeSegmentMetabolismI.h
algorithms.o: ../stl-lignum/include/Lignum.h ../stl-lignum/include/MyBud.h
algorithms.o: ../stl-lignum/include/Shading.h
algorithms.o: ../stl-lignum/include/ShadingI.h ./OpenGLUnix.h ./OpenGLUnixI.h
algorithms.o: OpenGL.h OpenGLSymbols.h OpenGLinterface.h /usr/include/GL/gl.h
algorithms.o: /usr/include/GL/glu.h OpenGLinterfaceI.h OpenGLfunctions.h
algorithms.o: OpenGLFunctor.h OpenGLFunctorI.h CTexture.h
algorithms.o: /usr/include/GL/glx.h /usr/include/X11/Xlib.h
algorithms.o: /usr/include/sys/types.h /usr/include/X11/X.h
algorithms.o: /usr/include/X11/Xfuncproto.h /usr/include/X11/Xosdefs.h
algorithms.o: /usr/include/X11/Xutil.h /usr/include/X11/Xmd.h
algorithms.o: /usr/include/GL/glxtokens.h /usr/include/GL/glut.h
