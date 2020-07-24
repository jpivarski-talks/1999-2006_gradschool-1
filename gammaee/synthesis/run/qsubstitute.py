import os, sys

maxjobs = sys.argv[1]

preferred_order = []
for l in iter(open("preferred_order.dat")):
  preferred_order.append(l)

def jobs():
  j = -2
  for l in iter(os.popen("qstat -u mccann", 'r')): j += 1
  if j < 0: j = 0
  return j

while len(preferred_order) > 0:
  while jobs() > maxjobs:
    print "Too many jobs, so I wait."
    os.system("sleep 300")
  print "Submitting %s!" % preferred_order[-1]
  os.system("qsub "+str(preferred_order.pop()))
