SRC = TreeMetaFileParser.cc 


CCINCLUDE = -I/usr/include/CC
INCLUDE = -I. -I../../c++adt/include -I../include

LIBDIR = -L../../c++adt/lib

LIB = -lc++adt

CC = CC -64

CFLAGS = -g -exceptions 

.IGNORE:

it: $(SRC)
	$(CC) -o $@ -DINITIALIZE_TREE $(CFLAGS) $(INCLUDE)  $(SRC) $(LIBDIR) $(LIB)

clean:
	-rm -rf it ii_files '*.o' 
depend:
	makedepend $(CCINCLUDE) $(INCLUDE) $(SRC)
# DO NOT DELETE

TreeMetaFileParser.o: ../include/TreeMetaFileParser.h /usr/include/stdlib.h
TreeMetaFileParser.o: /usr/include/standards.h /usr/include/sgidefs.h
TreeMetaFileParser.o: ../../c++adt/include/Table.h
TreeMetaFileParser.o: ../../c++adt/include/DList.h
TreeMetaFileParser.o: ../../c++adt/include/DListElement.h
TreeMetaFileParser.o: ../../c++adt/include/boolean.h
TreeMetaFileParser.o: ../../c++adt/include/Lex.h
TreeMetaFileParser.o: ../../c++adt/include/CString.h /usr/include/string.h
TreeMetaFileParser.o: /usr/include/stdio.h /usr/include/ctype.h
TreeMetaFileParser.o: /usr/include/CC/stream.h /usr/include/CC/iostream.h
TreeMetaFileParser.o: /usr/include/memory.h /usr/include/CC/iomanip.h
TreeMetaFileParser.o: /usr/include/CC/generic.h /usr/include/CC/stdiostream.h
TreeMetaFileParser.o: /usr/include/CC/fstream.h
