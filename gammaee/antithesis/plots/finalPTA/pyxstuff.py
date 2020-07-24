from pyx import *

texrunner = text.texrunner(mode="latex", lfs="12pt", errordebug=1)

c = canvas.canvas(texrunner=texrunner)
c.text(0, 0, r"\sf \#$e^+e^-$ to subtract $=$ $\sigma_\Upsilon(E)$ ${\cal B}_{\mu\mu}$ $\frac{\stackrel{\displaystyle \int_{0.6}^{0.8} \cos^2\theta_+ \mbox{ } d(\cos\theta_+)}{\mbox{ }}}{\stackrel{\mbox{ }}{\displaystyle \int_{-1}^{+1} \cos^2\theta_+ \mbox{ } d(\cos\theta_+)}}$ ${\cal L}_{\gamma\gamma}$", [text.halign.boxcenter, text.halign.flushcenter])
c.writeEPSfile("equation.eps")

import biggles
p = biggles.Table(1,3)
p[0,0] = biggles.FramedPlot()
p[0,0].add(biggles.Points             ([0, 1, 2], [317.8/317.8, 324.00/317.8, 323.16/317.8], symboltype="filled circle", symbolsize=2.))
p[0,0].add(biggles.SymmetricErrorBarsY([0, 1, 2], [317.8/317.8, 324.00/317.8, 323.16/317.8], [2.2/317.8, 1.2/317.8, 0.95/317.8]))
p[0,0].x.ticks = [0,1,2]
p[0,0].x.draw_subticks = 0
p[0,0].x1.ticklabels = [r"$\gamma\gamma$", r"${e^+e^-}_{in}$", r"${e^+e^-}_{out}$"]
p[0,0].x1.range = [-0.5, 2.5]
p[0,0].y1.label = r"$\Gamma_{ee}$ (normalized)"
p[0,0].y1.range = 0.97, 1.05
p[0,0].title = r"$\Upsilon(1S)$"

p[0,1] = biggles.FramedPlot()
p[0,1].add(biggles.Points             ([0, 1, 2], [133.2/133.2, 134.4/133.2, 134.02/133.2], symboltype="filled circle", symbolsize=2.))
p[0,1].add(biggles.SymmetricErrorBarsY([0, 1, 2], [133.2/133.2, 134.4/133.2, 134.02/133.2], [2.1/133.2, 1.2/133.2, 0.92/133.2]))
p[0,1].x.ticks = [0,1,2]
p[0,1].x.draw_subticks = 0
p[0,1].x1.ticklabels = [r"$\gamma\gamma$", r"${e^+e^-}_{in}$", r"${e^+e^-}_{out}$"]
p[0,1].x1.range = [-0.5, 2.5]
p[0,1].y1.range = 0.97, 1.05
p[0,1].title = r"$\Upsilon(2S)$"

p[0,2] = biggles.FramedPlot()
p[0,2].add(biggles.Points             ([0, 1, 2], [86.1/86.1, 89.0/86.1, 87.74/86.1], symboltype="filled circle", symbolsize=2.))
p[0,2].add(biggles.SymmetricErrorBarsY([0, 1, 2], [86.1/86.1, 89.0/86.1, 87.74/86.1], [1.9/86.1, 1.1/86.1, 0.87/86.1]))
p[0,2].x.ticks = [0,1,2]
p[0,2].x.draw_subticks = 0
p[0,2].x1.ticklabels = [r"$\gamma\gamma$", r"${e^+e^-}_{in}$", r"${e^+e^-}_{out}$"]
p[0,2].x1.range = [-0.5, 2.5]
p[0,2].y1.range = 0.97, 1.05
p[0,2].title = r"$\Upsilon(3S)$"

p.aspect_ratio = 0.5
p.show()
p.write_eps("octoberfits_fixen_summaryplot.eps")

#############################################################

import biggles, math

u1 = 9460.3**2/math.sqrt(2.)/1e9
u2 = 10023.26**2/math.sqrt(2.)/1e9
u3 = 10355.2**2/math.sqrt(2.)/1e9

p = biggles.FramedPlot()
p.add(biggles.Points([1,2,3,4,5,6,7], [4.669/u3, 4.595/u3, 4.576/u3, 4.634/u3, 4.669/u3, 4.551/u3, 4.622/u3], symboltype="filled circle", symbolsize=1.5))
p.add(biggles.SymmetricErrorBarsY([1,2,3,4,5,6,7], [4.669/u3, 4.595/u3, 4.576/u3, 4.634/u3, 4.669/u3, 4.551/u3, 4.622/u3], [0.068/u3, 0.061/u3, 0.058/u3, 0.071/u3, 0.105/u3, 0.068/u3, 0.059/u3]))
p.add(biggles.Points([9,10,11,12], [3.816/u1, 3.841/u1, 3.771/u1, 3.752/u1], symboltype="filled circle", symbolsize=1.5, color="red"))
p.add(biggles.SymmetricErrorBarsY([9,10,11,12], [3.816/u1, 3.841/u1, 3.771/u1, 3.752/u1], [0.013/u1, 0.015/u1, 0.033/u1, 0.020/u1], color="red"))
p.add(biggles.Points([14,], [4.161/u2], symboltype="filled circle", symbolsize=1.5, color="blue"))
p.add(biggles.SymmetricErrorBarsY([14], [4.161/u2], [0.038/u2], color="blue"))

p.x1.ticks = [1,  3,  5,  7,  10   ,12   ]
p.x2.ticks = [  2,  4,  6,  9,   11,   14]
p.x.draw_subticks = 0
# p.x1.ticklabels = ["Nov28", "", "Dec12", "", "Dec26", "", "Jan09", "", "Feb/Mar", "", "Apr2", ""]
# p.x2.ticklabels = ["", "Dec05", "", "Dec19", "", "Jan02", "", "Jan/Feb", "", "Apr1", "", r"$\Upsilon(2S)$"]
p.x1.ticklabels = ["Nov28", "Dec12", "Dec26", "Jan09", "Feb/Mar", "AprB"]
p.x2.ticklabels = ["Dec05", "Dec19", "Jan02", "Jan/Feb", "AprA", r"$\Upsilon(2S)$"]
p.x1.range = 0, 15
p.y1.label = r"beam energy spread / beam energy$^2$ ($\mu$eV)"
p.y1.range = 57.5, 63.5
p.y2.range = 57.5/(3.752/u1), 63.5/(3.752/u1)

p.aspect_ratio = 0.7
p.show()
p.write_eps("piecewise_constant_beamspread.eps")

################################################################

from pyx import *

c = canvas.canvas()
c.stroke(path.line(0, 0, 5, 0))
c.writeEPSfile("justaline.eps")

