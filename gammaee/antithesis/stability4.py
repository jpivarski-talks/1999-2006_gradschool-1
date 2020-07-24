execfile("/home/mccann/antithesis/utilities.py")
nobeam = getsb("cos")
ebeam = getsb("bge")
pbeam = getsb("bgp")
import gbwkf, gbwkftau, gbwkfee
runstart = pickle.load(open("/home/mccann/antithesis/old_dotps/runstart.p"))
runend = pickle.load(open("/home/mccann/antithesis/old_dotps/runend.p"))
import time, biggles

nbish2nb = 23.0481

def run_date(r):
  if r in runstart and r in runend:
    return (runstart[r] + runend[r])/2.
  elif r in runstart:
    return runstart[r]
  elif r in runend:
    return runend[r]
  elif r == 130630:
    return run_date(130629)
  else:
    raise Exception, r

def setup_runs(res, low, high, limit=True):
  beginning = run_date(low)

  tmpruns = []
  for r in initialrunlist:
    if r not in mybadruns and low <= r <= high and runsummary[r].res == res:
      if runsummary[r].kind == 'p':
        if not limit or run_date(r) < beginning + 48.*60.*60:
          tmpruns.append(r)
  return tmpruns

def setup_data(runs, lumisource=0):
  tmpdata = []
  for r in runs:
    tmpdata.append(get_runs([r], lumisource=lumisource))
  return tmpdata

def mygbwkf(mass, fullgam, rmsbeam, yint, phi, w):
  "yint = 0.018, 0.018, 0.018; phi=0"
  if w > mass + 200.:
    return 0.076/(w-mass)
  return gbwkf.gbwkf(mass, fullgam, rmsbeam, yint, phi, w-mass)

def mygbwkftau(mass, fullgam, rmsbeam, yint, phi, w):
  "yint = 0.20, 0.37, 0.27; phi = 0"
  if w > mass + 200.:
    return 0.076/(w-mass)
  return gbwkftau.gbwkf(mass, fullgam, rmsbeam, yint, phi, w-mass)

def mygbwkfee(mass, fullgam, rmsbeam, yint, phi, w):
  if w > mass + 200.:
    return 0.076/(w-mass)
  return gbwkfee.gbwkf(mass, fullgam, rmsbeam, yint, phi, w-mass)

def u1func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, w):
  tmp = 0.
  upsilon = area * 0.9757 * mygbwkf(9460.30, fullgam, rmsbeam, yint, phi, w)
  tmp += upsilon
  tmp += area * 0.578 * btautau * mygbwkftau(9460.30, fullgam, rmsbeam, tauyint, tauphi, w)
  tmp += back * (1.-twophofrac) * 9000.**2 / w**2
  tmp += back * twophofrac * log(w**2/9000.**2)

  return tmp

class FitRecord: pass
ggfits = pickle.load(open("/home/mccann/antithesis/fit_results/bhabhafits_0.p"))

