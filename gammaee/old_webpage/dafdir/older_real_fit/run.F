      program run
      external fcn
      integer icondn
      character chnam(4)
      real val, error, bnd1, bnd2
      integer ivarbl
      real eplus, eminus, eparab, globcc
      real emat(4,4)
      
      call mninit( 5, 6, 7 )
      call mnseti( 'Real Kuraev-Fadin Fit' )
      call mnparm( 1, 'area', 278.6,   2.,    0., 0. )
      call mnparm( 2, 'mass',   9.46,  0.001, 0., 0. )
      call mnparm( 3, 'wide',   3.816, 0.1,   0., 0. )
      call mnparm( 4, 'back',   2.931, 0.1,   0., 0. )

      call mncomd( fcn, 'migrad', icondn, 0 )
      call mncomd( fcn, 'minos', icondn, 0 )

      call mnpout( 1, chnam, val, error, bnd1, bnd2, ivarbl )
      call mnerrs( 1, eplus, eminus, eparab, globcc )
      call mnpout( 2, chnam, val, error, bnd1, bnd2, ivarbl )
      call mnpout( 3, chnam, val, error, bnd1, bnd2, ivarbl )
      call mnpout( 4, chnam, val, error, bnd1, bnd2, ivarbl )

      call mnemat( emat, 4 )

!       print *, rfrsin(0.1)

      stop
      end

!      real hc
!      do 100, hc = -20., 30., 1.
!         print *, hc, GBWKF(10000.,0.040,4.,hc)
! 100  continue

      subroutine fcn( npar, grad, fval, xval, iflag, futil )
      implicit double precision (A-H,O-Z)
      dimension grad(*), xval(*)
      integer i
      
      if ( iflag .eq. 1 ) then
         ! read input data
      endif

      do 100, i = 1, npar
         fval = fval + xval(i)
 100  continue

      if ( iflag .eq. 3 ) then
         ! output fitted data
      endif

      return
      end
