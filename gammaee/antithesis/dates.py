# Execute this LISP before starting python:
# (setenv "LD_LIBRARY_PATH" "/nfs/cleo3/Offline/rel/current/other_sources/mico/lib:$USER_DAF/software/lib/roofit_core:$USER_DAF/software/lib/roofit_models:/nfs/cleo3/Offline/rel/current/other_sources/Root/lib:/nfs/cleo3/Offline/rel/current/other_sources/python/lib:/cdat/daf9/mccann/software/lib")

execfile("utilities.py")
import os, time

def runtimes(run):
  startstr = os.popen("/nfs/cleo3/Common/rel/current/bin/i686-pc-linux-gnu/DBRunStatisticsRetrieve "+str(run)+" 4 | fgrep 'Created on E'").readline()[11:35]
  start = None
  if startstr[0:3] == "EST" or startstr[0:3] == "EDT":
    start = time.mktime(time.strptime(startstr, "%Z: %m/%d/%Y %H:%M:%S"))

  endstr = os.popen("/nfs/cleo3/Common/rel/current/bin/i686-pc-linux-gnu/DBRunStatisticsRetrieve "+str(run)+" 16 | fgrep 'Created on E'").readline()[11:35]
  end = None
  if endstr[0:3] == "EST" or endstr[0:3] == "EDT":
    end = time.mktime(time.strptime(endstr, "%Z: %m/%d/%Y %H:%M:%S"))

  return start, end

# def runtimes(run):
#   startstr = os.popen("/nfs/cleo3/Common/rel/current/bin/i686-pc-linux-gnu/DBRunStatisticsRetrieve "+str(run)+" 4 | fgrep 'Created on E'").readline()[11:35]
#   start = None
#   if startstr[0:3] == "EST" or startstr[0:3] == "EDT":
#     start = time.mktime(time.strptime(startstr, "%Z: %m/%d/%Y %H:%M:%S"))

#   endstr = os.popen("/nfs/cleo3/Common/rel/current/bin/i686-pc-linux-gnu/DBRunStatisticsRetrieve "+str(run)+" 16 | fgrep 'Created on E'").readline()[11:35]
#   end = None
#   if endstr[0:3] == "EST" or endstr[0:3] == "EDT":
#     end = time.mktime(time.strptime(endstr, "%Z: %m/%d/%Y %H:%M:%S"))

#   if start != None:
#     runstart[r] = start
#   if end != None:
#     runend[r] = end
#   print r, start, end
# runstart = {}
# runend = {}
# for r in range(min(initialrunlist), max(initialrunlist)+1): runtimes(r)
# pickle.dump(runstart, open("runstart.p", 'w'))
# pickle.dump(runend, open("runend.p", 'w'))
runstart = pickle.load(open("old_dotps/runstart.p"))
runend = pickle.load(open("old_dotps/runend.p"))


gapafterrun = {}
end = runend[min(initialrunlist)]
for r in range(min(initialrunlist)+1, max(initialrunlist)+1):
  thestart = end
  theend = end
  if r in runstart and runstart[r] != 0.:
    thestart = runstart[r]
  if r in runend and runend[r] != 0.:
    theend = runend[r]
  else:
    theend = thestart
  if r not in runstart or runstart[r] == 0.:
    thestart = theend
  gapafterrun[r-1] = thestart - end
  end = theend

def runsomething(r):
  if r in runstart and runstart[r] != 0.:
    return runstart[r]
  if r in runend and runend[r] != 0.:
    return runend[r]
  return runsomething(r-1)

p = biggles.FramedPlot()
p.add(biggles.Points(map(runsomething, range(min(initialrunlist), max(initialrunlist))),\
                     map(lambda r: (gapafterrun[r]+0.001) / 60. / 60., range(min(initialrunlist), max(initialrunlist))), symboltype="filled circle", symbolsize=0.4))
p.y1.log = 1
p.y1.range = 0.1, 30
p.show()

for r in range(min(initialrunlist)+1, max(initialrunlist)):
  if gapafterrun[r] < 0.:
    print r

h = hist.h1(130, 0, 6.5)
for r in range(min(initialrunlist)+1, max(initialrunlist)):
  if gapafterrun[r] != 0.:
    h.fill(log10(gapafterrun[r]))
h.plot().show()

h1 = hist.h1(70, 0, 604800)
h2 = hist.h1(70, 0, 604800)
for r in range(min(initialrunlist)+1, max(initialrunlist)):
  if gapafterrun[r] != 0.:
    h1.fill(runsomething(r) % 604800)
    h2.fill(runsomething(r) % 604800, gapafterrun[r])
(h2 / h1 / 60. / 60.).plot().show()

h1.plot().show()
h2.plot().show()


##############################################

initialrunlist.sort()
old = 0.
for r in initialrunlist:
  if r in runstart and runstart[r] != 0.:
    if runstart[r] > old:
      old = runstart[r]
    else:
      raise str(r)+" runstart"
  if r in runend and runend[r] != 0.:
    if runend[r] > old:
      old = runend[r]
    else:
      raise str(r)+" runend"
    
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

