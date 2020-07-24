from minuit import *
execfile("utilities.py")
nobeam = getsb("cos")
ebeam = getsb("bge")
pbeam = getsb("bgp")
import gbwkf
import gbwkftau
import random, sys
jitter = float(sys.argv[1])

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

def u1func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, w):
  tmp = 0.
  tmp += area * (1.-btautau) * mygbwkf(9460.30, fullgam, rmsbeam, yint, phi, w)
  tmp += area * btautau * mygbwkftau(9460.30, fullgam, rmsbeam, tauyint, tauphi, w)
  tmp += back * (1.-twophofrac) * 9000.**2 / w**2
  tmp += back * twophofrac * log(w**2/9000.**2)
  return tmp

def u2func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, w):
  tmp = 0.
  tmp += area * (1.-btautau) * mygbwkf(10023.26, fullgam, rmsbeam, yint, phi, w)
  tmp += area * btautau * mygbwkftau(10023.26, fullgam, rmsbeam, tauyint, tauphi, w)
  tmp += back * (1.-twophofrac) * 9000.**2 / w**2
  tmp += back * twophofrac * log(w**2/9000.**2)
  tmp += u1area * mygbwkf(9460.30, 0., 0., 0., 0., w)
  return tmp

def u3func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area, w):
  tmp = 0.
  tmp += area * (1.-btautau) * mygbwkf(10355.2, fullgam, rmsbeam, yint, phi, w)
  tmp += area * btautau * mygbwkftau(10355.2, fullgam, rmsbeam, tauyint, tauphi, w)
  tmp += back * (1.-twophofrac) * 9000.**2 / w**2
  tmp += back * twophofrac * log(w**2/9000.**2)
  tmp += u1area * mygbwkf(9460.30, 0., 0., 0., 0., w)
  tmp += u2area * mygbwkf(10023.26, 0., 0., 0., 0., w)
  return tmp

def get_runs(runs, usebhabha=False, energycorrection=True):
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
    
    if usebhabha:
      ngg = therun.bhabha
      if r in mycarefulscan: ngg = therun.bhabha_vstime.sum(0.,0.99)

    wsum += float(ngg)
    wesum += float(ngg) * runsummary[r].energy
#    print "    run", r, "energy =", runsummary[r].energy, "gamgams =", ngg

    if r in mycarefulscan:
      g += therun.gamgam_vstime.sum(0.,0.99)
      h += therun.hadroncool_vstime.sum(0.,0.99)
      e += therun.beamgase_vstime.sum(0.,0.99)
      p += therun.beamgasp_vstime.sum(0.,0.99)
      c += therun.cosmic_vstime.sum(0.,0.99)

      if usebhabha:
        g -= therun.gamgam_vstime.sum(0.,0.99)
        g += therun.bhabha_vstime.sum(0.,0.99)
    else:
      g += therun.gamgam
      h += therun.hadroncool
      e += therun.beamgase
      p += therun.beamgasp
      c += therun.cosmic

      if usebhabha:
        g -= therun.gamgam
        g += therun.bhabha

  average_energy = wesum / wsum
#  print "  Average energy is", average_energy

  ebkgnd = 1. * (ebeam.hadroncool - 1.*nobeam.hadroncool*ebeam.cosmic/nobeam.cosmic) * e / ebeam.beamgase
  pbkgnd = 1. * (pbeam.hadroncool - 1.*nobeam.hadroncool*pbeam.cosmic/nobeam.cosmic) * p / pbeam.beamgasp
  cbkgnd = 1. * nobeam.hadroncool * c / nobeam.cosmic

  hadrons = h - ebkgnd/2. - pbkgnd/2. - cbkgnd
  hadrons_err = sqrt(h + c * (1.*nobeam.hadroncool/nobeam.cosmic)**2 + ebkgnd/2. + pbkgnd/2.)
#  print "  Corrected number of hadrons is", hadrons, "+/-", hadrons_err
#  print "  Number of gamgams is", g

  cs = hadrons / g
  if energycorrection: cs *= 1./average_energy**2

  cs_err = cs * sqrt((1.*hadrons_err / hadrons)**2 + 1./g)
#  print "  Relative cross-section is", cs, "+/-", cs_err

  return average_energy, cs, cs_err

u1runs = {}
u2runs = {}
u3runs = {}
u1data = {}
u2data = {}
u3data = {}

u1runs["cont"] = []
u2runs["cont"] = []
u3runs["cont"] = []
for r in initialrunlist:
  if r not in mybadruns:
    if runsummary[r].res == 1 and runsummary[r].kind == 'c':
      u1runs["cont"].append(r)
    if runsummary[r].res == 2 and runsummary[r].kind == 'c':
      u2runs["cont"].append(r)
    if runsummary[r].res == 3 and runsummary[r].kind == 'c':
      u3runs["cont"].append(r)

u1runs["high"] = []
u2runs["high"] = []
u3runs["high"] = []
for r in initialrunlist:
  if r not in mybadruns:
    if runsummary[r].res == 1 and runsummary[r].kind == 'h':
      u1runs["high"].append(r)
    if runsummary[r].res == 2 and runsummary[r].kind == 'h':
      u2runs["high"].append(r)
    if runsummary[r].res == 3 and runsummary[r].kind == 'h':
      u3runs["high"].append(r)

