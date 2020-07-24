execfile("utilities.py")

# in practice, trackless tight (no eltrack) is the same as trackless

# p = biggles.FramedPlot()
# p.add(biggles.Points(Numeric.array(tmprunlist), Numeric.array(trackless_tight) - Numeric.array(trackless), symboltype="filled circle", symbolsize=1))
# p.aspect_ratio = 1
# p.yrange = 
# p.yrange = 0, 0.0025
# p.show()
# for r, tt, t in zip(tmprunlist, trackless_tight, trackless):
#   if tt != t:
#     print r, getdb(r).trackless, getdb(r).trackless_tighten_rawtk


tmprunlist = []
trackless = []
trackless_err = []
# bhamutt = []
# bhamutt_err = []
for r in initialrunlist:
  if r not in mybadruns:
    therun = getdb(r)

    tmprunlist.append(r)

    q = 1.*therun.trackless/therun.trackless_release_rawtk
    trackless.append(q)
    trackless_err.append(sqrt(q*(1.-q)/therun.trackless_release_rawtk))

#     q = 1.*therun.bhabhatwotrack/therun.mupairtwotrack
#     bhamutt.append(q)
#     bhamutt_err.append(q*sqrt(1./therun.bhabhatwotrack + 1./therun.mupairtwotrack))





# p = biggles.FramedPlot()
# p.add(biggles.SymmetricErrorBarsY(tmprunlist, trackless, trackless_err))
# p.aspect_ratio = 0.5
# p.show()

p = biggles.FramedPlot()
p.add(biggles.SymmetricErrorBarsY(tmprunlist, Numeric.array(trackless)*100, Numeric.array(trackless_err)*100))
p.add(biggles.Points(tmprunlist, Numeric.array(trackless)*100, symboltype="filled circle", symbolsize=1))
p.add(biggles.LineX(123102.5, type="dotted"))
p.add(biggles.LineX(125651.5, type="dotted"))
p.aspect_ratio = 0.5
p.yrange = 0, 2.
p.x1.label = r"Run number"
p.y1.label = r"Trackless bhabha fraction (percent)"
p.show()
p.write_eps("plots/runbyrun_trackless.eps")

for r, t, e in zip(tmprunlist, trackless, trackless_err):
  if t > 0.004:
    print r

print jt.wmean(zip(trackless, trackless_err))


gamgam_phib2b = hist.h1(120, -0.3, 0.3)
trackless_phib2b = hist.h1(120, -0.3, 0.3)
tmprunlist = []
bhamutt = []
bhamutt_err = []
for r in initialrunlist:
  if r not in mybadruns:
    therun = getdb(r)
    if r not in [121374, 121379, 121391, 121401, 121408, 122249, 123004, 128310]:
      gamgam_phib2b += therun.gamgam_phib2b
      trackless_phib2b += therun.trackless_phib2b

    tmprunlist.append(r)

    q = 1.*therun.bhabhatwotrack/therun.mupairtwotrack
    bhamutt.append(q)
    bhamutt_err.append(q*sqrt(1./therun.bhabhatwotrack + 1./therun.mupairtwotrack))


gamgam_phib2b2 = hist.h1(60, 0., 0.3)
trackless_phib2b2 = hist.h1(60, 0., 0.3)
tmp = range(60)
tmp.reverse()
tmp.extend(range(60))
for i1, i2 in zip(range(120), tmp):
  gamgam_phib2b2.vals[i2] = gamgam_phib2b.vals[i1]
  trackless_phib2b2.vals[i2] = trackless_phib2b.vals[i1]




p = gamgam_phib2b2.plot()
p.add(((trackless_phib2b2 + 0.001) / 500).steps(linetype="dashed"))
p.add(biggles.LineX(0.04, linetype="dotted"))
p.add(biggles.LineX(0.25, linetype="dotted"))
p.y1.log = 1
p.y1.range = 10, 5e6
p.x1.label = r"$|sin (\phi_1 - \phi_2)|$ for trackless events"
p.aspect_ratio = 0.5
p.show()
p.write_eps("plots/runbyrun_trackless0.eps")

# p = (gamgam_phib2b2 - trackless_phib2b2 / 500).plot()
# p.y1.log = 1
# p.y1.range = 10, 5e6
# p.show()









