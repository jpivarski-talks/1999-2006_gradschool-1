import cPickle as pickle, biggles, jimtools as jt, rootntuple, time
from math import *

desirable_dictionary = pickle.load(open("/home/mccann/synthesis/rootstab/rootstab6_desirable.p"))
# histlow_trig = desirable_dictionary["histlow_trig"]
# histlow_d0close = desirable_dictionary["histlow_d0close"]
# histlow_anyz = desirable_dictionary["histlow_anyz"]
# histlow_p1all = desirable_dictionary["histlow_p1all"]
# histlow_p1high = desirable_dictionary["histlow_p1high"]
# histlow_visen = desirable_dictionary["histlow_visen"]
# histlow_chen = desirable_dictionary["histlow_chen"]
# histlow_neue = desirable_dictionary["histlow_neue"]
# histlow_tracks = desirable_dictionary["histlow_tracks"]
# histhigh_trig = desirable_dictionary["histhigh_trig"]
# histhigh_d0close = desirable_dictionary["histhigh_d0close"]
# histhigh_anyz = desirable_dictionary["histhigh_anyz"]
# histhigh_p1all = desirable_dictionary["histhigh_p1all"]
# histhigh_p1high = desirable_dictionary["histhigh_p1high"]
# histhigh_visen = desirable_dictionary["histhigh_visen"]
# histhigh_chen = desirable_dictionary["histhigh_chen"]
# histhigh_neue = desirable_dictionary["histhigh_neue"]
# histhigh_tracks = desirable_dictionary["histhigh_tracks"]
# histloff_trig = desirable_dictionary["histloff_trig"]
# histloff_d0close = desirable_dictionary["histloff_d0close"]
# histloff_anyz = desirable_dictionary["histloff_anyz"]
# histloff_p1all = desirable_dictionary["histloff_p1all"]
# histloff_p1high = desirable_dictionary["histloff_p1high"]
# histloff_visen = desirable_dictionary["histloff_visen"]
# histloff_chen = desirable_dictionary["histloff_chen"]
# histloff_neue = desirable_dictionary["histloff_neue"]
# histloff_tracks = desirable_dictionary["histloff_tracks"]
# histhoff_trig = desirable_dictionary["histhoff_trig"]
# histhoff_d0close = desirable_dictionary["histhoff_d0close"]
# histhoff_anyz = desirable_dictionary["histhoff_anyz"]
# histhoff_p1all = desirable_dictionary["histhoff_p1all"]
# histhoff_p1high = desirable_dictionary["histhoff_p1high"]
# histhoff_visen = desirable_dictionary["histhoff_visen"]
# histhoff_chen = desirable_dictionary["histhoff_chen"]
# histhoff_neue = desirable_dictionary["histhoff_neue"]
# histhoff_tracks = desirable_dictionary["histhoff_tracks"]
numbha_low = desirable_dictionary["numbha_low"]
numgam_low = desirable_dictionary["numgam_low"]
numbha_high = desirable_dictionary["numbha_high"]
numgam_high = desirable_dictionary["numgam_high"]
numbha_loff = desirable_dictionary["numbha_loff"]
numgam_loff = desirable_dictionary["numgam_loff"]
numbha_hoff = desirable_dictionary["numbha_hoff"]
numgam_hoff = desirable_dictionary["numgam_hoff"]

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

def allcuts(cuts):
  passcuts = True
  for j in range(len(cuts)):
    passcuts = passcuts and cuts[j]
  return passcuts

