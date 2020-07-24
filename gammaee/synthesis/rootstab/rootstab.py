# HADRON CUTS
#    m_cut[0] = (v[k_trignum] > 0);
#    m_cut[1] = (fabs(v[k_d0close]) < 0.005);
#    m_cut[2] = (fabs(v[k_wz]) < 0.075  ||
# 	       (v[k_wz] == -1000.  &&  fabs(v[k_z0close]) < 0.075));
#    m_cut[3] = (v[k_p1] < 0.8);
#    m_cut[4] = (v[k_coolvisen] > 0.4);
#    m_cut[5] = (v[k_l4dec] > 0.);

# BHABHA CUTS
#    m_cut[0] = (v[k_trignum] > 0);
#    m_cut[1] = (v[k_oppositecharge] > 0);
#    m_cut[2] = (v[k_p2] > 0.7);
#    m_cut[3] = (fabs(v[k_d0close]) < 0.005);
#    m_cut[4] = (fabs(v[k_wz]) < 0.075  ||
# 	       (v[k_wz] == -1000.  &&  fabs(v[k_z0close]) < 0.075));
#    m_cut[5] = (v[k_eisr] < 0.2);
#    m_cut[6] = (v[k_econstr] < 0.2);
#    m_cut[7] = (v[k_cos1] < 0.79  &&  v[k_cos2] < 0.76) || (v[k_cos1] < 0.76  &&  v[k_cos2] < 0.79);
#    m_cut[8] = (v[k_e2] > 0.4);
#    m_cut[9] = (v[k_l4dec] > 0);

execfile("/home/mccann/bin/python/jimtools.py")
p = pyxplot.PyxPlot("rootstab2")

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

# low.stop = 100
# high.stop = 100

low.filter = hadron
high.filter = hadron
low.optimize = ["tracks", "visen", "ccen", "neue", "chen"]
high.optimize = ["tracks", "visen", "ccen", "neue", "chen"]

low_tracks = hist(*ibin(0, 18))
low_visen = hist(120, 0, 1.2)
low_ccen = hist(120, 0, 1.2)
low_neue = hist(120, 0, 1.2)
low_chen = hist(120, 0, 1.2)
high_tracks = hist(*ibin(0, 18))
high_visen = hist(120, 0, 1.2)
high_ccen = hist(120, 0, 1.2)
high_neue = hist(120, 0, 1.2)
high_chen = hist(120, 0, 1.2)

low_count = 0
for n in low:
  low_count += 1
  low_tracks.fill(n.tracks)
  low_visen.fill(n.visen)
  low_ccen.fill(n.ccen)
  low_neue.fill(n.neue)
  low_chen.fill(n.chen)

high_count = 0
for n in high:
  high_count += 1
  high_tracks.fill(n.tracks)
  high_visen.fill(n.visen)
  high_ccen.fill(n.ccen)
  high_neue.fill(n.neue)
  high_chen.fill(n.chen)

low_tracks.rootn()
low_visen.rootn()
low_ccen.rootn()
low_neue.rootn()
low_chen.rootn()
high_tracks.rootn()
high_visen.rootn()
high_ccen.rootn()
high_neue.rootn()
high_chen.rootn()

low_tracks /= low_count
low_visen /= low_count
low_ccen /= low_count
low_neue /= low_count
low_chen /= low_count
high_tracks /= high_count
high_visen /= high_count
high_ccen /= high_count
high_neue /= high_count
high_chen /= high_count

message = r"""My hadronic cuts, normalized to unit area.

solid (``low'' cross-section) is 16--17 March ("""+str(low_count)+""" events).

dashed (``high'' cross-section) is 13--14 April ("""+str(high_count)+""" events).

Errorbars are {\it really} small."""

p(low_tracks.plot(), high_tracks.plot().steps(style="dashed"), xtitle="Number of tracks")
p.append_log(message, {"low_tracks": low_tracks, "high_tracks": high_tracks})

p(low_visen.plot(), high_visen.plot().steps(style="dashed"), xtitle="Visible energy fraction")
p.append_log(message, {"low_visen": low_visen, "high_visen": high_visen})

