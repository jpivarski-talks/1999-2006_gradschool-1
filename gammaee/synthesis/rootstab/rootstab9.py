from math import *
import rootntuple, cPickle as pickle, time, jimtools as jt, biggles

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

def addtoplot(p, hist, color="black"):
  x = hist.bin_centers()
  y = hist.values
  dy = hist.errors
  p.add(biggles.Points(x, y, symboltype="filled circle", symbolsize=1, color=color))
  p.add(biggles.SymmetricErrorBarsY(x, y, dy, color=color))
  return p

def makeaplot(hist):
  p = biggles.FramedPlot()
  addtoplot(p, hist)
  return p

####################################################

ccen_high = jt.hist(100, 0.9, 1.1)
ccen_low = jt.hist(100, 0.9, 1.1)
ccen_high.ntuple(high, "ccen", step=1000)
ccen_low.ntuple(low, "ccen", step=1000)

p = makeaplot(ccen_high / sum(ccen_high.values))
addtoplot(p, ccen_low / sum(ccen_low.values), "red")
p.show()

s_high = 0.
s2_high = 0.
n_high = 0
s_low = 0.
s2_low = 0.
n_low = 0
def dome_high(ccen):
  if 0.9 < ccen < 1.1:
    global s_high, s2_high, n_high
    s_high += ccen
    s2_high += ccen**2
    n_high += 1
def dome_low(ccen):
  if 0.9 < ccen < 1.1:
    global s_low, s2_low, n_low
    s_low += ccen
    s2_low += ccen**2
    n_low += 1
high.map(dome_high, step=10)
low.map(dome_low, step=10)
mean_high = s_high / float(n_high)
mean_low = s_low / float(n_low)
stdev_high = sqrt(s2_high/float(n_high) - (s_high/float(n_high))**2)
stdev_low = sqrt(s2_low/float(n_low) - (s_low/float(n_low))**2)
print "mean high =", mean_high, "+/-", stdev_high/sqrt(n_high)
print "mean low = ", mean_low, "+/-", stdev_low/sqrt(n_low)

# mean high = 0.9870 +/- 7.46246259519e-05
# mean low =  0.9848 +/- 6.14521830758e-05

# So the April (high) cross-section has a CC calibration which is
# 0.22% higher than March (low), with 0.01% precision.
# This is 11 MeV high!

s_high = 0.
s2_high = 0.
n_high = 0
s_low = 0.
s2_low = 0.
n_low = 0
def dome_high(e1):
  if 0.9 < e1 < 1.1:
    global s_high, s2_high, n_high
    s_high += e1
    s2_high += e1**2
    n_high += 1
def dome_low(e1):
  if 0.9 < e1 < 1.1:
    global s_low, s2_low, n_low
    s_low += e1
    s2_low += e1**2
    n_low += 1
high.map(dome_high, step=10)
low.map(dome_low, step=10)
mean_high = s_high / float(n_high)
mean_low = s_low / float(n_low)
stdev_high = sqrt(s2_high/float(n_high) - (s_high/float(n_high))**2)
stdev_low = sqrt(s2_low/float(n_low) - (s_low/float(n_low))**2)
print "mean high =", mean_high, "+/-", stdev_high/sqrt(n_high)
print "mean low = ", mean_low, "+/-", stdev_low/sqrt(n_low)

# Do the same thing with biggest shower energy
# Same conclusion: 0.23% with 0.01% precision.

htrig =      {"high": jt.hist(8, -0.5, 7.5)}
htracks =    {"high": jt.hist(19, -0.5, 18.5)}
hp1 =        {"high": jt.hist(60, 0, 1.2)}
hchen =      {"high": jt.hist(60, 0, 1.2)}
hneue =      {"high": jt.hist(60, 0, 1.2)}
hvisen =     {"high": jt.hist(60, 0, 1.2)}
hcoolvisen = {"high": jt.hist(60, 0, 1.2)}
hcorvis =    {"high": jt.hist(60, 0, 1.2)}
for h in (htrig, htracks, hp1, hchen, hneue, hvisen, hcoolvisen, hcorvis):
  h["low"] = jt.hist(h["high"].bins, h["high"].low, h["high"].high)
  h["hoff"] = jt.hist(h["high"].bins, h["high"].low, h["high"].high)
  h["loff"] = jt.hist(h["high"].bins, h["high"].low, h["high"].high)

