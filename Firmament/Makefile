SRC = Firmament.cc FirmamentWithMask.cc MineSet.cc Interlen.cc \
       Voxel.cc voxellattice.cc voxelmatrix.cc
OBJ  = ${SRC:.cc=.o}
 
CCC = CC -64 -LANG:std

AR = $(CCC) -ar
ARFLAGS = -o
ARFILE = lib/libsky.a


#OPTIMIZE = -Ofast=ip28 -IPA
OPTIMIZE   = -g 

SUPPRESS = #-w 1155 -w 1183

CCCFLAGS = -c #-ptv -prelink -fullwarn 

INCLUDE =  -Iinclude -I../c++adt/include -I../stl-lignum/include -I../ScotsPine/include 

LIBFLAGS = -L../c++adt/lib -L../stl-lignum/lib -Llib 

#LIB1   = libc++adt.a

#LIBADT = -lc++adt
LIBMATH  = -lm 
LIBS     = -lsky -lc++adt $(LIBMATH)

.SUFFIXES: .o .cc

sinclude Makedepend

libsky.a:  $(OBJ)
	$(AR) $(ARFLAGS) $(ARFILE) $(OBJ)
libc++adt.a:
	(cd ../c++adt; make "CCC=$(CCC)" "CCCFLAGS=$(CCCFLAGS)" \
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
distclean: clean
	rm -f $(ARFILE) Makedepend
	(cd ../c++adt; make distclean)
depend:
	$(CCC) -M  $(INCLUDE) $(SRC) > Makedepend

#Do not delete this line -- make depend adds dependencies at the end of it
#If committing Makefile to cvs please remove the dependencies first

