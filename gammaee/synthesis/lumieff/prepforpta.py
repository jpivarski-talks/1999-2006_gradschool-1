basedir = "/home/mccann/synthesis/"
import cPickle as pickle, sys, os, re, Numeric, hist, biggles, math, jt
from minuit import *

class RunSummary: pass
initialrunlist = pickle.load(open(basedir+"lumieff/initialrunlist.p"))
runsummary = pickle.load(open(basedir+"lumieff/runsummary.p"))

skiplist = [123013, 123014]
testsample = filter(lambda r: runsummary[r].res == 3 and runsummary[r].kind == 'c' and r not in skiplist, initialrunlist)

def groupify(r):
  if 121400 < r < 121700: return 1
  if 121700 < r < 121850: return 2
  if 121850 < r < 122000: return 3
  if 122000 < r < 122200: return 4
  if 122200 < r < 122350: return 5
  if 122350 < r < 122500: return 6
  if 122500 < r < 122700: return 7
  if 122700 < r < 123200: return 8
  if 128000 < r < 128300: return 9
  raise Exception

def dividify(p):
  p.add(biggles.LineX(121400, type="longdashed"))
  p.add(biggles.LineX(121700, type="longdashed"))
  p.add(biggles.LineX(121850, type="longdashed"))
  p.add(biggles.LineX(122000, type="longdashed"))
  p.add(biggles.LineX(122200, type="longdashed"))
  p.add(biggles.LineX(122350, type="longdashed"))
  p.add(biggles.LineX(122500, type="longdashed"))
  p.add(biggles.LineX(122700, type="longdashed"))
  p.add(biggles.LineX(123200, type="longdashed"))
  p.add(biggles.LineX(128000, type="longdashed"))
  p.add(biggles.LineX(128300, type="longdashed"))

class RunRecord: pass
runrec = {}
for r in testsample:
  runrec[r] = pickle.load(open(basedir+"pickle/db_"+str(r)+".p"))

# uncorrected_gamgams = []
# corrected_gamgams = []
# uncorrected_gamgams_err = []
# corrected_gamgams_err = []
# for r in testsample:
#   uncorrected_gamgams.append(runrec[r].gamgam_cotT.sum(0.1, 1.23))
#   uncorrected_gamgams_err.append(runrec[r].gamgam_cotT.sumerr(0.1, 1.23))

#   corhist = (runrec[r].gamgam_cotT / runrec[r].bhabha_cotTnumer.divide_by_superset(runrec[r].bhabha_cotTdenom))
#   corrected_gamgams.append(corhist.sum(0.1, 1.23))
#   corrected_gamgams_err.append(corhist.sumerr(0.1, 1.23))
  
# p = biggles.FramedPlot()
# p.add(biggles.SymmetricErrorBarsY(testsample, uncorrected_gamgams, uncorrected_gamgams_err, color="red"))
# p.add(biggles.SymmetricErrorBarsY(testsample, corrected_gamgams, corrected_gamgams_err, color="blue"))
# p.xrange = 121400, 121700
# p.show()
# p.xrange = 121700, 121850
# p.show()
# p.xrange = 121850, 122000
# p.show()
# p.xrange = 122000, 122200
# p.show()
# p.xrange = 122200, 122350
# p.show()
# p.xrange = 122350, 122500
# p.show()
# p.xrange = 122500, 122700
# p.show()
# p.xrange = 122700, 123200
# p.show()
# p.xrange = 128000, 128300
# p.show()


# groups = range(1,10)
# uncorrected_gamgams = [0] * 9
# corrected_gamgams = [0] * 9
# uncorrected_gamgams_err = [0] * 9
# corrected_gamgams_err = [0] * 9
# for r in testsample:
#   g = groupify(r)
#   uncorrected_gamgams[g-1] += runrec[r].gamgam_cotT.sum(0.1, 1.23)
#   uncorrected_gamgams_err[g-1] += runrec[r].gamgam_cotT.sumerr(0.1, 1.23)**2

