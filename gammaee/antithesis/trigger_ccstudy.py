execfile("utilities.py")

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

mc1all = domc1()
mc2all = domc2()
mc3all = domc3()

mc1all_nolep = domc1(False)
mc2all_nolep = domc2(False)
mc3all_nolep = domc3(False)

print 1.*mc1all.hadroncool_trignum_count/mc1all.all
print 1.*mc1all.hadroncool_d0close_count/mc1all.all
print 1.*mc1all.hadroncool_wz_count/mc1all.all
print 1.*mc1all.hadroncool_p1_count/mc1all.all
print 1.*mc1all.hadroncool_coolvisen_count/mc1all.all

print 1.*mc1all.hadroncool_d0close_count/mc1all.hadroncool_trignum_count
print 1.*mc1all.hadroncool_wz_count/mc1all.hadroncool_d0close_count
print 1.*mc1all.hadroncool_p1_count/mc1all.hadroncool_wz_count
print 1.*mc1all.hadroncool_coolvisen_count/mc1all.hadroncool_p1_count


print 1.*(mc1["ee"]+mc1["ee0"]).hadroncool_p1_count/(mc1["ee"]+mc1["ee0"]).hadroncool_wz_count
print 1.*(mc1["mumu"]+mc1["mumu0"]).hadroncool_p1_count/(mc1["mumu"]+mc1["mumu0"]).hadroncool_wz_count
print 1.*(mc1["tautau"]).hadroncool_p1_count/(mc1["tautau"]).hadroncool_wz_count

print 1.*(mc1["tautau"]).hadroncool/(mc1["tautau"]).all
print 1.*(mc1["tautau"]).hadroncool/(mc1["tautau"]).hadroncool_trignum_count


print 1.*mc1all_nolep.hadroncool/mc1all_nolep.all
print 1.*mc1all_nolep.hadroncool_p1_count/mc1all_nolep.hadroncool_wz_count


print 1.*(mc1["ee"]+mc1["ee0"]).hadroncool_trignum_count/(mc1["ee"]+mc1["ee0"]).all
print 1.*(mc1["mumu"]+mc1["mumu0"]).hadroncool_trignum_count/(mc1["mumu"]+mc1["mumu0"]).all




ccpeak1 = RunRecord()
cccont1 = RunRecord()
ccpeak2 = RunRecord()
cccont2 = RunRecord()
ccpeak3 = RunRecord()
cccont3 = RunRecord()
for r in initialrunlist:
  if r not in mybadruns:
    if runsummary[r].res == 1 and runsummary[r].kind == 'p':
      ccpeak1 += getdb(r)
    if runsummary[r].res == 1 and runsummary[r].kind == 'c':
      cccont1 += getdb(r)
    if runsummary[r].res == 2 and runsummary[r].kind == 'p':
      ccpeak2 += getdb(r)
    if runsummary[r].res == 2 and runsummary[r].kind == 'c':
      cccont2 += getdb(r)
    if runsummary[r].res == 3 and runsummary[r].kind == 'p':
      ccpeak3 += getdb(r)
    if runsummary[r].res == 3 and runsummary[r].kind == 'c':
      cccont3 += getdb(r)

ptoc1 = (ccpeak1.hadron * (mc1all.bhabha / mc1all.hadron) - ccpeak1.bhabha) \
        / (cccont1.hadron * (mc1all.bhabha / mc1all.hadron) - cccont1.bhabha)
ptoc2 = (ccpeak2.hadron * (mc2all.bhabha / mc2all.hadron) - ccpeak2.bhabha) \
        / (cccont2.hadron * (mc2all.bhabha / mc2all.hadron) - cccont2.bhabha)
ptoc3 = (ccpeak3.hadron * (mc3all.bhabha / mc3all.hadron) - ccpeak3.bhabha) \
        / (cccont3.hadron * (mc3all.bhabha / mc3all.hadron) - cccont3.bhabha)
# ptoc1 = 1.* ccpeak1.gamgam / cccont1.gamgam
# ptoc2 = 1.* ccpeak2.gamgam / cccont2.gamgam
# ptoc3 = 1.* ccpeak3.gamgam / cccont3.gamgam

ccups1 = (ccpeak1 + cccont1 * -ptoc1)
ccups2 = (ccpeak1 + cccont2 * -ptoc2)
ccups3 = (ccpeak1 + cccont3 * -ptoc3)

nobeam = getsb("cos")
ebeam = getsb("bge")
pbeam = getsb("bgp")

ccups1_cor = ccups1 * 1.
for i in range(10):
  ccups1_cor += ebeam * (-1.*ccups1_cor.beamgase/ebeam.beamgase)
  ccups1_cor += pbeam * (-1.*ccups1_cor.beamgasp/pbeam.beamgasp)
  ccups1_cor += nobeam * (-1.*ccups1_cor.cosmic/nobeam.cosmic)
