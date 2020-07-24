from minuit import *
import Numeric
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

def u1func(w, area=13.682, rmsbeam=3.787, back=0.40577, fullgam=0.053, yint=0.0186, phi=0., btautau=0.0267, tauyint=0.2, tauphi=0., twophofrac=0.0792):
  tmp = 0.
  tmp += area * 0.9868 * mygbwkf(9460.30, fullgam, rmsbeam, yint, phi, w)
  tmp += area * 0.578 * btautau * mygbwkftau(9460.30, fullgam, rmsbeam, tauyint, tauphi, w)
  tmp += back * (1.-twophofrac) * 9000.**2 / w**2
  tmp += back * twophofrac * log(w**2/9000.**2)
  return tmp

def u2func(w, area=5.7247, rmsbeam=4.17582, back=0.40496, fullgam=0.043, yint=0.01792, phi=0., btautau=0.017, tauyint=0.37, tauphi=0., twophofrac=0.0792, u1area=13.682):
  tmp = 0.
  tmp += area * 0.9668 * mygbwkf(10023.26, fullgam, rmsbeam, yint, phi, w)
  tmp += area * 0.578 * btautau * mygbwkftau(10023.26, fullgam, rmsbeam, tauyint, tauphi, w)
  tmp += back * (1.-twophofrac) * 9000.**2 / w**2
  tmp += back * twophofrac * log(w**2/9000.**2)
  tmp += u1area * mygbwkf(9460.30, 0., 0., 0., 0., w)
  return tmp

def u3func(w, area=3.639, rmsbeam=4.47966, back=0.40423, fullgam=0.0263, yint=0.01823, phi=0., btautau=0.0239, tauyint=0.27, tauphi=0., twophofrac=0.0792, u1area=13.682, u2area=5.7247):
  tmp = 0.
  tmp += area * 0.9708 * mygbwkf(10355.2, fullgam, rmsbeam, yint, phi, w)
  tmp += area * 0.578 * btautau * mygbwkftau(10355.2, fullgam, rmsbeam, tauyint, tauphi, w)
  tmp += back * (1.-twophofrac) * 9000.**2 / w**2
  tmp += back * twophofrac * log(w**2/9000.**2)
  tmp += u1area * mygbwkf(9460.30, 0., 0., 0., 0., w)
  tmp += u2area * mygbwkf(10023.26, 0., 0., 0., 0., w)
  return tmp

def deriv(w, f):
  return (f(w+0.01) - f(w-0.01))/0.02

got_runs = {}

def get_runs(runs, usebhabha=False, energycorrection=True):
  if str(runs) in got_runs:
    return got_runs[str(runs)]

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

  got_runs[str(runs)] = (average_energy, cs, cs_err)

  return average_energy, cs, cs_err

u1runs = {}
u2runs = {}
u3runs = {}
u1data = {}
u2data = {}
u3data = {}

def setup_runs(res, low, high):
  tmpruns = []
  for r in initialrunlist:
    if r not in mybadruns and low <= r <= high and runsummary[r].res == res:
      if runsummary[r].kind == 's': # or runsummary[r].kind == 'p':
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

pp = biggles.Table(1,2)
p = biggles.FramedPlot()
pp[0,0] = p
energies = map(lambda (a,b,c): a*2000., u1data["jan16"])
p.add(biggles.Points(u1runs["jan16"], energies))
p.add(biggles.Slope(0, (u1runs["jan16"][0], 9460.30)))
p.add(biggles.Slope(0, (u1runs["jan16"][0], 9460.30-5), linetype="dotted"))
p.add(biggles.Slope(0, (u1runs["jan16"][0], 9460.30-7), linetype="dotted"))
p.add(biggles.Slope(0, (u1runs["jan16"][0], 9460.30+7), linetype="dotted"))
p.add(biggles.Slope(0, (u1runs["jan16"][0], 9460.30+9), linetype="dotted"))
p = biggles.FramedPlot()
pp[0,1] = p
x = Numeric.arange(min(energies), max(energies), (max(energies)-min(energies))/100.)
y = Numeric.arange(min(energies), max(energies), (max(energies)-min(energies))/100.)
for i, xi in enumerate(x):
  y[i] = u1func(xi)
p.add(biggles.Curve(y, x))
pp.show()
for r in u1runs["jan16"]:
  if 9460.30-7 < runsummary[r].energy*2000. < 9460.30-5: print r
for r in u1runs["jan16"]:
  if 9460.30+7 < runsummary[r].energy*2000. < 9460.30+9: print r

pp = biggles.Table(1,2)
p = biggles.FramedPlot()
pp[0,0] = p
energies = map(lambda (a,b,c): a*2000., u1data["jan30"])
p.add(biggles.Points(u1runs["jan30"], energies))
p.add(biggles.Slope(0, (u1runs["jan30"][0], 9460.30)))
p.add(biggles.Slope(0, (u1runs["jan30"][0], 9460.30-2), linetype="dotted"))
p.add(biggles.Slope(0, (u1runs["jan30"][0], 9460.30-4), linetype="dotted"))
p.add(biggles.Slope(0, (u1runs["jan30"][0], 9460.30+5), linetype="dotted"))
p = biggles.FramedPlot()
pp[0,1] = p
x = Numeric.arange(min(energies), max(energies), (max(energies)-min(energies))/100.)
y = Numeric.arange(min(energies), max(energies), (max(energies)-min(energies))/100.)
for i, xi in enumerate(x):
  y[i] = u1func(xi)
p.add(biggles.Curve(y, x))
pp.show()
for r in u1runs["jan30"]:
  if 9460.30-4 < runsummary[r].energy*2000. < 9460.30-2: print r
for r in u1runs["jan30"]:
  if 9460.30 < runsummary[r].energy*2000. < 9460.30+5: print r

pp = biggles.Table(1,2)
p = biggles.FramedPlot()
pp[0,0] = p
energies = map(lambda (a,b,c): a*2000., u1data["feb06"])
p.add(biggles.Points(u1runs["feb06"], energies))
p.add(biggles.Slope(0, (u1runs["feb06"][0], 9460.30)))
p.add(biggles.Slope(0, (u1runs["feb06"][0], 9460.30-2.5), linetype="dotted"))
p.add(biggles.Slope(0, (u1runs["feb06"][0], 9460.30-4.5), linetype="dotted"))
p = biggles.FramedPlot()
pp[0,1] = p
x = Numeric.arange(min(energies), max(energies), (max(energies)-min(energies))/100.)
y = Numeric.arange(min(energies), max(energies), (max(energies)-min(energies))/100.)
for i, xi in enumerate(x):
  y[i] = u1func(xi)
p.add(biggles.Curve(y, x))
pp.show()
for r in u1runs["feb06"]:
  if 9460.30-2.5 < runsummary[r].energy*2000. < 9460.30: print r
for r in u1runs["feb06"]:
  if 9460.30-4.5 < runsummary[r].energy*2000. < 9460.30-2.5: print r

pp = biggles.Table(1,2)
p = biggles.FramedPlot()
pp[0,0] = p
energies = map(lambda (a,b,c): a*2000., u1data["feb13"])
p.add(biggles.Points(u1runs["feb13"], energies))
p.add(biggles.Slope(0, (u1runs["feb13"][0], 9460.30)))
p.add(biggles.Slope(0, (u1runs["feb13"][0], 9460.30-2.5), linetype="dotted"))
p.add(biggles.Slope(0, (u1runs["feb13"][0], 9460.30-4.5), linetype="dotted"))
p = biggles.FramedPlot()
pp[0,1] = p
x = Numeric.arange(min(energies), max(energies), (max(energies)-min(energies))/100.)
y = Numeric.arange(min(energies), max(energies), (max(energies)-min(energies))/100.)
for i, xi in enumerate(x):
  y[i] = u1func(xi)
p.add(biggles.Curve(y, x))
pp.show()
for r in u1runs["feb13"]:
  if 9460.30-4.5 < runsummary[r].energy*2000. < 9460.30-2.5: print r

pp = biggles.Table(1,2)
p = biggles.FramedPlot()
pp[0,0] = p
energies = map(lambda (a,b,c): a*2000., u1data["feb20"])
p.add(biggles.Points(u1runs["feb20"], energies))
p.add(biggles.Slope(0, (u1runs["feb20"][0], 9460.30)))
p.add(biggles.Slope(0, (u1runs["feb20"][0], 9460.30-2.5), linetype="dotted"))
p.add(biggles.Slope(0, (u1runs["feb20"][0], 9460.30-4.5), linetype="dotted"))
p = biggles.FramedPlot()
pp[0,1] = p
x = Numeric.arange(min(energies), max(energies), (max(energies)-min(energies))/100.)
y = Numeric.arange(min(energies), max(energies), (max(energies)-min(energies))/100.)
for i, xi in enumerate(x):
  y[i] = u1func(xi)
p.add(biggles.Curve(y, x))
pp.show()
for r in u1runs["feb20"]:
  if 9460.30-4.5 < runsummary[r].energy*2000. < 9460.30-2.5: print r

