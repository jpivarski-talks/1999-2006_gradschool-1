# import cPickle
# class RunRecord: pass
# run = {}
# execfile("daf9/relatives.py")
# cPickle.dump(run, open("daf9/relatives.p", "w"))

import cPickle, hist, Numeric, math, biggles, random, jt

class RunRecord: pass
run = cPickle.load(open("/home/mccann/luminosity/run3/daf9/relatives.p"))

# cont1 = [123369, 123370, 123378, 123380, 123382, 123565, 123566, 123567, 123568, 123569, 123570, 123591, 123592, 123767, 123768, 123771, 123772, 123773, 123774, 123775, 123793, 123794, 123796, 123800, 123803, 123809, 123810, 123811, 123812, 123813, 123814, 123815, 123816, 123817, 123818, 123820, 123938, 123939, 123941, 123944, 123951, 123952, 123953, 123955, 123956, 123958, 123959, 123960, 123961, 123962, 124113, 124114, 124115, 124117, 124121, 124123, 124125, 124126, 124127, 124128, 124129, 124132, 124134, 124137, 124138, 124139, 124140, 124141, 124299, 124300, 124301, 124302, 124309, 124311, 124312, 124313, 124314, 124315, 124318, 124319, 124321, 124322, 124323, 124324, 124326, 124454, 124456, 124458, 124462, 124464, 124465, 124466, 124467, 124469, 124472, 124473, 124475, 124477, 124644, 124645, 124647, 124648, 124650, 124651, 124652, 124655, 124657, 124658, 124659, 124660, 124663, 124665, 124667, 124668, 124807, 124808, 124809, 124810, 124812, 124814, 124816, 124820, 125158, 125159, 125163, 125166, 125168, 125169, 125170, 125171, 125175, 125176, 125177, 125178, 125297, 125315]
# cont2 = [126252, 126253, 126254, 126255, 126256, 126257, 126258, 126259, 126260, 126263, 126265, 126266, 126268, 126273, 126471, 126472, 126473, 126475, 126476, 126477, 126478, 126479, 126480, 126483, 126485, 126487, 126488, 126490, 126492, 126494, 126651, 126652, 126653, 126656, 126657, 126658, 126662, 126664, 126665, 126666, 126667, 126668, 126669, 126670, 126673, 126832, 126834, 126835, 126836, 126837, 126838, 126839, 126842, 126845, 126846, 126847, 126851, 126853, 126854, 126855, 126856, 127417, 127418, 127420, 127421, 127422, 127423, 127424, 127442, 127443, 127444, 127619, 127620, 127621, 127622, 127623, 127625, 127626, 127627, 127630, 127631, 127635, 127637, 127638, 127641, 127642, 127643, 127644, 127645, 127646, 127647, 127650, 127651, 127652, 127654, 127657, 127659, 127661, 127662, 127663, 127667, 127668, 127670, 127673, 127677, 127678, 127680, 127681, 127682, 127683, 127684, 127685, 127690, 127692, 127694, 127695, 127698, 127700, 127701, 127702, 127703, 127710, 127712, 127721, 127722, 127723, 128314, 129065, 129066, 129069, 129070, 129071, 129072, 129073, 129080, 129519, 129522, 129524, 129526, 129527, 129529, 129531, 129672, 129673, 129674, 129675, 129676, 129678, 129680, 129681, 129685, 129687, 129689, 129691, 129692, 129693, 129707, 129708, 129709, 129710, 129711, 129712, 129713, 129714, 129715, 129716, 129719, 129723, 129724, 129728, 129730, 129845, 129847, 129848, 129849, 129850, 129851, 129852, 129853, 129855, 129857, 129860, 129861, 129863, 129864, 130199, 130200, 130203, 130204, 130205, 130206, 130207, 130209, 130210, 130247, 130248, 130249, 130250, 130251, 130252, 130254, 130255, 130259, 130271, 130272, 130275, 130276, 130278, 130420, 130421, 130423, 130424, 130425, 130426, 130427, 130429, 130460, 130461, 130462, 130463, 130464, 130467, 130469, 130470, 130614, 130616, 130626, 130628, 130629, 130630]
# cont3 = [121899, 121901, 121902, 121903, 121904, 121905, 121906, 121911, 121912, 121914, 121915, 122064, 122066, 122080, 122081, 122083, 122085, 122091, 122264, 122268, 122269, 122272, 122273, 122418, 122420, 122422, 122423, 122424, 122425, 122426, 122427, 122428, 122429, 122430, 122432, 122433, 122434, 122585, 122586, 122587, 122590, 122593, 122594, 122596, 122599, 122602, 122603, 122604, 122605, 122606, 122783, 122786, 122787, 122789, 122796, 122797, 122798, 122799, 122800, 122801, 122802, 122803, 122804, 122805, 122808, 122809, 122810, 123011, 123012, 123013, 123014, 123016, 123018, 123019]
cont1 = [123369, 123370, 123378, 123380, 123382, 123565, 123566, 123567, 123568, 123569, 123570, 123591, 123592, 123767, 123768, 123771, 123772, 123773, 123774, 123775, 123793, 123794, 123796, 123800, 123803, 123809, 123810, 123811, 123812, 123813, 123814, 123815, 123816, 123817, 123818, 123820, 123938, 123939, 123941, 123944, 123951, 123952, 123953, 123955, 123956, 123958, 123959, 123960, 123961, 123962, 124113, 124114, 124115, 124117, 124121, 124123, 124125, 124126, 124127, 124128, 124129, 124132, 124134, 124137, 124138, 124139, 124140, 124141, 124299, 124300, 124301, 124302, 124309, 124311, 124312, 124313, 124314, 124315, 124318, 124319, 124321, 124322, 124323, 124324, 124326, 124454, 124456, 124458, 124462, 124464, 124465, 124466, 124467, 124469, 124472, 124473, 124475, 124477, 124644, 124645, 124647, 124648, 124650, 124651, 124652, 124655, 124657, 124658, 124659, 124660, 124663, 124665, 124667, 124668, 124807, 124808, 124809, 124810, 124812, 124814, 124816, 124820, 125158, 125159, 125163, 125166, 125168, 125169, 125170, 125171, 125175, 125176, 125177, 125178, 125297, 125315]
cont2 = [126252, 126253, 126254, 126255, 126256, 126257, 126258, 126259, 126260, 126263, 126265, 126266, 126268, 126273, 126471, 126472, 126473, 126475, 126476, 126477, 126478, 126479, 126480, 126483, 126485, 126487, 126488, 126490, 126492, 126494, 126651, 126652, 126653, 126656, 126657, 126658, 126662, 126664, 126665, 126666, 126667, 126668, 126669, 126670, 126673, 126832, 126834, 126835, 126836, 126837, 126838, 126839, 126842, 126845, 126846, 126847, 126851, 126853, 126854, 126855, 126856, 127417, 127418, 127420, 127421, 127422, 127423, 127424, 127442, 127443, 127444, 127619, 127620, 127621, 127622, 127623, 127625, 127626, 127627, 127630, 127631, 127635, 127637, 127638, 127641, 127642, 127643, 127644, 127645, 127646, 127647, 127650, 127651, 127652, 127654, 127657, 127659, 127661, 127662, 127663, 127667, 127668, 127670, 127673, 127677, 127678, 127680, 127681, 127682, 127683, 127684, 127685, 127690, 127692, 127694, 127695, 127698, 127700, 127701, 127702, 127703, 127710, 127712, 127721, 127722, 127723, 128314, 129065, 129066, 129069, 129070, 129071, 129072, 129073, 129080, 129519, 129522, 129524, 129526, 129527, 129529, 129531, 129672, 129673, 129674, 129675, 129676, 129678, 129680, 129681, 129685, 129687, 129689, 129691, 129692, 129693, 129707, 129708, 129709, 129710, 129711, 129712, 129713, 129714, 129715, 129716, 129719, 129723, 129724, 129728, 129730, 129845, 129847, 129848, 129849, 129850, 129851, 129852, 129853, 129855, 129857, 129860, 129861, 129863, 129864, 130199, 130200, 130203, 130204, 130205, 130206, 130207, 130209, 130210, 130247, 130248, 130249, 130250, 130251, 130252, 130254, 130255, 130259, 130271, 130272, 130275, 130276, 130420, 130421, 130423, 130424, 130425, 130426, 130427, 130429, 130460, 130461, 130462, 130463, 130464, 130467, 130469, 130470, 130614, 130616, 130626, 130628, 130629, 130630]
cont3 = [121899, 121901, 121902, 121903, 121904, 121905, 121906, 121911, 121912, 121914, 121915, 122064, 122066, 122080, 122081, 122083, 122085, 122091, 122264, 122268, 122269, 122272, 122273, 122418, 122420, 122422, 122423, 122424, 122425, 122426, 122427, 122428, 122429, 122430, 122432, 122433, 122434, 122585, 122586, 122587, 122590, 122593, 122594, 122596, 122599, 122602, 122603, 122604, 122605, 122606, 122783, 122786, 122787, 122789, 122796, 122797, 122798, 122799, 122800, 122801, 122802, 122803, 122804, 122805, 122808, 122809, 122810, 123011, 123012, 123016, 123018, 123019]