#   corhist = (runrec[r].gamgam_cotT / runrec[r].bhabha_cotTnumer.divide_by_superset(runrec[r].bhabha_cotTdenom))
#   corrected_gamgams[g-1] += runrec[r].gamgam_cotT.sum(0.1, 1.23)
#   corrected_gamgams_err[g-1] += runrec[r].gamgam_cotT.sumerr(0.1, 1.23)**2
# for i,v in enumerate(uncorrected_gamgams_err):
#   uncorrected_gamgams_err[i] = math.sqrt(v)
# for i,v in enumerate(corrected_gamgams_err):
#   corrected_gamgams_err[i] = math.sqrt(v)

# p = biggles.FramedPlot()
# p.add(biggles.SymmetricErrorBarsY(groups, Numeric.array(uncorrected_gamgams)-Numeric.array(corrected_gamgams), uncorrected_gamgams_err))
# p.add(biggles.Points(groups, Numeric.array(uncorrected_gamgams)-Numeric.array(corrected_gamgams), type="filled circle"))
# p.add(biggles.LineY(0.))
# p.xrange = 0.5, 9.5
# p.yrange = Numeric.array([-1,1]) * 50
# p.show()


# uncorrected_gamgams = []
# corrected_gamgams = []
# uncorrected_gamgams_err = []
# corrected_gamgams_err = []
# for r in testsample:
#   uncorrected_gamgams.append(runrec[r].gamgam_cotT.sum(0.1, 1.23))
#   uncorrected_gamgams_err.append(runrec[r].gamgam_cotT.sumerr(0.1, 1.23))

#   corhist = (runrec[r].gamgam_cotT / runrec[r].bhabha_cotTnumer.divide_by_superset(runrec[r].bhabha_cotTdenom))
#   corrected_gamgams.append(corhist.sum(0.1, 1.23))
#   corrected_gamgams_err.append(corhist.sumerr(0.1, 1.23))

# p = biggles.FramedPlot()
# p.add(biggles.SymmetricErrorBarsY(range(len(testsample)), Numeric.array(corrected_gamgams)-Numeric.array(uncorrected_gamgams), uncorrected_gamgams_err))
# p.add(biggles.Points(range(len(testsample)), Numeric.array(corrected_gamgams)-Numeric.array(uncorrected_gamgams), type="filled circle"))
# p.add(biggles.LineY(0.))
# p.x1.label = "Run index"
# p.x2.label = "BhabhaBarrel trigger correction is small"
# p.y1.label = "Corrected - uncorrected and statistical error"
# p.aspect_ratio = 8.5/11.
# p.show()
# p.write_eps("ptatalk/prepforpta1.eps")


# print filter(lambda (r,v): v < 0, zip(testsample, Numeric.array(corrected_gamgams)-Numeric.array(uncorrected_gamgams)))
# [(123013, -1.9285714285714306), (123014, -0.61111111111112137)]

correction_factor = []
correction_factor_err = []
for r in testsample:
  num = runrec[r].bhabha_cotTnumer.sum(0.1, 1.23)
  den = runrec[r].bhabha_cotTdenom.sum(0.1, 1.23)
  frac = float(num)/float(den)
  correction_factor_err.append(math.sqrt(frac*(1.-frac)/float(den)))

  corhist = (runrec[r].gamgam_cotT / runrec[r].bhabha_cotTnumer.divide_by_superset(runrec[r].bhabha_cotTdenom))
  den = corhist.sum(0.1, 1.23)
  num = runrec[r].gamgam_cotT.sum(0.1, 1.23)
  frac = float(num)/float(den)
  correction_factor.append(frac)

p = biggles.FramedArray(1,2)
p[0,0].add(biggles.Points(testsample, correction_factor, type="filled circle"))
p[0,0].add(biggles.SymmetricErrorBarsY(testsample, correction_factor, correction_factor_err))
p[0,0].yrange = 0.98, 1.
p[0,0].xrange = 121400, 123200
p[0,0].add(biggles.LineX(122226, type="longdashed"))
p[0,1].add(biggles.Points(testsample, correction_factor, type="filled circle"))
p[0,1].add(biggles.SymmetricErrorBarsY(testsample, correction_factor, correction_factor_err))
p[0,1].yrange = 0.98, 1.
p[0,1].xrange = 128102, 128164
p.aspect_ratio = 8.5/11./2.
p.xlabel = "Run Number"
p.ylabel = "BhabhaBarrel trigger efficiency"
p[0,0].add(biggles.PlotLabel(0.25, 0.1, "db16"))
p[0,0].add(biggles.PlotLabel(0.75, 0.1, "db17"))
p[0,1].add(biggles.PlotLabel(0.5, 0.1, "Extra 3S in db22"))
# p.show()
p.write_eps("ptatalk/prepforpta2.eps")
# LIES!  ALL LIES!  The exclusionblocks weren't active in my bhabha sample!

