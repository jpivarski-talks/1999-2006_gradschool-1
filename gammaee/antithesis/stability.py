# This is based on bhabhafits.py

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

nbish2nb = 23.0481

class FitRecord: pass
ggfits = pickle.load(open("/home/mccann/antithesis/fit_results/bhabhafits_0.p"))

def run_date(r):
  if r in runstart and r in runend:
    return (runstart[r] + runend[r])/2.
  elif r in runstart:
    return runstart[r]
  elif r in runend:
    return runend[r]
  elif r == 130630:
    return run_date(130629)
  else:
    raise Exception, r

# The 48-hour limit is built into setup_runs
def setup_runs(res, low, high, scanassoc=True):
  beginning = run_date(low)

  tmpruns = []
  for r in initialrunlist:
    if r not in mybadruns and low <= r <= high and runsummary[r].res == res:
      if runsummary[r].kind == 's' or runsummary[r].kind == 'p':
        if scanassoc and run_date(r) < beginning + 48.*60.*60:
          tmpruns.append(r)
        if not scanassoc and run_date(r) >= beginning + 48.*60.*60:
          tmpruns.append(r)
  return tmpruns

def setup_data(runs, lumisource=0):
  tmpdata = []
  for r in runs:
    tmpdata.append(get_runs([r], lumisource=lumisource))
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
  tmp += area * 0.9757 * mygbwkf(9460.30, fullgam, rmsbeam, yint, phi, w)
  tmp += area * 0.578 * btautau * mygbwkftau(9460.30, fullgam, rmsbeam, tauyint, tauphi, w)
  tmp += back * (1.-twophofrac) * 9000.**2 / w**2
  tmp += back * twophofrac * log(w**2/9000.**2)
  return tmp

def u2func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, w):
  tmp = 0.
  tmp += area * 0.9582 * mygbwkf(10023.26, fullgam, rmsbeam, yint, phi, w)
  tmp += area * 0.578 * btautau * mygbwkftau(10023.26, fullgam, rmsbeam, tauyint, tauphi, w)
  tmp += back * (1.-twophofrac) * 9000.**2 / w**2
  tmp += back * twophofrac * log(w**2/9000.**2)
  tmp += u1area * mygbwkf(9460.30, 0., 0., 0., 0., w)
  return tmp

def u3func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area, w):
  tmp = 0.
  tmp += area * 0.9605 * mygbwkf(10355.2, fullgam, rmsbeam, yint, phi, w)
  tmp += area * 0.578 * btautau * mygbwkftau(10355.2, fullgam, rmsbeam, tauyint, tauphi, w)
  tmp += back * (1.-twophofrac) * 9000.**2 / w**2
  tmp += back * twophofrac * log(w**2/9000.**2)
  tmp += u1area * mygbwkf(9460.30, 0., 0., 0., 0., w)
  tmp += u2area * mygbwkf(10023.26, 0., 0., 0., 0., w)
  return tmp

def u1func_bkgndonly(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, w):
  tmp = 0.
  tmp += area * 0.578 * btautau * mygbwkftau(9460.30, fullgam, rmsbeam, tauyint, tauphi, w)
  tmp += back * (1.-twophofrac) * 9000.**2 / w**2
  tmp += back * twophofrac * log(w**2/9000.**2)
  return tmp

def u2func_bkgndonly(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, w):
  tmp = 0.
  tmp += area * 0.578 * btautau * mygbwkftau(10023.26, fullgam, rmsbeam, tauyint, tauphi, w)
  tmp += back * (1.-twophofrac) * 9000.**2 / w**2
  tmp += back * twophofrac * log(w**2/9000.**2)
  tmp += u1area * mygbwkf(9460.30, 0., 0., 0., 0., w)
  return tmp

def u3func_bkgndonly(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area, w):
  tmp = 0.
  tmp += area * 0.578 * btautau * mygbwkftau(10355.2, fullgam, rmsbeam, tauyint, tauphi, w)
  tmp += back * (1.-twophofrac) * 9000.**2 / w**2
  tmp += back * twophofrac * log(w**2/9000.**2)
  tmp += u1area * mygbwkf(9460.30, 0., 0., 0., 0., w)
  tmp += u2area * mygbwkf(10023.26, 0., 0., 0., 0., w)
  return tmp

def fakeallthree(area1, area2, area3, back, twophofrac, w):
  tmp = 0.
  tmp += back * (1.-twophofrac) * 9000.**2 / w**2
  tmp += back * twophofrac * log(w**2/9000.**2)
  if w > 9460.30+20.:
    tmp += area1 * 0.076 / (w - 9460.30)
  if w > 10023.26+10.:
    tmp += area2 * 0.076 / (w - 10023.26)
  if w > 10355.2+10.:
    tmp += area3 * 0.076 / (w - 10355.2)
  return tmp

def doallthree(back, twophofrac, w):
  tmp = 0.
  tmp += back * (1.-twophofrac) * 9000.**2 / w**2
  tmp += back * twophofrac * log(w**2/9000.**2)
  if w > 9460.30-8.:
    tmp += u1func(nbish2nb * 13.706441397531357, 3.7860955817996218, 0., 0.053, 0.018, 0.0, 0.0267, 0.2, 0.0, twophofrac, w)
  if w > 10023.26-8.:
    tmp += u2func(nbish2nb * 5.5910940385520558, 4.172051740847075, 0., 0.043, 0.018, 0.0, 0.017, 0.2, 0.0, twophofrac, 0., w)
  if w > 10355.2-8.:
    tmp += u3func(nbish2nb * 3.5871224559944799, 4.4739422571161098, 0., 0.0263, 0.018, 0.0, 0.0239, 0.2, 0., twophofrac, 0., 0., w)
  return tmp

def get_runs(runs, lumisource=0):
  g = 0
  h = 0
  e = 0
  p = 0
  c = 0
  wsum = 0.
  wesum = 0.
  for r in runs:
    therun = getdb(r)
    ngg = therun.gamgam
    if r in mycarefulscan: ngg = therun.gamgam_vstime.sum(0.,0.99)
    wsum += float(ngg)
    wesum += float(ngg) * runsummary[r].energy
