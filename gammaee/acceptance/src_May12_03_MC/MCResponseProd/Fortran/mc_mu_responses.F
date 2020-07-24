*
* $Id: mc_mu_responses.F,v 1.10 2002/09/27 20:28:03 bkh Exp $
*
* $Log: mc_mu_responses.F,v $
* Revision 1.10  2002/09/27 20:28:03  bkh
* Add ZD
*
* Revision 1.9  2002/08/07 21:18:41  bkh
* Make compatible with no more guser or Cleog3
*
* Revision 1.8  2001/10/17 06:06:33  swnam
* removed double declaration of muutyp in mc_mu_response.F
*
* Revision 1.7  2001/05/21 05:30:47  swnam
* some changes in message print mode
*
* Revision 1.6  2001/05/14 00:59:19  swnam
* skip the lower energy muon hits from the same multiplet
*
* Revision 1.5  2001/05/06 16:03:34  swnam
* message print type changed from msinfo to msdbug
*
* Revision 1.4  2001/05/01 22:07:05  swnam
* mc_mu_response_ has new arguments of muon hits, old codes were commented out.
*
* Revision 1.3  2001/04/16 05:16:47  savinov
* FortranInterfacer is used to hand the frame to muon c/c++ utilities called from Fortran
*
* Revision 1.2  2001/04/15 19:18:59  savinov
* Makefile and mc_mu_responses.F updated. Gettiing to mu MC, hooray
*
* Revision 1.1.1.1  1999/04/16 20:07:33  jjo
* Move MCxxResponseProxy from MCResponse library to this library.
* Make Geant calls from this library as fetching the hits (via GFHITS)
* currently couples this library to Geant.  Also, use bindable proxies. (jjo) 
*
* Revision 1.1  1999/02/25 21:31:08  bkh
* Update
*
*
#include "sys/CLEO_machine.h"

*
      SUBROUTINE MC_MU_RESPONSES( MaxResponse,
     &                            NResponse,
     &                            CellID,
     &                            ParticleID,
     &                            x01,
     &                            x02,
     &                            beta1,
     &                            beta2)

C    S. Nam : these are arguemnts in original version.
*     &                            CtrID,
*     &                            StripId,
*     &                            CtrAngle,
*     &                            StripAngle)

*
* begin_doc
*
*  Documentation for subroutine mc_mu_responses
*
*  Purpose:
*  --------
* This subroutine copies (by calling Geant routine "GFHITS") Geant muon hit information 
* into arrays to be returned to MCResponseProd 
*
*  Input Parameters:  (Name - Type - Meaning)
*  ----------------
*      integer MaxResponse ! Maximum # of hits restricted by calling c++ function 
*                          ! = 100, it is actually a dummy 
*
*  Output Parameters:  (Name - Type - Meaning)
*  -----------------
*      integer NResponse   ! # of hits returned 
*      integer     maxtothit ! size of arrays to store hit information
*      parameter (maxtothit=100) ! is 100
*      integer CellId(maxtothit) ! this is multiplet id
*      integer ParticleId(maxtothit) ! particle id 
*      real    x01(maxtothit) ! coordinate of track intersect with counter
*      real    x02(maxtothit) ! coordinate of track intersect with strip
*      real    beta1(maxtothit) ! angle of track intersecting counter 
*      real    beta2(maxtothit) ! angle of track intersecting strip

*
*  called by :
*  ----------- 
*  Class/MCMUResponseProxy.cc
*
*  calls 
*  -----
*  cqsdet : for muon detector names 
*  mugini : make sure muon geometry is initialized
*  gwork  : for geant
*  gfhits : get muon hits from Geant
*  muiqlo : find multiplet number from unit, layer information

*  Notes:
*  ------
*  S. Nam : the way to find MUOCQU and MULAY from NumBv(9) is new! 
*           it took long time to find out how to do it.
*
*  Author:   Brian K. Heltsley      Created:  Fri Feb 19 16:17:28 EST 1999
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
* #include "cl3seq/zfiles/usbank.inc"

