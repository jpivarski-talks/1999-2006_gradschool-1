      function casf(x)
      real ygaus
      common/pawpar/par(3)

      casf = par(1) * (42272.9 - 4407.91 * par(2) *x)

      ygaus = 0.0005 * exp(-(x-9.4633)**2/2.0/0.0015252**2)

      casf = casf + par(3) * ygaus / sqrt(2.*3.1415926) / 0.0015252

      return
      end
