#OS=Linux
OS=IRIX64
TARGET=$(OS).out/lengine
LIBTRG=$(OS).out/liblengine.a


CCC = CC -64 -LANG:std
CCCFLAGS =   -c

OPTIMIZE = -g
  
AR = $(CCC) -ar
ARFLAGS= -o
ARFILE=liblengine.a


SRC = lstring.cpp lstriter.cpp succstor.cpp lsysintrfc.cpp match.cpp
OBJ = ${SRC:.cpp=.o}

INCLUDE= -I../Globals

.SUFFIXES: .o .cpp 

sinclude Makedepend

$(ARFILE): $(OBJ)
	$(AR) $(ARFLAGS) $(ARFILE)  $(OBJ)

.cpp.o:
	$(CCC) $(CCCFLAGS) $(OPTIMIZE) $(INCLUDE) -o $@ $<


clean:
	rm -rf  $(OBJ) ii_files  core
distclean: clean
	rm -rf $(ARFILE) Makedepend
depend: 
	$(CCC) -M  $(INCLUDE) $(SRC)  > Makedepend
