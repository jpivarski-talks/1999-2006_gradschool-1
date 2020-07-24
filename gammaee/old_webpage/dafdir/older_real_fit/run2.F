      program run2
      external GBWKF

      real hc
      do 100, hc = -20., 30., 0.001
         print *, hc, GBWKF(10000.,1.,4.,hc)
 100  continue
      
      stop
      end
