basedir = "/home/mccann/synthesis/"
import cPickle

run = []
energy = {}
dataset = {}
events = {}
bblumi = {}
for l in iter(open("/nfs/cleo3/Offline/InfoFiles/data/runinfo.runinfo")):
  ll = l.split()
  r = int(ll[0])
  e = float(ll[8])
  d = int(ll[-1][4:])  # chop off the "data" part of the string
  ev = int(ll[1])
  bb = float(ll[4])
  run.append(r)
  energy[r] = e
  dataset[r] = d
  events[r] = ev
  bblumi[r] = bb
execfile("badrun3S.py")

class RunSummary : pass
initialrunlist = []
runsummary = {}
for r in run:
  if 4.71 < energy[r] < 5.205 and not r in badruns3S:
    rec = RunSummary()
    if energy[r] < 4.87152:
      rec.res = 1
      if energy[r] < 4.72:
        rec.kind = 'c'
      elif energy[r] > 4.78:
        rec.kind = 'h'
      elif abs(energy[r] - 4.73019) < 0.0008:
        rec.kind = 'p'
      else:
        rec.kind = 's'
    elif energy[r] < 5.096025:
      rec.res = 2
      if energy[r] < 5.005:
        rec.kind = 'c'
      elif energy[r] > 5.0424:
        rec.kind = 'h'
      elif abs(energy[r] - 5.01285) < 0.0008:
        rec.kind = 'p'
      else:
        rec.kind = 's'
    else:
      rec.res = 3
      if energy[r] < 5.17:
        rec.kind = 'c'
      elif energy[r] > 5.195:
        rec.kind = 'h'
      elif abs(energy[r] - 5.1792) < 0.0008 and r < 126000:
        rec.kind = 'p'
      else:
        rec.kind = 's'
    rec.db = dataset[r]
    rec.energy = energy[r]
    initialrunlist.append(r)
    runsummary[r] = rec

# runinfo bb luminosities in nb^-1
# 304,268.1 non-peak 1s, 1,121,212.7 peak
# 579,405.9 non-peak 2s, 1,191,933.2 peak
# 582,462.7 non-peak 3s, 1,063,619.7 peak

def checklooksokay(f):
  import biggles, hist
  cont = []
  scan = []
  peak = []
  high = []
  conten = []
  scanen = []
  peaken = []
  highen = []
  for r in initialrunlist:
    if f(r):
      if runsummary[r].kind == 'c':
        cont.append(r)
        conten.append(runsummary[r].energy)
      if runsummary[r].kind == 's':
        scan.append(r)
        scanen.append(runsummary[r].energy)
      if runsummary[r].kind == 'p':
        peak.append(r)
        peaken.append(runsummary[r].energy)
      if runsummary[r].kind == 'h':
        high.append(r)
        highen.append(runsummary[r].energy)
  p = biggles.FramedPlot()
  if len(cont) > 0:
    p.add(biggles.Points(cont, conten, symbolstyle="dot", color="green"))
  if len(scan) > 0:
    p.add(biggles.Points(scan, scanen, symbolstyle="dot", color="red"))
  if len(peak) > 0:
    p.add(biggles.Points(peak, peaken, symbolstyle="dot", color="blue"))
  if len(high) > 0:
    p.add(biggles.Points(high, highen, symbolstyle="dot", color="red"))
  p.x1.label = "Run number"
  p.y1.label = "Beam energy in GeV"
  p.x2.label = "Red is scan/high, blue is peak, green is continuum"
  p.show()
  p.write_eps("initialrunlist_checklooksokay.eps")
# checklooksokay(lambda r: runsummary[r].res == 2)
# checklooksokay(lambda r: True)

cPickle.dump(initialrunlist, open(basedir+"lumieff/initialrunlist.p", 'w'), -1)
cPickle.dump(runsummary, open(basedir+"lumieff/runsummary.p", 'w'), -1)
