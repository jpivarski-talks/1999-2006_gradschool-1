from math import *
import rootntuple, cPickle as pickle, time

initialrunlist = pickle.load(open("/home/mccann/synthesis/lumieff/initialrunlist.p"))
mybadruns = [122617, 124363, 124364, 124365, 124368, 124369, 124372, 124373, 124459, 122353, 126341, 129522, 123013, 123014, 121928, 121929, 121953, 127951, 127955, 130278, 121710, 121930, 121944, 121954, 123884, 122331, 122335, 122336, 122339, 122341, 122342, 122344, 122345, 122349, 122350, 122352, 121476, 121748, 121822, 121847, 122685, 123436, 123847, 123873, 124816, 124860, 124862, 125367, 126273, 126329, 127280, 124452, 124454, 124456, 124458, 124462, 124464, 124465, 124466, 124467, 124469, 124472, 124473, 124474, 124475, 124477, 124478, 124479, 124480, 123281, 123411, 121595, 122093, 122330, 126510]

class RunSummary : pass
runsummary = pickle.load(open("/home/mccann/synthesis/lumieff/runsummary.p"))

low_runs = [124684, 124685, 124687, 124688, 124690, 124691, 124699, 124701, 124702, 124704, 124705, 124706, 124707, 124708, 124709, 124712, 124713, 124714, 124716, 124718, 124719, 124720, 124721, 124722, 124725, 124726, 124727, 124728, 124729, 124730, 124731, 124732, 124733, 124734, 124735, 124736]
high_runs = [125360, 125361, 125362, 125363, 125364, 125366, 125368, 125369, 125370, 125372, 125373, 125375, 125377, 125378, 125380, 125382, 125384, 125389, 125391, 125392, 125395, 125396, 125397, 125398, 125399, 125400, 125403, 125404, 125405, 125407, 125408, 125416]

loff_runs = []
hoff_runs = []
for r in initialrunlist:
  if runsummary[r].kind == "c" and r not in mybadruns:
    if 124415 < r < 124948:
      loff_runs.append(r)
    if 124948 < r < 125465:
      hoff_runs.append(r)

def getntuple(run):
  return rootntuple.RootNtuple("/home/mccann/synthesis/root/db_"+str(run)+".root:/UpsilonGammaEEAnalysisProc/nt1")

low = getntuple(low_runs[0])
for r in low_runs[1:]:
  low += getntuple(r)

high = getntuple(high_runs[0])
for r in high_runs[1:]:
  high += getntuple(r)

loff = getntuple(loff_runs[0])
for r in loff_runs[1:]:
  loff += getntuple(r)

hoff = getntuple(hoff_runs[0])
for r in hoff_runs[1:]:
  hoff += getntuple(r)

# ['run', 'event', 'trig', 'type', 'd0close', 'anyz', 'p1x', 'p1y', 'p1z', 'p2x', 'p2y', 'p2z', 'visen', 'coolvisen', 'frozenvisen', 'tracks', 'rawtk', 'oppositesides', 'e1', 'e2', 'e3', 'phi1', 'cos1', 'phi2', 'cos2', 'oppositecharge', 'eisr', 'econstr', 'cosp', 'cosn', 'wpz', 'pdotp', 'ccen', 'neue', 'l4dec', 'chen']

def hadron(n):
  return n.type % 10 == 1

def gamgam(n):
  return int(floor(n.type / 10)) % 10 == 1

def bhabha(n):
  return int(floor(n.type / 100)) % 10 == 1

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
histlow_tracks = jt.hist(19, -0.5, 18.5)
histhigh_trig = jt.hist(8, -0.5, 7.5)
histhigh_d0close = jt.hist(100, -0.0005, 0.0005)
histhigh_anyz = jt.hist(100, -0.02, 0.02)
histhigh_p1all = jt.hist(120, 0, 1.2)
histhigh_p1high = jt.hist(100, 0.9, 1.05)
histhigh_p1cosp = jt.hist(100, -1, 1)
histhigh_visen = jt.hist(120, 0, 1.2)
histhigh_chen = jt.hist(120, 0, 1.2)
histhigh_neue = jt.hist(120, 0, 1.2)
histhigh_tracks = jt.hist(19, -0.5, 18.5)
histloff_trig = jt.hist(8, -0.5, 7.5)
histloff_d0close = jt.hist(100, -0.0005, 0.0005)
histloff_anyz = jt.hist(100, -0.02, 0.02)
histloff_p1all = jt.hist(120, 0, 1.2)
histloff_p1high = jt.hist(100, 0.9, 1.05)
histloff_p1cosp = jt.hist(100, -1, 1)
histloff_visen = jt.hist(120, 0, 1.2)
histloff_chen = jt.hist(120, 0, 1.2)
histloff_neue = jt.hist(120, 0, 1.2)
histloff_tracks = jt.hist(19, -0.5, 18.5)
histhoff_trig = jt.hist(8, -0.5, 7.5)
histhoff_d0close = jt.hist(100, -0.0005, 0.0005)
histhoff_anyz = jt.hist(100, -0.02, 0.02)
histhoff_p1all = jt.hist(120, 0, 1.2)
histhoff_p1high = jt.hist(100, 0.9, 1.05)
histhoff_p1cosp = jt.hist(100, -1, 1)
histhoff_visen = jt.hist(120, 0, 1.2)
histhoff_chen = jt.hist(120, 0, 1.2)
histhoff_neue = jt.hist(120, 0, 1.2)
histhoff_tracks = jt.hist(19, -0.5, 18.5)

def fillemall_low(n):
  global histlow_trig, histlow_d0close, histlow_anyz, histlow_p1all, histlow_p1high, histlow_visen, histlow_chen, histlow_neue 

  if allbutcut(-1, n):
    histlow_trig.fill(trignum(n))
    histlow_tracks.fill(n.tracks)

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
    histhigh_tracks.fill(n.tracks)

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

