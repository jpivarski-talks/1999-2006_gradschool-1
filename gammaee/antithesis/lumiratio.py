import biggles, Numeric

x = [9.460-0.020, 9.460, 10.023-0.020, 10.023, 10.355-0.020, 10.355]
y = [0.9990, 0.9921, 1.0002, 0.9969, 0.9983, 0.9928]
dy = [0.0025, 0.0020, 0.0017, 0.0037, 0.0029, 0.0023]

p = biggles.Table(2,1)
p[0,0] = biggles.FramedPlot()
p[0,0].add(biggles.Points(x, y, symboltype="filled circle"))
p[0,0].add(biggles.SymmetricErrorBarsY(x, y, dy))
p[0,0].add(biggles.LineY(1.))
p[0,0].x1.range = 9.3, 10.5
p[0,0].y1.range = 0.985, 1.0035
p[0,0].x1.label = "Center of mass energy (GeV)"
p[0,0].y1.label = "BB lumi / GG lumi"

p[1,0] = biggles.FramedPlot()
p[1,0].add(biggles.Curve([9.3, 9.4, 9.4, 9.5, 9.5, 10, 10, 10.1, 10.1, 10.3, 10.3, 10.4, 10.4, 10.5],\
                          Numeric.array([0, 0, 350.3*0.025/8.993, 350.3*0.025/8.993, 0, 0, 142.32*0.020/7.945, 142.32*0.020/7.945, 0, 0, 96.14*0.024/7.361, 96.14*0.024/7.361, 0, 0])*18/350.3))
p[1,0].x1.range = 9.3, 10.5
p[1,0].x1.label = "Center of mass energy (GeV)"
p[1,0].y1.label = r"Size of $\Upsilon \to e^+e^-$ correction"
p[1,0].y1.range = 0., 0.06

p.show()
p.write_eps("lumiratio.eps")