def group_correction_factor(gees):
  combine_correction_factor = []
  combine_correction_factor_err = []
  for r, c, e in zip(testsample, correction_factor, correction_factor_err):
    if groupify(r) in gees:
      combine_correction_factor.append(c)
      combine_correction_factor_err.append(e)
  return jt.wmean(zip(combine_correction_factor, combine_correction_factor_err))[0]
group1_cf = group_correction_factor([1])
group2_cf = group_correction_factor([2,3,4,5])
group3_cf = group_correction_factor([6,7,8])
group4_cf = group_correction_factor([9])

# [group1_cf, group2_cf, group3_cf, group4_cf] = [0.99767855156339857, 0.99336296199040242, 0.98772626160373478, 0.98944428510626869]

# correcting for those LIES
group1_cf = group_correction_factor([1])
group2_cf = group_correction_factor([1])
group3_cf = group_correction_factor([1])
group4_cf = group_correction_factor([1])

def use_cross_section(csfunc, filename):
  hads = []
  hads_err = []
  for r in testsample:
    c, e = csfunc(r)
    hads.append(c)
    hads_err.append(e)
  hads_center = jt.wmean(zip(hads, hads_err))[0]
  hads_sigs = []
  for r, c, e in zip(testsample, hads, hads_err):
    hads_sigs.append((c-hads_center)/e)
  hads_hist = hist.h1(50, -5, 5).fill(hads_sigs).rootn()
  def gauss(x, a, m, s):
    return a * math.exp(-(x-m)**2/2./s**2) / math.sqrt(2.*math.pi) / s
  chipoints = hads_hist.frame + (hads_hist.frame[1] - hads_hist.frame[0])/2.
  def chi2(a, m, s):
    c = 0.
    for i, x in zip(range(len(hads_hist.frame)), chipoints):
      if hads_hist.errs[i] > 0:
        c += (hads_hist.vals[i] - gauss(x, a, m, s))**2/hads_hist.errs[i]**2
    return c

  # def hist_look(a, m, s):
  #   p = hads_hist.plot()
  #   values = []
  #   for x in chipoints:
  #     values.append(gauss(x, a, m, s))
  #   p.add(biggles.Curve(chipoints, values))
  #   p.show()
  # hist_look(len(testsample)/5., 0, 1)

  m = Minuit(chi2, start=[len(testsample)/5., 0, 1])
  m.migrad()
  hist_chi2, hist_params, hist_errors = m.fval, m.values, m.errors
  ndf = len(filter(lambda x: x>0, hads_hist.errs))
  values = []
  for x in chipoints:
    values.append(gauss(x, *hist_params))
  hist_info = [["$\chi^2/ndf$", hist_chi2, "/", ndf], \
               ["RMS", hist_params[2], "$\pm$", hist_errors[2]]]

  p = biggles.Table(2,1)
  p[0,0] = biggles.FramedPlot()
  p[0,0].add(biggles.Points(Numeric.array(hads)/hads_center, range(len(testsample)), type="filled circle"))
  p[0,0].add(biggles.SymmetricErrorBarsX(Numeric.array(hads)/hads_center, range(len(testsample)), Numeric.array(hads_err)/hads_center))
  p[0,0].y1.draw_ticklabels = 0
  p[0,0].x1.label = "$\propto$ hadronic cross-section"
  p[0,0].add(biggles.LineX(1.))
  p[0,0].add(biggles.LineY(41.5, type="dashed"))
  l, r = 0.8, 1.2
  p[0,0].xrange = l, r
  p[0,0].add(biggles.DataLabel(l+0.15*(r-l), 41.5-7, "db16"))
  p[0,0].add(biggles.DataLabel(l+0.15*(r-l), 41.5+7, "db17"))
  p[0,1] = hads_hist.plot()
  p[0,1].add(biggles.Curve(chipoints, values))
  hist.addinfobox(p[0,1], hist_info, width=0.8, colwidth=[0.2,0.09,0.23], corner=1, numformat="%.2g")
  p[0,1].x1.label = "sigmas away from weighted mean"
  p[0,1].yrange = 0, 17
  p.aspect_ratio = 8.5/11.*4
  p.show()
  p.write_eps(filename)