rnum = []
eff = []
efferr = []
trackfrac = []
trackfracerr = []
c1lum = {}
c1lumerr = {}
c2lum = {}
c2lumerr = {}
c3lum = {}
c3lumerr = {}
c1lumphiup = {}
c1lumphiuperr = {}
c2lumphiup = {}
c2lumphiuperr = {}
c3lumphiup = {}
c3lumphiuperr = {}
c1lumphidown = {}
c1lumphidownerr = {}
c2lumphidown = {}
c2lumphidownerr = {}
c3lumphidown = {}
c3lumphidownerr = {}
block1 = []
block2 = []
block3 = []
block4 = []
block5 = []
block6 = []
block1err = []
block2err = []
block3err = []
block4err = []
block5err = []
block6err = []
for r, v in run.items():
  e = float(sum(v.eenom_numer))/float(sum(v.eenom_denom))
  eerr = math.sqrt(e*(1.-e)/float(sum(v.eenom_denom)))
  rnum.append(r)
  eff.append(e)
  efferr.append(eerr)
  tf = float(v.neetrackless)/float(v.neenom)
  tferr = math.sqrt(tf*(1.-tf)/float(v.neenom))
  trackfrac.append(tf)
  trackfracerr.append(tferr)
  if r in cont1:
    c1lum[r] = v.eenom_int[0]
    c1lumerr[r] = v.eenom_int[1]
    c1lumphiup[r] = v.eephiup_int[0]
    c1lumphiuperr[r] = v.eephiup_int[1]
    c1lumphidown[r] = v.eephidown_int[0]
    c1lumphidownerr[r] = v.eephidown_int[1]
  if r in cont2:
    c2lum[r] = v.eenom_int[0]
    c2lumerr[r] = v.eenom_int[1]
    c2lumphiup[r] = v.eephiup_int[0]
    c2lumphiuperr[r] = v.eephiup_int[1]
    c2lumphidown[r] = v.eephidown_int[0]
    c2lumphidownerr[r] = v.eephidown_int[1]
  if r in cont3:
    c3lum[r] = v.eenom_int[0]
    c3lumerr[r] = v.eenom_int[1]
    c3lumphiup[r] = v.eephiup_int[0]
    c3lumphiuperr[r] = v.eephiup_int[1]
    c3lumphidown[r] = v.eephidown_int[0]
    c3lumphidownerr[r] = v.eephidown_int[1]
  b1 = 0
  b2 = 0
  b3 = 0
  b4 = 0
  b5 = 0
  b6 = 0
  n1 = 0
  n2 = 0
  n3 = 0
  n4 = 0
  n5 = 0
  n6 = 0
  for i in range(5, 19):
    b1 += v.eethetaup_numer[i]
    n1 += v.eethetaup_denom[i]
  for i in range(19, 39):
    b2 += v.eenom_numer[i]
    n2 += v.eenom_denom[i]
  for i in range(39, 61):
    b3 += v.eenom_numer[i]
    n3 += v.eenom_denom[i]
  for i in range(61, 83):
    b4 += v.eenom_numer[i]
    n4 += v.eenom_denom[i]
  for i in range(83, 113):
    b5 += v.eenom_numer[i]
    n5 += v.eenom_denom[i]
  for i in range(133, 138):
    b6 += v.eethetadown_numer[i]
    n6 += v.eethetadown_denom[i]
  block1.append(float(b1)/float(n1))
  block1err.append(math.sqrt((float(b1)/float(n1))*(1.-float(b1)/float(n1))/float(n1)))
  block2.append(float(b2)/float(n2))
  block2err.append(math.sqrt((float(b2)/float(n2))*(1.-float(b2)/float(n2))/float(n2)))
  block3.append(float(b3)/float(n3))
  block3err.append(math.sqrt((float(b3)/float(n3))*(1.-float(b3)/float(n3))/float(n3)))
  block4.append(float(b4)/float(n4))
  block4err.append(math.sqrt((float(b4)/float(n4))*(1.-float(b4)/float(n4))/float(n4)))
  block5.append(float(b5)/float(n5))
  block5err.append(math.sqrt((float(b5)/float(n5))*(1.-float(b5)/float(n5))/float(n5)))
  block6.append(float(b6)/float(n6))
  block6err.append(math.sqrt((float(b6)/float(n6))*(1.-float(b6)/float(n6))/float(n6)))
  
