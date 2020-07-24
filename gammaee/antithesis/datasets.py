execfile("utilities.py")
nobeam = getsb("cos")
ebeam = getsb("bge")
pbeam = getsb("bgp")

peak1 = getrd(1, "peak", "all")
cont1 = getrd(1, "cont", "all")
peak2 = getrd(2, "peak", "all")
cont2 = getrd(2, "cont", "all")
peak3 = getrd(3, "peak", "all")
cont3 = getrd(3, "cont", "all")
cont = cont1 + cont2 + cont3
peak = peak1 + peak2 + peak3
data = peak1 + cont1 + peak2 + cont2 + peak3 + cont3

mc1 = {}
mc1["ggg"] = getmc(1, "ggg")
mc1["gggam"] = getmc(1, "gggam")
mc1["qq"] = getmc(1, "qq")
mc1["ee0"] = getmc(1, "ee0")
mc1["ee"] = getmc(1, "ee")
mc1["mumu0"] = getmc(1, "mumu0")
mc1["mumu"] = getmc(1, "mumu")
mc1["tautau"] = getmc(1, "tautau")

mc2 = {}
mc2["ggg"] = getmc(2, "ggg")
mc2["gggam"] = getmc(2, "gggam")
mc2["qq"] = getmc(2, "qq")
mc2["ee0"] = getmc(2, "ee0")
mc2["ee"] = getmc(2, "ee")
mc2["mumu0"] = getmc(2, "mumu0")
mc2["mumu"] = getmc(2, "mumu")
mc2["tautau"] = getmc(2, "tautau")
mc2["cas"] = getmc(2, "cas")
mc2["casll0"] = getmc(2, "casll0")
mc2["casll"] = getmc(2, "casll")

mc3 = {}
mc3["ggg"] = getmc(3, "ggg")
mc3["gggam"] = getmc(3, "gggam")
mc3["qq"] = getmc(3, "qq")
mc3["ee0"] = getmc(3, "ee0")
mc3["ee"] = getmc(3, "ee")
mc3["mumu0"] = getmc(3, "mumu0")
mc3["mumu"] = getmc(3, "mumu")
mc3["tautau"] = getmc(3, "tautau")
mc3["cas"] = getmc(3, "cas")
mc3["casll0"] = getmc(3, "casll0")
mc3["casll"] = getmc(3, "casll")

mc1all = domc1(promptleptons=False)
mc2all = domc2(promptleptons=False)
mc3all = domc3(promptleptons=False)

mc1all = domc1()
mc2all = domc2()
mc3all = domc3()

ptoc1 = (peak1.hadron * (mc1all.bhabha / mc1all.hadron) - peak1.bhabha) \
        / (cont1.hadron * (mc1all.bhabha / mc1all.hadron) - cont1.bhabha)
ptoc2 = (peak2.hadron * (mc2all.bhabha / mc2all.hadron) - peak2.bhabha) \
        / (cont2.hadron * (mc2all.bhabha / mc2all.hadron) - cont2.bhabha)
ptoc3 = (peak3.hadron * (mc3all.bhabha / mc3all.hadron) - peak3.bhabha) \
        / (cont3.hadron * (mc3all.bhabha / mc3all.hadron) - cont3.bhabha)

# ptoc1 = float(peak1.gamgam) / float(cont1.gamgam)
# ptoc2 = float(peak2.gamgam) / float(cont2.gamgam)
# ptoc3 = float(peak3.gamgam) / float(cont3.gamgam)

ptomc1 = (peak1.hadron - (cont1.hadron * ptoc1)) / mc1all.hadron
ptomc2 = (peak2.hadron - (cont2.hadron * ptoc2)) / mc2all.hadron
ptomc3 = (peak3.hadron - (cont3.hadron * ptoc3)) / mc3all.hadron

############################################################

ptoc = 1.*(peak1.gamgam+peak2.gamgam+peak3.gamgam)/(cont1.gamgam+cont2.gamgam+cont3.gamgam)

