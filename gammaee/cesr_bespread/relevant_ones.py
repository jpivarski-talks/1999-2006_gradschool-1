import pickle, time
runstart = pickle.load(open("/home/mccann/antithesis/old_dotps/runstart.p"))
runend = pickle.load(open("/home/mccann/antithesis/old_dotps/runend.p"))

def interval(name, rlow, rhigh):
  return name, runstart[rlow], runend[rhigh]

intervals = []
intervals.append(interval("3S_nov28", 121884, 122007))
intervals.append(interval("3S_dec05", 122069, 122178))
intervals.append(interval("3S_dec12", 122245, 122326))
intervals.append(interval("3S_dec19", 122409, 122527))
intervals.append(interval("3S_dec26", 122535, 122757))
intervals.append(interval("3S_jan02", 122766, 122881))
intervals.append(interval("3S_jan09", 122993, 123101))
intervals.append(interval("1S_jan16", 123164, 123178))
intervals.append(interval("1S_jan30", 123596, 123718))
intervals.append(interval("1S_feb06", 123781, 123893))
intervals.append(interval("1S_feb13", 124080, 124092))
intervals.append(interval("1S_feb20", 124102, 124214))
intervals.append(interval("1S_feb27", 124279, 124394))
intervals.append(interval("1S_mar06", 124436, 124520))
intervals.append(interval("1S_mar13", 124625, 124736))
intervals.append(interval("1S_apr03", 125119, 125127))
intervals.append(interval("1S_apr08", 125254, 125262))
intervals.append(interval("1S_apr09", 125285, 125295))
intervals.append(interval("1S_apr10", 125303, 125416))
intervals.append(interval("2S_may29", 126449, 126568))
intervals.append(interval("2S_jun11", 126776, 126783))
intervals.append(interval("2S_jun12", 126814, 126915))
intervals.append(interval("2S_jul10", 127588, 127615))
intervals.append(interval("2S_jul24", 127924, 127933))
intervals.append(interval("2S_aug07", 128303, 128316))

def datelabel(date, padding=0):
  for i in intervals:
    if i[1] - padding <= date <= i[2] + padding:
      return i[0]
  return None

import re
record = {}
record2 = {}
record3 = []
for line in open("fulllist.txt").readlines():
  entrydate = time.mktime(time.strptime(line[0:19], "%Y-%m-%d %H:%M:%S"))
  label = datelabel(entrydate, 10*60)
  if label != None:
    record[int(entrydate)] = [label, line[23:-1], int(line[-6:-1])]
    record2[int(line[-6:-1])] = [label, line[23:-1], int(entrydate)]
    oldone = re.findall("old: [0-9]+", line)[0][5:]
    record3.append(int(oldone))
print len(record.keys())

dates = record.keys()
dates.sort()

# savesets = record2.keys()
# savesets.sort()
# for ss in savesets:
#   print "get csr_set."+str(ss)
record3.sort()
for ss in record3:
  print "get csr_set."+str(ss)

# print map(lambda d: record[d][2], dates)

####################################################

def getstuff(saveset):
  lines = open("csr_set."+str(saveset)).readlines()
  i = 0
  hspvolt = []
  hbndcur = []
  horzcur = []
  while i < len(lines):
    if lines[i][0:13] == " CSR HSP VOLT":
      i += 1
      hspvolt += map(int, lines[i].split())

    elif lines[i][0:13] == " CSR HBND CUR":
      i += 1
      hbndcur += map(int, lines[i].split())

    elif lines[i][0:13] == " CSR HORZ CUR":
      for dummy in range(10):
        i += 1
        horzcur += map(int, lines[i].split())

    i += 1

  return hspvolt, hbndcur, horzcur

last_hspvolt = []; last_hbndcur = []; last_horzcur = []
for d in dates:
  rec = record[d]
#   if rec[1][0:14] != "STANDARD 1S_ON" and \
#      rec[1][0:14] != "STANDARD 2S_ON" and \
#      rec[1][0:14] != "STANDARD 3S_ON":
#     continue

  hspvolt, hbndcur, horzcur = getstuff(rec[-1])
  starstring = [" ", " ", " "]
  if last_hspvolt != hspvolt:
    starstring[0] = "*"
  if last_hbndcur != hbndcur:
    starstring[1] = "*"
  if last_horzcur != horzcur:
    starstring[2] = "*"
  starstring = reduce(lambda a, b: a+b, starstring)

  print time.asctime(time.localtime(d)), starstring, rec[0], rec[1]
  
  last_hspvolt = hspvolt
  last_hbndcur = hbndcur
  last_horzcur = horzcur

  
#####################################################

def interval(name, rlow, rhigh):
  if runend[rhigh] < runstart[rlow] + 48*60*60:
    earlier = runend[rhigh]
  else:
    earlier = runstart[rlow] + 48*60*60
  return name, runstart[rlow], earlier

