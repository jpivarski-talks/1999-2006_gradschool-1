C
C $Id: mc_cathodes_responses.F,v 1.2 1999/10/20 22:45:08 jjo Exp $
C
C $Log: mc_cathodes_responses.F,v $
C Revision 1.2  1999/10/20 22:45:08  jjo
C Add dummy cathode response for testing
C
C Revision 1.1.1.1  1999/04/16 20:07:33  jjo
C Move MCxxResponseProxy from MCResponse library to this library.
C Make Geant calls from this library as fetching the hits (via GFHITS)
C currently couples this library to Geant.  Also, use bindable proxies. (jjo)
C
C Revision 1.1  1999/02/25 21:31:07  bkh
C Update
C
C
      SUBROUTINE MC_CATHODES_RESPONSES( MaxResponse,
     &                                  NResponse,
     &                                  CellIdArray,
     &                                  TrackArray,
     &                                  ZPositionArray,
     &                                  PhiArray,
     &                                  ChargeArray,
     &                                  AnodeCellId )
C
C begin_doc
C
C  Documentation for subroutine mc_cathodes_responses
C
C  Purpose:
C  --------
C
C  Input Parameters:  (Name - Type - Meaning)
C  ----------------
C  MaxResponse - Maximum number of DR Responses to pass back to Cleo3 Frame
C 
C
C  Output Parameters:  (Name - Type - Meaning)
C  -----------------
C  NResponse          - number of Responses returned to Cleo3 Frame
C  CellIdArray        - CellId of hit
C  TrackArray         - Geant track number 
C  ZPositionArray     - Z position of hit
C  PhiArray           - phi position of hit
C  ChargeArray        - charge of hit
C  AnodeCellId        - anode CellId that corresponds to this hit
C
C  Other routines:
C  ---------------
C
C  Notes:
C  ------
C
C  Author:   Brian K. Heltsley      Created:  Fri Feb 19 16:17:14 EST 1999
C  -------
C
C  Major revisions:
C  ----------------
C     
C
C end_doc
C
#if defined(CLEO_TYPECHEK)
      IMPLICIT NONE
#endif
C
C begin_inc
C  Include files :
C  ---------------------
#include "seq/clutil/mesrep.inc"
C end_inc
C
C begin_var
C  input/output variables:
C  -----------------------
      integer MaxResponse, NResponse
      integer CellIdArray(*), TrackArray(*), AnodeCellId(*)
      real ZPositionArray(*), PhiArray(*), ChargeArray(*)
C
C  Local pre-defined variables:
C  ---------------------------
      LOGICAL RCSINI
      CHARACTER*(*) CHRCSS, CHRCSR, CHRCST, CHRCSD, CHRCSA
      PARAMETER(CHRCSS='$RCSfile: mc_cathodes_responses.F,v $')
      PARAMETER(CHRCSR='$Revision: 1.2 $')
      PARAMETER(CHRCST='$State: Exp $')
      PARAMETER(CHRCSD='$Date: 1999/10/20 22:45:08 $')
      PARAMETER(CHRCSA='$Author: jjo $')
C
      CHARACTER*(*) CRNAME
      PARAMETER(    CRNAME = 'MC_CATHODES_RESPONSES' )
C
C  Local User defined variables:
C  -----------------------------
C
      INTEGER NWRITE
C
C end_var
C
C  Data statements:
C  ----------------
C
      SAVE RCSINI
      SAVE NWRITE
C
      DATA RCSINI/.TRUE./
      DATA NWRITE/0/
C
C  executable code for routine mc_cathodes_responses:
#if WRITE_RCS_INFO
      IF(RCSINI)THEN
        RCSINI = .FALSE.
        WRITE(6,*)'-------- CVSinfo --------'
        WRITE(6,*)CHRCSS
        WRITE(6,*)CHRCSR//' '//CHRCST
        WRITE(6,*)CHRCSD//' '//CHRCSA
      ENDIF
#endif
C----6----------------------------------------------------------------72
C
      IF (NWRITE .LT. 1) THEN
        NWRITE = NWRITE + 1
        CHMESS='Creating Cathode Responses'
        CALL MESLOG(CRNAME,1,MSINFO)
      ENDIF
      
C     Initialize number of responses returned to Cleo3 frame
      NResponse = 0


C     Create dummy response for testing interface w/ c++
      NResponse = 1
      CellIdArray(1) = 188
      TrackArray(1) = 1
      ZPositionArray(1) = 1.0
      PhiArray(1) = 3.14159
      ChargeArray(1) = 0.001
      AnodeCellId(1) = 1
      
      RETURN
      END



