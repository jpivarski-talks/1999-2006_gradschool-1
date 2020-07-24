basedir = "/home/mccann/synthesis/"
import cPickle as pickle, Numeric, biggles, hist

class RunSummary : pass
initialrunlist = pickle.load(open(basedir+"lumieff/initialrunlist.p"))
runsummary = pickle.load(open(basedir+"lumieff/runsummary.p"))

class RunRecord : pass

def new_package():
  comb = RunRecord()
  execfile("combinetype_init.py")
  return comb

def addto_package(a, runnum):
  rec = pickle.load(open(basedir+"pickle/db_"+str(runnum)+".p"))
  if len(dir(rec)) != 366:
    raise ValueError, "something's wrong with "+str(runnum)
  for v in dir(rec):
    if v not in ("run", "last", "ebeam", "__doc__", "__module__"):
      if type(eval("a."+v)) == tuple:
        c = list(eval("a."+v))
        r = eval("rec."+v)
        for i in (0,1,2): c[i] += r[i]
        exec "a."+v+" = tuple(c)"
      else:
        exec "a."+v+" += rec."+v

def compare_packages(a, b, verbosity=0):
  sofar = True
  for v in dir(b):
    if v not in ("run", "last", "ebeam", "__doc__", "__module__"):
      if type(eval("a."+v)) == tuple:
        sofar = sofar and eval("a."+v+"[0] == b."+v+"[0]")
        sofar = sofar and eval("a."+v+"[1] == b."+v+"[1]")
        sofar = sofar and eval("a."+v+"[2] == b."+v+"[2]")
      else:
        sofar = sofar and eval("a."+v+" == b."+v)
      if verbosity > 0 and not sofar:
        print v
        if verbosity == 1: verbosity = 0
  return sofar

cont = new_package()
peak = new_package()
for r in initialrunlist:
  if runsummary[r].kind == 'c' and runsummary[r].res == 3:
    try:
      addto_package(cont, r)
    except IOError: pass
  if runsummary[r].kind == 'p' and runsummary[r].res == 3:
    try:
      addto_package(peak, r)
    except IOError: pass

# cont = new_package()
# peak = new_package()
# for r in initialrunlist:
#   if r in [121899, 121904, 121906, 122080, 122081, 122083, 122091, 122418, 122429, 122586, 122587, 122594, 122430, 122800, 122802]:
#     try:
#       addto_package(cont, r)
#       print "off-res", r
#     except IOError: pass
#   if r in [121969, 121972, 122132, 122136, 122143, 122147, 122133, 122576, 122647, 122816, 122829, 122831, 123043, 122832, 123044]:
#     try:
#       addto_package(peak, r)
#       print "on-res", r
#     except IOError: pass

monte_carlo = hist.h1(60, 0., 1.2, vals=[0, 0, 0, 1.71828, 0, \
2.19225, 3.71552, 3.30049, 7.5774, 7.05072, 12.3834, 13.7737, 18.0992, \
29.5093, 40.0744, 41.3412, 73.1172, 87.5791, 120.026, 131.712, \
190.291, 267.39, 352.673, 431.37, 571.363, 724.011, 839.47, 1140.85, \
1329.17, 1636.02, 2012.1, 2406.28, 2757.2, 3138.12, 3509.24, 4034.42, \
4364.67, 4666.25, 5204.9, 5563.57, 5742.44, 5641.72, 5814.84, 5625.07, \
5534.19, 5022.68, 4576.48, 3929.41, 3390.26, 2701.96, 1812.06, \
1067.65, 641.305, 385.562, 261.084, 148.978, 101.362, 61.5583, \
38.9909, 51.0872])

# for r in initialrunlist:
#   if runsummary[r].kind == 'p' and runsummary[r].res == 3:
#     try:
#       open(basedir+"pickle/db_"+str(r)+".p")
#       print r
#       peak = new_package()
#       addto_package(peak, r)
#       ptoc = float(peak.c_gam)/float(cont.c_gam)
#       histogramize(peak)
#       p = (peak.mh_had_visen - cont.mh_had_visen * ptoc).plot(False, points=True, errorbars=True)
#       ptomc = (peak.mh_had_visen - cont.mh_had_visen * ptoc).int(0.4,1.2) / monte_carlo.int(0.4,1.2)
#       p.add((monte_carlo * ptomc).lines())
#       p.show()
#       raw_input("wait> ")
#     except IOError: pass
# # not any one of these is weird

execfile("combinetype_histogramize.py")
histogramize(cont)
histogramize(peak)


ptoc = float(peak.c_gam)/float(cont.c_gam)
p = (peak.mh_had_visen - cont.mh_had_visen * ptoc).plot(False, errorbars=True)
ptomc = (peak.mh_had_visen - cont.mh_had_visen * ptoc).int(0.4,1.2) / monte_carlo.int(0.4,1.2)
p.add((monte_carlo * ptomc).lines())
p.show()


