TARGET=libMyCommon.a

SOURCE=\
file.c++\
sarray.c++\
dynarray.c++\
dynstack.c++

OBJECTS=${SOURCE:.c++=.o}

AR=ar
AROPT=-ruv
CC=CC

DEFINES=-DDEBUG
CCOPT=-c -g -O0 -fullwarn -woff 1375 $(DEFINES) -n32
DEPENDOPT=-M $(DEFINES)


$(TARGET) : $(OBJECTS)
	$(AR) $(AROPT) $(TARGET) $(OBJECTS)

.c++.o:
	$(CC) $(CCOPT) $<

depend:
	CC $(DEPENDOPT) $(SOURCE) > dependencies

clean:
	-rm $(TARGET)
	-rm $(OBJECTS)
	-rm dependencies
	touch dependencies

build:
	make clean
	make depend
	make

include dependencies