p1 = biggles.FramedArray(2,1)
p1[0,0].add(biggles.Points(rnum, eff, symboltype="filled circle", symbolsize=0.2))
p1[0,0].add(biggles.SymmetricErrorBarsY(rnum, eff, efferr))
p1[0,0].add(biggles.LineY(1., linetype="dotted"))
p1[0,0].yrange = (0.987, 1.005)
p1[0,0].xrange = (min(rnum)-100, max(rnum)+100)
p1[1,0].add(biggles.Points(rnum, eff, symboltype="filled circle", symbolsize=0.2))
p1[1,0].add(biggles.SymmetricErrorBarsY(rnum, eff, efferr))
p1[1,0].add(biggles.LineY(1., linetype="dotted"))
p1[1,0].yrange = (0.8, 1.1)
p1[1,0].xrange = (min(rnum)-100, max(rnum)+100)
p1.xlabel = "Run number"
p1.ylabel = "BarrelBhabha trigger efficiency"
p1[1,0].add(biggles.PlotLabel(0.25,0.25,"same outliers as last time"))
p1.show()
p1.write_eps("plottrig3_p1.eps")
print map(lambda (r, e): r, filter(lambda (r, e): e<0.99, zip(rnum, eff)))
print filter(lambda (r, err): err==0., zip(rnum, efferr))

