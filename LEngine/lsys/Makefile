CCC = CC -64 -LANG:std
CCCFLAGS =   -c
   
AR = $(CCC) -ar
ARFLAGS= -o
ARFILE=liblsys.a

LSYSFILES= lsys.L
SRC=${LSYSFILES:.L=.cpp}
OBJ=${SRC:.cpp=.o}

AR =  $(CCC) -ar  
ARFLAGS = -o 

INCLUDE= -I../Globals -I/usr/include -I../../c++adt/include -I../../stl-lignum/include

.SUFFIXES: .cpp .L

sinclude Makedepend

$(ARFILE): $(SRC) $(OBJ)
	$(AR) $(ARFLAGS) $(ARFILE)  $(OBJ)
.L.cpp:
	../L2C/l2c  $< $@
	$(CCC) $(OPTIMIZE) $(CCCFLAGS) $(INCLUDE)  $@
.cpp.o:
	$(CCC) $(CCCFLAGS) $(OPTIMIZE) $(INCLUDE)  $<
l2c:
	(cd ../L2C; make "CCC=$(CCC)" "CCCFLAGS=$(CCCFLAGS)" \
         "OPTIMIZE=$(OPTIMIZE)" "AR=ar" "ARFLAGS=rv" $@)

clean:
	rm -rf $(OBJ) $(SRC)  ii_files
distclean: clean
	rm -rf  $(ARFILE) Makedepend 
depend:	l2c $(SRC)
	$(CCC) -M  $(INCLUDE) $(SRC)  > Makedepend	


