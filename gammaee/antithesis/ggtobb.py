import sys
sys.path.append("/home/mccann/bin/python/obsolete")

from minuit import *
execfile("/home/mccann/antithesis/utilities.py")
import gbwkf
import gbwkftau
runstart = pickle.load(open("old_dotps/runstart.p"))
runend = pickle.load(open("old_dotps/runend.p"))
import time

nbish2nb = 23.0481
bhabha_interference = 1.   # this is a multiplier: 0. to turn off

class FitRecord: pass
ggfits = pickle.load(open("/home/mccann/antithesis/fit_results/octoberfits_fixen_0_1.0.p"))

# I learned this from Matt and the beam energy program logs
runsummary[123828].energy = 4.72992
runsummary[123832].energy = 4.72990

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
      if runsummary[r].kind == 's' or runsummary[r].kind == 'p':
        if run_date(r) < beginning + 48.*60.*60:
          tmpruns.append(r)
  return tmpruns

def setup_data(runs, correction=True):
  themap = {}
  for r in runs:
    thisen = round(runsummary[r].energy*2000.)
    if thisen not in themap:
      themap[thisen] = []
    themap[thisen].append(r)

  tmpdata = []
  for thisen, littlelist in themap.items():
    tmpdata.append(get_runs(littlelist, correction))
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
  return (x, y, yerr)

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

def whichamiin(r):
  if runsummary[r].res == 1:
    for s in ["jan16", "jan30", "feb06", "feb13", "feb20", "feb27", "mar06", "mar13", "apr03", "apr08", "apr09", "apr10"]:
      if r in u1runs[s]:
        return 1, s

  elif runsummary[r].res == 2:
    for s in ["may29", "jun11", "jun12", "jul10", "jul24", "aug07"]:
      if r in u2runs[s]:
        return 2, s

  elif runsummary[r].res == 3:
    for s in ["nov28", "dec05", "dec12", "dec19", "dec26", "jan02", "jan09"]:
      if r in u3runs[s]:
        return 3, s

  return runsummary[r].res, None

def get_runs(runs, correction=True):
  bb = 0.
  g = 0.
  wsum = 0.
  wesum = 0.
  for r in runs:
    therun = getdb(r)
    ngg = therun.gamgam
    if r in mycarefulscan: ngg = therun.gamgam_vstime.sum(0.,0.99)
    wsum += float(ngg)
    wesum += float(ngg) * runsummary[r].energy

    if runsummary[r].res == 1:
      myarea, myrmsbeam, myback, myjan16, myjan30, myfeb06, myfeb13, myfeb20, myfeb27, mymar06, mymar13, myapr03, myapr08, myapr09, myapr10, myfullgam, myyint, myphi, mybtautau, mytauyint, mytauphi, mytwophofrac, myrjan, myrfeb, myrapr1, myrapr2 = ggfits[1].values
    elif runsummary[r].res == 2:
      myarea, myrmsbeam, myback, mymay29, myjun11, myjun12, myjul10, myjul24, myaug07, myfullgam, myyint, myphi, mybtautau, mytauyint, mytauphi, mytwophofrac, myu1area = ggfits[2].values
    elif runsummary[r].res == 3:
      myarea, myrmsbeam, myback, mynov28, mydec05, mydec12, mydec19, mydec26, myjan02, myjan09, myfullgam, myyint, myphi, mybtautau, mytauyint, mytauphi, mytwophofrac, myu1area, myu2area, myrnov28, myrdec05, myrdec12, myrdec19, myrdec26, myrjan02, myrjan09 = ggfits[3].values

    whichres, whichweek = whichamiin(r)

    thisrmsbeam = myrmsbeam
    if whichres == 1:
      if whichweek != None:
        if whichweek in ["jan16", "jan30", "feb06", "feb13", "feb20"]: thisrmsbeam = myrjan
        if whichweek in ["feb27", "mar06", "mar13"]: thisrmsbeam = myrfeb
        if whichweek in ["apr03", "apr08", "apr09"]: thisrmsbeam = myrapr1
        if whichweek in ["apr10"]: thisrmsbeam = myrapr2
    if whichres == 3:
      if whichweek != None:
        thisrmsbeam = eval("myr"+whichweek)

    thisshift = 0.
    if whichweek != None:
      thisshift = 0. - eval("my"+whichweek)

    if r in mycarefulscan:
      g += therun.gamgam_vstime.sum(0.,0.99)

      bb += therun.bhabha_cosp.sum(0.6, 0.8) * therun.bhabha_vstime.sum(0.,0.99) / therun.bhabha
      if runsummary[r].kind != 'c':
        # eecs = e+e- cross-section = hadronic area / (1 - 3 Bmm) * Bmm * outer range
        if runsummary[r].res == 1 and correction:
          eecs = myarea * mygbwkf(9460.30+thisshift, myfullgam, thisrmsbeam, 0.588*bhabha_interference, 0., 2000.*runsummary[r].energy) / 0.9253 * 0.0249 * 0.298667/2.66667
          bb -= eecs * float(therun.gamgam) * runsummary[r].energy**2 / nbish2nb

        if runsummary[r].res == 2 and correction:
          eecs = myarea * mygbwkf(10023.26+thisshift, myfullgam, thisrmsbeam, 0.864*bhabha_interference, 0., 2000.*runsummary[r].energy) / 0.9391 * 0.0203 * 0.298667/2.6667
          bb -= eecs * float(therun.gamgam) * runsummary[r].energy**2 / nbish2nb

        if runsummary[r].res == 3 and correction:
          eecs = myarea * mygbwkf(10355.2+thisshift, myfullgam, thisrmsbeam, 0.686*bhabha_interference, 0., 2000.*runsummary[r].energy) / 0.9283 * 0.0239 * 0.298667/2.6667
          bb -= eecs * float(therun.gamgam) * runsummary[r].energy**2 / nbish2nb

    else:
      g += therun.gamgam

      bb += therun.bhabha_cosp.sum(0.6, 0.8)
      if runsummary[r].kind != 'c':
        # e+e- cross-section = hadronic area / (1 - 3 Bmm) * Bmm * outer range
        if runsummary[r].res == 1 and correction:
          eecs = myarea * mygbwkf(9460.30+thisshift, myfullgam, thisrmsbeam, 0.588*bhabha_interference, 0., 2000.*runsummary[r].energy) / 0.9253 * 0.0249 * 0.298667/2.66667
          bb -= eecs * float(therun.gamgam) * runsummary[r].energy**2 / nbish2nb

        if runsummary[r].res == 2 and correction:
          eecs = myarea * mygbwkf(10023.26+thisshift, myfullgam, thisrmsbeam, 0.864*bhabha_interference, 0., 2000.*runsummary[r].energy) / 0.9391 * 0.0203 * 0.298667/2.6667
          bb -= eecs * float(therun.gamgam) * runsummary[r].energy**2 / nbish2nb

        if runsummary[r].res == 3 and correction:
          eecs = myarea * mygbwkf(10355.2+thisshift, myfullgam, thisrmsbeam, 0.686*bhabha_interference, 0., 2000.*runsummary[r].energy) / 0.9283 * 0.0239 * 0.298667/2.6667
          bb -= eecs * float(therun.gamgam) * runsummary[r].energy**2 / nbish2nb

  average_energy = wesum / wsum

  return average_energy, bb/g, bb/g*sqrt(1./bb + 1./g)

def adddata2(data, shift, x, y, yerr):
  for (e, h, herr) in data:
    x.append(e*2000.+shift)
    y.append(h)
    yerr.append(herr)
  return None

class MoreThanHist:
  def __init__(self, bins, low, high):
    self.h = hist.h1(bins, low, high)
    self.data = []
  def fill(self, l):
    for x in l:
      self.data.append(x)
      self.h.fill(x)
  def rootn(self):
    self.h.rootn()
  def plot(self):
    return self.h.plot()
  def sum(self):
    return self.h.sum()
  def overflow(self):
    return self.h.overflow
  def underflow(self):
    return self.h.underflow
  def steps(self, linewidth=3.):
    return self.h.steps(linewidth=linewidth)

def dofitgauss(h):
  def gauss(m, s, x): return exp(-(x-m)**2/2./s**2)/sqrt(2.*pi)/s
  def fitgauss(m,s):
    c = 0.
    for x in h.data:
      c += -log(gauss(m, s, x))
    return c
  m = Minuit(fitgauss, start=[0., 1.], up=0.5)
  m.migrad()
  m.minos([0,1])
  err0 = (m.minos_errors[0][1] - m.minos_errors[0][0])/2.
  err1 = (m.minos_errors[1][1] - m.minos_errors[1][0])/2.
  return m.values[0], err0, m.values[1], err1, lambda x: 0.1*4.*len(h.data)*gauss(m.values[0], m.values[1], x)

############################################################################

u1runs = {}
u2runs = {}
u3runs = {}
u1data = {}
u2data = {}
u3data = {}

u1runs["cont"] = []
u2runs["cont"] = []
u3runs["cont"] = []
u1runs["high"] = []
u2runs["high"] = []
u3runs["high"] = []

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

for r in initialrunlist:
  if r not in mybadruns:
    if runsummary[r].res == 1 and runsummary[r].kind == 'c':
      u1runs["cont"].append(r)
    if runsummary[r].res == 2 and runsummary[r].kind == 'c':
      u2runs["cont"].append(r)
    if runsummary[r].res == 3 and runsummary[r].kind == 'c':
      u3runs["cont"].append(r)

for r in initialrunlist:
  if r not in mybadruns:
    if runsummary[r].res == 1 and runsummary[r].kind == 'h':
      u1runs["high"].append(r)
    if runsummary[r].res == 2 and runsummary[r].kind == 'h':
      u2runs["high"].append(r)
    if runsummary[r].res == 3 and runsummary[r].kind == 'h':
      u3runs["high"].append(r)

u1data["cont"] = [get_runs(u1runs["cont"], correction=False)]
u2data["cont"] = [get_runs(u2runs["cont"], correction=False)]
u3data["cont"] = [get_runs(u3runs["cont"], correction=False)]

u1data["high"] = [get_runs(u1runs["high"], correction=False)]
u2data["high"] = [get_runs(u2runs["high"], correction=False)]
u3data["high"] = [get_runs(u3runs["high"], correction=False)]

u1data["jan16"] = setup_data(u1runs["jan16"], correction=False)
u1data["jan30"] = setup_data(u1runs["jan30"], correction=False)
u1data["feb06"] = setup_data(u1runs["feb06"], correction=False)
u1data["feb13"] = setup_data(u1runs["feb13"], correction=False)
u1data["feb20"] = setup_data(u1runs["feb20"], correction=False)
u1data["feb27"] = setup_data(u1runs["feb27"], correction=False)
u1data["mar06"] = setup_data(u1runs["mar06"], correction=False)
u1data["mar13"] = setup_data(u1runs["mar13"], correction=False)
u1data["apr03"] = setup_data(u1runs["apr03"], correction=False)
u1data["apr08"] = setup_data(u1runs["apr08"], correction=False)
u1data["apr09"] = setup_data(u1runs["apr09"], correction=False)
u1data["apr10"] = setup_data(u1runs["apr10"], correction=False)

u2data["may29"] = setup_data(u2runs["may29"], correction=False)
u2data["jun11"] = setup_data(u2runs["jun11"], correction=False)
u2data["jun12"] = setup_data(u2runs["jun12"], correction=False)
u2data["jul10"] = setup_data(u2runs["jul10"], correction=False)
u2data["jul24"] = setup_data(u2runs["jul24"], correction=False)
u2data["aug07"] = setup_data(u2runs["aug07"], correction=False)

u3data["nov28"] = setup_data(u3runs["nov28"], correction=False)
u3data["dec05"] = setup_data(u3runs["dec05"], correction=False)
u3data["dec12"] = setup_data(u3runs["dec12"], correction=False)
u3data["dec19"] = setup_data(u3runs["dec19"], correction=False)
u3data["dec26"] = setup_data(u3runs["dec26"], correction=False)
u3data["jan02"] = setup_data(u3runs["jan02"], correction=False)
u3data["jan09"] = setup_data(u3runs["jan09"], correction=False)

###################################################################