def get_runs(runs, lumisource=0):
  g = 0.
  h = 0.
  e = 0.
  p = 0.
  c = 0.
  wsum = 0.
  wesum = 0.
  for r in runs:
    therun = getdb(r)
    ngg = therun.gamgam
    if r in mycarefulscan: ngg = therun.gamgam_vstime.sum(0.,0.99)
    wsum += float(ngg)
    if r not in (123828, 123832):
      wesum += float(ngg) * runsummary[r].energy
    else:
      wesum += float(ngg) * (runsummary[r].energy + 6.6e-4)

    if runsummary[r].res == 1:
      myarea, myrmsbeam, myback, myjan16, myjan30, myfeb06, myfeb13, myfeb20, myfeb27, mymar06, mymar13, myapr03, myapr08, myapr09, myapr10, myfullgam, myyint, myphi, mybtautau, mytauyint, mytauphi, mytwophofrac = ggfits[1].values
    elif runsummary[r].res == 2:
      myarea, myrmsbeam, myback, mymay29, myjun11, myjun12, myjul10, myjul24, myaug07, myfullgam, myyint, myphi, mybtautau, mytauyint, mytauphi, mytwophofrac, myu1area = ggfits[2].values
    elif runsummary[r].res == 3:
      myarea, myrmsbeam, myback, mynov28, mydec05, mydec12, mydec19, mydec26, myjan02, myjan09, myfullgam, myyint, myphi, mybtautau, mytauyint, mytauphi, mytwophofrac, myu1area, myu2area = ggfits[3].values

    if r in mycarefulscan:
      h += therun.hadroncool_vstime.sum(0.,0.99)
      e += therun.beamgase_vstime.sum(0.,0.99)
      p += therun.beamgasp_vstime.sum(0.,0.99)
      c += therun.cosmic_vstime.sum(0.,0.99)

      if lumisource == 0:
        g += therun.gamgam_vstime.sum(0.,0.99)
      elif lumisource == 1:
        g += therun.bhabha_cosp.sum(0., 0.6) * therun.bhabha_vstime.sum(0.,0.99) / therun.bhabha

        if runsummary[r].kind != 'c':
          # eecs = e+e- cross-section = hadronic area / (1 - 3 Bmm) * Bmm * inner range
          if runsummary[r].res == 1:
            eecs = myarea * mygbwkf(9460.30, myfullgam, myrmsbeam, 0.417*bhabha_interference, 0., 2000.*runsummary[r].energy) / 0.9253 * 0.0249 * 0.672/2.66667
            g -= eecs * float(therun.gamgam) * runsummary[r].energy**2 / nbish2nb

          if runsummary[r].res == 2:
            eecs = myarea * mygbwkf(10023.26, myfullgam, myrmsbeam, 0.613*bhabha_interference, 0., 2000.*runsummary[r].energy) / 0.9391 * 0.0203 * 0.672/2.6667
            g -= eecs * float(therun.gamgam) * runsummary[r].energy**2 / nbish2nb

          if runsummary[r].res == 3:
            eecs = myarea * mygbwkf(10355.2, myfullgam, myrmsbeam, 0.486*bhabha_interference, 0., 2000.*runsummary[r].energy) / 0.9283 * 0.0239 * 0.672/2.6667
            g -= eecs * float(therun.gamgam) * runsummary[r].energy**2 / nbish2nb

      elif lumisource == 2:
        g += therun.bhabha_cosp.sum(0.6, 0.8) * therun.bhabha_vstime.sum(0.,0.99) / therun.bhabha

        if runsummary[r].kind != 'c':
          # eecs = e+e- cross-section = hadronic area / (1 - 3 Bmm) * Bmm * outer range
          if runsummary[r].res == 1:
            eecs = myarea * mygbwkf(9460.30, myfullgam, myrmsbeam, 0.588*bhabha_interference, 0., 2000.*runsummary[r].energy) / 0.9253 * 0.0249 * 0.298667/2.66667
            g -= eecs * float(therun.gamgam) * runsummary[r].energy**2 / nbish2nb

          if runsummary[r].res == 2:
            eecs = myarea * mygbwkf(10023.26, myfullgam, myrmsbeam, 0.864*bhabha_interference, 0., 2000.*runsummary[r].energy) / 0.9391 * 0.0203 * 0.298667/2.6667
            g -= eecs * float(therun.gamgam) * runsummary[r].energy**2 / nbish2nb

          if runsummary[r].res == 3:
            eecs = myarea * mygbwkf(10355.2, myfullgam, myrmsbeam, 0.686*bhabha_interference, 0., 2000.*runsummary[r].energy) / 0.9283 * 0.0239 * 0.298667/2.6667
            g -= eecs * float(therun.gamgam) * runsummary[r].energy**2 / nbish2nb

    else:
      h += therun.hadroncool
      e += therun.beamgase
      p += therun.beamgasp
      c += therun.cosmic

      if lumisource == 0:
        g += therun.gamgam
      elif lumisource == 1:
        g += therun.bhabha_cosp.sum(0., 0.6)

        if runsummary[r].kind != 'c':
          # e+e- cross-section = hadronic area / (1 - 3 Bmm) * Bmm * inner range
          if runsummary[r].res == 1:
            eecs = myarea * mygbwkf(9460.30, myfullgam, myrmsbeam, 0.417*bhabha_interference, 0., 2000.*runsummary[r].energy) / 0.9253 * 0.0249 * 0.672/2.66667
            g -= eecs * float(therun.gamgam) * runsummary[r].energy**2 / nbish2nb

          if runsummary[r].res == 2:
            eecs = myarea * mygbwkf(10023.26, myfullgam, myrmsbeam, 0.613*bhabha_interference, 0., 2000.*runsummary[r].energy) / 0.9391 * 0.0203 * 0.672/2.6667
            g -= eecs * float(therun.gamgam) * runsummary[r].energy**2 / nbish2nb

          if runsummary[r].res == 3:
            eecs = myarea * mygbwkf(10355.2, myfullgam, myrmsbeam, 0.486*bhabha_interference, 0., 2000.*runsummary[r].energy) / 0.9283 * 0.0239 * 0.672/2.6667
            g -= eecs * float(therun.gamgam) * runsummary[r].energy**2 / nbish2nb

      elif lumisource == 2:
        g += therun.bhabha_cosp.sum(0.6, 0.8)

        if runsummary[r].kind != 'c':
          # e+e- cross-section = hadronic area / (1 - 3 Bmm) * Bmm * outer range
          if runsummary[r].res == 1:
            eecs = myarea * mygbwkf(9460.30, myfullgam, myrmsbeam, 0.588*bhabha_interference, 0., 2000.*runsummary[r].energy) / 0.9253 * 0.0249 * 0.298667/2.66667
            g -= eecs * float(therun.gamgam) * runsummary[r].energy**2 / nbish2nb

          if runsummary[r].res == 2:
            eecs = myarea * mygbwkf(10023.26, myfullgam, myrmsbeam, 0.864*bhabha_interference, 0., 2000.*runsummary[r].energy) / 0.9391 * 0.0203 * 0.298667/2.6667
            g -= eecs * float(therun.gamgam) * runsummary[r].energy**2 / nbish2nb

          if runsummary[r].res == 3:
            eecs = myarea * mygbwkf(10355.2, myfullgam, myrmsbeam, 0.686*bhabha_interference, 0., 2000.*runsummary[r].energy) / 0.9283 * 0.0239 * 0.298667/2.6667
            g -= eecs * float(therun.gamgam) * runsummary[r].energy**2 / nbish2nb

  average_energy = wesum / wsum

  ebkgnd = 1. * (ebeam.hadroncool - 1.*nobeam.hadroncool*ebeam.cosmic/nobeam.cosmic) * e / ebeam.beamgase
  pbkgnd = 1. * (pbeam.hadroncool - 1.*nobeam.hadroncool*pbeam.cosmic/nobeam.cosmic) * p / pbeam.beamgasp
  cbkgnd = 1. * nobeam.hadroncool * c / nobeam.cosmic

  hadrons = h - ebkgnd/2. - pbkgnd/2. - cbkgnd
  hadrons_err = sqrt(h + c * (1.*nobeam.hadroncool/nobeam.cosmic)**2 + ebkgnd/2. + pbkgnd/2.)

  cs = hadrons / g / average_energy**2 * nbish2nb
  cs_err = cs * sqrt((1.*hadrons_err / hadrons)**2 + 1./g)

  if lumisource == 1:
    cs /= 0.23684
    cs_err /= 0.23684

  if lumisource == 2:
    cs /= 0.118999
    cs_err /= 0.118999

  return average_energy, cs, cs_err

