# from __future__ import division

basedir = "/home/mccann/synthesis/"
plotdir = "/home/mccann/antithesis/plots/"
runrecord_length = 562
import sys
sys.path.append("/home/mccann/bin/python/obsolete")
import cPickle as pickle, Numeric, biggles, hist, random, jimtools as jt
from math import *

biggles.symboltype = "filled circle"
biggles.symbolsize = 0.8

class RunSummary : pass
initialrunlist = pickle.load(open(basedir+"lumieff/initialrunlist.p"))
runsummary = pickle.load(open(basedir+"lumieff/runsummary.p"))
    
rdrunlists = {}
rdrunlists["peak1db18"] = [123853]
rdrunlists["cont1db18"] = [123817]
rdrunlists["peak1db19"] = [124684]
rdrunlists["cont1db19"] = [125176]
rdrunlists["peak2db21"] = [126563, 126870, 127317, 127319, 126831]
rdrunlists["cont2db21"] = [126473, 126488, 126835]
rdrunlists["peak2db23"] = [129564, 129572, 129630, 130473]
rdrunlists["cont2db23"] = [129071, 129845, 129848, 130427]
rdrunlists["peak3db16"] = [121969, 121972, 122132, 122136, 122143, 122147, 122133]
rdrunlists["cont3db16"] = [121899, 121904, 121906, 122080, 122081, 122083, 122091]
rdrunlists["peak3db17"] = [122576, 122647, 122816, 122829, 122831, 123043, 122832, 123044]
rdrunlists["cont3db17"] = [122418, 122429, 122586, 122587, 122594, 122430, 122800, 122802]
rdrunlists["peak1dball"] = [123853, 124684]
rdrunlists["cont1dball"] = [123817, 125176]
rdrunlists["peak2dball"] = [126563, 126870, 127317, 127319, 126831, 129564, 129572, 129630, 130473]
rdrunlists["cont2dball"] = [126473, 126488, 126835, 129071, 129845, 129848, 130427]
rdrunlists["peak3dball"] = [121969, 121972, 122132, 122136, 122143, 122147, 122133, 122576, 122647, 122816, 122829, 122831, 123043, 122832, 123044]
rdrunlists["cont3dball"] = [121899, 121904, 121906, 122080, 122081, 122083, 122091, 122418, 122429, 122586, 122587, 122594, 122430, 122800, 122802]
rdrunlists["all"] = []
for k in ["peak1dball", "cont1dball", "peak2dball", "cont2dball", "peak3dball", "cont3dball"]:
  for r in rdrunlists[k]:
    rdrunlists["all"].append(r)

class RunRecord:
  def __add__(self, other):
    retval = RunRecord()
    retval.run = 0
    retval.lastevent = 0
    try:
      retval.ebeam = self.ebeam
    except AttributeError:
      try:
        retval.ebeam = other.ebeam
      except AttributeError:
        retval.ebeam = 0.
    for v in dir(other):
      if v not in ("run", "lastevent", "ebeam", "__doc__", "__module__", "__add__", "__mul__", "__div__"):
        try:
          exec "retval."+v+" = self."+v+" + other."+v
        except AttributeError:
          try:
            exec "retval."+v+" = self."+v
          except AttributeError:
            exec "retval."+v+" = other."+v
    return retval

  def __mul__(self, other):
    retval = RunRecord()
    retval.run = 0
    retval.lastevent = 0
    try:
      retval.ebeam = self.ebeam
    except AttributeError:
      retval.ebeam = 0.
    for v in dir(self):
      if v not in ("run", "lastevent", "ebeam", "__doc__", "__module__", "__add__", "__mul__", "__div__"):
        exec "retval."+v+" = self."+v+" * "+str(float(other))
    return retval

  def __div__(self, other):
    retval = RunRecord()
    retval.run = 0
    retval.lastevent = 0
    try:
      retval.ebeam = self.ebeam
    except AttributeError:
      retval.ebeam = 0.
    for v in dir(self):
      if v not in ("run", "lastevent", "ebeam", "__doc__", "__module__", "__add__", "__mul__", "__div__"):
        exec "retval."+v+" = self."+v+" / "+str(float(other))
    return retval