#ifndef CLEO_GEANT315
#include "geant321/gcflag.inc"
#include "geant321/gcbank.inc"
#else
#include "geant/gcdes/gcflag.inc"
#include "geant/gcdes/gcbank.inc"
#endif

#include "MUGeom/MUGeant3SetNames.h"
#include "seq/mu/mugeom.inc"

* end_inc
*
* begin_var
*  input/output variables:
*  -----------------------
C     for input
      integer MaxResponse ! Maximum # of hits restricted by calling c++ function 
                          ! = 100, it is actually a dummy 
C     for output 
      integer NResponse   ! # of hits returned 
      integer     maxtothit ! size of arrays to store hit information
      parameter (maxtothit=100) ! is 100
      integer CellId(maxtothit) ! this is multiplet id
      integer ParticleId(maxtothit) ! particle id 
      real    x01(maxtothit) ! coordinate of track intersect with counter
      real    x02(maxtothit) ! coordinate of track intersect with strip
      real    beta1(maxtothit) ! angle of track intersecting counter 
      real    beta2(maxtothit) ! angle of track intersecting strip

C     S. Nam : original output variables. commenting out 
*      integer CtrId(maxtothit)
*      integer StripId(maxtothit)
*      real    CtrAngle(maxtothit)
*      real    StripAngle(maxtothit)

*  Local pre-defined variables:
*  ---------------------------
      LOGICAL RCSINI
      CHARACTER*(*) CHRCSS, CHRCSR, CHRCST, CHRCSD, CHRCSA
      PARAMETER(CHRCSS='$RCSfile: mc_mu_responses.F,v $')
      PARAMETER(CHRCSR='$Revision: 1.10 $')
      PARAMETER(CHRCST='$State: Exp $')
      PARAMETER(CHRCSD='$Date: 2002/09/27 20:28:03 $')
      PARAMETER(CHRCSA='$Author: bkh $')
*
      CHARACTER*(*) CRNAME
      PARAMETER(    CRNAME = 'MC_MU_RESPONSES' )

*  Local User defined variables:
*  -----------------------------
      INTEGER NWRITE
      integer i, itmp, ii
      real    energy(maxtothit)
 
C     detector name variable 
      character*4 cuset  !  set name, input for gfhits 
      character*4 cudet  !  detector name,  input for gfhits 
      character*4 cdets(20)  ! list of detector namescharacter
      integer     ndets   ! index variable for detector number
      integer     IHIT  ! hit number (loop index over hits 1..NHITS)

C     Muon detector index variables
*      integer muutyp      ! unit type (1=R, 2=I, 3=O, 4=E)
      integer imuutyp      ! index of unit type (1=E, 2=I, 3=O, 4=R)

C     variable for calling gfhits
      integer     nwdhit ! number of words required per hit
      integer     nwdvol ! number of words specifying volume number
      integer     maxhit ! maximum number of hits accepted
      parameter (maxhit=100, nwdvol=9, nwdhit=8)
*     parameter (maxhit=100, nwdvol=1, nwdhit=8)

      integer     itrm(maxhit)   ! track number for a given hit
      integer     numvs(nwdvol)  !  volume number
      integer     numbv(nwdvol,maxhit)  ! volume number for hits
      real        vhit(nwdhit,maxhit)   ! array for retured hits (8,100)  
      integer     nhits  ! number of hits returned by gfhits, if it is
                         ! greater than maxhit, nhits=maxhit+1 and
                         ! maxhit hits are returned

*     MU-detector indexes
      INTEGER MUMLOG,MUOCQU,MULAY,MUCSFL,MUMINL,MUUTYP,MUCSIL
*     MUMLOG - charge division multiplet logical address
*     MUOCQU - OCtant/QUadrant number (1-8)
*     MULAY  - layer number (1=A,2=B,3=C)
*     MUCSFL - counter/strip flag (1=counter,2=strip)
*     MUMINL - charge division multiplet number within a layer
*     MUUTYP - unit type (1=R,2=I,3=O,4=E)
*     MUCSIL - counter/strip number within a layer (1..MUMOFM(0,MUCSFL,MUUTYP))

