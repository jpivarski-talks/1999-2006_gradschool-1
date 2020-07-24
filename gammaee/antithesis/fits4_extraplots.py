# First get the data and all the functions that come before them.

# fitrecord = pickle.load(open("/home/mccann/antithesis/fit_results/final.p"))
p = biggles.Table(3,1)
p[0,0] = u1plot(*fitrecord[1].values)
p[0,0].aspect_ratio = 0.33
p[0,0].add(biggles.PlotLabel(0.1,0.8,"(a)"))
p[0,0].y1.label = r"Hadronic cross-section in nb"
p[0,0].x1.label = r"Center-of-mass energy (2 $\times$ beam energy) in MeV"
p[1,0] = u2plot(*fitrecord[2].values)
p[1,0].aspect_ratio = 0.33
p[1,0].add(biggles.PlotLabel(0.1,0.8,"(b)"))
p[1,0].y1.label = r"Hadronic cross-section in nb"
p[1,0].x1.label = r"Center-of-mass energy (2 $\times$ beam energy) in MeV"
p[2,0] = u3plot(*fitrecord[3].values)
p[2,0].aspect_ratio = 0.33
p[2,0].add(biggles.PlotLabel(0.1,0.8,"(c)"))
p[2,0].y1.label = r"Hadronic cross-section in nb"
p[2,0].x1.label = r"Center-of-mass energy (2 $\times$ beam energy) in MeV"
p.aspect_ratio = 1.2
p.write_eps("/home/mccann/antithesis/fit_results/final_allfit.eps")

#############################################

def adddata2(data, shift, x, y, yerr):
  for (e, h, herr) in data:
    x.append(e*2000.+shift)
    y.append(h)
    yerr.append(herr)
  return None

def u1plot2(area, rmsbeam, back, jan16, jan30, feb06, feb13, feb20, feb27, mar06, mar13, apr03, apr08, apr09, apr10, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, p=None, GeV=False):
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
  adddata2(u1data["apr03"], apr03, x, y, yerr)
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
    addfunc(p, lambda w: u1func_bkgndonly(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, w), 9450., 9580., points=1000., linetype="dashed")
  else:
    addfunc(p, lambda w: u1func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, w*1000.), 9.420, 9.580, points=1000.)
    addfunc(p, lambda w: u1func_bkgndonly(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, w*1000.), 9.450, 9.580, points=1000., linetype="dashed")
  p.xrange = 9420., 9580.
  if GeV: p.xrange = tuple(Numeric.array(p.xrange) / 1000.)
  p.yrange = 0., 1.5 * nbish2nb
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
    addfunc(p, lambda w: u2func_bkgndonly(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, w), 10010., 10100., points=1000., linetype="dashed")
  else:
    addfunc(p, lambda w: u2func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, w*1000.), 9.980, 10.100, points=1000.)
    addfunc(p, lambda w: u2func_bkgndonly(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, w*1000.), 10.010, 10.100, points=1000., linetype="dashed")
  p.xrange = 9980., 10100.
  if GeV: p.xrange = tuple(Numeric.array(p.xrange) / 1000.)
  p.yrange = 0., 0.8 * nbish2nb
  p.aspect_ratio = 1.2
  return p

def u3plot2(area, rmsbeam, back, nov28, dec05, dec12, dec19, dec26, jan02, jan09, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area, p=None, GeV=False):
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
    addfunc(p, lambda w: u3func_bkgndonly(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area, w), 10340., 10420., points=1000., linetype="dashed")
  else:
    addfunc(p, lambda w: u3func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area, w*1000.), 10.320, 10.420, points=1000.)
    addfunc(p, lambda w: u3func_bkgndonly(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area, w*1000.), 10.340, 10.420, points=1000., linetype="dashed")
  p.xrange = 10320., 10420.
  if GeV: p.xrange = tuple(Numeric.array(p.xrange) / 1000.)
  p.yrange = 0., 0.7 * nbish2nb
  p.aspect_ratio = 1.2
  return p

def u1plot3(area, rmsbeam, back, jan16, jan30, feb06, feb13, feb20, feb27, mar06, mar13, apr03, apr08, apr09, apr10, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, p=None, GeV=False):
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
  adddata2(u1data["apr03"], apr03, x, y, yerr)
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
  p.yrange = 0., 1.5 * nbish2nb
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
  p.yrange = 0., 0.8 * nbish2nb
  p.aspect_ratio = 1.2
  return p

def u3plot3(area, rmsbeam, back, nov28, dec05, dec12, dec19, dec26, jan02, jan09, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area, p=None, GeV=False):
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
  p.yrange = 0., 0.7 * nbish2nb
  p.aspect_ratio = 1.2
  return p

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
p1.show()

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
p2.show()

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
p3.show()

# qq = biggles.Table(1,3)
# qq[0,0] = p1
# qq[0,1] = p2
# qq[0,2] = p3
# qq.aspect_ratio = 0.4
# qq.show()

p1.write_eps("/home/mccann/antithesis/plots/individual_noinset_1s.eps")
p2.write_eps("/home/mccann/antithesis/plots/individual_noinset_2s.eps")
p3.write_eps("/home/mccann/antithesis/plots/individual_noinset_3s.eps")

thep1_inset = biggles.DataInset((9540., 20.), (9580., 10.), p1_inset)
p1.add(thep1_inset)
thep2_inset = biggles.DataInset((10070., 10.), (10100., 15.), p2_inset)
p2.add(thep2_inset)
thep3_inset = biggles.DataInset((10390., 9.), (10410., 12.), p3_inset)
p3.add(thep3_inset)

p1.write_eps("/home/mccann/antithesis/plots/individual_withinset_1s.eps")
p2.write_eps("/home/mccann/antithesis/plots/individual_withinset_2s.eps")
p3.write_eps("/home/mccann/antithesis/plots/individual_withinset_3s.eps")

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
p1.show()

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
p2.show()

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
p3.show()

# qq = biggles.Table(1,3)
# qq[0,0] = p1
# qq[0,1] = p2
# qq[0,2] = p3
# qq.aspect_ratio = 0.4
# qq.show()

p1.write_eps("/home/mccann/antithesis/plots/individual0.7_noinset_1s.eps")
p2.write_eps("/home/mccann/antithesis/plots/individual0.7_noinset_2s.eps")
p3.write_eps("/home/mccann/antithesis/plots/individual0.7_noinset_3s.eps")

thep1_inset = biggles.DataInset((9540., 20.), (9580., 10.), p1_inset)
p1.add(thep1_inset)
thep2_inset = biggles.DataInset((10070., 10.), (10100., 15.), p2_inset)
p2.add(thep2_inset)
thep3_inset = biggles.DataInset((10390., 9.), (10410., 12.), p3_inset)
p3.add(thep3_inset)