#    print "    run", r, "energy =", runsummary[r].energy, "gamgams =", ngg

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
          if runsummary[r].res == 1:
            myarea, myrmsbeam, myback, myjan16, myjan30, myfeb06, myfeb13, myfeb20, myfeb27, mymar06, mymar13, myapr03, myapr08, myapr09, myapr10, myfullgam, myyint, myphi, mybtautau, mytauyint, mytauphi, mytwophofrac = ggfits[1].values
            # e+e- cross-section = hadronic area / (1 - 3 Bmm) * Bmm * inner range
            eecs = myarea * mygbwkf(9460.30, myfullgam, myrmsbeam, myyint, myphi, 2000.*runsummary[r].energy) / 0.9253 * 0.0249 * 0.672/2.66667
            # convert to a number of Upsilon --> e+e- and subtract from g (total inner e+e-)
            g -= eecs * float(therun.gamgam) * runsummary[r].energy**2 / nbish2nb

          if runsummary[r].res == 2:
            myarea, myrmsbeam, myback, mymay29, myjun11, myjun12, myjul10, myjul24, myaug07, myfullgam, myyint, myphi, mybtautau, mytauyint, mytauphi, mytwophofrac, myu1area = ggfits[2].values
            # e+e- cross-section = hadronic area / (1 - 3 Bmm) * Bmm * inner range
            eecs = myarea * mygbwkf(10023.26, myfullgam, myrmsbeam, myyint, myphi, 2000.*runsummary[r].energy) / 0.9391 * 0.0203 * 0.672/2.6667
            # convert to a number of Upsilon --> e+e- and subtract from g (total inner e+e-)
            g -= eecs * float(therun.gamgam) * runsummary[r].energy**2 / nbish2nb

          if runsummary[r].res == 3:
            myarea, myrmsbeam, myback, mynov28, mydec05, mydec12, mydec19, mydec26, myjan02, myjan09, myfullgam, myyint, myphi, mybtautau, mytauyint, mytauphi, mytwophofrac, myu1area, myu2area = ggfits[3].values
            # e+e- cross-section = hadronic area / (1 - 3 Bmm) * Bmm * inner range
            eecs = myarea * mygbwkf(10355.2, myfullgam, myrmsbeam, myyint, myphi, 2000.*runsummary[r].energy) / 0.9283 * 0.0239 * 0.672/2.6667
            # convert to a number of Upsilon --> e+e- and subtract from g (total inner e+e-)
            g -= eecs * float(therun.gamgam) * runsummary[r].energy**2 / nbish2nb

      elif lumisource == 2:
        g += therun.bhabha_cosp.sum(0.6, 0.8) * therun.bhabha_vstime.sum(0.,0.99) / therun.bhabha

        if runsummary[r].kind != 'c':
          if runsummary[r].res == 1:
            myarea, myrmsbeam, myback, myjan16, myjan30, myfeb06, myfeb13, myfeb20, myfeb27, mymar06, mymar13, myapr03, myapr08, myapr09, myapr10, myfullgam, myyint, myphi, mybtautau, mytauyint, mytauphi, mytwophofrac = ggfits[1].values
            # e+e- cross-section = hadronic area / (1 - 3 Bmm) * Bmm * outer range
            eecs = myarea * mygbwkf(9460.30, myfullgam, myrmsbeam, myyint, myphi, 2000.*runsummary[r].energy) / 0.9253 * 0.0249 * 0.298667/2.66667
            # convert to a number of Upsilon --> e+e- and subtract from g (total inner e+e-)
            g -= eecs * float(therun.gamgam) * runsummary[r].energy**2 / nbish2nb

          if runsummary[r].res == 2:
            myarea, myrmsbeam, myback, mymay29, myjun11, myjun12, myjul10, myjul24, myaug07, myfullgam, myyint, myphi, mybtautau, mytauyint, mytauphi, mytwophofrac, myu1area = ggfits[2].values
            # e+e- cross-section = hadronic area / (1 - 3 Bmm) * Bmm * outer range
            eecs = myarea * mygbwkf(10023.26, myfullgam, myrmsbeam, myyint, myphi, 2000.*runsummary[r].energy) / 0.9391 * 0.0203 * 0.298667/2.6667
            # convert to a number of Upsilon --> e+e- and subtract from g (total inner e+e-)
            g -= eecs * float(therun.gamgam) * runsummary[r].energy**2 / nbish2nb

          if runsummary[r].res == 3:
            myarea, myrmsbeam, myback, mynov28, mydec05, mydec12, mydec19, mydec26, myjan02, myjan09, myfullgam, myyint, myphi, mybtautau, mytauyint, mytauphi, mytwophofrac, myu1area, myu2area = ggfits[3].values
            # e+e- cross-section = hadronic area / (1 - 3 Bmm) * Bmm * outer range
            eecs = myarea * mygbwkf(10355.2, myfullgam, myrmsbeam, myyint, myphi, 2000.*runsummary[r].energy) / 0.9283 * 0.0239 * 0.298667/2.6667
            # convert to a number of Upsilon --> e+e- and subtract from g (total inner e+e-)
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
          if runsummary[r].res == 1:
            myarea, myrmsbeam, myback, myjan16, myjan30, myfeb06, myfeb13, myfeb20, myfeb27, mymar06, mymar13, myapr03, myapr08, myapr09, myapr10, myfullgam, myyint, myphi, mybtautau, mytauyint, mytauphi, mytwophofrac = ggfits[1].values
            # e+e- cross-section = hadronic area / (1 - 3 Bmm) * Bmm * inner range
            eecs = myarea * mygbwkf(9460.30, myfullgam, myrmsbeam, myyint, myphi, 2000.*runsummary[r].energy) / 0.9253 * 0.0249 * 0.672/2.66667
            # convert to a number of Upsilon --> e+e- and subtract from g (total inner e+e-)
            g -= eecs * float(therun.gamgam) * runsummary[r].energy**2 / nbish2nb

          if runsummary[r].res == 2:
            myarea, myrmsbeam, myback, mymay29, myjun11, myjun12, myjul10, myjul24, myaug07, myfullgam, myyint, myphi, mybtautau, mytauyint, mytauphi, mytwophofrac, myu1area = ggfits[2].values
            # e+e- cross-section = hadronic area / (1 - 3 Bmm) * Bmm * inner range
            eecs = myarea * mygbwkf(10023.26, myfullgam, myrmsbeam, myyint, myphi, 2000.*runsummary[r].energy) / 0.9391 * 0.0203 * 0.672/2.6667
            # convert to a number of Upsilon --> e+e- and subtract from g (total inner e+e-)
            g -= eecs * float(therun.gamgam) * runsummary[r].energy**2 / nbish2nb

          if runsummary[r].res == 3:
            myarea, myrmsbeam, myback, mynov28, mydec05, mydec12, mydec19, mydec26, myjan02, myjan09, myfullgam, myyint, myphi, mybtautau, mytauyint, mytauphi, mytwophofrac, myu1area, myu2area = ggfits[3].values
            # e+e- cross-section = hadronic area / (1 - 3 Bmm) * Bmm * inner range
            eecs = myarea * mygbwkf(10355.2, myfullgam, myrmsbeam, myyint, myphi, 2000.*runsummary[r].energy) / 0.9283 * 0.0239 * 0.672/2.6667
            # convert to a number of Upsilon --> e+e- and subtract from g (total inner e+e-)
            g -= eecs * float(therun.gamgam) * runsummary[r].energy**2 / nbish2nb

      elif lumisource == 2:
        g += therun.bhabha_cosp.sum(0.6, 0.8)

        if runsummary[r].kind != 'c':
          if runsummary[r].res == 1:
            myarea, myrmsbeam, myback, myjan16, myjan30, myfeb06, myfeb13, myfeb20, myfeb27, mymar06, mymar13, myapr03, myapr08, myapr09, myapr10, myfullgam, myyint, myphi, mybtautau, mytauyint, mytauphi, mytwophofrac = ggfits[1].values
            # e+e- cross-section = hadronic area / (1 - 3 Bmm) * Bmm * outer range
            eecs = myarea * mygbwkf(9460.30, myfullgam, myrmsbeam, myyint, myphi, 2000.*runsummary[r].energy) / 0.9253 * 0.0249 * 0.298667/2.66667
            # convert to a number of Upsilon --> e+e- and subtract from g (total inner e+e-)
            g -= eecs * float(therun.gamgam) * runsummary[r].energy**2 / nbish2nb

          if runsummary[r].res == 2:
            myarea, myrmsbeam, myback, mymay29, myjun11, myjun12, myjul10, myjul24, myaug07, myfullgam, myyint, myphi, mybtautau, mytauyint, mytauphi, mytwophofrac, myu1area = ggfits[2].values
            # e+e- cross-section = hadronic area / (1 - 3 Bmm) * Bmm * outer range
            eecs = myarea * mygbwkf(10023.26, myfullgam, myrmsbeam, myyint, myphi, 2000.*runsummary[r].energy) / 0.9391 * 0.0203 * 0.298667/2.6667
            # convert to a number of Upsilon --> e+e- and subtract from g (total inner e+e-)
            g -= eecs * float(therun.gamgam) * runsummary[r].energy**2 / nbish2nb

          if runsummary[r].res == 3:
            myarea, myrmsbeam, myback, mynov28, mydec05, mydec12, mydec19, mydec26, myjan02, myjan09, myfullgam, myyint, myphi, mybtautau, mytauyint, mytauphi, mytwophofrac, myu1area, myu2area = ggfits[3].values
            # e+e- cross-section = hadronic area / (1 - 3 Bmm) * Bmm * outer range
            eecs = myarea * mygbwkf(10355.2, myfullgam, myrmsbeam, myyint, myphi, 2000.*runsummary[r].energy) / 0.9283 * 0.0239 * 0.298667/2.6667
            # convert to a number of Upsilon --> e+e- and subtract from g (total inner e+e-)
            g -= eecs * float(therun.gamgam) * runsummary[r].energy**2 / nbish2nb

  average_energy = wesum / wsum
#  print "  Average energy is", average_energy

  ebkgnd = 1. * (ebeam.hadroncool - 1.*nobeam.hadroncool*ebeam.cosmic/nobeam.cosmic) * e / ebeam.beamgase
  pbkgnd = 1. * (pbeam.hadroncool - 1.*nobeam.hadroncool*pbeam.cosmic/nobeam.cosmic) * p / pbeam.beamgasp
  cbkgnd = 1. * nobeam.hadroncool * c / nobeam.cosmic

  hadrons = h - ebkgnd/2. - pbkgnd/2. - cbkgnd
  hadrons_err = sqrt(h + c * (1.*nobeam.hadroncool/nobeam.cosmic)**2 + ebkgnd/2. + pbkgnd/2.)
