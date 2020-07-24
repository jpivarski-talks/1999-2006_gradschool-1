execfile("/home/mccann/antithesis/utilities.py")
nobeam = getsb("cos")
ebeam = getsb("bge")
pbeam = getsb("bgp")
runstart = pickle.load(open("/home/mccann/antithesis/old_dotps/runstart.p"))
runend = pickle.load(open("/home/mccann/antithesis/old_dotps/runend.p"))
import time, biggles

def run_date(r):
  if r in runstart and r in runend:
    return (runstart[r] + runend[r])/2.
  elif r in runstart:
    return runstart[r]
  elif r in runend:
    return runend[r]
  else:
    raise Exception

# dbist = {}
# def getdber(r):
#   if r in dbist:
#     return dbist[r]
#   else:
#     dbist[r] = getdb(r)
#     return dbist[r]

allthe_h = {}
allthe_e = {}
allthe_p = {}
allthe_c = {}
allthe_b = {}
allthe_hvt = {}
allthe_evt = {}
allthe_pvt = {}
allthe_cvt = {}
allthe_bvt = {}
def getsome_h(r):
  if r in allthe_h:
    return allthe_h[r]
  else:
    therun = getdb(r)
    allthe_h[r] = therun.hadroncool
    allthe_e[r] = therun.beamgase
    allthe_p[r] = therun.beamgasp
    allthe_c[r] = therun.cosmic
    allthe_b[r] = therun.bhabha
    allthe_hvt[r] = therun.hadroncool_vstime
    allthe_evt[r] = therun.beamgase_vstime
    allthe_pvt[r] = therun.beamgasp_vstime
    allthe_cvt[r] = therun.cosmic_vstime
    allthe_bvt[r] = therun.bhabha_vstime
    return allthe_h[r]
def getsome_e(r):
  if r in allthe_e:
    return allthe_e[r]
  else:
    therun = getdb(r)
    allthe_h[r] = therun.hadroncool
    allthe_e[r] = therun.beamgase
    allthe_p[r] = therun.beamgasp
    allthe_c[r] = therun.cosmic
    allthe_b[r] = therun.bhabha
    allthe_hvt[r] = therun.hadroncool_vstime
    allthe_evt[r] = therun.beamgase_vstime
    allthe_pvt[r] = therun.beamgasp_vstime
    allthe_cvt[r] = therun.cosmic_vstime
    allthe_bvt[r] = therun.bhabha_vstime
    return allthe_e[r]
def getsome_p(r):
  if r in allthe_p:
    return allthe_p[r]
  else:
    therun = getdb(r)
    allthe_h[r] = therun.hadroncool
    allthe_e[r] = therun.beamgase
    allthe_p[r] = therun.beamgasp
    allthe_c[r] = therun.cosmic
    allthe_b[r] = therun.bhabha
    allthe_hvt[r] = therun.hadroncool_vstime
    allthe_evt[r] = therun.beamgase_vstime
    allthe_pvt[r] = therun.beamgasp_vstime
    allthe_cvt[r] = therun.cosmic_vstime
    allthe_bvt[r] = therun.bhabha_vstime
    return allthe_p[r]
def getsome_c(r):
  if r in allthe_c:
    return allthe_c[r]
  else:
    therun = getdb(r)
    allthe_h[r] = therun.hadroncool
    allthe_e[r] = therun.beamgase
    allthe_p[r] = therun.beamgasp
    allthe_c[r] = therun.cosmic
    allthe_b[r] = therun.bhabha
    allthe_hvt[r] = therun.hadroncool_vstime
    allthe_evt[r] = therun.beamgase_vstime
    allthe_pvt[r] = therun.beamgasp_vstime
    allthe_cvt[r] = therun.cosmic_vstime
    allthe_bvt[r] = therun.bhabha_vstime
    return allthe_c[r]
def getsome_b(r):
  if r in allthe_b:
    return allthe_b[r]
  else:
    therun = getdb(r)
    allthe_h[r] = therun.hadroncool
    allthe_e[r] = therun.beamgase
    allthe_p[r] = therun.beamgasp
    allthe_c[r] = therun.cosmic
    allthe_b[r] = therun.bhabha
    allthe_hvt[r] = therun.hadroncool_vstime
    allthe_evt[r] = therun.beamgase_vstime
    allthe_pvt[r] = therun.beamgasp_vstime
    allthe_cvt[r] = therun.cosmic_vstime
    allthe_bvt[r] = therun.bhabha_vstime
    return allthe_b[r]