myarea, myrmsbeam, myback, myjan16, myjan30, myfeb06, myfeb13, myfeb20, myfeb27, mymar06, mymar13, myapr03, myapr08, myapr09, myapr10, myfullgam, myyint, myphi, mybtautau, mytauyint, mytauphi, mytwophofrac, myrjan, myrfeb, myrapr1, myrapr2 = ggfits[1].values
pall = biggles.Table(1,2)
pall[0,0] = biggles.FramedArray(2,1)
p = pall[0,0]
x = []; y = []; dy = []
tmpx, tmpy, tmpdy = adddata(p[0,0], u1data["cont"], 0.)
x += tmpx; y += tmpy; dy += tmpdy
tmpx, tmpy, tmpdy = adddata(p[0,0], u1data["high"], 0.)
x += tmpx; y += tmpy; dy += tmpdy
tmpx, tmpy, tmpdy = adddata(p[0,0], u1data["jan16"], myjan16)
x += tmpx; y += tmpy; dy += tmpdy
tmpx, tmpy, tmpdy = adddata(p[0,0], u1data["jan30"], myjan30)
x += tmpx; y += tmpy; dy += tmpdy
tmpx, tmpy, tmpdy = adddata(p[0,0], u1data["feb06"], myfeb06)
x += tmpx; y += tmpy; dy += tmpdy
tmpx, tmpy, tmpdy = adddata(p[0,0], u1data["feb13"], myfeb13)
x += tmpx; y += tmpy; dy += tmpdy
tmpx, tmpy, tmpdy = adddata(p[0,0], u1data["feb20"], myfeb20)
x += tmpx; y += tmpy; dy += tmpdy
tmpx, tmpy, tmpdy = adddata(p[0,0], u1data["feb27"], myfeb27)
x += tmpx; y += tmpy; dy += tmpdy
tmpx, tmpy, tmpdy = adddata(p[0,0], u1data["mar06"], mymar06)
x += tmpx; y += tmpy; dy += tmpdy
tmpx, tmpy, tmpdy = adddata(p[0,0], u1data["mar13"], mymar13)
x += tmpx; y += tmpy; dy += tmpdy
tmpx, tmpy, tmpdy = adddata(p[0,0], u1data["apr03"], myapr03)
x += tmpx; y += tmpy; dy += tmpdy
tmpx, tmpy, tmpdy = adddata(p[0,0], u1data["apr08"], myapr08)
x += tmpx; y += tmpy; dy += tmpdy
tmpx, tmpy, tmpdy = adddata(p[0,0], u1data["apr09"], myapr09)
x += tmpx; y += tmpy; dy += tmpdy
tmpx, tmpy, tmpdy = adddata(p[0,0], u1data["apr10"], myapr10)
x += tmpx; y += tmpy; dy += tmpdy
centerline = jt.wmean(zip(y, dy))[0]
p[0,0].add(biggles.LineY(centerline))
pulls = map(lambda (ay, ady): (ay-centerline)/ady, zip(y, dy))
p[1,0].add(biggles.Points(x, pulls, symboltype="filled circle", symbolsize=1))
p[1,0].add(biggles.LineY(0))
p.xrange = 9440, 9490
p[1,0].yrange = -5, 5
mehist = MoreThanHist(25, -5., 5.)
mehist.fill(pulls)
mehist.rootn()
pall[0,1] = mehist.plot()
mean, meanerr, width, widtherr, f = dofitgauss(mehist)
x = Numeric.arange(-5., 5., 0.01)
y = Numeric.arange(-5., 5., 0.01)
for i, xi in enumerate(x): y[i] = f(xi)
pall[0,1].add(biggles.Curve(x,y, linecolor="red"))
hist.addinfobox(pall[0,1], [["entries", r"%d" % (len(dy))], ["mean", r"%4.2f $\pm$ %4.2f" % (mean, abs(meanerr))], ["width", r"%4.2f $\pm$ %4.2f" % (abs(width), abs(widtherr))], ["underflow", mehist.underflow()], ["overflow", mehist.overflow()]], width=0.7, colwidth=0.07)
p.xlabel = "Center of mass energy (MeV)"
p.ylabel = r"Raw $e^+e^-$ count / $\gamma\gamma$ count"
pall[0,1].x1.label = "Histogram of deviations"
pall.aspect_ratio = 1.2
pall.show()
pall.write_eps("plots/ggtobbuncor_1.eps")

myarea, myrmsbeam, myback, mymay29, myjun11, myjun12, myjul10, myjul24, myaug07, myfullgam, myyint, myphi, mybtautau, mytauyint, mytauphi, mytwophofrac, myu1area = ggfits[2].values
pall = biggles.Table(1,2)
pall[0,0] = biggles.FramedArray(2,1)
p = pall[0,0]
x = []; y = []; dy = []
tmpx, tmpy, tmpdy = adddata(p[0,0], u2data["cont"], 0.)
x += tmpx; y += tmpy; dy += tmpdy
tmpx, tmpy, tmpdy = adddata(p[0,0], u2data["high"], 0.)
x += tmpx; y += tmpy; dy += tmpdy
tmpx, tmpy, tmpdy = adddata(p[0,0], u2data["may29"], mymay29)
x += tmpx; y += tmpy; dy += tmpdy
tmpx, tmpy, tmpdy = adddata(p[0,0], u2data["jun11"], myjun11)
x += tmpx; y += tmpy; dy += tmpdy
tmpx, tmpy, tmpdy = adddata(p[0,0], u2data["jun12"], myjun12)
x += tmpx; y += tmpy; dy += tmpdy
tmpx, tmpy, tmpdy = adddata(p[0,0], u2data["jul10"], myjul10)
x += tmpx; y += tmpy; dy += tmpdy
tmpx, tmpy, tmpdy = adddata(p[0,0], u2data["jul24"], myjul24)
x += tmpx; y += tmpy; dy += tmpdy
tmpx, tmpy, tmpdy = adddata(p[0,0], u2data["aug07"], myaug07)
x += tmpx; y += tmpy; dy += tmpdy
centerline = jt.wmean(zip(y, dy))[0]
p[0,0].add(biggles.LineY(centerline))
pulls = map(lambda (ay, ady): (ay-centerline)/ady, zip(y, dy))
p[1,0].add(biggles.Points(x, pulls, symboltype="filled circle", symbolsize=1))
p[1,0].add(biggles.LineY(0))
p.xrange = 10007, 10047
p[1,0].yrange = -5, 5
mehist = MoreThanHist(25, -5., 5.)
mehist.fill(pulls)
mehist.rootn()
pall[0,1] = mehist.plot()
mean, meanerr, width, widtherr, f = dofitgauss(mehist)
x = Numeric.arange(-5., 5., 0.01)
y = Numeric.arange(-5., 5., 0.01)
for i, xi in enumerate(x): y[i] = f(xi)
pall[0,1].add(biggles.Curve(x,y, linecolor="red"))
hist.addinfobox(pall[0,1], [["entries", r"%d" % (len(dy))], ["mean", r"%4.2f $\pm$ %4.2f" % (mean, abs(meanerr))], ["width", r"%4.2f $\pm$ %4.2f" % (abs(width), abs(widtherr))], ["underflow", mehist.underflow()], ["overflow", mehist.overflow()]], width=0.7, colwidth=0.07)
p.xlabel = "Center of mass energy (MeV)"
p.ylabel = r"Raw $e^+e^-$ count / $\gamma\gamma$ count"
pall[0,1].x1.label = "Histogram of deviations"
pall.aspect_ratio = 1.2
pall.show()
pall.write_eps("plots/ggtobbuncor_2.eps")

myarea, myrmsbeam, myback, mynov28, mydec05, mydec12, mydec19, mydec26, myjan02, myjan09, myfullgam, myyint, myphi, mybtautau, mytauyint, mytauphi, mytwophofrac, myu1area, myu2area, myrnov28, myrdec05, myrdec12, myrdec19, myrdec26, myrjan02, myrjan09 = ggfits[3].values
pall = biggles.Table(1,2)
pall[0,0] = biggles.FramedArray(2,1)
p = pall[0,0]
x = []; y = []; dy = []
tmpx, tmpy, tmpdy = adddata(p[0,0], u3data["cont"], 0.)
x += tmpx; y += tmpy; dy += tmpdy
tmpx, tmpy, tmpdy = adddata(p[0,0], u3data["high"], 0.)
x += tmpx; y += tmpy; dy += tmpdy
tmpx, tmpy, tmpdy = adddata(p[0,0], u3data["nov28"], mynov28)
x += tmpx; y += tmpy; dy += tmpdy
tmpx, tmpy, tmpdy = adddata(p[0,0], u3data["dec05"], mydec05)
x += tmpx; y += tmpy; dy += tmpdy
tmpx, tmpy, tmpdy = adddata(p[0,0], u3data["dec12"], mydec12)
x += tmpx; y += tmpy; dy += tmpdy
tmpx, tmpy, tmpdy = adddata(p[0,0], u3data["dec19"], mydec19)
x += tmpx; y += tmpy; dy += tmpdy
tmpx, tmpy, tmpdy = adddata(p[0,0], u3data["dec26"], mydec26)
x += tmpx; y += tmpy; dy += tmpdy
tmpx, tmpy, tmpdy = adddata(p[0,0], u3data["jan02"], myjan02)
x += tmpx; y += tmpy; dy += tmpdy
tmpx, tmpy, tmpdy = adddata(p[0,0], u3data["jan09"], myjan09)
x += tmpx; y += tmpy; dy += tmpdy
centerline = jt.wmean(zip(y, dy))[0]
p[0,0].add(biggles.LineY(centerline))
pulls = map(lambda (ay, ady): (ay-centerline)/ady, zip(y, dy))
p[1,0].add(biggles.Points(x, pulls, symboltype="filled circle", symbolsize=1))
p[1,0].add(biggles.LineY(0))
p.xrange = 10340, 10380
p[1,0].yrange = -5, 5
mehist = MoreThanHist(25, -5., 5.)
mehist.fill(pulls)
mehist.rootn()
pall[0,1] = mehist.plot()
mean, meanerr, width, widtherr, f = dofitgauss(mehist)
x = Numeric.arange(-5., 5., 0.01)
y = Numeric.arange(-5., 5., 0.01)
for i, xi in enumerate(x): y[i] = f(xi)
pall[0,1].add(biggles.Curve(x,y, linecolor="red"))
hist.addinfobox(pall[0,1], [["entries", r"%d" % (len(dy))], ["mean", r"%4.2f $\pm$ %4.2f" % (mean, abs(meanerr))], ["width", r"%4.2f $\pm$ %4.2f" % (abs(width), abs(widtherr))], ["underflow", mehist.underflow()], ["overflow", mehist.overflow()]], width=0.7, colwidth=0.07)
p.xlabel = "Center of mass energy (MeV)"
p.ylabel = r"Raw $e^+e^-$ count / $\gamma\gamma$ count"
pall[0,1].x1.label = "Histogram of deviations"
pall.aspect_ratio = 1.2
pall.show()
pall.write_eps("plots/ggtobbuncor_3.eps")

##########################################################