p = cont.hadroncool_r_coolvisen.plot()
p.add((peak.hadroncool_r_coolvisen / ptoc).steps(linetype="dashed"))
p.add(biggles.LineX(0.4, linetype="dotted"))
p.aspect_ratio = 0.5
p.x1.label = "Visible energy / center-of-mass energy"
p.show()
p.write_eps("plots/proceedings_visen.eps")

############################################################

def ups_overlay(res, histogram, line1=None, line2=None):
  da = eval("peak"+str(res)+"."+str(histogram)+" - " \
            "cont"+str(res)+"."+str(histogram)+" * ptoc"+str(res))
  mc = eval("mc"+str(res)+"all."+str(histogram)+" * ptomc"+str(res))
  p = da.plot(False, points=True, errorbars=True)
  p.add(mc.steps())
  if line1 != None:
    p.add(biggles.LineX(line1, linetype="dotted"))
  if line2 != None:
    p.add(biggles.LineX(line2, linetype="dotted"))
  return p

# ups_overlay(1, "beamgasp_logwz", log10(0.075)).show()
# ups_overlay(2, "beamgasp_logwz", log10(0.075)).show()
# ups_overlay(3, "beamgasp_logwz", log10(0.075)).show()

res1 = peak1 + (cont1 * -ptoc1)
res2 = peak2 + (cont2 * -ptoc2)
res3 = peak3 + (cont3 * -ptoc3)

p = biggles.FramedArray(4,1)

ehist = ebeam.beamgase_wpz * cont.beamgase / ebeam.beamgase
phist = pbeam.beamgasp_wpz * cont.beamgasp / pbeam.beamgasp
p[0,0].add((ehist+phist).stepsfill(color=0x999999))
p[0,0].add(phist.stepsfill(color=0xdddddd))
p[0,0].add((ehist+phist).steps())
p[0,0].add(phist.steps())
p[0,0].add(cont.beamgasp_wpz.points(symboltype="filled circle", symbolsize=1))
p[0,0].add(cont.beamgasp_wpz.errorbars())
p[0,0].add(biggles.LineY(0.))
p[0,0].add(biggles.PlotLabel(0.05, 0.8, "(a)"))
p[0,0].add(biggles.LineX(-0.1, linetype="dotted"))
p[0,0].add(biggles.LineX(0.1, linetype="dotted"))

ehist =ebeam.beamgase_wpz * res1.beamgase / ebeam.beamgase
phist = pbeam.beamgasp_wpz * res1.beamgasp / pbeam.beamgasp
p[1,0].add((ehist+phist).stepsfill(color=0x999999))
p[1,0].add(phist.stepsfill(color=0xdddddd))
p[1,0].add((ehist+phist).steps())
p[1,0].add(phist.steps())
p[1,0].add(res1.beamgasp_wpz.points(symboltype="filled circle", symbolsize=1))
p[1,0].add(res1.beamgasp_wpz.errorbars())
p[1,0].add(biggles.LineY(0.))
p[1,0].add(biggles.PlotLabel(0.05, 0.8, "(b)"))

ehist =ebeam.beamgase_wpz * res2.beamgase / ebeam.beamgase
phist = pbeam.beamgasp_wpz * res2.beamgasp / pbeam.beamgasp
p[2,0].add((ehist+phist).stepsfill(color=0x999999))
p[2,0].add(phist.stepsfill(color=0xdddddd))
p[2,0].add((ehist+phist).steps())
p[2,0].add(phist.steps())
p[2,0].add(res2.beamgasp_wpz.points(symboltype="filled circle", symbolsize=1))
p[2,0].add(res2.beamgasp_wpz.errorbars())
p[2,0].add(biggles.LineY(0.))
p[2,0].add(biggles.PlotLabel(0.05, 0.8, "(c)"))