def firstafter(t):
  for r in range(min(initialrunlist), max(initialrunlist)+1):
    if r in runstart and runstart[r] > t:
      return str(r)
  return "XXXXXX"

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
  if l != None: p.add(biggles.FillBelow(l[0], l[1], color="red"))
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

p = biggles.Table(6,1)
p[0,0] = lookat(2002, 9)
p[1,0] = lookat(2002, 10)
p[2,0] = lookat(2002, 11)
p[3,0] = lookat(2002, 12)
p[4,0] = lookat(2002, 13)
p[5,0] = lookat(2002, 14)
p.aspect_ratio = 11./8.5
p.show()
p.write_eps("dates_wierd_happenings.eps")




p = biggles.Table(5,1)
p[0,0] = lookat(2001, 44+0)
p[1,0] = lookat(2001, 44+1)
p[2,0] = lookat(2001, 44+2)
p[3,0] = lookat(2001, 44+3)
p[4,0] = lookat(2001, 44+4)
p.aspect_ratio = 11./8.5
p.show()
p.write_eps("plots/dates1.eps")

p = biggles.Table(5,1)
p[0,0] = lookat(2001, 44+5)
p[1,0] = lookat(2001, 44+6)
p[2,0] = lookat(2001, 44+7)
p[3,0] = lookat(2002, 0)
p[4,0] = lookat(2002, 1)
p.aspect_ratio = 11./8.5
p.show()
p.write_eps("plots/dates2.eps")

p = biggles.Table(5,1)
p[0,0] = lookat(2002, 2)
p[1,0] = lookat(2002, 3)
p[2,0] = lookat(2002, 4)
p[3,0] = lookat(2002, 5)
p[4,0] = lookat(2002, 6)
p.aspect_ratio = 11./8.5
p.show()
p.write_eps("plots/dates3.eps")

p = biggles.Table(5,1)
p[0,0] = lookat(2002, 7)
p[1,0] = lookat(2002, 8)
p[2,0] = lookat(2002, 9)
p[3,0] = lookat(2002, 10)
p[4,0] = lookat(2002, 11)
p.aspect_ratio = 11./8.5
p.show()
p.write_eps("plots/dates4.eps")

p = biggles.Table(5,1)
p[0,0] = lookat(2002, 12)
p[1,0] = lookat(2002, 13)
p[2,0] = lookat(2002, 14)
p[3,0] = lookat(2002, 15)
p[4,0] = lookat(2002, 16)
p.aspect_ratio = 11./8.5
p.show()
p.write_eps("plots/dates5.eps")

p = biggles.Table(5,1)
p[0,0] = lookat(2002, 17)
p[1,0] = lookat(2002, 18)
p[2,0] = lookat(2002, 19)
p[3,0] = lookat(2002, 20)
p[4,0] = lookat(2002, 21)
p.aspect_ratio = 11./8.5
p.show()
p.write_eps("plots/dates6.eps")

p = biggles.Table(5,1)
p[0,0] = lookat(2002, 22)
p[1,0] = lookat(2002, 23)
p[2,0] = lookat(2002, 24)
p[3,0] = lookat(2002, 25)
p[4,0] = lookat(2002, 26)
p.aspect_ratio = 11./8.5
p.show()
p.write_eps("plots/dates7.eps")

p = biggles.Table(5,1)
p[0,0] = lookat(2002, 27)
p[1,0] = lookat(2002, 28)
p[2,0] = lookat(2002, 29)
p[3,0] = lookat(2002, 30)
p[4,0] = lookat(2002, 31)
p.aspect_ratio = 11./8.5
p.show()
p.write_eps("plots/dates8.eps")

p = biggles.Table(5,1)
p[0,0] = lookat(2002, 33)
p[1,0] = lookat(2002, 34)
p[2,0] = lookat(2002, 35)
p[3,0] = lookat(2002, 36)
p[4,0] = lookat(2002, 37)
p.aspect_ratio = 11./8.5
p.show()
p.write_eps("plots/dates9.eps")

p = biggles.Table(5,1)
p[0,0] = lookat(2002, 38)
p[1,0] = lookat(2002, 39)
p[2,0] = lookat(2002, 40)
p[3,0] = lookat(2002, 41)
p[4,0] = lookat(2002, 42)
p.aspect_ratio = 11./8.5
p.show()
p.write_eps("plots/dates10.eps")

p = biggles.Table(5,1)
p[0,0] = lookat(2002, 43)
p[1,0] = lookat(2002, 44)
p[2,0] = lookat(2002, 45)
p[3,0] = lookat(2002, 46)
p[4,0] = lookat(2002, 47)
p.aspect_ratio = 11./8.5
p.show()
p.write_eps("plots/dates11.eps")


for low, high in ((128756, 128849), ):
  en = []
  cs = []
  cs_err = []
  for r in initialrunlist:
    if r not in mybadruns:
      if low <= r <= high:
        en.append(runsummary[r].energy)
        cs.append(cross[r])
        cs_err.append(cross_err[r])
  p = biggles.FramedPlot()
  p.add(biggles.Points(en, cs, symboltype="filled circle", symbolsize=0.7))
  p.add(biggles.SymmetricErrorBarsY(en, cs, cs_err))
  p.show()




