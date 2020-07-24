# Check for continuum shifts, with bhabhas for extra sensitivity

# tmprunlist = []
# for r in initialrunlist:
#   if r not in mybadruns and runsummary[r].res == 2 and runsummary[r].kind == 'c' and 128425 < r:
#     tmprunlist.append(r)
# tmp1, tmp2, tmp3 = get_runs(tmprunlist, usebhabha=True)

# tmprunlist_again = []
# for r in initialrunlist:
#   if r not in mybadruns and runsummary[r].res == 2 and runsummary[r].kind == 'c' and 126432 < r < 128425:
#     tmprunlist_again.append(r)
# tmp1_again, tmp2_again, tmp3_again = get_runs(tmprunlist_again, usebhabha=True)




# Yes, you get the same thing by combining data as you do with a run-by-run weighted mean
#
# tmpcs1 = []
# tmpcs2 = []
# tmpcs3 = []
# for r in u1runs["cont"]:
#   tmpcs1.append(get_runs([r], usebhabha=True, energycorrection=False))
# for r in u2runs["cont"]:
#   tmpcs2.append(get_runs([r], usebhabha=True, energycorrection=False))
# for r in u3runs["cont"]:
#   tmpcs3.append(get_runs([r], usebhabha=True, energycorrection=False))

# print (jt.wmean(map(lambda (r, c, e): (c, e), tmpcs1))[0]-u1data["cont"][1])/u1data["cont"][2]
# print (jt.wmean(map(lambda (r, c, e): (c, e), tmpcs2))[0]-u2data["cont"][1])/u2data["cont"][2]
# print (jt.wmean(map(lambda (r, c, e): (c, e), tmpcs3))[0]-u3data["cont"][1])/u3data["cont"][2]

# The new calculation of hadronic cross-section is not at fault: even
# the old mistake in handling beam-gas error contributions has
# negligible effect.  I still see an overall reasonable chi^2, but
# discrepancies when I split into 1scont, 2scont, and 3scont.
#
# cross = {}
# cross_err = {}
# for r in initialrunlist:
#   if r not in mybadruns and runsummary[r].kind == 'c':
#     therun = getdb(r)

#     if r not in mycarefulscan:
#       efficiency = therun.bhabha_cotTnumer.divide_by_superset(therun.bhabha_cotTdenom)
#       for i, d in enumerate(therun.bhabha_cotTdenom):
#         if d == 0:
#           efficiency.vals[i] = 1.
#       gamgamcor = (therun.gamgam_cotT_cut / efficiency).sum()
#       gamgamcor_err = (therun.gamgam_cotT_cut / efficiency).sumerr()

#       e = 1. * (ebeam.hadroncool - 1.*nobeam.hadroncool*ebeam.cosmic/nobeam.cosmic) * therun.beamgase / ebeam.beamgase
#       p = 1. * (pbeam.hadroncool - 1.*nobeam.hadroncool*pbeam.cosmic/nobeam.cosmic) * therun.beamgasp / pbeam.beamgasp
#       c = 1. * nobeam.hadroncool * therun.cosmic / nobeam.cosmic

#       hadronraw = therun.hadroncool
#       hadroncor = therun.hadroncool - e/2. - p/2. - c
#       hadroncor_err = sqrt(therun.hadroncool + therun.cosmic*(1.*nobeam.hadron/nobeam.cosmic)**2 + (e/2.)**2 + (p/2.)**2)

#     else:
#       gamgamcor = therun.gamgam_vstime.sum(0.,0.99) * 0.9976
#       gamgamcor_err = sqrt(gamgamcor)

#       e = 1. * (ebeam.hadroncool_vstime.sum(0.,0.99) - 1.*nobeam.hadroncool_vstime.sum(0.,0.99)*ebeam.cosmic/nobeam.cosmic) * therun.beamgase / ebeam.beamgase
#       p = 1. * (pbeam.hadroncool_vstime.sum(0.,0.99) - 1.*nobeam.hadroncool_vstime.sum(0.,0.99)*pbeam.cosmic/nobeam.cosmic) * therun.beamgasp / pbeam.beamgasp
#       c = 1. * nobeam.hadroncool_vstime.sum(0.,0.99) * therun.cosmic / nobeam.cosmic

