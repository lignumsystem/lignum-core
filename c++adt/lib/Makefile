
SRCDIR1 = ../src
SRCDIR2 = ../include

SRC = $(SRCDIR1)/CString.cc  $(SRCDIR1)/DList.cc $(SRCDIR1)/DListElement.cc \
      $(SRCDIR1)/Ellipsis.cc $(SRCDIR1)/Lex.cc $(SRCDIR1)/ParametricCurve.cc \
      $(SRCDIR1)/PositionVector.cc $(SRCDIR1)/RMatrix.cc $(SRCDIR1)/HRMatrix.cc \
      $(SRCDIR1)/rand3.cc  $(SRCDIR1)/gauss.cc

OBJ = $(SRCDIR1)/CString.o $(SRCDIR1)/DList.o $(SRCDIR1)/DListElement.o \
      $(SRCDIR1)/Ellipsis.o $(SRCDIR1)/Lex.o $(SRCDIR1)/ParametricCurve.o \
      $(SRCDIR1)/PositionVector.o $(SRCDIR1)/RMatrix.o $(SRCDIR1)/HRMatrix.o \
      $(SRCDIR1)/rand3.o $(SRCDIR1)/gauss.o

INCLUDE= -I../include -I/usr/include/CC 

CCC = CC -64 -LANG:std
ETAGS = etags -d -T -C -o

OPTIMIZE = -O
CCCFLAGS =   -c

.SUFFIXES: .o .cc
ARCOMMAND=$(CCC) -ar 
ARCOMMANDFLAGS = -o
AR =  $(ARCOMMAND)
ARFLAGS =  $(ARCOMMANDFLAGS)
ARFILE = libc++adt.a


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
	makedepend $(INCLUDE) $(SRC) ../src/hrmatrix.cc