p = biggles.FramedArray(5,2)
p[0,0].add(getdb(121369).trackless_vstime.stepsfill(color="black"))
p[0,1].add(getdb(121374).trackless_vstime.stepsfill(color="black"))
p[1,0].add(getdb(121379).trackless_vstime.stepsfill(color="black"))
p[1,1].add(getdb(121391).trackless_vstime.stepsfill(color="black"))
p[2,0].add(getdb(121395).trackless_vstime.stepsfill(color="black"))
p[2,1].add(getdb(121401).trackless_vstime.stepsfill(color="black"))
p[3,0].add(getdb(121408).trackless_vstime.stepsfill(color="black"))
p[3,1].add(getdb(122249).trackless_vstime.stepsfill(color="black"))
p[4,0].add(getdb(123004).trackless_vstime.stepsfill(color="black"))
p[4,1].add(getdb(128310).trackless_vstime.stepsfill(color="black"))
p[0,0].add(biggles.LineY(0))
p[0,1].add(biggles.LineY(0))
p[1,0].add(biggles.LineY(0))
p[1,1].add(biggles.LineY(0))
p[2,0].add(biggles.LineY(0))
p[2,1].add(biggles.LineY(0))
p[3,0].add(biggles.LineY(0))
p[3,1].add(biggles.LineY(0))
p[4,0].add(biggles.LineY(0))
p[4,1].add(biggles.LineY(0))
p[0,0].add(biggles.PlotLabel(0.2, 0.85, "121369"))
p[0,1].add(biggles.PlotLabel(0.2, 0.85, "121374"))
p[1,0].add(biggles.PlotLabel(0.2, 0.85, "121379"))
p[1,1].add(biggles.PlotLabel(0.2, 0.85, "121391"))
p[2,0].add(biggles.PlotLabel(0.2, 0.85, "121395"))
p[2,1].add(biggles.PlotLabel(0.2, 0.85, "121401"))
p[3,0].add(biggles.PlotLabel(0.2, 0.85, "121408"))
p[3,1].add(biggles.PlotLabel(0.2, 0.85, "122249"))
p[4,0].add(biggles.PlotLabel(0.2, 0.85, "123004"))
p[4,1].add(biggles.PlotLabel(0.2, 0.85, "128310"))
p.yrange = -15, 150
p.xrange = -0.03, 1.03
p.xlabel = r"Event number as a fraction of the run"
p.ylabel = r"Number of trackless bhabha events / 100$^{th}$ of a run"
p.aspect_ratio = 1.2
p.show()
p.write_eps("plots/runbyrun_trackless2.eps")
           






tmprunlist2 = []
trackless_tight2 = []
trackless_tight_err2 = []
for r, t, e in zip(tmprunlist, trackless_tight, trackless_tight_err):
  if r not in [121369, 121374, 121379, 121391, 121395, 121401, 121408, 121476, 121748, 121822, 121847, 122249, 122685, 123004, 123436, 123847, 123873, 124816, 124860, 124862, 125367, 126273, 126329, 127280, 128310]:
    tmprunlist2.append(r)
    trackless_tight2.append(t)
    trackless_tight_err2.append(e)

p = biggles.FramedPlot()
p.add(biggles.SymmetricErrorBarsY(tmprunlist2, trackless_tight2, trackless_tight_err2))
p.add(biggles.Points(tmprunlist2, trackless_tight2, symboltype="filled circle", symbolsize=1))
p.aspect_ratio = 0.5
p.yrange = 0.0025, 0.035
p.yrange = 0, 0.0025
p.show()



for r, t, e in zip(tmprunlist, trackless_tight, trackless_tight_err):
  if e > 0 and (t - 0.001)/e < 1.5:
    therun = getdb(r)
    if sum(therun.trackless_vstime.vals) > 1 and max(therun.trackless_vstime.vals) > 0.8*sum(therun.trackless_vstime.vals):
      therun.trackless_vstime.plot().show()
      raw_input(str(r))


for r in [121369, 121374, 121379, 121391, 121395, 121401, 121408, 122249, 123004, 128310]:
  getdb(r).trackless_vstime.plot().show()
  raw_input(str(r))





# now for the twotrack bhabha, twotrack mupairs


p = biggles.FramedPlot()
p.add(biggles.SymmetricErrorBarsY(tmprunlist, Numeric.array(bhamutt), Numeric.array(bhamutt_err)))
p.add(biggles.Points(tmprunlist, Numeric.array(bhamutt), symboltype="filled circle", symbolsize=1))
# p.aspect_ratio = 0.5
# p.yrange = 0, 2.
# p.x1.label = r"Run number"
# p.y1.label = r""
p.yrange = 0, 5000
p.show()



