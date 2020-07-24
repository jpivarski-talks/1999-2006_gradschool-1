ccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc
ccccc program spitout ccccccccccccccccccccccccccccccccccccccccccccc
ccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc
      program spitout
      implicit none
      
      external gbwkf
      real gbwkf

      real*8 gam, enMeV
      real*8 darea, dmass, dwide, dback
      real*8 backgr, theory

      real*8 x
      real*8 rm, wspread, hc

 100  read ( *, * ) darea, dmass, dwide, dback, gam, enMeV

      rm = dmass * 1000.d0        ! mass in MeV
      wspread = dwide             ! beam energy spread in MeV
      
      hc = enMeV - rm
      backgr = dback * 9430.d0**2 / enMeV**2
      theory = darea * gbwkf( rm, gam, wspread, hc ) + backgr

      print *, theory

c     Y(1s) parameters
c      darea = 261.08D0
c      dmass = 9.4603D0
c      dwide = 3.7873D0
c      dback = 3.6179D0
c      gam = 52.5 / 1000.
c      low = 9428
c      high = 9564

c     Y(2s) parameters
c      darea = 112.43D0
c      dmass = 10.0246D0
c      dwide = 4.1504D0
c      dback = 3.7238D0
c      gam = 44 / 1000.
c      low = 9994
c      high = 10088

c     Y(3s) parameters
c      darea = 77.05870D0
c      dmass = 10.35820D0
c      dwide = 4.668636D0
c      dback = 3.844471D0
c      gam = 26.3 / 1000.
c      low = 10325
c      high = 10403

      stop
      end

