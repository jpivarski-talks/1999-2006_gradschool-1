from minuit import *

execfile("utilities.py")
nobeam = getsb("cos")
ebeam = getsb("bge")
pbeam = getsb("bgp")

# gamgamcor = {}
# gamgamcor_err = {}
# hadronraw = {}
# hadroncor = {}
# hadroncor_err = {}
# cross = {}
# cross_err = {}
# for r in initialrunlist:
#   if r not in mybadruns:
#     therun = getdb(r)

#     if r not in mycarefulscan:
#       efficiency = therun.bhabha_cotTnumer.divide_by_superset(therun.bhabha_cotTdenom)
#       for i, d in enumerate(therun.bhabha_cotTdenom):
#         if d == 0:
#           efficiency.vals[i] = 1.
#       gamgamcor[r] = (therun.gamgam_cotT_cut / efficiency).sum()
#       gamgamcor_err[r] = (therun.gamgam_cotT_cut / efficiency).sumerr()

#       e = 1. * (ebeam.hadroncool - 1.*nobeam.hadroncool*ebeam.cosmic/nobeam.cosmic) * therun.beamgase / ebeam.beamgase
#       p = 1. * (pbeam.hadroncool - 1.*nobeam.hadroncool*pbeam.cosmic/nobeam.cosmic) * therun.beamgasp / pbeam.beamgasp
#       c = 1. * nobeam.hadroncool * therun.cosmic / nobeam.cosmic

#       hadronraw[r] = therun.hadroncool
#       hadroncor[r] = therun.hadroncool - e/2. - p/2. - c
#       hadroncor_err[r] = sqrt(therun.hadroncool + therun.cosmic*(1.*nobeam.hadron/nobeam.cosmic)**2 + (e/2.)**2 + (p/2.)**2)

#     else:
#       gamgamcor[r] = therun.gamgam_vstime.sum(0.,0.99) * 0.9976
#       gamgamcor_err[r] = sqrt(gamgamcor[r])

#       e = 1. * (ebeam.hadroncool_vstime.sum(0.,0.99) - 1.*nobeam.hadroncool_vstime.sum(0.,0.99)*ebeam.cosmic/nobeam.cosmic) * therun.beamgase / ebeam.beamgase
#       p = 1. * (pbeam.hadroncool_vstime.sum(0.,0.99) - 1.*nobeam.hadroncool_vstime.sum(0.,0.99)*pbeam.cosmic/nobeam.cosmic) * therun.beamgasp / pbeam.beamgasp
#       c = 1. * nobeam.hadroncool_vstime.sum(0.,0.99) * therun.cosmic / nobeam.cosmic

#       hadronraw[r] = therun.hadroncool_vstime.sum(0.,0.99)
#       hadroncor[r] = therun.hadroncool_vstime.sum(0.,0.99) - e/2. - p/2. - c
#       hadroncor_err[r] = sqrt(therun.hadroncool_vstime.sum(0.,0.99) + therun.cosmic*(1.*nobeam.hadron/nobeam.cosmic)**2 + (e/2.)**2 + (p/2.)**2)
      
#     cross[r] = hadroncor[r] / gamgamcor[r] / runsummary[r].energy**2
#     cross_err[r] = cross[r] * sqrt((1.*hadroncor_err[r]/hadroncor[r])**2 + (1.*gamgamcor_err[r]/gamgamcor[r])**2)

# pickle.dump(cross, open("/home/mccann/antithesis/crosssection.p", 'w'), -1)
# pickle.dump(cross_err, open("/home/mccann/antithesis/crosssection_err.p", 'w'), -1)

cross = pickle.load(open("/home/mccann/antithesis/crosssection.p"))
cross_err = pickle.load(open("/home/mccann/antithesis/crosssection_err.p"))