def shrinkwrap(rstart, rend):
  reducedlist_old = []
  for r in range(rstart, rend):
    if r in initialrunlist and r not in mybadruns:
      reducedlist_old.append(r)

  reducedlist = []
  for r in range(rstart, rend+1):
    if r in initialrunlist and r not in mybadruns:
      reducedlist.append(r)

  print min(reducedlist), "-", "old:", max(reducedlist_old), "new:", max(reducedlist)

shrinkwrap(123144, 123193)
shrinkwrap(123359, 123382)
shrinkwrap(123563, 123741)
shrinkwrap(123741, 123903)
shrinkwrap(123936, 123962)
shrinkwrap(124052, 124092)
shrinkwrap(124094, 124258)
shrinkwrap(124258, 124415)
shrinkwrap(124415, 124522)
shrinkwrap(124807, 124820)
shrinkwrap(124607, 124764)
shrinkwrap(124958, 124973)
shrinkwrap(125095, 125147)
shrinkwrap(125158, 125178)
shrinkwrap(125254, 125262)
shrinkwrap(125277, 125297)
shrinkwrap(125298, 125433)
shrinkwrap(126438, 126569)
shrinkwrap(126641, 126674)
shrinkwrap(126763, 126786)
shrinkwrap(126787, 126917)
shrinkwrap(127048, 127135)
shrinkwrap(127191, 127250)
shrinkwrap(127570, 127641)
shrinkwrap(127683, 127739)
shrinkwrap(127906, 127963)
shrinkwrap(127643, 127682)
shrinkwrap(128291, 128316)
shrinkwrap(121880, 122013)
shrinkwrap(122037, 122198)
shrinkwrap(122225, 122330)
shrinkwrap(122401, 122534)
shrinkwrap(122535, 122653)
shrinkwrap(122757, 122897)
shrinkwrap(122991, 123144)
shrinkwrap(127761, 127906)
shrinkwrap(128099, 128154)


for r in initialrunlist:
  if r not in mybadruns:
    if r not in runstart and r not in runend:
      print r



def preferend(r):
  if r in runend and runend[r] != 0.:
    return runend[r]
  if r in runstart and runstart[r] != 0.:
    return runstart[r]
  return None

def preferstart(r):
  if r in runstart and runstart[r] != 0.:
    return runstart[r]
  if r in runend and runend[r] != 0.:
    return runend[r]
  return None

def biggestgap(rstart, rend):
  end = preferend(rstart)
  biggap = 0.
  for r in range(rstart+1, rend+1):
    start = preferstart(r)
    if start != None:
      gap = start - end
      if gap > biggap: biggap = gap
      end = preferend(r)
  return biggap / 60. / 60.

def special_shrinkwrap(rstart, rend):
  reducedlist = []
  for r in range(rstart, rend+1):
    if r in initialrunlist and r not in mybadruns:
      if runsummary[r].kind != 'c' and runsummary[r].kind != 'h':
        reducedlist.append(r)
  reducedlist.sort()
  return min(reducedlist), max(reducedlist)

print biggestgap(*special_shrinkwrap(123144, 123193))
print biggestgap(*special_shrinkwrap(123563, 123741))
print biggestgap(*special_shrinkwrap(123741, 123903))
print biggestgap(*special_shrinkwrap(124052, 124092))
print biggestgap(*special_shrinkwrap(124094, 124258))
print biggestgap(*special_shrinkwrap(124258, 124415))
print biggestgap(*special_shrinkwrap(124415, 124522))
print biggestgap(*special_shrinkwrap(124607, 124764))
print biggestgap(*special_shrinkwrap(125095, 125147))
print biggestgap(*special_shrinkwrap(125254, 125262))
print biggestgap(*special_shrinkwrap(125277, 125297))
print biggestgap(*special_shrinkwrap(125298, 125433))
print biggestgap(*special_shrinkwrap(126438, 126569))
print biggestgap(*special_shrinkwrap(126763, 126786))
print biggestgap(*special_shrinkwrap(126787, 126917))
print biggestgap(*special_shrinkwrap(127570, 127641))
print biggestgap(*special_shrinkwrap(127906, 127963))
print biggestgap(*special_shrinkwrap(128291, 128316))
print biggestgap(*special_shrinkwrap(121880, 122013))
print biggestgap(*special_shrinkwrap(122037, 122198))
print biggestgap(*special_shrinkwrap(122225, 122330))
print biggestgap(*special_shrinkwrap(122401, 122534))
print biggestgap(*special_shrinkwrap(122535, 122653))
print biggestgap(*special_shrinkwrap(122757, 122897))
print biggestgap(*special_shrinkwrap(122991, 123144))
print biggestgap(*special_shrinkwrap(127761, 127906))



