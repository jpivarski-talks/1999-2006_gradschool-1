from minuit import *
execfile("utilities.py")
nobeam = getsb("cos")
ebeam = getsb("bge")
pbeam = getsb("bgp")
import gbwkf
import gbwkftau

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

def adddata(p, data, shift):
  x = []
  y = []
  yerr = []
  for (e, h, herr) in data:
    x.append(e*2000.+shift)
    y.append(h)
    yerr.append(herr)
  p.add(biggles.Points(x, y, symboltype="filled circle", symbolsize=0.8))
  p.add(biggles.SymmetricErrorBarsY(x, y, yerr))
#  if len(x) == 1:
#    p.add(biggles.Points(x, y, symboltype="circle", symbolsize=7.))
  return None

def adddata_pull(p, data, shift, f):
  x = []
  y = []
  for (e, h, herr) in data:
    x.append(e*2000.+shift)
    y.append((h - f(e*2000.+shift))/herr)
  p.add(biggles.Points(x, y, symboltype="filled circle", symbolsize=0.8))
  return y

def adddata_pull2(p, runs, data, shift, f):
  x = []
  y = []
  for (r, (e, h, herr)) in zip(runs, data):
    x.append(r)
    y.append((h - f(e*2000.+shift))/herr)
  p.add(biggles.Points(x, y, symboltype="filled circle", symbolsize=0.8))
  return y

runstart = pickle.load(open("old_dotps/runstart.p"))
runend = pickle.load(open("old_dotps/runend.p"))

def adddata_pull3(p, runs, data, shift, f):
  x = []
  y = []
  for (r, (e, h, herr)) in zip(runs, data):
    d = 0
    if r in runstart and r in runend:
      d = (runstart[r] + runend[r])/2.
    elif r in runstart:
      d = runstart[r]
    elif r in runend:
      d = runend[r]
    else:
      raise Exception
    x.append(d)
    y.append((h - f(e*2000.+shift))/herr)
  p.add(biggles.Points(x, y, symboltype="filled circle", symbolsize=0.8))
  return x

def addfunc(p, f, low, high, points=100., linetype="solid"):
  x = Numeric.arange(low, high+(high-low)/points, (high-low)/points)
  y = Numeric.arange(low, high+(high-low)/points, (high-low)/points)
  for i, xi in enumerate(x):
    y[i] = f(xi)
  tmp = biggles.Curve(x, y, linetype=linetype)
  p.add(tmp)
  return tmp

def u1func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, w):
  tmp = 0.
  tmp += area * 0.9868 * mygbwkf(9460.30, fullgam, rmsbeam, yint, phi, w)
  tmp += area * 0.578 * btautau * mygbwkftau(9460.30, fullgam, rmsbeam, tauyint, tauphi, w)
  tmp += back * (1.-twophofrac) * 9000.**2 / w**2
  tmp += back * twophofrac * log(w**2/9000.**2)
  return tmp

def u2func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, w):
  tmp = 0.
  tmp += area * 0.9668 * mygbwkf(10023.26, fullgam, rmsbeam, yint, phi, w)
  tmp += area * 0.578 * btautau * mygbwkftau(10023.26, fullgam, rmsbeam, tauyint, tauphi, w)
  tmp += back * (1.-twophofrac) * 9000.**2 / w**2
  tmp += back * twophofrac * log(w**2/9000.**2)
  tmp += u1area * mygbwkf(9460.30, 0., 0., 0., 0., w)
  return tmp

def u3func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area, w):
  tmp = 0.
  tmp += area * 0.9708 * mygbwkf(10355.2, fullgam, rmsbeam, yint, phi, w)
  tmp += area * 0.578 * btautau * mygbwkftau(10355.2, fullgam, rmsbeam, tauyint, tauphi, w)
  tmp += back * (1.-twophofrac) * 9000.**2 / w**2
  tmp += back * twophofrac * log(w**2/9000.**2)
  tmp += u1area * mygbwkf(9460.30, 0., 0., 0., 0., w)
  tmp += u2area * mygbwkf(10023.26, 0., 0., 0., 0., w)
  return tmp

def fakeallthree(area1, area2, area3, back, twophofrac, w):
  tmp = 0.
  tmp += back * (1.-twophofrac) * 9000.**2 / w**2
  tmp += back * twophofrac * log(w**2/9000.**2)
  if w > 9460.30+20.:
    tmp += area1 * 0.076 / (w - 9460.30)
  if w > 10023.26+10.:
    tmp += area2 * 0.076 / (w - 10023.26)
  if w > 10355.2+10.:
    tmp += area3 * 0.076 / (w - 10355.2)
  return tmp * 0.077045  # do this with bhabhas, rather than gamgams

def doallthree(back, twophofrac, w):
  tmp = 0.
  tmp += back * (1.-twophofrac) * 9000.**2 / w**2
  tmp += back * twophofrac * log(w**2/9000.**2)
  if w > 9460.30-8.:
    tmp += u1func(13.706441397531357, 3.7860955817996218, 0., 0.053, 0.018, 0.0, 0.0267, 0.2, 0.0, twophofrac, w)
  if w > 10023.26-8.:
    tmp += u2func(5.5910940385520558, 4.172051740847075, 0., 0.043, 0.018, 0.0, 0.017, 0.2, 0.0, twophofrac, 0., w)
  if w > 10355.2-8.:
    tmp += u3func(3.5871224559944799, 4.4739422571161098, 0., 0.0263, 0.018, 0.0, 0.0239, 0.2, 0., twophofrac, 0., 0., w)
  return tmp * 0.077045  # do this with bhabhas, rather than gamgams

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
# u1data["cont"] = [get_runs(u1runs["cont"], usebhabha=True)]
# u2data["cont"] = [get_runs(u2runs["cont"], usebhabha=True)]
# u3data["cont"] = [get_runs(u3runs["cont"], usebhabha=True)]

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
# u1data["high"] = [get_runs(u1runs["high"], usebhabha=True)]
# u2data["high"] = [get_runs(u2runs["high"], usebhabha=True)]
# u3data["high"] = [get_runs(u3runs["high"], usebhabha=True)]

# def fitbackgrounds(back, twophofrac):
#   chi = 0.
#   for en, cs, cserr in [u1data["cont"][0], u2data["cont"][0], u3data["cont"][0]]:
#     chi += (fakeallthree(13.706, 5.591, 3.587, back, twophofrac, en*2000.)-cs)**2/cserr**2
#   return chi

# def fitbackgrounds_naive(back):
#   chi = 0.
#   for en, cs, cserr in [u1data["cont"][0]]:
#     chi += (fakeallthree(13.706, 5.591, 3.587, back, 0., en*2000.)-cs)**2/cserr**2
#   return chi

# m = Minuit(fitbackgrounds, start=[0.41, 0.10])
# m.migrad()
# print m.fval, m.values, m.errors
# m2 = Minuit(fitbackgrounds_naive, start=[0.41])
# m2.migrad()

# p = biggles.FramedPlot()
# adddata(p, u1data["cont"], 0)
# adddata(p, u2data["cont"], 0)
# adddata(p, u3data["cont"], 0)
# adddata(p, u1data["high"], 0)
# adddata(p, u2data["high"], 0)
# adddata(p, u3data["high"], 0)
# tmp1 = addfunc(p, lambda w: doallthree(m.values[0], m.values[1], w), 9350., 10450., points=1000.)
# tmp2 = addfunc(p, lambda w: 0.077045 * m.values[0] * ((1.-m.values[1]) * 9000.**2 / w**2 + m.values[1] * log(w**2/9000.**2)), 9350., 10450., linetype="longdashed")
# tmp3 = addfunc(p, lambda w: 0.077045 * m2.values[0] * 9000.**2 / w**2, 9350., 10450., linetype="dotted")
# p.yrange = 0.021, 0.028
# p.aspect_ratio = 1.2
# p.x1.label = r"$E_{COM} in MeV$"
# p.y1.label = r"Relative Hadronic Cross-section (bhabha luminosity)"
# tmp3.label = r"Just $1/s$"
# tmp2.label = ("With (%.2f $\pm$ %.2f)%% log$(s)$" % (m.values[1]*100., m.errors[1]*100.))
# tmp1.label = r"With $\Upsilon$ tails"
# p.add(biggles.PlotKey(0.15, 0.2, [tmp3, tmp2, tmp1]))
# p.xrange = 9350., 10450.
# p.show()
# p.write_eps("/home/mccann/antithesis/fit_results/effcor_backgrounds.eps")

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
  tmpdata = []
  for r in runs:
    e, cs, cserr = get_runs([r])
    cserr *= fudge
    tmpdata.append((e, cs, cserr))
  return tmpdata

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

u2data["may29"] = setup_data(u2runs["may29"])
u2data["jun11"] = setup_data(u2runs["jun11"])
u2data["jun12"] = setup_data(u2runs["jun12"])
u2data["jul10"] = setup_data(u2runs["jul10"])
u2data["jul24"] = setup_data(u2runs["jul24"])
u2data["aug07"] = setup_data(u2runs["aug07"])

u3data["nov28"] = setup_data(u3runs["nov28"])
u3data["dec05"] = setup_data(u3runs["dec05"])
u3data["dec12"] = setup_data(u3runs["dec12"])
u3data["dec19"] = setup_data(u3runs["dec19"])
u3data["dec26"] = setup_data(u3runs["dec26"])
u3data["jan02"] = setup_data(u3runs["jan02"])
u3data["jan09"] = setup_data(u3runs["jan09"])

def u1plot(area, rmsbeam, back, jan16, jan30, feb06, feb13, feb20, feb27, mar06, mar13, apr03, apr08, apr09, apr10, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac):
  p = biggles.FramedPlot()
  adddata(p, u1data["cont"], 0.)
  adddata(p, u1data["high"], 0.)
  adddata(p, u1data["jan16"], jan16)
  adddata(p, u1data["jan30"], jan30)
  adddata(p, u1data["feb06"], feb06)
  adddata(p, u1data["feb13"], feb13)
  adddata(p, u1data["feb20"], feb20)
  adddata(p, u1data["feb27"], feb27)
  adddata(p, u1data["mar06"], mar06)
  adddata(p, u1data["mar13"], mar13)
  adddata(p, u1data["apr03"], apr03)
  adddata(p, u1data["apr08"], apr08)
  adddata(p, u1data["apr09"], apr09)
  adddata(p, u1data["apr10"], apr10)
  addfunc(p, lambda w: u1func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, w), 9420., 9580.)
  p.x1.range = 9420., 9580.
  p.y1.range = 0., 1.5
  p.aspect_ratio = 1.2
  return p

def u2plot(area, rmsbeam, back, may29, jun11, jun12, jul10, jul24, aug07, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area):
  p = biggles.FramedPlot()
  adddata(p, u2data["cont"], 0.)
  adddata(p, u2data["high"], 0.)
  adddata(p, u2data["may29"], may29)
  adddata(p, u2data["jun11"], jun11)
  adddata(p, u2data["jun12"], jun12)
  adddata(p, u2data["jul10"], jul10)
  adddata(p, u2data["jul24"], jul24)
  adddata(p, u2data["aug07"], aug07)
  addfunc(p, lambda w: u2func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, w), 9980., 10100.)
  p.x1.range = 9980., 10100.
  p.y1.range = 0., 0.8
  p.aspect_ratio = 1.2
  return p

def u3plot(area, rmsbeam, back, nov28, dec05, dec12, dec19, dec26, jan02, jan09, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area):
  p = biggles.FramedPlot()
  adddata(p, u3data["cont"], 0.)
  adddata(p, u3data["high"], 0.)
  adddata(p, u3data["nov28"], nov28)
  adddata(p, u3data["dec05"], dec05)
  adddata(p, u3data["dec12"], dec12)
  adddata(p, u3data["dec19"], dec19)
  adddata(p, u3data["dec26"], dec26)
  adddata(p, u3data["jan02"], jan02)
  adddata(p, u3data["jan09"], jan09)
  addfunc(p, lambda w: u3func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area, w), 10320., 10420.)
  p.x1.range = 10320., 10420.
  p.y1.range = 0., 0.7
  p.aspect_ratio = 1.2
  return p

def chicontrib(data, shift, f):
  chi = 0.
  for en, cs, cserr in data:
    chi += (f(en*2000. + shift) - cs)**2 / cserr**2
  return chi

def u1fit(area, rmsbeam, back, jan16, jan30, feb06, feb13, feb20, feb27, mar06, mar13, apr03, apr08, apr09, apr10, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac):
#  print area, rmsbeam, back, jan16, jan30, feb06, feb13, feb20, feb27, mar06, mar13, apr03, apr08, apr09, apr10
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
#  u1plot(area, rmsbeam, back, jan16, jan30, feb06, feb13, feb20, feb27, mar06, mar13, apr03, apr08, apr09, apr10, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac).show()
  return chi

def u2fit(area, rmsbeam, back, may29, jun11, jun12, jul10, jul24, aug07, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area):
#  print area, rmsbeam, back, may29, jun11, jun12, jul10, jul24, aug07
  chi = 0.
  chi += chicontrib(u2data["cont"], 0., lambda w: u2func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, w))
  chi += chicontrib(u2data["high"], 0., lambda w: u2func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, w))
  chi += chicontrib(u2data["may29"], may29, lambda w: u2func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, w))
  chi += chicontrib(u2data["jun11"], jun11, lambda w: u2func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, w))
  chi += chicontrib(u2data["jun12"], jun12, lambda w: u2func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, w))
  chi += chicontrib(u2data["jul10"], jul10, lambda w: u2func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, w))
  chi += chicontrib(u2data["jul24"], jul24, lambda w: u2func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, w))
  chi += chicontrib(u2data["aug07"], aug07, lambda w: u2func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, w))
