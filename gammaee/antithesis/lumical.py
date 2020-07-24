from __future__ import division
from biggles import *
from Numeric import *
import jt

L1ee = array([179539.15, 313.68])
L1mm = array([183278.94, 609.25])
L1gg = array([177336.64, 416.]) / 0.985
L2ee = array([420444.14, 610.18])
L2mm = array([430360.26, 1009.66])
L2gg = array([420312.84, 719.93]) / 0.985
L3ee = array([145032.68, 310.14])
L3mm = array([147445.13, 592.71])
L3gg = array([145851.21, 418.17]) / 0.985

def trueerror((v,e)):
  return v*sqrt(e**2/v**2 + 0.005**2)

def trueerror2((v1,e1), (v2,e2), (v3,e3)):
  return (v1+v2+v3)*sqrt((e1**2+e2**2+e3**2)/(v1+v2+v3)**2 + 0.005**2)

wholething = Table(3,1)

wholething[0,0] = FramedPlot()
p = wholething[0,0]
p.add(Points([1, 2, 3], [L1ee[0], L1mm[0], L1gg[0]], symboltype="filled circle", symbolsize=2))
p.add(SymmetricErrorBarsY([1, 2, 3], [L1ee[0], L1mm[0], L1gg[0]], [trueerror(L1ee), trueerror(L1mm), trueerror(L1gg)]))
p.x1.ticks = [1,2,3]
p.x1.draw_ticks = 0
p.x2.draw_ticks = 0
p.x1.ticklabels = [r"$e^+e^-$", r"$\mu^+\mu^-$", r"$\gamma\gamma$"]
p.x1.range = 0.5, 3.5
p.y1.label = r"off-$\Upsilon(1S)$ luminosity (nb)"

wholething[1,0] = FramedPlot()
p = wholething[1,0]
p.add(Points([1, 2, 3], [L2ee[0], L2mm[0], L2gg[0]], symboltype="filled circle", symbolsize=2))
p.add(SymmetricErrorBarsY([1, 2, 3], [L2ee[0], L2mm[0], L2gg[0]], [trueerror(L2ee), trueerror(L2mm), trueerror(L2gg)]))
p.x1.ticks = [1,2,3]
p.x1.draw_ticks = 0
p.x2.draw_ticks = 0
p.x1.ticklabels = [r"$e^+e^-$", r"$\mu^+\mu^-$", r"$\gamma\gamma$"]
p.x1.range = 0.5, 3.5
p.y1.label = r"off-$\Upsilon(2S)$ luminosity (nb)"

wholething[2,0] = FramedPlot()
p = wholething[2,0]
p.add(Points([1, 2, 3], [L3ee[0], L3mm[0], L3gg[0]], symboltype="filled circle", symbolsize=2))
p.add(SymmetricErrorBarsY([1, 2, 3], [L3ee[0], L3mm[0], L3gg[0]], [trueerror(L3ee), trueerror(L3mm), trueerror(L3gg)]))
p.x1.ticks = [1,2,3]
p.x1.draw_ticks = 0
p.x2.draw_ticks = 0
p.x1.ticklabels = [r"$e^+e^-$", r"$\mu^+\mu^-$", r"$\gamma\gamma$"]
p.x1.range = 0.5, 3.5
p.y1.label = r"off-$\Upsilon(3S)$ luminosity (nb)"

wholething.show()
wholething.write_eps("/home/mccann/tmp.ps")

p = FramedPlot()
p.add(Points([1, 2, 3], [L1ee[0]+L2ee[0]+L3ee[0], L1mm[0]+L2mm[0]+L3mm[0], L1gg[0]+L2gg[0]+L3gg[0]], symboltype="filled circle", symbolsize=2))
p.add(SymmetricErrorBarsY([1, 2, 3], [L1ee[0]+L2ee[0]+L3ee[0], L1mm[0]+L2mm[0]+L3mm[0], L1gg[0]+L2gg[0]+L3gg[0]], [trueerror2(L1ee, L2ee, L3ee), trueerror2(L1mm, L2mm, L3mm), trueerror2(L1gg, L2gg, L3gg)]))
p.x1.ticks = [1,2,3]
p.x1.draw_ticks = 0
p.x2.draw_ticks = 0
p.x1.ticklabels = [r"$e^+e^-$", r"$\mu^+\mu^-$", r"$\gamma\gamma$"]
p.x1.range = 0.5, 3.5
p.y1.label = r"all off-$\Upsilon$ luminosity (nb)"
p.show()
p.write_eps("/home/mccann/tmp.ps")

print zip([L1ee[0]+L2ee[0]+L3ee[0], L1mm[0]+L2mm[0]+L3mm[0], L1gg[0]+L2gg[0]+L3gg[0]], [trueerror2(L1ee, L2ee, L3ee), trueerror2(L1mm, L2mm, L3mm), trueerror2(L1gg, L2gg, L3gg)])

(745015.96999999997, 3800.4106992897518),
(761084.32999999996, 4027.7956696546462),
(754823.03553299501, 3890.5976385867111)

print jt.wmean(zip([L1ee[0]+L2ee[0]+L3ee[0], L1mm[0]+L2mm[0]+L3mm[0], L1gg[0]+L2gg[0]+L3gg[0]], [trueerror2(L1ee, L2ee, L3ee), trueerror2(L1mm, L2mm, L3mm), trueerror2(L1gg, L2gg, L3gg)]))

(753334.9594020159, 2253.3621610084865)
