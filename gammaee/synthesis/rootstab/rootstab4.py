from math import *
import rootntuple, cPickle as pickle, time

class RunSummary : pass
runsummary = pickle.load(open("/home/mccann/synthesis/lumieff/runsummary.p"))

low_runs = [124684, 124685, 124687, 124688, 124690, 124691, 124699, 124701, 124702, 124704, 124705, 124706, 124707, 124708, 124709, 124712, 124713, 124714, 124716, 124718, 124719, 124720, 124721, 124722, 124725, 124726, 124727, 124728, 124729, 124730, 124731, 124732, 124733, 124734, 124735, 124736]
high_runs = [125360, 125361, 125362, 125363, 125364, 125366, 125368, 125369, 125370, 125372, 125373, 125375, 125377, 125378, 125380, 125382, 125384, 125389, 125391, 125392, 125395, 125396, 125397, 125398, 125399, 125400, 125403, 125404, 125405, 125407, 125408, 125416]

def getntuple(run):
  return rootntuple.RootNtuple("/home/mccann/synthesis/root/db_"+str(run)+".root:/UpsilonGammaEEAnalysisProc/nt1")

low = getntuple(low_runs[0])
for r in low_runs[1:]:
  low += getntuple(r)

high = getntuple(high_runs[0])
for r in high_runs[1:]:
  high += getntuple(r)

# ['run', 'event', 'trig', 'type', 'd0close', 'anyz', 'p1x', 'p1y', 'p1z', 'p2x', 'p2y', 'p2z', 'visen', 'coolvisen', 'frozenvisen', 'tracks', 'rawtk', 'oppositesides', 'e1', 'e2', 'e3', 'phi1', 'cos1', 'phi2', 'cos2', 'oppositecharge', 'eisr', 'econstr', 'cosp', 'cosn', 'wpz', 'pdotp', 'ccen', 'neue', 'l4dec', 'chen']

class variable:
  def __init__(self, low, high):
    self.x = arange(low, high, (high-low)/100.)

    self.highhad = {}
    self.highbha = {}
    self.lowhad = {}
    self.lowbha = {}

    for xi in self.x:
      self.highhad[xi] = 0
      self.highbha[xi] = 0
      self.lowhad[xi] = 0
      self.lowbha[xi] = 0

  def fill(self, n, func, which, hadfunc=hadron, lumifunc=bhabha):
    if which == 0:
      if hadfunc(n):
        for xi in self.x:
          if func(n, xi): self.highhad[xi] += 1
          
      if lumifunc(n):
        for xi in self.x:
          self.highbha[xi] += 1

    else:
      if hadfunc(n):
        for xi in self.x:
          if func(n, xi): self.lowhad[xi] += 1
          
      if lumifunc(n):
        for xi in self.x:
          self.lowbha[xi] += 1
    
  def xydy(self):
    y = [0.] * len(self.x)
    dy = [0.] * len(self.x)

    for i, xi in enumerate(self.x):
      try:
        y[i] = (1.*self.highhad[xi]/self.highbha[xi]) /                   \
               (1.*self.lowhad[xi]/self.lowbha[xi])
        dy[i] = y[i]*sqrt(1./self.highhad[xi] + 1./self.highbha[xi] +     \
                          1./self.lowhad[xi] + 1./self.lowbha[xi])
      except ZeroDivisionError:
        y[i] = 0.
        dy[i] = 0.

    return self.x, y, dy

# test_anyz  = variable(0., 0.075)
test_p1    = variable(0., 1.2)
# test_visen = variable(0.4, 1.2)
test_p1_gg = variable(0., 1.2)

def hadron(n):
  return n.type % 10 == 1

def mosthadron(n):
  return int(n.trig) % 10000 % 1000 > 0 and \
         abs(n.d0close) < 0.005 and \
         abs(n.anyz) < 0.075 and \
         n.coolvisen > 0.4

def gamgam(n):
  return int(floor(n.type / 10)) % 10 == 1

def bhabha(n):
  return int(floor(n.type / 100)) % 10 == 1

def cuts_anyz(n, val=0.075):
  return abs(n.anyz) < val

def cuts_p1(n, val=0.8):
  return sqrt(n.p1x**2+n.p1y**2+n.p1z**2) / runsummary[int(n.run)].energy < val

def cuts_visen(n, val=0.4):
  return n.coolvisen > val

