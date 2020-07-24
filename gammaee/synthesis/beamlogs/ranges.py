import cPickle as pickle, os, re, time

class RunSummary : pass
initialrunlist = pickle.load(open("/home/mccann/synthesis/lumieff/initialrunlist.p"))
runsummary = pickle.load(open("/home/mccann/synthesis/lumieff/runsummary.p"))
mybadruns = [122617, 124363, 124364, 124365, 124368, 124369, 124372, 124373, 124459, 122353, 126341, 129522, 123013, 123014, 121928, 121929, 121953, 127951, 127955, 130278, 121710, 121930, 121944, 121954, 123884, 122331, 122335, 122336, 122339, 122341, 122342, 122344, 122345, 122349, 122350, 122352, 121476, 121748, 121822, 121847, 122685, 123436, 123847, 123873, 124816, 124860, 124862, 125367, 126273, 126329, 127280, 124452, 124454, 124456, 124458, 124462, 124464, 124465, 124466, 124467, 124469, 124472, 124473, 124474, 124475, 124477, 124478, 124479, 124480, 123281, 123411, 121595, 122093, 122330, 126510]
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

# The 48-hour limit is built into setup_runs
def setup_runs(res, low, high):
  beginning = run_date(low)

  tmpruns = []
  for r in initialrunlist:
    if r not in mybadruns and low <= r <= high and runsummary[r].res == res:
      if runsummary[r].kind == 's' or runsummary[r].kind == 'p':
        if run_date(r) < beginning + 48.*60.*60:
          tmpruns.append(r)
  return tmpruns

u1runs = {}
u2runs = {}
u3runs = {}

u1runs["jan16"] = setup_runs(1, 123164, 123178)
u1runs["jan30"] = setup_runs(1, 123596, 123718)
u1runs["feb06"] = setup_runs(1, 123781, 123893)
u1runs["feb13"] = setup_runs(1, 124080, 124092)
u1runs["feb20"] = setup_runs(1, 124102, 124214)
u1runs["feb27"] = setup_runs(1, 124279, 124394)
u1runs["mar06"] = setup_runs(1, 124436, 124519)
u1runs["mar13"] = setup_runs(1, 124625, 124736)
u1runs["apr03"] = setup_runs(1, 125119, 125127)
u1runs["apr08"] = setup_runs(1, 125254, 125262)
u1runs["apr09"] = setup_runs(1, 125285, 125295)
u1runs["apr10"] = setup_runs(1, 125303, 125416)

u2runs["may29"] = setup_runs(2, 126449, 126568)
u2runs["jun11"] = setup_runs(2, 126776, 126783)
u2runs["jun12"] = setup_runs(2, 126814, 126915)
u2runs["jul10"] = setup_runs(2, 127588, 127615)
u2runs["jul24"] = setup_runs(2, 127924, 127933)
u2runs["aug07"] = setup_runs(2, 128303, 128316)

u3runs["nov28"] = setup_runs(3, 121884, 122007)
u3runs["dec05"] = setup_runs(3, 122069, 122178)
u3runs["dec12"] = setup_runs(3, 122245, 122326)
u3runs["dec19"] = setup_runs(3, 122409, 122527)
u3runs["dec26"] = setup_runs(3, 122535, 122757)
u3runs["jan02"] = setup_runs(3, 122766, 122881)
u3runs["jan09"] = setup_runs(3, 122993, 123101)

# runstat = {}
# for which in ("u1runs", "u2runs", "u3runs"):
#   theruns = eval(which)
#   for s in theruns:
#     for r in theruns[s]:
#       runstat[r] = []
#       for l in os.popen("/nfs/cleo3/Common/rel/current/bin/i686-pc-linux-gnu/DBRunStatisticsRetrieve "+str(r)+" 4 | grep 'energy:'"):
#         en = float(re.search("([0-9\.]+)", l).group())
#         runstat[r].append(en)
#       for l in os.popen("/nfs/cleo3/Common/rel/current/bin/i686-pc-linux-gnu/DBRunStatisticsRetrieve "+str(r)+" 64 | grep 'energy:'"):
#         en = float(re.search("([0-9\.]+)", l).group())
#         runstat[r].append(en)
# pickle.dump(runstat, open("runstat.p", "w"))
runstat = pickle.load(open("runstat.p"))

