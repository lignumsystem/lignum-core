PRJDIR=..
OS=IRIX64

TARGET=$(OS).out/l2c

OBJECTS=\
main.o\
module.o\
production.o\
lex_l.o\
l2c_tab.o

LSYSFILE = match-test.l
LSYSFILE_II=lsys.ii

include Make.$(OS)
LCPP = match-test.l
MATCHOBJECTS=matching.o match.o \
	     ../Generate/lsysintrfc.o\
             ../Generate/lstring.o \
             ../Generate/lstriter.o \
             ../Generate/succstor.o \
             module.o production.o \
             lsys.o \
             lex_l.o l2c_tab.o

INCDIRS=\
$(PLATINC)\
-I$(PRJDIR)/Common\
-I../Globals -I../Generate \
-I../lsys

LIBS=\
$(PLATLIBS)


LINKDIRS=\
$(PLATLINKDIRS)

CPPFILES=\
${OBJECTS:.o=.cpp}

FLEX=flex

FLEXOPT=-Pl

BISON=bison

BISONOPT=-d --debug -p l

$(TARGET): l2c_tab.cpp lex_l.cpp $(OBJECTS)  
	$(LINK) $(LINKFLAGS) $(OBJECTS) $(LINKDIRS) $(LIBS) -o $(TARGET)

match: depend $(MATCHOBJECTS) 
	$(LINK) $(LINKFLAGS) $(MATCHOBJECTS) $(LINKDIRS) $(LIBS) -o  $@
.cpp.o:
	$(CCPP) -c $(CCPPOPT) $(DEFINES) $(PLAT_DEFINES) $(INCDIRS) -o $@ $<

l2c_tab.cpp l2c_tab.h: l2c.y
	$(BISON) $(BISONOPT) l2c.y
	mv l2c.tab.h l2c_tab.h
	mv l2c.tab.c l2c_tab.cpp

lex_l.cpp: l2c.l
	$(FLEX) $(FLEXOPT) l2c.l
	mv lex.l.c lex_l.cpp

lsys.o: $(LCPP)
	cp $(LCPP) test.cpp
	CC -E -I../Globals -I../Generate test.cpp > test.i
	$(OS).out/l2c test.i lsys.i
	CC -c lsys.i 

build:
	make clean
	make depend $(TARGET)

clean:
	-rm -f $(TARGET) $(OBJECTS)  $(MATCHOBJECTS) match \
        l2c_tab.cpp l2c_tab.h lex_l.cpp dependencies core
	touch dependencies

depend: l2c_tab.cpp lex_l.cpp 
	$(DEPEND) $(DEFINES) $(PLAT_DEFINES) $(INCDIRS) $(CPPFILES) > dependencies

test:
	make
	$(TARGET) test.l 

testd:
	make
	$(TARGET) test.l 1

inst:
	make
	cp $(TARGET) $(HOME)/bin.$(OS)

include dependencies

