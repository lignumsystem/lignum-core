
SRCDIR1 = ./src
SRCDIR2 = ./include

SRC = $(SRCDIR1)/CString.cc  $(SRCDIR1)/DList.cc $(SRCDIR1)/DListElement.cc \
      $(SRCDIR1)/Ellipsis.cc $(SRCDIR1)/Lex.cc $(SRCDIR1)/ParametricCurve.cc \
      $(SRCDIR1)/PositionVector.cc $(SRCDIR1)/RMatrix.cc 

OBJ = $(SRCDIR1)/CString.o $(SRCDIR1)/DList.o $(SRCDIR1)/DListElement.o \
      $(SRCDIR1)/Ellipsis.o $(SRCDIR1)/Lex.o $(SRCDIR1)/ParametricCurve.o \
      $(SRCDIR1)/PositionVector.o $(SRCDIR1)/RMatrix.o 

INCLUDE= -Iinclude -I/usr/include/CC 

CCC = CC -64
ETAGS = etags -d -T -C -o

OPTIMIZE = -O
CCCFLAGS =   -c 

.SUFFIXES: .o .cc
ARCOMMAND = $(CCC) -ar  
ARCOMMANDFLAGS = -o
AR = $(ARCOMMAND)
ARFLAGS = $(ARCOMMANDFLAGS)
ARFILE = lib/libc++adt.a

PROGFILES = program-files.html

$(ARFILE): $(OBJ)
	$(AR) $(ARFLAGS) $(ARFILE) $(OBJ)

.cc.o: 
	$(CCC)  $(OPTIMIZE) $(CCCFLAGS) $(INCLUDE) $<  -o $@  

touch:
	touch $(SRC)

html:
	enscript -E --color -Whtml --toc -p$(PROGFILES) include/*.h $(SRC)
clean:
	rm -f $(OBJ) core

distclean: clean
	rm -rf src/ii_files include/ii_files ii_files $(ARFILE)

etags:
	$(ETAGS)   TAGSFILE ../src/*.cc ../include/*.h
depend:
	(cd lib; make depend)
	makedepend $(INCLUDE) $(SRC)