scandef = {}
scandef["jan16"] = (lambda r: 123164 <= r <= 123193 or 123369 <= r <= 123382)
scandef["jan30"] = (lambda r: 123565 <= r <= 123718)
scandef["feb06"] = (lambda r: 123767 <= r <= 123893)
scandef["feb13"] = (lambda r: 123938 <= r <= 123962 or 124080 <= r <= 124092)
scandef["feb20"] = (lambda r: 124102 <= r <= 124214)
scandef["feb27"] = (lambda r: 124279 <= r <= 124394)
scandef["mar06"] = (lambda r: 124436 <= r <= 124522 or 124807 <= r <= 124820)
scandef["mar13"] = (lambda r: 124625 <= r <= 124736 or 124960 <= r <= 124973)
scandef["apr03"] = (lambda r: 125119 <= r <= 125127 or 125158 <= r <= 125178)
scandef["apr08"] = (lambda r: 125254 <= r <= 125262 or r == 124954)
scandef["apr09"] = (lambda r: 125285 <= r <= 125297)
scandef["apr10"] = (lambda r: 125303 <= r <= 125416)
scandef["may29"] = (lambda r: 126449 <= r <= 126568)
scandef["jun11"] = (lambda r: 126651 <= r <= 126673 or 126776 <= r <= 126783)
scandef["jun12"] = (lambda r: 126814 <= r <= 126915 or 127059 <= r <= 127116 or 127206 <= r <= 127250)
scandef["jul10"] = (lambda r: 127588 <= r <= 127641)
scandef["jul24"] = (lambda r: 127683 <= r <= 127725 or 127924 <= r <= 127963)
scandef["aug07"] = (lambda r: 127643 <= r <= 127682 or 128303 <= r <= 128316)
scandef["nov28"] = (lambda r: 121884 <= r <= 122007)
scandef["dec05"] = (lambda r: 122064 <= r <= 122178)
scandef["dec12"] = (lambda r: 122245 <= r <= 122326)
scandef["dec19"] = (lambda r: 122409 <= r <= 122527)
scandef["dec26"] = (lambda r: 122535 <= r <= 122653)
scandef["jan02"] = (lambda r: 122766 <= r <= 122881)
scandef["jan09"] = (lambda r: 122993 <= r <= 123101)
scandef_order = ["jan16", "jan30", "feb06", "feb13", "feb20", "feb27", "mar06", "mar13", "apr03", "apr08", "apr09", "apr10", "may29", "jun11", "jun12", "jul10", "jul24", "aug07", "nov28", "dec05", "dec12", "dec19", "dec26", "jan02", "jan09"]

for s1 in scandef:
  for s2 in scandef:
    if s1 != s2:
      ok = True
      for r in initialrunlist:
        if r not in mybadruns:
          if scandef[s1](r) and scandef[s2](r):
            raise Exception

def using(r):
  ok = False
  for s in scandef:
    if scandef[s](r): ok = True
  return ok

def makelines_notusing(start, end, kind=None):
  x = []
  y = []
  for r in range(min(initialrunlist), max(initialrunlist)+1):
    if r in runstart and runstart[r] > start:
      if r in runend and runend[r] != 0. and runend[r] < end:
        if kind == None or (r in runsummary and runsummary[r].kind == kind):
          if not using(r):
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

def lookat_notusing(year, week):
  p = biggles.FramedPlot()
  hack = 3
  if year % 2000 == 2: hack = 2
  start = time.mktime(time.strptime("%02d %03d" % (year % 2000, (week * 7)+hack), "%y %j"))
  end = start + 604800.
  p.add(biggles.FillBelow([0, 604800], [0, 0], color="white"))
  l = makelines_notusing(start, end)
  if l != None: p.add(biggles.FillBelow(l[0], l[1], color="gray"))
  l = makelines_notusing(start, end, 'p')
  if l != None: p.add(biggles.FillBelow(l[0], l[1], color="light blue"))
  l = makelines_notusing(start, end, 'c')
  if l != None: p.add(biggles.FillBelow(l[0], l[1], color="green"))
  l = makelines_notusing(start, end, 's')
  if l != None: p.add(biggles.FillBelow(l[0], l[1], color="red"))
  l = makelines_notusing(start, end, 'h')
  if l != None: p.add(biggles.FillBelow(l[0], l[1], color="red"))
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
p[0,0] = lookat_notusing(2001, 44+0)
p[1,0] = lookat_notusing(2001, 44+1)
p[2,0] = lookat_notusing(2001, 44+2)
p[3,0] = lookat_notusing(2001, 44+3)
p[4,0] = lookat_notusing(2001, 44+4)
p.aspect_ratio = 11./8.5
p.show()

p = biggles.Table(5,1)
p[0,0] = lookat_notusing(2001, 44+5)
p[1,0] = lookat_notusing(2001, 44+6)
p[2,0] = lookat_notusing(2001, 44+7)
p[3,0] = lookat_notusing(2002, 0)
p[4,0] = lookat_notusing(2002, 1)
p.aspect_ratio = 11./8.5
p.show()

p = biggles.Table(5,1)
p[0,0] = lookat_notusing(2002, 2)
p[1,0] = lookat_notusing(2002, 3)
p[2,0] = lookat_notusing(2002, 4)
p[3,0] = lookat_notusing(2002, 5)
p[4,0] = lookat_notusing(2002, 6)
p.aspect_ratio = 11./8.5
p.show()

