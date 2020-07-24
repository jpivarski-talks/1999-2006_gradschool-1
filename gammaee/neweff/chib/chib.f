      function chib(x)
      common/pawpar/par(8)

      a1 = par(1) * 0.13759E-01 / 22.
      a2 = par(2) * 0.13759E-01 / 22.
      a3 = par(3) * 0.13759E-01 / 22.

      chib =        a1 * exp(-(x-0.11066)**2/2./par(4))/2.507/par(4)
      chib = chib + a2 * exp(-(x-0.13056)**2/2./par(5))/2.507/par(5)
      chib = chib + a3 * exp(-(x-0.16336)**2/2./par(6))/2.507/par(6)
      chib = chib + par(7) + par(8) * x

      return
      end
