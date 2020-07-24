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

print "nobeam:", nobeam.all, nobeam.cosmic
print "ebeam:", ebeam.all, ebeam.cosmic, ebeam.beamgase
print "pbeam:", pbeam.all, pbeam.cosmic, pbeam.beamgasp
ebeam_cosmic_factor = float(ebeam.cosmic)/float(nobeam.cosmic)
pbeam_cosmic_factor = float(pbeam.cosmic)/float(nobeam.cosmic)

bge = ebeam + (nobeam * -ebeam_cosmic_factor)
bgp = pbeam + (nobeam * -pbeam_cosmic_factor)

p = logify(ebeam.cosmic_logpdotp).plot()
p1 = logify(ebeam.cosmic_logpdotp).steps()
p1.label = r"$e^-$-beam"
p2 = logify((nobeam.cosmic_logpdotp * ebeam_cosmic_factor)).steps(linetype="dashed")
p2.label = r"no-beam"
p3 = biggles.LineX(0.1, linetype="dotted")
p3.label = "cuts"
p4 = biggles.LineX(0.001, linetype="dotted")
p.add(p1)
p.add(p2)
p.add(p3)
p.add(p4)
p.add(biggles.PlotKey(0.1, 0.9, [p1, p2, p3]))
p.x1.log = 1
p.x1.range = 1e-10, 1.
p.x1.label = r"$1 - |p_1\cdot p_2|$"
p.aspect_ratio = 0.5
p.show()
p.write_eps("plots/datasets_cosmicscale_a.eps")

p = logify(pbeam.cosmic_logpdotp).plot()
p1 = logify(pbeam.cosmic_logpdotp).steps()
p1.label = r"$e^+$-beam"
p2 = logify((nobeam.cosmic_logpdotp * pbeam_cosmic_factor)).steps(linetype="dashed")
p2.label = r"no-beam"
p3 = biggles.LineX(0.1, linetype="dotted")
p3.label = "cuts"
p4 = biggles.LineX(0.001, linetype="dotted")
p.add(p1)
p.add(p2)
p.add(p3)
p.add(p4)
p.add(biggles.PlotKey(0.1, 0.9, [p1, p2, p3]))
p.x1.log = 1
p.x1.range = 1e-10, 1.
p.x1.label = r"$1 - |p_1\cdot p_2|$"
p.aspect_ratio = 0.5
p.show()
p.write_eps("plots/datasets_cosmicscale_b.eps")

p = logify(ebeam.beamgase_logpdotp).plot()
p1 = logify(ebeam.beamgase_logpdotp).steps()
p1.label = r"$e^-$-beam"
p2 = logify((nobeam.beamgase_logpdotp * ebeam_cosmic_factor)).steps(linetype="dashed")
p2.label = r"no-beam"
p3 = biggles.LineX(0.1, linetype="dotted")
p3.label = "cuts"
p4 = biggles.LineX(0.001, linetype="dotted")
p.add(p1)
p.add(p2)
p.add(p3)
p.add(p4)
p.add(biggles.PlotKey(0.1, 0.9, [p1, p2, p3]))
p.x1.log = 1
p.x1.range = 1e-10, 1.
p.x1.label = r"$1 - |p_1\cdot p_2|$"
p.aspect_ratio = 0.5
p.show()
p.write_eps("plots/datasets_cosmicscale_c.eps")

p = logify(pbeam.beamgasp_logpdotp).plot()
p1 = logify(pbeam.beamgasp_logpdotp).steps()
p1.label = r"$e^+$-beam"
p2 = logify((nobeam.beamgasp_logpdotp * pbeam_cosmic_factor)).steps(linetype="dashed")
p2.label = r"no-beam"
p3 = biggles.LineX(0.1, linetype="dotted")
p3.label = "cuts"
p4 = biggles.LineX(0.001, linetype="dotted")
p.add(p1)
p.add(p2)
p.add(p3)
p.add(p4)
p.add(biggles.PlotKey(0.1, 0.9, [p1, p2, p3]))
p.x1.log = 1
p.x1.range = 1e-10, 1.
p.x1.label = r"$1 - |p_1\cdot p_2|$"
p.aspect_ratio = 0.5
p.show()
p.write_eps("plots/datasets_cosmicscale_d.eps")