p1.write_eps("/home/mccann/antithesis/plots/individual0.7_withinset_1s.eps")
p2.write_eps("/home/mccann/antithesis/plots/individual0.7_withinset_2s.eps")
p3.write_eps("/home/mccann/antithesis/plots/individual0.7_withinset_3s.eps")

####################

p1 = u1plot2(*fitrecord[1].values)
p2 = u2plot2(*fitrecord[2].values)
p3 = u3plot2(*fitrecord[3].values)

p1.y1.range = 0., 30.
p1.x.ticks = range(9420, 9580+20, 20)
p1.x.subticks = range(9420, 9580, 5)
p1.x1.label = r"Center-of-mass energy (2 $\times$ beam energy) in MeV"
p1.y1.label = "Hadronic cross-section in nb"

p2.x.ticks = range(9980, 10100+20, 20)
p2.x.subticks = range(9980, 10100, 5)
p2.y1.range = 0., 18.
p2.x1.label = r"Center-of-mass energy (2 $\times$ beam energy) in MeV"
p2.y1.label = "Hadronic cross-section in nb"

p3.y1.range = 0., 14.
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
p.show()
p.write_eps("/home/mccann/antithesis/fit_results/final_allfit_comb2.eps")

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
p[0,0].y1.range = 0., 30.
p[1,0].y1.range = 0., 18.
p[2,0].y1.range = 0., 16.
p[0,0].y.ticks = range(0, 31, 5)
p[1,0].y.ticks = range(0, 19, 5)
p[2,0].y.ticks = range(0, 17, 5)
p[0,0].y.subticks = range(0, 31)
p[1,0].y.subticks = range(0, 19)
p[2,0].y.subticks = range(0, 17)
p[0,0].y2.draw_ticklabels = 0
p[1,0].y2.draw_ticklabels = 0
p[2,0].y2.draw_ticklabels = 0
p.show()
p.write_eps("/home/mccann/antithesis/fit_results/final_allfit_comb3.eps")





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
p[0,0].y1.range = 0., 35.
p[1,0].y1.range = 0., 20.
p[2,0].y1.range = 0., 15.
p.aspect_ratio = 1.2
p.show()
p.write_eps("/home/mccann/antithesis/fit_results/final_allfit_comb.eps")






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
q2[0,0].add(biggles.PlotLabel(0.69, 0.18-0.01, r"$\Gamma_{ee}$ = 1.336", texthalign="right", fontsize=5.))
q2[0,0].add(biggles.PlotLabel(0.32, 0.14-0.02, r"$\pm$ 0.009", texthalign="left", fontsize=5.))
q2[0,0].add(biggles.PlotLabel(0.32, 0.10-0.03, r"$\pm$ 0.019 keV", texthalign="left", fontsize=5.))
q2[0,1].add(biggles.PlotLabel(0.69, 0.18-0.01, r"$\Gamma_{ee}$ = 0.616", texthalign="right", fontsize=5.))
q2[0,1].add(biggles.PlotLabel(0.32, 0.14-0.02, r"$\pm$ 0.010", texthalign="left", fontsize=5.))
q2[0,1].add(biggles.PlotLabel(0.32, 0.10-0.03, r"$\pm$ 0.009 keV", texthalign="left", fontsize=5.))
q2[0,2].add(biggles.PlotLabel(0.69, 0.18-0.01, r"$\Gamma_{ee}$ = 0.425", texthalign="right", fontsize=5.))
q2[0,2].add(biggles.PlotLabel(0.32, 0.14-0.02, r"$\pm$ 0.009", texthalign="left", fontsize=5.))
q2[0,2].add(biggles.PlotLabel(0.32, 0.10-0.03, r"$\pm$ 0.006 keV", texthalign="left", fontsize=5.))
q2[0,0].add(biggles.PlotLabel(0.2, 0.92, r"$\Upsilon(1S)$", fontsize=5.))
q2[0,1].add(biggles.PlotLabel(0.2, 0.92, r"$\Upsilon(2S)$", fontsize=5.))
q2[0,2].add(biggles.PlotLabel(0.2, 0.92, r"$\Upsilon(3S)$", fontsize=5.))
q2.yrange = 0., 30.
q2.xlabel = r"Center-of-mass energy in GeV"
q2.ylabel = r"Hadronic cross-section in nb"
q2.aspect_ratio = 7./10.5
q2.show()

print "STOP!"
print "STOP!"
print "STOP!"
print "STOP!"
print "STOP!"
print "STOP!"
print "STOP!"
print "STOP!"
print "STOP!"
print "STOP!"
print "STOP!"
print "STOP!"
print "STOP!"
print "STOP!"
print "STOP!"
print "STOP!"
print "STOP!"

q = biggles.FramedArray(1,3)
q[0,0].add(biggles.PlotBox((0.2, 0.15), (0.8, 0.09), color="yellow", width=130))
q[0,1].add(biggles.PlotBox((0.2, 0.15), (0.8, 0.09), color="yellow", width=130))
q[0,2].add(biggles.PlotBox((0.2, 0.15), (0.8, 0.09), color="yellow", width=130))
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
q[0,0].add(biggles.PlotLabel(0.69, 0.18-0.01, r"$\Gamma_{ee}$ = 1.336", texthalign="right", fontsize=5.))
q[0,0].add(biggles.PlotLabel(0.32, 0.14-0.02, r"$\pm$ 0.009", texthalign="left", fontsize=5.))
q[0,0].add(biggles.PlotLabel(0.32, 0.10-0.03, r"$\pm$ 0.019 keV", texthalign="left", fontsize=5.))
q[0,1].add(biggles.PlotLabel(0.69, 0.18-0.01, r"$\Gamma_{ee}$ = 0.616", texthalign="right", fontsize=5.))
q[0,1].add(biggles.PlotLabel(0.32, 0.14-0.02, r"$\pm$ 0.010", texthalign="left", fontsize=5.))
q[0,1].add(biggles.PlotLabel(0.32, 0.10-0.03, r"$\pm$ 0.009 keV", texthalign="left", fontsize=5.))
q[0,2].add(biggles.PlotLabel(0.69, 0.18-0.01, r"$\Gamma_{ee}$ = 0.425", texthalign="right", fontsize=5.))
q[0,2].add(biggles.PlotLabel(0.32, 0.14-0.02, r"$\pm$ 0.009", texthalign="left", fontsize=5.))
q[0,2].add(biggles.PlotLabel(0.32, 0.10-0.03, r"$\pm$ 0.006 keV", texthalign="left", fontsize=5.))
q[0,0].add(biggles.PlotLabel(0.2, 0.92, r"$\Upsilon(1S)$", fontsize=5.))
q[0,1].add(biggles.PlotLabel(0.2, 0.92, r"$\Upsilon(2S)$", fontsize=5.))
q[0,2].add(biggles.PlotLabel(0.2, 0.92, r"$\Upsilon(3S)$", fontsize=5.))
q.yrange = 0., 30.
q.xlabel = r"Center-of-mass energy in GeV"
q.ylabel = r"Hadronic cross-section in nb"
q.aspect_ratio = 7./10.5
q.show()
q.write_eps("/home/mccann/antithesis/plots/three_resonances_inset_squat2_hl.eps")