def getsome_hvt(r):
  if r in allthe_hvt:
    return allthe_hvt[r]
  else:
    therun = getdb(r)
    allthe_h[r] = therun.hadroncool
    allthe_e[r] = therun.beamgase
    allthe_p[r] = therun.beamgasp
    allthe_c[r] = therun.cosmic
    allthe_b[r] = therun.bhabha
    allthe_hvt[r] = therun.hadroncool_vstime
    allthe_evt[r] = therun.beamgase_vstime
    allthe_pvt[r] = therun.beamgasp_vstime
    allthe_cvt[r] = therun.cosmic_vstime
    allthe_bvt[r] = therun.bhabha_vstime
    return allthe_hvt[r]
def getsome_evt(r):
  if r in allthe_evt:
    return allthe_evt[r]
  else:
    therun = getdb(r)
    allthe_h[r] = therun.hadroncool
    allthe_e[r] = therun.beamgase
    allthe_p[r] = therun.beamgasp
    allthe_c[r] = therun.cosmic
    allthe_b[r] = therun.bhabha
    allthe_hvt[r] = therun.hadroncool_vstime
    allthe_evt[r] = therun.beamgase_vstime
    allthe_pvt[r] = therun.beamgasp_vstime
    allthe_cvt[r] = therun.cosmic_vstime
    allthe_bvt[r] = therun.bhabha_vstime
    return allthe_evt[r]
def getsome_pvt(r):
  if r in allthe_pvt:
    return allthe_pvt[r]
  else:
    therun = getdb(r)
    allthe_h[r] = therun.hadroncool
    allthe_e[r] = therun.beamgase
    allthe_p[r] = therun.beamgasp
    allthe_c[r] = therun.cosmic
    allthe_b[r] = therun.bhabha
    allthe_hvt[r] = therun.hadroncool_vstime
    allthe_evt[r] = therun.beamgase_vstime
    allthe_pvt[r] = therun.beamgasp_vstime
    allthe_cvt[r] = therun.cosmic_vstime
    allthe_bvt[r] = therun.bhabha_vstime
    return allthe_pvt[r]
def getsome_cvt(r):
  if r in allthe_cvt:
    return allthe_cvt[r]
  else:
    therun = getdb(r)
    allthe_h[r] = therun.hadroncool
    allthe_e[r] = therun.beamgase
    allthe_p[r] = therun.beamgasp
    allthe_c[r] = therun.cosmic
    allthe_b[r] = therun.bhabha
    allthe_hvt[r] = therun.hadroncool_vstime
    allthe_evt[r] = therun.beamgase_vstime
    allthe_pvt[r] = therun.beamgasp_vstime
    allthe_cvt[r] = therun.cosmic_vstime
    allthe_bvt[r] = therun.bhabha_vstime
    return allthe_cvt[r]
def getsome_bvt(r):
  if r in allthe_bvt:
    return allthe_bvt[r]
  else:
    therun = getdb(r)
    allthe_h[r] = therun.hadroncool
    allthe_e[r] = therun.beamgase
    allthe_p[r] = therun.beamgasp
    allthe_c[r] = therun.cosmic
    allthe_b[r] = therun.bhabha
    allthe_hvt[r] = therun.hadroncool_vstime
    allthe_evt[r] = therun.beamgase_vstime
    allthe_pvt[r] = therun.beamgasp_vstime
    allthe_cvt[r] = therun.cosmic_vstime
    allthe_bvt[r] = therun.bhabha_vstime
    return allthe_bvt[r]

def greaterthan1(splitnum, selfunc):
#   thedates = []
  theratio = []
  theerror = []
  d = 0.
  n = 0
  h = 0.
  e = 0.
  p = 0.
  c = 0.
  b = 0.
  for r in initialrunlist:
    if selfunc(r) and r not in mybadruns:
      h += float(getsome_h(r))
      e += float(getsome_e(r))
      p += float(getsome_p(r))
      c += float(getsome_c(r))
      b += float(getsome_b(r))

#      d += run_date(r)
      n += 1

      if n == splitnum:
#         thedates.append(d/n)

        ebkgnd = 1. * (ebeam.hadroncool - 1.*nobeam.hadroncool*ebeam.cosmic/nobeam.cosmic) * e / ebeam.beamgase
        pbkgnd = 1. * (pbeam.hadroncool - 1.*nobeam.hadroncool*pbeam.cosmic/nobeam.cosmic) * p / pbeam.beamgasp
        cbkgnd = 1. * nobeam.hadroncool * c / nobeam.cosmic
        hadrons = h - ebkgnd/2. - pbkgnd/2. - cbkgnd
        hadrons_err = sqrt(h + c * (1.*nobeam.hadroncool/nobeam.cosmic)**2 + ebkgnd/2. + pbkgnd/2.)
        theratio.append(hadrons/b)
        theerror.append(hadrons/b*sqrt((hadrons_err/hadrons)**2 + 1./b))

        d = 0.
        n = 0
        h = 0.
        e = 0.
        p = 0.
        c = 0.
        b = 0.

  return theratio, theerror