#   u2plot(area, rmsbeam, back, may29, jun11, jun12, jul10, jul24, aug07, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area).show()
  return chi

def u3fit(area, rmsbeam, back, nov28, dec05, dec12, dec19, dec26, jan02, jan09, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area):
#  print area, rmsbeam, back, nov28, dec05, dec12, dec19, dec26, jan02, jan09
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
#   u3plot(area, rmsbeam, back, nov28, dec05, dec12, dec19, dec26, jan02, jan09, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area).show()
  return chi

class FitRecord: pass
fitrecord = {}
fitrecord[1] = FitRecord()
fitrecord[2] = FitRecord()
fitrecord[3] = FitRecord()

u1fitter = Minuit(u1fit)
u1fitter.values = [13.7, 3.79, 0.404, 0.25, 0.63, 0.076, 0.066, 0.23, 0.19, 0.20, 0.57, 0.92, 0.80, 0.46, 0.62, 0.053, 0.01864, 0., 0.0267, 0.20, 0., 0.0792]
u1fitter.fix(range(u1fitter.npar))
u1fitter.release(["area", "rmsbeam", "back"])
u1fitter.release(["jan16", "jan30", "feb06", "feb13", "feb20", "feb27", "mar06", "mar13", "apr03", "apr08", "apr09", "apr10"])
u1fitter.migrad()
if u1fitter.valid: u1fitter.minos("area")
print u1fitter

fitrecord[1].values = u1fitter.values[:]
fitrecord[1].errors = u1fitter.errors[:]
fitrecord[1].fval = u1fitter.fval
fitrecord[1].fmin = u1fit(*u1fitter.values)
fitrecord[1].edm = u1fitter.edm
fitrecord[1].covariance = u1fitter.covariance[:]
fitrecord[1].ncalls = u1fitter.ncalls
fitrecord[1].minos_errors = u1fitter.minos_errors[:]
fitrecord[1].whystring = u1fitter.whystring
fitrecord[1].minos_whystring = u1fitter.minos_whystring
print "1S minimum is", fitrecord[1].fmin

u2fitter = Minuit(u2fit)
u2fitter.values = [5.59, 4.17, 0.405, -1.12, -1.05, -1.41, -0.75, -0.65, -0.39, 0.043, 0.01792, 0., 0.017, 0.37, 0., 0.0792, u1fitter.values[0]]
u2fitter.fix(range(u2fitter.npar))
u2fitter.release(["area", "rmsbeam", "back"])
u2fitter.release(["may29", "jun11", "jun12", "jul10", "jul24", "aug07"])
u2fitter.migrad()
if u2fitter.valid: u2fitter.minos("area")
print u2fitter

fitrecord[2].values = u2fitter.values[:]
fitrecord[2].errors = u2fitter.errors[:]
fitrecord[2].fval = u2fitter.fval
fitrecord[2].fmin = u2fit(*u2fitter.values)
fitrecord[2].edm = u2fitter.edm
fitrecord[2].covariance = u2fitter.covariance[:]
fitrecord[2].ncalls = u2fitter.ncalls
fitrecord[2].minos_errors = u2fitter.minos_errors[:]
fitrecord[2].whystring = u2fitter.whystring
fitrecord[2].minos_whystring = u2fitter.minos_whystring
print "2S minimum is", fitrecord[2].fmin

u3fitter = Minuit(u3fit)
u3fitter.values = [3.58, 4.48, 0.404, -2.12, -3.99, -3.18, -2.46, -2.72, -2.55, -2.64, 0.0263, 0.01823, 0., 0.0239, 0.27, 0., 0.0792, u1fitter.values[0], u2fitter.values[0]]
u3fitter.fix(range(u3fitter.npar))
u3fitter.release(["area", "rmsbeam", "back"])
u3fitter.release(["nov28", "dec05", "dec12", "dec19", "dec26", "jan02", "jan09"])
u3fitter.migrad()
if u3fitter.valid: u3fitter.minos("area")
print u3fitter

fitrecord[3].values = u3fitter.values[:]
fitrecord[3].errors = u3fitter.errors[:]
fitrecord[3].fval = u3fitter.fval
fitrecord[3].fmin = u3fit(*u3fitter.values)
fitrecord[3].edm = u3fitter.edm
fitrecord[3].covariance = u3fitter.covariance[:]
fitrecord[3].ncalls = u3fitter.ncalls
fitrecord[3].minos_errors = u3fitter.minos_errors[:]
fitrecord[3].whystring = u3fitter.whystring
fitrecord[3].minos_whystring = u3fitter.minos_whystring
print "3S minimum is", fitrecord[3].fmin

# pickle.dump(fitrecord, open("/home/mccann/antithesis/fit_results/effcor2.p", 'w'))
# fitrecord = pickle.load(open("/home/mccann/antithesis/fit_results/effcor.p"))
p = biggles.Table(3,1)
p[0,0] = u1plot(*fitrecord[1].values)
p[0,0].aspect_ratio = 0.33
p[0,0].add(biggles.PlotLabel(0.1,0.8,"(a)"))
p[0,0].y1.label = r"$\propto$ Hadronic Cross-section"
p[0,0].x1.label = r"Center-of-mass energy (2 $\times$ beam energy) in MeV"
p[1,0] = u2plot(*fitrecord[2].values)
p[1,0].aspect_ratio = 0.33
p[1,0].add(biggles.PlotLabel(0.1,0.8,"(b)"))
p[1,0].y1.label = r"$\propto$ Hadronic Cross-section"
p[1,0].x1.label = r"Center-of-mass energy (2 $\times$ beam energy) in MeV"
p[2,0] = u3plot(*fitrecord[3].values)
p[2,0].aspect_ratio = 0.33
p[2,0].add(biggles.PlotLabel(0.1,0.8,"(c)"))
p[2,0].y1.label = r"$\propto$ Hadronic Cross-section"
p[2,0].x1.label = r"Center-of-mass energy (2 $\times$ beam energy) in MeV"
p.aspect_ratio = 1.2
p.write_eps("/home/mccann/antithesis/fit_results/effcor_allfit.eps")

# u1plot(*u1fitter.values).show()
u1plot(*u1fitter.values).write_eps("/home/mccann/antithesis/fit_results/effcor2_1fit.eps")

# u2plot(*u2fitter.values).show()
u2plot(*u2fitter.values).write_eps("/home/mccann/antithesis/fit_results/effcor2_2fit.eps")

# u3plot(*u3fitter.values).show()
u3plot(*u3fitter.values).write_eps("/home/mccann/antithesis/fit_results/effcor2_3fit.eps")

def dofitgauss(h):
  def gauss(a,m,s, x): return a*exp(-(x-m)**2/2./s**2)
  def fitgauss(a,m,s):
    c = 0.
    for xlow, y, yerr in zip(h.frame, h.vals, h.errs):
      if yerr > 0.:
        x = xlow + (h.high - h.frame[-1])/2.
        c += (y - gauss(a,m,s, x))**2 / yerr**2
    return c
  m = Minuit(fitgauss, start=[10., 0., 1.])
  m.migrad()
  return m.values[2], lambda x: gauss(m.values[0], m.values[1], m.values[2], x)

import time

dticks = []
dlabels = []
for y in (2001, 2002):
  for m in Numeric.array(range(12))+1:
    for d in [1, 8, 15, 22]:
      dticks.append(time.mktime(time.strptime("%02d %02d %4d" % (m, d, y), "%m %d %Y")))
for y in (2001, 2002):
  for m in ("Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"):
    for d in [1, 8, 15, 22]:
      if d == 1:
        dlabels.append("%s" % (m))
      else:
        dlabels.append("%d" % (d))
dsubticks = []
for y in (2001, 2002):
  for d in Numeric.array(range(365))+1:
      dsubticks.append(time.mktime(time.strptime("%03d %4d" % (d, y), "%j %Y")))

def u1plot_pull(area, rmsbeam, back, jan16, jan30, feb06, feb13, feb20, feb27, mar06, mar13, apr03, apr08, apr09, apr10, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac):
  p = biggles.Table(3,1)
  p[0,0] = biggles.FramedPlot()
  p[2,0] = biggles.FramedPlot()
  h = hist.h1(100, -5., 5.)
  h.fill(adddata_pull(p[0,0], u1data["cont"], 0., lambda w: u1func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, w)))
  h.fill(adddata_pull(p[0,0], u1data["high"], 0., lambda w: u1func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, w)))
  h.fill(adddata_pull(p[0,0], u1data["jan16"], jan16, lambda w: u1func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, w)))
  h.fill(adddata_pull(p[0,0], u1data["jan30"], jan30, lambda w: u1func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, w)))
  h.fill(adddata_pull(p[0,0], u1data["feb06"], feb06, lambda w: u1func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, w)))
  h.fill(adddata_pull(p[0,0], u1data["feb13"], feb13, lambda w: u1func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, w)))
  h.fill(adddata_pull(p[0,0], u1data["feb20"], feb20, lambda w: u1func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, w)))
  h.fill(adddata_pull(p[0,0], u1data["feb27"], feb27, lambda w: u1func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, w)))
  h.fill(adddata_pull(p[0,0], u1data["mar06"], mar06, lambda w: u1func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, w)))
  h.fill(adddata_pull(p[0,0], u1data["mar13"], mar13, lambda w: u1func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, w)))
  h.fill(adddata_pull(p[0,0], u1data["apr03"], apr03, lambda w: u1func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, w)))
  h.fill(adddata_pull(p[0,0], u1data["apr08"], apr08, lambda w: u1func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, w)))
  h.fill(adddata_pull(p[0,0], u1data["apr09"], apr09, lambda w: u1func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, w)))
  h.fill(adddata_pull(p[0,0], u1data["apr10"], apr10, lambda w: u1func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, w)))
  dates = []
  dates += adddata_pull3(p[2,0], u1runs["jan16"], u1data["jan16"], jan16, lambda w: u1func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, w))
  dates += adddata_pull3(p[2,0], u1runs["jan30"], u1data["jan30"], jan30, lambda w: u1func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, w))
  dates += adddata_pull3(p[2,0], u1runs["feb06"], u1data["feb06"], feb06, lambda w: u1func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, w))
  dates += adddata_pull3(p[2,0], u1runs["feb13"], u1data["feb13"], feb13, lambda w: u1func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, w))
  dates += adddata_pull3(p[2,0], u1runs["feb20"], u1data["feb20"], feb20, lambda w: u1func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, w))
  dates += adddata_pull3(p[2,0], u1runs["feb27"], u1data["feb27"], feb27, lambda w: u1func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, w))
  dates += adddata_pull3(p[2,0], u1runs["mar06"], u1data["mar06"], mar06, lambda w: u1func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, w))
  dates += adddata_pull3(p[2,0], u1runs["mar13"], u1data["mar13"], mar13, lambda w: u1func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, w))
  dates += adddata_pull3(p[2,0], u1runs["apr03"], u1data["apr03"], apr03, lambda w: u1func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, w))
  dates += adddata_pull3(p[2,0], u1runs["apr08"], u1data["apr08"], apr08, lambda w: u1func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, w))
  dates += adddata_pull3(p[2,0], u1runs["apr09"], u1data["apr09"], apr09, lambda w: u1func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, w))
  dates += adddata_pull3(p[2,0], u1runs["apr10"], u1data["apr10"], apr10, lambda w: u1func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, w))
  p[2,0].add(biggles.LineY(0.))
#  p[2,0].x1.range = 123000, 125500
  p[2,0].x1.range = min(dates)-3.*24.*60.*60., max(dates)+3.*24.*60.*60.
  subticks = []
  sublabels = []
  for t, l in zip(dticks, dlabels):
    if min(dates)-3.*24.*60.*60. < t < max(dates)+3.*24.*60.*60.:
      subticks.append(t)
      sublabels.append(l)
  subsubticks = []
  for t in dsubticks:
    if min(dates)-3.*24.*60.*60. < t < max(dates)+3.*24.*60.*60.:
      subsubticks.append(t)
  p[2,0].x1.ticks = subticks
  p[2,0].x1.subticks = subsubticks
  p[2,0].x1.ticklabels = sublabels
  p[2,0].x2.ticks = subticks
  p[2,0].x2.subticks = subsubticks
  p[2,0].x2.draw_ticklabels = 0
  p[2,0].x1.label = r"Date in 2002"
  p[2,0].y1.label = r"Pull"
  p[2,0].y1.range = -5, 5
  p[0,0].y1.range = -5, 5
  p[0,0].add(biggles.LineY(0.))
  p[0,0].x1.range = 9420., 9580.
  p[0,0].x1.label = r"Center-of-mass energy (2 $\times$ beam energy) in MeV"
  p[0,0].y1.label = r"Pull"
  p[1,0] = h.plot()
  p[1,0].x1.label = r"Pull"
  h.rootn()
  width, f = dofitgauss(h)
  x = Numeric.arange(-5., 5., 0.01)
  y = Numeric.arange(-5., 5., 0.01)
  for i, xi in enumerate(x): y[i] = f(xi)
  p[1,0].add(biggles.Curve(x,y))
  entries = h.sum() + h.underflow + h.overflow
  hist.addinfobox(p[1,0], [["width", width], ["entries", entries], ["underflow", h.underflow], ["overflow", h.overflow]], width=0.25, colwidth=0.07)
  p[0,0].aspect_ratio = 0.33
  p[1,0].aspect_ratio = 0.33
  p[2,0].aspect_ratio = 0.33
  p[1,0], p[2,0] = p[2,0], p[1,0]
  p[0,0].add(biggles.PlotLabel(0.05,0.85,"(a)"))
  p[1,0].add(biggles.PlotLabel(0.05,0.85,"(b)"))
  p[2,0].add(biggles.PlotLabel(0.05,0.85,"(c)"))
  p.aspect_ratio = 1.2
  return p