# low.optimize = ["type", "anyz", "p1x", "p1y", "p1z", "run", "coolvisen"]
# high.optimize = ["type", "anyz", "p1x", "p1y", "p1z", "run", "coolvisen"]
low.optimize = ["type", "trig", "d0close", "anyz", "p1x", "p1y", "p1z", "run", "coolvisen"]
high.optimize = ["type", "trig", "d0close", "anyz", "p1x", "p1y", "p1z", "run", "coolvisen"]

low.range()
high.range()

counter = 0
for n in low:
  if counter % 10000 == 0:
    print time.asctime(time.localtime(time.time())), counter
  counter += 1

#   test_anyz.fill(n, cuts_anyz, 1)
  test_p1.fill(n, cuts_p1, 1, hadfunc=mosthadron)
#   test_visen.fill(n, cuts_visen, 1)
  test_p1_gg.fill(n, cuts_p1, 1, hadfunc=mosthadron, lumifunc=gamgam)

counter = 0
for n in high:
  if counter % 10000 == 0:
    print time.asctime(time.localtime(time.time())), counter
  counter += 1

#   test_anyz.fill(n, cuts_anyz, 0)
  test_p1.fill(n, cuts_p1, 0, hadfunc=mosthadron)
#   test_visen.fill(n, cuts_visen, 0)
  test_p1_gg.fill(n, cuts_p1, 0, hadfunc=mosthadron, lumifunc=gamgam)

# pickle.dump(test_anyz, open("rootstab4_anyz.p", "w"))
pickle.dump(test_p1, open("rootstab4_p1.p", "w"))
# pickle.dump(test_visen, open("rootstab4_visen.p", "w"))
pickle.dump(test_p1_gg, open("rootstab4_p1_gg.p", "w"))

clf()

subplot(311)
x, y, dy = test_anyz.xydy()
errorbar(x, y, dy, fmt="ok")
axhline(1.01305, color="k")
axhline(1, color="k")
axis([0, 0.075, 0.99, 1.06])
xlabel(r"Z vertex cut (m)")
title(r"Hadronic cross-section April/March ratio")

subplot(312)
x, y, dy = test_p1.xydy()
errorbar(x, y, dy, fmt="ok")
axhline(1.01305, color="k")
axhline(1, color="k")
axis([0, 1.2, 0.99, 1.06])
xlabel(r"Biggest track cut (/beam energy)")

subplot(313)
x, y, dy = test_visen.xydy()
errorbar(x, y, dy, fmt="ok")
axhline(1.01305, color="k")
axhline(1, color="k")
axis([0.4, 1.2, 0.99, 1.06])
xlabel(r"Visible energy cut (/COM energy)")

savefig("rootstab4_crosssec_ratio.eps")




title(r"Hadronic cross-section April/March ratio")
subplot(211)
x, y, dy = test_p1.xydy()
errorbar(x, y, dy, fmt="ok")
axhline(1.01305, color="k")
axhline(1, color="k")
axis([0, 1.2, 0.99, 1.06])
xlabel(r"Biggest track cut (/beam energy) (bhabha luminosity, same as prev)")

subplot(212)
x, y, dy = test_p1_gg.xydy()
errorbar(x, y, dy, fmt="ok")
axhline(1.01305, color="k")
axhline(1, color="k")
axis([0, 1.2, 0.99, 1.06])
xlabel(r"Biggest track cut (/beam energy) (gamgam luminosity)")

savefig("rootstab4_crosssec_ratio_p1.eps")



#####################################################

test_d0close = variable(0., 0.002)
test_chen = variable(0., 1.)
test_neue = variable(0., 1.)

def cuts_d0close(n, val=0.005):
  return abs(n.d0close) < val

def cuts_chen(n, val=0.):
  return n.chen > val

def cuts_neue(n, val=0.):
  return n.neue > val

low.optimize = ["type", "trig", "d0close", "anyz", "p1x", "p1y", "p1z", "run", "coolvisen", "chen", "neue"]
high.optimize = ["type", "trig", "d0close", "anyz", "p1x", "p1y", "p1z", "run", "coolvisen", "chen", "neue"]

counter = 0
for n in low:
  if counter % 10000 == 0:
    print time.asctime(time.localtime(time.time())), counter
  counter += 1

  test_d0close.fill(n, cuts_d0close, 1)
  test_chen.fill(n, cuts_chen, 1)
  test_neue.fill(n, cuts_neue, 1)

counter = 0
for n in high:
  if counter % 10000 == 0:
    print time.asctime(time.localtime(time.time())), counter
  counter += 1

  test_d0close.fill(n, cuts_d0close, 0)
  test_chen.fill(n, cuts_chen, 0)
  test_neue.fill(n, cuts_neue, 0)