#       hadronraw = therun.hadroncool_vstime.sum(0.,0.99)
#       hadroncor = therun.hadroncool_vstime.sum(0.,0.99) - e/2. - p/2. - c
#       hadroncor_err = sqrt(therun.hadroncool_vstime.sum(0.,0.99) + therun.cosmic*(1.*nobeam.hadron/nobeam.cosmic)**2 + (e/2.)**2 + (p/2.)**2)
      
#     cross[r] = hadroncor / gamgamcor # / runsummary[r].energy**2
#     cross_err[r] = cross[r] * sqrt((1.*hadroncor_err/hadroncor)**2 + (1.*gamgamcor_err/gamgamcor)**2)
# tmpcs1 = []
# tmpcs1_err = []
# tmpcs2 = []
# tmpcs2_err = []
# tmpcs3 = []
# tmpcs3_err = []
# tmpcs = []
# tmpcs_err = []
# for r in initialrunlist:
#   if r not in mybadruns:
#     if runsummary[r].res == 1 and runsummary[r].kind == 'c':
#       tmpcs1.append(cross[r])
#       tmpcs1_err.append(cross_err[r])
#     if runsummary[r].res == 2 and runsummary[r].kind == 'c':
#       tmpcs2.append(cross[r])
#       tmpcs2_err.append(cross_err[r])
#     if runsummary[r].res == 3 and runsummary[r].kind == 'c':
#       tmpcs3.append(cross[r])
#       tmpcs3_err.append(cross_err[r])
#     if runsummary[r].kind == 'c':
#       tmpcs.append(cross[r])
#       tmpcs_err.append(cross_err[r])
# print jt.wmean(zip(tmpcs1, tmpcs1_err)), u1data["cont"][1:]
# print jt.wmean(zip(tmpcs2, tmpcs2_err)), u2data["cont"][1:]
# print jt.wmean(zip(tmpcs3, tmpcs3_err)), u3data["cont"][1:]
# print jt.wmean(zip(tmpcs, tmpcs_err))

# print (jt.wmean(zip(tmpcs1, tmpcs1_err))[0]-jt.wmean(zip(tmpcs, tmpcs_err))[0])/jt.wmean(zip(tmpcs1, tmpcs1_err))[1]
# print (jt.wmean(zip(tmpcs2, tmpcs2_err))[0]-jt.wmean(zip(tmpcs, tmpcs_err))[0])/jt.wmean(zip(tmpcs2, tmpcs2_err))[1]
# print (jt.wmean(zip(tmpcs3, tmpcs3_err))[0]-jt.wmean(zip(tmpcs, tmpcs_err))[0])/jt.wmean(zip(tmpcs3, tmpcs3_err))[1]

# Even adding the tails doesn't help.
# print u1data["cont"][1]
# print u2data["cont"][1] * (1./1.0055)
# print u3data["cont"][1] * (1./1.0121)
# print u1data["cont"][2]




def draw_oneovers(norm, twophotfrac=0., u1=0.):
  x = Numeric.arange(4.65, 5.25+0.01, 0.01)
  y = Numeric.arange(4.65, 5.25+0.01, 0.01)
  for i, xi in enumerate(x):
    y[i] = norm * 4.65**2 / xi**2 + (twophotfrac) * norm * log(xi**2/4.65**2)
    if u1 > 0. and (xi - 9460.3/2000.)/u1 > 1./0.03:
      y[i] += u1/(xi - 9460.3/2000.)
#    y[i] *= xi**2
  return biggles.Curve(x, y)




p = biggles.FramedPlot()
p.add(biggles.Points([u1data["cont"][0], u1data["high"][0], \
                      u2data["cont"][0], u2data["high"][0], \
                      u3data["cont"][0], u3data["high"][0]],
                     [u1data["cont"][1], u1data["high"][1], \
                      u2data["cont"][1], u2data["high"][1], \
                      u3data["cont"][1], u3data["high"][1]]))
p.add(biggles.SymmetricErrorBarsY([u1data["cont"][0], u1data["high"][0], \
                                   u2data["cont"][0], u2data["high"][0], \
                                   u3data["cont"][0], u3data["high"][0]], \
                                  [u1data["cont"][1], u1data["high"][1], \
                                   u2data["cont"][1], u2data["high"][1], \
                                   u3data["cont"][1], u3data["high"][1]], \
                                  [u1data["cont"][2], u1data["high"][2], \
                                   u2data["cont"][2], u2data["high"][2], \
                                   u3data["cont"][2], u3data["high"][2]]))