def allbutcut(cuts, i):
  passcuts = True
  for j in range(len(cuts)):
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
histlow_p1all = jt.hist(30, 0, 1.2)
histlow_visen = jt.hist(30, 0, 1.2)
histlow_chen = jt.hist(30, 0, 1.2)
histlow_chen2 = jt.hist(120, 0, 1.2)
histlow_neue = jt.hist(30, 0, 1.2)
histlow_tracks = jt.hist(19, -0.5, 18.5)
histhigh_trig = jt.hist(8, -0.5, 7.5)
histhigh_p1all = jt.hist(30, 0, 1.2)
histhigh_visen = jt.hist(30, 0, 1.2)
histhigh_chen = jt.hist(30, 0, 1.2)
histhigh_chen2 = jt.hist(120, 0, 1.2)
histhigh_neue = jt.hist(30, 0, 1.2)
histhigh_tracks = jt.hist(19, -0.5, 18.5)
histloff_trig = jt.hist(8, -0.5, 7.5)
histloff_p1all = jt.hist(30, 0, 1.2)
histloff_visen = jt.hist(30, 0, 1.2)
histloff_chen = jt.hist(30, 0, 1.2)
histloff_chen2 = jt.hist(120, 0, 1.2)
histloff_neue = jt.hist(30, 0, 1.2)
histloff_tracks = jt.hist(19, -0.5, 18.5)
histhoff_trig = jt.hist(8, -0.5, 7.5)
histhoff_p1all = jt.hist(30, 0, 1.2)
histhoff_visen = jt.hist(30, 0, 1.2)
histhoff_chen = jt.hist(30, 0, 1.2)
histhoff_chen2 = jt.hist(120, 0, 1.2)
histhoff_neue = jt.hist(30, 0, 1.2)
histhoff_tracks = jt.hist(19, -0.5, 18.5)

low.optimize = ["d0close", "anyz", "trig", "p1x", "p1y", "p1z", "run", "coolvisen", "chen", "neue", "tracks"]
high.optimize = ["d0close", "anyz", "trig", "p1x", "p1y", "p1z", "run", "coolvisen", "chen", "neue", "tracks"]
loff.optimize = ["d0close", "anyz", "trig", "p1x", "p1y", "p1z", "run", "coolvisen", "chen", "neue", "tracks"]
hoff.optimize = ["d0close", "anyz", "trig", "p1x", "p1y", "p1z", "run", "coolvisen", "chen", "neue", "tracks"]

counter = 0
for n in low:
  if counter % 10000 == 0:
    print "low", time.asctime(time.localtime(time.time())), counter
  counter += 1

  p1 = sqrt(n.p1x**2+n.p1y**2+n.p1z**2) / runsummary[int(n.run)].energy
  cuts = [int(n.trig) % 10000 % 1000 > 0,   \
          abs(n.d0close) < 0.005,           \
          abs(n.anyz) < 0.075,              \
          p1 < 0.8,                         \
          n.coolvisen > 0.4]

  if allcuts(cuts):
    histlow_trig.fill(trignum(n))
    histlow_tracks.fill(n.tracks)

  if allbutcut(cuts, 3):
    histlow_p1all.fill(p1)

  if allbutcut(cuts, 4):
    histlow_visen.fill(n.coolvisen)
    histlow_chen.fill(n.chen)
    histlow_chen2.fill(n.chen)
    histlow_neue.fill(n.neue)

counter = 0
for n in high:
  if counter % 10000 == 0:
    print "high", time.asctime(time.localtime(time.time())), counter
  counter += 1

  p1 = sqrt(n.p1x**2+n.p1y**2+n.p1z**2) / runsummary[int(n.run)].energy
  cuts = [int(n.trig) % 10000 % 1000 > 0,   \
          abs(n.d0close) < 0.005,           \
          abs(n.anyz) < 0.075,              \
          p1 < 0.8,                         \
          n.coolvisen > 0.4]

  if allcuts(cuts):
    histhigh_trig.fill(trignum(n))
    histhigh_tracks.fill(n.tracks)

  if allbutcut(cuts, 3):
    histhigh_p1all.fill(p1)

  if allbutcut(cuts, 4):
    histhigh_visen.fill(n.coolvisen)
    histhigh_chen.fill(n.chen)
    histhigh_chen2.fill(n.chen)
    histhigh_neue.fill(n.neue)

