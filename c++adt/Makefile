CCC = CC -64 -LANG:std

OPTIMIZE = -g
CCCFLAGS =   -c 

AR = $(CCC) -ar  
ARFLAGS = -o
ARFILE = libc++adt.a

.SUFFIXES: .o .cc


$(ARFILE): 
	(cd lib; make "CCC=$(CCC)" "CCCFLAGS=$(CCCFLAGS)" "OPTIMIZE=$(OPTIMIZE)" \
                      "AR=$(AR)"  "ARFLAGS=$(ARFLAGS)" $@) 
touch:
	(cd lib; make touch)

html:
	cd lib; make html)
clean:
	(cd lib; make clean) 

distclean: 
	(cd lib; make distclean)

etags:
	(cd lib; make etags)
depend:
	(cd lib; make "CCC=$(CCC)" depend)
