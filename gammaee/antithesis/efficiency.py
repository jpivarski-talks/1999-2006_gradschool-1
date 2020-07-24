execfile("/home/mccann/antithesis/utilities.py")

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

def countfrac(pack):
  f = pack.hadroncool / float(pack.all)
  print f*100., sqrt(f*(1.-f)/float(pack.all))*100., "%"

countfrac(mc1["ee"]+mc1["ee0"])
countfrac(mc1["mumu"]+mc1["mumu0"])
countfrac(mc1["tautau"])
countfrac(mc1["ggg"])
countfrac(mc1["gggam"])
countfrac(mc1["qq"])

countfrac(mc2["ee"]+mc2["ee0"])
countfrac(mc2["mumu"]+mc2["mumu0"])
countfrac(mc2["tautau"])
countfrac(mc2["ggg"])
countfrac(mc2["gggam"])
countfrac(mc2["qq"])

countfrac(mc2["cas"]+mc2["casll"]+mc2["casll0"])
countfrac(mc2["casll"]+mc2["casll0"])
countfrac(mc2["casll0"])
countfrac(mc2["cas"])


countfrac(mc3["ee"]+mc3["ee0"])
countfrac(mc3["mumu"]+mc3["mumu0"])
countfrac(mc3["tautau"])
countfrac(mc3["ggg"])
countfrac(mc3["gggam"])
countfrac(mc3["qq"])

countfrac(mc3["cas"]+mc3["casll"]+mc3["casll0"])
countfrac(mc3["casll"]+mc3["casll0"])
countfrac(mc3["casll0"])
countfrac(mc3["cas"])

print (mc2["cas"]+mc2["casll"]+mc2["casll0"]).all, (mc2["casll"]+mc2["casll0"]).all
print (mc3["cas"]+mc3["casll"]+mc3["casll0"]).all, (mc3["casll"]+mc3["casll0"]).all

















print 1. * mc2["tautau"].hadroncool / mc2["tautau"].all
print 1. * mc2["tautau"].hadroncool_g4tracks / mc2["tautau"].all






def do_p1eff(h): return 1. * h.hadroncool_p1_count / h.hadroncool_wz_count
def do_p1totaleff(h): return 1. * h.hadroncool_p1_count / h.all

print do_p1totaleff(mc1["ee0"] + mc1["ee"])
print do_p1totaleff(mc2["ee0"] + mc2["ee"])
print do_p1totaleff(mc3["ee0"] + mc3["ee"])

print do_p1totaleff(mc1["mumu0"] + mc1["mumu"])
print do_p1totaleff(mc2["mumu0"] + mc2["mumu"])
print do_p1totaleff(mc3["mumu0"] + mc3["mumu"])

print do_p1totaleff(mc1["tautau"])
print do_p1totaleff(mc2["tautau"])
print do_p1totaleff(mc3["tautau"])

print do_p1totaleff(mc1["ggg"])
print do_p1totaleff(mc2["ggg"])
print do_p1totaleff(mc3["ggg"])

print do_p1totaleff(mc1["gggam"])
print do_p1totaleff(mc2["gggam"])
print do_p1totaleff(mc3["gggam"])

print do_p1totaleff(mc1["qq"])
print do_p1totaleff(mc2["qq"])
print do_p1totaleff(mc3["qq"])

print do_p1totaleff(mc2["casll0"] + mc2["casll"])
print do_p1totaleff(mc3["casll0"] + mc3["casll"])

print do_p1totaleff(mc2["cas"])
print do_p1totaleff(mc3["cas"])


print mc1all_nolep.hadroncool_r_trignum.sumerr() / mc1all_nolep.hadroncool_r_trignum.sum() * 100.*do_p1totaleff(mc1all_nolep)
print mc2all_nolep.hadroncool_r_trignum.sumerr() / mc2all_nolep.hadroncool_r_trignum.sum() * 100.*do_p1totaleff(mc1all_nolep)
print mc3all_nolep.hadroncool_r_trignum.sumerr() / mc3all_nolep.hadroncool_r_trignum.sum() * 100.*do_p1totaleff(mc1all_nolep)




print 100.*do_p1totaleff(domc1(False, dobmm=0, dor=0, docas=0, dogggam=0))
print 100.*(do_p1totaleff(domc1(False, dobmm=0, dor=0, docas=0, dogggam=0)) - do_p1totaleff(domc1(False, dobmm=1, dor=0, docas=0, dogggam=0)))
print 100.*(do_p1totaleff(domc1(False, dobmm=0, dor=0, docas=0, dogggam=0)) - do_p1totaleff(domc1(False, dobmm=0, dor=1, docas=0, dogggam=0)))
print 100.*(do_p1totaleff(domc1(False, dobmm=0, dor=0, docas=0, dogggam=0)) - do_p1totaleff(domc1(False, dobmm=0, dor=0, docas=0, dogggam=1)))

print 100.*do_p1totaleff(domc2(False, dobmm=0, dor=0, docas=0, dogggam=0))
print 100.*(do_p1totaleff(domc2(False, dobmm=0, dor=0, docas=0, dogggam=0)) - do_p1totaleff(domc2(False, dobmm=1, dor=0, docas=0, dogggam=0)))
print 100.*(do_p1totaleff(domc2(False, dobmm=0, dor=0, docas=0, dogggam=0)) - do_p1totaleff(domc2(False, dobmm=0, dor=1, docas=0, dogggam=0)))
print 100.*(do_p1totaleff(domc2(False, dobmm=0, dor=0, docas=0, dogggam=0)) - do_p1totaleff(domc2(False, dobmm=0, dor=0, docas=1, dogggam=0)))
print 100.*(do_p1totaleff(domc2(False, dobmm=0, dor=0, docas=0, dogggam=0)) - do_p1totaleff(domc2(False, dobmm=0, dor=0, docas=0, dogggam=1)))

