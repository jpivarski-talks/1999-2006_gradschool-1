C 
C  $Id: setup_geant.F,v 1.7 2002/08/07 21:18:42 bkh Exp $
C 
      SUBROUTINE SETUP_GEANT( UseFFRead, GeantBatchMode )
C 
C  begin_doc
C 
C   Documentation for subroutine setup_geant
C 
C   Purpose: Initialize Geant for Cleog3 when running under Suez
C   -------- The stand-alone version of cleog would initialize Geant via
C            gxint.F.
C 
C   Input Parameters: UseFFRead - true will call FFREAD
C   ----------------  GeantBatchMode - true set Geant BATCH variable true
C
C   Output Parameters: None
C   -----------------
C 
C   Other routines: Lots of Geant routines + user initialization
C   --------------- USER_GEANT_INIT (replaces uginit).
C 
C   Called By: Suez producer that makes Geant calls.  Currently,
C   ---------- this is the MCResponseProd producer, and the constructor 
C              calls this routine.
C   Notes:
C   ------
C 
C   Author:   John J O'Neill      Created:  Mon Oct 19 13:11:07 EDT 1998
C   -------
C 
C   Detailed description:
C   ---------------------
C   We are NOT using the Geant main routine, GXINT, but will setup
C   Geant ourselves.  This is necessary as we will be running cleog
C   as a Suez processor.  This routine makes the calls to setup up 
C   Geant
C
C   #1) Take code from guser_suez/gxint_321/gxint.F,the main Geant program,
C   which setups up Zebra common block size & calls guser_suez/gxint_321/gpaw.F
C
C   #2) Initialize Geant by making the calls that gpaw.F does.
C   
C
C
C   Documentation Notes:
C   The Geant manual sections relevant to a call are put in parenthesis.
C   The Geant 3.21 manaul can be found at 
C   http://wwwinfo.cern.ch/asdoc/geant_html3/geantall.html
C   The main Geant web page can be found at 
C   http://wwwinfo.cern.ch/asd/geant/index.html
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
c#include "geant321/gcxlun.inc"
c#include "geant321/gcunit.inc"

C  Common source for ZEBRA common block space
#include "ZebraCommonsModule/ZebraCommonsDeclarations.h"
C  end_inc
 
C  begin_var
C   input/output variables:
C   -----------------------
      logical UseFFRead, GeantBatchMode
C 
C   Local User defined variables:
C   -----------------------------

C     workstation type
      INTEGER IWTYP

      EXTERNAL      PAEXIT,UGLAST
      CHARACTER*80  BATCHF,PAWLOGF

C CHMESS - Text of current message
      CHARACTER*132   CHMESS

C   Local pre-defined variables:
C   ---------------------------
      LOGICAL LFIRST, RCSINI
      CHARACTER*(*) CHRCSS, CHRCSR, CHRCST, CHRCSD, CHRCSA
      PARAMETER(CHRCSS='$RCSfile: setup_geant.F,v $')
      PARAMETER(CHRCSR='$Revision: 1.7 $')
      PARAMETER(CHRCST='$State: Exp $')
      PARAMETER(CHRCSD='$Date: 2002/08/07 21:18:42 $')
      PARAMETER(CHRCSA='$Author: bkh $')
 
      CHARACTER*(*) CRNAME
      PARAMETER(    CRNAME = 'SETUP_GEANT' )
 
C  end_var
C 
C   Data statements:
C   ----------------
      SAVE RCSINI,LFIRST
      DATA RCSINI/.TRUE./, LFIRST/.TRUE./
 
C   executable code for routine setup_geant:
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
c CALL REPORT( ISEVERITY, CRNAME, MESSAGE ) 

      IF (LFIRST) THEN
        CHMESS='SETUP GEANT for Cleog running under Suez'
        CALL REPORT(MS_DEBUG,CRNAME, CHMESS)        
        LFIRST=.FALSE.
      ENDIF


C...Define size of USBANK
C     No idea why - 1000 ???
      IUSER(1) = NWORD_USER - 1000


C...Initialize Geant
C   Code taken from guser_suez/gxint_321/gpaw.F 
C     Do something with Geant timing system 
      CALL TIMEST(1.E6)

