execfile("/home/mccann/antithesis/utilities.py")
nobeam = getsb("cos")
ebeam = getsb("bge")
pbeam = getsb("bgp")
import gbwkf, gbwkftau, gbwkfee
runstart = pickle.load(open("/home/mccann/antithesis/old_dotps/runstart.p"))
runend = pickle.load(open("/home/mccann/antithesis/old_dotps/runend.p"))
import time

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

def setup_runs(res, low, high):
  tmpruns = []
  for r in initialrunlist:
    if r not in mybadruns and low <= r <= high and runsummary[r].res == res:
      if runsummary[r].kind == 'p':
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

def u1func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, w, lumisource=0):
  tmp = 0.
  upsilon = area * 0.9757 * mygbwkf(9460.30, fullgam, rmsbeam, yint, phi, w)
  tmp += upsilon
  tmp += area * 0.578 * btautau * mygbwkftau(9460.30, fullgam, rmsbeam, tauyint, tauphi, w)
  tmp += back * (1.-twophofrac) * 9000.**2 / w**2
  tmp += back * twophofrac * log(w**2/9000.**2)

  # see 21 Sep 2005 in notes (first page of blue #14)
  if lumisource == 1:
    tmp /= (1. + upsilon/0.9253*0.0249*0.252*0.23684/1.038558)
  elif lumisource == 2:
    tmp /= (1. + upsilon/0.9253*0.0249*0.112*0.118999/1.038558)
  return tmp

def get_runs(runs, lumisource=0):
  g = 0
  h = 0
  e = 0
  p = 0
  c = 0
  wsum = 0.
  wesum = 0.
  for r in runs:
    therun = getdb(r)
    ngg = therun.gamgam
    if r in mycarefulscan: ngg = therun.gamgam_vstime.sum(0.,0.99)
    wsum += float(ngg)
    wesum += float(ngg) * runsummary[r].energy

    h += therun.hadroncool
    e += therun.beamgase
    p += therun.beamgasp
    c += therun.cosmic

    if lumisource == 0:
      g += therun.gamgam
    elif lumisource == 1:
      g += therun.bhabha_cosp.sum(0., 0.6)
    elif lumisource == 2:
      g += therun.bhabha_cosp.sum(0.6, 0.8)

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
u1runs["jan30"] = setup_runs(1, 123596, 123718)
u1runs["feb06"] = setup_runs(1, 123781, 123893)
u1runs["feb20"] = setup_runs(1, 124102, 124214)
u1runs["feb27"] = setup_runs(1, 124279, 124394)
u1runs["mar06"] = setup_runs(1, 124436, 124519)
u1runs["mar13"] = setup_runs(1, 124625, 124736)
u1runs["apr10"] = setup_runs(1, 125303, 125416)

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
for s in u1runs:
  ggdata[s] = get_runs(u1runs[s], lumisource=0)
  bbindata[s] = get_runs(u1runs[s], lumisource=1)
  bboutdata[s] = get_runs(u1runs[s], lumisource=2)

# clf()

x = []; y = []; dy = []; dx = []; lab = []
for s in u1runs:
  x.append(ggdata[s][0]*2000. + u1shifts[s][0])
  y.append(ggdata[s][1])
  dy.append(ggdata[s][2])
  dx.append(u1shifts[s][1])
  lab.append(s)
errorbar(x, y, dy, dx, fmt="ok")

x = []; y = []; dy = []; dx = []; lab = []
for s in u1runs:
  x.append(bbindata[s][0]*2000. + u1shifts[s][0])
  y.append(bbindata[s][1])
  dy.append(bbindata[s][2])
  dx.append(u1shifts[s][1])
  lab.append(s)
errorbar(x, y, dy, dx, fmt="ob")

x = []; y = []; dy = []; dx = []; lab = []
for s in u1runs:
  x.append(bboutdata[s][0]*2000. + u1shifts[s][0])
  y.append(bboutdata[s][1])
  dy.append(bboutdata[s][2])
  dx.append(u1shifts[s][1])
  lab.append(s)