def fillemall_loff(n):
  global histloff_trig, histloff_d0close, histloff_anyz, histloff_p1all, histloff_p1high, histloff_visen, histloff_chen, histloff_neue 

  if allbutcut(-1, n):
    histloff_trig.fill(trignum(n))
    histloff_tracks.fill(n.tracks)

  if allbutcut(1, n):
    histloff_d0close.fill(n.d0close)

  if allbutcut(2, n):
    histloff_anyz.fill(n.anyz)

  if allbutcut(3, n):
    histloff_p1all.fill(sqrt(n.p1x**2+n.p1y**2+n.p1z**2) / runsummary[int(n.run)].energy)
    histloff_p1high.fill(sqrt(n.p1x**2+n.p1y**2+n.p1z**2) / runsummary[int(n.run)].energy)
    if sqrt(n.p1x**2+n.p1y**2+n.p1z**2) / runsummary[int(n.run)].energy > 0.8:
      histloff_p1cosp.fill(n.cosp)

  if allbutcut(4, n):
    histloff_visen.fill(n.coolvisen)
    histloff_chen.fill(n.chen)
    histloff_neue.fill(n.neue)

def fillemall_hoff(n):
  global histhoff_trig, histhoff_d0close, histhoff_anyz, histhoff_p1all, histhoff_p1high, histhoff_visen, histhoff_chen, histhoff_neue 

  if allbutcut(-1, n):
    histhoff_trig.fill(trignum(n))
    histhoff_tracks.fill(n.tracks)

  if allbutcut(1, n):
    histhoff_d0close.fill(n.d0close)

  if allbutcut(2, n):
    histhoff_anyz.fill(n.anyz)

  if allbutcut(3, n):
    histhoff_p1all.fill(sqrt(n.p1x**2+n.p1y**2+n.p1z**2) / runsummary[int(n.run)].energy)
    histhoff_p1high.fill(sqrt(n.p1x**2+n.p1y**2+n.p1z**2) / runsummary[int(n.run)].energy)
    if sqrt(n.p1x**2+n.p1y**2+n.p1z**2) / runsummary[int(n.run)].energy > 0.8:
      histhoff_p1cosp.fill(n.cosp)

  if allbutcut(4, n):
    histhoff_visen.fill(n.coolvisen)
    histhoff_chen.fill(n.chen)
    histhoff_neue.fill(n.neue)

low.optimize = ["type", "trig", "d0close", "anyz", "p1x", "p1y", "p1z", "run", "coolvisen", "cosp", "chen", "neue", "tracks"]
high.optimize = ["type", "trig", "d0close", "anyz", "p1x", "p1y", "p1z", "run", "coolvisen", "cosp", "chen", "neue", "tracks"]
loff.optimize = ["type", "trig", "d0close", "anyz", "p1x", "p1y", "p1z", "run", "coolvisen", "cosp", "chen", "neue", "tracks"]
hoff.optimize = ["type", "trig", "d0close", "anyz", "p1x", "p1y", "p1z", "run", "coolvisen", "cosp", "chen", "neue", "tracks"]

low.range()
high.range()
loff.range()
hoff.range()

numbha_low = 0
numgam_low = 0
numbha_high = 0
numgam_high = 0
numbha_loff = 0
numgam_loff = 0
numbha_hoff = 0
numgam_hoff = 0

counter = 0
for n in low:
  if counter % 10000 == 0:
    print "low", time.asctime(time.localtime(time.time())), counter
  counter += 1

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

  if bhabha(n):
    numbha_high += 1
  if gamgam(n):
    numgam_high += 1
  fillemall_high(n)

counter = 0
for n in loff:
  if counter % 10000 == 0:
    print "loff", time.asctime(time.localtime(time.time())), counter
  counter += 1

  if bhabha(n):
    numbha_loff += 1
  if gamgam(n):
    numgam_loff += 1
  fillemall_loff(n)

counter = 0
for n in hoff:
  if counter % 10000 == 0:
    print "hoff", time.asctime(time.localtime(time.time())), counter
  counter += 1

  if bhabha(n):
    numbha_hoff += 1
  if gamgam(n):
    numgam_hoff += 1
  fillemall_hoff(n)

desirable = ["histlow_trig", "histlow_d0close", "histlow_anyz", "histlow_p1all", "histlow_p1high", "histlow_visen", "histlow_chen", "histlow_neue", "histlow_tracks", "histhigh_trig", "histhigh_d0close", "histhigh_anyz", "histhigh_p1all", "histhigh_p1high", "histhigh_visen", "histhigh_chen", "histhigh_neue", "histhigh_tracks", "histloff_trig", "histloff_d0close", "histloff_anyz", "histloff_p1all", "histloff_p1high", "histloff_visen", "histloff_chen", "histloff_neue", "histloff_tracks", "histhoff_trig", "histhoff_d0close", "histhoff_anyz", "histhoff_p1all", "histhoff_p1high", "histhoff_visen", "histhoff_chen", "histhoff_neue", "histhoff_tracks", "numbha_low", "numgam_low", "numbha_high", "numgam_high", "numbha_loff", "numgam_loff", "numbha_hoff", "numgam_hoff"]
desirable_dictionary = {}
for x in desirable:
  desirable_dictionary[x] = eval(x)
pickle.dump(desirable_dictionary, open("rootstab6_desirable.p", "w"))

def plotdiff(histhigh, histlow, histhoff, histloff, tit):
  global numgam_high, numgam_low, numgam_hoff, numgam_loff
  histhigh.rootn()
  histlow.rootn()
  histhoff.rootn()
  histloff.rootn()

  upshigh = histhigh/float(numgam_high) - histhoff/float(numgam_hoff)
  upslow = histlow/float(numgam_low) - histloff/float(numgam_loff)
  diff = upshigh - upslow

  clf()
  subplot(211)
  x, y, dy = diff.bin_centers(), diff.values, diff.errors
  errorbar(x, y, dy, fmt=".k")
  axhline(0)
  xlabel(r"April - March difference of Upsilons (gg cont subtr)")
  title(tit)
  subplot(212)
  x, y, dy = upshigh.bin_centers(), upshigh.values, upshigh.errors
  errorbar(x, y, dy, fmt=".k")
  axhline(0)
  xlabel(r"April only (divided by num gamgams)")

