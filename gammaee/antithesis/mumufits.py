# This `fits' has been updated to have the 9 Nov efficiencies and
# luminosities.  It also has full bhabhafits capabilities, and the
# post-CESR study variable beam energy spread parameters.

# get_runs has been given a thorough look-over: it is correct (7 Oct
# 2005) (get_runs contains all corrections, from numbers of events to
# real, live cross-section.)

import sys
sys.path.append("/home/mccann/bin/python/obsolete")

from minuit import *
execfile("/home/mccann/antithesis/utilities.py")
nobeam = getsb("cos")
import gbwkf
import gbwkftau
runstart = pickle.load(open("/home/mccann/antithesis/old_dotps/runstart.p"))
runend = pickle.load(open("/home/mccann/antithesis/old_dotps/runend.p"))
import time
bsbha = pickle.load(open("/home/mccann/synthesis/run/bsbha.p"))

nbish2nb = 23.0481
# bhabha_interference = 1.   # this is a multiplier: 0. to turn off

class FitRecord: pass
ggfits = pickle.load(open("/home/mccann/antithesis/fit_results/novemberfits_noapr03_3_1.0.p"))

# I learned this from Matt and the beam energy program logs
runsummary[123828].energy = 4.72992
runsummary[123832].energy = 4.72990

def doitall(lumisource, bhabha_interference):
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

  def setup_data(runs, lumisource=0, u1area=None, u2area=None):
    tmpdata = []
    for r in runs:
      tmpdata.append(get_runs([r], lumisource=lumisource, u1area=u1area, u2area=u2area))
    return tmpdata

  def mygbwkf(mass, fullgam, rmsbeam, yint, phi, w):
    "yint = 0.018, 0.018, 0.018; phi=0"
    if w > mass + 200.:
      return 0.076/(w-mass)
    return gbwkf.gbwkf(mass, fullgam, rmsbeam, yint, phi, w-mass)

  def mygbwkftau(mass, fullgam, rmsbeam, yint, phi, w):
    "yint = 0.20, 0.37, 0.27; phi = 0"
    if w > mass + 200.:
      return 0.076/(w-mass)
    return gbwkftau.gbwkf(mass, fullgam, rmsbeam, yint, phi, w-mass)

  def adddata(p, data, shift):
    x = []
    y = []
    yerr = []
    for (e, h, herr) in data:
      x.append(e*2000.+shift)
      y.append(h)
      yerr.append(herr)
    p.add(biggles.Points(x, y, symboltype="filled circle", symbolsize=0.8))
    p.add(biggles.SymmetricErrorBarsY(x, y, yerr))
  #  if len(x) == 1:
  #    p.add(biggles.Points(x, y, symboltype="circle", symbolsize=7.))
    return None

  def adddata_pull(p, data, shift, f):
    x = []
    y = []
    for (e, h, herr) in data:
      x.append(e*2000.+shift)
      y.append((h - f(e*2000.+shift))/herr)
    p.add(biggles.Points(x, y, symboltype="filled circle", symbolsize=0.8))
    return y

  def adddata_pull2(p, runs, data, shift, f):
    x = []
    y = []
    for (r, (e, h, herr)) in zip(runs, data):
      x.append(r)
      y.append((h - f(e*2000.+shift))/herr)
    p.add(biggles.Points(x, y, symboltype="filled circle", symbolsize=0.8))
    return y

  def adddata_pull3(p, runs, data, shift, f):
    x = []
    y = []
    for (r, (e, h, herr)) in zip(runs, data):
      d = 0
      if r in runstart and r in runend:
        d = (runstart[r] + runend[r])/2.
      elif r in runstart:
        d = runstart[r]
      elif r in runend:
        d = runend[r]
      else:
        raise Exception
      x.append(d)
      y.append((h - f(e*2000.+shift))/herr)
    p.add(biggles.Points(x, y, symboltype="filled circle", symbolsize=0.8))
    return x

  def addfunc(p, f, low, high, points=100., linetype="solid", linewidth=1.):
    x = Numeric.arange(low, high+(high-low)/points, (high-low)/points)
    y = Numeric.arange(low, high+(high-low)/points, (high-low)/points)
    for i, xi in enumerate(x):
      y[i] = f(xi)
    tmp = biggles.Curve(x, y, linetype=linetype, linewidth=linewidth)
    p.add(tmp)
    return tmp

  def u1func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, w):
    tmp = 0.
    tmp += area * mygbwkftau(9460.30, fullgam, rmsbeam, tauyint, tauphi, w)
    tmp += back * 9000.**2 / w**2
    return tmp

  def u2func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, w):
    tmp = 0.
    tmp += area * mygbwkftau(10023.26, fullgam, rmsbeam, tauyint, tauphi, w)
    tmp += back * 9000.**2 / w**2
    return tmp

  def u3func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area, w):
    tmp = 0.
    tmp += area * mygbwkftau(10355.2, fullgam, rmsbeam, tauyint, tauphi, w)
    tmp += back * 9000.**2 / w**2
    return tmp

  def u1func_bkgndonly(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, w):
    tmp = 0.
    tmp += back * 9000.**2 / w**2
    return tmp

  def u2func_bkgndonly(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, w):
    tmp = 0.
    tmp += back * 9000.**2 / w**2
    return tmp

  def u3func_bkgndonly(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area, w):
    tmp = 0.
    tmp += back * 9000.**2 / w**2
    return tmp

  def whichamiin(r):
    if runsummary[r].res == 1:
      for s in ["jan16", "jan30", "feb06", "feb13", "feb20", "feb27", "mar06", "mar13", "apr08", "apr09", "apr10"]:
        if r in u1runs[s]:
          return 1, s

    elif runsummary[r].res == 2:
      for s in ["may29", "jun11", "jun12", "jul10", "jul24", "aug07"]:
        if r in u2runs[s]:
          return 2, s

    elif runsummary[r].res == 3:
      for s in ["nov28", "dec05", "dec12", "dec19", "dec26", "jan02", "jan09"]:
        if r in u3runs[s]:
          return 3, s

    return runsummary[r].res, None

  def get_runs(runs, lumisource=0, u1area=None, u2area=None):
    g = 0.
    h = 0.
    c = 0.
    wsum = 0.
    wesum = 0.
    for r in runs:
      therun = getdb(r)
      ngg = therun.gamgam
      if r in mycarefulscan: ngg = therun.gamgam_vstime.sum(0.,0.99)
      wsum += float(ngg)
      wesum += float(ngg) * runsummary[r].energy

      if runsummary[r].res == 1:
        myarea, myrmsbeam, myback, myjan16, myjan30, myfeb06, myfeb13, myfeb20, myfeb27, mymar06, mymar13, myapr08, myapr09, myapr10, myfullgam, myyint, myphi, mybtautau, mytauyint, mytauphi, mytwophofrac, myrjan, myrfeb, myrapr2 = ggfits[1].values
      elif runsummary[r].res == 2:
        myarea, myrmsbeam, myback, mymay29, myjun11, myjun12, myjul10, myjul24, myaug07, myfullgam, myyint, myphi, mybtautau, mytauyint, mytauphi, mytwophofrac, myu1area = ggfits[2].values
      elif runsummary[r].res == 3:
        myarea, myrmsbeam, myback, mynov28, mydec05, mydec12, mydec19, mydec26, myjan02, myjan09, myfullgam, myyint, myphi, mybtautau, mytauyint, mytauphi, mytwophofrac, myu1area, myu2area, myrnov28, myrdec05, myrdec12, myrdec19, myrdec26, myrjan02, myrjan09 = ggfits[3].values

      whichres, whichweek = whichamiin(r)

      thisrmsbeam = myrmsbeam
      if whichres == 1:
        if whichweek != None:
          if whichweek in ["jan16", "jan30", "feb06", "feb13", "feb20"]: thisrmsbeam = myrjan
          if whichweek in ["feb27", "mar06", "mar13"]: thisrmsbeam = myrfeb
          if whichweek in ["apr08", "apr09", "apr10"]: thisrmsbeam = myrapr2
      if whichres == 3:
        if whichweek != None:
          thisrmsbeam = eval("myr"+whichweek)

      thisshift = 0.
      if whichweek != None:
        thisshift = 0. - eval("my"+whichweek)

      if r in mycarefulscan:
        h += therun.mupair_vstime.sum(0.,0.99)
        c += therun.cosmic_vstime.sum(0.,0.99)

        if lumisource == 0:
          g += therun.gamgam_vstime.sum(0.,0.99)
        elif lumisource == 1:
          g += therun.bhabha_cosp.sum(0., 0.6) * therun.bhabha_vstime.sum(0.,0.99) / therun.bhabha

          if runsummary[r].kind != 'c':
            # eecs = e+e- cross-section = hadronic area / (1 - 3 Bmm) * Bmm * inner range
            if runsummary[r].res == 1:
              eecs = myarea * mygbwkf(9460.30+thisshift, myfullgam, thisrmsbeam, 0.417*bhabha_interference, 0., 2000.*runsummary[r].energy) / 0.9253 * 0.0249 * 0.672/2.66667
              g -= eecs * float(therun.gamgam) * runsummary[r].energy**2 / nbish2nb

            if runsummary[r].res == 2:
              eecs = myarea * mygbwkf(10023.26+thisshift, myfullgam, thisrmsbeam, 0.613*bhabha_interference, 0., 2000.*runsummary[r].energy) / 0.9391 * 0.0203 * 0.672/2.6667
              g -= eecs * float(therun.gamgam) * runsummary[r].energy**2 / nbish2nb

            if runsummary[r].res == 3:
              eecs = myarea * mygbwkf(10355.2+thisshift, myfullgam, thisrmsbeam, 0.486*bhabha_interference, 0., 2000.*runsummary[r].energy) / 0.9283 * 0.0239 * 0.672/2.6667
              g -= eecs * float(therun.gamgam) * runsummary[r].energy**2 / nbish2nb

        elif lumisource == 2:
          g += therun.bhabha_cosp.sum(0.6, 0.8) * therun.bhabha_vstime.sum(0.,0.99) / therun.bhabha

          if runsummary[r].kind != 'c':
            # eecs = e+e- cross-section = hadronic area / (1 - 3 Bmm) * Bmm * outer range
            if runsummary[r].res == 1:
              eecs = myarea * mygbwkf(9460.30+thisshift, myfullgam, thisrmsbeam, 0.588*bhabha_interference, 0., 2000.*runsummary[r].energy) / 0.9253 * 0.0249 * 0.298667/2.66667
              g -= eecs * float(therun.gamgam) * runsummary[r].energy**2 / nbish2nb

            if runsummary[r].res == 2:
              eecs = myarea * mygbwkf(10023.26+thisshift, myfullgam, thisrmsbeam, 0.864*bhabha_interference, 0., 2000.*runsummary[r].energy) / 0.9391 * 0.0203 * 0.298667/2.6667
              g -= eecs * float(therun.gamgam) * runsummary[r].energy**2 / nbish2nb

            if runsummary[r].res == 3:
              eecs = myarea * mygbwkf(10355.2+thisshift, myfullgam, thisrmsbeam, 0.686*bhabha_interference, 0., 2000.*runsummary[r].energy) / 0.9283 * 0.0239 * 0.298667/2.6667
              g -= eecs * float(therun.gamgam) * runsummary[r].energy**2 / nbish2nb

        elif lumisource == 3:
          g += 1.*bsbha[r] * therun.bhabha_vstime.sum(0.,0.99) / therun.bhabha

          if runsummary[r].kind != 'c':
            # eecs = e+e- cross-section = hadronic area / (1 - 3 Bmm) * Bmm * whole range
            if runsummary[r].res == 1:
              eecs = myarea * mygbwkf(9460.30+thisshift, myfullgam, thisrmsbeam, 0.597*bhabha_interference, 0., 2000.*runsummary[r].energy) / 0.9253 * 0.0249 * 1.73933/2.66667
              g -= eecs * float(therun.gamgam) * runsummary[r].energy**2 / nbish2nb

            if runsummary[r].res == 2:
              eecs = myarea * mygbwkf(10023.26+thisshift, myfullgam, thisrmsbeam, 0.873*bhabha_interference, 0., 2000.*runsummary[r].energy) / 0.9391 * 0.0203 * 1.73933/2.6667
              g -= eecs * float(therun.gamgam) * runsummary[r].energy**2 / nbish2nb

            if runsummary[r].res == 3:
              eecs = myarea * mygbwkf(10355.2+thisshift, myfullgam, thisrmsbeam, 0.691*bhabha_interference, 0., 2000.*runsummary[r].energy) / 0.9283 * 0.0239 * 1.73933/2.6667
              g -= eecs * float(therun.gamgam) * runsummary[r].energy**2 / nbish2nb

      else:
        h += therun.mupair
        c += therun.cosmic

        if lumisource == 0:
          g += therun.gamgam

        elif lumisource == 1:
          g += therun.bhabha_cosp.sum(0., 0.6)

          if runsummary[r].kind != 'c':
            # e+e- cross-section = hadronic area / (1 - 3 Bmm) * Bmm * inner range
            if runsummary[r].res == 1:
              eecs = myarea * mygbwkf(9460.30+thisshift, myfullgam, thisrmsbeam, 0.417*bhabha_interference, 0., 2000.*runsummary[r].energy) / 0.9253 * 0.0249 * 0.672/2.66667
              g -= eecs * float(therun.gamgam) * runsummary[r].energy**2 / nbish2nb

            if runsummary[r].res == 2:
              eecs = myarea * mygbwkf(10023.26+thisshift, myfullgam, thisrmsbeam, 0.613*bhabha_interference, 0., 2000.*runsummary[r].energy) / 0.9391 * 0.0203 * 0.672/2.6667
              g -= eecs * float(therun.gamgam) * runsummary[r].energy**2 / nbish2nb

            if runsummary[r].res == 3:
              eecs = myarea * mygbwkf(10355.2+thisshift, myfullgam, thisrmsbeam, 0.486*bhabha_interference, 0., 2000.*runsummary[r].energy) / 0.9283 * 0.0239 * 0.672/2.6667
              g -= eecs * float(therun.gamgam) * runsummary[r].energy**2 / nbish2nb

        elif lumisource == 2:
          g += therun.bhabha_cosp.sum(0.6, 0.8)

          if runsummary[r].kind != 'c':
            # e+e- cross-section = hadronic area / (1 - 3 Bmm) * Bmm * outer range
            if runsummary[r].res == 1:
              eecs = myarea * mygbwkf(9460.30+thisshift, myfullgam, thisrmsbeam, 0.588*bhabha_interference, 0., 2000.*runsummary[r].energy) / 0.9253 * 0.0249 * 0.298667/2.66667
              g -= eecs * float(therun.gamgam) * runsummary[r].energy**2 / nbish2nb

            if runsummary[r].res == 2:
              eecs = myarea * mygbwkf(10023.26+thisshift, myfullgam, thisrmsbeam, 0.864*bhabha_interference, 0., 2000.*runsummary[r].energy) / 0.9391 * 0.0203 * 0.298667/2.6667
              g -= eecs * float(therun.gamgam) * runsummary[r].energy**2 / nbish2nb

            if runsummary[r].res == 3:
              eecs = myarea * mygbwkf(10355.2+thisshift, myfullgam, thisrmsbeam, 0.686*bhabha_interference, 0., 2000.*runsummary[r].energy) / 0.9283 * 0.0239 * 0.298667/2.6667
              g -= eecs * float(therun.gamgam) * runsummary[r].energy**2 / nbish2nb

        elif lumisource == 3:
          g += 1.*bsbha[r]

          if runsummary[r].kind != 'c':
            # e+e- cross-section = hadronic area / (1 - 3 Bmm) * Bmm * whole range
            if runsummary[r].res == 1:
              eecs = myarea * mygbwkf(9460.30+thisshift, myfullgam, thisrmsbeam, 0.597*bhabha_interference, 0., 2000.*runsummary[r].energy) / 0.9253 * 0.0249 * 1.73933/2.66667
              g -= eecs * float(therun.gamgam) * runsummary[r].energy**2 / nbish2nb

            if runsummary[r].res == 2:
              eecs = myarea * mygbwkf(10023.26+thisshift, myfullgam, thisrmsbeam, 0.873*bhabha_interference, 0., 2000.*runsummary[r].energy) / 0.9391 * 0.0203 * 1.73933/2.6667
              g -= eecs * float(therun.gamgam) * runsummary[r].energy**2 / nbish2nb

            if runsummary[r].res == 3:
              eecs = myarea * mygbwkf(10355.2+thisshift, myfullgam, thisrmsbeam, 0.691*bhabha_interference, 0., 2000.*runsummary[r].energy) / 0.9283 * 0.0239 * 1.73933/2.6667
              g -= eecs * float(therun.gamgam) * runsummary[r].energy**2 / nbish2nb

    average_energy = wesum / wsum

    cbkgnd = 1. * nobeam.mupair * c / nobeam.cosmic

    hadrons = h - cbkgnd
    hadrons_err = sqrt(h + c * (1.*nobeam.mupair/nobeam.cosmic)**2)

    if lumisource == 3:
      if whichres == 1:
        cs = hadrons / g / average_energy**2 * 199.5   # these differences are due to different efficiencies, as predicted by the MC
      elif whichres == 2:
        cs = hadrons / g / average_energy**2 * 197.4   # and verified by my lumi counts
      elif whichres == 3:
        cs = hadrons / g / average_energy**2 * 196.0   # (I totally believe this.)
        
      cs_err = cs * sqrt((1.*hadrons_err / hadrons)**2 + 1./g)

    else:
      cs = hadrons / g / average_energy**2 * nbish2nb
      cs_err = cs * sqrt((1.*hadrons_err / hadrons)**2 + 1./g)

      if lumisource == 1:
        cs /= 0.23684
        cs_err /= 0.23684

      if lumisource == 2:
        cs /= 0.118999
        cs_err /= 0.118999

    if whichres == 1:
      cs /= 0.5499605367008682
      cs_err /= 0.5499605367008682
    elif whichres == 2:
      cs -= u1area * mygbwkf(9460.30, 0., 0., 0., 0., average_energy*2000.)
      cs /= 0.55475703830685041
      cs_err /= 0.55475703830685041
    elif whichres == 3:
      cs -= u1area * mygbwkf(9460.30, 0., 0., 0., 0., average_energy*2000.)
      cs -= u2area * mygbwkf(10023.26, 0., 0., 0., 0., average_energy*2000.)
      cs /= 0.5224697398918362
      cs_err /= 0.5224697398918362

    return average_energy, cs, cs_err

  def get_lumiweight(runs):
    lumiweight = 0.
    for r in runs:
      lumiweight += getdb(r).gamgam
    return lumiweight

  def u1plot(area, rmsbeam, back, jan16, jan30, feb06, feb13, feb20, feb27, mar06, mar13, apr08, apr09, apr10, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, rjan, rfeb, rapr2):
    p = biggles.FramedPlot()
    adddata(p, u1data["cont"], 0.)
    adddata(p, u1data["high"], 0.)
    adddata(p, u1data["jan16"], jan16)
    adddata(p, u1data["jan30"], jan30)
    adddata(p, u1data["feb06"], feb06)
    adddata(p, u1data["feb13"], feb13)
    adddata(p, u1data["feb20"], feb20)
    adddata(p, u1data["feb27"], feb27)
    adddata(p, u1data["mar06"], mar06)
    adddata(p, u1data["mar13"], mar13)
    adddata(p, u1data["apr08"], apr08)
    adddata(p, u1data["apr09"], apr09)
    adddata(p, u1data["apr10"], apr10)
    addfunc(p, lambda w: u1func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, w), 9420., 9580.)
    p.x1.range = 9420., 9580.
    p.y1.range = 0., 2.
    p.aspect_ratio = 1.2
    return p

  def u2plot(area, rmsbeam, back, may29, jun11, jun12, jul10, jul24, aug07, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area):
    p = biggles.FramedPlot()
    adddata(p, u2data["cont"], 0.)
    adddata(p, u2data["high"], 0.)
    adddata(p, u2data["may29"], may29)
    adddata(p, u2data["jun11"], jun11)
    adddata(p, u2data["jun12"], jun12)
    adddata(p, u2data["jul10"], jul10)
    adddata(p, u2data["jul24"], jul24)
    adddata(p, u2data["aug07"], aug07)
    addfunc(p, lambda w: u2func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, w), 9980., 10100.)
    p.x1.range = 9980., 10100.
    p.y1.range = 0., 2.
    p.aspect_ratio = 1.2
    return p

  def u3plot(area, rmsbeam, back, nov28, dec05, dec12, dec19, dec26, jan02, jan09, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area, rnov28, rdec05, rdec12, rdec19, rdec26, rjan02, rjan09):
    p = biggles.FramedPlot()
    adddata(p, u3data["cont"], 0.)
    adddata(p, u3data["high"], 0.)
    adddata(p, u3data["nov28"], nov28)
    adddata(p, u3data["dec05"], dec05)
    adddata(p, u3data["dec12"], dec12)
    adddata(p, u3data["dec19"], dec19)
    adddata(p, u3data["dec26"], dec26)
    adddata(p, u3data["jan02"], jan02)
    adddata(p, u3data["jan09"], jan09)
    addfunc(p, lambda w: u3func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area, w), 10320., 10420.)
    p.x1.range = 10320., 10420.
    p.y1.range = 0., 2.
    p.aspect_ratio = 1.2
    return p

  def chicontrib(data, shift, f):
    chi = 0.
    for en, cs, cserr in data:
      chi += (f(en*2000. + shift) - cs)**2 / cserr**2
    return chi

  def u1fit(area, rmsbeam, back, jan16, jan30, feb06, feb13, feb20, feb27, mar06, mar13, apr08, apr09, apr10, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, rjan, rfeb, rapr2):
    chi = 0.
    chi += chicontrib(u1data["cont"], 0., lambda w: u1func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, w))
    chi += chicontrib(u1data["high"], 0., lambda w: u1func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, w))
    chi += chicontrib(u1data["jan16"], jan16, lambda w: u1func(area, rjan, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, w))
    chi += chicontrib(u1data["jan30"], jan30, lambda w: u1func(area, rjan, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, w))
    chi += chicontrib(u1data["feb06"], feb06, lambda w: u1func(area, rjan, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, w))
    chi += chicontrib(u1data["feb13"], feb13, lambda w: u1func(area, rjan, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, w))
    chi += chicontrib(u1data["feb20"], feb20, lambda w: u1func(area, rjan, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, w))
    chi += chicontrib(u1data["feb27"], feb27, lambda w: u1func(area, rfeb, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, w))
    chi += chicontrib(u1data["mar06"], mar06, lambda w: u1func(area, rfeb, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, w))
    chi += chicontrib(u1data["mar13"], mar13, lambda w: u1func(area, rfeb, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, w))
    chi += chicontrib(u1data["apr08"], apr08, lambda w: u1func(area, rapr2, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, w))
    chi += chicontrib(u1data["apr09"], apr09, lambda w: u1func(area, rapr2, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, w))
    chi += chicontrib(u1data["apr10"], apr10, lambda w: u1func(area, rapr2, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, w))
    return chi

  def u2fit(area, rmsbeam, back, may29, jun11, jun12, jul10, jul24, aug07, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area):
    chi = 0.
    chi += chicontrib(u2data["cont"], 0., lambda w: u2func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, w))
    chi += chicontrib(u2data["high"], 0., lambda w: u2func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, w))
    chi += chicontrib(u2data["may29"], may29, lambda w: u2func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, w))
    chi += chicontrib(u2data["jun11"], jun11, lambda w: u2func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, w))
    chi += chicontrib(u2data["jun12"], jun12, lambda w: u2func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, w))
    chi += chicontrib(u2data["jul10"], jul10, lambda w: u2func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, w))
    chi += chicontrib(u2data["jul24"], jul24, lambda w: u2func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, w))
    chi += chicontrib(u2data["aug07"], aug07, lambda w: u2func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, w))
    return chi

  def u3fit(area, rmsbeam, back, nov28, dec05, dec12, dec19, dec26, jan02, jan09, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area, rnov28, rdec05, rdec12, rdec19, rdec26, rjan02, rjan09):
    chi = 0.
    chi += chicontrib(u3data["cont"], 0., lambda w: u3func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area, w))
    chi += chicontrib(u3data["high"], 0., lambda w: u3func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area, w))
    chi += chicontrib(u3data["nov28"], nov28, lambda w: u3func(area, rnov28, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area, w))
    chi += chicontrib(u3data["dec05"], dec05, lambda w: u3func(area, rdec05, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area, w))
    chi += chicontrib(u3data["dec12"], dec12, lambda w: u3func(area, rdec12, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area, w))
    chi += chicontrib(u3data["dec19"], dec19, lambda w: u3func(area, rdec19, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area, w))
    chi += chicontrib(u3data["dec26"], dec26, lambda w: u3func(area, rdec26, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area, w))
    chi += chicontrib(u3data["jan02"], jan02, lambda w: u3func(area, rjan02, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area, w))
    chi += chicontrib(u3data["jan09"], jan09, lambda w: u3func(area, rjan09, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area, w))
    return chi

  class MoreThanHist:
    def __init__(self, bins, low, high):
      self.h = hist.h1(bins, low, high)
      self.data = []
    def fill(self, l):
      for x in l:
        self.data.append(x)
        self.h.fill(x)
    def rootn(self):
      self.h.rootn()
    def plot(self):
      return self.h.plot()
    def sum(self):
      return self.h.sum()
    def overflow(self):
      return self.h.overflow
    def underflow(self):
      return self.h.underflow
    def steps(self, linewidth=3.):
      return self.h.steps(linewidth=linewidth)

  extraarea = 1.

  def dofitgauss(h):
    def gauss(m, s, x): return exp(-(x-m)**2/2./s**2)/sqrt(2.*pi)/s
    def fitgauss(m,s):
      c = 0.
      for x in h.data:
        c += -log(gauss(m, s, x))
      return c
    m = Minuit(fitgauss, start=[0., 1.], up=0.5)
    m.migrad()
    m.minos([0,1])
    err0 = (m.minos_errors[0][1] - m.minos_errors[0][0])/2.
    err1 = (m.minos_errors[1][1] - m.minos_errors[1][0])/2.
    return m.values[0], err0, m.values[1], err1, lambda x: 0.1*extraarea*len(h.data)*gauss(m.values[0], m.values[1], x)

  def adddata_pull(p, data, shift, f):
    x = []
    y = []
    for (e, h, herr) in data:
      x.append(e*2000.+shift)
      y.append((h - f(e*2000.+shift))/herr)
    p.add(biggles.Points(x, y, symboltype="filled circle", symbolsize=1.1))
    return y

  def adddata_pull3(p, runs, data, shift, f):
    x = []
    y = []
    for (r, (e, h, herr)) in zip(runs, data):
      d = 0
      if r in runstart and r in runend:
        d = (runstart[r] + runend[r])/2.
      elif r in runstart:
        d = runstart[r]
      elif r in runend:
        d = runend[r]
      else:
        raise Exception
      x.append(d)
      y.append((h - f(e*2000.+shift))/herr)
    p.add(biggles.Points(x, y, symboltype="filled circle", symbolsize=1.1))
    return x

  def u1plot_pull(area, rmsbeam, back, jan16, jan30, feb06, feb13, feb20, feb27, mar06, mar13, apr08, apr09, apr10, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, rjan, rfeb, rapr2):
    p = biggles.Table(1,3)
    p[0,0] = biggles.FramedPlot()
    p[0,2] = biggles.FramedPlot()
    h = MoreThanHist(25, -5., 5.)
    h.fill(adddata_pull(p[0,0], u1data["cont"], 0., lambda w: u1func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, w)))
    h.fill(adddata_pull(p[0,0], u1data["high"], 0., lambda w: u1func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, w)))
    h.fill(adddata_pull(p[0,0], u1data["jan16"], jan16, lambda w: u1func(area, rjan, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, w)))
    h.fill(adddata_pull(p[0,0], u1data["jan30"], jan30, lambda w: u1func(area, rjan, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, w)))
    h.fill(adddata_pull(p[0,0], u1data["feb06"], feb06, lambda w: u1func(area, rjan, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, w)))
    h.fill(adddata_pull(p[0,0], u1data["feb13"], feb13, lambda w: u1func(area, rjan, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, w)))
    h.fill(adddata_pull(p[0,0], u1data["feb20"], feb20, lambda w: u1func(area, rjan, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, w)))
    h.fill(adddata_pull(p[0,0], u1data["feb27"], feb27, lambda w: u1func(area, rfeb, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, w)))
    h.fill(adddata_pull(p[0,0], u1data["mar06"], mar06, lambda w: u1func(area, rfeb, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, w)))
    h.fill(adddata_pull(p[0,0], u1data["mar13"], mar13, lambda w: u1func(area, rfeb, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, w)))
    h.fill(adddata_pull(p[0,0], u1data["apr08"], apr08, lambda w: u1func(area, rapr2, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, w)))
    h.fill(adddata_pull(p[0,0], u1data["apr09"], apr09, lambda w: u1func(area, rapr2, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, w)))
    h.fill(adddata_pull(p[0,0], u1data["apr10"], apr10, lambda w: u1func(area, rapr2, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, w)))
    dates = []
    dates += adddata_pull3(p[0,2], u1runs["jan16"], u1data["jan16"], jan16, lambda w: u1func(area, rjan, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, w))
    dates += adddata_pull3(p[0,2], u1runs["jan30"], u1data["jan30"], jan30, lambda w: u1func(area, rjan, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, w))
    dates += adddata_pull3(p[0,2], u1runs["feb06"], u1data["feb06"], feb06, lambda w: u1func(area, rjan, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, w))
    dates += adddata_pull3(p[0,2], u1runs["feb13"], u1data["feb13"], feb13, lambda w: u1func(area, rjan, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, w))
    dates += adddata_pull3(p[0,2], u1runs["feb20"], u1data["feb20"], feb20, lambda w: u1func(area, rjan, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, w))
    dates += adddata_pull3(p[0,2], u1runs["feb27"], u1data["feb27"], feb27, lambda w: u1func(area, rfeb, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, w))
    dates += adddata_pull3(p[0,2], u1runs["mar06"], u1data["mar06"], mar06, lambda w: u1func(area, rfeb, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, w))
    dates += adddata_pull3(p[0,2], u1runs["mar13"], u1data["mar13"], mar13, lambda w: u1func(area, rfeb, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, w))
    dates += adddata_pull3(p[0,2], u1runs["apr08"], u1data["apr08"], apr08, lambda w: u1func(area, rapr2, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, w))
    dates += adddata_pull3(p[0,2], u1runs["apr09"], u1data["apr09"], apr09, lambda w: u1func(area, rapr2, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, w))
    dates += adddata_pull3(p[0,2], u1runs["apr10"], u1data["apr10"], apr10, lambda w: u1func(area, rapr2, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, w))
    p[0,2].add(biggles.LineY(0.))
  #  p[0,2].x1.range = 123000, 125500
    p[0,2].x1.range = min(dates)-7.*24.*60.*60., max(dates)+7.*24.*60.*60.
    subticks = []
    sublabels = []
    for t, l in zip(dticks, dlabels):
      if min(dates)-7.*24.*60.*60. < t < max(dates)+7.*24.*60.*60.:
        subticks.append(t)
        sublabels.append(l)
    subsubticks = []
    for t in dsubticks:
      if min(dates)-7.*24.*60.*60. < t < max(dates)+7.*24.*60.*60.:
        subsubticks.append(t)
    p[0,2].x1.ticks = subticks
    p[0,2].x1.subticks = subsubticks
    p[0,2].x1.ticklabels = sublabels
    p[0,2].x2.ticks = subticks
    p[0,2].x2.subticks = subsubticks
    p[0,2].x2.draw_ticklabels = 0
    p[0,2].x1.label = r"Date in 2002"
    p[0,2].y1.label = r"Pull"
    p[0,2].y1.range = -5, 5
    p[0,0].y1.range = -5, 5
    p[0,0].add(biggles.LineY(0.))
    p[0,0].x1.range = 9420., 9580.
    p[0,0].x.ticks = 9420., 9460., 9500., 9540., 9580.
    p[0,0].x1.label = r"$E_{COM}$ in MeV"
    p[0,0].y1.label = r"Pull"
    p[0,1] = h.plot()
    p[0,1].add(h.steps(linewidth=3.5))
    p[0,1].x1.label = r"Pull"
    h.rootn()
    mean, meanerr, width, widtherr, f = dofitgauss(h)
    x = Numeric.arange(-5., 5., 0.01)
    y = Numeric.arange(-5., 5., 0.01)
    for i, xi in enumerate(x): y[i] = f(xi)
    p[0,1].add(biggles.Curve(x,y,linewidth=3.5, linecolor="red"))
    entries = h.sum() + h.underflow() + h.overflow()
  #  hist.addinfobox(p[0,1], [["entries", entries], ["mean", r"%4.2f $\pm$ %4.2f" % (mean, abs(meanerr))], ["width", r"%4.2f $\pm$ %4.2f" % (abs(width), abs(widtherr))], ["underflow", h.underflow()], ["overflow", h.overflow()], ["", ""]], width=0.3, colwidth=0.07)
    p[0,0].aspect_ratio = 3.1
    p[0,1].aspect_ratio = 3.1
    p[0,2].aspect_ratio = 3.1
    p[0,1], p[0,2] = p[0,2], p[0,1]
    p.aspect_ratio = 8.5/11.
    return p

  def u1plot_pull_again(area, rmsbeam, back, jan16, jan30, feb06, feb13, feb20, feb27, mar06, mar13, apr08, apr09, apr10, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, rjan, rfeb, rapr2):
    p = biggles.Table(3,1)
    p[0,0] = biggles.FramedPlot()
    p[2,0] = biggles.FramedPlot()
    h = MoreThanHist(100, -5., 5.)
    h.fill(adddata_pull(p[0,0], u1data["cont"], 0., lambda w: u1func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, w)))
    h.fill(adddata_pull(p[0,0], u1data["high"], 0., lambda w: u1func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, w)))
    h.fill(adddata_pull(p[0,0], u1data["jan16"], jan16, lambda w: u1func(area, rjan, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, w)))
    h.fill(adddata_pull(p[0,0], u1data["jan30"], jan30, lambda w: u1func(area, rjan, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, w)))
    h.fill(adddata_pull(p[0,0], u1data["feb06"], feb06, lambda w: u1func(area, rjan, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, w)))
    h.fill(adddata_pull(p[0,0], u1data["feb13"], feb13, lambda w: u1func(area, rjan, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, w)))
    h.fill(adddata_pull(p[0,0], u1data["feb20"], feb20, lambda w: u1func(area, rjan, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, w)))
    h.fill(adddata_pull(p[0,0], u1data["feb27"], feb27, lambda w: u1func(area, rfeb, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, w)))
    h.fill(adddata_pull(p[0,0], u1data["mar06"], mar06, lambda w: u1func(area, rfeb, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, w)))
    h.fill(adddata_pull(p[0,0], u1data["mar13"], mar13, lambda w: u1func(area, rfeb, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, w)))
    h.fill(adddata_pull(p[0,0], u1data["apr08"], apr08, lambda w: u1func(area, rapr2, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, w)))
    h.fill(adddata_pull(p[0,0], u1data["apr09"], apr09, lambda w: u1func(area, rapr2, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, w)))
    h.fill(adddata_pull(p[0,0], u1data["apr10"], apr10, lambda w: u1func(area, rapr2, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, w)))
    dates = []
    dates += adddata_pull3(p[2,0], u1runs["jan16"], u1data["jan16"], jan16, lambda w: u1func(area, rjan, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, w))
    dates += adddata_pull3(p[2,0], u1runs["jan30"], u1data["jan30"], jan30, lambda w: u1func(area, rjan, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, w))
    dates += adddata_pull3(p[2,0], u1runs["feb06"], u1data["feb06"], feb06, lambda w: u1func(area, rjan, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, w))
    dates += adddata_pull3(p[2,0], u1runs["feb13"], u1data["feb13"], feb13, lambda w: u1func(area, rjan, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, w))
    dates += adddata_pull3(p[2,0], u1runs["feb20"], u1data["feb20"], feb20, lambda w: u1func(area, rjan, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, w))
    dates += adddata_pull3(p[2,0], u1runs["feb27"], u1data["feb27"], feb27, lambda w: u1func(area, rfeb, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, w))
    dates += adddata_pull3(p[2,0], u1runs["mar06"], u1data["mar06"], mar06, lambda w: u1func(area, rfeb, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, w))
    dates += adddata_pull3(p[2,0], u1runs["mar13"], u1data["mar13"], mar13, lambda w: u1func(area, rfeb, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, w))
    dates += adddata_pull3(p[2,0], u1runs["apr08"], u1data["apr08"], apr08, lambda w: u1func(area, rapr2, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, w))
    dates += adddata_pull3(p[2,0], u1runs["apr09"], u1data["apr09"], apr09, lambda w: u1func(area, rapr2, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, w))
    dates += adddata_pull3(p[2,0], u1runs["apr10"], u1data["apr10"], apr10, lambda w: u1func(area, rapr2, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, w))
    p[2,0].add(biggles.LineY(0.))
  #  p[2,0].x1.range = 123000, 125500
    p[2,0].x1.range = min(dates)-3.*24.*60.*60., max(dates)+3.*24.*60.*60.
    subticks = []
    sublabels = []
    for t, l in zip(dticks, dlabels):
      if min(dates)-3.*24.*60.*60. < t < max(dates)+3.*24.*60.*60.:
        subticks.append(t)
        sublabels.append(l)
    subsubticks = []
    for t in dsubticks:
      if min(dates)-3.*24.*60.*60. < t < max(dates)+3.*24.*60.*60.:
        subsubticks.append(t)
    p[2,0].x1.ticks = subticks
    p[2,0].x1.subticks = subsubticks
    p[2,0].x1.ticklabels = sublabels
    p[2,0].x2.ticks = subticks
    p[2,0].x2.subticks = subsubticks
    p[2,0].x2.draw_ticklabels = 0
    p[2,0].x1.label = r"Date in 2002"
    p[2,0].y1.label = r"Pull"
    p[2,0].y1.range = -5, 5
    p[0,0].y1.range = -5, 5
    p[0,0].add(biggles.LineY(0.))
    p[0,0].x1.range = 9420., 9580.
    p[0,0].x1.label = r"Center-of-mass energy (2 $\times$ beam energy) in MeV"
    p[0,0].y1.label = r"Pull"
    p[1,0] = h.plot()
    p[1,0].x1.label = r"Pull"
    h.rootn()
    mean, meanerr, width, widtherr, f = dofitgauss(h)
    x = Numeric.arange(-5., 5., 0.01)
    y = Numeric.arange(-5., 5., 0.01)
    for i, xi in enumerate(x): y[i] = f(xi)
    p[1,0].add(biggles.Curve(x,y))
    entries = h.sum() + h.underflow() + h.overflow()
    hist.addinfobox(p[1,0], [["entries", entries], ["mean", r"%4.2f $\pm$ %4.2f" % (mean, abs(meanerr))], ["width", r"%4.2f $\pm$ %4.2f" % (abs(width), abs(widtherr))], ["underflow", h.underflow()], ["overflow", h.overflow()], ["", ""]], width=0.3, colwidth=0.07)
    p[0,0].aspect_ratio = 0.33
    p[1,0].aspect_ratio = 0.33
    p[2,0].aspect_ratio = 0.33
    p[1,0], p[2,0] = p[2,0], p[1,0]
    p[0,0].add(biggles.PlotLabel(0.05,0.85,"(a)"))
    p[1,0].add(biggles.PlotLabel(0.05,0.85,"(b)"))
    p[2,0].add(biggles.PlotLabel(0.05,0.85,"(c)"))
    p.aspect_ratio = 1.2
    return p

  def u2plot_pull(area, rmsbeam, back, may29, jun11, jun12, jul10, jul24, aug07, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area):
    p = biggles.Table(1,3)
    p[0,0] = biggles.FramedPlot()
    p[0,2] = biggles.FramedPlot()
    h = MoreThanHist(25, -5., 5.)
    h.fill(adddata_pull(p[0,0], u2data["cont"], 0., lambda w: u2func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, w)))
    h.fill(adddata_pull(p[0,0], u2data["high"], 0., lambda w: u2func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, w)))
    h.fill(adddata_pull(p[0,0], u2data["may29"], may29, lambda w: u2func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, w)))
    h.fill(adddata_pull(p[0,0], u2data["jun11"], jun11, lambda w: u2func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, w)))
    h.fill(adddata_pull(p[0,0], u2data["jun12"], jun12, lambda w: u2func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, w)))
    h.fill(adddata_pull(p[0,0], u2data["jul10"], jul10, lambda w: u2func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, w)))
    h.fill(adddata_pull(p[0,0], u2data["jul24"], jul24, lambda w: u2func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, w)))
    h.fill(adddata_pull(p[0,0], u2data["aug07"], aug07, lambda w: u2func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, w)))
    dates = []
    dates += adddata_pull3(p[0,2], u2runs["may29"], u2data["may29"], may29, lambda w: u2func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, w))
    dates += adddata_pull3(p[0,2], u2runs["jun11"], u2data["jun11"], jun11, lambda w: u2func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, w))
    dates += adddata_pull3(p[0,2], u2runs["jun12"], u2data["jun12"], jun12, lambda w: u2func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, w))
    dates += adddata_pull3(p[0,2], u2runs["jul10"], u2data["jul10"], jul10, lambda w: u2func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, w))
    dates += adddata_pull3(p[0,2], u2runs["jul24"], u2data["jul24"], jul24, lambda w: u2func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, w))
    dates += adddata_pull3(p[0,2], u2runs["aug07"], u2data["aug07"], aug07, lambda w: u2func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, w))
    p[0,2].add(biggles.LineY(0.))
  #  p[0,2].x1.range = 126000, 128500
    p[0,2].x1.range = min(dates)-7.*24.*60.*60., max(dates)+7.*24.*60.*60.
    subticks = []
    sublabels = []
    for t, l in zip(dticks, dlabels):
      if min(dates)-7.*24.*60.*60. < t < max(dates)+7.*24.*60.*60.:
        subticks.append(t)
        sublabels.append(l)
    subsubticks = []
    for t in dsubticks:
      if min(dates)-7.*24.*60.*60. < t < max(dates)+7.*24.*60.*60.:
        subsubticks.append(t)
    p[0,2].x1.ticks = subticks
    p[0,2].x1.subticks = subsubticks
    p[0,2].x1.ticklabels = sublabels
    p[0,2].x2.ticks = subticks
    p[0,2].x2.subticks = subsubticks
    p[0,2].x2.draw_ticklabels = 0
    p[0,2].x1.label = r"Date in 2002"
    p[0,2].y1.label = r"Pull"
    p[0,2].y1.range = -5, 5
    p[0,0].y1.range = -5, 5
    p[0,0].add(biggles.LineY(0.))
    p[0,0].x1.range = 9980., 10100.
    p[0,0].x.ticks = 9980., 10020., 10060., 10100.
    p[0,0].x1.label = r"$E_{COM}$ in MeV"
    p[0,0].y1.label = r"Pull"
    p[0,1] = h.plot()
    p[0,1].add(h.steps(linewidth=3.5))
    p[0,1].x1.label = r"Pull"
    h.rootn()
    mean, meanerr, width, widtherr, f = dofitgauss(h)
    x = Numeric.arange(-5., 5., 0.01)
    y = Numeric.arange(-5., 5., 0.01)
    for i, xi in enumerate(x): y[i] = f(xi)
    p[0,1].add(biggles.Curve(x,y, linewidth=3.5, linecolor="red"))
    entries = h.sum() + h.underflow() + h.overflow()
  #  hist.addinfobox(p[0,1], [["entries", entries], ["mean", r"%4.2f $\pm$ %4.2f" % (mean, abs(meanerr))], ["width", r"%4.2f $\pm$ %4.2f" % (abs(width), abs(widtherr))], ["underflow", h.underflow()], ["overflow", h.overflow()], ["", ""]], width=0.3, colwidth=0.07)
    p[0,0].aspect_ratio = 3.1
    p[0,1].aspect_ratio = 3.1
    p[0,2].aspect_ratio = 3.1
    p[0,1], p[0,2] = p[0,2], p[0,1]
    p.aspect_ratio = 8.5/11.
    return p

  def u2plot_pull_again(area, rmsbeam, back, may29, jun11, jun12, jul10, jul24, aug07, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area):
    p = biggles.Table(3,1)
    p[0,0] = biggles.FramedPlot()
    p[2,0] = biggles.FramedPlot()
    h = MoreThanHist(100, -5., 5.)
    h.fill(adddata_pull(p[0,0], u2data["cont"], 0., lambda w: u2func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, w)))
    h.fill(adddata_pull(p[0,0], u2data["high"], 0., lambda w: u2func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, w)))
    h.fill(adddata_pull(p[0,0], u2data["may29"], may29, lambda w: u2func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, w)))
    h.fill(adddata_pull(p[0,0], u2data["jun11"], jun11, lambda w: u2func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, w)))
    h.fill(adddata_pull(p[0,0], u2data["jun12"], jun12, lambda w: u2func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, w)))
    h.fill(adddata_pull(p[0,0], u2data["jul10"], jul10, lambda w: u2func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, w)))
    h.fill(adddata_pull(p[0,0], u2data["jul24"], jul24, lambda w: u2func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, w)))
    h.fill(adddata_pull(p[0,0], u2data["aug07"], aug07, lambda w: u2func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, w)))
    dates = []
    dates += adddata_pull3(p[2,0], u2runs["may29"], u2data["may29"], may29, lambda w: u2func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, w))
    dates += adddata_pull3(p[2,0], u2runs["jun11"], u2data["jun11"], jun11, lambda w: u2func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, w))
    dates += adddata_pull3(p[2,0], u2runs["jun12"], u2data["jun12"], jun12, lambda w: u2func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, w))
    dates += adddata_pull3(p[2,0], u2runs["jul10"], u2data["jul10"], jul10, lambda w: u2func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, w))
    dates += adddata_pull3(p[2,0], u2runs["jul24"], u2data["jul24"], jul24, lambda w: u2func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, w))
    dates += adddata_pull3(p[2,0], u2runs["aug07"], u2data["aug07"], aug07, lambda w: u2func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, w))
    p[2,0].add(biggles.LineY(0.))
  #  p[2,0].x1.range = 126000, 128500
    p[2,0].x1.range = min(dates)-3.*24.*60.*60., max(dates)+3.*24.*60.*60.
    subticks = []
    sublabels = []
    for t, l in zip(dticks, dlabels):
      if min(dates)-3.*24.*60.*60. < t < max(dates)+3.*24.*60.*60.:
        subticks.append(t)
        sublabels.append(l)
    subsubticks = []
    for t in dsubticks:
      if min(dates)-3.*24.*60.*60. < t < max(dates)+3.*24.*60.*60.:
        subsubticks.append(t)
    p[2,0].x1.ticks = subticks
    p[2,0].x1.subticks = subsubticks
    p[2,0].x1.ticklabels = sublabels
    p[2,0].x2.ticks = subticks
    p[2,0].x2.subticks = subsubticks
    p[2,0].x2.draw_ticklabels = 0
    p[2,0].x1.label = r"Date in 2002"
    p[2,0].y1.label = r"Pull"
    p[2,0].y1.range = -5, 5
    p[0,0].y1.range = -5, 5
    p[0,0].add(biggles.LineY(0.))
    p[0,0].x1.range = 9980., 10100.
    p[0,0].x1.label = r"Center-of-mass energy (2 $\times$ beam energy) in MeV"
    p[0,0].y1.label = r"Pull"
    p[1,0] = h.plot()
    p[1,0].x1.label = r"Pull"
    h.rootn()
    mean, meanerr, width, widtherr, f = dofitgauss(h)
    x = Numeric.arange(-5., 5., 0.01)
    y = Numeric.arange(-5., 5., 0.01)
    for i, xi in enumerate(x): y[i] = f(xi)
    p[1,0].add(biggles.Curve(x,y))
    entries = h.sum() + h.underflow() + h.overflow()
    hist.addinfobox(p[1,0], [["entries", entries], ["mean", r"%4.2f $\pm$ %4.2f" % (mean, abs(meanerr))], ["width", r"%4.2f $\pm$ %4.2f" % (abs(width), abs(widtherr))], ["underflow", h.underflow()], ["overflow", h.overflow()], ["", ""]], width=0.3, colwidth=0.07)
    p[0,0].aspect_ratio = 0.33
    p[1,0].aspect_ratio = 0.33
    p[2,0].aspect_ratio = 0.33
    p[1,0], p[2,0] = p[2,0], p[1,0]
    p[0,0].add(biggles.PlotLabel(0.05,0.85,"(a)"))
    p[1,0].add(biggles.PlotLabel(0.05,0.85,"(b)"))
    p[2,0].add(biggles.PlotLabel(0.05,0.85,"(c)"))
    p.aspect_ratio = 1.2
    return p

  def u3plot_pull(area, rmsbeam, back, nov28, dec05, dec12, dec19, dec26, jan02, jan09, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area, rnov28, rdec05, rdec12, rdec19, rdec26, rjan02, rjan09):
    p = biggles.Table(1,3)
    p[0,0] = biggles.FramedPlot()
    p[0,2] = biggles.FramedPlot()
    h = MoreThanHist(25, -5., 5.)
    h.fill(adddata_pull(p[0,0], u3data["cont"], 0., lambda w: u3func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area, w)))
    h.fill(adddata_pull(p[0,0], u3data["high"], 0., lambda w: u3func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area, w)))
    h.fill(adddata_pull(p[0,0], u3data["nov28"], nov28, lambda w: u3func(area, rnov28, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area, w)))
    h.fill(adddata_pull(p[0,0], u3data["dec05"], dec05, lambda w: u3func(area, rdec05, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area, w)))
    h.fill(adddata_pull(p[0,0], u3data["dec12"], dec12, lambda w: u3func(area, rdec12, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area, w)))
    h.fill(adddata_pull(p[0,0], u3data["dec19"], dec19, lambda w: u3func(area, rdec19, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area, w)))
    h.fill(adddata_pull(p[0,0], u3data["dec26"], dec26, lambda w: u3func(area, rdec26, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area, w)))
    h.fill(adddata_pull(p[0,0], u3data["jan02"], jan02, lambda w: u3func(area, rjan02, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area, w)))
    h.fill(adddata_pull(p[0,0], u3data["jan09"], jan09, lambda w: u3func(area, rjan09, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area, w)))
    dates = []
    dates += adddata_pull3(p[0,2], u3runs["nov28"], u3data["nov28"], nov28, lambda w: u3func(area, rnov28, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area, w))
    dates += adddata_pull3(p[0,2], u3runs["dec05"], u3data["dec05"], dec05, lambda w: u3func(area, rdec05, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area, w))
    dates += adddata_pull3(p[0,2], u3runs["dec12"], u3data["dec12"], dec12, lambda w: u3func(area, rdec12, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area, w))
    dates += adddata_pull3(p[0,2], u3runs["dec19"], u3data["dec19"], dec19, lambda w: u3func(area, rdec19, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area, w))
    dates += adddata_pull3(p[0,2], u3runs["dec26"], u3data["dec26"], dec26, lambda w: u3func(area, rdec26, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area, w))
    dates += adddata_pull3(p[0,2], u3runs["jan02"], u3data["jan02"], jan02, lambda w: u3func(area, rjan02, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area, w))
    dates += adddata_pull3(p[0,2], u3runs["jan09"], u3data["jan09"], jan09, lambda w: u3func(area, rjan09, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area, w))
    p[0,2].add(biggles.LineY(0.))
  #  p[0,2].x1.range = 121500, 123500
    p[0,2].x1.range = min(dates)-7.*24.*60.*60., max(dates)+7.*24.*60.*60.
    subticks = []
    sublabels = []
    for t, l in zip(dticks, dlabels):
      if min(dates)-7.*24.*60.*60. < t < max(dates)+7.*24.*60.*60.:
        subticks.append(t)
        sublabels.append(l)
    subsubticks = []
    for t in dsubticks:
      if min(dates)-7.*24.*60.*60. < t < max(dates)+7.*24.*60.*60.:
        subsubticks.append(t)
    p[0,2].x1.ticks = subticks
    p[0,2].x1.subticks = subsubticks
    p[0,2].x1.ticklabels = sublabels
    p[0,2].x2.ticks = subticks
    p[0,2].x2.subticks = subsubticks
    p[0,2].x2.draw_ticklabels = 0
    p[0,2].x1.label = r"Date"
    p[0,2].y1.label = r"Pull"
    p[0,2].y1.range = -5, 5
    p[0,0].y1.range = -5, 5
    p[0,0].add(biggles.LineY(0.))
    p[0,0].x1.range = 10320., 10420.
    p[0,0].x.ticks = 10320., 10370., 10420.
    p[0,0].x1.label = r"$E_{COM}$ in MeV"
    p[0,0].y1.label = r"Pull"
    p[0,1] = h.plot()
    p[0,1].add(h.steps(linewidth=3.5))
    p[0,1].x1.label = r"Pull"
    h.rootn()
    mean, meanerr, width, widtherr, f = dofitgauss(h)
    x = Numeric.arange(-5., 5., 0.01)
    y = Numeric.arange(-5., 5., 0.01)
    for i, xi in enumerate(x): y[i] = f(xi)
    p[0,1].add(biggles.Curve(x,y, linewidth=3.5, linecolor="red"))
    entries = h.sum() + h.underflow() + h.overflow()
  #  hist.addinfobox(p[0,1], [["entries", entries], ["mean", r"%4.2f $\pm$ %4.2f" % (mean, abs(meanerr))], ["width", r"%4.2f $\pm$ %4.2f" % (abs(width), abs(widtherr))], ["underflow", h.underflow()], ["overflow", h.overflow()], ["", ""]], width=0.3, colwidth=0.07)
    p[0,0].aspect_ratio = 3.1
    p[0,1].aspect_ratio = 3.1
    p[0,2].aspect_ratio = 3.1
    p[0,1], p[0,2] = p[0,2], p[0,1]
    p.aspect_ratio = 8.5/11.
    return p

  def u3plot_pull_again(area, rmsbeam, back, nov28, dec05, dec12, dec19, dec26, jan02, jan09, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area, rnov28, rdec05, rdec12, rdec19, rdec26, rjan02, rjan09):
    p = biggles.Table(3,1)
    p[0,0] = biggles.FramedPlot()
    p[2,0] = biggles.FramedPlot()
    h = MoreThanHist(100, -5., 5.)
    h.fill(adddata_pull(p[0,0], u3data["cont"], 0., lambda w: u3func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area, w)))
    h.fill(adddata_pull(p[0,0], u3data["high"], 0., lambda w: u3func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area, w)))
    h.fill(adddata_pull(p[0,0], u3data["nov28"], nov28, lambda w: u3func(area, rnov28, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area, w)))
    h.fill(adddata_pull(p[0,0], u3data["dec05"], dec05, lambda w: u3func(area, rdec05, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area, w)))
    h.fill(adddata_pull(p[0,0], u3data["dec12"], dec12, lambda w: u3func(area, rdec12, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area, w)))
    h.fill(adddata_pull(p[0,0], u3data["dec19"], dec19, lambda w: u3func(area, rdec19, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area, w)))
    h.fill(adddata_pull(p[0,0], u3data["dec26"], dec26, lambda w: u3func(area, rdec26, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area, w)))
    h.fill(adddata_pull(p[0,0], u3data["jan02"], jan02, lambda w: u3func(area, rjan02, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area, w)))
    h.fill(adddata_pull(p[0,0], u3data["jan09"], jan09, lambda w: u3func(area, rjan09, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area, w)))
    dates = []
    dates += adddata_pull3(p[2,0], u3runs["nov28"], u3data["nov28"], nov28, lambda w: u3func(area, rnov28, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area, w))
    dates += adddata_pull3(p[2,0], u3runs["dec05"], u3data["dec05"], dec05, lambda w: u3func(area, rdec05, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area, w))
    dates += adddata_pull3(p[2,0], u3runs["dec12"], u3data["dec12"], dec12, lambda w: u3func(area, rdec12, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area, w))
    dates += adddata_pull3(p[2,0], u3runs["dec19"], u3data["dec19"], dec19, lambda w: u3func(area, rdec19, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area, w))
    dates += adddata_pull3(p[2,0], u3runs["dec26"], u3data["dec26"], dec26, lambda w: u3func(area, rdec26, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area, w))
    dates += adddata_pull3(p[2,0], u3runs["jan02"], u3data["jan02"], jan02, lambda w: u3func(area, rjan02, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area, w))
    dates += adddata_pull3(p[2,0], u3runs["jan09"], u3data["jan09"], jan09, lambda w: u3func(area, rjan09, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area, w))
    p[2,0].add(biggles.LineY(0.))
  #  p[2,0].x1.range = 121500, 123500
    p[2,0].x1.range = min(dates)-3.*24.*60.*60., max(dates)+3.*24.*60.*60.
    subticks = []
    sublabels = []
    for t, l in zip(dticks, dlabels):
      if min(dates)-3.*24.*60.*60. < t < max(dates)+3.*24.*60.*60.:
        subticks.append(t)
        sublabels.append(l)
    subsubticks = []
    for t in dsubticks:
      if min(dates)-3.*24.*60.*60. < t < max(dates)+3.*24.*60.*60.:
        subsubticks.append(t)
    p[2,0].x1.ticks = subticks
    p[2,0].x1.subticks = subsubticks
    p[2,0].x1.ticklabels = sublabels
    p[2,0].x2.ticks = subticks
    p[2,0].x2.subticks = subsubticks
    p[2,0].x2.draw_ticklabels = 0
    p[2,0].x1.label = r"Date in 2001-2002"
    p[2,0].y1.label = r"Pull"
    p[2,0].y1.range = -5, 5
    p[0,0].y1.range = -5, 5
    p[0,0].add(biggles.LineY(0.))
    p[0,0].x1.range = 10320., 10420.
    p[0,0].x1.label = r"Center-of-mass energy (2 $\times$ beam energy) in MeV"
    p[0,0].y1.label = r"Pull"
    p[1,0] = h.plot()
    p[1,0].x1.label = r"Pull"
    h.rootn()
    mean, meanerr, width, widtherr, f = dofitgauss(h)
    x = Numeric.arange(-5., 5., 0.01)
    y = Numeric.arange(-5., 5., 0.01)
    for i, xi in enumerate(x): y[i] = f(xi)
    p[1,0].add(biggles.Curve(x,y))
    entries = h.sum() + h.underflow() + h.overflow()
    hist.addinfobox(p[1,0], [["entries", entries], ["mean", r"%4.2f $\pm$ %4.2f" % (mean, abs(meanerr))], ["width", r"%4.2f $\pm$ %4.2f" % (abs(width), abs(widtherr))], ["underflow", h.underflow()], ["overflow", h.overflow()], ["", ""]], width=0.3, colwidth=0.07)
    p[0,0].aspect_ratio = 0.33
    p[1,0].aspect_ratio = 0.33
    p[2,0].aspect_ratio = 0.33
    p[1,0], p[2,0] = p[2,0], p[1,0]
    p[0,0].add(biggles.PlotLabel(0.05,0.85,"(a)"))
    p[1,0].add(biggles.PlotLabel(0.05,0.85,"(b)"))
    p[2,0].add(biggles.PlotLabel(0.05,0.85,"(c)"))
    p.aspect_ratio = 1.2
    return p

  def adddata2(data, shift, x, y, yerr):
    for (e, h, herr) in data:
      x.append(e*2000.+shift)
      y.append(h)
      yerr.append(herr)
    return None

  def u1plot2(area, rmsbeam, back, jan16, jan30, feb06, feb13, feb20, feb27, mar06, mar13, apr08, apr09, apr10, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, rjan, rfeb, rapr2, p=None, GeV=False):
    if p == None: p = biggles.FramedPlot()
    x = []
    y = []
    yerr = []
    adddata2(u1data["cont"], 0., x, y, yerr)
    adddata2(u1data["high"], 0., x, y, yerr)
    adddata2(u1data["jan16"], jan16, x, y, yerr)
    adddata2(u1data["jan30"], jan30, x, y, yerr)
    adddata2(u1data["feb06"], feb06, x, y, yerr)
    adddata2(u1data["feb13"], feb13, x, y, yerr)
    adddata2(u1data["feb20"], feb20, x, y, yerr)
    adddata2(u1data["feb27"], feb27, x, y, yerr)
    adddata2(u1data["mar06"], mar06, x, y, yerr)
    adddata2(u1data["mar13"], mar13, x, y, yerr)
    adddata2(u1data["apr08"], apr08, x, y, yerr)
    adddata2(u1data["apr09"], apr09, x, y, yerr)
    adddata2(u1data["apr10"], apr10, x, y, yerr)
    themap = {}
    for xi, yi, yerri in zip(x, y, yerr):
      if round(xi) not in themap: themap[round(xi)] = []
      themap[round(xi)].append((xi, yi, yerri))
    fewx = []
    fewy = []
    fewyerr = []
    for rxi in themap:
      fewx.append(jt.mean(map(lambda (xi, yi, yerri): xi, themap[rxi])))
      fewy.append(jt.wmean(map(lambda (xi, yi, yerri): (yi, yerri), themap[rxi]))[0])
      fewyerr.append(jt.wmean(map(lambda (xi, yi, yerri): (yi, yerri), themap[rxi]))[1])
    if GeV: fewx = list(Numeric.array(fewx) / 1000.)
    p.add(biggles.Points(fewx, fewy, symboltype="filled circle", symbolsize=0.8))
    p.add(biggles.SymmetricErrorBarsY(fewx, fewy, fewyerr))
    if not GeV:
      addfunc(p, lambda w: u1func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, w), 9420., 9580., points=1000.)
      addfunc(p, lambda w: u1func_bkgndonly(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, w), 9420., 9580., points=1000., linetype="dashed")
    else:
      addfunc(p, lambda w: u1func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, w*1000.), 9.420, 9.580, points=1000.)
      addfunc(p, lambda w: u1func_bkgndonly(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, w*1000.), 9.420, 9.580, points=1000., linetype="dashed")
    p.xrange = 9420., 9580.
    if GeV: p.xrange = tuple(Numeric.array(p.xrange) / 1000.)
    p.yrange = 0., 2.
    p.aspect_ratio = 1.2
    return p

  def u2plot2(area, rmsbeam, back, may29, jun11, jun12, jul10, jul24, aug07, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, p=None, GeV=False):
    if p == None: p = biggles.FramedPlot()
    x = []
    y = []
    yerr = []
    adddata2(u2data["cont"], 0., x, y, yerr)
    adddata2(u2data["high"], 0., x, y, yerr)
    adddata2(u2data["may29"], may29, x, y, yerr)
    adddata2(u2data["jun11"], jun11, x, y, yerr)
    adddata2(u2data["jun12"], jun12, x, y, yerr)
    adddata2(u2data["jul10"], jul10, x, y, yerr)
    adddata2(u2data["jul24"], jul24, x, y, yerr)
    adddata2(u2data["aug07"], aug07, x, y, yerr)
    themap = {}
    for xi, yi, yerri in zip(x, y, yerr):
      if round(xi) not in themap: themap[round(xi)] = []
      themap[round(xi)].append((xi, yi, yerri))
    fewx = []
    fewy = []
    fewyerr = []
    for rxi in themap:
      fewx.append(jt.mean(map(lambda (xi, yi, yerri): xi, themap[rxi])))
      fewy.append(jt.wmean(map(lambda (xi, yi, yerri): (yi, yerri), themap[rxi]))[0])
      fewyerr.append(jt.wmean(map(lambda (xi, yi, yerri): (yi, yerri), themap[rxi]))[1])
    if GeV: fewx = list(Numeric.array(fewx) / 1000.)
    p.add(biggles.Points(fewx, fewy, symboltype="filled circle", symbolsize=0.8))
    p.add(biggles.SymmetricErrorBarsY(fewx, fewy, fewyerr))
    if not GeV:
      addfunc(p, lambda w: u2func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, w), 9980., 10100., points=1000.)
      addfunc(p, lambda w: u2func_bkgndonly(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, w), 9980., 10100., points=1000., linetype="dashed")
    else:
      addfunc(p, lambda w: u2func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, w*1000.), 9.980, 10.100, points=1000.)
      addfunc(p, lambda w: u2func_bkgndonly(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, w*1000.), 9.980, 10.100, points=1000., linetype="dashed")
    p.xrange = 9980., 10100.
    if GeV: p.xrange = tuple(Numeric.array(p.xrange) / 1000.)
    p.yrange = 0., 2.
    p.aspect_ratio = 1.2
    return p

  def u3plot2(area, rmsbeam, back, nov28, dec05, dec12, dec19, dec26, jan02, jan09, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, rnov28, rdec05, rdec12, rdec19, rdec26, rjan02, rjan09, u2area, p=None, GeV=False):
    if p == None: p = biggles.FramedPlot()
    x = []
    y = []
    yerr = []
    adddata2(u3data["cont"], 0., x, y, yerr)
    adddata2(u3data["high"], 0., x, y, yerr)
    adddata2(u3data["nov28"], nov28, x, y, yerr)
    adddata2(u3data["dec05"], dec05, x, y, yerr)
    adddata2(u3data["dec12"], dec12, x, y, yerr)
    adddata2(u3data["dec19"], dec19, x, y, yerr)
    adddata2(u3data["dec26"], dec26, x, y, yerr)
    adddata2(u3data["jan02"], jan02, x, y, yerr)
    adddata2(u3data["jan09"], jan09, x, y, yerr)
    themap = {}
    for xi, yi, yerri in zip(x, y, yerr):
      if round(xi) not in themap: themap[round(xi)] = []
      themap[round(xi)].append((xi, yi, yerri))
    fewx = []
    fewy = []
    fewyerr = []
    for rxi in themap:
      fewx.append(jt.mean(map(lambda (xi, yi, yerri): xi, themap[rxi])))
      fewy.append(jt.wmean(map(lambda (xi, yi, yerri): (yi, yerri), themap[rxi]))[0])
      fewyerr.append(jt.wmean(map(lambda (xi, yi, yerri): (yi, yerri), themap[rxi]))[1])
    if GeV: fewx = list(Numeric.array(fewx) / 1000.)
    p.add(biggles.Points(fewx, fewy, symboltype="filled circle", symbolsize=0.8))
    p.add(biggles.SymmetricErrorBarsY(fewx, fewy, fewyerr))
    if not GeV:
      addfunc(p, lambda w: u3func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area, w), 10320., 10420., points=1000.)
      addfunc(p, lambda w: u3func_bkgndonly(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area, w), 10320., 10420., points=1000., linetype="dashed")
    else:
      addfunc(p, lambda w: u3func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area, w*1000.), 10.320, 10.420, points=1000.)
      addfunc(p, lambda w: u3func_bkgndonly(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area, w*1000.), 10.320, 10.420, points=1000., linetype="dashed")
    p.xrange = 10320., 10420.
    if GeV: p.xrange = tuple(Numeric.array(p.xrange) / 1000.)
    p.yrange = 0., 2.
    p.aspect_ratio = 1.2
    return p

  def u1plot3(area, rmsbeam, back, jan16, jan30, feb06, feb13, feb20, feb27, mar06, mar13, apr08, apr09, apr10, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, rjan, rfeb, rapr2, p=None, GeV=False):
    if p == None: p = biggles.FramedPlot()
    x = []
    y = []
    yerr = []
    adddata2(u1data["cont"], 0., x, y, yerr)
    adddata2(u1data["high"], 0., x, y, yerr)
    adddata2(u1data["jan16"], jan16, x, y, yerr)
    adddata2(u1data["jan30"], jan30, x, y, yerr)
    adddata2(u1data["feb06"], feb06, x, y, yerr)
    adddata2(u1data["feb13"], feb13, x, y, yerr)
    adddata2(u1data["feb20"], feb20, x, y, yerr)
    adddata2(u1data["feb27"], feb27, x, y, yerr)
    adddata2(u1data["mar06"], mar06, x, y, yerr)
    adddata2(u1data["mar13"], mar13, x, y, yerr)
    adddata2(u1data["apr08"], apr08, x, y, yerr)
    adddata2(u1data["apr09"], apr09, x, y, yerr)
    adddata2(u1data["apr10"], apr10, x, y, yerr)
    themap = {}
    for xi, yi, yerri in zip(x, y, yerr):
      if round(xi) not in themap: themap[round(xi)] = []
      themap[round(xi)].append((xi, yi, yerri))
    fewx = []
    fewy = []
    fewyerr = []
    for rxi in themap:
      fewx.append(jt.mean(map(lambda (xi, yi, yerri): xi, themap[rxi])))
      fewy.append(jt.wmean(map(lambda (xi, yi, yerri): (yi, yerri), themap[rxi]))[0])
      fewyerr.append(jt.wmean(map(lambda (xi, yi, yerri): (yi, yerri), themap[rxi]))[1])
    if GeV: fewx = list(Numeric.array(fewx) / 1000.)
    p.add(biggles.Points(fewx, fewy, symboltype="filled circle", symbolsize=3.))
    p.add(biggles.SymmetricErrorBarsY(fewx, fewy, fewyerr))
    if not GeV:
      addfunc(p, lambda w: u1func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, w), 9420., 9580., points=1000., linewidth=4.)
      addfunc(p, lambda w: u1func_bkgndonly(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, w), 9420., 9580., points=1000., linetype="dashed", linewidth=4.)
    else:
      addfunc(p, lambda w: u1func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, w*1000.), 9.420, 9.580, points=1000., linewidth=4.)
      addfunc(p, lambda w: u1func_bkgndonly(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, w*1000.), 9.420, 9.580, points=1000., linetype="dashed", linewidth=4.)
    p.xrange = 9420., 9580.
    if GeV: p.xrange = tuple(Numeric.array(p.xrange) / 1000.)
    p.yrange = 0., 2.
    p.aspect_ratio = 1.2
    return p

  def u2plot3(area, rmsbeam, back, may29, jun11, jun12, jul10, jul24, aug07, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, p=None, GeV=False):
    if p == None: p = biggles.FramedPlot()
    x = []
    y = []
    yerr = []
    adddata2(u2data["cont"], 0., x, y, yerr)
    adddata2(u2data["high"], 0., x, y, yerr)
    adddata2(u2data["may29"], may29, x, y, yerr)
    adddata2(u2data["jun11"], jun11, x, y, yerr)
    adddata2(u2data["jun12"], jun12, x, y, yerr)
    adddata2(u2data["jul10"], jul10, x, y, yerr)
    adddata2(u2data["jul24"], jul24, x, y, yerr)
    adddata2(u2data["aug07"], aug07, x, y, yerr)
    themap = {}
    for xi, yi, yerri in zip(x, y, yerr):
      if round(xi) not in themap: themap[round(xi)] = []
      themap[round(xi)].append((xi, yi, yerri))
    fewx = []
    fewy = []
    fewyerr = []
    for rxi in themap:
      fewx.append(jt.mean(map(lambda (xi, yi, yerri): xi, themap[rxi])))
      fewy.append(jt.wmean(map(lambda (xi, yi, yerri): (yi, yerri), themap[rxi]))[0])
      fewyerr.append(jt.wmean(map(lambda (xi, yi, yerri): (yi, yerri), themap[rxi]))[1])
    if GeV: fewx = list(Numeric.array(fewx) / 1000.)
    p.add(biggles.Points(fewx, fewy, symboltype="filled circle", symbolsize=3.))
    p.add(biggles.SymmetricErrorBarsY(fewx, fewy, fewyerr))
    if not GeV:
      addfunc(p, lambda w: u2func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, w), 9980., 10100., points=1000., linewidth=4.)
      addfunc(p, lambda w: u2func_bkgndonly(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, w), 9980., 10100., points=1000., linetype="dashed", linewidth=4.)
    else:
      addfunc(p, lambda w: u2func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, w*1000.), 9.980, 10.100, points=1000., linewidth=4.)
      addfunc(p, lambda w: u2func_bkgndonly(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, w*1000.), 9.980, 10.100, points=1000., linetype="dashed", linewidth=4.)
    p.xrange = 9980., 10100.
    if GeV: p.xrange = tuple(Numeric.array(p.xrange) / 1000.)
    p.yrange = 0., 2.
    p.aspect_ratio = 1.2
    return p

  def u3plot3(area, rmsbeam, back, nov28, dec05, dec12, dec19, dec26, jan02, jan09, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area, rnov28, rdec05, rdec12, rdec19, rdec26, rjan02, rjan09, p=None, GeV=False):
    if p == None: p = biggles.FramedPlot()
    x = []
    y = []
    yerr = []
    adddata2(u3data["cont"], 0., x, y, yerr)
    adddata2(u3data["high"], 0., x, y, yerr)
    adddata2(u3data["nov28"], nov28, x, y, yerr)
    adddata2(u3data["dec05"], dec05, x, y, yerr)
    adddata2(u3data["dec12"], dec12, x, y, yerr)
    adddata2(u3data["dec19"], dec19, x, y, yerr)
    adddata2(u3data["dec26"], dec26, x, y, yerr)
    adddata2(u3data["jan02"], jan02, x, y, yerr)
    adddata2(u3data["jan09"], jan09, x, y, yerr)
    themap = {}
    for xi, yi, yerri in zip(x, y, yerr):
      if round(xi) not in themap: themap[round(xi)] = []
      themap[round(xi)].append((xi, yi, yerri))
    fewx = []
    fewy = []
    fewyerr = []
    for rxi in themap:
      fewx.append(jt.mean(map(lambda (xi, yi, yerri): xi, themap[rxi])))
      fewy.append(jt.wmean(map(lambda (xi, yi, yerri): (yi, yerri), themap[rxi]))[0])
      fewyerr.append(jt.wmean(map(lambda (xi, yi, yerri): (yi, yerri), themap[rxi]))[1])
    if GeV: fewx = list(Numeric.array(fewx) / 1000.)
    p.add(biggles.Points(fewx, fewy, symboltype="filled circle", symbolsize=3.))
    p.add(biggles.SymmetricErrorBarsY(fewx, fewy, fewyerr))
    if not GeV:
      addfunc(p, lambda w: u3func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area, w), 10320., 10420., points=1000., linewidth=4.)
      addfunc(p, lambda w: u3func_bkgndonly(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area, w), 10320., 10420., points=1000., linetype="dashed", linewidth=4.)
    else:
      addfunc(p, lambda w: u3func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area, w*1000.), 10.320, 10.420, points=1000., linewidth=4.)
      addfunc(p, lambda w: u3func_bkgndonly(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area, w*1000.), 10.320, 10.420, points=1000., linetype="dashed", linewidth=4.)
    p.xrange = 10320., 10420.
    if GeV: p.xrange = tuple(Numeric.array(p.xrange) / 1000.)
    p.yrange = 0., 2.
    p.aspect_ratio = 1.2
    return p

  ############################################################################

  u1runs = {}
  u2runs = {}
  u3runs = {}
  u1data = {}
  u2data = {}
  u3data = {}

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

  u1data["cont"] = [get_runs(u1runs["cont"], lumisource=lumisource)]
  u1data["high"] = [get_runs(u1runs["high"], lumisource=lumisource)]
  u1data["jan16"] = setup_data(u1runs["jan16"], lumisource=lumisource)
  u1data["jan30"] = setup_data(u1runs["jan30"], lumisource=lumisource)
  u1data["feb06"] = setup_data(u1runs["feb06"], lumisource=lumisource)
  u1data["feb13"] = setup_data(u1runs["feb13"], lumisource=lumisource)
  u1data["feb20"] = setup_data(u1runs["feb20"], lumisource=lumisource)
  u1data["feb27"] = setup_data(u1runs["feb27"], lumisource=lumisource)
  u1data["mar06"] = setup_data(u1runs["mar06"], lumisource=lumisource)
  u1data["mar13"] = setup_data(u1runs["mar13"], lumisource=lumisource)
  u1data["apr08"] = setup_data(u1runs["apr08"], lumisource=lumisource)
  u1data["apr09"] = setup_data(u1runs["apr09"], lumisource=lumisource)
  u1data["apr10"] = setup_data(u1runs["apr10"], lumisource=lumisource)

  u1fitter = Minuit(u1fit)
  u1fitter.fix(range(u1fitter.npar))
  u1fitter.release(["area", "back"])

  u1fitter.values = ggfits[1].values
  u1fitter.values[u1fitter.findpar("area")] = 8.72
  u1fitter.values[u1fitter.findpar("back")] = 1.07
  u1fitter.values[u1fitter.findpar("tauyint")] = 0.195/sqrt(0.5499605367008682)
  u1fitter.migrad()
  if not u1fitter.valid: u1fitter.migrad()
  if u1fitter.valid: u1fitter.hesse()
  if u1fitter.valid: u1fitter.minos()
  print "1s: ", u1fitter
  print zip(u1fitter.names, u1fitter.minos_errors)

  u2data["cont"] = [get_runs(u2runs["cont"], lumisource=lumisource, u1area=u1fitter.values[u1fitter.findpar("area")])]
  u2data["high"] = [get_runs(u2runs["high"], lumisource=lumisource, u1area=u1fitter.values[u1fitter.findpar("area")])]
  u2data["may29"] = setup_data(u2runs["may29"], lumisource=lumisource, u1area=u1fitter.values[u1fitter.findpar("area")])
  u2data["jun11"] = setup_data(u2runs["jun11"], lumisource=lumisource, u1area=u1fitter.values[u1fitter.findpar("area")])
  u2data["jun12"] = setup_data(u2runs["jun12"], lumisource=lumisource, u1area=u1fitter.values[u1fitter.findpar("area")])
  u2data["jul10"] = setup_data(u2runs["jul10"], lumisource=lumisource, u1area=u1fitter.values[u1fitter.findpar("area")])
  u2data["jul24"] = setup_data(u2runs["jul24"], lumisource=lumisource, u1area=u1fitter.values[u1fitter.findpar("area")])
  u2data["aug07"] = setup_data(u2runs["aug07"], lumisource=lumisource, u1area=u1fitter.values[u1fitter.findpar("area")])

  u2fitter = Minuit(u2fit)
  u2fitter.fix(range(u2fitter.npar))
  u2fitter.release(["area", "back"])

  u2fitter.values = ggfits[2].values
  u2fitter.values[u2fitter.findpar("area")] *= 0.0203
  u2fitter.values[u2fitter.findpar("back")] *= 1./3.58
  u2fitter.values[u2fitter.findpar("tauyint")] = 0.240/sqrt(0.55475703830685041)
  u2fitter.migrad()
  if not u2fitter.valid: u2fitter.migrad()
  if u2fitter.valid: u2fitter.hesse()
  if u2fitter.valid: u2fitter.minos()
  print "2s: ", u2fitter
  print zip(u2fitter.names, u2fitter.minos_errors)

  u3data["cont"] = [get_runs(u3runs["cont"], lumisource=lumisource, u1area=u1fitter.values[u1fitter.findpar("area")], u2area=u2fitter.values[u2fitter.findpar("area")])]
  u3data["high"] = [get_runs(u3runs["high"], lumisource=lumisource, u1area=u1fitter.values[u1fitter.findpar("area")], u2area=u2fitter.values[u2fitter.findpar("area")])]
  u3data["nov28"] = setup_data(u3runs["nov28"], lumisource=lumisource, u1area=u1fitter.values[u1fitter.findpar("area")], u2area=u2fitter.values[u2fitter.findpar("area")])
  u3data["dec05"] = setup_data(u3runs["dec05"], lumisource=lumisource, u1area=u1fitter.values[u1fitter.findpar("area")], u2area=u2fitter.values[u2fitter.findpar("area")])
  u3data["dec12"] = setup_data(u3runs["dec12"], lumisource=lumisource, u1area=u1fitter.values[u1fitter.findpar("area")], u2area=u2fitter.values[u2fitter.findpar("area")])
  u3data["dec19"] = setup_data(u3runs["dec19"], lumisource=lumisource, u1area=u1fitter.values[u1fitter.findpar("area")], u2area=u2fitter.values[u2fitter.findpar("area")])
  u3data["dec26"] = setup_data(u3runs["dec26"], lumisource=lumisource, u1area=u1fitter.values[u1fitter.findpar("area")], u2area=u2fitter.values[u2fitter.findpar("area")])
  u3data["jan02"] = setup_data(u3runs["jan02"], lumisource=lumisource, u1area=u1fitter.values[u1fitter.findpar("area")], u2area=u2fitter.values[u2fitter.findpar("area")])
  u3data["jan09"] = setup_data(u3runs["jan09"], lumisource=lumisource, u1area=u1fitter.values[u1fitter.findpar("area")], u2area=u2fitter.values[u2fitter.findpar("area")])

  u3fitter = Minuit(u3fit)
  u3fitter.fix(range(u3fitter.npar))
  u3fitter.release(["area", "back"])
  u3fitter.values = ggfits[3].values
  u3fitter.values[u3fitter.findpar("area")] *= 0.0239
  u3fitter.values[u3fitter.findpar("back")] *= 1./3.58
  u3fitter.values[u3fitter.findpar("tauyint")] = 0.203/sqrt(0.5224697398918362)
  u3fitter.migrad()
  if not u3fitter.valid: u3fitter.migrad()
  if u3fitter.valid: u3fitter.hesse()
  if u3fitter.valid: u3fitter.minos()
  print "3s: ", u3fitter
  print zip(u3fitter.names, u3fitter.minos_errors)

  class FitRecord: pass
  fitrecord = {}
  fitrecord[1] = FitRecord()
  fitrecord[2] = FitRecord()
  fitrecord[3] = FitRecord()

  if u1fitter.values == None:
    fitrecord[1].values = None
  else:
    fitrecord[1].values = u1fitter.values[:]
  if u1fitter.errors == None:
    fitrecord[1].errors = None
  else:
    fitrecord[1].errors = u1fitter.errors[:]
  fitrecord[1].fval = u1fitter.fval
  fitrecord[1].fmin = u1fit(*u1fitter.values)
  fitrecord[1].edm = u1fitter.edm
  if u1fitter.covariance == None:
    fitrecord[1].covariance = None
  else:
    fitrecord[1].covariance = u1fitter.covariance[:]
  fitrecord[1].ncalls = u1fitter.ncalls
  if u1fitter.minos_errors == None:
    fitrecord[1].minos_errors = None
  else:
    fitrecord[1].minos_errors = u1fitter.minos_errors[:]
  fitrecord[1].whystring = u1fitter.whystring
  fitrecord[1].minos_whystring = u1fitter.minos_whystring

  if u2fitter.values == None:
    fitrecord[2].values = None
  else:
    fitrecord[2].values = u2fitter.values[:]
  if u2fitter.errors == None:
    fitrecord[2].errors = None
  else:
    fitrecord[2].errors = u2fitter.errors[:]
  fitrecord[2].fval = u2fitter.fval
  fitrecord[2].fmin = u2fit(*u2fitter.values)
  fitrecord[2].edm = u2fitter.edm
  if u2fitter.covariance == None:
    fitrecord[2].covariance = None
  else:
    fitrecord[2].covariance = u2fitter.covariance[:]
  fitrecord[2].ncalls = u2fitter.ncalls
  if u2fitter.minos_errors == None:
    fitrecord[2].minos_errors = None
  else:
    fitrecord[2].minos_errors = u2fitter.minos_errors[:]
  fitrecord[2].whystring = u2fitter.whystring
  fitrecord[2].minos_whystring = u2fitter.minos_whystring

  if u3fitter.values == None:
    fitrecord[3].values = None
  else:
    fitrecord[3].values = u3fitter.values[:]
  if u3fitter.errors == None:
    fitrecord[3].errors = None
  else:
    fitrecord[3].errors = u3fitter.errors[:]
  fitrecord[3].fval = u3fitter.fval
  fitrecord[3].fmin = u3fit(*u3fitter.values)
  fitrecord[3].edm = u3fitter.edm
  if u3fitter.covariance == None:
    fitrecord[3].covariance = None
  else:
    fitrecord[3].covariance = u3fitter.covariance[:]
  fitrecord[3].ncalls = u3fitter.ncalls
  if u3fitter.minos_errors == None:
    fitrecord[3].minos_errors = None
  else:
    fitrecord[3].minos_errors = u3fitter.minos_errors[:]
  fitrecord[3].whystring = u3fitter.whystring
  fitrecord[3].minos_whystring = u3fitter.minos_whystring

  pickle.dump((u1runs, u2runs, u3runs, u1data, u2data, u3data), open("/home/mccann/antithesis/fit_results/mumudata_nfi_"+str(lumisource)+"_"+str(bhabha_interference)+".p", 'w'))
  pickle.dump(fitrecord, open("/home/mccann/antithesis/fit_results/mumufits_nfi_"+str(lumisource)+"_"+str(bhabha_interference)+".p", 'w'))

  dticks = []
  dlabels = []
  for y in (2001, 2002):
    for m in Numeric.array(range(12))+1:
      for d in [1]:
        dticks.append(time.mktime(time.strptime("%02d %02d %4d" % (m, d, y), "%m %d %Y")))
  for y in (2001, 2002):
    for m in ("Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"):
      for d in [1,]:
        if d == 1:
          dlabels.append("%s" % (m))
        else:
          dlabels.append("%d" % (d))
  dsubticks = []
  for y in (2001, 2002):
    for d in Numeric.array(range(365))+1:
      if d % 7 == 0:
        dsubticks.append(time.mktime(time.strptime("%03d %4d" % (d, y), "%j %Y")))
  extraarea = 4.
  u1plot_pull(*fitrecord[1].values).write_eps("/home/mccann/antithesis/fit_results/mumufits_"+str(lumisource)+"_"+str(bhabha_interference)+"_pulls1.eps")

  dticks = []
  dlabels = []
  for y in (2001, 2002):
    for m in Numeric.array(range(12))+1:
      for d in [1, 8, 15, 22]:
        dticks.append(time.mktime(time.strptime("%02d %02d %4d" % (m, d, y), "%m %d %Y")))
  for y in (2001, 2002):
    for m in ("Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"):
      for d in [1, 8, 15, 22]:
        if d == 1:
          dlabels.append("%s" % (m))
        else:
          dlabels.append("%d" % (d))
  dsubticks = []
  for y in (2001, 2002):
    for d in Numeric.array(range(365))+1:
        dsubticks.append(time.mktime(time.strptime("%03d %4d" % (d, y), "%j %Y")))
  extraarea = 1.
  u1plot_pull_again(*fitrecord[1].values).write_eps("/home/mccann/antithesis/fit_results/mumufits_"+str(lumisource)+"_"+str(bhabha_interference)+"_pulls1again.eps")

  dticks = []
  dlabels = []
  for y in (2001, 2002):
    for m in Numeric.array(range(12))+1:
      for d in [1]:
        dticks.append(time.mktime(time.strptime("%02d %02d %4d" % (m, d, y), "%m %d %Y")))
  for y in (2001, 2002):
    for m in ("Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"):
      for d in [1]:
        if d == 1:
          dlabels.append("%s" % (m))
        else:
          dlabels.append("%d" % (d))
  dsubticks = []
  for y in (2001, 2002):
    for d in Numeric.array(range(365))+1:
      if d % 7 == 0:
        dsubticks.append(time.mktime(time.strptime("%03d %4d" % (d, y), "%j %Y")))
  extraarea = 4.
  u2plot_pull(*fitrecord[2].values).write_eps("/home/mccann/antithesis/fit_results/mumufits_"+str(lumisource)+"_"+str(bhabha_interference)+"_pulls2.eps")

  dticks = []
  dlabels = []
  for y in (2001, 2002):
    for m in Numeric.array(range(12))+1:
      for d in [1, 8, 15, 22]:
        dticks.append(time.mktime(time.strptime("%02d %02d %4d" % (m, d, y), "%m %d %Y")))
  for y in (2001, 2002):
    for m in ("Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"):
      for d in [1, 8, 15, 22]:
        if d == 1:
          dlabels.append("%s" % (m))
        else:
          dlabels.append("%d" % (d))
  dsubticks = []
  for y in (2001, 2002):
    for d in Numeric.array(range(365))+1:
        dsubticks.append(time.mktime(time.strptime("%03d %4d" % (d, y), "%j %Y")))
  extraarea = 1.
  u2plot_pull_again(*fitrecord[2].values).write_eps("/home/mccann/antithesis/fit_results/mumufits_"+str(lumisource)+"_"+str(bhabha_interference)+"_pulls2again.eps")

  dticks = []
  dlabels = []
  for y in (2001, 2002):
    for m in Numeric.array(range(12))+1:
      for d in [1]:
        dticks.append(time.mktime(time.strptime("%02d %02d %4d" % (m, d, y), "%m %d %Y")))
  for y in (2001, 2002):
    for m in ("Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"):
      for d in [1]:
        if d == 1:
          dlabels.append("%s %d" % (m, y))
        else:
          dlabels.append("%d" % (d))
  dsubticks = []
  for y in (2001, 2002):
    for d in Numeric.array(range(365))+1:
      if d % 7 == 0:
        dsubticks.append(time.mktime(time.strptime("%03d %4d" % (d, y), "%j %Y")))
  extraarea = 4.
  u3plot_pull(*fitrecord[3].values).write_eps("/home/mccann/antithesis/fit_results/mumufits_"+str(lumisource)+"_"+str(bhabha_interference)+"_pulls3.eps")

  dticks = []
  dlabels = []
  for y in (2001, 2002):
    for m in Numeric.array(range(12))+1:
      for d in [1, 8, 15, 22]:
        dticks.append(time.mktime(time.strptime("%02d %02d %4d" % (m, d, y), "%m %d %Y")))
  for y in (2001, 2002):
    for m in ("Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"):
      for d in [1, 8, 15, 22]:
        if d == 1:
          dlabels.append("%s %d" % (m, y))
        else:
          dlabels.append("%d" % (d))
  dsubticks = []
  for y in (2001, 2002):
    for d in Numeric.array(range(365))+1:
        dsubticks.append(time.mktime(time.strptime("%03d %4d" % (d, y), "%j %Y")))
  extraarea = 1.
  u3plot_pull_again(*fitrecord[3].values).write_eps("/home/mccann/antithesis/fit_results/mumufits_"+str(lumisource)+"_"+str(bhabha_interference)+"_pulls3again.eps")

  p1 = u1plot2(*fitrecord[1].values)
  p1_inset = u1plot3(*fitrecord[1].values)
  p2 = u2plot2(*fitrecord[2].values)
  p2_inset = u2plot3(*fitrecord[2].values)
  p3 = u3plot2(*fitrecord[3].values)
  p3_inset = u3plot3(*fitrecord[3].values)

  p1_inset.y1.range = 7., 9.
  p1_inset.x1.range = 9540., 9580.
  p1_inset.x1.draw_ticklabels = 0
  p1_inset.x.ticks = range(9540, 9580+40, 40)
  p1_inset.x.subticks = range(9540, 9580, 5)
  p1_inset.y2.draw_ticks = 0
  p1.aspect_ratio = 2.
  p1.y1.range = 0., 30.
  p1.x.ticks = range(9420, 9580+40, 40)
  p1.x.subticks = range(9420, 9580, 5)
  p1.add(biggles.PlotLabel(0.2, 0.92, r"$\Upsilon(1S)$", fontsize=3.5))
  p1.x1.label = "Center-of-mass energy in MeV"
  p1.y1.label = "Hadronic cross-section in nb"

  p2_inset.y1.range = 6.3, 8.3
  p2_inset.x1.range = 10070., 10100.
  p2_inset.x1.draw_ticklabels = 0
  p2_inset.x.ticks = range(10070, 10100, 40)
  p2_inset.x.subticks = range(10070, 10100, 5)
  p2_inset.y2.draw_ticks = 0
  p2.aspect_ratio = 2.
  p2.x.ticks = range(9980, 10100+40, 40)
  p2.x.subticks = range(9980, 10100, 5)
  p2.y1.range = 0., 18.
  p2.add(biggles.PlotLabel(0.2, 0.92, r"$\Upsilon(2S)$", fontsize=3.5))
  p2.x1.label = "Center-of-mass energy in MeV"
  p2.y1.label = "Hadronic cross-section in nb"

  p3_inset.x1.range = 10390., 10410.
  p3_inset.y1.range = 6., 8.
  p3_inset.x1.draw_ticklabels = 0
  p3_inset.x.ticks = range(10390, 10410, 25)
  p3_inset.x.subticks = range(10390, 10410, 5)
  p3.aspect_ratio = 2.
  p3.y1.range = 0., 14.
  p3.x.ticks = range(10320, 10420+25, 25)
  p3.x.subticks = range(10320, 10420, 5)
  p3.add(biggles.PlotLabel(0.2, 0.92, r"$\Upsilon(3S)$", fontsize=3.5))
  p3.x1.label = "Center-of-mass energy in MeV"
  p3.y1.label = "Hadronic cross-section in nb"

  # qq = biggles.Table(1,3)
  # qq[0,0] = p1
  # qq[0,1] = p2
  # qq[0,2] = p3
  # qq.aspect_ratio = 0.4

  p1.write_eps("/home/mccann/antithesis/fit_results/mumufits_"+str(lumisource)+"_"+str(bhabha_interference)+"_individual_noinset_1s.eps")
  p2.write_eps("/home/mccann/antithesis/fit_results/mumufits_"+str(lumisource)+"_"+str(bhabha_interference)+"_individual_noinset_2s.eps")
  p3.write_eps("/home/mccann/antithesis/fit_results/mumufits_"+str(lumisource)+"_"+str(bhabha_interference)+"_individual_noinset_3s.eps")

  thep1_inset = biggles.DataInset((9540., 20.), (9580., 10.), p1_inset)
  p1.add(thep1_inset)
  thep2_inset = biggles.DataInset((10070., 10.), (10100., 15.), p2_inset)
  p2.add(thep2_inset)
  thep3_inset = biggles.DataInset((10390., 9.), (10410., 12.), p3_inset)
  p3.add(thep3_inset)

  p1.write_eps("/home/mccann/antithesis/fit_results/mumufits_"+str(lumisource)+"_"+str(bhabha_interference)+"_individual_withinset_1s.eps")
  p2.write_eps("/home/mccann/antithesis/fit_results/mumufits_"+str(lumisource)+"_"+str(bhabha_interference)+"_individual_withinset_2s.eps")
  p3.write_eps("/home/mccann/antithesis/fit_results/mumufits_"+str(lumisource)+"_"+str(bhabha_interference)+"_individual_withinset_3s.eps")

  ###################

  p1 = u1plot2(*fitrecord[1].values)
  p1_inset = u1plot3(*fitrecord[1].values)
  p2 = u2plot2(*fitrecord[2].values)
  p2_inset = u2plot3(*fitrecord[2].values)
  p3 = u3plot2(*fitrecord[3].values)
  p3_inset = u3plot3(*fitrecord[3].values)

  p1_inset.y1.range = 7., 9.
  p1_inset.x1.range = 9540., 9580.
  p1_inset.x1.draw_ticklabels = 0
  p1_inset.x.ticks = range(9540, 9580+40, 40)
  p1_inset.x.subticks = range(9540, 9580, 5)
  p1_inset.y2.draw_ticks = 0
  p1.aspect_ratio = 0.7
  p1.y1.range = 0., 30.
  p1.x.ticks = range(9420, 9580+40, 40)
  p1.x.subticks = range(9420, 9580, 5)
  p1.add(biggles.PlotLabel(0.1, 0.92, r"$\Upsilon(1S)$", fontsize=3.5))
  p1.x1.label = "Center-of-mass energy in MeV"
  p1.y1.label = "Hadronic cross-section in nb"

  p2_inset.y1.range = 6.3, 8.3
  p2_inset.x1.range = 10070., 10100.
  p2_inset.x1.draw_ticklabels = 0
  p2_inset.x.ticks = range(10070, 10100, 40)
  p2_inset.x.subticks = range(10070, 10100, 5)
  p2_inset.y2.draw_ticks = 0
  p2.aspect_ratio = 0.7
  p2.x.ticks = range(9980, 10100+40, 40)
  p2.x.subticks = range(9980, 10100, 5)
  p2.y1.range = 0., 18.
  p2.add(biggles.PlotLabel(0.1, 0.92, r"$\Upsilon(2S)$", fontsize=3.5))
  p2.x1.label = "Center-of-mass energy in MeV"
  p2.y1.label = "Hadronic cross-section in nb"

  p3_inset.x1.range = 10390., 10410.
  p3_inset.y1.range = 6., 8.
  p3_inset.x1.draw_ticklabels = 0
  p3_inset.x.ticks = range(10390, 10410, 25)
  p3_inset.x.subticks = range(10390, 10410, 5)
  p3.aspect_ratio = 0.7
  p3.y1.range = 0., 14.
  p3.x.ticks = range(10320, 10420+25, 25)
  p3.x.subticks = range(10320, 10420, 5)
  p3.add(biggles.PlotLabel(0.1, 0.92, r"$\Upsilon(3S)$", fontsize=3.5))
  p3.x1.label = "Center-of-mass energy in MeV"
  p3.y1.label = "Hadronic cross-section in nb"

  # qq = biggles.Table(1,3)
  # qq[0,0] = p1
  # qq[0,1] = p2
  # qq[0,2] = p3
  # qq.aspect_ratio = 0.4

  p1.write_eps("/home/mccann/antithesis/fit_results/mumufits_"+str(lumisource)+"_"+str(bhabha_interference)+"_individual0.7_noinset_1s.eps")
  p2.write_eps("/home/mccann/antithesis/fit_results/mumufits_"+str(lumisource)+"_"+str(bhabha_interference)+"_individual0.7_noinset_2s.eps")
  p3.write_eps("/home/mccann/antithesis/fit_results/mumufits_"+str(lumisource)+"_"+str(bhabha_interference)+"_individual0.7_noinset_3s.eps")

  thep1_inset = biggles.DataInset((9540., 20.), (9580., 10.), p1_inset)
  p1.add(thep1_inset)
  thep2_inset = biggles.DataInset((10070., 10.), (10100., 15.), p2_inset)
  p2.add(thep2_inset)
  thep3_inset = biggles.DataInset((10390., 9.), (10410., 12.), p3_inset)
  p3.add(thep3_inset)

  p1.write_eps("/home/mccann/antithesis/fit_results/mumufits_"+str(lumisource)+"_"+str(bhabha_interference)+"_individual0.7_withinset_1s.eps")
  p2.write_eps("/home/mccann/antithesis/fit_results/mumufits_"+str(lumisource)+"_"+str(bhabha_interference)+"_individual0.7_withinset_2s.eps")
  p3.write_eps("/home/mccann/antithesis/fit_results/mumufits_"+str(lumisource)+"_"+str(bhabha_interference)+"_individual0.7_withinset_3s.eps")

  ####################

  p1 = u1plot2(*fitrecord[1].values)
  p2 = u2plot2(*fitrecord[2].values)
  p3 = u3plot2(*fitrecord[3].values)

  p1.y1.range = 0., 2.
  p1.x.ticks = range(9420, 9580+20, 20)
  p1.x.subticks = range(9420, 9580, 5)
  p1.x1.label = r"Center-of-mass energy (2 $\times$ beam energy) in MeV"
  p1.y1.label = "Hadronic cross-section in nb"

  p2.x.ticks = range(9980, 10100+20, 20)
  p2.x.subticks = range(9980, 10100, 5)
  p2.y1.range = 0., 2.
  p2.x1.label = r"Center-of-mass energy (2 $\times$ beam energy) in MeV"
  p2.y1.label = "Hadronic cross-section in nb"

  p3.y1.range = 0., 2.
  p3.x.ticks = range(10320, 10420+20, 20)
  p3.x.subticks = range(10320, 10420, 5)
  p3.x1.label = r"Center-of-mass energy (2 $\times$ beam energy) in MeV"
  p3.y1.label = "Hadronic cross-section in nb"

  p = biggles.Table(3,1)
  p[0,0] = p1
  p[0,0].add(biggles.PlotLabel(0.1,0.8,"(a)"))
  p[0,0].aspect_ratio = 0.33
  p[1,0] = p2
  p[1,0].add(biggles.PlotLabel(0.1,0.8,"(b)"))
  p[1,0].aspect_ratio = 0.33
  p[2,0] = p3
  p[2,0].add(biggles.PlotLabel(0.1,0.8,"(c)"))
  p[2,0].aspect_ratio = 0.33
  p.aspect_ratio = 1.2
  p.write_eps("/home/mccann/antithesis/fit_results/mumufits_"+str(lumisource)+"_"+str(bhabha_interference)+"_final_allfit_comb2.eps")

  p1_inset.y1.range = 7., 9.
  p1_inset.x1.range = 9540., 9580.
  p1_inset.y.ticks = [7., 8., 9.]
  p1_inset.y.subticks = Numeric.arange(7,9,0.2)
  p1_inset.y2.draw_ticklabels = 0
  p1_inset.y2.draw_ticks = 1
  p1_inset.x.draw_ticks = 0
  p1_inset.x.draw_ticklabels = 0

  p2_inset.y1.range = 6., 8.
  p2_inset.x1.range = 10070., 10100.
  p2_inset.y.ticks = [6., 7., 8.]
  p2_inset.y.subticks = Numeric.arange(6,8,0.2)
  p2_inset.y2.draw_ticklabels = 0
  p2_inset.y2.draw_ticks = 1
  p2_inset.x.draw_ticks = 0
  p2_inset.x.draw_ticklabels = 0

  p3_inset.x1.range = 10390., 10410.
  p3_inset.y1.range = 6., 8.
  p3_inset.y.ticks = [6., 7., 8.]
  p3_inset.y.subticks = Numeric.arange(6,8,0.2)
  p3_inset.y2.draw_ticklabels = 0
  p3_inset.y2.draw_ticks = 1
  p3_inset.x.draw_ticks = 0
  p3_inset.x.draw_ticklabels = 0

  p[0,0].add(biggles.PlotInset((0.8, 0.9), (0.95, 0.5), p1_inset))
  p[1,0].add(biggles.PlotInset((0.8, 0.9), (0.95, 0.5), p2_inset))
  p[2,0].add(biggles.PlotInset((0.8, 0.9), (0.95, 0.5), p3_inset))
  p[0,0].y1.range = 0., 2.
  p[1,0].y1.range = 0., 2.
  p[2,0].y1.range = 0., 2.
  p[0,0].y.ticks = range(0, 31, 5)
  p[1,0].y.ticks = range(0, 19, 5)
  p[2,0].y.ticks = range(0, 17, 5)
  p[0,0].y.subticks = range(0, 31)
  p[1,0].y.subticks = range(0, 19)
  p[2,0].y.subticks = range(0, 17)
  p[0,0].y2.draw_ticklabels = 0
  p[1,0].y2.draw_ticklabels = 0
  p[2,0].y2.draw_ticklabels = 0
  p.write_eps("/home/mccann/antithesis/fit_results/mumufits_"+str(lumisource)+"_"+str(bhabha_interference)+"_final_allfit_comb3.eps")






  p = biggles.Table(3,1)
  p[0,0] = u1plot2(*fitrecord[1].values)
  p[0,0].aspect_ratio = 0.33
  p[0,0].add(biggles.PlotLabel(0.1,0.8,"(a)"))
  p[0,0].y1.label = r"Hadronic cross-section in nb"
  p[0,0].x1.label = r"Center-of-mass energy (2 $\times$ beam energy) in MeV"
  p[1,0] = u2plot2(*fitrecord[2].values)
  p[1,0].aspect_ratio = 0.33
  p[1,0].add(biggles.PlotLabel(0.1,0.8,"(b)"))
  p[1,0].y1.label = r"Hadronic cross-section in nb"
  p[1,0].x1.label = r"Center-of-mass energy (2 $\times$ beam energy) in MeV"
  p[2,0] = u3plot2(*fitrecord[3].values)
  p[2,0].aspect_ratio = 0.33
  p[2,0].add(biggles.PlotLabel(0.1,0.8,"(c)"))
  p[2,0].y1.label = r"Hadronic cross-section in nb"
  p[2,0].x1.label = r"Center-of-mass energy (2 $\times$ beam energy) in MeV"
  p[0,0].y1.range = 0., 2.
  p[1,0].y1.range = 0., 2.
  p[2,0].y1.range = 0., 2.
  p.aspect_ratio = 1.2
  p.write_eps("/home/mccann/antithesis/fit_results/mumufits_"+str(lumisource)+"_"+str(bhabha_interference)+"_final_allfit_comb.eps")





  p1_inset = u1plot3(*fitrecord[1].values)
  p2_inset = u2plot3(*fitrecord[2].values)
  p3_inset = u3plot3(*fitrecord[3].values)

  p1_inset.y1.range = 7., 9.
  p1_inset.x1.range = 9540., 9580.
  p1_inset.y.ticks = [7., 8., 9.]
  p1_inset.y.subticks = Numeric.arange(7,9,0.2)
  p1_inset.y2.draw_ticklabels = 0
  p1_inset.y2.draw_ticks = 1
  p1_inset.x.draw_ticks = 0
  p1_inset.x.draw_ticklabels = 0

  p2_inset.y1.range = 6., 8.
  p2_inset.x1.range = 10070., 10100.
  p2_inset.y.ticks = [6., 7., 8.]
  p2_inset.y.subticks = Numeric.arange(6,8,0.2)
  p2_inset.y2.draw_ticklabels = 0
  p2_inset.y2.draw_ticks = 1
  p2_inset.x.draw_ticks = 0
  p2_inset.x.draw_ticklabels = 0

  p3_inset.x1.range = 10390., 10410.
  p3_inset.y1.range = 6., 8.
  p3_inset.y.ticks = [6., 7., 8.]
  p3_inset.y.subticks = Numeric.arange(6,8,0.2)
  p3_inset.y2.draw_ticklabels = 0
  p3_inset.y2.draw_ticks = 1
  p3_inset.x.draw_ticks = 0
  p3_inset.x.draw_ticklabels = 0

  q2 = biggles.FramedArray(1,3)
  q2[0,0].add(biggles.Points([0,1], [0,1]))
  q2[0,1].add(biggles.Points([0,1], [0,1]))
  q2[0,2].add(biggles.Points([0,1], [0,1]))
  q2[0,0].add(biggles.PlotInset((0.7, 0.96), (0.96, 0.7), p1_inset))
  q2[0,1].add(biggles.PlotInset((0.7, 0.96), (0.96, 0.7), p2_inset))
  q2[0,2].add(biggles.PlotInset((0.7, 0.96), (0.96, 0.7), p3_inset))
  q2[0,0].xrange = Numeric.array([0., 0.1]) + (9.4603 - 0.035)
  q2[0,1].xrange = Numeric.array([0., 0.1]) + (10.02326 - 0.035)
  q2[0,2].xrange = Numeric.array([0., 0.1]) + (10.3552 - 0.035)
  q2[0,0].add(biggles.PlotBox((0.2, 0.15), (0.8, 0.09), color="yellow", width=130))
  q2[0,1].add(biggles.PlotBox((0.2, 0.15), (0.8, 0.09), color="yellow", width=130))
  q2[0,2].add(biggles.PlotBox((0.2, 0.15), (0.8, 0.09), color="yellow", width=130))
