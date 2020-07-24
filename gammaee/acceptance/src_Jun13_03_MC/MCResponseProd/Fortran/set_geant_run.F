C 
C  $Id: set_geant_run.F,v 1.2 1999/05/26 18:41:59 jjo Exp $
C 
C  $Log: set_geant_run.F,v $
C  Revision 1.2  1999/05/26 18:41:59  jjo
C  Remove CGJRUN which calls zfiles
C
C  Revision 1.1  1999/05/03 20:21:25  jjo
C  Reorganize code to make running Cleog under Suez more robust
C
C 
      SUBROUTINE SET_GEANT_RUN( RUN_NUMBER )
C 
C  begin_doc
C 
C   Documentation for subroutine set_geant_run
C 
C   Purpose: Set the Geant run number.  
C   --------
C 
C   Input Parameters:  
C   ----------------
c   RUN_NUMBER  - integer - current run number which the Suez system sets
C 
C   Output Parameters: (Name - Meaning)
C   -----------------
C 
C   Other routines:
C   ---------------
C 
C   Called By: 
C   ----------
C
C   Notes: Need to call after setup_geant which initializes IDRUN
C   ------
C 
C   Author:   John J O'Neill      Created:  Wed Apr 28 17:35:36 EDT 1999
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

#include "geant321/gcflag.inc"
C  end_inc
 
C  begin_var
C   input/output variables:
C   -----------------------
      INTEGER RUN_NUMBER 
C 
C   Local User defined variables:
C   -----------------------------
 

C   Local pre-defined variables:
C   ---------------------------
      LOGICAL LFIRST, RCSINI
      CHARACTER*(*) CHRCSS, CHRCSR, CHRCST, CHRCSD, CHRCSA
      PARAMETER(CHRCSS='$RCSfile: set_geant_run.F,v $')
      PARAMETER(CHRCSR='$Revision: 1.2 $')
      PARAMETER(CHRCST='$State: Exp $')
      PARAMETER(CHRCSD='$Date: 1999/05/26 18:41:59 $')
      PARAMETER(CHRCSA='$Author: jjo $')
 
      CHARACTER*(*) CRNAME
      PARAMETER(    CRNAME = 'SET_GEANT_RUN' )
 
C  end_var
C 
C   Data statements:
C   ----------------
      SAVE RCSINI,LFIRST
      DATA RCSINI/.TRUE./, LFIRST/.TRUE./
 
C   executable code for routine set_geant_run:
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
        CHMESS='Setting Geant run number'
        CALL MESLOG(CRNAME,1,MSINFO)
        LFIRST=.FALSE.
      ENDIF


C     Note: Remove this warning when we remove FFREAD
C     remove FFREAD when QQ objects read in via Frame
      IDRUN = RUN_NUMBER
      WRITE(CHMESS, *)
     &     'Geant run # set via Suez (ignored FFREAD RUNG). ', IDRUN
      CALL MESLOG(CRNAME,1,MSINFO)
      
      RETURN
      END