print 100.*(do_p1totaleff(domc3(False, dobmm=0, dor=0, docas=0, dogggam=0)))
print 100.*(do_p1totaleff(domc3(False, dobmm=0, dor=0, docas=0, dogggam=0)) - do_p1totaleff(domc3(False, dobmm=1, dor=0, docas=0, dogggam=0)))
print 100.*(do_p1totaleff(domc3(False, dobmm=0, dor=0, docas=0, dogggam=0)) - do_p1totaleff(domc3(False, dobmm=0, dor=1, docas=0, dogggam=0)))
print 100.*(do_p1totaleff(domc3(False, dobmm=0, dor=0, docas=0, dogggam=0)) - do_p1totaleff(domc3(False, dobmm=0, dor=0, docas=1, dogggam=0)))
print 100.*(do_p1totaleff(domc3(False, dobmm=0, dor=0, docas=0, dogggam=0)) - do_p1totaleff(domc3(False, dobmm=0, dor=0, docas=0, dogggam=1)))


print 100.*do_p1totaleff(domc2(False))
print 100.*do_p1totaleff(domc2(False, docasll=1.))

print 100.*do_p1totaleff(domc3(False))
print 100.*do_p1totaleff(domc3(False, docasll=1.))






peak1 = getrd(1, "peak", "all")
cont1 = getrd(1, "cont", "all")
peak2 = getrd(2, "peak", "all")
cont2 = getrd(2, "cont", "all")
peak3 = getrd(3, "peak", "all")
cont3 = getrd(3, "cont", "all")

ptoc1 = (peak1.hadron * (mc1all.bhabha / mc1all.hadron) - peak1.bhabha) \
        / (cont1.hadron * (mc1all.bhabha / mc1all.hadron) - cont1.bhabha)
ptoc2 = (peak2.hadron * (mc2all.bhabha / mc2all.hadron) - peak2.bhabha) \
        / (cont2.hadron * (mc2all.bhabha / mc2all.hadron) - cont2.bhabha)
ptoc3 = (peak3.hadron * (mc3all.bhabha / mc3all.hadron) - peak3.bhabha) \
        / (cont3.hadron * (mc3all.bhabha / mc3all.hadron) - cont3.bhabha)

ptomc1 = (peak1.hadron - (cont1.hadron * ptoc1)) / mc1all.hadron
ptomc2 = (peak2.hadron - (cont2.hadron * ptoc2)) / mc2all.hadron
ptomc3 = (peak3.hadron - (cont3.hadron * ptoc3)) / mc3all.hadron

ups1 = peak1 + cont1 * -ptoc1
ups2 = peak2 + cont2 * -ptoc2
ups3 = peak3 + cont3 * -ptoc3

mups1 = mc1all * ptomc1
mups2 = mc2all * ptomc2
mups3 = mc3all * ptomc3

nobeam = getsb("cos")
ebeam = getsb("bge")
pbeam = getsb("bgp")

ups1_cor = ups1 * 1.
for i in range(10):
  ups1_cor += ebeam * (-1.*ups1_cor.beamgase/ebeam.beamgase)
  ups1_cor += pbeam * (-1.*ups1_cor.beamgasp/pbeam.beamgasp)
  ups1_cor += nobeam * (-1.*ups1_cor.cosmic/nobeam.cosmic)
ups2_cor = ups2 * 1.
for i in range(10):
  ups2_cor += ebeam * (-1.*ups2_cor.beamgase/ebeam.beamgase)
  ups2_cor += pbeam * (-1.*ups2_cor.beamgasp/pbeam.beamgasp)
  ups2_cor += nobeam * (-1.*ups2_cor.cosmic/nobeam.cosmic)
ups3_cor = ups3 * 1.
for i in range(10):
  ups3_cor += ebeam * (-1.*ups3_cor.beamgase/ebeam.beamgase)
  ups3_cor += pbeam * (-1.*ups3_cor.beamgasp/pbeam.beamgasp)
  ups3_cor += nobeam * (-1.*ups3_cor.cosmic/nobeam.cosmic)

p = biggles.Table(1,2)

p[0,0] = (peak1.hadroncool_p1 + 1e-5).plot()
p[0,0].add((mc1all.hadroncool_p1*ptomc1 + 1e-5).steps(linetype="dashed"))
p[0,0].add(biggles.LineX(0.8, linetype="dotted"))
p[0,0].y1.log = 1
p[0,0].y1.range = 5, 100000
p[0,0].x1.label = r"Momentum of the largest track / $E_{beam}$"
p[0,0].y1.label = r"Events / 0.01"

p[0,1] = (peak1.hadroncool_cvisen + 1e-5).plot()
p[0,1].add((mc1all.hadroncool_cvisen*ptomc1 + 1e-5).steps(linetype="dashed"))
p[0,1].add(biggles.LineX(0.4, linetype="dotted"))
p[0,1].y1.log = 1
p[0,1].y1.range = 5, 100000
p[0,1].x1.label = r"Visible energy / 2 $E_{beam}$"

p.aspect_ratio = 0.5
p.show()
p.write_eps("/home/mccann/prl/cuts.eps")






p = (peak1.hadroncool_p1 + 1e-5).plot()
p.add((mc1all.hadroncool_p1*ptomc1 + 1e-5).steps(linetype="dashed"))
p.add(biggles.LineX(0.8, linetype="dotted"))
p.y1.log = 1
p.y1.range = 5, 100000
p.x1.label = r"Momentum of the largest track / $E_{beam}$"
p.aspect_ratio = 1
p.show()
p.write_eps("/home/mccann/monster_talk/take_two/cuts_p1.eps")

