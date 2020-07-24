import sys
sys.path.append("/home/mccann/bin/python/obsolete")

from minuit import *
import biggles, Numeric

yint = [0.0087, 0.0174, 0.0348, 0.0435, 0.0522, 0.0609]
chi2 = [243.3, 240.2, 257.19, 277.08, 304.41, 339.03]

def fitme(a, b, c, x):
  return a + b*x + c*x**2

def minme(a, b, c):
  thesum = 0.
  for y, c2 in zip(yint, chi2):
    thesum += (c2 - fitme(a, b, c, y))**2
  return thesum

m = Minuit(minme, start=[240., 0., 20000.], step=[1., 10., 1000.])
m.migrad()

x = Numeric.arange(0., 0.07, 0.0001)
y = Numeric.arange(0., 0.07, 0.0001)
for i in range(len(x)):
  y[i] = fitme(m.values[0], m.values[1], m.values[2], x[i])

inrange = []
themin = None
for xi, yi in zip(x, y):
  if yi < min(y)+1.:
    inrange.append(xi)
  if yi == min(y):
    themin = xi

x = Numeric.arange(0., 0.07, 0.001)
y = Numeric.arange(0., 0.07, 0.001)
for i in range(len(x)):
  y[i] = fitme(m.values[0], m.values[1], m.values[2], x[i])

p = biggles.FramedPlot()
p.add(biggles.Points(yint, chi2, symboltype="filled circle"))
p.add(biggles.Points([0.0174], [240.2], symboltype="circle", symbolsize=5.))
p.add(biggles.Curve(x, y))
p.add(biggles.LineX(themin, linetype="dashed"))
p.add(biggles.LineX(min(inrange), linetype="dotted"))
p.add(biggles.LineX(max(inrange), linetype="dotted"))
p.x1.range = 0., 0.065
p.y1.range = 200., 400.
p.x1.label = r"Interference parameter $y_{int}$"
p.y1.label = r"$\chi^2$ for $\Upsilon(1S)$ fit"
p.show()
p.write_eps("interferencescan.eps")
