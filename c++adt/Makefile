SRCDIR1 = ./src

SRC = $(SRCDIR1)/CString.cc  $(SRCDIR1)/DList.cc $(SRCDIR1)/DListElement.cc \
      $(SRCDIR1)/Ellipsis.cc $(SRCDIR1)/Lex.cc $(SRCDIR1)/ParametricCurve.cc \
      $(SRCDIR1)/PositionVector.cc $(SRCDIR1)/RMatrix.cc $(SRCDIR1)/HRMatrix.cc \
      $(SRCDIR1)/rand3.cc  $(SRCDIR1)/gauss.cc

CCC = CC -64 -LANG:std
ETAGS = etags -d -T -C -o

OPTIMIZE = -g
CCCFLAGS =   -c 

.SUFFIXES: .o .cc
AR = $(CCC) -ar  
ARFLAGS = -o
ARFILE = libc++adt.a

PROGFILES = program-files.html

$(ARFILE): 
	(cd lib; make "CCC=$(CCC)" "CCCFLAGS=$(CCCFLAGS)" "OPTIMIZE=$(OPTIMIZE)" \
                      "AR=$(AR)"  "ARFLAGS=$(ARFLAGS)" $@) 
touch:
	(cd lib; make touch)

html:
	enscript -E --color -Whtml --toc -p$(PROGFILES) include/*.h $(SRC)
clean:
	(cd lib; make clean) 

distclean: 
	(cd lib; make distclean)

etags:
	(cd lib; make etags)
depend:
	(cd lib; make "CCC=$(CCC)" depend)
