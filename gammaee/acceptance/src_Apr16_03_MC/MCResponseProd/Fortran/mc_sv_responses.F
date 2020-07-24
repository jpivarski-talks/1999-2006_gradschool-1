*
* $Id: mc_sv_responses.F,v 1.8 2001/11/19 23:32:24 victor Exp $
*
* $Log: mc_sv_responses.F,v $
* Revision 1.8  2001/11/19 23:32:24  victor
* added resetEffs array
*
* Revision 1.7  2000/07/25 20:19:54  pg
* Minor clean up in Si code
*
* Revision 1.6  2000/07/14 20:07:29  lkg
* store decay tree id rather than geant id in response object
*
* Revision 1.5  2000/04/19 00:44:26  pg
* Added protection against TOO MANY HITS case. Extract Si geometry from SVAlignment stream.
*
* Revision 1.4  2000/03/15 21:26:36  pg
*  Delayed tag of the latest Si changes
*
* Revision 1.3  2000/03/08 22:38:46  pg
* Forgot to commit changes to Si hit production.
*
* Revision 1.2  1999/11/16 20:50:47  pg
* Added Si simulation
*
* Revision 1.1.1.1  1999/04/16 20:07:32  jjo
* Move MCxxResponseProxy from MCResponse library to this library.
* Make Geant calls from this library as fetching the hits (via GFHITS)
* currently couples this library to Geant.  Also, use bindable proxies. (jjo)
*
* Revision 1.1  1999/02/25 21:31:09  bkh
* Update
*
*
      SUBROUTINE MC_SV_RESPONSES( MAXTSV, NTOTSV, WAFER,
     +                            LTRKSV, ETRKSV,
     +                            XIN, XOUT, ZIN, ZOUT, resetEffs)

*
* begin_doc
*
*  Documentation for subroutine mc_sv_responses
*
*  Purpose:
*  --------
*
*  Input Parameters:  (Name - Type - Meaning)
*  ----------------
*
*  Output Parameters:  (Name - Type - Meaning)
*  -----------------
*
*  Other routines:
*  ---------------
*
*  Notes:
*  ------
*
*  Author:   Brian K. Heltsley      Created:  Fri Feb 19 16:17:42 EST 1999
*  -------
*
*  Major revisions:
*  ----------------
*     
*
* end_doc
*
#if defined(CLEO_TYPECHEK)
      IMPLICIT NONE
#endif
*
* begin_inc
*  Include files :
*  ---------------------
#include "seq/clutil/mesrep.inc"

#include "SiGeom/SiGeant3SetNames.h"
#include "cl3seq/sv3seq/svhseq.inc"
* end_inc
*
* begin_var
*  input/output variables:
*  -----------------------

      INTEGER MAXTSV, NTOTSV, WAFER(*), LTRKSV(*)

      REAL    ETRKSV( * ),XIN(*), XOUT(*), ZIN(*), ZOUT(*)
      INTEGER resetEffs(*)

*********************************************************************
* Local variables:
*
*       ICBCE  : 1 for CGNSCB, 2 for CGNSCE, loop index
*
*       MAXHIT : Maximum number of hits accepted
*
*       MWDVOL : Number of words specifying volume number
*
*       MWDHIT : Number of words required per hit
*
*       NUMBV  : Volume numbers
*
*       ITRM   : Track number for a given hit, set to 0 for used hits
*
*       VHIT   : Hits from GEANT
*
*       IERR   : error flag returned from CGCSDP
*
*       MDETS  : Number of detectors accepted
*
*       CUSET  : Detector set name
*
*       CUDET  : Detector name
*
*       CALLED : Is TRUE if this routine has been called with indices 1 or 2
*
*       IHIT   : hit index
*
*       JHIT   : hit index
*
*       ITOT   : track index
*
*       JENRCC : index in VHIT where the deposited energy is stored
*********************************************************************
*  Local pre-defined variables:
*  ---------------------------
      LOGICAL RCSINI,CALLED
      CHARACTER*(*) CHRCSS, CHRCSR, CHRCST, CHRCSD, CHRCSA
      PARAMETER(CHRCSS='$RCSfile: mc_sv_responses.F,v $')
      PARAMETER(CHRCSR='$Revision: 1.8 $')
      PARAMETER(CHRCST='$State: Exp $')
      PARAMETER(CHRCSD='$Date: 2001/11/19 23:32:24 $')
      PARAMETER(CHRCSA='$Author: victor $')
*
      CHARACTER*(*) CRNAME
      PARAMETER(    CRNAME = 'MC_SV_RESPONSES' )
*
*  Local User defined variables:
*  -----------------------------
*
*

      INTEGER    MAXHIT,        MWDVOL,     MWDHIT,     JENRCC
      PARAMETER( MAXHIT = 1000, MWDVOL = 1, MWDHIT = 14, jenrcc = 6 )

      INTEGER NUMBV( MWDVOL, MAXHIT ), ITRM( MAXHIT ), NUMVS( MWDVOL )
      REAL    VHIT(  MWDHIT, MAXHIT )


      INTEGER     MDETS
      PARAMETER ( MDETS = 61 )
c Due to quirks of GEANT and geometry parsing system, we have to declare 
c 61 different 'detectors', one per ladder, even though they are all
c identical
      CHARACTER*4 CUSET, CUDET(MDETS)

      INTEGER IHIT, JHIT, ITOT, NHITS, IERR, IOERR

      integer i,j
      integer NV,NBITSV,IDTYPE,iset1,idet1,nwhi1,nwdi1
      Character*4 NAMESV
      integer wfn
      real MTOCM,CMTOM
      parameter (MTOCM = 100., CMTOM = 0.01) 
