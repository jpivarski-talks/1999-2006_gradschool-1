      function refit(x)
      common/pawpar/par(5)
      real g1, g2

      g1 = 0.8*exp(-(x-par(6))**2/2./par(4)**2)/sqrt(6.28318)*par(4)
      g2 = 0.2*exp(-(x-par(6))**2/2./par(5)**2)/sqrt(6.28318)*par(5)

      refit = par(1) + x*par(2) + par(3)*(g1 + g2)

      return
      end