#  print "  Corrected number of hadrons is", hadrons, "+/-", hadrons_err
#  print "  Number of gamgams is", g

  cs = hadrons / g / average_energy**2 * nbish2nb

  cs_err = cs * sqrt((1.*hadrons_err / hadrons)**2 + 1./g)
#  print "  Hadronic cross-section is", cs, "+/-", cs_err

  if lumisource == 1:
    cs /= 0.23684
    cs_err /= 0.23684

  if lumisource == 2:
    cs /= 0.118999
    cs_err /= 0.118999

  return average_energy, cs, cs_err

############################################################################

# lumisource = 1
# u1runs = []
# u2runs = []
# u3runs = []
# u1cont = []
# u2cont = []
# u3cont = []
# u1cont_err = []
# u2cont_err = []
# u3cont_err = []
# for r in initialrunlist:
#   if r not in mybadruns:
#     if runsummary[r].res == 1 and runsummary[r].kind == 'c':
#       u1runs.append(r)
#       energy, cs, cserr = get_runs([r], lumisource=lumisource)
#       u1cont.append(cs)
#       u1cont_err.append(cserr)
#     if runsummary[r].res == 2 and runsummary[r].kind == 'c':
#       u2runs.append(r)
#       energy, cs, cserr = get_runs([r], lumisource=lumisource)
#       u2cont.append(cs)
#       u2cont_err.append(cserr)
#     if runsummary[r].res == 3 and runsummary[r].kind == 'c':
#       u3runs.append(r)
#       energy, cs, cserr = get_runs([r], lumisource=lumisource)
#       u3cont.append(cs)
#       u3cont_err.append(cserr)

# mean1 = jt.wmean(zip(u1cont, u1cont_err))[0]
# mean2 = jt.wmean(zip(u2cont, u2cont_err))[0]
# mean3 = jt.wmean(zip(u3cont, u3cont_err))[0]

# def L(x):
#   loglike = 0.
#   for c, e in zip(u1cont, u1cont_err):
#     loglike -= log( exp(-(c-mean1)**2/2./(e**2+x**2)) / sqrt(2.*pi*(e**2+x**2)) )
#   for c, e in zip(u2cont, u2cont_err):
#     loglike -= log( exp(-(c-mean2)**2/2./(e**2+x**2)) / sqrt(2.*pi*(e**2+x**2)) )
#   for c, e in zip(u3cont, u3cont_err):
#     loglike -= log( exp(-(c-mean3)**2/2./(e**2+x**2)) / sqrt(2.*pi*(e**2+x**2)) )
#   return loglike

# p = biggles.FramedPlot()
# x = Numeric.arange(0., 0.04, 0.001)
# y = Numeric.arange(0., 0.04, 0.001)
# for i, xi in enumerate(x): y[i] = L(xi)
# p.add(biggles.Curve(x, y))
# p.show()

# m = Minuit(L, start=[0.025], up=0.5)
# m.migrad()
# print m.values[0]
# m.minos(0)
# print m.minos_errors[0]

# h = hist.h1(100, 0., 0.5)
# h.fill(u1cont_err)
# h.fill(u2cont_err)
# h.fill(u3cont_err)
# h.plot().show()

############################################################################

for lumisource in (0,1,2):
  u1runs = []
  u2runs = []
  u3runs = []
  u1cont = []
  u2cont = []
  u3cont = []
  u1cont_err = []
  u2cont_err = []
  u3cont_err = []
  for r in initialrunlist:
    if r not in mybadruns:
      if runsummary[r].res == 1 and runsummary[r].kind == 'c':
        u1runs.append(r)
        energy, cs, cserr = get_runs([r], lumisource=lumisource)
        u1cont.append(cs)
        u1cont_err.append(cserr)
      if runsummary[r].res == 2 and runsummary[r].kind == 'c':
        u2runs.append(r)
        energy, cs, cserr = get_runs([r], lumisource=lumisource)
        u2cont.append(cs)
        u2cont_err.append(cserr)
      if runsummary[r].res == 3 and runsummary[r].kind == 'c':
        u3runs.append(r)
        energy, cs, cserr = get_runs([r], lumisource=lumisource)
        u3cont.append(cs)
        u3cont_err.append(cserr)

  mean1 = jt.wmean(zip(u1cont, u1cont_err))[0]
  mean2 = jt.wmean(zip(u2cont, u2cont_err))[0]
  mean3 = jt.wmean(zip(u3cont, u3cont_err))[0]

  xxx = map(run_date, u1runs + u2runs + u3runs)
  yyy = list(Numeric.array(u1cont)-mean1) + \
      list(Numeric.array(u2cont)-mean2) + \
      list(Numeric.array(u3cont)-mean3)
  yyyerr = u1cont_err + u2cont_err + u3cont_err

  p = biggles.FramedPlot()
  p.add(biggles.Points(xxx, yyy, symboltype="filled circle", size=0.7))
  p.add(biggles.SymmetricErrorBarsY(xxx, yyy, yyyerr))
  p.add(biggles.LineY(0.))
  p.x1.range = min(xxx)-14.*24.*60.*60., max(xxx)+14.*24.*60.*60.
  p.y1.range = -2., 2.
#  p.show()

  dticks = []
  dlabels = []
  for y in (2001, 2002):
    for m in Numeric.array(range(12))+1:
      for d in [1,]:
        dticks.append(time.mktime(time.strptime("%02d %02d %4d" % (m, d, y), "%m %d %Y")))
  for y in (2001, 2002):
    for m in ("", "Feb", "", "Apr", "", "Jun", "", "Aug", "", "Oct", "", "Dec"):
      for d in [1,]:
        dlabels.append("%s" % (m))
  dsubticks = []
  for y in (2001, 2002):
    for d in Numeric.array(range(365))+1:
      if d % 7 == 0:
        dsubticks.append(time.mktime(time.strptime("%03d %4d" % (d, y), "%j %Y")))
  subticks = []
  sublabels = []
  for t, l in zip(dticks, dlabels):
    if min(xxx)-14.*24.*60.*60. < t < max(xxx)+14.*24.*60.*60.:
      subticks.append(t)
      sublabels.append(l)
  subsubticks = []
  for t in dsubticks:
    if min(xxx)-14.*24.*60.*60. < t < max(xxx)+14.*24.*60.*60.:
      subsubticks.append(t)
  p.x1.ticks = subticks
  p.x1.subticks = subsubticks
  p.x1.ticklabels = sublabels
  p.x2.ticks = subticks
  p.x2.subticks = subsubticks
  p.x2.draw_ticklabels = 0

  p.y1.label = r"$\sigma - \langle\sigma\rangle$ in nb"
  p.x1.label = "Date in 2001-2002"
#  p.show()

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
    return m.values[0], err0, m.values[1], err1, lambda x: 0.1*len(h.data)*gauss(m.values[0], m.values[1], x)

  h = MoreThanHist(100, -5., 5.)
  h.fill(map(lambda (c,cerr): c/cerr, zip(yyy, yyyerr)))
  mean, meanerr, width, widtherr, f = dofitgauss(h)
  x = Numeric.arange(-5., 5., 0.01)
  y = Numeric.arange(-5., 5., 0.01)
  for i, xi in enumerate(x): y[i] = f(xi)

  q = h.plot()
  q.add(biggles.Curve(x,y, linewidth=3.5, color="red"))
  entries = h.sum() + h.underflow() + h.overflow()
  hist.addinfobox(q, [["entries", entries], ["mean", r"%4.2f $\pm$ %4.2f" % (mean, abs(meanerr))], ["width", r"%4.2f $\pm$ %4.2f" % (abs(width), abs(widtherr))]], width=0.5, colwidth=0.07)
  q.x1.label = r"Pull"
#  q.show()

  r = biggles.Table(1,2)
  p.aspect_ratio = 1.
  q.aspect_ratio = 1.
  r[0,0] = p
  r[0,1] = q
  r.aspect_ratio = 5./11.