ehist =ebeam.beamgase_wpz * res3.beamgase / ebeam.beamgase
phist = pbeam.beamgasp_wpz * res3.beamgasp / pbeam.beamgasp
p[3,0].add((ehist+phist).stepsfill(color=0x999999))
p[3,0].add(phist.stepsfill(color=0xdddddd))
p[3,0].add((ehist+phist).steps())
p[3,0].add(phist.steps())
p[3,0].add(res3.beamgasp_wpz.points(symboltype="filled circle", symbolsize=1))
p[3,0].add(res3.beamgasp_wpz.errorbars())
p[3,0].add(biggles.LineY(0.))
p[3,0].add(biggles.PlotLabel(0.05, 0.8, "(d)"))

p.xrange = -1, 1
p.yrange = -99, 99
p[0,0].yrange = 0, 800
p.xlabel = r"Beam-gas $\Sigma p_z$ for continuum and three resonances"
p.aspect_ratio = 1
p.show()
p.write_eps("plots/datasets_beamgas.eps")


#################

# ebeam1 = ebeam * cont1.beamgase / ebeam.beamgase
# pbeam1 = pbeam * cont1.beamgasp / pbeam.beamgasp
# ebeam2 = ebeam * cont2.beamgase / ebeam.beamgase
# pbeam2 = pbeam * cont2.beamgasp / pbeam.beamgasp
# ebeam3 = ebeam * cont3.beamgase / ebeam.beamgase
# pbeam3 = pbeam * cont3.beamgasp / pbeam.beamgasp

cont_nobg = cont + (ebeam * -cont.beamgase / ebeam.beamgase) + (pbeam * -cont.beamgasp / pbeam.beamgasp)
res1_nobg = res1 + (ebeam * -res1.beamgase / ebeam.beamgase) + (pbeam * -res1.beamgasp / pbeam.beamgasp)
res2_nobg = res2 + (ebeam * -res2.beamgase / ebeam.beamgase) + (pbeam * -res2.beamgasp / pbeam.beamgasp)
res3_nobg = res3 + (ebeam * -res3.beamgase / ebeam.beamgase) + (pbeam * -res3.beamgasp / pbeam.beamgasp)

p = biggles.FramedArray(4,1)

### do you really want cont.cosmic_logd0close or cont_nobg.cosmic_logd0close ???
# # you really want cont.cosmic_logd0close, since this agrees with the caption
chist = logify(nobeam.cosmic_logd0close * cont.cosmic / nobeam.cosmic)
p[0,0].add(chist.stepsfill(color=0xdddddd))
p[0,0].add(chist.steps())
p[0,0].add(logify(cont.cosmic_logd0close).points(symboltype="filled circle", symbolsize=1))
p[0,0].add(logify(cont.cosmic_logd0close).errorbars())
p[0,0].add(biggles.LineY(0.))
p[0,0].add(biggles.PlotLabel(0.05, 0.8, "(a)"))
p[0,0].add(biggles.LineX(0.005, linetype="dotted"))
p[0,0].yrange = 0, 3500

chist = logify(nobeam.cosmic_logd0close * res1_nobg.cosmic / nobeam.cosmic)
p[1,0].add(chist.stepsfill(color=0xdddddd))
p[1,0].add(chist.steps())
p[1,0].add(logify(res1_nobg.cosmic_logd0close).points(symboltype="filled circle", symbolsize=1))
p[1,0].add(logify(res1_nobg.cosmic_logd0close).errorbars())
p[1,0].add(biggles.LineY(0.))
p[1,0].add(biggles.PlotLabel(0.05, 0.8, "(b)"))
p[1,0].yrange = -499, 499

chist = logify(nobeam.cosmic_logd0close * res2_nobg.cosmic / nobeam.cosmic)
p[2,0].add(chist.stepsfill(color=0xdddddd))
p[2,0].add(chist.steps())
p[2,0].add(logify(res2_nobg.cosmic_logd0close).points(symboltype="filled circle", symbolsize=1))
p[2,0].add(logify(res2_nobg.cosmic_logd0close).errorbars())
p[2,0].add(biggles.LineY(0.))
p[2,0].add(biggles.PlotLabel(0.05, 0.8, "(c)"))
p[2,0].yrange = -499, 499