plotdiff(histhigh_trig, histlow_trig, histhoff_trig, histloff_trig, "Trigger")
savefig("rootstab6_plot_trig.eps")
plotdiff(histhigh_d0close, histlow_d0close, histhoff_d0close, histloff_d0close, "Closest track in XY (m)")
savefig("rootstab6_plot_d0close.eps")
plotdiff(histhigh_anyz, histlow_anyz, histhoff_anyz, histloff_anyz, "Event vertex in Z (m)")
savefig("rootstab6_plot_anyz.eps")
plotdiff(histhigh_p1all, histlow_p1all, histhoff_p1all, histloff_p1all, "Biggest track momentum (/ebeam)")
savefig("rootstab6_plot_p1all.eps")
plotdiff(histhigh_p1high, histlow_p1high, histhoff_p1high, histloff_p1high, "Biggest track momentum (/ebeam, close-up)")
savefig("rootstab6_plot_p1high.eps")
plotdiff(histhigh_p1cosp, histlow_p1cosp, histhoff_p1cosp, histloff_p1cosp, "Cos(theta) of the positive track if biggest track > 0.8 ebeam")
savefig("rootstab6_plot_p1cosp.eps")
plotdiff(histhigh_visen, histlow_visen, histhoff_visen, histloff_visen, "Visible energy (/COM energy)")
savefig("rootstab6_plot_visen.eps")
plotdiff(histhigh_chen, histlow_chen, histhoff_chen, histloff_chen, "Charged energy (/COM energy)")
savefig("rootstab6_plot_chen.eps")
plotdiff(histhigh_neue, histlow_neue, histhoff_neue, histloff_neue, "Neutral energy (/COM energy)")
savefig("rootstab6_plot_neue.eps")
plotdiff(histhigh_tracks, histlow_tracks, histhoff_tracks, histloff_tracks, "Number of tracks")
savefig("rootstab6_plot_tracks.eps")

def intdiff(histhigh, histlow, histhoff, histloff, low, high):
  global numgam_high, numgam_low, numgam_hoff, numgam_loff
  histhigh.rootn()
  histlow.rootn()
  histhoff.rootn()
  histloff.rootn()

  upshigh = histhigh/float(numgam_high) - histhoff/float(numgam_hoff)
  upslow = histlow/float(numgam_low) - histloff/float(numgam_loff)
  diff = upshigh - upslow

  dooverunder = False
  if low == high:
    il = 0
    ih = len(diff.values)
    dooverunder = True
  elif type(low) == int and type(high) == int:
    il = low
    ih = high
  else:
    il = int(round((low - diff.low)/(diff.high - diff.low)*diff.bins))
    ih = int(round((high - diff.low)/(diff.high - diff.low)*diff.bins))
  vals = diff.values[il:ih]
  errs = diff.errors[il:ih]

  thesum = reduce(lambda a, b: a+b, vals)
  theerr = reduce(lambda a, b: sqrt(a**2+b**2), errs)

  if dooverunder:
    thesum += diff.overflow + diff.underflow
    theerr = sqrt(theerr**2 + diff.overflow_error**2 + diff.underflow_error**2)
    print "underflow = %6.3f +/- %5.3f, overflow = %6.3f +/- %5.3f" % (diff.underflow, diff.underflow_error, diff.overflow, diff.overflow_error)

  print "From %d to %d is %6.3f +/- %5.3f" % (il, ih, thesum, theerr)

def inthigh(histhigh, histlow, histhoff, histloff, low, high):
  global numgam_high, numgam_low, numgam_hoff, numgam_loff
  histhigh.rootn()
  histlow.rootn()
  histhoff.rootn()
  histloff.rootn()

  upshigh = histhigh/float(numgam_high) - histhoff/float(numgam_hoff)
  upslow = histlow/float(numgam_low) - histloff/float(numgam_loff)
  diff = upshigh

  dooverunder = False
  if low == high:
    il = 0
    ih = len(diff.values)
    dooverunder = True
  elif type(low) == int and type(high) == int:
    il = low
    ih = high
  else:
    il = int(round((low - diff.low)/(diff.high - diff.low)*diff.bins))
    ih = int(round((high - diff.low)/(diff.high - diff.low)*diff.bins))
  vals = diff.values[il:ih]
  errs = diff.errors[il:ih]

  thesum = reduce(lambda a, b: a+b, vals)
  theerr = reduce(lambda a, b: sqrt(a**2+b**2), errs)

  if dooverunder:
    thesum += diff.overflow + diff.underflow
    theerr = sqrt(theerr**2 + diff.overflow_error**2 + diff.underflow_error**2)
    print "underflow = %6.3f +/- %5.3f, overflow = %6.3f +/- %5.3f" % (diff.underflow, diff.underflow_error, diff.overflow, diff.overflow_error)

  print "From %d to %d is %6.3f +/- %5.3f" % (il, ih, thesum, theerr)

intdiff(histhigh_trig, histlow_trig, histhoff_trig, histloff_trig, -1, -1)
intdiff(histhigh_d0close, histlow_d0close, histhoff_d0close, histloff_d0close, -0.0005, 0.0005)
intdiff(histhigh_anyz, histlow_anyz, histhoff_anyz, histloff_anyz, -1, -1)
intdiff(histhigh_p1all, histlow_p1all, histhoff_p1all, histloff_p1all, 0., 0.8)
intdiff(histhigh_p1all, histlow_p1all, histhoff_p1all, histloff_p1all, 0.8, 1.2)

intdiff(histhigh_p1high, histlow_p1high, histhoff_p1high, histloff_p1high, )
intdiff(histhigh_p1cosp, histlow_p1cosp, histhoff_p1cosp, histloff_p1cosp, )