pp = biggles.Table(1,2)
p = biggles.FramedPlot()
pp[0,0] = p
energies = map(lambda (a,b,c): a*2000., u1data["feb27"])
p.add(biggles.Points(u1runs["feb27"], energies))
p.add(biggles.Slope(0, (u1runs["feb27"][0], 9460.30)))
p.add(biggles.Slope(0, (u1runs["feb27"][0], 9460.30-3), linetype="dotted"))
p = biggles.FramedPlot()
pp[0,1] = p
x = Numeric.arange(min(energies), max(energies), (max(energies)-min(energies))/100.)
y = Numeric.arange(min(energies), max(energies), (max(energies)-min(energies))/100.)
for i, xi in enumerate(x):
  y[i] = u1func(xi)
p.add(biggles.Curve(y, x))
pp.show()
for r in u1runs["feb27"]:
  if 9460.30-3 < runsummary[r].energy*2000. < 9460.30: print r

pp = biggles.Table(1,2)
p = biggles.FramedPlot()
pp[0,0] = p
energies = map(lambda (a,b,c): a*2000., u1data["mar06"])
p.add(biggles.Points(u1runs["mar06"], energies))
p.add(biggles.Slope(0, (u1runs["mar06"][0], 9460.30)))
p.add(biggles.Slope(0, (u1runs["mar06"][0], 9460.30-3), linetype="dotted"))
p = biggles.FramedPlot()
pp[0,1] = p
x = Numeric.arange(min(energies), max(energies), (max(energies)-min(energies))/100.)
y = Numeric.arange(min(energies), max(energies), (max(energies)-min(energies))/100.)
for i, xi in enumerate(x):
  y[i] = u1func(xi)
p.add(biggles.Curve(y, x))
pp.show()
for r in u1runs["mar06"]:
  if 9460.30-3 < runsummary[r].energy*2000. < 9460.30: print r

pp = biggles.Table(1,2)
p = biggles.FramedPlot()
pp[0,0] = p
energies = map(lambda (a,b,c): a*2000., u1data["mar13"])
p.add(biggles.Points(u1runs["mar13"], energies))
p.add(biggles.Slope(0, (u1runs["mar13"][0], 9460.30)))
p.add(biggles.Slope(0, (u1runs["mar13"][0], 9460.30-3), linetype="dotted"))
p = biggles.FramedPlot()
pp[0,1] = p
x = Numeric.arange(min(energies), max(energies), (max(energies)-min(energies))/100.)
y = Numeric.arange(min(energies), max(energies), (max(energies)-min(energies))/100.)
for i, xi in enumerate(x):
  y[i] = u1func(xi)
p.add(biggles.Curve(y, x))
pp.show()
for r in u1runs["mar13"]:
  if 9460.30-3 < runsummary[r].energy*2000. < 9460.30: print r

pp = biggles.Table(1,2)
p = biggles.FramedPlot()
pp[0,0] = p
energies = map(lambda (a,b,c): a*2000., u1data["apr03"])
p.add(biggles.Points(u1runs["apr03"], energies))
p.add(biggles.Slope(0, (u1runs["apr03"][0], 9460.30)))
p.add(biggles.Slope(0, (u1runs["apr03"][0], 9460.30-3), linetype="dotted"))
p.add(biggles.Slope(0, (u1runs["apr03"][0], 9460.30-5), linetype="dotted"))
p = biggles.FramedPlot()
pp[0,1] = p
x = Numeric.arange(min(energies), max(energies), (max(energies)-min(energies))/100.)
y = Numeric.arange(min(energies), max(energies), (max(energies)-min(energies))/100.)
for i, xi in enumerate(x):
  y[i] = u1func(xi)
p.add(biggles.Curve(y, x))
pp.show()
for r in u1runs["apr03"]:
  if 9460.30-5 < runsummary[r].energy*2000. < 9460.30-3: print r

pp = biggles.Table(1,2)
p = biggles.FramedPlot()
pp[0,0] = p
energies = map(lambda (a,b,c): a*2000., u1data["apr08"])
p.add(biggles.Points(u1runs["apr08"], energies))
p.add(biggles.Slope(0, (u1runs["apr08"][0], 9460.30)))
p.add(biggles.Slope(0, (u1runs["apr08"][0], 9460.30-3), linetype="dotted"))
p.add(biggles.Slope(0, (u1runs["apr08"][0], 9460.30-5), linetype="dotted"))
p = biggles.FramedPlot()
pp[0,1] = p
x = Numeric.arange(min(energies), max(energies), (max(energies)-min(energies))/100.)
y = Numeric.arange(min(energies), max(energies), (max(energies)-min(energies))/100.)
for i, xi in enumerate(x):
  y[i] = u1func(xi)
p.add(biggles.Curve(y, x))
pp.show()
for r in u1runs["apr08"]:
  if 9460.30-3 < runsummary[r].energy*2000. < 9460.30: print r

pp = biggles.Table(1,2)
p = biggles.FramedPlot()
pp[0,0] = p
energies = map(lambda (a,b,c): a*2000., u1data["apr09"])
p.add(biggles.Points(u1runs["apr09"], energies))
p.add(biggles.Slope(0, (u1runs["apr09"][0], 9460.30)))
p.add(biggles.Slope(0, (u1runs["apr09"][0], 9460.30-3), linetype="dotted"))
p.add(biggles.Slope(0, (u1runs["apr09"][0], 9460.30-5), linetype="dotted"))
p = biggles.FramedPlot()
pp[0,1] = p
x = Numeric.arange(min(energies), max(energies), (max(energies)-min(energies))/100.)
y = Numeric.arange(min(energies), max(energies), (max(energies)-min(energies))/100.)
for i, xi in enumerate(x):
  y[i] = u1func(xi)
p.add(biggles.Curve(y, x))
pp.show()
for r in u1runs["apr09"]:
  if 9460.30-3 < runsummary[r].energy*2000. < 9460.30: print r

pp = biggles.Table(1,2)
p = biggles.FramedPlot()
pp[0,0] = p
energies = map(lambda (a,b,c): a*2000., u1data["apr10"])
p.add(biggles.Points(u1runs["apr10"], energies))
p.add(biggles.Slope(0, (u1runs["apr10"][0], 9460.30)))
p.add(biggles.Slope(0, (u1runs["apr10"][0], 9460.30-3), linetype="dotted"))
p.add(biggles.Slope(0, (u1runs["apr10"][0], 9460.30-5), linetype="dotted"))
p = biggles.FramedPlot()
pp[0,1] = p
x = Numeric.arange(min(energies), max(energies), (max(energies)-min(energies))/100.)
y = Numeric.arange(min(energies), max(energies), (max(energies)-min(energies))/100.)
for i, xi in enumerate(x):
  y[i] = u1func(xi)
p.add(biggles.Curve(y, x))
pp.show()

pp = biggles.Table(1,2)
p = biggles.FramedPlot()
pp[0,0] = p
energies = map(lambda (a,b,c): a*2000., u2data["may29"])
p.add(biggles.Points(u2runs["may29"], energies))
p.add(biggles.Slope(0, (u2runs["may29"][0], 10023.26)))
p.add(biggles.Slope(0, (u2runs["may29"][0], 10023.26-3), linetype="dotted"))
p.add(biggles.Slope(0, (u2runs["may29"][0], 10023.26-5), linetype="dotted"))
p = biggles.FramedPlot()
pp[0,1] = p
x = Numeric.arange(min(energies), max(energies), (max(energies)-min(energies))/100.)
y = Numeric.arange(min(energies), max(energies), (max(energies)-min(energies))/100.)
for i, xi in enumerate(x):
  y[i] = u2func(xi)
p.add(biggles.Curve(y, x))
pp.show()
for r in u2runs["may29"]:
  if 10023.26-3 < runsummary[r].energy*2000. < 10023.26: print r

pp = biggles.Table(1,2)
p = biggles.FramedPlot()
pp[0,0] = p
energies = map(lambda (a,b,c): a*2000., u2data["jun11"])
p.add(biggles.Points(u2runs["jun11"], energies))
p.add(biggles.Slope(0, (u2runs["jun11"][0], 10023.26)))
p.add(biggles.Slope(0, (u2runs["jun11"][0], 10023.26-3), linetype="dotted"))
p.add(biggles.Slope(0, (u2runs["jun11"][0], 10023.26-5), linetype="dotted"))
p = biggles.FramedPlot()
pp[0,1] = p
x = Numeric.arange(min(energies), max(energies), (max(energies)-min(energies))/100.)
y = Numeric.arange(min(energies), max(energies), (max(energies)-min(energies))/100.)
for i, xi in enumerate(x):
  y[i] = u2func(xi)
p.add(biggles.Curve(y, x))
pp.show()
for r in u2runs["jun11"]:
  if 10023.26-3 < runsummary[r].energy*2000. < 10023.26: print r