p = biggles.FramedPlot()
p.add(biggles.SymmetricErrorBarsY(tmprunlist, 1./Numeric.array(bhamutt), Numeric.array(bhamutt_err)/Numeric.array(bhamutt)**2))
p.add(biggles.Points(tmprunlist, 1./Numeric.array(bhamutt), symboltype="filled circle", symbolsize=1))
# p.aspect_ratio = 0.5
# p.yrange = 0, 2.
# p.x1.label = r"Run number"
# p.y1.label = r""
p.show()


tmp = initialrunlist[:]
tmp.sort(lambda a, b: int((random.randint(0,1)-0.5)*2))
for r in tmp:
  if runsummary[r].kind != 'p' and runsummary[r].kind != 'c':
    therun = getdb(r)
    q = 1.*therun.hadroncool/therun.gamgam
    qe = q*sqrt(1./therun.hadroncool + 1./therun.gamgam)
    raw_input(qe/q)

bhamu1s = []
bhamu1s_err = []
bhamu2s = []
bhamu2s_err = []
bhamu3s = []
bhamu3s_err = []
bhamuc = []
bhamuc_err = []
for r, bm, e in zip(tmprunlist, bhamutt, bhamutt_err):
  if runsummary[r].res == 1 and runsummary[r].kind == 'p':
    bhamu1s.append(bm)
    bhamu1s_err.append(e)
  elif runsummary[r].res == 2 and runsummary[r].kind == 'p':
    bhamu2s.append(bm)
    bhamu2s_err.append(e)
  elif runsummary[r].res == 3 and runsummary[r].kind == 'p':
    bhamu3s.append(bm)
    bhamu3s_err.append(e)
  elif runsummary[r].kind == 'c':
    bhamuc.append(bm)
    bhamuc_err.append(e)

print jt.wmean(zip(bhamu1s, bhamu1s_err))
print jt.wmean(zip(bhamu2s, bhamu2s_err))
print jt.wmean(zip(bhamu3s, bhamu3s_err))
print jt.wmean(zip(bhamuc, bhamuc_err))


tmprunlist = []
goodratio = []
goodratio_err = []
vstime = {}
allvstime = hist.h1(100, 0., 1.)
for r in initialrunlist:
  if r not in mybadruns:
    therun = getdb(r)

    tmprunlist.append(r)
    q = 1.*therun.mupairtwotrack/(therun.bhabhatwotrack + therun.mupairtwotrack)
    e = sqrt(1.*(therun.mupairtwotrack*therun.bhabhatwotrack**2 + therun.mupairtwotrack**2*therun.bhabhatwotrack))/(0. + therun.bhabhatwotrack + therun.mupairtwotrack)**2
    goodratio.append(q)
    goodratio_err.append(e)

    vstime[r] = hist.h1(100, 0., 1.)
    for i in range(100):
      mu = therun.mupairtwotrack_vstime.vals[i]
      ee = therun.bhabhatwotrack_vstime.vals[i]

      if (ee+mu) > 0:
        vstime[r].vals[i] = 1.*mu/(ee+mu)
        vstime[r].errs[i] = sqrt(1.*(mu*ee**2 + mu**2*ee))/(0. + ee + mu)**2
      else:
        vstime[r].vals[i] = 0.
        vstime[r].errs[i] = 0.

    allvstime += vstime[r]

themean = jt.wmean(zip(goodratio, goodratio_err))[0]


p = biggles.FramedPlot()
p.add(biggles.SymmetricErrorBarsY(tmprunlist, Numeric.array(goodratio)/themean, Numeric.array(goodratio_err)/themean))
p.add(biggles.Points(tmprunlist, Numeric.array(goodratio)/themean, symboltype="filled circle", symbolsize=1))
p.add(biggles.LineX(123102.5, type="dotted"))
p.add(biggles.LineX(125651.5, type="dotted"))
p.add(biggles.LineY(1))
p.aspect_ratio = 0.5
p.xrange = 121000, 131000
p.yrange = 0, 2.5
p.x1.label = r"Run number"
p.y1.label = r"Normalized mupairs/(bhabhas + mupairs)"
p.show()
p.write_eps("plots/runbyrun_bhamutt.eps")