chist = logify(nobeam.cosmic_logd0close * res3_nobg.cosmic / nobeam.cosmic)
p[3,0].add(chist.stepsfill(color=0xdddddd))
p[3,0].add(chist.steps())
p[3,0].add(logify(res3_nobg.cosmic_logd0close).points(symboltype="filled circle", symbolsize=1))
p[3,0].add(logify(res3_nobg.cosmic_logd0close).errorbars())
p[3,0].add(biggles.LineY(0.))
p[3,0].add(biggles.PlotLabel(0.05, 0.8, "(d)"))
p[3,0].yrange = -499, 499

p.xlog = 1
p.xrange = 1e-7, 1
p.xlabel = r"Cosmic ray $d_{XY}$ for continuum and three resonances"
p.aspect_ratio = 1
p.show()
p.write_eps("plots/datasets_cosmic.eps")



############################################

ebeam_cosmic_factor = float(ebeam.cosmic)/float(nobeam.cosmic)
pbeam_cosmic_factor = float(pbeam.cosmic)/float(nobeam.cosmic)

p = biggles.FramedArray(2,1)
p1a = logify(ebeam.cosmic_logpdotp).steps()
p1a.label = r"$e^-$-beam"
p[0,0].add(logify((nobeam.cosmic_logpdotp * ebeam_cosmic_factor)).stepsfill(color=0xdddddd))
p2a = logify((nobeam.cosmic_logpdotp * ebeam_cosmic_factor)).steps(linetype="longdashed")
p2a.label = r"no-beam"
p3a = biggles.LineX(0.1, linetype="dotted")
p3a.label = "cuts"
p4a = biggles.LineX(0.001, linetype="dotted")
p[0,0].add(p1a)
p[0,0].add(p2a)
p[0,0].add(p3a)
p[0,0].add(p4a)
p[0,0].add(biggles.PlotLabel(0.07, 0.87, "(a)"))
p[0,0].add(biggles.PlotKey(0.07, 0.75, [p1a, p2a, p3a]))
p[0,0].yrange = 0, 300
p1b = logify(pbeam.cosmic_logpdotp).steps()
p1b.label = r"$e^+$-beam"
p[1,0].add(logify((nobeam.cosmic_logpdotp * pbeam_cosmic_factor)).stepsfill(color=0xdddddd))
p2b = logify((nobeam.cosmic_logpdotp * pbeam_cosmic_factor)).steps(linetype="longdashed")
p2b.label = r"no-beam"
p3b = biggles.LineX(0.1, linetype="dotted")
p3b.label = "cuts"
p4b = biggles.LineX(0.001, linetype="dotted")
p[1,0].add(p1b)
p[1,0].add(p2b)
p[1,0].add(p3b)
p[1,0].add(p4b)
p[1,0].add(biggles.PlotLabel(0.07, 0.87, "(b)"))
p[1,0].add(biggles.PlotKey(0.07, 0.75, [p1b, p2b, p3b]))
p[1,0].yrange = 0, 69
p.xlog = 1
p.xrange = 1e-10, 1
p.xlabel = r"$1 - |p_1\cdot p_2|$"
p.show()
p.write_eps("plots/datasets_cosmicscale.eps")


#################################################
# my super awesome plot

execfile("/home/mccann/antithesis/utilities.py")
nobeam = getsb("cos")
ebeam = getsb("bge")
pbeam = getsb("bgp")
runstart = pickle.load(open("/home/mccann/antithesis/old_dotps/runstart.p"))
runend = pickle.load(open("/home/mccann/antithesis/old_dotps/runend.p"))
import time
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

u1runs = {}
u2runs = {}
u3runs = {}

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


whatilldo = []
for theresruns in (u1runs, u2runs, u3runs):
  for thescan in theresruns:
    for r in theresruns[thescan]:
      whatilldo.append(r)