pp = biggles.Table(1,2)
p = biggles.FramedPlot()
pp[0,0] = p
energies = map(lambda (a,b,c): a*2000., u2data["jun12"])
p.add(biggles.Points(u2runs["jun12"], energies))
p.add(biggles.Slope(0, (u2runs["jun12"][0], 10023.26)))
p.add(biggles.Slope(0, (u2runs["jun12"][0], 10023.26-3), linetype="dotted"))
p.add(biggles.Slope(0, (u2runs["jun12"][0], 10023.26-5), linetype="dotted"))
p = biggles.FramedPlot()
pp[0,1] = p
x = Numeric.arange(min(energies), max(energies), (max(energies)-min(energies))/100.)
y = Numeric.arange(min(energies), max(energies), (max(energies)-min(energies))/100.)
for i, xi in enumerate(x):
  y[i] = u2func(xi)
p.add(biggles.Curve(y, x))
pp.show()
for r in u2runs["jun12"]:
  if 10023.26-3 < runsummary[r].energy*2000. < 10023.26: print r

pp = biggles.Table(1,2)
p = biggles.FramedPlot()
pp[0,0] = p
energies = map(lambda (a,b,c): a*2000., u2data["jul10"])
p.add(biggles.Points(u2runs["jul10"], energies))
p.add(biggles.Slope(0, (u2runs["jul10"][0], 10023.26)))
p.add(biggles.Slope(0, (u2runs["jul10"][0], 10023.26-3), linetype="dotted"))
p.add(biggles.Slope(0, (u2runs["jul10"][0], 10023.26-5), linetype="dotted"))
p = biggles.FramedPlot()
pp[0,1] = p
x = Numeric.arange(min(energies), max(energies), (max(energies)-min(energies))/100.)
y = Numeric.arange(min(energies), max(energies), (max(energies)-min(energies))/100.)
for i, xi in enumerate(x):
  y[i] = u2func(xi)
p.add(biggles.Curve(y, x))
pp.show()
for r in u2runs["jul10"]:
  if 10023.26-3 < runsummary[r].energy*2000. < 10023.26: print r

pp = biggles.Table(1,2)
p = biggles.FramedPlot()
pp[0,0] = p
energies = map(lambda (a,b,c): a*2000., u2data["jul24"])
p.add(biggles.Points(u2runs["jul24"], energies))
p.add(biggles.Slope(0, (u2runs["jul24"][0], 10023.26)))
p.add(biggles.Slope(0, (u2runs["jul24"][0], 10023.26-3), linetype="dotted"))
p.add(biggles.Slope(0, (u2runs["jul24"][0], 10023.26-5), linetype="dotted"))
p = biggles.FramedPlot()
pp[0,1] = p
x = Numeric.arange(min(energies), max(energies), (max(energies)-min(energies))/100.)
y = Numeric.arange(min(energies), max(energies), (max(energies)-min(energies))/100.)
for i, xi in enumerate(x):
  y[i] = u2func(xi)
p.add(biggles.Curve(y, x))
pp.show()
for r in u2runs["jul24"]:
  if 10023.26-3 < runsummary[r].energy*2000. < 10023.26: print r

pp = biggles.Table(1,2)
p = biggles.FramedPlot()
pp[0,0] = p
energies = map(lambda (a,b,c): a*2000., u2data["aug07"])
p.add(biggles.Points(u2runs["aug07"], energies))
p.add(biggles.Slope(0, (u2runs["aug07"][0], 10023.26)))
p.add(biggles.Slope(0, (u2runs["aug07"][0], 10023.26-3), linetype="dotted"))
p.add(biggles.Slope(0, (u2runs["aug07"][0], 10023.26-5), linetype="dotted"))
p = biggles.FramedPlot()
pp[0,1] = p
x = Numeric.arange(min(energies), max(energies), (max(energies)-min(energies))/100.)
y = Numeric.arange(min(energies), max(energies), (max(energies)-min(energies))/100.)
for i, xi in enumerate(x):
  y[i] = u2func(xi)
p.add(biggles.Curve(y, x))
pp.show()
for r in u2runs["aug07"]:
  if 10023.26-3 < runsummary[r].energy*2000. < 10023.26: print r

pp = biggles.Table(1,2)
p = biggles.FramedPlot()
pp[0,0] = p
energies = map(lambda (a,b,c): a*2000., u3data["nov28"])
p.add(biggles.Points(u3runs["nov28"], energies))
p.add(biggles.Slope(0, (u3runs["nov28"][0], 10355.2)))
p.add(biggles.Slope(0, (u3runs["nov28"][0], 10355.2-3), linetype="dotted"))
p.add(biggles.Slope(0, (u3runs["nov28"][0], 10355.2-5), linetype="dotted"))
p = biggles.FramedPlot()
pp[0,1] = p
x = Numeric.arange(min(energies), max(energies), (max(energies)-min(energies))/100.)
y = Numeric.arange(min(energies), max(energies), (max(energies)-min(energies))/100.)
for i, xi in enumerate(x):
  y[i] = u3func(xi)
p.add(biggles.Curve(y, x))
pp.show()

pp = biggles.Table(1,2)
p = biggles.FramedPlot()
pp[0,0] = p
energies = map(lambda (a,b,c): a*2000., u3data["dec05"])
p.add(biggles.Points(u3runs["dec05"], energies))
p.add(biggles.Slope(0, (u3runs["dec05"][0], 10355.2)))
p.add(biggles.Slope(0, (u3runs["dec05"][0], 10355.2+7), linetype="dotted"))
p.add(biggles.Slope(0, (u3runs["dec05"][0], 10355.2+8), linetype="dotted"))
p = biggles.FramedPlot()
pp[0,1] = p
x = Numeric.arange(min(energies), max(energies), (max(energies)-min(energies))/100.)
y = Numeric.arange(min(energies), max(energies), (max(energies)-min(energies))/100.)
for i, xi in enumerate(x):
  y[i] = u3func(xi)
p.add(biggles.Curve(y, x))
pp.show()
for r in u3runs["dec05"]:
  if 10355.2+7 < runsummary[r].energy*2000. < 10355.2+8: print r

pp = biggles.Table(1,2)
p = biggles.FramedPlot()
pp[0,0] = p
energies = map(lambda (a,b,c): a*2000., u3data["dec12"])
p.add(biggles.Points(u3runs["dec12"], energies))
p.add(biggles.Slope(0, (u3runs["dec12"][0], 10355.2)))
p.add(biggles.Slope(0, (u3runs["dec12"][0], 10355.2-3), linetype="dotted"))
p.add(biggles.Slope(0, (u3runs["dec12"][0], 10355.2-5), linetype="dotted"))
p = biggles.FramedPlot()
pp[0,1] = p
x = Numeric.arange(min(energies), max(energies), (max(energies)-min(energies))/100.)
y = Numeric.arange(min(energies), max(energies), (max(energies)-min(energies))/100.)
for i, xi in enumerate(x):
  y[i] = u3func(xi)
p.add(biggles.Curve(y, x))
pp.show()
for r in u3runs["dec12"]:
  if 10355.2-3 < runsummary[r].energy*2000. < 10355.2: print r

pp = biggles.Table(1,2)
p = biggles.FramedPlot()
pp[0,0] = p
energies = map(lambda (a,b,c): a*2000., u3data["dec19"])
p.add(biggles.Points(u3runs["dec19"], energies))
p.add(biggles.Slope(0, (u3runs["dec19"][0], 10355.2)))
p.add(biggles.Slope(0, (u3runs["dec19"][0], 10355.2-3), linetype="dotted"))
p.add(biggles.Slope(0, (u3runs["dec19"][0], 10355.2-5), linetype="dotted"))
p = biggles.FramedPlot()
pp[0,1] = p
x = Numeric.arange(min(energies), max(energies), (max(energies)-min(energies))/100.)
y = Numeric.arange(min(energies), max(energies), (max(energies)-min(energies))/100.)
for i, xi in enumerate(x):
  y[i] = u3func(xi)
p.add(biggles.Curve(y, x))
pp.show()
for r in u3runs["dec19"]:
  if 10355.2-3 < runsummary[r].energy*2000. < 10355.2: print r

pp = biggles.Table(1,2)
p = biggles.FramedPlot()
pp[0,0] = p
energies = map(lambda (a,b,c): a*2000., u3data["dec26"])
p.add(biggles.Points(u3runs["dec26"], energies))
p.add(biggles.Slope(0, (u3runs["dec26"][0], 10355.2)))
p.add(biggles.Slope(0, (u3runs["dec26"][0], 10355.2-5), linetype="dotted"))
p.add(biggles.Slope(0, (u3runs["dec26"][0], 10355.2-7), linetype="dotted"))
p.add(biggles.Slope(0, (u3runs["dec26"][0], 10355.2+8), linetype="dotted"))
p.add(biggles.Slope(0, (u3runs["dec26"][0], 10355.2+10), linetype="dotted"))
p = biggles.FramedPlot()
pp[0,1] = p
x = Numeric.arange(min(energies), max(energies), (max(energies)-min(energies))/100.)
y = Numeric.arange(min(energies), max(energies), (max(energies)-min(energies))/100.)
for i, xi in enumerate(x):
  y[i] = u3func(xi)
