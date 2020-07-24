execfile("utilities.py")
import gbwkf
import gbwkftau

def mygbwkf(mass, fullgam, rmsbeam, yint, phi, w):
  "yint = 0.018, 0.018, 0.018; phi=0"
  if w > mass + 200.:
    return 0.076/(w-mass)
  return gbwkf.gbwkf(mass, fullgam, rmsbeam, yint, phi, w-mass)

def mygbwkftau(mass, fullgam, rmsbeam, yint, phi, w):
  "yint = 0.20, 0.37, 0.27; phi = 0"
  if w > mass + 200.:
    return 0.076/(w-mass)
  return gbwkftau.gbwkf(mass, fullgam, rmsbeam, yint, phi, w-mass)

def u1func(w, area=13.7, rmsbeam=3.79, back=0.406, fullgam=0.053, yint=0.01864, phi=0., btautau=0.0267, tauyint=0.20, tauphi=0.0, twophofrac=0.0792):
  tmp = 0.
  tmp += area * (1.-btautau) * mygbwkf(9460.30, fullgam, rmsbeam, yint, phi, w)
  tmp += area * btautau * mygbwkftau(9460.30, fullgam, rmsbeam, tauyint, tauphi, w)
  tmp += back * (1.-twophofrac) * 9000.**2 / w**2
  tmp += back * twophofrac * log(w**2/9000.**2)
  return tmp

def u1deriv(w):
  return (u1func(w+0.1) - u1func(w-0.1)) / 0.2

def u2func(w, area=5.59, rmsbeam=4.17, back=0.405, fullgam=0.043, yint=0.01792, phi=0., btautau=0.017, tauyint=0.37, tauphi=0., twophofrac=0.0792, u1area=13.7):
  tmp = 0.
  tmp += area * (1.-btautau) * mygbwkf(10023.26, fullgam, rmsbeam, yint, phi, w)
  tmp += area * btautau * mygbwkftau(10023.26, fullgam, rmsbeam, tauyint, tauphi, w)
  tmp += back * (1.-twophofrac) * 9000.**2 / w**2
  tmp += back * twophofrac * log(w**2/9000.**2)
  tmp += u1area * mygbwkf(9460.30, 0., 0., 0., 0., w)
  return tmp

def u2deriv(w):
  return (u2func(w+0.1) - u2func(w-0.1)) / 0.2

def u3func(w, area=3.582, rmsbeam=4.479, back=0.404, fullgam=0.0263, yint=0.01823, phi=0., btautau=0.0239, tauyint=0.27, tauphi=0., twophofrac=0.0792, u1area=13.7, u2area=5.59):
  tmp = 0.
  tmp += area * (1.-btautau) * mygbwkf(10355.2, fullgam, rmsbeam, yint, phi, w)
  tmp += area * btautau * mygbwkftau(10355.2, fullgam, rmsbeam, tauyint, tauphi, w)
  tmp += back * (1.-twophofrac) * 9000.**2 / w**2
  tmp += back * twophofrac * log(w**2/9000.**2)
  tmp += u1area * mygbwkf(9460.30, 0., 0., 0., 0., w)
  tmp += u2area * mygbwkf(10023.26, 0., 0., 0., 0., w)
  return tmp

def u3deriv(w):
  return (u3func(w+0.1) - u3func(w-0.1)) / 0.2

def crosssec_vstime(r):
  therun = getdb(r)
  g = therun.gamgam_vstime
  h = therun.hadroncool_vstime
  return (h / g) / runsummary[r].energy**2

def usedinscan(r):
  return (123164 <= r <= 123178) or \
         (123596 <= r <= 123718) or \
         (123781 <= r <= 123893) or \
         (124080 <= r <= 124092) or \
         (124102 <= r <= 124214) or \
         (124279 <= r <= 124394) or \
         (124436 <= r <= 124519) or \
         (124625 <= r <= 124736) or \
         (125119 <= r <= 125127) or \
         (125254 <= r <= 125262) or \
         (125285 <= r <= 125295) or \
         (125303 <= r <= 125416) or \
         (126449 <= r <= 126568) or \
         (126776 <= r <= 126783) or \
         (126814 <= r <= 126915) or \
         (127588 <= r <= 127615) or \
         (127924 <= r <= 127933) or \
         (128303 <= r <= 128316) or \
         (121884 <= r <= 122007) or \
         (122069 <= r <= 122178) or \
         (122245 <= r <= 122326) or \
         (122409 <= r <= 122527) or \
         (122535 <= r <= 122757) or \
         (122766 <= r <= 122881) or \
         (122993 <= r <= 123101)