nobeam = getsb("cos")
ebeam = getsb("bge")
pbeam = getsb("bgp")
bsbha = pickle.load(open("/home/mccann/synthesis/run/bsbha.p"))
def get_runs(runs, lumisource=0):
  g = 0.
  h = 0.
  e = 0.
  p = 0.
  c = 0.
  bb = 0.
  wsum = 0.
  wesum = 0.
  for r in runs:
    therun = getdb(r)
    ngg = therun.gamgam
    if r in mycarefulscan: ngg = therun.gamgam_vstime.sum(0.,0.99)
    wsum += float(ngg)
    wesum += float(ngg) * runsummary[r].energy

    if runsummary[r].res == 1:
      myarea, myrmsbeam, myback, myjan16, myjan30, myfeb06, myfeb13, myfeb20, myfeb27, mymar06, mymar13, myapr03, myapr08, myapr09, myapr10, myfullgam, myyint, myphi, mybtautau, mytauyint, mytauphi, mytwophofrac, myrjan, myrfeb, myrapr1, myrapr2 = ggfits[1].values
    elif runsummary[r].res == 2:
      myarea, myrmsbeam, myback, mymay29, myjun11, myjun12, myjul10, myjul24, myaug07, myfullgam, myyint, myphi, mybtautau, mytauyint, mytauphi, mytwophofrac, myu1area = ggfits[2].values
    elif runsummary[r].res == 3:
      myarea, myrmsbeam, myback, mynov28, mydec05, mydec12, mydec19, mydec26, myjan02, myjan09, myfullgam, myyint, myphi, mybtautau, mytauyint, mytauphi, mytwophofrac, myu1area, myu2area, myrnov28, myrdec05, myrdec12, myrdec19, myrdec26, myrjan02, myrjan09 = ggfits[3].values

    whichres, whichweek = whichamiin(r)

    thisrmsbeam = myrmsbeam
    if whichres == 1:
      if whichweek != None:
        if whichweek in ["jan16", "jan30", "feb06", "feb13", "feb20"]: thisrmsbeam = myrjan
        if whichweek in ["feb27", "mar06", "mar13"]: thisrmsbeam = myrfeb
        if whichweek in ["apr08", "apr09", "apr10"]: thisrmsbeam = myrapr2
    if whichres == 3:
      if whichweek != None:
        thisrmsbeam = eval("myr"+whichweek)

    thisshift = 0.
    if whichweek != None:
      thisshift = 0. - eval("my"+whichweek)

    if r in mycarefulscan:
      h += therun.hadroncool_vstime.sum(0.,0.99)
      e += therun.beamgase_vstime.sum(0.,0.99)
      p += therun.beamgasp_vstime.sum(0.,0.99)
      c += therun.cosmic_vstime.sum(0.,0.99)

      g += therun.gamgam_vstime.sum(0.,0.99)

      bb += 1.*bsbha[r] * therun.bhabha_vstime.sum(0.,0.99) / therun.bhabha

      if runsummary[r].kind != 'c':
        # eecs = e+e- cross-section = hadronic area / (1 - 3 Bmm) * Bmm * whole range
        if runsummary[r].res == 1:
          eecs = myarea * mygbwkf(9460.30+thisshift, myfullgam, thisrmsbeam, 0.597*bhabha_interference, 0., 2000.*runsummary[r].energy) / 0.9253 * 0.0249 * 1.73933/2.66667
          bb -= eecs * float(therun.gamgam) * runsummary[r].energy**2 / nbish2nb

        if runsummary[r].res == 2:
          eecs = myarea * mygbwkf(10023.26+thisshift, myfullgam, thisrmsbeam, 0.873*bhabha_interference, 0., 2000.*runsummary[r].energy) / 0.9391 * 0.0203 * 1.73933/2.6667
          bb -= eecs * float(therun.gamgam) * runsummary[r].energy**2 / nbish2nb

        if runsummary[r].res == 3:
          eecs = myarea * mygbwkf(10355.2+thisshift, myfullgam, thisrmsbeam, 0.691*bhabha_interference, 0., 2000.*runsummary[r].energy) / 0.9283 * 0.0239 * 1.73933/2.6667
          bb -= eecs * float(therun.gamgam) * runsummary[r].energy**2 / nbish2nb

    else:
      h += therun.hadroncool
      e += therun.beamgase
      p += therun.beamgasp
      c += therun.cosmic

      g += therun.gamgam

      bb += 1.*bsbha[r]

      if runsummary[r].kind != 'c':
        # e+e- cross-section = hadronic area / (1 - 3 Bmm) * Bmm * whole range
        if runsummary[r].res == 1:
          eecs = myarea * mygbwkf(9460.30+thisshift, myfullgam, thisrmsbeam, 0.597*bhabha_interference, 0., 2000.*runsummary[r].energy) / 0.9253 * 0.0249 * 1.73933/2.66667
          bb -= eecs * float(therun.gamgam) * runsummary[r].energy**2 / nbish2nb

        if runsummary[r].res == 2:
          eecs = myarea * mygbwkf(10023.26+thisshift, myfullgam, thisrmsbeam, 0.873*bhabha_interference, 0., 2000.*runsummary[r].energy) / 0.9391 * 0.0203 * 1.73933/2.6667
          bb -= eecs * float(therun.gamgam) * runsummary[r].energy**2 / nbish2nb

        if runsummary[r].res == 3:
          eecs = myarea * mygbwkf(10355.2+thisshift, myfullgam, thisrmsbeam, 0.691*bhabha_interference, 0., 2000.*runsummary[r].energy) / 0.9283 * 0.0239 * 1.73933/2.6667
          bb -= eecs * float(therun.gamgam) * runsummary[r].energy**2 / nbish2nb

  average_energy = wesum / wsum

  ebkgnd = 1. * (ebeam.hadroncool - 1.*nobeam.hadroncool*ebeam.cosmic/nobeam.cosmic) * e / ebeam.beamgase
  pbkgnd = 1. * (pbeam.hadroncool - 1.*nobeam.hadroncool*pbeam.cosmic/nobeam.cosmic) * p / pbeam.beamgasp
  cbkgnd = 1. * nobeam.hadroncool * c / nobeam.cosmic

  hadrons = h - ebkgnd/2. - pbkgnd/2. - cbkgnd
  hadrons_err = sqrt(h + c * (1.*nobeam.hadroncool/nobeam.cosmic)**2 + ebkgnd/2. + pbkgnd/2.)

  if whichres == 1:
    cs = hadrons / bb / average_energy**2 * 199.5   # these differences are due to different efficiencies, as predicted by the MC
  elif whichres == 2:
    cs = hadrons / bb / average_energy**2 * 197.4   # and verified by my lumi counts
  elif whichres == 3:
    cs = hadrons / bb / average_energy**2 * 196.0   # (I totally believe this.)

  cs_err = cs * sqrt((1.*hadrons_err / hadrons)**2 + 1./bb)

  average_energy = wesum / wsum

  if whichres == 1:
    rat = (bb/199.5) / (g/nbish2nb)
  if whichres == 2:
    rat = (bb/197.4) / (g/nbish2nb)
  if whichres == 3:
    rat = (bb/196.0) / (g/nbish2nb)

  return average_energy, rat, rat*sqrt(1./bb + 1./g)

u1data["cont"] = [get_runs(u1runs["cont"])]
u2data["cont"] = [get_runs(u2runs["cont"])]
u3data["cont"] = [get_runs(u3runs["cont"])]

u1data["high"] = [get_runs(u1runs["high"])]
u2data["high"] = [get_runs(u2runs["high"])]
u3data["high"] = [get_runs(u3runs["high"])]

u1data["low"] = [get_runs(filter(lambda r: runsummary[r].energy < (9460.3-1.7*3.79)/2000.,
                                 u1runs["jan16"] + \
                                 u1runs["jan30"] + \
                                 u1runs["feb06"] + \
                                 u1runs["feb13"] + \
                                 u1runs["feb20"] + \
                                 u1runs["feb27"] + \
                                 u1runs["mar06"] + \
                                 u1runs["mar13"] + \
                                 u1runs["apr03"] + \
                                 u1runs["apr08"] + \
                                 u1runs["apr09"] + \
                                 u1runs["apr10"]))]
u1data["mid1"] = [get_runs(filter(lambda r: (9460.3-1.7*3.79)/2000. < runsummary[r].energy < (9460.3)/2000.,
                                 u1runs["jan16"] + \
                                 u1runs["jan30"] + \
                                 u1runs["feb06"] + \
                                 u1runs["feb13"] + \
                                 u1runs["feb20"] + \
                                 u1runs["feb27"] + \
                                 u1runs["mar06"] + \
                                 u1runs["mar13"] + \
                                 u1runs["apr03"] + \
                                 u1runs["apr08"] + \
                                 u1runs["apr09"] + \
                                 u1runs["apr10"]))]
u1data["mid2"] = [get_runs(filter(lambda r: (9460.3)/2000. < runsummary[r].energy < (9460.3+1.7*3.79)/2000.,
                                 u1runs["jan16"] + \
                                 u1runs["jan30"] + \
                                 u1runs["feb06"] + \
                                 u1runs["feb13"] + \
                                 u1runs["feb20"] + \
                                 u1runs["feb27"] + \
                                 u1runs["mar06"] + \
                                 u1runs["mar13"] + \
                                 u1runs["apr03"] + \
                                 u1runs["apr08"] + \
                                 u1runs["apr09"] + \
                                 u1runs["apr10"]))]
u1data["hi"] = [get_runs(filter(lambda r: (9460.3+1.7*3.79)/2000. < runsummary[r].energy,
                                 u1runs["jan16"] + \
                                 u1runs["jan30"] + \
                                 u1runs["feb06"] + \
                                 u1runs["feb13"] + \
                                 u1runs["feb20"] + \
                                 u1runs["feb27"] + \
                                 u1runs["mar06"] + \
                                 u1runs["mar13"] + \
                                 u1runs["apr03"] + \
                                 u1runs["apr08"] + \
                                 u1runs["apr09"] + \
                                 u1runs["apr10"]))]
u1data["any"] = [get_runs(filter(lambda r: True,
                                 u1runs["jan16"] + \
                                 u1runs["jan30"] + \
                                 u1runs["feb06"] + \
                                 u1runs["feb13"] + \
                                 u1runs["feb20"] + \
                                 u1runs["feb27"] + \
                                 u1runs["mar06"] + \
                                 u1runs["mar13"] + \
                                 u1runs["apr03"] + \
                                 u1runs["apr08"] + \
                                 u1runs["apr09"] + \
                                 u1runs["apr10"]))]

u2data["low"] = [get_runs(filter(lambda r: runsummary[r].energy < (10023.26-1.7*4.18)/2000.,
                                 u2runs["may29"] + \
                                 u2runs["jun11"] + \
                                 u2runs["jun12"] + \
                                 u2runs["jul10"] + \
                                 u2runs["jul24"] + \
                                 u2runs["aug07"]))]
u2data["mid1"] = [get_runs(filter(lambda r: (10023.26-1.7*4.18)/2000. < runsummary[r].energy < (10023.26)/2000.,
                                 u2runs["may29"] + \
                                 u2runs["jun11"] + \
                                 u2runs["jun12"] + \
                                 u2runs["jul10"] + \
                                 u2runs["jul24"] + \
                                 u2runs["aug07"]))]
u2data["mid2"] = [get_runs(filter(lambda r: (10023.26)/2000. < runsummary[r].energy < (10023.26+1.7*4.18)/2000.,
                                 u2runs["may29"] + \
                                 u2runs["jun11"] + \
                                 u2runs["jun12"] + \
                                 u2runs["jul10"] + \
                                 u2runs["jul24"] + \
                                 u2runs["aug07"]))]
u2data["hi"] = [get_runs(filter(lambda r: (10023.26+1.7*4.18)/2000. < runsummary[r].energy,
                                 u2runs["may29"] + \
                                 u2runs["jun11"] + \
                                 u2runs["jun12"] + \
                                 u2runs["jul10"] + \
                                 u2runs["jul24"] + \
                                 u2runs["aug07"]))]
u2data["any"] = [get_runs(filter(lambda r: True < runsummary[r].energy,
                                 u2runs["may29"] + \
                                 u2runs["jun11"] + \
                                 u2runs["jun12"] + \
                                 u2runs["jul10"] + \
                                 u2runs["jul24"] + \
                                 u2runs["aug07"]))]

u3data["low"] = [get_runs(filter(lambda r: runsummary[r].energy < (10355.2-1.7*4.48)/2000.,
                                 u3runs["nov28"] + \
                                 u3runs["dec05"] + \
                                 u3runs["dec12"] + \
                                 u3runs["dec19"] + \
                                 u3runs["dec26"] + \
                                 u3runs["jan02"] + \
                                 u3runs["jan09"]))]
u3data["mid1"] = [get_runs(filter(lambda r: (10355.2-1.7*4.48)/2000. < runsummary[r].energy < (10355.2)/2000.,
                                 u3runs["nov28"] + \
                                 u3runs["dec05"] + \
                                 u3runs["dec12"] + \
                                 u3runs["dec19"] + \
                                 u3runs["dec26"] + \
                                 u3runs["jan02"] + \
                                 u3runs["jan09"]))]
u3data["mid2"] = [get_runs(filter(lambda r: (10355.2)/2000. < runsummary[r].energy < (10355.2+1.7*4.48)/2000.,
                                 u3runs["nov28"] + \
                                 u3runs["dec05"] + \
                                 u3runs["dec12"] + \
                                 u3runs["dec19"] + \
                                 u3runs["dec26"] + \
                                 u3runs["jan02"] + \
                                 u3runs["jan09"]))]
u3data["hi"] = [get_runs(filter(lambda r: (10355.2+1.7*4.48)/2000. < runsummary[r].energy,
                                 u3runs["nov28"] + \
                                 u3runs["dec05"] + \
                                 u3runs["dec12"] + \
                                 u3runs["dec19"] + \
                                 u3runs["dec26"] + \
                                 u3runs["jan02"] + \
                                 u3runs["jan09"]))]
u3data["any"] = [get_runs(filter(lambda r: True < runsummary[r].energy,
                                 u3runs["nov28"] + \
                                 u3runs["dec05"] + \
                                 u3runs["dec12"] + \
                                 u3runs["dec19"] + \
                                 u3runs["dec26"] + \
                                 u3runs["jan02"] + \
                                 u3runs["jan09"]))]