###########################################################

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

# def dofitgauss(h):
#   def gauss(a,m,s, x): return a*exp(-(x-m)**2/2./s**2)
#   def fitgauss(a,m,s):
#     c = 0.
#     for xlow, y, yerr in zip(h.h.frame, h.h.vals, h.h.errs):
#       if yerr > 0.:
#         x = xlow + (h.h.high - h.h.frame[-1])/2.
#         c += (y - gauss(a,m,s, x))**2 / yerr**2
#     return c
#   m = Minuit(fitgauss, start=[10., 0., 1.])
#   m.migrad()
#   m.fix(0)
#   m.migrad()
#   m.minos([1,2])
#   err1 = (m.minos_errors[1][1] - m.minos_errors[1][0])/2.
#   err2 = (m.minos_errors[2][1] - m.minos_errors[2][0])/2.
#   return m.values[1], err1, m.values[2], err2, lambda x: gauss(m.values[0], m.values[1], m.values[2], x)

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

def u1plot_pull(area, rmsbeam, back, jan16, jan30, feb06, feb13, feb20, feb27, mar06, mar13, apr03, apr08, apr09, apr10, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac):
  p = biggles.Table(3,1)
  p[0,0] = biggles.FramedPlot()
  p[2,0] = biggles.FramedPlot()
  h = MoreThanHist(100, -5., 5.)
  h.fill(adddata_pull(p[0,0], u1data["cont"], 0., lambda w: u1func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, w)))
  h.fill(adddata_pull(p[0,0], u1data["high"], 0., lambda w: u1func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, w)))
  h.fill(adddata_pull(p[0,0], u1data["jan16"], jan16, lambda w: u1func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, w)))
  h.fill(adddata_pull(p[0,0], u1data["jan30"], jan30, lambda w: u1func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, w)))
  h.fill(adddata_pull(p[0,0], u1data["feb06"], feb06, lambda w: u1func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, w)))
  h.fill(adddata_pull(p[0,0], u1data["feb13"], feb13, lambda w: u1func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, w)))
  h.fill(adddata_pull(p[0,0], u1data["feb20"], feb20, lambda w: u1func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, w)))
  h.fill(adddata_pull(p[0,0], u1data["feb27"], feb27, lambda w: u1func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, w)))
  h.fill(adddata_pull(p[0,0], u1data["mar06"], mar06, lambda w: u1func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, w)))
  h.fill(adddata_pull(p[0,0], u1data["mar13"], mar13, lambda w: u1func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, w)))
  h.fill(adddata_pull(p[0,0], u1data["apr03"], apr03, lambda w: u1func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, w)))
  h.fill(adddata_pull(p[0,0], u1data["apr08"], apr08, lambda w: u1func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, w)))
  h.fill(adddata_pull(p[0,0], u1data["apr09"], apr09, lambda w: u1func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, w)))
  h.fill(adddata_pull(p[0,0], u1data["apr10"], apr10, lambda w: u1func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, w)))
  dates = []
  dates += adddata_pull3(p[2,0], u1runs["jan16"], u1data["jan16"], jan16, lambda w: u1func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, w))
  dates += adddata_pull3(p[2,0], u1runs["jan30"], u1data["jan30"], jan30, lambda w: u1func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, w))
  dates += adddata_pull3(p[2,0], u1runs["feb06"], u1data["feb06"], feb06, lambda w: u1func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, w))
  dates += adddata_pull3(p[2,0], u1runs["feb13"], u1data["feb13"], feb13, lambda w: u1func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, w))
  dates += adddata_pull3(p[2,0], u1runs["feb20"], u1data["feb20"], feb20, lambda w: u1func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, w))
  dates += adddata_pull3(p[2,0], u1runs["feb27"], u1data["feb27"], feb27, lambda w: u1func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, w))
  dates += adddata_pull3(p[2,0], u1runs["mar06"], u1data["mar06"], mar06, lambda w: u1func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, w))
  dates += adddata_pull3(p[2,0], u1runs["mar13"], u1data["mar13"], mar13, lambda w: u1func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, w))
  dates += adddata_pull3(p[2,0], u1runs["apr03"], u1data["apr03"], apr03, lambda w: u1func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, w))
  dates += adddata_pull3(p[2,0], u1runs["apr08"], u1data["apr08"], apr08, lambda w: u1func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, w))
  dates += adddata_pull3(p[2,0], u1runs["apr09"], u1data["apr09"], apr09, lambda w: u1func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, w))
  dates += adddata_pull3(p[2,0], u1runs["apr10"], u1data["apr10"], apr10, lambda w: u1func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, w))
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
# u1plot_pull(*fitrecord[1].values).show()
u1plot_pull(*fitrecord[1].values).write_eps("/home/mccann/antithesis/fit_results/final_1pull.eps")

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

def u2plot_pull(area, rmsbeam, back, may29, jun11, jun12, jul10, jul24, aug07, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area):
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
# u2plot_pull(*u2fitter.values).show()
u2plot_pull(*fitrecord[2].values).write_eps("/home/mccann/antithesis/fit_results/final_2pull.eps")

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

