execfile("utilities.py")

tmprunlist = []
ratio = []
ratio_err = []
for r in initialrunlist:
  if r not in mybadruns:
    therun = getdb(r)

    tmprunlist.append(r)
    q = 1.*therun.bhabhatwotrack/therun.mupairtwotrack
    ratio.append(q)
    ratio_err.append(q*sqrt(1./therun.bhabhatwotrack + 1./therun.mupairtwotrack))

p = biggles.FramedPlot()
p.add(biggles.SymmetricErrorBarsY(tmprunlist, ratio, ratio_err))
p.add(biggles.Points(tmprunlist, ratio, symboltype="filled circle"))
p.yrange = -10, 50
p.show()

