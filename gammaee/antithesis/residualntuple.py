import sys
sys.path.append("/home/mccann/bin/python/obsolete")

from minuit import *
execfile("/home/mccann/antithesis/utilities.py")
nobeam = getsb("cos")
ebeam = getsb("bge")
pbeam = getsb("bgp")
import gbwkf
import gbwkftau
runstart = pickle.load(open("/home/mccann/antithesis/old_dotps/runstart.p"))
runend = pickle.load(open("/home/mccann/antithesis/old_dotps/runend.p"))
import time
bsbha = pickle.load(open("/home/mccann/synthesis/run/bsbha.p"))

nbish2nb = 23.0481
bhabha_interference = 1.   # this is a multiplier: 0. to turn off

class FitRecord: pass
ggfits = pickle.load(open("/home/mccann/antithesis/fit_results/octoberfits_fixen_0_1.0.p"))

# I learned this from Matt and the beam energy program logs
runsummary[123828].energy = 4.72992
runsummary[123832].energy = 4.72990

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

def background(w):
  tmp = 0.
  tmp += 9.35538858434 * (1.-0.0792) * 9000.**2 / w**2
  tmp += 9.35538858434 * 0.0792 * log(w**2/9000.**2)
  return tmp

def u1func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, w):
  tmp = 0.
  tmp += area * 0.9793 * mygbwkf(9460.30, fullgam, rmsbeam, yint, phi, w)
  tmp += area * 0.578 * btautau * mygbwkftau(9460.30, fullgam, rmsbeam, tauyint, tauphi, w)
  tmp += back * (1.-twophofrac) * 9000.**2 / w**2
  tmp += back * twophofrac * log(w**2/9000.**2)
  return tmp

def u2func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, w):
  tmp = 0.
  tmp += area * 0.9618 * mygbwkf(10023.26, fullgam, rmsbeam, yint, phi, w)
  tmp += area * 0.578 * btautau * mygbwkftau(10023.26, fullgam, rmsbeam, tauyint, tauphi, w)
  tmp += back * (1.-twophofrac) * 9000.**2 / w**2
  tmp += back * twophofrac * log(w**2/9000.**2)
  tmp += u1area * mygbwkf(9460.30, 0., 0., 0., 0., w)
  return tmp

def u3func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area, w):
  tmp = 0.
  tmp += area * 0.9641 * mygbwkf(10355.2, fullgam, rmsbeam, yint, phi, w)
  tmp += area * 0.578 * btautau * mygbwkftau(10355.2, fullgam, rmsbeam, tauyint, tauphi, w)
  tmp += back * (1.-twophofrac) * 9000.**2 / w**2
  tmp += back * twophofrac * log(w**2/9000.**2)
  tmp += u1area * mygbwkf(9460.30, 0., 0., 0., 0., w)
  tmp += u2area * mygbwkf(10023.26, 0., 0., 0., 0., w)
  return tmp

def whichamiin(r):
  if runsummary[r].res == 1:
    for s in ["jan16", "jan30", "feb06", "feb13", "feb20", "feb27", "mar06", "mar13", "apr03", "apr08", "apr09", "apr10"]:
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

