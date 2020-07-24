# this is just for the peakless April scan

import sys
sys.path.append("/home/mccann/bin/python/obsolete")

from minuit import *
execfile("utilities.py")
nobeam = getsb("cos")
ebeam = getsb("bge")
pbeam = getsb("bgp")
import gbwkf
import gbwkftau
runstart = pickle.load(open("old_dotps/runstart.p"))
runend = pickle.load(open("old_dotps/runend.p"))
import time

nbish2nb = 23.0481

def run_date(r):
  if r in runstart and r in runend:
    return (runstart[r] + runend[r])/2.
  elif r in runstart:
    return runstart[r]
  elif r in runend:
    return runend[r]
  else:
    raise Exception

# The 48-hour limit is built into setup_runs
def setup_runs(res, low, high):
  beginning = run_date(low)

  tmpruns = []
  for r in initialrunlist:
    if r not in mybadruns and low <= r <= high and runsummary[r].res == res:
      if runsummary[r].kind == 's': # or runsummary[r].kind == 'p':
        if run_date(r) < beginning + 48.*60.*60:
          tmpruns.append(r)
  return tmpruns

def setup_data(runs):
  tmpdata = []
  for r in runs:
    tmpdata.append(get_runs([r]))
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

def addfunc(p, f, low, high, points=100., linetype="solid", linewidth=1.):
  x = Numeric.arange(low, high+(high-low)/points, (high-low)/points)
  y = Numeric.arange(low, high+(high-low)/points, (high-low)/points)
  for i, xi in enumerate(x):
    y[i] = f(xi)
  tmp = biggles.Curve(x, y, linetype=linetype, linewidth=linewidth)
  p.add(tmp)
  return tmp

def u1func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, w):
  tmp = 0.
  tmp += area * 0.9757 * mygbwkf(9460.30, fullgam, rmsbeam, yint, phi, w)
  tmp += area * 0.578 * btautau * mygbwkftau(9460.30, fullgam, rmsbeam, tauyint, tauphi, w)
  tmp += back * (1.-twophofrac) * 9000.**2 / w**2
  tmp += back * twophofrac * log(w**2/9000.**2)
  return tmp

def u2func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, w):
  tmp = 0.
  tmp += area * 0.9582 * mygbwkf(10023.26, fullgam, rmsbeam, yint, phi, w)
  tmp += area * 0.578 * btautau * mygbwkftau(10023.26, fullgam, rmsbeam, tauyint, tauphi, w)
  tmp += back * (1.-twophofrac) * 9000.**2 / w**2
  tmp += back * twophofrac * log(w**2/9000.**2)
  tmp += u1area * mygbwkf(9460.30, 0., 0., 0., 0., w)
  return tmp

def u3func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area, w):
  tmp = 0.
  tmp += area * 0.9605 * mygbwkf(10355.2, fullgam, rmsbeam, yint, phi, w)
  tmp += area * 0.578 * btautau * mygbwkftau(10355.2, fullgam, rmsbeam, tauyint, tauphi, w)
  tmp += back * (1.-twophofrac) * 9000.**2 / w**2
  tmp += back * twophofrac * log(w**2/9000.**2)
  tmp += u1area * mygbwkf(9460.30, 0., 0., 0., 0., w)
  tmp += u2area * mygbwkf(10023.26, 0., 0., 0., 0., w)
  return tmp

def u1func_bkgndonly(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, w):
  tmp = 0.
  tmp += area * 0.578 * btautau * mygbwkftau(9460.30, fullgam, rmsbeam, tauyint, tauphi, w)
  tmp += back * (1.-twophofrac) * 9000.**2 / w**2
  tmp += back * twophofrac * log(w**2/9000.**2)
  return tmp

def u2func_bkgndonly(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, w):
  tmp = 0.
  tmp += area * 0.578 * btautau * mygbwkftau(10023.26, fullgam, rmsbeam, tauyint, tauphi, w)
  tmp += back * (1.-twophofrac) * 9000.**2 / w**2
  tmp += back * twophofrac * log(w**2/9000.**2)
  tmp += u1area * mygbwkf(9460.30, 0., 0., 0., 0., w)
  return tmp

def u3func_bkgndonly(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area, w):
  tmp = 0.
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
  return tmp

def doallthree(back, twophofrac, w):
  tmp = 0.
  tmp += back * (1.-twophofrac) * 9000.**2 / w**2
  tmp += back * twophofrac * log(w**2/9000.**2)
  if w > 9460.30-8.:
    tmp += u1func(nbish2nb * 13.706441397531357, 3.7860955817996218, 0., 0.053, 0.018, 0.0, 0.0267, 0.2, 0.0, twophofrac, w)
  if w > 10023.26-8.:
    tmp += u2func(nbish2nb * 5.5910940385520558, 4.172051740847075, 0., 0.043, 0.018, 0.0, 0.017, 0.2, 0.0, twophofrac, 0., w)
  if w > 10355.2-8.:
    tmp += u3func(nbish2nb * 3.5871224559944799, 4.4739422571161098, 0., 0.0263, 0.018, 0.0, 0.0239, 0.2, 0., twophofrac, 0., 0., w)
  return tmp