def lessthan1(splitnum, selfunc):
#   thedates = []
  theratio = []
  theerror = []
  for r in initialrunlist:
    if selfunc(r) and r not in mybadruns:

      for i in range(splitnum):
#         thedates.append(runstart[r]*float(i)/float(splitnum))

        h = sum(getsome_hvt(r).vals[i*100/splitnum:(i+1)*100/splitnum])
        e = sum(getsome_evt(r).vals[i*100/splitnum:(i+1)*100/splitnum])
        p = sum(getsome_pvt(r).vals[i*100/splitnum:(i+1)*100/splitnum])
        c = sum(getsome_cvt(r).vals[i*100/splitnum:(i+1)*100/splitnum])
        b = sum(getsome_bvt(r).vals[i*100/splitnum:(i+1)*100/splitnum])

        ebkgnd = 1. * (ebeam.hadroncool - 1.*nobeam.hadroncool*ebeam.cosmic/nobeam.cosmic) * e / ebeam.beamgase
        pbkgnd = 1. * (pbeam.hadroncool - 1.*nobeam.hadroncool*pbeam.cosmic/nobeam.cosmic) * p / pbeam.beamgasp
        cbkgnd = 1. * nobeam.hadroncool * c / nobeam.cosmic
        hadrons = h - ebkgnd/2. - pbkgnd/2. - cbkgnd
        hadrons_err = sqrt(h + c * (1.*nobeam.hadroncool/nobeam.cosmic)**2 + ebkgnd/2. + pbkgnd/2.)
        theratio.append(hadrons/b)
        theerror.append(hadrons/b*sqrt((hadrons_err/hadrons)**2 + 1./b))

  return theratio, theerror

# Check: yes, they're the same

# thedates1, theratio1, theerror1 = greaterthan1(1)
# thedates2, theratio2, theerror2 = lessthan1(1)

# thedates = thedates1
# theratio = Numeric.array(theratio1) - Numeric.array(theratio2)
# theerror = Numeric.array(theerror1) - Numeric.array(theerror2)

# p = biggles.FramedPlot()
# p.add(biggles.Points(thedates, theratio, symboltype="filled circle", symbolsize=0.8))
# p.add(biggles.SymmetricErrorBarsY(thedates, theratio, theerror))
# p.show()

def whatever(splitnum, selfunc):
  if splitnum >= 1:
    return greaterthan1(splitnum, selfunc)
  elif splitnum <= -1:
    return lessthan1(-splitnum, selfunc)
  else:
    raise Exception

def makeaplot(selfunc, title, name):
  fracofrun = []
  allthewidths = []
  alltheerrors = []
  for splitnum in [-100, -50, -25, -10, -5, -2, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 20, 30, 40, 50, 60, 70, 80, 90, 100]:
    if splitnum <= -1:
      fracofrun.append(-1./float(splitnum))
    else:
      fracofrun.append(float(splitnum))

    theratio, theerror = whatever(splitnum, selfunc)
    thewmean = jt.wmean(zip(theratio, theerror))[0]
    width = jt.stdev(map(lambda (rat, err): (rat-thewmean)/err, zip(theratio, theerror))) * sqrt(float(len(theratio))/float(len(theratio)+1))
    allthewidths.append(width)
    alltheerrors.append(width/sqrt(2.*len(theratio)))

  p = biggles.FramedPlot()
  p.add(biggles.Points(fracofrun, allthewidths, symboltype="filled circle", symbolsize=1))
  p.add(biggles.SymmetricErrorBarsY(fracofrun, allthewidths, alltheerrors))
  p.x1.log = 1
  p.x1.range = 0.005, 200.
  p.y1.range = 0., 2.
  p.title = title
  p.x1.label = "Segmentation size (fraction of a run)"
  p.y1.label = "Stdev of pull distribution of #hadrons/#bhabhas"
  p.show()
  p.write_eps(name+".eps")
  return p

