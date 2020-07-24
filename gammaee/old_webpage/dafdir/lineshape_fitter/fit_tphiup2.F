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
      external tgbwkf
      double precision tgbwkf
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
 200  if ( npoints .eq. 0 .or. (en(1).lt.0 .and. npoints.ne.18) ) then
         print *, 'To fit a resonance, STDIN must be one datum per ',
     $        'line, like this:'
         print *, '    energy in COM MeV     hadronic XS in nb     ',
     $        'err in hadronic XS in nb'
         print *, ' '
         print *, 'To draw a spectrum, STDIN must be one parameter',
     $        ' per line, like this:'
         print *, '    resonance (-1, -2, -3)'
         print *, '    low window edge in COM MeV (9428, 9994, 10325)'
         print *, '    high window edge in COM MeV (9564, 10088, 10403)'
         print *, '    BW gamma in MeV (0.0525, 0.044, 0.0263)'
         print *, '    qqbar interference mag (0.0174, 0.0169, 0.0171)'
         print *, '    qqbar interference phase (0, 0, 0)'
         print *, '    Br_{mu+mu-} (for tau) (0.0248, 0.0131, 0.0181)'
         print *, '    l+l- interference mag (0.34, 0.73, 0.47)'
         print *, '    l+l- interference phase (0, 0, 0)'
         print *, '    2-photon fraction (0.07, 0.07, 0.07)'
         print *, '    J/psi tail inclusion (1, 1, 1)'
         print *, '    psi'' tail inclusion (1, 1, 1)'
         print *, '    U(1S) tail inclusion (1, 1, 1) (if applicable)'
         print *, '    U(2S) tail inclusion (1, 1, 1) (if applicable)'
         print *, '    area in MeV nb (261.08, 112.43, 77.05870)'
         print *, '    mass in MeV (9460.3, 10024.6, 10358.2)'
         print *, '    beam spread in MeV (3.7873, 4.1504, 4.668636)'
         print *, '    1/s(@ 9430 MeV) in nb (3.364647, 3.463134, ',
     $        '3.575358)'
         print *, ' '
         stop

      else if ( en(1) .lt. 0. ) then
         res = -en(1)

         low = en(2)
         high = en(3)
         gam = en(4)
         yint = en(5)
         phi = en(6)
         brmumu = en(7)
         tyint = en(8)
         tphi = en(9)

         phofrac = en(10)
         j1t = en(11)
         j2t = en(12)
         y1t = en(13)
         y2t = en(14)

         par(1) = en(15)
         par(2) = en(16)
         par(3) = en(17)
         par(4) = en(18)

         step(1) = 1.0D0
         step(2) = 0.02D0
         step(3) = 0.01D0
         step(4) = 0.01D0

      else if ( en(1) .gt. 9428. .and. en(1) .lt. 9564. ) then
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
         yint = 0.0174D0
         phi = 0.0D0
         brmumu = 0.0248D0
         tyint = 0.34D0
         tphi = 1.D0   ! tphi up two from 0.D0

         phofrac = 0.033D0
         j1t = 1.D0
         j2t = 1.D0
         y1t = 1.D0
         y2t = 1.D0

C          par(1) = 261.08D0
C          par(2) = 9460.3D0
C          par(3) = 3.7873D0
C          par(4) = 3.364647D0
         par(1) = 282.06D0
         par(2) = 9460.241D0
         par(3) = 3.878D0
         par(4) = 4.188D0

         step(1) = 1.0D0
         step(2) = 0.02D0
         step(3) = 0.01D0
         step(4) = 0.01D0

      else if ( en(1) .gt. 9994. .and. en(1) .lt. 10088. ) then
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
         yint = 0.0169D0
         phi = 0.0D0
         brmumu = 0.0131D0
         tyint = 0.73D0
         tphi = 1.D0   ! tphi up two from 0.D0

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

      else if ( en(1) .gt. 10325. .and. en(1) .lt. 10403. ) then
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
         yint = 0.0171D0
         phi = 0.D0
         brmumu = 0.0181D0
         tyint = 0.47D0
         tphi = 1.D0   ! tphi up two from 0.D0

         phofrac = 0.033D0
         j1t = 1.D0
         j2t = 1.D0
         y1t = 1.D0
         y2t = 1.D0

