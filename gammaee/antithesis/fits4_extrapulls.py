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

def adddata_pull(p, data, shift, f):
  x = []
  y = []
  for (e, h, herr) in data:
    x.append(e*2000.+shift)
    y.append((h - f(e*2000.+shift))/herr)
  p.add(biggles.Points(x, y, symboltype="filled circle", symbolsize=1.1))
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
  p.add(biggles.Points(x, y, symboltype="filled circle", symbolsize=1.1))
  return x

dticks = []
dlabels = []
for y in (2001, 2002):
  for m in Numeric.array(range(12))+1:
    for d in [1]:
      dticks.append(time.mktime(time.strptime("%02d %02d %4d" % (m, d, y), "%m %d %Y")))
for y in (2001, 2002):
  for m in ("Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"):
    for d in [1,]:
      if d == 1:
        dlabels.append("%s" % (m))
      else:
        dlabels.append("%d" % (d))
dsubticks = []
for y in (2001, 2002):
  for d in Numeric.array(range(365))+1:
    if d % 7 == 0:
      dsubticks.append(time.mktime(time.strptime("%03d %4d" % (d, y), "%j %Y")))

def u1plot_pull(area, rmsbeam, back, jan16, jan30, feb06, feb13, feb20, feb27, mar06, mar13, apr03, apr08, apr09, apr10, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac):
  p = biggles.Table(1,3)
  p[0,0] = biggles.FramedPlot()
  p[0,2] = biggles.FramedPlot()
  h = MoreThanHist(25, -5., 5.)
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
  dates += adddata_pull3(p[0,2], u1runs["jan16"], u1data["jan16"], jan16, lambda w: u1func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, w))
  dates += adddata_pull3(p[0,2], u1runs["jan30"], u1data["jan30"], jan30, lambda w: u1func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, w))
  dates += adddata_pull3(p[0,2], u1runs["feb06"], u1data["feb06"], feb06, lambda w: u1func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, w))
  dates += adddata_pull3(p[0,2], u1runs["feb13"], u1data["feb13"], feb13, lambda w: u1func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, w))
  dates += adddata_pull3(p[0,2], u1runs["feb20"], u1data["feb20"], feb20, lambda w: u1func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, w))
  dates += adddata_pull3(p[0,2], u1runs["feb27"], u1data["feb27"], feb27, lambda w: u1func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, w))
  dates += adddata_pull3(p[0,2], u1runs["mar06"], u1data["mar06"], mar06, lambda w: u1func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, w))
  dates += adddata_pull3(p[0,2], u1runs["mar13"], u1data["mar13"], mar13, lambda w: u1func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, w))
  dates += adddata_pull3(p[0,2], u1runs["apr03"], u1data["apr03"], apr03, lambda w: u1func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, w))
  dates += adddata_pull3(p[0,2], u1runs["apr08"], u1data["apr08"], apr08, lambda w: u1func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, w))
  dates += adddata_pull3(p[0,2], u1runs["apr09"], u1data["apr09"], apr09, lambda w: u1func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, w))
  dates += adddata_pull3(p[0,2], u1runs["apr10"], u1data["apr10"], apr10, lambda w: u1func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, w))
  p[0,2].add(biggles.LineY(0.))