p.add(biggles.Curve(y, x))
pp.show()
for r in u3runs["dec26"]:
  if 10355.2-2 < runsummary[r].energy*2000. < 10355.2: print r
for r in u3runs["dec26"]:
  if 10355.2-7 < runsummary[r].energy*2000. < 10355.2-5: print r
for r in u3runs["dec26"]:
  if 10355.2+8 < runsummary[r].energy*2000. < 10355.2+10: print r

pp = biggles.Table(1,2)
p = biggles.FramedPlot()
pp[0,0] = p
energies = map(lambda (a,b,c): a*2000., u3data["jan02"])
p.add(biggles.Points(u3runs["jan02"], energies))
p.add(biggles.Slope(0, (u3runs["jan02"][0], 10355.2)))
p.add(biggles.Slope(0, (u3runs["jan02"][0], 10355.2-3), linetype="dotted"))
p.add(biggles.Slope(0, (u3runs["jan02"][0], 10355.2-5), linetype="dotted"))
p = biggles.FramedPlot()
pp[0,1] = p
x = Numeric.arange(min(energies), max(energies), (max(energies)-min(energies))/100.)
y = Numeric.arange(min(energies), max(energies), (max(energies)-min(energies))/100.)
for i, xi in enumerate(x):
  y[i] = u3func(xi)
p.add(biggles.Curve(y, x))
pp.show()
for r in u3runs["jan02"]:
  if 10355.2-3 < runsummary[r].energy*2000. < 10355.2: print r
for r in u3runs["jan02"]:
  if 10355.2-5 < runsummary[r].energy*2000. < 10355.2-3: print r

pp = biggles.Table(1,2)
p = biggles.FramedPlot()
pp[0,0] = p
energies = map(lambda (a,b,c): a*2000., u3data["jan09"])
p.add(biggles.Points(u3runs["jan09"], energies))
p.add(biggles.Slope(0, (u3runs["jan09"][0], 10355.2)))
p.add(biggles.Slope(0, (u3runs["jan09"][0], 10355.2-5), linetype="dotted"))
p.add(biggles.Slope(0, (u3runs["jan09"][0], 10355.2-7), linetype="dotted"))
p = biggles.FramedPlot()
pp[0,1] = p
x = Numeric.arange(min(energies), max(energies), (max(energies)-min(energies))/100.)
y = Numeric.arange(min(energies), max(energies), (max(energies)-min(energies))/100.)
for i, xi in enumerate(x):
  y[i] = u3func(xi)
p.add(biggles.Curve(y, x))
pp.show()
for r in u3runs["jan09"]:
  if 10355.2-5 < runsummary[r].energy*2000. < 10355.2: print r
for r in u3runs["jan09"]:
  if 10355.2-7 < runsummary[r].energy*2000. < 10355.2-5: print r

###########################

energies = (lambda r: runsummary[r].energy*2000.)(123164), (lambda r: runsummary[r].energy*2000.)(123164), (lambda r: runsummary[r].energy*2000.)(123165), (lambda r: runsummary[r].energy*2000.)(123176), (lambda r: runsummary[r].energy*2000.)(123170), (lambda r: runsummary[r].energy*2000.)(123172), (lambda r: runsummary[r].energy*2000.)(123596), (lambda r: runsummary[r].energy*2000.)(123604), (lambda r: runsummary[r].energy*2000.)(123603), (lambda r: runsummary[r].energy*2000.)(123607), (lambda r: runsummary[r].energy*2000.)(123828), (lambda r: runsummary[r].energy*2000.)(123832), (lambda r: runsummary[r].energy*2000.)(123781), (lambda r: runsummary[r].energy*2000.)(123790), (lambda r: runsummary[r].energy*2000.)(124080), (lambda r: runsummary[r].energy*2000.)(124091), (lambda r: runsummary[r].energy*2000.)(124102), (lambda r: runsummary[r].energy*2000.)(124111), (lambda r: runsummary[r].energy*2000.)(124279), (lambda r: runsummary[r].energy*2000.)(124294), (lambda r: runsummary[r].energy*2000.)(124436), (lambda r: runsummary[r].energy*2000.)(124437), (lambda r: runsummary[r].energy*2000.)(124450), (lambda r: runsummary[r].energy*2000.)(124625), (lambda r: runsummary[r].energy*2000.)(124639), (lambda r: runsummary[r].energy*2000.)(125125), (lambda r: runsummary[r].energy*2000.)(125126), (lambda r: runsummary[r].energy*2000.)(125254), (lambda r: runsummary[r].energy*2000.)(125262), (lambda r: runsummary[r].energy*2000.)(125285), (lambda r: runsummary[r].energy*2000.)(125295)

x = Numeric.arange(min(energies), max(energies), (max(energies)-min(energies))/100.)
y = Numeric.arange(min(energies), max(energies), (max(energies)-min(energies))/100.)
for i, xi in enumerate(x):
  y[i] = deriv(xi, lambda xii: deriv(xii, u1func))
p = biggles.FramedPlot()
p.add(biggles.Curve(x,y))
p.add(biggles.LineX((lambda r: runsummary[r].energy*2000.)(123164)))
p.add(biggles.LineX((lambda r: runsummary[r].energy*2000.)(123164)))
p.add(biggles.LineX((lambda r: runsummary[r].energy*2000.)(123165)))
p.add(biggles.LineX((lambda r: runsummary[r].energy*2000.)(123176)))
p.add(biggles.LineX((lambda r: runsummary[r].energy*2000.)(123170)))
p.add(biggles.LineX((lambda r: runsummary[r].energy*2000.)(123172)))
p.add(biggles.LineX((lambda r: runsummary[r].energy*2000.)(123596)))
p.add(biggles.LineX((lambda r: runsummary[r].energy*2000.)(123604)))
p.add(biggles.LineX((lambda r: runsummary[r].energy*2000.)(123603)))
p.add(biggles.LineX((lambda r: runsummary[r].energy*2000.)(123607)))
p.add(biggles.LineX((lambda r: runsummary[r].energy*2000.)(123828)))
p.add(biggles.LineX((lambda r: runsummary[r].energy*2000.)(123832)))
p.add(biggles.LineX((lambda r: runsummary[r].energy*2000.)(123781)))
p.add(biggles.LineX((lambda r: runsummary[r].energy*2000.)(123790)))
p.add(biggles.LineX((lambda r: runsummary[r].energy*2000.)(124080)))
p.add(biggles.LineX((lambda r: runsummary[r].energy*2000.)(124091)))
p.add(biggles.LineX((lambda r: runsummary[r].energy*2000.)(124102)))
p.add(biggles.LineX((lambda r: runsummary[r].energy*2000.)(124111)))
p.add(biggles.LineX((lambda r: runsummary[r].energy*2000.)(124279)))
p.add(biggles.LineX((lambda r: runsummary[r].energy*2000.)(124294)))
p.add(biggles.LineX((lambda r: runsummary[r].energy*2000.)(124436)))
p.add(biggles.LineX((lambda r: runsummary[r].energy*2000.)(124437)))
p.add(biggles.LineX((lambda r: runsummary[r].energy*2000.)(124450)))
p.add(biggles.LineX((lambda r: runsummary[r].energy*2000.)(124625)))
p.add(biggles.LineX((lambda r: runsummary[r].energy*2000.)(124639)))
p.add(biggles.LineX((lambda r: runsummary[r].energy*2000.)(125125)))
p.add(biggles.LineX((lambda r: runsummary[r].energy*2000.)(125126)))
p.add(biggles.LineX((lambda r: runsummary[r].energy*2000.)(125254)))
p.add(biggles.LineX((lambda r: runsummary[r].energy*2000.)(125262)))
p.add(biggles.LineX((lambda r: runsummary[r].energy*2000.)(125285)))
p.add(biggles.LineX((lambda r: runsummary[r].energy*2000.)(125295)))
p.yrange = -0.06, 0.03
p.show()

energies = (lambda r: runsummary[r].energy*2000.)(126462), (lambda r: runsummary[r].energy*2000.)(126464), (lambda r: runsummary[r].energy*2000.)(126465), (lambda r: runsummary[r].energy*2000.)(126467), (lambda r: runsummary[r].energy*2000.)(126776), (lambda r: runsummary[r].energy*2000.)(126777), (lambda r: runsummary[r].energy*2000.)(126778), (lambda r: runsummary[r].energy*2000.)(126779), (lambda r: runsummary[r].energy*2000.)(126823), (lambda r: runsummary[r].energy*2000.)(126824), (lambda r: runsummary[r].energy*2000.)(126825), (lambda r: runsummary[r].energy*2000.)(127588), (lambda r: runsummary[r].energy*2000.)(127589), (lambda r: runsummary[r].energy*2000.)(127592), (lambda r: runsummary[r].energy*2000.)(127610), (lambda r: runsummary[r].energy*2000.)(127611), (lambda r: runsummary[r].energy*2000.)(127612), (lambda r: runsummary[r].energy*2000.)(127924), (lambda r: runsummary[r].energy*2000.)(127925), (lambda r: runsummary[r].energy*2000.)(127927), (lambda r: runsummary[r].energy*2000.)(128310), (lambda r: runsummary[r].energy*2000.)(128312), (lambda r: runsummary[r].energy*2000.)(128313) 