def get_run(r):
  gamgam_lumi = None
  gamgam_lumi_err = None
  bhabha_lumi = None
  bhabha_lumi_err = None
  num_hadrons = None
  num_hadrons_err = None
  the_energy = None
  the_shift = None

  therun = getdb(r)
  for lumisource in (0, 3):
    g = 0.
    h = 0.
    e = 0.
    p = 0.
    c = 0.

    ngg = therun.gamgam
    if r in mycarefulscan: ngg = therun.gamgam_vstime.sum(0.,0.99)

    fitrec = pickle.load(open("/home/mccann/antithesis/fit_results/novemberfits_lastever_3_1.0.p"))

    if runsummary[r].res == 1:
      myarea, myrmsbeam, myback, myjan16, myjan30, myfeb06, myfeb13, myfeb20, myfeb27, mymar06, mymar13, myapr03, myapr08, myapr09, myapr10, myfullgam, myyint, myphi, mybtautau, mytauyint, mytauphi, mytwophofrac, myrjan, myrfeb, myrapr1, myrapr2 = fitrec[1].values
    elif runsummary[r].res == 2:
      myarea, myrmsbeam, myback, mymay29, myjun11, myjun12, myjul10, myjul24, myaug07, myfullgam, myyint, myphi, mybtautau, mytauyint, mytauphi, mytwophofrac, myu1area = fitrec[2].values
    elif runsummary[r].res == 3:
      myarea, myrmsbeam, myback, mynov28, mydec05, mydec12, mydec19, mydec26, myjan02, myjan09, myfullgam, myyint, myphi, mybtautau, mytauyint, mytauphi, mytwophofrac, myu1area, myu2area, myrnov28, myrdec05, myrdec12, myrdec19, myrdec26, myrjan02, myrjan09 = fitrec[3].values

    whichres, whichweek = whichamiin(r)
    thisshift = 0.
    if whichweek != None:
      thisshift = eval("my"+whichweek)

    the_energy = runsummary[r].energy*2000.
    the_shift = thisshift

    if runsummary[r].res == 1:
      myarea, myrmsbeam, myback, myjan16, myjan30, myfeb06, myfeb13, myfeb20, myfeb27, mymar06, mymar13, myapr03, myapr08, myapr09, myapr10, myfullgam, myyint, myphi, mybtautau, mytauyint, mytauphi, mytwophofrac, myrjan, myrfeb, myrapr1, myrapr2 = ggfits[1].values
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
        if whichweek in ["apr03", "apr08", "apr09"]: thisrmsbeam = myrapr1
        if whichweek in ["apr10"]: thisrmsbeam = myrapr2
    if whichres == 3:
      if whichweek != None:
        thisrmsbeam = eval("myr"+whichweek)

    thisshift = 0.
    if whichweek != None:
      thisshift = 0. - eval("my"+whichweek)

    if r in mycarefulscan:
      h += therun.hadroncool_vstime.sum(0.,0.99)
      e += therun.beamgase_vstime.sum(0.,0.99)
      p += therun.beamgasp_vstime.sum(0.,0.99)
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
      h += therun.hadroncool
      e += therun.beamgase
      p += therun.beamgasp
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

    average_energy = runsummary[r].energy

    ebkgnd = 1. * (ebeam.hadroncool - 1.*nobeam.hadroncool*ebeam.cosmic/nobeam.cosmic) * e / ebeam.beamgase
    pbkgnd = 1. * (pbeam.hadroncool - 1.*nobeam.hadroncool*pbeam.cosmic/nobeam.cosmic) * p / pbeam.beamgasp
    cbkgnd = 1. * nobeam.hadroncool * c / nobeam.cosmic

    hadrons = h - ebkgnd/2. - pbkgnd/2. - cbkgnd
    hadrons_err = sqrt(h + c * (1.*nobeam.hadroncool/nobeam.cosmic)**2 + ebkgnd/2. + pbkgnd/2.)

    num_hadrons = hadrons
    num_hadrons_err = hadrons_err

    if lumisource == 3:
      if whichres == 1:
        cs = hadrons / g / average_energy**2 * 199.5   # these differences are due to different efficiencies, as predicted by the MC
        bhabha_lumi = g * average_energy**2 / 199.5
        bhabha_lumi_err = sqrt(g) * average_energy**2 / 199.5
      elif whichres == 2:
        cs = hadrons / g / average_energy**2 * 197.4   # and verified by my lumi counts
        bhabha_lumi = g * average_energy**2 / 197.4
        bhabha_lumi_err = sqrt(g) * average_energy**2 / 197.4
      elif whichres == 3:
        cs = hadrons / g / average_energy**2 * 196.0   # (I totally believe this.)
        bhabha_lumi = g * average_energy**2 / 196.0
        bhabha_lumi_err = sqrt(g) * average_energy**2 / 196.0

      cs_err = cs * sqrt((1.*hadrons_err / hadrons)**2 + 1./g)

    else:
      cs = hadrons / g / average_energy**2 * nbish2nb
      cs_err = cs * sqrt((1.*hadrons_err / hadrons)**2 + 1./g)
      gamgam_lumi = g * average_energy**2 / nbish2nb
      gamgam_lumi_err = sqrt(g) * average_energy**2 / nbish2nb

      if lumisource == 1:
        cs /= 0.23684
        cs_err /= 0.23684

      if lumisource == 2:
        cs /= 0.118999
        cs_err /= 0.118999

  return float(the_energy), float(the_shift), float(gamgam_lumi), float(gamgam_lumi_err), float(bhabha_lumi), float(bhabha_lumi_err), float(num_hadrons), float(num_hadrons_err)

