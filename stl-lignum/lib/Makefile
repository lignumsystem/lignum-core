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

OBJ = ../Axis/AxisFriend.o \
      ../BranchingPoint/BranchingPointFriend.o \
      ../Bud/BudFriend.o \
      ../Bud/Bud.o \
      ../TreeMetaFileParser/TreeMetaFileParser.o \
      ../TreeSegment/BroadLeaf.o \
      ../TreeSegment/TreeSegmentFriend.o \
      ../TreeSegment/TreeSegment.o \
      ../TreeCompartment/TreeCompartmentFriend.o \
      ../Tree/TreeFriend.o \
      ../Tree/Tree.o \
      ../TreeSegment/BeamShading.o \
      ../TreeSegment/BroadLeafMetabolism.o \
      ../TreeSegment/CfTreeSegment.o


INCLUDE = -I../include  -I../../c++adt/include -I../../Firmament/include
STL = -I/usr/include/CC
CCC = CC -64
ETAGS = etags -d -T -C -o

OPTIMIZE = -g
CCCFLAGS =   -c   

.SUFFIXES: .o .cc
ARCOMMAND=$(CCC) -ar
ARCOMMANDFLAGS= -o
AR = $(ARCOMMAND)
ARFLAGS = $(ARCOMMANDFLAGS)
ARFILE = libLGM.a


$(ARFILE): $(OBJ)
	$(AR) $(ARFLAGS) $(ARFILE) $(OBJ)

.cc.o: 
	$(CCC)  $(OPTIMIZE) $(CCCFLAGS) $(INCLUDE) $(STL) $<  -o $@  

touch:
	touch $(SRC)

clean:
	rm -rf $(OBJ) core 

distclean: clean
	rm -rf $(OBJ) core $(ARFILE)
	rm -rf ../Axis/ii_files ../BranchingPoint/ii_files
	rm -rf ../Bud/ii_files ../Tree/ii_files 
	rm -rf ../TreeMetaFileParser/ii_files
	rm -rf ../TreeCompartment/ii_files ../TreeSegment/ii_files

etags:
	$(ETAGS)   TAGSFILE ../src/*.cc ../include/*.h
depend:
	makedepend $(INCLUDE) $(STL) $(SRC)