x = Numeric.arange(min(energies), max(energies), (max(energies)-min(energies))/100.)
y = Numeric.arange(min(energies), max(energies), (max(energies)-min(energies))/100.)
for i, xi in enumerate(x):
  y[i] = deriv(xi, lambda xii: deriv(xii, u2func))
p = biggles.FramedPlot()
p.add(biggles.Curve(x,y))
p.add(biggles.LineX((lambda r: runsummary[r].energy*2000.)(126462)))
p.add(biggles.LineX((lambda r: runsummary[r].energy*2000.)(126464)))
p.add(biggles.LineX((lambda r: runsummary[r].energy*2000.)(126465)))
p.add(biggles.LineX((lambda r: runsummary[r].energy*2000.)(126467)))
p.add(biggles.LineX((lambda r: runsummary[r].energy*2000.)(126776)))
p.add(biggles.LineX((lambda r: runsummary[r].energy*2000.)(126777)))
p.add(biggles.LineX((lambda r: runsummary[r].energy*2000.)(126778)))
p.add(biggles.LineX((lambda r: runsummary[r].energy*2000.)(126779)))
p.add(biggles.LineX((lambda r: runsummary[r].energy*2000.)(126823)))
p.add(biggles.LineX((lambda r: runsummary[r].energy*2000.)(126824)))
p.add(biggles.LineX((lambda r: runsummary[r].energy*2000.)(126825)))
p.add(biggles.LineX((lambda r: runsummary[r].energy*2000.)(127588)))
p.add(biggles.LineX((lambda r: runsummary[r].energy*2000.)(127589)))
p.add(biggles.LineX((lambda r: runsummary[r].energy*2000.)(127592)))
p.add(biggles.LineX((lambda r: runsummary[r].energy*2000.)(127610)))
p.add(biggles.LineX((lambda r: runsummary[r].energy*2000.)(127611)))
p.add(biggles.LineX((lambda r: runsummary[r].energy*2000.)(127612)))
p.add(biggles.LineX((lambda r: runsummary[r].energy*2000.)(127924)))
p.add(biggles.LineX((lambda r: runsummary[r].energy*2000.)(127925)))
p.add(biggles.LineX((lambda r: runsummary[r].energy*2000.)(127927)))
p.add(biggles.LineX((lambda r: runsummary[r].energy*2000.)(128310)))
p.add(biggles.LineX((lambda r: runsummary[r].energy*2000.)(128312)))
p.add(biggles.LineX((lambda r: runsummary[r].energy*2000.)(128313)))
p.yrange = -0.06, 0.03
p.show()

energies = (lambda r: runsummary[r].energy*2000.)(122073), (lambda r: runsummary[r].energy*2000.)(122077), (lambda r: runsummary[r].energy*2000.)(122245), (lambda r: runsummary[r].energy*2000.)(122256), (lambda r: runsummary[r].energy*2000.)(122409), (lambda r: runsummary[r].energy*2000.)(122415), (lambda r: runsummary[r].energy*2000.)(122535), (lambda r: runsummary[r].energy*2000.)(122542), (lambda r: runsummary[r].energy*2000.)(122556), (lambda r: runsummary[r].energy*2000.)(122564), (lambda r: runsummary[r].energy*2000.)(122537), (lambda r: runsummary[r].energy*2000.)(122548), (lambda r: runsummary[r].energy*2000.)(122549), (lambda r: runsummary[r].energy*2000.)(122560), (lambda r: runsummary[r].energy*2000.)(122766), (lambda r: runsummary[r].energy*2000.)(122776), (lambda r: runsummary[r].energy*2000.)(122780), (lambda r: runsummary[r].energy*2000.)(122781), (lambda r: runsummary[r].energy*2000.)(122993), (lambda r: runsummary[r].energy*2000.)(123004), (lambda r: runsummary[r].energy*2000.)(122996), (lambda r: runsummary[r].energy*2000.)(122998) 

x = Numeric.arange(min(energies), max(energies), (max(energies)-min(energies))/100.)
y = Numeric.arange(min(energies), max(energies), (max(energies)-min(energies))/100.)
for i, xi in enumerate(x):
  y[i] = deriv(xi, lambda xii: deriv(xii, u3func))
p = biggles.FramedPlot()
p.add(biggles.Curve(x,y))
p.add(biggles.LineX((lambda r: runsummary[r].energy*2000.)(122073)))
p.add(biggles.LineX((lambda r: runsummary[r].energy*2000.)(122077)))
p.add(biggles.LineX((lambda r: runsummary[r].energy*2000.)(122245)))
p.add(biggles.LineX((lambda r: runsummary[r].energy*2000.)(122256)))
p.add(biggles.LineX((lambda r: runsummary[r].energy*2000.)(122409)))
p.add(biggles.LineX((lambda r: runsummary[r].energy*2000.)(122415)))
p.add(biggles.LineX((lambda r: runsummary[r].energy*2000.)(122535)))
p.add(biggles.LineX((lambda r: runsummary[r].energy*2000.)(122542)))
p.add(biggles.LineX((lambda r: runsummary[r].energy*2000.)(122556)))
p.add(biggles.LineX((lambda r: runsummary[r].energy*2000.)(122564)))
p.add(biggles.LineX((lambda r: runsummary[r].energy*2000.)(122537)))
p.add(biggles.LineX((lambda r: runsummary[r].energy*2000.)(122548)))
p.add(biggles.LineX((lambda r: runsummary[r].energy*2000.)(122549)))
p.add(biggles.LineX((lambda r: runsummary[r].energy*2000.)(122560)))
p.add(biggles.LineX((lambda r: runsummary[r].energy*2000.)(122766)))
p.add(biggles.LineX((lambda r: runsummary[r].energy*2000.)(122776)))
p.add(biggles.LineX((lambda r: runsummary[r].energy*2000.)(122780)))
p.add(biggles.LineX((lambda r: runsummary[r].energy*2000.)(122781)))
p.add(biggles.LineX((lambda r: runsummary[r].energy*2000.)(122993)))
p.add(biggles.LineX((lambda r: runsummary[r].energy*2000.)(123004)))
p.add(biggles.LineX((lambda r: runsummary[r].energy*2000.)(122996)))
p.add(biggles.LineX((lambda r: runsummary[r].energy*2000.)(122998)))
p.yrange = -0.06, 0.03
p.show()

###########################

runstart = pickle.load(open("old_dotps/runstart.p"))
runend = pickle.load(open("old_dotps/runend.p"))

jan16 = 0.2385
jan30 = 0.6213
feb06 = 0.0660
feb13 = 0.0542
feb20 = 0.2200
feb27 = 0.1788
mar06 = 0.1869
mar13 = 0.5596
apr03 = 0.9043
apr08 = 0.7882
apr09 = 0.4462
apr10 = 0.6142

may29 = -1.1271
jun11 = -1.0656
jun12 = -1.4200
jul10 = -0.7603
jul24 = -0.6656
aug07 = -0.3975

nov28 = -2.1343
dec05 = -4.0054
dec12 = -3.1914
dec19 = -2.4656
dec26 = -2.7310
jan02 = -2.5623
jan09 = -2.6531

def miscal(cor, runs1, runs2, f, usebhabha):
  dt = min(map(lambda r: runstart[r], runs2)) - max(map(lambda r: runend[r], runs1))
  e1, sig1, err1 = get_runs(runs1, usebhabha=usebhabha)
  e2, sig2, err2 = get_runs(runs2, usebhabha=usebhabha)
  e1 *= 2000.
  e2 *= 2000.
  de = e2 - e1
  dsig = sig2 - sig1
  derr = sqrt(err2**2 + err1**2)
  der = deriv((e1+e2)/2.+cor, f)
  miscal = dsig/der - de
  mcerr = derr/abs(der)
  print "%32s vs %26s |    %5.2f +/- %4.2f    | %4d min | %7.4f | %7.4f" % (str(runs1), str(runs2), miscal, mcerr, int(round(dt/60.)), der, de)

def miscal2(cor, runs1, runs2, f, usebhabha):
  dt = min(map(lambda r: runstart[r], runs2)) - max(map(lambda r: runend[r], runs1))
  e1, sig1, err1 = get_runs(runs1, usebhabha=usebhabha)
  e2, sig2, err2 = get_runs(runs2, usebhabha=usebhabha)
  e1 *= 2000.
  e2 *= 2000.
  de = e2 - e1
  dsig = sig2 - sig1
  derr = sqrt(err2**2 + err1**2)
  der = deriv((e1+e2)/2.+cor, f)
  miscal = dsig/der - de
  mcerr = derr/abs(der)
  return miscal, mcerr