class ARun:
  def __init__(self, r):
    self.run = r
    self.en, self.shift, self.gg, self.gg_err, self.bb, self.bb_err, self.had, self.had_err = get_run(r)

  def getfval(self):
    fitrec = pickle.load(open("/home/mccann/antithesis/fit_results/novemberfits_lastever_3_1.0.p"))

    whichres, whichweek = whichamiin(self.run)
    if whichres == 1:
      myarea, myrmsbeam, myback, myjan16, myjan30, myfeb06, myfeb13, myfeb20, myfeb27, mymar06, mymar13, myapr03, myapr08, myapr09, myapr10, myfullgam, myyint, myphi, mybtautau, mytauyint, mytauphi, mytwophofrac, myrjan, myrfeb, myrapr1, myrapr2 = fitrec[1].values
      thisrmsbeam = myrmsbeam
      if whichweek != None:
        if whichweek in ["jan16", "jan30", "feb06", "feb13", "feb20"]: thisrmsbeam = myrjan
        if whichweek in ["feb27", "mar06", "mar13"]: thisrmsbeam = myrfeb
        if whichweek in ["apr03", "apr08", "apr09"]: thisrmsbeam = myrapr1
        if whichweek in ["apr10"]: thisrmsbeam = myrapr2
      else:
        if runsummary[self.run].kind != "c" and runsummary[self.run].kind != "h":
          raise Exception
      self.func = u1func(myarea, thisrmsbeam, myback, myfullgam, myyint, myphi, mybtautau, mytauyint, mytauphi, mytwophofrac, self.en+self.shift)
      self.deriv = (self.func - u1func(myarea, thisrmsbeam, myback, myfullgam, myyint, myphi, mybtautau, mytauyint, mytauphi, mytwophofrac, self.en+self.shift-0.1))/0.1

    elif whichres == 2:
      myarea, myrmsbeam, myback, mymay29, myjun11, myjun12, myjul10, myjul24, myaug07, myfullgam, myyint, myphi, mybtautau, mytauyint, mytauphi, mytwophofrac, myu1area = fitrec[2].values
      self.func = u2func(myarea, myrmsbeam, myback, myfullgam, myyint, myphi, mybtautau, mytauyint, mytauphi, mytwophofrac, myu1area, self.en+self.shift)
      self.deriv = (self.func - u2func(myarea, myrmsbeam, myback, myfullgam, myyint, myphi, mybtautau, mytauyint, mytauphi, mytwophofrac, myu1area, self.en+self.shift-0.1))/0.1

    elif whichres == 3:
      myarea, myrmsbeam, myback, mynov28, mydec05, mydec12, mydec19, mydec26, myjan02, myjan09, myfullgam, myyint, myphi, mybtautau, mytauyint, mytauphi, mytwophofrac, myu1area, myu2area, myrnov28, myrdec05, myrdec12, myrdec19, myrdec26, myrjan02, myrjan09 = fitrec[3].values
      thisrmsbeam = myrmsbeam
      if whichres == 3:
        if whichweek != None:
          thisrmsbeam = eval("myr"+whichweek)
        else:
          if runsummary[self.run].kind != "c" and runsummary[self.run].kind != "h":
            raise Exception
      self.func = u3func(myarea, thisrmsbeam, myback, myfullgam, myyint, myphi, mybtautau, mytauyint, mytauphi, mytwophofrac, myu1area, myu2area, self.en+self.shift)
      self.deriv = (self.func - u3func(myarea, thisrmsbeam, myback, myfullgam, myyint, myphi, mybtautau, mytauyint, mytauphi, mytwophofrac, myu1area, myu2area, self.en+self.shift-0.1))/0.1
    else:
      if runsummary[self.run].kind != "c" and runsummary[self.run].kind != "h":
        raise Exception

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
u1runs["apr03"] = setup_runs(1, 125119, 125127)
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

data = {}
for un in (u1runs, u2runs, u3runs):
  for s in un:
    for r in un[s]:
      print "arun", r
      data[r] = ARun(r)
for r in data:
  if runsummary[r].res == 1:
    print "u1", r
    data[r].getfval()
