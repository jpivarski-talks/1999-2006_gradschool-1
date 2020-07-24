*
* $Id: mc_cc_responses.F,v 1.7 2001/11/05 22:24:09 bkh Exp $
*
* $Log: mc_cc_responses.F,v $
* Revision 1.7  2001/11/05 22:24:09  bkh
* Sum energies for same cell and mc particle id
*
* Revision 1.6  2000/07/14 20:07:28  lkg
* store decay tree id rather than geant id in response object
*
* Revision 1.5  2000/03/24 23:14:47  bkh
* Get geant-cellid mapping in slightly different call
*
* Revision 1.4  1999/11/16 20:50:46  pg
* Added Si simulation
*
* Revision 1.3  1999/05/26 16:56:28  bkh
* Fix bug of adding to energy array; modify for new endcap crystal shapes
*
* Revision 1.2  1999/05/14 17:16:12  bkh
* Changes to make CC Responses work
*
* Revision 1.1.1.1  1999/04/16 20:07:33  jjo
* Move MCxxResponseProxy from MCResponse library to this library.
* Make Geant calls from this library as fetching the hits (via GFHITS)
* currently couples this library to Geant.  Also, use bindable proxies. (jjo)
*
* Revision 1.1  1999/02/25 21:31:07  bkh
* Update
*
*
      SUBROUTINE MC_CC_RESPONSES( MAXTCC, NTOTCC, CELHCC,
     *                            LTRKCC, ETRKCC )
*
* begin_doc
*
*  Documentation for subroutine mc_cc_responses
*
*  -------->>>> this is a rewrite of the CLEO2-version of ccggeh.F
*
*  Purpose:
*  --------
*       To fill input arrays with collated CC Geant hits for Response object
*
*  Input Parameters:
*  ----------------
*
*       MAXTCC : maximum number of CC hits or track-crystal combos accepted
*
*  Output Parameters:
*  -----------------
*
*       NTOTCC : number of GEANT track-crystal contributions
*
*       CELHCC : list of cellids of hits
*
*       LTRKCC : list of GEANT track id's contributing for each crystal hit
*
*       ETRKCC : list of energies of tracks contributing to each crystal hit
*
*  Other routines:
*  ---------------
*
*  Notes:
*  ------
C.
C. Detailed description
C.   This routine queries GEANT for the crystal hit information and
C.   puts the result in the output arrays in the arguments above.
C.   On the first event, it checks that all is ok to call GFHITS
C.   for each of endcap and crystal barrel. If all is ok for either
C.   then it calls GFHITS for that detector, and sums up the energy
C.   contributions for each crystal, catalogued by GEANT track number.
*
*  Author:   Brian K. Heltsley      Created:  Fri Feb 19 16:16:13 EST 1999
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

*#include "cleog/cgcdes/cgctrl.inc"

*#include "cleog/cgcdes/cgname.inc"

#include "CcGeom/CcGeant3SetNames.h"

* end_inc
*
* begin_var
*  input/output variables:
*  -----------------------

      INTEGER MAXTCC, NTOTCC, CELHCC( * ), LTRKCC( * )

      REAL    ETRKCC( * )
*
*  Local pre-defined variables:
*  ---------------------------
      LOGICAL RCSINI
      CHARACTER*(*) CHRCSS, CHRCSR, CHRCST, CHRCSD, CHRCSA
      PARAMETER(CHRCSS='$RCSfile: mc_cc_responses.F,v $')
      PARAMETER(CHRCSR='$Revision: 1.7 $')
      PARAMETER(CHRCST='$State: Exp $')
      PARAMETER(CHRCSD='$Date: 2001/11/05 22:24:09 $')
      PARAMETER(CHRCSA='$Author: bkh $')
*
      CHARACTER*(*) CRNAME
      PARAMETER(    CRNAME = 'MC_CC_RESPONSES' )
*
*  Local User defined variables:
*  -----------------------------
*