u1data["cont"] = [get_runs(u1runs["cont"])]
u2data["cont"] = [get_runs(u2runs["cont"])]
u3data["cont"] = [get_runs(u3runs["cont"])]

u1data["high"] = [get_runs(u1runs["high"])]
u2data["high"] = [get_runs(u2runs["high"])]
u3data["high"] = [get_runs(u3runs["high"])]

def setup_runs(res, low, high):
  tmpruns = []
  for r in initialrunlist:
    if r not in mybadruns and low <= r <= high and runsummary[r].res == res:
      if runsummary[r].kind == 's' or runsummary[r].kind == 'p':
        tmpruns.append(r)
  return tmpruns

u1runs["jan16"] = setup_runs(1, 123164, 123178)
u1runs["jan30"] = setup_runs(1, 123596, 123718)
u1runs["feb06"] = setup_runs(1, 123781, 123893)
u1runs["feb13"] = setup_runs(1, 124080, 124092)
u1runs["feb20"] = setup_runs(1, 124102, 124214)
u1runs["feb27"] = setup_runs(1, 124279, 124394)
u1runs["mar06"] = setup_runs(1, 124436, 124519)
u1runs["mar13"] = setup_runs(1, 124625, 124736)
u1runs["apr03"] = setup_runs(1, 125119, 125127)
u1runs["apr08"] = setup_runs(1, 125254, 125262)
u1runs["apr09"] = setup_runs(1, 125285, 125295)
u1runs["apr10"] = setup_runs(1, 125303, 125416)

u2runs["may29"] = setup_runs(2, 126449, 126568)
u2runs["jun11"] = setup_runs(2, 126776, 126783)
u2runs["jun12"] = setup_runs(2, 126814, 126915)
u2runs["jul10"] = setup_runs(2, 127588, 127615)
u2runs["jul24"] = setup_runs(2, 127924, 127933)
u2runs["aug07"] = setup_runs(2, 128303, 128316)

u3runs["nov28"] = setup_runs(3, 121884, 122007)
u3runs["dec05"] = setup_runs(3, 122069, 122178)
u3runs["dec12"] = setup_runs(3, 122245, 122326)
u3runs["dec19"] = setup_runs(3, 122409, 122527)
u3runs["dec26"] = setup_runs(3, 122535, 122757)
u3runs["jan02"] = setup_runs(3, 122766, 122881)
u3runs["jan09"] = setup_runs(3, 122993, 123101)

def setup_data(runs, fudge=1.):
  calibration = 0.
  tmpdata = []
  for r in runs:
    e, cs, cserr = get_runs([r])

    calibration += random.gauss(0., jitter/2000.)
    e += calibration

    cserr *= fudge
    tmpdata.append((e, cs, cserr))
  return tmpdata

def chicontrib(data, shift, f):
  chi = 0.
  for en, cs, cserr in data:
    chi += (f(en*2000. + shift) - cs)**2 / cserr**2
  return chi

def u1fit(area, rmsbeam, back, jan16, jan30, feb06, feb13, feb20, feb27, mar06, mar13, apr03, apr08, apr09, apr10, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac):
  chi = 0.
  chi += chicontrib(u1data["cont"], 0., lambda w: u1func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, w))
  chi += chicontrib(u1data["high"], 0., lambda w: u1func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, w))
  chi += chicontrib(u1data["jan16"], jan16, lambda w: u1func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, w))
  chi += chicontrib(u1data["jan30"], jan30, lambda w: u1func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, w))
  chi += chicontrib(u1data["feb06"], feb06, lambda w: u1func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, w))
  chi += chicontrib(u1data["feb13"], feb13, lambda w: u1func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, w))
  chi += chicontrib(u1data["feb20"], feb20, lambda w: u1func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, w))
  chi += chicontrib(u1data["feb27"], feb27, lambda w: u1func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, w))
  chi += chicontrib(u1data["mar06"], mar06, lambda w: u1func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, w))
  chi += chicontrib(u1data["mar13"], mar13, lambda w: u1func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, w))
  chi += chicontrib(u1data["apr03"], apr03, lambda w: u1func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, w))
  chi += chicontrib(u1data["apr08"], apr08, lambda w: u1func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, w))
  chi += chicontrib(u1data["apr09"], apr09, lambda w: u1func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, w))
  chi += chicontrib(u1data["apr10"], apr10, lambda w: u1func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, w))
  return chi

def u2fit(area, rmsbeam, back, may29, jun11, jun12, jul10, jul24, aug07, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area):
  chi = 0.
  chi += chicontrib(u2data["cont"], 0., lambda w: u2func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, w))
  chi += chicontrib(u2data["high"], 0., lambda w: u2func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, w))
  chi += chicontrib(u2data["may29"], may29, lambda w: u2func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, w))
  chi += chicontrib(u2data["jun11"], jun11, lambda w: u2func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, w))
  chi += chicontrib(u2data["jun12"], jun12, lambda w: u2func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, w))
  chi += chicontrib(u2data["jul10"], jul10, lambda w: u2func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, w))
  chi += chicontrib(u2data["jul24"], jul24, lambda w: u2func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, w))
  chi += chicontrib(u2data["aug07"], aug07, lambda w: u2func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, w))
  return chi