def get_runs(runs, usebhabha=False):
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

  cs = hadrons / g / average_energy**2 * nbish2nb

  cs_err = cs * sqrt((1.*hadrons_err / hadrons)**2 + 1./g)
#  print "  Hadronic cross-section is", cs, "+/-", cs_err

  if usebhabha:
    cs /= 0.077045
    cs_err /= 0.077045

  return average_energy, cs, cs_err

u1runs = {}
u1data = {}

u1runs["cont"] = []
for r in initialrunlist:
  if r not in mybadruns:
    if runsummary[r].res == 1 and runsummary[r].kind == 'c':
      u1runs["cont"].append(r)

u1runs["high"] = []
for r in initialrunlist:
  if r not in mybadruns:
    if runsummary[r].res == 1 and runsummary[r].kind == 'h':
      u1runs["high"].append(r)

u1data["cont"] = [get_runs(u1runs["cont"])]

u1data["high"] = [get_runs(u1runs["high"])]

u1runs["apr03"] = setup_runs(1, 125119, 125127)
u1runs["apr08"] = setup_runs(1, 125254, 125262)
u1runs["apr09"] = setup_runs(1, 125285, 125295)
u1runs["apr10"] = setup_runs(1, 125303, 125416)

u1data["apr03"] = setup_data(u1runs["apr03"])
u1data["apr08"] = setup_data(u1runs["apr08"])
u1data["apr09"] = setup_data(u1runs["apr09"])
u1data["apr10"] = setup_data(u1runs["apr10"])

def u1plot(area, rmsbeam, back, jan16, jan30, feb06, feb13, feb20, feb27, mar06, mar13, apr03, apr08, apr09, apr10, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac):
  p = biggles.FramedPlot()
  adddata(p, u1data["cont"], 0.)
  adddata(p, u1data["high"], 0.)
  adddata(p, u1data["apr03"], apr03)
  adddata(p, u1data["apr08"], apr08)
  adddata(p, u1data["apr09"], apr09)
  adddata(p, u1data["apr10"], apr10)
  addfunc(p, lambda w: u1func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, w), 9420., 9580.)
  p.x1.range = 9420., 9580.
  p.y1.range = 0., 1.5 * nbish2nb
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
  chi += chicontrib(u1data["apr03"], apr03, lambda w: u1func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, w))
  chi += chicontrib(u1data["apr08"], apr08, lambda w: u1func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, w))
  chi += chicontrib(u1data["apr09"], apr09, lambda w: u1func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, w))
  chi += chicontrib(u1data["apr10"], apr10, lambda w: u1func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, w))
#  u1plot(area, rmsbeam, back, jan16, jan30, feb06, feb13, feb20, feb27, mar06, mar13, apr03, apr08, apr09, apr10, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac).show()
  return chi

################################################################

u1fitter = Minuit(u1fit)
u1fitter.values = [319.2, 3.79, 9.35245, 0.25, 0.63, 0.076, 0.066, 0.23, 0.19, 0.20, 0.57, 0.92, 0.80, 0.46, 0.62, 0.053, 0.01864, 0., 0.0267, 0.20, 0., 0.0792]
u1fitter.fix(range(u1fitter.npar))
u1fitter.release(["rmsbeam", "back"])
u1fitter.release(["apr03", "apr08", "apr09", "apr10"])

u1fitter.values = [13.7 * nbish2nb, 3.79, 0.404 * nbish2nb, 0.25, 0.63, 0.076, 0.066, 0.23, 0.19, 0.20, 0.57, 0.92, 0.80, 0.46, 0.62, 0.053, 0.01864, 0., 0.0267, 0.20, 0., 0.0792]
u1fitter.values[u1fitter.findpar("btautau")] = 0.0249
u1fitter.values[u1fitter.findpar("tauyint")] = (2./3.)/137./u1fitter.values[u1fitter.findpar("btautau")]
u1fitter.migrad()
if not u1fitter.valid: u1fitter.migrad()
print "1s Istvan's B_mm: ", u1fitter.values[0]

class FitRecord: pass
fitrecord = {}
fitrecord[1] = FitRecord()

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

pickle.dump(fitrecord, open("/home/mccann/antithesis/fit_results/fits8_apr10scanonly.p", 'w'))

p = u1plot(*u1fitter.values)
p.show()
p.write_eps("/home/mccann/antithesis/fit_results/fits8_apr10scanonly.eps")
print u1fitter.values[0], u1fitter.errors[0]
print u1fitter.values[1], u1fitter.errors[1]