#  p[0,2].x1.range = 123000, 125500
  p[0,2].x1.range = min(dates)-7.*24.*60.*60., max(dates)+7.*24.*60.*60.
  subticks = []
  sublabels = []
  for t, l in zip(dticks, dlabels):
    if min(dates)-7.*24.*60.*60. < t < max(dates)+7.*24.*60.*60.:
      subticks.append(t)
      sublabels.append(l)
  subsubticks = []
  for t in dsubticks:
    if min(dates)-7.*24.*60.*60. < t < max(dates)+7.*24.*60.*60.:
      subsubticks.append(t)
  p[0,2].x1.ticks = subticks
  p[0,2].x1.subticks = subsubticks
  p[0,2].x1.ticklabels = sublabels
  p[0,2].x2.ticks = subticks
  p[0,2].x2.subticks = subsubticks
  p[0,2].x2.draw_ticklabels = 0
  p[0,2].x1.label = r"Date in 2002"
  p[0,2].y1.label = r"Pull"
  p[0,2].y1.range = -5, 5
  p[0,0].y1.range = -5, 5
  p[0,0].add(biggles.LineY(0.))
  p[0,0].x1.range = 9420., 9580.
  p[0,0].x.ticks = 9420., 9460., 9500., 9540., 9580.
  p[0,0].x1.label = r"$E_{COM}$ in MeV"
  p[0,0].y1.label = r"Pull"
  p[0,1] = h.plot()
  p[0,1].add(h.steps(linewidth=3.5))
  p[0,1].x1.label = r"Pull"
  h.rootn()
  mean, meanerr, width, widtherr, f = dofitgauss(h)
  x = Numeric.arange(-5., 5., 0.01)
  y = Numeric.arange(-5., 5., 0.01)
  for i, xi in enumerate(x): y[i] = f(xi)
  p[0,1].add(biggles.Curve(x,y,linewidth=3.5, linecolor="red"))
  entries = h.sum() + h.underflow() + h.overflow()
#  hist.addinfobox(p[0,1], [["entries", entries], ["mean", r"%4.2f $\pm$ %4.2f" % (mean, abs(meanerr))], ["width", r"%4.2f $\pm$ %4.2f" % (abs(width), abs(widtherr))], ["underflow", h.underflow()], ["overflow", h.overflow()], ["", ""]], width=0.3, colwidth=0.07)
  p[0,0].aspect_ratio = 3.1
  p[0,1].aspect_ratio = 3.1
  p[0,2].aspect_ratio = 3.1
  p[0,1], p[0,2] = p[0,2], p[0,1]
  p.aspect_ratio = 8.5/11.
  return p
p = u1plot_pull(*fitrecord[1].values)
p.show()
p.write_eps("/home/mccann/antithesis/plots/plenary_pulls1.eps")

dticks = []
dlabels = []
for y in (2001, 2002):
  for m in Numeric.array(range(12))+1:
    for d in [1]:
      dticks.append(time.mktime(time.strptime("%02d %02d %4d" % (m, d, y), "%m %d %Y")))
for y in (2001, 2002):
  for m in ("Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"):
    for d in [1]:
      if d == 1:
        dlabels.append("%s" % (m))
      else:
        dlabels.append("%d" % (d))
dsubticks = []
for y in (2001, 2002):
  for d in Numeric.array(range(365))+1:
    if d % 7 == 0:
      dsubticks.append(time.mktime(time.strptime("%03d %4d" % (d, y), "%j %Y")))

def u2plot_pull(area, rmsbeam, back, may29, jun11, jun12, jul10, jul24, aug07, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area):
  p = biggles.Table(1,3)
  p[0,0] = biggles.FramedPlot()
  p[0,2] = biggles.FramedPlot()
  h = MoreThanHist(25, -5., 5.)
  h.fill(adddata_pull(p[0,0], u2data["cont"], 0., lambda w: u2func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, w)))
  h.fill(adddata_pull(p[0,0], u2data["high"], 0., lambda w: u2func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, w)))
  h.fill(adddata_pull(p[0,0], u2data["may29"], may29, lambda w: u2func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, w)))
  h.fill(adddata_pull(p[0,0], u2data["jun11"], jun11, lambda w: u2func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, w)))
  h.fill(adddata_pull(p[0,0], u2data["jun12"], jun12, lambda w: u2func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, w)))
  h.fill(adddata_pull(p[0,0], u2data["jul10"], jul10, lambda w: u2func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, w)))
  h.fill(adddata_pull(p[0,0], u2data["jul24"], jul24, lambda w: u2func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, w)))
  h.fill(adddata_pull(p[0,0], u2data["aug07"], aug07, lambda w: u2func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, w)))
  dates = []
  dates += adddata_pull3(p[0,2], u2runs["may29"], u2data["may29"], may29, lambda w: u2func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, w))
  dates += adddata_pull3(p[0,2], u2runs["jun11"], u2data["jun11"], jun11, lambda w: u2func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, w))
  dates += adddata_pull3(p[0,2], u2runs["jun12"], u2data["jun12"], jun12, lambda w: u2func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, w))
  dates += adddata_pull3(p[0,2], u2runs["jul10"], u2data["jul10"], jul10, lambda w: u2func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, w))
  dates += adddata_pull3(p[0,2], u2runs["jul24"], u2data["jul24"], jul24, lambda w: u2func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, w))
  dates += adddata_pull3(p[0,2], u2runs["aug07"], u2data["aug07"], aug07, lambda w: u2func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, w))
  p[0,2].add(biggles.LineY(0.))
