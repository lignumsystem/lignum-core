
SRC = ../Axis/AxisFriend.cc  \
      ../BranchingPoint/BranchingPointFriend.cc \
      ../Bud/BudFriend.cc \
      ../Bud/Bud.cc \
      ../TreeMetaFileParser/TreeMetaFileParser.cc \
      ../TreeSegment/BroadLeaf.cc \
      ../TreeSegment/TreeSegmentFriend.cc \
      ../TreeSegment/TreeSegment.cc \
      ../TreeCompartment/TreeCompartmentFriend.cc\
      ../Tree/TreeFriend.cc \
      ../Tree/Tree.cc \
      ../TreeSegment/BeamShading.cc \
      ../TreeSegment/BroadLeafMetabolism.cc \
      ../TreeSegment/CfTreeSegment.cc 

OBJ = ${SRC:.cc=.o}

INCLUDE = -I../include  -I../../c++adt/include -I../../Firmament/include


CCC = CC -64 -LANG:std

ETAGS = etags -d -T -C -o

OPTIMIZE = -g
CCCFLAGS =   -c   

.SUFFIXES: .o .cc

AR=$(CCC) -ar
ARFLAGS= -o
ARFILE = libLGM.a

sinclude Makedepend

$(ARFILE): $(OBJ)
	$(AR) $(ARFLAGS) $(ARFILE) $(OBJ)

.cc.o: 
	$(CCC)  $(OPTIMIZE) $(CCCFLAGS) $(INCLUDE) $<  -o $@  

touch:
	touch $(SRC)

clean:
	rm -rf $(OBJ) core ../*/ii_files

distclean: clean
	rm -rf  $(ARFILE) Makedepend
etags:
	$(ETAGS)   TAGSFILE ../src/*.cc ../include/*.h

depend:
	$(CCC) -M  $(INCLUDE) $(SRC) > Makedepend

#Do not delete this line -- make depend adds dependencies at the end of it
#If committing Makefile to cvs please remove the dependencies first
