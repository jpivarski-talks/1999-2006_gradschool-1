execfile("/home/mccann/antithesis/utilities.py")
nobeam = getsb("cos")
ebeam = getsb("bge")
pbeam = getsb("bgp")
import gbwkf
import gbwkftau
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

def u1func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, w, lumisource=0):
  tmp = 0.
  upsilon = area * 0.9757 * mygbwkf(9460.30, fullgam, rmsbeam, yint, phi, w)
  tmp += upsilon
  tmp += area * 0.578 * btautau * mygbwkftau(9460.30, fullgam, rmsbeam, tauyint, tauphi, w)
  tmp += back * (1.-twophofrac) * 9000.**2 / w**2
  tmp += back * twophofrac * log(w**2/9000.**2)

  # see 21 Sep 2005 in notes (green #13)
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
u1runs["mar06"] = setup_runs(1, 124415, 124607)
u1runs["mar13"] = setup_runs(1, 124608, 124786)
u1runs["mar20"] = setup_runs(1, 124787, 124948)
u1runs["mar27"] = setup_runs(1, 124949, 125121)
u1runs["apr03"] = setup_runs(1, 125122, 125287)
u1runs["apr10"] = setup_runs(1, 125288, 125465)
# u1runs = {}
# u1runs["jan30"] = setup_runs(1, 123596, 123718)
# u1runs["feb06"] = setup_runs(1, 123781, 123893)
# u1runs["feb20"] = setup_runs(1, 124102, 124214)
# u1runs["feb27"] = setup_runs(1, 124279, 124394)
# u1runs["mar06"] = setup_runs(1, 124436, 124519)
# u1runs["mar13"] = setup_runs(1, 124625, 124736)
# u1runs["apr10"] = setup_runs(1, 125303, 125416)

ggdata = {}
bbindata = {}
bboutdata = {}
for s in u1runs:
  ggdata[s] = get_runs(u1runs[s], lumisource=0)
  bbindata[s] = get_runs(u1runs[s], lumisource=1)
  bboutdata[s] = get_runs(u1runs[s], lumisource=2)

p = biggles.FramedPlot()

x = ["mar06", "mar13", "mar20", "mar27", "apr03", "apr10"]
# x = ["jan30", "feb06", "feb20", "feb27", "mar06", "mar13", "apr10"] 

y = []; dy = []
for s in x:
  y.append(ggdata[s][1])
  dy.append(ggdata[s][2])
data1 = biggles.Points(range(len(x)), y, symboltype="filled circle")
data1.label = r"#had/#$\gamma\gamma$"
p.add(data1)
p.add(biggles.SymmetricErrorBarsY(range(len(x)), y, dy))

y = []; dy = []
for s in x:
  y.append(bbindata[s][1])
  dy.append(bbindata[s][2])
data2 = biggles.Points(range(len(x)), y, symboltype="triangle")
data2.label = r"#had/#inner $e^+e^-$"
p.add(data2)
p.add(biggles.SymmetricErrorBarsY(range(len(x)), y, dy))

y = []; dy = []
for s in x:
  y.append(bboutdata[s][1])
  dy.append(bboutdata[s][2])
data3 = biggles.Points(range(len(x)), y, symboltype="filled inverted triangle")
data3.label = r"#had/#outer $e^+e^-$"
p.add(data3)
p.add(biggles.SymmetricErrorBarsY(range(len(x)), y, dy))

p.add(biggles.PlotKey(0.1, 0.9, [data1, data2, data3]))

p.x1.ticklabels = x
p.y1.range = 24.5, 27
p.x1.label = r"Week beginning with..."
p.y1.label = r"Cross-section (nb) (just like yesterday's plot)"
p.show()
p.write_eps("stability3_labelall2.eps")






############################################################

def getdb_byrun(r):
  filename = basedir+"pickle/db_"+str(r)+".p"
  try:
    rec = pickle.load(open(filename))
    if runsummary[r].kind != "p": return []
    if len(dir(rec)) != runrecord_length:
      raise ValueError, "something's wrong with "+filename+", len dir is "+str(len(dir(rec)))
    return [rec]
  except IOError:
    return []

march_recs = reduce(lambda a, b: a+b, map(getdb_byrun, range(124607, 124764)))
april_recs = reduce(lambda a, b: a+b, map(getdb_byrun, range(125286, 125465)))

march_p1 = march_recs[0].hadroncool_p1
for rec in march_recs[1:]:
  march_p1 += rec.hadroncool_p1

april_p1 = april_recs[0].hadroncool_p1
for rec in april_recs[1:]:
  april_p1 += rec.hadroncool_p1

march_p1norm = march_p1 / march_p1.sum()
april_p1norm = april_p1 / april_p1.sum()

p = march_p1norm.plot()
p.add(april_p1norm.steps(linetype="dashed"))
p.show()
p.write_eps("stability3_p1overlay.eps")

p = (march_p1norm - april_p1norm).plot(False, points=True, errorbars=True)
p.y1.range = -0.005, 0.005
p.show()
p.write_eps("stability3_p1diff.eps")