intervals = []
intervals.append(interval("3S_nov28", 121884, 122007))
intervals.append(interval("3S_dec05", 122069, 122178))
intervals.append(interval("3S_dec12", 122245, 122326))
intervals.append(interval("3S_dec19", 122409, 122527))
intervals.append(interval("3S_dec26", 122535, 122757))
intervals.append(interval("3S_jan02", 122766, 122881))
intervals.append(interval("3S_jan09", 122993, 123101))
intervals.append(interval("1S_jan16", 123164, 123178))
intervals.append(interval("1S_jan30", 123596, 123718))
intervals.append(interval("1S_feb06", 123781, 123893))
intervals.append(interval("1S_feb13", 124080, 124092))
intervals.append(interval("1S_feb20", 124102, 124214))
intervals.append(interval("1S_feb27", 124279, 124394))
intervals.append(interval("1S_mar06", 124436, 124520))
intervals.append(interval("1S_mar13", 124625, 124736))
intervals.append(interval("1S_apr03", 125119, 125127))
intervals.append(interval("1S_apr08", 125254, 125262))
intervals.append(interval("1S_apr09", 125285, 125295))
intervals.append(interval("1S_apr10", 125303, 125416))
intervals.append(interval("2S_may29", 126449, 126568))
intervals.append(interval("2S_jun11", 126776, 126783))
intervals.append(interval("2S_jun12", 126814, 126915))
intervals.append(interval("2S_jul10", 127588, 127615))
intervals.append(interval("2S_jul24", 127924, 127933))
intervals.append(interval("2S_aug07", 128303, 128316))

def datelabel(date, padding=0):
  for i in intervals:
    if i[1] - padding <= date <= i[2] + padding:
      return i[0]
  return None

import re
record = {}
interesting = set()
for line in open("reallyfulllist.txt").readlines():
  try:
    entrydate = time.mktime(time.strptime(line[0:19], "%Y-%m-%d %H:%M:%S"))
    label = datelabel(entrydate, 0)
    if label != None:
      oldone = int(re.findall("old: *[0-9]+", line)[0][5:10])
      newone = int(re.findall("new: *[0-9]+", line)[0][5:10])
      label2 = re.findall("\.[0-9][0-9] .*\.\.\.old", line)[0][4:-6]

      if label not in record: record[label] = []
      record[label].append((int(entrydate), oldone, newone, label2))
      interesting.add(oldone)
      interesting.add(newone)
  except:
    print line
    raise Exception

for label, rec in record.items():
  rec.sort(lambda a1, a2: cmp(a1[0], a2[0]))

interesting2 = list(interesting)
interesting2.sort()
current = 0
for ss in interesting2:
  twodigits = ss / 1000
  if twodigits != current:
    print "cd /"
    print "cd [cesr.save.csr."+str(twodigits)+"]"
    current = twodigits
  print "get csr_set."+str(ss)

# for entrydate, oldone, newone, label2 in record["1S_apr10"]:
#   print label2, oldone, "->", newone

# for entrydate, oldone, newone, label2 in record["1S_mar13"]:
#   print label2, oldone, "->", newone

# howmany = 0
# for label, rec in record.items():
#   for entrydate, oldone, newone, label2 in rec:
#     howmany += 1
# print howmany

def getstuff(saveset):
  lines = open("csr_set."+str(saveset)).readlines()
  i = 0
  hspvolt = []
  hbndcur = []
  horzcur = []
  while i < len(lines):
    if lines[i][0:13] == " CSR HSP VOLT":
      i += 1
      hspvolt += map(int, lines[i].split())

    elif lines[i][0:13] == " CSR HBND CUR":
      i += 1
      hbndcur += map(int, lines[i].split())

    elif lines[i][0:13] == " CSR HORZ CUR":
      for dummy in range(10):
        i += 1
        horzcur += map(int, lines[i].split())

    i += 1

  return hspvolt, hbndcur, horzcur

for label in ["3S_nov28", "3S_dec05", "3S_dec12", "3S_dec19", "3S_dec26", "3S_jan02", "3S_jan09", "1S_jan16", "1S_jan30", "1S_feb06", "1S_feb13", "1S_feb20", "1S_feb27", "1S_mar06", "1S_mar13", "1S_apr03", "1S_apr08", "1S_apr09", "1S_apr10", "2S_may29", "2S_jun11", "2S_jun12", "2S_jul10", "2S_jul24", "2S_aug07"]:
  if label not in record: continue
  rec = record[label]
  print label, "-------------------------------------------------------------"
  for entrydate, oldone, newone, label2 in rec:
    if re.search("HEP", label2) == None: continue
    if re.search("_OFF", label2) != None: continue

    try:
      hspvolt1, hbndcur1, horzcur1 = getstuff(oldone)
      hspvolt2, hbndcur2, horzcur2 = getstuff(newone)
      starstring = [" ", " ", " "]
      if hspvolt1 != hspvolt2:
        starstring[0] = "*"
      if hbndcur1 != hbndcur2:
        starstring[1] = "*"
      if horzcur1 != horzcur2:
        starstring[2] = "*"
      starstring = reduce(lambda a, b: a+b, starstring)
    except IOError:
      starstring = "???"

    print "  ", time.asctime(time.localtime(entrydate)), starstring, ("%-30s" % (label2,)), oldone, "->", newone

