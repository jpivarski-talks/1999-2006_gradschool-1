import cPickle, hist, Numeric, math, biggles, random

# import cPickle
# class RunRecord:
#   def __init__(self, events = 0, gamgams = 0, bhabhas = 0, phi1 = [], phi2 = [], phi3 = [], phi4 = [], phi5 = [], numer = [], denom = [], numer_region = 0, denom_region = 0):
#     self.events = events
#     self.gamgams = gamgams
#     self.bhabhas = bhabhas
#     self.phi1 = phi1
#     self.phi2 = phi2
#     self.phi3 = phi3
#     self.phi4 = phi4
#     self.phi5 = phi5
#     self.numer = numer
#     self.denom = denom
#     self.numer_region = numer_region
#     self.denom_region = denom_region
# run = {}
# execfile("lumis.py")
# cPickle.dump((RunRecord, run), open("daf9/lumis2.p", "w"), -1)



class RunRecord: pass
(RunRecord, run) = cPickle.load(open("daf9/lumis.p"))

x = [] ; y = [] ; yerr = [] ; n = []
for r, ru in run.iteritems():
    x.append(r)
    frac = float(ru.numer_region)/float(ru.denom_region)
    y.append(frac)
    yerr.append(math.sqrt(frac*(1.-frac)/float(ru.denom_region)))
    n.append(float(ru.denom_region))

fracerrs = biggles.FramedArray(2, 1)
fracerrs.uniform_limits = 0
fracerrs[0,0].add(biggles.Points(x,y, symboltype="filled circle", symbolsize=0.5))
fracerrs[0,0].add(biggles.SymmetricErrorBarsY(x,y,yerr))
fracerrs[0,0].yrange = (0.99,1.0)
fracerrs[1,0].add(biggles.Points(x,y, symboltype="filled circle", symbolsize=0.5))
fracerrs[1,0].add(biggles.SymmetricErrorBarsY(x,y,yerr))
fracerrs[1,0].yrange = (0.8,1.02)
fracerrs.xlabel = "Run numbers"
fracerrs.ylabel = "BhabhaBarrel trigger efficiency"
fracerrs.show()
fracerrs.write_eps("plottrig_1.eps")

ylow, nlow = zip(*filter(lambda (yi, ni): yi < 0.99, zip(y,n)))
context = biggles.FramedArray(2, 1)
context[0,0].add(hist.h1(100, 0, 20000).fill(n).steps(True))
context[1,0].add(biggles.Points(n,y, symboltype="dot"))
context[1,0].add(biggles.Points(list(nlow),list(ylow), symboltype="circle", symbolsize=3))
context.xlabel = "Number of bhabha events"
context.ylabel = "Efficiency and histogram projection"
context.show()
context.write_eps("plottrig_2.eps")

sigmas = []
ymedian = hist.prehist(y).median
for yi, yerri in zip(y, yerr):
  if yerri == 0.:
    sigmas.append(1000.)
  else:
    sigmas.append(float(yi-ymedian)/float(yerri))
r = hist.prehist(sigmas)
sigshist = hist.h1(30, -6, 6).fill(sigmas)
sigsplot = sigshist.plot(False)
sigsplot.add(sigshist.stepsfill(-6, -2, True))
sigsplot.add(sigshist.stepsfill(2, 6, True))
sigsplot.add(sigshist.steps(True))
sigsplot.x1.label = "Sigmas away from median efficiency"
sigsplot.add(biggles.PlotLabel(1./6., 1./5., str(int(round(sigshist.sum(-6, -2) + sigshist.underflow)))+r" runs with low $\epsilon$", angle=90, halign="left"))
sigsplot.add(biggles.PlotLabel(5./6., 1./5., str(int(round(sigshist.sum(2, 6) + sigshist.overflow)))+r" runs with high $\epsilon$", angle=90, halign="left"))
sigsplot.add(biggles.PlotLabel(0.5, 1./5., str(int(round(sigshist.sum(-6, 6) + sigshist.overflow + sigshist.underflow)))+r" runs total", angle=90, halign="left"))
sigsplot.show()
sigsplot.write_eps("plottrig_3.eps")