tmprunlist = []
efrac = []
pfrac = []
cfrac = []
efrac_err = []
pfrac_err = []
cfrac_err = []
bgerun = {}
bgprun = {}
cosrun = {}
# for r in initialrunlist:
for r in whatilldo:
  if r not in mybadruns:
    tmprunlist.append(r)
    runhists = getdb(r)
    e = 1. * (ebeam.hadroncool - 1.*nobeam.hadroncool*ebeam.cosmic/nobeam.cosmic) * runhists.beamgase / ebeam.beamgase / runhists.gamgam
    p = 1. * (pbeam.hadroncool - 1.*nobeam.hadroncool*pbeam.cosmic/nobeam.cosmic) * runhists.beamgasp / pbeam.beamgasp / runhists.gamgam
    c = 1. * nobeam.hadroncool * runhists.cosmic / nobeam.cosmic / runhists.gamgam
    ee = e * sqrt(1./runhists.beamgase + 1./runhists.gamgam)
    pe = p * sqrt(1./runhists.beamgasp + 1./runhists.gamgam)
    ce = c * sqrt(1./runhists.cosmic + 1./runhists.gamgam)
    efrac.append(e)
    pfrac.append(p)
    cfrac.append(c)
    efrac_err.append(ee)
    pfrac_err.append(pe)
    cfrac_err.append(ce)
efrac = Numeric.array(efrac)
pfrac = Numeric.array(pfrac)
cfrac = Numeric.array(cfrac)
efrac_err = Numeric.array(efrac_err)
pfrac_err = Numeric.array(pfrac_err)
cfrac_err = Numeric.array(cfrac_err)
# 7.55 hadrons per gamgam in continuum
efrac /= 7.55
pfrac /= 7.55
cfrac /= 7.55
efrac_err /= 7.55
pfrac_err /= 7.55
cfrac_err /= 7.55

tmprunlist_rd = []
efrac_rd = []
pfrac_rd = []
cfrac_rd = []
for r, e, p, c in zip(tmprunlist, efrac, pfrac, cfrac):
  if r in rdrunlists["all"]:
    tmprunlist_rd.append(r)
    efrac_rd.append(e)
    pfrac_rd.append(p)
    cfrac_rd.append(c)
tmprunlist_rd = Numeric.array(tmprunlist_rd)
efrac_rd = Numeric.array(efrac_rd)
pfrac_rd = Numeric.array(pfrac_rd)
cfrac_rd = Numeric.array(cfrac_rd)
    
# global uncertainties:
print "global cfrac (fractional) uncertainty", sqrt(1./nobeam.hadroncool + 1./nobeam.cosmic)
print "global efrac (fractional) uncertainty", sqrt(2./ebeam.hadroncool + 1./ebeam.beamgase)
print "global pfrac (fractional) uncertainty", sqrt(2./pbeam.hadroncool + 1./pbeam.beamgasp)

p = biggles.FramedArray(3,1)
p[1,0].add(biggles.Points(tmprunlist, efrac*100, type="filled circle", size=1))
p[1,0].add(biggles.SymmetricErrorBarsY(tmprunlist, efrac*100, efrac_err*100))
p[1,0].add(biggles.Points(tmprunlist_rd, efrac_rd*100, type="circle", size=10))
p[2,0].add(biggles.Points(tmprunlist, pfrac*100, type="filled circle", size=1))
p[2,0].add(biggles.SymmetricErrorBarsY(tmprunlist, pfrac*100, pfrac_err*100))
p[2,0].add(biggles.Points(tmprunlist_rd, pfrac_rd*100, type="circle", size=10))
p[0,0].add(biggles.Points(tmprunlist, cfrac*100, type="filled circle", size=1))
p[0,0].add(biggles.SymmetricErrorBarsY(tmprunlist, cfrac*100, cfrac_err*100))
p[0,0].add(biggles.Points(tmprunlist_rd, cfrac_rd*100, type="circle", size=10))