#  r.show()
  r.write_eps("/home/mccann/antithesis/plots/stability_cont_"+str(lumisource)+".eps")

  u1runs = {}
  u2runs = {}
  u3runs = {}
  u1runslate = {}
  u2runslate = {}
  u3runslate = {}
  u1data = {}
  u2data = {}
  u3data = {}
  u1datalate = {}
  u2datalate = {}
  u3datalate = {}

  u1runs["jan16"] = setup_runs(1, 123164, 123178, scanassoc=True)
  u1runs["jan30"] = setup_runs(1, 123596, 123718, scanassoc=True)
  u1runs["feb06"] = setup_runs(1, 123781, 123893, scanassoc=True)
  u1runs["feb13"] = setup_runs(1, 124080, 124092, scanassoc=True)
  u1runs["feb20"] = setup_runs(1, 124102, 124214, scanassoc=True)
  u1runs["feb27"] = setup_runs(1, 124279, 124394, scanassoc=True)
  u1runs["mar06"] = setup_runs(1, 124436, 124519, scanassoc=True)
  u1runs["mar13"] = setup_runs(1, 124625, 124736, scanassoc=True)
  u1runs["apr03"] = setup_runs(1, 125119, 125127, scanassoc=True)
  u1runs["apr08"] = setup_runs(1, 125254, 125262, scanassoc=True)
  u1runs["apr09"] = setup_runs(1, 125285, 125295, scanassoc=True)
  u1runs["apr10"] = setup_runs(1, 125303, 125416, scanassoc=True)

  u2runs["may29"] = setup_runs(2, 126449, 126568, scanassoc=True)
  u2runs["jun11"] = setup_runs(2, 126776, 126783, scanassoc=True)
  u2runs["jun12"] = setup_runs(2, 126814, 126915, scanassoc=True)
  u2runs["jul10"] = setup_runs(2, 127588, 127615, scanassoc=True)
  u2runs["jul24"] = setup_runs(2, 127924, 127933, scanassoc=True)
  u2runs["aug07"] = setup_runs(2, 128303, 128316, scanassoc=True)

  u3runs["nov28"] = setup_runs(3, 121884, 122007, scanassoc=True)
  u3runs["dec05"] = setup_runs(3, 122069, 122178, scanassoc=True)
  u3runs["dec12"] = setup_runs(3, 122245, 122326, scanassoc=True)
  u3runs["dec19"] = setup_runs(3, 122409, 122527, scanassoc=True)
  u3runs["dec26"] = setup_runs(3, 122535, 122757, scanassoc=True)
  u3runs["jan02"] = setup_runs(3, 122766, 122881, scanassoc=True)
  u3runs["jan09"] = setup_runs(3, 122993, 123101, scanassoc=True)

  u1data["jan16"] = setup_data(u1runs["jan16"], lumisource=lumisource)
  u1data["jan30"] = setup_data(u1runs["jan30"], lumisource=lumisource)
  u1data["feb06"] = setup_data(u1runs["feb06"], lumisource=lumisource)
  u1data["feb13"] = setup_data(u1runs["feb13"], lumisource=lumisource)
  u1data["feb20"] = setup_data(u1runs["feb20"], lumisource=lumisource)
  u1data["feb27"] = setup_data(u1runs["feb27"], lumisource=lumisource)
  u1data["mar06"] = setup_data(u1runs["mar06"], lumisource=lumisource)
  u1data["mar13"] = setup_data(u1runs["mar13"], lumisource=lumisource)
  u1data["apr03"] = setup_data(u1runs["apr03"], lumisource=lumisource)
  u1data["apr08"] = setup_data(u1runs["apr08"], lumisource=lumisource)
  u1data["apr09"] = setup_data(u1runs["apr09"], lumisource=lumisource)
  u1data["apr10"] = setup_data(u1runs["apr10"], lumisource=lumisource)

  u2data["may29"] = setup_data(u2runs["may29"], lumisource=lumisource)
  u2data["jun11"] = setup_data(u2runs["jun11"], lumisource=lumisource)
  u2data["jun12"] = setup_data(u2runs["jun12"], lumisource=lumisource)
  u2data["jul10"] = setup_data(u2runs["jul10"], lumisource=lumisource)
  u2data["jul24"] = setup_data(u2runs["jul24"], lumisource=lumisource)
  u2data["aug07"] = setup_data(u2runs["aug07"], lumisource=lumisource)

  u3data["nov28"] = setup_data(u3runs["nov28"], lumisource=lumisource)
  u3data["dec05"] = setup_data(u3runs["dec05"], lumisource=lumisource)
  u3data["dec12"] = setup_data(u3runs["dec12"], lumisource=lumisource)
  u3data["dec19"] = setup_data(u3runs["dec19"], lumisource=lumisource)
  u3data["dec26"] = setup_data(u3runs["dec26"], lumisource=lumisource)
  u3data["jan02"] = setup_data(u3runs["jan02"], lumisource=lumisource)
  u3data["jan09"] = setup_data(u3runs["jan09"], lumisource=lumisource)

  u1runslate["jan16"] = setup_runs(1, 123164, 123178, scanassoc=False)
  u1runslate["jan30"] = setup_runs(1, 123596, 123718, scanassoc=False)
  u1runslate["feb06"] = setup_runs(1, 123781, 123893, scanassoc=False)
  u1runslate["feb13"] = setup_runs(1, 124080, 124092, scanassoc=False)
  u1runslate["feb20"] = setup_runs(1, 124102, 124214, scanassoc=False)
  u1runslate["feb27"] = setup_runs(1, 124279, 124394, scanassoc=False)
  u1runslate["mar06"] = setup_runs(1, 124436, 124519, scanassoc=False)
  u1runslate["mar13"] = setup_runs(1, 124625, 124736, scanassoc=False)
  u1runslate["apr03"] = setup_runs(1, 125119, 125127, scanassoc=False)
  u1runslate["apr08"] = setup_runs(1, 125254, 125262, scanassoc=False)
  u1runslate["apr09"] = setup_runs(1, 125285, 125295, scanassoc=False)
  u1runslate["apr10"] = setup_runs(1, 125303, 125416, scanassoc=False)

  u2runslate["may29"] = setup_runs(2, 126449, 126568, scanassoc=False)
  u2runslate["jun11"] = setup_runs(2, 126776, 126783, scanassoc=False)
  u2runslate["jun12"] = setup_runs(2, 126814, 126915, scanassoc=False)
  u2runslate["jul10"] = setup_runs(2, 127588, 127615, scanassoc=False)
  u2runslate["jul24"] = setup_runs(2, 127924, 127933, scanassoc=False)
  u2runslate["aug07"] = setup_runs(2, 128303, 128316, scanassoc=False)

  u3runslate["nov28"] = setup_runs(3, 121884, 122007, scanassoc=False)
  u3runslate["dec05"] = setup_runs(3, 122069, 122178, scanassoc=False)
  u3runslate["dec12"] = setup_runs(3, 122245, 122326, scanassoc=False)
  u3runslate["dec19"] = setup_runs(3, 122409, 122527, scanassoc=False)
  u3runslate["dec26"] = setup_runs(3, 122535, 122757, scanassoc=False)
  u3runslate["jan02"] = setup_runs(3, 122766, 122881, scanassoc=False)
  u3runslate["jan09"] = setup_runs(3, 122993, 123101, scanassoc=False)

  u1datalate["jan16"] = setup_data(u1runslate["jan16"], lumisource=lumisource)
  u1datalate["jan30"] = setup_data(u1runslate["jan30"], lumisource=lumisource)
  u1datalate["feb06"] = setup_data(u1runslate["feb06"], lumisource=lumisource)
  u1datalate["feb13"] = setup_data(u1runslate["feb13"], lumisource=lumisource)
  u1datalate["feb20"] = setup_data(u1runslate["feb20"], lumisource=lumisource)
  u1datalate["feb27"] = setup_data(u1runslate["feb27"], lumisource=lumisource)
  u1datalate["mar06"] = setup_data(u1runslate["mar06"], lumisource=lumisource)
  u1datalate["mar13"] = setup_data(u1runslate["mar13"], lumisource=lumisource)
  u1datalate["apr03"] = setup_data(u1runslate["apr03"], lumisource=lumisource)
  u1datalate["apr08"] = setup_data(u1runslate["apr08"], lumisource=lumisource)
  u1datalate["apr09"] = setup_data(u1runslate["apr09"], lumisource=lumisource)
  u1datalate["apr10"] = setup_data(u1runslate["apr10"], lumisource=lumisource)

  u2datalate["may29"] = setup_data(u2runslate["may29"], lumisource=lumisource)
  u2datalate["jun11"] = setup_data(u2runslate["jun11"], lumisource=lumisource)
  u2datalate["jun12"] = setup_data(u2runslate["jun12"], lumisource=lumisource)
  u2datalate["jul10"] = setup_data(u2runslate["jul10"], lumisource=lumisource)
  u2datalate["jul24"] = setup_data(u2runslate["jul24"], lumisource=lumisource)
  u2datalate["aug07"] = setup_data(u2runslate["aug07"], lumisource=lumisource)

  u3datalate["nov28"] = setup_data(u3runslate["nov28"], lumisource=lumisource)
  u3datalate["dec05"] = setup_data(u3runslate["dec05"], lumisource=lumisource)
  u3datalate["dec12"] = setup_data(u3runslate["dec12"], lumisource=lumisource)
  u3datalate["dec19"] = setup_data(u3runslate["dec19"], lumisource=lumisource)
  u3datalate["dec26"] = setup_data(u3runslate["dec26"], lumisource=lumisource)
  u3datalate["jan02"] = setup_data(u3runslate["jan02"], lumisource=lumisource)
  u3datalate["jan09"] = setup_data(u3runslate["jan09"], lumisource=lumisource)

  if lumisource == 0:
    jan16 =   0.240609780596
    jan30 =   0.532886153782
    feb06 =   0.233679169962
    feb13 =   0.054962722633
    feb20 =   0.160661818497
    feb27 =   0.112259329033
    mar06 =   0.219895304517
    mar13 =   0.568669674887
    apr03 =   0.904486221013
    apr08 =   0.786778708973
    apr09 =   0.445348165738
    apr10 =   0.747312963605
    may29 =  -1.03832488008 
    jun11 =  -1.07988239788 
    jun12 =  -1.51427193529 
    jul10 =  -0.770597225561
    jul24 =  -0.684404542801
    aug07 =  -0.392068578403
    nov28 =  -2.29937800587 
    dec05 =  -4.06130713092 
    dec12 =  -3.1797290744  
    dec19 =  -2.09955840481 
    dec26 =  -2.93022974685 
    jan02 =  -2.69223785972 
    jan09 =  -2.48164392013 
  elif lumisource == 1:
    jan16 = 0.43995128496   
    jan30 = 0.510453953796  
    feb06 = 0.0393865886958 
    feb13 = 0.121482561577  
    feb20 = 0.0716885100899 
    feb27 = 0.235279211218  
    mar06 = 0.341791380564  
    mar13 = 0.308639946732  
    apr03 = 0.871866303365  
    apr08 = 0.602604485207  
    apr09 = 0.539936165122  
    apr10 = 0.672894582578  
    may29 =  -1.26365295117 
    jun11 =  -1.14127837047 
    jun12 =  -0.928183450655
    jul10 =  -0.662023174224
    jul24 =  -0.755104492557
    aug07 =  -0.526232253623
    nov28 =  -3.08670276898 
    dec05 =  -3.79878701904 
    dec12 =  -2.94503610632 
    dec19 =  -2.73838291066 
    dec26 =  -2.68377418599 
    jan02 =  -2.69037693241 
    jan09 =  -2.72244222944 
  elif lumisource == 2:
    jan16 =   0.410525992227
    jan30 =   0.590806616192
    feb06 =   0.139542494039
    feb13 =   0.026978861675
    feb20 =   0.079383426176
    feb27 =   0.188389582564
    mar06 =   0.493238273524
    mar13 =   0.380525500344
    apr03 =   0.82378364456 
    apr08 =   0.600886301731
    apr09 =   0.646010701599
    apr10 =   0.704273160387
    may29 =  -1.18409437209 
    jun11 =  -1.07686130565 
    jun12 =  -1.03888275814 
    jul10 =  -0.81180137209 
    jul24 =  -0.687066343026
    aug07 =  -0.678196380356
    nov28 =  -3.26950954112 
    dec05 =  -3.81874447879 
    dec12 =  -2.69523715354 
    dec19 =  -2.74889362332 
    dec26 =  -2.66285796831 
    jan02 =  -2.70059556893 
    jan09 =  -2.90842427327 

  def makedata(res):
    if res == 1:
      return map(lambda (r, (en, c, e)): (r, en+jan16/2000., c, e), zip(u1runs["jan16"], u1data["jan16"])) + \
             map(lambda (r, (en, c, e)): (r, en+jan30/2000., c, e), zip(u1runs["jan30"], u1data["jan30"])) + \
             map(lambda (r, (en, c, e)): (r, en+feb06/2000., c, e), zip(u1runs["feb06"], u1data["feb06"])) + \
             map(lambda (r, (en, c, e)): (r, en+feb13/2000., c, e), zip(u1runs["feb13"], u1data["feb13"])) + \
             map(lambda (r, (en, c, e)): (r, en+feb20/2000., c, e), zip(u1runs["feb20"], u1data["feb20"])) + \
             map(lambda (r, (en, c, e)): (r, en+feb27/2000., c, e), zip(u1runs["feb27"], u1data["feb27"])) + \
             map(lambda (r, (en, c, e)): (r, en+mar06/2000., c, e), zip(u1runs["mar06"], u1data["mar06"])) + \
             map(lambda (r, (en, c, e)): (r, en+mar13/2000., c, e), zip(u1runs["mar13"], u1data["mar13"])) + \
             map(lambda (r, (en, c, e)): (r, en+apr03/2000., c, e), zip(u1runs["apr03"], u1data["apr03"])) + \
             map(lambda (r, (en, c, e)): (r, en+apr08/2000., c, e), zip(u1runs["apr08"], u1data["apr08"])) + \
             map(lambda (r, (en, c, e)): (r, en+apr09/2000., c, e), zip(u1runs["apr09"], u1data["apr09"])) + \
             map(lambda (r, (en, c, e)): (r, en+apr10/2000., c, e), zip(u1runs["apr10"], u1data["apr10"]))
    elif res == 2:
      return map(lambda (r, (en, c, e)): (r, en+may29/2000., c, e), zip(u2runs["may29"], u2data["may29"])) + \
             map(lambda (r, (en, c, e)): (r, en+jun11/2000., c, e), zip(u2runs["jun11"], u2data["jun11"])) + \
             map(lambda (r, (en, c, e)): (r, en+jun12/2000., c, e), zip(u2runs["jun12"], u2data["jun12"])) + \
             map(lambda (r, (en, c, e)): (r, en+jul10/2000., c, e), zip(u2runs["jul10"], u2data["jul10"])) + \
             map(lambda (r, (en, c, e)): (r, en+jul24/2000., c, e), zip(u2runs["jul24"], u2data["jul24"])) + \
             map(lambda (r, (en, c, e)): (r, en+aug07/2000., c, e), zip(u2runs["aug07"], u2data["aug07"]))
    elif res == 3:
      return map(lambda (r, (en, c, e)): (r, en+nov28/2000., c, e), zip(u3runs["nov28"], u3data["nov28"])) + \
             map(lambda (r, (en, c, e)): (r, en+dec05/2000., c, e), zip(u3runs["dec05"], u3data["dec05"])) + \
             map(lambda (r, (en, c, e)): (r, en+dec12/2000., c, e), zip(u3runs["dec12"], u3data["dec12"])) + \
             map(lambda (r, (en, c, e)): (r, en+dec19/2000., c, e), zip(u3runs["dec19"], u3data["dec19"])) + \
             map(lambda (r, (en, c, e)): (r, en+dec26/2000., c, e), zip(u3runs["dec26"], u3data["dec26"])) + \
             map(lambda (r, (en, c, e)): (r, en+jan02/2000., c, e), zip(u3runs["jan02"], u3data["jan02"])) + \
             map(lambda (r, (en, c, e)): (r, en+jan09/2000., c, e), zip(u3runs["jan09"], u3data["jan09"]))

  def makedatalate(res):
    if res == 1:
      return map(lambda (r, (en, c, e)): (r, en+jan16/2000., c, e), zip(u1runslate["jan16"], u1datalate["jan16"])) + \
             map(lambda (r, (en, c, e)): (r, en+jan30/2000., c, e), zip(u1runslate["jan30"], u1datalate["jan30"])) + \
             map(lambda (r, (en, c, e)): (r, en+feb06/2000., c, e), zip(u1runslate["feb06"], u1datalate["feb06"])) + \
             map(lambda (r, (en, c, e)): (r, en+feb13/2000., c, e), zip(u1runslate["feb13"], u1datalate["feb13"])) + \
             map(lambda (r, (en, c, e)): (r, en+feb20/2000., c, e), zip(u1runslate["feb20"], u1datalate["feb20"])) + \
             map(lambda (r, (en, c, e)): (r, en+feb27/2000., c, e), zip(u1runslate["feb27"], u1datalate["feb27"])) + \
             map(lambda (r, (en, c, e)): (r, en+mar06/2000., c, e), zip(u1runslate["mar06"], u1datalate["mar06"])) + \
             map(lambda (r, (en, c, e)): (r, en+mar13/2000., c, e), zip(u1runslate["mar13"], u1datalate["mar13"])) + \
             map(lambda (r, (en, c, e)): (r, en+apr03/2000., c, e), zip(u1runslate["apr03"], u1datalate["apr03"])) + \
             map(lambda (r, (en, c, e)): (r, en+apr08/2000., c, e), zip(u1runslate["apr08"], u1datalate["apr08"])) + \
             map(lambda (r, (en, c, e)): (r, en+apr09/2000., c, e), zip(u1runslate["apr09"], u1datalate["apr09"])) + \
             map(lambda (r, (en, c, e)): (r, en+apr10/2000., c, e), zip(u1runslate["apr10"], u1datalate["apr10"]))
    elif res == 2:
      return map(lambda (r, (en, c, e)): (r, en+may29/2000., c, e), zip(u2runslate["may29"], u2datalate["may29"])) + \
             map(lambda (r, (en, c, e)): (r, en+jun11/2000., c, e), zip(u2runslate["jun11"], u2datalate["jun11"])) + \
             map(lambda (r, (en, c, e)): (r, en+jun12/2000., c, e), zip(u2runslate["jun12"], u2datalate["jun12"])) + \
             map(lambda (r, (en, c, e)): (r, en+jul10/2000., c, e), zip(u2runslate["jul10"], u2datalate["jul10"])) + \
             map(lambda (r, (en, c, e)): (r, en+jul24/2000., c, e), zip(u2runslate["jul24"], u2datalate["jul24"])) + \
             map(lambda (r, (en, c, e)): (r, en+aug07/2000., c, e), zip(u2runslate["aug07"], u2datalate["aug07"]))
    elif res == 3:
      return map(lambda (r, (en, c, e)): (r, en+nov28/2000., c, e), zip(u3runslate["nov28"], u3datalate["nov28"])) + \
             map(lambda (r, (en, c, e)): (r, en+dec05/2000., c, e), zip(u3runslate["dec05"], u3datalate["dec05"])) + \
             map(lambda (r, (en, c, e)): (r, en+dec12/2000., c, e), zip(u3runslate["dec12"], u3datalate["dec12"])) + \
             map(lambda (r, (en, c, e)): (r, en+dec19/2000., c, e), zip(u3runslate["dec19"], u3datalate["dec19"])) + \
             map(lambda (r, (en, c, e)): (r, en+dec26/2000., c, e), zip(u3runslate["dec26"], u3datalate["dec26"])) + \
             map(lambda (r, (en, c, e)): (r, en+jan02/2000., c, e), zip(u3runslate["jan02"], u3datalate["jan02"])) + \
             map(lambda (r, (en, c, e)): (r, en+jan09/2000., c, e), zip(u3runslate["jan09"], u3datalate["jan09"]))

  def makedata2(res, peaky):
    if peaky == 'p':
      if res == 1:
        return filter(lambda (r, en, c, e): abs(en - 4.73019) < 0.0008, makedata(res))
      if res == 2:
        return filter(lambda (r, en, c, e): abs(en - 5.01285) < 0.0008, makedata(res))
      if res == 3:
        return filter(lambda (r, en, c, e): abs(en - 5.1792) < 0.0008, makedata(res))
    else:
      if res == 1:
        return filter(lambda (r, en, c, e): abs(en - 4.73019) >= 0.0008, makedata(res))
      if res == 2:
        return filter(lambda (r, en, c, e): abs(en - 5.01285) >= 0.0008, makedata(res))
      if res == 3:
        return filter(lambda (r, en, c, e): abs(en - 5.1792) >= 0.0008, makedata(res))
      
  def makeitright(runsdata):
    runs = []
    data = []
    for (r, en, c, e) in runsdata:
      runs.append(r)
      data.append((en, c, e))
    return (runs, data)

  def doitall((runs, data), fun, thelabel):
    shifty = hist.h1(100, -1., 1.)
    thewonderfuldata = map(lambda (en, c, e): (fun(en*2000.)-fun(en*2000.+0.07))/e, data)
    shifty.fill(thewonderfuldata)
    shiftyplot = shifty.plot()
    hist.addinfobox(shiftyplot, [["mean", r"%4.2f" % (jt.mean(thewonderfuldata),)], ["stdev", r"%4.2f" % (jt.stdev(thewonderfuldata),)]], width=0.5, colwidth=0.07)
    shiftyplot.write_eps("/home/mccann/antithesis/plots/stability_shiftupp_"+thelabel+"_"+str(lumisource)+".eps")

    shifty = hist.h1(100, -1., 1.)
    thewonderfuldata = map(lambda (en, c, e): (fun(en*2000.)-fun(en*2000.-0.07))/e, data)
    shifty.fill(thewonderfuldata)
    shiftyplot = shifty.plot()
    hist.addinfobox(shiftyplot, [["mean", r"%4.2f" % (jt.mean(thewonderfuldata),)], ["stdev", r"%4.2f" % (jt.stdev(thewonderfuldata),)]], width=0.5, colwidth=0.07)
    shiftyplot.write_eps("/home/mccann/antithesis/plots/stability_shiftdownp_"+thelabel+"_"+str(lumisource)+".eps")

    xxx = map(run_date, runs)
    yyy = map(lambda (en, c, e): c-fun(en*2000.), data)
    yyyerr = map(lambda (en, c, e): e, data)

    p = biggles.FramedPlot()
    p.add(biggles.Points(xxx, yyy, symboltype="filled circle", size=0.7))
    p.add(biggles.SymmetricErrorBarsY(xxx, yyy, yyyerr))
    p.add(biggles.LineY(0.))
    p.x1.range = min(xxx)-14.*24.*60.*60., max(xxx)+14.*24.*60.*60.
    p.y1.range = -2., 2.