rpeak1 = []
cpeak1 = []
epeak1 = []
rcont1 = []
ccont1 = []
econt1 = []
rpeak2 = []
cpeak2 = []
epeak2 = []
rcont2 = []
ccont2 = []
econt2 = []
rpeak3 = []
cpeak3 = []
epeak3 = []
rcont3 = []
ccont3 = []
econt3 = []
for r in initialrunlist:
  if r not in mybadruns:
    if runsummary[r].res == 1 and runsummary[r].kind == 'p':
      rpeak1.append(r)
      cpeak1.append(cross[r])
      epeak1.append(cross_err[r])
    if runsummary[r].res == 1 and runsummary[r].kind == 'c':
      rcont1.append(r)
      ccont1.append(cross[r])
      econt1.append(cross_err[r])
    if runsummary[r].res == 2 and runsummary[r].kind == 'p' and r < 128425:
      rpeak2.append(r)
      cpeak2.append(cross[r])
      epeak2.append(cross_err[r])
    if runsummary[r].res == 2 and runsummary[r].kind == 'c':
      rcont2.append(r)
      ccont2.append(cross[r])
      econt2.append(cross_err[r])
    if runsummary[r].res == 3 and runsummary[r].kind == 'p':
      rpeak3.append(r)
      cpeak3.append(cross[r])
      epeak3.append(cross_err[r])
    if runsummary[r].res == 3 and runsummary[r].kind == 'c':
      rcont3.append(r)
      ccont3.append(cross[r])
      econt3.append(cross_err[r])

mcont1 = jt.wmean(zip(ccont1, econt1))[0]
mcont2 = jt.wmean(zip(ccont2, econt2))[0]
mcont3 = jt.wmean(zip(ccont3, econt3))[0]

print sum(map(lambda (c,e): (c-mcont1)**2/e**2, zip(ccont1, econt1))), len(ccont1)-1
print sum(map(lambda (c,e): (c-mcont2)**2/e**2, zip(ccont2, econt2))), len(ccont2)-1
print sum(map(lambda (c,e): (c-mcont3)**2/e**2, zip(ccont3, econt3))), len(ccont3)-1



mpeak1 = jt.wmean(zip(cpeak1, epeak1))[0]
mpeak2 = jt.wmean(zip(cpeak2, epeak2))[0]
mpeak3 = jt.wmean(zip(cpeak3, epeak3))[0]

print sum(map(lambda (c,e): (c-mpeak1)**2/e**2, zip(cpeak1, epeak1))), len(cpeak1)-1
print sum(map(lambda (c,e): (c-mpeak2)**2/e**2, zip(cpeak2, epeak2))), len(cpeak2)-1
print sum(map(lambda (c,e): (c-mpeak3)**2/e**2, zip(cpeak3, epeak3))), len(cpeak3)-1


print jt.wmean(zip(ccont1, econt1))
print jt.wmean(zip(ccont2, econt2))
print jt.wmean(zip(ccont3, econt3))


# # cross2 = {}
# # cross2_err = {}
# for r in initialrunlist:
#   if r not in mybadruns and runsummary[r].kind == 'p' and runsummary[r].res == 2:
#     therun = getdb(r)

#     e = 1. * (ebeam.hadroncool - 1.*nobeam.hadroncool*ebeam.cosmic/nobeam.cosmic) * therun.beamgase / ebeam.beamgase
#     p = 1. * (pbeam.hadroncool - 1.*nobeam.hadroncool*pbeam.cosmic/nobeam.cosmic) * therun.beamgasp / pbeam.beamgasp
#     c = 1. * nobeam.hadroncool * therun.cosmic / nobeam.cosmic

#     hadronraw_r = therun.hadroncool
#     hadroncor_r = therun.hadroncool - e/2. - p/2. - c
#     hadroncor_err_r = sqrt(therun.hadroncool + therun.cosmic*(1.*nobeam.hadroncool/nobeam.cosmic)**2 + (e/2.)**2 + (p/2.)**2)

#     cross2[r] = hadroncor_r / therun.bhabha
#     cross2_err[r] = cross2[r] * sqrt((1.*hadroncor_err_r/hadroncor_r)**2 + 1./therun.bhabha)


# ctmp = []
# etmp = []
# for r in initialrunlist:
#   if r not in mybadruns:
#     if runsummary[r].res == 2 and runsummary[r].kind == 'p' and r > 128000:
#       ctmp.append(cross[r])
#       etmp.append(cross_err[r])
# print jt.wmean(zip(ctmp, etmp))



ctmp = []
etmp = []
for r in initialrunlist:
  if r not in mybadruns:
    if runsummary[r].res == 2 and runsummary[r].kind == 'p' and r < 127642:
      ctmp.append(cross2[r])
      etmp.append(cross2_err[r])
print jt.wmean(zip(ctmp, etmp))