for label in ["3S_nov28", "3S_dec05", "3S_dec12", "3S_dec19", "3S_dec26", "3S_jan02", "3S_jan09", "1S_jan16", "1S_jan30", "1S_feb06", "1S_feb13", "1S_feb20", "1S_feb27", "1S_mar06", "1S_mar13", "1S_apr03", "1S_apr08", "1S_apr09", "1S_apr10", "2S_may29", "2S_jun11", "2S_jun12", "2S_jul10", "2S_jul24", "2S_aug07"]:
  if label not in record:
    print label

print "1S_jan16", time.asctime(time.localtime(runstart[123164]))
print "1S_apr03", time.asctime(time.localtime(runstart[125119]))
print "1S_apr08", time.asctime(time.localtime(runstart[125254]))
print "1S_apr09", time.asctime(time.localtime(runstart[125285]))
print "2S_jul24", time.asctime(time.localtime(runstart[127924]))

######################################################

def interval(name, rlow, rhigh):
  return name, runstart[rlow], runend[rhigh]

intervals = []
intervals.append(interval("3S_nov28", 121884, 122007))
intervals.append(interval("3S_dec05", 122069, 122178))
intervals.append(interval("3S_dec12", 122245, 122326))
intervals.append(interval("3S_dec19", 122409, 122527))
intervals.append(interval("3S_jan02", 122766, 122881))
intervals.append(interval("3S_jan09", 122993, 123101))
intervals.append(interval("1S_jan30", 123596, 123718))
intervals.append(interval("1S_feb06", 123781, 123893))
intervals.append(interval("1S_feb20", 124102, 124214))
intervals.append(interval("1S_feb27", 124279, 124394))
intervals.append(interval("1S_mar06", 124436, 124520))
intervals.append(interval("1S_mar13", 124625, 124736))
intervals.append(interval("1S_apr10", 125303, 125416))
intervals.append(interval("2S_may29", 126449, 126568))
intervals.append(interval("2S_jun12", 126814, 126915))

def datelabel(date, padding=0):
  for i in intervals:
    if i[1] - padding <= date <= i[2] + padding:
      return i[0]
  return None

import re
record = {}
for line in open("reallyfulllist.txt").readlines():
  try:
    entrydate = time.mktime(time.strptime(line[0:19], "%Y-%m-%d %H:%M:%S"))
    label = datelabel(entrydate, 0)
    if label != None:
      oldone = int(re.findall("old: *[0-9]+", line)[0][5:10])
      newone = int(re.findall("new: *[0-9]+", line)[0][5:10])
      label2 = re.findall("\.[0-9][0-9] .*\.\.\.old", line)[0][4:-6]
      if re.search("HEP", label2) != None and \
             re.search("STANDARD", label2) != None and \
             re.search("_ON", label2) != None:
        if label not in record: record[label] = []
        record[label].append((int(entrydate), oldone, newone, label2))
  except:
    print line
    raise Exception

for label, rec in record.items():
  rec.sort(lambda a1, a2: cmp(a1[0], a2[0]))

def getstuff(saveset):
  lines = open("csr_set."+str(saveset)).readlines()
  i = 0
  hspvolt = []
  hbndcur = []
  horzcur = []
  while i < len(lines):
    if lines[i][0:13] == " CSR HSP VOLT":
      i += 1
      hspvolt += map(int, lines[i].split())

    elif lines[i][0:13] == " CSR HBND CUR":
      i += 1
      hbndcur += map(int, lines[i].split())

    elif lines[i][0:13] == " CSR HORZ CUR":
      for dummy in range(10):
        i += 1
        horzcur += map(int, lines[i].split())
    elif lines[i][0:12] == " CSR LATTICE":
      i += 1
#      print lines[i]
#      lattices.add(lines[i])

    i += 1

  return hspvolt, hbndcur, horzcur