def u3plot_pull(area, rmsbeam, back, nov28, dec05, dec12, dec19, dec26, jan02, jan09, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area):
  p = biggles.Table(3,1)
  p[0,0] = biggles.FramedPlot()
  p[2,0] = biggles.FramedPlot()
  h = MoreThanHist(100, -5., 5.)
  h.fill(adddata_pull(p[0,0], u3data["cont"], 0., lambda w: u3func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area, w)))
  h.fill(adddata_pull(p[0,0], u3data["high"], 0., lambda w: u3func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area, w)))
  h.fill(adddata_pull(p[0,0], u3data["nov28"], nov28, lambda w: u3func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area, w)))
  h.fill(adddata_pull(p[0,0], u3data["dec05"], dec05, lambda w: u3func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area, w)))
  h.fill(adddata_pull(p[0,0], u3data["dec12"], dec12, lambda w: u3func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area, w)))
  h.fill(adddata_pull(p[0,0], u3data["dec19"], dec19, lambda w: u3func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area, w)))
  h.fill(adddata_pull(p[0,0], u3data["dec26"], dec26, lambda w: u3func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area, w)))
  h.fill(adddata_pull(p[0,0], u3data["jan02"], jan02, lambda w: u3func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area, w)))
  h.fill(adddata_pull(p[0,0], u3data["jan09"], jan09, lambda w: u3func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area, w)))
  dates = []
  dates += adddata_pull3(p[2,0], u3runs["nov28"], u3data["nov28"], nov28, lambda w: u3func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area, w))
  dates += adddata_pull3(p[2,0], u3runs["dec05"], u3data["dec05"], dec05, lambda w: u3func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area, w))
  dates += adddata_pull3(p[2,0], u3runs["dec12"], u3data["dec12"], dec12, lambda w: u3func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area, w))
  dates += adddata_pull3(p[2,0], u3runs["dec19"], u3data["dec19"], dec19, lambda w: u3func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area, w))
  dates += adddata_pull3(p[2,0], u3runs["dec26"], u3data["dec26"], dec26, lambda w: u3func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area, w))
  dates += adddata_pull3(p[2,0], u3runs["jan02"], u3data["jan02"], jan02, lambda w: u3func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area, w))
  dates += adddata_pull3(p[2,0], u3runs["jan09"], u3data["jan09"], jan09, lambda w: u3func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area, w))
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
# u3plot_pull(*u3fitter.values).show()
u3plot_pull(*fitrecord[3].values).write_eps("/home/mccann/antithesis/fit_results/final_3pull.eps")

###############################################################

def adddata2(data, shift, x, y, yerr):
  for (e, h, herr) in data:
    x.append(e*2000.+shift)
    y.append(h)
    yerr.append(herr)
  return None

class FitRecord: pass
fitrecord = pickle.load(open("/home/mccann/antithesis/fit_results/effcor.p"))

def get_cosmics(runs, usebhabha=False):
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
    
    if usebhabha:
      ngg = therun.bhabha
      if r in mycarefulscan: ngg = therun.bhabha_vstime.sum(0.,0.99)

    wsum += float(ngg)
    wesum += float(ngg) * runsummary[r].energy
#    print "    run", r, "energy =", runsummary[r].energy, "gamgams =", ngg

    if r in mycarefulscan:
      g += therun.gamgam_vstime.sum(0.,0.99)
      h += therun.hadroncool_vstime.sum(0.,0.99)
      e += therun.beamgase_vstime.sum(0.,0.99)
      p += therun.beamgasp_vstime.sum(0.,0.99)
      c += therun.cosmic_vstime.sum(0.,0.99)

      if usebhabha:
        g -= therun.gamgam_vstime.sum(0.,0.99)
        g += therun.bhabha_vstime.sum(0.,0.99)
    else:
      g += therun.gamgam
      h += therun.hadroncool
      e += therun.beamgase
      p += therun.beamgasp
      c += therun.cosmic

      if usebhabha:
        g -= therun.gamgam
        g += therun.bhabha

  average_energy = wesum / wsum
#  print "  Average energy is", average_energy

  ebkgnd = 1. * (ebeam.hadroncool - 1.*nobeam.hadroncool*ebeam.cosmic/nobeam.cosmic) * e / ebeam.beamgase
  pbkgnd = 1. * (pbeam.hadroncool - 1.*nobeam.hadroncool*pbeam.cosmic/nobeam.cosmic) * p / pbeam.beamgasp
  cbkgnd = 1. * nobeam.hadroncool * c / nobeam.cosmic

  hadrons = cbkgnd
  hadrons_err = sqrt(c * (1.*nobeam.hadroncool/nobeam.cosmic)**2)
#  print "  Corrected number of hadrons is", hadrons, "+/-", hadrons_err
#  print "  Number of gamgams is", g

  cs = hadrons / g / average_energy**2 * nbish2nb

  cs_err = cs * sqrt((1.*hadrons_err / hadrons)**2 + 1./g)
#  print "  Relative cross-section is", cs, "+/-", cs_err

  if usebhabha:
    cs /= 0.077045
    cs_err /= 0.077045

  return average_energy, cs, cs_err

def get_pbkgnd(runs, usebhabha=False):
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
    
    if usebhabha:
      ngg = therun.bhabha
      if r in mycarefulscan: ngg = therun.bhabha_vstime.sum(0.,0.99)

    wsum += float(ngg)
    wesum += float(ngg) * runsummary[r].energy
#    print "    run", r, "energy =", runsummary[r].energy, "gamgams =", ngg

    if r in mycarefulscan:
      g += therun.gamgam_vstime.sum(0.,0.99)
      h += therun.hadroncool_vstime.sum(0.,0.99)
      e += therun.beamgase_vstime.sum(0.,0.99)
      p += therun.beamgasp_vstime.sum(0.,0.99)
      c += therun.cosmic_vstime.sum(0.,0.99)

      if usebhabha:
        g -= therun.gamgam_vstime.sum(0.,0.99)
        g += therun.bhabha_vstime.sum(0.,0.99)
    else:
      g += therun.gamgam
      h += therun.hadroncool
      e += therun.beamgase
      p += therun.beamgasp
      c += therun.cosmic

      if usebhabha:
        g -= therun.gamgam
        g += therun.bhabha

  average_energy = wesum / wsum
#  print "  Average energy is", average_energy

  ebkgnd = 1. * (ebeam.hadroncool - 1.*nobeam.hadroncool*ebeam.cosmic/nobeam.cosmic) * e / ebeam.beamgase
  pbkgnd = 1. * (pbeam.hadroncool - 1.*nobeam.hadroncool*pbeam.cosmic/nobeam.cosmic) * p / pbeam.beamgasp
  cbkgnd = 1. * nobeam.hadroncool * c / nobeam.cosmic

  hadrons = pbkgnd
  hadrons_err = sqrt(1. * p * (pbeam.hadroncool - 1.*nobeam.hadroncool*pbeam.cosmic/nobeam.cosmic)**2 / pbeam.beamgasp**2)
#  print "  Corrected number of hadrons is", hadrons, "+/-", hadrons_err
#  print "  Number of gamgams is", g

  cs = hadrons / g / average_energy**2 * nbish2nb

  cs_err = cs * sqrt((1.*hadrons_err / hadrons)**2 + 1./g)
#  print "  Relative cross-section is", cs, "+/-", cs_err

  if usebhabha:
    cs /= 0.077045
    cs_err /= 0.077045

  return average_energy, cs, cs_err

def get_ebkgnd(runs, usebhabha=False):
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
    
    if usebhabha:
      ngg = therun.bhabha
      if r in mycarefulscan: ngg = therun.bhabha_vstime.sum(0.,0.99)

    wsum += float(ngg)
    wesum += float(ngg) * runsummary[r].energy