intdiff(histhigh_visen, histlow_visen, histhoff_visen, histloff_visen, 0.4, 0.95)
intdiff(histhigh_visen, histlow_visen, histhoff_visen, histloff_visen, 0.95, 1.2)

intdiff(histhigh_chen, histlow_chen, histhoff_chen, histloff_chen, 0.4, 0.95)
intdiff(histhigh_chen, histlow_chen, histhoff_chen, histloff_chen, 0.95, 1.2)


intdiff(histhigh_neue, histlow_neue, histhoff_neue, histloff_neue, )

intdiff(histhigh_tracks, histlow_tracks, histhoff_tracks, histloff_tracks, 0, 5)
intdiff(histhigh_tracks, histlow_tracks, histhoff_tracks, histloff_tracks, 5, -1)

inthigh(histhigh_tracks, histlow_tracks, histhoff_tracks, histloff_tracks, 0, 5)
inthigh(histhigh_tracks, histlow_tracks, histhoff_tracks, histloff_tracks, 5, -1)


upshigh_chen = (histhigh_chen/float(numbha_high) - histhoff_chen/float(numbha_hoff))
upslow_chen = (histlow_chen/float(numbha_low) - histloff_chen/float(numbha_loff))



clf()
subplot(311)
x, y, dy = upshigh_chen.bin_centers(), upshigh_chen.values, upshigh_chen.errors
errorbar(x, y, dy, fmt=".k")
x, y, dy = upslow_chen.bin_centers(), upslow_chen.values, upslow_chen.errors
errorbar(x, y, dy, fmt=".r")
axhline(0)
title("Charged energy (/COM), black=April, red=March")

subplot(312)
x, y, dy = upshigh_chen.bin_centers(), upshigh_chen.values, upshigh_chen.errors
errorbar(x, y, dy, fmt=".k")
x, y, dy = upslow_chen.bin_centers(), upslow_chen.values, upslow_chen.errors
errorbar(x, y, dy, fmt=".r")
axhline(0)

subplot(313)
x, y, dy = upshigh_chen.bin_centers(), upshigh_chen.values, upshigh_chen.errors
errorbar(x, y, dy, fmt=".k")
x, y, dy = upslow_chen.bin_centers(), upslow_chen.values, upslow_chen.errors
errorbar(x, y, dy, fmt=".r")
axhline(0)

savefig("rootstab6_chen_byhand.eps")

####################################################

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
histlow_d0close = jt.hist(70, -7, 0)
histlow_anyz = jt.hist(70, -7, 0)
histhigh_d0close = jt.hist(70, -7, 0)
histhigh_anyz = jt.hist(70, -7, 0)
histloff_d0close = jt.hist(70, -7, 0)
histloff_anyz = jt.hist(70, -7, 0)
histhoff_d0close = jt.hist(70, -7, 0)
histhoff_anyz = jt.hist(70, -7, 0)

def fillemall_low(n):
  global histlow_d0close, histlow_anyz

  if allbutcut(1, n):
    histlow_d0close.fill(log10(abs(n.d0close)))

  if allbutcut(2, n):
    histlow_anyz.fill(log10(abs(n.anyz)))

def fillemall_high(n):
  global histhigh_d0close, histhigh_anyz

  if allbutcut(1, n):
    histhigh_d0close.fill(log10(abs(n.d0close)))

  if allbutcut(2, n):
    histhigh_anyz.fill(log10(abs(n.anyz)))

def fillemall_loff(n):
  global histloff_d0close, histloff_anyz

  if allbutcut(1, n):
    histloff_d0close.fill(log10(abs(n.d0close)))

  if allbutcut(2, n):
    histloff_anyz.fill(log10(abs(n.anyz)))

def fillemall_hoff(n):
  global histhoff_d0close, histhoff_anyz

  if allbutcut(1, n):
    histhoff_d0close.fill(log10(abs(n.d0close)))

  if allbutcut(2, n):
    histhoff_anyz.fill(log10(abs(n.anyz)))

low.optimize = ["type", "trig", "d0close", "anyz", "p1x", "p1y", "p1z", "run", "coolvisen"]
high.optimize = ["type", "trig", "d0close", "anyz", "p1x", "p1y", "p1z", "run", "coolvisen"]
loff.optimize = ["type", "trig", "d0close", "anyz", "p1x", "p1y", "p1z", "run", "coolvisen"]
hoff.optimize = ["type", "trig", "d0close", "anyz", "p1x", "p1y", "p1z", "run", "coolvisen"]

low.range()
high.range()
loff.range()
hoff.range()

numbha_low = 0
numgam_low = 0
numbha_high = 0
numgam_high = 0
numbha_loff = 0
numgam_loff = 0
numbha_hoff = 0
numgam_hoff = 0

counter = 0
for n in low:
  if counter % 10000 == 0:
    print "low", time.asctime(time.localtime(time.time())), counter
  counter += 1

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

  if bhabha(n):
    numbha_high += 1
  if gamgam(n):
    numgam_high += 1
  fillemall_high(n)

counter = 0
for n in loff:
  if counter % 10000 == 0:
    print "loff", time.asctime(time.localtime(time.time())), counter
  counter += 1

  if bhabha(n):
    numbha_loff += 1
  if gamgam(n):
    numgam_loff += 1
  fillemall_loff(n)

counter = 0
for n in hoff:
  if counter % 10000 == 0:
    print "hoff", time.asctime(time.localtime(time.time())), counter
  counter += 1

  if bhabha(n):
    numbha_hoff += 1
  if gamgam(n):
    numgam_hoff += 1
  fillemall_hoff(n)

desirable2 = ["histlow_trig", "histlow_d0close", "histlow_anyz", "histhigh_d0close", "histhigh_anyz", "histloff_d0close", "histloff_anyz", "histhoff_d0close", "histhoff_anyz", "numbha_low", "numgam_low", "numbha_high", "numgam_high", "numbha_loff", "numgam_loff", "numbha_hoff", "numgam_hoff"]
desirable2_dictionary = {}
for x in desirable2:
  desirable2_dictionary[x] = eval(x)
