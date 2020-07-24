ccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc
ccccc program fit ccccccccccccccccccccccccccccccccccccccccccccccccc
ccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc
      program fit
      implicit none
      
      external gbwkf
      real gbwkf

      common /datapoints/low, high, gam,
     $                   enMeV(1000), hxc(1000), hxcerr2(1000),npoints
      real*8  low, high, gam, enMeV, hxc, hxcerr2
      integer npoints      

      character*30     form
      integer          run
      character        type
      real energy, hadXC, hadXCerr

      external chifit

      character*10 chnam
      integer      npar
      integer      ipar
      integer      ierflg
      real*8       darea, dmass, dwide, dback
      real*8       dstep
      real*8       dlo, dhi

      integer      narg, ndim
      parameter    (ndim=10)
      real*8       darg(ndim)

      double precision area, mass, wide, back
      double precision earea, emass, ewide, eback
      double precision bnd1, bnd2
      integer ivarbl

      npoints = 0
 100  read ( *, *, end=300 ) energy, hadXC, hadXCerr
      
      npoints          = npoints + 1
      enMeV(npoints)   = energy * 1000.
      hxc(npoints)     = hadXC
      hxcerr2(npoints) = hadXCerr**2
      type*, npoints,enMeV(npoints),hxc(npoints),hxcerr2(npoints)
      goto 100

 300  call mninit( 6, 6, 6 )
      call mnseti( 'Real Kuraev-Fadin Fit' )

      npar = 4
      
c     Y(1s) parameters
c      darea = 261.08D0
c      dmass = 9.4603D0
c      dwide = 3.7873D0
c      dback = 3.6179D0
c      gam = 52.5 / 1000.
c      low = 9428
c      high = 9564

c     Y(2s) parameters
      darea = 112.43D0
      dmass = 10.0246D0
      dwide = 4.1504D0
      dback = 3.7238D0
      gam = 44 / 1000.
      low = 9994
      high = 10088

c     Y(3s) parameters
c      darea = 77.05870D0
c      dmass = 10.35820D0
c      dwide = 4.668636D0
c      dback = 3.844471D0
c      gam = 26.3 / 1000.
c      low = 10325
c      high = 10403

      ipar = 1
      chnam = 'area'
      dstep = 1.D0
      dlo = 0.D0
      dhi = 0.D0
      call mnparm( ipar, chnam, darea, dstep, dlo, dhi, ierflg )
      if ( ierflg .gt. 0 ) print *, 'parameter ''area'' open failure'
      ipar = 2
      chnam = 'mass'
      dstep = 0.0002D0
      dlo = 0.D0
      dhi = 0.D0
      call mnparm( ipar, chnam, dmass, dstep, dlo, dhi, ierflg )
      if ( ierflg .gt. 0 ) print *, 'parameter ''mass'' open failure'
      ipar = 3
      chnam = 'wide'
      dstep = 0.02D0
      dlo = 0.D0
      dhi = 0.D0
      call mnparm( ipar, chnam, dwide, dstep, dlo, dhi, ierflg )
      if ( ierflg .gt. 0 ) print *, 'parameter ''wide'' open failure'
      ipar = 4
      chnam = 'back'
      dstep = 0.01D0
      dlo = 0.D0
      dhi = 0.D0
      call mnparm( ipar, chnam, dback, dstep, dlo, dhi, ierflg )
      if ( ierflg .gt. 0 ) print *, 'parameter ''back'' open failure'

      area = darea
      mass = dmass
      wide = dwide
      back = dback
      call printout( area, mass, wide, back )

c     set strategy:  2 = willing to expend CPU for precision;
c                    1 = default,
c                    0 = crude but fast
      narg = 1
      darg(1) = 1.
      call mnexcm( chifit, 'SET STRATEGY', darg, narg, ierflg, 0 )
      if ( ierflg.gt.0 ) print *, 'call to SET STRATEGY failed'

c     do the minimization
      narg = 2
      darg(1) = 2000.     ! maximum number of iterations
      darg(2) = 0.03      ! tolerance
      call mnexcm( chifit, 'MINIMIZE', darg, narg, ierflg, 0 )
      if ( ierflg.gt.0 ) print *, 'call to MINIMIZE failed'

c     scan
      narg = 0
c      call mnexcm( chifit, 'SCAN', darg, narg, ierflg, 0 )
c      if ( ierflg.gt.0 ) print *, 'call to SCAN failed'

c     call minos
      narg = 0
c      call mnexcm( chifit, 'MINOS', darg, narg, ierflg, 0 )
c      if ( ierflg.gt.0 ) print *, 'call to MINOS failed'

c     call hesse
      narg = 1
      darg(1) = 2000.     ! maximum number of iterations
c      call mnexcm( chifit, 'HESSE', darg, narg, ierflg, 0 )
c      if ( ierflg.gt.0 ) print *, 'call to HESSE failed'