#    print "    run", r, "energy =", runsummary[r].energy, "gamgams =", ngg

    if r in mycarefulscan:
      g += therun.gamgam_vstime.sum(0.,0.99)
      h += therun.hadroncool_vstime.sum(0.,0.99)
      e += therun.beamgase_vstime.sum(0.,0.99)
      p += therun.beamgasp_vstime.sum(0.,0.99)
      c += therun.cosmic_vstime.sum(0.,0.99)

      if usebhabha:
        g -= therun.gamgam_vstime.sum(0.,0.99)
        g += therun.bhabha_vstime.sum(0.,0.99)
    else:
      g += therun.gamgam
      h += therun.hadroncool
      e += therun.beamgase
      p += therun.beamgasp
      c += therun.cosmic

      if usebhabha:
        g -= therun.gamgam
        g += therun.bhabha

  average_energy = wesum / wsum
#  print "  Average energy is", average_energy

  ebkgnd = 1. * (ebeam.hadroncool - 1.*nobeam.hadroncool*ebeam.cosmic/nobeam.cosmic) * e / ebeam.beamgase
  pbkgnd = 1. * (pbeam.hadroncool - 1.*nobeam.hadroncool*pbeam.cosmic/nobeam.cosmic) * p / pbeam.beamgasp
  cbkgnd = 1. * nobeam.hadroncool * c / nobeam.cosmic

  hadrons = ebkgnd
  hadrons_err = sqrt(1. * e * (ebeam.hadroncool - 1.*nobeam.hadroncool*ebeam.cosmic/nobeam.cosmic)**2 / ebeam.beamgase**2)
#  print "  Corrected number of hadrons is", hadrons, "+/-", hadrons_err
#  print "  Number of gamgams is", g

  cs = hadrons / g / average_energy**2 * nbish2nb

  cs_err = cs * sqrt((1.*hadrons_err / hadrons)**2 + 1./g)
#  print "  Relative cross-section is", cs, "+/-", cs_err

  if usebhabha:
    cs /= 0.077045
    cs_err /= 0.077045

  return average_energy, cs, cs_err

def setup_cosmics(runs, fudge=1.):
  tmpdata = []
  for r in runs:
    e, cs, cserr = get_cosmics([r])
    cserr *= fudge
    tmpdata.append((e, cs, cserr))
  return tmpdata

def setup_pbkgnd(runs, fudge=1.):
  tmpdata = []
  for r in runs:
    e, cs, cserr = get_pbkgnd([r])
    cserr *= fudge
    tmpdata.append((e, cs, cserr))
  return tmpdata

def setup_ebkgnd(runs, fudge=1.):
  tmpdata = []
  for r in runs:
    e, cs, cserr = get_ebkgnd([r])
    cserr *= fudge
    tmpdata.append((e, cs, cserr))
  return tmpdata

u3cosmics = {}
u3pbkgnd = {}
u3ebkgnd = {}

u3cosmics["cont"] = [get_cosmics(u3runs["cont"])]
u3cosmics["high"] = [get_cosmics(u3runs["high"])]
u3cosmics["nov28"] = setup_cosmics(u3runs["nov28"])
u3cosmics["dec05"] = setup_cosmics(u3runs["dec05"])
u3cosmics["dec12"] = setup_cosmics(u3runs["dec12"])
u3cosmics["dec19"] = setup_cosmics(u3runs["dec19"])
u3cosmics["dec26"] = setup_cosmics(u3runs["dec26"])
u3cosmics["jan02"] = setup_cosmics(u3runs["jan02"])
u3cosmics["jan09"] = setup_cosmics(u3runs["jan09"])

u3pbkgnd["cont"] = [get_pbkgnd(u3runs["cont"])]
u3pbkgnd["high"] = [get_pbkgnd(u3runs["high"])]
u3pbkgnd["nov28"] = setup_pbkgnd(u3runs["nov28"])
u3pbkgnd["dec05"] = setup_pbkgnd(u3runs["dec05"])
u3pbkgnd["dec12"] = setup_pbkgnd(u3runs["dec12"])
u3pbkgnd["dec19"] = setup_pbkgnd(u3runs["dec19"])
u3pbkgnd["dec26"] = setup_pbkgnd(u3runs["dec26"])
u3pbkgnd["jan02"] = setup_pbkgnd(u3runs["jan02"])
u3pbkgnd["jan09"] = setup_pbkgnd(u3runs["jan09"])

u3ebkgnd["cont"] = [get_ebkgnd(u3runs["cont"])]
u3ebkgnd["high"] = [get_ebkgnd(u3runs["high"])]
u3ebkgnd["nov28"] = setup_ebkgnd(u3runs["nov28"])
u3ebkgnd["dec05"] = setup_ebkgnd(u3runs["dec05"])
u3ebkgnd["dec12"] = setup_ebkgnd(u3runs["dec12"])
u3ebkgnd["dec19"] = setup_ebkgnd(u3runs["dec19"])
u3ebkgnd["dec26"] = setup_ebkgnd(u3runs["dec26"])
u3ebkgnd["jan02"] = setup_ebkgnd(u3runs["jan02"])
u3ebkgnd["jan09"] = setup_ebkgnd(u3runs["jan09"])

factor = nbish2nb

contstuff = getdb(u3runs["cont"][0])
for r in u3runs["cont"]:
  if r != u3runs["cont"][0]:
    contstuff += getdb(r)

# contstuff1 = getdb(u1runs["cont"][0])
# for r in u1runs["cont"]:
#   if r != u1runs["cont"][0]:
#     contstuff1 += getdb(r)

# contstuff2 = getdb(u2runs["cont"][0])
# for r in u2runs["cont"]:
#   if r != u2runs["cont"][0]:
#     contstuff2 += getdb(r)

def u3func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area, w):
  tmp = 0.
  tmp += area * 0.9708 * mygbwkf(10355.2, fullgam, rmsbeam, yint, phi, w)
  tmp += area * 0.578 * btautau * mygbwkftau(10355.2, fullgam, rmsbeam, tauyint, tauphi, w)
  tmp += back * (1.-twophofrac) * 9000.**2 / w**2
  tmp += back * twophofrac * log(w**2/9000.**2)
  tmp += u1area * mygbwkf(9460.30, 0., 0., 0., 0., w)
  tmp += u2area * mygbwkf(10023.26, 0., 0., 0., 0., w)
  return tmp*factor

def u3func_tail(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area, w):
  tmp = area * 0.9708 * mygbwkf(10355.2, fullgam, rmsbeam, yint, phi, w)
  tmp -= area * 0.9708 * exp(-(w-10355.2)**2/2./rmsbeam**2) / sqrt(2.*pi) / rmsbeam
  return abs(tmp)*factor

