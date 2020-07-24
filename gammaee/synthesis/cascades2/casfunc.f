      function casfunc(x)
      common/pawpar/par(3)

      casfunc = par(3)*(x**2-18.92233477371051*x+89.51347812358851)
      casfunc = casfunc + par(2)*(x-9.458357142857055)
      casfunc = casfunc + par(1)

      return
      end