ccups2_cor = ccups2 * 1.
for i in range(10):
  ccups2_cor += ebeam * (-1.*ccups2_cor.beamgase/ebeam.beamgase)
  ccups2_cor += pbeam * (-1.*ccups2_cor.beamgasp/pbeam.beamgasp)
  ccups2_cor += nobeam * (-1.*ccups2_cor.cosmic/nobeam.cosmic)
ccups3_cor = ccups3 * 1.
for i in range(10):
  ccups3_cor += ebeam * (-1.*ccups3_cor.beamgase/ebeam.beamgase)
  ccups3_cor += pbeam * (-1.*ccups3_cor.beamgasp/pbeam.beamgasp)
  ccups3_cor += nobeam * (-1.*ccups3_cor.cosmic/nobeam.cosmic)



print 1.*ccups1.ccstudy1_analtrigcount/ccups1.ccstudy1, "+/-", 1.*ccups1.ccstudy1_analtrigcount/ccups1.ccstudy1 * sqrt((ccpeak1.ccstudy1_analtrigcount + cccont1.ccstudy1_analtrigcount * ptoc1**2)/(ccpeak1.ccstudy1_analtrigcount + cccont1.ccstudy1_analtrigcount * -ptoc1)**2 + (ccpeak1.ccstudy1 + cccont1.ccstudy1 * ptoc1**2)/(ccpeak1.ccstudy1 + cccont1.ccstudy1 * -ptoc1)**2), "vs", 1.*mc1all.ccstudy1_analtrigcount/mc1all.ccstudy1
print 1.*ccups2.ccstudy1_analtrigcount/ccups2.ccstudy1, "+/-", 1.*ccups2.ccstudy1_analtrigcount/ccups2.ccstudy1 * sqrt((ccpeak2.ccstudy1_analtrigcount + cccont2.ccstudy1_analtrigcount * ptoc2**2)/(ccpeak2.ccstudy1_analtrigcount + cccont2.ccstudy1_analtrigcount * -ptoc2)**2 + (ccpeak2.ccstudy1 + cccont2.ccstudy1 * ptoc2**2)/(ccpeak2.ccstudy1 + cccont2.ccstudy1 * -ptoc2)**2), "vs", 1.*mc2all.ccstudy1_analtrigcount/mc2all.ccstudy1
print 1.*ccups3.ccstudy1_analtrigcount/ccups3.ccstudy1, "+/-", 1.*ccups3.ccstudy1_analtrigcount/ccups3.ccstudy1 * sqrt((ccpeak3.ccstudy1_analtrigcount + cccont3.ccstudy1_analtrigcount * ptoc3**2)/(ccpeak3.ccstudy1_analtrigcount + cccont3.ccstudy1_analtrigcount * -ptoc3)**2 + (ccpeak3.ccstudy1 + cccont3.ccstudy1 * ptoc3**2)/(ccpeak3.ccstudy1 + cccont3.ccstudy1 * -ptoc3)**2), "vs", 1.*mc3all.ccstudy1_analtrigcount/mc3all.ccstudy1




print 1.*ccups1_cor.ccstudy1_analtrigcount/ccups1_cor.ccstudy1, "+/-", 1.*ccups1_cor.ccstudy1_analtrigcount/ccups1_cor.ccstudy1 * sqrt((ccpeak1.ccstudy1_analtrigcount + cccont1.ccstudy1_analtrigcount * ptoc1**2)/(ccpeak1.ccstudy1_analtrigcount + cccont1.ccstudy1_analtrigcount * -ptoc1)**2 + (ccpeak1.ccstudy1 + cccont1.ccstudy1 * ptoc1**2)/(ccpeak1.ccstudy1 + cccont1.ccstudy1 * -ptoc1)**2), "vs", 1.*mc1all.ccstudy1_analtrigcount/mc1all.ccstudy1
print 1.*ccups2_cor.ccstudy1_analtrigcount/ccups2_cor.ccstudy1, "+/-", 1.*ccups2_cor.ccstudy1_analtrigcount/ccups2_cor.ccstudy1 * sqrt((ccpeak2.ccstudy1_analtrigcount + cccont2.ccstudy1_analtrigcount * ptoc2**2)/(ccpeak2.ccstudy1_analtrigcount + cccont2.ccstudy1_analtrigcount * -ptoc2)**2 + (ccpeak2.ccstudy1 + cccont2.ccstudy1 * ptoc2**2)/(ccpeak2.ccstudy1 + cccont2.ccstudy1 * -ptoc2)**2), "vs", 1.*mc2all.ccstudy1_analtrigcount/mc2all.ccstudy1
print 1.*ccups3_cor.ccstudy1_analtrigcount/ccups3_cor.ccstudy1, "+/-", 1.*ccups3_cor.ccstudy1_analtrigcount/ccups3_cor.ccstudy1 * sqrt((ccpeak3.ccstudy1_analtrigcount + cccont3.ccstudy1_analtrigcount * ptoc3**2)/(ccpeak3.ccstudy1_analtrigcount + cccont3.ccstudy1_analtrigcount * -ptoc3)**2 + (ccpeak3.ccstudy1 + cccont3.ccstudy1 * ptoc3**2)/(ccpeak3.ccstudy1 + cccont3.ccstudy1 * -ptoc3)**2), "vs", 1.*mc3all.ccstudy1_analtrigcount/mc3all.ccstudy1