counter = 0
for n in loff:
  if counter % 10000 == 0:
    print "loff", time.asctime(time.localtime(time.time())), counter
  counter += 1

  p1 = sqrt(n.p1x**2+n.p1y**2+n.p1z**2) / runsummary[int(n.run)].energy
  cuts = [int(n.trig) % 10000 % 1000 > 0,   \
          abs(n.d0close) < 0.005,           \
          abs(n.anyz) < 0.075,              \
          p1 < 0.8,                         \
          n.coolvisen > 0.4]

  if allcuts(cuts):
    histloff_trig.fill(trignum(n))
    histloff_tracks.fill(n.tracks)

  if allbutcut(cuts, 3):
    histloff_p1all.fill(p1)

  if allbutcut(cuts, 4):
    histloff_visen.fill(n.coolvisen)
    histloff_chen.fill(n.chen)
    histloff_chen2.fill(n.chen)
    histloff_neue.fill(n.neue)

counter = 0
for n in hoff:
  if counter % 10000 == 0:
    print "hoff", time.asctime(time.localtime(time.time())), counter
  counter += 1

  p1 = sqrt(n.p1x**2+n.p1y**2+n.p1z**2) / runsummary[int(n.run)].energy
  cuts = [int(n.trig) % 10000 % 1000 > 0,   \
          abs(n.d0close) < 0.005,           \
          abs(n.anyz) < 0.075,              \
          p1 < 0.8,                         \
          n.coolvisen > 0.4]

  if allcuts(cuts):
    histhoff_trig.fill(trignum(n))
    histhoff_tracks.fill(n.tracks)

  if allbutcut(cuts, 3):
    histhoff_p1all.fill(p1)

  if allbutcut(cuts, 4):
    histhoff_visen.fill(n.coolvisen)
    histhoff_chen.fill(n.chen)
    histhoff_chen2.fill(n.chen)
    histhoff_neue.fill(n.neue)

def plotoverlay(histhigh, histlow, histhoff, histloff, p):
  global numbha_high, numbha_low, numbha_hoff, numbha_loff
  histhigh.rootn()
  histlow.rootn()
  histhoff.rootn()
  histloff.rootn()

  upshigh = histhigh/float(numbha_high) - histhoff/float(numbha_hoff)
  upslow = histlow/float(numbha_low) - histloff/float(numbha_loff)

  x, y, dy = upshigh.bin_centers(), upshigh.values, upshigh.errors
  p.add(biggles.Points(x, y, symboltype="filled triangle", symbolsize=0.8))
  p.add(biggles.SymmetricErrorBarsY(x, y, dy))
  x, y, dy = upslow.bin_centers(), upslow.values, upslow.errors
  p.add(biggles.Points(x, y, symboltype="inverted triangle", symbolsize=0.8))
  p.add(biggles.SymmetricErrorBarsY(x, y, dy))
  return p

def plotfrac(histhigh, histlow, histhoff, histloff, p):
  global numbha_high, numbha_low, numbha_hoff, numbha_loff
  histhigh.rootn()
  histlow.rootn()
  histhoff.rootn()
  histloff.rootn()

  upshigh = histhigh/float(numbha_high) - histhoff/float(numbha_hoff)
  upslow = histlow/float(numbha_low) - histloff/float(numbha_loff)
  frac = upshigh / upslow

  x, y, dy = frac.bin_centers(), frac.values, frac.errors
  ave = jt.wmean(zip(y, dy))[0]
  print ave
  p.add(biggles.Points(x, y, symboltype="filled circle", symbolsize=0.8))
  p.add(biggles.SymmetricErrorBarsY(x, y, dy))
  p.add(biggles.LineY(ave)) 
  return p

def plotsig(histhigh, histlow, histhoff, histloff, p):
  global numbha_high, numbha_low, numbha_hoff, numbha_loff
  histhigh.rootn()
  histlow.rootn()
  histhoff.rootn()
  histloff.rootn()

  upshigh = histhigh/float(numbha_high) - histhoff/float(numbha_hoff)
  upslow = histlow/float(numbha_low) - histloff/float(numbha_loff)
  frac = upshigh / upslow

  x, y, dy = frac.bin_centers(), frac.values, frac.errors
  ave = jt.wmean(zip(y, dy))[0]
  sig = [-1000.] * len(y)
  for i in range(len(y)):
    try:
      sig[i] = (y[i] - ave)/dy[i]
    except ZeroDivisionError:
      sig[i] = -1000.
  p.add(biggles.Points(x, sig, symboltype="filled circle", symbolsize=0.8))
  p.add(biggles.LineY(0))
  p.yrange = -5, 5
  return p

