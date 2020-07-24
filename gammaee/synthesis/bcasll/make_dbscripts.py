import cPickle as pickle

class RunSummary : pass
initialrunlist = pickle.load(open("/home/mccann/synthesis/lumieff/initialrunlist.p"))
runsummary = pickle.load(open("/home/mccann/synthesis/lumieff/runsummary.p"))
runstart = pickle.load(open("/home/mccann/antithesis/old_dotps/runstart.p"))
runend = pickle.load(open("/home/mccann/antithesis/old_dotps/runend.p"))

mybadruns = [122617, 124363, 124364, 124365, 124368, 124369, 124372, 124373, 124459, 122353, 126341, 129522, 123013, 123014, 121928, 121929, 121953, 127951, 127955, 130278, 121710, 121930, 121944, 121954, 123884, 122331, 122335, 122336, 122339, 122341, 122342, 122344, 122345, 122349, 122350, 122352, 121476, 121748, 121822, 121847, 122685, 123436, 123847, 123873, 124816, 124860, 124862, 125367, 126273, 126329, 127280, 124452, 124454, 124456, 124458, 124462, 124464, 124465, 124466, 124467, 124469, 124472, 124473, 124474, 124475, 124477, 124478, 124479, 124480, 123281, 123411, 121595, 122093, 122330, 126510]

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
#      if runsummary[r].kind == 's' or runsummary[r].kind == 'p':
      if runsummary[r].kind == 'p':
        if run_date(r) < beginning + 48.*60.*60:
          tmpruns.append(r)
  return tmpruns

u2runs = {}
u3runs = {}

u2runs["cont"] = []
u3runs["cont"] = []
for r in initialrunlist:
  if r not in mybadruns:
    if runsummary[r].res == 2 and runsummary[r].kind == 'c':
      u2runs["cont"].append(r)
    if runsummary[r].res == 3 and runsummary[r].kind == 'c':
      u3runs["cont"].append(r)

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

for Y, y in zip([2, 3], [u2runs, u3runs]):
  for s in y:
    for r in y[s]:
      thedir = "peak"+str(Y)
      if s == "cont":
        thedir = "cont"+str(Y)
      open("/home/mccann/synthesis/bcasll/runscripts/db_"+str(r)+".run", 'w').write("""#$ -l u5
#$ -o /cdat/tem/mccann/bcasll_%(r)d.log
#$ -S /bin/bash
#$ -j y

cd /home/mccann/synthesis/bcasll/
. /nfs/cleo3/scripts/cleo3defs
c3rel Dec10_03

export USER_RUN=%(r)d
export USER_DB=%(db)d
export USER_DIR=%(thedir)s
suez -f database.tcl
rm -f core

exit
""" % {"r" : r, "db" : runsummary[r].db, "thedir" : thedir})