p = biggles.Table(5,1)
p[0,0] = lookat_notusing(2002, 7)
p[1,0] = lookat_notusing(2002, 8)
p[2,0] = lookat_notusing(2002, 9)
p[3,0] = lookat_notusing(2002, 10)
p[4,0] = lookat_notusing(2002, 11)
p.aspect_ratio = 11./8.5
p.show()

p = biggles.Table(5,1)
p[0,0] = lookat_notusing(2002, 12)
p[1,0] = lookat_notusing(2002, 13)
p[2,0] = lookat_notusing(2002, 14)
p[3,0] = lookat_notusing(2002, 15)
p[4,0] = lookat_notusing(2002, 16)
p.aspect_ratio = 11./8.5
p.show()

p = biggles.Table(5,1)
p[0,0] = lookat_notusing(2002, 17)
p[1,0] = lookat_notusing(2002, 18)
p[2,0] = lookat_notusing(2002, 19)
p[3,0] = lookat_notusing(2002, 20)
p[4,0] = lookat_notusing(2002, 21)
p.aspect_ratio = 11./8.5
p.show()

p = biggles.Table(5,1)
p[0,0] = lookat_notusing(2002, 22)
p[1,0] = lookat_notusing(2002, 23)
p[2,0] = lookat_notusing(2002, 24)
p[3,0] = lookat_notusing(2002, 25)
p[4,0] = lookat_notusing(2002, 26)
p.aspect_ratio = 11./8.5
p.show()

p = biggles.Table(5,1)
p[0,0] = lookat_notusing(2002, 27)
p[1,0] = lookat_notusing(2002, 28)
p[2,0] = lookat_notusing(2002, 29)
p[3,0] = lookat_notusing(2002, 30)
p[4,0] = lookat_notusing(2002, 31)
p.aspect_ratio = 11./8.5
p.show()

p = biggles.Table(5,1)
p[0,0] = lookat_notusing(2002, 33)
p[1,0] = lookat_notusing(2002, 34)
p[2,0] = lookat_notusing(2002, 35)
p[3,0] = lookat_notusing(2002, 36)
p[4,0] = lookat_notusing(2002, 37)
p.aspect_ratio = 11./8.5
p.show()

p = biggles.Table(5,1)
p[0,0] = lookat_notusing(2002, 38)
p[1,0] = lookat_notusing(2002, 39)
p[2,0] = lookat_notusing(2002, 40)
p[3,0] = lookat_notusing(2002, 41)
p[4,0] = lookat_notusing(2002, 42)
p.aspect_ratio = 11./8.5
p.show()

p = biggles.Table(5,1)
p[0,0] = lookat_notusing(2002, 43)
p[1,0] = lookat_notusing(2002, 44)
p[2,0] = lookat_notusing(2002, 45)
p[3,0] = lookat_notusing(2002, 46)
p[4,0] = lookat_notusing(2002, 47)
p.aspect_ratio = 11./8.5
p.show()

for s in scandef_order:
  tmprunlist = []
  for r in initialrunlist:
    if r not in mybadruns:
      if runsummary[r].kind == 'p':
        if scandef[s](r):
          tmprunlist.append(runsummary[r].energy)
  tmprunlist.sort()
  print s, ":"
  start = 0.
  count = 0
  for e in tmprunlist:
    if e == start:
      count += 1
    else:
      print e*1000., "("+str(count+1)+")"
      start = e
      count = 0
  raw_input()



################################################################

nobeam = getsb("cos")
ebeam = getsb("bge")
pbeam = getsb("bgp")

def get_runs(runs):
  g = 0
  h = 0
  e = 0
  p = 0
  c = 0
  wsum = 0.
  wesum = 0.
  for r in runs:
    therun = getdb(r)
    wsum += float(therun.gamgam)
    wesum += float(therun.gamgam) * runsummary[r].energy
    print "    run", r, "energy =", runsummary[r].energy, "gamgams =", therun.gamgam

    if r in mycarefulscan:
      g += therun.gamgam_vstime.sum(0.,0.99)
      h += therun.hadroncool_vstime.sum(0.,0.99)
      e += therun.beamgase_vstime.sum(0.,0.99)
      p += therun.beamgasp_vstime.sum(0.,0.99)
      c += therun.cosmic_vstime.sum(0.,0.99)
    else:
      g += therun.gamgam
      h += therun.hadroncool
      e += therun.beamgase
      p += therun.beamgasp
      c += therun.cosmic

  average_energy = wesum / wsum
  print "  Average energy is", average_energy

  ebkgnd = 1. * (ebeam.hadroncool - 1.*nobeam.hadroncool*ebeam.cosmic/nobeam.cosmic) * e / ebeam.beamgase
  pbkgnd = 1. * (pbeam.hadroncool - 1.*nobeam.hadroncool*pbeam.cosmic/nobeam.cosmic) * p / pbeam.beamgasp
  cbkgnd = 1. * nobeam.hadroncool * c / nobeam.cosmic

  hadrons = h - ebkgnd/2. - pbkgnd/2. - cbkgnd
  hadrons_err = sqrt(h + c * (1.*nobeam.hadroncool/nobeam.cosmic)**2 + ebkgnd/2. + pbkgnd/2.)
  print "  Corrected number of hadrons is", hadrons, "+/-", hadrons_err
  print "  Number of gamgams is", g

  cs = hadrons / g / average_energy**2
  cs_err = cs * sqrt((1.*hadrons_err / hadrons)**2 + 1./g)
  print "  Relative cross-section is", cs, "+/-", cs_err

  return average_energy, cs, cs_err