ccpeak1.ccstudy1_chen.plot().show()

(ccpeak1.ccstudy1_chen - cccont1.ccstudy1_chen * ptoc1).plot().show()
(ccpeak2.ccstudy1_chen - cccont2.ccstudy1_chen * ptoc2).plot().show()
(ccpeak3.ccstudy1_chen - cccont3.ccstudy1_chen * ptoc3).plot().show()

(ccpeak1.ccstudy1_p1 - cccont1.ccstudy1_p1 * ptoc1).plot().show()
(ccpeak2.ccstudy1_p1 - cccont2.ccstudy1_p1 * ptoc2).plot().show()
(ccpeak3.ccstudy1_p1 - cccont3.ccstudy1_p1 * ptoc3).plot().show()

(ccpeak1.ccstudy1_tracks - cccont1.ccstudy1_tracks * ptoc1).plot().show()
(ccpeak2.ccstudy1_tracks - cccont2.ccstudy1_tracks * ptoc2).plot().show()
(ccpeak3.ccstudy1_tracks - cccont3.ccstudy1_tracks * ptoc3).plot().show()

(ccpeak1.ccstudy1_analtrig - cccont1.ccstudy1_analtrig * ptoc1).plot().show()
(ccpeak2.ccstudy1_analtrig - cccont2.ccstudy1_analtrig * ptoc2).plot().show()
(ccpeak3.ccstudy1_analtrig - cccont3.ccstudy1_analtrig * ptoc3).plot().show()

(ccpeak1.ccstudy1_e1GeV - cccont1.ccstudy1_e1GeV * ptoc1).plot().show()
(ccpeak2.ccstudy1_e1GeV - cccont2.ccstudy1_e1GeV * ptoc2).plot().show()
(ccpeak3.ccstudy1_e1GeV - cccont3.ccstudy1_e1GeV * ptoc3).plot().show()

(ccpeak1.ccstudy1_e2GeV - cccont1.ccstudy1_e2GeV * ptoc1).plot().show()
(ccpeak2.ccstudy1_e2GeV - cccont2.ccstudy1_e2GeV * ptoc2).plot().show()
(ccpeak3.ccstudy1_e2GeV - cccont3.ccstudy1_e2GeV * ptoc3).plot().show()

(ccpeak1.ccstudy1_e1GeV_fail - cccont1.ccstudy1_e1GeV_fail * ptoc1).plot().show()
(ccpeak2.ccstudy1_e1GeV_fail - cccont2.ccstudy1_e1GeV_fail * ptoc2).plot().show()
(ccpeak3.ccstudy1_e1GeV_fail - cccont3.ccstudy1_e1GeV_fail * ptoc3).plot().show()

(ccpeak1.ccstudy1_e2GeV_fail - cccont1.ccstudy1_e2GeV_fail * ptoc1).plot().show()
(ccpeak2.ccstudy1_e2GeV_fail - cccont2.ccstudy1_e2GeV_fail * ptoc2).plot().show()
(ccpeak3.ccstudy1_e2GeV_fail - cccont3.ccstudy1_e2GeV_fail * ptoc3).plot().show()

p = (ccups1.ccstudy1_e1GeV / 1. / ccups1.ccstudy1).plot()
p.add((ccups1.ccstudy1_e2GeV / 1. / ccups1.ccstudy1).steps())
p.add((ccups1.ccstudy1_e1GeV_fail / 1. / ccups1.ccstudy1_e1GeV_fail.sum()).steps(linetype="dashed"))
p.add((ccups1.ccstudy1_e2GeV_fail / 1. / ccups1.ccstudy1_e2GeV_fail.sum()).steps(linetype="dashed"))
p.add(biggles.LineX(0.15, linetype="dotted"))
p.add(biggles.LineX(0.75, linetype="dotted"))
p.add(biggles.LineX(1.50, linetype="dotted"))
p.add(biggles.LineY(0))
p.yrange = -0.01, 0.10
p.x1.label = r"$E_1$ and $E_2$ (in GeV) for cccheck events and cccheck failures"
p.aspect_ratio = 0.5
p.show()
p.write_eps("plots/trigger_neutralpart.eps")
