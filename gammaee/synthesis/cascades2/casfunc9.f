      function casfunc9(x)
      common/pawpar/par(3)

      casfunc9 = -0.21139165885844988*x + 0.01117158214919767*x**2

      casfunc9 = par(3)*(1. + casfunc9)
      casfunc9 = casfunc9 + par(2)*(1 - 0.10572660610042615*x)
      casfunc9 = casfunc9 + par(1)

      return
      end