def u3func_backgrounds(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area, w):
  tmp = 0.
  tmp += area * 0.578 * btautau * mygbwkftau(10355.2, fullgam, rmsbeam, tauyint, tauphi, w)
  tmp += back * (1.-twophofrac) * 9000.**2 / w**2
  tmp += back * twophofrac * log(w**2/9000.**2)
  tmp += u1area * mygbwkf(9460.30, 0., 0., 0., 0., w)
  tmp += u2area * mygbwkf(10023.26, 0., 0., 0., 0., w)
  return tmp*factor

def u3func_u1area(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area, w):
  tmp = 0.
  tmp += u1area * mygbwkf(9460.30, 0., 0., 0., 0., w)
  return tmp*factor

def u3func_u2area(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area, w):
  tmp = 0.
  tmp += u2area * mygbwkf(10023.26, 0., 0., 0., 0., w)
  return tmp*factor

def u3func_jpsi(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area, w):
  tmp = 0.
  tmp += u1area * 4.11 * mygbwkf(3096.916, 0., 0., 0., 0., w)
  return tmp*factor

def u3func_psiprime(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area, w):
  tmp = 0.
  tmp += u1area * 1.61 * mygbwkf(3686.093, 0., 0., 0., 0., w)
  return tmp*factor

def u3func_twophoton(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area, w):
  tmp = 0.
  tmp += back * twophofrac * log(w**2/9000.**2)
  return tmp*factor

def u3func_tau(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area, w, res=True, cont=True):
  tmp = 0.
  if res: tmp += area * 0.578 * btautau * mygbwkftau(10355.2, fullgam, rmsbeam, tauyint, tauphi, w)
  if cont: tmp += 0.578*contstuff.mupair_logd0close.int(-7.,-3.)/contstuff.gamgam * (u3data["cont"][0][0]*2000.)**2 / w**2
  return tmp*factor

def u2func_tau(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, w, res=True, cont=True):
  tmp = 0.
  if res: tmp += area * 0.578 * btautau * mygbwkftau(10023.26, fullgam, rmsbeam, tauyint, tauphi, w)
  if cont: tmp += 0.578*contstuff2.mupair_logd0close.int(-7.,-3.)/contstuff2.gamgam * (u2data["cont"][0][0]*2000.)**2 / w**2
  return tmp*factor

def u1func_tau(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, w, res=True, cont=True):
  tmp = 0.
  if res: tmp += area * 0.578 * btautau * mygbwkftau(9460.30, fullgam, rmsbeam, tauyint, tauphi, w)
  if cont: tmp += 0.578*contstuff.mupair_logd0close.int(-7.,-3.)/contstuff.gamgam * (u1data["cont"][0][0]*2000.)**2 / w**2
  return tmp*factor

# def really(ecom, whichres):
#   if whichres == 3:
#     area, rmsbeam, back, nov28, dec05, dec12, dec19, dec26, jan02, jan09, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area = fitrecord[3].values
#     return u3func_tau(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area, ecom, res=True, cont=False)/u3func_tau(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area, ecom, res=True, cont=True)
#   if whichres == 2:
#     area, rmsbeam, back, may29, jun11, jun12, jul10, jul24, aug07, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area = fitrecord[2].values
#     return u2func_tau(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, ecom, res=True, cont=False)/u2func_tau(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, ecom, res=True, cont=True)
#   if whichres == 1:
#     area, rmsbeam, back, jan16, jan30, feb06, feb13, feb20, feb27, mar06, mar13, apr03, apr08, apr09, apr10, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac = fitrecord[1].values
#     return u1func_tau(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, ecom, res=True, cont=False)/u1func_tau(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, ecom, res=True, cont=True)

area, rmsbeam, back, nov28, dec05, dec12, dec19, dec26, jan02, jan09, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area = fitrecord[3].values

p = biggles.FramedPlot()
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
p.add(biggles.Points(fewx, fewy, symboltype="filled circle", symbolsize=0.8))
p.add(biggles.SymmetricErrorBarsY(fewx, fewy, fewyerr))

x = []
y = []
yerr = []
adddata2(u3cosmics["cont"], 0., x, y, yerr)
adddata2(u3cosmics["high"], 0., x, y, yerr)
adddata2(u3cosmics["nov28"], nov28, x, y, yerr)
adddata2(u3cosmics["dec05"], dec05, x, y, yerr)
adddata2(u3cosmics["dec12"], dec12, x, y, yerr)
adddata2(u3cosmics["dec19"], dec19, x, y, yerr)
adddata2(u3cosmics["dec26"], dec26, x, y, yerr)
adddata2(u3cosmics["jan02"], jan02, x, y, yerr)
adddata2(u3cosmics["jan09"], jan09, x, y, yerr)
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
p.add(biggles.Points(fewx, fewy, symboltype="filled circle", symbolsize=0.8))
cosmic_points = biggles.SymmetricErrorBarsY(fewx, fewy, fewyerr)
p.add(cosmic_points)
# p.add(biggles.DataLabel(10389, factor*0.0016, r"cosmic"))
# p.add(biggles.DataLabel(10402, factor*0.0016, r"rays", texthalign="left"))
cosmic_points.label = "cosmic rays"

x = []
y = []
yerr = []
adddata2(u3pbkgnd["cont"], 0., x, y, yerr)
adddata2(u3pbkgnd["high"], 0., x, y, yerr)
adddata2(u3pbkgnd["nov28"], nov28, x, y, yerr)
adddata2(u3pbkgnd["dec05"], dec05, x, y, yerr)
adddata2(u3pbkgnd["dec12"], dec12, x, y, yerr)
adddata2(u3pbkgnd["dec19"], dec19, x, y, yerr)
adddata2(u3pbkgnd["dec26"], dec26, x, y, yerr)
adddata2(u3pbkgnd["jan02"], jan02, x, y, yerr)
adddata2(u3pbkgnd["jan09"], jan09, x, y, yerr)
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
pbkgnd_points = biggles.Points(fewx, fewy, symboltype="triangle", symbolsize=2.)
p.add(pbkgnd_points)
# p.add(biggles.DataLabel(10389, factor*0.00045, r"$e^+$-gas"))
pbkgnd_points.label = r"$e^+$ beam-gas"