p1 = biggles.FramedPlot()
p1.add(biggles.Points(rnum, eff, symboltype="filled circle", symbolsize=0.7))
p1.add(biggles.SymmetricErrorBarsY(rnum, eff, efferr))
p1.add(biggles.LineY(1., linetype="dotted"))
p1.yrange = (0.987, 1.005)
p1.xrange = (min(rnum)-100, max(rnum)+100)
p1.x1.label = "Run number"
p1.y1.label = "BarrelBhabha trigger efficiency"
p1.add(biggles.PlotLabel(0.5,0.15,"five outliers, all with suspicious notes in Elog"))
p1.aspect_ratio = 8.5/11./1.5
# p1.show()
p1.write_eps("/home/mccann/synthesis/lumieff/ptatalk/afterexclude.eps")






effmean, effmeanerr = jt.wmean(zip(eff, efferr))
effsigmas = map(lambda (e, err): (e-effmean)/(err+1e-10), zip(eff,efferr))
p1ahist = hist.h1(100, -5., 5.).fill(effsigmas)
p1a = p1ahist.plot()
p1a.xlabel = "Sigmas away from mean efficiency of "+("%3.1f%s" % (effmean*100., "%"))
effmeanmean = jt.mean(filter(lambda x: math.fabs(x)<5, effsigmas))
effstdev = jt.stdev(filter(lambda x: math.fabs(x)<5, effsigmas))
efffailures = sorted(zip(*filter(lambda (r,e): e<-5., zip(rnum, effsigmas)))[0])
addinfobox(p1a, [["stdev", effstdev], ["underflow", p1ahist.underflow]] + efffailures, numformat="%g")
def effgauss(x):
  return math.exp(-(x-effmeanmean)**2/2./effstdev)/math.sqrt(2.*math.pi)/effstdev
p1a.add((hist.h1(100, -5., 5., func=effgauss)*p1ahist.int()).lines(True))
p1a.show()
p1a.write_eps("plottrig3_p1a.eps")

print filter(lambda (r,e,e2): r==130278, zip(rnum, eff, efferr))

print p1ahist.overflow

print filter(lambda (r,e): e>5., zip(rnum, effsigmas))

print filter(lambda (r,e,e2): r==122619, zip(rnum, eff, efferr))

pb1 = biggles.FramedArray(2,1)
pb1[0,0].add(biggles.Points(rnum, block1, symboltype="filled circle", symbolsize=0.2))
pb1[0,0].add(biggles.SymmetricErrorBarsY(rnum, block1, block1err))
pb1[0,0].add(biggles.LineY(1., linetype="dotted"))
pb1[0,0].yrange = (0.975, 1.005)
pb1[0,0].xrange = (min(rnum)-100, max(rnum)+100)
pb1[1,0].add(biggles.Points(rnum, block1, symboltype="filled circle", symbolsize=0.2))
pb1[1,0].add(biggles.SymmetricErrorBarsY(rnum, block1, block1err))
pb1[1,0].add(biggles.LineY(1., linetype="dotted"))
pb1[1,0].yrange = (0., 1.1)
pb1[1,0].xrange = (min(rnum)-100, max(rnum)+100)
pb1.xlabel = "Run number"
pb1.ylabel = r"BB trigger efficiency in $\theta$ tile 1"
pb1[1,0].add(biggles.PlotLabel(0.25,0.25,"same outliers as last time"))
pb1.show()
pb1.write_eps("plottrig3_pb1.eps")
print map(lambda (r, e): r, filter(lambda (r, e): e<0.98, zip(rnum, block1)))

pb2 = biggles.FramedArray(2,1)
pb2[0,0].add(biggles.Points(rnum, block2, symboltype="filled circle", symbolsize=0.2))
pb2[0,0].add(biggles.SymmetricErrorBarsY(rnum, block2, block2err))
pb2[0,0].add(biggles.LineY(1., linetype="dotted"))
pb2[0,0].yrange = (0.975, 1.005)
pb2[0,0].xrange = (min(rnum)-100, max(rnum)+100)
pb2[1,0].add(biggles.Points(rnum, block2, symboltype="filled circle", symbolsize=0.2))
pb2[1,0].add(biggles.SymmetricErrorBarsY(rnum, block2, block2err))
pb2[1,0].add(biggles.LineY(1., linetype="dotted"))
pb2[1,0].yrange = (0., 1.1)
pb2[1,0].xrange = (min(rnum)-100, max(rnum)+100)
pb2.xlabel = "Run number"
pb2.ylabel = r"BB trigger efficiency in $\theta$ tile 2"
pb2[1,0].add(biggles.PlotLabel(0.25,0.25,"same outliers as last time"))
pb2.show()
pb2.write_eps("plottrig3_pb2.eps")
print map(lambda (r, e): r, filter(lambda (r, e): e<0.98, zip(rnum, block2)))