p = biggles.FramedArray(2,1)
plotfrac(histhigh_trig, histlow_trig, histhoff_trig, histloff_trig, p[0,0])
p[0,0].yrange = 0.7, 1.3
plotsig(histhigh_trig, histlow_trig, histhoff_trig, histloff_trig, p[1,0])
p.ylabel = "          sigmas            April/March Upsilon ratio"
p.xlabel = "Trigger lines"
p.show()
p.write_eps("rootstab8_ratios_trig.eps")

p = biggles.FramedArray(2,1)
plotfrac(histhigh_p1all, histlow_p1all, histhoff_p1all, histloff_p1all, p[0,0])
p[0,0].yrange = 0.8, 1.20001
plotsig(histhigh_p1all, histlow_p1all, histhoff_p1all, histloff_p1all, p[1,0])
p.ylabel = "          sigmas            April/March Upsilon ratio"
p.xlabel = "Biggest track momentum / eBeam"
p.show()
p.write_eps("rootstab8_ratios_p1.eps")

p = biggles.FramedArray(2,1)
plotfrac(histhigh_visen, histlow_visen, histhoff_visen, histloff_visen, p[0,0])
p[0,0].yrange = 0.8, 1.20001
plotsig(histhigh_visen, histlow_visen, histhoff_visen, histloff_visen, p[1,0])
p.ylabel = "          sigmas            April/March Upsilon ratio"
p.xlabel = "Visible energy / ECOM"
p.show()
p.write_eps("rootstab8_ratios_visen.eps")

p = biggles.FramedArray(2,1)
plotfrac(histhigh_chen, histlow_chen, histhoff_chen, histloff_chen, p[0,0])
p[0,0].yrange = 0.8, 1.20001
plotsig(histhigh_chen, histlow_chen, histhoff_chen, histloff_chen, p[1,0])
p.ylabel = "          sigmas            April/March Upsilon ratio"
p.xlabel = "Charged energy / ECOM"
p.show()
p.write_eps("rootstab8_ratios_chen.eps")

p = biggles.FramedArray(2,1)
plotfrac(histhigh_neue, histlow_neue, histhoff_neue, histloff_neue, p[0,0])
p[0,0].yrange = 0.8, 1.20001
plotsig(histhigh_neue, histlow_neue, histhoff_neue, histloff_neue, p[1,0])
p.ylabel = "          sigmas            April/March Upsilon ratio"
p.xlabel = "Neutral energy / ECOM"
p.show()
p.write_eps("rootstab8_ratios_neue.eps")

p = biggles.FramedArray(2,1)
plotfrac(histhigh_tracks, histlow_tracks, histhoff_tracks, histloff_tracks, p[0,0])
p[0,0].yrange = 0.9, 1.20001
plotsig(histhigh_tracks, histlow_tracks, histhoff_tracks, histloff_tracks, p[1,0])
p.ylabel = "          sigmas            April/March Upsilon ratio"
p.xlabel = "Number of tracks"
p.show()
p.write_eps("rootstab8_ratios_tracks.eps")

######################################################

histhigh_chen2.rootn()
histlow_chen2.rootn()
histhoff_chen2.rootn()
histloff_chen2.rootn()

upshigh_chen2 = histhigh_chen2/float(numbha_high) - histhoff_chen2/float(numbha_hoff)
upslow_chen2 = histlow_chen2/float(numbha_low) - histloff_chen2/float(numbha_loff)
diff_chen2 = upshigh_chen2 - upslow_chen2

x, y, dy = upshigh_chen2.bin_centers(), upshigh_chen2.values, upshigh_chen2.errors
p = biggles.FramedPlot()
p.add(biggles.Points(x, y, symboltype="filled circle", symbolsize=0.8))
p.add(biggles.SymmetricErrorBarsY(x, y, dy))
x, y, dy = upslow_chen2.bin_centers(), upslow_chen2.values, upslow_chen2.errors
p.add(biggles.Points(x, y, symboltype="filled circle", symbolsize=0.8, color="red"))
p.add(biggles.SymmetricErrorBarsY(x, y, dy, color="red"))
p.show()





