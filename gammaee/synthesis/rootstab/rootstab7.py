from math import *
import rootntuple, cPickle as pickle, time, jimtools as jt
execfile("/home/mccann/antithesis/utilities.py")

initialrunlist = pickle.load(open("/home/mccann/synthesis/lumieff/initialrunlist.p"))
mybadruns = [122617, 124363, 124364, 124365, 124368, 124369, 124372, 124373, 124459, 122353, 126341, 129522, 123013, 123014, 121928, 121929, 121953, 127951, 127955, 130278, 121710, 121930, 121944, 121954, 123884, 122331, 122335, 122336, 122339, 122341, 122342, 122344, 122345, 122349, 122350, 122352, 121476, 121748, 121822, 121847, 122685, 123436, 123847, 123873, 124816, 124860, 124862, 125367, 126273, 126329, 127280, 124452, 124454, 124456, 124458, 124462, 124464, 124465, 124466, 124467, 124469, 124472, 124473, 124474, 124475, 124477, 124478, 124479, 124480, 123281, 123411, 121595, 122093, 122330, 126510]

class RunSummary : pass
runsummary = pickle.load(open("/home/mccann/synthesis/lumieff/runsummary.p"))

runstart = pickle.load(open("/home/mccann/antithesis/old_dotps/runstart.p"))
runend = pickle.load(open("/home/mccann/antithesis/old_dotps/runend.p"))
def run_date(r):
  if r in runstart and r in runend:
    return (runstart[r] + runend[r])/2.
  elif r in runstart:
    return runstart[r]
  elif r in runend:
    return runend[r]
  else:
    raise Exception

bbinr = {}
for r in initialrunlist:
  if r not in mybadruns and runsummary[r].kind == "p" and runsummary[r].res == 1:
    therun = getdb(r)
    bbinr[r] = therun.bhabha

runnums = []
wles = [] # weird little events
for r in initialrunlist:
  if r not in mybadruns and runsummary[r].kind == "p" and runsummary[r].res == 1:
    try:
      thefile = rootntuple.RootDir("/home/mccann/synthesis/root/db_"+str(r)+".root").get("UpsilonGammaEEAnalysisProc")
      ntuple = thefile.get("nt1")
      num = ntuple.count("type % 10 == 1 and chen > 0.98 and ccen < 0.8 and tracks > 5")
      thefile.closefile()
      runnums.append(r)
      wles.append(num)
      print r, "has", num
    except IOError:
      print r, "has no ntuple"

pickle.dump({"runnums": runnums, "wles": wles}, open("rootstab7_wles.p", "w"))

import time, Numeric
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

wles_frac = []
wles_frac_err = []
for r, w in zip(runnums, wles):
  if w > 0:
    wles_frac.append(1.*w/bbinr[r])
    wles_frac_err.append(1.*w/bbinr[r]*sqrt(1./w + 1./bbinr[r]))
  else:
    wles_frac.append(0.)
    wles_frac_err.append(0.)

import biggles
p = biggles.FramedPlot()
x = map(run_date, runnums)
y = wles_frac
dy = wles_frac_err
p.add(biggles.Points(x, y, symboltype="filled circle", symbolsize=0.8))
p.add(biggles.SymmetricErrorBarsY(x, y, dy))

subticks = []
sublabels = []
for t, l in zip(dticks, dlabels):
  if min(x)-7.*24.*60.*60. < t < max(x)+7.*24.*60.*60.:
    subticks.append(t)
    sublabels.append(l)
subsubticks = []
for t in dsubticks:
  if min(x)-7.*24.*60.*60. < t < max(x)+7.*24.*60.*60.:
    subsubticks.append(t)
p.x1.ticks = subticks
p.x1.subticks = subsubticks
p.x1.ticklabels = sublabels
p.x2.ticks = subticks
p.x2.subticks = subsubticks
p.x2.draw_ticklabels = 0
p.x1.label = r"Date in 2002"