c     print results
      narg = 0
      call mnexcm( chifit, 'SAVE', darg, narg, ierflg, 0 )
      if ( ierflg.gt.0 ) print *, 'call to SAVE failed'

      narg = 0
      call mnexcm( chifit, 'SHOW CORRELATIONS', darg, narg, ierflg, 0 )
      if ( ierflg.gt.0 ) print *, 'call to SHOW CORRELATIONS failed'

      narg = 0
      call mnexcm( chifit, 'SHOW COVARIANCE', darg, narg, ierflg, 0 )
      if ( ierflg.gt.0 ) print *, 'call to SHOW COVARIANCE failed'

      narg = 0
      call mnexcm( chifit, 'SHOW EIGENVALUES', darg, narg, ierflg, 0 )
      if ( ierflg.gt.0 ) print *, 'call to SHOW EIGENVALUES failed'

      narg = 0
      call mnexcm( chifit, 'SHOW FCNVALUE', darg, narg, ierflg, 0 )
      if ( ierflg.gt.0 ) print *, 'call to SHOW FCNVALUE failed'

      call mnpout( 1, chnam, area, earea, bnd1, bnd2, ivarbl )
      call mnpout( 2, chnam, mass, emass, bnd1, bnd2, ivarbl )
      call mnpout( 3, chnam, wide, ewide, bnd1, bnd2, ivarbl )
      call mnpout( 4, chnam, back, eback, bnd1, bnd2, ivarbl )

      call printout( area, mass, wide, back )

      print *, 'param	area = ', area, ' +/- ', earea, ' MeV nb'
      print *, 'param	mass = ', mass, ' +/- ', emass, ' GeV'
      print *, 'param	wide = ', wide, ' +/- ', ewide, ' MeV'
      print *, 'param	back = ', back, ' +/- ', eback, ' nb'

      stop
      end

ccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc
ccccc subroutine chifit ccccccccccccccccccccccccccccccccccccccccccc
ccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc
      subroutine chifit( npar, deri, dval, dpar, iflag )
      implicit none

      external gbwkf
      real*8 gbwkf

      common /datapoints/low, high, gam,
     $                   enMeV(1000), hxc(1000), hxcerr2(1000),npoints
      real*8 low, high, gam, enMeV, hxc, hxcerr2
      integer npoints      

      integer          npar, iflag
      real*8 deri(*), dpar(*), dval

      integer          i
      real*8 backgr, theory

      real*8 x
      real*8 rm, wspread, hc
      rm = dpar(2) * 1000.d0      ! mass in MeV
      wspread = dpar(3)           ! beam energy spread in MeV

      dval = 0.
      do 400 i = 1, npoints
         hc = enMeV(i) - rm
         backgr = dpar(4) * 9430.d0**2 / enMeV(i)**2
         theory = dpar(1) * gbwkf( rm, gam, wspread, hc ) + backgr
         dval = dval + ( theory - hxc(i) )**2 / hxcerr2(i)

         if (iflag.eq.3)print *, i, theory - hxc(i), enMeV(i),
     /     ( theory - hxc(i) )**2 / hxcerr2(i)
c         print *, 'a: ', enMeV(i), hxc(i), sqrt(hxcerr2(i))
c         print *, 'b: ', enMeV(i), theory
 400  continue

      print 500, dpar(1), dpar(2), dpar(3), dpar(4), dval, npoints
 500  format( 'testat ', f20.10, ' ', f20.10, ' ', f20.10, ' ', f20.10,
     $        ' = ', f20.10, ' / ', i10 )

c      call printout( dpar(1), dpar(2), dpar(3), dpar(4) )

      return
      end

ccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc
ccccc subroutine printout ccccccccccccccccccccccccccccccccccccccccc
ccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc
      subroutine printout( area, mass, wide, back )
      implicit none
      
      external gbwkf
      real*8 gbwkf

      common /datapoints/low, high, gam,
     $                   enMeV(1000), hxc(1000), hxcerr2(1000),npoints
      real*8 low, high, gam, enMeV, hxc, hxcerr2
      integer npoints

      integer          i, lun
      double precision area, mass, wide, back

      real*8 x, backgr, theory

      real*8 rm, wspread, hc

      data lun/15/

      rm = mass * 1000.d0         ! mass in MeV
      wspread = wide              ! beam energy spread in MeV
     
      open(unit=lun,file='expt.dat',form='formatted',status='UNKNOWN')

      print *, 'Writing out experimental points.'
c      low = enMeV(1)
c      high = enMeV(1)
      do 500, i = 1, npoints
         write(lun,*) enMeV(i), hxc(i), sqrt(hxcerr2(i))
c         if ( enMeV(i) .lt. low ) low = enMeV(i)
c         if ( enMeV(i) .gt. high ) high = enMeV(i)
 500  continue

      open(unit=lun,file='theo.dat',form='formatted',status='UNKNOWN')

      print *, 'Writing out theoretical curve.'
      do 600, x = low-3., high+3., (high-low)/1000.
         hc = x - rm
         backgr = back * 9430.**2 / x**2
         theory = area * gbwkf( rm, gam, wspread, hc ) + backgr
         write(lun,*) x, theory
 600  continue

      return
      end
