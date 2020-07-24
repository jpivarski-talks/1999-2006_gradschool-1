C
C $Id: mc_dr_responses.F,v 1.24 2001/12/18 20:49:50 dubrovin Exp $
C
C $Log: mc_dr_responses.F,v $
C Revision 1.24  2001/12/18 20:49:50  dubrovin
C Add parameters ChargeDep at call get_wireeff.F and DecayTreeIdHit at smear_drift.F
C
C Revision 1.23  2001/10/30 18:33:52  dubrovin
C Commented call  drmc_iondist
C
C Revision 1.22  2001/05/23 13:57:31  dubrovin
C Fix typo in if condition for DriftDistGeantHit
C
C Revision 1.21  2001/05/13 00:08:35  dubrovin
C Add parameter DriftDistGeantHit in call smear_drift
C
C Revision 1.20  2001/04/10 16:06:01  dubrovin
C Add additional parameter cosZGeantHit at call dr_hit_eloss
C
C Revision 1.19  2001/01/26 17:32:31  dubrovin
C Multiple modification of code to get tuned version
C
C Revision 1.18  2000/12/20 17:42:04  dubrovin
C Switch off ion statistics correction while the constants will have tuned
C
C Revision 1.17  2000/10/13 21:44:08  dubrovin
C Add call drmc_iondist
C
C Revision 1.16  2000/09/07 22:54:04  dubrovin
C Add LayerGeantHit parameter at call of check_geant_hit
C
C Revision 1.15  2000/08/11 20:01:41  dubrovin
C Change arrays dimension kMaxHit(2500) -> kMaxHitTotal(5000)
C
C Revision 1.14  2000/08/09 00:53:44  lkg
C Remove debug statements that I inadvertently committed
C
C Revision 1.13  2000/07/14 20:07:28  lkg
C store decay tree id rather than geant id in response object
C
C Revision 1.12  2000/07/07 02:22:18  lkg
C Handle addition of x,y positions to MCDRResponse
C
C Revision 1.11  2000/03/28 21:43:15  jjo
C Improve comments
C
C Revision 1.10  2000/03/28 20:12:08  jjo
C Use 'SimpleSimulation' for now
C
C Revision 1.9  2000/02/15 00:52:48  jjo
C Add 'Simple' simulation - all cells have identical resolution (via single
C Gaussian) and efficiency set by a parameter.  By default, this is not used
C now.  Also improve variable names.
C
C Revision 1.8  1999/12/13 01:59:25  jjo
C 1) Use Cleog3_suez version of cddspa.inc ( Cleog3 version
C uses 13 elements/DR Geant hit, not 14).
C 2) Convert IonDistGeantHit & DriftDistGeantHit to cm
C 3) Remove particleSpecies from call to wire_eff
C 4) Add debug printouts
C
C Revision 1.7  1999/12/08 00:25:09  jjo
C Fix bug in wire # vs CellID.  Improve printout
C
C Revision 1.6  1999/11/22 22:21:33  jjo
C Remove excessive report calls
C
C Revision 1.5  1999/11/18 19:49:44  jjo
C clean up - remove unused variables, dont loop over sets, etc.
C
C Revision 1.4  1999/10/27 22:45:20  jjo
C Add HitIsEff flag to flag in/efficient hits, added
C deadwire logical, clean up code
C
C Revision 1.3  1999/10/20 22:44:18  jjo
C Add comments
C
C Revision 1.2  1999/10/19 16:29:23  jjo
C Add in DR simulation code which is based on
C the CleoII/II.5 DR simulation.
C
C Revision 1.1.1.1  1999/04/16 20:07:33  jjo
C Move MCxxResponseProxy from MCResponse library to this library.
C Make Geant calls from this library as fetching the hits (via GFHITS)
C currently couples this library to Geant.  Also, use bindable proxies. (jjo)
C
C Revision 1.1  1999/02/25 21:31:08  bkh
C Update
C
      SUBROUTINE MC_DR_RESPONSES( MaxResponse,
     &                            NResponse,
     &                            CellIDArray,
     &                            TrackArray,
     &                            LR_Ambiguity_Array,
     &                            DriftDistArray,
     &                            DriftTimeArray,
     &                            sinXangleArray,
     &                            cosZArray,
     &                            pathLengthArray,
     &                            XArray,
     &                            YArray,
     &                            ZArray,
     &                            ChargeDepArray,
     &                            ELossArray, 
     &                            HitIsEffArray )