ptoc = float(peak.c_gam)/float(cont.c_gam)
p = peak.mh_had_visen.plot()
p.add((cont.mh_had_visen * ptoc).steps())
p.show()

counter = 0
cont = new_package()
for r in initialrunlist:
  if runsummary[r].kind == 'c' and runsummary[r].res == 3:
    try:
      open(basedir+"pickle/db_"+str(r)+".p")
      print r
      addto_package(cont, r)
      counter += 1
      if counter % 10 == 0:
        ptoc = float(peak.c_gam)/float(cont.c_gam)
        histogramize(cont)
        p = peak.mh_had_visen.plot()
        p.add((cont.mh_had_visen * ptoc).errorbars())
        p.show()
        raw_input("wait> ")
        cont = new_package()
    except IOError: pass


# what's wrong with the world today:
ptoc = float(peak.c_gam)/float(cont.c_gam)
p = peak.mh_had_visen.plot()
p.add((cont.mh_had_visen * ptoc).errorbars())
p.write_eps("../plots/whats_wrong_with_the_world_today.ps")


for r in initialrunlist:
  if runsummary[r].kind == 'p' and runsummary[r].res == 3:
    try:
      open(basedir+"pickle/db_"+str(r)+".p")
      print r
    except IOError: pass
# 121474 - 121626
cont = new_package()
peak = new_package()
for r in initialrunlist:
  if r < 121886 and runsummary[r].kind == 'c' and runsummary[r].res == 3:
    try:
      addto_package(cont, r)
    except IOError: pass
  if runsummary[r].kind == 'p' and runsummary[r].res == 3:
    try:
      addto_package(peak, r)
    except IOError: pass
ptoc = float(peak.c_gam)/float(cont.c_gam)
histogramize(cont)
histogramize(peak)
p = peak.mh_had_visen.plot()
p.add((cont.mh_had_visen * ptoc).errorbars())
p.show()




cont = new_package()
peak = new_package()
for r in initialrunlist:
  if runsummary[r].kind == 'c' and runsummary[r].res == 3:
    try:
      addto_package(cont, r)
    except IOError: pass
  if runsummary[r].kind == 'p' and runsummary[r].res == 3:
    try:
      addto_package(peak, r)
    except IOError: pass
ptoc = float(peak.c_gam)/float(cont.c_gam)
histogramize(cont)
histogramize(peak)
p = peak.mh_had_p2.plot()
p.add((cont.mh_had_p2 * ptoc).steps())
p.xrange = 0.8, 1.2
p.show()

for i in cont.mh_had_p2.vals:
  print i
print ptoc


# import minuit, math, Numeric

# def gauss(x, a, m, s):
#   return a * math.exp(-(x-m)**2/2./s**2) / math.sqrt(2.*math.pi) / s

# def chi1(a, m, s):
#   c = 0.
#   for x in Numeric.arange(0.99, 1.01, 0.001):
#     c += peak.mh_had_p2(x) - gauss(x, a, m, s)
#   return c

# def chi2(a, m, s):
#   c = 0.
#   for x in Numeric.arange(0.99, 1.01, 0.001):
#     c += cont.mh_had_p2(x) - gauss(x, a, m, s)
#   return c

# p = peak.mh_had_p2.plot()
# xvals = Numeric.arange(0.99, 1.01, 0.001)
# yvals = map(gauss, xvals, [100., 1., 0.1])
# p.add()

# minuit.Minuit(chi1, start=[]).migrad()



ptoc = float(peak.c_gam)/float(cont.c_gam)
(peak.mh_had_trig - cont.mh_had_trig * ptoc).plot().write_eps("../plots/peak_mh_had_trig.eps")
(peak.mh_had_d0close1 - cont.mh_had_d0close1 * ptoc).plot().write_eps("../plots/peak_mh_had_d0close1.eps")
(peak.mh_had_d0close2 - cont.mh_had_d0close2 * ptoc).plot().write_eps("../plots/peak_mh_had_d0close2.eps")
(peak.mh_had_p2 - cont.mh_had_p2 * ptoc).plot().write_eps("../plots/peak_mh_had_p2.eps")
(peak.mh_had_wz1 - cont.mh_had_wz1 * ptoc).plot().write_eps("../plots/peak_mh_had_wz1.eps")
(peak.mh_had_wz2 - cont.mh_had_wz2 * ptoc).plot().write_eps("../plots/peak_mh_had_wz2.eps")
(peak.mh_had_z0close1 - cont.mh_had_z0close1 * ptoc).plot().write_eps("../plots/peak_mh_had_z0close1.eps")
(peak.mh_had_z0close2 - cont.mh_had_z0close2 * ptoc).plot().write_eps("../plots/peak_mh_had_z0close2.eps")
(peak.mh_had_visen - cont.mh_had_visen * ptoc).plot().write_eps("../plots/peak_mh_had_visen.eps")
(peak.mh_had_coolvisen - cont.mh_had_coolvisen * ptoc).plot().write_eps("../plots/peak_mh_had_coolvisen.eps")
(peak.mh_had_ntracks - cont.mh_had_ntracks * ptoc).plot().write_eps("../plots/peak_mh_had_ntracks.eps")

