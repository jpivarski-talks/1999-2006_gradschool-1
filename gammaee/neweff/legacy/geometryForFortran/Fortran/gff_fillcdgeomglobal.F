
* $Id: gff_fillcdgeomglobal.F,v 1.3 2003/03/05 18:59:59 dpp Exp $
*
* $Log: gff_fillcdgeomglobal.F,v $
* Revision 1.3  2003/03/05 18:59:59  dpp
*      -> compatibility for ZD
*      -> more general code
*      -> remove redundant filling of equivalanced varaiables
*
* Revision 1.2  1999/05/28 02:38:14  lyon
* C++ -> Fortran handlers for the different geometry subsystems
*
* Revision 1.1.1.1  1999/05/04 17:44:13  lyon
* Imported geometryForFortran sources
*
* Revision 1.1  1999/05/03 21:12:53  lyon
* Files needed for fortran geometry communication
*
*
      SUBROUTINE GFF_FILLCDGEOMGLOBAL(nDRLayers)
*
* begin_doc
*
*  Documentation for subroutine gff_fillcdgeomglobal
*
*  MOST IMPORTANT PURPOSE: define the 
*      time dependent detector device configuration
*
*  Purpose: Fill global DR information in cdgeomglobal.inc 
*    (called by ADRSenseWireStore::fillFortranCDGEOMCD)
*
*   This function fills the following variables in cdgeomcd.inc:
*      IDFRCD, IDTOCD, NDVLCD, NLDVCD, IDVLCD, ILDVCD, NAXLCD, NLYRCD,
*      NQDVCD, MDEVCD, NCANCD, LCANCD, MCANCD, NCATCD, LCATCD, MCATCD,
*      LCANIZ, MCANIZ, LCANPT, MCANPT, LCANVD, MCANVD, LCANDR, MCANDR,
*      LCATDR, MCATDR, LCSVX1, MCSVX1, LCSVZ1, MCSVZ1
*
*
*  --------
*
*  Author:   Adam Lyon      Created:  Wed Apr 28 16:10:53 EDT 1999
*  -------
*
*  Major revisions:
*  ----------------
*  DPP 12-Feb-2003: ZD and return to passed device configuration dependence 
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
* end_inc
*
* begin_var
*  input/output variables:
*  -----------------------
      integer nDRLayers
*
*  Local pre-defined variables:
*  ---------------------------
      LOGICAL RCSINI
      CHARACTER*(*) CHRCSS, CHRCSR, CHRCST, CHRCSD, CHRCSA
      PARAMETER(CHRCSS='$RCSfile: gff_fillcdgeomglobal.F,v $')
      PARAMETER(CHRCSR='$Revision: 1.3 $')
      PARAMETER(CHRCST='$State: Exp $')
      PARAMETER(CHRCSD='$Date: 2003/03/05 18:59:59 $')
      PARAMETER(CHRCSA='$Author: dpp $')
*
      CHARACTER*(*) CRNAME
      PARAMETER(    CRNAME = 'GFF_FILLCDGEOMGLOBAL' )
*
*  Local User defined variables:
*  -----------------------------
*
      LOGICAL never_used_detectors
      PARAMETER (never_used_detectors=.false.)

      INTEGER ndev, i, lyr

Cdpp      PARAMETER (ndev       = 4)  ! <<<<< Be sure to update this!!

Cdpp  nDRLayers is passed as an arguement
C*****These should be removed at some point (number of layers)
Cdpp that means that these should also be passed as arguments (Guang Shun)
      INTEGER nSVRphiLayers, nSVRZLayers, nDRCathLayers, nZDLayers
      PARAMETER (nDRCathLayers = 1)      

c      PARAMETER (nSVRphiLayers = 0)
c      PARAMETER (nSVRZLayers   = 0)
      PARAMETER (nSVRphiLayers = 4)
      PARAMETER (nSVRZLayers   = 4)

      PARAMETER (nZDLayers = 0)      
c      PARAMETER (nZDLayers = 6)      
            
*
* end_var
*
*  Data statements:
*  ----------------
*
*  executable code for routine gff_fillcdgeomglobal:
*----6----------------------------------------------------------------72
      ndev=0

Cdpp define the representation of the possible devices 
Cdpp in the current configuration    (device ordered)
      CALL VZERO(IDTOCD, MXDVCD)
Cdpp and Create the device configuration table (CD ordered); inverse of IDTOCD
      CALL VZERO(IDFRCD, KDEVCD)
Cdpp and Specify the number of layers in each device (device ordered)
      CALL VZERO(NLDVCD, MXDVCD)
Cdpp and Specify the number of layers in each device (CD ordered)
      CALL VZERO(NDVLCD, KDEVCD)


Cdpp do we want to include the --ZD anodes-- in this configuration ?
      IF(nZDLayers.GE.1)THEN
        ndev=ndev+1
        IDTOCD(IZDA) = ndev 
        IDFRCD(IDTOCD(IZDA))=IZDA
        NLDVCD(IZDA)  = nZDLayers
        NDVLCD(IDTOCD(IZDA))  = nZDLayers
      ENDIF

Cdpp do we want to include the --DR3 anodes-- in this configuration ?
      IF(nDRLayers.GE.1)THEN
        ndev=ndev+1
        IDTOCD(IDRFT) = ndev
        IDFRCD(IDTOCD(IDRFT))= IDRFT
        NLDVCD(IDRFT) = nDRLayers
        NDVLCD(IDTOCD(IDRFT)) = nDRLayers  
      ENDIF