C          par(1) = 77.2389619673D0
C          par(2) = 10357.9759316115D0
C          par(3) = 4.6910300462D0
C          par(4) = 4.2916222779D0
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

      if ( en(1) .gt. 0 ) then
c     Do my pre-minimization
C          do while(step(1).gt.0.0001   .and. step(2).gt.0.000003 .and.
C      $            step(3).gt.0.000003 .and. step(4).gt.0.000001)
C             call mymini(4, par, step)
C             call mymini(3, par, step)
C             call mymini(1, par, step)
C             call mymini(2, par, step)
C          end do
         
         darea = par(1)
         dmass = par(2)
         dwide = par(3)
         dback = par(4)

         step(1) = 1.0D0
         step(2) = 0.02D0
         step(3) = 0.01D0
         step(4) = 0.01D0
         
C          print *, 'SCANAREA IDEAL ', darea
C          do area=(darea-0.021),(darea+0.021),(0.021/30.)
C             par(1) = area
C             x = 0
C             call chifunc(4, deri, x, par, 0)
C             print *, 'SCANAREA ', area, ' ', x
C          end do
C          par(1) = darea

C          print *, 'SCANMASS IDEAL ', dmass
C          do mass=(dmass-0.021),(dmass+0.021),(0.021/30.)
C             par(2) = mass
C             x = 0
C             call chifunc(4, deri, x, par, 0)
C             print *, 'SCANMASS ', mass, ' ', x
C          end do
C          par(2) = dmass

C          print *, 'SCANWIDE IDEAL ', dwide
C          do wide=(dwide-0.021),(dwide+0.021),(0.021/30.)
C             par(3) = wide
C             x = 0
C             call chifunc(4, deri, x, par, 0)
C             print *, 'SCANWIDE ', wide, ' ', x
C          end do
C          par(3) = dwide

C          print *, 'SCANBACK IDEAL ', dback
C          do back=(dback-0.021),(dback+0.021),(0.021/30.)
C             par(4) = back
C             x = 0
C             call chifunc(4, deri, x, par, 0)
C             print *, 'SCANBACK ', back, ' ', x
C          end do
C          par(4) = dback

c        Set up MINUIT and all its parameters
         call mninit(6, 6, 6)
         call mnseti('Kuraev-Fadin Fit with Goodies')

         ipar = 1
         chnam = 'area'
         dstep = step(1)
         dlo = 50.D0
         dhi = 300.D0
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

c         narg = 1
c         darg(1) = 1.
c         call mnexcm(chifunc, 'FIX', darg, narg, ierflg, 0)
c         if ( ierflg .gt. 0 ) then
c            print *, 'call to FIX 1 (area) failed ', ierflg
c            stop
c         end if
c         narg = 1
c         darg(1) = 2.
c         call mnexcm(chifunc, 'FIX', darg, narg, ierflg, 0)
c         if ( ierflg .gt. 0 ) then
c            print *, 'call to FIX 2 (mass) failed ', ierflg
c            stop
c         end if
c         narg = 1
c         darg(1) = 3.
c         call mnexcm(chifunc, 'FIX', darg, narg, ierflg, 0)
c         if ( ierflg .gt. 0 ) then
c            print *, 'call to FIX 3 (wide) failed ', ierflg
c            stop
c         end if
c         narg = 1
c         darg(1) = 4.
c         call mnexcm(chifunc, 'FIX', darg, narg, ierflg, 0)
c         if ( ierflg .gt. 0 ) then
c            print *, 'call to FIX 4 (back) failed ', ierflg
c            stop
c         end if

C          narg = 1
C          darg(1) = 0.           ! 0 = check gradient correctness
C                                 ! 1 = force MINUIT to use my gradients
C          call mnexcm(chifunc, 'SET GRADIENT', darg, narg, ierflg, 0)
C          if ( ierflg .gt. 0 ) then
C             print *, 'call to SET GRADIENT 0 failed ', ierflg
C             stop
C          end if

C          narg = 2
C          darg(1) = 10000.       ! maximum number of iterations
C          darg(2) = 0.00001      ! tolerance is 0.001% of a chi^2
C          call mnexcm(chifunc, 'SIMPLEX', darg, narg, ierflg, 0)
C          if ( ierflg .gt. 0 ) then
C             print *, 'call to SIMPLEX failed ', ierflg
C             stop
C          end if

