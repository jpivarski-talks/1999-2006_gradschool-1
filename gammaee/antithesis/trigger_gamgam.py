execfile("utilities.py")

tmprunlist = []
for r in initialrunlist:
  if r not in mybadruns:
    tmprunlist.append(r)

tmprunlist = []
corrections = []
corrections_err = []
# simple_corrections = []
# simple_corrections_err = []
for r in initialrunlist:
  if r not in mybadruns:
    therun = getdb(r)
    before = therun.gamgam_cotT_cut.sum()
    efficiency = therun.gamgam_cotTnumer.divide_by_superset(therun.gamgam_cotTdenom)
    for i, d in enumerate(therun.gamgam_cotTdenom):
      if d == 0:
        efficiency.vals[i] = 1.
    after = (therun.gamgam_cotT_cut / efficiency).sum()
    tmprunlist.append(r)
    q = 1. * before / after
    corrections.append(q)
    corrections_err.append(sqrt(q*(1.-q)/therun.gamgam_cotTdenom.sum()))
#     q = 1. * therun.gamgam_cotTnumer.sum() / therun.gamgam_cotTdenom.sum()
#     simple_corrections.append(q)
#     simple_corrections_err.append(sqrt(q*(1.-q)/therun.gamgam_cotTdenom.sum()))

p = biggles.FramedPlot()
p.add(biggles.Points(tmprunlist, corrections, symboltype="filled circle", symbolsize=0.5))
p.add(biggles.SymmetricErrorBarsY(tmprunlist, corrections, corrections_err))
p.show()

tmprunlist2 = []
corrections2 = []
corrections_err2 = []
for r, c, e in zip(tmprunlist, corrections, corrections_err):
  if r not in [121710, 121930, 121944, 121954, 123884]:
    tmprunlist2.append(r)
    corrections2.append(c)
    corrections_err2.append(e)

p = biggles.FramedPlot()
p.add(biggles.Points(tmprunlist2, Numeric.array(corrections2)*100, symboltype="filled circle", symbolsize=1))
p.add(biggles.SymmetricErrorBarsY(tmprunlist2, Numeric.array(corrections2)*100, Numeric.array(corrections_err2)*100))
p.add(biggles.LineX(123102.5, type="dotted"))
p.add(biggles.LineX(125651.5, type="dotted"))
p.add(biggles.LineY(100))
p.aspect_ratio = 0.4
p.x1.label = "Run number"
p.y1.label = "BarrelBhabha efficiency for gamgams"
p.yrange = 98.9, 100.1
p.xrange = 121000, 131000
p.show()
p.write_eps("plots/trigger_gamgam_vrun.eps")







for r, c in zip(tmprunlist, corrections):
  if c < 0.99:
    print r, c, runsummary[r].res, runsummary[r].kind
121710 0.989724921787 3 p  -6.41549060321
121930 0.982378406894 3 p  -12.6996837966  # calling trigger experts
121944 0.988335932978 3 p  -8.10691359604
121954 0.944052898991 3 p  -21.7970091163  # bands in phi vs theta: it's gone!
123884 0.98489669117 1 p   -9.42378233268  # trigger problems, "bad run"
# I'm going to assume that all of these are bad.


p = getdb(121954).gamgam_cotTdenom.plot()
p.add(getdb(121954).gamgam_cotTnumer.steps(linetype="dotted"))
p.show()
getdb(121954).gamgam_cotT_cut.plot().show()


p = getdb(initialrunlist[0]).bhabha_cotTdenom.plot()
p.add(getdb(initialrunlist[0]).bhabha_cotTnumer.steps(linetype="dotted"))
p.show()
p = getdb(initialrunlist[0]).gamgam_cotTdenom.plot()
p.add(getdb(initialrunlist[0]).gamgam_cotTnumer.steps(linetype="dotted"))
p.show()
getdb(initialrunlist[0]).gamgam_cotT_cut.plot().show()

print getdb(initialrunlist[0]).bhabha_cotTdenom.sum(), getdb(initialrunlist[0]).gamgam_cotT_cut.sum()


for r in initialrunlist:
  if r not in mybadruns:
    therun = getdb(r)
    p = therun.bhabha_cotTdenom.plot()
    p.add(therun.gamgam_cotTdenom.steps(linetype="dotted"))
    p.show()
    raw_input(r)








themean = jt.wmean(zip(corrections, corrections_err))[0]

for r, c, e in zip(tmprunlist, corrections, corrections_err):
  if not e==0. and not -5 < (c-themean)/e < 5:
    print r, c, (c-themean)/e, runsummary[r].res, runsummary[r].kind
