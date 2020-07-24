      function cas2f(x)
      common/pawpar/par(3)

      cas2f = (x-9.46030)**2 - 0.02**2

      cas2f = par(1) + par(2)*(x-9.46030) + par(3)*cas2f

      return
      end