C          narg = 1
C          darg(1) = 10000.       ! maximum number of iterations
C          call mnexcm(chifunc, 'HESSE', darg, narg, ierflg, 0)
C          if ( ierflg .gt. 0 ) then
C             print *, 'call to HESSE failed ', ierflg
C             stop
C          end if

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

C          dpar(1) = area
C          dpar(2) = mass
C          dpar(3) = wide
C          dpar(4) = back
C          larea = 0.01 * earea
C          lmass = 0.01 * emass
C          lwide = 0.01 * ewide
C          lback = 0.01 * eback
C          deri(1) = 0.
C          deri(2) = 0.
C          deri(3) = 0.
C          deri(4) = 0.
C          print *, 'Calculating function at minimum...'
C          call chifunc(4, deri, min, dpar, 0)

C          print *, 'Trying area-epsilon face of hypercube...'
C          a = area - larea
C          do m = mass-lmass, mass+lmass, lmass/3.
C             do w = wide-lwide, wide+lwide, lwide/3.
C                do b = back-lback, back+lback, lback/3.
C                   dpar(1) = a
C                   dpar(2) = m
C                   dpar(3) = w
C                   dpar(4) = b
C                   call chifunc(4, deri, trial, dpar, 0)
C                   if ( trial .le. min ) then
C                      print *, 'Smaller minimum found.'
C                      stop
C                   end if
C                end do
C             end do
C          end do
C          print *, 'Trying area+epsilon face of hypercube...'
C          a = area + larea
C          do m = mass-lmass, mass+lmass, lmass/3.
C             do w = wide-lwide, wide+lwide, lwide/3.
C                do b = back-lback, back+lback, lback/3.
C                   dpar(1) = a
C                   dpar(2) = m
C                   dpar(3) = w
C                   dpar(4) = b
C                   call chifunc(4, deri, trial, dpar, 0)
C                   if ( trial .le. min ) then
C                      print *, 'Smaller minimum found.'
C                      stop
C                   end if
C                end do
C             end do
C          end do

C          print *, 'Trying mass-epsilon face of hypercube...'
C          m = mass - lmass
C          do a = area-larea, area+larea, larea/3.
C             do w = wide-lwide, wide+lwide, lwide/3.
C                do b = back-lback, back+lback, lback/3.
C                   dpar(1) = a
C                   dpar(2) = m
C                   dpar(3) = w
C                   dpar(4) = b
C                   call chifunc(4, deri, trial, dpar, 0)
C                   if ( trial .le. min ) then
C                      print *, 'Smaller minimum found.'
C                      stop
C                   end if
C                end do
C             end do
C          end do
C          print *, 'Trying mass+epsilon face of hypercube...'
C          m = mass + lmass
C          do a = area-larea, area+larea, larea/3.
C             do w = wide-lwide, wide+lwide, lwide/3.
C                do b = back-lback, back+lback, lback/3.
C                   dpar(1) = a
C                   dpar(2) = m
C                   dpar(3) = w
C                   dpar(4) = b
C                   call chifunc(4, deri, trial, dpar, 0)
C                   if ( trial .le. min ) then
C                      print *, 'Smaller minimum found.'
C                      stop
C                   end if
C                end do
C             end do
C          end do

C          print *, 'Trying wide-epsilon face of hypercube...'
C          w = wide - lwide
C          do m = mass-lmass, mass+lmass, lmass/3.
C             do a = area-larea, area+larea, larea/3.
C                do b = back-lback, back+lback, lback/3.
C                   dpar(1) = a
C                   dpar(2) = m
C                   dpar(3) = w
C                   dpar(4) = b
C                   call chifunc(4, deri, trial, dpar, 0)
C                   if ( trial .le. min ) then
C                      print *, 'Smaller minimum found.'
C                      stop
C                   end if
C                end do
C             end do
C          end do
C          print *, 'Trying wide+epsilon face of hypercube...'
C          w = wide + lwide
C          do m = mass-lmass, mass+lmass, lmass/3.
C             do a = area-larea, area+larea, larea/3.
C                do b = back-lback, back+lback, lback/3.
C                   dpar(1) = a
C                   dpar(2) = m
C                   dpar(3) = w
C                   dpar(4) = b
C                   call chifunc(4, deri, trial, dpar, 0)
C                   if ( trial .le. min ) then
C                      print *, 'Smaller minimum found.'
C                      stop
C                   end if
C                end do
C             end do
C          end do