pbeam.beamgasp_logpdotp.plot().show()
print pbeam.beamgasp, pbeam.beamgasp_logpdotp.sum(-10, -3)

#####################

print cont1.hadron_cvisen.sum(0.,0.4)/cont1.hadron_cvisen.sum()
print cont2.hadron_cvisen.sum(0.,0.4)/cont2.hadron_cvisen.sum()
print cont3.hadron_cvisen.sum(0.,0.4)/cont3.hadron_cvisen.sum()

allcont = cont1 + cont2 + cont3

# from minuit import *
# def chi2(area=12000., wid=0.074, cen=0.103, a2=100., c2=0.2, w2=0.1, a3=100., c3=0.2, w3=0.1):
#   p = allcont.hadron_cvisen.plot()
#   x = Numeric.arange(0., 1.2, 0.01)
#   y = Numeric.arange(0., 1.2, 0.01)
#   chi = 0.
#   for i, xi in enumerate(x):
#     if xi > 0.103:
#       y[i] = area * wid**2 / ((xi - cen)**2 + wid**2) + \
#              a2 * exp(-(xi - c2)**2/2./w2**2)
#     else:
#       y[i] = a3 * exp(-(xi - c3)**2/2./w3**2)
#     if 0.070 < xi < 0.4:
#       chi += float(y[i] - allcont.hadron_cvisen(xi))**2/float(allcont.hadron_cvisen(xi))
#   p.add(biggles.Curve(x, y))
#   p.add(biggles.LineX(0.4, linetype="dotted"))
#   p.show()
#   print [area, wid, cen, a2, c2, w2, a3, c3, w3]
#   return chi
# # m = Minuit(chi2, start=[9799.2731968022345, 0.099002750320770383, 0.10788223178521787, 1428.4721694589882, 0.28467581201802777, 0.12506827405606946, 12100., 0.090, 0.02])
# # m.migrad()
# chi2(9767.3889516768413, 0.098751665380004933, 0.10752800951840705, 1410.411844713158, 0.28448100217338945, 0.12650381838520536, 12802.885849865814, 0.08948721622732643, 0.02299330693866063)

from minuit import *
def chi2(a, b):
  p = allcont.hadron_cvisen.plot()
  x = Numeric.arange(0.0895, 1.1, 0.01)
  x1 = Numeric.arange(0.0895, 0.3, 0.01)
  x2 = Numeric.arange(0.0895, 1.1, 0.01)
  y = Numeric.arange(0.0895, 0.3, 0.01)
  y2 = Numeric.arange(0.0895, 1.1, 0.01)
  chi = 0.
  area = 0.
  for i, xi in enumerate(x):
    y2[i] = a * exp(-b*xi)
    if xi < 0.3:
      y[i] = a * exp(-b*xi)
      chi += float(y[i] - allcont.hadron_cvisen(xi))**2/float(allcont.hadron_cvisen(xi))
    if xi > 0.4:
      area += y2[i]*0.01
#  p.add(biggles.Curve(x1, y))
#  p.add(biggles.Curve(x2, y2, linetype="longdashed"))
  p.add(biggles.LineX(0.4, linetype="dotted"))
  p.aspect_ratio = 0.5
  p.x1.label = r"$E_{vis}$ of continuum"
  p.show()
  p.write_eps("plots/datasets_visen_continuum.eps")
  print [a, b]
  print area, allcont.hadron_cvisen.int(0.4, 1.2), area/allcont.hadron_cvisen.int(0.4, 1.2)
  # this extrapolation yielded 11% two-photon after the cut
  return chi
# chi2(50000., 10)
# m = Minuit(chi2, start=[50000., 10])
# m.migrad()
chi2(21666.412333091983, 6.1153478081851533)







# def overlay(sample1, sample2, histname, factor=1., line1=None, line2=None):
#   p = eval(str(sample1)+"."+str(histname)+".plot()")
#   p.add(eval("("+str(sample2)+"."+str(histname)+" * "+str(factor)+").steps(linetype=\"dashed\")"))
#   if line1 != None:
#     p.add(biggles.LineX(line1, linetype="dotted"))
#   if line2 != None:
#     p.add(biggles.LineX(line2, linetype="dotted"))
#   return p