runtimes = {}
runstart[127604] = time.mktime(time.strptime("7/11/2002 08:38:23", "%m/%d/%Y %H:%M:%S"))
for which in ("u1runs", "u2runs", "u3runs"):
  theruns = eval(which)
  for s in theruns:
    for r in theruns[s]:
      rst = runstart[r]
      if r not in runend:
        ren = runstart[r+1]-5
      else:
        ren = runend[r]
      runtimes[r] = rst, ren

# thelogs = ["/cdat/dafe/mccann/synthesis/beamlogs_logs/energy_Apr0202_1734.log", \
#            "/cdat/dafe/mccann/synthesis/beamlogs_logs/energy_Apr0302_1844.log", \
#            "/cdat/dafe/mccann/synthesis/beamlogs_logs/energy_Apr0802_1051.log", \
#            "/cdat/dafe/mccann/synthesis/beamlogs_logs/energy_Apr0902_1615.log", \
#            "/cdat/dafe/mccann/synthesis/beamlogs_logs/energy_Apr1002_1143.log", \
#            "/cdat/dafe/mccann/synthesis/beamlogs_logs/energy_Apr2401_0517.log", \
#            "/cdat/dafe/mccann/synthesis/beamlogs_logs/energy_Apr2401_0518.log", \
#            "/cdat/dafe/mccann/synthesis/beamlogs_logs/energy_Apr2401_0519.log", \
#            "/cdat/dafe/mccann/synthesis/beamlogs_logs/energy_Apr2402_1121.log", \
#            "/cdat/dafe/mccann/synthesis/beamlogs_logs/energy_Apr3002_1316.log", \
#            "/cdat/dafe/mccann/synthesis/beamlogs_logs/energy_Dec0202_0654.log", \
#            "/cdat/dafe/mccann/synthesis/beamlogs_logs/energy_Dec0302_1654.log", \
#            "/cdat/dafe/mccann/synthesis/beamlogs_logs/energy_Dec0401_1205.log", \
#            "/cdat/dafe/mccann/synthesis/beamlogs_logs/energy_Dec0501_1717.log", \
#            "/cdat/dafe/mccann/synthesis/beamlogs_logs/energy_Dec0501_2023.log", \
#            "/cdat/dafe/mccann/synthesis/beamlogs_logs/energy_Dec1002_1758.log", \
#            "/cdat/dafe/mccann/synthesis/beamlogs_logs/energy_Dec1701_2047.log", \
#            "/cdat/dafe/mccann/synthesis/beamlogs_logs/energy_Dec1801_1640.log", \
#            "/cdat/dafe/mccann/synthesis/beamlogs_logs/energy_Dec1801_1941.log", \
#            "/cdat/dafe/mccann/synthesis/beamlogs_logs/energy_Dec1802_1552.log", \
#            "/cdat/dafe/mccann/synthesis/beamlogs_logs/energy_Dec2602_1046.log", \
#            "/cdat/dafe/mccann/synthesis/beamlogs_logs/energy_Dec3101_0731.log", \
#            "/cdat/dafe/mccann/synthesis/beamlogs_logs/energy_Dec3101_0752.log", \
#            "/cdat/dafe/mccann/synthesis/beamlogs_logs/energy_Feb0402_1722.log", \
#            "/cdat/dafe/mccann/synthesis/beamlogs_logs/energy_Feb0602_2053.log", \
#            "/cdat/dafe/mccann/synthesis/beamlogs_logs/energy_Feb0602_2054.log", \
#            "/cdat/dafe/mccann/synthesis/beamlogs_logs/energy_Feb0701_0149.log", \
#            "/cdat/dafe/mccann/synthesis/beamlogs_logs/energy_Feb0701_0404.log", \
#            "/cdat/dafe/mccann/synthesis/beamlogs_logs/energy_Feb0902_1715.log", \
#            "/cdat/dafe/mccann/synthesis/beamlogs_logs/energy_Feb1202_0702.log", \
#            "/cdat/dafe/mccann/synthesis/beamlogs_logs/energy_Feb1202_1958.log", \
#            "/cdat/dafe/mccann/synthesis/beamlogs_logs/energy_Feb1202_2000.log", \
#            "/cdat/dafe/mccann/synthesis/beamlogs_logs/energy_Feb1902_1948.log", \
#            "/cdat/dafe/mccann/synthesis/beamlogs_logs/energy_Feb2101_0115.log", \
#            "/cdat/dafe/mccann/synthesis/beamlogs_logs/energy_Feb2702_0246.log", \
#            "/cdat/dafe/mccann/synthesis/beamlogs_logs/energy_Feb2702_0336.log", \
#            "/cdat/dafe/mccann/synthesis/beamlogs_logs/energy_Feb2702_0729.log", \
#            "/cdat/dafe/mccann/synthesis/beamlogs_logs/energy_Jan0401_1421.log", \
#            "/cdat/dafe/mccann/synthesis/beamlogs_logs/energy_Jan0802_0000.log", \
#            "/cdat/dafe/mccann/synthesis/beamlogs_logs/energy_Jan0902_1700.log", \
#            "/cdat/dafe/mccann/synthesis/beamlogs_logs/energy_Jan0902_1701.log", \
#            "/cdat/dafe/mccann/synthesis/beamlogs_logs/energy_Jan1101_0426.log", \
#            "/cdat/dafe/mccann/synthesis/beamlogs_logs/energy_Jan1502_1917.log", \
#            "/cdat/dafe/mccann/synthesis/beamlogs_logs/energy_Jan2302_2144.log", \
#            "/cdat/dafe/mccann/synthesis/beamlogs_logs/energy_Jan2302_2215.log", \
#            "/cdat/dafe/mccann/synthesis/beamlogs_logs/energy_Jan2702_2123.log", \
#            "/cdat/dafe/mccann/synthesis/beamlogs_logs/energy_Jan2702_2211.log", \
#            "/cdat/dafe/mccann/synthesis/beamlogs_logs/energy_Jan2802_1701.log", \
#            "/cdat/dafe/mccann/synthesis/beamlogs_logs/energy_Jan2902_1625.log", \
#            "/cdat/dafe/mccann/synthesis/beamlogs_logs/energy_Jan2902_1901.log", \
#            "/cdat/dafe/mccann/synthesis/beamlogs_logs/energy_Jul0302_0257.log", \
#            "/cdat/dafe/mccann/synthesis/beamlogs_logs/energy_Jul0302_0259.log", \
#            "/cdat/dafe/mccann/synthesis/beamlogs_logs/energy_Jul0402_0320.log", \
#            "/cdat/dafe/mccann/synthesis/beamlogs_logs/energy_Jul0902_1630.log", \
#            "/cdat/dafe/mccann/synthesis/beamlogs_logs/energy_Jul0902_1656.log", \
#            "/cdat/dafe/mccann/synthesis/beamlogs_logs/energy_Jul0902_1657.log", \
#            "/cdat/dafe/mccann/synthesis/beamlogs_logs/energy_Jul0902_1658.log", \
#            "/cdat/dafe/mccann/synthesis/beamlogs_logs/energy_Jul1002_2121.log", \
#            "/cdat/dafe/mccann/synthesis/beamlogs_logs/energy_Jul1102_0139.log", \
#            "/cdat/dafe/mccann/synthesis/beamlogs_logs/energy_Jul1102_0146.log", \
#            "/cdat/dafe/mccann/synthesis/beamlogs_logs/energy_Jul1102_0149.log", \
#            "/cdat/dafe/mccann/synthesis/beamlogs_logs/energy_Jul1902_0645.log", \
#            "/cdat/dafe/mccann/synthesis/beamlogs_logs/energy_Jul1902_0646.log", \
#            "/cdat/dafe/mccann/synthesis/beamlogs_logs/energy_Jul1902_0647.log", \
#            "/cdat/dafe/mccann/synthesis/beamlogs_logs/energy_Jul1902_0827.log", \
#            "/cdat/dafe/mccann/synthesis/beamlogs_logs/energy_Jul1902_1537.log", \
#            "/cdat/dafe/mccann/synthesis/beamlogs_logs/energy_Jul2302_1355.log", \
#            "/cdat/dafe/mccann/synthesis/beamlogs_logs/energy_Jul2402_1713.log", \
#            "/cdat/dafe/mccann/synthesis/beamlogs_logs/energy_Jul2402_1714.log", \
#            "/cdat/dafe/mccann/synthesis/beamlogs_logs/energy_Jul2402_1715.log", \
#            "/cdat/dafe/mccann/synthesis/beamlogs_logs/energy_Jul2802_1318.log", \
#            "/cdat/dafe/mccann/synthesis/beamlogs_logs/energy_Jul3002_1840.log", \
#            "/cdat/dafe/mccann/synthesis/beamlogs_logs/energy_Jun0201_1537.log", \
#            "/cdat/dafe/mccann/synthesis/beamlogs_logs/energy_Jun1902_2022.log", \
#            "/cdat/dafe/mccann/synthesis/beamlogs_logs/energy_Jun2102_0401.log", \
#            "/cdat/dafe/mccann/synthesis/beamlogs_logs/energy_Jun2102_0445.log", \
#            "/cdat/dafe/mccann/synthesis/beamlogs_logs/energy_Jun2102_0448.log", \
#            "/cdat/dafe/mccann/synthesis/beamlogs_logs/energy_Jun2202_1525.log", \
#            "/cdat/dafe/mccann/synthesis/beamlogs_logs/energy_Jun2502_1126.log", \
#            "/cdat/dafe/mccann/synthesis/beamlogs_logs/energy_Jun2602_1842.log", \
#            "/cdat/dafe/mccann/synthesis/beamlogs_logs/energy_Mar0301_0832.log", \
#            "/cdat/dafe/mccann/synthesis/beamlogs_logs/energy_Mar0602_2041.log", \
#            "/cdat/dafe/mccann/synthesis/beamlogs_logs/energy_Mar1302_2056.log", \
#            "/cdat/dafe/mccann/synthesis/beamlogs_logs/energy_Mar1401_0406.log", \
#            "/cdat/dafe/mccann/synthesis/beamlogs_logs/energy_Mar1901_0921.log", \
#            "/cdat/dafe/mccann/synthesis/beamlogs_logs/energy_Mar2002_1641.log", \
#            "/cdat/dafe/mccann/synthesis/beamlogs_logs/energy_Mar2002_1652.log", \
#            "/cdat/dafe/mccann/synthesis/beamlogs_logs/energy_Mar2702_0505.log", \
#            "/cdat/dafe/mccann/synthesis/beamlogs_logs/energy_Mar2702_1840.log", \
#            "/cdat/dafe/mccann/synthesis/beamlogs_logs/energy_May0101_1524.log", \
#            "/cdat/dafe/mccann/synthesis/beamlogs_logs/energy_May0102_1138.log", \
#            "/cdat/dafe/mccann/synthesis/beamlogs_logs/energy_May0301_0947.log", \
#            "/cdat/dafe/mccann/synthesis/beamlogs_logs/energy_May0701_2038.log", \
#            "/cdat/dafe/mccann/synthesis/beamlogs_logs/energy_May0902_1103.log", \
#            "/cdat/dafe/mccann/synthesis/beamlogs_logs/energy_May1502_1000.log", \
#            "/cdat/dafe/mccann/synthesis/beamlogs_logs/energy_May1502_1003.log", \
#            "/cdat/dafe/mccann/synthesis/beamlogs_logs/energy_May1902_1336.log", \
#            "/cdat/dafe/mccann/synthesis/beamlogs_logs/energy_May2302_1252.log", \
#            "/cdat/dafe/mccann/synthesis/beamlogs_logs/energy_May2302_1253.log", \
#            "/cdat/dafe/mccann/synthesis/beamlogs_logs/energy_May2302_1254.log", \
#            "/cdat/dafe/mccann/synthesis/beamlogs_logs/energy_May2302_1255.log", \
#            "/cdat/dafe/mccann/synthesis/beamlogs_logs/energy_May2401_1834.log", \
#            "/cdat/dafe/mccann/synthesis/beamlogs_logs/energy_May2401_1835.log", \
#            "/cdat/dafe/mccann/synthesis/beamlogs_logs/energy_May2401_1905.log", \
#            "/cdat/dafe/mccann/synthesis/beamlogs_logs/energy_May2401_2309.log", \
#            "/cdat/dafe/mccann/synthesis/beamlogs_logs/energy_May2501_2341.log", \
#            "/cdat/dafe/mccann/synthesis/beamlogs_logs/energy_May2902_1053.log", \
#            "/cdat/dafe/mccann/synthesis/beamlogs_logs/energy_May2902_1055.log", \
#            "/cdat/dafe/mccann/synthesis/beamlogs_logs/energy_Nov0201_1952.log", \
#            "/cdat/dafe/mccann/synthesis/beamlogs_logs/energy_Nov0802_2010.log", \
#            "/cdat/dafe/mccann/synthesis/beamlogs_logs/energy_Nov0802_2013.log", \
#            "/cdat/dafe/mccann/synthesis/beamlogs_logs/energy_Nov1201_1650.log", \
#            "/cdat/dafe/mccann/synthesis/beamlogs_logs/energy_Nov1201_1709.log", \
#            "/cdat/dafe/mccann/synthesis/beamlogs_logs/energy_Nov1302_1821.log", \
#            "/cdat/dafe/mccann/synthesis/beamlogs_logs/energy_Nov1701_0957.log", \
#            "/cdat/dafe/mccann/synthesis/beamlogs_logs/energy_Nov1701_1001.log", \
#            "/cdat/dafe/mccann/synthesis/beamlogs_logs/energy_Nov1701_1502.log", \
#            "/cdat/dafe/mccann/synthesis/beamlogs_logs/energy_Nov1801_0917.log", \
#            "/cdat/dafe/mccann/synthesis/beamlogs_logs/energy_Nov1901_0525.log", \
#            "/cdat/dafe/mccann/synthesis/beamlogs_logs/energy_Nov1901_0750.log", \
#            "/cdat/dafe/mccann/synthesis/beamlogs_logs/energy_Nov2202_1453.log", \
#            "/cdat/dafe/mccann/synthesis/beamlogs_logs/energy_Nov2502_1702.log", \
#            "/cdat/dafe/mccann/synthesis/beamlogs_logs/energy_Nov2502_1704.log", \
#            "/cdat/dafe/mccann/synthesis/beamlogs_logs/energy_Nov2602_1047.log", \
#            "/cdat/dafe/mccann/synthesis/beamlogs_logs/energy_Nov2602_1048.log", \
#            "/cdat/dafe/mccann/synthesis/beamlogs_logs/energy_Nov2602_1054.log", \
#            "/cdat/dafe/mccann/synthesis/beamlogs_logs/energy_Oct0102_1124.log", \
#            "/cdat/dafe/mccann/synthesis/beamlogs_logs/energy_Oct0102_1125.log", \
#            "/cdat/dafe/mccann/synthesis/beamlogs_logs/energy_Oct0802_1406.log", \
#            "/cdat/dafe/mccann/synthesis/beamlogs_logs/energy_Oct0802_1410.log", \
#            "/cdat/dafe/mccann/synthesis/beamlogs_logs/energy_Oct1102_0021.log", \
#            "/cdat/dafe/mccann/synthesis/beamlogs_logs/energy_Oct1102_0022.log", \
#            "/cdat/dafe/mccann/synthesis/beamlogs_logs/energy_Oct1402_1505.log", \
#            "/cdat/dafe/mccann/synthesis/beamlogs_logs/energy_Oct1402_1507.log", \
#            "/cdat/dafe/mccann/synthesis/beamlogs_logs/energy_Oct1602_0032.log", \
#            "/cdat/dafe/mccann/synthesis/beamlogs_logs/energy_Oct1901_1408.log", \
#            "/cdat/dafe/mccann/synthesis/beamlogs_logs/energy_Oct1901_1529.log", \
#            "/cdat/dafe/mccann/synthesis/beamlogs_logs/energy_Oct1902_0524.log", \
#            "/cdat/dafe/mccann/synthesis/beamlogs_logs/energy_Oct2002_1354.log", \
#            "/cdat/dafe/mccann/synthesis/beamlogs_logs/energy_Oct2701_0547.log", \
#            "/cdat/dafe/mccann/synthesis/beamlogs_logs/energy_Oct3002_1547.log", \
#            "/cdat/dafe/mccann/synthesis/beamlogs_logs/energy_Oct3101_0630.log", \
#            "/cdat/dafe/mccann/synthesis/beamlogs_logs/energy_Sep1402_1512.log", \
#            "/cdat/dafe/mccann/synthesis/beamlogs_logs/energy_Sep1402_1513.log", \
#            "/cdat/dafe/mccann/synthesis/beamlogs_logs/energy_Sep1402_1514.log", \
#            "/cdat/dafe/mccann/synthesis/beamlogs_logs/energy_Sep1402_2258.log", \
#            "/cdat/dafe/mccann/synthesis/beamlogs_logs/energy_Sep1702_1235.log", \
#            "/cdat/dafe/mccann/synthesis/beamlogs_logs/energy_Sep1702_1344.log", \
#            "/cdat/dafe/mccann/synthesis/beamlogs_logs/energy_Sep1702_1501.log", \
#            "/cdat/dafe/mccann/synthesis/beamlogs_logs/energy_Sep1702_1504.log", \
#            "/cdat/dafe/mccann/synthesis/beamlogs_logs/energy_Sep2102_1555.log", \
#            "/cdat/dafe/mccann/synthesis/beamlogs_logs/energy_Sep2102_2131.log", \
#            "/cdat/dafe/mccann/synthesis/beamlogs_logs/energy_Sep2202_0858.log", \
#            "/cdat/dafe/mccann/synthesis/beamlogs_logs/energy_Sep2402_1434.log"]

