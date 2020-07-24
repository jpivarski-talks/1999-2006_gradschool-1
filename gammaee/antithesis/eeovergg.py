execfile("utilities.py")
runstart = pickle.load(open("old_dotps/runstart.p"))
runend = pickle.load(open("old_dotps/runend.p"))

class FitRecord: pass
ggfits = pickle.load(open("/home/mccann/antithesis/fit_results/bhabhafits_0.p"))

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

def setup_data(runs, lumisource=0):
  tmpdata = []
  for r in runs:
    tmpdata.append(get_runs([r], lumisource=lumisource))
  return tmpdata

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

def get_runs(runs, lumisource=0):
  ee = 0
  gg = 0
  wsum = 0.
  wesum = 0.
  for r in runs:
    therun = getdb(r)
    ngg = therun.gamgam
    if r in mycarefulscan: ngg = therun.gamgam_vstime.sum(0.,0.99)
    wsum += float(ngg)
    wesum += float(ngg) * runsummary[r].energy

    if r in mycarefulscan:
      gg += therun.gamgam_vstime.sum(0.,0.99)

      if lumisource == 0:
        ee += therun.bhabha_vstime.sum(0.,0.99)
      elif lumisource == 1:
        ee += therun.bhabha_cosp.sum(0., 0.6) * therun.bhabha_vstime.sum(0.,0.99) / therun.bhabha
      elif lumisource == 2:
        ee += therun.bhabha_cosp.sum(0.6, 0.8) * therun.bhabha_vstime.sum(0.,0.99) / therun.bhabha

    else:
      gg += therun.gamgam

      if lumisource == 0:
        ee += therun.bhabha
      elif lumisource == 1:
        ee += therun.bhabha_cosp.sum(0., 0.6)

      elif lumisource == 2:
        ee += therun.bhabha_cosp.sum(0.6, 0.8)

  average_energy = wesum / wsum

  eegg = float(ee)/float(gg)
  eegg_err = eegg * sqrt(1./ee + 1./gg)
  return average_energy, eegg, eegg_err

for lumisource in (0,1,2):
  u1runs = {}
  u2runs = {}
  u3runs = {}
  u1data = {}
  u2data = {}
  u3data = {}

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

  u1runs["high"] = []
  u2runs["high"] = []
  u3runs["high"] = []
  for r in initialrunlist:
    if r not in mybadruns:
      if runsummary[r].res == 1 and runsummary[r].kind == 'h':
        u1runs["high"].append(r)
      if runsummary[r].res == 2 and runsummary[r].kind == 'h':
        u2runs["high"].append(r)
      if runsummary[r].res == 3 and runsummary[r].kind == 'h':
        u3runs["high"].append(r)

  u1data["cont"] = [get_runs(u1runs["cont"], lumisource=lumisource)]
  u2data["cont"] = [get_runs(u2runs["cont"], lumisource=lumisource)]
  u3data["cont"] = [get_runs(u3runs["cont"], lumisource=lumisource)]

  u1data["high"] = [get_runs(u1runs["high"], lumisource=lumisource)]
  u2data["high"] = [get_runs(u2runs["high"], lumisource=lumisource)]
  u3data["high"] = [get_runs(u3runs["high"], lumisource=lumisource)]

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

  def adddata2(data, shift, x, y, yerr):
    for (e, h, herr) in data:
      x.append(e*2000.+shift)
      y.append(h)
      yerr.append(herr)
    return None

  def u1ploteegg(area, rmsbeam, back, jan16, jan30, feb06, feb13, feb20, feb27, mar06, mar13, apr03, apr08, apr09, apr10, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac):
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
    p = biggles.FramedPlot()
    p.add(biggles.Points(fewx, fewy, symboltype="filled circle", symbolsize=1.2))
    p.add(biggles.SymmetricErrorBarsY(fewx, fewy, fewyerr))
    p.add(biggles.LineY(u1data["cont"][0][1]))
    p.xrange = 9420., 9580.
    return p

  def u2ploteegg(area, rmsbeam, back, may29, jun11, jun12, jul10, jul24, aug07, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area):
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
    p = biggles.FramedPlot()
    p.add(biggles.Points(fewx, fewy, symboltype="filled circle", symbolsize=1.2))
    p.add(biggles.SymmetricErrorBarsY(fewx, fewy, fewyerr))
    p.add(biggles.LineY(u2data["cont"][0][1]))
    p.xrange = 9980., 10100.
    return p

  def u3ploteegg(area, rmsbeam, back, nov28, dec05, dec12, dec19, dec26, jan02, jan09, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, u1area, u2area):
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
    p = biggles.FramedPlot()
    p.add(biggles.Points(fewx, fewy, symboltype="filled circle", symbolsize=0.8))
    p.add(biggles.SymmetricErrorBarsY(fewx, fewy, fewyerr))
    p.xrange = 10320., 10420.
    p.add(biggles.LineY(u3data["cont"][0][1]))
    return p

  p = biggles.Table(3,1)
  p[0,0] = u1ploteegg(*ggfits[1].values)
  p[1,0] = u2ploteegg(*ggfits[2].values)
  p[2,0] = u3ploteegg(*ggfits[3].values)
  p[0,0].y1.label = r"$\Upsilon(1S)$ $e^+e^-$/$\gamma\gamma$"
  p[1,0].y1.label = r"$\Upsilon(2S)$ $e^+e^-$/$\gamma\gamma$"
  p[2,0].y1.label = r"$\Upsilon(3S)$ $e^+e^-$/$\gamma\gamma$"
  p[0,0].x1.label = r"Center-of-mass energy in MeV"
  p[1,0].x1.label = r"Center-of-mass energy in MeV"
  p[2,0].x1.label = r"Center-of-mass energy in MeV"
  if lumisource == 0:
    p.title = r"$e^+e^-$ is all barrel bhabhas"
  elif lumisource == 1:
    p.title = r"inner $e^+e^-$ only (0 < $cos\theta_{e+}$ < 0.6)"
  elif lumisource == 2:
    p.title = r"outer $e^+e^-$ only (0.6 < $cos\theta_{e+}$ < 0.8)"
  p.aspect_ratio = 11./8.5
  p.write_eps("/home/mccann/antithesis/plots/eeovergg_"+str(lumisource)+".eps")