themean = jt.wmean(zip(allvstime.vals, allvstime.errs))[0]
allvstime_norm = allvstime / themean
p = allvstime_norm.plot(False, errorbars=True)
p.add(allvstime_norm.points(symbolsize=1))
p.add(biggles.LineY(1, linetype="dashed"))
# p.add(biggles.Curve([0.01, 0.99], [themean, themean], linetype="dashed"))
p.add(biggles.Points([0.005, 0.995], [allvstime_norm.vals[0], allvstime_norm.vals[-1]], symboltype="circle", symbolsize=7))
p.yrange = 0.89, 1.12
p.xrange = -0.1, 1.1
p.x1.label = r"Event number as a fraction of the run"
p.aspect_ratio = 0.4
p.show()
p.write_eps("plots/runbyrun_bhamutt2.eps")

print sqrt((allvstime_norm.vals[0]-1)**2+allvstime_norm.errs[0]**2)
print sqrt((allvstime_norm.vals[-1]-1)**2+allvstime_norm.errs[-1]**2)


bbtt = {}
for r in initialrunlist:
  if r not in mybadruns:
    bbtt[r] = getdb(r).bhabhatwotrack_vstime

allmeans = []
for r in initialrunlist:
  if r not in mybadruns:
    mean = 0.
    all = 0.
    for x, v in zip(bbtt[r].frame, bbtt[r].vals):
      mean += (x+0.005)*v
      all += v
    mean /= all;
    allmeans.append(mean)

p = biggles.FramedPlot()
p.add(biggles.Points(tmprunlist, allmeans))
p.show()

print jt.stdev(Numeric.array(allmeans)-0.5)
h = hist.h1(100, -5, 5)
h.fill((Numeric.array(allmeans)-0.5)/0.014)
h.plot().show()

for r, m in zip(tmprunlist, allmeans):
  if abs(m-0.5) > 0.014*5:
    bbtt[r].plot().show()
    print r, runsummary[r].res, runsummary[r].kind

getdb(121595).bhabhatwotrack_vstime.plot().show()
getdb(121595).hadron_vstime.plot().show()

getdb(122093).bhabhatwotrack_vstime.plot().show()
getdb(122093).hadron_vstime.plot().show()

getdb(122330).bhabhatwotrack_vstime.plot().show()
getdb(122330).hadron_vstime.plot().show()

getdb(126510).bhabhatwotrack_vstime.plot().show()
getdb(126510).hadron_vstime.plot().show()


getdb(121595).beamgasp_vstime.plot().show()
getdb(122093).beamgasp_vstime.plot().show()
getdb(122330).beamgasp_vstime.plot().show()
getdb(126510).beamgasp_vstime.plot().show()




vstime[121595].plot(False, points=True, errorbars=True).show()
vstime[122330].plot(False, points=True, errorbars=True).show()
vstime[127613].plot(False, points=True, errorbars=True).show()
vstime[128154].plot(False, points=True, errorbars=True).show()

for r in initialrunlist:
  if r not in mybadruns:
    vs = []
    es = []
    for i in range(100):
      if vstime[r].vals[i] > 0:
        vs.append(vstime[r].vals[i])
        es.append(vstime[r].errs[i])
    if len(vs) > 0:
      average = jt.wmean(zip(vs, es))[0]
      for i in range(100):
        if vstime[r].vals[i] > 10*average:
          vstime[r].plot(False, points=True, errorbars=True).show()
          raw_input("run "+str(r)+": bin"+str(i)+" is high")
          break



for r in initialrunlist:
  if r not in mybadruns:
    v1 = []
    e1 = []
    v2 = []
    e2 = []
    for i in range(0, 50):
      if vstime[r].vals[i] > 0.:
        v1.append(vstime[r].vals[i])
        e1.append(vstime[r].errs[i])
    for i in range(50, 100):
      if vstime[r].vals[i] > 0.:
        v2.append(vstime[r].vals[i])
        e2.append(vstime[r].errs[i])
    if len(v1) == 0 or len(v2) == 0 or sum(e1) == 0. or sum(e2) == 0.:
        vstime[r].plot(False, points=True, errorbars=True).show()
        raw_input("run "+str(r)+" is missing half")
    else:
      firsthalf = jt.wmean(zip(v1, e1))
      secondhalf = jt.wmean(zip(v2, e2))
      if abs(firsthalf[0]-secondhalf[0])/sqrt(firsthalf[1]**2+secondhalf[1]**2) > 1.5:
        vstime[r].plot(False, points=True, errorbars=True).show()
        raw_input("run "+str(r)+" is weird")
      


