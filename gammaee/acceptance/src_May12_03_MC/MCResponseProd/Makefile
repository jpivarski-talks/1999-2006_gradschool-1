#=============================================================================
#
# Purpose: Link a Processor/Producer
#
# How to use:
#
#   1.) Copy this file to your build area. (Please don't build code in your
#       source area!)
#
#   2.) This makefile includes "M.tail", which contains all the "meat".
#       (suffix rules, platform dependencies etc.)
#
#   3.) Dependencies (ala makedepend) are done via a ".depend" file 
#       which gets created and include by "M.tail".
#
#   4.) Make sure the environment variable USER_SRC is set to the
#       directory *above* the source code:
#         e.g. "setenv USER_SRC /home/mkl/work/cleo3/cvssrc"
#
#   5.) To link a shared library, do"
#         unix> gmake CXX=<compiler> shared_module
#         e.g. "gmake CXX=cxx shared_module"
#
#   6.) The library will appear by default as "../lib/lib<directory>.a", 
#       and the linked shared library as "../shlib/<directory>.so".
#       If you want the shared library name to have a different name,
#       specify that name with "SHARMODNAME" below.
#
#   7.) To compile and link in debug mode, use "DEBUG=y":
#          e.g. "gmake CXX=cxx DEBUG=y shared_module"
#        This will result in an appended "_g" to library and 
#       shared library names.
#
#   8.) You can OVERRIDE any symbol used in a makefile by specifying the new
#       symbol on the command line, for example, 
#          e.g. "gmake USER_OBJS=myfunc.o"
#       Please remember that this will OVERRIDE any value specified in the 
#       Makefile. If you just which to add extra information to the current
#       makefile value the 'XTRA_????' symbols have been created. Look through
#       this file to see which symbols add to the makefile symbols. 
#
#=============================================================================
SHELL := /bin/sh
USER_LINK := CXX

#----------------------------
# name of job and executable
#----------------------------
ifeq "$(JOB)" ""
  WHERE := $(shell pawd)
  JOB := $(notdir $(WHERE))
endif

# if you want your shared processor to have a distinctive name other
# than "<LIBNAME>.so", specify it here. E.g. MyLibProd
SHARMODNAME := $(JOB)

#----------------------------------------
# List of subdirectories containing code
#----------------------------------------
DIR_LIST := . Class Instantiate Fortran $(XTRA_DIR)




#----------------------
# PLATFORM DEPENDENCIES
#----------------------
# SOLARIS 
#   X windows - Xm is a shared library, need to be in SYS_LIBS
#   SYSLIB - directory name for additional system libraries
#
# OSF1
#   X windows - put all in X11_LIBs
#   SYS_LIBS - need to add these extra libraries
#----------------------
ifeq "$(OS_NAME)" "SunOS"
  CXX=CC
  LINK_FLAGS := -Bdynamic
  SYS_LIBS    = Xm 
  X11_LIBS    = grafX11 
  SYSLIB     += /usr/openwin/lib/ /usr/dt/lib/ /usr/local/lib 
endif

ifeq "$(OS_NAME)" "Linux"
  CXX=g++
  SYS_LIBS    = Xm crypt
  X11_LIBS    = grafX11 
endif

ifeq "$(OS_NAME)" "OSF1"
  CXX=cxx
  X11_LIBS  = grafX11 Xm Xt X11 PW Xmu ICE SM ICE
  #SYS_LIBS  = complex cxx exc dnet_stub mld
  SYS_LIBS  = exc dnet_stub mld
  SYSLIB   += /usr/lib
endif



#---------------------
# Set up CLEO library
#---------------------
CLEO3LIB	:= $(C3_LIB)/lib
OTHRLIB		:= $(C3_OTHER)/lib
CLEOLIB		:= $(C_LIB)/lib
CERN3LIB 	:= $(CERN3_LIB)/lib
COMMLIB   	:= $(COMM_LIB)/lib
SYSLIB   	:=

#------------------------------------
# USER, CLEO and CERN object modules
#------------------------------------
USER_OBJS :=	$(XTRA_OBJS)
CLEO3_OBJS :=	
OTHR_OBJS :=	
CLEO_OBJS :=	
CERN_OBJS :=	
COMM_OBJS :=	