p = (peak1.hadroncool_cvisen + 1e-5).plot()
p.add((mc1all.hadroncool_cvisen*ptomc1 + 1e-5).steps(linetype="dashed"))
p.add(biggles.LineX(0.4, linetype="dotted"))
p.y1.log = 1
p.y1.range = 10, 10000
p.x1.label = "Visible energy / $2E_{beam}$"
p.aspect_ratio = 1
p.show()
p.write_eps("/home/mccann/monster_talk/take_two/cuts_visen.eps")

peak1_narrower = hist.h1(40, -0.02, 0.02)
peak1_narrower.vals = peak1.hadroncool_d0close.vals[40:80]
peak1_narrower.frame = peak1.hadroncool_d0close.frame[40:80]
peak1_narrower.high = peak1.hadroncool_d0close.frame[80]

mc1all_narrower = hist.h1(40, -0.02, 0.02)
mc1all_narrower.vals = mc1all.hadroncool_d0close.vals[40:80]
mc1all_narrower.frame = mc1all.hadroncool_d0close.frame[40:80]
mc1all_narrower.high = mc1all.hadroncool_d0close.frame[80]

p = (peak1_narrower + 1e-5).plot()
p.add((mc1all_narrower*ptomc1 + 1e-5).steps(linetype="dashed"))
p.add(biggles.LineX(-0.005, linetype="dotted"))
p.add(biggles.LineX(0.005, linetype="dotted"))
p.y1.log = 1
p.y1.range = 1, 1000000
p.x1.ticks = (-0.02, -0.01, 0, 0.01, 0.02)
p.x1.label = "Closest track to origin in XY (m)"
p.aspect_ratio = 1
p.show()
p.write_eps("/home/mccann/monster_talk/take_two/cuts_d0close.eps")

p = (peak1.hadroncool_anyz + 1e-5).plot()
p.add((mc1all.hadroncool_anyz*ptomc1 + 1e-5).steps(linetype="dashed"))
p.add(biggles.LineX(-0.075, linetype="dotted"))
p.add(biggles.LineX(0.075, linetype="dotted"))
p.y1.log = 1
p.y1.range = 1, 100000
p.x1.label = "Closest track to origin in Z (m)"
p.aspect_ratio = 1
p.show()
p.write_eps("/home/mccann/monster_talk/take_two/cuts_anyz.eps")









p = biggles.FramedArray(3,1)
p[0,0].add(ups1_cor.hadroncool_r_d0close.points(symbolsize=1))
p[0,0].add(ups1_cor.hadroncool_r_d0close.errorbars())
p[0,0].add(mups1.hadroncool_r_d0close.steps())
p[0,0].add(biggles.LineX(0.005, linetype="dotted"))
p[0,0].add(biggles.LineX(-0.005, linetype="dotted"))
p[0,0].add(biggles.Slope(0, (0, 1)))
p[0,0].add(biggles.PlotLabel(0.8, 0.8, r"$\Upsilon(1S)$"))
p[0,0].yrange = min(ups1_cor.hadroncool_r_d0close)*10, max(ups1_cor.hadroncool_r_d0close)*1.2
p[1,0].add(ups2_cor.hadroncool_r_d0close.points(symbolsize=1))
p[1,0].add(ups2_cor.hadroncool_r_d0close.errorbars())
p[1,0].add(mups2.hadroncool_r_d0close.steps())
p[1,0].add(biggles.LineX(0.005, linetype="dotted"))
p[1,0].add(biggles.LineX(-0.005, linetype="dotted"))
p[1,0].add(biggles.Slope(0, (0, 1)))
p[1,0].add(biggles.PlotLabel(0.8, 0.8, r"$\Upsilon(2S)$"))
p[1,0].yrange = min(ups2_cor.hadroncool_r_d0close)*10, max(ups2_cor.hadroncool_r_d0close)*1.2
p[2,0].add(ups3_cor.hadroncool_r_d0close.points(symbolsize=1))
p[2,0].add(ups3_cor.hadroncool_r_d0close.errorbars())
p[2,0].add(mups3.hadroncool_r_d0close.steps())
p[2,0].add(biggles.LineX(0.005, linetype="dotted"))
p[2,0].add(biggles.LineX(-0.005, linetype="dotted"))
p[2,0].add(biggles.Slope(0, (0, 1)))
p[2,0].add(biggles.PlotLabel(0.8, 0.8, r"$\Upsilon(3S)$"))
p[2,0].yrange = min(ups3_cor.hadroncool_r_d0close)*10, max(ups3_cor.hadroncool_r_d0close)*1.2
p.xrange = -0.05, 0.05
p.aspect_ratio = 1.2
p.xlabel = r"$d_{XY}$ with only trigger applied"
p.show()
p.write_eps("plots/efficiency_dxy_linear.eps")

