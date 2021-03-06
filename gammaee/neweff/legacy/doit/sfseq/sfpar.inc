*
* $Id: sfpar.inc,v 1.9 2003/03/05 18:37:03 dpp Exp $
*
* $Log: sfpar.inc,v $
* Revision 1.9  2003/03/05 18:37:03  dpp
*      -> increase MHITSF from 160000 to 560000
*      -> increase MLAYSF from 100 to 150
*      -> add parameters for arrays for intermediate chain storage for z slices
*      -> remove special (faster?) reset for sfbwal
*
* Revision 1.8  2002/09/05 19:20:05  dpp
*      -> change MHITSF for TPC , protected by compile switc
*
* Revision 1.7  2001/11/20 17:52:17  dpp
*      -> delete stupid useless nonexistent include file
*
* Revision 1.6  2000/08/18 18:38:29  dpp
*      -> more definitions for WIDHIS
*
* Revision 1.5  2000/02/12 20:36:12  dpp
*      -> definition of WIDHIS locations and array size
*
* Revision 1.4  1999/11/19 22:48:36  dpp
* move time cuts from sfpar to sfcom
*
* Revision 1.3  1999/10/06 12:45:54  dpp
* dimension stereo transion thresholds
*
* Revision 1.2  1999/01/29 15:07:10  dpp
* z-measurements cuts for SFMERG
*
* Revision 1.1.1.1  1998/02/06 19:11:50  dpp
* DOIT first release.
*
* Revision 1.1.1.1  1997/04/30 12:31:42  clib
* Developmental version of DUET.
*
* Revision 1.9  1996/05/17 21:03:12  clib
* Improved VD TDC cuts for LEVEL3, will work for 81206 on, including
* the 2,5 bucket data.
*
* Revision 1.8  1996/04/23 19:38:02  dpp
* define VD TDC window for both before and after the VD E<=>W swaparoo
*
* Revision 1.7  1996/04/15 17:15:40  dpp
* moved some velocity calculation constants from parameters to common
*
* Revision 1.6  1996/04/03 16:16:08  dpp
* remove parameters for smallest starting layer in beamwall; put in SFCUTS
* tune VD TDC cuts for --> VD WEST <--  used for beam wall
*
* Revision 1.5  1996/03/20 17:07:16  zfiles
* add array of zeroing list for SFIND
*
* Revision 1.4  1996/02/29 17:50:23  zfiles
* changes for level3: time cuts, begin/end layers
*
* Revision 1.3  1996/02/15 15:04:10  zfiles
* Move sflacd to sfcom.
*
* Revision 1.2  1995/04/20 22:29:05  zfiles
* Dan's change. See TITLE.doit
*
* Revision 1.1.1.1  1994/10/08  01:01:12  zfiles
* first version of doit in CVS
*
*
*CMZ :  6.00/25 12/05/94  11.03.10  by  Anders Ryd
*CMZ :  6.00/18 22/03/94  14.08.23  by  Dan Peterson
*CMZ :          30/03/93  13.10.25  by  Dan Peterson
* ----------------------------------------------------------
* PARAMETERS FOR SFIND ROUTINES
*
* sfpar.inc
*
#if !defined(CLEO_NOCOMDOC)
C MNLBSF.....MINIMUM LAYERS BACK FROM MLASSF FOR SFIND TO INITIATE CHAIN
C MCHAIN.....MAXIMUM NUMBER OF CHAINS IN SIMPLE STORAGE
C MCHANLIST..Maximum number of chains in the intermediate list
C MSFZM......MAXIMUM NUMBER OF Z MEASUREMENTS ON CHAIN
C MULST......MULTIPLIER
C MULSTH.....HALF OF MULTIPLIER
C CELSSF.....SCALING, NUMBER OF WIRES IN LAYER PER METER RADIUS
C MVSTOR.....DECLARATION OF SPACE FOR VCELOCITY CALCULATION
C MSETUP.....MAXIMUM NUMBER OF SETS OF CUTTING VARIABLES SETUP IN SFINIT
C MSTDEF.....MAXIMUM NUMBER OF STEREO THRESHOLD DEFINITIONS
C MKILCH.....MAXIMUM NUMBER OF CHAIN THAT ARE MERGED INTO A SUPER CHAIN
C MCHANM.....MAXIMUM NUMBER OF CHAINS TO PASS(TOGETHER) TO THE OUTSIDE
C MHITSF.....MAXIMUM NUMBER OF RAW HITS in the simple storage
C MHITSFLIST.Maximum number of hits in the intermediate starage
C MISTFB.....TOTAL SIZE OF ISTFOR PLUS ISTBAK DUMMY ARRAY
C MLMCHN.....TOTAL SIZE OF LINCHN PLUS MINCHN DUMMY ARRAY
C MLAYSF.....NUMBER OF SF LAYER, SF LAYERS ARE DEFINED IN SFINIT
C MCDLSF.. ..NUMBER OF CD LAYERS WHICH ARE THE SOURCE OF SF LAYERS
C MMERG......MAXIMUM NUMBER OF MERGES
C MSUPCH.....MAXIMUM NUMBER OF SUPER CHAINS; >/=MCHAIN
C MSUPCE.....MAXIMUM NUMBER OF SUPER CHAIN ELEMENTS(SIMPLE CHAINS IN ALL SUPER)
C MSFSSF.....MAXIMUM SF LAYERS IN AN SSF LAYER
C MUTSTC.....MAXIMUM NUMBER OF TESTS OF CHAIN CONTINUITY, DIMENSION