for r in initialrunlist:
  if r not in mybadruns:
    if (vstime[r].sumerr(0.,0.5)**2 + vstime[r].sumerr(0.5,1.)**2) > 0:
      if abs(vstime[r].sum(0.,0.5)-vstime[r].sum(0.5,1.))/sqrt(vstime[r].sumerr(0.,0.5)**2 + vstime[r].sumerr(0.5,1.)**2) > 5.:
        print r, abs(vstime[r].sum(0.,0.5)-vstime[r].sum(0.5,1.))/sqrt(vstime[r].sumerr(0.,0.5)**2 + vstime[r].sumerr(0.5,1.)**2)
        vstime[r].plot(False, points=True, errorbars=True).show()
        raw_input("run "+str(r)+" is weird")
#     else:
#         vstime[r].plot(False, points=True, errorbars=True).show()
#         raw_input("run "+str(r)+" is missing half")
      








# #############################


hadcool = {}
gamcool = {}
crosssec = {}
for r in initialrunlist:
  if r not in mybadruns:
    therun = getdb(r)
    hadcool[r] = therun.hadroncool_vstime
    gamcool[r] = therun.gamgam_vstime
    crosssec[r] = therun.hadroncool_vstime / therun.gamgam_vstime

# this was fun
# for r in initialrunlist:
#   if r not in mybadruns:
#     p = crosssec[r].plot()
#     p.yrange = 0, 50
#     p.show()

p = biggles.FramedPlot()
p.add(biggles.Points(tmprunlist, means, symboltype="filled circle", symbolsize=0.8))
p.add(biggles.SymmetricErrorBarsY(tmprunlist, means, means_err))
p.show()



def linefit(h, careful=False):
  sumwt = 0.
  sumx = 0.
  sumy = 0.
  sumx2 = 0.
  sumy2 = 0.
  sumxy = 0.
  for i, x, y, yerr in zip(range(100), h.frame + 0.005, h.vals, h.errs):
    if y > 0:
      if not careful or i < 99:
        weight = 1./yerr**2
        sumwt += weight
        sumx += weight * x
        sumy += weight * y
        sumx2 += weight * x**2
        sumy2 += weight * y**2
        sumxy += weight * x*y
  det = sumwt * sumx2 - sumx * sumx
  if det > 0:
    yint = (sumx2*sumy - sumx*sumxy)/det
    slope = (sumxy*sumwt - sumx*sumy)/det
    yint_err = sqrt(sumx2/det)
    slope_err = sqrt(sumwt/det)
    return yint, yint_err, slope, slope_err
  return None

def chi2(h, yint, slope):
  c = 0.
  n = 0
  for x, y, yerr in zip(h.frame + 0.005, h.vals, h.errs):
    if y > 0:
      line = yint + slope*x
      c += (line - y)**2/yerr**2
      n += 1
  return c, n-2




for r in initialrunlist:
  if r not in mybadruns:
    if r in mycarefulscan:
      output = linefit(crosssec[r], True)
    else:
      output = linefit(crosssec[r])
    if output != None:
      yint, yint_err, slope, slope_err = output
      if r in mycarefulscan:
        p = crosssec[r].plot()
        p.add(biggles.Slope(slope, (0, yint)))
        p.show()
        raw_input(r)
    else:
      raise Exception

slopes = []
slopes_err = []
chi2s = []
ndofs = []
for r in initialrunlist:
  if r not in mybadruns:
    if r in mycarefulscan:
      output = linefit(crosssec[r], True)
    else:
      output = linefit(crosssec[r])
    if output != None:
      yint, yint_err, slope, slope_err = output
      slopes.append(slope)
      slopes_err.append(slope_err)
      c, n = chi2(crosssec[r], yint, slope)
      chi2s.append(c)
      ndofs.append(n)
    else:
      raise Exception


p = biggles.FramedPlot()
p.add(biggles.Points(tmprunlist, slopes, symboltype="filled circle", symbolsize=0.8))
p.add(biggles.SymmetricErrorBarsY(tmprunlist, slopes, slopes_err))
p.show()


hslopes = hist.h1(100, -5, 5)
hredchi = hist.h1(100, 0, 1.5)
mean_redchi = 0.
all_redchi = 0
for r, s, e, c, n in zip(tmprunlist, slopes, slopes_err, chi2s, ndofs):
  hslopes.fill(s/e)
  hredchi.fill(c/n)
  mean_redchi += c/n
  all_redchi += 1
  if s/e<-5 or c/n>1.5:
    print r, s/e, c/n





