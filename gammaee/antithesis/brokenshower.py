execfile("utilities.py")

initialrunlist = [123369, 126252, 121576, 123370, 126253, 121579, 123378, 126254, 121580, 123380, 126255, 121581, 123382, 126256, 121582, 123566, 121588, 126257, 123565, 121585, 126258, 123567, 126259, 123568, 121590, 126260, 121592, 123569, 126263, 121593, 123570, 126265, 121595, 123591, 126266, 121608, 123592, 126268, 121609, 123767, 126273, 121623, 123768, 126471, 121624, 123771, 126472, 121769, 123772, 126473, 121771, 123773, 126475, 121772, 123774, 126476, 121774, 123775, 126477, 121778, 123793, 126478, 121779, 123794, 126479, 121780, 123796, 126480, 121781, 123800, 126483, 121899, 123803, 126485, 121901, 123809, 126487, 121902, 123810, 126488, 121903, 123811, 126490, 121904, 123812, 126492, 121905, 123813, 126494, 121906, 123814, 126651, 121911, 123815, 126652, 121912, 123816, 126653, 121914, 123817, 126656, 121915, 123818, 126657, 122064, 123820, 126658, 122066, 123938, 126662, 122080, 123939, 126664, 122081, 123941, 126665, 122083, 126666, 123944, 122085, 123945, 126667, 122089, 123951, 126668, 122091, 123952, 126669, 122264, 123953, 126670, 122268, 123955, 126673, 122269, 123956, 126832, 122272, 123958, 126833, 122273, 123959, 126834, 123960, 122418, 126835, 122420, 123961, 126836, 122422, 123962, 126837, 122423, 124113, 126838, 122424, 124114, 126839, 122425, 126842, 124115, 122426, 124117, 126845, 122427, 124121, 126846, 122428, 124123, 126847, 122429, 124125, 126851, 122430, 124126, 126853, 122432, 124127, 126854, 122433, 124128, 126855, 124129, 122434, 126856, 122585, 124132, 127059, 122586, 124134, 127061, 122587, 124137, 127062, 122589, 124138, 127064, 122590, 124139, 127065, 122593, 124140, 127066, 122594, 124141, 127067, 122596, 124299, 127068, 122599, 124300, 127070, 122602, 124301, 127071, 122603, 124302, 127072, 122604, 124309, 127073, 122605, 127074, 124311, 122606, 124312, 127097, 122783, 124313, 127099, 122785, 124314, 127108, 122786, 124315, 127110, 122787, 124318, 122789, 127111, 124319, 127112, 122796, 124321, 127113, 122797, 124322, 127114, 122798, 124323, 127115, 122799, 124324, 127116, 122800, 124326, 127221, 122801, 124454, 127222, 122802, 124456, 127224, 122803, 124458, 127228, 122804, 127229, 122805, 124462, 127231, 122808, 124464, 127234, 122809, 124465, 127235, 124466, 122810, 127237, 122967, 124467, 127238, 123011, 124469, 127240, 123012, 124472, 127241, 123013, 124473, 127247, 123014, 124474, 127249, 123016, 124475, 127250, 123018, 124477, 127619, 123019, 124478, 127620, 128115, 127621, 124643, 127623, 124644, 128116, 127622, 124645, 128117, 128121, 124647, 127625, 127626, 128122, 124648, 128123, 124650, 127627, 128124, 128125, 124651, 124652, 127630, 127631, 128128, 124655, 128130, 127635, 124657, 127637, 127638, 124658, 128131, 128132, 124659, 128133, 124663, 124660, 127641, 127642, 128134, 127643, 128135, 124665, 127644, 124667, 127646, 127645, 128137, 124668, 128138, 128141, 127647, 124808, 128144, 124807, 128145, 127650, 124809, 127651, 124810, 128146, 124812, 127652, 128147, 124814, 128149, 127654, 127657, 124816, 128148, 127659, 128150, 124820, 127661, 128152, 124954, 127662, 125158, 128153, 128154, 127663, 127667, 125159, 122568, 125166, 127670, 127668, 125163, 122569, 122570, 125169, 127673, 125168, 122571, 122572, 127677, 122573, 127678, 125170, 127680, 125171, 122575, 122574, 127681, 125175, 121474, 125176, 127682, 121476, 127683, 125177, 125178, 127684, 125297, 121477, 121479, 127685, 121480, 124960, 127690, 125315, 127692, 127694, 121523, 121519, 124961, 124962, 127695, 121525, 124963, 127698, 121527, 127700, 124967, 124966, 127701, 121528, 124968, 121529, 121530, 127702, 124969, 121531, 121534, 127710, 127703, 124970, 124971, 121535, 127712, 127721, 121536, 124972]

tmprunlist = []
brokenshowers = []
for r in initialrunlist:
  if r not in mybadruns:
    theruninfo = getdb(r)
    tmprunlist.append(r)
    tbs = 1.*theruninfo.brokenshower/theruninfo.bhabha
    brokenshowers.append(tbs)

