execfile("utilities.py")

gamgam = {}
lastevent = {}
p2lumi = {}
ribb = {}
# execfile("lumilogs1.py")  # wrong p2lumi (wrong nb^-1)
execfile("lumilogs2.py")    # lastevent
# execfile("lumilogs3.py")  # only slightly wrong gamgam
execfile("lumilogs4.py")    # ribb
execfile("lumilogs5.py")    # right p2lumi (numbers of events)

u1runs = []
u2runs = []
u3runs = []
for r in initialrunlist:
  if r not in mybadruns:
    if runsummary[r].res == 1 and runsummary[r].kind == 'c':
      u1runs.append(r)
    if runsummary[r].res == 2 and runsummary[r].kind == 'c':
      u2runs.append(r)
    if runsummary[r].res == 3 and runsummary[r].kind == 'c':
      u3runs.append(r)

# for r in u1runs + u2runs + u3runs:
#   therun = getdb(r)
#   if therun.gamgam != gamgam[r]:
#     print "gamgam discrepancy:", therun.gamgam, gamgam[r]
#   if therun.lastevent != lastevent[r]:
#     print "lastevent discrepancy:", therun.lastevent, lastevent[r]

# this is what reads in my gamgam counts
for r in u1runs + u2runs + u3runs:
  gamgam[r] = getdb(r).gamgam

print jt.mean(map(lambda r: runsummary[r].energy, u1runs))
print jt.mean(map(lambda r: runsummary[r].energy, u2runs))
print jt.mean(map(lambda r: runsummary[r].energy, u3runs))
  
def count(what, where):
  n = 0
  for r in where:
    n += what[r]
  return n





