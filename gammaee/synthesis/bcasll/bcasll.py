from minuit import *
from math import *
import hist, biggles

execfile("hist2s.py")
execfile("hist3s.py")

def plotit(prompt, ratio):
  p = data.plot(False, points=True)
  mc = mcprompt * prompt
  p.add(mc.stepsfill(color="#dddddd"))
  p.add(mc.steps())
  mc += mccascade * prompt * ratio
  p.add(mc.steps(linetype="solid"))
  p.add(data.points())
  p.add(data.errorbars())
  return mc, p

def chi2(prompt, ratio):
  mc, p = plotit(prompt, ratio)
  p.show()
  c = 0.
  for mv, me, dv, de in zip(mc.vals, mc.errs, data.vals, data.errs):
    c += (mv - dv)**2 / sqrt(me**2 + de**2)
  return c

p = biggles.Table(1,2)

data = hist.h1(100, 0.7, 1.2, vals=peak2, errs=peak2_err) - (hist.h1(100, 0.7, 1.2, vals=cont2, errs=cont2_err) * 0.064825)
mcprompt = hist.h1(100, 0.7, 1.2, vals=mc2mm, errs=mc2mm_err)
mccascade = hist.h1(100, 0.7, 1.2, vals=mc2cas, errs=mc2cas_err)

m = Minuit(chi2, start=[5., 0.5])
m.migrad()
m.minos()
rat2 = mccascade.sum() / mcprompt.sum() * m.values[1]
rat2_err = rat2 * sqrt(mccascade.sumerr()**2/mccascade.sum()**2 + mcprompt.sumerr()**2/mcprompt.sum()**2 + ((m.minos_errors[1][0]-m.minos_errors[1][1])/2.)**2/m.values[1])
print rat2, rat2_err
p[0,0] = plotit(m.values[0], m.values[1])[1]
p[0,0].x1.label = r"$m_{\mu\mu}/M_\Upsilon$ for $\Upsilon(2S)$"
p[0,0].xrange = 0.8, 1.1
p[0,0].yrange = -200, 1200
p[0,0].aspect_ratio = 1.
p[0,0].show()

data = hist.h1(100, 0.7, 1.2, vals=peak3, errs=peak3_err) - (hist.h1(100, 0.7, 1.2, vals=cont3, errs=cont3_err) * 0.9620496)
mcprompt = hist.h1(100, 0.7, 1.2, vals=mc3mm, errs=mc3mm_err)
mccascade = hist.h1(100, 0.7, 1.2, vals=mc3cas, errs=mc3cas_err)

m = Minuit(chi2, start=[6.5, 1.0])
m.migrad()
m.minos()
rat3 = mccascade.sum() / mcprompt.sum() * m.values[1]
rat3_err = rat3 * sqrt(mccascade.sumerr()**2/mccascade.sum()**2 + mcprompt.sumerr()**2/mcprompt.sum()**2 + ((m.minos_errors[1][0]-m.minos_errors[1][1])/2.)**2/m.values[1])
print rat3, rat3_err
p[0,1] = plotit(m.values[0], m.values[1])[1]
p[0,1].x1.label = r"$m_{\mu\mu}/M_\Upsilon$ for $\Upsilon(3S)$"
p[0,1].xrange = 0.8, 1.1
p[0,1].yrange = -500, 3500
p[0,1].y.ticks = range(-500, 3500+500, 500)
p[0,1].y2.draw_ticklabels = 0
p[0,1].aspect_ratio = 1.
p[0,1].show()

p.aspect_ratio = 0.5
p.show()

p.write_eps("/home/mccann/antithesis/plots/beautiful_bcasll_2.eps")