list_of_histograms = [
  "mh_had_trig",
  "mh_had_d0close1",
  "mh_had_d0close2",
  "mh_had_p2",
  "mh_had_wz1",
  "mh_had_wz2",
  "mh_had_z0close1",
  "mh_had_z0close2",
  "mh_had_visen",
  "mh_had_ntracks",
  "mh_had_coolvisen",
  "mh_had_coolvisen_nol4dec",
  "mh_gam_e2",
  "mh_gam_ntracks",
  "mh_gam_zback",
  "mh_gam_z1",
  "mh_gam_z2",
  "mh_gam_z1_noexclude",
  "mh_gam_z2_noexclude",
  "mh_gam_phiback",
  "mh_gam_phiback_notracks",
  "mh_gam_trigcorrect",
  "mh_gam_e3in",
  "mh_gam_e3out",
  "mh_tkl_e2",
  "mh_tkl_ntracks",
  "mh_tkl_zback",
  "mh_tkl_z1",
  "mh_tkl_z2",
  "mh_tkl_z1_noexclude",
  "mh_tkl_z2_noexclude",
  "mh_tkl_phiback",
  "mh_tkl_phiback_notrackcut",
  "mh_bha_trig",
  "mh_bha_p2",
  "mh_bha_d0close1",
  "mh_bha_d0close2",
  "mh_bha_wz1",
  "mh_bha_wz2",
  "mh_bha_z0close1",
  "mh_bha_z0close2",
  "mh_bha_eisr",
  "mh_bha_econstraint",
  "mh_bha_costheta1",
  "mh_bha_costheta2",
  "mh_bha_e2",
  "mh_bha_trignumer",
  "mh_bha_trigdenom",
  "mh_bha_trignumer_showergeometry",
  "mh_bha_trigdenom_showergeometry",
  "mh_bha_trignumer_showergeometry2",
  "mh_bha_trigdenom_showergeometry2",
  "mh_bha_trignumer_excludeblocks",
  "mh_bha_trigdenom_excludeblocks",
  "mh_bha_trignumer_showergeometry_excludeblocks",
  "mh_bha_trigdenom_showergeometry_excludeblocks",
  "mh_bha_trignumer_showergeometry2_excludeblocks",
  "mh_bha_trigdenom_showergeometry2_excludeblocks",
  "mh_mup_trig",
  "mh_mup_p2",
  "mh_mup_d0close1",
  "mh_mup_d0close2",
  "mh_mup_wz1",
  "mh_mup_wz2",
  "mh_mup_z0close1",
  "mh_mup_z0close2",
  "mh_mup_eisr",
  "mh_mup_econstraint",
  "mh_mup_costheta1",
  "mh_mup_costheta2",
  "mh_mup_e2",
  "mh_cos_trig",
  "mh_cos_ntracks",
  "mh_cos_d0close1",
  "mh_cos_d0close2",
  "mh_cos_pdotp1",
  "mh_cos_pdotp2",
  "mh_cos_ccen",
  "mh_cos_visen",
  "mh_bge_trig",
  "mh_bge_ntracks",
  "mh_bge_d0close1",
  "mh_bge_d0close2",
  "mh_bge_wz1",
  "mh_bge_wz2",
  "mh_bge_z0close1",
  "mh_bge_z0close2",
  "mh_bge_pdotp1",
  "mh_bge_pdotp2",
  "mh_bge_wpz",
  "mh_bge_visen",
  "mh_bgp_trig",
  "mh_bgp_ntracks",
  "mh_bgp_d0close1",
  "mh_bgp_d0close2",
  "mh_bgp_wz1",
  "mh_bgp_wz2",
  "mh_bgp_z0close1",
  "mh_bgp_z0close2",
  "mh_bgp_pdotp1",
  "mh_bgp_pdotp2",
  "mh_bgp_wpz",
  "mh_bgp_visen",
  "mh_ccs_d0close1",
  "mh_ccs_d0close2",
  "mh_ccs_p2",
  "mh_ccs_wz1",
  "mh_ccs_wz2",
  "mh_ccs_z0close1",
  "mh_ccs_z0close2",
  "mh_ccs_ntracks",
  "mh_ccs_chen",
  "mh_ccs_hadtrig",
  "mh_ccs_e1",
  "mh_ccs_e2",
  "mh_ncs_hadtrig",
  "mh_ncs_e1",
  "mh_ncs_e2",
  ]

for histname in list_of_histograms:
  exec "cont."+histname+".plot().write_eps(\"../plots/"+histname+".eps\")"