def pseudohadron(trig, d0close, anyz, p1x, p1y, p1z, run, coolvisen):
  p1 = sqrt(p1x**2+p1y**2+p1z**2) / runsummary[int(run)].energy
  return int(trig) % 10000 % 1000 > 0 and   \
         abs(d0close) < 0.005 and           \
         abs(anyz) < 0.075 and              \
         p1 < 0.8 and                         \
         coolvisen > 0.4

histlow_chen3 = jt.hist(120, 0, 1.2).ntuple(low, "chen", pseudohadron)
histhigh_chen3 = jt.hist(120, 0, 1.2).ntuple(high, "chen", pseudohadron)
histloff_chen3 = jt.hist(120, 0, 1.2).ntuple(loff, "chen", pseudohadron)
histhoff_chen3 = jt.hist(120, 0, 1.2).ntuple(hoff, "chen", pseudohadron)

upshigh_chen3 = histhigh_chen3/float(numbha_high) - histhoff_chen3/float(numbha_hoff)
upslow_chen3 = histlow_chen3/float(numbha_low) - histloff_chen3/float(numbha_loff)
diff_chen3 = upshigh_chen3 - upslow_chen3

def xydy(hist):
  return hist.bin_centers(), hist.values, hist.errors

x, y, dy = xydy(histhigh_chen3/numbha_high)
p = biggles.FramedPlot()
p.add(biggles.Points(x, y, symboltype="filled circle", symbolsize=0.8))
p.add(biggles.SymmetricErrorBarsY(x, y, dy))
x, y, dy = xydy(histlow_chen3/numbha_low)
p.add(biggles.Points(x, y, symboltype="filled circle", symbolsize=0.8, color="red"))
p.add(biggles.SymmetricErrorBarsY(x, y, dy, color="red"))
p.show()

x, y, dy = upshigh_chen3.bin_centers(), upshigh_chen3.values, upshigh_chen3.errors
p = biggles.FramedPlot()
p.add(biggles.Points(x, y, symboltype="filled circle", symbolsize=0.8))
p.add(biggles.SymmetricErrorBarsY(x, y, dy))
x, y, dy = upslow_chen3.bin_centers(), upslow_chen3.values, upslow_chen3.errors
p.add(biggles.Points(x, y, symboltype="filled circle", symbolsize=0.8, color="red"))
p.add(biggles.SymmetricErrorBarsY(x, y, dy, color="red"))
p.show()

#########################################################

pseudo_visen = jt.hist(120, 0, 1.2)
pseudo_chen = jt.hist(120, 0, 1.2)
pseudo_neue = jt.hist(120, 0, 1.2)
pseudo_ccen = jt.hist(120, 0, 1.2)
pseudo_p1 = jt.hist(120, 0, 1.2)
pseudo_tracks = jt.hist(19, -0.5, 18.5)

real_visen = jt.hist(120, 0, 1.2)
real_chen = jt.hist(120, 0, 1.2)
real_neue = jt.hist(120, 0, 1.2)
real_ccen = jt.hist(120, 0, 1.2)
real_p1 = jt.hist(120, 0, 1.2)
real_tracks = jt.hist(19, -0.5, 18.5)

high.optimize = ['d0close', 'anyz', 'trig', 'p1x', 'p1y', 'p1z', 'run', 'coolvisen', 'chen', 'neue', 'tracks', 'type', 'ccen']

lil_matrix = [[0, 0], [0, 0]]

for n in high:
  p1 = sqrt(n.p1x**2+n.p1y**2+n.p1z**2) / runsummary[int(n.run)].energy
  pseudo_cut = int(n.trig) % 10000 % 1000 > 0 and   \
               abs(n.d0close) < 0.005 and           \
               abs(n.anyz) < 0.075 and              \
               p1 < 0.8 and                         \
               n.coolvisen > 0.4
  real_cut = int(n.type) % 10 == 1

  i = 0; j = 0
  if pseudo_cut:
    i = 1
    pseudo_visen.fill(n.coolvisen)
    pseudo_chen.fill(n.chen)
    pseudo_neue.fill(n.neue)
    pseudo_ccen.fill(n.ccen)
    pseudo_p1.fill(p1)
    pseudo_tracks.fill(n.tracks)

  if real_cut:
    j = 1
    real_visen.fill(n.coolvisen)
    real_chen.fill(n.chen)
    real_neue.fill(n.neue)
    real_ccen.fill(n.ccen)
    real_p1.fill(p1)
    real_tracks.fill(n.tracks)

  lil_matrix[i][j] += 1

