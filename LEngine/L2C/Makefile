#To compile "l2c" on SGI type 
#    make l2c
#To compile with g++ on SGI or on  Linux type
#    make gnu  
#or  (using copy paste)
#    make "CCC=g++" "CCCFLAGS=-c" "OPTIMIZE=-g"  l2c

SRC=main.cpp module.cpp production.cpp l2c_tab.cpp lex_l.cpp 
OBJ=${SRC:.cpp=.o}

OPTIMIZE = -g
SUPPRESS =  

CCC = CC -64 -LANG:std
CCCFLAGS = -c   

INCLUDE = -I. -I../Common -I../Globals -I../Generate 

FLEX=flex
FLEXOPT=-Pl

BISON=bison
BISONOPT=-d --debug -p l

.SUFFIXES:.cpp

sinclude Makedepend

l2c: l2c_tab.cpp lex_l.cpp $(OBJ)  
	$(CCC)  $(OBJ) -o $@

gnu:
	make "CCC=g++" "CCCFLAGS=-c" "OPTIMIZE=-g"  l2c
lignux: 
	make "CCC=g++" "CCCFLAGS=-c" "OPTIMIZE=-g"  l2c

l2c_tab.cpp l2c_tab.h: l2c.y
	$(BISON) $(BISONOPT) l2c.y
	mv l2c.tab.h l2c_tab.h
	mv l2c.tab.c l2c_tab.cpp

lex_l.cpp: l2c.l
	$(FLEX) $(FLEXOPT) l2c.l
	mv lex.l.c lex_l.cpp

.cpp.o:
	$(CCC) -c  $(OPTIMIZE) $(SUPPRESS) $(CCCFLAGS) $(INCLUDE)  -o $@ $<

clean:
	rm -rf  $(OBJ) l2c_tab.cpp l2c_tab.h lex_l.cpp core ii_files
distclean:clean
	rm -f l2c Makedepend

depend: l2c_tab.cpp lex_l.cpp 
	$(CCC) -M  $(INCLUDE) $(SRC) > Makedepend

