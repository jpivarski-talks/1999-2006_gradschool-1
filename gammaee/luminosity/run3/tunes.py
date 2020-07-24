import Numeric, hist, math, random

a = Numeric.array(map(lambda x: map(lambda y: float(y), x.split()), open("/cdat/dafe/mccann/luminosity/tunes.dat", "r").read().splitlines()))

execfile("/cdat/dafe/mccann/luminosity/tmp.py")

def cotT(aline):
  myx = random.gauss(bx, bdx)
  myy = random.gauss(by, bdy)
  myz = 0.
  if random.random() > bzgap:
    myz = random.gauss(bz, bdz1)
  else:
    myz = random.gauss(bz, bdz2)
  (westx, westy, westz, eastx, easty, eastz) = aline
  westcotT = (westz + myz)/math.sqrt((westx + myx)**2+(westy + myy)**2)
  eastcotT = (eastz + myz)/math.sqrt((eastx + myx)**2+(easty + myy)**2)
  return (westcotT - eastcotT)/2.

(bx, by, bz) = (0., 0., 0.)
(bdx, bdy, bdz1, bdz2, bzgap) = (0., 0., 0., 0., 0.)
def test(x, y, z, dx, dy, dz1, dz2, zgap):
  global bx, by, bz, bdx, bdy, bdz1, bdz2, bzgap
  (bx, by, bz) = (x, y, z)
  (bdx, bdy, bdz1, bdz2, bzgap) = (dx, dy, dz1, dz2, zgap)
  g = hist.h1(138, 0., 1.38, vals=histogram)
  g /= g.int()
  h = hist.h1(138, 0., 1.38).fill(map(cotT, a))
  h /= h.int()
  p = g.plot(False)
#  p.add(g.stepsfill(asbiggles=True, color="yellow"))
  p.add(g.steps(asbiggles=True, linetype="dotted"))
  p.add(h.steps(asbiggles=True))
  p.xlabel = r"average cot($\theta$) (solid is MC, dotted is data)"
#  p.xlabel = r"average cot($\theta$) (no beamspot corrections)"
  p.show()
  p.write_eps("tunes.eps")

test(0., 0., 0., \
     0.000325, 0.000006, \
     0.671*math.sqrt(2)*0.01273, 0.469*math.sqrt(2)*0.01273, \
     0.237)

test(0., 0., 0., 0., 0., 0., 0., 0.237)


(bx, by, bz) = (0., 0., 0.)
(bdx, bdy, bdz1, bdz2, bzgap) = (0., 0., 0., 0., 0.)
h1 = hist.h1(138, 0., 1.38).fill(map(cotT, a))
(bx, by, bz) = (0., 0., 0.)
(bdx, bdy, bdz1, bdz2, bzgap) = (10., 10., 0., 0., 0.)
h2 = hist.h1(138, 0., 1.38).fill(map(cotT, a))
h1 /= h1.int()
h2 /= h2.int()
(h1 - h2).plot().show()
