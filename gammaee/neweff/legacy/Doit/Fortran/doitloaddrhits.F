*
* $Id: doitloaddrhits.F,v 1.6 2003/03/05 18:57:57 dpp Exp $
*
* $Log: doitloaddrhits.F,v $
* Revision 1.6  2003/03/05 18:57:57  dpp
*      -> fill new cdscrtcd variable
*      -> remove sfseq/sfextra.inc
*      -> changed all variable names in cdscrtcd to have common root
*      -> fill Evnt_OpnHit = 1
*      -> add new variables
*
* Revision 1.5  2000/03/03 15:19:30  lyon
* Get the TDC right and add quality and window information
*
* Revision 1.4  1999/12/01 22:15:00  lyon
* allow for gaps in identifier numbers
*
* Revision 1.3  1999/11/19 15:15:22  lyon
* Put tdc into EvntHit_rawTDC instead of EvntHit_corTIM -- oops
*
* Revision 1.2  1999/11/18 22:33:16  lyon
* tdc is a Integer, not a Real (duh)
*
* Revision 1.1  1999/05/20 13:03:58  lyon
* Needed to pass hit information through fortran functions
*
* Revision 1.1  1999/05/03 21:17:04  lyon
* Fortran/C++ communication
*
* Revision 1.1  1999/04/16 18:57:48  lyon
* for Fortran communication
*
*
      SUBROUTINE DOITLOADDRHITS(layer, wire, tdc, time,
     &     charge, phi, distance, xpos, ypos, cdla, qual,
     &     early, late, ntdc, o_idx)
*
* begin_doc
*
*  Documentation for subroutine doitloaddrhits
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
*  Author:   Adam Lyon      Created:  Thu Apr 15 14:08:16 EDT 1999
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
#include "cl3seq/cdgm3/cdgeompa.inc"
#include "cl3seq/cdgm3/cdgeomcd.inc"
#include "doit/duseq/cdscrtcd.inc"
* end_inc
*
* begin_var
*  input/output variables:
*  -----------------------
      INTEGER layer, wire, hitnum, cdla, fh, tdc, o_idx, qual, ntdc
      REAL time, charge, phi, distance, xpos, ypos, early, late
*
*  Local pre-defined variables:
*  ---------------------------
      LOGICAL RCSINI
      CHARACTER*(*) CHRCSS, CHRCSR, CHRCST, CHRCSD, CHRCSA
      PARAMETER(CHRCSS='$RCSfile: doitloaddrhits.F,v $')
      PARAMETER(CHRCSR='$Revision: 1.6 $')
      PARAMETER(CHRCST='$State: Exp $')
      PARAMETER(CHRCSD='$Date: 2003/03/05 18:57:57 $')
      PARAMETER(CHRCSA='$Author: dpp $')
*
      CHARACTER*(*) CRNAME
      PARAMETER(    CRNAME = 'DOITLOADDRHITS' )
*
*  Local User defined variables:
*  -----------------------------
      INTEGER i
*
*
* end_var
*
*  Data statements:
*  ----------------
*
      SAVE RCSINI
*
      DATA RCSINI/.TRUE./

*
*  executable code for routine doitloaddrhits:
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
      EvntHit_Num=EvntHit_Num + 1

      if (EvntHit_Num .gt. EvntHitMax ) then
        CHMESS='Doit -- Number of hits exceeded EvntHitMax!!'
        CALL MESLOG(CRNAME, 1, MSEMER)
        STOP
      endif
        
      i=EvntHit_Num

C*****Copy hit information into the common block

      EvntHit_CDlayr(i)   = layer
      EvntHit_laWire(i)   = wire
      EvntHit_rawTDC(i)   = tdc
      EvntHit_corTIM(i)   = time
      EvntHit_rawTIM(i)   = time
      EvntHit_Charge(i)   = charge
C     EvntHit_rawADC(i)   is not filled
      EvntHit_Drift(i)    = distance
      EvntHit_PhiWir(i)   = phi
C     EvntHit_corPhi(i)   is filled later and can be track dependent
      EvntHit_X(i)        = xpos
      EvntHit_Y(i)        = ypos
C     EvntHit_Z(i)        is filled later
      EvntHit_Qual(i)     = qual
      EvntHit_TimEarly(i) = early
      EvntHit_TimLate(i)  = late
      EvntHit_nMult(i)    = ntdc 


      EvntHit_NHitDev(i)  = i
      EvntHit_MapDet(CDLA)= EvntHit_Num

C*****new variables for multihit electronics
C     set for single hit

      EvntHit_OpnHit(i)   = 7
      EvntHit_PrimCls(i)  = 0
      EvntHit_NxtCls(i)   = 0
      EvntHit_1stMlt(i)   = EvntHit_Num
      EvntHit_NxtMlt(i)   = 0
      EvntHit_PrimMlt(i)  = 0
C     EvntHit_UsePrim(i)  is filled later


C*****return the current index      
      o_idx = i

C fill the SF link list        
      fh = EvntHit_1stLyr(layer)
C Is there already a first hit in the layer, move it out of the way
      if ( fh .ne. 0 ) then
        EvntHit_NxtLyr(i) = fh
      endif
      EvntHit_1stLyr(layer) = i
            
      RETURN
      END