C     Tell users which Geant version we are using
      PRINT *,' *************************************************** '
      PRINT *,' *                                                 * '
      PRINT *,' *               G E A N T   3 . 2 1               * '
      PRINT *,' *                                                 * '
      PRINT *,' *                    C E R N                      * '
      PRINT *,' *                                                 * '
      PRINT *,' *               15/3/94  Geneva  CH               * '
      PRINT *,' *                                                 * '
      PRINT *,' *************************************************** '

C     PAWINT1 - 1st level PAW initialization'
Ccleo CLEO MOD - add BATCHMODE flag to turn on/off Geant BATCH variable
      CALL PAWINT1('GEANT',BATCHF,PAWLOGF,GeantBatchMode)
      CHMESS='Called PAWINT1'
      CALL REPORT(MS_DEBUG,CRNAME, CHMESS)        


C     setup Zebra for Geant
      CALL GZEBRA(NWORD_GEANT)
      CHMESS='Called GZEBRA'
      CALL REPORT(MS_DEBUG,CRNAME, CHMESS)        


C     Pawint2 - 2nd level PAW initialization, 
C     1) Paw type (paw, paw++)
C     2) Hbook & KUIP
C     3) The command structure (pawdef)
C     4) request workstation type of user
      CALL PAWINT2(-NWORD_PAW,' ',UGLAST,IWTYP)
      CHMESS='Called PAWINT2'
      CALL REPORT(MS_DEBUG,CRNAME, CHMESS)        


#if !defined(CERNLIB_IBM)
C     Seems that zbrdef is used for paw++ ???
      CALL ZBRDEF
      CHMESS='Called ZBRDEF'
      CALL REPORT(MS_DEBUG,CRNAME, CHMESS)        
#endif


C     3rd level paw initialization 
C     1) Higz & Hplot,  
C     2) Comis & Sigma
C     3) A number of different COMMON blocks.
      CALL PAWINT3
      CHMESS='Called PAWINT3'
      CALL REPORT(MS_DEBUG,CRNAME, CHMESS)        


C     Call routine named USER_GEANT_INIT instead of UGINIT
C     when running cleog under suez to avoid confusion with
C     file Cleog3_suez/cbase/uginit.F.
Ccleo      CALL UGINIT
      CALL USER_GEANT_INIT( UseFFRead )


C     Initialize the drawing package (DRAW).  
C     Have to initialise graphics package via IGINIT or HPLINT before this call
      CALL GDINIT


C     Initialize Geant timing system
      CALL TIMEL(TIMINT)


C     Initial GEANT run and event number
      IDRUN=0
      IEVENT=0
      

      CHMESS='Finished Geant setup for CLEOG running under Suez'
      CALL REPORT(MS_INFO,CRNAME, CHMESS)        

      RETURN
      END



C  $Log: setup_geant.F,v $
C  Revision 1.7  2002/08/07 21:18:42  bkh
C  Make compatible with no more guser or Cleog3
C
C  Revision 1.6  2000/05/22 16:02:41  jjo
C  Updates for FFREAD and Geant Batch mode:
C  1) Make FFREAD optional by default - turned on via Suez run
C  time parameter.  2) Set Geant "BATCH" flag to true by default,
C  if BATCH=false, Geant will prompt user for Higz window to open.
C
C  Revision 1.5  2000/03/26 21:28:22  lkg
C  get zebra commons declarations from ZebraCommonsModule rather than hardwiring
C
C  Revision 1.4  1999/11/18 19:50:08  jjo
C  improve report messages
C
C  Revision 1.3  1999/11/16 20:50:48  pg
C  Added Si simulation
C
C  Revision 1.2  1999/05/03 20:21:27  jjo
C  Reorganize code to make running Cleog under Suez more robust
C
C  Revision 1.1.1.1  1999/04/16 20:07:33  jjo
C  Move MCxxResponseProxy from MCResponse library to this library.
C  Make Geant calls from this library as fetching the hits (via GFHITS)
C  currently couples this library to Geant.  Also, use bindable proxies. (jjo)
C