p = biggles.FramedArray(3,1)
p[0,0].add(ups1_cor.hadroncool_r_anyz.points(symbolsize=1))
p[0,0].add(ups1_cor.hadroncool_r_anyz.errorbars())
p[0,0].add(mups1.hadroncool_r_anyz.steps())
p[0,0].add(biggles.LineX(0.075, linetype="dotted"))
p[0,0].add(biggles.LineX(-0.075, linetype="dotted"))
p[0,0].add(biggles.Slope(0, (0, 1)))
p[0,0].add(biggles.PlotLabel(0.8, 0.8, r"$\Upsilon(1S)$"))
p[0,0].yrange = min(ups1_cor.hadroncool_r_anyz)*10, max(ups1_cor.hadroncool_r_anyz)*1.2
p[1,0].add(ups2_cor.hadroncool_r_anyz.points(symbolsize=1))
p[1,0].add(ups2_cor.hadroncool_r_anyz.errorbars())
p[1,0].add(mups2.hadroncool_r_anyz.steps())
p[1,0].add(biggles.LineX(0.075, linetype="dotted"))
p[1,0].add(biggles.LineX(-0.075, linetype="dotted"))
p[1,0].add(biggles.Slope(0, (0, 1)))
p[1,0].add(biggles.PlotLabel(0.8, 0.8, r"$\Upsilon(2S)$"))
p[1,0].yrange = min(ups2_cor.hadroncool_r_anyz)*10, max(ups2_cor.hadroncool_r_anyz)*1.2
p[2,0].add(ups3_cor.hadroncool_r_anyz.points(symbolsize=1))
p[2,0].add(ups3_cor.hadroncool_r_anyz.errorbars())
p[2,0].add(mups3.hadroncool_r_anyz.steps())
p[2,0].add(biggles.LineX(0.075, linetype="dotted"))
p[2,0].add(biggles.LineX(-0.075, linetype="dotted"))
p[2,0].add(biggles.Slope(0, (0, 1)))
p[2,0].add(biggles.PlotLabel(0.8, 0.8, r"$\Upsilon(3S)$"))
p[2,0].yrange = min(ups3_cor.hadroncool_r_anyz)*10, max(ups3_cor.hadroncool_r_anyz)*1.2
p.xrange = -0.1, 0.1
p.aspect_ratio = 1.2
p.xlabel = r"$d_{Z}$ with only previous cuts applied"
p.show()
p.write_eps("plots/efficiency_dz_linear.eps")



















p = biggles.FramedArray(3,1)
p[0,0].add(logify(ups1_cor.hadroncool_r_logd0close).points(symbolsize=1))
p[0,0].add(logify(ups1_cor.hadroncool_r_logd0close).errorbars())
p[0,0].add(logify(mups1.hadroncool_r_logd0close).steps())
p[0,0].add(biggles.LineX(0.005, linetype="dotted"))
p[0,0].add(biggles.Slope(0, (0, 1)))
p[0,0].add(biggles.PlotLabel(0.8, 0.8, r"$\Upsilon(1S)$"))
p[0,0].yrange = min(ups1_cor.hadroncool_r_logd0close)*3, max(ups1_cor.hadroncool_r_logd0close)*1.2
p[1,0].add(logify(ups2_cor.hadroncool_r_logd0close).points(symbolsize=1))
p[1,0].add(logify(ups2_cor.hadroncool_r_logd0close).errorbars())
p[1,0].add(logify(mups2.hadroncool_r_logd0close).steps())
p[1,0].add(biggles.LineX(0.005, linetype="dotted"))
p[1,0].add(biggles.Slope(0, (0, 1)))
p[1,0].add(biggles.PlotLabel(0.8, 0.8, r"$\Upsilon(2S)$"))
p[1,0].yrange = min(ups2_cor.hadroncool_r_logd0close)*3, max(ups2_cor.hadroncool_r_logd0close)*1.2
p[2,0].add(logify(ups3_cor.hadroncool_r_logd0close).points(symbolsize=1))
p[2,0].add(logify(ups3_cor.hadroncool_r_logd0close).errorbars())
p[2,0].add(logify(mups3.hadroncool_r_logd0close).steps())
p[2,0].add(biggles.LineX(0.005, linetype="dotted"))
p[2,0].add(biggles.Slope(0, (0, 1)))
p[2,0].add(biggles.PlotLabel(0.8, 0.8, r"$\Upsilon(3S)$"))
p[2,0].yrange = min(ups3_cor.hadroncool_r_logd0close)*3, max(ups3_cor.hadroncool_r_logd0close)*1.2
p.xlog = 1
p.xrange = 1e-7, 1.001
p.aspect_ratio = 1.2
p.xlabel = r"$d_{XY}$ with only trigger applied"
p.show()
p.write_eps("plots/efficiency_dxy.eps")

p = biggles.FramedArray(3,1)
p[0,0].add(logify(ups1_cor.hadroncool_r_loganyz).points(symbolsize=1))
p[0,0].add(logify(ups1_cor.hadroncool_r_loganyz).errorbars())
p[0,0].add(logify(mups1.hadroncool_r_loganyz).steps())
p[0,0].add(biggles.LineX(0.075, linetype="dotted"))
p[0,0].add(biggles.Slope(0, (0, 1)))
p[0,0].add(biggles.PlotLabel(0.15, 0.8, r"$\Upsilon(1S)$"))
p[0,0].yrange = min(ups1_cor.hadroncool_r_loganyz)*3, max(ups1_cor.hadroncool_r_loganyz)*1.2
p[1,0].add(logify(ups2_cor.hadroncool_r_loganyz).points(symbolsize=1))
p[1,0].add(logify(ups2_cor.hadroncool_r_loganyz).errorbars())
p[1,0].add(logify(mups2.hadroncool_r_loganyz).steps())
p[1,0].add(biggles.LineX(0.075, linetype="dotted"))
p[1,0].add(biggles.Slope(0, (0, 1)))
p[1,0].add(biggles.PlotLabel(0.15, 0.8, r"$\Upsilon(2S)$"))
p[1,0].yrange = min(ups2_cor.hadroncool_r_loganyz)*3, max(ups2_cor.hadroncool_r_loganyz)*1.2
p[2,0].add(logify(ups3_cor.hadroncool_r_loganyz).points(symbolsize=1))
p[2,0].add(logify(ups3_cor.hadroncool_r_loganyz).errorbars())
p[2,0].add(logify(mups3.hadroncool_r_loganyz).steps())
p[2,0].add(biggles.LineX(0.075, linetype="dotted"))
p[2,0].add(biggles.Slope(0, (0, 1)))
p[2,0].add(biggles.PlotLabel(0.15, 0.8, r"$\Upsilon(3S)$"))
p[2,0].yrange = min(ups3_cor.hadroncool_r_loganyz)*3, max(ups3_cor.hadroncool_r_loganyz)*1.2
p.xlog = 1
p.xrange = 1e-6, 1.001
p.aspect_ratio = 1.2
p.xlabel = r"$d_{Z}$ with only previous cuts applied"
p.show()
p.write_eps("plots/efficiency_dz.eps")