# lattices = set()
for label in ["3S_nov28", "3S_dec05", "3S_dec12", "3S_dec19", "3S_jan02", "3S_jan09", "1S_jan30", "1S_feb06", "1S_feb20", "1S_feb27", "1S_mar06", "1S_mar13", "1S_apr10", "2S_may29", "2S_jun12"]:
  if label not in record: raise Exception, label
  rec = record[label]
  print label, "--------------------------------------------------------------------"
  for entrydate, oldone, newone, label2 in rec:
    try:
      hspvolt1, hbndcur1, horzcur1 = getstuff(oldone)
      hspvolt2, hbndcur2, horzcur2 = getstuff(newone)
      starstring = [" ", " ", " "]
      if hspvolt1 != hspvolt2:
        starstring[0] = "*"
      if hbndcur1 != hbndcur2:
        starstring[1] = "*"
      if horzcur1 != horzcur2:
        starstring[2] = "*"
      starstring = reduce(lambda a, b: a+b, starstring)
    except IOError:
      starstring = "???"

    print "  ", time.asctime(time.localtime(entrydate)), starstring, ("%-30s" % (label2,)), oldone, "->", newone

import Numeric
for label in ["3S_nov28", "3S_dec05", "3S_dec12", "3S_dec19", "3S_jan02", "3S_jan09", "1S_jan30", "1S_feb06", "1S_feb20", "1S_feb27", "1S_mar06", "1S_mar13", "1S_apr10", "2S_may29", "2S_jun12"]:
  if label not in record: raise Exception, label
  rec = record[label]
  print label, "--------------------------------------------------------------------"
  for entrydate, oldone, newone, label2 in rec:
    hspvolt1, hbndcur1, horzcur1 = getstuff(oldone)
    hspvolt2, hbndcur2, horzcur2 = getstuff(newone)
    hspdiff = Numeric.array(hspvolt1) - Numeric.array(hspvolt2)
    horzdiff = Numeric.array(hbndcur1 + horzcur1) - Numeric.array(hbndcur2 + horzcur2)
    starstring = "%5d %5d, %5d %5d" % (min(hspdiff), max(hspdiff), min(horzdiff), max(horzdiff))

    print "  ", time.asctime(time.localtime(entrydate)), starstring, ("%-30s" % (label2,)), oldone, "->", newone

for label, oldone, newone in [("3S_nov28", 77166, 77166), ("3S_dec05", 77166, 77322), ("3S_dec12", 77322, 77454), ("3S_dec19", 77454, 77677), ("3S_jan02", 77677, 77958), ("3S_jan09", 77958, 78156), ("1S_jan30", 78779, 78779), ("1S_feb06", 78779, 78909), ("1S_feb20", 78909, 79231), ("1S_feb27", 79383, 79383), ("1S_mar06", 79383, 79561), ("1S_mar13", 79561, 79745), ("1S_apr10", 79745, 80329), ("2S_may29", 82614, 82614), ("2S_jun12", 82614, 82874)]:
    hspvolt1, hbndcur1, horzcur1 = getstuff(oldone)
    hspvolt2, hbndcur2, horzcur2 = getstuff(newone)
    hspdiff = Numeric.array(hspvolt1) - Numeric.array(hspvolt2)
    horzdiff = Numeric.array(hbndcur1 + horzcur1) - Numeric.array(hbndcur2 + horzcur2)
    starstring = "%5d %5d, %5d %5d" % (min(hspdiff), max(hspdiff), min(horzdiff), max(horzdiff))

    print label, starstring

##############################################################

import Numeric

hspvolt1, hbndcur1, horzcur1 = getstuff(79383)
hspvolt2, hbndcur2, horzcur2 = getstuff(79388)
hspvolt3, hbndcur3, horzcur3 = getstuff(79391)
hspvolt4, hbndcur4, horzcur4 = getstuff(79406)
hspvolt5, hbndcur5, horzcur5 = getstuff(79411)

print Numeric.array(hspvolt1) - Numeric.array(hspvolt2)
print Numeric.array(hspvolt1) - Numeric.array(hspvolt3)
print Numeric.array(hspvolt1) - Numeric.array(hspvolt4)
print Numeric.array(hspvolt1) - Numeric.array(hspvolt5)

hspvolt1, hbndcur1, horzcur1 = getstuff(79561)
hspvolt2, hbndcur2, horzcur2 = getstuff(79567)
hspvolt3, hbndcur3, horzcur3 = getstuff(79569)
hspvolt4, hbndcur4, horzcur4 = getstuff(79577)
hspvolt5, hbndcur5, horzcur5 = getstuff(79580)
hspvolt6, hbndcur6, horzcur6 = getstuff(79581)

print Numeric.array(hspvolt1) - Numeric.array(hspvolt2)
print Numeric.array(hspvolt1) - Numeric.array(hspvolt3)
print Numeric.array(hspvolt1) - Numeric.array(hspvolt4)
print Numeric.array(hspvolt1) - Numeric.array(hspvolt5)
print Numeric.array(hspvolt1) - Numeric.array(hspvolt6)