pickle.dump(test_d0close, open("rootstab4_d0close.p", "w"))
pickle.dump(test_chen, open("rootstab4_chen.p", "w"))
pickle.dump(test_neue, open("rootstab4_neue.p", "w"))

clf()

subplot(311)
x, y, dy = test_d0close.xydy()
errorbar(x, y, dy, fmt="ok")
axhline(1.01305, color="k")
axhline(1, color="k")
axis([0, 0.002, 0.97, 1.04])
xlabel(r"Closest track to beamspot in XY cut (m)")
title(r"Hadronic cross-section April/March ratio")

subplot(312)
x, y, dy = test_chen.xydy()
errorbar(x, y, dy, fmt="ok")
axhline(1.01305, color="k")
axhline(1, color="k")
axis([0, 1, 0.99, 1.06])
xlabel(r"Charged energy cut (/COM energy)")

subplot(313)
x, y, dy = test_neue.xydy()
errorbar(x, y, dy, fmt="ok")
axhline(1.01305, color="k")
axhline(1, color="k")
axis([0, 1, 1.01, 1.08])
xlabel(r"Neutral energy cut (/COM energy)")

savefig("rootstab4_crosssec_d0chne.eps")




#####################################################

for x in desirable:
  exec("del "+str(x))

def allbutcut(i, n):
  cuts = [int(n.trig) % 10000 % 1000 > 0,   \
          abs(n.d0close) < 0.005,           \
          abs(n.anyz) < 0.075,              \
          sqrt(n.p1x**2+n.p1y**2+n.p1z**2) / runsummary[int(n.run)].energy < 0.8, \
          n.coolvisen > 0.4]

  if i == -1:
    return cuts[0] and cuts[1] and cuts[2] and cuts[3] and cuts[4]

  passcuts = True
  for j in range(4):
    if j != i:
      passcuts = passcuts and cuts[j]
  return passcuts

def trignum(n):
  trig10 = int(n.trig) % 10000 % 1000
  eltrack = trig10 / 100 > 0

  trig10 = trig10 % 100
  radtau = trig10 / 10 > 0

  trig10 = trig10 % 10
  hadron = trig10 > 0

  return eltrack + radtau*2 + hadron*4

import jimtools as jt
histlow_trig = jt.hist(8, -0.5, 7.5)
histlow_d0close = jt.hist(100, -0.0005, 0.0005)
histlow_anyz = jt.hist(100, -0.02, 0.02)
histlow_p1all = jt.hist(120, 0, 1.2)
histlow_p1high = jt.hist(100, 0.9, 1.05)
histlow_p1cosp = jt.hist(100, -1, 1)
histlow_visen = jt.hist(120, 0, 1.2)
histlow_chen = jt.hist(120, 0, 1.2)
histlow_neue = jt.hist(120, 0, 1.2)
histhigh_trig = jt.hist(8, -0.5, 7.5)
histhigh_d0close = jt.hist(100, -0.0005, 0.0005)
histhigh_anyz = jt.hist(100, -0.02, 0.02)
histhigh_p1all = jt.hist(120, 0, 1.2)
histhigh_p1high = jt.hist(100, 0.9, 1.05)
histhigh_p1cosp = jt.hist(100, -1, 1)
histhigh_visen = jt.hist(120, 0, 1.2)
histhigh_chen = jt.hist(120, 0, 1.2)
histhigh_neue = jt.hist(120, 0, 1.2)

def fillemall_low(n):
  global histlow_trig, histlow_d0close, histlow_anyz, histlow_p1all, histlow_p1high, histlow_visen, histlow_chen, histlow_neue 

  if allbutcut(-1, n):
    histlow_trig.fill(trignum(n))

  if allbutcut(1, n):
    histlow_d0close.fill(n.d0close)

  if allbutcut(2, n):
    histlow_anyz.fill(n.anyz)

  if allbutcut(3, n):
    histlow_p1all.fill(sqrt(n.p1x**2+n.p1y**2+n.p1z**2) / runsummary[int(n.run)].energy)
    histlow_p1high.fill(sqrt(n.p1x**2+n.p1y**2+n.p1z**2) / runsummary[int(n.run)].energy)
    if sqrt(n.p1x**2+n.p1y**2+n.p1z**2) / runsummary[int(n.run)].energy > 0.8:
      histlow_p1cosp.fill(n.cosp)

  if allbutcut(4, n):
    histlow_visen.fill(n.coolvisen)
    histlow_chen.fill(n.chen)
    histlow_neue.fill(n.neue)