C...THESE ARE CUTS IN SFMERG

C MVCTSF...CUT ON MATCHING VELOCITIES IN MERGE
C MGCTSF...CUT ON MAXIMUM GAP TO TRY TO BRIDGE IN SFMERG
C MLMTSF...NUMBER OF LAYERS TO TRY TO MATCH IN MERGE
C MCC1SF...CELL CUT FOR 1 LAYER IN MERGE
C MCCASF...CELL CUT FOR AVERAGE OF LAYERS IN MERGE
C MCCPSF...CELL CUT FOR PARALLEL CHAINS, DIE WHEN MAXPSF FAIL
C MAXPSF...NUMBER OF FAILURES OUTSIDE OF MCCPSF TO KILL MERGE
C MINEXT...MINIMUM EXTENSION OF MAJOR CHAIN IN MERGE
C ZNMIN1...MINIMUM NUMBER OF Z MEASUREMENTS IN A CHAIN TO USE ITS Z VALUE
C ZNMIN2...MINIMUM DIFF IN NUMBER OF Z MEASUREMENTS TO EXCLUDE A MEASUREMENT 
C ZNMIN3...MINIMUM SUM OF NUMBER OF Z MEASUREMENTS TO REQUIRE SIMILAR VALUES
C ZDMAX....MAXIMUM DIFFERENCE IN Z VALUES ALLOWED

C...THESE USED ONLY FOR SFBWAL

C SFLTPT...LOW  TIME CUT FOR PT
C SFHTPT...HIGH TIME CUT FOR PT
C SFLVDn...LOW  TIME CUT FOR VD
C SFHVDn...HIGH TIME CUT FOR VD
C SFLTDR...LOW  TIME CUT FOR DR
C SFHTDR...HIGH TIME CUT FOR DR

C...THESE ARE USED FOR SWITCHING IN SFDATA

C SFMAPV...value for selecting MAP ENTRY VALUE
C SFSMAP...value for SETTING THE 1ST MAP LOCATION POINTER
C SF1STH...value for selecting FIRST HIT IN LAYER
C SFNXTH...value for selecting NEXT HIT IN LAYER
C SFCYLN...value for selecting CYLINDER NUMBER
C SFWIRN...value for selecting WIRE NUMBER
C SFRTDC...value for selecting RAW TDC
C SFTMPS...value for selecting TIME IN PICOSECONDS
C SFRADC...value for selecting RAWADC
C SFADCH...value for selecting PULSE HEIGHT IN HAPPY UNITS

C...THESE DEFINE THE WIDTH/SHIFT/VERIFICATION HISTORY IN SFCHAN

C MWIDH..........array size of WIDHIS
C MWIDHP.........array size +1, for the storage array in DSFHIT
C WH_W_LEN.......width adjustments due to chain length
C WH_W_GAP.......width adjustments due to gaps in chain
C WH_W_NAR.......width adjustments due to narrow cell following wide
C WH_W_ST_CH.....width adjustments due to change in stereo angle
C WH_S_SMO.......shift in prediction based on smoothing 
C WH_W_CNTR......width adjustments due to prediction at cell center
C WH_W_ST_SH.....width adjustments due to scaled stereo shift
C WH_W_VEL.......width adjustments due to large velocity
C WH_W_IG_DOUB...width adjustments due to ignoring doublet
C WH_W_PHICOR....width adjustments based on PHICOR; excess velocity change
C WH_W_RAD_OUT...width adjustments to include radially out hit
C WH_V_Z_STR.....details of verification of z hits to allow select trial
C WH_V_Z_RZT.....details of verification of z hits to allow remove z test
 