def getrd_byrun(r):
  filename = basedir+"pickle/rd_"+str(r)+".p"
  rec = pickle.load(open(filename))
  if len(dir(rec)) != runrecord_length:
    raise ValueError, "something's wrong with "+filename+", len dir is "+str(len(dir(rec)))
  return rec

def getdb(r):
  filename = basedir+"pickle/db_"+str(r)+".p"
  rec = pickle.load(open(filename))
  if len(dir(rec)) != runrecord_length:
    raise ValueError, "something's wrong with "+filename+", len dir is "+str(len(dir(rec)))
  return rec

def getrd(res, kind, db):
  retval = RunRecord()
  for i in rdrunlists[kind+str(res)+"db"+str(db)]:
    retval += getrd_byrun(i)
  return retval

def getmc_byfilename(filename):
  rec = pickle.load(open(filename))
  if len(dir(rec)) != runrecord_length:
    raise ValueError, "something's wrong with "+filename+", len dir is "+str(len(dir(rec)))
  return rec

def getmc(res, kind, db="all", qual="good"):
  filenames = []
  if db != "all":
    if res != 3:
      filenames.append(basedir+"pickle/mc_mc"+str(res)+kind+"_db"+str(db)+"_"+qual+".p")
    else:
      filenames.append(basedir+"pickle/mc_mc"+str(res)+kind+"_"+qual+".p")
  else:
    if res == 1:
      filenames.append(basedir+"pickle/mc_mc"+str(res)+kind+"_db18_"+qual+".p")
#      filenames.append(basedir+"pickle/mc_mc"+str(res)+kind+"_db19_"+qual+".p")
    elif res == 2:
      filenames.append(basedir+"pickle/mc_mc"+str(res)+kind+"_db21_"+qual+".p")
#      filenames.append(basedir+"pickle/mc_mc"+str(res)+kind+"_db23_"+qual+".p")
    ### AGIH!  you should NEVER combine MC from different datasets, because it's all the same events!
    elif res == 3:
      filenames.append(basedir+"pickle/mc_mc"+str(res)+kind+"_"+qual+".p")
    else: raise ValueError

  retval = RunRecord()
  for i in filenames:
    retval += getmc_byfilename(i)
  return retval

def getsb_byfilename(filename):
  rec = pickle.load(open(filename))
  if len(dir(rec)) != runrecord_length:
    raise ValueError, "something's wrong with "+filename+", len dir is "+str(len(dir(rec)))
  return rec

def getsb(kind):
  filenames = []
  if kind == "bge":
    filenames.append(basedir+"pickle/sb_bge1.p")
    filenames.append(basedir+"pickle/sb_bge2.p")
    filenames.append(basedir+"pickle/sb_bge3.p")
  elif kind == "bgp":
    filenames.append(basedir+"pickle/sb_bgp.p")
  elif kind == "cos":
    filenames.append(basedir+"pickle/sb_cos1.p")
    filenames.append(basedir+"pickle/sb_cos2.p")
    filenames.append(basedir+"pickle/sb_cos3.p")
    filenames.append(basedir+"pickle/sb_cos4.p")
  else:
    raise ValueError, "What kind of sb is "+kind+"?"

  retval = RunRecord()
  for i in filenames:
    retval += getsb_byfilename(i)
  return retval

def domc1(promptleptons=True, dobmm=0, dor=0, docas=0, dogggam=0):
  bmm = 0.0249 + dobmm*0.0007
  r = 3.58 + dor*0.14
  gggam = 0.032 + dogggam*0.0045
  retval = RunRecord()
  if promptleptons:
    retval += (mc1["ee"] + mc1["ee0"]) * bmm / (mc1["ee"] + mc1["ee0"]).all
    retval += (mc1["mumu"] + mc1["mumu0"]) * bmm / (mc1["mumu"] + mc1["mumu0"]).all
    retval += (mc1["tautau"]) * bmm * 0.9922 / (mc1["tautau"]).all
  retval += mc1["qq"] * r * bmm / mc1["qq"].all
  retval += mc1["ggg"] * (1. - (2. + 0.9922 + r)*bmm)/(1. + gggam) / mc1["ggg"].all
  retval += mc1["gggam"] * (1. - (2. + 0.9922 + r)*bmm)/(1. + gggam)*gggam / mc1["gggam"].all
  return retval

