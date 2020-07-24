import pickle

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
  elif r == 130630:
    return run_date(130629)
  else:
    raise Exception, r

def setup_runs(res, low, high, scanassoc=True):
  beginning = run_date(low)

  tmpruns = []
  for r in initialrunlist:
    if r not in mybadruns and low <= r <= high and runsummary[r].res == res:
      if runsummary[r].kind == 's' or runsummary[r].kind == 'p':
        if scanassoc and run_date(r) < beginning + 48.*60.*60:
          tmpruns.append(r)
        if not scanassoc and run_date(r) >= beginning + 48.*60.*60:
          tmpruns.append(r)
  return tmpruns

low = setup_runs(1, 124625, 124736, scanassoc=False)
high = setup_runs(1, 125303, 125416, scanassoc=False)