#   q2[0,0].add(biggles.PlotLabel(0.69, 0.18-0.01, r"$\Gamma_{ee}$ = 1.336", texthalign="right", fontsize=5.))
#   q2[0,0].add(biggles.PlotLabel(0.32, 0.14-0.02, r"$\pm$ 0.009", texthalign="left", fontsize=5.))
#   q2[0,0].add(biggles.PlotLabel(0.32, 0.10-0.03, r"$\pm$ 0.019 keV", texthalign="left", fontsize=5.))
#   q2[0,1].add(biggles.PlotLabel(0.69, 0.18-0.01, r"$\Gamma_{ee}$ = 0.616", texthalign="right", fontsize=5.))
#   q2[0,1].add(biggles.PlotLabel(0.32, 0.14-0.02, r"$\pm$ 0.010", texthalign="left", fontsize=5.))
#   q2[0,1].add(biggles.PlotLabel(0.32, 0.10-0.03, r"$\pm$ 0.009 keV", texthalign="left", fontsize=5.))
#   q2[0,2].add(biggles.PlotLabel(0.69, 0.18-0.01, r"$\Gamma_{ee}$ = 0.425", texthalign="right", fontsize=5.))
#   q2[0,2].add(biggles.PlotLabel(0.32, 0.14-0.02, r"$\pm$ 0.009", texthalign="left", fontsize=5.))
#   q2[0,2].add(biggles.PlotLabel(0.32, 0.10-0.03, r"$\pm$ 0.006 keV", texthalign="left", fontsize=5.))
  q2[0,0].add(biggles.PlotLabel(0.2, 0.92, r"$\Upsilon(1S)$", fontsize=5.))
  q2[0,1].add(biggles.PlotLabel(0.2, 0.92, r"$\Upsilon(2S)$", fontsize=5.))
  q2[0,2].add(biggles.PlotLabel(0.2, 0.92, r"$\Upsilon(3S)$", fontsize=5.))
  q2.yrange = 0., 30.
  q2.xlabel = r"Center-of-mass energy in GeV"
  q2.ylabel = r"Hadronic cross-section in nb"
  q2.aspect_ratio = 7./10.5


  q = biggles.FramedArray(1,3)
