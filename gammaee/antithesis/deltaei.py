from math import *
import biggles, Numeric

def tell_me_about_it(m):
  for i in x:
    print r"%s & %4.2f $\pm$ %4.2f & %d $\pm$ %d \\" % (names[i], y[i], (ye1[i]+ye2[i])/2., y[i]/(m/2.)*1.e6, (ye1[i]+ye2[i])/2./(m/2.)*1.e6)

p = biggles.Table(3,1)

# x = range(12)
# y = Numeric.array([3.53109261894, 3.82938651019, 3.79132045452, 3.66019208508, 3.72243929539, 3.81254895096, 3.74133996111, 3.81332115001, 4.34302799263, 3.76039540395, 3.9359142978 , 3.70290786805])
# ye1 = Numeric.array([0.117137905601, 0.038674137147, 0.051347450846, 0.105920052988, 0.053143812374, 0.049659414663, 0.056950431400, 0.047938756886, 0.202105109666, 0.123147411173, 0.143610041316, 0.049672885049])
# ye2 = Numeric.array([0.120177204869, 0.038940181694, 0.051922389251, 0.108057671074, 0.054158264634, 0.050478493155, 0.057938390014, 0.048652415255, 0.221548245821, 0.131973253598, 0.155519499517, 0.048574632647])
# names = ["jan16", "jan30", "feb06", "feb13", "feb20", "feb27", "mar06", "mar13", "apr03", "apr08", "apr09", "apr10"]

x = range(11)
y = Numeric.array([3.53109261894, 3.82938651019, 3.79132045452, 3.66019208508, 3.72243929539, 3.81254895096, 3.74133996111, 3.81332115001, 3.76039540395, 3.9359142978 , 3.70290786805])
ye1 = Numeric.array([0.117137905601, 0.038674137147, 0.051347450846, 0.105920052988, 0.053143812374, 0.049659414663, 0.056950431400, 0.047938756886, 0.123147411173, 0.143610041316, 0.049672885049])
ye2 = Numeric.array([0.120177204869, 0.038940181694, 0.051922389251, 0.108057671074, 0.054158264634, 0.050478493155, 0.057938390014, 0.048652415255, 0.131973253598, 0.155519499517, 0.048574632647])
names = ["jan16", "jan30", "feb06", "feb13", "feb20", "feb27", "mar06", "mar13", "apr08", "apr09", "apr10"]

y = y/sqrt(2.)
ye1 = ye1/sqrt(2.)
ye2 = ye2/sqrt(2.)
tell_me_about_it(9460.3)

y = y/(9460.3/2.)*1.e6
ye1 = ye1/(9460.3/2.)*1.e6
ye2 = ye2/(9460.3/2.)*1.e6

p[0,0] = biggles.FramedPlot()
p[0,0].add(biggles.Points(x, y, symboltype="filled circle", symbolsize=1.5))
p[0,0].add(biggles.ErrorBarsY(x, y-ye1, y+ye2))
p[0,0].add(biggles.LineY(3.78739/sqrt(2.)/(9460.3/2.)*1.e6, linetype="dashed"))
p[0,0].x.ticks = x
p[0,0].x.ticklabels = names
p[0,0].x2.draw_ticklabels = 0
p[0,0].x.draw_subticks = 0
p[0,0].aspect_ratio = 0.3
p[0,0].yrange = 400., 700.
p[0,0].y1.label = r"$\Upsilon(1S)$ $\sigma_E/E$ $\times$ 10$^{6}$ in MeV"
p[0,0].show()

x = range(6)
y = Numeric.array([4.28629322679, 4.01314654533, 4.25415201809, 3.91987316377, 3.7696777093 , 4.23821651803])
ye1 = Numeric.array([0.144585229188, 0.268883169298, 0.113942384667, 0.163686711709, 0.408913954759, 0.184621198411])
ye2 = Numeric.array([0.152490222232, 0.290949860127, 0.117809357952, 0.168979048619, 0.505852991529, 0.193678057158])
names = ["may29", "jun11", "jun12", "jul10", "jul24", "aug07"]

y = y/sqrt(2.)
ye1 = ye1/sqrt(2.)
ye2 = ye2/sqrt(2.)
tell_me_about_it(10023.26)

y = y/(10023.26/2.)*1.e6
ye1 = ye1/(10023.26/2.)*1.e6
ye2 = ye2/(10023.26/2.)*1.e6