u1runs = {}
u1runs["jan30"] = setup_runs(1, 123596, 123718, limit=False)
u1runs["feb06"] = setup_runs(1, 123781, 123893, limit=False)
u1runs["feb20"] = setup_runs(1, 124102, 124214, limit=False)
u1runs["feb27"] = setup_runs(1, 124279, 124394, limit=False)
u1runs["mar06"] = setup_runs(1, 124436, 124519, limit=False)
u1runs["mar13"] = setup_runs(1, 124625, 124736, limit=False)
u1runs["apr10"] = setup_runs(1, 125303, 125416, limit=False)

u1shifts = {}
u1shifts["jan30"] = 0.621277, 0.089388
u1shifts["feb06"] = 0.0660375, 0.0851125
u1shifts["feb20"] = 0.219987, 0.102028
u1shifts["feb27"] = 0.1787539, 0.0875286
u1shifts["mar06"] = 0.18694, 0.12965
u1shifts["mar13"] = 0.559595, 0.0978411
u1shifts["apr10"] = 0.6142458, 0.0557527

ggdata = {}
bbindata = {}
bboutdata = {}
bhabha_interference = 1.0
for s in u1runs:
  ggdata[s] = get_runs(u1runs[s], lumisource=0)
  bbindata[s] = get_runs(u1runs[s], lumisource=1)
  bboutdata[s] = get_runs(u1runs[s], lumisource=2)