ctmp = []
etmp = []
for r in initialrunlist:
  if r not in mybadruns:
    if runsummary[r].res == 2 and runsummary[r].kind == 'p' and r > 127642:
      ctmp.append(cross2[r])
      etmp.append(cross2_err[r])
print jt.wmean(zip(ctmp, etmp))






def linefit(xlist, ylist, elist, slopesig=False):
  sumwt = 0.
  sumx = 0.
  sumy = 0.
  sumx2 = 0.
  sumy2 = 0.
  sumxy = 0.
  for x, y, yerr in zip(xlist, ylist, elist):
    if y > 0:
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
    if slopesig:
      return slope / slope_err
    else:
      return biggles.Slope(slope, (0, yint))
  return None

print linefit(rpeak1, cpeak1, epeak1, True)
print linefit(rcont1, ccont1, econt1, True)
print linefit(rpeak2, cpeak2, epeak2, True)
print linefit(rcont2, ccont2, econt2, True)
print linefit(rpeak3, cpeak3, epeak3, True)
print linefit(rcont3, ccont3, econt3, True)


p = biggles.Table(3,2)
p.title = "Relative Hadronic Cross-Sections"

p[0,0] = biggles.FramedPlot()
p[0,0].add(biggles.Points(rpeak1, cpeak1, symboltype="filled circle", symbolsize=2))
p[0,0].add(biggles.SymmetricErrorBarsY(rpeak1, cpeak1, epeak1))
p[0,0].add(linefit(rpeak1, cpeak1, epeak1))
p[0,0].xrange = min(rpeak1)-100, max(rpeak1)+100
p[0,0].x1.label = r"Run number for on-res $\Upsilon(1S)$"

p[0,1] = biggles.FramedPlot()
p[0,1].add(biggles.Points(rcont1, ccont1, symboltype="filled circle", symbolsize=2))
p[0,1].add(biggles.SymmetricErrorBarsY(rcont1, ccont1, econt1))
p[0,1].add(linefit(rcont1, ccont1, econt1))
p[0,1].xrange = min(rcont1)-100, max(rcont1)+100
p[0,1].x1.label = r"Run number for off-res $\Upsilon(1S)$"

p[1,0] = biggles.FramedPlot()
p[1,0].add(biggles.Points(rpeak2, cpeak2, symboltype="filled circle", symbolsize=2))
p[1,0].add(biggles.SymmetricErrorBarsY(rpeak2, cpeak2, epeak2))
p[1,0].add(linefit(rpeak2, cpeak2, epeak2))
p[1,0].xrange = min(rpeak2)-100, max(rpeak2)+100
p[1,0].x1.label = r"Run number for on-res $\Upsilon(2S)$"

p[1,1] = biggles.FramedPlot()
p[1,1].add(biggles.Points(rcont2, ccont2, symboltype="filled circle", symbolsize=2))
p[1,1].add(biggles.SymmetricErrorBarsY(rcont2, ccont2, econt2))
p[1,1].add(linefit(rcont2, ccont2, econt2))
p[1,1].xrange = min(rcont2)-100, max(rcont2)+100
p[1,1].x1.label = r"Run number for off-res $\Upsilon(2S)$"

p[2,0] = biggles.FramedPlot()
p[2,0].add(biggles.Points(rpeak3, cpeak3, symboltype="filled circle", symbolsize=2))
p[2,0].add(biggles.SymmetricErrorBarsY(rpeak3, cpeak3, epeak3))
p[2,0].add(linefit(rpeak3, cpeak3, epeak3))
p[2,0].xrange = min(rpeak3)-100, max(rpeak3)+100
p[2,0].x1.label = r"Run number for on-res $\Upsilon(3S)$"

p[2,1] = biggles.FramedPlot()
p[2,1].add(biggles.Points(rcont3, ccont3, symboltype="filled circle", symbolsize=2))
p[2,1].add(biggles.SymmetricErrorBarsY(rcont3, ccont3, econt3))
p[2,1].add(linefit(rcont3, ccont3, econt3))
p[2,1].xrange = min(rcont3)-500, max(rcont3)+500
p[2,1].x1.label = r"Run number for off-res $\Upsilon(3S)$"

p.aspect_ratio = 1.2
p.show()
p.write_eps("plots/runbyrun_peaksconts.eps")



