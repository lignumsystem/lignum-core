SRCDIR1 = ../src
SRCDIR2 = ../include

SRC = $(SRCDIR1)/VoxelBox.cc  $(SRCDIR1)/VoxelSpace.cc  

OBJ = ${SRC:.cc=.o} 

INCLUDE= -I../include -I../../c++adt/include -I../../stl-lignum/include \
-I../../Firmament/include -I../../ScotsPine/include -I/usr/X11R6/include -I../../Graphics

ARFILE=libvoxel.a

ETAGS = etags -d -T -C -o

.SUFFIXES: .o .cc

PROGFILES = program-files.html

sinclude Makedepend

$(ARFILE): $(OBJ)
	$(AR) $(ARFLAGS) $(ARFILE) $(OBJ)

.cc.o: 
	$(CCC)  $(OPTIMIZE) $(CCCFLAGS) $(INCLUDE) $<  -o $@  

touch:
	touch $(SRC)
html:
	enscript -E --color -Whtml --toc -p$(PROGFILES) include/*.h $(SRC)
clean:
	rm -rf $(OBJ) ../src/ii_files ../include/ii_files ii_files core

distclean: clean
	rm -rf  $(ARFILE) Makedepend

etags:
	$(ETAGS)   TAGSFILE ../src/*.cc ../include/*.h
depend:
	$(CCC) -M  $(INCLUDE) $(SRC) > Makedepend
#Do not delete this line -- make depend adds dependencies at the end of it
#If committing Makefile to cvs please remove the dependencies first
