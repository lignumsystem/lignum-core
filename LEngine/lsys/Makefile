OS=IRIX64
TARGET=$(OS).out/liblsys.a
LSYSL= lsys.L
LSYSSRC=lsys.cpp
CPPSRC=

OBJECTS=${CPPSRC:.cpp=.o}

include Make.$(OS)

INCDIRS= -I../Globals -I/usr/include -I../../c++adt/include -I../../stl-lignum/include

$(TARGET): $(LSYSSRC) lsys.o
	$(AR) $(AROPT) $(TARGET) $(OBJECTS) lsys.o

$(LSYSSRC): $(LSYSL)
	../L2C/IRIX64.out/l2c  $(LSYSL)  $(LSYSSRC)

lsys.o: $(LSYSSRC) 
	$(CCPPI) $(CPPOPT) -I/usr/include $(INCDIRS) $(LSYSSRC)

.cpp.o:
	$(CCPP) $(CPPOPT) -I/usr/include $(INCDIRS) $<

#$(LSYSSRC): ../L2C/lsys.i
#	cp ../L2C/lsys.i $(LSYSSRC)

#$(LSYSSRC): ../L2C/lsys.ii
#cp ../L2C/lsys.ii $(LSYSSRC)
clean:
	-rm -f $(TARGET) $(OBJECTS) lsys.cpp lsys.o
	-rm -f dependencies
	touch dependencies


build:
	make clean depend
	make

depend:
	$(DEPEND) $(DEFINES) $(PLAT_DEFINES) $(INCDIRS) $(CPPSRC) > dependencies

include dependencies
