from __future__ import division
from minuit import *
import biggles, Numeric, cPickle as pickle, gbwkf, gbwkftau, jt

scandef_order = ["jan16", "jan30", "feb06", "feb13", "feb20", "feb27", "mar06", "mar13", "apr03", "apr08", "apr09", "apr10", "may29", "jun11", "jun12", "jul10", "jul24", "aug07", "nov28", "dec05", "dec12", "dec19", "dec26", "jan02", "jan09"]
scanen = pickle.load(open("/home/mccann/antithesis/scanen.p"))
scancs = pickle.load(open("/home/mccann/antithesis/scancs.p"))
scancs_err = pickle.load(open("/home/mccann/antithesis/scancs_err.p"))

scanu1s = ["jan16", "jan30", "feb06", "feb13", "feb20", "feb27", "mar06", "mar13", "apr03", "apr08", "apr09", "apr10"]
scanu2s = ["may29", "jun11", "jun12", "jul10", "jul24", "aug07"]
scanu3s = ["nov28", "dec05", "dec12", "dec19", "dec26", "jan02", "jan09"]

def y1sfunc(area, mass, wide, back, en):
  had = area * gbwkf.gbwkf(mass, 0.053, wide, 0.018, 0., en*2000. - mass)
  tau = area * (0.57 * 0.0267) * gbwkftau.gbwkf(mass, 0.053, wide, 0.20, 0., en*2000. - mass)
  cont = back * 4.717**2 / en**2
  return had + tau + cont

def y2sfunc(area, mass, wide, back, en):
  had = area * gbwkf.gbwkf(mass, 0.043, wide, 0.018, 0., en*2000. - mass)
  tau = area * (0.57 * 0.017) * gbwkftau.gbwkf(mass, 0.053, wide, 0.37, 0., en*2000. - mass)
  cont = back * 4.717**2 / en**2
  return had + tau + cont

def y3sfunc(area, mass, wide, back, en):
  had = area * gbwkf.gbwkf(mass, 0.0263, wide, 0.018, 0., en*2000. - mass)
  tau = area * (0.57 * 0.0239) * gbwkftau.gbwkf(mass, 0.053, wide, 0.27, 0., en*2000. - mass)
  cont = back * 4.717**2 / en**2
  return had + tau + cont

def plotoverlay(f, s, area, mass, wide, back, label=True, title=None):
  p = biggles.FramedPlot()
  p.add(biggles.Points(Numeric.array(scanen[s])*2000., scancs[s], symboltype="filled circle", symbolsize=0.7))
  p.add(biggles.SymmetricErrorBarsY(Numeric.array(scanen[s])*2000., scancs[s], scancs_err[s]))
  xlow = min(scanen[s])*2000. - 5.
  xhigh = max(scanen[s])*2000. + 5.
  thex = Numeric.arange(xlow, xhigh, (xhigh - xlow)/100.)
  they = Numeric.arange(xlow, xhigh, (xhigh - xlow)/100.)
  for i, x in enumerate(thex):
    they[i] = f(area, mass, wide, back, x/2000.)
  p.add(biggles.Curve(thex, they))
  p.xrange = xlow, xhigh
  p.yrange = 0., max(scancs[s]) * 1.2
  if label:
    p.x1.label = r"$E_{COM}$ in MeV"
    p.y1.label = "Relative Hadronic Cross-section"
  else:
    p.x1.draw_ticklabels = 0
    p.y1.draw_ticklabels = 0
  if title != None:
    p.x2.label = title
  return p  

def chi2(f, s, area, mass, wide, back, showit=False):
  c = 0.
  for en, cs, cs_err in zip(scanen[s], scancs[s], scancs_err[s]):
    c += (cs - f(area, mass, wide, back, en))**2 / cs_err**2
  if showit:
    plotoverlay(f, s, area, mass, wide, back, True).show()
  return c

chi2(y1sfunc, "jan30", 13.85, 9459.73, 3.88, 0.34, showit=True)
chi2(y2sfunc, "jun12", 5.35, 10024.34, 3.98, 0.35, showit=True)
chi2(y3sfunc, "nov28", 3.72, 10357.86, 4.95, 0.36, showit=True)

scanfit = {}
for s in scanu1s:
  scanfit[s] = Minuit(lambda area, mass, wide, back: chi2(y1sfunc, s, area, mass, wide, back), start=[13.85, 9459.73, 3.88, 0.34])
  scanfit[s].migrad()
  a, m, w, b = scanfit[s].values
  plotoverlay(y3sfunc, s, a, m, w, b).show()
  print "reduced chi2", scanfit[s].fval/(len(scanen[s])-4), "precision", scanfit[s].errors[0]/scanfit[s].values[0]*100, "%"