p = biggles.FramedArray(3,1)
p[0,0].add(ups1_cor.hadroncool_r_p1.points(symbolsize=1))
p[0,0].add(ups1_cor.hadroncool_r_p1.errorbars())
p[0,0].add(mups1.hadroncool_r_p1.steps())
p[0,0].add(biggles.LineX(0.8, linetype="dotted"))
p[0,0].add(biggles.Slope(0, (0, 1)))
p[0,0].add(biggles.PlotLabel(0.8, 0.8, r"$\Upsilon(1S)$"))
p[0,0].yrange = min(ups1_cor.hadroncool_r_p1)*3, max(ups1_cor.hadroncool_r_p1)*1.2
p[1,0].add(ups2_cor.hadroncool_r_p1.points(symbolsize=1))
p[1,0].add(ups2_cor.hadroncool_r_p1.errorbars())
p[1,0].add(mups2.hadroncool_r_p1.steps())
p[1,0].add(biggles.LineX(0.8, linetype="dotted"))
p[1,0].add(biggles.Slope(0, (0, 1)))
p[1,0].add(biggles.PlotLabel(0.8, 0.8, r"$\Upsilon(2S)$"))
p[1,0].yrange = min(ups2_cor.hadroncool_r_p1)*3, max(ups2_cor.hadroncool_r_p1)*1.2
p[2,0].add(ups3_cor.hadroncool_r_p1.points(symbolsize=1))
p[2,0].add(ups3_cor.hadroncool_r_p1.errorbars())
p[2,0].add(mups3.hadroncool_r_p1.steps())
p[2,0].add(biggles.LineX(0.8, linetype="dotted"))
p[2,0].add(biggles.Slope(0, (0, 1)))
p[2,0].add(biggles.PlotLabel(0.8, 0.8, r"$\Upsilon(3S)$"))
p[2,0].yrange = min(ups3_cor.hadroncool_r_p1)*3, max(ups3_cor.hadroncool_r_p1)*1.2
p.xrange = 0, 1.20001
p.aspect_ratio = 1.2
p.xlabel = r"$|p_1|/E_{beam}$ with only previous cuts applied"
p.show()
p.write_eps("plots/efficiency_p1.eps")

p = biggles.FramedArray(3,1)
p[0,0].add(ups1_cor.hadroncool_r_coolvisen.points(symbolsize=1))
p[0,0].add(ups1_cor.hadroncool_r_coolvisen.errorbars())
p[0,0].add(mups1.hadroncool_r_coolvisen.steps())
p[0,0].add(biggles.LineX(0.4, linetype="dotted"))
p[0,0].add(biggles.Slope(0, (0, 1)))
p[0,0].add(biggles.PlotLabel(0.15, 0.8, r"$\Upsilon(1S)$"))
p[0,0].yrange = min(ups1_cor.hadroncool_r_coolvisen)*3, max(ups1_cor.hadroncool_r_coolvisen)*1.2
p[1,0].add(ups2_cor.hadroncool_r_coolvisen.points(symbolsize=1))
p[1,0].add(ups2_cor.hadroncool_r_coolvisen.errorbars())
p[1,0].add(mups2.hadroncool_r_coolvisen.steps())
p[1,0].add(biggles.LineX(0.4, linetype="dotted"))
p[1,0].add(biggles.Slope(0, (0, 1)))
p[1,0].add(biggles.PlotLabel(0.15, 0.8, r"$\Upsilon(2S)$"))
p[1,0].yrange = min(ups2_cor.hadroncool_r_coolvisen)*3, max(ups2_cor.hadroncool_r_coolvisen)*1.2
p[2,0].add(ups3_cor.hadroncool_r_coolvisen.points(symbolsize=1))
p[2,0].add(ups3_cor.hadroncool_r_coolvisen.errorbars())
p[2,0].add(mups3.hadroncool_r_coolvisen.steps())
p[2,0].add(biggles.LineX(0.4, linetype="dotted"))
p[2,0].add(biggles.Slope(0, (0, 1)))
p[2,0].add(biggles.PlotLabel(0.15, 0.8, r"$\Upsilon(3S)$"))
p[2,0].yrange = min(ups3_cor.hadroncool_r_coolvisen)*3, max(ups3_cor.hadroncool_r_coolvisen)*1.2
p.xrange = 0, 1.20001
p.aspect_ratio = 1.2
p.xlabel = r"$E_{vis}/E_{COM}$ with only previous cuts applied"
p.show()
p.write_eps("plots/efficiency_visen.eps")



def calculate_p1(h):
  return 100.*h.sum(0.8,1.2)/h.sum(), 100.*sqrt(h.sumerr(0.8,1.2)**2*h.sum(0,0.8)**2 + h.sumerr(0,0.8)**2*h.sum(0.8,1.2)**2)/h.sum()**2

print calculate_p1(ups1_cor.hadroncool_r_p1)
print calculate_p1(ups2_cor.hadroncool_r_p1)
print calculate_p1(ups3_cor.hadroncool_r_p1)

print calculate_p1(mups1.hadroncool_r_p1)
print calculate_p1(mups2.hadroncool_r_p1)
print calculate_p1(mups3.hadroncool_r_p1)