Cdpp do we want to include the --silicon rphi-- in this configuration ?
      IF(nSVRphiLayers.GE.1)THEN
        ndev=ndev+1
        IDTOCD(ISVX1) = ndev
        IDFRCD(IDTOCD(ISVX1))= ISVX1
        NLDVCD(ISVX1) = nSVRphiLayers
        NDVLCD(IDTOCD(ISVX1))  = nSVRphiLayers
      ENDIF

Cdpp do we want to include the --silicon sz-- in this configuration ?
      IF(nSVRZLayers.GE.1)THEN
        ndev=ndev+1
        IDTOCD(ISVZ1) = ndev
        IDFRCD(IDTOCD(ISVZ1))= ISVZ1
        NLDVCD(ISVZ1) = NSVRZLayers  
        NDVLCD(IDTOCD(ISVZ1))    = NSVRZLayers  
      ENDIF

Cdpp do we want to include the --DR3 cathodes-- in this configuration ?
      IF(nDRCathLayers.GE.1)THEN
        ndev=ndev+1
        IDTOCD(IDRCT) = ndev
        IDFRCD(IDTOCD(IDRCT))=IDRCT
        NLDVCD(IDRCT) = NDRCathLayers
        NDVLCD(IDTOCD(IDRCT))  = NDRCathLayers
      ENDIF

Cdpp we don't ever want to include this old junk in a CLEO3 configuration 
Cdpp but these lines are here for demonstration
Cdpp note: the number of layers is not given for these never_used_detectors 
      IF(never_used_detectors)THEN
        ndev=ndev+1
        IDTOCD(IIVDT) = ndev
        IDFRCD(IDTOCD(IIVDT))=IDRCT
      ENDIF
      IF(never_used_detectors)THEN
        ndev=ndev+1
        IDTOCD(IVDET) = ndev 
        IDFRCD(IDTOCD(IVDET))=IDRCT
      ENDIF
      IF(never_used_detectors)THEN
        ndev=ndev+1
        IDTOCD(IVDCT) = ndev 
        IDFRCD(IDTOCD(IVDCT))=IDRCT
      ENDIF
      IF(never_used_detectors)THEN
        ndev=ndev+1
        IDTOCD(IPROP) = ndev 
        IDFRCD(IDTOCD(IPROP))=IDRCT
      ENDIF
      IF(never_used_detectors)THEN
        ndev=ndev+1
        IDTOCD(IPTLA) = ndev 
        IDFRCD(IDTOCD(IPTLA))=IDRCT
      ENDIF
      IF(never_used_detectors)THEN
        ndev=ndev+1
        IDTOCD(IPTLC) = ndev 
        IDFRCD(IDTOCD(IPTLC))=IDRCT
      ENDIF


Cdpp it will be a very long time before the linear collider TPC is used in CLEO
      IF(never_used_detectors)THEN
        ndev=ndev+1
        IDTOCD(ITPC1) = ndev 
        IDFRCD(IDTOCD(ITPC1))=ITPC1
      ENDIF

Cdpp finally update the CDGEOMCD number of devices
      MDEVCD = ndev  ! Number of CD devices

C*****Set first and last layer numbers in each device (CD ordered)
Cdpp OK
      CALL VZERO(IDVLCD, MXDVCD*2)
      lyr = 1
      do i = 1, ndev
        IDVLCD(1, i) = lyr         ! Set first layer
        lyr = lyr + NDVLCD(i) - 1  ! Get last layer
        IDVLCD(2, i) = lyr         ! Set last layer
        lyr = lyr + 1              ! Get first layer next device
      enddo
      
C*****Total number of CD layers
Cdpp OK
      NLYRCD = lyr - 1

C*****Set first and last layer numbers in each device (device ordered)
Cdpp OK
      CALL VZERO(ILDVCD, MXDVCD*2)
      do i = 1, MXDVCD
        
C*****  Get the CD index for this device
        IF(IDTOCD(i).NE.0)THEN

C*****  Now get first and last layers
          ILDVCD(1,i) = IDVLCD(1,IDTOCD(i))
          ILDVCD(2,i) = IDVLCD(2,IDTOCD(i))
        ENDIF
      enddo
      
Cdpp this is WRONG, but this value is not used in CLEO3 or CLEOc
      NAXLCD = nDRLayers

C*****No charge division anymore
Cdpp OK
      NQDVCD = 0
      
C*****Set number of and first and last anode layer numbers
Cdpp OK
      NCANCD = nDRLayers + nZDLayers
      LCANCD=0
      MCANCD=0
      IF(IDTOCD(IDRFT).GE.0)THEN
        LCANCD = IDVLCD(1,IDTOCD(IDRFT))
        MCANCD = IDVLCD(2,IDTOCD(IDRFT))
      ENDIF
      IF(IDTOCD(IZDA).GE.0)THEN
        IF(
     1       (IDVLCD(1,IDTOCD(IZDA)).LT.IDVLCD(1,IDTOCD(IDRFT))).and.
     2       (IDVLCD(1,IDTOCD(IZDA)).NE.0))THEN
          LCANCD = IDVLCD(1,IDTOCD(IZDA))
        ENDIF
        IF(
     1       (IDVLCD(2,IDTOCD(IZDA)).GT.IDVLCD(2,IDTOCD(IDRFT))))THEN
          MCANCD = IDVLCD(2,IDTOCD(IZDA))
        ENDIF
      ENDIF

*----6----------------------------------------------------------------72

C*****Set number of and first and last cd cathodes
      NCATCD = nDRCathLayers
      IF(IDTOCD(IDRCT).GE.0)THEN
        LCATCD = IDVLCD(1,IDTOCD(IDRCT))
        MCATCD = IDVLCD(2,IDTOCD(IDRCT))
      ENDIF

*----6----------------------------------------------------------------72
      RETURN
      END