u1x = map(lambda (en,rat,err): en*2000., u1data["cont"] + u1data["low"] + u1data["mid1"] + u1data["mid2"] + u1data["hi"] + u1data["high"])
u1y = map(lambda (en,rat,err): rat, u1data["cont"] + u1data["low"] + u1data["mid1"] + u1data["mid2"] + u1data["hi"] + u1data["high"])
u1dy = map(lambda (en,rat,err): err, u1data["cont"] + u1data["low"] + u1data["mid1"] + u1data["mid2"] + u1data["hi"] + u1data["high"])

u2x = map(lambda (en,rat,err): en*2000., u2data["cont"] + u2data["low"] + u2data["mid1"] + u2data["mid2"] + u2data["hi"] + u2data["high"])
u2y = map(lambda (en,rat,err): rat, u2data["cont"] + u2data["low"] + u2data["mid1"] + u2data["mid2"] + u2data["hi"] + u2data["high"])
u2dy = map(lambda (en,rat,err): err, u2data["cont"] + u2data["low"] + u2data["mid1"] + u2data["mid2"] + u2data["hi"] + u2data["high"])

u3x = map(lambda (en,rat,err): en*2000., u3data["cont"] + u3data["low"] + u3data["mid1"] + u3data["mid2"] + u3data["hi"] + u3data["high"])
u3y = map(lambda (en,rat,err): rat, u3data["cont"] + u3data["low"] + u3data["mid1"] + u3data["mid2"] + u3data["hi"] + u3data["high"])
u3dy = map(lambda (en,rat,err): err, u3data["cont"] + u3data["low"] + u3data["mid1"] + u3data["mid2"] + u3data["hi"] + u3data["high"])

p = biggles.FramedPlot()
p.add(biggles.Points(u1x+u2x+u3x, u1y+u2y+u3y, symboltype="filled circle"))
p.add(biggles.SymmetricErrorBarsY(u1x+u2x+u3x, u1y+u2y+u3y, u1dy+u2dy+u3dy))
p.add(biggles.LineY(1.))
p.x1.range = 9300, 10500
p.x1.label = r"$E_{CM}$"
p.y1.label = r"BB lumi / $\gamma\gamma$ lumi"
p.show()
p.write_eps("ggtobb_by5.eps")

# anyx = map(lambda (en,rat,err): en*2000., u1data["cont"] + u1data["any"] + u1data["high"] + u2data["cont"] + u2data["any"] + u2data["high"] + u3data["cont"] + u3data["any"] + u3data["high"])
# anyy = map(lambda (en,rat,err): rat, u1data["cont"] + u1data["any"] + u1data["high"] + u2data["cont"] + u2data["any"] + u2data["high"] + u3data["cont"] + u3data["any"] + u3data["high"])
# anydy = map(lambda (en,rat,err): err, u1data["cont"] + u1data["any"] + u1data["high"] + u2data["cont"] + u2data["any"] + u2data["high"] + u3data["cont"] + u3data["any"] + u3data["high"])

# p = biggles.FramedPlot()
# p.add(biggles.Points(anyx, anyy, symboltype="filled circle"))
# p.add(biggles.SymmetricErrorBarsY(anyx, anyy, anydy))
# p.show()





# Now with inner Bhabhas
##########################################################

nobeam = getsb("cos")
ebeam = getsb("bge")
pbeam = getsb("bgp")
bsbha = pickle.load(open("/home/mccann/synthesis/run/bsbha.p"))
def get_runs(runs, lumisource=0):
  g = 0.
  h = 0.
  e = 0.
  p = 0.
  c = 0.
  bb = 0.
  wsum = 0.
  wesum = 0.
  for r in runs:
    therun = getdb(r)
    ngg = therun.gamgam
    if r in mycarefulscan: ngg = therun.gamgam_vstime.sum(0.,0.99)
    wsum += float(ngg)
    wesum += float(ngg) * runsummary[r].energy

    if runsummary[r].res == 1:
      myarea, myrmsbeam, myback, myjan16, myjan30, myfeb06, myfeb13, myfeb20, myfeb27, mymar06, mymar13, myapr03, myapr08, myapr09, myapr10, myfullgam, myyint, myphi, mybtautau, mytauyint, mytauphi, mytwophofrac, myrjan, myrfeb, myrapr1, myrapr2 = ggfits[1].values
    elif runsummary[r].res == 2:
      myarea, myrmsbeam, myback, mymay29, myjun11, myjun12, myjul10, myjul24, myaug07, myfullgam, myyint, myphi, mybtautau, mytauyint, mytauphi, mytwophofrac, myu1area = ggfits[2].values
    elif runsummary[r].res == 3:
      myarea, myrmsbeam, myback, mynov28, mydec05, mydec12, mydec19, mydec26, myjan02, myjan09, myfullgam, myyint, myphi, mybtautau, mytauyint, mytauphi, mytwophofrac, myu1area, myu2area, myrnov28, myrdec05, myrdec12, myrdec19, myrdec26, myrjan02, myrjan09 = ggfits[3].values

    whichres, whichweek = whichamiin(r)

    thisrmsbeam = myrmsbeam
    if whichres == 1:
      if whichweek != None:
        if whichweek in ["jan16", "jan30", "feb06", "feb13", "feb20"]: thisrmsbeam = myrjan
        if whichweek in ["feb27", "mar06", "mar13"]: thisrmsbeam = myrfeb
        if whichweek in ["apr08", "apr09", "apr10"]: thisrmsbeam = myrapr2
    if whichres == 3:
      if whichweek != None:
        thisrmsbeam = eval("myr"+whichweek)

    thisshift = 0.
    if whichweek != None:
      thisshift = 0. - eval("my"+whichweek)

    if r in mycarefulscan:
      h += therun.hadroncool_vstime.sum(0.,0.99)
      e += therun.beamgase_vstime.sum(0.,0.99)
      p += therun.beamgasp_vstime.sum(0.,0.99)
      c += therun.cosmic_vstime.sum(0.,0.99)

      g += therun.gamgam_vstime.sum(0.,0.99)

      bb += therun.bhabha_cosp.sum(0., 0.6) * therun.bhabha_vstime.sum(0.,0.99) / therun.bhabha

      if runsummary[r].kind != 'c':
        # eecs = e+e- cross-section = hadronic area / (1 - 3 Bmm) * Bmm * inner range
        if runsummary[r].res == 1:
          eecs = myarea * mygbwkf(9460.30+thisshift, myfullgam, thisrmsbeam, 0.417*bhabha_interference, 0., 2000.*runsummary[r].energy) / 0.9253 * 0.0249 * 0.672/2.66667
          bb -= eecs * float(therun.gamgam) * runsummary[r].energy**2 / nbish2nb

        if runsummary[r].res == 2:
          eecs = myarea * mygbwkf(10023.26+thisshift, myfullgam, thisrmsbeam, 0.613*bhabha_interference, 0., 2000.*runsummary[r].energy) / 0.9391 * 0.0203 * 0.672/2.6667
          bb -= eecs * float(therun.gamgam) * runsummary[r].energy**2 / nbish2nb

        if runsummary[r].res == 3:
          eecs = myarea * mygbwkf(10355.2+thisshift, myfullgam, thisrmsbeam, 0.486*bhabha_interference, 0., 2000.*runsummary[r].energy) / 0.9283 * 0.0239 * 0.672/2.6667
          bb -= eecs * float(therun.gamgam) * runsummary[r].energy**2 / nbish2nb

    else:
      h += therun.hadroncool
      e += therun.beamgase
      p += therun.beamgasp
      c += therun.cosmic

      g += therun.gamgam

      bb += therun.bhabha_cosp.sum(0., 0.6)

      if runsummary[r].kind != 'c':
        # e+e- cross-section = hadronic area / (1 - 3 Bmm) * Bmm * inner range
        if runsummary[r].res == 1:
          eecs = myarea * mygbwkf(9460.30+thisshift, myfullgam, thisrmsbeam, 0.417*bhabha_interference, 0., 2000.*runsummary[r].energy) / 0.9253 * 0.0249 * 0.672/2.66667
          bb -= eecs * float(therun.gamgam) * runsummary[r].energy**2 / nbish2nb

        if runsummary[r].res == 2:
          eecs = myarea * mygbwkf(10023.26+thisshift, myfullgam, thisrmsbeam, 0.613*bhabha_interference, 0., 2000.*runsummary[r].energy) / 0.9391 * 0.0203 * 0.672/2.6667
          bb -= eecs * float(therun.gamgam) * runsummary[r].energy**2 / nbish2nb

        if runsummary[r].res == 3:
          eecs = myarea * mygbwkf(10355.2+thisshift, myfullgam, thisrmsbeam, 0.486*bhabha_interference, 0., 2000.*runsummary[r].energy) / 0.9283 * 0.0239 * 0.672/2.6667
          bb -= eecs * float(therun.gamgam) * runsummary[r].energy**2 / nbish2nb

  average_energy = wesum / wsum

  ebkgnd = 1. * (ebeam.hadroncool - 1.*nobeam.hadroncool*ebeam.cosmic/nobeam.cosmic) * e / ebeam.beamgase
  pbkgnd = 1. * (pbeam.hadroncool - 1.*nobeam.hadroncool*pbeam.cosmic/nobeam.cosmic) * p / pbeam.beamgasp
  cbkgnd = 1. * nobeam.hadroncool * c / nobeam.cosmic

  hadrons = h - ebkgnd/2. - pbkgnd/2. - cbkgnd
  hadrons_err = sqrt(h + c * (1.*nobeam.hadroncool/nobeam.cosmic)**2 + ebkgnd/2. + pbkgnd/2.)

  cs = hadrons / bb / average_energy**2 * nbish2nb / 0.23684
  cs_err = cs * sqrt((1.*hadrons_err / hadrons)**2 + 1./bb) / 0.23684

  average_energy = wesum / wsum

  rat = (bb*0.23684) / (g)

  return average_energy, rat, rat*sqrt(1./bb + 1./g)

u1data["cont"] = [get_runs(u1runs["cont"])]
u2data["cont"] = [get_runs(u2runs["cont"])]
u3data["cont"] = [get_runs(u3runs["cont"])]

u1data["high"] = [get_runs(u1runs["high"])]
u2data["high"] = [get_runs(u2runs["high"])]
u3data["high"] = [get_runs(u3runs["high"])]

u1data["low"] = [get_runs(filter(lambda r: runsummary[r].energy < (9460.3-1.7*3.79)/2000.,
                                 u1runs["jan16"] + \
                                 u1runs["jan30"] + \
                                 u1runs["feb06"] + \
                                 u1runs["feb13"] + \
                                 u1runs["feb20"] + \
                                 u1runs["feb27"] + \
                                 u1runs["mar06"] + \
                                 u1runs["mar13"] + \
                                 u1runs["apr03"] + \
                                 u1runs["apr08"] + \
                                 u1runs["apr09"] + \
                                 u1runs["apr10"]))]
u1data["mid1"] = [get_runs(filter(lambda r: (9460.3-1.7*3.79)/2000. < runsummary[r].energy < (9460.3)/2000.,
                                 u1runs["jan16"] + \
                                 u1runs["jan30"] + \
                                 u1runs["feb06"] + \
                                 u1runs["feb13"] + \
                                 u1runs["feb20"] + \
                                 u1runs["feb27"] + \
                                 u1runs["mar06"] + \
                                 u1runs["mar13"] + \
                                 u1runs["apr03"] + \
                                 u1runs["apr08"] + \
                                 u1runs["apr09"] + \
                                 u1runs["apr10"]))]
u1data["mid2"] = [get_runs(filter(lambda r: (9460.3)/2000. < runsummary[r].energy < (9460.3+1.7*3.79)/2000.,
                                 u1runs["jan16"] + \
                                 u1runs["jan30"] + \
                                 u1runs["feb06"] + \
                                 u1runs["feb13"] + \
                                 u1runs["feb20"] + \
                                 u1runs["feb27"] + \
                                 u1runs["mar06"] + \
                                 u1runs["mar13"] + \
                                 u1runs["apr03"] + \
                                 u1runs["apr08"] + \
                                 u1runs["apr09"] + \
                                 u1runs["apr10"]))]
u1data["hi"] = [get_runs(filter(lambda r: (9460.3+1.7*3.79)/2000. < runsummary[r].energy,
                                 u1runs["jan16"] + \
                                 u1runs["jan30"] + \
                                 u1runs["feb06"] + \
                                 u1runs["feb13"] + \
                                 u1runs["feb20"] + \
                                 u1runs["feb27"] + \
                                 u1runs["mar06"] + \
                                 u1runs["mar13"] + \
                                 u1runs["apr03"] + \
                                 u1runs["apr08"] + \
                                 u1runs["apr09"] + \
                                 u1runs["apr10"]))]
