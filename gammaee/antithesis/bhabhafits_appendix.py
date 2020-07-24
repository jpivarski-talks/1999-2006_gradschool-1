import biggles, Numeric

pp = biggles.Table(3,1)

x = [0, 1, 2]
y = [319.2, 324.1, 323.36]
yerr = [2.1, 1.2, 0.92]

p = biggles.FramedPlot()
p.add(biggles.Points(x, y, size=1., type="filled circle"))
p.add(biggles.SymmetricErrorBarsY(x, y, yerr))
p.xrange = -0.5, 2.5
p.x1.ticks = x
p.x1.ticklabels = [r"$\gamma\gamma$ lumi", r"inner $e^+e^-$", r"outer $e^+e^-$"]
p.x.draw_subticks = 0
p.x2.draw_ticks = 0
p.yrange = 316, 326
p.ylabel = r"$\Upsilon(1S)$ area in MeV nb"
pp[0,0] = p

x = [0, 1, 2]
y = [133.2, 134.2, 133.99]
yerr = [2.1, 1.2, 0.95]

p = biggles.FramedPlot()
p.add(biggles.Points(x, y, size=1., type="filled circle"))
p.add(biggles.SymmetricErrorBarsY(x, y, yerr))
p.xrange = -0.5, 2.5
p.x1.ticks = x
p.x1.ticklabels = [r"$\gamma\gamma$ lumi", r"inner $e^+e^-$", r"outer $e^+e^-$"]
p.x.draw_subticks = 0
p.x2.draw_ticks = 0
p.yrange = 130, 136
p.ylabel = r"$\Upsilon(2S)$ area in MeV nb"
pp[1,0] = p

x = [0, 1, 2]
y = [84.9, 88.8, 87.81]
yerr = [1.9, 1.1, 0.86]

p = biggles.FramedPlot()
p.add(biggles.Points(x, y, size=1., type="filled circle"))
p.add(biggles.SymmetricErrorBarsY(x, y, yerr))
p.xrange = -0.5, 2.5
p.x1.ticks = x
p.x1.ticklabels = [r"$\gamma\gamma$ lumi", r"inner $e^+e^-$", r"outer $e^+e^-$"]
p.x.draw_subticks = 0
p.x2.draw_ticks = 0
p.yrange = 82, 91
p.ylabel = r"$\Upsilon(3S)$ area in MeV nb"
pp[2,0] = p

pp.aspect_ratio = 11./8.5
pp.show()
pp.write_eps("fit_results/bhabhafits_appendix.eps")