p.title = "Weird little events in U(1S) peak"
p.y1.range = 0, 0.004
p.show()
p.write_eps("rootstab7_wles.eps")

bhabhas_comb = []
dates_comb = []
wles_comb = []
bhabhas_point = []
dates_point = []
wles_point = []
prev = run_date(runnums[0])
for r, w in zip(runnums, wles):
  d = run_date(r)
  if d - prev > 36*60*60:
    bhabhas_comb.append(sum(bhabhas_point))
    dates_comb.append(jt.mean(dates_point))
    wles_comb.append(sum(wles_point))
    bhabhas_point = []
    dates_point = []
    wles_point = []

  bhabhas_point.append(bbinr[r])
  dates_point.append(d)
  wles_point.append(w)
  prev = d

if len(dates_point) > 0:
  bhabhas_comb.append(sum(bhabhas_point))
  dates_comb.append(jt.mean(dates_point))
  wles_comb.append(sum(wles_point))

wles_frac = []
wles_frac_err = []
for bb, w in zip(bhabhas_comb, wles_comb):
  if w > 0:
    wles_frac.append(1.*w/bb)
    wles_frac_err.append(1.*w/bb*sqrt(1./w + 1./bb))
  else:
    wles_frac.append(0.)
    wles_frac_err.append(0.)

p = biggles.FramedPlot()
x = dates_comb
y = wles_frac
dy = wles_frac_err
p.add(biggles.Points(x, y, symboltype="filled circle", symbolsize=0.8))
p.add(biggles.SymmetricErrorBarsY(x, y, dy))

subticks = []
sublabels = []
for t, l in zip(dticks, dlabels):
  if min(x)-7.*24.*60.*60. < t < max(x)+7.*24.*60.*60.:
    subticks.append(t)
    sublabels.append(l)
subsubticks = []
for t in dsubticks:
  if min(x)-7.*24.*60.*60. < t < max(x)+7.*24.*60.*60.:
    subsubticks.append(t)
p.x1.ticks = subticks
p.x1.subticks = subsubticks
p.x1.ticklabels = sublabels
p.x2.ticks = subticks
p.x2.subticks = subsubticks
p.x2.draw_ticklabels = 0
p.x1.label = r"Date in 2002"

p.title = "Weird little events in U(1S) peak"
p.y1.range = 0, 0.0016
p.show()
p.write_eps("rootstab7_wles_comb.eps")

#####################################

for r in initialrunlist:
  if r not in mybadruns and runsummary[r].kind == "c" and runsummary[r].res == 1:
    therun = getdb(r)
    bbinr[r] = therun.bhabha

cont_runs = []
for r in initialrunlist:
  if r not in mybadruns and runsummary[r].kind == "c" and runsummary[r].res == 1:
    cont_runs.append(r)

def getntuple(run):
  return rootntuple.RootNtuple("/home/mccann/synthesis/root/db_"+str(run)+".root:/UpsilonGammaEEAnalysisProc/nt1")

cont = getntuple(cont_runs[0])
for r in cont_runs[1:]:
  cont += getntuple(r)
num_wle = cont.count("type % 10 == 1 and chen > 0.98 and ccen < 0.8 and tracks > 5")

num_bha = sum(map(lambda r: bbinr[r], cont_runs))

#######################################

def hadron(n):
  return n.type % 10 == 1

def gamgam(n):
  return int(floor(n.type / 10)) % 10 == 1

def bhabha(n):
  return int(floor(n.type / 100)) % 10 == 1

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

low.optimize = ["type", "chen", "ccen", "tracks"]
high.optimize = ["type", "chen", "ccen", "tracks"]

num_low = low.count("type % 10 == 1 and chen > 0.98 and ccen < 0.8 and tracks > 5")
num_high = high.count("type % 10 == 1 and chen > 0.98 and ccen < 0.8 and tracks > 5")

