ccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc
ccccc program fit ccccccccccccccccccccccccccccccccccccccccccccccccc
ccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc
      program fit
      implicit none
      
c     common block
      common /criteria/low, high, gam, yint, phi,
     $     phofrac, j1t, j2t, y1t, y2t,
     $     en(2000), xs(2000), err2(2000),
     $     npoints, res
      real*8 low, high, gam, yint, phi
      real*8 phofrac, j1t, j2t, y1t, y2t
      real*8 en, xs, err2
      integer npoints, res

c     functions
      external gbwkf
      real gbwkf
      external fitfunc
      real fitfunc
      external chifunc
      real chifunc

c     variables for reading data
      real thisen, thisXS, thisErr

c     variables for scan parameters
      real*8 darea, dmass, dwide, dback
      real*8 area, mass, wide, back
      real*8 chi
      real*8 deri(4), dpar(4)

c     variables for printing out fit results as a curve
      real*8 x
      integer i

c     read in formatted data: energy in COM MeV, hadronic XS in nb, err in XS
      npoints = 0
 100  read (*, *, end=200) thisen, thisXS, thisErr
      npoints = npoints + 1
      en(npoints)   = thisen
      xs(npoints)   = thisXS
      err2(npoints) = thisErr**2
      goto 100

c     set up the other parameters based on a guess about the resonance
 200  if ( en(1) .gt. 9428. .and. en(1) .lt. 9564. ) then
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
         phofrac = 0.07D0
         j1t = 1.D0
         j2t = 1.D0
         y1t = 1.D0
         y2t = 1.D0

C          darea = 261.08D0
C          dmass = 9460.3D0
C          dwide = 3.7873D0
C          dback = 3.364647D0
         darea = 282.06D0
         dmass = 9460.241D0
         dwide = 3.878D0
         dback = 4.188D0

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
         phofrac = 0.07D0
         j1t = 1.D0
         j2t = 1.D0
         y1t = 1.D0
         y2t = 1.D0

         darea = 112.43D0
         dmass = 10024.6D0
         dwide = 4.1504D0
         dback = 3.463134D0

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
         phi = 45.0D0
         phofrac = 0.07D0
         j1t = 1.D0
         j2t = 1.D0
         y1t = 1.D0
         y2t = 1.D0

C          darea = 77.2389619673D0
C          dmass = 10357.9759316115D0
C          dwide = 4.6910300462D0
C          dback = 4.2916222779D0
         darea = 76.3D0
         dmass = 10358.0166D0
         dwide = 4.697D0
         dback = 4.245D0

      else
         print *, 'First data point is way off--- maybe you forgot to ',
     $        'convert to COM MeV?'
         stop
      end if

      if ( res .gt. 0 ) then
         deri(1) = 0
         deri(2) = 0
         deri(3) = 0
         deri(4) = 0
         
C          do mass=(dmass-0.1),(dmass+0.1),(0.2/30.)
C             do wide=(dwide-0.1),(dwide+0.1),(0.2/30.)
C                do area=(darea-2.0),(darea+2.0),(4.0/30.)
C                   do back=(dback-0.02),(dback+0.02),(0.04/30.)
C                      chi = 0
C                      dpar(1) = area
C                      dpar(2) = mass
C                      dpar(3) = wide
C                      dpar(4) = back
C                      call chifunc(4, deri, chi, dpar, 0)
C                      print 400, area, mass, wide, back, chi
C  400                 format('SCAN ', f20.10, ' ', f20.10, ' ', 
C      $                      f20.10, ' ', f20.10, ' ', f20.10)
C                   end do
C                end do
C             end do
C          end do

 400     format('{', f20.10, ', ', f20.10, '},')

         darea = 282.4988536003D0
         dmass = 9460.2458262984D0
         dwide = 3.8832847206D0
         dback = 4.2280353296D0

         area = darea
         mass = dmass
         wide = dwide
         back = dback

         do area=(darea-1.48),(darea+1.48),(1.48/30.)
            chi = 0
            dpar(1) = area
            dpar(2) = mass
            dpar(3) = wide
            dpar(4) = back
            call chifunc(4, deri, chi, dpar, 0)
            print 400, area, chi
         end do

         print *, ' '
         do mass=(dmass-0.026),(dmass+0.026),(0.026/30.)
            chi = 0
            dpar(1) = area
            dpar(2) = mass
            dpar(3) = wide
            dpar(4) = back
            call chifunc(4, deri, chi, dpar, 0)
            print 400, mass, chi
         end do

         print *, ' '
         do wide=(dwide-0.021),(dwide+0.021),(0.021/30.)
            chi = 0
            dpar(1) = area
            dpar(2) = mass
            dpar(3) = wide
            dpar(4) = back
            call chifunc(4, deri, chi, dpar, 0)
            print 400, wide, chi
         end do

         print *, ' '
         do back=(dback-0.013),(dback+0.013),(0.013/30.)
            chi = 0
            dpar(1) = area
            dpar(2) = mass
            dpar(3) = wide
            dpar(4) = back
            call chifunc(4, deri, chi, dpar, 0)
            print 400, back, chi
         end do

      endif

      stop
      end

ccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc
ccccc function fitfunc cccccccccccccccccccccccccccccccccccccccccccc
ccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc
      function fitfunc(x, area, mass, wide, back)
      implicit none

c     formal parameters
      double precision x, area, mass, wide, back
      double precision fitfunc

c     common block
      common /criteria/low, high, gam, yint, phi,
     $     phofrac, j1t, j2t, y1t, y2t,
     $     en(2000), xs(2000), err2(2000),
     $     npoints, res
      real*8 low, high, gam, yint, phi
      real*8 phofrac, j1t, j2t, y1t, y2t
      real*8 en, xs, err2
      integer npoints, res

c     functions
      external gbwkf
      real*8 gbwkf

c     parts of the theory expression
      real*8 peak, sInv, photon, tails

      peak = area * gbwkf(mass, gam, wide, yint, phi, x - mass)
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
      subroutine chifunc(npar, deri, dval, dpar, iflag)
      implicit none

c     formal parameters
      integer npar
      real*8 deri(*), dval, dpar(*)
      integer iflag

c     common block
      common /criteria/low, high, gam, yint, phi,
     $     phofrac, j1t, j2t, y1t, y2t,
     $     en(2000), xs(2000), err2(2000),
     $     npoints, res
      real*8 low, high, gam, yint, phi
      real*8 phofrac, j1t, j2t, y1t, y2t
      real*8 en, xs, err2
      integer npoints, res

c     functions
      external fitfunc
      real fitfunc

c     looping variable
      integer i

      dval = 0.
      do 700 i = 1, npoints
         dval = dval + (xs(i) -
     $        fitfunc(en(i), dpar(1), dpar(2), dpar(3), dpar(4)))**2
     $        / err2(i)

 700  continue

      return
      end