p(low_ccen.plot(), high_ccen.plot().steps(style="dashed"), xtitle="CC energy fraction")
p.append_log(message, {"low_ccen": low_ccen, "high_ccen": high_ccen})

p(low_neue.plot(), high_neue.plot().steps(style="dashed"), xtitle="Neutral energy fraction")
p.append_log(message, {"low_neue": low_neue, "high_neue": high_neue})

p(low_chen.plot(), high_chen.plot().steps(style="dashed"), xtitle="Charged energy fraction")
p.append_log(message, {"low_chen": low_chen, "high_chen": high_chen})



low.filter = bhabha
high.filter = bhabha
low.optimize = ["run", "tracks", "cosp", "cosn", "p1x", "p1y", "p1z", "p2x", "p2y", "p2z", "eisr", "econstr", "e1", "e2", "e3", "phi1", "phi2", "cos1", "cos2"]
high.optimize = ["run", "tracks", "cosp", "cosn", "p1x", "p1y", "p1z", "p2x", "p2y", "p2z", "eisr", "econstr", "e1", "e2", "e3", "phi1", "phi2", "cos1", "cos2"]

lowb_tracks = hist(*ibin(0, 18))
lowb_cosp = hist(100, -1, 1)
lowb_cosn = hist(100, -1, 1)
lowb_trackphi = hist(100, -pi, pi)
lowb_p1 = hist(120, 0, 1.2)
lowb_p2 = hist(120, 0, 1.2)
lowb_p1perp = hist(120, 0, 1.2)
lowb_p2perp = hist(120, 0, 1.2)
lowb_eisr = hist(100, 0, 1)
lowb_econstr = hist(150, -1.5, 1)
lowb_e1 = hist(120, 0, 1.2)
lowb_e2 = hist(120, 0, 1.2)
lowb_e3 = hist(120, 0, 1.2)
lowb_phi1 = hist(100, -pi, pi)
lowb_phi2 = hist(100, -pi, pi)
lowb_cos1 = hist(100, -1, 1)
lowb_cos2 = hist(100, -1, 1)
highb_tracks = hist(*ibin(0, 18))
highb_cosp = hist(100, -1, 1)
highb_cosn = hist(100, -1, 1)
highb_trackphi = hist(100, -pi, pi)
highb_p1 = hist(120, 0, 1.2)
highb_p2 = hist(120, 0, 1.2)
highb_p1perp = hist(120, 0, 1.2)
highb_p2perp = hist(120, 0, 1.2)
highb_eisr = hist(100, 0, 1)
highb_econstr = hist(150, -1.5, 1)
highb_e1 = hist(120, 0, 1.2)
highb_e2 = hist(120, 0, 1.2)
highb_e3 = hist(120, 0, 1.2)
highb_phi1 = hist(100, -pi, pi)
highb_phi2 = hist(100, -pi, pi)
highb_cos1 = hist(100, -1, 1)
highb_cos2 = hist(100, -1, 1)

low_count = 0
for n in low:
  low_count += 1
  lowb_tracks.fill(n.tracks)
  lowb_cosp.fill(n.cosp)
  lowb_cosn.fill(n.cosn)
  lowb_trackphi.fill(atan2(n.p1y, n.p1x))
  lowb_p1.fill(sqrt(n.p1x**2 + n.p1y**2 + n.p1z**2)/runsummary[n.run].energy)
  lowb_p2.fill(sqrt(n.p2x**2 + n.p2y**2 + n.p2z**2)/runsummary[n.run].energy)
  lowb_p1perp.fill(sqrt(n.p1x**2 + n.p1y**2)/runsummary[n.run].energy)
  lowb_p2perp.fill(sqrt(n.p2x**2 + n.p2y**2)/runsummary[n.run].energy)
  lowb_eisr.fill(n.eisr)
  lowb_econstr.fill(n.econstr)
  lowb_e1.fill(n.e1)
  lowb_e2.fill(n.e2)
  lowb_e3.fill(n.e3)
  lowb_phi1.fill(n.phi1)
  lowb_phi2.fill(n.phi2)
  lowb_cos1.fill(n.cos1)
  lowb_cos2.fill(n.cos2)