p.add(draw_oneovers(0.35, 0.13))
p.add(draw_oneovers(0.351, 0))
p.add(draw_oneovers(0.351, 0, 0.0006))
p.add(draw_oneovers(0.351, 0, 0.0012))
p.xrange = 4.65, 5.25
# p.add(draw_oneovers(0.02692, 0.14))
p.show()
p.write_eps("/home/mccann/tmp.ps")





def reshrink(low, high, domore=False):
  tmpruns = []
  for r in initialrunlist:
    if r not in mybadruns and (runsummary[r].kind == 'p' or runsummary[r].kind == 's') and low <= r <= high:
      tmpruns.append(r)
  if domore:
    print tmpruns
  if len(tmpruns) > 0:
    return min(tmpruns), max(tmpruns)
  else:
    return None


###############################################################
# Maybe I get to start here
import biggles, Numeric, cPickle as pickle, time
execfile("/home/mccann/antithesis/utilities.py")

runstart = pickle.load(open("/home/mccann/antithesis/old_dotps/runstart.p"))
runend = pickle.load(open("/home/mccann/antithesis/old_dotps/runend.p"))

def run_date(r):
  if r in runstart and r in runend:
    return (runstart[r] + runend[r])/2.
  elif r in runstart:
    return runstart[r]
  elif r in runend:
    return runend[r]
  else:
    raise Exception

def run_date2(r1, r2):
  dstart = "unknown"
  dend = "unknown"
  if r1 in runstart:
    dstart = time.strftime("%d %b %y %H:%M", time.localtime(runstart[r1]))
  if r2 in runend:
    dend = time.strftime("%d %b %y %H:%M", time.localtime(runend[r2]))
  return dstart, dend

def shrinkmore(res, low, high):
  beginning = run_date(low)

  tmpruns = []
  for r in initialrunlist:
    if r not in mybadruns and low <= r <= high and runsummary[r].res == res:
      if runsummary[r].kind == 's' or runsummary[r].kind == 'p':
        if run_date(r) < beginning + 48.*60.*60:
          tmpruns.append(r)
  return min(tmpruns), max(tmpruns)

scandef = {}

# scandef["jan16"] = (123164, 123178)
# scandef["jan30"] = (123596, 123718)
# scandef["feb06"] = (123781, 123893)
# scandef["feb13"] = (124080, 124092)
# scandef["feb20"] = (124102, 124214)
# scandef["feb27"] = (124279, 124394)
# scandef["mar06"] = (124436, 124519)
# scandef["mar13"] = (124625, 124736)
# scandef["apr03"] = (125119, 125127)
# scandef["apr08"] = (125254, 125262)
# scandef["apr09"] = (125285, 125295)
# scandef["apr10"] = (125303, 125416)

# scandef["may29"] = (126449, 126568)
# scandef["jun11"] = (126776, 126783)
# scandef["jun12"] = (126814, 126915)
# scandef["jul10"] = (127588, 127615)
# scandef["jul24"] = (127924, 127933)
# scandef["aug07"] = (128303, 128316)

# scandef["nov28"] = (121884, 122007)
# scandef["dec05"] = (122069, 122178)
# scandef["dec12"] = (122245, 122326)
# scandef["dec19"] = (122409, 122527)
# scandef["dec26"] = (122535, 122757)
# scandef["jan02"] = (122766, 122881)
# scandef["jan09"] = (122993, 123101)

scandef["jan16"] = shrinkmore(1, 123164, 123178)
scandef["jan30"] = shrinkmore(1, 123596, 123718)
scandef["feb06"] = shrinkmore(1, 123781, 123893)
scandef["feb13"] = shrinkmore(1, 124080, 124092)
scandef["feb20"] = shrinkmore(1, 124102, 124214)
scandef["feb27"] = shrinkmore(1, 124279, 124394)
scandef["mar06"] = shrinkmore(1, 124436, 124519)
scandef["mar13"] = shrinkmore(1, 124625, 124736)
scandef["apr03"] = shrinkmore(1, 125119, 125127)
scandef["apr08"] = shrinkmore(1, 125254, 125262)
scandef["apr09"] = shrinkmore(1, 125285, 125295)
scandef["apr10"] = shrinkmore(1, 125303, 125416)

