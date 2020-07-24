import cPickle, hist, Numeric, math, biggles, random

class RunRecord: pass
run = cPickle.load(open("daf9/lumi2_all.p"))

allnumer = Numeric.zeros((100,64),'d')
alldenom = Numeric.zeros((100,64),'d')
for r in run.values():
  allnumer += r.numer
  alldenom += r.denom

allfrac = Numeric.zeros((100,64),'d')
for i in range(100):
  for j in range(64):
    if alldenom[i,j] > 0.:
      allfrac[i,j] = allnumer[i,j] / alldenom[i,j]
    else:
      allfrac[i,j] = 0.

def look(a, low, high):
  tmp = Numeric.zeros((100,64,3),'d')
  for i in range(100):
    for j in range(64):
      if a[i,j] > high:
        tmp[i,j,0] = tmp[i,j,1] = tmp[i,j,2] = 1.
      elif a[i,j] < low:
        tmp[i,j,0] = tmp[i,j,1] = tmp[i,j,2] = 0.
      else:
        tmp[i,j,0] = tmp[i,j,1] = tmp[i,j,2] = (a[i,j]-low)/(high-low)
#       if 19 < i < 35 and 15 < j < 21:
#         tmp[i,j,0] = 1.
#         tmp[i,j,1] = 0.
#         tmp[i,j,2] = 0.
#       if 75 < i < 82 and 37 < j < 41:
#         tmp[i,j,0] = 1.
#         tmp[i,j,1] = 0.
#         tmp[i,j,2] = 0.
#       if 75 < i < 82 and 58 < j < 62:
#         tmp[i,j,0] = 1.
#         tmp[i,j,1] = 0.
#         tmp[i,j,2] = 0.
  return tmp
p = biggles.FramedPlot()
p.add(biggles.Density(look(allfrac,0.95,1.), ((0, 1.25*math.pi), (1, 0.25*math.pi))))
# p.add(biggles.DataLabel(0.28, 3, "A"))
# p.add(biggles.DataLabel(0.79, 1.99, "B"))
# p.add(biggles.DataLabel(0.79, 0.95, "C"))
p.x1.label = r"|cos$\theta$| of tracks"
p.y1.label = r"$\phi$ of TRACKS (180$\degree$ range)"
p.title = r"BarrelBhabha trigger $\epsilon$ from bhabhas (95%-100%)"
p.xrange = (0.,1.)
p.yrange = (0.25*math.pi-0.2, 1.25*math.pi+0.2)
p.show()
p.write_eps("plottrig2_1.eps")

# tr1phi = -math.pi / 2.
# tr2phi = tr1phi + math.pi
# thefunc = lambda x: (64./2./math.pi*(math.atan2(math.cos(x+(x+math.pi)),math.sin(x+(x+math.pi)))+math.pi))
# p = h1(100,0.*math.pi,1.5*math.pi,func=thefunc).plot(False, lines=True)
# p.add(biggles.LineX(0.25*math.pi))
# p.add(biggles.LineX(1.25*math.pi))
# p.show()

phidist = Numeric.zeros(64, 'd')
for r in run.values():
  phidist += r.phi1
  phidist += r.phi2
  phidist += r.phi3
  phidist += r.phi4
  phidist += r.phi5

p = hist.h1(64, 0.25*math.pi, 1.25*math.pi, vals=phidist[::-1]).rootn().plot(False, points=True, errorbars=True)
p.x1.label = r"$\phi$ of SHOWERS (180$\degree$ range) in 0.45 < |cos$\theta$| < 0.7"
p.yrange = (15000,20000)
p.show()
p.write_eps("plottrig2_2.eps")

# block A,B,C versus run
runnumbers = run.keys()
runnumbers.sort()
a = []
aerr = []
b = []
berr = []
c = []
cerr = []
for r in runnumbers:
  num = 0
  den = 0
  for i in range(20, 35):
    for j in range(16, 21):
      num += run[r].numer[i,j]
      den += run[r].denom[i,j]
  tmp = float(num)/float(den)
  a.append(tmp)
  aerr.append(math.sqrt(tmp*(1.-tmp)/float(den)))

  num = 0
  den = 0
  for i in range(76, 82):
    for j in range(38, 41):
      num += run[r].numer[i,j]
      den += run[r].denom[i,j]
  tmp = float(num)/float(den)
  b.append(tmp)
  berr.append(math.sqrt(tmp*(1.-tmp)/float(den)))

  num = 0
  den = 0
  for i in range(76, 82):
    for j in range(59, 62):
      num += run[r].numer[i,j]
      den += run[r].denom[i,j]
  tmp = float(num)/float(den)
  c.append(tmp)
  cerr.append(math.sqrt(tmp*(1.-tmp)/float(den)))