# u1plot_pull(*fitrecord[1].values).show()
u1plot_pull(*fitrecord[1].values).write_eps("/home/mccann/antithesis/fit_results/effcor2_1pull.eps")

dticks = []
dlabels = []
for y in (2001, 2002):
  for m in Numeric.array(range(12))+1:
    for d in [1, 8, 15, 22]:
      dticks.append(time.mktime(time.strptime("%02d %02d %4d" % (m, d, y), "%m %d %Y")))
for y in (2001, 2002):
  for m in ("Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"):
    for d in [1, 8, 15, 22]:
      if d == 1:
        dlabels.append("%s" % (m))
      else:
        dlabels.append("%d" % (d))
dsubticks = []
for y in (2001, 2002):
  for d in Numeric.array(range(365))+1:
      dsubticks.append(time.mktime(time.strptime("%03d %4d" % (d, y), "%j %Y")))

def u2plot_pull(area, rmsbeam, back, may29, jun11, jun12, jul10, jul24, aug07, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area):
  p = biggles.Table(3,1)
  p[0,0] = biggles.FramedPlot()
  p[2,0] = biggles.FramedPlot()
  h = hist.h1(100, -5., 5.)
  h.fill(adddata_pull(p[0,0], u2data["cont"], 0., lambda w: u2func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, w)))
  h.fill(adddata_pull(p[0,0], u2data["high"], 0., lambda w: u2func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, w)))
  h.fill(adddata_pull(p[0,0], u2data["may29"], may29, lambda w: u2func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, w)))
  h.fill(adddata_pull(p[0,0], u2data["jun11"], jun11, lambda w: u2func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, w)))
  h.fill(adddata_pull(p[0,0], u2data["jun12"], jun12, lambda w: u2func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, w)))
  h.fill(adddata_pull(p[0,0], u2data["jul10"], jul10, lambda w: u2func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, w)))
  h.fill(adddata_pull(p[0,0], u2data["jul24"], jul24, lambda w: u2func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, w)))
  h.fill(adddata_pull(p[0,0], u2data["aug07"], aug07, lambda w: u2func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, w)))
  dates = []
  dates += adddata_pull3(p[2,0], u2runs["may29"], u2data["may29"], may29, lambda w: u2func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, w))
  dates += adddata_pull3(p[2,0], u2runs["jun11"], u2data["jun11"], jun11, lambda w: u2func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, w))
  dates += adddata_pull3(p[2,0], u2runs["jun12"], u2data["jun12"], jun12, lambda w: u2func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, w))
  dates += adddata_pull3(p[2,0], u2runs["jul10"], u2data["jul10"], jul10, lambda w: u2func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, w))
  dates += adddata_pull3(p[2,0], u2runs["jul24"], u2data["jul24"], jul24, lambda w: u2func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, w))
  dates += adddata_pull3(p[2,0], u2runs["aug07"], u2data["aug07"], aug07, lambda w: u2func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, w))
  p[2,0].add(biggles.LineY(0.))
#  p[2,0].x1.range = 126000, 128500
  p[2,0].x1.range = min(dates)-3.*24.*60.*60., max(dates)+3.*24.*60.*60.
  subticks = []
  sublabels = []
  for t, l in zip(dticks, dlabels):
    if min(dates)-3.*24.*60.*60. < t < max(dates)+3.*24.*60.*60.:
      subticks.append(t)
      sublabels.append(l)
  subsubticks = []
  for t in dsubticks:
    if min(dates)-3.*24.*60.*60. < t < max(dates)+3.*24.*60.*60.:
      subsubticks.append(t)
  p[2,0].x1.ticks = subticks
  p[2,0].x1.subticks = subsubticks
  p[2,0].x1.ticklabels = sublabels
  p[2,0].x2.ticks = subticks
  p[2,0].x2.subticks = subsubticks
  p[2,0].x2.draw_ticklabels = 0
  p[2,0].x1.label = r"Date in 2002"
  p[2,0].y1.label = r"Pull"
  p[2,0].y1.range = -5, 5
  p[0,0].y1.range = -5, 5
  p[0,0].add(biggles.LineY(0.))
  p[0,0].x1.range = 9980., 10100.
  p[0,0].x1.label = r"Center-of-mass energy (2 $\times$ beam energy) in MeV"
  p[0,0].y1.label = r"Pull"
  p[1,0] = h.plot()
  p[1,0].x1.label = r"Pull"
  h.rootn()
  width, f = dofitgauss(h)
  x = Numeric.arange(-5., 5., 0.01)
  y = Numeric.arange(-5., 5., 0.01)
  for i, xi in enumerate(x): y[i] = f(xi)
  p[1,0].add(biggles.Curve(x,y))
  entries = h.sum() + h.underflow + h.overflow
  hist.addinfobox(p[1,0], [["width", width], ["entries", entries], ["underflow", h.underflow], ["overflow", h.overflow]], width=0.25, colwidth=0.07)
  p[0,0].aspect_ratio = 0.33
  p[1,0].aspect_ratio = 0.33
  p[2,0].aspect_ratio = 0.33
  p[1,0], p[2,0] = p[2,0], p[1,0]
  p[0,0].add(biggles.PlotLabel(0.05,0.85,"(a)"))
  p[1,0].add(biggles.PlotLabel(0.05,0.85,"(b)"))
  p[2,0].add(biggles.PlotLabel(0.05,0.85,"(c)"))
  p.aspect_ratio = 1.2
  return p
# u2plot_pull(*u2fitter.values).show()
u2plot_pull(*fitrecord[2].values).write_eps("/home/mccann/antithesis/fit_results/effcor2_2pull.eps")

dticks = []
dlabels = []
for y in (2001, 2002):
  for m in Numeric.array(range(12))+1:
    for d in [1, 8, 15, 22]:
      dticks.append(time.mktime(time.strptime("%02d %02d %4d" % (m, d, y), "%m %d %Y")))
for y in (2001, 2002):
  for m in ("Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"):
    for d in [1, 8, 15, 22]:
      if d == 1:
        dlabels.append("%s %d" % (m, y))
      else:
        dlabels.append("%d" % (d))
dsubticks = []
for y in (2001, 2002):
  for d in Numeric.array(range(365))+1:
      dsubticks.append(time.mktime(time.strptime("%03d %4d" % (d, y), "%j %Y")))

def u3plot_pull(area, rmsbeam, back, nov28, dec05, dec12, dec19, dec26, jan02, jan09, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area):
  p = biggles.Table(3,1)
  p[0,0] = biggles.FramedPlot()
  p[2,0] = biggles.FramedPlot()
  h = hist.h1(100, -5., 5.)
  h.fill(adddata_pull(p[0,0], u3data["cont"], 0., lambda w: u3func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area, w)))
  h.fill(adddata_pull(p[0,0], u3data["high"], 0., lambda w: u3func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area, w)))
  h.fill(adddata_pull(p[0,0], u3data["nov28"], nov28, lambda w: u3func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area, w)))
  h.fill(adddata_pull(p[0,0], u3data["dec05"], dec05, lambda w: u3func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area, w)))
  h.fill(adddata_pull(p[0,0], u3data["dec12"], dec12, lambda w: u3func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area, w)))
  h.fill(adddata_pull(p[0,0], u3data["dec19"], dec19, lambda w: u3func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area, w)))
  h.fill(adddata_pull(p[0,0], u3data["dec26"], dec26, lambda w: u3func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area, w)))
  h.fill(adddata_pull(p[0,0], u3data["jan02"], jan02, lambda w: u3func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area, w)))
  h.fill(adddata_pull(p[0,0], u3data["jan09"], jan09, lambda w: u3func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area, w)))
  dates = []
  dates += adddata_pull3(p[2,0], u3runs["nov28"], u3data["nov28"], nov28, lambda w: u3func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area, w))
  dates += adddata_pull3(p[2,0], u3runs["dec05"], u3data["dec05"], dec05, lambda w: u3func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area, w))
  dates += adddata_pull3(p[2,0], u3runs["dec12"], u3data["dec12"], dec12, lambda w: u3func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area, w))
  dates += adddata_pull3(p[2,0], u3runs["dec19"], u3data["dec19"], dec19, lambda w: u3func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area, w))
  dates += adddata_pull3(p[2,0], u3runs["dec26"], u3data["dec26"], dec26, lambda w: u3func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area, w))
  dates += adddata_pull3(p[2,0], u3runs["jan02"], u3data["jan02"], jan02, lambda w: u3func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area, w))
  dates += adddata_pull3(p[2,0], u3runs["jan09"], u3data["jan09"], jan09, lambda w: u3func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area, w))
  p[2,0].add(biggles.LineY(0.))
#  p[2,0].x1.range = 121500, 123500
  p[2,0].x1.range = min(dates)-3.*24.*60.*60., max(dates)+3.*24.*60.*60.
  subticks = []
  sublabels = []
  for t, l in zip(dticks, dlabels):
    if min(dates)-3.*24.*60.*60. < t < max(dates)+3.*24.*60.*60.:
      subticks.append(t)
      sublabels.append(l)
  subsubticks = []
  for t in dsubticks:
    if min(dates)-3.*24.*60.*60. < t < max(dates)+3.*24.*60.*60.:
      subsubticks.append(t)
  p[2,0].x1.ticks = subticks
  p[2,0].x1.subticks = subsubticks
  p[2,0].x1.ticklabels = sublabels
  p[2,0].x2.ticks = subticks
  p[2,0].x2.subticks = subsubticks
  p[2,0].x2.draw_ticklabels = 0
  p[2,0].x1.label = r"Date in 2001-2002"
  p[2,0].y1.label = r"Pull"
  p[2,0].y1.range = -5, 5
  p[0,0].y1.range = -5, 5
  p[0,0].add(biggles.LineY(0.))
  p[0,0].x1.range = 10320., 10420.
  p[0,0].x1.label = r"Center-of-mass energy (2 $\times$ beam energy) in MeV"
  p[0,0].y1.label = r"Pull"
  p[1,0] = h.plot()
  p[1,0].x1.label = r"Pull"
  h.rootn()
  width, f = dofitgauss(h)
  x = Numeric.arange(-5., 5., 0.01)
  y = Numeric.arange(-5., 5., 0.01)
  for i, xi in enumerate(x): y[i] = f(xi)
  p[1,0].add(biggles.Curve(x,y))
  entries = h.sum() + h.underflow + h.overflow
  hist.addinfobox(p[1,0], [["width", width], ["entries", entries], ["underflow", h.underflow], ["overflow", h.overflow]], width=0.25, colwidth=0.07)
  p[0,0].aspect_ratio = 0.33
  p[1,0].aspect_ratio = 0.33
  p[2,0].aspect_ratio = 0.33
  p[1,0], p[2,0] = p[2,0], p[1,0]
  p[0,0].add(biggles.PlotLabel(0.05,0.85,"(a)"))
  p[1,0].add(biggles.PlotLabel(0.05,0.85,"(b)"))
  p[2,0].add(biggles.PlotLabel(0.05,0.85,"(c)"))
  p.aspect_ratio = 1.2
  return p
# u3plot_pull(*u3fitter.values).show()
u3plot_pull(*fitrecord[3].values).write_eps("/home/mccann/antithesis/fit_results/effcor2_3pull.eps")

# # def u1plot_pull2(area, rmsbeam, back, jan16, jan30, feb06, feb13, feb20, feb27, mar06, mar13, apr03, apr08, apr09, apr10, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac):
# #   p = biggles.Table(2,1)
# #   p[0,0] = biggles.FramedPlot()
# #   p[1,0] = biggles.FramedPlot()
# #   adddata_pull(p[0,0], u1data["jan16"], jan16, lambda w: u1func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, w))
# #   adddata_pull2(p[1,0], u1runs["jan16"], u1data["jan16"], jan16, lambda w: u1func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, w))
# #   adddata_pull(p[0,0], u1data["jan30"], jan30, lambda w: u1func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, w))
# #   adddata_pull2(p[1,0], u1runs["jan30"], u1data["jan30"], jan30, lambda w: u1func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, w))
# #   adddata_pull(p[0,0], u1data["feb06"], feb06, lambda w: u1func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, w))
# #   adddata_pull2(p[1,0], u1runs["feb06"], u1data["feb06"], feb06, lambda w: u1func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, w))
# #   adddata_pull(p[0,0], u1data["feb13"], feb13, lambda w: u1func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, w))
# #   adddata_pull2(p[1,0], u1runs["feb13"], u1data["feb13"], feb13, lambda w: u1func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, w))
# #   adddata_pull(p[0,0], u1data["feb20"], feb20, lambda w: u1func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, w))
# #   adddata_pull2(p[1,0], u1runs["feb20"], u1data["feb20"], feb20, lambda w: u1func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, w))
# #   adddata_pull(p[0,0], u1data["feb27"], feb27, lambda w: u1func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, w))
# #   adddata_pull2(p[1,0], u1runs["feb27"], u1data["feb27"], feb27, lambda w: u1func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, w))
# #   adddata_pull(p[0,0], u1data["mar06"], mar06, lambda w: u1func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, w))
# #   adddata_pull2(p[1,0], u1runs["mar06"], u1data["mar06"], mar06, lambda w: u1func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, w))
# #   adddata_pull(p[0,0], u1data["mar13"], mar13, lambda w: u1func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, w))
# #   adddata_pull2(p[1,0], u1runs["mar13"], u1data["mar13"], mar13, lambda w: u1func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, w))
# #   adddata_pull(p[0,0], u1data["apr03"], apr03, lambda w: u1func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, w))
# #   adddata_pull2(p[1,0], u1runs["apr03"], u1data["apr03"], apr03, lambda w: u1func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, w))
# #   adddata_pull(p[0,0], u1data["apr08"], apr08, lambda w: u1func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, w))
# #   adddata_pull2(p[1,0], u1runs["apr08"], u1data["apr08"], apr08, lambda w: u1func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, w))
# #   adddata_pull(p[0,0], u1data["apr09"], apr09, lambda w: u1func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, w))
# #   adddata_pull2(p[1,0], u1runs["apr09"], u1data["apr09"], apr09, lambda w: u1func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, w))
# #   adddata_pull(p[0,0], u1data["apr10"], apr10, lambda w: u1func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, w))
# #   adddata_pull2(p[1,0], u1runs["apr10"], u1data["apr10"], apr10, lambda w: u1func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, w))
# #   p[0,0].add(biggles.LineY(0.))
# #   p[0,0].x1.range = 9420., 9580.
# #   p[0,0].x1.label = r"$E_{COM}$ in MeV"
# #   p[0,0].y1.label = r"Pull"
# #   p[1,0].add(biggles.LineY(0.))
# #   p[1,0].x1.range = 123000, 125500
# #   p[1,0].x1.label = r"Run Number"
# #   p[1,0].y1.label = r"Pull"
# #   p[0,0].aspect_ratio = 0.5
# #   p[1,0].aspect_ratio = 0.5
# #   p.aspect_ratio = 1
# #   return p
# # u1plot_pull2(*u1fitter.values).show()
# # u1plot_pull2(*u1fitter.values).write_eps("/home/mccann/antithesis/fit_results/effcor2_1pullpull.eps")

