	DOUBLE PRECISION FUNCTION TAUKF(RM,GAM,WSPREAD,YINT,PHI,HC)
C>>>>Double-precision version<<<<<<<
C   Observed shape of resonance peak, starting with Breit-Wigner
C   F_KF(x,s) convoluted with unit-area Breit-Wigner, and with beam resolution
C    unit-area Gaussian
C   Use to fit observed line shape: sig(W_CESR)=A*TAUKF(W_CESR) (in MeV^-2)
C      yields A, from which Gam_ee^exp is calculated 
C   BW(w) = (GAM/2*pi)/[(w-M)^2+GAM^2/4] (unit integral over w)
C   Modified in Dec03 to accommodate broad resonances (GAM>>WSPREAD)
C   The Breit-Wigner formula is most valid when --
C     W-M<~M [otherwise one should use the relativistic form, multiplying
C       the W-M in the BW denominator by (W+M)/(2M)]
C     M is far from threshold W0 for the dominant decay [otherwise one should
C       insert a phase space factor (1-W0^2/W^2)/(1-W0^2/M^2)]
C     The resonance is isolated from other resonances
C   If GAM<1 keV, the Breit-Wigner is replaced with a delta function
C   Calls FUNCTION TFKF to get Kuraev-Fadin radiative tail function, F_KF(x,s)
C   BW*KF -> BWKF; G*BWKF -> TAUKF
C   Gaussian(w) = exp{-.5*[(w-M)^2/WSPREAD^2]}/(2*pi*WSPREAD) (unit int...)
C   Normalized per unit W, MeV^-1
C   Width GAM and interference parameters YINT,PHI are constants.
C    Changing them would trigger time-consuming reinitializations.
C   Allows variation of mass RM and spread WSPREAD within narrow ranges for
C    fitting without time consuming reinitialization of tables
C   All energies are in MeV
C   RM = central resonance mass (can be fitted)
C   GAM= resonance Breit-Wigner total width (constant, not to be varied in fit)
C   WSPREAD = r.m.s. c.m. beam energy spread, in MeV (can be fitted)
C   YINT = ratio of interference term to BW cross section at WR-RM = GAM/2
C        = (2/3)*alpha*R/(1-n*B_mumu), where n=2 for psis, 3 for Ys
C        = .012,.010, .018,.018,.018 for psi, psi', Y(1S, 2S, 3S)
C     (constant, not to be varied in fit)
C   For mumu or tautau, YINT = (2/3)*alpha/B_mumu
C         = .082,.68, .20,.37,.27 for psi, psi', Y(1S, 2S, 3S)
C   PHI = phase of interfering flat background ampl, in degrees (constant)
C       Resonant phase is assumed to run 0 .. 90 .. 180 with increasing W.
C       If interference is destructive for W<M, PHI=0.
C   WT = true c.m. e+e- collision energy for particular event
C   WR = rest energy of produced resonance for particular event
C   WA = WT*RM/WR
C   WC = centroid of CESR energy distribution
C   HC = WC - RM  (and so on for other H...)
C    This is the energy scan variable.
C
	IMPLICIT DOUBLE PRECISION A,B,C,D,E,F,G,H
     2   ,O,P,Q,R,S,T,U,V,W,X,Y,Z
	PARAMETER (MKBIN=3000)                ! # bins in WA-RM, was 1500
	PARAMETER (MTBIN=3000)                ! # bins of HT=WT-RM, was 2000
	PARAMETER (ROOT2=1.414213d0)
	PARAMETER (PI=3.1415926d0)
	PARAMETER (RTWOPI=2.506628d0)           ! sqrt(2pi)
	PARAMETER (RTWOBPI=0.7978845d0)         ! sqrt(2/pi)
	PARAMETER (PMAX=8.d0)                   ! max power in Gaussian
	PARAMETER (TINY=1.d-3)                ! minimum GAM used
	PARAMETER (VTINY=1.d-8)               ! minimum interference
	COMMON/TCKF/HT(0:MTBIN),BWKF(-MTBIN:MTBIN) ! BW-F_KF convolution
	LOGICAL LSKIP                         ! if true, skip spread
	DIMENSION TFKFT(MKBIN)	              ! F_KF(x,s) (Kuraev-Fadin eq.28)
	DIMENSION HA(MKBIN)                   ! WA-RM of centroid WA bin
	DIMENSION DWA(MKBIN)                  ! bin width in WA-RM
	DIMENSION DWT(0:MTBIN)                ! WT-RM bin center
	SAVE TFKFT
	SAVE HA
	SAVE DWA
	SAVE DWT
	SAVE GAMSAV
	SAVE YINSAV
	SAVE PHISAV
	SAVE RMSAV
	DATA RMSAV,GAMSAV,YINSAV,PHISAV/0.D1,0.D1,0.D1,0.D1/
