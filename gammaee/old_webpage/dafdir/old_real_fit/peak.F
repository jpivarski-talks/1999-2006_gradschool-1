ccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc
ccccc program peak cccccccccccccccccccccccccccccccccccccccccccccccc
ccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc
      program peak
      implicit none
      
      external gbwkf
      real gbwkf
      real func

      double precision area, mass, wide, back, gam, epsilon
      double precision low, high, middle, flow, fhigh, fmiddle
      integer n, i

      epsilon = 0.0000001

      read (*, *) n, area, mass, wide, back

      if ( n .eq. 1 ) then
         gam = 52.5 / 1000.
         low = 9428.
         high = 9564.
      elseif ( n .eq. 2 ) then
         gam = 44 / 1000.
         low = 9994.
         high = 10088.         
      elseif ( n .eq. 3 ) then
         gam = 26.3 / 1000.
         low = 10325.
         high = 10403.
      else
         print *, 'Ack!'
         print *, 'Pffft!'
         print *, 'Gaulk! Bpbpbpblllll...'
         print *, ' '
         print *, 'You killed it! You... you...! How could you?!?'
         stop
      endif

      flow = func(low, area, mass, wide, back, gam, epsilon)
      fhigh = func(high, area, mass, wide, back, gam, epsilon)

      if ( flow * fmiddle .gt. 0 ) then
         print *, 'Not straddling zero! Ack pffft!'
         stop
      endif

 100  middle = (high + low) / 2.
      fmiddle = func(middle, area, mass, wide, back, gam, epsilon)
      
c      print *, low, middle, high
c      print *, flow, fmiddle, fhigh
c      print *, ' '

      if ( flow * fmiddle .lt. 0. ) then
         high = middle
         fhigh = fmiddle
      elseif ( fmiddle * fhigh .lt. 0 ) then
         low = middle
         flow = fmiddle
      endif
      
      if ( fmiddle .ne. 0.  .and.  high - low .gt. 10. * epsilon )
     $   goto 100

      write (unit=*, fmt='(f20.6,a)'), middle, ' MeV'

      stop
      end

ccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc
ccccc function func ccccccccccccccccccccccccccccccccccccccccccccccc
ccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc
      function func( x, area, mass, wide, back, gam, epsilon )
      implicit none
      
      external gbwkf
      real*8 gbwkf

      double precision x, area, mass, wide, back, gam, epsilon
      double precision backgr, theo1, theo2
      double precision rm, wspread, hc
      real func

      rm = mass * 1000.d0         ! mass in MeV
      wspread = wide              ! beam energy spread in MeV
     
      hc = x - rm
      backgr = back * 9430.**2 / x**2
      theo1 = area * gbwkf(rm, gam, wspread, hc) + backgr

      hc = hc + epsilon
      theo2 = area * gbwkf(rm, gam, wspread, hc) + backgr

      func = (theo1 - theo2)    ! / epsilon  (I only use the signs, so this
                                ! doesn't have to be a proper derivative.)
      return
      end