for s in scanu2s:
  scanfit[s] = Minuit(lambda area, mass, wide, back: chi2(y2sfunc, s, area, mass, wide, back), start=[5.35, 10024.34, 3.98, 0.35])
  scanfit[s].migrad()
  a, m, w, b = scanfit[s].values
  plotoverlay(y3sfunc, s, a, m, w, b).show()
  print "reduced chi2", scanfit[s].fval/(len(scanen[s])-4), "precision", scanfit[s].errors[0]/scanfit[s].values[0]*100, "%"

for s in scanu3s:
  m = 10358.131397318795
  if s == "dec05": m = 10359.4784845
  if s == "dec19": m = 10357.5457012
  scanfit[s] = Minuit(lambda area, mass, wide, back: chi2(y3sfunc, s, area, mass, wide, back), start=[3.4897, m, 4.317, 0.3497])
  scanfit[s].migrad()
  a, m, w, b = scanfit[s].values
  plotoverlay(y3sfunc, s, a, m, w, b).show()
  print "reduced chi2", scanfit[s].fval/(len(scanen[s])-4), "precision", scanfit[s].errors[0]/scanfit[s].values[0]*100, "%"



areas = []
for s in scanu1s:
  areas.append((scanfit[s].values[0], scanfit[s].errors[0]))
print jt.wmean(areas)[1]/jt.wmean(areas)[0]*100.

areas = []
for s in scanu2s:
  areas.append((scanfit[s].values[0], scanfit[s].errors[0]))
print jt.wmean(areas)[1]/jt.wmean(areas)[0]*100.

areas = []
for s in scanu3s:
  areas.append((scanfit[s].values[0], scanfit[s].errors[0]))
print jt.wmean(areas)[1]/jt.wmean(areas)[0]*100.



p = biggles.Table(5,5)
i = 0
j = 0
for s in scandef_order:
  print s
  a, m, w, b = scanfit[s].values
  if s in scanu1s:
    p[j,i] = plotoverlay(y1sfunc, s, a, m, w, b, label=False, title=s)
  if s in scanu2s:
    p[j,i] = plotoverlay(y2sfunc, s, a, m, w, b, label=False, title=s)
  if s in scanu3s:
    p[j,i] = plotoverlay(y3sfunc, s, a, m, w, b, label=False, title=s)
  i += 1
  if i == 5:
    i = 0
    j += 1
p.aspect_ratio = 8./11.5
p.show()
p.write_eps("plots/all25.eps")




for s in scandef_order:
  print "CDF[ChiSquareDistribution["+str(len(scanen[s]) - 4)+"], "+str(scanfit[s].fval)+"],"



def variation(res, par):
  wides = []
  wides_err = []
  scans = scanu1s
  if res == 2: scans = scanu2s
  if res == 3: scans = scanu3s
  for s in scans:
    wides.append(scanfit[s].values[par])
    wides_err.append(scanfit[s].errors[par])
  p = biggles.FramedPlot()
  plotdata(p, range(len(wides)), wides, wides_err, symbolsize=3)
  p.y1.label = "area"
  if par == 1: p.y1.label = "mass"
  if par == 2: p.y1.label = "wide"
  if par == 3: p.y1.label = "back"
  p.x1.draw_ticklabels = 0
  return p

p = biggles.Table(4,3)
for res in range(3):
  for par in range(4):
    p[par, res] = variation(res+1, par)
p.aspect_ratio = 8./11.5
p.show()
p.write_eps("plots/all25.eps")


###################################################

def plotoverlay(f, s, area, mass, wide, back, label=True, title=None):
  p = biggles.FramedPlot()
  p.add(biggles.Points(Numeric.array(allscanen[s])*2000., allscancs[s], symboltype="filled circle", symbolsize=0.7))
  p.add(biggles.SymmetricErrorBarsY(Numeric.array(allscanen[s])*2000., allscancs[s], allscancs_err[s]))
  xlow = min(allscanen[s])*2000. - 5.
  xhigh = max(allscanen[s])*2000. + 5.
  thex = Numeric.arange(xlow, xhigh, (xhigh - xlow)/100.)
  they = Numeric.arange(xlow, xhigh, (xhigh - xlow)/100.)
  for i, x in enumerate(thex):
    they[i] = f(area, mass, wide, back, x/2000.)
  p.add(biggles.Curve(thex, they))
  p.xrange = xlow, xhigh
  p.yrange = 0., max(allscancs[s]) * 1.2
  if label:
    p.x1.label = r"$E_{COM}$ in MeV"
    p.y1.label = "Relative Hadronic Cross-section"
  else:
    p.x1.draw_ticklabels = 0
    p.y1.draw_ticklabels = 0
  if title != None:
    p.x2.label = title
  return p  

