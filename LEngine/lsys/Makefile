OS=IRIX64
TARGET=$(OS).out/liblsys.a
LSYSSRC=lsys.cpp
CPPSRC=

OBJECTS=${CPPSRC:.cpp=.o}

include Make.$(OS)

INCDIRS= -I../Globals -I/usr/include

$(TARGET): $(OBJECTS) lsys.o
	$(AR) $(AROPT) $(TARGET) $(OBJECTS) lsys.o


lsys.o: $(LSYSSRC) 
	$(CCPPI) $(CPPOPT) -I/usr/include $(INCDIRS) $(LSYSSRC)

.cpp.o:
	$(CCPP) $(CPPOPT) -I/usr/include $(INCDIRS) $<

#$(LSYSSRC): ../L2C/lsys.i
#	cp ../L2C/lsys.i $(LSYSSRC)

#$(LSYSSRC): ../L2C/lsys.ii
#cp ../L2C/lsys.ii $(LSYSSRC)
clean:
	-rm $(TARGET) $(OBJECTS) lsys.o
	-rm dependencies
	touch dependencies


build:
	make clean depend
	make

depend:
	$(DEPEND) $(DEFINES) $(PLAT_DEFINES) $(INCDIRS) $(CPPSRC) > dependencies

include dependencies