C
C begin_doc
C
C  Documentation for subroutine mc_dr_responses
C
C  Purpose:
C  --------
C
C  Input Parameters:  (Name - Type - Meaning)
C  ----------------
C  MaxResponse - Maximum number of DR Responses to pass back to Cleo3 Frame
C
C  Output Parameters:  (Name - Type - Meaning)
C  -----------------
C  NResponse          - number of Responses returned to Cleo3 Frame
C  CellIDArray        - Wire Number of hit
C  TrackArray         - Decay Tree (not Geant) track number that caused hit
C  LR_Ambiguity_Array - Left/Right drift distance ambiguity (+/- 1) 
C  DriftDistArray     - Geant Drift distance 
C  DriftTimeArray     - Total drift time (drift+TOF) calc by TMCCL 
C  sinXangleArray     - sin of crossing angle wrt layer
C  cosZArray          - cos in z direction, aka dip angle
C  pathLengthArray    - path length in cell
C  XArray             - X position of hit
C  YArray             - Y position of hit
C  ZArray             - Z position of hit
C  ChargeDepArray     - charge deposited in cell in "Happy Units" 
C  ELossArray         - Geant energy loss in cell
C  HitIsEffArray      - logical array to say if this hit is (is not) efficient
C
C  Other routines:
C  ---------------
C
C  Notes:
C  ------
C  We only use Cleo units in this routine.  We convert from 
C  Geant units when we copy from the Geant hits array (GeantHitsArray).
C
C  This routine is based on the CleoII/II.5 CD simulation (cleog/crawm/cdrawm.F)
C  See DRMCUtil/Doc/cleo2_cdrawm_history.txt for cvs/cmz comments.
C  The CLEO-II/II.5 recompress/svx DR simulation package written by Craig Prescott,
C  Veronique Boisvert and others - see CBX 98-70 for details. 
C
C  Author:   Brian K. Heltsley      Created:  Fri Feb 19 16:17:22 EST 1999
C  -------
C
C  Major revisions:
C  ----------------
C     
C end_doc
C
#if defined(CLEO_TYPECHEK)
      IMPLICIT NONE
#endif

C begin_inc
C  Include files :
C  ---------------------
C   Cleo3 Message Reporter
#include "ToolBox/report.inc"

C   Geant includes
#include "geant321/gcbank.inc"
#include "geant321/gcflag.inc"

C   Cleog includes
#include "Cleog3_suez/cg3cdes/cddspa.inc"

C   cdgeom includes
#include "cl3seq/cdgm3/cdgeompa.inc"
#include "cl3seq/cdgm3/cdgeomcd.inc"

C   Offsets into Geant hit bank
#include "DRMCUtil/Fortran/geant_dr_hit_def.inc"

C end_inc

C begin_var
C  input/output variables:
C  -----------------------
      integer MaxResponse, NResponse
      integer CellIDArray(*), TrackArray(*), LR_Ambiguity_Array(*)
      real DriftDistArray(*), DriftTimeArray(*)
      real sinXangleArray(*), cosZArray(*)
      real pathLengthArray(*), ZArray(*),ChargeDepArray(*),ELossArray(*)
      real XArray(*), YArray(*)
      logical HitIsEffArray(*)


C  Local pre-defined variables:
C  ---------------------------
      LOGICAL RCSINI
      CHARACTER*(*) CHRCSS, CHRCSR, CHRCST, CHRCSD, CHRCSA
      PARAMETER(CHRCSS='$RCSfile: mc_dr_responses.F,v $')
      PARAMETER(CHRCSR='$Revision: 1.24 $')
      PARAMETER(CHRCST='$State: Exp $')
      PARAMETER(CHRCSD='$Date: 2001/12/18 20:49:50 $')
      PARAMETER(CHRCSA='$Author: dubrovin $')

      CHARACTER*(*) CRNAME
      PARAMETER(    CRNAME = 'MC_DR_RESPONSES' )