hspvolt1, hbndcur1, horzcur1 = getstuff(79745)
hspvolt2, hbndcur2, horzcur2 = getstuff(79746)
hspvolt3, hbndcur3, horzcur3 = getstuff(79751)

print Numeric.array(hspvolt1) - Numeric.array(hspvolt2)
print Numeric.array(hspvolt1) - Numeric.array(hspvolt3)

hspvolt1, hbndcur1, horzcur1 = getstuff(80329)
hspvolt2, hbndcur2, horzcur2 = getstuff(80500)
hspvolt3, hbndcur3, horzcur3 = getstuff(80507)
hspvolt4, hbndcur4, horzcur4 = getstuff(80508)
hspvolt5, hbndcur5, horzcur5 = getstuff(80510)
hspvolt6, hbndcur6, horzcur6 = getstuff(80530)
hspvolt7, hbndcur7, horzcur7 = getstuff(80533)
hspvolt8, hbndcur8, horzcur8 = getstuff(80542)

print Numeric.array(hspvolt1) - Numeric.array(hspvolt2)
print Numeric.array(hspvolt1) - Numeric.array(hspvolt3)
print Numeric.array(hspvolt1) - Numeric.array(hspvolt4)
print Numeric.array(hspvolt1) - Numeric.array(hspvolt5)
print Numeric.array(hspvolt1) - Numeric.array(hspvolt6)
print Numeric.array(hspvolt1) - Numeric.array(hspvolt7)
print Numeric.array(hspvolt1) - Numeric.array(hspvolt8)

hspvolt1, hbndcur1, horzcur1 = getstuff(79383)
hspvolt2, hbndcur2, horzcur2 = getstuff(79561)
hspvolt3, hbndcur3, horzcur3 = getstuff(79745)
hspvolt4, hbndcur4, horzcur4 = getstuff(80533)

print Numeric.array(hspvolt1) - Numeric.array(hspvolt2)
print Numeric.array(hspvolt1) - Numeric.array(hspvolt3)
print Numeric.array(hspvolt1) - Numeric.array(hspvolt4)

print Numeric.array(hspvolt3) - Numeric.array(hspvolt4)

##################################################################

execfile("/home/mccann/antithesis/utilities.py")
nobeam = getsb("cos")
ebeam = getsb("bge")
pbeam = getsb("bgp")
import gbwkf, gbwkftau, gbwkfee
runstart = pickle.load(open("/home/mccann/antithesis/old_dotps/runstart.p"))
runend = pickle.load(open("/home/mccann/antithesis/old_dotps/runend.p"))
import time

nbish2nb = 23.0481

def setup_data(runs, lumisource=0):
  tmpdata = []
  for r in runs:
    tmpdata.append(get_runs([r], lumisource=lumisource))
  return tmpdata

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

def u1func(area, rmsbeam, back, fullgam, yint, phi, btautau, tauyint, tauphi, twophofrac, w, lumisource=0):
  tmp = 0.
  upsilon = area * 0.9757 * mygbwkf(9460.30, fullgam, rmsbeam, yint, phi, w)
  tmp += upsilon
  tmp += area * 0.578 * btautau * mygbwkftau(9460.30, fullgam, rmsbeam, tauyint, tauphi, w)
  tmp += back * (1.-twophofrac) * 9000.**2 / w**2
  tmp += back * twophofrac * log(w**2/9000.**2)

  # see 21 Sep 2005 in notes (green #13)
  if lumisource == 1:
    tmp /= (1. + upsilon/0.9253*0.0249*0.252*0.23684/1.038558)
  elif lumisource == 2:
    tmp /= (1. + upsilon/0.9253*0.0249*0.112*0.118999/1.038558)
  return tmp

def get_runs(runs, lumisource=0):
  g = 0
  h = 0
  e = 0
  p = 0
  c = 0
  wsum = 0.
  wesum = 0.
  for r in runs:
    therun = getdb(r)
    ngg = therun.gamgam
    if r in mycarefulscan: ngg = therun.gamgam_vstime.sum(0.,0.99)
    wsum += float(ngg)
    wesum += float(ngg) * runsummary[r].energy

    h += therun.hadroncool
    e += therun.beamgase
    p += therun.beamgasp
    c += therun.cosmic

    if lumisource == 0:
      g += therun.gamgam
    elif lumisource == 1:
      g += therun.bhabha_cosp.sum(0., 0.6)
    elif lumisource == 2:
      g += therun.bhabha_cosp.sum(0.6, 0.8)

  average_energy = wesum / wsum

  ebkgnd = 1. * (ebeam.hadroncool - 1.*nobeam.hadroncool*ebeam.cosmic/nobeam.cosmic) * e / ebeam.beamgase
  pbkgnd = 1. * (pbeam.hadroncool - 1.*nobeam.hadroncool*pbeam.cosmic/nobeam.cosmic) * p / pbeam.beamgasp
  cbkgnd = 1. * nobeam.hadroncool * c / nobeam.cosmic

  hadrons = h - ebkgnd/2. - pbkgnd/2. - cbkgnd
  hadrons_err = sqrt(h + c * (1.*nobeam.hadroncool/nobeam.cosmic)**2 + ebkgnd/2. + pbkgnd/2.)

  cs = hadrons / g / average_energy**2 * nbish2nb
  cs_err = cs * sqrt((1.*hadrons_err / hadrons)**2 + 1./g)

  if lumisource == 1:
    cs /= 0.23684
    cs_err /= 0.23684

  if lumisource == 2:
    cs /= 0.118999
    cs_err /= 0.118999

  return average_energy, cs, cs_err