pickle.dump(desirable2_dictionary, open("rootstab6_desirable2.p", "w"))

def plotdiff(histhigh, histlow, histhoff, histloff, tit):
  global numgam_high, numgam_low, numgam_hoff, numgam_loff
  histhigh.rootn()
  histlow.rootn()
  histhoff.rootn()
  histloff.rootn()

  upshigh = histhigh/float(numgam_high) - histhoff/float(numgam_hoff)
  upslow = histlow/float(numgam_low) - histloff/float(numgam_loff)
  diff = upshigh - upslow

  clf()
  subplot(211)
  x, y, dy = diff.bin_centers(), diff.values, diff.errors
  errorbar(x, y, dy, fmt=".k")
  axhline(0)
  xlabel(r"April - March difference of Upsilons (gg cont subtr)")
  title(tit)
  subplot(212)
  x, y, dy = upshigh.bin_centers(), upshigh.values, upshigh.errors
  errorbar(x, y, dy, fmt=".k")
  axhline(0)
  xlabel(r"April only (divided by num gamgams)")

plotdiff(histhigh_d0close, histlow_d0close, histhoff_d0close, histloff_d0close, "Closest track in XY (m)")
savefig("rootstab6_plot_d0close2.eps")
plotdiff(histhigh_anyz, histlow_anyz, histhoff_anyz, histloff_anyz, "Event vertex in Z (m)")
savefig("rootstab6_plot_anyz2.eps")

##################################################

def plotdiff(histhigh, histlow, histhoff, histloff, tit):
  global numbha_high, numbha_low, numbha_hoff, numbha_loff
  histhigh.rootn()
  histlow.rootn()
  histhoff.rootn()
  histloff.rootn()

  upshigh = histhigh/float(numbha_high) - histhoff/float(numbha_hoff)
  upslow = histlow/float(numbha_low) - histloff/float(numbha_loff)
  diff = upshigh - upslow

  clf()
  subplot(211)
  x, y, dy = diff.bin_centers(), diff.values, diff.errors
  errorbar(x, y, dy, fmt=".k")
  axhline(0)
  xlabel(r"April - March difference of Upsilons (Bhabha cont subtr)")
  title(tit)
  subplot(212)
  x, y, dy = upshigh.bin_centers(), upshigh.values, upshigh.errors
  errorbar(x, y, dy, fmt=".k")
  axhline(0)
  xlabel(r"April only (divided by num bhabhas)")

plotdiff(histhigh_trig, histlow_trig, histhoff_trig, histloff_trig, "Trigger")
savefig("rootstab6_plotbb_trig.eps")
plotdiff(histhigh_d0close, histlow_d0close, histhoff_d0close, histloff_d0close, "Closest track in XY (m)")
savefig("rootstab6_plotbb_d0close.eps")
plotdiff(histhigh_anyz, histlow_anyz, histhoff_anyz, histloff_anyz, "Event vertex in Z (m)")
savefig("rootstab6_plotbb_anyz.eps")
plotdiff(histhigh_p1all, histlow_p1all, histhoff_p1all, histloff_p1all, "Biggest track momentum (/ebeam)")
savefig("rootstab6_plotbb_p1all.eps")
plotdiff(histhigh_p1high, histlow_p1high, histhoff_p1high, histloff_p1high, "Biggest track momentum (/ebeam, close-up)")
savefig("rootstab6_plotbb_p1high.eps")
plotdiff(histhigh_p1cosp, histlow_p1cosp, histhoff_p1cosp, histloff_p1cosp, "Cos(theta) of the positive track if biggest track > 0.8 ebeam")
savefig("rootstab6_plotbb_p1cosp.eps")
plotdiff(histhigh_visen, histlow_visen, histhoff_visen, histloff_visen, "Visible energy (/COM energy)")
savefig("rootstab6_plotbb_visen.eps")
plotdiff(histhigh_chen, histlow_chen, histhoff_chen, histloff_chen, "Charged energy (/COM energy)")
savefig("rootstab6_plotbb_chen.eps")
plotdiff(histhigh_neue, histlow_neue, histhoff_neue, histloff_neue, "Neutral energy (/COM energy)")
savefig("rootstab6_plotbb_neue.eps")
plotdiff(histhigh_tracks, histlow_tracks, histhoff_tracks, histloff_tracks, "Number of tracks")
savefig("rootstab6_plotbb_tracks.eps")



def intdiff(histhigh, histlow, histhoff, histloff, low, high):
  global numbha_high, numbha_low, numbha_hoff, numbha_loff
  histhigh.rootn()
  histlow.rootn()
  histhoff.rootn()
  histloff.rootn()

  upshigh = histhigh/float(numbha_high) - histhoff/float(numbha_hoff)
  upslow = histlow/float(numbha_low) - histloff/float(numbha_loff)
  diff = upshigh - upslow

  dooverunder = False
  if low == high:
    il = 0
    ih = len(diff.values)
    dooverunder = True
  elif type(low) == int and type(high) == int:
    il = low
    ih = high
  else:
    il = int(round((low - diff.low)/(diff.high - diff.low)*diff.bins))
    ih = int(round((high - diff.low)/(diff.high - diff.low)*diff.bins))
  vals = diff.values[il:ih]
  errs = diff.errors[il:ih]

  thesum = reduce(lambda a, b: a+b, vals)
  theerr = reduce(lambda a, b: sqrt(a**2+b**2), errs)

  if dooverunder:
    thesum += diff.overflow + diff.underflow
    theerr = sqrt(theerr**2 + diff.overflow_error**2 + diff.underflow_error**2)
    print "underflow = %6.3f +/- %5.3f, overflow = %6.3f +/- %5.3f" % (diff.underflow, diff.underflow_error, diff.overflow, diff.overflow_error)

  print "From %d to %d is %6.3f +/- %5.3f" % (il, ih, thesum, theerr)

