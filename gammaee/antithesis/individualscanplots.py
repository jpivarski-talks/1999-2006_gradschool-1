fitrecord = pickle.load(open("/home/mccann/antithesis/fit_results/novemberfits_noapr03_3_1.0.p"))

def u1plot(area, rmsbeam, back, jan16, jan30, feb06, feb13, feb20, feb27, mar06, mar13, apr08, apr09, apr10, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, rjan, rfeb, rapr2, which, p):
  adddata(p, u1data["cont"], 0.)
  adddata(p, u1data["high"], 0.)
  adddata(p, u1data[which], eval(which))
  if which in ["jan16", "jan30", "feb06", "feb13", "feb20"]:
    addfunc(p, lambda w: u1func(area, rjan, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, w), 9420., 9580.)
  if which in ["feb27", "mar06", "mar13"]:
    addfunc(p, lambda w: u1func(area, rfeb, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, w), 9420., 9580.)
  if which in ["apr08", "apr09", "apr10"]:
    addfunc(p, lambda w: u1func(area, rapr2, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, w), 9420., 9580.)
  p.add(biggles.PlotLabel(0.8, 0.85, which))
area, rmsbeam, back, jan16, jan30, feb06, feb13, feb20, feb27, mar06, mar13, apr08, apr09, apr10, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, rjan, rfeb, rapr2 = fitrecord[1].values
p = biggles.FramedArray(6,2)
u1plot(area, rmsbeam, back, jan16, jan30, feb06, feb13, feb20, feb27, mar06, mar13, apr08, apr09, apr10, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, rjan, rfeb, rapr2, "jan16", p[0,0])
u1plot(area, rmsbeam, back, jan16, jan30, feb06, feb13, feb20, feb27, mar06, mar13, apr08, apr09, apr10, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, rjan, rfeb, rapr2, "jan30", p[1,0])
u1plot(area, rmsbeam, back, jan16, jan30, feb06, feb13, feb20, feb27, mar06, mar13, apr08, apr09, apr10, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, rjan, rfeb, rapr2, "feb06", p[2,0])
u1plot(area, rmsbeam, back, jan16, jan30, feb06, feb13, feb20, feb27, mar06, mar13, apr08, apr09, apr10, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, rjan, rfeb, rapr2, "feb13", p[3,0])
u1plot(area, rmsbeam, back, jan16, jan30, feb06, feb13, feb20, feb27, mar06, mar13, apr08, apr09, apr10, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, rjan, rfeb, rapr2, "feb20", p[4,0])
u1plot(area, rmsbeam, back, jan16, jan30, feb06, feb13, feb20, feb27, mar06, mar13, apr08, apr09, apr10, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, rjan, rfeb, rapr2, "feb27", p[5,0])
u1plot(area, rmsbeam, back, jan16, jan30, feb06, feb13, feb20, feb27, mar06, mar13, apr08, apr09, apr10, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, rjan, rfeb, rapr2, "mar06", p[0,1])
u1plot(area, rmsbeam, back, jan16, jan30, feb06, feb13, feb20, feb27, mar06, mar13, apr08, apr09, apr10, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, rjan, rfeb, rapr2, "mar13", p[1,1])
u1plot(area, rmsbeam, back, jan16, jan30, feb06, feb13, feb20, feb27, mar06, mar13, apr08, apr09, apr10, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, rjan, rfeb, rapr2, "apr08", p[2,1])
u1plot(area, rmsbeam, back, jan16, jan30, feb06, feb13, feb20, feb27, mar06, mar13, apr08, apr09, apr10, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, rjan, rfeb, rapr2, "apr09", p[3,1])
u1plot(area, rmsbeam, back, jan16, jan30, feb06, feb13, feb20, feb27, mar06, mar13, apr08, apr09, apr10, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, rjan, rfeb, rapr2, "apr10", p[4,1])
p.aspect_ratio = 1.5
p.xrange = 9440., 9489.
p.yrange = 0., 29.
p.xlabel = r"$E_{CM}$ (MeV)"
p.ylabel = r"Selected Events / nb$^{-1}$"
p.show()
p.write_eps("/home/mccann/thesis/newplots/allscans1s.eps")