pb3 = biggles.FramedArray(2,1)
pb3[0,0].add(biggles.Points(rnum, block3, symboltype="filled circle", symbolsize=0.2))
pb3[0,0].add(biggles.SymmetricErrorBarsY(rnum, block3, block3err))
pb3[0,0].add(biggles.LineY(1., linetype="dotted"))
pb3[0,0].yrange = (0.975, 1.005)
pb3[0,0].xrange = (min(rnum)-100, max(rnum)+100)
pb3[1,0].add(biggles.Points(rnum, block3, symboltype="filled circle", symbolsize=0.2))
pb3[1,0].add(biggles.SymmetricErrorBarsY(rnum, block3, block3err))
pb3[1,0].add(biggles.LineY(1., linetype="dotted"))
pb3[1,0].yrange = (0., 1.1)
pb3[1,0].xrange = (min(rnum)-100, max(rnum)+100)
pb3.xlabel = "Run number"
pb3.ylabel = r"BB trigger efficiency in $\theta$ tile 3"
pb3[1,0].add(biggles.PlotLabel(0.25,0.25,"same outliers as last time"))
pb3.show()
pb3.write_eps("plottrig3_pb3.eps")
print map(lambda (r, e): r, filter(lambda (r, e): e<0.98, zip(rnum, block3)))

pb4 = biggles.FramedArray(2,1)
pb4[0,0].add(biggles.Points(rnum, block4, symboltype="filled circle", symbolsize=0.2))
pb4[0,0].add(biggles.SymmetricErrorBarsY(rnum, block4, block4err))
pb4[0,0].add(biggles.LineY(1., linetype="dotted"))
pb4[0,0].yrange = (0.975, 1.005)
pb4[0,0].xrange = (min(rnum)-100, max(rnum)+100)
pb4[1,0].add(biggles.Points(rnum, block4, symboltype="filled circle", symbolsize=0.2))
pb4[1,0].add(biggles.SymmetricErrorBarsY(rnum, block4, block4err))
pb4[1,0].add(biggles.LineY(1., linetype="dotted"))
pb4[1,0].yrange = (0., 1.1)
pb4[1,0].xrange = (min(rnum)-100, max(rnum)+100)
pb4.xlabel = "Run number"
pb4.ylabel = r"BB trigger efficiency in $\theta$ tile 4"
pb4[1,0].add(biggles.PlotLabel(0.25,0.25,"same outliers as last time"))
pb4.show()
pb4.write_eps("plottrig3_pb4.eps")
print map(lambda (r, e): r, filter(lambda (r, e): e<0.98, zip(rnum, block4)))

pb5 = biggles.FramedArray(2,1)
pb5[0,0].add(biggles.Points(rnum, block5, symboltype="filled circle", symbolsize=0.2))
pb5[0,0].add(biggles.SymmetricErrorBarsY(rnum, block5, block5err))
pb5[0,0].add(biggles.LineY(1., linetype="dotted"))
pb5[0,0].yrange = (0.975, 1.005)
pb5[0,0].xrange = (min(rnum)-100, max(rnum)+100)
pb5[1,0].add(biggles.Points(rnum, block5, symboltype="filled circle", symbolsize=0.2))
pb5[1,0].add(biggles.SymmetricErrorBarsY(rnum, block5, block5err))
pb5[1,0].add(biggles.LineY(1., linetype="dotted"))
pb5[1,0].yrange = (0., 1.1)
pb5[1,0].xrange = (min(rnum)-100, max(rnum)+100)
pb5.xlabel = "Run number"
pb5.ylabel = r"BB trigger efficiency in $\theta$ tile 5"
pb5[1,0].add(biggles.PlotLabel(0.25,0.25,"same outliers as last time"))
pb5.show()
pb5.write_eps("plottrig3_pb5.eps")
print map(lambda (r, e): r, filter(lambda (r, e): e<0.98, zip(rnum, block5)))

pb6 = biggles.FramedArray(2,1)
pb6[0,0].add(biggles.Points(rnum, block6, symboltype="filled circle", symbolsize=0.2))
pb6[0,0].add(biggles.SymmetricErrorBarsY(rnum, block6, block6err))
pb6[0,0].add(biggles.LineY(1., linetype="dotted"))
pb6[0,0].yrange = (0.975, 1.005)
pb6[0,0].xrange = (min(rnum)-100, max(rnum)+100)
pb6[1,0].add(biggles.Points(rnum, block6, symboltype="filled circle", symbolsize=0.2))
pb6[1,0].add(biggles.SymmetricErrorBarsY(rnum, block6, block6err))
pb6[1,0].add(biggles.LineY(1., linetype="dotted"))
pb6[1,0].yrange = (0., 1.1)
pb6[1,0].xrange = (min(rnum)-100, max(rnum)+100)
pb6.xlabel = "Run number"
pb6.ylabel = r"BB trigger efficiency in $\theta$ tile 6"
pb6[1,0].add(biggles.PlotLabel(0.25,0.25,"same outliers as last time"))
pb6.show()
pb6.write_eps("plottrig3_pb6.eps")
print map(lambda (r, e): r, filter(lambda (r, e): e<0.98, zip(rnum, block6)))






