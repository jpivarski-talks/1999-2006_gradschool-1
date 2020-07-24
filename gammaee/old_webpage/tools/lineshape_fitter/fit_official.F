ccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc
ccccc program fit ccccccccccccccccccccccccccccccccccccccccccccccccc
ccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc
      program fit
      implicit none
      
c     common block
      common /criteria/low, high, gam, yint, phi,
     $     brmumu, tyint, tphi,
     $     phofrac, j1t, j2t, y1t, y2t,
     $     en(2000), xs(2000), err2(2000),
     $     npoints, res
      double precision low, high, gam, yint, phi
      double precision brmumu, tyint, tphi
      double precision phofrac, j1t, j2t, y1t, y2t
      double precision en, xs, err2
      integer npoints, res

c     functions
      external gbwkf
      double precision gbwkf
      external chifunc
      external fitfunc
      double precision fitfunc

c     variables for reading data
      double precision thisen, thisXS, thisErr

c     variables for the pre-minimization
      double precision par(4), step(4)

c     variables for MINUIT parameters
      double precision darea, dmass, dwide, dback
      integer ipar
      character*10 chnam
      double precision dstep, dlo, dhi
      integer ierflg
      integer narg
      double precision darg(10)

c     variables for reading out fit results
      double precision area, mass, wide, back
      double precision earea, emass, ewide, eback
      double precision bnd1, bnd2
      integer ivarbl

c     variables for checking a small hypercube around the minimum
      double precision min, trial
      double precision a, m, w, b
      double precision larea, lmass, lwide, lback

c     variables for printing out fit results as a curve
      double precision x
      integer i

c     variables for checking chi^2 at the uncertainties
      double precision deri(4), dval, dpar(4)

c     read in formatted data: energy in COM MeV, hadronic XS in nb, err in XS
      npoints = 0
 100  read (*, *, end=200) thisen, thisXS, thisErr
      npoints = npoints + 1
      en(npoints)   = thisen
      xs(npoints)   = thisXS
      err2(npoints) = thisErr**2
      goto 100

c     set up the other parameters based on a guess about the resonance
 200  if ( en(2) .gt. 9428. .and. en(2) .lt. 9564. ) then
         print *, ' '
         print *, '****************************************************'
         print *, 'Assuming upsilon ONE(1)-S, ', npoints,
     $        ' data points.'
         print *, '****************************************************'
         print *, ' '
         res = 1
         low = 9428.D0
         high = 9564.D0
         gam = 0.0525D0
         yint = en(1)
         phi = 0.0D0
         brmumu = 0.0248D0
         tyint = 0.34D0
         tphi = 0.D0

         phofrac = 0.033D0
         j1t = 1.D0
         j2t = 1.D0
         y1t = 1.D0
         y2t = 1.D0

         par(1) = 282.06D0
         par(2) = 9460.241D0
         par(3) = 3.878D0
         par(4) = 4.188D0

         step(1) = 1.0D0
         step(2) = 0.02D0
         step(3) = 0.01D0
         step(4) = 0.01D0

      else if ( en(2) .gt. 9994. .and. en(2) .lt. 10088. ) then
         print *, ' '
         print *, '****************************************************'
         print *, 'Assuming upsilon TWO(2)-S, ', npoints,
     $        ' data points.'
         print *, '****************************************************'
         print *, ' '
         res = 2
         low = 9994.D0
         high = 10088.D0
         gam = 0.044D0
         yint = en(1)
         phi = 0.0D0
         brmumu = 0.0131D0
         tyint = 0.73D0
         tphi = 0.D0

         phofrac = 0.033D0
         j1t = 1.D0
         j2t = 1.D0
         y1t = 1.D0
         y2t = 1.D0

         par(1) = 112.43D0
         par(2) = 10024.6D0
         par(3) = 4.1504D0
         par(4) = 3.463134D0

         step(1) = 1.0D0
         step(2) = 0.02D0
         step(3) = 0.01D0
         step(4) = 0.01D0

      else if ( en(2) .gt. 10325. .and. en(2) .lt. 10403. ) then
         print *, ' '
         print *, '****************************************************'
         print *, 'Assuming upsilon THREE(3)-S, ', npoints,
     $        ' data points.'
         print *, '****************************************************'
         print *, ' '
         res = 3
         low = 10325.D0
         high = 10403.D0

         gam = 0.0263D0
         yint = en(1)
         phi = 0.D0
         brmumu = 0.0181D0
         tyint = 0.47D0
         tphi = 0.D0

         phofrac = 0.033D0
         j1t = 1.D0
         j2t = 1.D0
         y1t = 1.D0
         y2t = 1.D0

         par(1) = 76.3D0
         par(2) = 10358.0166D0
         par(3) = 4.697D0
         par(4) = 4.245D0

         step(1) = 1.0D0
         step(2) = 0.02D0
         step(3) = 0.01D0
         step(4) = 0.01D0

      else
         print *, 'First data point is way off--- maybe you forgot to ',
     $        'convert to COM MeV?'
         stop
      end if

      print *, 'WHICHYINT ', yint

      if ( en(2) .gt. 0 ) then
         darea = par(1)
         dmass = par(2)
         dwide = par(3)
         dback = par(4)

         step(1) = 1.0D0
         step(2) = 0.02D0
         step(3) = 0.01D0
         step(4) = 0.01D0
         