C  Local User defined variables:
C  -----------------------------
C     chmess - Text of current message
      character*132 chmess


C-----------------------------------------------------------------
C Variables to get Geant hits via DRMCUtil/Fortran/fill_geant_drhits.F
C     kNWordVol - # of words specifying volume # used by DR for layer number
      integer kNWordVol
      parameter  (kNWordVol = 1)
C     NGeantHits - number of Geant hits
C     GeantTracksArray - Geant track number associated with hit 
C     GeantLayersArray - contains DR layer # associated with hit 
C     GeantHitsArray   - contains Geant hits

c      integer NGeantHits, GeantTracksArray(kMaxHit) 
c      integer GeantLayersArray(kMaxHit)
c      real GeantHitsArray( MXCDNH, kMaxHit)

c D.M. 08/11/00 :
c kMaxHit is used for layers but in 0.3% cases for BBbar events
c it is too short to store all hits. So it is replaced for 
c kMaxHitTotal, defined in geant_dr_hit_def.inc
      integer NGeantHits, GeantTracksArray(kMaxHitTotal) 
      integer GeantLayersArray(kMaxHitTotal)
      real GeantHitsArray( MXCDNH, kMaxHitTotal)


C-----------------------------------------------------------------
C     Info related to hit
C     CellId        - DR CellId number
C     LayerGeantHit - DR Layer Number
C     iGeantHit     - loop index for Geant hits
      integer CellId, LayerGeantHit, iGeantHit


C-----------------------------------------------------------------
C local variables to hold geant hit
C     ZGeantHit          - Z position of geant hit 
C     cosZGeantHit       - cos in z direction of geant hit, aka dip angle
C     pathLengthGeantHit - pathLength of geant hit 
C     ElossGeantHit      - Energy loss for geant hit 
C     TOFGeantHit        - TOF for geant hit 
C     DriftDistGeantHit  - drift distance of geant hit 
C     sinXangleGeantHit  - sin of crossing angle wrt layer of geant hit 
C     IonDistGeantHit    - distance based on ion statistics of geant hit 
      real XGeantHit, YGeantHit
      real ZGeantHit, cosZGeantHit, pathLengthGeantHit, ElossGeantHit
      real TOFGeantHit, DriftDistGeantHit, sinXangleGeantHit
      real IonDistGeantHit
C     WireNumGeantHit    - wire # that has geant hit
C     TrackGeantHit      - geant track number that generated geant hit 
C     DecayTreeIdHit     - decay tree particle identifier for TrackGeantHit
      integer WireNumGeantHit, TrackGeantHit, DecayTreeIdHit


C-----------------------------------------------------------------
C misc
      logical lfirst

C-----------------------------------------------------------------
C Variables used to convert Geant hit to be used in this routine
C     Cotangent - Cotangent of ACOS(CZ)
      real Cotangent

C     ChargeDep - charge deposited in cell in "Happy Units"
      real ChargeDep


C-----------------------------------------------------------------
C Variables used for hit efficency 
C     CellEff - efficiency of Cell for hit to fire
      real CellEff


C-----------------------------------------------------------------
C Ion statistics variables
C     IonDistSmeared - Ion distance smeared by DRMCUtil/Fortran/smear_drift.F
C     tmpDistSmear - temp. variable to hold Ion statistic smearing
C     PhiScaledDistSmear - Ion statistic smearing scaled by phi fitting weights 
      real IonDistSmeared
C     real tmpDistSmear, PhiScaledDistSmear 

C     PhiWire - phi of given DR wire (currently not used so comment out)
C     real PhiWire

C     LR_ambiguity -  Left/Right ambiguity of drift distance (+/- 1)
      integer LR_ambiguity

C     DriftTime - uncorrected time from drift distance & TOF to layer
      real DriftTime


C-----------------------------------------------------------------
C Hit makes charge integeration time cutoff variables
C     TOF_Estimate - estimated TOF of Geant hit
C     kCLight - "speed" of light: In TMCCL and KTOFPS, CLIGHT "=" 3.E-4
      real TOF_Estimate, kCLight
      parameter ( kCLight = 3.0E-4 )

C     InTime - .true. if hit is in time for charge integeration
      logical InTime