# # def u2plot_pull2(area, rmsbeam, back, may29, jun11, jun12, jul10, jul24, aug07, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area):
# #   p = biggles.Table(2,1)
# #   p[0,0] = biggles.FramedPlot()
# #   p[1,0] = biggles.FramedPlot()
# #   adddata_pull(p[0,0], u2data["may29"], may29, lambda w: u2func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, w))
# #   adddata_pull2(p[1,0], u2runs["may29"], u2data["may29"], may29, lambda w: u2func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, w))
# #   adddata_pull(p[0,0], u2data["jun11"], jun11, lambda w: u2func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, w))
# #   adddata_pull2(p[1,0], u2runs["jun11"], u2data["jun11"], jun11, lambda w: u2func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, w))
# #   adddata_pull(p[0,0], u2data["jun12"], jun12, lambda w: u2func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, w))
# #   adddata_pull2(p[1,0], u2runs["jun12"], u2data["jun12"], jun12, lambda w: u2func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, w))
# #   adddata_pull(p[0,0], u2data["jul10"], jul10, lambda w: u2func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, w))
# #   adddata_pull2(p[1,0], u2runs["jul10"], u2data["jul10"], jul10, lambda w: u2func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, w))
# #   adddata_pull(p[0,0], u2data["jul24"], jul24, lambda w: u2func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, w))
# #   adddata_pull2(p[1,0], u2runs["jul24"], u2data["jul24"], jul24, lambda w: u2func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, w))
# #   adddata_pull(p[0,0], u2data["aug07"], aug07, lambda w: u2func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, w))
# #   adddata_pull2(p[1,0], u2runs["aug07"], u2data["aug07"], aug07, lambda w: u2func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, w))
# #   p[0,0].add(biggles.LineY(0.))
# #   p[0,0].x1.range = 9980., 10100.
# #   p[0,0].x1.label = r"$E_{COM}$ in MeV"
# #   p[0,0].y1.label = r"Pull"
# #   p[1,0].add(biggles.LineY(0.))
# #   p[1,0].x1.range = 126000, 128500
# #   p[1,0].x1.label = r"Run Number"
# #   p[1,0].y1.label = r"Pull"
# #   p[0,0].aspect_ratio = 0.5
# #   p[1,0].aspect_ratio = 0.5
# #   p.aspect_ratio = 1
# #   return p
# # u2plot_pull2(*u2fitter.values).show()
# # u2plot_pull2(*u2fitter.values).write_eps("/home/mccann/antithesis/fit_results/effcor2_2pullpull.eps")

# # def u3plot_pull2(area, rmsbeam, back, nov28, dec05, dec12, dec19, dec26, jan02, jan09, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area):
# #   p = biggles.Table(2,1)
# #   p[0,0] = biggles.FramedPlot()
# #   p[1,0] = biggles.FramedPlot()
# #   adddata_pull(p[0,0], u3data["nov28"], nov28, lambda w: u3func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area, w))
# #   adddata_pull2(p[1,0], u3runs["nov28"], u3data["nov28"], nov28, lambda w: u3func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area, w))
# #   adddata_pull(p[0,0], u3data["dec05"], dec05, lambda w: u3func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area, w))
# #   adddata_pull2(p[1,0], u3runs["dec05"], u3data["dec05"], dec05, lambda w: u3func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area, w))
# #   adddata_pull(p[0,0], u3data["dec12"], dec12, lambda w: u3func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area, w))
# #   adddata_pull2(p[1,0], u3runs["dec12"], u3data["dec12"], dec12, lambda w: u3func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area, w))
# #   adddata_pull(p[0,0], u3data["dec19"], dec19, lambda w: u3func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area, w))
# #   adddata_pull2(p[1,0], u3runs["dec19"], u3data["dec19"], dec19, lambda w: u3func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area, w))
# #   adddata_pull(p[0,0], u3data["dec26"], dec26, lambda w: u3func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area, w))
# #   adddata_pull2(p[1,0], u3runs["dec26"], u3data["dec26"], dec26, lambda w: u3func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area, w))
# #   adddata_pull(p[0,0], u3data["jan02"], jan02, lambda w: u3func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area, w))
# #   adddata_pull2(p[1,0], u3runs["jan02"], u3data["jan02"], jan02, lambda w: u3func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area, w))
# #   adddata_pull(p[0,0], u3data["jan09"], jan09, lambda w: u3func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area, w))
# #   adddata_pull2(p[1,0], u3runs["jan09"], u3data["jan09"], jan09, lambda w: u3func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area, w))
# #   p[0,0].add(biggles.LineY(0.))
# #   p[0,0].x1.range = 10320., 10420.
# #   p[0,0].x1.label = r"$E_{COM}$ in MeV"
# #   p[0,0].y1.label = r"Pull"
# #   p[1,0].add(biggles.LineY(0.))
# #   p[1,0].x1.range = 121500, 123500
# #   p[1,0].x1.label = r"Run Number"
# #   p[1,0].y1.label = r"Pull"
# #   p[0,0].aspect_ratio = 0.5
# #   p[1,0].aspect_ratio = 0.5
# #   p.aspect_ratio = 1
# #   return p
# # u3plot_pull2(*u3fitter.values).show()
# # u3plot_pull2(*u3fitter.values).write_eps("/home/mccann/antithesis/fit_results/effcor2_3pullpull.eps")

# #######################################

# # areas = Numeric.arange(u1fitter.values[0] - 3.*u1fitter.errors[0], \
# #                        u1fitter.values[0] + 3.*u1fitter.errors[0], \
# #                        6.*u1fitter.errors[0]/100.)
# # chi2s = Numeric.arange(u1fitter.values[0] - 3.*u1fitter.errors[0], \
# #                        u1fitter.values[0] + 3.*u1fitter.errors[0], \
# #                        6.*u1fitter.errors[0]/100.)
# # for i, a in enumerate(areas):
# #   tmp = u1fitter.values[:]
# #   tmp[0] = a
# #   chi2s[i] = u1fit(*tmp)

# # p = biggles.FramedPlot()
# # p.add(biggles.Curve(areas, chi2s))
# # p.add(biggles.LineY(min(chi2s)+1.))
# # p.xrange = u1fitter.values[0] - 3*u1fitter.errors[0], u1fitter.values[0] + 3*u1fitter.errors[0]
# # p.yrange = min(chi2s), max(chi2s)
# # p.x2.range = -3*u1fitter.errors[0], 3*u1fitter.errors[0]
# # p.y2.range = 0., max(chi2s) - min(chi2s)
# # # p.show()
# # p.write_eps("fit_results/effcor2_1scan.eps")

# # areas = Numeric.arange(u2fitter.values[0] - 3.*u2fitter.errors[0], \
# #                        u2fitter.values[0] + 3.*u2fitter.errors[0], \
# #                        6.*u2fitter.errors[0]/100.)
# # chi2s = Numeric.arange(u2fitter.values[0] - 3.*u2fitter.errors[0], \
# #                        u2fitter.values[0] + 3.*u2fitter.errors[0], \
# #                        6.*u2fitter.errors[0]/100.)
# # for i, a in enumerate(areas):
# #   tmp = u2fitter.values[:]
# #   tmp[0] = a
# #   chi2s[i] = u2fit(*tmp)

# # p = biggles.FramedPlot()
# # p.add(biggles.Curve(areas, chi2s))
# # p.add(biggles.LineY(min(chi2s)+1.))
# # p.xrange = u2fitter.values[0] - 3*u2fitter.errors[0], u2fitter.values[0] + 3*u2fitter.errors[0]
# # p.yrange = min(chi2s), max(chi2s)
# # p.x2.range = -3*u2fitter.errors[0], 3*u2fitter.errors[0]
# # p.y2.range = 0., max(chi2s) - min(chi2s)
# # # p.show()
# # p.write_eps("fit_results/effcor2_2scan.eps")

# # areas = Numeric.arange(u3fitter.values[0] - 3.*u3fitter.errors[0], \
# #                        u3fitter.values[0] + 3.*u3fitter.errors[0], \
# #                        6.*u3fitter.errors[0]/100.)
# # chi2s = Numeric.arange(u3fitter.values[0] - 3.*u3fitter.errors[0], \
# #                        u3fitter.values[0] + 3.*u3fitter.errors[0], \
# #                        6.*u3fitter.errors[0]/100.)
# # for i, a in enumerate(areas):
# #   tmp = u3fitter.values[:]
# #   tmp[0] = a
# #   chi2s[i] = u3fit(*tmp)

# # p = biggles.FramedPlot()
# # p.add(biggles.Curve(areas, chi2s))
# # p.add(biggles.LineY(min(chi2s)+1.))
# # p.xrange = u3fitter.values[0] - 3*u3fitter.errors[0], u3fitter.values[0] + 3*u3fitter.errors[0]
# # p.yrange = min(chi2s), max(chi2s)
# # p.x2.range = -3*u3fitter.errors[0], 3*u3fitter.errors[0]
# # p.y2.range = 0., max(chi2s) - min(chi2s)
# # # p.show()
# # p.write_eps("fit_results/effcor2_3scan.eps")

# ########### systematics studies

# print "u1 systematics studies"

# u1fitter.values[u1fitter.findpar("fullgam")] = 0.053 + 0.0015
# u1fitter.migrad()
# print "u1 fullgam: area diff =", fitrecord[1].values[0] - u1fitter.values[0]
# u1fitter.values[u1fitter.findpar("fullgam")] = 0.053

# u1fitter.values[u1fitter.findpar("yint")] = 0.01864 + 0.00060
# u1fitter.migrad()
# print "u1 yint: area diff =", fitrecord[1].values[0] - u1fitter.values[0]
# u1fitter.values[u1fitter.findpar("yint")] = 0.01864

# u1fitter.values[u1fitter.findpar("btautau")] = 0.0267 + 0.0015
# u1fitter.values[u1fitter.findpar("tauyint")] = 0.20 - 0.01
# u1fitter.migrad()
# print "u1 btautau/tauyint: area diff =", fitrecord[1].values[0] - u1fitter.values[0]
# u1fitter.values[u1fitter.findpar("btautau")] = 0.0267
# u1fitter.values[u1fitter.findpar("tauyint")] = 0.20

# u1fitter.values[u1fitter.findpar("twophofrac")] = 0.0792 + 0.0054
# u1fitter.migrad()
# print "u1 twophofrac: area diff =", fitrecord[1].values[0] - u1fitter.values[0]
# u1fitter.values[u1fitter.findpar("twophofrac")] = 0.0792

# u1fitter.values[u1fitter.findpar("btautau")] = 0.0249
# u1fitter.migrad()
# print "u1 btautau=bmumu: area = ", u1fitter.values[0]
# u1fitter.values[u1fitter.findpar("btautau")] = 0.0249 + 0.0007
# u1fitter.migrad()
# print "u1 btautau=bmumu up: area = ", u1fitter.values[0]
# u1fitter.values[u1fitter.findpar("btautau")] = 0.
# u1fitter.migrad()
# print "u1 btautau=0: area = ", u1fitter.values[0]

# u1fitter.values[u1fitter.findpar("fullgam")] = 0.
# u1fitter.values[u1fitter.findpar("yint")] = 0.
# u1fitter.values[u1fitter.findpar("tauyint")] = 0.
# u1fitter.migrad()
# print "u1 delta func: area diff =", fitrecord[1].values[0] - u1fitter.values[0]

# ####

# print "u2 systematics studies"

# u2fitter.values[u2fitter.findpar("fullgam")] = 0.043 + 0.006
# u2fitter.migrad()
# print "u2 fullgam: area diff =", fitrecord[2].values[0] - u2fitter.values[0]
# u2fitter.values[u2fitter.findpar("fullgam")] = 0.043