C          print *, 'Trying back-epsilon face of hypercube...'
C          b = back - lback
C          do m = mass-lmass, mass+lmass, lmass/3.
C             do w = wide-lwide, wide+lwide, lwide/3.
C                do a = area-larea, area+larea, larea/3.
C                   dpar(1) = a
C                   dpar(2) = m
C                   dpar(3) = w
C                   dpar(4) = b
C                   call chifunc(4, deri, trial, dpar, 0)
C                   if ( trial .le. min ) then
C                      print *, 'Smaller minimum found.'
C                      stop
C                   end if
C                end do
C             end do
C          end do
C          print *, 'Trying back+epsilon face of hypercube...'
C          b = back + lback
C          do m = mass-lmass, mass+lmass, lmass/3.
C             do w = wide-lwide, wide+lwide, lwide/3.
C                do a = area-larea, area+larea, larea/3.
C                   dpar(1) = a
C                   dpar(2) = m
C                   dpar(3) = w
C                   dpar(4) = b
C                   call chifunc(4, deri, trial, dpar, 0)
C                   if ( trial .le. min ) then
C                      print *, 'Smaller minimum found.'
C                      stop
C                   end if
C                end do
C             end do
C          end do

C          print *, 'This minimum is a true minimum! ',
C      $        '(because I cannot believe the function is so devious ',
C      $        'that it has a little valley that escapes my net)'

         print *, ' '
         do 215, x = low-3., high+3., (high-low)/1000.
            print 210, x, fitfunc(x, area, mass, wide, back, 0)
 210        format('LINESHAPE	', f20.10, '	', f20.10)
 215     continue

         print *, ' '
         do 225, i = 1, npoints
            print 220, en(i), (xs(i) -
     $        fitfunc(en(i), area, mass, wide, back, 0)), sqrt(err2(i))
 220        format('RESIDUAL 	', f20.10, '	', f20.10, '	', f20.10)
 225     continue

         print *, ' '
         do 235, i = 1, npoints
            print 230, en(i), (xs(i) -
     $        fitfunc(en(i), area, mass, wide, back, 0)) / sqrt(err2(i))
 230        format('NORMRESID	', f20.10, '	', f20.10)
 235     continue

C          print *, ' '
C          print *, 'Evaluate at minimum:'
C          dpar(1) = area
C          dpar(2) = mass
C          dpar(3) = wide
C          dpar(4) = back
C          deri(1) = 0.
C          deri(2) = 0.
C          deri(3) = 0.
C          deri(4) = 0.
C          call chifunc(4, deri, dval, dpar, 0)

C          print *, 'Evaluate at +1 sigma in area:'
C          dpar(1) = area + earea
C          call chifunc(4, deri, dval, dpar, 0)

C          print *, 'Evaluate at -1 sigma in area:'
C          dpar(1) = area - earea
C          call chifunc(4, deri, dval, dpar, 0)

C          print *, 'Evaluate at +1 sigma in mass:'
C          dpar(1) = area
C          dpar(2) = mass + emass
C          call chifunc(4, deri, dval, dpar, 0)

C          print *, 'Evaluate at -1 sigma in mass:'
C          dpar(2) = mass - emass
C          call chifunc(4, deri, dval, dpar, 0)

C          print *, 'Evaluate at +1 sigma in wide:'
C          dpar(2) = mass
C          dpar(3) = wide + ewide
C          call chifunc(4, deri, dval, dpar, 0)

C          print *, 'Evaluate at -1 sigma in wide:'
C          dpar(3) = wide - ewide
C          call chifunc(4, deri, dval, dpar, 0)

C          print *, 'Evaluate at +1 sigma in back:'
C          dpar(3) = wide
C          dpar(4) = back + eback
C          call chifunc(4, deri, dval, dpar, 0)

C          print *, 'Evaluate at -1 sigma in back:'
C          dpar(4) = back - eback
C          call chifunc(4, deri, dval, dpar, 0)

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
      external tgbwkf
      double precision tgbwkf