def energyMeV(r):
  en = runsummary[r].energy * 2000.
  if (123164 <= r <= 123178): en += 0.25
  if (123596 <= r <= 123718): en += 0.63
  if (123781 <= r <= 123893): en += 0.075
  if (124080 <= r <= 124092): en += 0.065
  if (124102 <= r <= 124214): en += 0.23
  if (124279 <= r <= 124394): en += 0.19
  if (124436 <= r <= 124519): en += 0.20
  if (124625 <= r <= 124736): en += 0.57
  if (125119 <= r <= 125127): en += 0.91
  if (125254 <= r <= 125262): en += 0.80
  if (125285 <= r <= 125295): en += 0.46
  if (125303 <= r <= 125416): en += 0.62
  
  if (126449 <= r <= 126568): en += -1.12
  if (126776 <= r <= 126783): en += -1.05
  if (126814 <= r <= 126915): en += -1.41
  if (127588 <= r <= 127615): en += -0.75
  if (127924 <= r <= 127933): en += -0.65
  if (128303 <= r <= 128316): en += -0.39

  if (121884 <= r <= 122007): en += -2.12
  if (122069 <= r <= 122178): en += -3.99
  if (122245 <= r <= 122326): en += -3.18
  if (122409 <= r <= 122527): en += -2.46
  if (122535 <= r <= 122757): en += -2.72
  if (122766 <= r <= 122881): en += -2.55
  if (122993 <= r <= 123101): en += -2.64

  return en

u1runs = []
u1vstime = {}
for r in initialrunlist:
  if usedinscan(r) and runsummary[r].res == 1 and r not in mybadruns:
    if 1. < abs(energyMeV(r) - 9460.30) < 7.:
      u1runs.append(r)
      u1vstime[r] = crosssec_vstime(r) - u1func(energyMeV(r))
u2runs = []
u2vstime = {}
for r in initialrunlist:
  if usedinscan(r) and runsummary[r].res == 2 and r not in mybadruns:
    if 1. < abs(energyMeV(r) - 10023.26) < 7.:
      u2runs.append(r)
      u2vstime[r] = crosssec_vstime(r) - u2func(energyMeV(r))
u3runs = []
u3vstime = {}
for r in initialrunlist:
  if usedinscan(r) and runsummary[r].res == 3 and r not in mybadruns:
    if 1. < abs(energyMeV(r) - 10355.2) < 7.:
      u3runs.append(r)
      u3vstime[r] = crosssec_vstime(r) - u3func(energyMeV(r))

for r in u1runs:
  if -5. < energyMeV(r) - 9460.30 < -1.:
    p = u1vstime[r].plot(False, errorbars=True, points=True)
    p.add(biggles.LineY(0.))
    p.yrange = -1., 1.
    p.y2.range = Numeric.array(p.y1.range) / u1deriv(energyMeV(r))
    p.xrange = 0., 1.
    p.show()
    raw_input(r)

for r in u2runs:
  if -5. < energyMeV(r) - 10023.26 < -1.:
    p = u2vstime[r].plot(False, errorbars=True, points=True)
    p.add(biggles.LineY(0.))
    p.yrange = -1., 1.
    p.y2.range = Numeric.array(p.y1.range) / u2deriv(energyMeV(r))
    p.xrange = 0., 1.
    p.show()
    raw_input(r)

for r in u3runs:
  if -5. < energyMeV(r) - 10355.2 < -1.:
    p = u3vstime[r].plot(False, errorbars=True, points=True)
    p.add(biggles.LineY(0.))
    p.yrange = -1., 1.
    p.y2.range = Numeric.array(p.y1.range) / u3deriv(energyMeV(r))
    p.xrange = 0., 1.
    p.show()
    raw_input(r)

# 123178
# 123596
# 123604
# 123705
# 123781
# 123790
# 123828
# 123832
# 124080
# 124091
# 124102
# 124111
# 124279
# 124290
# 124294
# 124436
# 124437
# 124445
# 124450
# 124625
# 124632
# 124639
# 125125
# 125126
# 125259
# 125285
# 125291
# 125295
# 125309

# 126462
# 126464
# 126465
# 126467
# 126776
# 126777
# 126778
# 126779
# 126823
# 126824
# 126825
# 127588
# 127589
# 127592
# 127610
# 127611
# 127612
# 127924
# 127925
# 127927
# 128310
# 128312
# 128313

# 121898
# 122076
# 122245
# 122256
# 122409
# 122415
# 122535
# 122542
# 122556
# 122564
# 122766
# 122776
# 122993
# 123004
