C 
C  $Id: user_geant_init.F,v 1.9 2001/10/05 22:02:49 bkh Exp $
C 
C 
      SUBROUTINE USER_GEANT_INIT( UseFFRead )
C 
C  begin_doc
C 
C   Documentation for subroutine user_geant_init
C 
C   Purpose: Geant User initialization routine for running cleog under suez.
C   -------- The Geant manual recomends calling this routine uginit
C            but give it a different name to avoid confusion with 
C            uginit routine in Cleog3/cbase/uginit.F
C            This routine follows the example uginit routine in the Geant3.21 manual
C            The Geant 3.21 manaul can be found at 
C            http://wwwinfo.cern.ch/asdoc/geant_html3/geantall.html
C            The main Geant web page can be found at 
C            http://wwwinfo.cern.ch/asd/geant/index.html
C
C            This calls the Cleog initialization routine CLEOG_INIT
C
C   Input Parameters:  UseFFRead - true will call FFREAD
C   ----------------
C 
C   Output Parameters: None
C   -----------------
C 
C   Other routines: MESLOG GINIT GLUNDI GZINIT GDINIT CLEOG_INIT GHEINI GBHSTA
C   ---------------
C 
C   Called By: setup_geant 
C   ----------
C
C   Notes: 
C   ------ 
C   This routine is reorganized to follow the example in the Geant 3.21 manaul.
C   Comment with 'Ccleo' identifies Cleo modifications which are due to running
C   Cleog under Suez.  
C
C   The Geant 3.21 manual can be found at 
C   http://wwwinfo.cern.ch/asdoc/geant_html3/geantall.html
C
C   The main Geant web page can be found at 
C   http://wwwinfo.cern.ch/asd/geant/index.html
C
C   This routine only makes initialization calls.  
C   No calls that depend on run number.
C
C
C   Author:   John J O'Neill      Created:  Wed Apr 28 14:03:20 EDT 1999
C   -------
C 
C   Detailed description:
C   ---------------------
C 
C   Major revisions:
C   ----------------
C      
C 
C  end_doc
C 
      IMPLICIT NONE
 
C  begin_inc
C   Include files :
C   ---------------------
C   Cleo Message Reporter
#include "seq/clutil/mesrep.inc"

#include "Cleog3/cg3cdes/cgctrl.inc"
#include "Cleog3/cg3cdes/cgspec.inc"

#include "CcGeom/CcGeant3SetNames.h"
#include "SiGeom/SiGeant3SetNames.h"

C  end_inc
 
C  begin_var
C   input/output variables:
C   -----------------------
      logical UseFFRead
C 
C   Local User defined variables:
C   -----------------------------
 

C   Local pre-defined variables:
C   ---------------------------
      LOGICAL LFIRST, RCSINI
      CHARACTER*(*) CHRCSS, CHRCSR, CHRCST, CHRCSD, CHRCSA
      PARAMETER(CHRCSS='$RCSfile: user_geant_init.F,v $')
      PARAMETER(CHRCSR='$Revision: 1.9 $')
      PARAMETER(CHRCST='$State: Exp $')
      PARAMETER(CHRCSD='$Date: 2001/10/05 22:02:49 $')
      PARAMETER(CHRCSA='$Author: bkh $')
 
      CHARACTER*(*) CRNAME
      PARAMETER(    CRNAME = 'USER_GEANT_INIT' )
 
C  end_var
C 
C   Data statements:
C   ----------------
      SAVE RCSINI,LFIRST
      DATA RCSINI/.TRUE./, LFIRST/.TRUE./
 
C   executable code for routine user_geant_init:
#if WRITE_RCS_INFO
      IF(RCSINI)THEN
        RCSINI = .FALSE.
        WRITE(6,*)'-------- CVSinfo --------'
        WRITE(6,*)CHRCSS
        WRITE(6,*)CHRCSR//' '//CHRCST
        WRITE(6,*)CHRCSD//' '//CHRCSA
      ENDIF
#endif
C ----6----------------------------------------------------------------72
 
      IF (LFIRST) THEN
        CHMESS='Geant User initialization routine'
        CALL MESLOG(CRNAME,1,MSINFO)
        LFIRST=.FALSE.
      ENDIF


C.....Geant Initialization
C     Initialise the GEANT common blocks with default values (BASE-030, BASE-110)
      CALL GINIT


c commented out 10/5/2001 bkh  (we don't use lund within geant)
Ccleo Add call to GLUNDI
C     Initialize LUND - call before GFFGO as it defines the data record LUND. (KINE-200)
c      CALL GLUNDI


Ccleo Call cginff which calls GFFGO
C     Define read CLEOG/GEANT/GQQ FFREAD cards
C     See (BASE-040, BASE-110) for Geant FFREAD cards
      CALL CGINFF( UseFFRead )
      

C     Initialise the memory manager (ZEBRA), link areas and run header bank JRUNG (BASE-110)
C     GZINIT sets JRUNG bank but when running under cleog under suez, the run # hasn't been set yet
C     cgudbr.F will set JRUNG when we call it.
      CALL GZINIT


C     Initialize GEANT drawing package (DRAW)
C     Need to initialised the graphics package via IGINIT or HPLINT
      CALL GDINIT


Ccleo     gpart called in CGPART which is called from CLEOG_INIT
Ccleo     GPART - not called here 

Ccleo     Geometry is created by C++. 
Ccleo     Currently MCResponseProd::updateCleogBeginRun calls BuildGeantGeometry object
Ccleo     UGEOM 

Ccleo     Called after geometry definition in BuildGeantGeometry object
Ccleo     GPHYSI 

Ccleo     print Geant banks - called by BuildGeantGeometry object

Ccleo Cleog initializations that do not depend on run number
      CALL CLEOG_INIT

Ccleo Initialize GHEISHA if selected (PHYS 510)
      CALL GHEINI

Ccleo Initialize GEANT histograms
      IF(NHSTAC.GT.0) CALL GBHSTA

Ccleo Convert Set name to Hollerith 
Ccleo Need to add other detectors
      CALL UCTOH( 'SI3 ', LSETSC(ICGSSV), 4, 4 )
      CALL UCTOH( 'DR3 ', LSETSC(ICGSDR), 4, 4 )
      CALL UCTOH( 'CC  ', LSETSC(ICGSCB), 4, 4 )
      CALL UCTOH( 'MU  ', LSETSC(ICGSMO), 4, 4 )

      RETURN
      END


C  $Log: user_geant_init.F,v $
C  Revision 1.9  2001/10/05 22:02:49  bkh
C  Remove call to initialize lund
C
C  Revision 1.8  2001/04/16 05:16:47  savinov
C  FortranInterfacer is used to hand the frame to muon c/c++ utilities called from Fortran
C
C  Revision 1.7  2000/05/22 16:03:45  jjo
C  Update to make FFREAD optional
C
C  Revision 1.6  1999/12/06 21:13:04  jjo
C  Remove warning printout about rung FFREAD card
C  as it was moved to guser_suez/geant/gffgo
C
C  Revision 1.5  1999/11/09 16:13:03  jjo
C  Added DR3 to LSETSC
C
C  Revision 1.4  1999/10/14 21:05:11  jjo
C  Added SI3 geant set name
C
C  Revision 1.3  1999/05/26 18:46:57  jjo
C  Print message saying we need to add Geant SET names
C
C  Revision 1.2  1999/05/14 17:16:13  bkh
C  Changes to make CC Responses work
C
C  Revision 1.1  1999/05/03 20:21:28  jjo
C  Reorganize code to make running Cleog under Suez more robust
C