#   q[0,0].add(biggles.PlotBox((0.2, 0.15), (0.8, 0.09), color="yellow", width=130))
#   q[0,1].add(biggles.PlotBox((0.2, 0.15), (0.8, 0.09), color="yellow", width=130))
#   q[0,2].add(biggles.PlotBox((0.2, 0.15), (0.8, 0.09), color="yellow", width=130))
  longer = {}
  longer[1] = fitrecord[1].values[:]
  longer[1].append(q[0,0])
  longer[1].append(True)
  longer[2] = fitrecord[2].values[:]
  longer[2].append(q[0,1])
  longer[2].append(True)
  longer[3] = fitrecord[3].values[:]
  longer[3].append(q[0,2])
  longer[3].append(True)
  u1plot2(*longer[1])
  u2plot2(*longer[2])
  u3plot2(*longer[3])
  q[0,0].add(biggles.PlotInset((0.7, 0.96), (0.96, 0.7), p1_inset))
  q[0,1].add(biggles.PlotInset((0.7, 0.96), (0.96, 0.7), p2_inset))
  q[0,2].add(biggles.PlotInset((0.7, 0.96), (0.96, 0.7), p3_inset))
  # q[0,0].xrange = Numeric.array([0., 0.049]) + 9.437
  # q[0,1].xrange = Numeric.array([0., 0.049]) + 10.001
  # q[0,2].xrange = Numeric.array([0., 0.049]) + 10.333
  q[0,0].xrange = Numeric.array([0., 0.1]) + (9.4603 - 0.035)
  q[0,1].xrange = Numeric.array([0., 0.1]) + (10.02326 - 0.035)
  q[0,2].xrange = Numeric.array([0., 0.1]) + (10.3552 - 0.035)
  # q[0,0].add(biggles.PlotLabel(0.7, 0.18-0.01, r"$\Gamma_{ee}$ = 1.336", texthalign="right", fontsize=5.))
  # q[0,0].add(biggles.PlotLabel(0.31, 0.14-0.02, r"$\pm$ 0.009", texthalign="left", fontsize=5.))
  # q[0,0].add(biggles.PlotLabel(0.31, 0.10-0.03, r"$\pm$ 0.019 keV", texthalign="left", fontsize=5.))
  # q[0,1].add(biggles.PlotLabel(0.7, 0.18-0.01, r"$\Gamma_{ee}$ = 0.616", texthalign="right", fontsize=5.))
  # q[0,1].add(biggles.PlotLabel(0.31, 0.14-0.02, r"$\pm$ 0.010", texthalign="left", fontsize=5.))
  # q[0,1].add(biggles.PlotLabel(0.31, 0.10-0.03, r"$\pm$ 0.009 keV", texthalign="left", fontsize=5.))
  # q[0,2].add(biggles.PlotLabel(0.7, 0.18-0.01, r"$\Gamma_{ee}$ = 0.425", texthalign="right", fontsize=5.))
  # q[0,2].add(biggles.PlotLabel(0.31, 0.14-0.02, r"$\pm$ 0.009", texthalign="left", fontsize=5.))
  # q[0,2].add(biggles.PlotLabel(0.31, 0.10-0.03, r"$\pm$ 0.006 keV", texthalign="left", fontsize=5.))