print "                                                               | Miscalibration (MeV) |   time   |  deriv. | Ediff (MeV)"
print "---------------------------------------------------------------+----------------------+----------+---------+------------"
miscal(jan16, [123164, 123165], [123176], u1func, usebhabha=False)
miscal(jan16, [123170], [123172], u1func, usebhabha=False)
miscal(jan30, [123596], [123604], u1func, usebhabha=False)
miscal(jan30, [123603], [123607], u1func, usebhabha=False)
miscal(feb06, [123828], [123832], u1func, usebhabha=False)
miscal(feb06, [123781], [123790], u1func, usebhabha=False)
miscal(feb13, [124080], [124091], u1func, usebhabha=False)
miscal(feb20, [124102], [124111], u1func, usebhabha=False)
miscal(feb27, [124279], [124294], u1func, usebhabha=False)
miscal(mar06, [124436, 124437], [124450], u1func, usebhabha=False)
miscal(mar13, [124625], [124639], u1func, usebhabha=False)
miscal(apr03, [125125], [125126], u1func, usebhabha=False)
miscal(apr08, [125254], [125262], u1func, usebhabha=False)
miscal(apr09, [125285], [125295], u1func, usebhabha=False)
print "---------------------------------------------------------------+----------------------+----------+---------+------------"
miscal(may29, [126462, 126464], [126465, 126467], u2func, usebhabha=False)
miscal((jun11+jun12)/2., [126776, 126777, 126778, 126779], [126823, 126824, 126825], u2func, usebhabha=False)
miscal(jul10, [127588, 127589, 127592], [127610, 127611, 127612], u2func, usebhabha=False)
miscal(jul24, [127924, 127925], [127927], u2func, usebhabha=False)
miscal(aug07, [128310], [128312, 128313], u2func, usebhabha=False)
print "---------------------------------------------------------------+----------------------+----------+---------+------------"
miscal(dec05, [122073], [122077], u3func, usebhabha=False)
miscal(dec12, [122245], [122256], u3func, usebhabha=False)
miscal(dec19, [122409], [122415], u3func, usebhabha=False)
miscal(dec26, [122535], [122542], u3func, usebhabha=False)
miscal(dec26, [122556], [122564], u3func, usebhabha=False)
miscal(dec26, [122537], [122548], u3func, usebhabha=False)
miscal(dec26, [122549], [122560], u3func, usebhabha=False)
miscal(jan02, [122766], [122776], u3func, usebhabha=False)
miscal(jan02, [122780], [122781], u3func, usebhabha=False)
miscal(jan09, [122993], [123004], u3func, usebhabha=False)
miscal(jan09, [122996], [122998], u3func, usebhabha=False)

#                                                                | Miscalibration (MeV) |   time   |  deriv. | Ediff (MeV)
# ---------------------------------------------------------------+----------------------+----------+---------+------------
#                 [123164, 123165] vs                   [123176] |     0.78 +/- 0.35    |  535 min |  0.0751 | -0.0731
#                         [123170] vs                   [123172] |     1.23 +/- 0.58    |   33 min | -0.0595 |  0.0000
#                         [123596] vs                   [123604] |     0.04 +/- 0.31    |  572 min |  0.1189 | -0.0200
#                         [123603] vs                   [123607] |    -0.33 +/- 0.54    |  185 min | -0.1087 |  0.0000
#                         [123828] vs                   [123832] |     0.64 +/- 0.56    |  243 min |  0.0981 | -0.0200
#                         [123781] vs                   [123790] |     0.44 +/- 0.29    |  456 min |  0.1235 |  0.0000
#                         [124080] vs                   [124091] |    -0.48 +/- 0.30    |  460 min |  0.1236 | -0.3200
#                         [124102] vs                   [124111] |     0.35 +/- 0.27    |  374 min |  0.1235 |  0.2400
#                         [124279] vs                   [124294] |    -0.75 +/- 0.46    |  509 min |  0.1015 | -0.0400
#                 [124436, 124437] vs                   [124450] |     1.02 +/- 0.43    |  457 min |  0.1053 | -0.1402
#                         [124625] vs                   [124639] |     0.12 +/- 0.49    |  544 min |  0.0949 | -0.2000
#                         [125125] vs                   [125126] |    -0.06 +/- 0.34    |   22 min |  0.1226 |  0.0000
#                         [125254] vs                   [125262] |    -0.21 +/- 0.86    |  436 min |  0.0678 |  0.0000
#                         [125285] vs                   [125295] |    -0.86 +/- 0.75    |  451 min |  0.0815 |  0.0000
# ---------------------------------------------------------------+----------------------+----------+---------+------------
#                 [126462, 126464] vs           [126465, 126467] |     0.50 +/- 0.50    |   22 min |  0.0401 | -0.1283
# [126776, 126777, 126778, 126779] vs   [126823, 126824, 126825] |    -0.44 +/- 0.26    | 1453 min |  0.0405 |  0.1519
#         [127588, 127589, 127592] vs   [127610, 127611, 127612] |     0.02 +/- 0.32    |  645 min |  0.0393 |  0.0763
#                 [127924, 127925] vs                   [127927] |     0.25 +/- 0.53    |   30 min |  0.0396 |  0.0000
#                         [128310] vs           [128312, 128313] |    -0.90 +/- 0.83    |   15 min |  0.0383 |  0.0000
# ---------------------------------------------------------------+----------------------+----------+---------+------------
#                         [122073] vs                   [122077] |     0.77 +/- 1.13    |  150 min | -0.0181 |  0.0000
#                         [122245] vs                   [122256] |     0.20 +/- 0.90    |  653 min |  0.0229 | -0.2000
#                         [122409] vs                   [122415] |     0.88 +/- 1.00    |  474 min |  0.0219 |  0.0000
#                         [122535] vs                   [122542] |    -0.96 +/- 0.84    |  386 min |  0.0221 |  0.0000
#                         [122556] vs                   [122564] |    -0.75 +/- 0.98    |  368 min |  0.0221 |  0.0000
#                         [122537] vs                   [122548] |    -1.39 +/- 1.63    |  404 min |  0.0086 |  0.4000
#                         [122549] vs                   [122560] |    -0.66 +/- 0.94    |  416 min | -0.0179 |  0.0000
#                         [122766] vs                   [122776] |     1.02 +/- 0.91    |  430 min |  0.0231 | -0.4000
#                         [122780] vs                   [122781] |     0.96 +/- 1.48    |    2 min |  0.0156 |  0.0000
#                         [122993] vs                   [123004] |    -1.63 +/- 0.99    |  521 min |  0.0231 | -0.2000
#                         [122996] vs                   [122998] |     0.46 +/- 2.08    |   13 min |  0.0095 |  0.0000

print "                                                               | Miscalibration (MeV) |   time   |  deriv. | Ediff (MeV)"
print "---------------------------------------------------------------+----------------------+----------+---------+------------"
miscal(jan16, [123164, 123165], [123176], lambda x: u1func(x)*0.077045, usebhabha=True)
miscal(jan16, [123170], [123172], lambda x: u1func(x)*0.077045, usebhabha=True)
miscal(jan30, [123596], [123604], lambda x: u1func(x)*0.077045, usebhabha=True)
miscal(jan30, [123603], [123607], lambda x: u1func(x)*0.077045, usebhabha=True)
miscal(feb06, [123828], [123832], lambda x: u1func(x)*0.077045, usebhabha=True)
miscal(feb06, [123781], [123790], lambda x: u1func(x)*0.077045, usebhabha=True)
miscal(feb13, [124080], [124091], lambda x: u1func(x)*0.077045, usebhabha=True)
miscal(feb20, [124102], [124111], lambda x: u1func(x)*0.077045, usebhabha=True)
miscal(feb27, [124279], [124294], lambda x: u1func(x)*0.077045, usebhabha=True)
miscal(mar06, [124436, 124437], [124450], lambda x: u1func(x)*0.077045, usebhabha=True)
miscal(mar13, [124625], [124639], lambda x: u1func(x)*0.077045, usebhabha=True)
miscal(apr03, [125125], [125126], lambda x: u1func(x)*0.077045, usebhabha=True)
miscal(apr08, [125254], [125262], lambda x: u1func(x)*0.077045, usebhabha=True)
miscal(apr09, [125285], [125295], lambda x: u1func(x)*0.077045, usebhabha=True)
print "---------------------------------------------------------------+----------------------+----------+---------+------------"
miscal(may29, [126462, 126464], [126465, 126467], lambda x: u2func(x)*0.077045, usebhabha=True)
miscal((jun11+jun12)/2., [126776, 126777, 126778, 126779], [126823, 126824, 126825], lambda x: u2func(x)*0.077045, usebhabha=True)
miscal(jul10, [127588, 127589, 127592], [127610, 127611, 127612], lambda x: u2func(x)*0.077045, usebhabha=True)
miscal(jul24, [127924, 127925], [127927], lambda x: u2func(x)*0.077045, usebhabha=True)
miscal(aug07, [128310], [128312, 128313], lambda x: u2func(x)*0.077045, usebhabha=True)
print "---------------------------------------------------------------+----------------------+----------+---------+------------"
miscal(dec05, [122073], [122077], lambda x: u3func(x)*0.077045, usebhabha=True)
miscal(dec12, [122245], [122256], lambda x: u3func(x)*0.077045, usebhabha=True)
miscal(dec19, [122409], [122415], lambda x: u3func(x)*0.077045, usebhabha=True)
miscal(dec26, [122535], [122542], lambda x: u3func(x)*0.077045, usebhabha=True)
miscal(dec26, [122556], [122564], lambda x: u3func(x)*0.077045, usebhabha=True)
miscal(dec26, [122537], [122548], lambda x: u3func(x)*0.077045, usebhabha=True)
miscal(dec26, [122549], [122560], lambda x: u3func(x)*0.077045, usebhabha=True)
miscal(jan02, [122766], [122776], lambda x: u3func(x)*0.077045, usebhabha=True)
miscal(jan02, [122780], [122781], lambda x: u3func(x)*0.077045, usebhabha=True)
miscal(jan09, [122993], [123004], lambda x: u3func(x)*0.077045, usebhabha=True)
miscal(jan09, [122996], [122998], lambda x: u3func(x)*0.077045, usebhabha=True)