def domc2(promptleptons=True, dobmm=0, dor=0, docas=0, dogggam=0, docasll=0):
  bmm = 0.0203 + dobmm*0.0009
  r = 3.58 + dor*0.14
  cas = 0.454 + docas*0.0149
  gggam = 0.032 + dogggam*0.0045
  retval = RunRecord()
  if promptleptons:
    retval += (mc2["ee"] + mc2["ee0"]) * bmm / (mc2["ee"] + mc2["ee0"]).all
    retval += (mc2["mumu"] + mc2["mumu0"]) * bmm / (mc2["mumu"] + mc2["mumu0"]).all
    retval += (mc2["tautau"]) * bmm * 0.9938 / (mc2["tautau"]).all
  retval += mc2["qq"] * r * bmm / mc2["qq"].all
  retval += (mc2["cas"] + mc2["casll"] + mc2["casll0"]) * cas / (mc2["cas"] + (mc2["casll"] + mc2["casll0"]) * (1. + docasll*0.11)).all
  retval += mc2["ggg"] * (1. - (2. + 0.9938 + r)*bmm - cas)/(1. + gggam) / mc2["ggg"].all
  retval += mc2["gggam"] * (1. - (2. + 0.9938 + r)*bmm - cas)/(1. + gggam)*gggam / mc2["gggam"].all
  return retval

def domc3(promptleptons=True, dobmm=0, dor=0, docas=0, dogggam=0, docasll=0):
  bmm = 0.0239 + dobmm*0.0012
  r = 3.58 + dor*0.14
  cas = 0.452 + docas*0.0146
  gggam = 0.032 + dogggam*0.0045
  retval = RunRecord()
  if promptleptons:
    retval += (mc3["ee"] + mc3["ee0"]) * bmm / (mc3["ee"] + mc3["ee0"]).all
    retval += (mc3["mumu"] + mc3["mumu0"]) * bmm / (mc3["mumu"] + mc3["mumu0"]).all
    retval += (mc3["tautau"]) * bmm * 0.9946 / (mc3["tautau"]).all
  retval += mc3["qq"] * r * bmm / mc3["qq"].all
  retval += (mc3["cas"] + mc3["casll"] + mc3["casll0"]) * cas / (mc3["cas"] + (mc3["casll"] + mc3["casll0"]) * (1. + docasll*0.2)).all
  retval += mc3["ggg"] * (1. - (2. + 0.9946 + r)*bmm - cas)/(1. + gggam) / mc3["ggg"].all
  retval += mc3["gggam"] * (1. - (2. + 0.9946 + r)*bmm - cas)/(1. + gggam)*gggam / mc3["gggam"].all
  return retval

####################################

def logify(h):
  f2 = []
  for x in h.frame:
    f2.append(10**x)
  return hist.h1frame(f2, high=h.high, vals=h.vals, errs=h.errs, overflow=h.overflow, underflow=h.underflow, overflow_error=h.overflow_error, underflow_error=h.underflow_error)

mybadruns = [122617, 124363, 124364, 124365, 124368, 124369, 124372, 124373, 124459, 122353, 126341, 129522, 123013, 123014, 121928, 121929, 121953, 127951, 127955, 130278, 121710, 121930, 121944, 121954, 123884, 122331, 122335, 122336, 122339, 122341, 122342, 122344, 122345, 122349, 122350, 122352, 121476, 121748, 121822, 121847, 122685, 123436, 123847, 123873, 124816, 124860, 124862, 125367, 126273, 126329, 127280, 124452, 124454, 124456, 124458, 124462, 124464, 124465, 124466, 124467, 124469, 124472, 124473, 124474, 124475, 124477, 124478, 124479, 124480, 123281, 123411, 121595, 122093, 122330, 126510]