# def overlay_logify(sample1, sample2, histname, factor=1., line1=None, line2=None):
#   p = eval("logify("+str(sample1)+"."+str(histname)+").plot()")
#   p.add(eval("logify("+str(sample2)+"."+str(histname)+" * "+str(factor)+").steps(linetype=\"dashed\")"))
#   if line1 != None:
#     p.add(biggles.LineX(line1, linetype="dotted"))
#   if line2 != None:
#     p.add(biggles.LineX(line2, linetype="dotted"))
#   p.x1.log = 1
#   return p

# def title(p, t, aspect_ratio=None):
#   p.x1.label = t
#   if aspect_ratio != None:
#     p.aspect_ratio = aspect_ratio
#   return p


# overlay("ebeam", "nobeam", "beamgase_logpdotp", 1.4529).show()
# overlay("pbeam", "nobeam", "beamgasp_logpdotp", 0.2459).show()

# data = getrd_byrun(121899)
# data += getrd_byrun(121904)
# data += getrd_byrun(122081)
# data += getrd_byrun(122083)
# data += getrd_byrun(121969)
# data += getrd_byrun(121906)
# data += getrd_byrun(122080)
# data += getrd_byrun(122147)
# data += getrd_byrun(122132)
# data += getrd_byrun(122136)
# data += getrd_byrun(122429)
# data += getrd_byrun(122418)
# data += getrd_byrun(122430)
# data += getrd_byrun(122091)
# data += getrd_byrun(122576)
# data += getrd_byrun(122586)
# data += getrd_byrun(122587)
# data += getrd_byrun(122594)
# data += getrd_byrun(122647)
# data += getrd_byrun(122800)
# data += getrd_byrun(122802)
# data += getrd_byrun(122816)
# data += getrd_byrun(122829)





###############################################################

peak1 = getrd(1, "peak", "all")
cont1 = getrd(1, "cont", "all")
peak2 = getrd(2, "peak", "all")
cont2 = getrd(2, "cont", "all")
peak3 = getrd(3, "peak", "all")
cont3 = getrd(3, "cont", "all")
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

mc1all = domc1()
mc2all = domc2()
mc3all = domc3()

ptoc1 = (peak1.hadron * (mc1all.bhabha / mc1all.hadron) - peak1.bhabha) \
        / (cont1.hadron * (mc1all.bhabha / mc1all.hadron) - cont1.bhabha)
ptoc2 = (peak2.hadron * (mc2all.bhabha / mc2all.hadron) - peak2.bhabha) \
        / (cont2.hadron * (mc2all.bhabha / mc2all.hadron) - cont2.bhabha)
ptoc3 = (peak3.hadron * (mc3all.bhabha / mc3all.hadron) - peak3.bhabha) \
        / (cont3.hadron * (mc3all.bhabha / mc3all.hadron) - cont3.bhabha)

ptoc1 = float(peak1.gamgam) / float(cont1.gamgam)
ptoc2 = float(peak2.gamgam) / float(cont2.gamgam)
ptoc3 = float(peak3.gamgam) / float(cont3.gamgam)

ptomc1 = (peak1.hadron - (cont1.hadron * ptoc1)) / mc1all.hadron
ptomc2 = (peak2.hadron - (cont2.hadron * ptoc2)) / mc2all.hadron
ptomc3 = (peak3.hadron - (cont3.hadron * ptoc3)) / mc3all.hadron

def ups_overlay(res, histogram):
  da = eval("peak"+str(res)+"."+str(histogram)+" - " \
            "cont"+str(res)+"."+str(histogram)+" * ptoc"+str(res))
  mc = eval("mc"+str(res)+"all."+str(histogram)+" * ptomc"+str(res))
  p = da.plot(False, points=True, errorbars=True)
  p.add(mc.steps())
  return p