c     parts of the theory expression
      double precision peak, tpeak, sInv, photon, tails

c     0: normal operation
      if ( imode .eq. 0 ) then
         peak = area * gbwkf(mass, gam, wide, yint, phi, x - mass)
C          peak = gbwkf(mass, gam, wide, yint, phi, x - mass)
C          print 550, mass, wide, x-mass, peak
C  550     format('gbwkf( ', f20.10, ' ', f20.10, ' ', f20.10, ' ) = ',
C      $        f20.10)
C          peak = peak * area

         tpeak = area * 1./(1./brmumu - 3.) * 0.2493 / 0.9287
     $        * tgbwkf(mass, gam, wide, tyint, tphi, x - mass)
         sInv = back * 9430.**2 / x**2
         photon = phofrac * back * log(x**2) / log(9430.**2)
         tails = j1t*75.3/(x - 3096.87) + j2t*30.4/(x - 3685.96)
         if ( abs(res) .gt. 1 ) tails = tails + y1t*18.9/(x - 9460.3)
         if ( abs(res) .gt. 2 ) tails = tails + y2t*7.9/(x - 10024.6)

         fitfunc = peak + tpeak + sInv + photon + tails

c     1: this is for an area derivative
      else if ( imode .eq. 1 ) then
         peak = gbwkf(mass, gam, wide, yint, phi, x - mass)
         tpeak = 1./(1./brmumu - 3.) * 0.2493 / 0.9287
     $        * tgbwkf(mass, gam, wide, tyint, tphi, x - mass)

         fitfunc = peak + tpeak
         
c     2: this is for a mass derivative
      else if ( imode .eq. 2 ) then
         x = x - 0.0001     ! move all x points down by delta m
         
         peak = area * gbwkf(mass, gam, wide, yint, phi, x - mass)
         tpeak = area * 1./(1./brmumu - 3.) * 0.2493 / 0.9287
     $        * tgbwkf(mass, gam, wide, tyint, tphi, x - mass)
         sInv = back * 9430.**2 / x**2
         photon = phofrac * back * log(x**2) / log(9430.**2)
         tails = j1t*75.3/(x - 3096.87) + j2t*30.4/(x - 3685.96)
         if ( abs(res) .gt. 1 ) tails = tails + y1t*18.9/(x - 9460.3)
         if ( abs(res) .gt. 2 ) tails = tails + y2t*7.9/(x - 10024.6)

         fitfunc = peak + tpeak + sInv + photon + tails

c     3: this is for a wide derivative
      else if ( imode .eq. 3 ) then
         x = x - (x - mass)*(0.0003 / wide)  ! squish all points in by a delta w
         
         peak = area * gbwkf(mass, gam, wide, yint, phi, x - mass)
         tpeak = area * 1./(1./brmumu - 3.) * 0.2493 / 0.9287
     $        * tgbwkf(mass, gam, wide, tyint, tphi, x - mass)
         sInv = back * 9430.**2 / x**2
         photon = phofrac * back * log(x**2) / log(9430.**2)
         tails = j1t*75.3/(x - 3096.87) + j2t*30.4/(x - 3685.96)
         if ( abs(res) .gt. 1 ) tails = tails + y1t*18.9/(x - 9460.3)
         if ( abs(res) .gt. 2 ) tails = tails + y2t*7.9/(x - 10024.6)

         fitfunc = peak + tpeak + sInv + photon + tails
         
