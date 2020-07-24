C 
C  $Id: setup_kuip.F,v 1.4 2002/08/07 21:18:42 bkh Exp $
C 
C  $Log: setup_kuip.F,v $
C  Revision 1.4  2002/08/07 21:18:42  bkh
C  Make compatible with no more guser or Cleog3
C
C  Revision 1.3  1999/10/14 21:06:00  jjo
C  Update warning message
C
C  Revision 1.2  1999/05/26 18:44:14  jjo
C  Remove call to ZCCDF which builds KUIP help for Zfiles
C
C  Revision 1.1  1999/05/03 20:21:27  jjo
C  Reorganize code to make running Cleog under Suez more robust
C
C 
      SUBROUTINE SETUP_KUIP
C 
C  begin_doc
C 
C   Documentation for subroutine setup_kuip
C 
C   Purpose: Initializes and calls KUIP used by cleog running under suez
C   -------- The KUIP prompt is only meant for "experts", "normal" users
C            will interacte with cleog via Suez run-time parameters and
C            never call KUIP.  
C
C   Input Parameters:  None
C   ----------------
C 
C   Output Parameters: None
C   -----------------
C 
C   Other routines: Calls KUIP & Cleog routines to define KUIP menus.
C   --------------- 
C 
C   Called By: Suez producer that calls Geant.  Currently MCResponseProd
C   ---------- calls Geant.
C
C   Notes: 
C   ------
C   This routine is only called when running cleog under suez if the
C   user sets the Suez run-time parameter UseKuip true (default false).
C   This routine will make the KUIP initialization calls and call
C   KUWHAG to get the KUIP prompt.
C
C   In the stand-alone version of Cleog
C   KUIP would be initialized by the GPAW subroutine.
C   Cleog KUIP calls were made in uginit (which GPAW called)
C   then KUWHAG was called to give the KUIP prompt.
C   The calls in this subroutine are made in the same order
C   as we did in the stand-alone version of CLEOG.
C
C   MODIFICATIONS OF DEFAULT GEANT/KUIP BEHAVIOR
C    1) The Geant trigger command is ignored - Suez now triggers Geant
C       A warning is printed in this routine telling users this and if
C       a user types 'TRIG' the routine dummy_cgtrig.F is called which
C       prints a warning saying that the trigger command has been
C       disabled.
C
C    2) If the users enters 'EXIT' at KUIP prompt the job will exit.
C       I don't know how to override the default behavior of 'EXIT'.
C
C   Author:   John J O'Neill      Created:  Mon Apr 26 12:36:30 EDT 1999
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
C   Cleo3 Message Reporter
#include "ToolBox/report.inc"

#include "geant321/gcflag.inc"
#include "geant321/gctime.inc"
#include "geant321/gcomis.inc"

C --- CLEO mod ---
#include "geant321/gtomis.inc"
C --- CLEO mod end ---
C  end_inc
 
C  begin_var
C   input/output variables:
C   -----------------------
 
C 
C   Local User defined variables:
C   -----------------------------
C CHMESS - Text of current message
      CHARACTER*132   CHMESS
 
      CHARACTER*80  PAWLOGF


C   Local pre-defined variables:
C   ---------------------------
      LOGICAL LFIRST, RCSINI
      CHARACTER*(*) CHRCSS, CHRCSR, CHRCST, CHRCSD, CHRCSA
      PARAMETER(CHRCSS='$RCSfile: setup_kuip.F,v $')
      PARAMETER(CHRCSR='$Revision: 1.4 $')
      PARAMETER(CHRCST='$State: Exp $')
      PARAMETER(CHRCSD='$Date: 2002/08/07 21:18:42 $')
      PARAMETER(CHRCSA='$Author: bkh $')
 
      CHARACTER*(*) CRNAME
      PARAMETER(    CRNAME = 'SETUP_KUIP' )
 
C  end_var
C 
C   Data statements:
C   ----------------
      SAVE RCSINI,LFIRST
      DATA RCSINI/.TRUE./, LFIRST/.TRUE./
 
C   executable code for routine setup_kuip:
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
        CHMESS='Setting up KUIP for use in Cleog under Suez'
        CALL REPORT(MS_DEBUG, CRNAME, CHMESS)
        LFIRST=.FALSE.
      ENDIF

C     defines user KUIP menu and commands - 
C     Stand-alone Cleog called this from gpaw.F
      CALL GINTRI

C     Stand-alone Cleog called this from gpaw.F
      CALL KUEXEC('ROOT /GEANT')

C     Stand-alone Cleog called this from gpaw.F
Ccleo CALL KUEXEC('SET/PROMPT ''GEANT >''')
      CALL KUEXEC('SET/PROMPT ''CLEOG >''')

C     Define KUIP Cleog utility commands 
C     Stand-alone Cleog called this from Cleog3_suez/cbase/uginit.F
      CALL CGKDEF

C     setup for kuip - call system logon macro
C     Stand-alone Cleog called this from the GPAW subroutine
      CALL PAWINT4(PAWLOGF)

C     Get the KUIP prompt 
C     Print warning about special features of KUIP under Cleog under Suez
C     Stand-alone Cleog called this from the GPAW subroutine
      CHMESS='--- KUIP when running Cleog under Suez ---'
      CALL REPORT(MS_WARNING,CRNAME, CHMESS)        
      CHMESS='1) Geant TRIG command disabled'
      CALL REPORT(MS_WARNING,CRNAME, CHMESS)        
      CHMESS='   Suez triggers Geant, currenlty via MCResponseProd'
      CALL REPORT(MS_WARNING,CRNAME, CHMESS)        

      CHMESS='2) Need to leave KUIP prompt with "QUIT"'
      CALL REPORT(MS_WARNING,CRNAME, CHMESS)        
      CHMESS='        DO NOT USE "EXIT"'
      CALL REPORT(MS_WARNING,CRNAME, CHMESS)        
      CALL KUWHAG
      
      RETURN
      END