def fillemall_high(n):
  global histhigh_trig, histhigh_d0close, histhigh_anyz, histhigh_p1all, histhigh_p1high, histhigh_visen, histhigh_chen, histhigh_neue 

  if allbutcut(-1, n):
    histhigh_trig.fill(trignum(n))

  if allbutcut(1, n):
    histhigh_d0close.fill(n.d0close)

  if allbutcut(2, n):
    histhigh_anyz.fill(n.anyz)

  if allbutcut(3, n):
    histhigh_p1all.fill(sqrt(n.p1x**2+n.p1y**2+n.p1z**2) / runsummary[int(n.run)].energy)
    histhigh_p1high.fill(sqrt(n.p1x**2+n.p1y**2+n.p1z**2) / runsummary[int(n.run)].energy)
    if sqrt(n.p1x**2+n.p1y**2+n.p1z**2) / runsummary[int(n.run)].energy > 0.8:
      histhigh_p1cosp.fill(n.cosp)

  if allbutcut(4, n):
    histhigh_visen.fill(n.coolvisen)
    histhigh_chen.fill(n.chen)
    histhigh_neue.fill(n.neue)

test_p1_forward  = variable(0.8, 1.2)
test_p1_backward = variable(0.8, 1.2)

low.optimize = ["type", "trig", "d0close", "anyz", "p1x", "p1y", "p1z", "run", "coolvisen", "cosp", "chen", "neue"]
high.optimize = ["type", "trig", "d0close", "anyz", "p1x", "p1y", "p1z", "run", "coolvisen", "cosp", "chen", "neue"]

def cuts_p1_forward(n, val=0.8):
  return 0.6 < n.cosp < 0.8 and \
         sqrt(n.p1x**2+n.p1y**2+n.p1z**2) / runsummary[int(n.run)].energy < val

def cuts_p1_backward(n, val=0.8):
  return -0.8 < n.cosp < -0.6 and \
         sqrt(n.p1x**2+n.p1y**2+n.p1z**2) / runsummary[int(n.run)].energy < val

def bhabha_limited(n):
  return int(floor(n.type / 100)) % 10 == 1 and 0. < n.cosp < 0.6

numbha_low = 0
numgam_low = 0
numbha_high = 0
numgam_high = 0

counter = 0
for n in low:
  if counter % 10000 == 0:
    print "low", time.asctime(time.localtime(time.time())), counter
  counter += 1

  test_p1_forward.fill(n, cuts_p1_forward, 1, hadfunc=mosthadron, lumifunc=bhabha_limited)
  test_p1_backward.fill(n, cuts_p1_backward, 1, hadfunc=mosthadron, lumifunc=bhabha_limited)

  if bhabha(n):
    numbha_low += 1
  if gamgam(n):
    numgam_low += 1
  fillemall_low(n)

counter = 0
for n in high:
  if counter % 10000 == 0:
    print "high", time.asctime(time.localtime(time.time())), counter
  counter += 1

  test_p1_forward.fill(n, cuts_p1_forward, 0, hadfunc=mosthadron, lumifunc=bhabha_limited)
  test_p1_backward.fill(n, cuts_p1_backward, 0, hadfunc=mosthadron, lumifunc=bhabha_limited)

  if bhabha(n):
    numbha_high += 1
  if gamgam(n):
    numgam_high += 1
  fillemall_high(n)

desirable = ["histlow_trig", "histlow_d0close", "histlow_anyz", "histlow_p1all", "histlow_p1high", "histlow_visen", "histlow_chen", "histlow_neue", "histhigh_trig", "histhigh_d0close", "histhigh_anyz", "histhigh_p1all", "histhigh_p1high", "histhigh_visen", "histhigh_chen", "histhigh_neue", "numbha_low", "numgam_low", "numbha_high", "numgam_high", "test_p1_forward", "test_p1_backward"]
desirable_dictionary = {}
for x in desirable:
  desirable_dictionary[x] = eval(x)
pickle.dump(desirable_dictionary, open("rootstab4_desirable.p", "w"))

clf()

subplot(211)
x, y, dy = test_p1_forward.xydy()
errorbar(x, y, dy, fmt="ok")
axhline(1.01305, color="k")
axhline(1, color="k")
axis([0.8, 1.2, 0.99, 1.06])
xlabel(r"Biggest track cut (/beam energy) (forward (0.6 < cos theta+ < 0.8))")
title(r"Hadronic cross-section April/March ratio (bhabhas are stat. indep.)")