# Yes, the ones above are the only ones you need to worry about.



histo = hist.h1(100, -5., 5.)
for c, e in zip(corrections, corrections_err):
  histo.fill((c-themean)/e)
histo.rootn()
histo.plot().show()

def histochi(a, m, s):
  binwide = histo.frame[1] - histo.frame[0]
  chi = 0.
  xes = []
  yes = []
  for lowx, v, e in zip(histo.frame, histo.vals, histo.errs):
    x = lowx + binwide / 2.
    gauss = a * exp(-(x-m)**2/2./s**2)/sqrt(2.*pi)/s
    if e > 0:
      chi += (gauss - v)**2/e**2
    xes.append(x)
    yes.append(gauss)
  p = histo.plot()
  p.add(biggles.Curve(xes, yes))
  p.x1.label = r"Sigmas away from mean efficiency of 99.67%"
  hist.addinfobox(p, [["Gaussian width", "%.3g" % s], ["Overflow", histo.overflow], ["Underflow", histo.underflow], ["Total", len(tmprunlist)]], width=0.40, numformat="%g")
  p.aspect_ratio = 0.6
  p.write_eps("plots/trigger_gamgam_hist.eps")
  p.show()
  return chi
# from minuit import *
# m = Minuit(histochi, start=[290., -0.2, 1.2], step=[100., 0.01, 0.1])
# m.migrad()
# print m.values
# print m.fval
# print histo.underflow
histochi(288.58272841918921, -0.094867287985651472, 1.1422822640086117)










p = biggles.FramedPlot()
p.add(biggles.Points(tmprunlist, simple_corrections, symboltype="filled circle"))
p.add(biggles.SymmetricErrorBarsY(tmprunlist, simple_corrections, simple_corrections_err))
p.show()












# now with bhabhish cotT

tmprunlist = []
corrections = []
corrections_err = []
for r in initialrunlist:
  if r not in mybadruns:
    therun = getdb(r)
    before = therun.gamgam_cotT_cut.sum()
    efficiency = therun.bhabha_cotTnumer.divide_by_superset(therun.bhabha_cotTdenom)
    for i, d in enumerate(therun.bhabha_cotTdenom):
      if d == 0:
        efficiency.vals[i] = 1.
    after = (therun.gamgam_cotT_cut / efficiency).sum()
    tmprunlist.append(r)
    q = 1. * before / after
    corrections.append(q)
    corrections_err.append(sqrt(q*(1.-q)/therun.bhabha_cotTdenom.sum()))

p = biggles.FramedPlot()
p.add(biggles.Points(tmprunlist, corrections, symboltype="filled circle", symbolsize=1))
p.add(biggles.SymmetricErrorBarsY(tmprunlist, corrections, corrections_err))
p.aspect_ratio = 0.4
p.x1.label = "Run number"
p.y1.label = "BarrelBhabha efficiency"
p.show()
p.write_eps("plots/trigger_gamgam_vrun.eps")

themean = jt.wmean(zip(corrections, corrections_err))[0]




histo = hist.h1(100, -5., 5.)
for c, e in zip(corrections, corrections_err):
  if e == 0.:
    histo.fill(7.)
  else:
    histo.fill((c-themean)/e)
histo.rootn()
histo.plot().show()

def histochi(a, m, s):
  binwide = histo.frame[1] - histo.frame[0]
  chi = 0.
  xes = []
  yes = []
  for lowx, v, e in zip(histo.frame, histo.vals, histo.errs):
    x = lowx + binwide / 2.
    gauss = a * exp(-(x-m)**2/2./s**2)/sqrt(2.*pi)/s
    if e > 0:
      chi += (gauss - v)**2/e**2
    xes.append(x)
    yes.append(gauss)
  p = histo.plot()
  p.add(biggles.Curve(xes, yes))
  p.x1.label = r"Sigmas away from mean efficiency of 99.76%"
  hist.addinfobox(p, [["Gaussian width", "%.3g" % s], ["Overflow", histo.overflow], ["Underflow", histo.underflow], ["Total", len(tmprunlist)]], width=0.40, numformat="%g")
  p.aspect_ratio = 0.6
  p.write_eps("plots/trigger_gamgam_hist.eps")
  p.show()
  return chi
# from minuit import *
# m = Minuit(histochi, start=[290., -0.2, 1.2], step=[100., 0.01, 0.1])
# m.migrad()
print m.values
print m.fval
# print histo.underflow
histochi(287.73127919292023, -0.14275609978218731, 1.1244953359121559)