#                                                                | Miscalibration (MeV) |   time   |  deriv. | Ediff (MeV)
# ---------------------------------------------------------------+----------------------+----------+---------+------------
#                 [123164, 123165] vs                   [123176] |     0.27 +/- 0.15    |  535 min |  0.0058 | -0.0727
#                         [123170] vs                   [123172] |     0.04 +/- 0.22    |   33 min | -0.0046 |  0.0000
#                         [123596] vs                   [123604] |     0.05 +/- 0.11    |  572 min |  0.0092 | -0.0200
#                         [123603] vs                   [123607] |    -0.19 +/- 0.18    |  185 min | -0.0084 |  0.0000
#                         [123828] vs                   [123832] |     0.14 +/- 0.19    |  243 min |  0.0076 | -0.0200
#                         [123781] vs                   [123790] |     0.01 +/- 0.10    |  456 min |  0.0095 |  0.0000
#                         [124080] vs                   [124091] |     0.00 +/- 0.10    |  460 min |  0.0095 | -0.3200
#                         [124102] vs                   [124111] |    -0.02 +/- 0.09    |  374 min |  0.0095 |  0.2400
#                         [124279] vs                   [124294] |    -0.14 +/- 0.15    |  509 min |  0.0078 | -0.0400
#                 [124436, 124437] vs                   [124450] |     0.13 +/- 0.15    |  457 min |  0.0081 | -0.1408
#                         [124625] vs                   [124639] |     0.16 +/- 0.16    |  544 min |  0.0073 | -0.2000
#                         [125125] vs                   [125126] |     0.02 +/- 0.12    |   22 min |  0.0094 |  0.0000
#                         [125254] vs                   [125262] |    -0.12 +/- 0.27    |  436 min |  0.0052 |  0.0000
#                         [125285] vs                   [125295] |     0.58 +/- 0.25    |  451 min |  0.0063 |  0.0000
# ---------------------------------------------------------------+----------------------+----------+---------+------------
#                 [126462, 126464] vs           [126465, 126467] |    -0.23 +/- 0.19    |   22 min |  0.0031 | -0.1293
# [126776, 126777, 126778, 126779] vs   [126823, 126824, 126825] |     0.01 +/- 0.10    | 1453 min |  0.0031 |  0.1504
#         [127588, 127589, 127592] vs   [127610, 127611, 127612] |    -0.05 +/- 0.12    |  645 min |  0.0030 |  0.0760
#                 [127924, 127925] vs                   [127927] |    -0.26 +/- 0.19    |   30 min |  0.0031 |  0.0000
#                         [128310] vs           [128312, 128313] |    -0.14 +/- 0.29    |   15 min |  0.0030 |  0.0000
# ---------------------------------------------------------------+----------------------+----------+---------+------------
#                         [122073] vs                   [122077] |    -0.06 +/- 0.42    |  150 min | -0.0014 |  0.0000
#                         [122245] vs                   [122256] |     0.31 +/- 0.38    |  653 min |  0.0018 | -0.2000
#                         [122409] vs                   [122415] |     0.71 +/- 0.38    |  474 min |  0.0017 |  0.0000
#                         [122535] vs                   [122542] |    -0.08 +/- 0.34    |  386 min |  0.0017 |  0.0000
#                         [122556] vs                   [122564] |     0.02 +/- 0.38    |  368 min |  0.0017 |  0.0000
#                         [122537] vs                   [122548] |     1.22 +/- 0.73    |  404 min |  0.0007 |  0.4000
#                         [122549] vs                   [122560] |     0.33 +/- 0.39    |  416 min | -0.0014 |  0.0000
#                         [122766] vs                   [122776] |     0.55 +/- 0.34    |  430 min |  0.0018 | -0.4000
#                         [122780] vs                   [122781] |     1.34 +/- 0.66    |    2 min |  0.0012 |  0.0000
#                         [122993] vs                   [123004] |    -0.02 +/- 0.38    |  521 min |  0.0018 | -0.2000
#                         [122996] vs                   [122998] |    -0.14 +/- 0.88    |   13 min |  0.0007 |  0.0000

print miscal2(feb13, [124080], [124091], lambda x: u1func(x)*0.077045, usebhabha=True)
# (0.0038226691041641225, 0.10279699221662786)

############################################

data = (
  ( 535,  0.27, 0.15 ), \
  (  33,  0.04, 0.22 ), \
  ( 572,  0.05, 0.11 ), \
  ( 185, -0.19, 0.18 ), \
#  ( 243,  0.14, 0.19 ), \
  ( 456,  0.01, 0.10 ), \
  ( 460,  0.004, 0.10 ), \
  ( 374, -0.02, 0.09 ), \
  ( 509, -0.14, 0.15 ), \
  ( 457,  0.13, 0.15 ), \
  ( 544,  0.16, 0.16 ), \
  (  22,  0.02, 0.12 ), \
  ( 436, -0.12, 0.27 ), \
  ( 451,  0.58, 0.25 ), \
  (  22, -0.23, 0.19 ), \
  (1453,  0.01, 0.10 ), \
  ( 645, -0.05, 0.12 ), \
  (  30, -0.26, 0.19 ), \
  (  15, -0.14, 0.29 ), \
  ( 150, -0.06, 0.42 ), \
  ( 653,  0.31, 0.38 ), \
  ( 474,  0.71, 0.38 ), \
  ( 386, -0.08, 0.34 ), \
  ( 368,  0.02, 0.38 ), \
  ( 404,  1.22, 0.73 ), \
  ( 416,  0.33, 0.39 ), \
  ( 430,  0.55, 0.34 ), \
  (   2,  1.34, 0.66 ), \
  ( 521, -0.02, 0.38 ), \
  (  13, -0.14, 0.88 ))

p = biggles.FramedPlot()
p.add(biggles.Points(map(lambda (a,b,c): a/60., data), map(lambda (a,b,c): b, data), symboltype="filled circle"))
p.add(biggles.SymmetricErrorBarsY(map(lambda (a,b,c): a/60., data), map(lambda (a,b,c): b, data), map(lambda (a,b,c): c, data)))
p.add(biggles.LineY(0))
p.y1.label = "Energy calibration shift in MeV"
p.x1.label = "Hours between the two measurements"
p.aspect_ratio = 0.5
p.y1.range = -2.5, 2.5
p.show()
p.write_eps("/home/mccann/antithesis/plots/proceedings_miscal.eps")

p = biggles.FramedPlot()
p.add(biggles.Points(map(lambda (a,b,c): a/60., data), map(lambda (a,b,c): b/2., data), symboltype="filled circle"))
p.add(biggles.SymmetricErrorBarsY(map(lambda (a,b,c): a/60., data), map(lambda (a,b,c): b/2., data), map(lambda (a,b,c): c/2., data)))
p.add(biggles.LineY(0))
p.y1.label = "Energy calibration shift in MeV"
p.x1.label = "Hours between the two measurements"
p.aspect_ratio = 0.5
p.y1.range = -1., 1.
p.show()
p.write_eps("/home/mccann/antithesis/clns/miscal.eps")



p = biggles.FramedPlot()
p.add(biggles.Points(map(lambda (a,b,c): a, data), map(lambda (a,b,c): b**2, data), symboltype="filled circle"))
p.add(biggles.SymmetricErrorBarsY(map(lambda (a,b,c): a, data), map(lambda (a,b,c): b**2, data), map(lambda (a,b,c): b**2*2.*c/b, data)))
p.add(biggles.LineY(0))
p.y1.label = r"Energy miscalibration squared in MeV$^2$"
p.x1.label = "Seconds between pair of runs"
p.yrange = 0, 0.5
p.show()
p.write_eps("/home/mccann/tmp.eps")