def use_cross_section(csfunc, filename):
  hads = []
  hads_err = []
  for r in testsample:
    c, e = csfunc(r)
    hads.append(c)
    hads_err.append(e)
  hads_center = jt.wmean(zip(hads, hads_err))[0]

  p = biggles.FramedPlot()
  p.add(biggles.Points(range(len(testsample)), Numeric.array(hads)/hads_center, type="filled circle"))
  p.add(biggles.SymmetricErrorBarsY(range(len(testsample)), Numeric.array(hads)/hads_center, Numeric.array(hads_err)/hads_center))
  p.x1.draw_ticklabels = 0
  p.x1.label = "Runs by index"
  p.y1.label = "Normalized hadronic cross-section"
  p.add(biggles.LineY(1.))
  p.add(biggles.LineX(41.5, type="dashed"))
  l, r = 0.8, 1.2
  p.yrange = l, r+0.001
  p.add(biggles.DataLabel(41.5-10, l+0.15*(r-l), "db16"))
  p.add(biggles.DataLabel(41.5+10, l+0.15*(r-l), "db17"))
  p.aspect_ratio = 8.5/11.
  p.show()
  p.write_eps(filename)

def cross_section(r):
  cf = 0.
  if groupify(r) in [1]:
    cf = group1_cf
  elif groupify(r) in [2,3,4,5]:
    cf = group2_cf
  elif groupify(r) in [6,7,8]:
    cf = group3_cf
  elif groupify(r) in [9]:
    cf = group4_cf
  frac = float(runrec[r].hadron) / (float(runrec[r].gamgam) / cf)
  fracerr = frac * math.sqrt(1./float(runrec[r].hadron) + 1./float(runrec[r].gamgam))
  return frac, fracerr
use_cross_section(cross_section, "ptatalk/prepforpta3.eps")
# 

def cs_oldhadron(r):
  cf = 0.
  if groupify(r) in [1]:
    cf = group1_cf
  elif groupify(r) in [2,3,4,5]:
    cf = group2_cf
  elif groupify(r) in [6,7,8]:
    cf = group3_cf
  elif groupify(r) in [9]:
    cf = group4_cf
  frac = float(runrec[r].oldhadron) / (float(runrec[r].gamgam) / cf)
  fracerr = frac * math.sqrt(1./float(runrec[r].oldhadron) + 1./float(runrec[r].gamgam))
  return frac, fracerr
use_cross_section(cs_oldhadron, "ptatalk/prepforpta3_oldhadron.eps")
# 

def cs_oldhadronall(r):
  cf = 0.
  if groupify(r) in [1]:
    cf = group1_cf
  elif groupify(r) in [2,3,4,5]:
    cf = group2_cf
  elif groupify(r) in [6,7,8]:
    cf = group3_cf
  elif groupify(r) in [9]:
    cf = group4_cf
  frac = float(runrec[r].oldhadronall) / (float(runrec[r].gamgam) / cf)
  fracerr = frac * math.sqrt(1./float(runrec[r].oldhadronall) + 1./float(runrec[r].gamgam))
  return frac, fracerr
use_cross_section(cs_oldhadronall, "ptatalk/prepforpta3_oldhadronall.eps")
# 

def cs_oldhadronalloldgam(r):
  cf = 0.
  if groupify(r) in [1]:
    cf = group1_cf
  elif groupify(r) in [2,3,4,5]:
    cf = group2_cf
  elif groupify(r) in [6,7,8]:
    cf = group3_cf
  elif groupify(r) in [9]:
    cf = group4_cf
  frac = float(runrec[r].oldhadronall) / (float(runrec[r].gamgam_tighten_e2) / cf)
  fracerr = frac * math.sqrt(1./float(runrec[r].oldhadronall) + 1./float(runrec[r].gamgam_tighten_e2))
  return frac, fracerr
use_cross_section(cs_oldhadronalloldgam, "ptatalk/prepforpta3_oldhadronalloldgam.eps")
# 