#   q[0,0].add(biggles.PlotLabel(0.69, 0.18-0.01, r"$\Gamma_{ee}$ = 1.336", texthalign="right", fontsize=5.))
#   q[0,0].add(biggles.PlotLabel(0.32, 0.14-0.02, r"$\pm$ 0.009", texthalign="left", fontsize=5.))
#   q[0,0].add(biggles.PlotLabel(0.32, 0.10-0.03, r"$\pm$ 0.019 keV", texthalign="left", fontsize=5.))
#   q[0,1].add(biggles.PlotLabel(0.69, 0.18-0.01, r"$\Gamma_{ee}$ = 0.616", texthalign="right", fontsize=5.))
#   q[0,1].add(biggles.PlotLabel(0.32, 0.14-0.02, r"$\pm$ 0.010", texthalign="left", fontsize=5.))
#   q[0,1].add(biggles.PlotLabel(0.32, 0.10-0.03, r"$\pm$ 0.009 keV", texthalign="left", fontsize=5.))
#   q[0,2].add(biggles.PlotLabel(0.69, 0.18-0.01, r"$\Gamma_{ee}$ = 0.425", texthalign="right", fontsize=5.))
#   q[0,2].add(biggles.PlotLabel(0.32, 0.14-0.02, r"$\pm$ 0.009", texthalign="left", fontsize=5.))
#   q[0,2].add(biggles.PlotLabel(0.32, 0.10-0.03, r"$\pm$ 0.006 keV", texthalign="left", fontsize=5.))
  q[0,0].add(biggles.PlotLabel(0.2, 0.92, r"$\Upsilon(1S)$", fontsize=5.))
  q[0,1].add(biggles.PlotLabel(0.2, 0.92, r"$\Upsilon(2S)$", fontsize=5.))
  q[0,2].add(biggles.PlotLabel(0.2, 0.92, r"$\Upsilon(3S)$", fontsize=5.))
  q.yrange = 0., 30.
  q.xlabel = r"Center-of-mass energy in GeV"
  q.ylabel = r"Hadronic cross-section in nb"
  q.aspect_ratio = 7./10.5
  q.write_eps("/home/mccann/antithesis/fit_results/mumufits_"+str(lumisource)+"_"+str(bhabha_interference)+"_three_resonances_inset_squat2.eps")


  p = biggles.Table(3,1)
  p[0,0] = u1plot(*fitrecord[1].values)
  p[0,0].aspect_ratio = 0.33
  p[0,0].add(biggles.PlotLabel(0.1,0.8,"(a)"))
  p[0,0].y1.label = r"$\propto$ Hadronic Cross-section"
  p[0,0].x1.label = r"Center-of-mass energy (2 $\times$ beam energy) in MeV"
  p[1,0] = u2plot(*fitrecord[2].values)
  p[1,0].aspect_ratio = 0.33
  p[1,0].add(biggles.PlotLabel(0.1,0.8,"(b)"))
  p[1,0].y1.label = r"$\propto$ Hadronic Cross-section"
  p[1,0].x1.label = r"Center-of-mass energy (2 $\times$ beam energy) in MeV"
  p[2,0] = u3plot(*fitrecord[3].values)
  p[2,0].aspect_ratio = 0.33
  p[2,0].add(biggles.PlotLabel(0.1,0.8,"(c)"))
  p[2,0].y1.label = r"$\propto$ Hadronic Cross-section"
  p[2,0].x1.label = r"Center-of-mass energy (2 $\times$ beam energy) in MeV"
  p.aspect_ratio = 1.2
  p.write_eps("/home/mccann/antithesis/fit_results/mumufits_"+str(lumisource)+"_"+str(bhabha_interference)+"_allfit.eps")

  p = biggles.Table(3,1)
  p[0,0] = u1plot2(*fitrecord[1].values)
  p[0,0].aspect_ratio = 0.33
  p[0,0].add(biggles.PlotLabel(0.1,0.8,"(a)"))
  p[0,0].y1.label = r"$\propto$ Hadronic Cross-section"
  p[0,0].x1.label = r"Center-of-mass energy (2 $\times$ beam energy) in MeV"
  p[1,0] = u2plot2(*fitrecord[2].values)
  p[1,0].aspect_ratio = 0.33
  p[1,0].add(biggles.PlotLabel(0.1,0.8,"(b)"))
  p[1,0].y1.label = r"$\propto$ Hadronic Cross-section"
  p[1,0].x1.label = r"Center-of-mass energy (2 $\times$ beam energy) in MeV"
  p[2,0] = u3plot2(*fitrecord[3].values)
  p[2,0].aspect_ratio = 0.33
  p[2,0].add(biggles.PlotLabel(0.1,0.8,"(c)"))
  p[2,0].y1.label = r"$\propto$ Hadronic Cross-section"
  p[2,0].x1.label = r"Center-of-mass energy (2 $\times$ beam energy) in MeV"
  p.aspect_ratio = 1.2
  p.write_eps("/home/mccann/antithesis/fit_results/mumufits_"+str(lumisource)+"_"+str(bhabha_interference)+"_allfit_comb.eps")