C
C---Is this a new set of parameters (RM,GAM,WSPREAD)?
	IF(GAM.NE.GAMSAV)GO TO 18
	IF(YINT.NE.YINSAV)GO TO 18
	IF(PHI.NE.PHISAV)GO TO 18
	IF(ABS(RM/RMSAV-1.).GT..0003)GO TO 18
	GO TO 19
C
C---Save new parameters
 18	GAMSAV=GAM
	YINSAV=YINT
	PHISAV=PHI
	RMSAV=RM
C	
C---Initialize table of F_KF values
C     F_KF is calculated once at an array of energies WA, and stored as TFKFT.
C     F_KF is a function of x, and only weakly (in logs) a function of s.
C     Nominally, s = WT^2 and x = (s-WR^2)/s.
C     We approximate F_KF as a function of a single variable WA = sqrt(s').
C     We take s' = (WT*RM/WR)^2 and x' = (s'-RM^2)/s', which differs only
C      in the explicit dependence of F_KF on s in log terms.
C     
	DWA1=.5D0/MKBIN                       ! width of bin1=(1 MeV)/MKBIN
	DWA(1)=DWA1
	HA(1)=.5D0*DWA1                       ! middle of bin1
	HA1=0.D0                              ! bottom of bin1
	DO 10 KBIN=1,MKBIN                  ! loop over WA's
	  IF(KBIN.GT.1)THEN
	    J=KBIN-1
	    HA1=HA1+DWA(J)                  ! bottom of bin
	    DWA(KBIN)=KBIN*DWA1             ! bin width (prop to WA-RM)
	    HA(KBIN)=DWA(KBIN)/DLOG(1.D0+DWA(KBIN)/HA1)   ! 'centroid' of bin
	  ENDIF
 	  S=(HA(KBIN)+RM)**2
	  X=(S-RM**2)/S
	  TFKFT(KBIN)=TFKF(X,S)               ! store F_KF value
 10	CONTINUE
ct	type 1000,MKBIN,HA(MKBIN),TFKFT(1)   ! diagnostic
ct 1000	format(' MKBIN,HA(MKBIN),TFKFT(1)=',I6,F12.1,E12.4)
C
C---Define bins in HT
	IF(GAM.LT.TINY)GO TO 20             ! skip BW convolution?
	JTBIN=MTBIN/100
	IF(GAM.GE.1.D0)JTBIN=MTBIN/10
cz	IF(GAM.GE.10.D0)JTBIN=MTBIN
	AJTB=FLOAT(JTBIN)
	DWT1=GAM/AJTB                       ! inside binwid in MeV
	DWT(0)=DWT1                         ! width of bin0
	HT1=-.5D0*DWT1                        ! bottom of bin0
	HT(0)=0.D0                            ! middle of bin0
	DO 17 ITBIN=1,MTBIN                 ! loop over WT's
	  IF(ITBIN.LE.JTBIN)THEN            ! inside GAM?
	    D=DWT1                          ! width of bin (fixed)
	    HT1=HT1+DWT1                    ! bottom of bin
	    HT(ITBIN)=HT1+.5D0*DWT1           ! middle of bin
	  ELSE                              ! outside GAM
	    D=DWT1*FLOAT(ITBIN)/AJTB        ! width of bin (prop to WT-RM)
	    HT1=HT1+DWT(ITBIN-1)            ! bottom of bin
	    HT(ITBIN)=DSQRT(D/(1.D0/HT1-1.D0/(HT1+D)))  ! 'centroid' of bin
	  ENDIF
	  DWT(ITBIN)=D
 17	CONTINUE
C
C---Load table of BW convoluted with F_KF, for an array of WT values
	GAMBPIM=GAM/(PI*RM)                ! GAM/(pi*RM)
	GAMSB4=GAM**2/4.D0
	IF(ABS(YINT).GT.VTINY)THEN         ! any interference?
	   PHIRAD=PI*PHI/180.D0              ! in radians
	   CPHI=DCOS(PHIRAD)
	   SPHI=DSIN(PHIRAD)
	ENDIF
	DO 14 ITBIN=-MTBIN,MTBIN           ! loop over WT's
	  H=HT(IABS(ITBIN))                ! middle of bin
	  IF(ITBIN.LT.0)H=-H
	  WT=H+RM
	  BWKF(ITBIN)=0.D0
	  IF(WT.LE.0.D0)GO TO 14
	  SUM=0.
	  DO 15 KBIN=1,MKBIN               ! sum over WA's
	    WA=HA(KBIN)+RM
	    HR=(WT/WA-1.)*RM
	    DENOM=HR**2+GAMSB4*(1.D0+HR/RM)**2  ! BW denominator
cbw	    DENOM=(HR*.5D0*(WA+RM)/RM)**2+GAMSB4*(1.D0+HR/RM)**2 ! relativ'ic 
	    BW=1.D0/DENOM
	    IF(ABS(YINT).GT.VTINY)BW=BW*(1.D0+YINT*(2.D0*HR*CPHI/GAM+SPHI))
	    SUM=SUM+TFKFT(KBIN)*DWA(KBIN)*BW   ! BW convolution integrand
 15	  CONTINUE
	  IF(ABS(HR)/GAM.GT.8.D0)THEN        ! have we got all of BW?
	    BWKF(ITBIN)=GAMBPIM*SUM        ! BW*KF convolution
C            2/RM converts variable of integration from x to W.
C            GAM/(2pi) normalizes Breit-Wigner
	  ELSE
	    SM=WT**2-RM**2
	    BWKF(ITBIN)=0.D0
	    IF(SM.GT.0.D0)BWKF(ITBIN)=2.D0*TFKF(SM/S,S)/RM  ! BW ~ delta fn
	  ENDIF
 14	CONTINUE
C
C---Calculate [BW convoluted with F_KF] convoluted with Gaussian, at given HC
 19	IF(GAM.LT.TINY)GO TO 20            ! skip BW convolution?
	SUM=0.D0
	DELHF=-1.D8			! init previous WT-RM
	LSKIP=.FALSE.
	IF(WSPREAD.LT.5.D0*DWT(0))LSKIP=.TRUE.  ! skip spread?
	DO 11 ITBIN=-MTBIN,MTBIN           ! sum over WT's
	  H=HT(IABS(ITBIN))                ! WT-RM
	  IF(ITBIN.LT.0)H=-H
	  DELH=H-HC
	  IF(LSKIP)THEN
	    IF(DELH*DELHF.LT.0.D0)THEN
	      TAUKF=BWKF(ITBIN)
	      RETURN
	    ENDIF
	    DELHF=DELH
	    GO TO 11
	  ENDIF
	  SIGS=DELH/(ROOT2*WSPREAD)        ! sqrt of exponent
	  IF((ITBIN.EQ.MTBIN).AND.(SIGS.LT.2.D0))GO TO 12 ! run out of bins?
	  IF(SIGS.GT.3.D0)GO TO 13         ! Gaussian getting negligible?
	  P=SIGS**2                        ! exponent
	  IF(P.LT.PMAX)THEN
c!!	    IF(DWT(IABS(ITBIN)).GT..2d0*WSPREAD)GO TO 12  ! binning too coarse?
            SUM=SUM+DEXP(-P)*BWKF(ITBIN)*DWT(IABS(ITBIN))
	  ENDIF
 11	CONTINUE
 13	TAUKF=SUM/(RTWOPI*WSPREAD)         ! convolution
C         1/(sqrt(2*pi)*WSPREAD) normalizes Gaussian
	RETURN
C
C---Don't smear if overflow MKBINs
 12	SM=(HC+RM)**2-RM**2
	TAUKF=0.d0
	IF(SM.GT.0.d0)TAUKF=2.d0*TFKF(SM/S,S)/RM     ! ignore GAM, WSPREAD
	RETURN
C
C---Gaussian, KF convolution in case of negligible GAM
 20	SUM=0.d0
	DO 21 KBIN=1,MKBIN                     ! loop over array points
	  SIGS=(HA(KBIN)-HC)/(ROOT2*WSPREAD)
	  IF((KBIN.EQ.MKBIN).AND.(SIGS.LT.2.d0))GO TO 12 ! running out of bins?
	  IF(SIGS.GT.3.d0)GO TO 23              ! Gaussian getting negligible?
	  P=SIGS**2
	  IF(P.LT.PMAX)THEN
	    IF(DWT(IABS(ITBIN)).GT..2d0*WSPREAD)GO TO 12  ! binning too coarse?
	    SUM=SUM+DEXP(-P)*TFKFT(KBIN)*DWA(KBIN)
	  ENDIF
 21	CONTINUE
 23	TAUKF=RTWOBPI*SUM/(RM*WSPREAD)
C         2/RM converts variable of integration from x to W.
C         1/(sqrt(2*pi)*WSPREAD) normalizes Gaussian
	RETURN
	END
C
C--------------------------------------------------------------------------
	DOUBLE PRECISION FUNCTION TFKF(X,S)
C   Radiative tail spectrum from Kuraev and Fadin (equation 28)
C   Does not include contribution of radiated e+e- pairs (theta term)
C    (Use FUNCTION TFKFP to get same F with pairs included)
C   This routine assumes that resonance Gamma_ee ~ 0
C   All energies are in MeV
C   RM = central resonance mass
C   WT = true c.m. e+e- energy for particular event
C   WR = rest energy of produced resonance for particular event
C    assumed = RM for this routine
C   WC = centroid of CESR energy spectrum
C   S = WT^2
C   X = (WT^2 - WR^2)/WT^2   (~DeltaE/E)
C   TFKF diverges at x->0 like 1/(x^.9), so we average over x for x<XAV
C   DO NOT call this function for x<=0; it's not protected!
	IMPLICIT DOUBLE PRECISION A,B,C,D,E,F,G,H
     2   ,O,P,Q,R,S,T,U,V,W,X,Y,Z
	PARAMETER (XAV=1.D-6)                   ! average over x<XAV, was e-6
	PARAMETER (XFAST=.1D0)                  ! approx for x<XFAST (was .01)
	PARAMETER (ALPBPI=2.322819D-3)		! alpha/pi
	PARAMETER (PI=3.1415926D0)		! pi, pi^2
	PARAMETER (AM2=.2611199D0)		! m_e^2 in MeV^2
	PARAMETER (FAC=2.78987D0)                 ! pi^2/3 - .5
	LOGICAL LFIRST, LFAST
	DATA LFIRST/.TRUE./                     ! T: haven't hit singularity
	DATA LFAST/.TRUE./                      ! T: haven't done low-x logs
C
C---Initialize logs for fast calculation at low x
	IF(X.LE.XFAST)THEN                      ! x low enough to approx logs?
	  IF(LFAST)THEN                         ! no low-x logs yet?
	    S0=(1.D0-X)*S                         ! s value for x=0
	    ALOGRF=DLOG(S0/AM2)                 ! "L"  (K&F's notation)
	    BETAF=2.D0*ALPBPI*(ALOGRF-1.D0)	! "beta" (same as J&S's "t")
	    BETA2F=BETAF**2
	    LFAST=.FALSE.
	  ENDIF
	  XB=X/(1.-X)                           ! 1st order correction to "L"
	  ALOGR=ALOGRF+XB                       ! corrected "L"
	  BETA=BETAF+ALPBPI*XB                  ! corrected "t"
	  BETA2=BETA2F
	ELSE
	  ALOGR=DLOG(S/AM2)			! slow calculation for logs
	  BETA=2.D0*ALPBPI*(ALOGR-1.D0)
	  BETA2=BETA**2
	ENDIF
C
C---Smooth over small-x singularity
C     The delta-function singularity is replaced by a linearly decreasing
C     function having the same area, extending from x=0 to x=XAV, and matching
C     on to the tail of F_KF(x) at x=XAV.
	IF(X.LE.XAV)THEN                        ! is x at the singularity?
	  IF(LFIRST)THEN                        ! first time at singularity?
	    F1=1.D0+.75D0*BETA+ALPBPI*FAC       ! integrate over singularity
     2       +BETA**2*(-.4370503D0-ALOGR/72.D0)
	    TFKFAV=F1*XAV**(BETA-1.D0)             ! av TFKF between 0 and XAV
	    T1=BETA*XAV**(BETA-1.D0)*(1.+ALPBPI*FAC+.75D0*BETA ! 1st tm eq. 28
     2       -(BETA2/24.D0)*(ALOGR/3.D0+10.4892D0))
	    T2=BETA*(1.D0-.5D0*XAV)                            ! 2nd term ..
	    T3=.125D0*BETA2*(-4.D0*(2.D0-XAV)*DLOG(XAV)
     2       -((1.D0+3.D0*(1.D0-XAV**2))/XAV)*DLOG(1.D0-XAV)-6.D0+XAV)
	    TFKF2=T1-T2+T3                       ! TFKF at X = XAV
	    LFIRST=.FALSE.
	  ENDIF
	  TFKF=TFKFAV-(TFKFAV-TFKF2)*(2.D0*X-XAV)/XAV ! sloping spread singularity
	  RETURN
	ENDIF
C
C---For non-infinitesimal x
	T1=BETA*X**(BETA-1.D0)*(1.D0+ALPBPI*FAC+.75D0*BETA ! 1st tm in eq. 28
     2   -(BETA2/24.D0)*(ALOGR/3.D0+10.4892D0))
	T2=BETA*(1.D0-.5D0*X)                                ! 2nd term ..
	T3=.125D0*BETA2*(-4.D0*(2.D0-X)*DLOG(X)-((1.D0+3.D0*(1.D0-X**2))/X)
     2   *DLOG(1.D0-X)-6.D0+X)                          ! 3rd term
	TFKF=T1-T2+T3
	RETURN
	END