c        Set up MINUIT and all its parameters
         call mninit(6, 6, 6)
         call mnseti('Kuraev-Fadin Fit with Goodies')

         ipar = 1
         chnam = 'area'
         dstep = step(1)
         dlo = 10.D0
         dhi = 500.D0
         call mnparm(ipar, chnam, darea, dstep, dlo, dhi, ierflg)
         if ( ierflg .gt. 0 ) then
            print *, 'parameter ''area'' open failure ', ierflg
            stop
         end if

         ipar = 2
         chnam = 'mass'
         dstep = step(2)
         dlo = low
         dhi = high
         call mnparm(ipar, chnam, dmass, dstep, dlo, dhi, ierflg)
         if ( ierflg .gt. 0 ) then
            print *, 'parameter ''mass'' open failure ', ierflg
            stop
         end if

         ipar = 3
         chnam = 'wide'
         dstep = step(3)
         dlo = 0.1D0
         dhi = 8.D0
         call mnparm(ipar, chnam, dwide, dstep, dlo, dhi, ierflg)
         if ( ierflg .gt. 0 ) then
            print *, 'parameter ''wide'' open failure ', ierflg
            stop
         end if

         ipar = 4
         chnam = 'back'
         dstep = step(4)
         dlo = 0.D0
         dhi = 8.D0
         call mnparm(ipar, chnam, dback, dstep, dlo, dhi, ierflg)
         if ( ierflg .gt. 0 ) then
            print *, 'parameter ''back'' open failure ', ierflg
            stop
         end if

         narg = 1
         darg(1) = 2.           ! 1 = default, 2 = slow & precise
         call mnexcm(chifunc, 'SET STRATEGY', darg, narg, ierflg, 0)
         if ( ierflg .gt. 0 ) then
            print *, 'call to SET STRATEGY failed ', ierflg
            stop
         end if

         narg = 2
         darg(1) = 10000.       ! maximum number of iterations
         darg(2) = 0.1          ! tolerance is 0.01% of a chi^2
         call mnexcm(chifunc, 'MINIMIZE', darg, narg, ierflg, 0)
         if ( ierflg .gt. 0 ) then
            print *, 'call to MINIMIZE failed ', ierflg
            stop
         end if

         narg = 2
         darg(1) = 10000.       ! maximum number of iterations
         darg(2) = 1.           ! which parmeter (area)
         call mnexcm(chifunc, 'MINOS', darg, narg, ierflg, 0)
         if ( ierflg .gt. 0 ) then
            print *, 'call to MINOS AREA failed ', ierflg
            stop
         end if

         narg = 0
         call mnexcm(chifunc, 'SAVE', darg, narg, ierflg, 0)
         call mnexcm(chifunc, 'SHOW CORRELATIONS', darg, narg, ierflg,
     $        0)
         call mnexcm(chifunc, 'SHOW COVARIANCE', darg, narg, ierflg, 0)
         call mnexcm(chifunc, 'SHOW EIGENVALUES', darg, narg, ierflg, 0)