scanen = {}
scancs = {}
scancs_err = {}
for s in scandef_order:
  print "Working on: "+s

  scanen[s] = []
  scancs[s] = []
  scancs_err[s] = []
  
  print "  Continuum point"
  runlist = []
  for r in initialrunlist:
    if scandef[s](r) and r not in mybadruns and runsummary[r].kind == 'c':
      runlist.append(r)
  if len(runlist) > 0:
    e, cs, cs_err = get_runs(runlist)
    scanen[s].append(e)
    scancs[s].append(cs)
    scancs_err[s].append(cs_err)
  else:
    print "  (there isn't one)"

  print "  High-energy tail point"
  runlist = []
  for r in initialrunlist:
    if scandef[s](r) and r not in mybadruns and runsummary[r].kind == 'h':
      runlist.append(r)
  if len(runlist) > 0:
    e, cs, cs_err = get_runs(runlist)
    scanen[s].append(e)
    scancs[s].append(cs)
    scancs_err[s].append(cs_err)
  else:
    print "  (there isn't one)"
    
  print "  See if there are any peak points..."
  runlist = {}
  for r in initialrunlist:
    if scandef[s](r) and r not in mybadruns and runsummary[r].kind == 'p':
      round_energy = int(round(runsummary[r].energy*10000))
      if round_energy not in runlist:
        runlist[round_energy] = [r]
      else:
        runlist[round_energy].append(r)
  for round_energy in runlist:
    print "  Peak points near", 1.*round_energy/10., "MeV", "(there are", len(runlist[round_energy]), "of them)"
    if len(runlist[round_energy]) == 0: raise Exception
    e, cs, cs_err = get_runs(runlist[round_energy])
    scanen[s].append(e)
    scancs[s].append(cs)
    scancs_err[s].append(cs_err)

  print "  Any scan points that might be left"
  for r in initialrunlist:
    if scandef[s](r) and r not in mybadruns and runsummary[r].kind == 's':
      e, cs, cs_err = get_runs([r])
      scanen[s].append(e)
      scancs[s].append(cs)
      scancs_err[s].append(cs_err)
      
  print "All done with this scan!"
  print ""

pickle.dump(scanen, open("/home/mccann/antithesis/scanen.p", 'w'), -1)
pickle.dump(scancs, open("/home/mccann/antithesis/scancs.p", 'w'), -1)
pickle.dump(scancs_err, open("/home/mccann/antithesis/scancs_err.p", 'w'), -1)

p = biggles.Table(5,5)
i = 0
j = 0
for s in scandef_order:
  p[i,j] = biggles.FramedPlot()
  p[i,j].add(biggles.Points(scanen[s], scancs[s], symboltype="filled circle", symbolsize=0.7))
  p[i,j].add(biggles.SymmetricErrorBarsY(scanen[s], scancs[s], scancs_err[s]))
  p[i,j].xrange = min(scanen[s]) - 0.005, max(scanen[s]) + 0.005
  p[i,j].yrange = 0, max(scancs[s]) * 1.2
  p[i,j].aspect_ratio = 8./11.5 * 0.9
  p[i,j].x1.draw_ticklabels = 0
  p[i,j].y1.draw_ticklabels = 0
  p[i,j].x2.label = s
  i += 1
  if i == 5:
    i = 0
    j += 1
p.aspect_ratio = 8./11.5
p.show()
p.write_eps("plots/all25.eps")






############################################################

def get_runs(runs):
  g = 0
  h = 0
  e = 0
  p = 0
  c = 0
  wsum = 0.
  wesum = 0.
  for r in runs:
    therun = getdb(r)
    wsum += float(therun.gamgam)
    wesum += float(therun.gamgam) * runsummary[r].energy
    print "    run", r, "energy =", runsummary[r].energy, "gamgams =", therun.gamgam

    g += therun.gamgam
    h += therun.hadroncool_g4tracks
    e += therun.beamgase
    p += therun.beamgasp
    c += therun.cosmic

  average_energy = wesum / wsum
  print "  Average energy is", average_energy

  ebkgnd = 1. * (ebeam.hadroncool_g4tracks - 1.*nobeam.hadroncool_g4tracks*ebeam.cosmic/nobeam.cosmic) * e / ebeam.beamgase
  pbkgnd = 1. * (pbeam.hadroncool_g4tracks - 1.*nobeam.hadroncool_g4tracks*pbeam.cosmic/nobeam.cosmic) * p / pbeam.beamgasp
  cbkgnd = 1. * nobeam.hadroncool_g4tracks * c / nobeam.cosmic

  hadrons = h - ebkgnd/2. - pbkgnd/2. - cbkgnd
  hadrons_err = sqrt(h + c * (1.*nobeam.hadroncool_g4tracks/nobeam.cosmic)**2 + ebkgnd/2. + pbkgnd/2.)
  print "  Corrected number of hadrons is", hadrons, "+/-", hadrons_err
  print "  Number of gamgams is", g

  cs = hadrons / g / average_energy**2
  cs_err = cs * sqrt((1.*hadrons_err / hadrons)**2 + 1./g)
  print "  Relative cross-section is", cs, "+/-", cs_err

  return average_energy, cs, cs_err