#    p.show()

    dticks = []
    dlabels = []
    for y in (2001, 2002):
      for m in Numeric.array(range(12))+1:
        for d in [1,]:
          dticks.append(time.mktime(time.strptime("%02d %02d %4d" % (m, d, y), "%m %d %Y")))
    for y in (2001, 2002):
      for m in ("", "Feb", "", "Apr", "", "Jun", "", "Aug", "", "Oct", "", "Dec"):
        for d in [1,]:
          dlabels.append("%s" % (m))
    dsubticks = []
    for y in (2001, 2002):
      for d in Numeric.array(range(365))+1:
        if d % 7 == 0:
          dsubticks.append(time.mktime(time.strptime("%03d %4d" % (d, y), "%j %Y")))
    subticks = []
    sublabels = []
    for t, l in zip(dticks, dlabels):
      if min(xxx)-14.*24.*60.*60. < t < max(xxx)+14.*24.*60.*60.:
        subticks.append(t)
        sublabels.append(l)
    subsubticks = []
    for t in dsubticks:
      if min(xxx)-14.*24.*60.*60. < t < max(xxx)+14.*24.*60.*60.:
        subsubticks.append(t)
    p.x1.ticks = subticks
    p.x1.subticks = subsubticks
    p.x1.ticklabels = sublabels
    p.x2.ticks = subticks
    p.x2.subticks = subsubticks
    p.x2.draw_ticklabels = 0

    p.y1.label = r"$\sigma - \langle\sigma\rangle$ in nb"
    p.x1.label = "Date in 2001-2002"