# u2fitter.values[u2fitter.findpar("yint")] = 0.01792 + 0.00060
# u2fitter.migrad()
# print "u2 yint: area diff =", fitrecord[2].values[0] - u2fitter.values[0]
# u2fitter.values[u2fitter.findpar("yint")] = 0.01792

# u2fitter.values[u2fitter.findpar("btautau")] = 2.*0.017
# u2fitter.values[u2fitter.findpar("tauyint")] = 0.37/2.
# u2fitter.migrad()
# print "u2 btautau/tauyint plus: area diff =", fitrecord[2].values[0] - u2fitter.values[0]
# u2fitter.values[u2fitter.findpar("btautau")] = 0.
# u2fitter.migrad()
# print "u2 btautau/tauyint minus: area diff =", fitrecord[2].values[0] - u2fitter.values[0]
# u2fitter.values[u2fitter.findpar("btautau")] = 0.017
# u2fitter.values[u2fitter.findpar("tauyint")] = 0.37

# u2fitter.values[u2fitter.findpar("twophofrac")] = 0.0792 + 0.0054
# u2fitter.migrad()
# print "u2 twophofrac: area diff =", fitrecord[2].values[0] - u2fitter.values[0]
# u2fitter.values[u2fitter.findpar("twophofrac")] = 0.0792

# u2fitter.values[u2fitter.findpar("u1area")] = fitrecord[1].values[0] + fitrecord[1].errors[0]
# u2fitter.migrad()
# print "u2 u1area: area diff =", fitrecord[2].values[0] - u2fitter.values[0]
# u2fitter.values[u2fitter.findpar("u1area")] = fitrecord[1].values[0]

# u2fitter.values[u2fitter.findpar("btautau")] = 0.0203
# u2fitter.migrad()
# print "u2 btautau=bmumu: area = ", u2fitter.values[0]

# u2fitter.values[u2fitter.findpar("btautau")] = 0.0203
# u2fitter.migrad()
# print "u2 btautau=bmumu: area = ", u2fitter.values[0]

# u2fitter.values[u2fitter.findpar("btautau")] = 0.0203
# u2fitter.migrad()
# print "u2 btautau=bmumu: area = ", u2fitter.values[0]

# u2fitter.values[u2fitter.findpar("btautau")] = 0.0203 + 0.0008
# u2fitter.migrad()
# print "u2 btautau=bmumu up: area = ", u2fitter.values[0]
# u2fitter.values[u2fitter.findpar("btautau")] = 0.
# u2fitter.migrad()
# print "u2 btautau=0: area = ", u2fitter.values[0]

# u2fitter.values[u2fitter.findpar("fullgam")] = 0.
# u2fitter.values[u2fitter.findpar("yint")] = 0.
# u2fitter.values[u2fitter.findpar("tauyint")] = 0.
# u2fitter.migrad()
# print "u2 delta func: area diff =", fitrecord[2].values[0] - u2fitter.values[0]

# ####

# print "u3 systematics studies"

# u3fitter.values[u3fitter.findpar("fullgam")] = 0.0263 + 0.0034
# u3fitter.migrad()
# print "u3 fullgam: area diff =", fitrecord[3].values[0] - u3fitter.values[0]
# u3fitter.values[u3fitter.findpar("fullgam")] = 0.0263

# u3fitter.values[u3fitter.findpar("yint")] = 0.01823 + 0.00060
# u3fitter.migrad()
# print "u3 yint: area diff =", fitrecord[3].values[0] - u3fitter.values[0]
# u3fitter.values[u3fitter.findpar("yint")] = 0.01823

# u3fitter.values[u3fitter.findpar("btautau")] = 2.*0.0239
# u3fitter.values[u3fitter.findpar("tauyint")] = 0.27/2.
# u3fitter.migrad()
# print "u3 btautau/tauyint plus: area diff =", fitrecord[3].values[0] - u3fitter.values[0]
# u3fitter.values[u3fitter.findpar("btautau")] = 0.
# u3fitter.migrad()
# print "u3 btautau/tauyint minus: area diff =", fitrecord[3].values[0] - u3fitter.values[0]
# u3fitter.values[u3fitter.findpar("btautau")] = 0.0239
# u3fitter.values[u3fitter.findpar("tauyint")] = 0.27

# u3fitter.values[u3fitter.findpar("twophofrac")] = 0.0792 + 0.0054
# u3fitter.migrad()
# print "u3 twophofrac: area diff =", fitrecord[3].values[0] - u3fitter.values[0]
# u3fitter.values[u3fitter.findpar("twophofrac")] = 0.0792

# u3fitter.values[u3fitter.findpar("u1area")] = fitrecord[1].values[0] + fitrecord[1].errors[0]
# u3fitter.migrad()
# print "u3 u1area: area diff =", fitrecord[3].values[0] - u3fitter.values[0]
# u3fitter.values[u3fitter.findpar("u1area")] = fitrecord[1].values[0]

# u3fitter.values[u3fitter.findpar("u2area")] = fitrecord[2].values[0] + fitrecord[2].errors[0]
# u3fitter.migrad()
# print "u3 u2area: area diff =", fitrecord[3].values[0] - u3fitter.values[0]
# u3fitter.values[u3fitter.findpar("u2area")] = fitrecord[2].values[0]

# u3fitter.values[u3fitter.findpar("btautau")] = 0.0239
# u3fitter.migrad()
# print "u3 btautau=bmumu: area = ", u3fitter.values[0]
# u3fitter.values[u3fitter.findpar("btautau")] = 0.0239 + 0.0012
# u3fitter.migrad()
# print "u3 btautau=bmumu up: area = ", u3fitter.values[0]
# u3fitter.values[u3fitter.findpar("btautau")] = 0.
# u3fitter.migrad()
# print "u3 btautau=0: area = ", u3fitter.values[0]

# u3fitter.values[u3fitter.findpar("fullgam")] = 0.
# u3fitter.values[u3fitter.findpar("yint")] = 0.
# u3fitter.values[u3fitter.findpar("tauyint")] = 0.
# u3fitter.migrad()
# print "u3 delta func: area diff =", fitrecord[3].values[0] - u3fitter.values[0]

# ############

# def correlation_coefficients(cov, n):
#   printout = ""
#   for i in range(n):
#     for j in range(i+1):
#       printout += ("%5.2f " % (cov[i][j] / sqrt(cov[i][i] * cov[j][j]),))
#     printout += "\n"
#   return printout

# print "u1 correlation coefficients"
# print correlation_coefficients(fitrecord[1].covariance, 15)
# print "u2 correlation coefficients"
# print correlation_coefficients(fitrecord[2].covariance, 9)
# print "u3 correlation coefficients"
# print correlation_coefficients(fitrecord[3].covariance, 10)


#############################################



# x = Numeric.arange(fitrecord[1].values[0] + 2*fitrecord[1].minos_errors[0][0], \
#                    fitrecord[1].values[0] + 2*fitrecord[1].minos_errors[0][1], \
#                    (fitrecord[1].minos_errors[0][0]+fitrecord[1].minos_errors[0][1])/4.)
# y = Numeric.arange(fitrecord[1].values[0] + 2*fitrecord[1].minos_errors[0][0], \
#                    fitrecord[1].values[0] + 2*fitrecord[1].minos_errors[0][1], \
#                    (fitrecord[1].minos_errors[0][0]+fitrecord[1].minos_errors[0][1])/4.)
# x2 = []
# y2 = []
# u1fitter.migrad()
# for i, xi in enumerate(x):
#   u1fitter.values[0] = xi
#   y[i] = u1fit(*u1fitter.values)
# u1fitter.fix("area")
# for xi in x:
#   u1fitter.values[0] = xi
#   u1fitter.migrad()
#   if u1fitter.valid:
#     x2.append(xi)
#     y2.append(u1fitter.fval)



############################################################################################
# THE FIRST ATTEMPT AT CHI^2 SCANS
############################################################################################

# p = biggles.FramedPlot()
# # tmp0 = biggles.Curve(x3, y3, linetype="dotted")
# tmp1 = biggles.Curve(x, y, linetype="dashed")
# tmp2 = biggles.Curve(x2, y2)
# tmp3 = biggles.Points([x[2], x[4], x[6]], [y[4]+1, y[4], y[4]+1], symboltype="filled circle", symbolsize=2)
# tmp0.label = r"Parabolic Errors from MIGRAD Hessian"
# tmp1.label = "Keeping other parameters fixed"
# tmp2.label = "Minimizing w.r.t. all other parameters"
# tmp3.label = r"The -1, 0, +1 $\sigma$ points"
# # p.add(tmp0)
# p.add(tmp1)
# p.add(tmp2)
# p.add(tmp3)
# p.add(biggles.PlotKey(0.2, 0.8, [tmp1, tmp2, tmp3]))
# p.x1.label = r"Area of $\Upsilon(1S)$"
# p.y1.label = r"$\chi^2$"
# p.show()
# p.write_eps("/home/mccann/antithesis/fit_results/superscan1s.eps")

# u2fitter.values = [fitrecord[2].values[0], 4.17, 0.405, -1.12, -1.05, -1.41, -0.75, -0.65, -0.39, 0.043, 0.01792, 0., 0.017, 0.37, 0., 0.0792, fitrecord[1].values[0]]
# u2fitter.fix(range(u2fitter.npar))
# u2fitter.release(["area", "rmsbeam", "back"])
# u2fitter.release(["may29", "jun11", "jun12", "jul10", "jul24", "aug07"])
# xx = Numeric.arange(fitrecord[2].values[0] + 2*fitrecord[2].minos_errors[0][0], \
#                    fitrecord[2].values[0] + 2*fitrecord[2].minos_errors[0][1], \
#                    (fitrecord[2].minos_errors[0][0]+fitrecord[2].minos_errors[0][1])/4.)
# yy = Numeric.arange(fitrecord[2].values[0] + 2*fitrecord[2].minos_errors[0][0], \
#                    fitrecord[2].values[0] + 2*fitrecord[2].minos_errors[0][1], \
#                    (fitrecord[2].minos_errors[0][0]+fitrecord[2].minos_errors[0][1])/4.)
# xx2 = []
# yy2 = []
# u2fitter.migrad()
# for i, xxi in enumerate(xx):
#   u2fitter.values[0] = xxi
#   yy[i] = u2fit(*u2fitter.values)
# u2fitter.fix("area")
# for xxi in xx:
#   u2fitter.values[0] = xxi
#   u2fitter.migrad()
#   if u2fitter.valid:
#     xx2.append(xxi)
#     yy2.append(u2fitter.fval)

# p = biggles.FramedPlot()
# # tmp0 = biggles.Curve(xx3, yy3, linetype="dotted")
# tmp1 = biggles.Curve(xx, yy, linetype="dashed")
# tmp2 = biggles.Curve(xx2, yy2)
# tmp3 = biggles.Points([xx[2], xx[4], xx[6]], [yy[4]+1, yy[4], yy[4]+1], symboltype="filled circle", symbolsize=2)
# # tmp0.label = r"Parabola through -1, 0, +1 $\sigma$"
# tmp1.label = "Keeping other parameters fixed"
# tmp2.label = "Minimizing w.r.t. all other parameters"
# tmp3.label = r"The -1, 0, +1 $\sigma$ points"
# # p.add(tmp0)
# p.add(tmp1)
# p.add(tmp2)
# p.add(tmp3)
# p.add(biggles.PlotKey(0.2, 0.8, [tmp1, tmp2, tmp3]))
# p.x1.label = r"Area of $\Upsilon(2S)$"
# p.y1.label = r"$\chi^2$"
# p.show()
# p.write_eps("/home/mccann/antithesis/fit_results/superscan2s.eps")

# u3fitter.values = [fitrecord[3].values[0], 4.48, 0.404, -2.12, -3.99, -3.18, -2.46, -2.72, -2.55, -2.64, 0.0263, 0.01823, 0., 0.0239, 0.27, 0., 0.0792, fitrecord[1].values[0], fitrecord[2].values[0]]
# u3fitter.fix(range(u3fitter.npar))
# u3fitter.release(["area", "rmsbeam", "back"])
# u3fitter.release(["nov28", "dec05", "dec12", "dec19", "dec26", "jan02", "jan09"])
# xxx = Numeric.arange(fitrecord[3].values[0] + 2*fitrecord[3].minos_errors[0][0], \
#                    fitrecord[3].values[0] + 2*fitrecord[3].minos_errors[0][1], \
#                    (fitrecord[3].minos_errors[0][0]+fitrecord[3].minos_errors[0][1])/4.)
# yyy = Numeric.arange(fitrecord[3].values[0] + 2*fitrecord[3].minos_errors[0][0], \
#                    fitrecord[3].values[0] + 2*fitrecord[3].minos_errors[0][1], \
#                    (fitrecord[3].minos_errors[0][0]+fitrecord[3].minos_errors[0][1])/4.)
# xxx2 = []
# yyy2 = []
# u3fitter.migrad()
# for i, xxxi in enumerate(xxx):
#   u3fitter.values[0] = xxxi
#   yyy[i] = u3fit(*u3fitter.values)
# u3fitter.fix("area")
# for xxxi in xxx:
#   u3fitter.values[0] = xxxi
#   u3fitter.migrad()
#   if u3fitter.valid:
#     xxx2.append(xxxi)
#     yyy2.append(u3fitter.fval)