newplot = biggles.FramedArray(5, 1)
num = hist.h1(100, 0, 1)
den = hist.h1(100, 0, 1)
num.vals = 0. + Numeric.array(run[121928].numer)
den.vals = 0. + Numeric.array(run[121928].denom)
newplot[0,0].add((num / den).points(True, symboltype="filled circle", symbolsize=1))
newplot[0,0].add((num / den).errorbars(True))
newplot[0,0].add(biggles.LineY(1, linetype="dotted"))
newplot[0,0].add(biggles.LineX(0.45, linetype="longdashed"))
newplot[0,0].add(biggles.LineX(0.70, linetype="longdashed"))
newplot[0,0].add(biggles.PlotLabel(0.1, 0.85, "121928"))
newplot[0,0].add(biggles.PlotLabel(0.675, 0.2, "accepted region"))
num = hist.h1(100, 0, 1)
den = hist.h1(100, 0, 1)
num.vals = 0. + Numeric.array(run[121929].numer)
den.vals = 0. + Numeric.array(run[121929].denom)
newplot[1,0].add((num / den).points(True, symboltype="filled circle", symbolsize=1))
newplot[1,0].add((num / den).errorbars(True))
newplot[1,0].add(biggles.LineY(1, linetype="dotted"))
newplot[1,0].add(biggles.LineX(0.45, linetype="longdashed"))
newplot[1,0].add(biggles.LineX(0.70, linetype="longdashed"))
newplot[1,0].add(biggles.PlotLabel(0.1, 0.85, "121929"))
num = hist.h1(100, 0, 1)
den = hist.h1(100, 0, 1)
num.vals = 0. + Numeric.array(run[121953].numer)
den.vals = 0. + Numeric.array(run[121953].denom)
newplot[2,0].add((num / den).points(True, symboltype="filled circle", symbolsize=1))
newplot[2,0].add((num / den).errorbars(True))
newplot[2,0].add(biggles.LineY(1, linetype="dotted"))
newplot[2,0].add(biggles.LineX(0.45, linetype="longdashed"))
newplot[2,0].add(biggles.LineX(0.70, linetype="longdashed"))
newplot[2,0].add(biggles.PlotLabel(0.1, 0.85, "121953"))
num = hist.h1(100, 0, 1)
den = hist.h1(100, 0, 1)
num.vals = 0. + Numeric.array(run[127951].numer)
den.vals = 0. + Numeric.array(run[127951].denom)
newplot[3,0].add((num / den).points(True, symboltype="filled circle", symbolsize=1))
newplot[3,0].add((num / den).errorbars(True))
newplot[3,0].add(biggles.LineY(1, linetype="dotted"))
newplot[3,0].add(biggles.LineX(0.45, linetype="longdashed"))
newplot[3,0].add(biggles.LineX(0.70, linetype="longdashed"))
newplot[3,0].add(biggles.PlotLabel(0.1, 0.85, "127951"))
num = hist.h1(100, 0, 1)
den = hist.h1(100, 0, 1)
num.vals = 0. + Numeric.array(run[127955].numer)
den.vals = 0. + Numeric.array(run[127955].denom)
newplot[4,0].add((num / den).points(True, symboltype="filled circle", symbolsize=1))
newplot[4,0].add((num / den).errorbars(True))
newplot[4,0].add(biggles.LineY(1, linetype="dotted"))
newplot[4,0].add(biggles.LineX(0.45, linetype="longdashed"))
newplot[4,0].add(biggles.LineX(0.70, linetype="longdashed"))
newplot[4,0].add(biggles.PlotLabel(0.1, 0.85, "127955"))
newplot.yrange = (0.5, 1.2)
newplot.xrange = (-0.1, 0.9)
newplot.xlabel = r"average cos($\theta$) of bhabha tracks"
newplot.ylabel = "BhabhaBarrel trigger efficiency"
newplot.show()
newplot.write_eps("plottrig_4.eps")

num = hist.h1(100, 0, 1)
den = hist.h1(100, 0, 1)
for ru in run.values():
  num.vals += Numeric.array(ru.numer)
  den.vals += Numeric.array(ru.denom)
newerplot = biggles.FramedArray(3,1)
newerplot[0,0].add(den.stepsfill(0.45, 0.70, True))
newerplot[0,0].add(den.steps(True))
newerplot[0,0].add(biggles.PlotLabel(0.5,0.5,("%3.1f%s lies in the accepted region" % (den.sum(0.45, 0.7)/den.sum(0., 1.)*100., "%"))))
newerplot[1,0].add((num/den).points(True))
newerplot[1,0].add((num/den).errorbars(True))
newerplot[1,0].add(biggles.LineY(1, linetype="dotted"))
newerplot[1,0].add(biggles.LineX(0.45, linetype="longdashed"))
newerplot[1,0].add(biggles.LineX(0.70, linetype="longdashed"))
newerplot[2,0].add((num/den).points(True))
newerplot[2,0].add((num/den).errorbars(True))
newerplot[2,0].add(biggles.LineY(1, linetype="dotted"))
newerplot[2,0].add(biggles.LineX(0.45, linetype="longdashed"))
newerplot[2,0].add(biggles.LineX(0.70, linetype="longdashed"))
newerplot[0,0].yrange = (0., max(den.vals)*1.1)
newerplot[1,0].yrange = (0.96, 1.01)
newerplot[2,0].yrange = (-0.1, 1.1)
newerplot.xrange = (-0.1, 0.9)
newerplot.xlabel = r"average cos($\theta$) of bhabha tracks"
newerplot.ylabel = "BhabhaBarrel trigger efficiency"
newerplot.show()
newerplot.write_eps("plottrig_5.eps")