def u2plot(area, rmsbeam, back, may29, jun11, jun12, jul10, jul24, aug07, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, which, p):
  adddata(p, u2data["cont"], 0.)
  adddata(p, u2data["high"], 0.)
  adddata(p, u2data[which], eval(which))
  addfunc(p, lambda w: u2func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, w), 9980., 10100.)
  p.add(biggles.PlotLabel(0.8, 0.85, which))
area, rmsbeam, back, may29, jun11, jun12, jul10, jul24, aug07, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area = fitrecord[2].values
p = biggles.FramedArray(3,2)
u2plot(area, rmsbeam, back, may29, jun11, jun12, jul10, jul24, aug07, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, "may29", p[0,0])
u2plot(area, rmsbeam, back, may29, jun11, jun12, jul10, jul24, aug07, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, "jun11", p[1,0])
u2plot(area, rmsbeam, back, may29, jun11, jun12, jul10, jul24, aug07, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, "jun12", p[2,0])
u2plot(area, rmsbeam, back, may29, jun11, jun12, jul10, jul24, aug07, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, "jul10", p[0,1])
u2plot(area, rmsbeam, back, may29, jun11, jun12, jul10, jul24, aug07, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, "jul24", p[1,1])
u2plot(area, rmsbeam, back, may29, jun11, jun12, jul10, jul24, aug07, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, "aug07", p[2,1])
p.aspect_ratio = 1.5
p.xrange = 10000., 10050.
p.yrange = 0., 17.
p.xlabel = r"$E_{CM}$ (MeV)"
p.ylabel = r"Selected Events / nb$^{-1}$"
p.show()
p.write_eps("/home/mccann/thesis/newplots/allscans2s.eps")

def u3plot(area, rmsbeam, back, nov28, dec05, dec12, dec19, dec26, jan02, jan09, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area, rnov28, rdec05, rdec12, rdec19, rdec26, rjan02, rjan09, which, p):
  adddata(p, u3data["cont"], 0.)
  adddata(p, u3data["high"], 0.)
  adddata(p, u3data[which], eval(which))
  addfunc(p, lambda w: u3func(area, eval("r"+which), back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area, w), 10320., 10420.)
  p.add(biggles.PlotLabel(0.8, 0.85, which))
area, rmsbeam, back, nov28, dec05, dec12, dec19, dec26, jan02, jan09, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area, rnov28, rdec05, rdec12, rdec19, rdec26, rjan02, rjan09 = fitrecord[3].values
p = biggles.FramedArray(4,2)
u3plot(area, rmsbeam, back, nov28, dec05, dec12, dec19, dec26, jan02, jan09, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area, rnov28, rdec05, rdec12, rdec19, rdec26, rjan02, rjan09, "nov28", p[0,0])
u3plot(area, rmsbeam, back, nov28, dec05, dec12, dec19, dec26, jan02, jan09, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area, rnov28, rdec05, rdec12, rdec19, rdec26, rjan02, rjan09, "dec05", p[1,0])
u3plot(area, rmsbeam, back, nov28, dec05, dec12, dec19, dec26, jan02, jan09, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area, rnov28, rdec05, rdec12, rdec19, rdec26, rjan02, rjan09, "dec12", p[2,0])
u3plot(area, rmsbeam, back, nov28, dec05, dec12, dec19, dec26, jan02, jan09, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area, rnov28, rdec05, rdec12, rdec19, rdec26, rjan02, rjan09, "dec19", p[3,0])
u3plot(area, rmsbeam, back, nov28, dec05, dec12, dec19, dec26, jan02, jan09, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area, rnov28, rdec05, rdec12, rdec19, rdec26, rjan02, rjan09, "dec26", p[0,1])
u3plot(area, rmsbeam, back, nov28, dec05, dec12, dec19, dec26, jan02, jan09, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area, rnov28, rdec05, rdec12, rdec19, rdec26, rjan02, rjan09, "jan02", p[1,1])
u3plot(area, rmsbeam, back, nov28, dec05, dec12, dec19, dec26, jan02, jan09, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area, rnov28, rdec05, rdec12, rdec19, rdec26, rjan02, rjan09, "jan09", p[2,1])
p.xrange = 10335., 10389.
p.yrange = 0., 13.
p.aspect_ratio = 1.5
p.xlabel = r"$E_{CM}$ (MeV)"
p.ylabel = r"Selected Events / nb$^{-1}$"
p.show()
p.write_eps("/home/mccann/thesis/newplots/allscans3s.eps")