# p.show()  # LOOK FIRST!!!
# raw_input("Look at that plot: is everything below 5%?")
# for r, c, e, p in zip(tmprunlist, cfrac, efrac, pfrac):
#   if c > 0.05 or e > 0.02 or p > 0.02:
#     print "bad run", r, "cfrac", c, "efrac", e, "pfrac", p

p[0,0].yrange = 0, 4
p[1,0].yrange = 0, 0.999
p[2,0].yrange = 0, 0.999
p[1,0].add(biggles.PlotLabel(0.03, 0.8, r"(b) $e^-$ beam-gas", halign="left"))
p[2,0].add(biggles.PlotLabel(0.03, 0.8, r"(c) $e^+$ beam-gas", halign="left"))
p[0,0].add(biggles.PlotLabel(0.03, 0.8, r"(a) cosmic rays", halign="left"))
p[0,0].add(biggles.LineX(123102.5, type="dotted"))
p[0,0].add(biggles.LineX(125651.5, type="dotted"))
p[1,0].add(biggles.LineX(123102.5, type="dotted"))
p[1,0].add(biggles.LineX(125651.5, type="dotted"))
p[2,0].add(biggles.LineX(123102.5, type="dotted"))
p[2,0].add(biggles.LineX(125651.5, type="dotted"))
p.ylabel = "Percentage of continuum hadrons"
p.xlabel = "Run number"
p.aspect_ratio = 1
p.show()
# p.write_eps("plots/datasets_databasecontamination.eps")
p.write_eps("/cdat/dafe/mccann/the-ark/datasets_databasecontamination.eps")

if initialrunlist[0] in mybadruns:
  print "You've got a problem!!!"
alldata_cosmic_logd0close = getdb(initialrunlist[0]).cosmic_logd0close
alldata_beamgas_loganyz = getdb(initialrunlist[0]).beamgase_loganyz
alldata_beamgas_loganyz += getdb(initialrunlist[0]).beamgasp_loganyz
for r in initialrunlist[1:]:
  if r not in mybadruns:
    runhists = getdb(r)
    alldata_cosmic_logd0close += runhists.cosmic_logd0close
    alldata_beamgas_loganyz += runhists.beamgase_loganyz
    alldata_beamgas_loganyz += runhists.beamgasp_loganyz

scale_factor1 = alldata_cosmic_logd0close.sum(log10(0.005), 0) / nobeam.cosmic_logd0close.sum(log10(0.005), 0)
scale_factor2 = alldata_beamgas_loganyz.sum(log10(0.075), 0) / (ebeam.beamgase_loganyz.sum(log10(0.075), 0) + pbeam.beamgasp_loganyz.sum(log10(0.075), 0))

overlay1 = nobeam.cosmic_logd0close * scale_factor1
overlay2 = (ebeam.beamgase_loganyz + pbeam.beamgasp_loganyz) * scale_factor2

p = biggles.Table(2,1)
p[0,0] = logify(alldata_cosmic_logd0close).plot()
p[0,0].add(logify(overlay1).points(symbolsize=1))
p[0,0].add(logify(overlay1).errorbars())
p[0,0].add(biggles.LineX(0.005, type="dotted"))
p[0,0].add(biggles.PlotLabel(0.07, 0.85, "(a)"))
p[0,0].x1.log = 1
p[0,0].x1.label = r"$d_{XY}$ with cosmic ray cuts"
p[0,0].x1.range = 1e-7, 1.
p[0,0].y1.range = 0, max(overlay1.vals) * 1.2
p[1,0] = logify(alldata_beamgas_loganyz).plot()
p[1,0].add(logify(overlay2).points(symbolsize=1))
p[1,0].add(logify(overlay2).errorbars())
p[1,0].add(biggles.LineX(0.075, type="dotted"))
p[1,0].add(biggles.PlotLabel(0.07, 0.85, "(b)"))
p[1,0].x1.log = 1
p[1,0].x1.label = r"$d_{Z}$ with beam-gas cuts"
p[1,0].x1.range = 1e-6, 1.
p[1,0].y1.range = 0, max(overlay2.vals) * 1.2
p.aspect_ratio = 1
p.show()
p.write_eps("plots/datasets_database_dxydzcuts.eps")