#endif

      INTEGER MNLBSF
      INTEGER MCHAIN,MHITSF,MLAYSF,MCDLSF
      INTEGER MCHANLIST,MHITSFLIST
      INTEGER MSFZM
      INTEGER MISTFB,MLMCHN
      INTEGER MULST, MULSTH,CELSSF
      INTEGER MVSTOR,MSETUP,MSTDEF
      INTEGER MKILCH,MCHANM
      INTEGER MMERG
      INTEGER MSUPCH,MSUPCE
      INTEGER MSFSSF
      INTEGER MUTSTC

      INTEGER MVCTSF,MGCTSF
      INTEGER MLMTSF,MCC1SF,MCCASF,MCCPSF,MAXPSF,MINEXT
      INTEGER ZNMIN1,ZNMIN2,ZNMIN3
      INTEGER ZDMAX

      INTEGER SFLTPT,SFHTPT
      INTEGER SFLVD1,SFHVD1,SFLVD2,SFHVD2
      INTEGER SFLTDR,SFHTDR
      INTEGER GTIME,TFUDG1,TFUDG2,TFUDG3
      INTEGER SFMAPV,SFSMAP,SF1STH,SFNXTH,SFCYLN
      INTEGER SFWIRN,SFRTDC,SFTMPS,SFRADC,SFADCH

      INTEGER MWIDH,       MWIDHP,      WH_W_LEN
      INTEGER WH_W_GAP,    WH_W_NAR,    WH_W_ST_CH
      INTEGER WH_S_SMO,    WH_W_CNTR,   WH_W_ST_SH
      INTEGER WH_W_VEL,    WH_W_IG_DOUB,WH_W_PHICOR
      INTEGER WH_W_RAD_OUT,WH_V_Z_STR
      INTEGER WH_V_Z_RZT_R,WH_V_Z_RZT_Z,WH_V_Z_RZT_C


      PARAMETER (MNLBSF=10)
      PARAMETER (MCHAIN=50)
      PARAMETER (MCHANLIST=5000)
      PARAMETER (MSFZM =10)
      PARAMETER (MULSTH=512,MULST=MULSTH*2, CELSSF=450)
      PARAMETER (MVSTOR=14)
      PARAMETER (MSTDEF=4)
      PARAMETER (MSETUP=3)
      PARAMETER (MKILCH=7)
      PARAMETER (MCHANM=20)

#if defined(CLEO_DOITTPC)
      PARAMETER (MHITSF=560000,MLAYSF=150)
#else
      PARAMETER (MHITSF=11710,MLAYSF=56)
#endif
      PARAMETER (MHITSFLIST=2*MHITSF)
      PARAMETER (MCDLSF=200)
      PARAMETER (MISTFB=2*MHITSF, MLMCHN=2*MCHAIN)
      PARAMETER (MMERG =100)
      PARAMETER (MSUPCH=150)
      PARAMETER (MSUPCE=200)
      PARAMETER (MSFSSF=2)
      PARAMETER (MUTSTC=3)

      PARAMETER (MVCTSF=4*MULST/10, MGCTSF=12)
      PARAMETER (MLMTSF=4)
      PARAMETER (MCC1SF=6*MULST, MCCASF=4*MULST)
      PARAMETER (MCCPSF=2*MULST, MAXPSF=3, MINEXT=3)
      PARAMETER (ZNMIN1=1)
      PARAMETER (ZNMIN2=2)
      PARAMETER (ZNMIN3=5)
      PARAMETER (ZDMAX=MULST*1/2)


      PARAMETER (SFLTPT=1120,SFHTPT=2280)
      PARAMETER (SFLVD1=1050,SFHVD1=2000)
      PARAMETER (SFLVD2= 600,SFHVD2=1600)
      PARAMETER (SFLTDR=1000,SFHTDR=4000)

      PARAMETER (SFMAPV= 1,SFSMAP= 2,SF1STH= 3,SFNXTH= 4,SFCYLN= 5)
      PARAMETER (SFWIRN= 6,SFRTDC= 7,SFTMPS= 8,SFRADC= 9,SFADCH=10)

      PARAMETER (MWIDH=       16 , MWIDHP= MWIDH+1 , WH_W_LEN=     1 )
      PARAMETER (WH_W_GAP=     2 , WH_W_NAR=     3 , WH_W_ST_CH=   4 )
      PARAMETER (WH_S_SMO=     5 , WH_W_CNTR=    6 , WH_W_ST_SH=   7 )
      PARAMETER (WH_W_VEL=     8 , WH_W_IG_DOUB= 9 , WH_W_PHICOR= 10 )
      PARAMETER (WH_W_RAD_OUT=11 , WH_V_Z_STR=  13 )
      PARAMETER (WH_V_Z_RZT_R=14 , WH_V_Z_RZT_Z=15 , WH_V_Z_RZT_C=16 )

C23456789 123456789 123456789 123456789 123456789 123456789 123456789 12