high_count = 0
for n in high:
  high_count += 1
  highb_tracks.fill(n.tracks)
  highb_cosp.fill(n.cosp)
  highb_cosn.fill(n.cosn)
  highb_trackphi.fill(atan2(n.p1y, n.p1x))
  highb_p1.fill(sqrt(n.p1x**2 + n.p1y**2 + n.p1z**2)/runsummary[n.run].energy)
  highb_p2.fill(sqrt(n.p2x**2 + n.p2y**2 + n.p2z**2)/runsummary[n.run].energy)
  highb_p1perp.fill(sqrt(n.p1x**2 + n.p1y**2)/runsummary[n.run].energy)
  highb_p2perp.fill(sqrt(n.p2x**2 + n.p2y**2)/runsummary[n.run].energy)
  highb_eisr.fill(n.eisr)
  highb_econstr.fill(n.econstr)
  highb_e1.fill(n.e1)
  highb_e2.fill(n.e2)
  highb_e3.fill(n.e3)
  highb_phi1.fill(n.phi1)
  highb_phi2.fill(n.phi2)
  highb_cos1.fill(n.cos1)
  highb_cos2.fill(n.cos2)

pickle.dump((low_count, high_count, lowb_tracks, lowb_cosp, lowb_cosn, lowb_trackphi, lowb_p1, lowb_p2, lowb_p1perp, lowb_p2perp, lowb_eisr, lowb_econstr, lowb_e1, lowb_e2, lowb_e3, lowb_phi1, lowb_phi2, lowb_cos1, lowb_cos2, highb_tracks, highb_cosp, highb_cosn, highb_trackphi, highb_p1, highb_p2, highb_p1perp, highb_p2perp, highb_eisr, highb_econstr, highb_e1, highb_e2, highb_e3, highb_phi1, highb_phi2, highb_cos1, highb_cos2), open("tmp.p", "w"))

(low_count, high_count, lowb_tracks, lowb_cosp, lowb_cosn, lowb_trackphi, lowb_p1, lowb_p2, lowb_p1perp, lowb_p2perp, lowb_eisr, lowb_econstr, lowb_e1, lowb_e2, lowb_e3, lowb_phi1, lowb_phi2, lowb_cos1, lowb_cos2, highb_tracks, highb_cosp, highb_cosn, highb_trackphi, highb_p1, highb_p2, highb_p1perp, highb_p2perp, highb_eisr, highb_econstr, highb_e1, highb_e2, highb_e3, highb_phi1, highb_phi2, highb_cos1, highb_cos2) = pickle.load(open("tmp.p"))

hist_names = ["tracks", "cosp", "cosn", "trackphi", "p1", "p2", "p1perp", "p2perp", "eisr", "econstr", "e1", "e2", "e3", "phi1", "phi2", "cos1", "cos2"]

hist_titles = {"tracks": r"Number of tracks", \
               "cosp": r"Positive-track $\cos\theta$", \
               "cosn": r"Negative-track $\cos\theta$", \
               "trackphi": r"Biggest-$|\vec{p}|$ track $\phi$", \
               "p1": r"$|\vec{p}_1| / E_{beam}$", \
               "p2": r"$|\vec{p}_2| / E_{beam}$", \
               "p1perp": r"$(\vec{p}_1)_T / E_{beam}$", \
               "p2perp": r"$(\vec{p}_2)_T / E_{beam}$", \
               "eisr": r"$|\vec{p}_1 + \vec{p}_2| / E_{beam}$", \
               "econstr": r"$(2 E_{beam} - |\vec{p}_1| - |\vec{p}_2| - |\vec{p}_1 + \vec{p}_2|)/(2 E_{beam})$", \
               "e1": r"Biggest-shower energy / $E_{beam}$", \
               "e2": r"Second-biggest shower energy / $E_{beam}$", \
               "e3": r"Third-biggest shower energy / $E_{beam}$", \
               "phi1": r"Biggest-shower $\phi$", \
               "phi2": r"Second-biggest shower $\phi$", \
               "cos1": r"Biggest-shower $\cos\theta$", \
               "cos2": r"Second-biggest shower $\cos\theta$"}

