      function twog(x)
      common/pawpar/par(4)

      if (x.lt.par(2)) then
         twog = par(1) * exp(-(x-par(2))**2/2/par(3))
      else
         twog = par(1) * par(4)**2 / ((x-par(2))**2 + par(4)**2)
      endif

      return
      end