print map(lambda (r, e, er): r, filter(lambda (r, e, er): math.fabs(e-0.996)>3*er and e<0.996, zip(rnum, block1, block1err)))
print map(lambda (r, e, er): r, filter(lambda (r, e, er): math.fabs(e-0.996)>3*er and e<0.996, zip(rnum, block2, block2err)))
print map(lambda (r, e, er): r, filter(lambda (r, e, er): math.fabs(e-0.996)>3*er and e<0.996, zip(rnum, block3, block3err)))
print map(lambda (r, e, er): r, filter(lambda (r, e, er): math.fabs(e-0.996)>3*er and e<0.996, zip(rnum, block4, block4err)))
print map(lambda (r, e, er): r, filter(lambda (r, e, er): math.fabs(e-0.996)>3*er and e<0.996, zip(rnum, block5, block5err)))
print map(lambda (r, e, er): r, filter(lambda (r, e, er): math.fabs(e-0.996)>3*er and e<0.996, zip(rnum, block6, block6err)))


print filter(lambda (r, e, er): math.fabs(e-0.996)>3*er and e<0.996, zip(rnum, block4, block4err))

for i in range(len(rnum)):
  if rnum[i] == 130421:
    print i

print block1[1263], block1err[1263], \
      block2[1263], block2err[1263], \
      block3[1263], block3err[1263], \
      block4[1263], block4err[1263], \
      block5[1263], block5err[1263], \
      block6[1263], block6err[1263]

numer = hist.h1(138, 0., 1.38, vals=run[130421].eenom_numer)
denom = hist.h1(138, 0., 1.38, vals=run[130421].eenom_denom)
tmp = (numer / denom).plot(False, points=True, errorbars=True)
tmp.yrange = (0.9, 1.05)
tmp.xlabel = r"cot$\theta$ of run 130421, a continuum run"
tmp.ylabel = r"BhabhaBarrel trigger efficiency"
tmp.show()
tmp.write_eps("plottrig3_pb7.eps")


p2 = biggles.FramedPlot()
rnumgap, tfgap, tferrgap = zip(*filter(lambda (x,y,z): y>0., zip(rnum, trackfrac, trackfracerr)))
p2.add(biggles.Points(rnumgap, tfgap, symboltype="filled circle", symbolsize=0.2))
p2.add(biggles.SymmetricErrorBarsY(rnumgap, tfgap, tferrgap))
p2.xrange = (min(rnum)-100, max(rnum)+100)
p2.yrange = (0.0001, 1.)
p2.ylog = 1
p2.y1.label = r"Fraction of bhabhas which are trackless"
p2.y2.label = r"Fraction of ``gamgams'' which are really bhabhas"
p2.y2.range = p2.yrange[0]*0.00088*8.347, p2.yrange[1]*0.00088*8.347
p2.x1.label = "Run number"
p2.show()
p2.write_eps("plottrig3_p2.eps")

tfmean, tfmeanerr = jt.wmean(zip(trackfrac, trackfracerr))
tfsigmas = map(lambda (x,y): (x-tfmean)/y, zip(tfgap, tferrgap))
rnumgapgap, tfsigmasgapgap = zip(*filter(lambda (r,s): s<5, zip(rnumgap, tfsigmas)))
tfsigmasggmean, tfsigmasggstdev = jt.mean(tfsigmasgapgap), jt.stdev(tfsigmasgapgap)

def tfgauss(x):
  return math.exp(-(x-tfsigmasggmean)**2/2./tfsigmasggstdev**2)/math.sqrt(2.*math.pi)/tfsigmasggstdev

tfsigmashist = hist.h1(100, -10., 25.).fill(tfsigmas)
p5 = tfsigmashist.plot()
p5.add((hist.h1(100, -10., 5., func=tfgauss)*tfsigmashist.int(-10., 5.)).lines(True))
p5.xlabel = "Stdevs away from wmean trackless bhabha fraction"
# p5.show()
rnumantigapgap, tfsigmasantigapgap = zip(*sorted(filter(lambda (r,s): s>5, zip(rnumgap, tfsigmas)), lambda (x1,y1), (x2,y2): y2>y1 or x2>x1))
# print rnumantigapgap
p5height = 0.15
for r, v in zip(rnumantigapgap, tfsigmasantigapgap):
  p5.add(biggles.PlotLabel(0.67, p5height, "%d has %3.1f%s, %3.1f%s" % (r, float(run[r].neetrackless)/float(run[r].neenom)*100., "%", v, r"$\sigma$'s")))
  p5height += 0.05
p5.show()
p5.write_eps("plottrig3_p5.eps")





# This is the end of the work you have done so far.  13 April 1:30 PM
# Below this is OPENING THE BOX...


execfile("somehadrons.py")
had1 = []
had1err = []
had1phiup = []
had1phiuperr = []
had1phidown = []
had1phidownerr = []
had2 = []
had2err = []
had2phiup = []
had2phiuperr = []
had2phidown = []
had2phidownerr = []
had3 = []
had3err = []
had3phiup = []
had3phiuperr = []
had3phidown = []
had3phidownerr = []
for c in cont1:
  had1.append(hadrons[c]/c1lum[c])
  had1err.append(hadrons[c]/c1lum[c]*math.sqrt(1./float(hadrons[c])+(float(c1lumerr[c])/float(c1lum[c]))**2))
  had1phiup.append(hadrons[c]/c1lumphiup[c])
  had1phiuperr.append(hadrons[c]/c1lumphiup[c]*math.sqrt(1./float(hadrons[c])+(float(c1lumphiuperr[c])/float(c1lumphiup[c]))**2))
  had1phidown.append(hadrons[c]/c1lumphidown[c])
  had1phidownerr.append(hadrons[c]/c1lumphidown[c]*math.sqrt(1./float(hadrons[c])+(float(c1lumphidownerr[c])/float(c1lumphidown[c]))**2))