oneovers_x = [cont1.ebeam, cont2.ebeam, cont3.ebeam]
oneovers_y1 = [1.*cont1.hadron_r_coolvisen.sum(0,0.4)/cont1.bhabha/cont1.ebeam**2, \
               1.*cont2.hadron_r_coolvisen.sum(0,0.4)/cont2.bhabha/cont2.ebeam**2, \
               1.*cont3.hadron_r_coolvisen.sum(0,0.4)/cont3.bhabha/cont3.ebeam**2]
oneovers_y1err = [1.*cont1.hadron_r_coolvisen.sum(0,0.4)/cont1.bhabha/cont1.ebeam**2*sqrt(1./cont1.hadron_r_coolvisen.sum(0,0.4) + 1./cont1.bhabha), \
                  1.*cont2.hadron_r_coolvisen.sum(0,0.4)/cont2.bhabha/cont2.ebeam**2*sqrt(1./cont2.hadron_r_coolvisen.sum(0,0.4) + 1./cont2.bhabha), \
                  1.*cont3.hadron_r_coolvisen.sum(0,0.4)/cont3.bhabha/cont3.ebeam**2*sqrt(1./cont3.hadron_r_coolvisen.sum(0,0.4) + 1./cont3.bhabha)]

oneovers_y2 = [1.*cont1.hadron_r_coolvisen.sum(0.4,1.2)/cont1.bhabha/cont1.ebeam**2, \
               1.*cont2.hadron_r_coolvisen.sum(0.4,1.2)/cont2.bhabha/cont2.ebeam**2, \
               1.*cont3.hadron_r_coolvisen.sum(0.4,1.2)/cont3.bhabha/cont3.ebeam**2]
oneovers_y2err = [1.*cont1.hadron_r_coolvisen.sum(0.4,1.2)/cont1.bhabha/cont1.ebeam**2*sqrt(1./cont1.hadron_r_coolvisen.sum(0.4,1.2) + 1./cont1.bhabha), \
                  1.*cont2.hadron_r_coolvisen.sum(0.4,1.2)/cont2.bhabha/cont2.ebeam**2*sqrt(1./cont2.hadron_r_coolvisen.sum(0.4,1.2) + 1./cont2.bhabha), \
                  1.*cont3.hadron_r_coolvisen.sum(0.4,1.2)/cont3.bhabha/cont3.ebeam**2*sqrt(1./cont3.hadron_r_coolvisen.sum(0.4,1.2) + 1./cont3.bhabha)]



oneovers_x = [cont1.ebeam, cont2.ebeam, cont3.ebeam]
oneovers_y2 = [1.*cont1.hadroncool/cont1.bhabha/cont1.ebeam**2, \
               1.*cont2.hadroncool/cont2.bhabha/cont2.ebeam**2, \
               1.*cont3.hadroncool/cont3.bhabha/cont3.ebeam**2]
oneovers_y2err = [1.*cont1.hadroncool/cont1.bhabha/cont1.ebeam**2*sqrt(1./cont1.hadroncool + 1./cont1.bhabha), \
                  1.*cont2.hadroncool/cont2.bhabha/cont2.ebeam**2*sqrt(1./cont2.hadroncool + 1./cont2.bhabha), \
                  1.*cont3.hadroncool/cont3.bhabha/cont3.ebeam**2*sqrt(1./cont3.hadroncool + 1./cont3.bhabha)]



from minuit import *
def fitto_y1(a, b):
  chi2 = 0.
  for x, y, e in zip(oneovers_x, oneovers_y1, oneovers_y1err):
    chi2 += (a*log(x**2) + b/x**2 - y)**2 / e**2
  return chi2
def fitto_y2(a, b):
  chi2 = 0.
  for x, y, e in zip(oneovers_x, oneovers_y2, oneovers_y2err):
    chi2 += (a*log(x**2) + b/x**2 - y)**2 / e**2
  return chi2
