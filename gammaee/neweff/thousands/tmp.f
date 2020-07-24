      function tmp(x)
      common/pawpar/par(6)

      tmp = par(4) + par(5)*exp(-x**2/par(6))
      tmp = tmp + par(1)*exp(-(x-par(2))**2/par(3)**2)

      return
      end