mybadruns_why = {}
mybadruns_why[122617] = "not in database"
mybadruns_why[124363] = "not in database"
mybadruns_why[124364] = "not in database"
mybadruns_why[124365] = "not in database"
mybadruns_why[124368] = "not in database"
mybadruns_why[124369] = "not in database"
mybadruns_why[124372] = "not in database"
mybadruns_why[124373] = "not in database"
mybadruns_why[124459] = "not in database"
mybadruns_why[122353] = "way too much cosmic ray (12%)/beam-gas (e=3%, p=15%), and suspicious note in elog"
mybadruns_why[126341] = "way too much p-beam-gas (2%), and suspicious note in elog"
mybadruns_why[129522] = "way too much p-beam-gas (2%), no mention of this in elog, but lots of components dying in elog"
mybadruns_why[123013] = "a really tiny run"
mybadruns_why[123014] = "a really tiny run"
mybadruns_why[121928] = "gamgam trigger troubles"
mybadruns_why[121929] = "gamgam trigger troubles"
mybadruns_why[121953] = "gamgam trigger troubles"
mybadruns_why[127951] = "gamgam trigger troubles"
mybadruns_why[127955] = "gamgam trigger troubles"
mybadruns_why[130278] = "gamgam trigger troubles"
mybadruns_why[121710] = "gamgam trigger troubles"
mybadruns_why[121930] = "gamgam trigger troubles"
mybadruns_why[121944] = "gamgam trigger troubles"
mybadruns_why[121954] = "gamgam trigger troubles"
mybadruns_why[123884] = "gamgam trigger troubles"
mybadruns_why[122331] = "broken showers in barrel"
mybadruns_why[122335] = "broken showers in barrel"
mybadruns_why[122336] = "broken showers in barrel"
mybadruns_why[122339] = "broken showers in barrel"
mybadruns_why[122341] = "broken showers in barrel"
mybadruns_why[122342] = "broken showers in barrel"
mybadruns_why[122344] = "broken showers in barrel"
mybadruns_why[122345] = "broken showers in barrel"
mybadruns_why[122349] = "broken showers in barrel"
mybadruns_why[122350] = "broken showers in barrel"
mybadruns_why[122352] = "broken showers in barrel"
mybadruns_why[121476] = "failed trackless bhabha test"
mybadruns_why[121748] = "failed trackless bhabha test"
mybadruns_why[121822] = "failed trackless bhabha test"
mybadruns_why[121847] = "failed trackless bhabha test"
mybadruns_why[122685] = "failed trackless bhabha test"
mybadruns_why[123436] = "failed trackless bhabha test"
mybadruns_why[123847] = "failed trackless bhabha test"
mybadruns_why[123873] = "failed trackless bhabha test"
mybadruns_why[124816] = "failed trackless bhabha test"
mybadruns_why[124860] = "failed trackless bhabha test"
mybadruns_why[124862] = "failed trackless bhabha test"
mybadruns_why[125367] = "failed trackless bhabha test"
mybadruns_why[126273] = "failed trackless bhabha test"
mybadruns_why[126329] = "failed trackless bhabha test"
mybadruns_why[127280] = "failed trackless bhabha test"
mybadruns_why[124452] = "bhabha peak is very wide (in p1)"
mybadruns_why[124454] = "bhabha peak is very wide (in p1)"
mybadruns_why[124456] = "bhabha peak is very wide (in p1)"
mybadruns_why[124458] = "bhabha peak is very wide (in p1)"
mybadruns_why[124462] = "bhabha peak is very wide (in p1)"
mybadruns_why[124464] = "bhabha peak is very wide (in p1)"
mybadruns_why[124465] = "bhabha peak is very wide (in p1)"
mybadruns_why[124466] = "bhabha peak is very wide (in p1)"
mybadruns_why[124467] = "bhabha peak is very wide (in p1)"
mybadruns_why[124469] = "bhabha peak is very wide (in p1)"
mybadruns_why[124472] = "bhabha peak is very wide (in p1)"
mybadruns_why[124473] = "bhabha peak is very wide (in p1)"
mybadruns_why[124474] = "bhabha peak is very wide (in p1)"
mybadruns_why[124475] = "bhabha peak is very wide (in p1)"
mybadruns_why[124477] = "bhabha peak is very wide (in p1)"
mybadruns_why[124478] = "bhabha peak is very wide (in p1)"
mybadruns_why[124479] = "bhabha peak is very wide (in p1)"
mybadruns_why[124480] = "bhabha peak is very wide (in p1)"
mybadruns_why[123281] = "hadronic cross-section dies in the last few minutes"
mybadruns_why[123411] = "hadronic cross-section dies in the last few minutes"
mybadruns_why[121595] = "large unidentified backgrounds"
mybadruns_why[122093] = "large unidentified backgrounds"
mybadruns_why[122330] = "large unidentified backgrounds"
mybadruns_why[126510] = "large unidentified backgrounds"
# mybadruns_why[] = ""