#    p.show()

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

    def dofitgauss(h):
      def gauss(m, s, x): return exp(-(x-m)**2/2./s**2)/sqrt(2.*pi)/s
      def fitgauss(m,s):
        c = 0.
        for x in h.data:
          if abs(x-m) > 20.*s: raise Exception
          c += -log(gauss(m, s, x))
        return c
      m = Minuit(fitgauss, start=[0., 1.], up=0.5)
      try:
        m.migrad()
        m.minos([0,1])
        err0 = (m.minos_errors[0][1] - m.minos_errors[0][0])/2.
        err1 = (m.minos_errors[1][1] - m.minos_errors[1][0])/2.
        return m.values[0], err0, m.values[1], err1, lambda x: 0.1*len(h.data)*gauss(m.values[0], m.values[1], x)
      except Exception:
        return m.values[0], 1000., m.values[1], 1000., lambda x: 0.1*len(h.data)*gauss(m.values[0], m.values[1], x)

    h = MoreThanHist(100, -5., 5.)
    h.fill(map(lambda (c,cerr): c/cerr, zip(yyy, yyyerr)))
    mean, meanerr, width, widtherr, f = dofitgauss(h)
    x = Numeric.arange(-5., 5., 0.01)
    y = Numeric.arange(-5., 5., 0.01)
    for i, xi in enumerate(x): y[i] = f(xi)

    q = h.plot()
    q.add(biggles.Curve(x,y, linewidth=3.5, color="red"))
    entries = h.sum() + h.underflow() + h.overflow()
    hist.addinfobox(q, [["entries", entries], ["mean", r"%4.2f $\pm$ %4.2f" % (mean, abs(meanerr))], ["width", r"%4.2f $\pm$ %4.2f" % (abs(width), abs(widtherr))]], width=0.5, colwidth=0.07)
    q.x1.label = r"Pull"