pseudo_visen.rootn()
pseudo_chen.rootn()
pseudo_neue.rootn()
pseudo_ccen.rootn()
pseudo_p1.rootn()
pseudo_tracks.rootn()

real_visen.rootn()
real_chen.rootn()
real_neue.rootn()
real_ccen.rootn()
real_p1.rootn()
real_tracks.rootn()

def xydy(hist):
  return hist.bin_centers(), hist.values, hist.errors

def compare(pseudohist, realhist, title, filetitle):
  x, y, dy = xydy(pseudohist)
  p = biggles.FramedPlot()
  p.add(biggles.Points(x, y, symboltype="filled circle", symbolsize=0.8))
  p.add(biggles.SymmetricErrorBarsY(x, y, dy))
  x, y, dy = xydy(realhist)
  p.add(biggles.Points(x, y, symboltype="filled circle", symbolsize=0.8, color="red"))
  p.add(biggles.SymmetricErrorBarsY(x, y, dy, color="red"))
  p.x1.label = "black=mocked up cuts, red=analysis cuts: "+title
  p.aspect_ratio = 1
  p.show()
  p.write_eps("rootstab8_pseudoreal_"+filetitle+".eps")

compare(pseudo_visen , real_visen , "visible energy", "visen")
compare(pseudo_chen  , real_chen  , "charged energy", "chen")
compare(pseudo_neue  , real_neue  , "neutral energy", "neue")
compare(pseudo_ccen  , real_ccen  , "CC energy", "ccen")
compare(pseudo_p1    , real_p1    , "biggest-track p", "p1")
compare(pseudo_tracks, real_tracks, "#tracks", "tracks")










#######################################################

histhigh_chen.rootn()
histlow_chen.rootn()

upshigh_chen = histhigh_chen/float(numbha_high) - histhoff_chen/float(numbha_hoff)
upslow_chen = histlow_chen/float(numbha_low) - histloff_chen/float(numbha_loff)
diff_chen = upshigh_chen - upslow_chen
frac_chen = upshigh_chen / upslow_chen

x, y, dy = upshigh_chen.bin_centers(), upshigh_chen.values, upshigh_chen.errors
p = biggles.FramedPlot()
p.add(biggles.Points(x, y, symboltype="filled circle", symbolsize=0.8))
p.add(biggles.SymmetricErrorBarsY(x, y, dy))
x, y, dy = upslow_chen.bin_centers(), upslow_chen.values, upslow_chen.errors
p.add(biggles.Points(x, y, symboltype="filled circle", symbolsize=0.8, color="red"))
p.add(biggles.SymmetricErrorBarsY(x, y, dy, color="red"))
p.show()

x, y, dy = diff_chen.bin_centers(), diff_chen.values, diff_chen.errors
p = biggles.FramedPlot()
p.add(biggles.Points(x, y, symboltype="filled circle", symbolsize=0.8))
p.add(biggles.SymmetricErrorBarsY(x, y, dy))
p.show()

x, y, dy = frac_chen.bin_centers(), frac_chen.values, frac_chen.errors
p = biggles.FramedPlot()
p.add(biggles.Points(x, y, symboltype="filled circle", symbolsize=0.8))
p.add(biggles.SymmetricErrorBarsY(x, y, dy))
p.show()


################################################

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

def hadron(type):
  return type % 10 == 1

def bhabha(type):
  return int(floor(type / 100)) % 10 == 1

chen2_low = jt.hist(120, 0, 1.2).ntuple(low, "chen", hadron)
chen2_high = jt.hist(120, 0, 1.2).ntuple(high, "chen", hadron)
chen2_loff = jt.hist(120, 0, 1.2).ntuple(loff, "chen", hadron)
chen2_hoff = jt.hist(120, 0, 1.2).ntuple(hoff, "chen", hadron)