#  p[0,2].x1.range = 126000, 128500
  p[0,2].x1.range = min(dates)-7.*24.*60.*60., max(dates)+7.*24.*60.*60.
  subticks = []
  sublabels = []
  for t, l in zip(dticks, dlabels):
    if min(dates)-7.*24.*60.*60. < t < max(dates)+7.*24.*60.*60.:
      subticks.append(t)
      sublabels.append(l)
  subsubticks = []
  for t in dsubticks:
    if min(dates)-7.*24.*60.*60. < t < max(dates)+7.*24.*60.*60.:
      subsubticks.append(t)
  p[0,2].x1.ticks = subticks
  p[0,2].x1.subticks = subsubticks
  p[0,2].x1.ticklabels = sublabels
  p[0,2].x2.ticks = subticks
  p[0,2].x2.subticks = subsubticks
  p[0,2].x2.draw_ticklabels = 0
  p[0,2].x1.label = r"Date in 2002"
  p[0,2].y1.label = r"Pull"
  p[0,2].y1.range = -5, 5
  p[0,0].y1.range = -5, 5
  p[0,0].add(biggles.LineY(0.))
  p[0,0].x1.range = 9980., 10100.
  p[0,0].x.ticks = 9980., 10020., 10060., 10100.
  p[0,0].x1.label = r"$E_{COM}$ in MeV"
  p[0,0].y1.label = r"Pull"
  p[0,1] = h.plot()
  p[0,1].add(h.steps(linewidth=3.5))
  p[0,1].x1.label = r"Pull"
  h.rootn()
  mean, meanerr, width, widtherr, f = dofitgauss(h)
  x = Numeric.arange(-5., 5., 0.01)
  y = Numeric.arange(-5., 5., 0.01)
  for i, xi in enumerate(x): y[i] = f(xi)
  p[0,1].add(biggles.Curve(x,y, linewidth=3.5, linecolor="red"))
  entries = h.sum() + h.underflow() + h.overflow()
#  hist.addinfobox(p[0,1], [["entries", entries], ["mean", r"%4.2f $\pm$ %4.2f" % (mean, abs(meanerr))], ["width", r"%4.2f $\pm$ %4.2f" % (abs(width), abs(widtherr))], ["underflow", h.underflow()], ["overflow", h.overflow()], ["", ""]], width=0.3, colwidth=0.07)
  p[0,0].aspect_ratio = 3.1
  p[0,1].aspect_ratio = 3.1
  p[0,2].aspect_ratio = 3.1
  p[0,1], p[0,2] = p[0,2], p[0,1]
  p.aspect_ratio = 8.5/11.
  return p
p = u2plot_pull(*u2fitter.values)
p.show()
p.write_eps("/home/mccann/antithesis/plots/plenary_pulls2.eps")

dticks = []
dlabels = []
for y in (2001, 2002):
  for m in Numeric.array(range(12))+1:
    for d in [1]:
      dticks.append(time.mktime(time.strptime("%02d %02d %4d" % (m, d, y), "%m %d %Y")))
for y in (2001, 2002):
  for m in ("Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"):
    for d in [1]:
      if d == 1:
        dlabels.append("%s %d" % (m, y))
      else:
        dlabels.append("%d" % (d))
dsubticks = []
for y in (2001, 2002):
  for d in Numeric.array(range(365))+1:
    if d % 7 == 0:
      dsubticks.append(time.mktime(time.strptime("%03d %4d" % (d, y), "%j %Y")))

