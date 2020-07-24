ccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc
ccccc program plot cccccccccccccccccccccccccccccccccccccccccccccccc
ccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc
      program plot
      implicit none
      
      external gbwkf
      real gbwkf

      integer i
      real    x
      real    backgr, theory
      real    rm, gam, wspread, hc

      real area, mass, wide, back, g, low, high
      read ( *, * ) area, mass, wide, back, g, low, high

      rm = mass * 1000.           ! mass in MeV
      gam = g / 1000.             ! gamma in keV
      wspread = wide              ! beam energy spread in MeV
     
      do 100, x = low, high, (high-low)/1000.
         hc = x - rm
         backgr = back * 9430.**2 / x**2
         theory = area * gbwkf( rm, gam, wspread, hc ) + backgr
         print *, x, theory
 100  continue

      stop
      end
