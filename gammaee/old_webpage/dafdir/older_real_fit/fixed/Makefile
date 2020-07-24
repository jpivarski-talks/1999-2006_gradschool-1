#
# Makefile to make simple program
#
FFLAG = -O1 -static -w1

# -- executable name
EXE   = fitY2s

# -- library search path
CERNDIR = $(CERNLIB)
CLIBDIR = /cleo/clib/lib

# -- main driver
MAIN =   fit

# -- libraries

CERNBAG = -L$(CERNDIR) \
	-lkernlib -lpacklib -lmathlib

LIBS =	-L$(CLIBDIR) \
	$(CERNBAG)

# CPPBAG = get_isgw2_ff_3s1_.cc report.cc PDL.cc get_as.cc get_gammaji.cc
# CPPOBJ = get_isgw2_ff_3s1_.o report.o PDL.o get_as.o get_gammaji.o

FORTBAG = $(wildcard *.F)
FORTOBJ = $(FORTBAG:%.F=%.o)

# -- action
#fit:   
#

##$(EXE):	$(MAIN).o $(CPPOBJ)
##	f77 $(MAIN).o -non_shared \

$(EXE):	$(FORTOBJ) \
	f77 $(FORTOBJ) -non_shared \
	$(CERNBAG)  \
	-lcomplex -lcxx -lexc -lUfor -lfor -lFutil -lots -lm \
	$(CERNBAG) -o $(EXE) -Wl,-m > $(EXE).map

## %.o:%.cc
## 	cxx -c -D__CXX__  $<

##$(MAIN).o:$(MAIN).F
##	f77 -c $(MAIN).F

## %.o:%.F
%.F:
	f77 -I$(CERNSRC)/packlib/minuit -c $<
