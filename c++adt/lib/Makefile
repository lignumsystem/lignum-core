
SRCDIR1 = ../src
SRCDIR2 = ../include

SRC = $(SRCDIR1)/CString.cc  $(SRCDIR1)/DList.cc $(SRCDIR1)/DListElement.cc \
      $(SRCDIR1)/Ellipse.cc $(SRCDIR1)/Ellipsis.cc $(SRCDIR1)/Lex.cc \
      $(SRCDIR1)/ParametricCurve.cc $(SRCDIR1)/Polygon.cc \
      $(SRCDIR1)/PositionVector.cc $(SRCDIR1)/RMatrix.cc \
      $(SRCDIR1)/Triangle.cc $(SRCDIR1)/HRMatrix.cc \
      $(SRCDIR1)/Gauss.cc $(SRCDIR1)/Uniform.cc $(SRCDIR1)/rand3.cc  $(SRCDIR1)/normal.cc $(SRCDIR1)/Bernoulli.cc

OBJ = ${SRC:.cc=.o} 

INCLUDE= -I../include 

CCC = CC -64 -LANG:std
ETAGS = etags -d -T -C -o

OPTIMIZE = -O
CCCFLAGS =   -c

.SUFFIXES: .o .cc
AR =  $(CCC) -ar 
ARFLAGS =  -o
ARFILE = libc++adt.a

PROGFILES = program-files.html

sinclude Makedepend

$(ARFILE): $(OBJ)
	$(AR) $(ARFLAGS) $(ARFILE) $(OBJ)

hrmatrix: $(ARFILE)
	$(CCC)  ../src/hrmatrix.cc -o $@ $(INCLUDE) -L. -lc++adt -lm 
.cc.o: 
	$(CCC)  $(OPTIMIZE) $(CCCFLAGS) $(INCLUDE) $<  -o $@  

touch:
	touch $(SRC)
html:
	enscript -E --color -Whtml --toc -p$(PROGFILES) include/*.h $(SRC)
clean:
	rm -rf $(OBJ) hrmatrix ../src/ii_files ../include/ii_files ii_files core

distclean: clean
	rm -rf  $(ARFILE) Makedepend

etags:
	$(ETAGS)   TAGSFILE ../src/*.cc ../include/*.h
depend:
	$(CCC) -M  $(INCLUDE) $(SRC) > Makedepend
#Do not delete this line -- make depend adds dependencies at the end of it
#If committing Makefile to cvs please remove the dependencies first