u1data["any"] = [get_runs(filter(lambda r: True,
                                 u1runs["jan16"] + \
                                 u1runs["jan30"] + \
                                 u1runs["feb06"] + \
                                 u1runs["feb13"] + \
                                 u1runs["feb20"] + \
                                 u1runs["feb27"] + \
                                 u1runs["mar06"] + \
                                 u1runs["mar13"] + \
                                 u1runs["apr03"] + \
                                 u1runs["apr08"] + \
                                 u1runs["apr09"] + \
                                 u1runs["apr10"]))]

u2data["low"] = [get_runs(filter(lambda r: runsummary[r].energy < (10023.26-1.7*4.18)/2000.,
                                 u2runs["may29"] + \
                                 u2runs["jun11"] + \
                                 u2runs["jun12"] + \
                                 u2runs["jul10"] + \
                                 u2runs["jul24"] + \
                                 u2runs["aug07"]))]
u2data["mid1"] = [get_runs(filter(lambda r: (10023.26-1.7*4.18)/2000. < runsummary[r].energy < (10023.26)/2000.,
                                 u2runs["may29"] + \
                                 u2runs["jun11"] + \
                                 u2runs["jun12"] + \
                                 u2runs["jul10"] + \
                                 u2runs["jul24"] + \
                                 u2runs["aug07"]))]
u2data["mid2"] = [get_runs(filter(lambda r: (10023.26)/2000. < runsummary[r].energy < (10023.26+1.7*4.18)/2000.,
                                 u2runs["may29"] + \
                                 u2runs["jun11"] + \
                                 u2runs["jun12"] + \
                                 u2runs["jul10"] + \
                                 u2runs["jul24"] + \
                                 u2runs["aug07"]))]
u2data["hi"] = [get_runs(filter(lambda r: (10023.26+1.7*4.18)/2000. < runsummary[r].energy,
                                 u2runs["may29"] + \
                                 u2runs["jun11"] + \
                                 u2runs["jun12"] + \
                                 u2runs["jul10"] + \
                                 u2runs["jul24"] + \
                                 u2runs["aug07"]))]
u2data["any"] = [get_runs(filter(lambda r: True < runsummary[r].energy,
                                 u2runs["may29"] + \
                                 u2runs["jun11"] + \
                                 u2runs["jun12"] + \
                                 u2runs["jul10"] + \
                                 u2runs["jul24"] + \
                                 u2runs["aug07"]))]

u3data["low"] = [get_runs(filter(lambda r: runsummary[r].energy < (10355.2-1.7*4.48)/2000.,
                                 u3runs["nov28"] + \
                                 u3runs["dec05"] + \
                                 u3runs["dec12"] + \
                                 u3runs["dec19"] + \
                                 u3runs["dec26"] + \
                                 u3runs["jan02"] + \
                                 u3runs["jan09"]))]
u3data["mid1"] = [get_runs(filter(lambda r: (10355.2-1.7*4.48)/2000. < runsummary[r].energy < (10355.2)/2000.,
                                 u3runs["nov28"] + \
                                 u3runs["dec05"] + \
                                 u3runs["dec12"] + \
                                 u3runs["dec19"] + \
                                 u3runs["dec26"] + \
                                 u3runs["jan02"] + \
                                 u3runs["jan09"]))]
u3data["mid2"] = [get_runs(filter(lambda r: (10355.2)/2000. < runsummary[r].energy < (10355.2+1.7*4.48)/2000.,
                                 u3runs["nov28"] + \
                                 u3runs["dec05"] + \
                                 u3runs["dec12"] + \
                                 u3runs["dec19"] + \
                                 u3runs["dec26"] + \
                                 u3runs["jan02"] + \
                                 u3runs["jan09"]))]
u3data["hi"] = [get_runs(filter(lambda r: (10355.2+1.7*4.48)/2000. < runsummary[r].energy,
                                 u3runs["nov28"] + \
                                 u3runs["dec05"] + \
                                 u3runs["dec12"] + \
                                 u3runs["dec19"] + \
                                 u3runs["dec26"] + \
                                 u3runs["jan02"] + \
                                 u3runs["jan09"]))]
u3data["any"] = [get_runs(filter(lambda r: True < runsummary[r].energy,
                                 u3runs["nov28"] + \
                                 u3runs["dec05"] + \
                                 u3runs["dec12"] + \
                                 u3runs["dec19"] + \
                                 u3runs["dec26"] + \
                                 u3runs["jan02"] + \
                                 u3runs["jan09"]))]

u1x = map(lambda (en,rat,err): en*2000., u1data["cont"] + u1data["low"] + u1data["mid1"] + u1data["mid2"] + u1data["hi"] + u1data["high"])
u1y = map(lambda (en,rat,err): rat, u1data["cont"] + u1data["low"] + u1data["mid1"] + u1data["mid2"] + u1data["hi"] + u1data["high"])
u1dy = map(lambda (en,rat,err): err, u1data["cont"] + u1data["low"] + u1data["mid1"] + u1data["mid2"] + u1data["hi"] + u1data["high"])

u2x = map(lambda (en,rat,err): en*2000., u2data["cont"] + u2data["low"] + u2data["mid1"] + u2data["mid2"] + u2data["hi"] + u2data["high"])
u2y = map(lambda (en,rat,err): rat, u2data["cont"] + u2data["low"] + u2data["mid1"] + u2data["mid2"] + u2data["hi"] + u2data["high"])
u2dy = map(lambda (en,rat,err): err, u2data["cont"] + u2data["low"] + u2data["mid1"] + u2data["mid2"] + u2data["hi"] + u2data["high"])

u3x = map(lambda (en,rat,err): en*2000., u3data["cont"] + u3data["low"] + u3data["mid1"] + u3data["mid2"] + u3data["hi"] + u3data["high"])
u3y = map(lambda (en,rat,err): rat, u3data["cont"] + u3data["low"] + u3data["mid1"] + u3data["mid2"] + u3data["hi"] + u3data["high"])
u3dy = map(lambda (en,rat,err): err, u3data["cont"] + u3data["low"] + u3data["mid1"] + u3data["mid2"] + u3data["hi"] + u3data["high"])

p = biggles.FramedPlot()
p.add(biggles.Points(u1x+u2x+u3x, u1y+u2y+u3y, symboltype="filled circle"))
p.add(biggles.SymmetricErrorBarsY(u1x+u2x+u3x, u1y+u2y+u3y, u1dy+u2dy+u3dy))
p.add(biggles.LineY(1.))
p.x1.range = 9300, 10500
p.x1.label = r"$E_{CM}$"
p.y1.label = r"inner BB lumi / $\gamma\gamma$ lumi"
p.show()
p.write_eps("ggtobb_by5_innerbb.eps")





# Now with outer Bhabhas
##########################################################

nobeam = getsb("cos")
ebeam = getsb("bge")
pbeam = getsb("bgp")
bsbha = pickle.load(open("/home/mccann/synthesis/run/bsbha.p"))
def get_runs(runs, lumisource=0):
  g = 0.
  h = 0.
  e = 0.
  p = 0.
  c = 0.
  bb = 0.
  wsum = 0.
  wesum = 0.
  for r in runs:
    therun = getdb(r)
    ngg = therun.gamgam
    if r in mycarefulscan: ngg = therun.gamgam_vstime.sum(0.,0.99)
    wsum += float(ngg)
    wesum += float(ngg) * runsummary[r].energy

    if runsummary[r].res == 1:
      myarea, myrmsbeam, myback, myjan16, myjan30, myfeb06, myfeb13, myfeb20, myfeb27, mymar06, mymar13, myapr03, myapr08, myapr09, myapr10, myfullgam, myyint, myphi, mybtautau, mytauyint, mytauphi, mytwophofrac, myrjan, myrfeb, myrapr1, myrapr2 = ggfits[1].values
    elif runsummary[r].res == 2:
      myarea, myrmsbeam, myback, mymay29, myjun11, myjun12, myjul10, myjul24, myaug07, myfullgam, myyint, myphi, mybtautau, mytauyint, mytauphi, mytwophofrac, myu1area = ggfits[2].values
    elif runsummary[r].res == 3:
      myarea, myrmsbeam, myback, mynov28, mydec05, mydec12, mydec19, mydec26, myjan02, myjan09, myfullgam, myyint, myphi, mybtautau, mytauyint, mytauphi, mytwophofrac, myu1area, myu2area, myrnov28, myrdec05, myrdec12, myrdec19, myrdec26, myrjan02, myrjan09 = ggfits[3].values

    whichres, whichweek = whichamiin(r)

    thisrmsbeam = myrmsbeam
    if whichres == 1:
      if whichweek != None:
        if whichweek in ["jan16", "jan30", "feb06", "feb13", "feb20"]: thisrmsbeam = myrjan
        if whichweek in ["feb27", "mar06", "mar13"]: thisrmsbeam = myrfeb
        if whichweek in ["apr08", "apr09", "apr10"]: thisrmsbeam = myrapr2
    if whichres == 3:
      if whichweek != None:
        thisrmsbeam = eval("myr"+whichweek)

    thisshift = 0.
    if whichweek != None:
      thisshift = 0. - eval("my"+whichweek)

    if r in mycarefulscan:
      h += therun.hadroncool_vstime.sum(0.,0.99)
      e += therun.beamgase_vstime.sum(0.,0.99)
      p += therun.beamgasp_vstime.sum(0.,0.99)
      c += therun.cosmic_vstime.sum(0.,0.99)

      g += therun.gamgam_vstime.sum(0.,0.99)

      bb += therun.bhabha_cosp.sum(0.6, 0.8) * therun.bhabha_vstime.sum(0.,0.99) / therun.bhabha

      if runsummary[r].kind != 'c':
        # eecs = e+e- cross-section = hadronic area / (1 - 3 Bmm) * Bmm * outer range
        if runsummary[r].res == 1:
          eecs = myarea * mygbwkf(9460.30+thisshift, myfullgam, thisrmsbeam, 0.588*bhabha_interference, 0., 2000.*runsummary[r].energy) / 0.9253 * 0.0249 * 0.298667/2.66667
          bb -= eecs * float(therun.gamgam) * runsummary[r].energy**2 / nbish2nb

        if runsummary[r].res == 2:
          eecs = myarea * mygbwkf(10023.26+thisshift, myfullgam, thisrmsbeam, 0.864*bhabha_interference, 0., 2000.*runsummary[r].energy) / 0.9391 * 0.0203 * 0.298667/2.6667
          bb -= eecs * float(therun.gamgam) * runsummary[r].energy**2 / nbish2nb

        if runsummary[r].res == 3:
          eecs = myarea * mygbwkf(10355.2+thisshift, myfullgam, thisrmsbeam, 0.686*bhabha_interference, 0., 2000.*runsummary[r].energy) / 0.9283 * 0.0239 * 0.298667/2.6667
          bb -= eecs * float(therun.gamgam) * runsummary[r].energy**2 / nbish2nb

    else:
      h += therun.hadroncool
      e += therun.beamgase
      p += therun.beamgasp
      c += therun.cosmic

      g += therun.gamgam

      bb += therun.bhabha_cosp.sum(0.6, 0.8)

      if runsummary[r].kind != 'c':
        # e+e- cross-section = hadronic area / (1 - 3 Bmm) * Bmm * outer range
        if runsummary[r].res == 1:
          eecs = myarea * mygbwkf(9460.30+thisshift, myfullgam, thisrmsbeam, 0.588*bhabha_interference, 0., 2000.*runsummary[r].energy) / 0.9253 * 0.0249 * 0.298667/2.66667
          bb -= eecs * float(therun.gamgam) * runsummary[r].energy**2 / nbish2nb

        if runsummary[r].res == 2:
          eecs = myarea * mygbwkf(10023.26+thisshift, myfullgam, thisrmsbeam, 0.864*bhabha_interference, 0., 2000.*runsummary[r].energy) / 0.9391 * 0.0203 * 0.298667/2.6667
          bb -= eecs * float(therun.gamgam) * runsummary[r].energy**2 / nbish2nb

        if runsummary[r].res == 3:
          eecs = myarea * mygbwkf(10355.2+thisshift, myfullgam, thisrmsbeam, 0.686*bhabha_interference, 0., 2000.*runsummary[r].energy) / 0.9283 * 0.0239 * 0.298667/2.6667
          bb -= eecs * float(therun.gamgam) * runsummary[r].energy**2 / nbish2nb

  average_energy = wesum / wsum

  ebkgnd = 1. * (ebeam.hadroncool - 1.*nobeam.hadroncool*ebeam.cosmic/nobeam.cosmic) * e / ebeam.beamgase
  pbkgnd = 1. * (pbeam.hadroncool - 1.*nobeam.hadroncool*pbeam.cosmic/nobeam.cosmic) * p / pbeam.beamgasp
  cbkgnd = 1. * nobeam.hadroncool * c / nobeam.cosmic

  hadrons = h - ebkgnd/2. - pbkgnd/2. - cbkgnd
  hadrons_err = sqrt(h + c * (1.*nobeam.hadroncool/nobeam.cosmic)**2 + ebkgnd/2. + pbkgnd/2.)

  cs = hadrons / bb / average_energy**2 * nbish2nb / 0.118999
  cs_err = cs * sqrt((1.*hadrons_err / hadrons)**2 + 1./bb) / 0.118999

  average_energy = wesum / wsum

  rat = (bb*0.118999) / (g)

  return average_energy, rat, rat*sqrt(1./bb + 1./g)