wsum2 = 0.
sumw = 0.
for t, m, e in data:
  wsum2 += m**2/e**2
  sumw += 1./e**2
print sqrt(1.*wsum2/sumw)
print sqrt(1./sumw)


from math import *
from minuit import *
import hist, Numeric, biggles

def gauss(m, s):
  def f(x, m, s):
    return exp(-(x-m)**2/2./s**2)/sqrt(2*pi)/s
  nll = 0.
  for (a,b,c) in data:
    nll -= log(f(b/c, m, s))
  return nll

def plotfun(p, f, low, high, points=100):
  x = Numeric.arange(low, high+(high-low)/points, (high-low)/points)
  y = Numeric.arange(low, high+(high-low)/points, (high-low)/points)
  for i, xi in enumerate(x):
    y[i] = f(xi)
  p.add(biggles.Curve(x, y))

m = Minuit(gauss, start=[0,1], up=0.5)
m.migrad()
print m.values, m.errors

h = hist.h1(100, -5, 5)
h.fill(map(lambda (a,b,c): b/c, data))
p = h.plot()
plotfun(p, lambda x: 1.*len(data)/10.*exp(-(x-m.values[0])**2/2./m.values[1]**2)/sqrt(2*pi)/m.values[1], -5., 5.)
hist.addinfobox(p, [["mean", m.values[0], r"$\pm$ %.2f" % (m.errors[0])], ["width", m.values[1], r"$\pm$ %.2f" % (m.errors[1])]], 0.3, 0.1, numformat='%.2g')
p.x1.label = "Pull distribution of energy miscalibrations"
p.aspect_ratio = 0.5
p.x.ticks = range(-5, 6, 1)
p.x2.draw_ticklabels = 0
p.show()
p.write_eps("/home/mccann/antithesis/clns/miscalpull.eps")

m = Minuit(gauss, start=[0,1], up=0.5)
m.fix("m")
m.migrad()
m.errors[0] = 0.
print m.values, m.errors

h = hist.h1(100, -5, 5)
h.fill(map(lambda (a,b,c): b/c, data))
p = h.plot()
plotfun(p, lambda x: 1.*len(data)/10.*exp(-(x-m.values[0])**2/2./m.values[1]**2)/sqrt(2*pi)/m.values[1], -5., 5.)
hist.addinfobox(p, [["-log likelihood", m.fval], ["mean", 0, 0], ["width", "%.2f" % (m.values[1]), r"$\pm$ %.2f" % (m.errors[1])]], 0.45, 0.17, numformat='%.2g')
p.x1.label = "Pull distribution of energy miscalibrations"
p.show()
p.write_eps("/home/mccann/tmp.eps")



##############################################

DELTAE = [0.27,  0.04,  0.05, -0.19,  0.14,  0.01,  0.004, -0.02, -0.14,  0.13,  0.16,  0.02, -0.12,  0.58, -0.23,  0.01, -0.05, -0.26, -0.14, -0.06,  0.31,  0.71, -0.08,  0.02,  1.22,  0.33,  0.55,  1.34, -0.02, -0.14]
deltae = [0.15, 0.22, 0.11, 0.18, 0.19, 0.10, 0.10, 0.09, 0.15, 0.15, 0.16, 0.12, 0.27, 0.25, 0.19, 0.10, 0.12, 0.19, 0.29, 0.42, 0.38, 0.38, 0.34, 0.38, 0.73, 0.39, 0.34, 0.66, 0.38, 0.88]

nll = 0.
j = 0.12
for DE, de in zip(DELTAE, deltae):
  nll += -log(exp(-DE**2/2./(de**2+j**2))/sqrt(2.*pi)/sqrt(de**2+j**2))
print nll

###############################################

def mystery_wb(cor, runs1, runs2, f, dele):
  e1, sig1, err1 = get_runs(runs1, usebhabha=True)
  e2, sig2, err2 = get_runs(runs2, usebhabha=True)
  e1 *= 2000.
  e2 *= 2000.
  der = deriv((e1+e2)/2.+cor, f)
  return (sig1 - sig2)**2/(err1**2 + err2**2 + ((dele-(e1-e2))*der)**2)
  
def mystery_s(dele):
  tmp = 0.
  tmp += mystery_wb(jan16, [123164, 123165], [123176], lambda x: u1func(x)*0.077045, dele)
  tmp += mystery_wb(jan16, [123170], [123172], lambda x: u1func(x)*0.077045, dele)
  tmp += mystery_wb(jan30, [123596], [123604], lambda x: u1func(x)*0.077045, dele)
  tmp += mystery_wb(jan30, [123603], [123607], lambda x: u1func(x)*0.077045, dele)
  tmp += mystery_wb(feb06, [123828], [123832], lambda x: u1func(x)*0.077045, dele)
  tmp += mystery_wb(feb06, [123781], [123790], lambda x: u1func(x)*0.077045, dele)
  tmp += mystery_wb(feb13, [124080], [124091], lambda x: u1func(x)*0.077045, dele)
  tmp += mystery_wb(feb20, [124102], [124111], lambda x: u1func(x)*0.077045, dele)
  tmp += mystery_wb(feb27, [124279], [124294], lambda x: u1func(x)*0.077045, dele)
  tmp += mystery_wb(mar06, [124436, 124437], [124450], lambda x: u1func(x)*0.077045, dele)
  tmp += mystery_wb(mar13, [124625], [124639], lambda x: u1func(x)*0.077045, dele)
  tmp += mystery_wb(apr03, [125125], [125126], lambda x: u1func(x)*0.077045, dele)
  tmp += mystery_wb(apr08, [125254], [125262], lambda x: u1func(x)*0.077045, dele)
  tmp += mystery_wb(apr09, [125285], [125295], lambda x: u1func(x)*0.077045, dele)
  tmp += mystery_wb(may29, [126462, 126464], [126465, 126467], lambda x: u2func(x)*0.077045, dele)
  tmp += mystery_wb((jun11+jun12)/2., [126776, 126777, 126778, 126779], [126823, 126824, 126825], lambda x: u2func(x)*0.077045, dele)
  tmp += mystery_wb(jul10, [127588, 127589, 127592], [127610, 127611, 127612], lambda x: u2func(x)*0.077045, dele)
  tmp += mystery_wb(jul24, [127924, 127925], [127927], lambda x: u2func(x)*0.077045, dele)
  tmp += mystery_wb(aug07, [128310], [128312, 128313], lambda x: u2func(x)*0.077045, dele)
  tmp += mystery_wb(dec05, [122073], [122077], lambda x: u3func(x)*0.077045, dele)
  tmp += mystery_wb(dec12, [122245], [122256], lambda x: u3func(x)*0.077045, dele)
  tmp += mystery_wb(dec19, [122409], [122415], lambda x: u3func(x)*0.077045, dele)
  tmp += mystery_wb(dec26, [122535], [122542], lambda x: u3func(x)*0.077045, dele)
  tmp += mystery_wb(dec26, [122556], [122564], lambda x: u3func(x)*0.077045, dele)
  tmp += mystery_wb(dec26, [122537], [122548], lambda x: u3func(x)*0.077045, dele)
  tmp += mystery_wb(dec26, [122549], [122560], lambda x: u3func(x)*0.077045, dele)
  tmp += mystery_wb(jan02, [122766], [122776], lambda x: u3func(x)*0.077045, dele)
  tmp += mystery_wb(jan02, [122780], [122781], lambda x: u3func(x)*0.077045, dele)
  tmp += mystery_wb(jan09, [122993], [123004], lambda x: u3func(x)*0.077045, dele)
  tmp += mystery_wb(jan09, [122996], [122998], lambda x: u3func(x)*0.077045, dele)
  return tmp / 29.

print mystery_s(0.)
print mystery_s(0.09)
print mystery_s(0.15)

#############################################

some_ediff = -0.0727,   0.0000,  -0.0200,   0.0000,  -0.0200,   0.0000,  -0.3200,   0.2400,  -0.0400,  -0.1408,  -0.2000,   0.0000,   0.0000,   0.0000,  -0.1293,   0.1504,   0.0760,   0.0000,   0.0000,   0.0000,  -0.2000,   0.0000,   0.0000,   0.0000,   0.4000,   0.0000,  -0.4000,   0.0000,  -0.2000,   0.0000

def zerogood(x):
  if x==0.0000: return 1.
  return 0.

def myway(sigmae):
  return sum(map(lambda ((t,DE,de),ed): (DE**2/(de**2+sigmae**2)/14.)*zerogood(ed), zip(data, some_ediff)))

some_e1 = get_runs([123164, 123165])[0]*2000.
some_e2 = get_runs([123176])[0]*2000.

print map(lambda (t,DE,de): (DE - (some_e1 - some_e2))**2/(de**2+0.07**2), data)[0]
print mystery_wb(jan16, [123164, 123165], [123176], lambda x: u1func(x)*0.077045, 0.07)