def inthigh(histhigh, histlow, histhoff, histloff, low, high):
  global numbha_high, numbha_low, numbha_hoff, numbha_loff
  histhigh.rootn()
  histlow.rootn()
  histhoff.rootn()
  histloff.rootn()

  upshigh = histhigh/float(numbha_high) - histhoff/float(numbha_hoff)
  upslow = histlow/float(numbha_low) - histloff/float(numbha_loff)
  diff = upshigh

  dooverunder = False
  if low == high:
    il = 0
    ih = len(diff.values)
    dooverunder = True
  elif type(low) == int and type(high) == int:
    il = low
    ih = high
  else:
    il = int(round((low - diff.low)/(diff.high - diff.low)*diff.bins))
    ih = int(round((high - diff.low)/(diff.high - diff.low)*diff.bins))
  vals = diff.values[il:ih]
  errs = diff.errors[il:ih]

  thesum = reduce(lambda a, b: a+b, vals)
  theerr = reduce(lambda a, b: sqrt(a**2+b**2), errs)

  if dooverunder:
    thesum += diff.overflow + diff.underflow
    theerr = sqrt(theerr**2 + diff.overflow_error**2 + diff.underflow_error**2)
    print "underflow = %6.3f +/- %5.3f, overflow = %6.3f +/- %5.3f" % (diff.underflow, diff.underflow_error, diff.overflow, diff.overflow_error)

  print "From %d to %d is %6.3f +/- %5.3f" % (il, ih, thesum, theerr)

intdiff(histhigh_tracks, histlow_tracks, histhoff_tracks, histloff_tracks, 0, 5)
intdiff(histhigh_tracks, histlow_tracks, histhoff_tracks, histloff_tracks, 5, -1)

inthigh(histhigh_tracks, histlow_tracks, histhoff_tracks, histloff_tracks, 0, 5)
inthigh(histhigh_tracks, histlow_tracks, histhoff_tracks, histloff_tracks, 5, -1)

intdiff(histhigh_tracks, histlow_tracks, histhoff_tracks, histloff_tracks, -1, -1)
inthigh(histhigh_tracks, histlow_tracks, histhoff_tracks, histloff_tracks, -1, -1)

print ((histhigh_chen/float(numbha_high) - histhoff_chen/float(numbha_hoff)) - (histlow_chen/float(numbha_low) - histloff_chen/float(numbha_loff))).values[100]
print ((histhigh_chen/float(numbha_high) - histhoff_chen/float(numbha_hoff)) - (histlow_chen/float(numbha_low) - histloff_chen/float(numbha_loff))).errors[100]

print ((histhigh_chen/float(numbha_high) - histhoff_chen/float(numbha_hoff))).values[100]
print ((histhigh_chen/float(numbha_high) - histhoff_chen/float(numbha_hoff))).errors[100]


###################################################

desirable_dictionary = pickle.load(open("/home/mccann/synthesis/rootstab/rootstab6_desirable.p"))
histlow_trig = desirable_dictionary["histlow_trig"]
histlow_d0close = desirable_dictionary["histlow_d0close"]
histlow_anyz = desirable_dictionary["histlow_anyz"]
histlow_p1all = desirable_dictionary["histlow_p1all"]
histlow_p1high = desirable_dictionary["histlow_p1high"]
histlow_visen = desirable_dictionary["histlow_visen"]
histlow_chen = desirable_dictionary["histlow_chen"]
histlow_neue = desirable_dictionary["histlow_neue"]
histlow_tracks = desirable_dictionary["histlow_tracks"]
histhigh_trig = desirable_dictionary["histhigh_trig"]
histhigh_d0close = desirable_dictionary["histhigh_d0close"]
histhigh_anyz = desirable_dictionary["histhigh_anyz"]
histhigh_p1all = desirable_dictionary["histhigh_p1all"]
histhigh_p1high = desirable_dictionary["histhigh_p1high"]
histhigh_visen = desirable_dictionary["histhigh_visen"]
histhigh_chen = desirable_dictionary["histhigh_chen"]
histhigh_neue = desirable_dictionary["histhigh_neue"]
histhigh_tracks = desirable_dictionary["histhigh_tracks"]
histloff_trig = desirable_dictionary["histloff_trig"]
histloff_d0close = desirable_dictionary["histloff_d0close"]
histloff_anyz = desirable_dictionary["histloff_anyz"]
histloff_p1all = desirable_dictionary["histloff_p1all"]
histloff_p1high = desirable_dictionary["histloff_p1high"]
histloff_visen = desirable_dictionary["histloff_visen"]
histloff_chen = desirable_dictionary["histloff_chen"]
histloff_neue = desirable_dictionary["histloff_neue"]
histloff_tracks = desirable_dictionary["histloff_tracks"]
histhoff_trig = desirable_dictionary["histhoff_trig"]
histhoff_d0close = desirable_dictionary["histhoff_d0close"]
histhoff_anyz = desirable_dictionary["histhoff_anyz"]
histhoff_p1all = desirable_dictionary["histhoff_p1all"]
histhoff_p1high = desirable_dictionary["histhoff_p1high"]
histhoff_visen = desirable_dictionary["histhoff_visen"]
histhoff_chen = desirable_dictionary["histhoff_chen"]
histhoff_neue = desirable_dictionary["histhoff_neue"]
histhoff_tracks = desirable_dictionary["histhoff_tracks"]
numbha_low = desirable_dictionary["numbha_low"]
numgam_low = desirable_dictionary["numgam_low"]
numbha_high = desirable_dictionary["numbha_high"]
numgam_high = desirable_dictionary["numgam_high"]
numbha_loff = desirable_dictionary["numbha_loff"]
numgam_loff = desirable_dictionary["numgam_loff"]
numbha_hoff = desirable_dictionary["numbha_hoff"]
numgam_hoff = desirable_dictionary["numgam_hoff"]

theexcess = sum((histhigh_trig/float(numbha_high) - histlow_trig/float(numbha_low)).values)
thetotal = sum((histhigh_trig/float(numbha_high) - histhoff_trig/float(numbha_hoff)).values)

