execfile("/home/mccann/bin/python/jimtools.py")
p = pyxplot.PyxPlot("rootstab3")

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

def hadron(type):
  return type % 10 == 1

def gamgam(type):
  return int(floor(type / 10)) % 10 == 1

def bhabha(type):
  return int(floor(type / 100)) % 10 == 1

oldhist = pickle.load(open("rootstab2.p"))
low_count, high_count = 997646, 689636

lowtphi = oldhist["lowb_trackphi"]
hightphi = oldhist["highb_trackphi"]

p((lowtphi - hightphi).plot().errorbars(), xtitle=r"Biggest-$|\vec{p}|$ track $\phi$", ytitle=r"March $-$ April difference")
p.append_log("I'm using rootstab2's histograms.  (Normalized before taking difference.)")

low.filter = bhabha
high.filter = bhabha
low.optimize = ["p1x", "p1y", "p1z", "cosp", "cosn", "p2x", "p2y"]
high.optimize = ["p1x", "p1y", "p1z", "cosp", "cosn", "p2x", "p2y"]

lowb_pphi = hist(100, -pi, pi)
lowb_pcos = hist(100, -1, 1)
lowb_pcosregion = hist(100, -1, 1)
highb_pphi = hist(100, -pi, pi)
highb_pcos = hist(100, -1, 1)
highb_pcosregion = hist(100, -1, 1)

for n in low:
  cos1 = n.p1z/sqrt(n.p1x**2+n.p1y**2+n.p1z**2)
  if abs(n.cosp - cos1) < abs(n.cosn - cos1):
    phi = atan2(n.p1y, n.p1x)
  else:
    phi = atan2(n.p2y, n.p2x)

  lowb_pphi.fill(phi)
  lowb_pcos.fill(n.cosp)
  if -0.9 < phi < -0.4:
    lowb_pcosregion.fill(n.cosp)
lowb_pphi.rootn()
lowb_pcos.rootn()
lowb_pcosregion.rootn()
lowb_pphi /= low_count
lowb_pcos /= low_count
lowb_pcosregion /= low_count

for n in high:
  cos1 = n.p1z/sqrt(n.p1x**2+n.p1y**2+n.p1z**2)
  if abs(n.cosp - cos1) < abs(n.cosn - cos1):
    phi = atan2(n.p1y, n.p1x)
  else:
    phi = atan2(n.p2y, n.p2x)

  highb_pphi.fill(phi)
  highb_pcos.fill(n.cosp)
  if -0.9 < phi < -0.4:
    highb_pcosregion.fill(n.cosp)
highb_pphi.rootn()
highb_pcos.rootn()
highb_pcosregion.rootn()
highb_pphi /= high_count
highb_pcos /= high_count
highb_pcosregion /= high_count

p((lowb_pphi - highb_pphi).plot().errorbars(), y=graph.axis.linear(min=-1e-3, max=1e-3), xtitle=r"positive track $\phi$", ytitle=r"March $-$ April difference (normalized first)")
p.append_log(r"same as previous page, but I now choose the {\it positive} track", {"lowb_pphi":lowb_pphi, "highb_pphi":highb_pphi})


############################################

low.filter = bhabha
high.filter = bhabha
low.optimize = ["cos1", "cosp", "cosn", "phi1", "phi2"]
high.optimize = ["cos1", "cosp", "cosn", "phi1", "phi2"]

lowb_sphi = hist(256, -pi, pi)
highb_sphi = hist(256, -pi, pi)

for n in low:
  if abs(n.cosp - n.cos1) < abs(n.cosn - n.cos1):
    phi = n.phi1
  else:
    phi = n.phi2
  lowb_sphi.fill(phi)
lowb_sphi.rootn()
lowb_sphi /= low_count  

for n in high:
  if abs(n.cosp - n.cos1) < abs(n.cosn - n.cos1):
    phi = n.phi1
  else:
    phi = n.phi2
  highb_sphi.fill(phi)
highb_sphi.rootn()
highb_sphi /= high_count  