# p = biggles.FramedPlot()
# # tmp0 = biggles.Curve(xxx3, yyy3, linetype="dotted")
# tmp1 = biggles.Curve(xxx, yyy, linetype="dashed")
# tmp2 = biggles.Curve(xxx2, yyy2)
# tmp3 = biggles.Points([xxx[2], xxx[4], xxx[6]], [yyy[4]+1, yyy[4], yyy[4]+1], symboltype="filled circle", symbolsize=2)
# # tmp0.label = r"Parabola through -1, 0, +1 $\sigma$"
# tmp1.label = "Keeping other parameters fixed"
# tmp2.label = "Minimizing w.r.t. all other parameters"
# tmp3.label = r"The -1, 0, +1 $\sigma$ points"
# # p.add(tmp0)
# p.add(tmp1)
# p.add(tmp2)
# p.add(tmp3)
# p.add(biggles.PlotKey(0.2, 0.8, [tmp1, tmp2, tmp3]))
# p.x1.label = r"Area of $\Upsilon(3S)$"
# p.y1.label = r"$\chi^2$"
# p.show()
# p.write_eps("/home/mccann/antithesis/fit_results/superscan3s.eps")

# # x3 = Numeric.arange(fitrecord[1].values[0] + 2*fitrecord[1].minos_errors[0][0], \
# #                    fitrecord[1].values[0] + 2*fitrecord[1].minos_errors[0][1], \
# #                    fitrecord[1].errors[0]*0.1)
# # y3 = Numeric.arange(fitrecord[1].values[0] + 2*fitrecord[1].minos_errors[0][0], \
# #                    fitrecord[1].values[0] + 2*fitrecord[1].minos_errors[0][1], \
# #                    fitrecord[1].errors[0]*0.1)
# # tmpa = (x[6]*(x[4]*(x[4]-x[6])*y[2]+x[2]*(-x[2]+x[6])*y[4])+x[2]*(x[2]-x[4])*x[4]*y[6])/((x[2]-x[4])*(x[2]-x[6])*(x[4]-x[6]))
# # tmpb = (x[6]**2*(y[2]-y[4])+x[2]**2*(y[4]-y[6])+x[4]**2*(-y[2]+y[6]))/((x[2]-x[4])*(x[2]-x[6])*(x[4]-x[6]))
# # tmpc = (x[6]*(-y[2]+y[4])+x[4]*(y[2]-y[6])+x[2]*(-y[4]+y[6]))/((x[2]-x[4])*(x[2]-x[6])*(x[4]-x[6]))
# # for i, xi in enumerate(x3):
# #   y3[i] = tmpa + tmpb*xi + tmpc*xi**2

############################################################################################
# THE BETTER CHI^2 SCANS
############################################################################################

# def drawsuper(fitter, filename):
#   bestarea = fitter.values[0]
#   paraberr = fitter.errors[0]
#   minoserr = (abs(fitter.minos_errors[0][0]) + abs(fitter.minos_errors[0][1]))/2.
#   bestchi2 = fitter.fval

#   x1 = bestarea - paraberr
#   x2 = bestarea
#   x3 = bestarea + paraberr
#   y1 = bestchi2 + 1
#   y2 = bestchi2
#   y3 = bestchi2 + 1

#   a = (x3*(x2*(x2-x3)*y1+x1*(-x1+x3)*y2)+x1*(x1-x2)*x2*y3)/((x1-x2)*(x1-x3)*(x2-x3))
#   b = (x3**2*(y1-y2)+x1**2*(y2-y3)+x2**2*(-y1+y3))/((x1-x2)*(x1-x3)*(x2-x3))
#   c = (x3*(-y1+y2)+x2*(y1-y3)+x1*(-y2+y3))/((x1-x2)*(x1-x3)*(x2-x3))

#   dots_x = [bestarea + fitter.minos_errors[0][0], bestarea + fitter.minos_errors[0][1]]
#   dots_y = [bestchi2+1, bestchi2+1]

#   paracurve_x = Numeric.arange(bestarea - 2*minoserr, bestarea + 2*minoserr, minoserr/100.)
#   paracurve_y = Numeric.arange(bestarea - 2*minoserr, bestarea + 2*minoserr, minoserr/100.)
#   for i, xi in enumerate(paracurve_x):
#     paracurve_y[i] = a + b*xi + c*xi**2

#   fitter.fix("area")
#   fullcurve_trialx = Numeric.arange(bestarea - 2*minoserr, bestarea + 2*minoserr, minoserr/5.)
#   fullcurve_x = []
#   fullcurve_y = []
#   for xi in fullcurve_trialx:
#     fitter.values[0] = xi
#     fitter.migrad()
#     fullcurve_x.append(xi)
#     fullcurve_y.append(fitter.fval)
  
#   p = biggles.FramedPlot()
#   tmp1 = biggles.Curve(paracurve_x, paracurve_y, linetype="dotted")
#   tmp1.label = "Parabolic error (from MIGRAD's Hessian matrix)"
#   tmp2 = biggles.Curve(fullcurve_x, fullcurve_y)
#   tmp2.label = "Minimum w.r.t other parameters (should agree with MINOS)"
#   tmp3 = biggles.Points(dots_x, dots_y, symboltype="filled circle", symbolsize=2)
#   tmp3.label = "MINOS errors"
#   p.add(tmp1)
#   p.add(tmp2)
#   p.add(tmp3)
#   p.add(biggles.PlotKey(0.2, 0.8, [tmp1, tmp2, tmp3]))
# #  p.show()
#   p.write_eps(filename)

# u1fitter.values = [13.7, 3.79, 0.404, 0.25, 0.63, 0.076, 0.066, 0.23, 0.19, 0.20, 0.57, 0.92, 0.80, 0.46, 0.62, 0.053, 0.01864, 0., 0.0267, 0.20, 0., 0.0792]
# u1fitter.fix(range(u1fitter.npar))
# u1fitter.release(["area", "rmsbeam", "back"])
# u1fitter.release(["jan16", "jan30", "feb06", "feb13", "feb20", "feb27", "mar06", "mar13", "apr03", "apr08", "apr09", "apr10"])
# u1fitter.migrad()
# u1fitter.minos_errors[0] = fitrecord[1].minos_errors[0]
# drawsuper(u1fitter, "/home/mccann/antithesis/fit_results/superduper_scans1s.eps")

# u2fitter = Minuit(u2fit)
# u2fitter.values = [5.59, 4.17, 0.405, -1.12, -1.05, -1.41, -0.75, -0.65, -0.39, 0.043, 0.01792, 0., 0.017, 0.37, 0., 0.0792, fitrecord[1].values[0]]
# u2fitter.fix(range(u2fitter.npar))
# u2fitter.release(["area", "rmsbeam", "back"])
# u2fitter.release(["may29", "jun11", "jun12", "jul10", "jul24", "aug07"])
# u2fitter.migrad()
# u2fitter.minos_errors[0] = fitrecord[2].minos_errors[0]
# drawsuper(u2fitter, "/home/mccann/antithesis/fit_results/superduper_scans2s.eps")

# u3fitter = Minuit(u3fit)
# u3fitter.values = [3.58, 4.48, 0.404, -2.12, -3.99, -3.18, -2.46, -2.72, -2.55, -2.64, 0.0263, 0.01823, 0., 0.0239, 0.27, 0., 0.0792, fitrecord[1].values[0], fitrecord[2].values[0]]
# u3fitter.fix(range(u3fitter.npar))
# u3fitter.release(["area", "rmsbeam", "back"])
# u3fitter.release(["nov28", "dec05", "dec12", "dec19", "dec26", "jan02", "jan09"])
# u3fitter.migrad()
# u3fitter.minos_errors[0] = fitrecord[3].minos_errors[0]
# drawsuper(u3fitter, "/home/mccann/antithesis/fit_results/superduper_scans3s.eps")




#######################################################

def adddata2(data, shift, x, y, yerr):
  for (e, h, herr) in data:
    x.append(e*2000.+shift)
    y.append(h)
    yerr.append(herr)
  return None

def u1plot2(area, rmsbeam, back, jan16, jan30, feb06, feb13, feb20, feb27, mar06, mar13, apr03, apr08, apr09, apr10, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac):
  p = biggles.FramedPlot()
  x = []
  y = []
  yerr = []
  adddata2(u1data["cont"], 0., x, y, yerr)
  adddata2(u1data["high"], 0., x, y, yerr)
  adddata2(u1data["jan16"], jan16, x, y, yerr)
  adddata2(u1data["jan30"], jan30, x, y, yerr)
  adddata2(u1data["feb06"], feb06, x, y, yerr)
  adddata2(u1data["feb13"], feb13, x, y, yerr)
  adddata2(u1data["feb20"], feb20, x, y, yerr)
  adddata2(u1data["feb27"], feb27, x, y, yerr)
  adddata2(u1data["mar06"], mar06, x, y, yerr)
  adddata2(u1data["mar13"], mar13, x, y, yerr)
  adddata2(u1data["apr03"], apr03, x, y, yerr)
  adddata2(u1data["apr08"], apr08, x, y, yerr)
  adddata2(u1data["apr09"], apr09, x, y, yerr)
  adddata2(u1data["apr10"], apr10, x, y, yerr)
  themap = {}
  for xi, yi, yerri in zip(x, y, yerr):
    if round(xi) not in themap: themap[round(xi)] = []
    themap[round(xi)].append((xi, yi, yerri))
  fewx = []
  fewy = []
  fewyerr = []
  for rxi in themap:
    fewx.append(jt.mean(map(lambda (xi, yi, yerri): xi, themap[rxi])))
    fewy.append(jt.wmean(map(lambda (xi, yi, yerri): (yi, yerri), themap[rxi]))[0])
    fewyerr.append(jt.wmean(map(lambda (xi, yi, yerri): (yi, yerri), themap[rxi]))[1])
  p.add(biggles.Points(fewx, fewy, symboltype="filled circle", symbolsize=0.8))
  p.add(biggles.SymmetricErrorBarsY(fewx, fewy, fewyerr))
  addfunc(p, lambda w: u1func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, w), 9420., 9580., points=1000.)
  p.x1.range = 9420., 9580.
  p.y1.range = 0., 1.5
  p.aspect_ratio = 1.2
  return p

def u2plot2(area, rmsbeam, back, may29, jun11, jun12, jul10, jul24, aug07, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area):
  p = biggles.FramedPlot()
  x = []
  y = []
  yerr = []
  adddata2(u2data["cont"], 0., x, y, yerr)
  adddata2(u2data["high"], 0., x, y, yerr)
  adddata2(u2data["may29"], may29, x, y, yerr)
  adddata2(u2data["jun11"], jun11, x, y, yerr)
  adddata2(u2data["jun12"], jun12, x, y, yerr)
  adddata2(u2data["jul10"], jul10, x, y, yerr)
  adddata2(u2data["jul24"], jul24, x, y, yerr)
  adddata2(u2data["aug07"], aug07, x, y, yerr)
  themap = {}
  for xi, yi, yerri in zip(x, y, yerr):
    if round(xi) not in themap: themap[round(xi)] = []
    themap[round(xi)].append((xi, yi, yerri))
  fewx = []
  fewy = []
  fewyerr = []
  for rxi in themap:
    fewx.append(jt.mean(map(lambda (xi, yi, yerri): xi, themap[rxi])))
    fewy.append(jt.wmean(map(lambda (xi, yi, yerri): (yi, yerri), themap[rxi]))[0])
    fewyerr.append(jt.wmean(map(lambda (xi, yi, yerri): (yi, yerri), themap[rxi]))[1])
  p.add(biggles.Points(fewx, fewy, symboltype="filled circle", symbolsize=0.8))
  p.add(biggles.SymmetricErrorBarsY(fewx, fewy, fewyerr))
  addfunc(p, lambda w: u2func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, w), 9980., 10100., points=1000.)
  p.x1.range = 9980., 10100.
  p.y1.range = 0., 0.8
  p.aspect_ratio = 1.2
  return p

def u3plot2(area, rmsbeam, back, nov28, dec05, dec12, dec19, dec26, jan02, jan09, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area):
  p = biggles.FramedPlot()
  x = []
  y = []
  yerr = []
  adddata2(u3data["cont"], 0., x, y, yerr)
  adddata2(u3data["high"], 0., x, y, yerr)
  adddata2(u3data["nov28"], nov28, x, y, yerr)
  adddata2(u3data["dec05"], dec05, x, y, yerr)
  adddata2(u3data["dec12"], dec12, x, y, yerr)
  adddata2(u3data["dec19"], dec19, x, y, yerr)
  adddata2(u3data["dec26"], dec26, x, y, yerr)
  adddata2(u3data["jan02"], jan02, x, y, yerr)
  adddata2(u3data["jan09"], jan09, x, y, yerr)
  themap = {}
  for xi, yi, yerri in zip(x, y, yerr):
    if round(xi) not in themap: themap[round(xi)] = []
    themap[round(xi)].append((xi, yi, yerri))
  fewx = []
  fewy = []
  fewyerr = []
  for rxi in themap:
    fewx.append(jt.mean(map(lambda (xi, yi, yerri): xi, themap[rxi])))
    fewy.append(jt.wmean(map(lambda (xi, yi, yerri): (yi, yerri), themap[rxi]))[0])
    fewyerr.append(jt.wmean(map(lambda (xi, yi, yerri): (yi, yerri), themap[rxi]))[1])
  p.add(biggles.Points(fewx, fewy, symboltype="filled circle", symbolsize=0.8))
  p.add(biggles.SymmetricErrorBarsY(fewx, fewy, fewyerr))
  addfunc(p, lambda w: u3func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area, w), 10320., 10420., points=1000.)
  p.x1.range = 10320., 10420.
  p.y1.range = 0., 0.7
  p.aspect_ratio = 1.2
  return p