def plotdiff(histhigh, histlow, histhoff, histloff, tit):
  global numbha_high, numbha_low, numbha_hoff, numbha_loff
  histhigh.rootn()
  histlow.rootn()
  histhoff.rootn()
  histloff.rootn()

  upshigh = histhigh/float(numbha_high) - histhoff/float(numbha_hoff)
  upslow = histlow/float(numbha_low) - histloff/float(numbha_loff)
  diff = histhigh/float(numbha_high) - histlow/float(numbha_low)

  clf()
  subplot(311)
  x, y, dy = diff.bin_centers(), diff.values, diff.errors
  errorbar(x, y, dy, fmt=".k")
  axhline(0)
  xlabel(r"April - March difference of Upsilons (implicit cont subtr)")
  title(tit)
  subplot(312)
  x, y, dy = upshigh.bin_centers(), upshigh.values, upshigh.errors
  errorbar(x, y, dy, fmt=".k")
  axhline(0)
  xlabel(r"April only (divided by num bhabhas)")
  subplot(313)
  x, y, dy = upshigh.bin_centers(), upshigh.values, upshigh.errors
  errorbar(x, y, dy, fmt=".k")
  expanddiff = diff * (1.*thetotal/theexcess)
  x, y, dy = expanddiff.bin_centers(), expanddiff.values, expanddiff.errors
  errorbar(x, y, dy, fmt=".r")
  axhline(0)
  xlabel(r"Overlay of the two")

plotdiff(histhigh_trig, histlow_trig, histhoff_trig, histloff_trig, "Trigger")
savefig("rootstab6_plotimp_trig.eps")
plotdiff(histhigh_p1all, histlow_p1all, histhoff_p1all, histloff_p1all, "Biggest track momentum (/ebeam)")
savefig("rootstab6_plotimp_p1all.eps")
plotdiff(histhigh_p1high, histlow_p1high, histhoff_p1high, histloff_p1high, "Biggest track momentum (/ebeam, close-up)")
savefig("rootstab6_plotimp_p1high.eps")
plotdiff(histhigh_p1cosp, histlow_p1cosp, histhoff_p1cosp, histloff_p1cosp, "Cos(theta) of the positive track if biggest track > 0.8 ebeam")
savefig("rootstab6_plotimp_p1cosp.eps")
plotdiff(histhigh_visen, histlow_visen, histhoff_visen, histloff_visen, "Visible energy (/COM energy)")
savefig("rootstab6_plotimp_visen.eps")
plotdiff(histhigh_chen, histlow_chen, histhoff_chen, histloff_chen, "Charged energy (/COM energy)")
savefig("rootstab6_plotimp_chen.eps")
plotdiff(histhigh_neue, histlow_neue, histhoff_neue, histloff_neue, "Neutral energy (/COM energy)")
savefig("rootstab6_plotimp_neue.eps")
plotdiff(histhigh_tracks, histlow_tracks, histhoff_tracks, histloff_tracks, "Number of tracks")
savefig("rootstab6_plotimp_tracks.eps")

######################################################

import jimtools as jt
histlow_ccenpeak = None
histhigh_ccenpeak = jt.hist(120, 0, 1.2)
histloff_ccenpeak = None
histhoff_ccenpeak = jt.hist(120, 0, 1.2)

def hadron_peak(type, chen):
  return type % 10 == 1 and chen > 0.98

print "zero", time.asctime(time.localtime(time.time()))
histhigh_ccenpeak.ntuple(high, "ccen", hadron_peak)
print "one", time.asctime(time.localtime(time.time()))
histhoff_ccenpeak.ntuple(hoff, "ccen", hadron_peak)
print "two", time.asctime(time.localtime(time.time()))

desirable_dictionary = pickle.load(open("/home/mccann/synthesis/rootstab/rootstab6_desirable.p"))
numbha_low = desirable_dictionary["numbha_low"]
numgam_low = desirable_dictionary["numgam_low"]
numbha_high = desirable_dictionary["numbha_high"]
numgam_high = desirable_dictionary["numgam_high"]
numbha_loff = desirable_dictionary["numbha_loff"]
numgam_loff = desirable_dictionary["numgam_loff"]
numbha_hoff = desirable_dictionary["numbha_hoff"]
numgam_hoff = desirable_dictionary["numgam_hoff"]

def plotdiff(histhigh, histlow, histhoff, histloff, tit):
  global numbha_high, numbha_low, numbha_hoff, numbha_loff

  upshigh = histhigh/float(numbha_high) - histhoff/float(numbha_hoff)
#   upslow = histlow/float(numbha_low) - histloff/float(numbha_loff)
#   diff = upshigh - upslow

  clf()
#   subplot(211)
#   x, y, dy = diff.bin_centers(), diff.values, diff.errors
#   errorbar(x, y, dy, fmt=".k")
#   axhline(0)
#   xlabel(r"April - March difference of Upsilons (Bhabha cont subtr)")
  title(tit)
#  subplot(212)
  x, y, dy = upshigh.bin_centers(), upshigh.values, upshigh.errors
  errorbar(x, y, dy, fmt=".k")
  axhline(0)
  xlabel(r"April only (divided by num bhabhas)")

plotdiff(histhigh_ccenpeak, histlow_ccenpeak, histhoff_ccenpeak, histloff_ccenpeak, "Total CC energy (/COM) for events in the charged energy peak")
savefig("rootstab6_plotbb_ccenpeak.eps")

histhigh_trackspeak = jt.hist(19, -0.5, 18.5)
histhoff_trackspeak = jt.hist(19, -0.5, 18.5)
histlow_trackspeak = None
histloff_trackspeak = None

print "zero", time.asctime(time.localtime(time.time()))
histhigh_trackspeak.ntuple(high, "tracks", hadron_peak)
print "one", time.asctime(time.localtime(time.time()))
histhoff_trackspeak.ntuple(hoff, "tracks", hadron_peak)
print "two", time.asctime(time.localtime(time.time()))

plotdiff(histhigh_trackspeak, histlow_trackspeak, histhoff_trackspeak, histloff_trackspeak, "Number of tracks for events in the charged energy peak")
savefig("rootstab6_plotbb_trackspeak.eps")