def chi2(f, s, area, mass, wide, back, showit=False):
  c = 0.
  for en, cs, cs_err in zip(allscanen[s], allscancs[s], allscancs_err[s]):
    c += (cs - f(area, mass, wide, back, en))**2 / cs_err**2
  if showit:
    plotoverlay(f, s, area, mass, wide, back, True).show()
  return c

allscanfit = {}
for s in ["u1s"]:
  allscanfit[s] = Minuit(lambda area, mass, wide, back: chi2(y1sfunc, s, area, mass, wide, back), start=[13.85, 9459.73, 3.88, 0.14])
  allscanfit[s].migrad()
  a, m, w, b = allscanfit[s].values
  plotoverlay(y3sfunc, s, a, m, w, b).show()
  print "reduced chi2", allscanfit[s].fval/(len(allscanen[s])-4), "precision", allscanfit[s].errors[0]/allscanfit[s].values[0]*100, "%"

for s in ["u2s"]:
  allscanfit[s] = Minuit(lambda area, mass, wide, back: chi2(y2sfunc, s, area, mass, wide, back), start=[5.35, 10024.34, 3.98, 0.14])
  allscanfit[s].migrad()
  a, m, w, b = allscanfit[s].values
  plotoverlay(y3sfunc, s, a, m, w, b).show()
  print "reduced chi2", allscanfit[s].fval/(len(allscanen[s])-4), "precision", allscanfit[s].errors[0]/allscanfit[s].values[0]*100, "%"

for s in ["u3s"]:
  allscanfit[s] = Minuit(lambda area, mass, wide, back: chi2(y3sfunc, s, area, mass, wide, back), start=[3.4, 10358.131397318795, 4.7, 0.15])
  allscanfit[s].migrad()
  a, m, w, b = allscanfit[s].values
  plotoverlay(y3sfunc, s, a, m, w, b).show()
  print "reduced chi2", allscanfit[s].fval/(len(allscanen[s])-4), "precision", allscanfit[s].errors[0]/allscanfit[s].values[0]*100, "%"

def reasonable((low, high), special=False):
  tmp = range(int(round(low, -1)), int(round(high, -1)), int(round((high-low)/5, -1)))
  if special:
    tmp = range(int(round(low, -1)), int(round(high, -1)), int(round((high-low)/4, -1)))
  out = []
  for i in tmp:
    if low < i < high:
      out.append(float(i))
  return out

p = biggles.Table(1,3)
a, m, w, b = allscanfit["u1s"].values
p[0,0] = plotoverlay(y1sfunc, "u1s", a, m, w, b)
p[0,0].yrange = 0, 1
p[0,0].y1.draw_ticklabels = 0
p[0,0].y1.label = ""
p[0,0].x1.ticks = reasonable(p[0,0].xrange)
p[0,0].aspect_ratio = 1
p[0,0].add(biggles.PlotLabel(0.75, 0.8, r"$\Upsilon(1S)$"))
a, m, w, b = allscanfit["u2s"].values
p[0,1] = plotoverlay(y2sfunc, "u2s", a, m, w, b)
p[0,1].yrange = 0, 1
p[0,1].y1.draw_ticklabels = 0
p[0,1].y1.label = ""
p[0,1].x1.ticks = reasonable((p[0,1].xrange[0]-10, p[0,1].xrange[1]+10), special=True)
p[0,1].aspect_ratio = 1
p[0,1].add(biggles.PlotLabel(0.75, 0.8, r"$\Upsilon(2S)$"))
a, m, w, b = allscanfit["u3s"].values
p[0,2] = plotoverlay(y3sfunc, "u3s", a, m, w, b)
p[0,2].yrange = 0, 1
p[0,2].y1.draw_ticklabels = 0
p[0,2].y1.label = ""
p[0,2].x1.ticks = reasonable(p[0,2].xrange)
p[0,2].aspect_ratio = 1
p[0,2].add(biggles.PlotLabel(0.75, 0.8, r"$\Upsilon(3S)$"))
p.aspect_ratio = 0.33
p.show()
p.write_eps("plots/junePTA/onetwothree.eps")





#################################################



print allscanen["u1s"][0], allscancs["u1s"][0]*allscanen["u1s"][0]**2, allscancs_err["u1s"][0]*allscanen["u1s"][0]**2
print allscanen["u2s"][0], allscancs["u2s"][0]*allscanen["u2s"][0]**2, allscancs_err["u2s"][0]*allscanen["u2s"][0]**2
print allscanen["u3s"][0], allscancs["u3s"][0]*allscanen["u3s"][0]**2, allscancs_err["u3s"][0]*allscanen["u3s"][0]**2