scanen = {}
scancs = {}
scancs_err = {}
for s in scandef_order:
  print "Working on: "+s

  scanen[s] = []
  scancs[s] = []
  scancs_err[s] = []
  
  print "  Continuum point"
  runlist = []
  for r in initialrunlist:
    if scandef[s](r) and r not in mybadruns and runsummary[r].kind == 'c':
      runlist.append(r)
  if len(runlist) > 0:
    e, cs, cs_err = get_runs(runlist)
    scanen[s].append(e)
    scancs[s].append(cs)
    scancs_err[s].append(cs_err)
  else:
    print "  (there isn't one)"

  print "  High-energy tail point"
  runlist = []
  for r in initialrunlist:
    if scandef[s](r) and r not in mybadruns and runsummary[r].kind == 'h':
      runlist.append(r)
  if len(runlist) > 0:
    e, cs, cs_err = get_runs(runlist)
    scanen[s].append(e)
    scancs[s].append(cs)
    scancs_err[s].append(cs_err)
  else:
    print "  (there isn't one)"
    
  print "  See if there are any peak points..."
  runlist = {}
  for r in initialrunlist:
    if scandef[s](r) and r not in mybadruns and runsummary[r].kind == 'p':
      round_energy = int(round(runsummary[r].energy*10000))
      if round_energy not in runlist:
        runlist[round_energy] = [r]
      else:
        runlist[round_energy].append(r)
  for round_energy in runlist:
    print "  Peak points near", 1.*round_energy/10., "MeV", "(there are", len(runlist[round_energy]), "of them)"
    if len(runlist[round_energy]) == 0: raise Exception
    e, cs, cs_err = get_runs(runlist[round_energy])
    scanen[s].append(e)
    scancs[s].append(cs)
    scancs_err[s].append(cs_err)

  print "  Any scan points that might be left"
  for r in initialrunlist:
    if scandef[s](r) and r not in mybadruns and runsummary[r].kind == 's':
      e, cs, cs_err = get_runs([r])
      scanen[s].append(e)
      scancs[s].append(cs)
      scancs_err[s].append(cs_err)
      
  print "All done with this scan!"
  print ""

pickle.dump(scancs, open("/home/mccann/antithesis/scancs_g4.p", 'w'), -1)
pickle.dump(scancs_err, open("/home/mccann/antithesis/scancs_g4_err.p", 'w'), -1)







###################################################

allscandef = {}
allscandef["u1s"] = (lambda r: scandef["jan16"](r) or scandef["jan30"](r) or scandef["feb06"](r) or scandef["feb13"](r) or scandef["feb20"](r) or scandef["feb27"](r) or scandef["mar06"](r) or scandef["mar13"](r) or scandef["apr03"](r) or scandef["apr08"](r) or scandef["apr09"](r) or scandef["apr10"](r))
allscandef["u2s"] = (lambda r: scandef["may29"](r) or scandef["jun11"](r) or scandef["jun12"](r) or scandef["jul10"](r) or scandef["jul24"](r) or scandef["aug07"](r))
allscandef["u3s"] = (lambda r: scandef["nov28"](r) or scandef["dec05"](r) or scandef["dec12"](r) or scandef["dec19"](r) or scandef["dec26"](r) or scandef["jan02"](r) or scandef["jan09"](r))
allscandef_order = ["u1s", "u2s", "u3s"]

