

#make "CCC=g++" "CCCFLAGS=-c" "OPTIMIZE=-O" "AR=ar"  "ARFLAGS=rvs" 

CCC=g++
CCCFLAGS=-c
OPTIMIZE=-g
AR=ar
ARFLAGS=rvs

ARFILE = libvoxel.a

LIBOGL =  -lglut -lGLU -lGL -lXmu -lXext -lX11

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