errorbar(x, y, dy, dx, fmt="or")

x = arange(9460-5, 9460+5, 0.025)
y = map(lambda xi: u1func(318.5185, 3.78739, 0.40577*nbish2nb, 0.053, 0.01864, 0., 0.0267, 0.2, 0., 0.0792, xi, lumisource=0), x)
hadogg = plot(x, y, "-k")
x = arange(9460-5, 9460+5, 0.025)
y = map(lambda xi: u1func(318.5185, 3.78739, 0.40577*nbish2nb, 0.053, 0.01864, 0., 0.0267, 0.2, 0., 0.0792, xi, lumisource=1), x)
hadobbin = plot(x, y, "-b")
x = arange(9460-5, 9460+5, 0.025)
y = map(lambda xi: u1func(318.5185, 3.78739, 0.40577*nbish2nb, 0.053, 0.01864, 0., 0.0267, 0.2, 0., 0.0792, xi, lumisource=2), x)
hadobbout = plot(x, y, "-r")

legend((hadogg, hadobbin, hadobbout), (r"#had/#gamgam", r"#had/#inner e+e-", r"#had/#outer e+e-"), loc=2)

axis([9459.6875908166221, 9461.8265039232774, 24.482067285271594, 26.736764571284123])
xlabel(r"Center-of-mass energy (MeV)")
ylabel(r"Cross-section (uncorrected for Upsilon -> e+e-) (nb)")

x = []; y = []; dy = []; dx = []
for s in u1runs:
  x.append(ggdata[s][0]*2000. + u1shifts[s][0])
  y.append(ggdata[s][1])
  dy.append(ggdata[s][2])
  dx.append(u1shifts[s][1])
text(x[-1]+0.1, y[-1], r"11-14 Apr")

gcf().set_figheight(6)
gcf().set_figwidth(5)
savefig("plots/stability2_thecorrections.eps")

def u1func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, w, lumisource=0):
  tmp = 0.
  upsilon = area * 0.9757 * mygbwkf(9460.30, fullgam, rmsbeam, yint, phi, w)
  tmp += upsilon
  tmp += area * 0.578 * btautau * mygbwkftau(9460.30, fullgam, rmsbeam, tauyint, tauphi, w)
  tmp += back * (1.-twophofrac) * 9000.**2 / w**2
  tmp += back * twophofrac * log(w**2/9000.**2)

  if lumisource == 1:
    upsilon = area * mygbwkfee(9460.30, fullgam, rmsbeam, 0.417, 0., w)
    tmp /= (1. + upsilon/0.9253*0.0249*0.252*0.23684/1.038558)
  elif lumisource == 2:
    upsilon = area * mygbwkfee(9460.30, fullgam, rmsbeam, 0.588, 0., w)
    tmp /= (1. + upsilon/0.9253*0.0249*0.112*0.118999/1.038558)
  return tmp

x = arange(9460-5, 9460+5, 0.025)
y = map(lambda xi: u1func(318.5185, 3.78739, 0.40577*nbish2nb, 0.053, 0.01864, 0., 0.0267, 0.2, 0., 0.0792, xi, lumisource=0), x)
hadogg = plot(x, y, "--k")
x = arange(9460-5, 9460+5, 0.025)
y = map(lambda xi: u1func(318.5185, 3.78739, 0.40577*nbish2nb, 0.053, 0.01864, 0., 0.0267, 0.2, 0., 0.0792, xi, lumisource=1), x)
hadobbin = plot(x, y, "--b")
x = arange(9460-5, 9460+5, 0.025)
y = map(lambda xi: u1func(318.5185, 3.78739, 0.40577*nbish2nb, 0.053, 0.01864, 0., 0.0267, 0.2, 0., 0.0792, xi, lumisource=2), x)
hadobbout = plot(x, y, "--r")

axis([9459.6875908166221, 9461.8265039232774, 24.482067285271594, 26.736764571284123])

gcf().set_figheight(6)
gcf().set_figwidth(5)
savefig("plots/stability2_thecorrections_withinterference.eps")