def rebin(h, bins):
  xlow = h.frame[0]
  xstep = 1. * (h.high - h.frame[0]) / bins
  xhigh = h.frame[0] + xstep

  tmp = hist.h1(bins, xlow, h.high)

  for i in range(bins):
    tmp.vals[i] = h.sum(xlow, xhigh)
    tmp.errs[i] = h.sumerr(xlow, xhigh)
    xlow += xstep
    xhigh += xstep

  tmp.underflow = h.underflow
  tmp.underflow_error = h.underflow_error
  tmp.overflow = h.overflow
  tmp.overflow_error = h.overflow_error
  return tmp



p = biggles.Table(2,1)

h1 = rebin(ups1_cor.hadroncool_r_p1 / ups1_cor.hadroncool_r_p1.sum(), 30)
h2 = rebin(ups2_cor.hadroncool_r_p1 / ups2_cor.hadroncool_r_p1.sum(), 30)
h3 = rebin(ups3_cor.hadroncool_r_p1 / ups3_cor.hadroncool_r_p1.sum(), 30)
p[0,0] = biggles.FramedPlot()
stuff = [h1.points(symboltype="circle", symbolsize=3), \
         h2.points(symboltype="triangle", symbolsize=3), \
         h3.points(symboltype="cross", symbolsize=3)]
stuff[0].label = r"$\Upsilon$ (1S)"
stuff[1].label = r"$\Upsilon$ (2S)"
stuff[2].label = r"$\Upsilon$ (3S)"
p[0,0].add(stuff[0])
p[0,0].add(h1.errorbars())
p[0,0].add(stuff[1])
p[0,0].add(h2.errorbars())
p[0,0].add(stuff[2])
p[0,0].add(h3.errorbars())
p[0,0].add(biggles.LineX(0.8, linetype="dotted"))
p[0,0].add(biggles.LineY(0))
p[0,0].add(biggles.PlotKey(0.8, 0.8, stuff))
p[0,0].yrange = -0.01, 0.20
p[0,0].xrange = 0, 1.2
p[0,0].x1.label = r"$|p_1|/E_{beam}$ of all three resonances"

h1 = rebin(ups1_cor.hadroncool_r_coolvisen / ups1_cor.hadroncool_r_coolvisen.sum(), 30)
h2 = rebin(ups2_cor.hadroncool_r_coolvisen / ups2_cor.hadroncool_r_coolvisen.sum(), 30)
h3 = rebin(ups3_cor.hadroncool_r_coolvisen / ups3_cor.hadroncool_r_coolvisen.sum(), 30)
p[1,0] = biggles.FramedPlot()
stuff = [h1.points(symboltype="circle", symbolsize=3), \
         h2.points(symboltype="triangle", symbolsize=3), \
         h3.points(symboltype="cross", symbolsize=3)]
stuff[0].label = r"$\Upsilon$ (1S)"
stuff[1].label = r"$\Upsilon$ (2S)"
stuff[2].label = r"$\Upsilon$ (3S)"
p[1,0].add(stuff[0])
p[1,0].add(h1.errorbars())
p[1,0].add(stuff[1])
p[1,0].add(h2.errorbars())
p[1,0].add(stuff[2])
p[1,0].add(h3.errorbars())
p[1,0].add(biggles.LineX(0.4, linetype="dotted"))
p[1,0].add(biggles.LineY(0))
p[1,0].add(biggles.PlotKey(0.1, 0.8, stuff))
p[1,0].yrange = -0.01, 0.14
p[1,0].xrange = 0, 1.2
p[1,0].x1.label = r"$E_{vis}/E_{COM}$ of all three resonances"

p.aspect_ratio = 1.2
p.show()
p.write_eps("plots/efficiency_overlay.eps")




















def calculate_visen(h):
  return 100.*h.sum(0.3,0.4)/h.sum(0.3,1.2), 100.*sqrt(h.sumerr(0.3,0.4)**2*h.sum(0.4,1.2)**2 + h.sumerr(0.4,1.2)**2*h.sum(0.3,0.4)**2)/h.sum(0.3,1.2)**2


print 100.*(peak1.hadroncool_r_coolvisen + cont1.hadroncool_r_coolvisen * -ptoc1).sum(0.3,0.4)/(peak1.hadroncool_r_coolvisen + cont1.hadroncool_r_coolvisen * -ptoc1).sum(0.3,1.2)
print 100.*(peak2.hadroncool_r_coolvisen + cont2.hadroncool_r_coolvisen * -ptoc2).sum(0.3,0.4)/(peak2.hadroncool_r_coolvisen + cont2.hadroncool_r_coolvisen * -ptoc2).sum(0.3,1.2)
print 100.*(peak3.hadroncool_r_coolvisen + cont3.hadroncool_r_coolvisen * -ptoc3).sum(0.3,0.4)/(peak3.hadroncool_r_coolvisen + cont3.hadroncool_r_coolvisen * -ptoc3).sum(0.3,1.2)

print 100.*(peak1.hadroncool_r_coolvisen + cont1.hadroncool_r_coolvisen * -ptoc1 * 1.005).sum(0.3,0.4)/(peak1.hadroncool_r_coolvisen + cont1.hadroncool_r_coolvisen * -ptoc1).sum(0.3,1.2)
print 100.*(peak2.hadroncool_r_coolvisen + cont2.hadroncool_r_coolvisen * -ptoc2 * 1.005).sum(0.3,0.4)/(peak2.hadroncool_r_coolvisen + cont2.hadroncool_r_coolvisen * -ptoc2).sum(0.3,1.2)
print 100.*(peak3.hadroncool_r_coolvisen + cont3.hadroncool_r_coolvisen * -ptoc3 * 1.005).sum(0.3,0.4)/(peak3.hadroncool_r_coolvisen + cont3.hadroncool_r_coolvisen * -ptoc3).sum(0.3,1.2)