def addtogroupsplot(p, csfunc, offset, color, kind):
  combinemap = {}
  combinemap[0] = []
  combinemap[1] = []
  combinemap[2] = []
  combinemap[3] = []
  combinemap[4] = []
  combinemap[5] = []
  combinemap[6] = []
  combinemap[7] = []
  combinemap[8] = []
  combinemap[9] = []
  for r in testsample:
    combinemap[0].append(csfunc(r))
    combinemap[groupify(r)].append(csfunc(r))
  groups = range(1,10)
  hadgroup = [0] * 9
  hadgroup_err = [0] * 9
  for g in groups:
    hadgroup[g-1], hadgroup_err[g-1] = jt.wmean(combinemap[g])
  center_of_groups = jt.wmean(combinemap[0])[0]
  tmp = biggles.Points(Numeric.array(groups)+offset, Numeric.array(hadgroup)/center_of_groups, type=kind, color=color)
  p.add(tmp)
  p.add(biggles.SymmetricErrorBarsY(Numeric.array(groups)+offset, Numeric.array(hadgroup)/center_of_groups, Numeric.array(hadgroup_err)/center_of_groups, color=color))
  p.add(biggles.LineY(1., type="longdashed"))
  return tmp


q = biggles.FramedPlot()
q_one = addtogroupsplot(q, cs_oldhadronalloldgam, -0.15, "black", "filled circle")
q_one.label = "Old hadron cuts, Gamgam cut at 0.9 eBeam"
q_two = addtogroupsplot(q, cs_oldhadronall, 0., "red", "filled square")
q_two.label = "Old hadron cuts, Gamgam cut at 0.7 eBeam"
q_three = addtogroupsplot(q, cross_section, 0.15, "blue", "filled diamond")
q_three.label = "New hadron cuts, Gamgam cut at 0.7 eBeam"
q.add(biggles.PlotKey(0.1, 0.25, [q_one, q_two, q_three]))
q.yrange = 0.92, 1.06
q.xrange = 0.5, 9.5
q.x1.ticks = range(1,10)
q.x1.subticks_size = 0
q.x2.ticks_size = 0
q.x2.subticks_size = 0
q.ylabel = "Normalized hadronic cross-section"
q.xlabel = "Continuum running period"
q.aspect_ratio = 8.5/11./1.5
# q.show()
q.write_eps("ptatalk/prepforpta4.eps")

r = biggles.FramedPlot()
r_one = addtogroupsplot(r, cs_oldhadronalloldgam, -0.15, "black", "filled circle")
r.yrange = 0.92, 1.06
r.xrange = 0.5, 9.5
r.x1.ticks = range(1,10)
r.x1.subticks_size = 0
r.x2.ticks_size = 0
r.x2.subticks_size = 0
r.ylabel = "Normalized hadronic cross-section"
r.xlabel = "Continuum running period"
r.aspect_ratio = 8.5/11./1.5
# r.show()
r.write_eps("ptatalk/prepforpta4_0.eps")




def addtogroupsplot2(csfunc):
  combinemap = {}
  combinemap[0] = []
  combinemap[1] = []
  combinemap[2] = []
  combinemap[3] = []
  combinemap[4] = []
  combinemap[5] = []
  combinemap[6] = []
  combinemap[7] = []
  combinemap[8] = []
  combinemap[9] = []
  for r in testsample:
    combinemap[0].append(csfunc(r))
    combinemap[groupify(r)].append(csfunc(r))
  groups = range(1,10)
  hadgroup = [0] * 9
  hadgroup_err = [0] * 9
  for g in groups:
    hadgroup[g-1], hadgroup_err[g-1] = jt.wmean(combinemap[g])
  center_of_groups = jt.wmean(combinemap[0])[0]

  centers, errors = Numeric.array(hadgroup)/center_of_groups, Numeric.array(hadgroup_err)/center_of_groups
  chi2 = 0.
  for c, e in zip(centers, errors):
    print (c-1), e
    chi2 += ((c-1)/e)**2
  print chi2

addtogroupsplot2(cross_section) # 12.6516285349
addtogroupsplot2(cs_oldhadron) # 36.5350290484
addtogroupsplot2(cs_oldhadronall) # 20.9166693414
addtogroupsplot2(cs_oldhadronalloldgam) # 25.7198624176