p[1,0] = biggles.FramedPlot()
p[1,0].add(biggles.Points(x, y, symboltype="filled circle", symbolsize=1.5))
p[1,0].add(biggles.ErrorBarsY(x, y-ye1, y+ye2))
p[1,0].add(biggles.LineY(4.17582/sqrt(2.)/(10023.26/2.)*1.e6, linetype="dashed"))
p[1,0].x.ticks = x
p[1,0].x.ticklabels = names
p[1,0].x2.draw_ticklabels = 0
p[1,0].x.draw_subticks = 0
p[1,0].aspect_ratio = 0.3
p[1,0].yrange = 400., 800.
p[1,0].y1.label = r"$\Upsilon(2S)$ $\sigma_E/E$ $\times$ 10$^{6}$ in MeV"
p[1,0].show()

x = range(7)
y = Numeric.array([4.72450425724, 4.46267905895, 4.52718460772, 4.6962385988 , 4.12004615603, 4.57916877699, 4.60685866392])
ye1 = Numeric.array([0.150954112466, 0.142993252651, 0.133047518868, 0.176719742849, 0.198653927997, 0.152275083521, 0.127680425201])
ye2 = Numeric.array([0.154184543894, 0.142662643858, 0.135000477462, 0.178467951499, 0.209468631457, 0.157597202084, 0.130522649229])
names = ["nov28", "dec05", "dec12", "dec19", "dec26", "jan02", "jan09"]

y = y/sqrt(2.)
ye1 = ye1/sqrt(2.)
ye2 = ye2/sqrt(2.)
tell_me_about_it(10355.2)

y = y/(10355.2/2.)*1.e6
ye1 = ye1/(10355.2/2.)*1.e6
ye2 = ye2/(10355.2/2.)*1.e6

p[2,0] = biggles.FramedPlot()
p[2,0].add(biggles.Points(x, y, symboltype="filled circle", symbolsize=1.5))
p[2,0].add(biggles.ErrorBarsY(x, y-ye1, y+ye2))
p[2,0].add(biggles.LineY(4.479665/sqrt(2.)/(10355.2/2.)*1.e6, linetype="dashed"))
p[2,0].x.ticks = x
p[2,0].x.ticklabels = names
p[2,0].x2.draw_ticklabels = 0
p[2,0].x.draw_subticks = 0
p[2,0].aspect_ratio = 0.3
p[2,0].yrange = 400., 800.
p[2,0].y1.label = r"$\Upsilon(3S)$ $\sigma_E/E$ $\times$ 10$^{6}$ in MeV"
p[2,0].show()

p.show()
p.write_eps("plots/deltaei_cesr.eps")

#########################################################################

import biggles, Numeric

def tell_me_about_it(m):
  for i in x:
    print r"%s & %4.2f $\pm$ %4.2f \\" % (names[i], y[i], (ye1[i]+ye2[i])/2.)

p = biggles.Table(3,1)

# x = range(12)
# y = Numeric.array([0.241934049129, 0.534254035023, 0.234935273574, 0.056486855145, 0.161719743037, 0.113433362711, 0.220960593008, 0.569961219798, 0.905744806291, 0.787956903225, 0.446522214888, 0.748251072592])
# ye1 = Numeric.array([0.121971108592, 0.096952499896, 0.091146172455, 0.104758501781, 0.099146251762, 0.10014453932 , 0.119220904428, 0.104421216079, 0.14566890263 , 0.12024992048 , 0.1284003502, 0.099694995107])
# ye2 = Numeric.array([0.120466867014, 0.097376934260, 0.092615198133, 0.103967721465, 0.098891005365, 0.100768912548, 0.121773566791, 0.104179063002, 0.144559450814, 0.12046044686, 0.128311257112, 0.096451107284])
# names = ["jan16", "jan30", "feb06", "feb13", "feb20", "feb27", "mar06", "mar13", "apr03", "apr08", "apr09", "apr10"]

x = range(11)
y = Numeric.array([0.241934049129, 0.534254035023, 0.234935273574, 0.056486855145, 0.161719743037, 0.113433362711, 0.220960593008, 0.569961219798, 0.787956903225, 0.446522214888, 0.748251072592])
ye1 = Numeric.array([0.121971108592, 0.096952499896, 0.091146172455, 0.104758501781, 0.099146251762, 0.10014453932 , 0.119220904428, 0.104421216079, 0.12024992048 , 0.1284003502, 0.099694995107])
ye2 = Numeric.array([0.120466867014, 0.097376934260, 0.092615198133, 0.103967721465, 0.098891005365, 0.100768912548, 0.121773566791, 0.104179063002, 0.12046044686, 0.128311257112, 0.096451107284])
names = ["jan16", "jan30", "feb06", "feb13", "feb20", "feb27", "mar06", "mar13", "apr08", "apr09", "apr10"]

