ccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc
ccccc program resid ccccccccccccccccccccccccccccccccccccccccccccccc
ccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc
      program resid
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

      integer      mode

      double precision area, mass, wide, back
      double precision earea, emass, ewide, eback
      double precision bnd1, bnd2
      integer ivarbl

      npoints = 0
      read ( *, * ) area, mass, wide, back, gam, mode
 100  read ( *, *, end=300 ) energy, hadXC, hadXCerr
      
      npoints          = npoints + 1
      enMeV(npoints)   = energy * 1000.
      hxc(npoints)     = hadXC
      hxcerr2(npoints) = hadXCerr**2
c      type*, npoints,enMeV(npoints),hxc(npoints),hxcerr2(npoints)
      goto 100

 300  call printout( area, mass, wide, back, mode )

      stop
      end

ccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc
ccccc subroutine printout ccccccccccccccccccccccccccccccccccccccccc
ccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc
      subroutine printout( area, mass, wide, back, mode )
      implicit none
      
      external gbwkf
      real*8 gbwkf

      common /datapoints/low, high, gam,
     $                   enMeV(1000), hxc(1000), hxcerr2(1000),npoints
      real*8 low, high, gam, enMeV, hxc, hxcerr2
      integer npoints

      integer          i, lun
      double precision area, mass, wide, back

      integer          mode

      real*8 x, backgr, theory

      real*8 rm, wspread, hc

      data lun/15/

      rm = mass * 1000.d0         ! mass in MeV
      wspread = wide              ! beam energy spread in MeV
     
      do 500, i = 1, npoints
         hc = enMeV(i) - rm
         backgr = back * 9430.**2 / enMeV(i)**2
         theory = area * gbwkf( rm, gam, wspread, hc ) + backgr
         if ( mode .eq. 1 ) then
            print *, enMeV(i), (hxc(i) - theory)/sqrt(hxcerr2(i))
         else
            print *, enMeV(i), hxc(i) - theory, sqrt(hxcerr2(i))
         endif
c         print *, enMeV(i), hxc(i) - theory, sqrt(hxcerr2(i)),
c     2            (hxc(i) - theory)/sqrt(hxcerr2(i))

 500  continue

      return
      end