p = biggles.Table(3,1)
p[0,0] = u1plot2(*fitrecord[1].values)
p[0,0].aspect_ratio = 0.33
p[0,0].add(biggles.PlotLabel(0.1,0.8,"(a)"))
p[0,0].y1.label = r"$\propto$ Hadronic Cross-section"
p[0,0].x1.label = r"Center-of-mass energy (2 $\times$ beam energy) in MeV"
p[1,0] = u2plot2(*fitrecord[2].values)
p[1,0].aspect_ratio = 0.33
p[1,0].add(biggles.PlotLabel(0.1,0.8,"(b)"))
p[1,0].y1.label = r"$\propto$ Hadronic Cross-section"
p[1,0].x1.label = r"Center-of-mass energy (2 $\times$ beam energy) in MeV"
p[2,0] = u3plot2(*fitrecord[3].values)
p[2,0].aspect_ratio = 0.33
p[2,0].add(biggles.PlotLabel(0.1,0.8,"(c)"))
p[2,0].y1.label = r"$\propto$ Hadronic Cross-section"
p[2,0].x1.label = r"Center-of-mass energy (2 $\times$ beam energy) in MeV"
p.aspect_ratio = 1.2
p.show()
p.write_eps("/home/mccann/antithesis/fit_results/effcor_allfit_comb.eps")

##########################################################

def adddata2(data, shift, x, y, yerr):
  for (e, h, herr) in data:
    x.append(e*2000.+shift)
    y.append(h)
    yerr.append(herr)
  return None

class FitRecord: pass
fitrecord = pickle.load(open("/home/mccann/antithesis/fit_results/effcor.p"))

def get_cosmics(runs, usebhabha=False, energycorrection=True):
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

  hadrons = cbkgnd
  hadrons_err = sqrt(c * (1.*nobeam.hadroncool/nobeam.cosmic)**2)
#  print "  Corrected number of hadrons is", hadrons, "+/-", hadrons_err
#  print "  Number of gamgams is", g

  cs = hadrons / g
  if energycorrection: cs *= 1./average_energy**2

  cs_err = cs * sqrt((1.*hadrons_err / hadrons)**2 + 1./g)
#  print "  Relative cross-section is", cs, "+/-", cs_err

  return average_energy, cs, cs_err

def get_pbkgnd(runs, usebhabha=False, energycorrection=True):
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

  hadrons = pbkgnd
  hadrons_err = sqrt(1. * p * (pbeam.hadroncool - 1.*nobeam.hadroncool*pbeam.cosmic/nobeam.cosmic)**2 / pbeam.beamgasp**2)
#  print "  Corrected number of hadrons is", hadrons, "+/-", hadrons_err
#  print "  Number of gamgams is", g

  cs = hadrons / g
  if energycorrection: cs *= 1./average_energy**2

  cs_err = cs * sqrt((1.*hadrons_err / hadrons)**2 + 1./g)
#  print "  Relative cross-section is", cs, "+/-", cs_err

  return average_energy, cs, cs_err

def get_ebkgnd(runs, usebhabha=False, energycorrection=True):
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

  hadrons = ebkgnd
  hadrons_err = sqrt(1. * e * (ebeam.hadroncool - 1.*nobeam.hadroncool*ebeam.cosmic/nobeam.cosmic)**2 / ebeam.beamgase**2)
#  print "  Corrected number of hadrons is", hadrons, "+/-", hadrons_err
#  print "  Number of gamgams is", g

  cs = hadrons / g
  if energycorrection: cs *= 1./average_energy**2

  cs_err = cs * sqrt((1.*hadrons_err / hadrons)**2 + 1./g)
#  print "  Relative cross-section is", cs, "+/-", cs_err

  return average_energy, cs, cs_err

def setup_cosmics(runs, fudge=1.):
  tmpdata = []
  for r in runs:
    e, cs, cserr = get_cosmics([r])
    cserr *= fudge
    tmpdata.append((e, cs, cserr))
  return tmpdata

def setup_pbkgnd(runs, fudge=1.):
  tmpdata = []
  for r in runs:
    e, cs, cserr = get_pbkgnd([r])
    cserr *= fudge
    tmpdata.append((e, cs, cserr))
  return tmpdata

def setup_ebkgnd(runs, fudge=1.):
  tmpdata = []
  for r in runs:
    e, cs, cserr = get_ebkgnd([r])
    cserr *= fudge
    tmpdata.append((e, cs, cserr))
  return tmpdata

u3cosmics = {}
u3pbkgnd = {}
u3ebkgnd = {}

u3cosmics["cont"] = [get_cosmics(u3runs["cont"])]
u3cosmics["high"] = [get_cosmics(u3runs["high"])]
u3cosmics["nov28"] = setup_cosmics(u3runs["nov28"])
u3cosmics["dec05"] = setup_cosmics(u3runs["dec05"])
u3cosmics["dec12"] = setup_cosmics(u3runs["dec12"])
u3cosmics["dec19"] = setup_cosmics(u3runs["dec19"])
u3cosmics["dec26"] = setup_cosmics(u3runs["dec26"])
u3cosmics["jan02"] = setup_cosmics(u3runs["jan02"])
u3cosmics["jan09"] = setup_cosmics(u3runs["jan09"])

u3pbkgnd["cont"] = [get_pbkgnd(u3runs["cont"])]
u3pbkgnd["high"] = [get_pbkgnd(u3runs["high"])]
u3pbkgnd["nov28"] = setup_pbkgnd(u3runs["nov28"])
u3pbkgnd["dec05"] = setup_pbkgnd(u3runs["dec05"])
u3pbkgnd["dec12"] = setup_pbkgnd(u3runs["dec12"])
u3pbkgnd["dec19"] = setup_pbkgnd(u3runs["dec19"])
u3pbkgnd["dec26"] = setup_pbkgnd(u3runs["dec26"])
u3pbkgnd["jan02"] = setup_pbkgnd(u3runs["jan02"])
u3pbkgnd["jan09"] = setup_pbkgnd(u3runs["jan09"])

u3ebkgnd["cont"] = [get_ebkgnd(u3runs["cont"])]
u3ebkgnd["high"] = [get_ebkgnd(u3runs["high"])]
u3ebkgnd["nov28"] = setup_ebkgnd(u3runs["nov28"])
u3ebkgnd["dec05"] = setup_ebkgnd(u3runs["dec05"])
u3ebkgnd["dec12"] = setup_ebkgnd(u3runs["dec12"])
u3ebkgnd["dec19"] = setup_ebkgnd(u3runs["dec19"])
u3ebkgnd["dec26"] = setup_ebkgnd(u3runs["dec26"])
u3ebkgnd["jan02"] = setup_ebkgnd(u3runs["jan02"])
u3ebkgnd["jan09"] = setup_ebkgnd(u3runs["jan09"])

factor = 1.

contstuff = getdb(u3runs["cont"][0])
for r in u3runs["cont"]:
  if r != u3runs["cont"][0]:
    contstuff += getdb(r)

contstuff1 = getdb(u1runs["cont"][0])
for r in u1runs["cont"]:
  if r != u1runs["cont"][0]:
    contstuff1 += getdb(r)

contstuff2 = getdb(u2runs["cont"][0])
for r in u2runs["cont"]:
  if r != u2runs["cont"][0]:
    contstuff2 += getdb(r)

def u3func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area, w):
  tmp = 0.
  tmp += area * 0.9708 * mygbwkf(10355.2, fullgam, rmsbeam, yint, phi, w)
  tmp += area * 0.578 * btautau * mygbwkftau(10355.2, fullgam, rmsbeam, tauyint, tauphi, w)
  tmp += back * (1.-twophofrac) * 9000.**2 / w**2
  tmp += back * twophofrac * log(w**2/9000.**2)
  tmp += u1area * mygbwkf(9460.30, 0., 0., 0., 0., w)
  tmp += u2area * mygbwkf(10023.26, 0., 0., 0., 0., w)
  return tmp*factor

def u3func_tail(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area, w):
  tmp = area * 0.9708 * mygbwkf(10355.2, fullgam, rmsbeam, yint, phi, w)
  tmp -= area * 0.9708 * exp(-(w-10355.2)**2/2./rmsbeam**2) / sqrt(2.*pi) / rmsbeam
  return abs(tmp)*factor

def u3func_backgrounds(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area, w):
  tmp = 0.
  tmp += area * 0.578 * btautau * mygbwkftau(10355.2, fullgam, rmsbeam, tauyint, tauphi, w)
  tmp += back * (1.-twophofrac) * 9000.**2 / w**2
  tmp += back * twophofrac * log(w**2/9000.**2)
  tmp += u1area * mygbwkf(9460.30, 0., 0., 0., 0., w)
  tmp += u2area * mygbwkf(10023.26, 0., 0., 0., 0., w)
  return tmp*factor

def u3func_u1area(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area, w):
  tmp = 0.
  tmp += u1area * mygbwkf(9460.30, 0., 0., 0., 0., w)
  return tmp*factor

def u3func_u2area(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area, w):
  tmp = 0.
  tmp += u2area * mygbwkf(10023.26, 0., 0., 0., 0., w)
  return tmp*factor

def u3func_jpsi(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area, w):
  tmp = 0.
  tmp += u1area * 4.11 * mygbwkf(3096.916, 0., 0., 0., 0., w)
  return tmp*factor

def u3func_psiprime(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area, w):
  tmp = 0.
  tmp += u1area * 1.61 * mygbwkf(3686.093, 0., 0., 0., 0., w)
  return tmp*factor

def u3func_twophoton(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area, w):
  tmp = 0.
  tmp += back * twophofrac * log(w**2/9000.**2)
  return tmp*factor

def u3func_tau(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area, w, res=True, cont=True):
  tmp = 0.
  if res: tmp += area * 0.578 * btautau * mygbwkftau(10355.2, fullgam, rmsbeam, tauyint, tauphi, w)
  if cont: tmp += 0.578*contstuff.mupair_logd0close.int(-7.,-3.)/contstuff.gamgam * (u3data["cont"][0][0]*2000.)**2 / w**2
  return tmp*factor

def u2func_tau(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, w, res=True, cont=True):
  tmp = 0.
  if res: tmp += area * 0.578 * btautau * mygbwkftau(10023.26, fullgam, rmsbeam, tauyint, tauphi, w)
  if cont: tmp += 0.578*contstuff2.mupair_logd0close.int(-7.,-3.)/contstuff2.gamgam * (u2data["cont"][0][0]*2000.)**2 / w**2
  return tmp*factor

def u1func_tau(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, w, res=True, cont=True):
  tmp = 0.
  if res: tmp += area * 0.578 * btautau * mygbwkftau(9460.30, fullgam, rmsbeam, tauyint, tauphi, w)
  if cont: tmp += 0.578*contstuff.mupair_logd0close.int(-7.,-3.)/contstuff.gamgam * (u1data["cont"][0][0]*2000.)**2 / w**2
  return tmp*factor

# def really(ecom, whichres):
#   if whichres == 3:
#     area, rmsbeam, back, nov28, dec05, dec12, dec19, dec26, jan02, jan09, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area = fitrecord[3].values
#     return u3func_tau(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area, ecom, res=True, cont=False)/u3func_tau(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area, ecom, res=True, cont=True)
#   if whichres == 2:
#     area, rmsbeam, back, may29, jun11, jun12, jul10, jul24, aug07, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area = fitrecord[2].values
#     return u2func_tau(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, ecom, res=True, cont=False)/u2func_tau(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, ecom, res=True, cont=True)
#   if whichres == 1:
#     area, rmsbeam, back, jan16, jan30, feb06, feb13, feb20, feb27, mar06, mar13, apr03, apr08, apr09, apr10, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac = fitrecord[1].values
#     return u1func_tau(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, ecom, res=True, cont=False)/u1func_tau(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, ecom, res=True, cont=True)

def u3plot2(area, rmsbeam, back, nov28, dec05, dec12, dec19, dec26, jan02, jan09, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area):
  p = biggles.FramedPlot()
  x = []
  y = []
  yerr = []
  adddata2(u3data["cont"], 0., x, y, yerr)
  adddata2(u3data["high"], 0., x, y, yerr)
  adddata2(u3data["nov28"], nov28, x, y, yerr)
  adddata2(u3data["dec05"], dec05, x, y, yerr)
  adddata2(u3data["dec12"], dec12, x, y, yerr)
  adddata2(u3data["dec19"], dec19, x, y, yerr)
  adddata2(u3data["dec26"], dec26, x, y, yerr)
  adddata2(u3data["jan02"], jan02, x, y, yerr)
  adddata2(u3data["jan09"], jan09, x, y, yerr)
  themap = {}
  for xi, yi, yerri in zip(x, y, yerr):
    if round(xi) not in themap: themap[round(xi)] = []
    themap[round(xi)].append((xi, yi, yerri))
  fewx = []
  fewy = []
  fewyerr = []
  for rxi in themap:
    fewx.append(jt.mean(map(lambda (xi, yi, yerri): xi, themap[rxi])))
    fewy.append(jt.wmean(map(lambda (xi, yi, yerri): (yi, yerri), themap[rxi]))[0])
    fewyerr.append(jt.wmean(map(lambda (xi, yi, yerri): (yi, yerri), themap[rxi]))[1])
  p.add(biggles.Points(fewx, fewy, symboltype="filled circle", symbolsize=0.8))
  p.add(biggles.SymmetricErrorBarsY(fewx, fewy, fewyerr))

  x = []
  y = []
  yerr = []
  adddata2(u3cosmics["cont"], 0., x, y, yerr)
  adddata2(u3cosmics["high"], 0., x, y, yerr)
  adddata2(u3cosmics["nov28"], nov28, x, y, yerr)
  adddata2(u3cosmics["dec05"], dec05, x, y, yerr)
  adddata2(u3cosmics["dec12"], dec12, x, y, yerr)
  adddata2(u3cosmics["dec19"], dec19, x, y, yerr)
  adddata2(u3cosmics["dec26"], dec26, x, y, yerr)
  adddata2(u3cosmics["jan02"], jan02, x, y, yerr)
  adddata2(u3cosmics["jan09"], jan09, x, y, yerr)
  themap = {}
  for xi, yi, yerri in zip(x, y, yerr):
    if round(xi) not in themap: themap[round(xi)] = []
    themap[round(xi)].append((xi, yi, yerri))
  fewx = []
  fewy = []
  fewyerr = []
  for rxi in themap:
    fewx.append(jt.mean(map(lambda (xi, yi, yerri): xi, themap[rxi])))
    fewy.append(jt.wmean(map(lambda (xi, yi, yerri): (yi, yerri), themap[rxi]))[0])
    fewyerr.append(jt.wmean(map(lambda (xi, yi, yerri): (yi, yerri), themap[rxi]))[1])
  p.add(biggles.Points(fewx, fewy, symboltype="filled circle", symbolsize=0.8))
  cosmic_points = biggles.SymmetricErrorBarsY(fewx, fewy, fewyerr)
  p.add(cosmic_points)