# runlog = {}
# runerr = {}
# for thelog in thelogs:
#   print "Entering", thelog
#   thedate = ""
#   thetime = ""
#   theerror = ""
#   for line in open(thelog):
#     mat = re.search("Date: ([0-9]+)", line)
#     if mat != None: thedate = mat.groups()[0]
#     mat = re.search("Time: ([0-9:]+)", line)
#     if mat != None: thetime = mat.groups()[0]
#     mat = re.search("ERROR", line)
#     if mat != None: theerror = line
#     mat = re.search("Final Beam Energy[ \->]*([0-9\.]+)", line)
#     if mat != None:
#       try:
#         thesecs = time.mktime(time.strptime(thedate + thetime, "%Y%m%d%H:%M"))
#         theenergy = mat.groups()[0]
#         for r in runtimes:
#           if runtimes[r][0] <= thesecs <= runtimes[r][1]:
#             if r not in runlog:
#               runlog[r] = []
#               runerr[r] = []

#             runlog[r].append(float(theenergy))
#             runerr[r].append(theerror)
#             print r, "has", runlog[r]
#       except ValueError:
#         pass

#       thedate = ""
#       thetime = ""
#       theerror = ""
# pickle.dump(runlog, open("runlog.p", "w"))
# pickle.dump(runerr, open("runerr.p", "w"))