p = biggles.FramedPlot()
p.add(biggles.Points(tmprunlist, brokenshowers, symboltype="filled circle", symbolsize=1))
p.add(biggles.LineX(123102.5, type="dotted"))
p.add(biggles.LineX(125651.5, type="dotted"))
p.aspect_ratio = 0.5
p.x1.label = "Run number"
p.y1.label = "Broken shower fraction"
p.show()
p.write_eps("/cdat/dafe/mccann/tmp.ps")

def makedense(xy):
  themax = 0
  for x in xy:
    for y in x:
      if y > themax:
        themax = y
  dxy = []
#   for x in Numeric.transpose(xy):
  for x in xy:
    dxy.append([])
    for y in x:
      dxy[-1].append([1-y/themax, 1-y/themax, 1-y/themax])
  return Numeric.array(dxy)

theplot = Numeric.zeros((128,68), 'd')
for r, b in zip(tmprunlist, brokenshowers):
  if b > 0.02 and r < 122400:
    theplot += getdb(r).brokenshower_where
p = biggles.FramedPlot()
p.add(biggles.Density(makedense(theplot), [[0.5,0.5], [128.5,68.5]]))
p.xrange = 0.5, 128.5
p.yrange = 0.5, 68.5
p.add(biggles.LineY(10.5, linetype="dotted"))
p.add(biggles.LineY(58.5, linetype="dotted"))
p.x1.label = "(Cell id - 11) mod 128"
p.x2.label = "angle in radians"
p.x2.range = -pi, pi
p.y1.label = "Ring number (lines are barrel vs. endcap)"
p.y2.label = r"Approximate cot$\theta$ in barrel"
p.y2.range = -2.14, 2.14
p.show()
p.write_eps("/cdat/dafe/mccann/tmp.ps")

theplot = Numeric.zeros((128,68), 'd')
for r, b in zip(tmprunlist, brokenshowers):
  if 0.01 < b and 122400 < r < 124000:
    theplot += getdb(r).brokenshower_where
p = biggles.FramedPlot()
p.add(biggles.Density(makedense(theplot), [[0.5,0.5], [128.5,68.5]]))
p.xrange = 0.5, 128.5
p.yrange = 0.5, 68.5
p.add(biggles.LineY(10.5, linetype="dotted"))
p.add(biggles.LineY(58.5, linetype="dotted"))
p.x1.label = "(Cell id - 11) mod 128"
p.x2.label = "angle in radians"
p.x2.range = -pi, pi
p.y1.label = "Ring number (lines are barrel vs. endcap)"
p.y2.label = r"Approximate cot$\theta$ in barrel"
p.y2.range = -2.14, 2.14
p.show()
p.write_eps("/cdat/dafe/mccann/tmp.ps")

theplot = Numeric.zeros((128,68), 'd')
for r, b in zip(tmprunlist, brokenshowers):
  if b > 0.02 and r > 126000:
    theplot += getdb(r).brokenshower_where
p = biggles.FramedPlot()
p.add(biggles.Density(makedense(theplot), [[0.5,0.5], [128.5,68.5]]))
p.xrange = 0.5, 128.5
p.yrange = 0.5, 68.5
p.add(biggles.LineY(10.5, linetype="dotted"))
p.add(biggles.LineY(58.5, linetype="dotted"))
p.x1.label = "(Cell id - 11) mod 128"
p.x2.label = "angle in radians"
p.x2.range = -pi, pi
p.y1.label = "Ring number (lines are barrel vs. endcap)"
p.y2.label = r"Approximate cot$\theta$ in barrel"
p.y2.range = -2.14, 2.14
p.show()
p.write_eps("/cdat/dafe/mccann/tmp.ps")

theplot = Numeric.zeros((128,68), 'd')
for r, b in zip(tmprunlist, brokenshowers):
  if b > 0.015 and r > 126000:
    theplot += getdb(r).brokenshower_where_tight
p = biggles.FramedPlot()
p.add(biggles.Density(makedense(theplot), [[0.5,0.5], [128.5,68.5]]))
p.xrange = 0.5, 128.5
p.yrange = 0.5, 68.5
p.add(biggles.LineY(10.5, linetype="dotted"))
p.add(biggles.LineY(58.5, linetype="dotted"))
p.x1.label = "(Cell id - 11) mod 128"
p.x2.label = "angle in radians"
p.x2.range = -pi, pi
p.y1.label = "Ring number (lines are barrel vs. endcap)"
p.y2.label = r"Approximate cot$\theta$ in barrel"
p.y2.range = -2.14, 2.14
p.show()
p.write_eps("/cdat/dafe/mccann/tmp.ps")


tmp = []
for r, b in zip(tmprunlist, brokenshowers):
  if b > 0.015:
    tmp.append(r)
tmp.sort()
print tmp



for r, b in zip(tmprunlist, brokenshowers):
  if b > 0.02 and r > 126000:
    print "brokenshower run", r, b