hist_logy = {"tracks": True, \
             "cosp": False, \
             "cosn": False, \
             "trackphi": False, \
             "p1": True, \
             "p2": True, \
             "p1perp": True, \
             "p2perp": True, \
             "eisr": False, \
             "econstr": True, \
             "e1": False, \
             "e2": False, \
             "e3": False, \
             "phi1": False, \
             "phi2": False, \
             "cos1": False, \
             "cos2": False}

for n in hist_names:
  exec "lowb_"+n+".rootn()"
  exec "lowb_"+n+" /= low_count"
  exec "highb_"+n+".rootn()"
  exec "highb_"+n+" /= high_count"

message = r"""My bhabha cuts, normalized to unit area.

solid (``low'' cross-section) is 16--17 March ("""+str(low_count)+""" events).

dashed (``high'' cross-section) is 13--14 April ("""+str(high_count)+""" events).

Errorbars are {\it really} small."""

for n in hist_names[4:]:
  exec "p(lowb_"+n+".plot(), highb_"+n+".plot().steps(style=\"dashed\", logy="+str(hist_logy[n])+"), xtitle=r\""+hist_titles[n]+"\", logy="+str(hist_logy[n])+")"
  raw_input()
  exec "p.append_log(message, {\"lowb_"+n+"\": lowb_"+n+", \"highb_"+n+"\": highb_"+n+"})"
  raw_input()



low.filter = bhabha
high.filter = bhabha
low.optimize = ["e1", "e2"]
high.optimize = ["e1", "e2"]

big1sum = 0.
big2sum = 0.
big1sum2 = 0.
big2sum2 = 0.
total = 0
for n in low:
  big1sum += n.e1
  big2sum += n.e2
  big1sum2 += n.e1**2
  big2sum2 += n.e2**2
  total += 1
print "big1", big1sum/total, sqrt(big1sum2/total - (big1sum/total)**2)/sqrt(total)
print "big2", big2sum/total, sqrt(big2sum2/total - (big2sum/total)**2)/sqrt(total)

big1sum = 0.
big2sum = 0.
big1sum2 = 0.
big2sum2 = 0.
total = 0
for n in high:
  big1sum += n.e1
  big2sum += n.e2
  big1sum2 += n.e1**2
  big2sum2 += n.e2**2
  total += 1
print "big1", big1sum/total, sqrt(big1sum2/total - (big1sum/total)**2)/sqrt(total)
print "big2", big2sum/total, sqrt(big2sum2/total - (big2sum/total)**2)/sqrt(total)







low.filter = None
low.optimize = ["type", "cosp"]
high.filter = None
high.optimize = ["type", "cosp"]

low_hadrons = 0
low_bhabhas = 0
low_outerbhabhas = 0
for n in low:
  if hadron(n.type): low_hadrons += 1
  if bhabha(n.type): low_bhabhas += 1
  if bhabha(n.type) and 0.6 < n.cosp < 0.8: low_outerbhabhas += 1

high_hadrons = 0
high_bhabhas = 0
high_outerbhabhas = 0
for n in high:
  if hadron(n.type): high_hadrons += 1
  if bhabha(n.type): high_bhabhas += 1
  if bhabha(n.type) and 0.6 < n.cosp < 0.8: high_outerbhabhas += 1

print "low", low_hadrons, low_bhabhas, 1.*low_hadrons / low_bhabhas
print "high", high_hadrons, high_bhabhas, 1.*high_hadrons / high_bhabhas

print "low outer", low_hadrons, low_outerbhabhas, 1.*low_hadrons / low_outerbhabhas
print "high outer", high_hadrons, high_outerbhabhas, 1.*high_hadrons / high_outerbhabhas