#   p.add(biggles.DataLabel(10389, factor*0.0016, r"cosmic"))
#   p.add(biggles.DataLabel(10402, factor*0.0016, r"rays", texthalign="left"))
  cosmic_points.label = "cosmic rays"
  p.add(biggles.DataLabel(10370, factor*0.0025, r"cosmic rays"))

  x = []
  y = []
  yerr = []
  adddata2(u3pbkgnd["cont"], 0., x, y, yerr)
  adddata2(u3pbkgnd["high"], 0., x, y, yerr)
  adddata2(u3pbkgnd["nov28"], nov28, x, y, yerr)
  adddata2(u3pbkgnd["dec05"], dec05, x, y, yerr)
  adddata2(u3pbkgnd["dec12"], dec12, x, y, yerr)
  adddata2(u3pbkgnd["dec19"], dec19, x, y, yerr)
  adddata2(u3pbkgnd["dec26"], dec26, x, y, yerr)
  adddata2(u3pbkgnd["jan02"], jan02, x, y, yerr)
  adddata2(u3pbkgnd["jan09"], jan09, x, y, yerr)
  themap = {}
  for xi, yi, yerri in zip(x, y, yerr):
    if round(xi) not in themap: themap[round(xi)] = []
    themap[round(xi)].append((xi, yi, yerri))
  fewx = []
  fewy = []
  fewyerr = []
  for rxi in themap:
    fewx.append(jt.mean(map(lambda (xi, yi, yerri): xi, themap[rxi])))
    fewy.append(jt.wmean(map(lambda (xi, yi, yerri): (yi, yerri), themap[rxi]))[0])
    fewyerr.append(jt.wmean(map(lambda (xi, yi, yerri): (yi, yerri), themap[rxi]))[1])
  pbkgnd_points = biggles.Points(fewx, fewy, symboltype="triangle", symbolsize=2.)
  p.add(pbkgnd_points)
#   p.add(biggles.DataLabel(10389, factor*0.00045, r"$e^+$-gas"))
  pbkgnd_points.label = r"$e^+$ beam-gas"

  x = []
  y = []
  yerr = []
  adddata2(u3ebkgnd["cont"], 0., x, y, yerr)
  adddata2(u3ebkgnd["high"], 0., x, y, yerr)
  adddata2(u3ebkgnd["nov28"], nov28, x, y, yerr)
  adddata2(u3ebkgnd["dec05"], dec05, x, y, yerr)
  adddata2(u3ebkgnd["dec12"], dec12, x, y, yerr)
  adddata2(u3ebkgnd["dec19"], dec19, x, y, yerr)
  adddata2(u3ebkgnd["dec26"], dec26, x, y, yerr)
  adddata2(u3ebkgnd["jan02"], jan02, x, y, yerr)
  adddata2(u3ebkgnd["jan09"], jan09, x, y, yerr)
  themap = {}
  for xi, yi, yerri in zip(x, y, yerr):
    if round(xi) not in themap: themap[round(xi)] = []
    themap[round(xi)].append((xi, yi, yerri))
  fewx = []
  fewy = []
  fewyerr = []
  for rxi in themap:
    fewx.append(jt.mean(map(lambda (xi, yi, yerri): xi, themap[rxi])))
    fewy.append(jt.wmean(map(lambda (xi, yi, yerri): (yi, yerri), themap[rxi]))[0])
    fewyerr.append(jt.wmean(map(lambda (xi, yi, yerri): (yi, yerri), themap[rxi]))[1])
  ebkgnd_points = biggles.Points(fewx, fewy, symboltype="filled inverted triangle", symbolsize=2.)
  p.add(ebkgnd_points)
#   p.add(biggles.DataLabel(10389, factor*0.0002, r"$e^-$-gas"))
  ebkgnd_points.label = r"$e^-$ beam-gas"

  addfunc(p, lambda w: u3func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area, w), 10290., 10420.)

  addfunc(p, lambda w: u3func_backgrounds(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area, w), 10290., 10420., linetype="dashed")
  p.add(biggles.DataLabel(10297., 0.7*u3func_backgrounds(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area, 10297.), r"all backgrounds", texthalign="left"))
  
  addfunc(p, lambda w: u3func_tau(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area, w), 10290., 10420.)
  p.add(biggles.DataLabel(10297., (1./0.7)*u3func_tau(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area, 10297.), r"$\tau^+\tau^-$", texthalign="left"))
  
  addfunc(p, lambda w: u3func_twophoton(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area, w), 10290., 10420.)
  p.add(biggles.DataLabel(10297., 0.7*u3func_twophoton(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area, 10297.), r"two-photon fusion", texthalign="left"))
  
  addfunc(p, lambda w: u3func_u1area(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area, w), 10290., 10420.)
  p.add(biggles.DataLabel(10305., 0.7*u3func_u1area(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area, 10305.), r"$\Upsilon(1S)$"))
  
  addfunc(p, lambda w: u3func_u2area(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area, w), 10290., 10420.)
  p.add(biggles.DataLabel(10305., (1./0.7)*u3func_u2area(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area, 10305.), r"$\Upsilon(2S)$"))
  
  addfunc(p, lambda w: u3func_jpsi(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area, w), 10290., 10420., linetype="dotted")
  p.add(biggles.DataLabel(10305., 0.7*u3func_jpsi(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area, 10305.), r"$J/\psi$"))
  
  addfunc(p, lambda w: u3func_psiprime(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area, w), 10290., 10420., linetype="dotted")
  p.add(biggles.DataLabel(10305., 0.7*u3func_psiprime(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area, 10305.), r"$\psi(2S)$"))
  
  def inset(area, rmsbeam, back, nov28, dec05, dec12, dec19, dec26, jan02, jan09, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area):
    p = biggles.FramedPlot()
    addfunc(p, lambda w: u3func_tau(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area, w), 10290., 10420.)
    p.x1.draw_ticks = 0
    p.x2.draw_ticks = 0
    p.y1.draw_ticks = 0
    p.y2.draw_ticks = 0
    p.x1.draw_ticklabels = 0
    p.y1.draw_ticklabels = 0
    p.x1.range = 10290., 10420.
    return p
  p.add(biggles.DataInset((10390, 0.2*factor), (10415, 0.02*factor), inset(area, rmsbeam, back, nov28, dec05, dec12, dec19, dec26, jan02, jan09, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area)))
  p.add(biggles.DataLine((10382., u3func_tau(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area, 10380.)), (10382., 0.05*factor)))
  p.add(biggles.DataLine((10382., 0.05*factor), (10390., 0.05*factor)))
  p.add(biggles.DataLine((10390., 0.05*factor), (10387., 0.05*factor*1.2)))
  p.add(biggles.DataLine((10390., 0.05*factor), (10387., 0.05*factor/1.2)))

  p.add(biggles.DataLabel(10379., 0.7*factor, r"observed $\Upsilon(3S)$ lineshape"))
#  p.add(biggles.PlotKey(0.9, 0.1, [pbkgnd_points, ebkgnd_points], texthalign="right"))

  p.add(biggles.DataLabel(10389., 0.00045*factor, r"$e^+$bg"))
  p.add(biggles.DataLabel(10395., 0.00012*factor, r"$e^-$ beam-gas"))

  p.y1.ticklabels = [r"$10^{-4}$", r"$10^{-3}$", r"$10^{-2}$", r"$0.1$", r"$1$"]
  p.x1.ticks = [10300, 10325, 10350, 10375, 10400]
  p.x2.ticks = [10300, 10325, 10350, 10375, 10400]
  p.x1.subticks = range(10290, 10420, 5)
  p.x2.subticks = range(10290, 10420, 5)
  p.x1.range = 10290., 10420.
  p.y1.range = 0.00005*factor, 1.3*factor
  p.aspect_ratio = 1.2
  p.y1.log = 1
  p.x1.label = r"Center-of-mass energy in MeV"
  p.y1.label = r"$\propto$ Hadronic Cross-section"
  return p
u3plot2(*fitrecord[3].values).show()
u3plot2(*fitrecord[3].values).write_eps("/home/mccann/antithesis/plots/awesome.eps")




###############################################################

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
u1data["cont"] = [get_runs(u1runs["cont"], usebhabha=True)]
u2data["cont"] = [get_runs(u2runs["cont"], usebhabha=True)]
u3data["cont"] = [get_runs(u3runs["cont"], usebhabha=True)]

datapoint1 = list(u1data["cont"][0])
datapoint2 = list(u2data["cont"][0])
datapoint3 = list(u3data["cont"][0])
datapoint2[1] -= (13.706441397531357 * 0.9868 * mygbwkf(9460.30, 0, 4, 0, 0, datapoint2[0]*2000.) + 13.706441397531357 * 0.578 * 0.0267 * mygbwkftau(9460.30, 0, 4, 0, 0, datapoint2[0]*2000.)) * 0.077045
datapoint3[1] -= (13.706441397531357 * 0.9868 * mygbwkf(9460.30, 0, 4, 0, 0, datapoint3[0]*2000.) + 13.706441397531357 * 0.578 * 0.0267 * mygbwkftau(9460.30, 0, 4, 0, 0, datapoint3[0]*2000.)) * 0.077045
datapoint3[1] -= (5.5910940385520558 * 0.9668 * mygbwkf(10023.26, 0, 4, 0, 0, datapoint3[0]*2000.) + 5.5910940385520558 * 0.578 * 0.017 * mygbwkftau(10023.26, 0, 4, 0, 0, datapoint3[0]*2000.)) * 0.077045

def fakeallthree(area1, area2, area3, back, twophofrac, w):
  tmp = 0.
  tmp += back * (1.-twophofrac) * 9000.**2 / w**2
  tmp += back * twophofrac * log(w**2/9000.**2)
  return tmp * 0.077045  # do this with bhabhas, rather than gamgams

def adddata(p, data, shift, circle=False, justadot=False):
  x = []
  y = []
  yerr = []
  for (e, h, herr) in data:
    x.append(e*2000.+shift)
    y.append(h)
    yerr.append(herr)
  p.add(biggles.Points(x, y, symboltype="filled circle", symbolsize=0.8))
  if not justadot:
    p.add(biggles.SymmetricErrorBarsY(x, y, yerr))
  if len(x) == 1 and circle:
    p.add(biggles.Points(x, y, symboltype="circle", symbolsize=7.))
  return None

def fitbackgrounds(back, twophofrac):
  chi = 0.
  for en, cs, cserr in [datapoint1, datapoint2, datapoint3]:
    chi += (fakeallthree(13.706, 5.591, 3.587, back, twophofrac, en*2000.)-cs)**2/cserr**2
  return chi

def fitbackgrounds_naive(back):
  chi = 0.
  for en, cs, cserr in [datapoint1]:
    chi += (fakeallthree(13.706, 5.591, 3.587, back, 0., en*2000.)-cs)**2/cserr**2
  return chi

m = Minuit(fitbackgrounds, start=[0.41, 0.10])
m.migrad()
print m.fval, m.values, m.errors
m2 = Minuit(fitbackgrounds_naive, start=[0.41])
m2.migrad()

p = biggles.FramedPlot()
adddata(p, u1data["cont"], 0, justadot=True)
adddata(p, u2data["cont"], 0, justadot=True)
adddata(p, u3data["cont"], 0, justadot=True)
adddata(p, [datapoint1], 0, circle=True)
adddata(p, [datapoint2], 0, circle=True)
adddata(p, [datapoint3], 0, circle=True)
tmp2 = addfunc(p, lambda w: 0.077045 * m.values[0] * ((1.-m.values[1]) * 9000.**2 / w**2 + m.values[1] * log(w**2/9000.**2)), 9350., 10450., linetype="solid")
tmp3 = addfunc(p, lambda w: 0.077045 * m2.values[0] * 9000.**2 / w**2, 9350., 10450., linetype="longdashed")
p.yrange = 0.021, 0.028
p.aspect_ratio = 0.5
p.x1.label = r"Center-of-mass energy in MeV"
p.y1.label = r"$\propto$ Hadronic Cross-section"
tmp3.label = r"Just $1/s$"
tmp2.label = ("With (%.2f $\pm$ %.2f)%% log$(s)$" % (m.values[1]*100., m.errors[1]*100.))
p.add(biggles.PlotKey(0.15, 0.25, [tmp3, tmp2]))
p.xrange = 9350., 10450.
p.show()
p.write_eps("/home/mccann/antithesis/plots/proceedings_backgrounds.eps")