print "************************************** from B&S bhabhas with interference"
doitall(3, 1.)

# Look at all the plots I made!
# 
# "/home/mccann/antithesis/fit_results/mumufits_"+str(lumisource)+"_"+str(bhabha_interference)+"_allfit_comb.eps")
# "/home/mccann/antithesis/fit_results/mumufits_"+str(lumisource)+"_"+str(bhabha_interference)+"_allfit.eps")
# "/home/mccann/antithesis/fit_results/mumufits_"+str(lumisource)+"_"+str(bhabha_interference)+"_final_allfit_comb2.eps")
# "/home/mccann/antithesis/fit_results/mumufits_"+str(lumisource)+"_"+str(bhabha_interference)+"_final_allfit_comb3.eps")
# "/home/mccann/antithesis/fit_results/mumufits_"+str(lumisource)+"_"+str(bhabha_interference)+"_final_allfit_comb.eps")
# "/home/mccann/antithesis/fit_results/mumufits_"+str(lumisource)+"_"+str(bhabha_interference)+"_individual0.7_noinset_1s.eps")
# "/home/mccann/antithesis/fit_results/mumufits_"+str(lumisource)+"_"+str(bhabha_interference)+"_individual0.7_noinset_2s.eps")
# "/home/mccann/antithesis/fit_results/mumufits_"+str(lumisource)+"_"+str(bhabha_interference)+"_individual0.7_noinset_3s.eps")
# "/home/mccann/antithesis/fit_results/mumufits_"+str(lumisource)+"_"+str(bhabha_interference)+"_individual0.7_withinset_1s.eps")
# "/home/mccann/antithesis/fit_results/mumufits_"+str(lumisource)+"_"+str(bhabha_interference)+"_individual0.7_withinset_2s.eps")
# "/home/mccann/antithesis/fit_results/mumufits_"+str(lumisource)+"_"+str(bhabha_interference)+"_individual0.7_withinset_3s.eps")
# "/home/mccann/antithesis/fit_results/mumufits_"+str(lumisource)+"_"+str(bhabha_interference)+"_individual_noinset_1s.eps")
# "/home/mccann/antithesis/fit_results/mumufits_"+str(lumisource)+"_"+str(bhabha_interference)+"_individual_noinset_2s.eps")
# "/home/mccann/antithesis/fit_results/mumufits_"+str(lumisource)+"_"+str(bhabha_interference)+"_individual_noinset_3s.eps")
# "/home/mccann/antithesis/fit_results/mumufits_"+str(lumisource)+"_"+str(bhabha_interference)+"_individual_withinset_1s.eps")
# "/home/mccann/antithesis/fit_results/mumufits_"+str(lumisource)+"_"+str(bhabha_interference)+"_individual_withinset_2s.eps")
# "/home/mccann/antithesis/fit_results/mumufits_"+str(lumisource)+"_"+str(bhabha_interference)+"_individual_withinset_3s.eps")
# "/home/mccann/antithesis/fit_results/mumufits_"+str(lumisource)+"_"+str(bhabha_interference)+"_pulls1again.eps")
# "/home/mccann/antithesis/fit_results/mumufits_"+str(lumisource)+"_"+str(bhabha_interference)+"_pulls1.eps")
# "/home/mccann/antithesis/fit_results/mumufits_"+str(lumisource)+"_"+str(bhabha_interference)+"_pulls2again.eps")
# "/home/mccann/antithesis/fit_results/mumufits_"+str(lumisource)+"_"+str(bhabha_interference)+"_pulls2.eps")
# "/home/mccann/antithesis/fit_results/mumufits_"+str(lumisource)+"_"+str(bhabha_interference)+"_pulls3again.eps")
# "/home/mccann/antithesis/fit_results/mumufits_"+str(lumisource)+"_"+str(bhabha_interference)+"_pulls3.eps")
# "/home/mccann/antithesis/fit_results/mumufits_"+str(lumisource)+"_"+str(bhabha_interference)+"_three_resonances_inset_squat2.eps")