runlog = pickle.load(open("runlog.p"))
runerr = pickle.load(open("runerr.p"))

for r in runlog:
  if r not in (127601, 127602, 124279, 124281):
    goods = []
    bads = []
    for val, err in zip(runlog[r], runerr[r]):
      if err == "":
        goods.append(val)
      else:
        bads.append(val)
    good_average = 0.
    bad_average = 0.
    if len(goods) > 0: good_average = sum(goods)/len(goods)*2.
    if len(bads) > 0: bad_average = sum(bads)/len(bads)*2.

#     print "%d %10.3f %10.3f %10.3f" % (r, runsummary[r].energy*2000., good_average, bad_average)
#     if abs(runsummary[r].energy*2000. - good_average) > 0.2:
#       print r
    print r, str(round(runsummary[r].energy*2000., 2)), map(lambda q: str(round(q, 2)), Numeric.array(goods)*2.)

bigpull2s = [126866, 126868, 126858, 126859, 126862, 126869, 126870, 126871]  # it's one of these
bigpull2s = 126862

# outer bhabhas
#  run   energy   cross-sec      uncertainty       pull
##############################################################
# 126858 10025.2 13.8072205746 0.141833403627 -0.535990781252
# 126859 10025.4 14.0516267611 0.151219149435  1.3062277364
# 126862 10025.4 13.2482923505 0.175109954799 -3.45958494505
# 126866 10025.4 14.0827166409 0.167878401636  1.3617983305
# 126868 10025.4 13.710875691  0.140856371582 -1.01681181493
# 126869 10025.4 13.6349103474 0.139960155461 -1.56608690285
# 126870 10025.4 13.714107655  0.141562236028 -0.988911045709
# 126871 10025.2 13.7353840229 0.139021645376 -1.06356062834

# inner bhabhas
#  run   energy   cross-sec      uncertainty       pull
##############################################################
# 126858 10025.2 13.8805559367 0.182685784272
# 126859 10025.4 13.7173676903 0.187207533592
# 126862 10025.4 13.7298286026 0.234578059278
# 126866 10025.4 14.069914221  0.214668348847
# 126868 10025.4 13.7990120479 0.181617454826
# 126869 10025.4 13.8878663485 0.183414580519
# 126870 10025.4 13.5433960222 0.177788996133
# 126871 10025.2 13.5645220828 0.174620737505






print jt.mean([13.8805559367, 13.7173676903, 14.069914221 , 13.7990120479, 13.8878663485, 13.5433960222, 13.5645220828])
outer: 13.8195488133 (others) and 13.2482923505 (badone) = 0.5 pm 0.18 diff
inner: 13.7803763356 (others) and 13.7298286026 (badone) = 0.05 pm 0.2 diff
