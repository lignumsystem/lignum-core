CCC = CC -64 -LANG:std
CCCFLAGS =   -c
   
AR = $(CCC) -ar
ARFLAGS= -o
ARFILE=liblsys.a

LSYS= bearberry.L pine9bp.L cs-plantA.L cs-plantB.L  cs-plantC.L \
      cs-plantD.L cs-plant.L 
SRC=${LSYS:.L=.cpp}
OBJ=${SRC:.cpp=.o}


INCLUDE= -I../include -I../../c++adt/include -I../../stl-lignum/include

.SUFFIXES: .L .cpp

sinclude Makedepend

$(ARFILE): $(SRC) $(OBJ)
	$(AR) $(ARFLAGS) $(ARFILE)  $(OBJ)
.L.cpp:
	../L2C/l2c  $< $@
	$(CCC) $(CCCFLAGS) $(OPTIMIZE) $(INCLUDE)  $@ 
	rm -f *.c
.cpp.o:
	$(CCC) $(CCCFLAGS) $(OPTIMIZE) $(INCLUDE)  $< -o $@ 
l2c:
	(cd ../L2C; make "CCC=$(CCC)" "CCCFLAGS=$(CCCFLAGS)" \
         "OPTIMIZE=$(OPTIMIZE)" "AR=ar" "ARFLAGS=rvs" $@)
clean:
	rm -rf *.a *.o *.cpp  ii_files
distclean: clean
	rm -rf  $(ARFILE) Makedepend *.c 
depend:	l2c $(SRC)
	$(CCC) -M  $(INCLUDE) $(SRC)  > Makedepend	


