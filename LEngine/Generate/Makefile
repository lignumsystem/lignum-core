#OS=Linux
OS=IRIX64
TARGET=$(OS).out/lengine
LIBTRG=$(OS).out/liblengine.a

OBJECTS=\
lstring.o\
lstriter.o\
succstor.o\
lsysintrfc.o\
match.o

include Make.$(OS)


INCDIRS=\
$(PLATINC)\
-I../Globals


LIBS=\
$(PLATLIBS)


LINKDIRS=\
$(PLATLINKDIRS)

CPPFILES=\
${OBJECTS:.o=.cpp}

lib:
	make $(LIBTRG)

$(TARGET): test.o $(OBJECTS) ../lsys/lsys.o
	$(LINK) $(LINKFLAGS) test.o $(OBJECTS) ../lsys/lsys.o $(LINKDIRS) $(LIBS) -o $(TARGET)



$(LIBTRG): $(OBJECTS)
	ar -ruv $(LIBTRG) $(OBJECTS)

.cpp.o:
	$(CCPP) $(CCPPOPT) $(DEFINES) $(PLAT_DEFINES) $(INCDIRS) -o $@ $<

build:
	make clean
	make depend $(TARGET)

clean:
	-rm -f $(TARGET) $(OBJECTS) dependencies core
	touch dependencies

depend: 
	$(DEPEND) $(DEFINES) $(PLAT_DEFINES) $(INCDIRS) $(CPPFILES) > dependencies

test:
	make
	$(TARGET) test.l 

testd:
	make
	$(TARGET) test.l 1
include dependencies