ups_overlay(1, "hadron_trig").show()
ups_overlay(1, "hadron_d0close").show()
ups_overlay(1, "hadron_logd0close").show()
ups_overlay(1, "hadron_wz").show()
ups_overlay(1, "hadron_logwz").show()
ups_overlay(1, "hadron_criticalz0close").show()
ups_overlay(1, "hadron_criticallogz0close").show()
ups_overlay(1, "hadron_anyz").show()
ups_overlay(1, "hadron_loganyz").show()
ups_overlay(1, "hadron_p1").show()
ups_overlay(1, "hadron_cvisen").show()
ups_overlay(1, "hadron_hotvisen").show()
ups_overlay(1, "hadron_tracks").show()
ups_overlay(1, "hadron_r_trignum").show()
ups_overlay(1, "hadron_r_d0close").show()
ups_overlay(1, "hadron_r_logd0close").show()
ups_overlay(1, "hadron_r_wz").show()
ups_overlay(1, "hadron_r_logwz").show()
ups_overlay(1, "hadron_r_criticalz0close").show()
ups_overlay(1, "hadron_r_criticallogz0close").show()
ups_overlay(1, "hadron_r_anyz").show()
ups_overlay(1, "hadron_r_loganyz").show()
ups_overlay(1, "hadron_r_p1").show()
ups_overlay(1, "hadron_r_coolvisen").show()
ups_overlay(1, "hadron_r_hotvisen").show()
ups_overlay(1, "hadron_r_tracks").show()

ups_overlay(2, "hadron_trig").show()
ups_overlay(2, "hadron_d0close").show()
ups_overlay(2, "hadron_logd0close").show()
ups_overlay(2, "hadron_wz").show()
ups_overlay(2, "hadron_logwz").show()
ups_overlay(2, "hadron_criticalz0close").show()
ups_overlay(2, "hadron_criticallogz0close").show()
ups_overlay(2, "hadron_anyz").show()
ups_overlay(2, "hadron_loganyz").show()
ups_overlay(2, "hadron_p1").show()
ups_overlay(2, "hadron_cvisen").show()
ups_overlay(2, "hadron_hotvisen").show()
ups_overlay(2, "hadron_tracks").show()
ups_overlay(2, "hadron_r_trignum").show()
ups_overlay(2, "hadron_r_d0close").show()
ups_overlay(2, "hadron_r_logd0close").show()
ups_overlay(2, "hadron_r_wz").show()
ups_overlay(2, "hadron_r_logwz").show()
ups_overlay(2, "hadron_r_criticalz0close").show()
ups_overlay(2, "hadron_r_criticallogz0close").show()
ups_overlay(2, "hadron_r_anyz").show()
ups_overlay(2, "hadron_r_loganyz").show()
ups_overlay(2, "hadron_r_p1").show()
ups_overlay(2, "hadron_r_coolvisen").show()
ups_overlay(2, "hadron_r_hotvisen").show()
ups_overlay(2, "hadron_r_tracks").show()

ups_overlay(3, "hadron_trig").show()
ups_overlay(3, "hadron_d0close").show()
ups_overlay(3, "hadron_logd0close").show()
ups_overlay(3, "hadron_wz").show()
ups_overlay(3, "hadron_logwz").show()
ups_overlay(3, "hadron_criticalz0close").show()
ups_overlay(3, "hadron_criticallogz0close").show()
ups_overlay(3, "hadron_anyz").show()
ups_overlay(3, "hadron_loganyz").show()
ups_overlay(3, "hadron_p1").show()
ups_overlay(3, "hadron_cvisen").show()
ups_overlay(3, "hadron_hotvisen").show()
ups_overlay(3, "hadron_tracks").show()
ups_overlay(3, "hadron_r_trignum").show()
ups_overlay(3, "hadron_r_d0close").show()
ups_overlay(3, "hadron_r_logd0close").show()
ups_overlay(3, "hadron_r_wz").show()
ups_overlay(3, "hadron_r_logwz").show()
ups_overlay(3, "hadron_r_criticalz0close").show()
ups_overlay(3, "hadron_r_criticallogz0close").show()
ups_overlay(3, "hadron_r_anyz").show()
ups_overlay(3, "hadron_r_loganyz").show()
ups_overlay(3, "hadron_r_p1").show()
ups_overlay(3, "hadron_r_coolvisen").show()
ups_overlay(3, "hadron_r_hotvisen").show()
ups_overlay(3, "hadron_r_tracks").show()