c     4: this is for a back derivative
      else if ( imode .eq. 4 ) then
         sInv = 9430.**2 / x**2
         photon = phofrac * log(x**2) / log(9430.**2)

         fitfunc = sInv + photon

      else
         fitfunc = 0.
      end if

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
      do 700 i = 1, npoints
         dval = dval + (xs(i) -
     $        fitfunc(en(i), dpar(1), dpar(2), dpar(3), dpar(4), 0))**2
     $        / err2(i)
 700  continue

      if ( iflag .eq. 2 ) then
         deri(1) = 0.
         do 710 i = 1, npoints
            deri(1) = deri(1) - 2.*(xs(i) -
     $           fitfunc(en(i), dpar(1), dpar(2), dpar(3), dpar(4), 0))
     $           * fitfunc(en(i), dpar(1), dpar(2), dpar(3), dpar(4), 1)
     $           / err2(i)
 710     continue

         deri(2) = 0.
         do 720 i = 1, npoints
            deri(2) = deri(2) + (xs(i) -
     $           fitfunc(en(i), dpar(1), dpar(2), dpar(3), dpar(4), 2)
     $           )**2 / err2(i)
 720     continue
         deri(2) = (deri(2) - dval) / 0.0001 ! delta m is 0.0001

         deri(3) = 0.
         do 730 i = 1, npoints
            deri(3) = deri(3) + (xs(i) -
     $           fitfunc(en(i), dpar(1), dpar(2), dpar(3), dpar(4), 3)
     $           )**2 / err2(i)
 730     continue
         deri(3) = (deri(3) - dval) / 0.0003 ! delta w is 0.0003

         deri(4) = 0.
         do 740 i = 1, npoints
            deri(4) = deri(4) - 2.*(xs(i) -
     $           fitfunc(en(i), dpar(1), dpar(2), dpar(3), dpar(4), 0))
     $           * fitfunc(en(i), dpar(1), dpar(2), dpar(3), dpar(4), 4)
     $           / err2(i)
 740     continue

         print 750, deri(1), deri(2), deri(3), deri(4)
 750     format('DERIVS ', f20.10, ' ', f20.10, ' ', f20.10,
     $          ' ', f20.10)
      end if

      print 800, dval, npoints-4, dval/(npoints-4)
 800  format('CHI2                                                    ',
     $     '                                  ',
     $     f20.10, ' / ', i3, ' = ', f20.10)

      return
      end

ccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc
ccccc subroutine mymini ccccccccccccccccccccccccccccccccccccccccccc
ccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc
      subroutine mymini(i, par, step)
      implicit none

c     formal parameters
      integer i
      double precision par(*), step(*)

c     functions
      external chifunc
      double precision chifunc

c     three sample points to define a parabola
      double precision x1, x2, x3, y1, y2, y3, y12, y23, y31

c     dummy variables
      double precision deri(4), tmp(4)

c     new value of par(i)
      double precision newx

      deri(1) = 0.
      deri(2) = 0.
      deri(3) = 0.
      deri(4) = 0.

      tmp(1) = par(1)
      tmp(2) = par(2)
      tmp(3) = par(3)
      tmp(4) = par(4)

      y1 = 0.
      x1 = par(i) - step(i)
      tmp(i) = x1
      call chifunc(4, deri, y1, tmp, 0)

      y2 = 0.
      x2 = par(i)
      tmp(i) = x2
      call chifunc(4, deri, y2, tmp, 0)

      y3 = 0.
      x3 = par(i) + step(i)
      tmp(i) = x3
      call chifunc(4, deri, y3, tmp, 0)

      y12 = y1 - y2
      y23 = y2 - y3
      y31 = y3 - y1

      newx = (y12*x3**2 + y23*x1**2 + y31*x2**2) / 2.0 /
     $       (y12*x3    + y23*x1    + y31*x2)

      if ( i.eq.1 ) then
         print 901, i, newx-par(i)
 901     format('MYMINI Moving par(', i1, ') ', f10.5)
      elseif ( i.eq.2 ) then
         print 902, i, newx-par(i)
 902     format('MYMINI Moving par(', i1, ')            ', f10.5)
      elseif ( i.eq.3 ) then
         print 903, i, newx-par(i)
 903     format('MYMINI Moving par(', i1, ')                       ',
     $          f10.5)
      elseif ( i.eq.4 ) then
         print 904, i, newx-par(i)
 904     format('MYMINI Moving par(', i1,
     $          ')                                  ', f10.5)
      endif

      step(i) = 3.*abs(newx-par(i))
      par(i) = newx

      return
      end


C          print *, 'MATH Show[ListPlot[{{', x1, ',', y1, '},'
C          print *, 'MATH                {', x2, ',', y2, '},'
C          print *, 'MATH                {', x3, ',', y3, '}}, '
C          print *, 'MATH        DisplayFunction -> Identity],'
C          print *, 'MATH      Graphics[{Line[{{'
C          print *, 'MATH ', newx, ',60},{', newx, ',70}}]}],'
C          print *, 'MATH      DisplayFunction -> $DisplayFunction];'