#    q.show()

    r = biggles.Table(1,2)
    p.aspect_ratio = 1.
    q.aspect_ratio = 1.
    r[0,0] = p
    r[0,1] = q
    r.aspect_ratio = 5./11.
#    r.show()
    r.write_eps("/home/mccann/antithesis/plots/stability_"+thelabel+"_"+str(lumisource)+".eps")

#     for tmp in zip(["area", "rmsbeam", "back", "jan16", "jan30", "feb06", "feb13", "feb20", "feb27", "mar06", "mar13", "apr03", "apr08", "apr09", "apr10", "fullgam", "yint", "phi", "btautau", "tauyint", "tauphi", "twophofrac"], [13.7, 3.79, 0.404, 0.25, 0.63, 0.076, 0.066, 0.23, 0.19, 0.20, 0.57, 0.92, 0.80, 0.46, 0.62, 0.053, 0.01864, 0., 0.0267, 0.20, 0., 0.0792]): print tmp
#     for tmp in zip(["area", "rmsbeam", "back", "may29", "jun11", "jun12", "jul10", "jul24", "aug07", "fullgam", "yint", "phi", "btautau", "tauyint", "tauphi", "twophofrac", "u1area"], [5.72, 4.1758, 0.40496499767, -1.127, -1.065, -1.42, -0.76, -0.6656, -0.39747, 0.043, 0.01792, 0., 0.017, 0.37, 0., 0.0792, "u1fitter.values[0]"]): print tmp
#     for tmp in zip(["area", "rmsbeam", "back", "nov28", "dec05", "dec12", "dec19", "dec26", "jan02", "jan09", "fullgam", "yint", "phi", "btautau", "tauyint", "tauphi", "twophofrac", "u1area", "u2area"], [3.58, 4.48, 0.404, -2.12, -3.99, -3.18, -2.46, -2.72, -2.55, -2.64, 0.0263, 0.01823, 0., 0.0239, 0.27, 0., 0.0792, "u1fitter.values[0]", "u2fitter.values[0]"]): print tmp

  if lumisource == 0:
    area = 319.222190193
    rmsbeam = 3.77898332112
    back = 9.35245823819

    fullgam = 0.053
    yint = 0.01864
    phi = 0.0
    btautau = 0.0267
    tauyint = 0.2
    tauphi = 0.0
    twophofrac = 0.0792

    doitall(makeitright(makedata2(1, 'p')), lambda w: u1func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, w), "peak1")
    doitall(makeitright(makedata2(1, 's')), lambda w: u1func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, w), "scan1")
    doitall(makeitright(makedatalate(1)), lambda w: u1func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, w), "late1")

    area =  133.211507233
    rmsbeam = 4.16424969862
    back =    9.33118325362

    fullgam = 0.043
    yint = 0.01792
    phi = 0.0
    btautau = 0.017
    tauyint = 0.37
    tauphi = 0.0
    twophofrac = 0.0792
    u1area = 319.222190193

    doitall(makeitright(makedata2(2, 'p')), lambda w: u2func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, w), "peak2")
    doitall(makeitright(makedata2(2, 's')), lambda w: u2func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, w), "scan2")
    doitall(makeitright(makedatalate(2)), lambda w: u2func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, w), "late2")

    area =   84.9230277774
    rmsbeam = 4.50762704657
    back =    9.31502157956

    fullgam = 0.0263
    yint = 0.01823
    phi = 0.0
    btautau = 0.0239
    tauyint = 0.27
    tauphi = 0.0
    twophofrac = 0.0792
    u1area = 319.222190193
    u2area = 133.211507233

    doitall(makeitright(makedata2(3, 'p')), lambda w: u3func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area, w), "peak3")
    doitall(makeitright(makedata2(3, 's')), lambda w: u3func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area, w), "scan3")
    doitall(makeitright(makedatalate(3)), lambda w: u3func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area, w), "late3")

  if lumisource == 1:
    area = 324.10
    rmsbeam = 3.78826720511
    back = 9.35975830341

    fullgam = 0.053
    yint = 0.01864
    phi = 0.0
    btautau = 0.0267
    tauyint = 0.2
    tauphi = 0.0
    twophofrac = 0.0792

    doitall(makeitright(makedata2(1, 'p')), lambda w: u1func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, w), "peak1")
    doitall(makeitright(makedata2(1, 's')), lambda w: u1func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, w), "scan1")
    doitall(makeitright(makedatalate(1)), lambda w: u1func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, w), "late1")

    area = 134.243099282
    rmsbeam = 4.17627005891
    back = 9.32659148004

    fullgam = 0.043
    yint = 0.01792
    phi = 0.0
    btautau = 0.017
    tauyint = 0.37
    tauphi = 0.0
    twophofrac = 0.0792
    u1area = 324.10

    doitall(makeitright(makedata2(2, 'p')), lambda w: u2func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, w), "peak2")
    doitall(makeitright(makedata2(2, 's')), lambda w: u2func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, w), "scan2")
    doitall(makeitright(makedatalate(2)), lambda w: u2func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, w), "late2")

    area = 88.8178733524
    rmsbeam = 4.66319531916
    back = 9.32390764057

    fullgam = 0.0263
    yint = 0.01823
    phi = 0.0
    btautau = 0.0239
    tauyint = 0.27
    tauphi = 0.0
    twophofrac = 0.0792
    u1area = 324.10
    u2area = 134.243099282

    doitall(makeitright(makedata2(3, 'p')), lambda w: u3func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area, w), "peak3")
    doitall(makeitright(makedata2(3, 's')), lambda w: u3func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area, w), "scan3")
    doitall(makeitright(makedatalate(3)), lambda w: u3func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area, w), "late3")

  if lumisource == 2:
    area = 323.356
    rmsbeam = 3.81117299777
    back = 9.3570928174

    fullgam = 0.053
    yint = 0.01864
    phi = 0.0
    btautau = 0.0267
    tauyint = 0.2
    tauphi = 0.0
    twophofrac = 0.0792

    doitall(makeitright(makedata2(1, 'p')), lambda w: u1func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, w), "peak1")
    doitall(makeitright(makedata2(1, 's')), lambda w: u1func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, w), "scan1")
    doitall(makeitright(makedatalate(1)), lambda w: u1func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, w), "late1")

    area = 133.987969754
    rmsbeam = 4.16268441974
    back = 9.32466643979

    fullgam = 0.043
    yint = 0.01792
    phi = 0.0
    btautau = 0.017
    tauyint = 0.37
    tauphi = 0.0
    twophofrac = 0.0792
    u1area = 323.356

    doitall(makeitright(makedata2(2, 'p')), lambda w: u2func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, w), "peak2")
    doitall(makeitright(makedata2(2, 's')), lambda w: u2func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, w), "scan2")
    doitall(makeitright(makedatalate(2)), lambda w: u2func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, w), "late2")

    area = 87.81
    rmsbeam = 4.61586857163
    back = 9.33450635422

    fullgam = 0.0263
    yint = 0.01823
    phi = 0.0
    btautau = 0.0239
    tauyint = 0.27
    tauphi = 0.0
    twophofrac = 0.0792
    u1area = 323.356
    u2area = 133.987969754

    doitall(makeitright(makedata2(3, 'p')), lambda w: u3func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area, w), "peak3")
    doitall(makeitright(makedata2(3, 's')), lambda w: u3func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area, w), "scan3")
    doitall(makeitright(makedatalate(3)), lambda w: u3func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area, w), "late3")

