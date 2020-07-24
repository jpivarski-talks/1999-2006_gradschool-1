from biggles import *
from math import *
from Numeric import *

def fun(x):
  return exp(-(x-0.67)**2/2./0.62**2)/sqrt(2.*pi)/0.62

x = arange(0., 3., 0.001)
y = arange(0., 3., 0.001)
y2 = arange(0., 3., 0.001)
for i, xi in enumerate(x):
  y[i] = fun(xi)
  if 0.55 - 0.34 < xi < 0.55 + 0.30:
    y2[i] = fun(xi)
  else:
    y2[i] = 0.

p = FramedPlot()
p.add(FillBelow(x, y2, color="grey"))
p.add(Curve(x, y))
p.add(DataLine((0.55, 0.), (0.55, fun(0.55))))
p.x.range = 0., 3.
p.y.range = 0., 0.8
p.x2.draw_axis = 0
p.y2.draw_axis = 0
p.aspect_ratio = 0.3
# p.x1.label = r"$B_{invisible}$"
# p.y1.label = r"$\partial P/\partial B$"
p.y1.draw_ticklabels = 0
p.y2.draw_ticklabels = 0
p.x2.draw_ticklabels = 0
p.frame.ticklabels_style["fontsize"] = 8.
p.frame.label_style["fontsize"] = 6.
p.write_eps("/home/mccann/antithesis/plots/plenary_probabilityplot.eps")
p.show()

########################################################

x = arange(0., 3., 0.001)
y = arange(0., 3., 0.001)
y2 = arange(0., 3., 0.001)
for i, xi in enumerate(x):
  y[i] = fun(xi)
  if 0.78 - 0.48 < xi < 0.78 + 0.57:
    y2[i] = fun(xi)
  else:
    y2[i] = 0.

p = FramedPlot()
p.add(FillBelow(x, y2, color="grey"))
p.add(Curve(x, y))
p.add(DataLine((0.78, 0.), (0.78, fun(0.78))))
p.x.range = 0., 3.
p.y.range = 0., 0.8
p.x2.draw_axis = 0
p.y2.draw_axis = 0
p.aspect_ratio = 0.3
# p.x1.label = r"$B_{invisible}$"
# p.y1.label = r"$\partial P/\partial B$"
p.y1.draw_ticklabels = 0
p.y2.draw_ticklabels = 0
p.x2.draw_ticklabels = 0
p.frame.ticklabels_style["fontsize"] = 8.
p.frame.label_style["fontsize"] = 6.
p.write_eps("/home/mccann/antithesis/plots/plenary_probabilityplot_corrected.eps")
p.show()