subplot(212)
x, y, dy = test_p1_backward.xydy()
errorbar(x, y, dy, fmt="ok")
axhline(1.01305, color="k")
axhline(1, color="k")
axis([0.8, 1.2, 0.99, 1.06])
xlabel(r"Biggest track cut (/beam energy) (backward (-0.8 < cos theta+ < -0.6))")

savefig("rootstab4_crosssec_ratio_p1forback.eps")

def plotdiff(histhigh, histlow, tit):
  global numgam_high, numgam_low
  histhigh.rootn()
  histlow.rootn()
  diff = (histhigh / numgam_high - histlow / numgam_low)
  x, y, dy = diff.bin_centers(), diff.values, diff.errors
  clf()
  subplot(211)
  errorbar(x, y, dy, fmt="ok")
  axhline(0)
  xlabel(r"April - March difference normalized to equal Gamgams")
  title(tit)
  subplot(212)
  x, y, dy = histhigh.bin_centers(), histhigh.values, histhigh.errors
  errorbar(x, y, dy, fmt="ok")
  xlabel(r"April histogram")

plotdiff(histhigh_trig, histlow_trig, "Trigger")
savefig("rootstab4_plot_trig.eps")
plotdiff(histhigh_d0close, histlow_d0close, "Closest track in XY (m)")
savefig("rootstab4_plot_d0close.eps")
plotdiff(histhigh_anyz, histlow_anyz, "Event vertex in Z (m)")
savefig("rootstab4_plot_anyz.eps")
plotdiff(histhigh_p1all, histlow_p1all, "Biggest track momentum (/ebeam)")
savefig("rootstab4_plot_p1all.eps")
plotdiff(histhigh_p1high, histlow_p1high, "Biggest track momentum (/ebeam, close-up)")
savefig("rootstab4_plot_p1high.eps")
plotdiff(histhigh_p1cosp, histlow_p1cosp, "Cos(theta) of the positive track if biggest track > 0.8 ebeam")
savefig("rootstab4_plot_p1cosp.eps")
plotdiff(histhigh_visen, histlow_visen, "Visible energy (/COM energy)")
savefig("rootstab4_plot_visen.eps")
plotdiff(histhigh_chen, histlow_chen, "Charged energy (/COM energy)")
savefig("rootstab4_plot_chen.eps")
plotdiff(histhigh_neue, histlow_neue, "Neutral energy (/COM energy)")
savefig("rootstab4_plot_neue.eps")

execfile("/home/mccann/bin/python/jimtools.py")
from_rootstab = pickle.load(open("rootstab.p"))
histhigh_tracks = from_rootstab["high_tracks_2"] * 1328741.
histlow_tracks = from_rootstab["low_tracks_2"] * 1897574.
plotdiff(histhigh_tracks, histlow_tracks, "Number of tracks")
savefig("rootstab4_plot_tracks.eps")

##########################################

def twophoton(trig, d0close, anyz, p1x, p1y, p1z, run, coolvisen, tracks):
  return 0.04 < coolvisen < 0.3 and \
         sqrt(p1x**2+p1y**2+p1z**2) / runsummary[int(run)].energy < 0.8 and \
         int(trig) % 10000 % 1000 > 0 and \
         abs(d0close) < 0.005 and \
         tracks > 1

low.filter = twophoton
high.filter = twophoton
low.optimize = ["wpz", "anyz"]
high.optimize = ["wpz", "anyz"]
low.range()
high.range()

lowwpz = hist(300, -1, 1)
lowanyz = hist(300, -0.5, 0.5)
highwpz = hist(300, -1, 1)
highanyz = hist(300, -0.5, 0.5)

print "before", time.asctime(time.localtime(time.time()))
low2pho = 0
high2pho = 0
for n in low:
  lowwpz.fill(n.wpz)
  lowanyz.fill(n.anyz)
  low2pho += 1
for n in high:
  highwpz.fill(n.wpz)
  highanyz.fill(n.anyz)
  high2pho += 1
print "after", time.asctime(time.localtime(time.time()))
low.filter = None
high.filter = None

lowwpz.rootn()
lowanyz.rootn()
highwpz.rootn()
highanyz.rootn()

