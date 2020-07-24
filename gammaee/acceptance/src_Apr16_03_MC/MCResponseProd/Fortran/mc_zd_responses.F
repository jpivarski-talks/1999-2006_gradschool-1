
      SUBROUTINE MC_ZD_RESPONSES( MaxResponse,
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
C  Documentation for subroutine mc_ZD_responses
C
C  Purpose:
C  --------
C
C  Input Parameters:  (Name - Type - Meaning)
C  ----------------
C  MaxResponse - Maximum number of ZD Responses to pass back to Cleo3 Frame
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
      PARAMETER(CHRCSS='$RCSfile: mc_zd_responses.F,v $')
      PARAMETER(CHRCSR='$Revision: 1.3 $')
      PARAMETER(CHRCST='$State: Exp $')
      PARAMETER(CHRCSD='$Date: 2003/03/19 22:58:33 $')
      PARAMETER(CHRCSA='$Author: bkh $')

      CHARACTER*(*) CRNAME
      PARAMETER(    CRNAME = 'MC_ZD_RESPONSES' )

C  Local User defined variables:
C  -----------------------------
C     chmess - Text of current message
      character*132 chmess


C-----------------------------------------------------------------
C Variables to get Geant hits via ZDMCUtil/Fortran/fill_geant_zdhits.F
C     kNWordVol - # of words specifying volume # used by ZD for layer number
      integer kNWordVol
      parameter  (kNWordVol = 1)
C     NGeantHits - number of Geant hits
C     GeantTracksArray - Geant track number associated with hit 
C     GeantLayersArray - contains ZD layer # associated with hit 
C     GeantHitsArray   - contains Geant hits

c      integer NGeantHits, GeantTracksArray(kMaxHit) 
c      integer GeantLayersArray(kMaxHit)
c      real GeantHitsArray( MXCDNH, kMaxHit)

c D.M. 08/11/00 :
c kMaxHit is used for layers but in 0.3% cases for BBbar events
c it is too short to store all hits. So it is replaced for 
c kMaxHitTotal, defined in geant_ZD_hit_def.inc
      integer NGeantHits, GeantTracksArray(kMaxHitTotal) 
      integer GeantLayersArray(kMaxHitTotal)
      real GeantHitsArray( MXCDNH, kMaxHitTotal)


C-----------------------------------------------------------------
C     Info related to hit
C     CellId        - ZD CellId number
C     LayerGeantHit - ZD Layer Number
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
C     IonDistSmeared - Ion distance smeared by ZDMCUtil/Fortran/zd_smear_drift.F
C     tmpDistSmear - temp. variable to hold Ion statistic smearing
C     PhiScaledDistSmear - Ion statistic smearing scaled by phi fitting weights 
      real IonDistSmeared
C     real tmpDistSmear, PhiScaledDistSmear 

C     PhiWire - phi of given ZD wire (currently not used so comment out)
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
      logical  hit_intime, ZD_hit_is_eff
      external hit_intime, ZD_hit_is_eff
      integer  CDHITS_LAYER_FROM_VOLUME
      external CDHITS_LAYER_FROM_VOLUME


C end_var

C  Data statements:
C  ----------------
      SAVE RCSINI, lfirst
      DATA RCSINI/.TRUE./, lfirst/.true./

      data DoSimpleSimulation/.false./
      data Simple_Eff/1.0/, Simple_Resolution/0.000150/

C  executable code for routine mc_ZD_responses:
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
       
          chmess = 'Creating ZD Responses'
          call report(MS_DEBUG, crname, chmess)
          write(chmess,*) '******************************'
          call report(MS_INFO, crname, chmess)        


        if (DoSimpleSimulation) then

          chmess = 'ZD Simulation in Tuning mode'
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

          chmess = 'ZD Simulation in normal mode:'
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
C     all 'DETS' in the DR3 SET - we have a seperate DET for each ZD layer.
      call fill_geant_ZDhits( NGeantHits, GeantTracksArray,
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

          go to 1234 ! bkh dummy jump
C         Copy ZD Geant hit info into local variables
c         and use CLEO units: cm->meters and seconds->picoseconds.
          call ZDhit_2_cleo_units( GeantHitsArray,
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


c         Check ZD Geant hits
          call zd_check_geant_hit( WireNumGeantHit,
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
          call zd_get_cellid( WireNumGeantHit,
     &                     LayerGeantHit,
     &                     CellID )

c         Is wire dead ?
          call zd_get_deadwire( NoConstantsUpdate,
     &                       CellID,
     &                       DeadWire )

c         Require wire to be alive
          if ( .NOT. DeadWire ) then

c           Convert energy loss to pulse height and make DOCA and wire corrections 
            call ZD_hit_eloss( ElossGeantHit,
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
              call ZD_Get_WireEff( NoConstantsUpdate, 
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
c              call zd_simple_smear_drift( Simple_Resolution,
c     &                                 IonDistGeantHit,
c     &                                 IonDistSmeared )

c             IonDistSmeared  = DriftDistGeantHit
              IonDistSmeared  = IonDistGeantHit

            else

c             Do simulation of resolution using constants Gaussian
              call zd_smear_drift( LayerGeantHit,
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

            call zdmc_drift2time( TOFGeantHit,
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
            call check_zd_anode_time( CellID,
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
            HitIsEff = ZD_hit_is_eff( CellEff )


C           What to do about hits later than the charge integration time ?
C           Should be dealt with in digitization phase

 1234       continue ! bkh dummer jump place
            HitIsEff = .true.  ! bkh dummy
            cellid = nresponse+1 ! bkh dummy

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

c#if defined(DEBUG_RESPONSE)
              call DUMP_ZD_RESPONSE( NResponse, CellID, DecayTreeIdHit,
     &             LR_ambiguity, DriftDistGeantHit, DriftTime,
     &             sinXangleGeantHit, cosZGeantHit, pathLengthGeantHit,
     &             XGeantHit, YGeantHit, ZGeantHit, 
     &             ChargeDep, ElossGeantHit, HitIsEff )
c#endif

            else
C             MaxResponse is passed in from MCZDResponseProxy.cc's faultHandler
              write(chmess,*) 'Too many ZD Responses = ', NResponse
              call report(MS_ERROR, crname, chmess)        
              chmess = 'Will ignore this hit'
              call report(MS_ERROR, crname, chmess)        
            endif

C         DeadWire
          endif

C       end of the loop over NGeantHits
        enddo

c#if defined(DEBUG_RESPONSE)
      write(chmess,*) 'Number of MC_ZD_Responses = ', NResponse
      call report(MS_INFO, crname, chmess)
c#endif
      return
      end