def u3fit(area, rmsbeam, back, nov28, dec05, dec12, dec19, dec26, jan02, jan09, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area):
  chi = 0.
  chi += chicontrib(u3data["cont"], 0., lambda w: u3func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area, w))
  chi += chicontrib(u3data["high"], 0., lambda w: u3func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area, w))
  chi += chicontrib(u3data["nov28"], nov28, lambda w: u3func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area, w))
  chi += chicontrib(u3data["dec05"], dec05, lambda w: u3func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area, w))
  chi += chicontrib(u3data["dec12"], dec12, lambda w: u3func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area, w))
  chi += chicontrib(u3data["dec19"], dec19, lambda w: u3func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area, w))
  chi += chicontrib(u3data["dec26"], dec26, lambda w: u3func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area, w))
  chi += chicontrib(u3data["jan02"], jan02, lambda w: u3func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area, w))
  chi += chicontrib(u3data["jan09"], jan09, lambda w: u3func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area, w))
  return chi

u1data["jan16"] = setup_data(u1runs["jan16"])
u1data["jan30"] = setup_data(u1runs["jan30"])
u1data["feb06"] = setup_data(u1runs["feb06"])
u1data["feb13"] = setup_data(u1runs["feb13"])
u1data["feb20"] = setup_data(u1runs["feb20"])
u1data["feb27"] = setup_data(u1runs["feb27"])
u1data["mar06"] = setup_data(u1runs["mar06"])
u1data["mar13"] = setup_data(u1runs["mar13"])
u1data["apr03"] = setup_data(u1runs["apr03"])
u1data["apr08"] = setup_data(u1runs["apr08"])
u1data["apr09"] = setup_data(u1runs["apr09"])
u1data["apr10"] = setup_data(u1runs["apr10"])

u1fitter = Minuit(u1fit)
u1fitter.values = [13.7, 3.79, 0.404, 0.25, 0.63, 0.076, 0.066, 0.23, 0.19, 0.20, 0.57, 0.92, 0.80, 0.46, 0.62, 0.053, 0.01864, 0., 0.0267, 0.20, 0., 0.0792]
u1fitter.fix(range(u1fitter.npar))
u1fitter.release(["area", "rmsbeam", "back"])
u1fitter.release(["jan16", "jan30", "feb06", "feb13", "feb20", "feb27", "mar06", "mar13", "apr03", "apr08", "apr09", "apr10"])
u1fitter.migrad()
print "1s under jitter", jitter, "=", u1fitter.values[0], "with chi^2", u1fitter.fval

u2data["may29"] = setup_data(u2runs["may29"], fudge=1.2)
u2data["jun11"] = setup_data(u2runs["jun11"], fudge=1.2)
u2data["jun12"] = setup_data(u2runs["jun12"], fudge=1.2)
u2data["jul10"] = setup_data(u2runs["jul10"], fudge=1.2)
u2data["jul24"] = setup_data(u2runs["jul24"], fudge=1.2)
u2data["aug07"] = setup_data(u2runs["aug07"], fudge=1.2)

u2fitter = Minuit(u2fit)
u2fitter.values = [5.59, 4.17, 0.405, -1.12, -1.05, -1.41, -0.75, -0.65, -0.39, 0.043, 0.01792, 0., 0.017, 0.37, 0., 0.0792, u1fitter.values[0]]
u2fitter.fix(range(u2fitter.npar))
u2fitter.release(["area", "rmsbeam", "back"])
u2fitter.release(["may29", "jun11", "jun12", "jul10", "jul24", "aug07"])
u2fitter.migrad()
print "2s under jitter", jitter, "=", u2fitter.values[0], "with chi^2", u2fitter.fval

u3data["nov28"] = setup_data(u3runs["nov28"])
u3data["dec05"] = setup_data(u3runs["dec05"])
u3data["dec12"] = setup_data(u3runs["dec12"])
u3data["dec19"] = setup_data(u3runs["dec19"])
u3data["dec26"] = setup_data(u3runs["dec26"])
u3data["jan02"] = setup_data(u3runs["jan02"])
u3data["jan09"] = setup_data(u3runs["jan09"])

u3fitter = Minuit(u3fit)
u3fitter.values = [3.58, 4.48, 0.404, -2.12, -3.99, -3.18, -2.46, -2.72, -2.55, -2.64, 0.0263, 0.01823, 0., 0.0239, 0.27, 0., 0.0792, u1fitter.values[0], u2fitter.values[0]]
u3fitter.fix(range(u3fitter.npar))
u3fitter.release(["area", "rmsbeam", "back"])
u3fitter.release(["nov28", "dec05", "dec12", "dec19", "dec26", "jan02", "jan09"])
u3fitter.migrad()
print "3s under jitter", jitter, "=", u3fitter.values[0], "with chi^2", u3fitter.fval