lowanyz_03 = sum(lowanyz.values[60:240])
highanyz_03 = sum(highanyz.values[60:240])
pickle.dump({"lowwpz": lowwpz, "highwpz": highwpz, "lowanyz": lowanyz, "highanyz": highanyz, "low2pho": low2pho, "high2pho": high2pho, "lowanyz_03": lowanyz_03, "highanyz_03": highanyz_03}, open("rootstab4_twophoton_stuff.p", "w"))

print "low2pho =", low2pho, "and high2pho =", high2pho
print "lowanyz_03 =", lowanyz_03, "and highanyz_03 =", highanyz_03
print "numgam_low =", numgam_low, "and numgam_high =", numgam_high
print "numbha_low =", numbha_low, "and numbha_high =", numbha_high

clf()
subplot(211)
h = lowwpz / numgam_low
x, y, dy = h.bin_centers(), h.values, h.errors
errorbar(x, y, dy, fmt=".k")
h = highwpz / numgam_high
x, y, dy = h.bin_centers(), h.values, h.errors
errorbar(x, y, dy, fmt=".r")
xlabel(r"Net event momentum in Z (/ebeam)")
title(r"Red = April, black = March, normalized to equal gamgams")

subplot(212)
h = lowanyz / numgam_low
x, y, dy = h.bin_centers(), h.values, h.errors
errorbar(x, y, dy, fmt=".k")
h = highanyz / numgam_high
x, y, dy = h.bin_centers(), h.values, h.errors
errorbar(x, y, dy, fmt=".r")
semilogy()
xlabel(r"Z of the event vertex (m)")
axvline(-0.03, color="k")
axvline(0.03, color="k")

savefig(r"rootstab4_twophoton_overlays.eps")

clf()
subplot(211)
h = (highwpz / numgam_high) - (lowwpz / numgam_low)
x, y, dy = h.bin_centers(), h.values, h.errors
errorbar(x, y, dy, fmt=".k")
xlabel(r"Net event momentum in Z (/ebeam)")
title(r"April minus March")

subplot(212)
h = (highanyz / numgam_high) - (lowanyz / numgam_low)
x, y, dy = h.bin_centers(), h.values, h.errors
errorbar(x, y, dy, fmt=".k")
xlabel(r"Z of the event vertex (m)")

savefig(r"rootstab4_twophoton_differences.eps")


##########################################

desirable_dictionary = pickle.load(open("rootstab6_desirable.p"))

histhigh_d0close = desirable_dictionary["histhigh_d0close"]
histhigh_anyz = desirable_dictionary["histhigh_anyz"]
histlow_d0close = desirable_dictionary["histlow_d0close"]
histlow_anyz = desirable_dictionary["histlow_anyz"]
histhoff_d0close = desirable_dictionary["histhoff_d0close"]
histhoff_anyz = desirable_dictionary["histhoff_anyz"]
histloff_d0close = desirable_dictionary["histloff_d0close"]
histloff_anyz = desirable_dictionary["histloff_anyz"]

numgam_high = desirable_dictionary["numgam_high"]
numgam_low = desirable_dictionary["numgam_low"]
numgam_hoff = desirable_dictionary["numgam_hoff"]
numgam_loff = desirable_dictionary["numgam_loff"]

upshigh_d0close = (histhigh_d0close/float(numgam_high) - histhoff_d0close/float(numgam_hoff))
upslow_d0close = (histlow_d0close/float(numgam_low) - histloff_d0close/float(numgam_loff))
upshigh_anyz = (histhigh_anyz/float(numgam_high) - histhoff_anyz/float(numgam_hoff))
upslow_anyz = (histlow_anyz/float(numgam_low) - histloff_anyz/float(numgam_loff))

clf()

subplot(211)
x, y, dy = upshigh_d0close.bin_centers(), upshigh_d0close.values, upshigh_d0close.errors
errorbar(x, y, dy, fmt=".k")
x, y, dy = upslow_d0close.bin_centers(), upslow_d0close.values, upslow_d0close.errors
errorbar(x, y, dy, fmt=".r")
xlabel("Closest track in XY (m)")
title("black = April, red = March")

subplot(212)
x, y, dy = upshigh_anyz.bin_centers(), upshigh_anyz.values, upshigh_anyz.errors
errorbar(x, y, dy, fmt=".k")
x, y, dy = upslow_anyz.bin_centers(), upslow_anyz.values, upslow_anyz.errors
errorbar(x, y, dy, fmt=".r")
xlabel("Event vertex in Z (m)")

savefig("rootstab6_d0closeanyz_widths.eps")
