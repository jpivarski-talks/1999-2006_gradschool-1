basedir = "/home/mccann/synthesis/"
import cPickle as pickle, sys, os, re

class RunSummary : pass
initialrunlist = pickle.load(open(basedir+"lumieff/initialrunlist.p"))
runsummary = pickle.load(open(basedir+"lumieff/runsummary.p"))

# testsample = filter(lambda r: runsummary[r].res == 3 and runsummary[r].kind == 'c', initialrunlist)
# for r in testsample: print r

done = []
# for l in iter(os.popen("ls "+basedir+"log", 'r')):
#   done.append(re.compile("db_([0-9]{6})\.log").match(l).group(1))
# This is more complicated than you think.

kindorder = {'c': 0, 'h': 1, 'p': 2, 's': 3}
preferred_order1 = filter(lambda r: r not in done and runsummary[r].res == 1, initialrunlist)
preferred_order2 = filter(lambda r: r not in done and runsummary[r].res == 2, initialrunlist)
preferred_order3 = filter(lambda r: r not in done and runsummary[r].res == 3, initialrunlist)

# reverse to get the right order in popping
preferred_order1.sort(lambda a, b: cmp(kindorder[runsummary[a].kind], kindorder[runsummary[b].kind]) or cmp(a, b), reverse=True)
preferred_order2.sort(lambda a, b: cmp(kindorder[runsummary[a].kind], kindorder[runsummary[b].kind]) or cmp(a, b), reverse=True)
preferred_order3.sort(lambda a, b: cmp(kindorder[runsummary[a].kind], kindorder[runsummary[b].kind]) or cmp(a, b), reverse=True)

# import biggles
# p = biggles.FramedPlot()
# p.add(biggles.Points(range(len(preferred_order1)), map(lambda r: runsummary[r].energy, preferred_order1)))
# p.show()

preferred_order1 = map(lambda r: "runscripts/db_"+str(r)+".run", preferred_order1)
preferred_order2 = map(lambda r: "runscripts/db_"+str(r)+".run", preferred_order2)
preferred_order3 = map(lambda r: "runscripts/db_"+str(r)+".run", preferred_order3)

preferred_order4 = []
for l in iter(os.popen("ls runscripts/{mc,sb}_*.run", 'r')):
  preferred_order4.append(l.rstrip())

preferred_order = []
while len(preferred_order1) > 0 or len(preferred_order2) > 0 or len(preferred_order3) > 0 or len(preferred_order4):
  if len(preferred_order1) > 0: preferred_order.append(preferred_order1.pop())
  if len(preferred_order2) > 0: preferred_order.append(preferred_order2.pop())
  if len(preferred_order3) > 0: preferred_order.append(preferred_order3.pop())
  if len(preferred_order4) > 0: preferred_order.append(preferred_order4.pop())
preferred_order.reverse()

# the runs you want first are at the END of the list (that's why I had
# to do all the reverse operations)

f = open("preferred_order.dat", 'w')
for l in preferred_order:
  f.write(l)
  f.write("\n")
f.close()