u1data["cont"] = [get_runs(u1runs["cont"])]
u2data["cont"] = [get_runs(u2runs["cont"])]
u3data["cont"] = [get_runs(u3runs["cont"])]

u1data["high"] = [get_runs(u1runs["high"])]
u2data["high"] = [get_runs(u2runs["high"])]
u3data["high"] = [get_runs(u3runs["high"])]

u1data["low"] = [get_runs(filter(lambda r: runsummary[r].energy < (9460.3-1.7*3.79)/2000.,
                                 u1runs["jan16"] + \
                                 u1runs["jan30"] + \
                                 u1runs["feb06"] + \
                                 u1runs["feb13"] + \
                                 u1runs["feb20"] + \
                                 u1runs["feb27"] + \
                                 u1runs["mar06"] + \
                                 u1runs["mar13"] + \
                                 u1runs["apr03"] + \
                                 u1runs["apr08"] + \
                                 u1runs["apr09"] + \
                                 u1runs["apr10"]))]
u1data["mid1"] = [get_runs(filter(lambda r: (9460.3-1.7*3.79)/2000. < runsummary[r].energy < (9460.3)/2000.,
                                 u1runs["jan16"] + \
                                 u1runs["jan30"] + \
                                 u1runs["feb06"] + \
                                 u1runs["feb13"] + \
                                 u1runs["feb20"] + \
                                 u1runs["feb27"] + \
                                 u1runs["mar06"] + \
                                 u1runs["mar13"] + \
                                 u1runs["apr03"] + \
                                 u1runs["apr08"] + \
                                 u1runs["apr09"] + \
                                 u1runs["apr10"]))]
u1data["mid2"] = [get_runs(filter(lambda r: (9460.3)/2000. < runsummary[r].energy < (9460.3+1.7*3.79)/2000.,
                                 u1runs["jan16"] + \
                                 u1runs["jan30"] + \
                                 u1runs["feb06"] + \
                                 u1runs["feb13"] + \
                                 u1runs["feb20"] + \
                                 u1runs["feb27"] + \
                                 u1runs["mar06"] + \
                                 u1runs["mar13"] + \
                                 u1runs["apr03"] + \
                                 u1runs["apr08"] + \
                                 u1runs["apr09"] + \
                                 u1runs["apr10"]))]
u1data["hi"] = [get_runs(filter(lambda r: (9460.3+1.7*3.79)/2000. < runsummary[r].energy,
                                 u1runs["jan16"] + \
                                 u1runs["jan30"] + \
                                 u1runs["feb06"] + \
                                 u1runs["feb13"] + \
                                 u1runs["feb20"] + \
                                 u1runs["feb27"] + \
                                 u1runs["mar06"] + \
                                 u1runs["mar13"] + \
                                 u1runs["apr03"] + \
                                 u1runs["apr08"] + \
                                 u1runs["apr09"] + \
                                 u1runs["apr10"]))]
u1data["any"] = [get_runs(filter(lambda r: True,
                                 u1runs["jan16"] + \
                                 u1runs["jan30"] + \
                                 u1runs["feb06"] + \
                                 u1runs["feb13"] + \
                                 u1runs["feb20"] + \
                                 u1runs["feb27"] + \
                                 u1runs["mar06"] + \
                                 u1runs["mar13"] + \
                                 u1runs["apr03"] + \
                                 u1runs["apr08"] + \
                                 u1runs["apr09"] + \
                                 u1runs["apr10"]))]

u2data["low"] = [get_runs(filter(lambda r: runsummary[r].energy < (10023.26-1.7*4.18)/2000.,
                                 u2runs["may29"] + \
                                 u2runs["jun11"] + \
                                 u2runs["jun12"] + \
                                 u2runs["jul10"] + \
                                 u2runs["jul24"] + \
                                 u2runs["aug07"]))]
u2data["mid1"] = [get_runs(filter(lambda r: (10023.26-1.7*4.18)/2000. < runsummary[r].energy < (10023.26)/2000.,
                                 u2runs["may29"] + \
                                 u2runs["jun11"] + \
                                 u2runs["jun12"] + \
                                 u2runs["jul10"] + \
                                 u2runs["jul24"] + \
                                 u2runs["aug07"]))]
u2data["mid2"] = [get_runs(filter(lambda r: (10023.26)/2000. < runsummary[r].energy < (10023.26+1.7*4.18)/2000.,
                                 u2runs["may29"] + \
                                 u2runs["jun11"] + \
                                 u2runs["jun12"] + \
                                 u2runs["jul10"] + \
                                 u2runs["jul24"] + \
                                 u2runs["aug07"]))]
u2data["hi"] = [get_runs(filter(lambda r: (10023.26+1.7*4.18)/2000. < runsummary[r].energy,
                                 u2runs["may29"] + \
                                 u2runs["jun11"] + \
                                 u2runs["jun12"] + \
                                 u2runs["jul10"] + \
                                 u2runs["jul24"] + \
                                 u2runs["aug07"]))]
u2data["any"] = [get_runs(filter(lambda r: True < runsummary[r].energy,
                                 u2runs["may29"] + \
                                 u2runs["jun11"] + \
                                 u2runs["jun12"] + \
                                 u2runs["jul10"] + \
                                 u2runs["jul24"] + \
                                 u2runs["aug07"]))]

u3data["low"] = [get_runs(filter(lambda r: runsummary[r].energy < (10355.2-1.7*4.48)/2000.,
                                 u3runs["nov28"] + \
                                 u3runs["dec05"] + \
                                 u3runs["dec12"] + \
                                 u3runs["dec19"] + \
                                 u3runs["dec26"] + \
                                 u3runs["jan02"] + \
                                 u3runs["jan09"]))]
u3data["mid1"] = [get_runs(filter(lambda r: (10355.2-1.7*4.48)/2000. < runsummary[r].energy < (10355.2)/2000.,
                                 u3runs["nov28"] + \
                                 u3runs["dec05"] + \
                                 u3runs["dec12"] + \
                                 u3runs["dec19"] + \
                                 u3runs["dec26"] + \
                                 u3runs["jan02"] + \
                                 u3runs["jan09"]))]
u3data["mid2"] = [get_runs(filter(lambda r: (10355.2)/2000. < runsummary[r].energy < (10355.2+1.7*4.48)/2000.,
                                 u3runs["nov28"] + \
                                 u3runs["dec05"] + \
                                 u3runs["dec12"] + \
                                 u3runs["dec19"] + \
                                 u3runs["dec26"] + \
                                 u3runs["jan02"] + \
                                 u3runs["jan09"]))]
u3data["hi"] = [get_runs(filter(lambda r: (10355.2+1.7*4.48)/2000. < runsummary[r].energy,
                                 u3runs["nov28"] + \
                                 u3runs["dec05"] + \
                                 u3runs["dec12"] + \
                                 u3runs["dec19"] + \
                                 u3runs["dec26"] + \
                                 u3runs["jan02"] + \
                                 u3runs["jan09"]))]
u3data["any"] = [get_runs(filter(lambda r: True < runsummary[r].energy,
                                 u3runs["nov28"] + \
                                 u3runs["dec05"] + \
                                 u3runs["dec12"] + \
                                 u3runs["dec19"] + \
                                 u3runs["dec26"] + \
                                 u3runs["jan02"] + \
                                 u3runs["jan09"]))]

u1x = map(lambda (en,rat,err): en*2000., u1data["cont"] + u1data["low"] + u1data["mid1"] + u1data["mid2"] + u1data["hi"] + u1data["high"])
u1y = map(lambda (en,rat,err): rat, u1data["cont"] + u1data["low"] + u1data["mid1"] + u1data["mid2"] + u1data["hi"] + u1data["high"])
u1dy = map(lambda (en,rat,err): err, u1data["cont"] + u1data["low"] + u1data["mid1"] + u1data["mid2"] + u1data["hi"] + u1data["high"])

u2x = map(lambda (en,rat,err): en*2000., u2data["cont"] + u2data["low"] + u2data["mid1"] + u2data["mid2"] + u2data["hi"] + u2data["high"])
u2y = map(lambda (en,rat,err): rat, u2data["cont"] + u2data["low"] + u2data["mid1"] + u2data["mid2"] + u2data["hi"] + u2data["high"])
u2dy = map(lambda (en,rat,err): err, u2data["cont"] + u2data["low"] + u2data["mid1"] + u2data["mid2"] + u2data["hi"] + u2data["high"])

u3x = map(lambda (en,rat,err): en*2000., u3data["cont"] + u3data["low"] + u3data["mid1"] + u3data["mid2"] + u3data["hi"] + u3data["high"])
u3y = map(lambda (en,rat,err): rat, u3data["cont"] + u3data["low"] + u3data["mid1"] + u3data["mid2"] + u3data["hi"] + u3data["high"])
u3dy = map(lambda (en,rat,err): err, u3data["cont"] + u3data["low"] + u3data["mid1"] + u3data["mid2"] + u3data["hi"] + u3data["high"])

p = biggles.FramedPlot()
p.add(biggles.Points(u1x+u2x+u3x, u1y+u2y+u3y, symboltype="filled circle"))
p.add(biggles.SymmetricErrorBarsY(u1x+u2x+u3x, u1y+u2y+u3y, u1dy+u2dy+u3dy))
p.add(biggles.LineY(1.))
p.x1.range = 9300, 10500
p.x1.label = r"$E_{CM}$"
p.y1.label = r"outer BB lumi / $\gamma\gamma$ lumi"
p.show()
p.write_eps("ggtobb_by5_outerbb.eps")





# Now outer/inner Bhabhas
##########################################################

