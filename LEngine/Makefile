CCC = CC -64 -LANG:std

#OPTIMIZE = -Ofast=ip28 -IPA
OPTIMIZE   = -g 

AR =  $(CCC) -ar  
ARFLAGS = -o 

SUPPRESS = #-w 1155 -w 1183

CCCFLAGS = -c  #-prelink -ptused   -ptv  #  -fullwarn 


LIBD = lib64

lengine:
	(cd L2C; make "CCC=$(CCC)" "CCCFLAGS=$(CCCFLAGS)" "OPTIMIZE=$(OPTIMIZE)" \
                      "AR=$(AR)"  "ARFLAGS=$(ARFLAGS)" "LIBD=$(LIBD)"  l2c)
	(cd L2Lignum; make "CCC=$(CCC)" "CCCFLAGS=$(CCCFLAGS)" "OPTIMIZE=$(OPTIMIZE)"\
                            "AR=$(AR)"  "ARFLAGS=$(ARFLAGS)" "LIBD=$(LIBD)" libL.a)
	(mv  L2C/l2c bin; mv L2Lignum/libL.a lib)

gnu:
	make "CCC=g++" "CCCFLAGS=$(CCCFLAGS)" "OPTIMIZE=$(OPTIMIZE)" \
             "AR=ar"  "ARFLAGS=rvs" "LIBD=lib32"  lengine
lignux: 
	make "CCC=g++" "CCCFLAGS=-c" "OPTIMIZE=-g" \
             "AR=ar"  "ARFLAGS=rv" "LIBD=lib32" lengine
clean: 
	(cd L2C; make clean)
	(cd L2Lignum; make clean)
distclean: 
	(cd L2Lignum; make distclean)
	rm -f bin/l2c lib/libL.a
depend: 
	(cd L2Lignum; make "CCC=$(CCC)"  depend)