def fitfunc(a, m, s):
  binwide = h.frame[1] - h.frame[0]
  chi = 0.
  xes = []
  yes = []
  for lowx, v, e in zip(h.frame, h.vals, h.errs):
    x = lowx + binwide / 2.
    gauss = a * exp(-(x-m)**2/2./s**2)/sqrt(2.*pi)/s
    if e > 0:
      chi += (gauss - v)**2/e**2
    xes.append(x)
    yes.append(gauss)
  p = h.plot()
  p.add(biggles.Curve(xes, yes))
  p.show()
  return chi

def drawline(a, m, s):
  binwide = h.frame[1] - h.frame[0]
  chi = 0.
  xes = []
  yes = []
  for lowx, v, e in zip(h.frame, h.vals, h.errs):
    x = lowx + binwide / 2.
    gauss = a * exp(-(x-m)**2/2./s**2)/sqrt(2.*pi)/s
    if e > 0:
      chi += (gauss - v)**2/e**2
    xes.append(x)
    yes.append(gauss)
  return biggles.Curve(xes, yes)

hpeak1 = hist.h1(100, -5, 5)
hpeak1.fill((Numeric.array(cpeak1) - jt.wmean(zip(cpeak1, epeak1))[0]) / Numeric.array(epeak1))
hpeak1.rootn()
h = hpeak1
m = Minuit(fitfunc, start=[0.2*len(cpeak1), 0, 1])
m.migrad()
parpeak1 = m.values
errpeak1 = m.errors

hcont1 = hist.h1(100, -5, 5)
hcont1.fill((Numeric.array(ccont1) - jt.wmean(zip(ccont1, econt1))[0]) / Numeric.array(econt1))
hcont1.rootn()
h = hcont1
m = Minuit(fitfunc, start=[0.2*len(ccont1), 0, 1])
m.migrad()
parcont1 = m.values
errcont1 = m.errors

hpeak2 = hist.h1(100, -5, 5)
hpeak2.fill((Numeric.array(cpeak2) - jt.wmean(zip(cpeak2, epeak2))[0]) / Numeric.array(epeak2))
hpeak2.rootn()
h = hpeak2
m = Minuit(fitfunc, start=[0.2*len(cpeak2), 0, 1])
m.migrad()
parpeak2 = m.values
errpeak2 = m.errors

hcont2 = hist.h1(100, -5, 5)
hcont2.fill((Numeric.array(ccont2) - jt.wmean(zip(ccont2, econt2))[0]) / Numeric.array(econt2))
hcont2.rootn()
h = hcont2
m = Minuit(fitfunc, start=[0.2*len(ccont2), 0, 1])
m.migrad()
parcont2 = m.values
errcont2 = m.errors

hpeak3 = hist.h1(100, -5, 5)
hpeak3.fill((Numeric.array(cpeak3) - jt.wmean(zip(cpeak3, epeak3))[0]) / Numeric.array(epeak3))
hpeak3.rootn()
h = hpeak3
m = Minuit(fitfunc, start=[0.2*len(cpeak3), 0, 1])
m.migrad()
parpeak3 = m.values
errpeak3 = m.errors

hcont3 = hist.h1(100, -5, 5)
hcont3.fill((Numeric.array(ccont3) - jt.wmean(zip(ccont3, econt3))[0]) / Numeric.array(econt3))
hcont3.rootn()
h = hcont3
m = Minuit(fitfunc, start=[0.2*len(ccont3), 0, 1])
m.migrad()
parcont3 = m.values
errcont3 = m.errors

p = biggles.Table(3,2)

p[0,0] = hpeak1.plot()
p[0,0].add(drawline(*parpeak1))
p[0,0].add(biggles.PlotLabel(0.9, 0.8, "width: "+("%3.2f" % (parpeak1[2])), texthalign="right"))
p[0,0].add(biggles.PlotLabel(0.9, 0.7, r"$\pm$"+("%3.2f" % (errpeak1[2])), texthalign="right"))
p[0,0].x1.label = r"Deviation of on-res $\Upsilon(1S)$"

p[0,1] = hcont1.plot()
p[0,1].add(drawline(*parcont1))
p[0,1].add(biggles.PlotLabel(0.9, 0.8, "width: "+("%3.2f" % (parcont1[2])), texthalign="right"))
p[0,1].add(biggles.PlotLabel(0.9, 0.7, r"$\pm$"+("%3.2f" % (errcont1[2])), texthalign="right"))
p[0,1].x1.label = r"Deviation of off-res $\Upsilon(1S)$"