u1runs = {}
u1runs["feb27"] = []
u1runs["mar06"] = []
u1runs["mar13"] = []
u1runs["apr10"] = []
for r in initialrunlist:
  if runsummary[r].res == 1 and runsummary[r].kind == "p" and r not in mybadruns and r in runstart and r in runend:
    if runstart[r] > time.mktime(time.strptime("Mar 1 10:35:54 2002", "%b %d %H:%M:%S %Y")) and \
       runend[r] < time.mktime(time.strptime("Mar 3 14:45:44 2002", "%b %d %H:%M:%S %Y")):
      u1runs["feb27"].append(r)
    if runstart[r] > time.mktime(time.strptime("Mar 8 08:59:40 2002", "%b %d %H:%M:%S %Y")) and \
       runend[r] < time.mktime(time.strptime("Mar 9 11:36:08 2002", "%b %d %H:%M:%S %Y")):
      u1runs["mar06"].append(r)
    if runstart[r] > time.mktime(time.strptime("Mar 15 10:04:49 2002", "%b %d %H:%M:%S %Y")) and \
       runend[r] < time.mktime(time.strptime("Mar 17 09:32:29 2002", "%b %d %H:%M:%S %Y")):
      u1runs["mar13"].append(r)
    if (runstart[r] > time.mktime(time.strptime("Apr 11 09:11:09 2002", "%b %d %H:%M:%S %Y")) and \
        runend[r] < time.mktime(time.strptime("Apr 12 12:56:29 2002", "%b %d %H:%M:%S %Y"))) or \
        (runstart[r] > time.mktime(time.strptime("Apr 12 15:20:08 2002", "%b %d %H:%M:%S %Y")) and \
         runend[r] < time.mktime(time.strptime("Apr 14 14:56:21 2002", "%b %d %H:%M:%S %Y"))):
      u1runs["apr10"].append(r)

# for r in initialrunlist:
#   if runsummary[r].res == 1 and runsummary[r].kind == "p" and r not in mybadruns and (r not in runstart or r not in runend):
#     if 124328 < r < 124376 or 124481 < r < 124507 or 124672 < r < 124718 or 125316 < r < 125400:
#       print r
u1runs["feb27"].append(124330)
u1runs["feb27"].append(124334)
u1runs["apr10"].append(125342)
u1runs["apr10"].append(125377)

u1shifts = {}
u1shifts["feb27"] = 0.1787539, 0.0875286
u1shifts["mar06"] = 0.18694, 0.12965
u1shifts["mar13"] = 0.559595, 0.0978411
u1shifts["apr10"] = 0.6142458, 0.0557527

ggdata = {}
bbindata = {}
bboutdata = {}
for s in u1runs:
  ggdata[s] = get_runs(u1runs[s], lumisource=0)
  bbindata[s] = get_runs(u1runs[s], lumisource=1)
  bboutdata[s] = get_runs(u1runs[s], lumisource=2)

import biggles
p = biggles.FramedPlot()

x = []; y = []; dy = []; dx = []
for s in u1runs:
  x.append(ggdata[s][0]*2000. + u1shifts[s][0])
  y.append(ggdata[s][1])
  dy.append(ggdata[s][2])
  dx.append(u1shifts[s][1])
p.add(biggles.Points(x, y, symboltype="filled circle", symbolsize=1))
p.add(biggles.SymmetricErrorBarsY(x, y, dy))
p.add(biggles.SymmetricErrorBarsX(x, y, dx))
# p.show()

x = []; y = []; dy = []; dx = []; lab = []
for s in u1runs:
  x.append(bbindata[s][0]*2000. + u1shifts[s][0])
  y.append(bbindata[s][1])
  dy.append(bbindata[s][2])
  dx.append(u1shifts[s][1])
  lab.append(s)