p = biggles.FramedArray(3,1)
p[0,0].add(biggles.Points(runnumbers, a, symboltype="filled circle", symbolsize=0.5))
p[0,0].add(biggles.SymmetricErrorBarsY(runnumbers, a, aerr))
p[0,0].yrange = (0., 1.1)
p[1,0].add(biggles.Points(runnumbers, b, symboltype="filled circle", symbolsize=0.5))
p[1,0].add(biggles.SymmetricErrorBarsY(runnumbers, b, berr))
p[1,0].yrange = (0., 1.1)
p[2,0].add(biggles.Points(runnumbers, c, symboltype="filled circle", symbolsize=0.5))
p[2,0].add(biggles.SymmetricErrorBarsY(runnumbers, c, cerr))
p[2,0].yrange = (0., 1.1)
p.xlabel = r"$\epsilon$ of blocks A, B, C versus run"

p[0,0].add(biggles.LineX(122354, linetype="longdashed"))
p[1,0].add(biggles.LineX(122354, linetype="longdashed"))
p[2,0].add(biggles.LineX(122354, linetype="longdashed"))
p[2,0].add(biggles.DataLabel(122354+70, 0.2, "122354 (in 3S db17)", texthalign="left"))

p[0,0].add(biggles.LineX(123490, linetype="longdashed"))
p[1,0].add(biggles.LineX(123490, linetype="longdashed"))
p[2,0].add(biggles.LineX(123490, linetype="longdashed"))
p[2,0].add(biggles.DataLabel(123490+70, 0.4, "123490 (in 1S db18)", texthalign="left"))

p[0,0].add(biggles.LineX(128821, linetype="longdashed"))
p[1,0].add(biggles.LineX(128821, linetype="longdashed"))
p[2,0].add(biggles.LineX(128821, linetype="longdashed"))
p[2,0].add(biggles.DataLabel(128821+70, 0.2, "128821 (in 2S db23)", texthalign="left"))
p.show()
p.write_eps("plottrig2_3.eps")




allnumer = Numeric.zeros((100,64),'d')
alldenom = Numeric.zeros((100,64),'d')
for r in run.values():
  allnumer += r.numer
  alldenom += r.denom
thetanumer = Numeric.zeros(100, 'd')
thetadenom = Numeric.zeros(100, 'd')
for i in range(100):
  num = 0
  den = 0
  for j in range(64):
    if not (19-4 < i < 35+4 and 15-2 < j < 21+2)      \
       and not (75-2 < i < 82+2 and 37-2 < j < 41+2)  \
       and not (75-2 < i < 82+2 and 58-2 < j < 62+2):
      num += allnumer[i,j]
      den += alldenom[i,j]
  thetanumer[i] += num
  thetadenom[i] += den
# thetanumer = Numeric.sum(Numeric.transpose(allnumer))
# thetadenom = Numeric.sum(Numeric.transpose(alldenom))
p = (hist.h1(100, 0., 1., vals=thetanumer)/hist.h1(100, 0., 1., vals=thetadenom)).plot(False, points=True, errorbars=True)
p.add(biggles.LineX(0.05, linetype="longdashed"))
p.add(biggles.LineX(0.19, linetype="longdashed"))
p.add(biggles.LineX(0.36, linetype="longdashed"))
p.add(biggles.LineX(0.52, linetype="longdashed"))
p.add(biggles.LineX(0.64, linetype="longdashed"))
p.add(biggles.LineX(0.75, linetype="longdashed"))
p.add(biggles.LineX(0.81, linetype="longdashed"))
p.add(biggles.LineY(1., linetype="solid"))
p.xrange = (0.0, 0.9)
p.yrange = (0.98, 1.002)
p.xlabel = r"|cos$\theta$| of tracks with tile divisions"
p.ylabel = r"$\epsilon$ with blocks A, B, C, removed"
p.show()
p.write_eps("plottrig2_4.eps")

# gamgams grow more slowly than bhabhas
# q = hist.h1(100, 0., 1., vals=thetadenom).plot()
# x = Numeric.arange(0., 0.99, 0.01)
# y = Numeric.arange(0., 0.99, 0.01)
# for i in range(len(y)):
#   y[i] = (1. + math.pow(x[i], 2)) / math.sqrt(1. - math.pow(x[i], 2)) * \
#          hist.h1(100, 0., 1., vals=thetadenom).int()
# q.add(biggles.Curve(x,y))
# q.add(biggles.LineX(0.40, linetype="longdashed"))
# q.add(biggles.LineX(0.52, linetype="longdashed"))
# q.add(biggles.LineX(0.64, linetype="longdashed"))
# q.add(biggles.LineX(0.72, linetype="longdashed"))
# q.show()
# print hist.h1(100, 0., 1., vals=thetadenom).int(0.4, 0.72)
# print hist.h1(100, 0., 1., vals=thetadenom).int(0.72, 1.)




