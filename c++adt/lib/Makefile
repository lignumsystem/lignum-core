
SRCDIR1 = ../src
SRCDIR2 = ../include

SRC = $(SRCDIR1)/CString.cc  $(SRCDIR1)/DList.cc $(SRCDIR1)/DListElement.cc \
      $(SRCDIR1)/Ellipsis.cc $(SRCDIR1)/Lex.cc $(SRCDIR1)/ParametricCurve.cc \
      $(SRCDIR1)/PositionVector.cc $(SRCDIR1)/RMatrix.cc $(SRCDIR1)/HRMatrix.cc \
      $(SRCDIR1)/rand3.cc  $(SRCDIR1)/gauss.cc

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

sinclude Makedepend

$(ARFILE): $(OBJ)
	$(AR) $(ARFLAGS) $(ARFILE) $(OBJ)

hrmatrix: $(ARFILE)
	$(CCC)  ../src/hrmatrix.cc -o $@ $(INCLUDE) -L. -lc++adt -lm 
.cc.o: 
	$(CCC)  $(OPTIMIZE) $(CCCFLAGS) $(INCLUDE) $<  -o $@  

touch:
	touch $(SRC)

clean:
	rm -f $(OBJ) hrmatrix core

distclean: clean
	rm -rf ../src/ii_files ../include/ii_files ii_files $(ARFILE)

etags:
	$(ETAGS)   TAGSFILE ../src/*.cc ../include/*.h
depend:
	$(CCC) -M  $(INCLUDE) $(SRC) ../src/hrmatrix.cc > Makedepend
#Do not delete this line -- make depend adds dependencies at the end of it
#If committing Makefile to cvs please remove the dependencies first