p.add(biggles.Points(x, y, symboltype="filled circle", symbolsize=1, color="blue"))
p.add(biggles.SymmetricErrorBarsY(x, y, dy, color="blue"))
p.add(biggles.SymmetricErrorBarsX(x, y, dx, color="blue"))
# p.show()
p.add(biggles.DataLabel(x[0], y[0]-0.15, lab[0]))
p.add(biggles.DataLabel(x[1], y[1]-0.2, lab[1]))
p.add(biggles.DataLabel(x[2], y[2]-0.2, lab[2]))
p.add(biggles.DataLabel(x[3], y[3]-0.2, lab[3]))

x = []; y = []; dy = []; dx = []
for s in u1runs:
  x.append(bboutdata[s][0]*2000. + u1shifts[s][0])
  y.append(bboutdata[s][1])
  dy.append(bboutdata[s][2])
  dx.append(u1shifts[s][1])
p.add(biggles.Points(x, y, symboltype="filled circle", symbolsize=1, color="red"))
p.add(biggles.SymmetricErrorBarsY(x, y, dy, color="red"))
p.add(biggles.SymmetricErrorBarsX(x, y, dx, color="red"))
# p.show()

x = Numeric.arange(9460-5, 9460+5, 0.025)
y = map(lambda xi: u1func(318.5185, 3.78739, 0.40577*nbish2nb, 0.053, 0.01864, 0., 0.0267, 0.2, 0., 0.0792, xi, lumisource=0), x)
p.add(biggles.Curve(x, y, color="black"))
# p.show()

x = Numeric.arange(9460-5, 9460+5, 0.025)
y = map(lambda xi: u1func(318.5185, 3.78739, 0.40577*nbish2nb, 0.053, 0.01864, 0., 0.0267, 0.2, 0., 0.0792, xi, lumisource=1), x)
p.add(biggles.Curve(x, y, color="blue"))
# p.show()

x = Numeric.arange(9460-5, 9460+5, 0.025)
y = map(lambda xi: u1func(318.5185, 3.78739, 0.40577*nbish2nb, 0.053, 0.01864, 0., 0.0267, 0.2, 0., 0.0792, xi, lumisource=2), x)
p.add(biggles.Curve(x, y, color="red"))
# p.show()

p.x1.range = 9460.2, 9461.5
p.y1.range = 25, 26.5
p.show()

p.write_eps("relevantones_stability2like.eps")

x = []; y = []; dy = []; dx = []; lab = []
for s in u1runs:
  x.append(bboutdata[s][0]*2000. + u1shifts[s][0])
  y.append(bboutdata[s][1])
  dy.append(bboutdata[s][2])
  dx.append(u1shifts[s][1])
  lab.append(s)

###########################################################

def getstuff(saveset):
  lines = open("csr_set."+str(saveset)).readlines()
  i = 0
  hspvolt = []
  hbndcur = []
  horzcur = []
  while i < len(lines):
    if lines[i][0:13] == " CSR HSP VOLT":
      i += 1
      hspvolt += map(int, lines[i].split())

    elif lines[i][0:13] == " CSR HBND CUR":
      i += 1
      hbndcur += map(int, lines[i].split())

    elif lines[i][0:13] == " CSR HORZ CUR":
      for dummy in range(10):
        i += 1
        horzcur += map(int, lines[i].split())
    elif lines[i][0:12] == " CSR LATTICE":
      i += 1
      print lines[i]
#      lattices.add(lines[i])

    i += 1

  return hspvolt, hbndcur, horzcur

getstuff(77775)
getstuff(77777)
getstuff(77778)
getstuff(77779)
getstuff(77782)
getstuff(77783)
getstuff(77786)
getstuff(77787)
getstuff(77788)
getstuff(77791)
getstuff(77798)

#################################################################

# study a scan

# 2001-12-27 22:50:54.98 STANDARD 3S_ON HEP 77866
# 2001-12-25 20:31:26.40 ENCAL 3S_-07 HEP 77787
# 2001-12-25 18:12:21.27 ENCAL 3S_-05 HEP 77782
# 2001-12-25 16:12:32.99 ENCAL 3S_-02 HEP 77776
# 2001-12-25 19:28:58.39 ENCAL 3S_+03 HEP 77785
# 2001-12-25 21:35:20.06 ENCAL 3S_+06 HEP 77790
# 2001-12-25 22:35:16.27 ENCAL 3S_+09 HEP 77793
# 2001-12-25 17:11:20.18 ENCAL 3S_+11 HEP 77778
# 2001-12-26 09:07:58.95 ENCAL 3S_+20 HEP 77801

# ascii
# cd [cesr.save.csr.77]
# get csr_set.77866
# get csr_set.77787
# get csr_set.77782
# get csr_set.77776
# get csr_set.77785
# get csr_set.77790
# get csr_set.77793
# get csr_set.77778
# get csr_set.77801