*     Map to GEANT workspace
      EQUIVALENCE( NUMBV(1,1), WS(21) )
      EQUIVALENCE( VHIT (1,1), WS((       NWDVOL)*MAXHIT+21) )
      EQUIVALENCE( ITRM (1  ), WS((NWDVOL+NWDHIT)*MAXHIT+21) )
*
* end_var

*     Data statements:
      SAVE RCSINI, NWRITE, NDETS, CDETS
*
      DATA RCSINI/.TRUE./
      DATA NWRITE/0/

*
*     executable code for routine mc_mu_responses:
#if WRITE_RCS_INFO
      IF(RCSINI)THEN
        RCSINI = .FALSE.
        WRITE(6,*)'-------- CVSinfo --------'
        WRITE(6,*)CHRCSS
        WRITE(6,*)CHRCSR//' '//CHRCST
        WRITE(6,*)CHRCSD//' '//CHRCSA
      ENDIF
#endif

C --- for the first call ----------------------------------------------------
      IF (NWRITE .LT. 1) THEN
         NWRITE = NWRITE + 1
         CHMESS='first call'
         CALL MESLOG(CRNAME,1,MSDBUG)
         
C        prepare cdets array 
         cuset = 'MU'
         ndets = 20
         call cqsdet(cuset, cdets, ndets)
         if (ndets.gt.20) then
            chmess = 'ndets is bigger than 20 !!!, will be cut'
            call meslog(crname,1,msinfo)
            ndets = 20
         endif
         
C        print muon layer detector names 
         do i = 1, ndets
           write(chmess,9988) i, cuset, cdets(i)
 9988      format('detector set and det name: ', I3, 2X, a, a)
           call meslog(crname,1,msdbug)
        enddo
        
        call mugini
      ENDIF

C --- Get the hit workspace from GEANT (to store GEANT hits info) ----------
      CALL GWORK( (NWDVOL+NWDHIT+1)*MAXHIT )
      IF( IEOTRI.NE.0 ) THEN
         WRITE(CHMESS,10000)
10000    FORMAT(' Failed to get workspace from GEANT, skipped event' )
         CALL MESLOG( CRNAME, 1, MSERRO )
         GOTO 999
      ENDIF

C     print all hits informaiton : temporary, debug purpose only
*     CALL GPHITS('*','*')
*     CALL GPsets('*','*')


C --  extract muon hits information from JHITS using gfhits call ------------
C     in the loop over MUUTYP
C*    MUUTYP-unit type happans to number GEANT MU-II detectors
C*           i.e. 1=MORL 2=MOIL 3=MOOL 4=MEEL 

      NResponse = 0
      do 10 imuutyp = 1, ndets     ! this is simply a loop from 1 to 4
C        cdets(1) = MUEL
C        cdets(2) = MUIL
C        cdets(3) = MUOL
C        cdets(4) = MURL
         if (imuutyp.eq.1) muutyp=4
         if (imuutyp.eq.2) muutyp=2
         if (imuutyp.eq.3) muutyp=3
         if (imuutyp.eq.4) muutyp=1

         cudet = cdets(imuutyp)
         write(chmess,9989) cuset, cudet
 9989    format('detector set and det name for gfhits: ', a, a)
         call meslog(crname,1,msdbug)

*        get greant hits
         call gfhits(cuset, cudet, nwdvol, nwdhit, maxhit, 0, numvs,
     &               itrm, numbv, vhit, nhits)

         write(chmess,9990) nhits
 9990    format('total number of hits returned',I6)
         call meslog(crname,1,msdbug)

         if (nhits.lt.1) goto 10   ! no hit returned go to next unit type
         if (nhits.gt.maxhit) then 
            WRITE(CHMESS,10010) MAXHIT
10010       FORMAT(' Too many hits for local buffer, using', I6 )
            CALL MESLOG( CRNAME, 2, MSERRO )
            NHITS = MAXHIT
         ENDIF
         