for r in data:
  if runsummary[r].res == 2:
    print "u2", r
    data[r].getfval()
for r in data:
  if runsummary[r].res == 3:
    print "u3", r
    data[r].getfval()

# x = []
# y = []
# dy = []
# for r in data:
#   if runsummary[r].res == 1:
#     x.append(data[r].en + data[r].shift)
#     y.append(data[r].had/data[r].bb - data[r].func)
#     dy.append(data[r].had/data[r].bb*sqrt((data[r].had_err/data[r].had)**2 + (data[r].bb_err/data[r].bb)**2))
# p = biggles.FramedPlot()
# p.add(biggles.Points(x, y, symboltype="filled circle", symbolsize=0.5))
# p.add(biggles.SymmetricErrorBarsY(x, y, dy))
# p.show()

histneg = hist.h1(20, -4, 4)
histpos = hist.h1(20, -4, 4)
histpeak = hist.h1(20, -4, 4)
histcont = hist.h1(20, -4, 4)
histtail = hist.h1(20, -4, 4)
profile = hist.prof(20, -4, 4)
x = []
y = []
for r in data:
  crosssec = data[r].had/data[r].bb
  crosssec_err = crosssec*sqrt((data[r].had_err/data[r].had)**2 + (data[r].bb_err/data[r].bb)**2)
  pull = (crosssec - data[r].func)/crosssec_err
  x.append(data[r].deriv)
  y.append(pull**2)
  profile.fill(x[-1], y[-1])
  if x[-1] < -1:
    histneg.fill(pull)
  if x[-1] > 1:
    histpos.fill(pull)
  if -0.1 < x[-1] < 0.1 and runsummary[r].kind == "p":
    histpeak.fill(pull)
  if -0.1 < x[-1] < 0.1 and runsummary[r].kind == "c":
    histcont.fill(pull)
  if -0.1 < x[-1] < 0.1 and runsummary[r].kind == "h":
    histtail.fill(pull)
p = biggles.FramedPlot()
p.add(biggles.Points(x, y, symboltype="filled circle", symbolsize=0.5))
p.y1.range = 0, 10
p.y1.label = r"Contribution to $\chi^2$"
p.x1.label = r"Function derivative (nb/MeV)"
p.show()
p.write_eps("residualntuple_1.eps")

profile.update()
x = profile.frame + (profile.high - profile.frame[-1])/2.
y = profile.vals
dy = profile.errs
p = biggles.FramedPlot()
p.add(biggles.Points(x, y, symboltype="filled circle", symbolsize=0.5))
p.add(biggles.SymmetricErrorBarsY(x, y, dy))
p.y1.range = 0, 5
p.y1.label = r"Contribution to $\chi^2$"
p.x1.label = r"Function derivative (nb/MeV)"
p.show()
p.write_eps("residualntuple_2.eps")

histneg.rootn()
histpos.rootn()
histpeak.rootn()
histcont.rootn()
histtail.rootn()

p = (histneg / histneg.sum()).plot()
p.add((histpos / histpos.sum()).steps(linecolor="red"))
p.add((histpeak / histpeak.sum()).steps(linecolor="blue"))
p.add((histcont / histcont.sum()).steps(linecolor="green"))
p.add((histtail / histtail.sum()).steps(linecolor="purple"))
p.add((histneg / histneg.sum()).errorbars())
p.add((histpos / histpos.sum()).errorbars(linecolor="red"))
p.add((histpeak / histpeak.sum()).errorbars(linecolor="blue"))
p.add((histcont / histcont.sum()).errorbars(linecolor="green"))
p.add((histtail / histtail.sum()).errorbars(linecolor="purple"))
p.x1.range = 5, 30
p.y1.range = 0, 0.4
p.x1.label = r"Pull distributions of different types of datasets"
p.show()
p.write_eps("residualntuple_3.eps")

x = []
y = []
profile = hist.prof(20, 5, 30)
for r in data:
  crosssec = data[r].had/data[r].bb
  crosssec_err = crosssec*sqrt((data[r].had_err/data[r].had)**2 + (data[r].bb_err/data[r].bb)**2)
  x.append(crosssec)
  y.append((crosssec - data[r].func)**2/crosssec_err**2)
  profile.fill(x[-1], y[-1])