p[1,0] = hpeak2.plot()
p[1,0].add(drawline(*parpeak2))
p[1,0].add(biggles.PlotLabel(0.9, 0.8, "width: "+("%3.2f" % (parpeak2[2])), texthalign="right"))
p[1,0].add(biggles.PlotLabel(0.9, 0.7, r"$\pm$"+("%3.2f" % (errpeak2[2])), texthalign="right"))
p[1,0].x1.label = r"Deviation of on-res $\Upsilon(2S)$"

p[1,1] = hcont2.plot()
p[1,1].add(drawline(*parcont2))
p[1,1].add(biggles.PlotLabel(0.9, 0.8, "width: "+("%3.2f" % (parcont2[2])), texthalign="right"))
p[1,1].add(biggles.PlotLabel(0.9, 0.7, r"$\pm$"+("%3.2f" % (errcont2[2])), texthalign="right"))
p[1,1].x1.label = r"Deviation of off-res $\Upsilon(2S)$"

p[2,0] = hpeak3.plot()
p[2,0].add(drawline(*parpeak3))
p[2,0].add(biggles.PlotLabel(0.9, 0.8, "width: "+("%3.2f" % (parpeak3[2])), texthalign="right"))
p[2,0].add(biggles.PlotLabel(0.9, 0.7, r"$\pm$"+("%3.2f" % (errpeak3[2])), texthalign="right"))
p[2,0].x1.label = r"Deviation of on-res $\Upsilon(3S)$"

p[2,1] = hcont3.plot()
p[2,1].add(drawline(*parcont3))
p[2,1].add(biggles.PlotLabel(0.9, 0.8, "width: "+("%3.2f" % (parcont3[2])), texthalign="right"))
p[2,1].add(biggles.PlotLabel(0.9, 0.7, r"$\pm$"+("%3.2f" % (errcont3[2])), texthalign="right"))
p[2,1].x1.label = r"Deviation of off-res $\Upsilon(3S)$"

p.aspect_ratio = 1.2
p.show()
p.write_eps("plots/runbyrun_peaksconts2.eps")



def fitfunc2(a):
  chi = 0.
  for en, c, cerr in zip(energies, cross_sections, cross_sections_err):
    if en > 10200:
      chi += (c - 1.0121*a*9440**2/en**2)**2/cerr**2
    elif en > 9800:
      chi += (c - 1.0055*a*9440**2/en**2)**2/cerr**2
    else:
      chi += (c - a*9440**2/en**2)**2/cerr**2
  return chi

def drawoneovers(a, howfar=5.):
  xes = Numeric.arange(min(energies)-howfar, max(energies)+howfar*4, 5.)
  yes = Numeric.arange(min(energies)-howfar, max(energies)+howfar*4, 5.)
  for i, x in enumerate(xes):
    yes[i] = a*9440**2/x**2
  return biggles.Curve(xes, yes)

energies = []
cross_sections = []
cross_sections_err = []
for r in initialrunlist:
  if r not in mybadruns:
    if runsummary[r].kind == 'c':
      energies.append(runsummary[r].energy*2000)
      cross_sections.append(cross[r])
      cross_sections_err.append(cross_err[r])
m = Minuit(fitfunc2)
m.migrad()
print m.fval, len(energies)-1
print m.values[0]

p = biggles.FramedPlot()
plotdata(p, energies, cross_sections, cross_sections_err)
p.add(drawoneovers(m.values[0], 200.))
p.aspect_ratio = 0.1
p.xrange = 9300, 10500
p.y1.draw_ticklabels = 0
p.x1.label = r"$E_{COM}$ in MeV"
p.yrange = 0, 0.6
p.show()
p.write_eps("plots/junePTA/oneovers.eps")


p = biggles.Table(3,1)
p.aspect_ratio = 1.2

energies = []
cross_sections = []
cross_sections_err = []
for r in initialrunlist:
  if r not in mybadruns:
    if runsummary[r].res == 1:
      energies.append(runsummary[r].energy*2000)
      cross_sections.append(cross[r])
      cross_sections_err.append(cross_err[r])