tmprunlist = []
brokenshower_rd = []
for r in rdrunlists["all"]:
  tmprunlist.append(r)
  brokenshower_rd.append(1.*getrd_byrun(r).brokenshower / getrd_byrun(r).bhabha)
p = biggles.FramedPlot()
p.add(biggles.Points(tmprunlist, brokenshower_rd, symboltype="filled circle"))
p.show()

for r, b in zip(tmprunlist, brokenshower_rd):
  if b > 0.1:
    print r


broke_rd = getrd_byrun(122586) + getrd_byrun(122587) + getrd_byrun(122594)
fixed_rd = RunRecord()
for r in rdrunlists["all"]:
  if runsummary[r].res == 3 and runsummary[r].kind == 'c':
    if r not in [122576, 122647, 122586, 122587, 122594]:
      fixed_rd += getrd_byrun(r)

nobeam = getsb("cos")
ebeam = getsb("bge")
pbeam = getsb("bgp")

fixed_rdcor = fixed_rd * 1.
for i in range(10):
  fixed_rdcor += ebeam * (-1.*fixed_rdcor.beamgase/ebeam.beamgase)
  fixed_rdcor += pbeam * (-1.*fixed_rdcor.beamgasp/pbeam.beamgasp)
  fixed_rdcor += nobeam * (-1.*fixed_rdcor.cosmic/nobeam.cosmic)
broke_rdcor = broke_rd * 1.
for i in range(10):
  broke_rdcor += ebeam * (-1.*broke_rdcor.beamgase/ebeam.beamgase)
  broke_rdcor += pbeam * (-1.*broke_rdcor.beamgasp/pbeam.beamgasp)
  broke_rdcor += nobeam * (-1.*broke_rdcor.cosmic/nobeam.cosmic)

print fixed_rd.beamgase, fixed_rdcor.beamgase
print fixed_rd.beamgasp, fixed_rdcor.beamgasp
print fixed_rd.cosmic, fixed_rdcor.cosmic

print broke_rd.beamgase, broke_rdcor.beamgase
print broke_rd.beamgasp, broke_rdcor.beamgasp
print broke_rd.cosmic, broke_rdcor.cosmic

p = (fixed_rd.oldhadronall_r_olde1 / fixed_rd.bhabha).plot()
p.add((broke_rd.oldhadronall_r_olde1 / broke_rd.bhabha).points())
p.add((broke_rd.oldhadronall_r_olde1 / broke_rd.bhabha).errorbars())
p.show()
p.write_eps("/home/mccann/tmp1.ps")

print (1.*fixed_rd.oldhadronall_r_olde1.overflow / fixed_rd.bhabha), \
      (1.*broke_rd.oldhadronall_r_olde1.overflow / broke_rd.bhabha)


p = (fixed_rd.oldhadronall_r_oldccen / fixed_rd.bhabha).plot()
p.add((broke_rd.oldhadronall_r_oldccen / broke_rd.bhabha).points())
p.add((broke_rd.oldhadronall_r_oldccen / broke_rd.bhabha).errorbars())
p.show()
p.write_eps("/home/mccann/tmp2.ps")

print (1.*fixed_rd.oldhadronall_r_oldccen.overflow / fixed_rd.bhabha), \
      (1.*broke_rd.oldhadronall_r_oldccen.overflow / broke_rd.bhabha)

p = (fixed_rdcor.hadron_r_coolvisen / fixed_rdcor.bhabha).plot()
p.add((broke_rdcor.hadron_r_coolvisen / broke_rdcor.bhabha).points())
p.add((broke_rdcor.hadron_r_coolvisen / broke_rdcor.bhabha).errorbars())
p.add(biggles.LineX(0.4, type="dotted"))
p.add(biggles.LineY(0))
p.show()
p.write_eps("/home/mccann/tmp3.ps")

p.yrange = -0.005, 0.03
p.show()
p.write_eps("/home/mccann/tmp4.ps")

print (1.*fixed_rdcor.hadron_r_coolvisen.sum(0.,0.4) / fixed_rdcor.bhabha), \
      (1.*fixed_rdcor.hadron_r_coolvisen.sumerr(0.,0.4) / fixed_rdcor.bhabha), \
      (1.*broke_rdcor.hadron_r_coolvisen.sum(0.,0.4) / broke_rdcor.bhabha), \
      (1.*broke_rdcor.hadron_r_coolvisen.sumerr(0.,0.4) / broke_rdcor.bhabha)

print (1.*fixed_rdcor.hadron_r_coolvisen.sum(0.2,0.4) / fixed_rdcor.bhabha), \
      (1.*fixed_rdcor.hadron_r_coolvisen.sumerr(0.2,0.4) / fixed_rdcor.bhabha), \
      (1.*broke_rdcor.hadron_r_coolvisen.sum(0.2,0.4) / broke_rdcor.bhabha), \
      (1.*broke_rdcor.hadron_r_coolvisen.sumerr(0.2,0.4) / broke_rdcor.bhabha)

print (1.*fixed_rdcor.hadron_r_coolvisen.sum(0.4,1.2) / fixed_rdcor.bhabha)
