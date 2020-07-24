C 
C  $Id: cleog_init.F,v 1.5 2000/03/28 21:44:10 jjo Exp $
C 
C  $Log: cleog_init.F,v $
C  Revision 1.5  2000/03/28 21:44:10  jjo
C  Really remove clbank.inc
C
C  Revision 1.4  2000/03/28 21:43:39  jjo
C  Remove clbank.inc common block
C
C  Revision 1.3  2000/01/26 23:40:09  lkg
C  #ifdef out QQ-related code.  Geant will only communicate through MCDecayTree (via the G3DecayTree interface), not with QQ directly
C
C  Revision 1.2  1999/05/26 18:40:08  jjo
C  Remove Zfiles related calls and QQ with cleog
C
C  Revision 1.1  1999/05/03 20:21:24  jjo
C  Reorganize code to make running Cleog under Suez more robust
C
C 
      SUBROUTINE CLEOG_INIT
C 
C  begin_doc
C 
C   Documentation for subroutine cleog_init
C 
C   Purpose: Initialize Cleog code for running Cleog under Suez.  
C   -------- Makes the Cleo specific calls that were in Cleog3/cbase/uginit.F 
C            that do not depend on begin run.  Not Geometry calls are made
C            as the geometry is created by MCResponseProd suez producer.
C
C   Input Parameters:  None
C   ----------------
C 
C   Output Parameters: None
C   -----------------
C 
C   Other routines:
C   ---------------
C 
C   Called By: user_geant_init.F
C   ----------
C
C   Notes:
C   ------
C 
C   Author:   John J O'Neill      Created:  Wed Apr 28 18:14:38 EDT 1999
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
#include "Cleog3/cg3cdes/cgname.inc"
#include "Cleog3/cg3cdes/cgbfld.inc"

#include "geant321/gckine.inc"
C  end_inc
 
C  begin_var
C   input/output variables:
C   -----------------------
 
C 
C   Local User defined variables:
C   -----------------------------
      LOGICAL  LQJEXI
      EXTERNAL LQJEXI
 

C   Local pre-defined variables:
C   ---------------------------
      LOGICAL LFIRST, RCSINI
      CHARACTER*(*) CHRCSS, CHRCSR, CHRCST, CHRCSD, CHRCSA
      PARAMETER(CHRCSS='$RCSfile: cleog_init.F,v $')
      PARAMETER(CHRCSR='$Revision: 1.5 $')
      PARAMETER(CHRCST='$State: Exp $')
      PARAMETER(CHRCSD='$Date: 2000/03/28 21:44:10 $')
      PARAMETER(CHRCSA='$Author: jjo $')
 
      CHARACTER*(*) CRNAME
      PARAMETER(    CRNAME = 'CLEOG_INIT' )
 
C  end_var
C 
C   Data statements:
C   ----------------
      SAVE RCSINI,LFIRST
      DATA RCSINI/.TRUE./, LFIRST/.TRUE./
 
C   executable code for routine cleog_init:
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
        CHMESS='Cleog Initialization'
        CALL MESLOG(CRNAME,1,MSINFO)
        LFIRST=.FALSE.
      ENDIF


C     Initialize CLEOG unit numbers
      CALL CGILUN


C      Need to replace cgvrsn for cleo3
CC     Print CLEOG version number
C      CALL CGVRSN


C zfiles  Need to investigate this
C zfilesC     Read INIT structure
C zfiles      CALL CGRDIN

#if defined(CLEO_RESTORE_QQ)
C     Automatically set IKINE value if .rp/.ctr file specified
      CALL CGQQSR
#else
      IKINE = 4
#endif

#if defined(CLEO_RESTORE_QQ)
C     Initialize GEANT particles if they are not read in,
C     AND the initialization for proper GEANT<->QQ mapping
      IF(.NOT.LQJEXI(CJPART)) CALL CGPART( IKINE )
#else
C     Have GEANT initialize its standard particles.  We may eventually need
C     to have an interface to MCINFO to allow addition of special purpose
C     particles like KSVEE (interact hadronically like KS, but decay only
C     to pi+pi-.
      CALL GPART
#endif

#if defined(CLEO_RESTORE_QQ)
C     Handle the remaining QQ initialization if .rp or .ctr 
C     files were specified
      CALL CGQQIN
#else
C     I don't think we need to do anything about the beam position (IBPSRC)
C     or crossing angle (IXASRC), but it would get done here!      
#endif

C     Set the CLEOG B field
      CALL CGBINI


C     User initialization routine
C     Need to move this so it's called after all geometry, etc. initialized
      CHMESS='NEED TO MOVE USBJOB after geometry initialized, etc'
      CALL MESLOG(CRNAME,1,MSWARN)
      CALL USBJOB

      
      RETURN
      END