allscanen = {}
allscancs = {}
allscancs_err = {}
for s in allscandef_order:
  print "Working on: "+s

  allscanen[s] = []
  allscancs[s] = []
  allscancs_err[s] = []
  
  print "  Continuum point"
  runlist = []
  for r in initialrunlist:
    if allscandef[s](r) and r not in mybadruns and runsummary[r].kind == 'c':
      runlist.append(r)
  if len(runlist) > 0:
    e, cs, cs_err = get_runs(runlist)
    allscanen[s].append(e)
    allscancs[s].append(cs)
    allscancs_err[s].append(cs_err)
  else:
    print "  (there isn't one)"

  print "  High-energy tail point"
  runlist = []
  for r in initialrunlist:
    if allscandef[s](r) and r not in mybadruns and runsummary[r].kind == 'h':
      runlist.append(r)
  if len(runlist) > 0:
    e, cs, cs_err = get_runs(runlist)
    allscanen[s].append(e)
    allscancs[s].append(cs)
    allscancs_err[s].append(cs_err)
  else:
    print "  (there isn't one)"
    
  print "  See if there are any peak/scan points..."
  runlist = {}
  for r in initialrunlist:
    if allscandef[s](r) and r not in mybadruns and (runsummary[r].kind == 'p' or runsummary[r].kind == 's'):
      round_energy = int(round(runsummary[r].energy*10000))
      if round_energy not in runlist:
        runlist[round_energy] = [r]
      else:
        runlist[round_energy].append(r)
  for round_energy in runlist:
    print "  Peak points near", 1.*round_energy/10., "MeV", "(there are", len(runlist[round_energy]), "of them)"
    if len(runlist[round_energy]) == 0: raise Exception
    e, cs, cs_err = get_runs(runlist[round_energy])
    allscanen[s].append(e)
    allscancs[s].append(cs)
    allscancs_err[s].append(cs_err)





########################

# thecosmics = {}
# thebeamgase = {}
# thebeamgasp = {}
# thegamgams = {}
# for r in initialrunlist:
#   if r not in mybadruns:
#     therun = getdb(r)
#     thecosmics[r] = therun.cosmic
#     thebeamgase[r] = therun.beamgase
#     thebeamgasp[r] = therun.beamgasp
#     thegamgams[r] = therun.gamgam
# pickle.dump(thecosmics, file("old_dotps/tmp_thecosmics.p", 'w'))
# pickle.dump(thebeamgase, file("old_dotps/tmp_thebeamgase.p", 'w'))
# pickle.dump(thebeamgasp, file("old_dotps/tmp_thebeamgasp.p", 'w'))
# pickle.dump(thegamgams, file("old_dotps/tmp_thegamgams.p", 'w'))
thecosmics = pickle.load(file("old_dotps/tmp_thecosmics.p"))
thebeamgase = pickle.load(file("old_dotps/tmp_thebeamgase.p"))
thebeamgasp = pickle.load(file("old_dotps/tmp_thebeamgasp.p"))
thegamgams = pickle.load(file("old_dotps/tmp_thegamgams.p"))

x = []
y = []
yerr = []
for r in initialrunlist:
  if r not in mybadruns and r in runstart and r in runend:
    x.append(runend[r] - runstart[r])
    y.append(thecosmics[r])
    yerr.append(1./thecosmics[r])
p = biggles.FramedPlot()
p.add(biggles.Points(x, y, symboltype="filled circle", symbolsize=0.7))
p.add(biggles.SymmetricErrorBarsY(x, y, yerr))
p.x1.label = "Seconds between StartRun and EndRun"
p.y1.label = "Number of Cosmic Rays"
p.show()
p.write_eps("/home/mccann/tmp.ps")

x = []
xerr = []
y = []
yerr = []
for r in initialrunlist:
  if r not in mybadruns:
    x.append(thegamgams[r])
    xerr.append(1./thegamgams[r])
    y.append(thebeamgase[r])
    yerr.append(1./thebeamgase[r])
p = biggles.FramedPlot()
p.add(biggles.Points(x, y, symboltype="filled circle", symbolsize=0.7))
p.add(biggles.SymmetricErrorBarsX(x, y, xerr))
p.add(biggles.SymmetricErrorBarsY(x, y, yerr))
p.x1.label = r"Number of $e^+e^-\to \gamma\gamma$"
p.y1.label = r"Number of $e^-$ beamgas events"
p.show()
p.write_eps("/home/mccann/tmp.ps")

x = []
xerr = []
y = []
yerr = []
for r in initialrunlist:
  if r not in mybadruns:
    x.append(thegamgams[r])
    xerr.append(1./thegamgams[r])
    y.append(thebeamgasp[r])
    yerr.append(1./thebeamgasp[r])
p = biggles.FramedPlot()
p.add(biggles.Points(x, y, symboltype="filled circle", symbolsize=0.7))
p.add(biggles.SymmetricErrorBarsX(x, y, xerr))
p.add(biggles.SymmetricErrorBarsY(x, y, yerr))
p.x1.label = r"Number of $e^+e^-\to \gamma\gamma$"
p.y1.label = r"Number of $e^+$ beamgas events"
p.show()
p.write_eps("/home/mccann/tmp.ps")







x = []
y = []
yerr = []
p = biggles.FramedPlot()
for r in initialrunlist:
  if r not in mybadruns and r in runstart and r in runend:
    x.append(runend[r] - runstart[r])
    y.append(thecosmics[r])
    yerr.append(1./thecosmics[r])
    if 4.*thecosmics[r] < (runend[r] - runstart[r]) - 800:
      p.add(biggles.DataLabel(runend[r] - runstart[r], thecosmics[r], str(r), texthalign="left", textvalign="top"))
p.add(biggles.Points(x, y, symboltype="filled circle", symbolsize=0.7))
p.add(biggles.SymmetricErrorBarsY(x, y, yerr))
p.x1.label = "Seconds between StartRun and EndRun"
p.y1.label = "Number of Cosmic Rays"
p.show()