y = y/2.
ye1 = ye1/2.
ye2 = ye2/2.
tell_me_about_it(9460.3)

y = y - 0.184067
y = y*2.
ye1 = ye1*2.
ye2 = ye2*2.

p[0,0] = biggles.FramedPlot()
p[0,0].add(biggles.Points(x, y, symboltype="filled circle", symbolsize=1.5))
p[0,0].add(biggles.ErrorBarsY(x, y-ye1, y+ye2))
p[0,0].add(biggles.LineY(0., linetype="dashed"))
p[0,0].x.ticks = x
p[0,0].x.ticklabels = names
p[0,0].x2.draw_ticklabels = 0
p[0,0].x.draw_subticks = 0
p[0,0].aspect_ratio = 0.3
p[0,0].yrange = -3., 3.
p[0,0].y1.label = r"$\Upsilon(1S)$ mass error (MeV)"
p[0,0].show()

x = range(6)
y = Numeric.array([-1.03471139435, -1.0756193477 , -1.51190614047, -0.76665957624, -0.68098213432, -0.38857711883])
ye1 = Numeric.array([0.20367963451384269, 0.15635288404235886, 0.18033145254889613, 0.12780380085143295, 0.22423919461754346, 0.20628099762766355])
ye2 = Numeric.array([0.20367963451384269, 0.15717029222414905, 0.18372025230915937, 0.12768438726253803, 0.22423919461754346, 0.2026417202061282])
names = ["may29", "jun11", "jun12", "jul10", "jul24", "aug07"]

y = y/2.
ye1 = ye1/2.
ye2 = ye2/2.
tell_me_about_it(10023.26)

y = y - 0.184067
y = y*2.
ye1 = ye1*2.
ye2 = ye2*2.

p[1,0] = biggles.FramedPlot()
p[1,0].add(biggles.Points(x, y, symboltype="filled circle", symbolsize=1.5))
p[1,0].add(biggles.ErrorBarsY(x, y-ye1, y+ye2))
# p[1,0].add(biggles.LineY(0./2., linetype="dashed"))
p[1,0].add(biggles.LineY(jimtools.wmean(zip(y, (ye1+ye2)/2.))[0], linetype="dashed"))
p[1,0].x.ticks = x
p[1,0].x.ticklabels = names
p[1,0].x2.draw_ticklabels = 0
p[1,0].x.draw_subticks = 0
p[1,0].aspect_ratio = 0.3
p[1,0].yrange = -4., 2.
p[1,0].y1.label = r"$\Upsilon(2S)$ mass error (MeV)"
p[1,0].show()

x = range(7)
y = Numeric.array([-2.30027319166, -4.06155793189, -3.17991710448, -2.09985899579, -2.9303022962 , -2.69262151463, -2.48179026004])
ye1 = Numeric.array([0.564407698114, 0.232590133108, 0.306092018377, 0.36297484652 , 0.215275701388, 0.306332866293, 0.383146910508])
ye2 = Numeric.array([0.507764470918, 0.246887091937, 0.323194515037, 0.335506281266, 0.217123979715, 0.312457879845, 0.418056301328])
names = ["nov28", "dec05", "dec12", "dec19", "dec26", "jan02", "jan09"]

y = y/2.
ye1 = ye1/2.
ye2 = ye2/2.
tell_me_about_it(10355.2)

y = y - 0.184067
y = y*2.
ye1 = ye1*2.
ye2 = ye2*2.

p[2,0] = biggles.FramedPlot()
p[2,0].add(biggles.Points(x, y, symboltype="filled circle", symbolsize=1.5))
p[2,0].add(biggles.ErrorBarsY(x, y-ye1, y+ye2))
# p[2,0].add(biggles.LineY(0./2., linetype="dashed"))
p[2,0].add(biggles.LineY(jimtools.wmean(zip(y, (ye1+ye2)/2.))[0], linetype="dashed"))
p[2,0].x.ticks = x
p[2,0].x.ticklabels = names
p[2,0].x2.draw_ticklabels = 0
p[2,0].x.draw_subticks = 0
p[2,0].aspect_ratio = 0.3
p[2,0].yrange = -6., 0.
p[2,0].y1.label = r"$\Upsilon(3S)$ mass error (MeV)"
p[2,0].show()

p.show()
p.write_eps("plots/deltam_cesr.eps")

###################################################

from minuit import *

