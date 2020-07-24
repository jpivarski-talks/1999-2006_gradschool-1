      function caspeak(x)
      common/pawpar/par(3)

      caspeak = exp(-(x-9.4633)**2/2/0.0014**2)
      caspeak = par(1) * caspeak / sqrt(2*3.1415926)/0.0014
      caspeak = caspeak + par(2) + par(3)*x

      return
      end