def get_runs(runs, lumisource=0):
  g = 0.
  h = 0.
  e = 0.
  p = 0.
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
        if whichweek in ["apr08", "apr09", "apr10"]: thisrmsbeam = myrapr2
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

  average_energy = wesum / wsum

  ebkgnd = 1. * (ebeam.hadroncool - 1.*nobeam.hadroncool*ebeam.cosmic/nobeam.cosmic) * e / ebeam.beamgase
  pbkgnd = 1. * (pbeam.hadroncool - 1.*nobeam.hadroncool*pbeam.cosmic/nobeam.cosmic) * p / pbeam.beamgasp
  cbkgnd = 1. * nobeam.hadroncool * c / nobeam.cosmic

  hadrons = h - ebkgnd/2. - pbkgnd/2. - cbkgnd
  hadrons_err = sqrt(h + c * (1.*nobeam.hadroncool/nobeam.cosmic)**2 + ebkgnd/2. + pbkgnd/2.)

  if lumisource == 3:
    if whichres == 1:
      cs = 1. / g / average_energy**2 * 199.5   # these differences are due to different efficiencies, as predicted by the MC
    elif whichres == 2:
      cs = 1. / g / average_energy**2 * 197.4   # and verified by my lumi counts
    elif whichres == 3:
      cs = 1. / g / average_energy**2 * 196.0   # (I totally believe this.)

    cs_err = cs * sqrt((1.*hadrons_err / hadrons)**2 + 1./g)

  else:
    cs = 1. / g / average_energy**2 * nbish2nb
    cs_err = cs * sqrt((1.*hadrons_err / hadrons)**2 + 1./g)

    if lumisource == 1:
      cs /= 0.23684
      cs_err /= 0.23684

    if lumisource == 2:
      cs /= 0.118999
      cs_err /= 0.118999

  return 1./cs



jan16 & 123164--123178 & Jan 15--16, 2002 \\
jan30 & 123596--123645 & Jan 30--Feb  1, 2002 \\
feb06 & 123781--123836 & Feb  6--8, 2002 \\
feb13 & 124080--124092 & Feb 19--20, 2002 \\
feb20 & 124102--124159 & Feb 20--22, 2002 \\
feb27 & 124279--124338 & Feb 27--Mar  1, 2002 \\
mar06 & 124436--124495 & Mar  6--8, 2002 \\
mar13 & 124625--124681 & Mar 13--15, 2002 \\
apr08 & 125254--125262 & Apr  8--9, 2002 \\
apr09 & 125285--125295 & Apr  9--10, 2002 \\
apr10 & 125303--125358 & Apr 10--12, 2002 \\
high-energy tail point & 124960--124973 & Mar 27--28, 2002 \\
may29 & 126449--126508 & May 29--31, 2002 \\
jun11 & 126776--126783 & Jun 11--12, 2002 \\
jun12 & 126814--126871 & Jun 12--14, 2002 \\
jul10 & 127588--127615 & Jul 10--11, 2002 \\
jul24 & 127924--127933 & Jul 23--24, 2002 \\
aug07 & 128303--128316 & Aug  7--8, 2002 \\
high-energy tail point & 127206--127219 & Jun 26--27, 2002 \\
nov28 & 121884--121940 & Nov 28--30, 2001 \\
dec05 & 122069--122126 & Dec  6--8, 2001 \\
dec12 & 122245--122298 & Dec 12--14, 2001 \\
dec19 & 122409--122452 & Dec 19--22, 2001 \\
jan02 & 122766--122821 & Jan  2--4, 2002 \\
jan09 & 122993--123044 & Jan  9--11, 2002 \\
high-energy tail point & 122568--122575 & Dec 26--26, 2001 \\


["jan16", "jan30", "feb06", "feb13", "feb20", "feb27", "mar06", "mar13", "apr08", "apr09", "apr10", "high"]

["may29", "jun11", "jun12", "jul10", "jul24", "aug07", "high"]

["nov28", "dec05", "dec12", "dec19", "jan02", "jan09", "high"]