makeaplot(lambda r: runsummary[r].res == 1 and runsummary[r].kind == "p" and 123359 < r < 123563, "Jan 24 - Jan 28 2002 peak data", "nail_jan23")
makeaplot(lambda r: runsummary[r].res == 1 and runsummary[r].kind == "p" and 123563 < r < 123766, "Jan 31 - Feb 4 2002 peak data", "nail_jan30")
makeaplot(lambda r: runsummary[r].res == 1 and runsummary[r].kind == "p" and 123783 < r < 123928, "Feb 7 - Feb 11 2002 peak data", "nail_feb07")
makeaplot(lambda r: runsummary[r].res == 1 and runsummary[r].kind == "c" and 123783 < r < 123928, "Feb 7 - Feb 11 2002 continuum data", "nail_feb07c")
makeaplot(lambda r: runsummary[r].res == 1 and runsummary[r].kind == "p" and 124607 < r < 124764, "Mar 14 - Mar 18 2002 peak data", "nail_mar14")
makeaplot(lambda r: runsummary[r].res == 1 and runsummary[r].kind == "c" and 124607 < r < 124764, "Mar 14 - Mar 18 2002 continuum data", "nail_mar14c")
makeaplot(lambda r: runsummary[r].res == 1 and runsummary[r].kind == "p" and 125308 < r < 125433, "Apr 11 - Apr 15 2002 peak data", "nail_apr11")

p = makeaplot(lambda r: runsummary[r].res == 1 and runsummary[r].kind == "p" and abs(runsummary[r].energy - 4.73019) < 0.0001, "All U(1S) peak data within 0.1 MeV (really 0.5)", "nail_all")
p.title = "All U(1S) peak data within 0.2 MeV (really 0.5 MeV)"
p.y1.range = 0, 3
p.show()
p.write_eps("nail_all.eps")

p = makeaplot(lambda r: runsummary[r].res == 2 and runsummary[r].kind == "c", "All U(2S) continuum data", "nail_all2s_c")
p.show()

p = makeaplot(lambda r: runsummary[r].res == 2 and runsummary[r].kind == "p", "All U(2S) peak data", "nail_all2s")
p.y1.range = 0, 5
p.show()
p.write_eps("nail_all2s.eps")

######################################################

theratio, theerror = whatever(10, lambda r: runsummary[r].res == 1 and runsummary[r].kind == "p" and abs(runsummary[r].energy - 4.73019) < 0.0001)
p = biggles.FramedPlot()
p.add(biggles.Points(range(len(theratio)), theratio, symboltype="filled circle", symbolsize=0.8))
p.add(biggles.SymmetricErrorBarsY(range(len(theratio)), theratio, theerror))
p.title = "All U(1S) peak data within 0.2 MeV (really 0.5 MeV)"
p.y1.label = "#hadrons/#bhabhas"
p.x1.label = "10-run index (segmentation size=10)"
p.show()
p.write_eps("nail_all_10.eps")

theratio, theerror = whatever(10, lambda r: runsummary[r].res == 2 and runsummary[r].kind == "p")
p = biggles.FramedPlot()
p.add(biggles.Points(range(len(theratio)), theratio, symboltype="filled circle", symbolsize=0.8))
p.add(biggles.SymmetricErrorBarsY(range(len(theratio)), theratio, theerror))
p.title = "All U(2S) peak data"
p.y1.label = "#hadrons/#bhabhas"
p.x1.label = "10-run index (segmentation size=10)"
p.show()
p.write_eps("nail_all2s_10.eps")

theratio, theerror = whatever(1, lambda r: runsummary[r].res == 1 and runsummary[r].kind == "p" and 123563 < r < 123766)
p = biggles.FramedPlot()
p.add(biggles.Points(range(len(theratio)), theratio, symboltype="filled circle", symbolsize=0.8))
p.add(biggles.SymmetricErrorBarsY(range(len(theratio)), theratio, theerror))
p.title = "Jan 31 - Feb 4"
p.y1.label = "#hadrons/#bhabhas"
p.x1.label = "run index (segmentation size=1)"
p.show()
p.write_eps("nail_jan31_1.eps")

##########################################################