nobeam = getsb("cos")
ebeam = getsb("bge")
pbeam = getsb("bgp")
bsbha = pickle.load(open("/home/mccann/synthesis/run/bsbha.p"))
def get_runs1(runs):
  bb = 0.
  wsum = 0.
  wesum = 0.
  for r in runs:
    therun = getdb(r)
    
    ngg = therun.gamgam
    if r in mycarefulscan: ngg = therun.gamgam_vstime.sum(0.,0.99)
    wsum += float(ngg)
    wesum += float(ngg) * runsummary[r].energy

    if runsummary[r].res == 1:
      myarea, myrmsbeam, myback, myjan16, myjan30, myfeb06, myfeb13, myfeb20, myfeb27, mymar06, mymar13, myapr03, myapr08, myapr09, myapr10, myfullgam, myyint, myphi, mybtautau, mytauyint, mytauphi, mytwophofrac, myrjan, myrfeb, myrapr1, myrapr2 = ggfits[1].values
    elif runsummary[r].res == 2:
      myarea, myrmsbeam, myback, mymay29, myjun11, myjun12, myjul10, myjul24, myaug07, myfullgam, myyint, myphi, mybtautau, mytauyint, mytauphi, mytwophofrac, myu1area = ggfits[2].values
    elif runsummary[r].res == 3:
      myarea, myrmsbeam, myback, mynov28, mydec05, mydec12, mydec19, mydec26, myjan02, myjan09, myfullgam, myyint, myphi, mybtautau, mytauyint, mytauphi, mytwophofrac, myu1area, myu2area, myrnov28, myrdec05, myrdec12, myrdec19, myrdec26, myrjan02, myrjan09 = ggfits[3].values

    whichres, whichweek = whichamiin(r)

    thisrmsbeam = myrmsbeam
    if whichres == 1:
      if whichweek != None:
        if whichweek in ["jan16", "jan30", "feb06", "feb13", "feb20"]: thisrmsbeam = myrjan
        if whichweek in ["feb27", "mar06", "mar13"]: thisrmsbeam = myrfeb
        if whichweek in ["apr08", "apr09", "apr10"]: thisrmsbeam = myrapr2
    if whichres == 3:
      if whichweek != None:
        thisrmsbeam = eval("myr"+whichweek)

    thisshift = 0.
    if whichweek != None:
      thisshift = 0. - eval("my"+whichweek)

    if r in mycarefulscan:
      bb += therun.bhabha_cosp.sum(0.6, 0.8) * therun.bhabha_vstime.sum(0.,0.99) / therun.bhabha

      if runsummary[r].kind != 'c':
        # eecs = e+e- cross-section = hadronic area / (1 - 3 Bmm) * Bmm * outer range
        if runsummary[r].res == 1:
          eecs = myarea * mygbwkf(9460.30+thisshift, myfullgam, thisrmsbeam, 0.588*bhabha_interference, 0., 2000.*runsummary[r].energy) / 0.9253 * 0.0249 * 0.298667/2.66667
          bb -= eecs * float(therun.gamgam) * runsummary[r].energy**2 / nbish2nb

        if runsummary[r].res == 2:
          eecs = myarea * mygbwkf(10023.26+thisshift, myfullgam, thisrmsbeam, 0.864*bhabha_interference, 0., 2000.*runsummary[r].energy) / 0.9391 * 0.0203 * 0.298667/2.6667
          bb -= eecs * float(therun.gamgam) * runsummary[r].energy**2 / nbish2nb

        if runsummary[r].res == 3:
          eecs = myarea * mygbwkf(10355.2+thisshift, myfullgam, thisrmsbeam, 0.686*bhabha_interference, 0., 2000.*runsummary[r].energy) / 0.9283 * 0.0239 * 0.298667/2.6667
          bb -= eecs * float(therun.gamgam) * runsummary[r].energy**2 / nbish2nb

    else:
      bb += therun.bhabha_cosp.sum(0.6, 0.8)

      if runsummary[r].kind != 'c':
        # e+e- cross-section = hadronic area / (1 - 3 Bmm) * Bmm * outer range
        if runsummary[r].res == 1:
          eecs = myarea * mygbwkf(9460.30+thisshift, myfullgam, thisrmsbeam, 0.588*bhabha_interference, 0., 2000.*runsummary[r].energy) / 0.9253 * 0.0249 * 0.298667/2.66667
          bb -= eecs * float(therun.gamgam) * runsummary[r].energy**2 / nbish2nb

        if runsummary[r].res == 2:
          eecs = myarea * mygbwkf(10023.26+thisshift, myfullgam, thisrmsbeam, 0.864*bhabha_interference, 0., 2000.*runsummary[r].energy) / 0.9391 * 0.0203 * 0.298667/2.6667
          bb -= eecs * float(therun.gamgam) * runsummary[r].energy**2 / nbish2nb

        if runsummary[r].res == 3:
          eecs = myarea * mygbwkf(10355.2+thisshift, myfullgam, thisrmsbeam, 0.686*bhabha_interference, 0., 2000.*runsummary[r].energy) / 0.9283 * 0.0239 * 0.298667/2.6667
          bb -= eecs * float(therun.gamgam) * runsummary[r].energy**2 / nbish2nb

  average_energy = wesum / wsum
  return average_energy, (bb*0.118999), 1./bb

def get_runs2(runs):
  bb = 0.
  wsum = 0.
  wesum = 0.
  for r in runs:
    therun = getdb(r)
    
    ngg = therun.gamgam
    if r in mycarefulscan: ngg = therun.gamgam_vstime.sum(0.,0.99)
    wsum += float(ngg)
    wesum += float(ngg) * runsummary[r].energy

    if runsummary[r].res == 1:
      myarea, myrmsbeam, myback, myjan16, myjan30, myfeb06, myfeb13, myfeb20, myfeb27, mymar06, mymar13, myapr03, myapr08, myapr09, myapr10, myfullgam, myyint, myphi, mybtautau, mytauyint, mytauphi, mytwophofrac, myrjan, myrfeb, myrapr1, myrapr2 = ggfits[1].values
    elif runsummary[r].res == 2:
      myarea, myrmsbeam, myback, mymay29, myjun11, myjun12, myjul10, myjul24, myaug07, myfullgam, myyint, myphi, mybtautau, mytauyint, mytauphi, mytwophofrac, myu1area = ggfits[2].values
    elif runsummary[r].res == 3:
      myarea, myrmsbeam, myback, mynov28, mydec05, mydec12, mydec19, mydec26, myjan02, myjan09, myfullgam, myyint, myphi, mybtautau, mytauyint, mytauphi, mytwophofrac, myu1area, myu2area, myrnov28, myrdec05, myrdec12, myrdec19, myrdec26, myrjan02, myrjan09 = ggfits[3].values

    whichres, whichweek = whichamiin(r)

    thisrmsbeam = myrmsbeam
    if whichres == 1:
      if whichweek != None:
        if whichweek in ["jan16", "jan30", "feb06", "feb13", "feb20"]: thisrmsbeam = myrjan
        if whichweek in ["feb27", "mar06", "mar13"]: thisrmsbeam = myrfeb
        if whichweek in ["apr08", "apr09", "apr10"]: thisrmsbeam = myrapr2
    if whichres == 3:
      if whichweek != None:
        thisrmsbeam = eval("myr"+whichweek)

    thisshift = 0.
    if whichweek != None:
      thisshift = 0. - eval("my"+whichweek)

    if r in mycarefulscan:
      bb += therun.bhabha_cosp.sum(0., 0.6) * therun.bhabha_vstime.sum(0.,0.99) / therun.bhabha

      if runsummary[r].kind != 'c':
        # eecs = e+e- cross-section = hadronic area / (1 - 3 Bmm) * Bmm * inner range
        if runsummary[r].res == 1:
          eecs = myarea * mygbwkf(9460.30+thisshift, myfullgam, thisrmsbeam, 0.417*bhabha_interference, 0., 2000.*runsummary[r].energy) / 0.9253 * 0.0249 * 0.672/2.66667
          bb -= eecs * float(therun.gamgam) * runsummary[r].energy**2 / nbish2nb

        if runsummary[r].res == 2:
          eecs = myarea * mygbwkf(10023.26+thisshift, myfullgam, thisrmsbeam, 0.613*bhabha_interference, 0., 2000.*runsummary[r].energy) / 0.9391 * 0.0203 * 0.672/2.6667
          bb -= eecs * float(therun.gamgam) * runsummary[r].energy**2 / nbish2nb

        if runsummary[r].res == 3:
          eecs = myarea * mygbwkf(10355.2+thisshift, myfullgam, thisrmsbeam, 0.486*bhabha_interference, 0., 2000.*runsummary[r].energy) / 0.9283 * 0.0239 * 0.672/2.6667
          bb -= eecs * float(therun.gamgam) * runsummary[r].energy**2 / nbish2nb

    else:
      bb += therun.bhabha_cosp.sum(0., 0.6)

      if runsummary[r].kind != 'c':
        # e+e- cross-section = hadronic area / (1 - 3 Bmm) * Bmm * inner range
        if runsummary[r].res == 1:
          eecs = myarea * mygbwkf(9460.30+thisshift, myfullgam, thisrmsbeam, 0.417*bhabha_interference, 0., 2000.*runsummary[r].energy) / 0.9253 * 0.0249 * 0.672/2.66667
          bb -= eecs * float(therun.gamgam) * runsummary[r].energy**2 / nbish2nb

        if runsummary[r].res == 2:
          eecs = myarea * mygbwkf(10023.26+thisshift, myfullgam, thisrmsbeam, 0.613*bhabha_interference, 0., 2000.*runsummary[r].energy) / 0.9391 * 0.0203 * 0.672/2.6667
          bb -= eecs * float(therun.gamgam) * runsummary[r].energy**2 / nbish2nb

        if runsummary[r].res == 3:
          eecs = myarea * mygbwkf(10355.2+thisshift, myfullgam, thisrmsbeam, 0.486*bhabha_interference, 0., 2000.*runsummary[r].energy) / 0.9283 * 0.0239 * 0.672/2.6667
          bb -= eecs * float(therun.gamgam) * runsummary[r].energy**2 / nbish2nb

  average_energy = wesum / wsum
  return average_energy, (bb*0.23684), 1./bb

def fixit((en1, lum1, oon1), (en2, lum2, oon2)):
  if abs(en1 - en2) > 0.0000001:
    raise Exception
  return en1, lum1/lum2, lum1/lum2*sqrt(oon1+oon2)

u1data["cont"] = [fixit(get_runs1(u1runs["cont"]), get_runs2(u1runs["cont"]))]
u2data["cont"] = [fixit(get_runs1(u2runs["cont"]), get_runs2(u2runs["cont"]))]
u3data["cont"] = [fixit(get_runs1(u3runs["cont"]), get_runs2(u3runs["cont"]))]

u1data["high"] = [fixit(get_runs1(u1runs["high"]), get_runs2(u1runs["high"]))]
u2data["high"] = [fixit(get_runs1(u2runs["high"]), get_runs2(u2runs["high"]))]
u3data["high"] = [fixit(get_runs1(u3runs["high"]), get_runs2(u3runs["high"]))]

u1data["low"] = [fixit(get_runs1(filter(lambda r: runsummary[r].energy < (9460.3-1.7*3.79)/2000., \
                                 u1runs["jan16"] + \
                                 u1runs["jan30"] + \
                                 u1runs["feb06"] + \
                                 u1runs["feb13"] + \
                                 u1runs["feb20"] + \
                                 u1runs["feb27"] + \
                                 u1runs["mar06"] + \
                                 u1runs["mar13"] + \
                                 u1runs["apr03"] + \
                                 u1runs["apr08"] + \
                                 u1runs["apr09"] + \
                                 u1runs["apr10"])), \
                       get_runs2(filter(lambda r: runsummary[r].energy < (9460.3-1.7*3.79)/2000., \
                                 u1runs["jan16"] + \
                                 u1runs["jan30"] + \
                                 u1runs["feb06"] + \
                                 u1runs["feb13"] + \
                                 u1runs["feb20"] + \
                                 u1runs["feb27"] + \
                                 u1runs["mar06"] + \
                                 u1runs["mar13"] + \
                                 u1runs["apr03"] + \
                                 u1runs["apr08"] + \
                                 u1runs["apr09"] + \
                                 u1runs["apr10"])))]
u1data["mid1"] = [fixit(get_runs1(filter(lambda r: (9460.3-1.7*3.79)/2000. < runsummary[r].energy < (9460.3)/2000., \
                                 u1runs["jan16"] + \
                                 u1runs["jan30"] + \
                                 u1runs["feb06"] + \
                                 u1runs["feb13"] + \
                                 u1runs["feb20"] + \
                                 u1runs["feb27"] + \
                                 u1runs["mar06"] + \
                                 u1runs["mar13"] + \
                                 u1runs["apr03"] + \
                                 u1runs["apr08"] + \
                                 u1runs["apr09"] + \
                                 u1runs["apr10"])), \
                        get_runs2(filter(lambda r: (9460.3-1.7*3.79)/2000. < runsummary[r].energy < (9460.3)/2000., \
                                 u1runs["jan16"] + \
                                 u1runs["jan30"] + \
                                 u1runs["feb06"] + \
                                 u1runs["feb13"] + \
                                 u1runs["feb20"] + \
                                 u1runs["feb27"] + \
                                 u1runs["mar06"] + \
                                 u1runs["mar13"] + \
                                 u1runs["apr03"] + \
                                 u1runs["apr08"] + \
                                 u1runs["apr09"] + \
                                 u1runs["apr10"])))]
u1data["mid2"] = [fixit(get_runs1(filter(lambda r: (9460.3)/2000. < runsummary[r].energy < (9460.3+1.7*3.79)/2000., \
                                 u1runs["jan16"] + \
                                 u1runs["jan30"] + \
                                 u1runs["feb06"] + \
                                 u1runs["feb13"] + \
                                 u1runs["feb20"] + \
                                 u1runs["feb27"] + \
                                 u1runs["mar06"] + \
                                 u1runs["mar13"] + \
                                 u1runs["apr03"] + \
                                 u1runs["apr08"] + \
                                 u1runs["apr09"] + \
                                 u1runs["apr10"])), \
                        get_runs2(filter(lambda r: (9460.3)/2000. < runsummary[r].energy < (9460.3+1.7*3.79)/2000., \
                                 u1runs["jan16"] + \
                                 u1runs["jan30"] + \
                                 u1runs["feb06"] + \
                                 u1runs["feb13"] + \
                                 u1runs["feb20"] + \
                                 u1runs["feb27"] + \
                                 u1runs["mar06"] + \
                                 u1runs["mar13"] + \
                                 u1runs["apr03"] + \
                                 u1runs["apr08"] + \
                                 u1runs["apr09"] + \
                                 u1runs["apr10"])))]