def fitto_y2_correctly(a, b):
  chi2 = 0.
  for x, y, e in zip(oneovers_x, oneovers_y2, oneovers_y2err):
    chi2 += (a*(b*log(x**2/4.65**2) + (1.-b)*4.65*2/x**2) - y)**2 / e**2
  return chi2

curve_x = Numeric.arange(4.6, 5.3, 0.01)
curve_y1 = Numeric.arange(4.6, 5.3, 0.01)
curve_y2 = Numeric.arange(4.6, 5.3, 0.01)

m1 = Minuit(fitto_y1)
m1.migrad()
for i, x in enumerate(curve_x):
  curve_y1[i] = m1.values[0]*log(x**2) + m1.values[1]/x**2

m2 = Minuit(fitto_y2)
m2.migrad()
for i, x in enumerate(curve_x):
  curve_y2[i] = m2.values[0]*log(x**2) + m2.values[1]/x**2

print m1.values[0]/m1.values[1] # 90%, or 20% if you exclude the really low visen stuff
print m2.values[0]/m2.values[1] # 0.15%, up to 0.31% if you imagine 1%
                                # cosmic rays in the 2S and 2% in the
                                # 3S (most extreme case)
print Numeric.array(zip(m2.values, m2.errors)) * 100

print m1.fval, m2.fval # C.L. of chi^2/1 dof = 5.85 is some 2%, but 46
                       # is ridiculous


print cont1.hadron_r_coolvisen.sum(0,0.4) / cont1.hadron_r_coolvisen.sum(0,1.2) # 63% is below this cut


p = biggles.Table(2,1)
p[0,0] = (cont1.hadron_r_coolvisen / cont1.bhabha / cont1.ebeam**2).plot()
p[0,0].add((cont2.hadron_r_coolvisen / cont2.bhabha / cont2.ebeam**2).steps(linetype="longdashed"))
p[0,0].add((cont3.hadron_r_coolvisen / cont3.bhabha / cont3.ebeam**2).steps(linetype="dotted"))
p[0,0].add(biggles.LineX(0.4, type="dotted"))
p[0,0].x1.range = 0, 1.2
p[0,0].x1.label = r"$E_{vis}/E_{COM}$ of 1S, 2S, 3S continuum data, normalized to equal luminosity"
p[0,0].y1.label = r"$\propto$ cross-section"
p[1,0] = biggles.FramedArray(2,1)
# p[1,0][0,0].add(biggles.Points(oneovers_x, oneovers_y1, symboltype="filled circle", symbolsize=2))
p[1,0][0,0].add(biggles.SymmetricErrorBarsY(oneovers_x, oneovers_y1, oneovers_y1err, symbolsize=3))
p[1,0][0,0].add(biggles.Curve(curve_x, curve_y1, linetype="dotted"))
p[1,0][0,0].add(biggles.PlotLabel(0.05, 0.2, r"failed (below) $E_{vis}$ cut", halign="left"))
p[1,0][0,0].yrange = 0.04, 0.05
# p[1,0][1,0].add(biggles.Points(oneovers_x, oneovers_y2, symboltype="filled circle", symbolsize=2))
p[1,0][1,0].add(biggles.SymmetricErrorBarsY(oneovers_x, oneovers_y2, oneovers_y2err, symbolsize=3))
p[1,0][1,0].add(biggles.Curve(curve_x, curve_y2, linetype="dotted"))
p[1,0][1,0].add(biggles.PlotLabel(0.05, 0.2, r"passed (above) $E_{vis}$ cut", halign="left"))
p[1,0][1,0].yrange = 0.02, 0.0299999
p[1,0].xrange = 4.6, 5.3001
p[1,0].xlabel = r"Single-beam energy in GeV"
p[1,0].ylabel = r"$\propto$ Cross-section failing/passing $E_{vis}$ cut"
p.aspect_ratio = 1
p.show()
p.write_eps("plots/datasets_twophoton_visen.eps")