C        loop over hits returned from Geant
         do 100 ihit = 1, nhits

*           find octant/quadrant number (1-8)
            MUOCQU = 0
            do itmp = 2, 8
               if (NUMBV(itmp,IHIT).ne.0) MUOCQU = itmp
            enddo
            if (MUOCQU.eq.0) MUOCQU = 1

*           find layer number (1-3)
            MULAY= NUMBV(9,IHIT)            

*           WRITE(CHMESS,9892) NUMBV(1,IHIT),NUMBV(2,IHIT),
*     &          numvs(1),numvs(2)
* 9892      FORMAT('swn: numbv information', 4(I5,3X))
*           CALL MESLOG( CRNAME, 2, MSdbug )
            
*           find out counter logical multiplet number
*           set counter/strip flag to counters
            MUCSFL=1
*           calculate counter number within a layer
*           from hit coordinate in Layer Reference System
            MUCSIL = IFIX( (VHIT(5,IHIT)+0.5*MUMOFM(0,MUCSFL,MUUTYP)*
     +      CSWDMU(MUCSFL)) /CSWDMU(MUCSFL) )+1
            MUCSIL = MIN0(MUMOFM(0,MUCSFL,MUUTYP),MAX0(1,MUCSIL))
*           multiplet number within a layer
*           ( must restrict to 2 multiplets to fix bug for endcaps )
            MUMINL = MIN0(2,(MUCSIL-1)/MUMOFM(1,MUCSFL,MUUTYP)+1)
*           convert to logical multiplet number
            CALL MUIQLO(MUOCQU,MUUTYP,MULAY,MUCSFL,MUMINL, MUMLOG)

*C           skip week hits
            if (NResponse.gt.0) then
            do ii = 1, NResponse
               if (mumlog.eq.Cellid(ii)) then
                  WRITE(CHMESS,9993) mumlog,vhit(4,ihit),energy(ii)
 9993             FORMAT('skip this week hit', I5, 2X, 2(G10.3,3X))
                  CALL MESLOG( CRNAME, 2, MSdbug )                  
                  goto 100
               endif
            enddo
            endif

*           store the hits
            NResponse = NResponse + 1            
            CellId(NResponse) = Mumlog
            ParticleId(NResponse) = itrm(ihit)
            x01(NResponse)    = vhit(5,ihit)
            x02(NResponse)    = vhit(6,ihit)
            beta1(NResponse)  = vhit(7,ihit)
            beta2(NResponse)  = vhit(8,ihit)
            energy(NResponse)  = vhit(4,ihit)

            WRITE(CHMESS,9992) NResponse,mumlog,MUOCQU,MUUTYP,MULAY,
     &                         MUCSFL,MUMINL,MUCSIL,vhit(5,ihit)
 9992       FORMAT('hit stored:', 8(I3,3X),G10.3)
            CALL MESLOG( CRNAME, 2, MSdbug )

*           WRITE(CHMESS,1902) NResponse,x01(NResponse) ,x02(NResponse),
*     &                        beta1(NResponse),beta2(NResponse)
* 1902      FORMAT('output from gfhits for =',I3,
*     +            ' X0=',G10.3,1X,G10.3,
*     +            ' BETA=',G10.3,1X,G10.3)
*           CALL MESLOG( CRNAME, 1, MSdbug )

*           WRITE(CHMESS,996) vhit(1,ihit),vhit(4,ihit),
*     &                     vhit(5,ihit),vhit(7,ihit)
*           CALL MESLOG( CRNAME, 2, MSdbug )
* 996       FORMAT('swn: mc_mu whatt saved',4(3X,G10.3))

*           S. Nam : original code
*            CtrId(NResponse)      = int(vhit(5,ihit))
*            StripId(NResponse)    = int(vhit(6,ihit))
*            CtrAngle(NResponse)   = vhit(7,ihit)
*            StripAngle(NResponse) = vhit(8,ihit)

 100     continue
 10      continue

 999  continue
      RETURN
      END