for c in cont2:
  had2.append(hadrons[c]/c2lum[c])
  had2err.append(hadrons[c]/c2lum[c]*math.sqrt(1./float(hadrons[c])+(float(c2lumerr[c])/float(c2lum[c]))**2))
  had2phiup.append(hadrons[c]/c2lumphiup[c])
  had2phiuperr.append(hadrons[c]/c2lumphiup[c]*math.sqrt(1./float(hadrons[c])+(float(c2lumphiuperr[c])/float(c2lumphiup[c]))**2))
  had2phidown.append(hadrons[c]/c2lumphidown[c])
  had2phidownerr.append(hadrons[c]/c2lumphidown[c]*math.sqrt(1./float(hadrons[c])+(float(c2lumphidownerr[c])/float(c2lumphidown[c]))**2))
for c in cont3:
  had3.append(hadrons[c]/c3lum[c])
  had3err.append(hadrons[c]/c3lum[c]*math.sqrt(1./float(hadrons[c])+(float(c3lumerr[c])/float(c3lum[c]))**2))
  had3phiup.append(hadrons[c]/c3lumphiup[c])
  had3phiuperr.append(hadrons[c]/c3lumphiup[c]*math.sqrt(1./float(hadrons[c])+(float(c3lumphiuperr[c])/float(c3lumphiup[c]))**2))
  had3phidown.append(hadrons[c]/c3lumphidown[c])
  had3phidownerr.append(hadrons[c]/c3lumphidown[c]*math.sqrt(1./float(hadrons[c])+(float(c3lumphidownerr[c])/float(c3lumphidown[c]))**2))

# p3 = biggles.Table(3,1)
# p3[0,0] = biggles.FramedPlot()
# p3[1,0] = biggles.FramedPlot()
# p3[2,0] = biggles.FramedPlot()
# p3[0,0].add(biggles.Points(cont1, had1, symboltype="filled circle", symbolsize=0.2))
# p3[0,0].add(biggles.SymmetricErrorBarsY(cont1, had1, had1err))
# p3[0,0].ylabel = r"$\propto$ $\Upsilon(1S)$ continuum $\sigma$"
# p3[1,0].add(biggles.Points(cont2, had2, symboltype="filled circle", symbolsize=0.2))
# p3[1,0].add(biggles.SymmetricErrorBarsY(cont2, had2, had2err))
# p3[1,0].ylabel = r"$\propto$ $\Upsilon(2S)$ continuum $\sigma$"
# p3[2,0].add(biggles.Points(cont3, had3, symboltype="filled circle", symbolsize=0.2))
# p3[2,0].add(biggles.SymmetricErrorBarsY(cont3, had3, had3err))
# p3[2,0].xlabel = "Run number (continuum runs only)"
# p3[2,0].ylabel = r"$\propto$ $\Upsilon(3S)$ continuum $\sigma$"
# p3.show()
# p3.write_eps("plottrig3_p3.eps")

recont3 = range(1,8)
rehad3 = [0] * 7
rehad3err = [0] * 7
reenn3 = [0] * 7

def putitin(run_number):
  if run_number < 122000: return 1
  elif run_number < 122200: return 2
  elif run_number < 122350: return 3
  elif run_number < 122500: return 4
  elif run_number < 122700: return 5
  elif run_number < 122900: return 6
  else: return 7

for i in range(len(had3)):
  print putitin(cont3[i])-1
  rehad3[putitin(cont3[i])-1] += had3[i]
  rehad3err[putitin(cont3[i])-1] += had3err[i]**2
  reenn3[putitin(cont3[i])-1] += 1
for i in range(len(rehad3err)):
  rehad3[i] = float(rehad3[i])/float(reenn3[i])
  rehad3err[i] = float(math.sqrt(rehad3err[i]))/float(reenn3[i])

print zip(recont3, rehad3, rehad3err)