numbha2_low = low.count(bhabha)
numbha2_high = high.count(bhabha)
numbha2_loff = loff.count(bhabha)
numbha2_hoff = hoff.count(bhabha)

upshigh_chen2 = chen2_high/float(numbha2_high) - chen2_hoff/float(numbha2_hoff)
upslow_chen2 = chen2_low/float(numbha2_low) - chen2_loff/float(numbha2_loff)
diff_chen2 = upshigh_chen2 - upslow_chen2

x, y, dy = upshigh_chen2.bin_centers(), upshigh_chen2.values, upshigh_chen2.errors
p = biggles.FramedPlot()
p.add(biggles.Points(x, y, symboltype="filled circle", symbolsize=0.8))
p.add(biggles.SymmetricErrorBarsY(x, y, dy))
x, y, dy = upslow_chen2.bin_centers(), upslow_chen2.values, upslow_chen2.errors
p.add(biggles.Points(x, y, symboltype="filled circle", symbolsize=0.8, color="red"))
p.add(biggles.SymmetricErrorBarsY(x, y, dy, color="red"))
p.show()
p.write_eps("rootstab8_theres_no_peak.eps")

x, y, dy = diff_chen2.bin_centers(), diff_chen2.values, diff_chen2.errors
q = biggles.FramedPlot()
q.add(biggles.Points(x, y, symboltype="filled circle", symbolsize=0.8))
q.add(biggles.SymmetricErrorBarsY(x, y, dy))
q.show()





x, y, dy = histhigh_chen.bin_centers(), histhigh_chen.values, histhigh_chen.errors
p = biggles.FramedPlot()
p.add(biggles.Points(x, y, symboltype="filled circle", symbolsize=0.8))
p.add(biggles.SymmetricErrorBarsY(x, y, dy))
x, y, dy = chen2_high.bin_centers(), chen2_high.values, chen2_high.errors
p.add(biggles.Points(x, y, symboltype="filled circle", symbolsize=0.8, color="red"))
p.add(biggles.SymmetricErrorBarsY(x, y, dy, color="red"))
p.show()
p.write_eps("rootstab8_because_i_forgot_p1.eps")

x, y, dy = histlow_chen.bin_centers(), histlow_chen.values, histlow_chen.errors
p = biggles.FramedPlot()
p.add(biggles.Points(x, y, symboltype="filled circle", symbolsize=0.8))
p.add(biggles.SymmetricErrorBarsY(x, y, dy))
x, y, dy = chen2_low.bin_centers(), chen2_low.values, chen2_low.errors
p.add(biggles.Points(x, y, symboltype="filled circle", symbolsize=0.8, color="red"))
p.add(biggles.SymmetricErrorBarsY(x, y, dy, color="red"))
p.show()

x, y, dy = histhoff_chen.bin_centers(), histhoff_chen.values, histhoff_chen.errors
p = biggles.FramedPlot()
p.add(biggles.Points(x, y, symboltype="filled circle", symbolsize=0.8))
p.add(biggles.SymmetricErrorBarsY(x, y, dy))
x, y, dy = chen2_hoff.bin_centers(), chen2_hoff.values, chen2_hoff.errors
p.add(biggles.Points(x, y, symboltype="filled circle", symbolsize=0.8, color="red"))
p.add(biggles.SymmetricErrorBarsY(x, y, dy, color="red"))
p.show()

x, y, dy = histloff_chen.bin_centers(), histloff_chen.values, histloff_chen.errors
p = biggles.FramedPlot()
p.add(biggles.Points(x, y, symboltype="filled circle", symbolsize=0.8))
p.add(biggles.SymmetricErrorBarsY(x, y, dy))
x, y, dy = chen2_loff.bin_centers(), chen2_loff.values, chen2_loff.errors
p.add(biggles.Points(x, y, symboltype="filled circle", symbolsize=0.8, color="red"))
p.add(biggles.SymmetricErrorBarsY(x, y, dy, color="red"))
p.show()