p = biggles.FramedPlot()
p.add(biggles.Points(x, y, symboltype="filled circle", symbolsize=0.5))
p.x1.range = 5, 30
p.y1.label = r"Contribution to $\chi^2$"
p.x1.label = r"Absolute cross-section (nb)"
p.show()
p.write_eps("residualntuple_4.eps")

profile.update()
x = profile.frame + (profile.high - profile.frame[-1])/2.
y = profile.vals
dy = profile.errs
p = biggles.FramedPlot()
p.add(biggles.Points(x, y, symboltype="filled circle", symbolsize=0.5))
p.add(biggles.SymmetricErrorBarsY(x, y, dy))
p.x1.range = 5, 30
p.y1.range = 0, 5
p.y1.label = r"Contribution to $\chi^2$"
p.x1.label = r"Absolute cross-section (nb)"
p.show()
p.write_eps("residualntuple_5.eps")

x = []
y = []
dy = []
for r in data:
  ratio = data[r].bb/data[r].gg
  ratio_err = ratio*sqrt((data[r].bb_err/data[r].bb)**2 + (data[r].gg_err/data[r].gg)**2)
  x.append(data[r].had/data[r].bb)
  y.append(ratio)
  dy.append(ratio_err)
p = biggles.FramedPlot()
p.add(biggles.Points(x, y, symboltype="filled circle", symbolsize=0.5))
p.add(biggles.SymmetricErrorBarsY(x, y, dy))
p.add(biggles.LineY(1.))
p.x1.range = 5, 30
p.y1.label = r"Bhabha luminosity / gamgam luminosity"
p.x1.label = r"Absolute cross-section (nb)"
p.show()
p.write_eps("residualntuple_6.eps")

x = []
y = []
profile = hist.prof(20, 5, 30)
for r in data:
  ratio = data[r].bb/data[r].gg
  ratio_err = ratio*sqrt((data[r].bb_err/data[r].bb)**2 + (data[r].gg_err/data[r].gg)**2)
  x.append(data[r].had/data[r].bb)
  y.append((ratio-1)/ratio_err)
  profile.fill(x[-1], y[-1])
p = biggles.FramedPlot()
p.add(biggles.Points(x, y, symboltype="filled circle", symbolsize=0.5))
p.add(biggles.LineY(0.))
p.x1.range = 5, 30
p.y1.label = r"BB/GG sigmas"
p.x1.label = r"Absolute cross-section (nb)"
p.show()
p.write_eps("residualntuple_7.eps")

profile.update()
x = profile.frame + (profile.high - profile.frame[-1])/2.
y = profile.vals
dy = profile.errs
p = biggles.FramedPlot()
p.add(biggles.Points(x, y, symboltype="filled circle", symbolsize=0.5))
p.add(biggles.SymmetricErrorBarsY(x, y, dy))
p.add(biggles.LineY(0.))
p.x1.range = 5, 30
p.y1.range = -3, 3
p.y1.label = r"BB/GG sigmas"
p.x1.label = r"Absolute cross-section (nb)"
p.show()
p.write_eps("residualntuple_8.eps")

offres = []
on1 = []
on2 = []
on3 = []
off1 = []
off2 = []
off3 = []
for r in data:
  ratio = data[r].bb/data[r].gg
  ratio_err = ratio*sqrt((data[r].bb_err/data[r].bb)**2 + (data[r].gg_err/data[r].gg)**2)
  if runsummary[r].kind == "c":
    offres.append((ratio, ratio_err))
    if runsummary[r].res == 1:
      off1.append((ratio, ratio_err))
    elif runsummary[r].res == 2:
      off2.append((ratio, ratio_err))
    elif runsummary[r].res == 3:
      off3.append((ratio, ratio_err))
  elif runsummary[r].kind == "s" and runsummary[r].res == 1:
    on1.append((ratio, ratio_err))
  elif runsummary[r].kind == "s" and runsummary[r].res == 2:
    on2.append((ratio, ratio_err))
  elif runsummary[r].kind == "s" and runsummary[r].res == 3:
    on3.append((ratio, ratio_err))

print jt.wmean(offres)
print jt.wmean(on1)
print jt.wmean(on2)
print jt.wmean(on3)
print jt.wmean(off1)
print jt.wmean(off2)
print jt.wmean(off3)