p(lowb_sphi.plot(), highb_sphi.plot().steps(style="dashed"), xtitle=r"shower-closest-to-positive-track $\phi$")
p.append_log("overlay", {"lowb_sphi":lowb_sphi, "highb_sphi":highb_sphi})

p((lowb_sphi - highb_sphi).plot().errorbars(), xtitle=r"shower-closest-to-positive-track $\phi$", y=graph.axis.linear(min=-1e-3, max=1e-3))
p.append_log("difference (same histos as prev page)")



############################################

low.filter = bhabha
high.filter = bhabha
low.optimize = ["cos1", "cos2", "cosp", "cosn"]
high.optimize = ["cos1", "cos2", "cosp", "cosn"]

lowb_scos = hist(200, -1, 1)
highb_scos = hist(200, -1, 1)

for n in low:
  if abs(n.cosp - n.cos1) < abs(n.cosn - n.cos1):
    thecos = n.cos1
  else:
    thecos = n.cos2
  lowb_scos.fill(thecos)
lowb_scos.rootn()
lowb_scos /= low_count  

for n in high:
  if abs(n.cosp - n.cos1) < abs(n.cosn - n.cos1):
    thecos = n.cos1
  else:
    thecos = n.cos2
  highb_scos.fill(thecos)
highb_scos.rootn()
highb_scos /= high_count  

p(lowb_scos.plot(), highb_scos.plot().steps(style="dashed"), xtitle=r"shower-closest-to-positive-track $\phi$")
p.append_log("overlay", {"lowb_scos":lowb_scos, "highb_scos":highb_scos})

p((lowb_scos - highb_scos).plot().errorbars(), xtitle=r"shower-closest-to-positive-track $\phi$")
p((lowb_scos - highb_scos).plot().errorbars(), xtitle=r"shower-closest-to-positive-track $\phi$", y=graph.axis.linear(min=-1e-3, max=1e-3))
p.append_log("difference (same histos as prev page)")



############################################

low_count = 1897574
high_count = 1328741

low.filter = lambda d0close, anyz: abs(d0close) < 0.005 and abs(anyz) < 0.075
high.filter = lambda d0close, anyz: abs(d0close) < 0.005 and abs(anyz) < 0.075
low.optimize = ["p1x", "p1y", "p1z", "visen", "run"]
high.optimize = ["p1x", "p1y", "p1z", "visen", "run"]

low_p1 = hist(120, 0, 1.2)
low_visen = hist(120, 0, 1.2)
high_p1 = hist(120, 0, 1.2)
high_visen = hist(120, 0, 1.2)

for n in low:
  p1 = sqrt(n.p1x**2 + n.p1y**2 + n.p1z**2) / runsummary[n.run].energy
  if n.visen > 0.4:
    low_p1.fill(p1)
  if p1 < 0.8:
    low_visen.fill(n.visen)
low_p1.rootn()
low_p1 /= low_count
low_visen.rootn()
low_visen /= low_count

for n in high:
  p1 = sqrt(n.p1x**2 + n.p1y**2 + n.p1z**2) / runsummary[n.run].energy
  if n.visen > 0.4:
    high_p1.fill(p1)
  if p1 < 0.8:
    high_visen.fill(n.visen)
high_p1.rootn()
high_p1 /= high_count
high_visen.rootn()
high_visen /= high_count

p(low_p1.plot(), high_p1.plot().steps(style="dashed"), xtitle=r"Biggest-momentum track with other hadron cuts")
p.append_log("(we keep events below 0.8)", {"low_p1":low_p1, "high_p1":high_p1})

p((low_p1 - high_p1).plot().errorbars(), xtitle=r"Biggest-momentum track with other hadron cuts")
p.append_log("this is the difference (same histos as prev page)")

p(low_visen.plot(), high_visen.plot().steps(style="dashed"), xtitle=r"Visible energy with other hadron cuts")
p.append_log("(we keep events above 0.4)", {"low_visen":low_visen, "high_visen":high_visen})

p((low_visen - high_visen).plot().errorbars(), xtitle=r"Visible energy with other hadron cuts")
p.append_log("this is the difference (same histos as prev page)")