scandef["may29"] = shrinkmore(2, 126449, 126568)
scandef["jun11"] = shrinkmore(2, 126776, 126783)
scandef["jun12"] = shrinkmore(2, 126814, 126915)
scandef["jul10"] = shrinkmore(2, 127588, 127615)
scandef["jul24"] = shrinkmore(2, 127924, 127933)
scandef["aug07"] = shrinkmore(2, 128303, 128316)

scandef["nov28"] = shrinkmore(3, 121884, 122007)
scandef["dec05"] = shrinkmore(3, 122069, 122178)
scandef["dec12"] = shrinkmore(3, 122245, 122326)
scandef["dec19"] = shrinkmore(3, 122409, 122527)
scandef["dec26"] = shrinkmore(3, 122535, 122757)
scandef["jan02"] = shrinkmore(3, 122766, 122881)
scandef["jan09"] = shrinkmore(3, 122993, 123101)

def tell_me_about(n):
  rstart, rend = scandef[n]
  dstart, dend = run_date2(rstart, rend)
  print n, "&", rstart, "&", rend, "&", dstart, "&", dend, "\\\\"

tell_me_about("jan16")
tell_me_about("jan30")
tell_me_about("feb06")
tell_me_about("feb13")
tell_me_about("feb20")
tell_me_about("feb27")
tell_me_about("mar06")
tell_me_about("mar13")
tell_me_about("apr03")
tell_me_about("apr08")
tell_me_about("apr09")
tell_me_about("apr10")

tell_me_about("may29")
tell_me_about("jun11")
tell_me_about("jun12")
tell_me_about("jul10")
tell_me_about("jul24")
tell_me_about("aug07")

tell_me_about("nov28")
tell_me_about("dec05")
tell_me_about("dec12")
tell_me_about("dec19")
tell_me_about("dec26")
tell_me_about("jan02")
tell_me_about("jan09")

def makelines(start, end, kind=None):
  x = []
  y = []
  for r in range(min(initialrunlist), max(initialrunlist)+1):
    if r in runstart and runstart[r] > start:
      if r in runend and runend[r] != 0. and runend[r] < end:
        if kind == None or (r in runsummary and runsummary[r].kind == kind):
          x.append(runstart[r]-start)
          x.append(runstart[r]-start)
          x.append(runend[r]-start)
          x.append(runend[r]-start)
          y.append(0)
          y.append(1)
          y.append(1)
          y.append(0)
  if len(x) > 0:
    return x, y
  return None

def makelines2(start, end, s, p):
  tmp = []
  for r in range(min(initialrunlist), max(initialrunlist)+1):
    if r in runstart and runstart[r] > start:
      if r in runend and runend[r] != 0. and runend[r] < end:
        if scandef[s][0] <= r <= scandef[s][1]:
          tmp.append(runstart[r]-start)
          tmp.append(runend[r]-start)
  if len(tmp) > 0:
    x = [tmp[0], tmp[0], tmp[-1], tmp[-1]]
    y = [0., 0.5, 0.5, 0.]
    p.add(biggles.FillBelow(x, y, color="white"))
    p.add(biggles.Curve(x, y))
    p.add(biggles.DataLabel((tmp[-1]+tmp[0])/2., 0.25, s))
  return None

def firstafter(t):
  for r in range(min(initialrunlist), max(initialrunlist)+1):
    if r in runstart and runstart[r] > t:
      return str(r)
  return "FINIS!"

def lookat(year, week):
  p = biggles.FramedPlot()
  hack = 3
  if year % 2000 == 2: hack = 2
  start = time.mktime(time.strptime("%02d %03d" % (year % 2000, (week * 7)+hack), "%y %j"))
  end = start + 604800.
  l = makelines(start, end)
  if l != None: p.add(biggles.FillBelow(l[0], l[1], color="gray"))
  l = makelines(start, end, 'p')
  if l != None: p.add(biggles.FillBelow(l[0], l[1], color="light blue"))
  l = makelines(start, end, 'c')
  if l != None: p.add(biggles.FillBelow(l[0], l[1], color="green"))
  l = makelines(start, end, 's')
  if l != None: p.add(biggles.FillBelow(l[0], l[1], color="red"))
  l = makelines(start, end, 'h')
  if l != None: p.add(biggles.FillBelow(l[0], l[1], color="purple"))

  for s in scandef:
    makelines2(start, end, s, p)

  p.x2.label = "Week of "+time.strftime("%a %d %B %Y", time.localtime(start))
  p.y1.range = 0, 1
  p.y1.draw_ticklabels = 0
  p.x1.range = 0, 604800
  p.x2.ticks = map(lambda x: x*604800./7. + 604800./7./2., range(7))
  p.x2.ticklabels = ["Wed", "Thu", "Fri", "Sat", "Sun", "Mon", "Tue"]
  p.x1.ticks = map(lambda x: x*604800./7., range(8))
  p.x1.ticklabels = map(firstafter, map(lambda x: x*604800./7. + start, range(8)))
  p.aspect_ratio = 0.15
  return p

