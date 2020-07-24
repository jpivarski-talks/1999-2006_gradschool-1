

      subroutine sortm( radsort, row, col, npos )
      implicit none

      double precision radsort(*)
      integer row, col, npos

      integer i,j

      call sortd( radsort, row, col, npos )

      return
      end