mean_redchi /= float(all_redchi)

hslopes.plot().show()
hredchi.plot().show()

hslopes.rootn()
def hslopeschi(a, m, s):
  binwide = hslopes.frame[1] - hslopes.frame[0]
  chi = 0.
  xes = []
  yes = []
  for lowx, v, e in zip(hslopes.frame, hslopes.vals, hslopes.errs):
    x = lowx + binwide / 2.
    gauss = a * exp(-(x-m)**2/2./s**2)/sqrt(2.*pi)/s
    if e > 0:
      chi += (gauss - v)**2/e**2
    xes.append(x)
    yes.append(gauss)
  p = biggles.Table(1,2)
  p[0,0] = hslopes.plot()
  p[0,0].add(biggles.Curve(xes, yes))
  p[0,0].x1.label = r"Distribution of slope/slope uncertainty"
  hist.addinfobox(p[0,0], [["Mean", "%.3g" % m], ["Sigma", "%.3g" % s], ["Overflow", hslopes.overflow], ["Underflow", hslopes.underflow], ["Total", all_redchi]], width=0.40, numformat="%g")
  p[0,0].add(biggles.PlotLabel(0.1,0.9, "(a)"))
  p[0,1] = hredchi.plot()
  p[0,1].add(biggles.PlotLabel(0.1,0.9, "(b)"))
  p[0,1].x1.label = r"Distribution of $\chi^2$/#d.o.f."
  hist.addinfobox(p[0,1], [["Mean", mean_redchi], ["Overflow", hredchi.overflow], ["Total", all_redchi]], width=0.40, numformat="%g")
  p.aspect_ratio = 0.4
  p.show()
  p.write_eps("plots/runbyrun_hadxs1.eps")
  return chi
# from minuit import *
# m = Minuit(hslopeschi, start=[288.58272841918921, -0.094867287985651472, 1.1422822640086117])
# m.migrad()
# print m.values
# print m.fval
hslopeschi(291.93388673545957, -0.053903000001475972, 1.0364887626787449)











for r, s, e in zip(tmprunlist, slopes, slopes_err):
  if abs(s)/e > 3:
    p = crosssec[r].plot(False, errorbars=True, points=True)
    yint, yint_err, slope, slope_err = linefit(crosssec[r])
    p.add(biggles.Slope(slope, (0, yint)))
    p.show()
    raw_input("%d %d %s %g %g %g" % (r, runsummary[r].res, runsummary[r].kind, abs(s)/e, s, e))


for r, s, e in zip(tmprunlist, slopes, slopes_err):
  if r in [123281, 123411, 125064, 126305, 127218]:
    p = crosssec[r].plot(False, errorbars=True, points=True)
    yint, yint_err, slope, slope_err = linefit(crosssec[r])
    p.add(biggles.Slope(slope, (0, yint)))
    p.show()
    raw_input("%d %d %s %g %g %g" % (r, runsummary[r].res, runsummary[r].kind, abs(s)/e, s, e))

hadcool[127218].plot().show()
gamcool[127218].plot().show()


cs123281 = getdb(123281).hadroncool_vstime / getdb(123281).gamgam_vstime
cs123411 = getdb(123411).hadroncool_vstime / getdb(123411).gamgam_vstime
p = biggles.FramedArray(2,1)
p[0,0].add(cs123281.errorbars())
p[0,0].add(cs123281.points(symbolsize=1))
yint, yint_err, slope, slope_err = linefit(cs123281)
p[0,0].add(biggles.Slope(slope, (0, yint)))
p[0,0].add(biggles.PlotLabel(0.15, 0.8, "123281"))
p[0,0].add(biggles.LineY(0))
p[1,0].add(cs123411.errorbars())
p[1,0].add(cs123411.points(symbolsize=1))
yint, yint_err, slope, slope_err = linefit(cs123411)
p[1,0].add(biggles.Slope(slope, (0, yint)))
p[1,0].add(biggles.PlotLabel(0.15, 0.8, "123411"))
p[1,0].add(biggles.LineY(0))
p.ylabel = "Relative Hadronic Cross-section"
p.xlabel = "Event number as a fraction of the run"
p[0,0].yrange = -9, 59
p[1,0].yrange = -9, 89
p.aspect_ratio = 0.5
p.show()
p.write_eps("plots/runbyrun_hadxs2.eps")