p = biggles.FramedPlot()

xf = Numeric.arange(9460-5, 9460+5, 0.025)
yf = map(lambda xi: u1func(318.5185, 3.78739, 0.40577*nbish2nb, 0.053, 0.01864, 0., 0.0267, 0.2, 0., 0.0792, xi), xf)
p.add(biggles.Curve(xf, yf))

x = []; y = []; dy = []; dx = []; lab = []
for s in u1runs:
  x.append(ggdata[s][0]*2000. + u1shifts[s][0])
  y.append(ggdata[s][1])
  dy.append(ggdata[s][2])
  dx.append(u1shifts[s][1])
  lab.append(s)
p.add(biggles.Points(x, y, symboltype="filled circle", symbolsize=1))
p.add(biggles.SymmetricErrorBarsX(x, y, dx))
p.add(biggles.SymmetricErrorBarsY(x, y, dy))

# x = []; y = []; dy = []; dx = []; lab = []
# for s in u1runs:
#   x.append(bbindata[s][0]*2000. + u1shifts[s][0])
#   y.append(bbindata[s][1])
#   dy.append(bbindata[s][2])
#   dx.append(u1shifts[s][1])
#   lab.append(s)
# p.add(biggles.Points(x, y, symboltype="filled circle", symbolsize=1, color="blue"))
# p.add(biggles.SymmetricErrorBarsX(x, y, dx, color="blue"))
# p.add(biggles.SymmetricErrorBarsY(x, y, dy, color="blue"))

x = []; y = []; dy = []; dx = []; lab = []
for s in u1runs:
  x.append(bboutdata[s][0]*2000. + u1shifts[s][0])
  y.append(bboutdata[s][1])
  dy.append(bboutdata[s][2])
  dx.append(u1shifts[s][1])
  lab.append(s)
p.add(biggles.Points(x, y, symboltype="filled circle", symbolsize=1, color="red"))
p.add(biggles.SymmetricErrorBarsX(x, y, dx, color="red"))
p.add(biggles.SymmetricErrorBarsY(x, y, dy, color="red"))

p.x1.range = 9460.2, 9461.4
p.x1.ticks = Numeric.arange(9460.2, 9461.4+0.2, 0.2)
p.x1.label = r"2 $\times$ beam energy (MeV)"
p.y1.range = 25., 26.7
p.y1.label = r"Cross-section (nb)"
p.aspect_ratio = 0.8
p.show()
p.write_eps("plots/stability4_unlimited.eps")

#############################################################

p = biggles.FramedPlot()
x = [99.8, 100., 100., 100.2]
dx = [0.16, 0.16, 0.16, 0.16]
y = [97.9, 99.3, 100., 99.5]
dy = [0.3, 0.4, 0.3, 0.3]
p.add(biggles.Points(x, y, symboltype="filled circle", symbolsize=1.5))
p.add(biggles.SymmetricErrorBarsX(x, y, dx))
p.add(biggles.SymmetricErrorBarsY(x, y, dy))
p.x1.range = 99.4, 100.601
p.x1.label = "simulated beam energy spread"
p.y1.range = 96.5, 101.5
p.y1.label = "measured beam energy spread"
p.aspect_ratio = 0.8
p.show()
p.write_eps("plots/cesrv_correlation.eps")

