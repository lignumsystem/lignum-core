MAIN = Firmament.cc FirmamentWithMask.cc MineSet.cc Interlen.cc Voxel.cc voxellattice.cc voxelmatrix.cc
OBJ  = Firmament.o  FirmamentWithMask.o MineSet.o Interlen.o Voxel.o voxellattice.o voxelmatrix.o 
 
CCC = CC -64 -LANG:std

ARCOMMAND=$(CCC) -ar
ARCOMMANDFLAGS= -o
AR = $(ARCOMMAND)  
ARFLAGS = $(ARCOMMANDFLAGS) 
ARFILE = lib/libsky.a


#OPTIMIZE = -Ofast=ip28 -IPA
OPTIMIZE   = -g 

SUPPRESS = #-w 1155 -w 1183

CCCFLAGS = -c #-ptv -prelink -fullwarn 

INCLUDE =  -Iinclude -I../c++adt/include -I../stl-lignum/include -I../ScotsPine/include 
STL     = -I/usr/include/CC

LIBFLAGS = -L../c++adt/lib -L../stl-lignum/lib -Llib 

#LIB1   = libc++adt.a

#LIBADT = -lc++adt
LIBMATH  = -lm 
LIBS     = -lsky -lc++adt $(LIBMATH)

.SUFFIXES: .o .cc

libsky.a:  $(OBJ)
	$(AR) $(ARFLAGS) $(ARFILE) $(OBJ)
libc++adt.a:
	(cd ../c++adt/lib; make "CCC=$(CCC)" "CCCFLAGS=$(CCCFLAGS)" \
         "OPTIMIZE=$(OPTIMIZE)" "AR=$(AR)"  "ARFLAGS = $(ARFLAGS)" $@)
sky: $(MAIN)  
	$(CCC) -DFIRMAMENT -g  -o $@  $(INCLUDE)  $(MAIN)  \
	$(LIBFLAGS) $(LIBS) 
sky-dump: sky-dump.o libsky.a libc++adt.a
	$(CCC) sky-dump.o  $(OPTIMIZE)  $(INCLUDE) \
        $(LIBFLAGS) $(LIBS)  -o $@
.cc.o: 
	$(CCC) $(OPTIMIZE) $(SUPPRESS) $(CCCFLAGS) $(INCLUDE) $< -o $@

clean:
	rm -rf $(OBJ) sky sky-dump sky-dump.o core sky ii_files
	rm -rf $(ARFILE)
distclean:
	(cd ../c++adt/lib; make distclean)
	make clean

depend:
	makedepend $(INCLUDE) $(STL) $(MAIN)

# DO NOT DELETE