c        extract the fitted values and draw theory plots
         call mnpout(1, chnam, area, earea, bnd1, bnd2, ivarbl)
         call mnpout(2, chnam, mass, emass, bnd1, bnd2, ivarbl)
         call mnpout(3, chnam, wide, ewide, bnd1, bnd2, ivarbl)
         call mnpout(4, chnam, back, eback, bnd1, bnd2, ivarbl)

         print *, ' '
         do 215, x = low-3., high+3., (high-low)/1000.
            print 210, x, fitfunc(x, area, mass, wide, back, 0)
 210        format('LINESHAPE	', f20.10, '	', f20.10)
 215     continue

         print *, ' '
         do 225, i = 2, npoints
            print 220, en(i), (xs(i) -
     $        fitfunc(en(i), area, mass, wide, back, 0)), sqrt(err2(i))
 220        format('RESIDUAL 	', f20.10, '	', f20.10, '	', f20.10)
 225     continue

         print *, ' '
         do 235, i = 2, npoints
            print 230, en(i), (xs(i) -
     $        fitfunc(en(i), area, mass, wide, back, 0)) / sqrt(err2(i))
 230        format('NORMRESID	', f20.10, '	', f20.10)
 235     continue

         print *, ' '
         print *, 'Evaluate at minimum:'
         dpar(1) = area
         dpar(2) = mass
         dpar(3) = wide
         dpar(4) = back
         deri(1) = 0.
         deri(2) = 0.
         deri(3) = 0.
         deri(4) = 0.
         call chifunc(4, deri, dval, dpar, 0)

         print *, 'THEFINALMINIMUM ', dval

         print *, ' '
         print 300, 'area', area, earea, 'MeV nb'
         print 300, 'mass', mass, emass, 'MeV   '
         print 300, 'wide', wide, ewide, 'MeV   '
         print 300, 'back', back, eback, 'nb    '
 300     format('FITTED PARAMETER	', a4, ' = ', f20.10, ' +/- ', f20.10,
     $        ' ', a6)
         print *, ' '
         call mnexcm(chifunc, 'SHOW FCNVALUE', darg, narg, ierflg, 0)
         print *, ' '
         if ( res .eq. 1 ) print *, 'Assuming upsilon ONE(1)-S, ',
     $        npoints, ' data points.'
         if ( res .eq. 2 ) print *, 'Assuming upsilon TWO(2)-S, ',
     $        npoints, ' data points.'
         if ( res .eq. 3 ) print *, 'Assuming upsilon THREE(3)-S, ',
     $        npoints, ' data points.'

      else
         area  = par(1)
         mass  = par(2)
         wide  = par(3)
         back  = par(4)

         do 500, x = low-3., high+3., (high-low)/1000.
            print 400, x, fitfunc(x, area, mass, wide, back, 0)
 400        format(f20.10, '	', f20.10)
 500     continue

      endif

      stop
      end

ccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc
ccccc function fitfunc cccccccccccccccccccccccccccccccccccccccccccc
ccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc
      double precision function fitfunc(x, area, mass, wide, back,
     $                                  imode)
      implicit none

c     formal parameters
      double precision x, area, mass, wide, back
      integer imode

c     common block
      common /criteria/low, high, gam, yint, phi,
     $     brmumu, tyint, tphi,
     $     phofrac, j1t, j2t, y1t, y2t,
     $     en(2000), xs(2000), err2(2000),
     $     npoints, res
      double precision low, high, gam, yint, phi
      double precision brmumu, tyint, tphi
      double precision phofrac, j1t, j2t, y1t, y2t
      double precision en, xs, err2
      integer npoints, res

c     functions
      external gbwkf
      double precision gbwkf

c     parts of the theory expression
      double precision peak, tpeak, sInv, photon, tails

      peak = area * gbwkf(mass, gam, wide, yint, phi, x - mass)
      tpeak = 0
      sInv = back * 9430.**2 / x**2
      photon = phofrac * back * log(x**2) / log(9430.**2)
      tails = j1t*75.3/(x - 3096.87) + j2t*30.4/(x - 3685.96)
      if ( abs(res) .gt. 1 ) tails = tails + y1t*18.9/(x - 9460.3)
      if ( abs(res) .gt. 2 ) tails = tails + y2t*7.9/(x - 10024.6)

      fitfunc = peak + sInv + photon + tails

      return
      end

ccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc
ccccc subroutine chifunc cccccccccccccccccccccccccccccccccccccccccc
ccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc
      subroutine chifunc(npar, deri, dval, dpar, iflag, futil)
      implicit none

c     formal parameters
      integer npar
      double precision deri(*), dval, dpar(*)
      integer iflag
      external futil

c     common block
      common /criteria/low, high, gam, yint, phi,
     $     brmumu, tyint, tphi,
     $     phofrac, j1t, j2t, y1t, y2t,
     $     en(2000), xs(2000), err2(2000),
     $     npoints, res
      double precision low, high, gam, yint, phi
      double precision brmumu, tyint, tphi
      double precision phofrac, j1t, j2t, y1t, y2t
      double precision en, xs, err2
      integer npoints, res

c     functions
      external fitfunc
      double precision fitfunc

c     looping variable
      integer i

      print 600, dpar(1), dpar(2), dpar(3), dpar(4)
 600  format('SAMPLE ', f20.10, ' ', f20.10, ' ', f20.10, ' ', f20.10)

      dval = 0.
      do 700 i = 2, npoints
         dval = dval + (xs(i) -
     $        fitfunc(en(i), dpar(1), dpar(2), dpar(3), dpar(4), 0))**2
     $        / err2(i)
 700  continue

      print 800, dval, npoints-4, dval/(npoints-4)
 800  format('CHI2                                                    ',
     $     '                                  ',
     $     f20.10, ' / ', i3, ' = ', f20.10)

      return
      end