p = biggles.Table(5,1)
p[0,0] = lookat(2001, 44+3)
p[1,0] = lookat(2001, 44+4)
p[2,0] = lookat(2001, 44+5)
p[3,0] = lookat(2001, 44+6)
p[4,0] = lookat(2001, 44+7)
p.aspect_ratio = 11./8.5
p.show()
p.write_eps("/home/mccann/antithesis/clns/scan_periods1.eps")

p = biggles.Table(5,1)
p[0,0] = lookat(2002, 0)
p[1,0] = lookat(2002, 1)
p[2,0] = lookat(2002, 2)
p[3,0] = lookat(2002, 4)
p[4,0] = lookat(2002, 5)
p.aspect_ratio = 11./8.5
p.show()
p.write_eps("/home/mccann/antithesis/clns/scan_periods2.eps")

p = biggles.Table(5,1)
p[0,0] = lookat(2002, 6)
p[1,0] = lookat(2002, 7)
p[2,0] = lookat(2002, 8)
p[3,0] = lookat(2002, 9)
p[4,0] = lookat(2002, 10)
p.aspect_ratio = 11./8.5
p.show()
p.write_eps("/home/mccann/antithesis/clns/scan_periods3.eps")

p = biggles.Table(5,1)
p[0,0] = lookat(2002, 12)
p[1,0] = lookat(2002, 13)
p[2,0] = lookat(2002, 14)
p[3,0] = lookat(2002, 21)
p[4,0] = lookat(2002, 22)
p.aspect_ratio = 11./8.5
p.show()
p.write_eps("/home/mccann/antithesis/clns/scan_periods4.eps")

p = biggles.Table(5,1)
p[0,0] = lookat(2002, 23)
p[1,0] = lookat(2002, 27)
p[2,0] = lookat(2002, 28)
p[3,0] = lookat(2002, 29)
p[4,0] = lookat(2002, 31)
p.aspect_ratio = 11./8.5
p.show()
p.write_eps("/home/mccann/antithesis/clns/scan_periods5.eps")




# p = biggles.Table(5,1)
# p[0,0] = lookat(2001, 44+0)
# p[1,0] = lookat(2001, 44+1)
# p[2,0] = lookat(2001, 44+2)
# p[3,0] = lookat(2001, 44+3)
# p[4,0] = lookat(2001, 44+4)
# p.aspect_ratio = 11./8.5
# p.show()
# p.write_eps("plots/fits2_dates01.eps")

# p = biggles.Table(5,1)
# p[0,0] = lookat(2001, 44+5)
# p[1,0] = lookat(2001, 44+6)
# p[2,0] = lookat(2001, 44+7)
# p[3,0] = lookat(2002, 0)
# p[4,0] = lookat(2002, 1)
# p.aspect_ratio = 11./8.5
# p.show()
# p.write_eps("plots/fits2_dates02.eps")

# p = biggles.Table(5,1)
# p[0,0] = lookat(2002, 2)
# p[1,0] = lookat(2002, 3)
# p[2,0] = lookat(2002, 4)
# p[3,0] = lookat(2002, 5)
# p[4,0] = lookat(2002, 6)
# p.aspect_ratio = 11./8.5
# p.show()
# p.write_eps("plots/fits2_dates03.eps")

# p = biggles.Table(5,1)
# p[0,0] = lookat(2002, 7)
# p[1,0] = lookat(2002, 8)
# p[2,0] = lookat(2002, 9)
# p[3,0] = lookat(2002, 10)
# p[4,0] = lookat(2002, 11)
# p.aspect_ratio = 11./8.5
# p.show()
# p.write_eps("plots/fits2_dates04.eps")