############################################################################

from minuit import *
execfile("utilities.py")
runstart = pickle.load(open("old_dotps/runstart.p"))
runend = pickle.load(open("old_dotps/runend.p"))
import time

def setup_runs(low, high):
  tmpruns = []
  for r in initialrunlist:
    if r not in mybadruns and low <= r <= high:
      if runsummary[r].kind == 'p':
        tmpruns.append(r)
  return tmpruns

def run_date(r):
  if r in runstart and r in runend:
    return (runstart[r] + runend[r])/2.
  elif r in runstart:
    return runstart[r]
  elif r in runend:
    return runend[r]
  elif r == 130630:
    return run_date(130629)
  else:
    raise Exception, r

runs = {}
runs["jan16"] = setup_runs(123164, 123178)
runs["jan30"] = setup_runs(123596, 123718)
runs["feb06"] = setup_runs(123781, 123893)
runs["feb13"] = setup_runs(124080, 124092)
runs["feb20"] = setup_runs(124102, 124214)
runs["feb27"] = setup_runs(124279, 124394)
runs["mar06"] = setup_runs(124436, 124519)
runs["mar13"] = setup_runs(124625, 124736)
runs["apr03"] = setup_runs(125119, 125127)
runs["apr08"] = setup_runs(125254, 125262)
runs["apr09"] = setup_runs(125285, 125295)
runs["apr10"] = setup_runs(125303, 125416)

shift = {}
shift["jan16"] = 0.25
shift["jan30"] = 0.63
shift["feb06"] = 0.076
shift["feb13"] = 0.066
shift["feb20"] = 0.23
shift["feb27"] = 0.19
shift["mar06"] = 0.20
shift["mar13"] = 0.57
shift["apr03"] = 0.92
shift["apr08"] = 0.80
shift["apr09"] = 0.46
shift["apr10"] = 0.62

def histmean(h, low, high):
  halfspace = (h.frame[1] - h.frame[0])/2.
  thesum = 0.
  then = 0.
  for f, v in zip(h.frame, h.vals):
    if low < f + halfspace < high:
      thesum += (f + halfspace) * v
      then += v
  return thesum/then

def histmeanerr(h, mean, low, high):
  halfspace = (h.frame[1] - h.frame[0])/2.
  thesum2 = 0.
  then = 0.
  for f, v in zip(h.frame, h.vals):
    if low < f + halfspace < high:
      thesum2 += ((f + halfspace) - mean)**2 * v
      then += v
  return sqrt(thesum2/then) / sqrt(then)

rs = []
cosp = []
cosn = []
e2 = []
p2 = []
cosp_err = []
cosn_err = []
e2_err = []
p2_err = []
for scan in runs.keys():
  for r in runs[scan]:
    rs.append(r)

    therun = getdb(r)
    cosp.append(histmean(therun.bhabha_cosp, -0.8, 0.8))
    cosp_err.append(histmeanerr(therun.bhabha_cosp, cosp[-1], -0.8, 0.8))
    cosn.append(histmean(therun.bhabha_cosn, -0.8, 0.8))
    cosn_err.append(histmeanerr(therun.bhabha_cosn, cosn[-1], -0.8, 0.8))
    e2.append(histmean(therun.bhabha_e2, 0.4, 1.2) * (therun.ebeam*2000.+shift[scan])/(therun.ebeam*2000.))
    e2_err.append(histmeanerr(therun.bhabha_e2, e2[-1], 0.4, 1.2) * (therun.ebeam*2000.+shift[scan])/(therun.ebeam*2000.))
    p2.append(histmean(therun.bhabha_p2, 0.4, 1.2) * (therun.ebeam*2000.+shift[scan])/(therun.ebeam*2000.))
    p2_err.append(histmeanerr(therun.bhabha_p2, p2[-1], 0.4, 1.2) * (therun.ebeam*2000.+shift[scan])/(therun.ebeam*2000.))
#     e2.append(histmean(therun.bhabha_e2, 0.4, 1.2))
#     e2_err.append(histmeanerr(therun.bhabha_e2, e2[-1], 0.4, 1.2))
#     p2.append(histmean(therun.bhabha_p2, 0.4, 1.2))
#     p2_err.append(histmeanerr(therun.bhabha_p2, p2[-1], 0.4, 1.2))

p = biggles.FramedPlot()
p.add(biggles.Points(rs, cosp, type="filled circle", size=0.8))
p.add(biggles.SymmetricErrorBarsY(rs, cosp, cosp_err))
p.show()
p = biggles.FramedPlot()
p.add(biggles.Points(rs, cosn, type="filled circle", size=0.8))
p.add(biggles.SymmetricErrorBarsY(rs, cosn, cosn_err))
p.show()

# for r, cp in zip(rs, cosp):
#   if cp > 0.6:
#     print r
# for r, cn in zip(rs, cosn):
#   if cn < -0.6:
#     print r

h1 = getdb(125340).bhabha_cosp
h2 = (getdb(125342).bhabha_cosp * (getdb(125340).bhabha_cosp.sum(0.6, 0.8)/getdb(125342).bhabha_cosp.sum(0.6, 0.8)))
p = h1.plot()
p.add(h2.points())
p.add(h2.errorbars())
p.show()
p = (h1 - h1).plot()
p.add((h2 - h1).points())
p.add((h2 - h1).errorbars())
p.yrange = -300, 300
p.show()

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
  return m.values[0], err0, m.values[1], err1, lambda x: 0.1*len(h.data)*gauss(m.values[0], m.values[1], x)

wmean = jt.wmean(zip(cosp, cosp_err))[0]
h = MoreThanHist(100, -5, 5)
h.fill(map(lambda (d, e): (d-wmean)/e, zip(cosp, cosp_err)))
mean, meanerr, width, widtherr, f = dofitgauss(h)
x = Numeric.arange(-5., 5., 0.01)
y = Numeric.arange(-5., 5., 0.01)
for i, xi in enumerate(x): y[i] = f(xi)
p = h.plot()
p.add(biggles.Curve(x,y, linewidth=3.5, color="red"))
p.show()
print width, widtherr

p = biggles.FramedPlot()
p.add(biggles.Points(rs, e2, type="filled circle", size=0.8))
p.add(biggles.SymmetricErrorBarsY(rs, e2, e2_err))
p.show()

p = biggles.FramedPlot()
p.add(biggles.Points(rs, p2, type="filled circle", size=0.8))
p.add(biggles.SymmetricErrorBarsY(rs, p2, p2_err))
p.show()

wmean = jt.wmean(zip(p2, p2_err))[0]
h = MoreThanHist(100, -5, 5)
h.fill(map(lambda (d, e): (d-wmean)/e, zip(p2, p2_err)))
mean, meanerr, width, widtherr, f = dofitgauss(h)
x = Numeric.arange(-5., 5., 0.01)
y = Numeric.arange(-5., 5., 0.01)
for i, xi in enumerate(x): y[i] = f(xi)
p = h.plot()
p.add(biggles.Curve(x,y, linewidth=3.5, color="red"))
p.show()
print width, widtherr

lows = getdb(121899).bhabha_e2 - getdb(121899).bhabha_e2
highs = getdb(121899).bhabha_e2 - getdb(121899).bhabha_e2
for r, e in zip(rs, e2):
  if e < 0.955 and r > 124500:
    lows += getdb(r).bhabha_e2
  if r > 125000:
    highs += getdb(r).bhabha_e2

h1 = lows + 0.00001
h2 = highs * highs.sum(0.4, 1.2) / lows.sum(0.4, 1.2) + 0.00001
p = h1.plot()
p.add(h2.points())
p.add(h2.errorbars())
p.yrange = 1, 1000000
p.y.log = 1
p.show()

contr = []
conte2 = []
conte2_err = []
for r in initialrunlist:
  if r not in mybadruns and runsummary[r].kind == 'c':
    therun = getdb(r)
    contr.append(r)
    conte2.append(histmean(therun.bhabha_e2, 0.4, 1.2))
    conte2_err.append(histmeanerr(therun.bhabha_e2, conte2[-1], 0.4, 1.2))

p = biggles.FramedPlot()
p.add(biggles.Points(contr, conte2, type="filled circle", size=0.8))
p.add(biggles.SymmetricErrorBarsY(contr, conte2, conte2_err))
p.show()