p[0,0] = biggles.FramedPlot()
p[0,0].add(biggles.Points(energies, cross_sections, symboltype="filled circle", symbolsize=0.6))
p[0,0].add(biggles.SymmetricErrorBarsY(energies, cross_sections, cross_sections_err))
p[0,0].xrange = min(energies)-5., max(energies)+5.
p[0,0].yrange = 0, 1.5
p[0,0].x1.label = r"$\Upsilon(1S)$ center of mass energy in MeV"
p[0,0].add(drawoneovers(m.values[0]))

energies = []
cross_sections = []
cross_sections_err = []
for r in initialrunlist:
  if r not in mybadruns:
    if runsummary[r].res == 2:
      energies.append(runsummary[r].energy*2000)
      cross_sections.append(cross[r])
      cross_sections_err.append(cross_err[r])
p[1,0] = biggles.FramedPlot()
p[1,0].add(biggles.Points(energies, cross_sections, symboltype="filled circle", symbolsize=0.6))
p[1,0].add(biggles.SymmetricErrorBarsY(energies, cross_sections, cross_sections_err))
p[1,0].xrange = min(energies)-5., max(energies)+5.
p[1,0].yrange = 0, 0.9
p[1,0].x1.label = r"$\Upsilon(2S)$ center of mass energy in MeV"
p[1,0].add(drawoneovers(m.values[0]))

energies = []
cross_sections = []
cross_sections_err = []
for r in initialrunlist:
  if r not in mybadruns:
    if runsummary[r].res == 3:
      energies.append(runsummary[r].energy*2000)
      cross_sections.append(cross[r])
      cross_sections_err.append(cross_err[r])
p[2,0] = biggles.FramedPlot()
p[2,0].add(biggles.Points(energies, cross_sections, symboltype="filled circle", symbolsize=0.6))
p[2,0].add(biggles.SymmetricErrorBarsY(energies, cross_sections, cross_sections_err))
p[2,0].xrange = min(energies)-5., max(energies)+5.
p[2,0].yrange = 0, 0.7
p[2,0].x1.label = r"$\Upsilon(3S)$ center of mass energy in MeV"
p[2,0].add(drawoneovers(m.values[0]))

p.show()
p.write_eps("plots/runbyrun_thescans.eps")


energies = []
cross_sections = []
cross_sections_err = []
energies2 = []
cross_sections2 = []
cross_sections_err2 = []
for r in initialrunlist:
  if r not in mybadruns:
    if runsummary[r].res == 3 and runsummary[r].kind == 's':
      if r > 126000:
#      if r < 121886:
        energies.append(runsummary[r].energy*2000)
        cross_sections.append(cross[r])
        cross_sections_err.append(cross_err[r])
for r in initialrunlist:
  if r not in mybadruns:
    if runsummary[r].res == 3 and runsummary[r].kind == 's':
      if r > 121886 and r < 126000:
        energies2.append(runsummary[r].energy*2000)
        cross_sections2.append(cross[r])
        cross_sections_err2.append(cross_err[r])
p = biggles.FramedPlot()
p.add(biggles.Points(energies2, cross_sections2, symboltype="filled circle", symbolsize=0.6))
p.add(biggles.SymmetricErrorBarsY(energies2, cross_sections2, cross_sections_err2))
p.add(biggles.Points(energies, cross_sections, symboltype="filled circle", symbolsize=0.6, color="red"))
p.add(biggles.SymmetricErrorBarsY(energies, cross_sections, cross_sections_err, color="red"))
p.xrange = 10339.6, 10386.0
p.yrange = 0, 0.7
p.x1.label = r"$\Upsilon(3S)$ center of mass energy in MeV"
p.add(drawoneovers(m.values[0]))
p.add(biggles.LineX(10350, linetype="dotted"))
p.add(biggles.LineX(10352, linetype="dotted"))
p.show()


tmprunlist = []
cross_sections = []
cross_sections_err = []
for r in initialrunlist:
  if r not in mybadruns:
    if runsummary[r].res == 3 and runsummary[r].kind == 's':
#      if 10350./2000. < runsummary[r].energy < 10352./2000.:
#        print r, cross[r], cross_err[r]
        tmprunlist.append(r)
        cross_sections.append(cross[r])
        cross_sections_err.append(cross_err[r])
p = biggles.FramedPlot()
p.add(biggles.Points(tmprunlist, cross_sections, symboltype="filled circle"))
p.add(biggles.SymmetricErrorBarsY(tmprunlist, cross_sections, cross_sections_err))
p.show()