# p = biggles.Table(5,1)
# p[0,0] = lookat(2002, 12)
# p[1,0] = lookat(2002, 13)
# p[2,0] = lookat(2002, 14)
# p[3,0] = lookat(2002, 15)
# p[4,0] = lookat(2002, 16)
# p.aspect_ratio = 11./8.5
# p.show()
# p.write_eps("plots/fits2_dates05.eps")

# p = biggles.Table(5,1)
# p[0,0] = lookat(2002, 17)
# p[1,0] = lookat(2002, 18)
# p[2,0] = lookat(2002, 19)
# p[3,0] = lookat(2002, 20)
# p[4,0] = lookat(2002, 21)
# p.aspect_ratio = 11./8.5
# p.show()
# p.write_eps("plots/fits2_dates06.eps")

# p = biggles.Table(5,1)
# p[0,0] = lookat(2002, 22)
# p[1,0] = lookat(2002, 23)
# p[2,0] = lookat(2002, 24)
# p[3,0] = lookat(2002, 25)
# p[4,0] = lookat(2002, 26)
# p.aspect_ratio = 11./8.5
# p.show()
# p.write_eps("plots/fits2_dates07.eps")

# p = biggles.Table(5,1)
# p[0,0] = lookat(2002, 27)
# p[1,0] = lookat(2002, 28)
# p[2,0] = lookat(2002, 29)
# p[3,0] = lookat(2002, 30)
# p[4,0] = lookat(2002, 31)
# p.aspect_ratio = 11./8.5
# p.show()
# p.write_eps("plots/fits2_dates08.eps")

# p = biggles.Table(5,1)
# p[0,0] = lookat(2002, 33)
# p[1,0] = lookat(2002, 34)
# p[2,0] = lookat(2002, 35)
# p[3,0] = lookat(2002, 36)
# p[4,0] = lookat(2002, 37)
# p.aspect_ratio = 11./8.5
# p.show()
# p.write_eps("plots/fits2_dates09.eps")

# p = biggles.Table(5,1)
# p[0,0] = lookat(2002, 38)
# p[1,0] = lookat(2002, 39)
# p[2,0] = lookat(2002, 40)
# p[3,0] = lookat(2002, 41)
# p[4,0] = lookat(2002, 42)
# p.aspect_ratio = 11./8.5
# p.show()
# p.write_eps("plots/fits2_dates10.eps")

# p = biggles.Table(5,1)
# p[0,0] = lookat(2002, 43)
# p[1,0] = lookat(2002, 44)
# p[2,0] = lookat(2002, 45)
# p[3,0] = lookat(2002, 46)
# p[4,0] = lookat(2002, 47)
# p.aspect_ratio = 11./8.5
# p.show()
# p.write_eps("plots/fits2_dates11.eps")






def plotfun(f, low, high, points=100):
  x = Numeric.arange(low, high+(high-low)/points, (high-low)/points)
  y = Numeric.arange(low, high+(high-low)/points, (high-low)/points)
  for i, xi in enumerate(x):
    y[i] = f(xi)
  return biggles.Curve(x, y)

def mygbwkf(mass, fullgam, rmsbeam, yint, phi, w):
  if w > mass + 200.:
    return 0.076/(w-mass)
  return gbwkf(mass, fullgam, rmsbeam, yint, phi, w-mass)

p = biggles.FramedPlot()
p.add(plotfun(lambda x: mygbwkf(9460.30, 0.043, 5., 0.018, 0., x), 9460.30-5., 5.25*2000.))
p.add(plotfun(lambda x: mygbwkf(10023.26, 0.043, 5., 0.018, 0., x), 10023.26-5., 5.25*2000.))
p.add(plotfun(lambda x: mygbwkf(10355.2, 0.043, 5., 0.018, 0., x), 10355.2-5., 5.25*2000.))
p.ylog = 1
p.show()

p = biggles.FramedPlot()
p.add(plotfun(lambda x: mygbwkf(9460.30, 0.043, 3., 0.018, 0., x), 9460.30-5., 5.25*2000.))
p.add(plotfun(lambda x: mygbwkf(10023.26, 0.043, 3., 0.018, 0., x), 10023.26-5., 5.25*2000.))
p.add(plotfun(lambda x: mygbwkf(10355.2, 0.043, 3., 0.018, 0., x), 10355.2-5., 5.25*2000.))
p.ylog = 1
p.show()