def u3plot_pull(area, rmsbeam, back, nov28, dec05, dec12, dec19, dec26, jan02, jan09, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area):
  p = biggles.Table(1,3)
  p[0,0] = biggles.FramedPlot()
  p[0,2] = biggles.FramedPlot()
  h = MoreThanHist(25, -5., 5.)
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
  dates += adddata_pull3(p[0,2], u3runs["nov28"], u3data["nov28"], nov28, lambda w: u3func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area, w))
  dates += adddata_pull3(p[0,2], u3runs["dec05"], u3data["dec05"], dec05, lambda w: u3func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area, w))
  dates += adddata_pull3(p[0,2], u3runs["dec12"], u3data["dec12"], dec12, lambda w: u3func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area, w))
  dates += adddata_pull3(p[0,2], u3runs["dec19"], u3data["dec19"], dec19, lambda w: u3func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area, w))
  dates += adddata_pull3(p[0,2], u3runs["dec26"], u3data["dec26"], dec26, lambda w: u3func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area, w))
  dates += adddata_pull3(p[0,2], u3runs["jan02"], u3data["jan02"], jan02, lambda w: u3func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area, w))
  dates += adddata_pull3(p[0,2], u3runs["jan09"], u3data["jan09"], jan09, lambda w: u3func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area, w))
  p[0,2].add(biggles.LineY(0.))
#  p[0,2].x1.range = 121500, 123500
  p[0,2].x1.range = min(dates)-7.*24.*60.*60., max(dates)+7.*24.*60.*60.
  subticks = []
  sublabels = []
  for t, l in zip(dticks, dlabels):
    if min(dates)-7.*24.*60.*60. < t < max(dates)+7.*24.*60.*60.:
      subticks.append(t)
      sublabels.append(l)
  subsubticks = []
  for t in dsubticks:
    if min(dates)-7.*24.*60.*60. < t < max(dates)+7.*24.*60.*60.:
      subsubticks.append(t)
  p[0,2].x1.ticks = subticks
  p[0,2].x1.subticks = subsubticks
  p[0,2].x1.ticklabels = sublabels
  p[0,2].x2.ticks = subticks
  p[0,2].x2.subticks = subsubticks
  p[0,2].x2.draw_ticklabels = 0
  p[0,2].x1.label = r"Date"
  p[0,2].y1.label = r"Pull"
  p[0,2].y1.range = -5, 5
  p[0,0].y1.range = -5, 5
  p[0,0].add(biggles.LineY(0.))
  p[0,0].x1.range = 10320., 10420.
  p[0,0].x.ticks = 10320., 10370., 10420.
  p[0,0].x1.label = r"$E_{COM}$ in MeV"
  p[0,0].y1.label = r"Pull"
  p[0,1] = h.plot()
  p[0,1].add(h.steps(linewidth=3.5))
  p[0,1].x1.label = r"Pull"
  h.rootn()
  mean, meanerr, width, widtherr, f = dofitgauss(h)
  x = Numeric.arange(-5., 5., 0.01)
  y = Numeric.arange(-5., 5., 0.01)
  for i, xi in enumerate(x): y[i] = f(xi)
  p[0,1].add(biggles.Curve(x,y, linewidth=3.5, linecolor="red"))
  entries = h.sum() + h.underflow() + h.overflow()
#  hist.addinfobox(p[0,1], [["entries", entries], ["mean", r"%4.2f $\pm$ %4.2f" % (mean, abs(meanerr))], ["width", r"%4.2f $\pm$ %4.2f" % (abs(width), abs(widtherr))], ["underflow", h.underflow()], ["overflow", h.overflow()], ["", ""]], width=0.3, colwidth=0.07)
  p[0,0].aspect_ratio = 3.1
  p[0,1].aspect_ratio = 3.1
  p[0,2].aspect_ratio = 3.1
  p[0,1], p[0,2] = p[0,2], p[0,1]
  p.aspect_ratio = 8.5/11.
  return p
p = u3plot_pull(*u3fitter.values)
p.show()
p.write_eps("/home/mccann/antithesis/plots/plenary_pulls3.eps")

######################################################