C     HitIsEff - true if this hit is efficient
      logical HitIsEff


C-----------------------------------------------------------------
C     For DeadWire
C     NoConstantsUpdate - tell constants access subroutines to update constants
      logical NoConstantsUpdate
      parameter ( NoConstantsUpdate = .false. )
      logical DeadWire


C-----------------------------------------------------------------
C...Variables used for a simple simulation 
C   with all wires have the same efficiency and resolution
C     DoSimpleSimulation - true - do the 'simple' simulation
C     Should do this via suez run time parameter
      logical DoSimpleSimulation

      real Simple_Eff, Simple_Resolution
*      parameter ( DoSimpleSimulation = .false.,
*     &            Simple_Eff = 1.0,
**    &            Simple_Resolution = 0.000150 )
*     &            Simple_Resolution = 0.000000 )


C-----------------------------------------------------------------
C Externals
      logical  hit_intime, dr_hit_is_eff
      external hit_intime, dr_hit_is_eff
      integer  CDHITS_LAYER_FROM_VOLUME
      external CDHITS_LAYER_FROM_VOLUME


C end_var

C  Data statements:
C  ----------------
      SAVE RCSINI, lfirst
      DATA RCSINI/.TRUE./, lfirst/.true./

      data DoSimpleSimulation/.false./
      data Simple_Eff/1.0/, Simple_Resolution/0.000150/

C  executable code for routine mc_dr_responses:
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

      if (lfirst) then

          lfirst=.false.
       
          chmess = 'Creating DR Responses'
          call report(MS_DEBUG, crname, chmess)
          write(chmess,*) '******************************'
          call report(MS_INFO, crname, chmess)        


        if (DoSimpleSimulation) then

          chmess = 'DR Simulation in Tuning mode'
          call report(MS_INFO, crname, chmess)
          chmess = 'Tuning constants from file/db'
          call report(MS_INFO, crname, chmess)
          chmess = 'ON : Dead wires, Wire eff., Ion Stat.'
          call report(MS_INFO, crname, chmess)
          chmess = 'OFF: Gaussian smearing'
          call report(MS_INFO, crname, chmess)

c          write(chmess,*) 'Eff=', Simple_Eff,
c     &                   ' Resolution',Simple_Resolution
c          call report(MS_INFO, crname, chmess)

        else

          chmess = 'DR Simulation in normal mode:'
          call report(MS_INFO, crname, chmess)
          chmess = 'Tuning constants from file/db'
          call report(MS_INFO, crname, chmess)
          chmess = 'ON : Dead wires, Wire eff., Ion Stat., Gaus.smear.'
          call report(MS_INFO, crname, chmess)
          chmess = 'ON : Amplitude correction'
          call report(MS_INFO, crname, chmess)

        endif

          write(chmess,*) '******************************'
          call report(MS_INFO, crname, chmess)

*          call print_drift_function

      endif

C     Initialize number of responses returned to Cleo3 frame
      NResponse = 0


C     Get Geant hits in this Geant 'set'.  This fills the Geant hits for
C     all 'DETS' in the DR3 SET - we have a seperate DET for each DR layer.
      call fill_geant_drhits( NGeantHits, GeantTracksArray,
     &                        GeantLayersArray, GeantHitsArray )


C       Loop over number of Geant hits
        do iGeantHit = 1, NGeantHits

C         ---------------------------------------------
C         Get Geant Hits & Convert to Cleo units (m,ps)
C         ---------------------------------------------
          LayerGeantHit = GeantLayersArray(iGeantHit)
          TrackGeantHit = GeantTracksArray(iGeantHit)
C         Look up the decay tree track number for this Geant track number
          call gdt_geant_to_dktree_partid( TrackGeantHit, 
     $                                     DecayTreeIdHit )


C         Copy DR Geant hit info into local variables
c         and use CLEO units: cm->meters and seconds->picoseconds.
          call drhit_2_cleo_units( GeantHitsArray,
     &                             iGeantHit,
     &                             WireNumGeantHit,
     &                             XGeantHit,
     &                             YGeantHit,
     &                             ZGeantHit,
     &                             cosZGeantHit,
     &                             pathLengthGeantHit, 
     &                             ElossGeantHit,
     &                             TOFGeantHit,
     &                             DriftDistGeantHit,
     &                             sinXangleGeantHit,
     &                             IonDistGeantHit,
     &                             LR_ambiguity,
     &                             Cotangent )