#-------------------------------------------------------
# list of include directories
# USER_INCS should be defined with respect to USER_SRC
# CLEO3_INCS should be set to C3_INC; $USER_SRC/include is implicitly included
# OTHR_INCS should be defined with respect to C3_OTHER
# CLEO_INCS should be defined with respect to C_CVSSRC
# CERN_INCS should be defined with respect to CERNSRC
# (don't forget to leave the "." in the CLEO_INCS list)
#
# Add $(C3_CVSSRC)/guser_suez/ to OTHR_INCS as guser_suez is defined
# wrt to USER_SRC so if the user doesn't have a guser_suez
# checked out the compiler can't find the includes from guser_suez.
# USER_INCS is searched first, then OTHR_INCS
#-------------------------------------------------------
USER_INCS  := guser_suez MCResponse $(XTRA_INCS) . 
OTHR_INCS  := $(C3_CVSSRC)/guser_suez/ $(C3_CVSSRC)/C3Mu/C3Mu $(C3_INC)
CLEO3_INCS := $(C3_INC)
#CLEO_INCS  := .
CERN_INCS  := . geant321 
COMM_INCS  =	$(CONSTANTS_INCS)

#---------------------------------------
# USER, CLEO and CERN libraries to load
#---------------------------------------

USER_LIBS  :=	
CLEO3_LIBS :=	MCResponse		\
		DetectorConfiguration	\
		guser_suez		\
		Cleog3_suez		\
		ZDGeantHits		\
		ZDMCUtil		\
		DRGeantHits		\
		DRMCUtil		\
		MUGeantHits		\
		rimc			\
		CDOffCal		\
		C3cc			\
		C3Mu			\
		C3sv			\
		CalibratedData		\
		IRGeom			\
		CoilGeom		\
		ASiStorePro		\
		SiGeom			\
		AZDGeom			\
		ZDGeomProd		\
		DRWireLayer		\
		ZDWireLayerProd		\
		ActiveElements		\
		ADRGeom			\
		DRGeom			\
		CcGeom			\
		RichGeom		\
		C3Rich			\
		MUGeom			\
		MagField                \
		geometryForFortran	\
		FortranInterface	\
		G3DecayTree		\
		MCInfo			\
		GeantUtil		\
		lunmgr			\
		RandomModule		\
                KinematicTrajectory	\
                DetectorGeometry	\
		Geant3Interface		\
		BDLclientInst		\
		ProxyBind		\
                Processor		\
		CleoDB			\
                CommandPattern		\
                StorageManagement	\
                DataHandler		\
                ToolBox			\
#                Utility



OTHR_LIBS  :=	CLHEP
CLEO_LIBS  :=
CERN_LIBS  := geant321 pawlib	graflib	$(X11_LIBS) packlib mathlib
COMM_LIBS   = $(CONSTANTS_LIBS)
#SYS_LIBS   :=

#-------------------------------------------------
# list of undefined symbols
#-------------------------------------------------
USER_SYMS 	:= $(XTRA_SYMS)

#-------------------------------------------------
# force loading of all guser_suez symbols
#-------------------------------------------------
GUSER_LIB 	:= $(wildcard ../lib/libguser_suez.a)
ifeq "$(GUSER_LIB)" ""
 GUSERLIBDIR := $(patsubst %,%/$(OS_NAME),$(CLEO3LIB))
 GUSER_LIB = $(GUSERLIBDIR)/libguser_suez.a
endif
GUSER_FILES  	  := $(filter %.o, $(shell ar -t $(GUSER_LIB)))
GUSER_SYMS	:=  $(GUSER_FILES:%.o=%_)

#----------------------------------------------------------------------
# force loading of a symbols from qqjs73, but dummied out here
#----------------------------------------------------------------------
#JETSET_SYMS :=

#-----------------------------------
# make up list of undefined symbols
#-----------------------------------
CLEO_SYMS :=	$(USER_SYMS)	$(GUSER_SYMS)	$(JETSET_SYMS)

#--------------------------------------------------------------
# extra compiler/linker flags
#--------------------------------------------------------------
USER_FFLAGS     := $(XTRA_FFLAGS)
USER_CFLAGS     := $(XTRA_CFLAGS)
USER_CXXFLAGS   := $(XTRA_CXXFLAGS)

USER_LFLAGS	:= $(XTRA_LFLAGS)

#---------------------------------------------
# #define for cpp, define SELECT symbols here
#---------------------------------------------
# -DDEBUG_RESPONSE 
USER_DEFS 	:= -DCERNLIB_DECS -DCERNLIB_QMVAOS -DCERNLIB_DOUBLE -DCERNLIB_CG -DCERNLIB_UNIX -DCERNLIB_USRJMP -DCLEO_TYPECHECK -DCERNLIB_TYPE -DCERNLIB_UNIX $(XTRA_DEFS)

#--------------------------------------------------------------
# invoke standard tail to Makefile to execute compile and link
#--------------------------------------------------------------
include $(C3_GMAKE)/M.tail

#
# $Id: Makefile,v 1.23 2003/03/18 23:07:33 bkh Exp $
#
# DO NOT DELETE