ee1s = 1555455./8.993 / 1.e6
ee2s = 3327270./7.945 / 1.e6
ee3s = 1134794./7.361 / 1.e6
gg1s = ee1s * 0.989
gg2s = ee2s * 0.994
gg3s = ee3s * 0.995
mm1s = ee1s * 1.013
mm2s = ee2s * 1.022
mm3s = ee3s * 1.010
ee = ee1s + ee2s + ee3s
gg = gg1s + gg2s + gg3s
mm = mm1s + mm2s + mm3s
tot = ee1s*1.002+ee2s*1.006+ee3s*1.002
eestat = sqrt(1./(1555455.+3327270.+1134794.))
mmstat = sqrt(8.993/0.5367/(1555455.+3327270.+1134794.))
ggstat = sqrt(8.993/1.297/(1555455.+3327270.+1134794.))

p = biggles.FramedPlot()
p.add(biggles.Points(range(3), [ee, mm, gg], symboltype="filled circle", symbolsize=2.))
p.add(biggles.SymmetricErrorBarsY(range(3), [ee, mm, gg], [ee*sqrt(0.0125**2+eestat**2), mm*sqrt(0.0125**2+mmstat**2), gg*sqrt(0.018**2+ggstat**2)]))
p.add(biggles.SymmetricErrorBarsY(range(3), [ee, mm, gg], [ee*sqrt(0.016**2+eestat**2), mm*sqrt(0.016**2+mmstat**2), gg*sqrt(0.018**2+ggstat**2)]))
p.add(biggles.SymmetricErrorBarsY(range(3), [ee, mm, gg], [ee*eestat, mm*mmstat, gg*ggstat]))
p.add(biggles.LineY(tot, linetype="longdashed"))
p.add(biggles.LineY(tot*(1+0.013), linetype="dotted"))
p.add(biggles.LineY(tot*(1-0.013), linetype="dotted"))
p.x.ticks = range(3)
p.x1.ticklabels = [r"$e^+e^-$", r"$\mu^+\mu^-$", r"$\gamma\gamma$"]
p.x.subticks = 0
p.x.range = -0.5, 2.5
p.x1.draw_ticks = 0
p.x2.draw_ticks = 0
p.x2.draw_ticklabels = 0
p.y.range = 0.7, 0.8
p.y1.label = r"Integrated luminosity in fb$^{-1}$"
p.y2.range = (0.7-tot)/tot*100., (0.8-tot)/tot*100.
p.y2.ticks = [-6, -4, -2, 0, 2, 4, 6]
p.y2.ticklabels = ["6", "4", "2", "0", "2", "4", "6"]
p.y2.subticks = Numeric.arange(-6, 7, 1)
p.y2.label = r"Percent Error"
p.aspect_ratio = 7.5/11.
p.frame.label_style["fontsize"] = 4.
p.show()
p.write_eps("/home/mccann/antithesis/plots/plenary_lumi.eps")

####################################################

area, rmsbeam, back, jan16, jan30, feb06, feb13, feb20, feb27, mar06, mar13, apr03, apr08, apr09, apr10, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac = u1fitter.values
f = lambda w: u1func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, w)

p = biggles.FramedPlot()
addfunc(p, f, 9420., 9580.)
p.xrange = 9435., 9490.
p.yrange = 0., 30.
p.aspect_ratio = 2.
p.x1.label = r"Center-of-mass energy in MeV"
p.y1.label = r"Hadronic cross-section in nb"
xvals = [9457., 9469., 9452., 9463.]
p.add(biggles.Points(xvals, map(f, xvals), symboltype="filled circle", symbolsize=2.))
p.add(biggles.DataLabel(xvals[0]-3., f(xvals[0]), "1, 5", texthalign="right", textvalign="bottom", fontsize=4.))
p.add(biggles.DataLabel(xvals[1]+3., f(xvals[1]), "2", texthalign="left", textvalign="bottom", fontsize=4.))
p.add(biggles.DataLabel(xvals[2]-3., f(xvals[2]), "3", texthalign="right", textvalign="bottom", fontsize=4.))
p.add(biggles.DataLabel(xvals[3]+3., f(xvals[3]), "4", texthalign="left", textvalign="bottom", fontsize=4.))
p.show()
p.write_eps("/home/mccann/antithesis/plots/plenary_fitorder.eps")