c         Check DR Geant hits
          call check_geant_hit( WireNumGeantHit,
     &                          LayerGeantHit,
     &                          XGeantHit,
     &                          YGeantHit,
     &                          ZGeantHit,
     &                          cosZGeantHit,
     &                          pathLengthGeantHit,
     &                          ElossGeantHit,
     &                          TOFGeantHit,
     &                          DriftDistGeantHit,
     &                          sinXangleGeantHit,
     &                          IonDistGeantHit,
     &                          TrackGeantHit )

c         ---------------
c         Smear Geant hit
c         ---------------
c         Find out what cell we are in
          call get_cellid( WireNumGeantHit,
     &                     LayerGeantHit,
     &                     CellID )

c         Is wire dead ?
          call get_deadwire( NoConstantsUpdate,
     &                       CellID,
     &                       DeadWire )

c         Require wire to be alive
          if ( .NOT. DeadWire ) then

c           Convert energy loss to pulse height and make DOCA and wire corrections 
            call dr_hit_eloss( ElossGeantHit,
     &                         CellID,
     &                         LayerGeantHit,
     &                         DriftDistGeantHit,
     &                         cosZGeantHit,
     &                         ChargeDep )


c             Get Cell Efficiency - Was cleog/crawm/cdreff.F in cleo2
c             Do Simple simulation of eff
c             CellEff = Simple_Eff


c             Do 'full' simulation of eff. using constants
c             Electrons have additional correction so pass TrackGeantHit
c              call wire_eff( TrackGeantHit,
c     &                       CellID,
c     &                       LayerGeantHit,
c     &                       DriftDistGeantHit,
c     &                       cosZGeantHit,
c     &                       sinXangleGeantHit,
c     &                       CellEff )


c             Get Wire Efficiency only
              call Get_WireEff( NoConstantsUpdate, 
     &                          CellID, 
     &                          ChargeDep, 
     &                          CellEff )


c             Simulate an effect of ion statistics contribution to the drift distance
c              call drmc_iondist( LayerGeantHit,
c     &                           cosZGeantHit,
c     &                           sinXangleGeantHit,
c     &                           pathLengthGeantHit,
c     &                           ElossGeantHit,
c     &                           DriftDistGeantHit,
c     &                           IonDistGeantHit )

c 2001/10/18 D.M. switch off ion dist. correction. It is accounted in the drift function.
            IonDistGeantHit = DriftDistGeantHit  

            if ( DoSimpleSimulation ) then

c              Do Simple simulation of resolution
c              call simple_smear_drift( Simple_Resolution,
c     &                                 IonDistGeantHit,
c     &                                 IonDistSmeared )

c             IonDistSmeared  = DriftDistGeantHit
              IonDistSmeared  = IonDistGeantHit

            else

c             Do simulation of resolution using constants Gaussian
              call smear_drift( LayerGeantHit,
     &                          DriftDistGeantHit,
     &                          IonDistGeantHit,
     &                          cosZGeantHit,
     &                          ChargeDep,
     &                          DecayTreeIdHit,
     &                          IonDistSmeared )

            endif

c Stupid check and truncation to prevent FPE.
            if ( IonDistSmeared .le.-0.02 ) IonDistSmeared=-0.02
            if ( IonDistSmeared .ge. 0.02 ) IonDistSmeared= 0.02
            if ( DriftDistGeantHit .le.-0.02 ) DriftDistGeantHit=-0.02
            if ( DriftDistGeantHit .ge. 0.02 ) DriftDistGeantHit= 0.02


C           Scale smearing as a function of phi - Due mainly to radiation damage.  
C           Will need to look at this in the future for DR3 but for now ignore.  
C           Was cleog/crawm/phisca.F in cleo2.
C            Calc Phi of wire
c            call phi_of_dr_wire(WireNumGeantHit, LayerGeantHit, PhiWire)
C            call scale_phi_fit_wt( LayerGeantHit,
C     &                             PhiWire,
C     &                             tmpDistSmear,
C     &                             PhiScaledDistSmear )