print calculate_visen(mc1all_nolep.hadroncool_r_coolvisen)
print calculate_visen(mc2all_nolep.hadroncool_r_coolvisen)
print calculate_visen(mc3all_nolep.hadroncool_r_coolvisen)


print 100. * ups1.hadroncool_l4dec_count / ups1.hadroncool_coolvisen_count
print 100. * ups2.hadroncool_l4dec_count / ups2.hadroncool_coolvisen_count
print 100. * ups3.hadroncool_l4dec_count / ups3.hadroncool_coolvisen_count

print sqrt(1./peak1.hadroncool_l4dec_count)
print sqrt(1./cont1.hadroncool_l4dec_count)
print sqrt(1./peak2.hadroncool_l4dec_count)
print sqrt(1./cont2.hadroncool_l4dec_count)
print sqrt(1./peak3.hadroncool_l4dec_count)
print sqrt(1./cont3.hadroncool_l4dec_count)






tmp_ups1 = peak1 + cont1 * -ptoc1
tmp_ups2 = peak2 + cont2 * -ptoc2
tmp_ups3 = peak3 + cont3 * -ptoc3

print "No beam-gas, cosmic ray corrections"
print "ups1s visen", calculate_visen(tmp_ups1.hadroncool_r_coolvisen)
print "ups1s l4dec", 100.*tmp_ups1.hadroncool_l4dec_count/tmp_ups1.hadroncool_coolvisen_count
print "ups2s visen", calculate_visen(tmp_ups2.hadroncool_r_coolvisen)
print "ups2s l4dec", 100.*tmp_ups2.hadroncool_l4dec_count/tmp_ups2.hadroncool_coolvisen_count
print "ups3s visen", calculate_visen(tmp_ups3.hadroncool_r_coolvisen)
print "ups3s l4dec", 100.*tmp_ups3.hadroncool_l4dec_count/tmp_ups3.hadroncool_coolvisen_count

for i in range(10):
  tmp_ups1 += ebeam * (-1.*tmp_ups1.beamgase/ebeam.beamgase)
  tmp_ups1 += pbeam * (-1.*tmp_ups1.beamgasp/pbeam.beamgasp)
  tmp_ups1 += nobeam * (-1.*tmp_ups1.cosmic/nobeam.cosmic)
for i in range(10):
  tmp_ups2 += ebeam * (-1.*tmp_ups2.beamgase/ebeam.beamgase)
  tmp_ups2 += pbeam * (-1.*tmp_ups2.beamgasp/pbeam.beamgasp)
  tmp_ups2 += nobeam * (-1.*tmp_ups2.cosmic/nobeam.cosmic)
for i in range(10):
  tmp_ups3 += ebeam * (-1.*tmp_ups3.beamgase/ebeam.beamgase)
  tmp_ups3 += pbeam * (-1.*tmp_ups3.beamgasp/pbeam.beamgasp)
  tmp_ups3 += nobeam * (-1.*tmp_ups3.cosmic/nobeam.cosmic)

print "With beam-gas, cosmic ray corrections"
print "ups1s visen", calculate_visen(tmp_ups1.hadroncool_r_coolvisen)
print "ups1s l4dec", 100.*tmp_ups1.hadroncool_l4dec_count/tmp_ups1.hadroncool_coolvisen_count
print "ups2s visen", calculate_visen(tmp_ups2.hadroncool_r_coolvisen)
print "ups2s l4dec", 100.*tmp_ups2.hadroncool_l4dec_count/tmp_ups2.hadroncool_coolvisen_count
print "ups3s visen", calculate_visen(tmp_ups3.hadroncool_r_coolvisen)
print "ups3s l4dec", 100.*tmp_ups3.hadroncool_l4dec_count/tmp_ups3.hadroncool_coolvisen_count

tmp_ups1 = peak1 + cont1 * -ptoc1 * 1.005
tmp_ups2 = peak2 + cont2 * -ptoc2 * 1.005
tmp_ups3 = peak3 + cont3 * -ptoc3 * 1.005

print "Continuum up a notch"
print "ups1s visen", calculate_visen(tmp_ups1.hadroncool_r_coolvisen)
print "ups1s l4dec", 100.*tmp_ups1.hadroncool_l4dec_count/tmp_ups1.hadroncool_coolvisen_count
print "ups2s visen", calculate_visen(tmp_ups2.hadroncool_r_coolvisen)
print "ups2s l4dec", 100.*tmp_ups2.hadroncool_l4dec_count/tmp_ups2.hadroncool_coolvisen_count
print "ups3s visen", calculate_visen(tmp_ups3.hadroncool_r_coolvisen)
print "ups3s l4dec", 100.*tmp_ups3.hadroncool_l4dec_count/tmp_ups3.hadroncool_coolvisen_count






tmp_peak1 = getrd(1, "peak", "18")
tmp_cont1 = getrd(1, "cont", "18")
tmp_peak2 = getrd(2, "peak", "21")
tmp_cont2 = getrd(2, "cont", "21")
tmp_peak3 = getrd(3, "peak", "16")
tmp_cont3 = getrd(3, "cont", "16")
tmp_ptoc1 = (tmp_peak1.hadron * (mc1all.bhabha / mc1all.hadron) - tmp_peak1.bhabha) \
        / (tmp_cont1.hadron * (mc1all.bhabha / mc1all.hadron) - tmp_cont1.bhabha)