def inthigh(histhigh, histlow, histhoff, histloff, low, high):
  global numbha_high, numbha_low, numbha_hoff, numbha_loff

  upshigh = histhigh/float(numbha_high) - histhoff/float(numbha_hoff)
  diff = upshigh

  dooverunder = False
  if low == high:
    il = 0
    ih = len(diff.values)
    dooverunder = True
  elif type(low) == int and type(high) == int:
    il = low
    ih = high
  else:
    il = int(round((low - diff.low)/(diff.high - diff.low)*diff.bins))
    ih = int(round((high - diff.low)/(diff.high - diff.low)*diff.bins))
  vals = diff.values[il:ih]
  errs = diff.errors[il:ih]

  thesum = reduce(lambda a, b: a+b, vals)
  theerr = reduce(lambda a, b: sqrt(a**2+b**2), errs)

  if dooverunder:
    thesum += diff.overflow + diff.underflow
    theerr = sqrt(theerr**2 + diff.overflow_error**2 + diff.underflow_error**2)
    print "underflow = %g +/- %g, overflow = %g +/- %g" % (diff.underflow, diff.underflow_error, diff.overflow, diff.overflow_error)

  print "From %d to %d is %g +/- %g" % (il, ih, thesum, theerr)

inthigh(histhigh_ccenpeak, histlow_ccenpeak, histhoff_ccenpeak, histloff_ccenpeak, 0.8, 1.2)
inthigh(histhigh_trackspeak, histlow_trackspeak, histhoff_trackspeak, histloff_trackspeak, -1, -1)

clf()
x, y, dy = histhoff_trackspeak.bin_centers(), histhoff_trackspeak.values, histhoff_trackspeak.errors
errorbar(x, y, dy, fmt=".k")
xlabel("Number of tracks in charged energy peak in off-resonance")
savefig("rootstab6_plotbb_trackspeakoff.eps")

histhigh_p1peak = jt.hist(60, 0, 1.2)
histhoff_p1peak = jt.hist(60, 0, 1.2)
histlow_p1peak = None
histloff_p1peak = None

def makep1(p1x, p1y, p1z, run):
  return sqrt(p1x**2+p1y**2+p1z**2)/runsummary[run].energy

print "zero", time.asctime(time.localtime(time.time()))
histhigh_p1peak.ntuple(high, makep1, hadron_peak)
print "one", time.asctime(time.localtime(time.time()))
histhoff_p1peak.ntuple(hoff, makep1, hadron_peak)
print "two", time.asctime(time.localtime(time.time()))

plotdiff(histhigh_p1peak, histlow_p1peak, histhoff_p1peak, histloff_p1peak, "Biggest track momentum (/ebeam) for events in the charged energy peak")
savefig("rootstab6_plotbb_p1peak.eps")

############################################

import jimtools as jt

desirable_dictionary = pickle.load(open("/home/mccann/synthesis/rootstab/rootstab6_desirable.p"))
numbha_low = desirable_dictionary["numbha_low"]
numgam_low = desirable_dictionary["numgam_low"]
numbha_high = desirable_dictionary["numbha_high"]
numgam_high = desirable_dictionary["numgam_high"]
numbha_loff = desirable_dictionary["numbha_loff"]
numgam_loff = desirable_dictionary["numgam_loff"]
numbha_hoff = desirable_dictionary["numbha_hoff"]
numgam_hoff = desirable_dictionary["numgam_hoff"]

def plotdiff(histhigh, histlow, histhoff, histloff, tit):
  global numbha_high, numbha_low, numbha_hoff, numbha_loff
  upshigh = histhigh/float(numbha_high) - histhoff/float(numbha_hoff)
  clf()
  title(tit)
  x, y, dy = upshigh.bin_centers(), upshigh.values, upshigh.errors
  errorbar(x, y, dy, fmt=".k")
  axhline(0)
  xlabel(r"April only (divided by num bhabhas)")

def hadron_peak_noconv(trig, d0close, anyz, coolvisen, chen, tracks):
  return int(trig) % 10000 % 1000 > 0 and \
         abs(d0close) < 0.005 and \
         abs(anyz) < 0.075 and \
         coolvisen > 0.4 and \
         chen > 0.98 and \
         tracks > 4

histhigh_p1peak = jt.hist(60, 0, 1.2)
histhoff_p1peak = jt.hist(60, 0, 1.2)
histlow_p1peak = None
histloff_p1peak = None

def makep1(p1x, p1y, p1z, run):
  return sqrt(p1x**2+p1y**2+p1z**2)/runsummary[run].energy

print "zero", time.asctime(time.localtime(time.time()))
histhigh_p1peak.ntuple(high, makep1, hadron_peak_noconv)
print "one", time.asctime(time.localtime(time.time()))
histhoff_p1peak.ntuple(hoff, makep1, hadron_peak_noconv)
print "two", time.asctime(time.localtime(time.time()))

plotdiff(histhigh_p1peak, histlow_p1peak, histhoff_p1peak, histloff_p1peak, "Biggest track momentum (/ebeam) with charged energy > 0.98 ECOM and tracks > 4")
savefig("rootstab6_plotbb_p1peak_noconv.eps")

import biggles
h = (histhigh_p1peak/float(numbha_high) - histhoff_p1peak/float(numbha_hoff))
x, y, dy = h.bin_centers(), h.values, h.errors
p = biggles.FramedPlot()
p.add(biggles.Points(x, y, symboltype="filled circle", symbolsize=0.8))
p.add(biggles.SymmetricErrorBarsY(x, y, dy))
p.add(biggles.LineY(0))
p.add(biggles.LineX(0.8, linetype="dashed"))
p.x1.label = "p1 with charged energy > 0.98 ECOM and tracks > 4"
p.aspect_ratio = 1
p.y1.range = -3e-5, 7e-5
p.show()
p.write_eps("rootstab6_plotbb_p1peak_noconv.eps")