u1data["hi"] = [fixit(get_runs1(filter(lambda r: (9460.3+1.7*3.79)/2000. < runsummary[r].energy, \
                                 u1runs["jan16"] + \
                                 u1runs["jan30"] + \
                                 u1runs["feb06"] + \
                                 u1runs["feb13"] + \
                                 u1runs["feb20"] + \
                                 u1runs["feb27"] + \
                                 u1runs["mar06"] + \
                                 u1runs["mar13"] + \
                                 u1runs["apr03"] + \
                                 u1runs["apr08"] + \
                                 u1runs["apr09"] + \
                                 u1runs["apr10"])), \
                      get_runs2(filter(lambda r: (9460.3+1.7*3.79)/2000. < runsummary[r].energy, \
                                 u1runs["jan16"] + \
                                 u1runs["jan30"] + \
                                 u1runs["feb06"] + \
                                 u1runs["feb13"] + \
                                 u1runs["feb20"] + \
                                 u1runs["feb27"] + \
                                 u1runs["mar06"] + \
                                 u1runs["mar13"] + \
                                 u1runs["apr03"] + \
                                 u1runs["apr08"] + \
                                 u1runs["apr09"] + \
                                 u1runs["apr10"])))]
u1data["any"] = [fixit(get_runs1(filter(lambda r: True, \
                                 u1runs["jan16"] + \
                                 u1runs["jan30"] + \
                                 u1runs["feb06"] + \
                                 u1runs["feb13"] + \
                                 u1runs["feb20"] + \
                                 u1runs["feb27"] + \
                                 u1runs["mar06"] + \
                                 u1runs["mar13"] + \
                                 u1runs["apr03"] + \
                                 u1runs["apr08"] + \
                                 u1runs["apr09"] + \
                                 u1runs["apr10"])), \
                       get_runs2(filter(lambda r: True, \
                                 u1runs["jan16"] + \
                                 u1runs["jan30"] + \
                                 u1runs["feb06"] + \
                                 u1runs["feb13"] + \
                                 u1runs["feb20"] + \
                                 u1runs["feb27"] + \
                                 u1runs["mar06"] + \
                                 u1runs["mar13"] + \
                                 u1runs["apr03"] + \
                                 u1runs["apr08"] + \
                                 u1runs["apr09"] + \
                                 u1runs["apr10"])))]

u2data["low"] = [fixit(get_runs1(filter(lambda r: runsummary[r].energy < (10023.26-1.7*4.18)/2000., \
                                 u2runs["may29"] + \
                                 u2runs["jun11"] + \
                                 u2runs["jun12"] + \
                                 u2runs["jul10"] + \
                                 u2runs["jul24"] + \
                                 u2runs["aug07"])), \
                       get_runs2(filter(lambda r: runsummary[r].energy < (10023.26-1.7*4.18)/2000., \
                                 u2runs["may29"] + \
                                 u2runs["jun11"] + \
                                 u2runs["jun12"] + \
                                 u2runs["jul10"] + \
                                 u2runs["jul24"] + \
                                 u2runs["aug07"])))]
u2data["mid1"] = [fixit(get_runs1(filter(lambda r: (10023.26-1.7*4.18)/2000. < runsummary[r].energy < (10023.26)/2000., \
                                 u2runs["may29"] + \
                                 u2runs["jun11"] + \
                                 u2runs["jun12"] + \
                                 u2runs["jul10"] + \
                                 u2runs["jul24"] + \
                                 u2runs["aug07"])), \
                        get_runs2(filter(lambda r: (10023.26-1.7*4.18)/2000. < runsummary[r].energy < (10023.26)/2000., \
                                 u2runs["may29"] + \
                                 u2runs["jun11"] + \
                                 u2runs["jun12"] + \
                                 u2runs["jul10"] + \
                                 u2runs["jul24"] + \
                                 u2runs["aug07"])))]
u2data["mid2"] = [fixit(get_runs1(filter(lambda r: (10023.26)/2000. < runsummary[r].energy < (10023.26+1.7*4.18)/2000., \
                                 u2runs["may29"] + \
                                 u2runs["jun11"] + \
                                 u2runs["jun12"] + \
                                 u2runs["jul10"] + \
                                 u2runs["jul24"] + \
                                 u2runs["aug07"])), \
                        get_runs2(filter(lambda r: (10023.26)/2000. < runsummary[r].energy < (10023.26+1.7*4.18)/2000., \
                                 u2runs["may29"] + \
                                 u2runs["jun11"] + \
                                 u2runs["jun12"] + \
                                 u2runs["jul10"] + \
                                 u2runs["jul24"] + \
                                 u2runs["aug07"])))]
u2data["hi"] = [fixit(get_runs1(filter(lambda r: (10023.26+1.7*4.18)/2000. < runsummary[r].energy, \
                                 u2runs["may29"] + \
                                 u2runs["jun11"] + \
                                 u2runs["jun12"] + \
                                 u2runs["jul10"] + \
                                 u2runs["jul24"] + \
                                 u2runs["aug07"])), \
                      get_runs2(filter(lambda r: (10023.26+1.7*4.18)/2000. < runsummary[r].energy, \
                                 u2runs["may29"] + \
                                 u2runs["jun11"] + \
                                 u2runs["jun12"] + \
                                 u2runs["jul10"] + \
                                 u2runs["jul24"] + \
                                 u2runs["aug07"])))]
u2data["any"] = [fixit(get_runs1(filter(lambda r: True < runsummary[r].energy, \
                                 u2runs["may29"] + \
                                 u2runs["jun11"] + \
                                 u2runs["jun12"] + \
                                 u2runs["jul10"] + \
                                 u2runs["jul24"] + \
                                 u2runs["aug07"])), \
                       get_runs2(filter(lambda r: True < runsummary[r].energy, \
                                 u2runs["may29"] + \
                                 u2runs["jun11"] + \
                                 u2runs["jun12"] + \
                                 u2runs["jul10"] + \
                                 u2runs["jul24"] + \
                                 u2runs["aug07"])))]

u3data["low"] = [fixit(get_runs1(filter(lambda r: runsummary[r].energy < (10355.2-1.7*4.48)/2000., \
                                 u3runs["nov28"] + \
                                 u3runs["dec05"] + \
                                 u3runs["dec12"] + \
                                 u3runs["dec19"] + \
                                 u3runs["dec26"] + \
                                 u3runs["jan02"] + \
                                 u3runs["jan09"])), \
                       get_runs2(filter(lambda r: runsummary[r].energy < (10355.2-1.7*4.48)/2000., \
                                 u3runs["nov28"] + \
                                 u3runs["dec05"] + \
                                 u3runs["dec12"] + \
                                 u3runs["dec19"] + \
                                 u3runs["dec26"] + \
                                 u3runs["jan02"] + \
                                 u3runs["jan09"])))]
u3data["mid1"] = [fixit(get_runs1(filter(lambda r: (10355.2-1.7*4.48)/2000. < runsummary[r].energy < (10355.2)/2000., \
                                 u3runs["nov28"] + \
                                 u3runs["dec05"] + \
                                 u3runs["dec12"] + \
                                 u3runs["dec19"] + \
                                 u3runs["dec26"] + \
                                 u3runs["jan02"] + \
                                 u3runs["jan09"])), \
                        get_runs2(filter(lambda r: (10355.2-1.7*4.48)/2000. < runsummary[r].energy < (10355.2)/2000., \
                                 u3runs["nov28"] + \
                                 u3runs["dec05"] + \
                                 u3runs["dec12"] + \
                                 u3runs["dec19"] + \
                                 u3runs["dec26"] + \
                                 u3runs["jan02"] + \
                                 u3runs["jan09"])))]
u3data["mid2"] = [fixit(get_runs1(filter(lambda r: (10355.2)/2000. < runsummary[r].energy < (10355.2+1.7*4.48)/2000., \
                                 u3runs["nov28"] + \
                                 u3runs["dec05"] + \
                                 u3runs["dec12"] + \
                                 u3runs["dec19"] + \
                                 u3runs["dec26"] + \
                                 u3runs["jan02"] + \
                                 u3runs["jan09"])), \
                        get_runs2(filter(lambda r: (10355.2)/2000. < runsummary[r].energy < (10355.2+1.7*4.48)/2000., \
                                 u3runs["nov28"] + \
                                 u3runs["dec05"] + \
                                 u3runs["dec12"] + \
                                 u3runs["dec19"] + \
                                 u3runs["dec26"] + \
                                 u3runs["jan02"] + \
                                 u3runs["jan09"])))]
u3data["hi"] = [fixit(get_runs1(filter(lambda r: (10355.2+1.7*4.48)/2000. < runsummary[r].energy, \
                                 u3runs["nov28"] + \
                                 u3runs["dec05"] + \
                                 u3runs["dec12"] + \
                                 u3runs["dec19"] + \
                                 u3runs["dec26"] + \
                                 u3runs["jan02"] + \
                                 u3runs["jan09"])),
                      get_runs2(filter(lambda r: (10355.2+1.7*4.48)/2000. < runsummary[r].energy, \
                                 u3runs["nov28"] + \
                                 u3runs["dec05"] + \
                                 u3runs["dec12"] + \
                                 u3runs["dec19"] + \
                                 u3runs["dec26"] + \
                                 u3runs["jan02"] + \
                                 u3runs["jan09"])))]
u3data["any"] = [fixit(get_runs1(filter(lambda r: True < runsummary[r].energy, \
                                 u3runs["nov28"] + \
                                 u3runs["dec05"] + \
                                 u3runs["dec12"] + \
                                 u3runs["dec19"] + \
                                 u3runs["dec26"] + \
                                 u3runs["jan02"] + \
                                 u3runs["jan09"])), \
                       get_runs2(filter(lambda r: True < runsummary[r].energy, \
                                 u3runs["nov28"] + \
                                 u3runs["dec05"] + \
                                 u3runs["dec12"] + \
                                 u3runs["dec19"] + \
                                 u3runs["dec26"] + \
                                 u3runs["jan02"] + \
                                 u3runs["jan09"])))]

u1x = map(lambda (en,rat,err): en*2000., u1data["cont"] + u1data["low"] + u1data["mid1"] + u1data["mid2"] + u1data["hi"] + u1data["high"])
u1y = map(lambda (en,rat,err): rat, u1data["cont"] + u1data["low"] + u1data["mid1"] + u1data["mid2"] + u1data["hi"] + u1data["high"])
u1dy = map(lambda (en,rat,err): err, u1data["cont"] + u1data["low"] + u1data["mid1"] + u1data["mid2"] + u1data["hi"] + u1data["high"])

u2x = map(lambda (en,rat,err): en*2000., u2data["cont"] + u2data["low"] + u2data["mid1"] + u2data["mid2"] + u2data["hi"] + u2data["high"])
u2y = map(lambda (en,rat,err): rat, u2data["cont"] + u2data["low"] + u2data["mid1"] + u2data["mid2"] + u2data["hi"] + u2data["high"])
u2dy = map(lambda (en,rat,err): err, u2data["cont"] + u2data["low"] + u2data["mid1"] + u2data["mid2"] + u2data["hi"] + u2data["high"])

u3x = map(lambda (en,rat,err): en*2000., u3data["cont"] + u3data["low"] + u3data["mid1"] + u3data["mid2"] + u3data["hi"] + u3data["high"])
u3y = map(lambda (en,rat,err): rat, u3data["cont"] + u3data["low"] + u3data["mid1"] + u3data["mid2"] + u3data["hi"] + u3data["high"])
u3dy = map(lambda (en,rat,err): err, u3data["cont"] + u3data["low"] + u3data["mid1"] + u3data["mid2"] + u3data["hi"] + u3data["high"])

p = biggles.FramedPlot()
p.add(biggles.Points(u1x+u2x+u3x, u1y+u2y+u3y, symboltype="filled circle"))
p.add(biggles.SymmetricErrorBarsY(u1x+u2x+u3x, u1y+u2y+u3y, u1dy+u2dy+u3dy))
p.add(biggles.LineY(1.))
p.x1.range = 9300, 10500
p.x1.label = r"$E_{CM}$"
p.y1.label = r"outer BB lumi / inner BB lumi"
p.show()
p.write_eps("ggtobb_by5_outerinner.eps")