x = []
y = []
yerr = []
adddata2(u3ebkgnd["cont"], 0., x, y, yerr)
adddata2(u3ebkgnd["high"], 0., x, y, yerr)
adddata2(u3ebkgnd["nov28"], nov28, x, y, yerr)
adddata2(u3ebkgnd["dec05"], dec05, x, y, yerr)
adddata2(u3ebkgnd["dec12"], dec12, x, y, yerr)
adddata2(u3ebkgnd["dec19"], dec19, x, y, yerr)
adddata2(u3ebkgnd["dec26"], dec26, x, y, yerr)
adddata2(u3ebkgnd["jan02"], jan02, x, y, yerr)
adddata2(u3ebkgnd["jan09"], jan09, x, y, yerr)
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
ebkgnd_points = biggles.Points(fewx, fewy, symboltype="filled inverted triangle", symbolsize=2.)
p.add(ebkgnd_points)
# p.add(biggles.DataLabel(10389, factor*0.0002, r"$e^-$-gas"))
ebkgnd_points.label = r"$e^-$ beam-gas"

addfunc(p, lambda w: u3func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area, w), 10290., 10420.)

addfunc(p, lambda w: u3func_backgrounds(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area, w), 10290., 10420., linetype="dashed")
p.add(biggles.DataLabel(10297., 0.8*u3func_backgrounds(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area, 10297.), r"all backgrounds", texthalign="left", fontsize=2.8))
  
addfunc(p, lambda w: u3func_tau(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area, w), 10290., 10420.)
p.add(biggles.DataLabel(10297., (1./0.8)*u3func_tau(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area, 10297.), r"$\tau^+\tau^-$", texthalign="left", fontsize=2.8))
  
addfunc(p, lambda w: u3func_twophoton(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area, w), 10290., 10420.)
p.add(biggles.DataLabel(10297., 0.8*u3func_twophoton(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area, 10297.), r"two-photon fusion", texthalign="left", fontsize=2.8))
  
addfunc(p, lambda w: u3func_u1area(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area, w), 10290., 10420.)
p.add(biggles.DataLabel(10305., 0.8*u3func_u1area(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area, 10305.), r"$\Upsilon(1S)$", fontsize=2.8))
  
addfunc(p, lambda w: u3func_u2area(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area, w), 10290., 10420.)
p.add(biggles.DataLabel(10305., (1./0.8)*u3func_u2area(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area, 10305.), r"$\Upsilon(2S)$", fontsize=2.8))
  
addfunc(p, lambda w: u3func_jpsi(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area, w), 10290., 10420., linetype="dotted")
p.add(biggles.DataLabel(10305., 0.8*u3func_jpsi(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area, 10305.), r"$J/\psi$", fontsize=2.8))
  
addfunc(p, lambda w: u3func_psiprime(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area, w), 10290., 10420., linetype="dotted")
p.add(biggles.DataLabel(10305., 0.8*u3func_psiprime(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area, 10305.), r"$\psi(2S)$", fontsize=2.8))
  
def inset(area, rmsbeam, back, nov28, dec05, dec12, dec19, dec26, jan02, jan09, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area):
  p = biggles.FramedPlot()
  addfunc(p, lambda w: u3func_tau(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area, w), 10290., 10420., linewidth=5.)
  addfunc(p, lambda w: u3func_tau(0., rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area, w), 10290., 10420., linetype="dashed", linewidth=5.)
  p.x1.draw_ticks = 0
  p.x2.draw_ticks = 0
  p.y1.draw_ticks = 0
  p.y2.draw_ticks = 0
  p.x1.draw_ticklabels = 0
  p.y1.draw_ticklabels = 0
  p.x1.range = 10290., 10420.
  return p
p.add(biggles.DataInset((10390, 0.2*factor), (10415, 0.02*factor), inset(area, rmsbeam, back, nov28, dec05, dec12, dec19, dec26, jan02, jan09, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area)))
p.add(biggles.DataLine((10382., u3func_tau(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area, 10380.)), (10382., 0.05*factor)))
p.add(biggles.DataLine((10382., 0.05*factor), (10390., 0.05*factor)))
p.add(biggles.DataLine((10390., 0.05*factor), (10387., 0.05*factor*1.2)))
p.add(biggles.DataLine((10390., 0.05*factor), (10387., 0.05*factor/1.2)))

p.add(biggles.DataLabel(10379., 0.8*factor/1.2, r"$\Upsilon(3S)$ lineshape", fontsize=2.8))
# p.add(biggles.PlotKey(0.9, 0.1, [pbkgnd_points, ebkgnd_points], texthalign="right"))

p.add(biggles.DataLabel(10395.-34., factor*0.0025*0.9, r"cosmic rays", fontsize=2.8))
p.add(biggles.DataLabel(10395.-50., 0.00045*factor*1.9, r"$e^+$ beam-gas", fontsize=2.8))
p.add(biggles.DataLabel(10395.-25., 0.00012*factor, r"$e^-$ beam-gas", fontsize=2.8))

# p.y1.ticklabels = [r"$10^{-4}$", r"$10^{-3}$", r"$10^{-2}$", r"$0.1$", r"$1$"]
p.x1.ticks = [10300, 10325, 10350, 10375, 10400]
p.x2.ticks = [10300, 10325, 10350, 10375, 10400]
p.x1.subticks = range(10290, 10420, 5)
p.x2.subticks = range(10290, 10420, 5)
p.x1.range = 10290., 10420.
p.y1.range = 0.001, 50.
p.aspect_ratio = 1
p.y1.log = 1
p.x1.label = r"$E_{CM}$ (MeV)"
p.y1.label = r"Selected Events / nb$^{-1}$"
p.frame.ticklabels_style["fontsize"] = 3.
p.frame.label_style["fontsize"] = 3.

p.show()
p.write_eps("/home/mccann/antithesis/plots/notau_backgrounds_1.eps")




###############################################################

u1runs["cont"] = []
u2runs["cont"] = []
u3runs["cont"] = []
for r in initialrunlist:
  if r not in mybadruns:
    if runsummary[r].res == 1 and runsummary[r].kind == 'c':
      u1runs["cont"].append(r)
    if runsummary[r].res == 2 and runsummary[r].kind == 'c':
      u2runs["cont"].append(r)
    if runsummary[r].res == 3 and runsummary[r].kind == 'c':
      u3runs["cont"].append(r)
u1data["cont"] = [get_runs(u1runs["cont"], usebhabha=True)]
u2data["cont"] = [get_runs(u2runs["cont"], usebhabha=True)]
u3data["cont"] = [get_runs(u3runs["cont"], usebhabha=True)]

# u1data["cont"] = [get_runs(u1runs["cont"], usebhabha=True)]
# u2data["cont"] = [get_runs(u2runs["cont"], usebhabha=True)]
# u3data["cont"] = [get_runs(u3runs["cont"], usebhabha=True)]

# u1data["high"] = [get_runs(u1runs["high"], usebhabha=True)]
# u2data["high"] = [get_runs(u2runs["high"], usebhabha=True)]
# u3data["high"] = [get_runs(u3runs["high"], usebhabha=True)]