p4 = biggles.Table(2,1)
p4[0,0] = biggles.FramedPlot()
p4[0,0].add(biggles.Points(cont3, had3, symboltype="filled circle", symbolsize=0.2))
p4[0,0].add(biggles.SymmetricErrorBarsY(cont3, had3, had3err))
p4[0,0].add(biggles.LineX(122000, linetype="longdashed"))
p4[0,0].add(biggles.LineX(122200, linetype="longdashed"))
p4[0,0].add(biggles.LineX(122350, linetype="longdashed"))
p4[0,0].add(biggles.LineX(122500, linetype="longdashed"))
p4[0,0].add(biggles.LineX(122700, linetype="longdashed"))
p4[0,0].add(biggles.LineX(122900, linetype="longdashed"))
p4[0,0].yrange = 5.5, 7
p4[0,0].y1.label = r"below $\Upsilon(3S)$ hadronic $\sigma$, arb. units"
p4[0,0].xlabel = "Run number"
p4[1,0] = biggles.FramedPlot()
p4[1,0].add(biggles.Points(recont3, rehad3, symboltype="filled circle", symbolsize=1))
p4[1,0].add(biggles.SymmetricErrorBarsY(recont3, rehad3, rehad3err))
rec3mean, rec3stdev = jt.wmean(zip(had3, had3err))
p4[1,0].add(biggles.LineY(rec3mean + rec3stdev, linetype="dotted"))
p4[1,0].add(biggles.LineY(rec3mean, linetype="longdashed"))
p4[1,0].add(biggles.LineY(rec3mean - rec3stdev, linetype="dotted"))
p4[1,0].xrange = 0.5, 7.5
p4[1,0].yrange = 5.5, 7
p4[1,0].y1.label = r"below $\Upsilon(3S)$ hadronic $\sigma$, arb. units"
p4.show()
p4.write_eps("plottrig3_p4.eps")


execfile("rigamgam.py")
execfile("ribhabha.py")
reNN = [0] * 7
reNhad = [0] * 7
reNhaderr = [0] * 7
rec3lum = [0] * 7
rec3lumerr = [0] * 7
rerigglum = [0] * 7
rerigglumerr = [0] * 7
reribblum = [0] * 7
reribblumerr = [0] * 7
for c in cont3:
  i = putitin(c)-1
  reNN[i] += 1
  reNhad[i] += hadrons[c]
  rec3lum[i] += c3lum[c]
  rec3lumerr[i] += c3lumerr[c]**2
  rerigglum[i] += rigamgam[c][0]
  rerigglumerr[i] += rigamgam[c][1]**2
  reribblum[i] += ribhabha[c][0]
  reribblumerr[i] += ribhabha[c][1]**2
hadxs_rec3lum = [0] * 7
hadxs_rec3lumerr = [0] * 7
hadxs_rerigglum = [0] * 7
hadxs_rerigglumerr = [0] * 7
hadxs_reribblum = [0] * 7
hadxs_reribblumerr = [0] * 7
for i in range(7):
  reNhaderr[i] = math.sqrt(reNhad[i])
  rec3lumerr[i] = math.sqrt(rec3lumerr[i])
  rerigglumerr[i] = math.sqrt(rerigglumerr[i])
  reribblumerr[i] = math.sqrt(reribblumerr[i])
  hadxs_rec3lum[i] = float(reNhad[i])/float(rec3lum[i])
  hadxs_rec3lumerr[i] = hadxs_rec3lum[i] * math.sqrt((float(reNhaderr[i])/float(reNhad[i]))**2 + (float(rec3lumerr[i])/float(rec3lum[i]))**2)
  hadxs_rerigglum[i] = float(reNhad[i])/float(rerigglum[i])
  hadxs_rerigglumerr[i] = hadxs_rerigglum[i] * math.sqrt((float(reNhaderr[i])/float(reNhad[i]))**2 + (float(rerigglumerr[i])/float(rerigglum[i]))**2)
  hadxs_reribblum[i] = float(reNhad[i])/float(reribblum[i])
  hadxs_reribblumerr[i] = hadxs_reribblum[i] * math.sqrt((float(reNhaderr[i])/float(reNhad[i]))**2 + (float(reribblumerr[i])/float(reribblum[i]))**2)

fudge_factor = 0.9
p4a = biggles.FramedPlot()
p4a_me = biggles.Points(recont3, fudge_factor*Numeric.array(hadxs_rec3lum), symboltype="filled circle", symbolsize=2)
p4a_me.label = r"from my $\gamma\gamma$ luminosity"
p4a.add(p4a_me)
p4a.add(biggles.SymmetricErrorBarsY(recont3, fudge_factor*Numeric.array(hadxs_rec3lum), fudge_factor*Numeric.array(hadxs_rec3lumerr)))
p4a_gg = biggles.Points(Numeric.array(recont3)+0.1, hadxs_rerigglum, symboltype="diamond", symbolsize=2)
p4a_gg.label = r"from RunInfo's $\gamma\gamma$ luminosity"
p4a.add(p4a_gg)
p4a.add(biggles.SymmetricErrorBarsY(Numeric.array(recont3)+0.1, hadxs_rerigglum, hadxs_rerigglumerr))
p4a_bb = biggles.Points(Numeric.array(recont3)+0.2, hadxs_reribblum, symboltype="triangle", symbolsize=2)
p4a_bb.label = r"from RunInfo's $e^+e^-$ luminosity"
p4a.add(p4a_bb)
p4a.add(biggles.SymmetricErrorBarsY(Numeric.array(recont3)+0.2, hadxs_reribblum, hadxs_reribblumerr))
p4a.add(biggles.PlotKey(0.1, 0.2, [p4a_me, p4a_gg, p4a_bb]))
p4a.xrange = 0.5, 7.5
p4a.yrange = 5, 6
p4a.y1.label = r"below $\Upsilon(3S)$ hadronic $\sigma$, runinfo's units"
p4a.show()
p4a.write_eps("plottrig3_p4a.eps")