tmp_ptoc2 = (tmp_peak2.hadron * (mc2all.bhabha / mc2all.hadron) - tmp_peak2.bhabha) \
        / (tmp_cont2.hadron * (mc2all.bhabha / mc2all.hadron) - tmp_cont2.bhabha)
tmp_ptoc3 = (tmp_peak3.hadron * (mc3all.bhabha / mc3all.hadron) - tmp_peak3.bhabha) \
        / (tmp_cont3.hadron * (mc3all.bhabha / mc3all.hadron) - tmp_cont3.bhabha)
tmp_ups1 = tmp_peak1 + tmp_cont1 * -tmp_ptoc1
tmp_ups2 = tmp_peak2 + tmp_cont2 * -tmp_ptoc2
tmp_ups3 = tmp_peak3 + tmp_cont3 * -tmp_ptoc3

print "with the upper databases"
print "ups1s visen", calculate_visen(tmp_ups1.hadroncool_r_coolvisen)
print "ups2s visen", calculate_visen(tmp_ups2.hadroncool_r_coolvisen)
print "ups3s visen", calculate_visen(tmp_ups3.hadroncool_r_coolvisen)



tmp_peak1 = getrd(1, "peak", "19")
tmp_cont1 = getrd(1, "cont", "19")
tmp_peak2 = getrd(2, "peak", "23")
tmp_cont2 = getrd(2, "cont", "23")
tmp_peak3 = getrd(3, "peak", "17")
tmp_cont3 = getrd(3, "cont", "17")
tmp_ptoc1 = (tmp_peak1.hadron * (mc1all.bhabha / mc1all.hadron) - tmp_peak1.bhabha) \
        / (tmp_cont1.hadron * (mc1all.bhabha / mc1all.hadron) - tmp_cont1.bhabha)
tmp_ptoc2 = (tmp_peak2.hadron * (mc2all.bhabha / mc2all.hadron) - tmp_peak2.bhabha) \
        / (tmp_cont2.hadron * (mc2all.bhabha / mc2all.hadron) - tmp_cont2.bhabha)
tmp_ptoc3 = (tmp_peak3.hadron * (mc3all.bhabha / mc3all.hadron) - tmp_peak3.bhabha) \
        / (tmp_cont3.hadron * (mc3all.bhabha / mc3all.hadron) - tmp_cont3.bhabha)
tmp_ups1 = tmp_peak1 + tmp_cont1 * -tmp_ptoc1
tmp_ups2 = tmp_peak2 + tmp_cont2 * -tmp_ptoc2
tmp_ups3 = tmp_peak3 + tmp_cont3 * -tmp_ptoc3

print "with the lower databases"
print "ups1s visen", calculate_visen(tmp_ups1.hadroncool_r_coolvisen)
print "ups2s visen", calculate_visen(tmp_ups2.hadroncool_r_coolvisen)
print "ups3s visen", calculate_visen(tmp_ups3.hadroncool_r_coolvisen)




















mc1 = {}
mc1["ggg"] = getmc(1, "ggg", "18")
mc1["gggam"] = getmc(1, "gggam", "18")
mc1["qq"] = getmc(1, "qq", "18")
mc1["ee0"] = getmc(1, "ee0", "18")
mc1["ee"] = getmc(1, "ee", "18")
mc1["mumu0"] = getmc(1, "mumu0", "18")
mc1["mumu"] = getmc(1, "mumu", "18")
mc1["tautau"] = getmc(1, "tautau", "18")

print 100.*do_p1totaleff(domc1(False, dobmm=0, dor=0, docas=0, dogggam=0))

mc1 = {}
mc1["ggg"] = getmc(1, "ggg", "19")
mc1["gggam"] = getmc(1, "gggam", "19")
mc1["qq"] = getmc(1, "qq", "19")
mc1["ee0"] = getmc(1, "ee0", "19")
mc1["ee"] = getmc(1, "ee", "19")
mc1["mumu0"] = getmc(1, "mumu0", "19")
mc1["mumu"] = getmc(1, "mumu", "19")
mc1["tautau"] = getmc(1, "tautau", "19")

print 100.*do_p1totaleff(domc1(False, dobmm=0, dor=0, docas=0, dogggam=0))



mc2 = {}
mc2["ggg"] = getmc(2, "ggg", "21")
mc2["gggam"] = getmc(2, "gggam", "21")
mc2["qq"] = getmc(2, "qq", "21")
mc2["ee0"] = getmc(2, "ee0", "21")
mc2["ee"] = getmc(2, "ee", "21")
mc2["mumu0"] = getmc(2, "mumu0", "21")
mc2["mumu"] = getmc(2, "mumu", "21")
mc2["tautau"] = getmc(2, "tautau", "21")
mc2["cas"] = getmc(2, "cas", "21")
mc2["casll0"] = getmc(2, "casll0", "21")
mc2["casll"] = getmc(2, "casll", "21")

print 100.*do_p1totaleff(domc2(False, dobmm=0, dor=0, docas=0, dogggam=0))

mc2 = {}
mc2["ggg"] = getmc(2, "ggg", "23")
mc2["gggam"] = getmc(2, "gggam", "23")
mc2["qq"] = getmc(2, "qq", "23")
mc2["ee0"] = getmc(2, "ee0", "23")
mc2["ee"] = getmc(2, "ee", "23")
mc2["mumu0"] = getmc(2, "mumu0", "23")
mc2["mumu"] = getmc(2, "mumu", "23")
mc2["tautau"] = getmc(2, "tautau", "23")
mc2["cas"] = getmc(2, "cas", "23")
mc2["casll0"] = getmc(2, "casll0", "23")
mc2["casll"] = getmc(2, "casll", "23")

print 100.*do_p1totaleff(domc2(False, dobmm=0, dor=0, docas=0, dogggam=0))