# def fitbackgrounds(back, twophofrac):
#   chi = 0.
#   for en, cs, cserr in [u1data["cont"][0], u2data["cont"][0], u3data["cont"][0]]:
#     chi += (fakeallthree(nbish2nb * 13.706, nbish2nb * 5.591, nbish2nb * 3.587, back, twophofrac, en*2000.)-cs)**2/cserr**2
#   return chi

# def fitbackgrounds_naive(back):
#   chi = 0.
#   for en, cs, cserr in [u1data["cont"][0]]:
#     chi += (fakeallthree(nbish2nb * 13.706, nbish2nb * 5.591, nbish2nb * 3.587, back, 0., en*2000.)-cs)**2/cserr**2
#   return chi

# m = Minuit(fitbackgrounds, start=[0.41, 0.10])
# m.migrad()
# print m.fval, m.values, m.errors
# m2 = Minuit(fitbackgrounds_naive, start=[0.41])
# m2.migrad()

# p = biggles.FramedPlot()
# adddata(p, u1data["cont"], 0)
# adddata(p, u2data["cont"], 0)
# adddata(p, u3data["cont"], 0)
# adddata(p, u1data["high"], 0)
# adddata(p, u2data["high"], 0)
# adddata(p, u3data["high"], 0)
# tmp1 = addfunc(p, lambda w: doallthree(m.values[0], m.values[1], w), 9350., 10450., points=1000.)
# tmp2 = addfunc(p, lambda w: m.values[0] * ((1.-m.values[1]) * 9000.**2 / w**2 + m.values[1] * log(w**2/9000.**2)), 9350., 10450., linetype="longdashed")
# tmp3 = addfunc(p, lambda w: m2.values[0] * 9000.**2 / w**2, 9350., 10450., linetype="dotted")
# p.aspect_ratio = 1.2
# p.x1.label = r"$E_{COM} in MeV$"
# p.y1.label = r"Hadronic Cross-section (bhabha luminosity)"
# tmp3.label = r"Just $1/s$"
# tmp2.label = ("With (%.2f $\pm$ %.2f)%% log$(s)$" % (m.values[1]*100., m.errors[1]*100.))
# tmp1.label = r"With $\Upsilon$ tails"
# p.add(biggles.PlotKey(0.15, 0.2, [tmp3, tmp2, tmp1]))
# p.xrange = 9350., 10450.
# p.yrange = 6., 9.
# p.show()
# p.write_eps("/home/mccann/antithesis/fit_results/final_backgrounds.eps")

datapoint1 = list(u1data["cont"][0])
datapoint2 = list(u2data["cont"][0])
datapoint3 = list(u3data["cont"][0])
datapoint2[1] -= (nbish2nb * 13.706441397531357 * 0.9868 * mygbwkf(9460.30, 0, 4, 0, 0, datapoint2[0]*2000.) + 13.706441397531357 * 0.578 * 0.0267 * mygbwkftau(9460.30, 0, 4, 0, 0, datapoint2[0]*2000.))
datapoint3[1] -= (nbish2nb * 13.706441397531357 * 0.9868 * mygbwkf(9460.30, 0, 4, 0, 0, datapoint3[0]*2000.) + 13.706441397531357 * 0.578 * 0.0267 * mygbwkftau(9460.30, 0, 4, 0, 0, datapoint3[0]*2000.))
datapoint3[1] -= (nbish2nb * 5.5910940385520558 * 0.9668 * mygbwkf(10023.26, 0, 4, 0, 0, datapoint3[0]*2000.) + 5.5910940385520558 * 0.578 * 0.017 * mygbwkftau(10023.26, 0, 4, 0, 0, datapoint3[0]*2000.))

def fakeallthree(area1, area2, area3, back, twophofrac, w):
  tmp = 0.
  tmp += back * (1.-twophofrac) * 9000.**2 / w**2
  tmp += back * twophofrac * log(w**2/9000.**2)
  return tmp

def adddata(p, data, shift, circle=False, justadot=False):
  x = []
  y = []
  yerr = []
  for (e, h, herr) in data:
    x.append(e*2000.+shift)
    y.append(h)
    yerr.append(herr)
  p.add(biggles.Points(x, y, symboltype="filled circle", symbolsize=0.8))
  if not justadot:
    p.add(biggles.SymmetricErrorBarsY(x, y, yerr))
  if len(x) == 1 and circle:
    p.add(biggles.Points(x, y, symboltype="circle", symbolsize=7.))
  return None

def fitbackgrounds(back, twophofrac):
  chi = 0.
  for en, cs, cserr in [datapoint1, datapoint2, datapoint3]:
    chi += (fakeallthree(nbish2nb * 13.706, nbish2nb * 5.591, nbish2nb * 3.587, back, twophofrac, en*2000.)-cs)**2/cserr**2
  return chi

def fitbackgrounds_naive(back):
  chi = 0.
  for en, cs, cserr in [datapoint1]:
    chi += (fakeallthree(nbish2nb * 13.706, nbish2nb * 5.591, nbish2nb * 3.587, back, 0., en*2000.)-cs)**2/cserr**2
  return chi

m = Minuit(fitbackgrounds, start=[0.41, 0.10])
m.migrad()
print m.fval, m.values, m.errors
m2 = Minuit(fitbackgrounds_naive, start=[0.41])
m2.migrad()

p = biggles.FramedPlot()
adddata(p, u1data["cont"], 0, justadot=True)
adddata(p, u2data["cont"], 0, justadot=True)
adddata(p, u3data["cont"], 0, justadot=True)
adddata(p, [datapoint1], 0, circle=True)
adddata(p, [datapoint2], 0, circle=True)
adddata(p, [datapoint3], 0, circle=True)
tmp2 = addfunc(p, lambda w: m.values[0] * ((1.-m.values[1]) * 9000.**2 / w**2 + m.values[1] * log(w**2/9000.**2)), 9350., 10450., linetype="solid")
tmp3 = addfunc(p, lambda w: m2.values[0] * 9000.**2 / w**2, 9350., 10450., linetype="longdashed")
p.aspect_ratio = 0.5
p.x1.label = r"Center-of-mass energy in MeV"
p.y1.label = r"Hadronic Cross-section in nb"
tmp3.label = r"Just $1/s$"
tmp2.label = ("With (%.2f $\pm$ %.2f)%% log$(s)$" % (m.values[1]*100., m.errors[1]*100.))
p.add(biggles.PlotKey(0.15, 0.25, [tmp2, tmp3]))
p.xrange = 9350., 10450.
p.yrange = 6., 9.
p.show()
p.write_eps("/home/mccann/antithesis/plots/proceedings_backgrounds.eps")