* end_var
*

*  Data statements:
*  ----------------
*
      SAVE RCSINI
      SAVE CALLED
*
      DATA RCSINI/.TRUE./
      DATA CALLED/.FALSE./

      DATA NUMVS / MWDVOL*0 /
      DATA CUSET / 'SI3 ' /
c      DATA CUDET / 'SNSR' /
*
*  executable code for routine mc_sv_responses:
#if WRITE_RCS_INFO
      IF(RCSINI)THEN
        RCSINI = .FALSE.
        WRITE(6,*)'-------- CVSinfo --------'
        WRITE(6,*)CHRCSS
        WRITE(6,*)CHRCSR//' '//CHRCST
        WRITE(6,*)CHRCSD//' '//CHRCSA
      ENDIF
#endif
*----6----------------------------------------------------------------72
*
* First time around, check set definition, get set info...
      IF( .NOT. CALLED ) THEN
         
         CALLED = .TRUE.
         
*     Check that set is defined
         CALL CGCSDP( MWDVOL, CUSET, MDETS, CUDET, IERR )
         
         IF( IERR .NE. 0 ) THEN
            
            WRITE( CHMESS, 10010, IOSTAT = IOERR ) CUSET
10010       FORMAT(' Detector for set ', A, ' is not defined ')
            CALL MESLOG( CRNAME, 1, MSABOR )
            
         ELSE
            WRITE( CHMESS, 10011, IOSTAT = IOERR ) CUSET
10011       FORMAT(' Detector for set ', A, ' is defined. All OK. ')
            CALL MESLOG( CRNAME, 1, MSINFO )
            
         endif
         
      ENDIF
      ihit=0
      ntotsv=0
c     Loop over detectors
      do 85 i = 1,mdets
         
         CALL GFHITS( CUSET, CUDET(i), MWDVOL, MWDHIT, MAXHIT, 0, NUMVS,
     +        ITRM, NUMBV, VHIT, NHITS )
         
         IF( NHITS .GT. MAXHIT ) THEN
            
            WRITE( CHMESS, 10020, IOSTAT = IOERR ) MAXHIT
10020       FORMAT(' Too many hits for local buffer, using', I6 )
            CALL MESLOG( CRNAME, 2, MSERRO )
            
            NHITS = MAXHIT
            
         ENDIF
         

         DO 75 J=1,NHITS
#ifdef 0
            WRITE(*,*) '   -----------------------------'
            WRITE(*,*) '   HIT Information for HIT #', J
            WRITE(*,*) '   TRACK #',ITRM(J)
            WRITE(*,*) '   WAFER #',VHIT(JSVWN,J)
            WRITE(*,*) '   '
            WRITE(*,*) '   XInWorld',VHIT(JSVXIW,J)
            WRITE(*,*) '   YInWorld',VHIT(JSVYIW,J)
            WRITE(*,*) '   ZInWorld',VHIT(JSVZIW,J)
            WRITE(*,*) '   '
            WRITE(*,*) '   XInLocal',VHIT(JSVXIL,J)
            WRITE(*,*) '   YInLocal',VHIT(JSVYIL,J)
            WRITE(*,*) '   ZInLocal',VHIT(JSVZIL,J)
            WRITE(*,*) '   '
            WRITE(*,*) '   XOutLocal',VHIT(JSVXO,J)
            WRITE(*,*) '   YOutLocal',VHIT(JSVYO,J)
            WRITE(*,*) '   ZOutLocal',VHIT(JSVZO,J)
            WRITE(*,*) '   '
            WRITE(*,*) '   P',VHIT(JSVP,J)
            WRITE(*,*) '   S=PATH LENGTH OF THE STEP',
     &           VHIT(JSVS,J)
            WRITE(*,*) '   TLEN=TRACK LENGTH AT CURRENT PT',
     &           VHIT(JSVTLN,J)
            WRITE(*,*) '   EDEP',VHIT(JSVED,J)  
            WRITE(*,*) '   '
#endif      
            ihit=ihit+1
c     Protect against overflow
            if(ihit.ge.maxtsv) then
               WRITE( CHMESS, 10030, IOSTAT = IOERR ) MAXTSV
10030          FORMAT(' Overflowing input array, using', I9 )
               CALL MESLOG( CRNAME, 3, MSERRO )
            else
C     set wafer number - it will work as a cell number for now.
               WAFER(ihit) = VHIT(JSVWN,J)
c     Associated track
               CALL GDT_GEANT_TO_DKTREE_PARTID( ITRM(J), LTRKSV(ihit) )
c     Deposited energy
               ETRKSV(ihit) = VHIT(JSVED,J)
C     convert from cm to meters (08/19/93): 'in' and 'out' coordinates  
               ZIN(ihit)  = VHIT(JSVZIL,J)*CMTOM
               ZOUT(ihit) = VHIT(JSVZO,J)*CMTOM
               XIN(ihit)  = VHIT(JSVXIL,J)*CMTOM
               XOUT(ihit) = VHIT(JSVXO,J)*CMTOM
               
C     resetEffs(ihit) is set to 1 when the track number of the current hit
C     is different from the track number of the previous hit. Otherwise
C     resetEffs(ihit) is set to 0. 
               if( J .gt. 1) then 
                  if( ITRM(J) .ne. ITRM(J-1) ) then
                     resetEffs(ihit) = 1
                  else
                     resetEffs(ihit) = 0
                  endif
               else
                  resetEffs(ihit) = 1
               endif
               

            endif
 75      continue
         NTOTSV = ntotsv+nhits
 85   continue
C     save the number of hits stored
      
      RETURN
      END