#############################################################

myarea, myrmsbeam, myback, myjan16, myjan30, myfeb06, myfeb13, myfeb20, myfeb27, mymar06, mymar13, myapr03, myapr08, myapr09, myapr10, myfullgam, myyint, myphi, mybtautau, mytauyint, mytauphi, mytwophofrac = ggfits[1].values

x = Numeric.arange(9460.-30., 9460.+30., 0.1)
y = Numeric.arange(9460.-30., 9460.+30., 0.1)
y = map(lambda en: 8.686*9460.30**2/en**2 + myarea * mygbwkf(9460.30, myfullgam, myrmsbeam, 0.588, 0., en) / 0.9253 * 0.0249 * 0.298667/2.66667, y)
x2 = Numeric.arange(9460.-30., 9460.+30., 0.1)
y2 = Numeric.arange(9460.-30., 9460.+30., 0.1)
y2 = map(lambda en: 8.686*9460.30**2/en**2 + myarea * mygbwkf(9460.30, myfullgam, myrmsbeam, 0., 0., en) / 0.9253 * 0.0249 * 0.298667/2.66667, y2)

p = biggles.FramedArray(2,1)
p[0,0].add(biggles.Curve(x2, y2, linetype="dashed"))
p[0,0].add(biggles.Curve(x, y))
p[1,0].add(biggles.Curve(x, y))
p.xrange = 9460.-30., 9460.+30.
p[0,0].yrange = 8.6, 8.8
p[1,0].yrange = 0., 9.9999
p.xlabel = r"2 $\times$ beam energy (MeV)"
p.ylabel = r"outer $e^+e^-$ effective cross-section (nb)"
p.aspect_ratio = 0.8
p.show()
p.write_eps("plots/bbout_effective_crosssection.eps")


p = biggles.FramedPlot()
p.add(biggles.Curve(x2, y2, linetype="dashed"))
p.add(biggles.Curve(x, y))
p.xrange = 9459.6875908166221, 9461.8265039232774
p.yrange = Numeric.array([24.482067285271594, 26.736764571284123])*8.735/25.
p.show()

#################################################

execfile("/home/mccann/antithesis/utilities.py")
import biggles, Numeric

x = Numeric.arange(-1, 1, 0.05)
y = map(lambda xi: 200*(1+xi**2), x)

p = getdb(123369).bhabha_cosp.plot()
p.aspect_ratio = 0.5
p.x1.label = r"cos$\theta_+$"
p.add(getdb(123369).bhabha_cosp.stepsfill(0., 0.6))
p.add(biggles.LineX(0., linetype="dashed"))
p.add(biggles.LineX(0.6, linetype="dashed"))
p.add(getdb(123369).bhabha_cosp.steps())
p.add(biggles.Curve(x, y, linetype="dotted"))
p.y1.draw_ticklabels = 0
p.x1.ticklabels_style["fontsize"] = 5.
p.x1.label_style["fontsize"] = 5.
p.show()
p.write_eps("plots/draw_innerbb.eps")

p = getdb(123369).bhabha_cosp.plot()
p.aspect_ratio = 0.5
p.x1.label = r"cos$\theta_+$"
p.add(getdb(123369).bhabha_cosp.stepsfill(0.6, 0.8))
p.add(biggles.LineX(0.6, linetype="dashed"))
p.add(biggles.LineX(0.8, linetype="dashed"))
p.add(getdb(123369).bhabha_cosp.steps())
p.add(biggles.Curve(x, y, linetype="dotted"))
p.y1.draw_ticklabels = 0
p.x1.ticklabels_style["fontsize"] = 5.
p.x1.label_style["fontsize"] = 5.
p.show()
p.write_eps("plots/draw_outerbb.eps")