*
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
*       JENRCC : index in VHIT where the deposited energy is stored
*********************************************************************

      INTEGER    MAXHIT,        MWDVOL,     MWDHIT,     JENRCC
      PARAMETER( MAXHIT = 1000, MWDVOL = 2, MWDHIT = 6, jenrcc = 6 )

      INTEGER NUMBV( MWDVOL, MAXHIT ), ITRM( MAXHIT ), NUMVS( MWDVOL )
      REAL    VHIT(  MWDHIT, MAXHIT )

      integer jdet, shapeid, copynumber, phiew

      INTEGER     MDETS
      PARAMETER ( MDETS = 29 )
      CHARACTER*4 CUSET, CUDET( MDETS )

      INTEGER IHIT, JHIT, NHITS, IERR, IOERR, dgid(3)


      integer cellid, partid

      real energy

      LOGICAL CALLED

*
* end_var
*
*  Data statements:
*  ----------------
*
      SAVE RCSINI

      SAVE CALLED, NUMVS, CUSET, CUDET, IERR

* -------------------- DATA  initializations ---------------
      DATA RCSINI / .TRUE. /

      DATA NUMVS / MWDVOL*0 /

      DATA CALLED / .FALSE. /

      DATA CUSET / CRYSTAL_SETNAME /

*
*  executable code for routine mc_cc_responses:
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

* zero # of track-crystal contributions
      NTOTCC = 0

* First time around, check set definition, get set info...
      IF( .NOT. CALLED ) THEN

        CALLED = .TRUE.

* Check that set is defined
        CALL CGCSDP( MWDVOL, CUSET, MDETS, CUDET, IERR )

      ENDIF

      IF( IERR .NE. 0 ) THEN

        WRITE( CHMESS, 10010, IOSTAT = IOERR ) CUSET
10010   FORMAT(' Detector for set ', A, ' is not defined ')
        CALL MESLOG( CRNAME, 1, MSABOR )

      ELSE
        do jdet = 1, mdets

          read( cudet( jdet ), '(2x,i2)', err=999 ) shapeid

          if( jdet .ne. shapeid ) then
            write( chmess, 10015, iostat = ioerr ) jdet, shapeid
10015       format(' Crystal number=', i4,' does not match shape=',
     *               i4 )
            call meslog( crname, 1, MSERRO )
          endif

* Get the hits
          CALL GFHITS( CUSET, CUDET( jdet ),
     +                 MWDVOL, MWDHIT, MAXHIT, 0, NUMVS,
     +                 ITRM,   NUMBV,  VHIT,   NHITS )

          IF( NHITS .GT. MAXHIT ) THEN

            WRITE( CHMESS, 10020, IOSTAT = IOERR ) MAXHIT
10020       FORMAT(' Too many hits for local buffer, using', I6 )
            CALL MESLOG( CRNAME, 2, MSERRO )

            NHITS = MAXHIT

          ENDIF
*   Loop over hits, summing energy in each block, watch out for hits
*   from different tracks in the same block
          DO 400 IHIT = 1, NHITS

* assign cellid for this hit

            phiew = numbv( 1, ihit )
            copynumber = numbv( 2, ihit )

            dgid(1)=shapeid
            dgid(2)=copynumber
            dgid(3)=phiew
            call cc_dgid_to_cellid( dgid , cellid )

            CALL GDT_GEANT_TO_DKTREE_PARTID( itrm( ihit ), partid )
            energy = vhit( jenrcc, ihit )

* first try to find other occurrence of this cellid,partid in existing array

            do jhit = 1, ntotcc

              if( celhcc( jhit ) .eq. cellid .and.
     *            ltrkcc( jhit ) .eq. partid        ) then

                etrkcc( jhit ) = etrkcc( jhit ) + energy
                go to 400
              endif
            enddo

* if get here, did not find earlier, so make a new entry

* quit if not enough space in array
            IF( NTOTCC .GE. MAXTCC ) THEN

              WRITE( CHMESS, 10030, IOSTAT = IOERR ) MAXTCC
10030         FORMAT(' Overflowing input array, using', I9 )
              CALL MESLOG( CRNAME, 3, MSERRO )

            ELSE

              ntotcc = ntotcc + 1
              celhcc( ntotcc ) = cellid
              ltrkcc( ntotcc ) = partid
              etrkcc( ntotcc ) = energy

            ENDIF

  400     CONTINUE
        ENDDO
      ENDIF

C     normal return
      RETURN

C     Go here if error in read
  999 continue
      WRITE( CHMESS, 10099, IOSTAT = IOERR )  cudet( jdet )
10099 FORMAT(' Unrecognized crystal name:',a )
      CALL MESLOG( CRNAME, 3, MSERRO )

      RETURN
      END