def getstuff(saveset):
  lines = open("csr_set."+str(saveset)).readlines()
  i = 0
  hspvolt = []
  hbndcur = []
  horzcur = []
  while i < len(lines):
    if lines[i][0:13] == " CSR HSP VOLT":
      i += 1
      hspvolt += map(int, lines[i].split())

    elif lines[i][0:13] == " CSR HBND CUR":
      i += 1
      hbndcur += map(int, lines[i].split())

    elif lines[i][0:13] == " CSR HORZ CUR":
      for dummy in range(10):
        i += 1
        horzcur += map(int, lines[i].split())
    elif lines[i][0:12] == " CSR LATTICE":
      i += 1
#      print lines[i]
#      lattices.add(lines[i])

    i += 1

  return hspvolt, hbndcur, horzcur

hspvolt0, hbndcur0, horzcur0 = getstuff(77866)
hspvolt1, hbndcur1, horzcur1 = getstuff(77787)
hspvolt2, hbndcur2, horzcur2 = getstuff(77782)
hspvolt3, hbndcur3, horzcur3 = getstuff(77776)
hspvolt4, hbndcur4, horzcur4 = getstuff(77785)
hspvolt5, hbndcur5, horzcur5 = getstuff(77790)
hspvolt6, hbndcur6, horzcur6 = getstuff(77793)
hspvolt7, hbndcur7, horzcur7 = getstuff(77778)
hspvolt8, hbndcur8, horzcur8 = getstuff(77801)

print Numeric.array(hspvolt0) - Numeric.array(hspvolt1)
print Numeric.array(hspvolt0) - Numeric.array(hspvolt2)
print Numeric.array(hspvolt0) - Numeric.array(hspvolt3)
print Numeric.array(hspvolt0) - Numeric.array(hspvolt4)
print Numeric.array(hspvolt0) - Numeric.array(hspvolt5)
print Numeric.array(hspvolt0) - Numeric.array(hspvolt6)
print Numeric.array(hspvolt0) - Numeric.array(hspvolt7)
print Numeric.array(hspvolt0) - Numeric.array(hspvolt8)

print Numeric.array(hspvolt1) - Numeric.array(hspvolt2)
print Numeric.array(hspvolt1) - Numeric.array(hspvolt3)
print Numeric.array(hspvolt1) - Numeric.array(hspvolt4)
print Numeric.array(hspvolt1) - Numeric.array(hspvolt5)
print Numeric.array(hspvolt1) - Numeric.array(hspvolt6)
print Numeric.array(hspvolt1) - Numeric.array(hspvolt7)
print Numeric.array(hspvolt1) - Numeric.array(hspvolt8)

print Numeric.array(hbndcur0 + horzcur0) - Numeric.array(hbndcur1 + horzcur1)
print Numeric.array(hbndcur0 + horzcur0) - Numeric.array(hbndcur2 + horzcur2)
print Numeric.array(hbndcur0 + horzcur0) - Numeric.array(hbndcur3 + horzcur3)
print Numeric.array(hbndcur0 + horzcur0) - Numeric.array(hbndcur4 + horzcur4)
print Numeric.array(hbndcur0 + horzcur0) - Numeric.array(hbndcur5 + horzcur5)
print Numeric.array(hbndcur0 + horzcur0) - Numeric.array(hbndcur6 + horzcur6)
print Numeric.array(hbndcur0 + horzcur0) - Numeric.array(hbndcur7 + horzcur7)
print Numeric.array(hbndcur0 + horzcur0) - Numeric.array(hbndcur8 + horzcur8)

hspvolt0, hbndcur0, horzcur0 = getstuff(80329)
hspvolt1, hbndcur1, horzcur1 = getstuff(79709)
hspvolt2, hbndcur2, horzcur2 = getstuff(79715)

print Numeric.array(hspvolt0) - Numeric.array(hspvolt1)
print Numeric.array(hspvolt0) - Numeric.array(hspvolt2)

print Numeric.array(hbndcur0 + horzcur0) - Numeric.array(hbndcur1 + horzcur1)
print Numeric.array(hbndcur0 + horzcur0) - Numeric.array(hbndcur2 + horzcur2)

hspvolt0, hbndcur0, horzcur0 = getstuff(80329)
hspvolt1, hbndcur1, horzcur1 = getstuff(79717)
hspvolt2, hbndcur2, horzcur2 = getstuff(79707)

print Numeric.array(hspvolt0) - Numeric.array(hspvolt1)
print Numeric.array(hspvolt0) - Numeric.array(hspvolt2)

print Numeric.array(hbndcur0 + horzcur0) - Numeric.array(hbndcur1 + horzcur1)
print Numeric.array(hbndcur0 + horzcur0) - Numeric.array(hbndcur2 + horzcur2)