chen_low = jt.hist(30, 0.9, 1.2)
ccen_low = jt.hist(60, 0, 1.2)
tracks_low = jt.hist(19, -0.5, 18.5)
chen_high = jt.hist(30, 0.9, 1.2)
ccen_high = jt.hist(60, 0, 1.2)
tracks_high = jt.hist(19, -0.5, 18.5)

chen_cont = jt.hist(30, 0.9, 1.2)

wle_cut = lambda type, chen, ccen, tracks: type % 10 == 1 and chen > 0.98 and ccen < 0.8 and tracks > 5

low.filter = lambda type, chen, ccen: type % 10 == 1 and chen > 0.9
high.filter = lambda type, chen, ccen: type % 10 == 1 and chen > 0.9

# chen_low.ntuple(low, "chen", low.filter)
# chen_high.ntuple(high, "chen", high.filter)
# chen_cont.ntuple(cont, "chen", low.filter)

for n in low:
#  if n.ccen < 0.8 and n.tracks > 5:
    chen_low.fill(n.chen)
#  if n.chen > 0.98 and n.tracks > 5:
    ccen_low.fill(n.ccen)
#  if n.chen > 0.98 and n.ccen < 0.8:
    tracks_low.fill(n.tracks)

for n in high:
#  if n.ccen < 0.8 and n.tracks > 5:
    chen_high.fill(n.chen)
#  if n.chen > 0.98 and n.tracks > 5:
    ccen_high.fill(n.ccen)
#  if n.chen > 0.98 and n.ccen < 0.8:
    tracks_high.fill(n.tracks)

chen_low.rootn()
ccen_low.rootn()
tracks_low.rootn()
chen_high.rootn()
ccen_high.rootn()
tracks_high.rootn()

x, y, dy = chen_low.bin_centers(), chen_low.values, chen_low.errors
p = biggles.FramedPlot()
p.add(biggles.Points(x, y, symboltype="filled circle", symbolsize=0.8))
p.add(biggles.SymmetricErrorBarsY(x, y, dy))
p.show()

x, y, dy = chen_high.bin_centers(), chen_high.values, chen_high.errors
p = biggles.FramedPlot()
p.add(biggles.Points(x, y, symboltype="filled circle", symbolsize=0.8))
p.add(biggles.SymmetricErrorBarsY(x, y, dy))
p.show()

x, y, dy = ccen_low.bin_centers(), ccen_low.values, ccen_low.errors
p = biggles.FramedPlot()
p.add(biggles.Points(x, y, symboltype="filled circle", symbolsize=0.8))
p.add(biggles.SymmetricErrorBarsY(x, y, dy))
p.show()

x, y, dy = ccen_high.bin_centers(), ccen_high.values, ccen_high.errors
p = biggles.FramedPlot()
p.add(biggles.Points(x, y, symboltype="filled circle", symbolsize=0.8))
p.add(biggles.SymmetricErrorBarsY(x, y, dy))
p.show()

x, y, dy = tracks_low.bin_centers(), tracks_low.values, tracks_low.errors
p = biggles.FramedPlot()
p.add(biggles.Points(x, y, symboltype="filled circle", symbolsize=0.8))
p.add(biggles.SymmetricErrorBarsY(x, y, dy))
p.show()

x, y, dy = tracks_high.bin_centers(), tracks_high.values, tracks_high.errors
p = biggles.FramedPlot()
p.add(biggles.Points(x, y, symboltype="filled circle", symbolsize=0.8))
p.add(biggles.SymmetricErrorBarsY(x, y, dy))
p.show()


chen_diff = chen_high/689636. - chen_low/997646.
x, y, dy = chen_diff.bin_centers(), chen_diff.values, chen_diff.errors
p = biggles.FramedPlot()
p.add(biggles.Points(x, y, symboltype="filled circle", symbolsize=0.8))
p.add(biggles.SymmetricErrorBarsY(x, y, dy))
p.show()