def makeanotherplot(selfunc, title, name):
  fracofrun = []
  allredchi2 = []
  for splitnum in [-100, -50, -25, -10, -5, -2, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 20, 30, 40, 50, 60, 70, 80, 90, 100]:
    if splitnum <= -1:
      fracofrun.append(-1./float(splitnum))
    else:
      fracofrun.append(float(splitnum))

    theratio, theerror = whatever(splitnum, selfunc)
    if len(theratio) > 2:
      thewmean = jt.wmean(zip(theratio, theerror))[0]
      thechi2 = sum(map(lambda (rat, err): (rat-thewmean)**2/err**2, zip(theratio, theerror)))
      thendof = len(theratio)-1
      if thendof > 0:
        allredchi2.append(thechi2/thendof)
      else:
        allredchi2.append(-1)
    else:
      allredchi2.append(-1)

  p = biggles.FramedPlot()
  p.add(biggles.Points(fracofrun, allredchi2, symboltype="filled circle", symbolsize=1))

  p.x1.log = 1
  p.x1.range = 0.005, 200.
  p.y1.range = 0., 2.
  p.title = title
  p.x1.label = "Segmentation size (fraction of a run)"
  p.y1.label = "reduced chi2 of #hadrons/#bhabhas to wmean"
  p.show()
  p.write_eps(name+".eps")
  return p

makeanotherplot(lambda r: runsummary[r].res == 1 and runsummary[r].kind == "p" and 123359 < r < 123563, "Jan 24 - Jan 28 2002 peak data", "nailnother_jan23")
makeanotherplot(lambda r: runsummary[r].res == 1 and runsummary[r].kind == "p" and 123563 < r < 123766, "Jan 31 - Feb 4 2002 peak data", "nailnother_jan30")
makeanotherplot(lambda r: runsummary[r].res == 1 and runsummary[r].kind == "p" and 123783 < r < 123928, "Feb 7 - Feb 11 2002 peak data", "nailnother_feb07")
makeanotherplot(lambda r: runsummary[r].res == 1 and runsummary[r].kind == "c" and 123783 < r < 123928, "Feb 7 - Feb 11 2002 continuum data", "nailnother_feb07c")
makeanotherplot(lambda r: runsummary[r].res == 1 and runsummary[r].kind == "p" and 124607 < r < 124764, "Mar 14 - Mar 18 2002 peak data", "nailnother_mar14")
makeanotherplot(lambda r: runsummary[r].res == 1 and runsummary[r].kind == "c" and 124607 < r < 124764, "Mar 14 - Mar 18 2002 continuum data", "nailnother_mar14c")
makeanotherplot(lambda r: runsummary[r].res == 1 and runsummary[r].kind == "p" and 125308 < r < 125433, "Apr 11 - Apr 15 2002 peak data", "nailnother_apr11")

p = makeanotherplot(lambda r: runsummary[r].res == 1 and runsummary[r].kind == "p" and abs(runsummary[r].energy - 4.73019) < 0.0001, "All U(1S) peak data within 0.1 MeV (really 0.5)", "nailnother_all")

theratio, theerror = whatever(10, lambda r: runsummary[r].res == 1 and runsummary[r].kind == "c" and 124607 < r < 124764)
p = biggles.FramedPlot()
p.add(biggles.Points(range(len(theratio)), theratio, symboltype="filled circle", symbolsize=0.8))
p.add(biggles.SymmetricErrorBarsY(range(len(theratio)), theratio, theerror))
p.title = "Mar 14 - Mar 18 2002 continuum data"
p.y1.label = "#hadrons/#bhabhas"
p.x1.label = "run index (segmentation size=1)"
p.show()
p.write_eps("nailnother_mar14c_1.eps")







#######################################################

hadsbypercent = hist.h1(10, 0, 1)
bhasbypercent = hist.h1(10, 0, 1)

for r in initialrunlist:
  if runsummary[r].res == 1 and runsummary[r].kind == "p" and 123563 < r < 123766 and r not in mybadruns:
    therun = getdber(r)

    h = therun.hadroncool_vstime
    e = therun.beamgase_vstime
    p = therun.beamgasp_vstime
    c = therun.cosmic_vstime
    b = therun.bhabha_vstime

    ebkgnd = e * (ebeam.hadroncool - nobeam.hadroncool*ebeam.cosmic/nobeam.cosmic) / ebeam.beamgase
    pbkgnd = p * (pbeam.hadroncool - nobeam.hadroncool*pbeam.cosmic/nobeam.cosmic) / pbeam.beamgasp
    cbkgnd = c * nobeam.hadroncool / nobeam.cosmic
    hadrons = h - ebkgnd/2. - pbkgnd/2. - cbkgnd

    for i in range(10):
      for j in range(10):
        hadsbypercent.vals[i] += hadrons[10*i+j]
        bhasbypercent.vals[i] += b[10*i+j]

hadsbypercent.rootn()
bhasbypercent.rootn()

p = (hadsbypercent / bhasbypercent).plot(False, points=True, errorbars=True)
p.y1.range = 1.8, 2.
p.show()