#   rmsbeam = 3.77876134921 +/- 0.0262426780529      + 0.0263068514958
#   rmsbeam = 4.16194910214 +/- 0.083770990361576883 + 0.079511910847998801
#   rmsbeam = 4.50761526701 +/- 0.103363948356       + 0.103044759691

x = [9460.30/2000., 10023.26/2000., 10355.2/2000.]
y = [3.77876134921/sqrt(2.)/(9460.30/2.)*1.e6, \
     4.16194910214/sqrt(2.)/(10023.26/2.)*1.e6, \
     4.50761526701/sqrt(2.)/(10355.2/2.)*1.e6]
yerr = [(0.0262426780529 + 0.0263068514958)/2./sqrt(2.)/(9460.30/2.)*1.e6, \
        (0.083770990361576883 + 0.079511910847998801)/2./sqrt(2.)/(10023.26/2.)*1.e6, \
        (0.103363948356 + 0.103044759691)/2./sqrt(2.)/(10355.2/2.)*1.e6]

def line(x, yint, slope): return yint + slope*x
def f(yint, slope):
  c = 0.
  for xi, yi, yierr in zip(x, y, yerr):
    c += (line(xi, yint, slope) - yi)**2/yierr**2
  return c
m = Minuit(f)
m.fix("yint")
m.migrad()
m.minos()
print m

xx = Numeric.arange(4.6, 5.3, 0.1)
yy = Numeric.arange(4.6, 5.3, 0.1)
for i, xi in enumerate(xx):
  yy[i] = 762.4*xi/(10355.2/2000.)

xxx = Numeric.arange(4.6, 5.3, 0.1)
yyy = Numeric.arange(4.6, 5.3, 0.1)
for i, xi in enumerate(xxx):
  yyy[i] = line(xi, m.values[0], m.values[1])

p = biggles.FramedPlot()
p.add(biggles.Points(x, y, symboltype="filled circle", symbolsize=2.))
p.add(biggles.SymmetricErrorBarsY(x, y, yerr))
p.add(biggles.Curve(xx, yy))
p.add(biggles.Curve(xxx, yyy, linetype="longdashed"))
p.xrange = 4.6, 5.3
p.x.ticks = [4.6, 4.7, 4.8, 4.9, 5.0, 5.1, 5.2, 5.3]
p.x2.draw_ticklabels = 0
p.yrange = 500., 800.
p.aspect_ratio = 1.
p.x1.label = r"Single-beam energy in GeV"
p.y1.label = r"$\sigma_E/E$ $\times$ 10$^{6}$"
p.show()
p.write_eps("/home/mccann/antithesis/clns/beamenergyspread.eps")

#######################################################

# print jt.stdev([0.12, 0.27, 0.12, 0.03, 0.08, 0.06, 0.11, 0.28, 0.45, 0.39, 0.22, 0.37])*sqrt(12./11.)
# print jt.stdev([-0.52, -0.54, -0.76, -0.38, -0.34, -0.19])*sqrt(6./5.)
# print jt.stdev([-1.15, -2.03, -1.59, -1.05, -1.47, -1.35, -1.24])*sqrt(7./6.)

x = [9460.30/2., 10023.26/2., 10355.2/2.]
# y = [x[0]+0.197, x[1]-0.456, x[2]-1.514]
y = [0.197, -0.456, -1.514]
yerr1 = [0.016, 0.035, 0.057]
yerr2 = [0.14, 0.20, 0.33]

def line(x, yint, slope): return yint + slope*x
def f(yint, slope):
  c = 0.
  for xi, yi, yierr in zip(x, y, yerr2):
    c += (line(xi, yint, slope) - yi)**2/yierr**2
  return c
m = Minuit(f)
m.migrad()
m.hesse()
m.minos()
print m

xxx = Numeric.arange(4600., 5300., 10.)
yyy = Numeric.arange(4600., 5300., 10.)
for i, xi in enumerate(xxx):
  yyy[i] = line(xi, m.values[0], m.values[1])

p = biggles.FramedPlot()
p.add(biggles.Points(x, y, type="filled circle", size=2.))
p.add(biggles.SymmetricErrorBarsY(x, y, yerr1))
p.add(biggles.SymmetricErrorBarsY(x, y, yerr2))
p.add(biggles.Curve(xxx, yyy, linetype="longdashed"))
p.xrange = 4600, 5300
p.yrange = -3., 1.
p.aspect_ratio = 1.
p.x1.label = r"Single-beam energy in MeV"
p.y1.label = r"Beam energy correction in MeV"
p.show()
p.write_eps("/home/mccann/antithesis/clns/energycorrection.eps")