nhad = {}
ngam = {}
nbha = {}
for s in ("high", "low", "hoff", "loff"):
  nt = eval(s)
  nt.filter = None
  nt.range()
  nt.optimize = ["type", "trig", "tracks", "p1x", "p1y", "p1z", "run", "chen", "neue", "visen", "coolvisen", "d0close", "anyz"]

  if s == "high" or s == "hoff":
    factor = 1.0022
  else:
    factor = 1.0

  nhad[s] = 0
  ngam[s] = 0
  nbha[s] = 0
  lilcounter = 0
  for n in nt:
    lilcounter += 1
    if lilcounter % 10000 == 0: print time.asctime()

    if gamgam(n):
      ngam[s] += 1
    if hadron(n):
      nhad[s] += 1

      htrig[s].fill(trignum(n))
      htracks[s].fill(n.tracks)
      hp1[s].fill(sqrt(n.p1x**2+n.p1y**2+n.p1z**2) / runsummary[int(n.run)].energy)
      hchen[s].fill(n.chen)
      hneue[s].fill(n.neue)
      hvisen[s].fill(n.visen)
      hcoolvisen[s].fill(n.coolvisen)
      hcorvis[s].fill(n.chen + n.neue/factor)

  print "done with", s

for h in (htrig, htracks, hp1, hchen, hneue, hvisen, hcoolvisen, hcorvis):
  h["high"].rootn()
  h["low"].rootn()
  h["hoff"].rootn()
  h["loff"].rootn()

# Forgot this
# for s in ("high", "low", "hoff", "loff"):
#   nbha[s] = eval(s).count(lambda type: int(floor(type / 100)) % 10 == 1)
#   print "done with", s

# And this (actually, I had the correction backward)
# for s in ("high", "low", "hoff", "loff"):
#   if s == "high" or s == "hoff":
#     factor = 1.0022
#   else:
#     factor = 1.0
#   hcorvis[s].ntuple(eval(s), lambda chen, neue: chen+neue/factor, lambda type: type % 10 == 1)
#   print "done with", s

ptoc_high = 1.*ngam["high"]/ngam["hoff"]
ptoc_low = 1.*ngam["low"]/ngam["loff"]

def plotthree(h, title, filename=None, ghigh=0.966*nbha["high"], ghoff=nbha["hoff"], glow=0.966*nbha["low"], gloff=nbha["loff"]):
#   hups = h["high"] - h["hoff"]*ptoc_high
#   lups = h["low"] - h["loff"]*ptoc_low
#   frac = hups/lups * 1.*ngam["low"]/ngam["high"]

#   hups = h["high"]/float(ngam["high"]) - h["hoff"]/float(ngam["hoff"])
#   lups = h["low"]/float(ngam["low"]) - h["loff"]/float(ngam["loff"])
#   frac = hups/lups

  hups = h["high"]/float(ghigh) - h["hoff"]/float(ghoff)
  lups = h["low"]/float(glow) - h["loff"]/float(gloff)
  frac = hups/lups

  wm = jt.wmean(zip(frac.values, frac.errors))[0]
  
  sigmas = []
  for i in range(frac.bins):
    if frac.errors[i] > 0.:
      sigmas.append((frac.values[i]-wm) / frac.errors[i])
    else:
      sigmas.append(0.)

  p = biggles.FramedArray(3,1)
  addtoplot(p[0,0], hups)
  p[0,0].yrange = 0., max(hups.values)*1.1

  addtoplot(p[1,0], frac)
  p[1,0].add(biggles.LineY(wm))
  p[1,0].yrange = 0.701, 1.299

  p[2,0].add(biggles.Points(frac.bin_centers(), sigmas))
  p[2,0].add(biggles.LineY(0.))
  p[2,0].yrange = -4., 4.

  p.xlabel = title
  p.show()
  if filename != None: p.write_eps(filename)

plotthree(htrig, "trigger", "rootstab9_trig.eps")
plotthree(htracks, "tracks", "rootstab9_tracks.eps")
plotthree(hp1, "largest track momentum", "rootstab9_p1.eps")
plotthree(hchen, "charged energy", "rootstab9_chen.eps")
plotthree(hneue, "neutral energy", "rootstab9_neue.eps")
plotthree(hvisen, "visible energy (raw)", "rootstab9_visen.eps")
plotthree(hcoolvisen, "visible energy (hot showers removed)", "rootstab9_coolvisen.eps")
plotthree(hcorvis, "visible energy (corrected for CC calibration)", "rootstab9_corvis.eps")



