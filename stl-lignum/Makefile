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

CCCFLAGS = -c -ptv -prelink #-fullwarn 

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
clean:
	(cd lib; make clean)
	rm -rf $(OBJ) $(ALGOBJ) core lignum algorithms broadleaf ii_files
	rm -rf ./*/ii_files
distclean:
	(cd ../c++adt/lib; make distclean)
	(cd ../Firmament; make distclean)
	(cd lib; make distclean)
	rm -rf $(OBJ) $(ALGOBJ) $(BLOBJ) core lignum algorithms broadleaf ii_files 
depend: 
	makedepend $(INCLUDE) $(CCCINCLUDE) $(STL) $(MAIN) $(ALGSRC) $(BLSRC)  
# DO NOT DELETE

main.o: /usr/include/stdlib.h /usr/include/features.h
main.o: /usr/include/sys/cdefs.h /usr/include/gnu/stubs.h
main.o: /usr/lib/gcc-lib/i386-redhat-linux/egcs-2.91.66/include/stddef.h
main.o: /usr/include/sys/types.h /usr/include/bits/types.h
main.o: /usr/include/time.h /usr/include/endian.h /usr/include/bits/endian.h
main.o: /usr/include/sys/select.h /usr/include/bits/select.h
main.o: /usr/include/bits/sigset.h /usr/include/sys/sysmacros.h
main.o: /usr/include/alloca.h include/Tree.h ../c++adt/include/CString.h
main.o: /usr/include/string.h /usr/include/stdio.h
main.o: /usr/lib/gcc-lib/i386-redhat-linux/egcs-2.91.66/include/stdarg.h
main.o: /usr/include/libio.h /usr/include/_G_config.h
main.o: /usr/include/bits/stdio_lim.h /usr/include/ctype.h
main.o: ../c++adt/include/ParametricCurve.h
main.o: /usr/lib/gcc-lib/i386-redhat-linux/egcs-2.91.66/include/float.h
main.o: ../c++adt/include/Point.h /usr/include/math.h
main.o: /usr/include/bits/huge_val.h /usr/include/bits/mathdef.h
main.o: /usr/include/bits/mathcalls.h ../c++adt/include/PointI.h
main.o: ../c++adt/include/PositionVector.h ../c++adt/include/mathsym.h
main.o: ../c++adt/include/RMatrix.h ../c++adt/include/TMatrix.h
main.o: ../c++adt/include/TMatrixI.h include/Algorithms.h include/LGMdecl.h
main.o: include/LGMSymbols.h include/LGMUnits.h include/AlgorithmsI.h
main.o: include/TreeFunctor.h include/TreeCompartment.h
main.o: include/TreeCompartmentI.h include/TreeFunctorI.h
main.o: include/TreeMetaFileParser.h ../c++adt/include/Table.h
main.o: ../c++adt/include/DList.h ../c++adt/include/DListElement.h
main.o: ../c++adt/include/boolean.h ../c++adt/include/TableI.h
main.o: ../c++adt/include/Lex.h include/RootSystem.h include/Bud.h
main.o: include/BudI.h include/DefaultBud.h include/BranchingPoint.h
main.o: include/BranchingPointI.h include/TreeSegment.h
main.o: include/TreeSegmentI.h include/TreeSegmentMetabolismI.h
main.o: include/HwTreeSegment.h include/BroadLeaf.h
main.o: ../c++adt/include/Ellipsis.h ../Firmament/include/Firmament.h
main.o: include/HwTreeSegmentI.h include/CfTreeSegment.h include/Axis.h
main.o: include/AxisI.h ../c++adt/include/ConnectionMatrix.h
main.o: ../c++adt/include/ConnectionMatrixI.h include/TreeI.h
main.o: include/TreeMetabolismI.h include/MyTreeSegment.h include/MyBud.h
algorithms.o: /usr/include/stdlib.h /usr/include/features.h
algorithms.o: /usr/include/sys/cdefs.h /usr/include/gnu/stubs.h
algorithms.o: /usr/lib/gcc-lib/i386-redhat-linux/egcs-2.91.66/include/stddef.h
algorithms.o: /usr/include/sys/types.h /usr/include/bits/types.h
algorithms.o: /usr/include/time.h /usr/include/endian.h
algorithms.o: /usr/include/bits/endian.h /usr/include/sys/select.h
algorithms.o: /usr/include/bits/select.h /usr/include/bits/sigset.h
algorithms.o: /usr/include/sys/sysmacros.h /usr/include/alloca.h
algorithms.o: include/Tree.h ../c++adt/include/CString.h
algorithms.o: /usr/include/string.h /usr/include/stdio.h
algorithms.o: /usr/lib/gcc-lib/i386-redhat-linux/egcs-2.91.66/include/stdarg.h
algorithms.o: /usr/include/libio.h /usr/include/_G_config.h
algorithms.o: /usr/include/bits/stdio_lim.h /usr/include/ctype.h
algorithms.o: ../c++adt/include/ParametricCurve.h
algorithms.o: /usr/lib/gcc-lib/i386-redhat-linux/egcs-2.91.66/include/float.h
algorithms.o: ../c++adt/include/Point.h /usr/include/math.h
algorithms.o: /usr/include/bits/huge_val.h /usr/include/bits/mathdef.h
algorithms.o: /usr/include/bits/mathcalls.h ../c++adt/include/PointI.h
algorithms.o: ../c++adt/include/PositionVector.h ../c++adt/include/mathsym.h
algorithms.o: ../c++adt/include/RMatrix.h ../c++adt/include/TMatrix.h
algorithms.o: ../c++adt/include/TMatrixI.h include/Algorithms.h
algorithms.o: include/LGMdecl.h include/LGMSymbols.h include/LGMUnits.h
algorithms.o: include/AlgorithmsI.h include/TreeFunctor.h
algorithms.o: include/TreeCompartment.h include/TreeCompartmentI.h
algorithms.o: include/TreeFunctorI.h include/TreeMetaFileParser.h
algorithms.o: ../c++adt/include/Table.h ../c++adt/include/DList.h
algorithms.o: ../c++adt/include/DListElement.h ../c++adt/include/boolean.h
algorithms.o: ../c++adt/include/TableI.h ../c++adt/include/Lex.h
algorithms.o: include/RootSystem.h include/Bud.h include/BudI.h
algorithms.o: include/DefaultBud.h include/BranchingPoint.h
algorithms.o: include/BranchingPointI.h include/TreeSegment.h
algorithms.o: include/TreeSegmentI.h include/TreeSegmentMetabolismI.h
algorithms.o: include/HwTreeSegment.h include/BroadLeaf.h
algorithms.o: ../c++adt/include/Ellipsis.h ../Firmament/include/Firmament.h
algorithms.o: include/HwTreeSegmentI.h include/CfTreeSegment.h include/Axis.h
algorithms.o: include/AxisI.h ../c++adt/include/ConnectionMatrix.h
algorithms.o: ../c++adt/include/ConnectionMatrixI.h include/TreeI.h
algorithms.o: include/TreeMetabolismI.h include/MyTreeSegment.h
algorithms.o: include/MyBud.h
broadleaf.o: /usr/include/stdlib.h /usr/include/features.h
broadleaf.o: /usr/include/sys/cdefs.h /usr/include/gnu/stubs.h
broadleaf.o: /usr/lib/gcc-lib/i386-redhat-linux/egcs-2.91.66/include/stddef.h
broadleaf.o: /usr/include/sys/types.h /usr/include/bits/types.h
broadleaf.o: /usr/include/time.h /usr/include/endian.h
broadleaf.o: /usr/include/bits/endian.h /usr/include/sys/select.h
broadleaf.o: /usr/include/bits/select.h /usr/include/bits/sigset.h
broadleaf.o: /usr/include/sys/sysmacros.h /usr/include/alloca.h
broadleaf.o: include/Tree.h ../c++adt/include/CString.h /usr/include/string.h
broadleaf.o: /usr/include/stdio.h
broadleaf.o: /usr/lib/gcc-lib/i386-redhat-linux/egcs-2.91.66/include/stdarg.h
broadleaf.o: /usr/include/libio.h /usr/include/_G_config.h
broadleaf.o: /usr/include/bits/stdio_lim.h /usr/include/ctype.h
broadleaf.o: ../c++adt/include/ParametricCurve.h
broadleaf.o: /usr/lib/gcc-lib/i386-redhat-linux/egcs-2.91.66/include/float.h
broadleaf.o: ../c++adt/include/Point.h /usr/include/math.h
broadleaf.o: /usr/include/bits/huge_val.h /usr/include/bits/mathdef.h
broadleaf.o: /usr/include/bits/mathcalls.h ../c++adt/include/PointI.h
broadleaf.o: ../c++adt/include/PositionVector.h ../c++adt/include/mathsym.h
broadleaf.o: ../c++adt/include/RMatrix.h ../c++adt/include/TMatrix.h
broadleaf.o: ../c++adt/include/TMatrixI.h include/Algorithms.h
broadleaf.o: include/LGMdecl.h include/LGMSymbols.h include/LGMUnits.h
broadleaf.o: include/AlgorithmsI.h include/TreeFunctor.h
broadleaf.o: include/TreeCompartment.h include/TreeCompartmentI.h
broadleaf.o: include/TreeFunctorI.h include/TreeMetaFileParser.h
broadleaf.o: ../c++adt/include/Table.h ../c++adt/include/DList.h
broadleaf.o: ../c++adt/include/DListElement.h ../c++adt/include/boolean.h
broadleaf.o: ../c++adt/include/TableI.h ../c++adt/include/Lex.h
broadleaf.o: include/RootSystem.h include/Bud.h include/BudI.h
broadleaf.o: include/DefaultBud.h include/BranchingPoint.h
broadleaf.o: include/BranchingPointI.h include/TreeSegment.h
broadleaf.o: include/TreeSegmentI.h include/TreeSegmentMetabolismI.h
broadleaf.o: include/HwTreeSegment.h include/BroadLeaf.h
broadleaf.o: ../c++adt/include/Ellipsis.h ../Firmament/include/Firmament.h
broadleaf.o: include/HwTreeSegmentI.h include/CfTreeSegment.h include/Axis.h
broadleaf.o: include/AxisI.h ../c++adt/include/ConnectionMatrix.h
broadleaf.o: ../c++adt/include/ConnectionMatrixI.h include/TreeI.h
broadleaf.o: include/TreeMetabolismI.h include/MyTreeSegment.h
broadleaf.o: include/MyBud.h