# count only the first 99 bins in vstime
mycarefulscan = [121369, 121374, 121379, 121391, 121395, 121401, 121408, 122249, 123004, 128310]


# print "Just before gotdb"
# gotdb = {}
# for r in initialrunlist:
#   if r not in mybadruns:
#     gotdb[r] = getdb(r)
# print "Just after gotdb"
# pickle.dump(gotdb, open(basedir+"pickle/alldb.p", 'w'))
# print "Just after write gotdb"

# print "Just before load gotdb"
# gotdb = pickle.load(open(basedir+"pickle/alldb.p"))
# print "Just after load gotdb"



# cross = pickle.load(open("/home/mccann/antithesis/crosssection.p"))
# cross_err = pickle.load(open("/home/mccann/antithesis/crosssection_err.p"))




# scandef = {}
# scandef["jan16"] = (lambda r: 123164 <= r <= 123193 or 123369 <= r <= 123382)
# scandef["jan30"] = (lambda r: 123565 <= r <= 123718)
# scandef["feb06"] = (lambda r: 123767 <= r <= 123893)
# scandef["feb13"] = (lambda r: 123938 <= r <= 123962 or 124080 <= r <= 124092)
# scandef["feb20"] = (lambda r: 124102 <= r <= 124214)
# scandef["feb27"] = (lambda r: 124279 <= r <= 124394)
# scandef["mar06"] = (lambda r: 124436 <= r <= 124522 or 124807 <= r <= 124820)
# scandef["mar13"] = (lambda r: 124625 <= r <= 124736 or 124960 <= r <= 124973)
# scandef["apr03"] = (lambda r: 125119 <= r <= 125127 or 125158 <= r <= 125178)
# scandef["apr08"] = (lambda r: 125254 <= r <= 125262 or r == 124954)
# scandef["apr09"] = (lambda r: 125285 <= r <= 125297)
# scandef["apr10"] = (lambda r: 125303 <= r <= 125416)
# scandef["may29"] = (lambda r: 126449 <= r <= 126568)
# scandef["jun11"] = (lambda r: 126651 <= r <= 126673 or 126776 <= r <= 126783)
# scandef["jun12"] = (lambda r: 126814 <= r <= 126915 or 127059 <= r <= 127116 or 127206 <= r <= 127250)
# scandef["jul10"] = (lambda r: 127588 <= r <= 127641)
# scandef["jul24"] = (lambda r: 127683 <= r <= 127725 or 127924 <= r <= 127963)
# scandef["aug07"] = (lambda r: 127643 <= r <= 127682 or 128303 <= r <= 128316)
# scandef["nov28"] = (lambda r: 121884 <= r <= 122007)
# scandef["dec05"] = (lambda r: 122064 <= r <= 122178)
# scandef["dec12"] = (lambda r: 122245 <= r <= 122326)
# scandef["dec19"] = (lambda r: 122409 <= r <= 122527)
# scandef["dec26"] = (lambda r: 122535 <= r <= 122653)
# scandef["jan02"] = (lambda r: 122766 <= r <= 122881)
# scandef["jan09"] = (lambda r: 122993 <= r <= 123101)
# scandef_order = ["jan16", "jan30", "feb06", "feb13", "feb20", "feb27", "mar06", "mar13", "apr03", "apr08", "apr09", "apr10", "may29", "jun11", "jun12", "jul10", "jul24", "aug07", "nov28", "dec05", "dec12", "dec19", "dec26", "jan02", "jan09"]