c            tmpDistSmear = IonDistSmeared - DriftDistGeantHit
c            PhiScaledDistSmear = tmpDistSmear
c            IonDistSmeared = DriftDistGeantHit + PhiScaledDistSmear


         
C           Invert the drift function: uses smeared ion distance
            LR_ambiguity    = IFIX(SIGN(1., DriftDistGeantHit))
C           This was cdoffcal/cdcal/tmccl.F in Cleo-II

            call drmc_drift2time( TOFGeantHit,
     &                            ABS(IonDistSmeared),
     &                            LayerGeantHit,
     &                            ZGeantHit,
     &                            LR_ambiguity,
     &                            sinXangleGeantHit,
     &                            Cotangent,
     &                            ChargeDep,
     &                            DriftTime )


************* Test
*            print *, TOFGeantHit, IonDistSmeared, LayerGeantHit,
*     >      ZGeantHit, LR_ambiguity, sinXangleGeantHit,
*     >      Cotangent,ChargeDep, DriftTime
************* Test


cc            Print *, '*+*+*+*+*+*+*+*++* drift dist, time',
cc     $           abs(IonDistSmeared), DriftTime
C           Check for valid time - was chktim.f in Cleo2
            call check_dr_anode_time( CellID,
     &                                DriftTime )


C           Check to see if hit is in time for charge integration.  Note: TMCCL returns
C           the drift time plus the difference between GEANT's TOF and Radius/KCLight.
C           Hence, the time we should pass to hit_intime.F is *not* TOFGeantHit, but the
C           estimate of the TOF. 
C           DRMCUtil/Fortran/hit_intime.F was cleog/crawm/phtime.F in Cleo2
            TOF_Estimate = RCD(LayerGeantHit) / kCLight
            InTime = hit_intime(CellId, DriftTime,TOF_Estimate)
            if ( .NOT. InTime ) ChargeDep = 0.

C           Determine if DR hit is efficient
            HitIsEff = dr_hit_is_eff( CellEff )


C           What to do about hits later than the charge integration time ?
C           Should be dealt with in digitization phase


C           Save hit
            if ( iGeantHit .lt. MaxResponse ) then
              NResponse                     = NResponse + 1
              CellIDArray(NResponse)        = CellID
              TrackArray(NResponse)         = DecayTreeIdHit
              LR_Ambiguity_Array(NResponse) = LR_ambiguity
              DriftDistArray(NResponse)     = DriftDistGeantHit
              DriftTimeArray(NResponse)     = DriftTime
              sinXangleArray(NResponse)     = sinXangleGeantHit
              cosZArray(NResponse)          = cosZGeantHit
              pathLengthArray(NResponse)    = pathLengthGeantHit
              XArray(NResponse)             = XGeantHit
              YArray(NResponse)             = YGeantHit
              ZArray(NResponse)             = ZGeantHit
              ChargeDepArray(NResponse)     = ChargeDep
              ELossArray(NResponse)         = ElossGeantHit
              HitIsEffArray(NResponse)      = HitIsEff

#if defined(DEBUG_RESPONSE)
              call DUMP_DR_RESPONSE( NResponse, CellID, DecayTreeIdHit,
     &             LR_ambiguity, DriftDistGeantHit, DriftTime,
     &             sinXangleGeantHit, cosZGeantHit, pathLengthGeantHit,
     &             XGeantHit, YGeantHit, ZGeantHit, 
     &             ChargeDep, ElossGeantHit, HitIsEff )
#endif

            else
C             MaxResponse is passed in from MCDRResponseProxy.cc's faultHandler
              write(chmess,*) 'Too many DR Responses = ', NResponse
              call report(MS_ERROR, crname, chmess)        
              chmess = 'Will ignore this hit'
              call report(MS_ERROR, crname, chmess)        
            endif

C         DeadWire
          endif

C       end of the loop over NGeantHits
        enddo

#if defined(DEBUG_RESPONSE)
      write(chmess,*) 'Number of MC_DR_Responses = ', NResponse
      call report(MS_DEBUG, crname, chmess)
#endif

      return
      end



