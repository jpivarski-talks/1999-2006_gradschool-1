basedir = "/home/mccann/synthesis/"
import cPickle as pickle

class RunSummary : pass
initialrunlist = pickle.load(open(basedir+"lumieff/initialrunlist.p"))
runsummary = pickle.load(open(basedir+"lumieff/runsummary.p"))

for r in initialrunlist:
  if runsummary[r].res == 1:
    open(basedir+"run/rootscripts/db_"+str(r)+".run", 'w').write("""#$ -l u5
#$ -o /cdat/dafe/mccann/synthesis/rootlog/db_%(r)d.log
#$ -S /bin/bash
#$ -j y

cd /home/mccann/synthesis/run/
. /nfs/cleo3/scripts/cleo3defs
c3rel Dec10_03

export USER_RUN=%(r)d
export USER_DB=%(db)d
suez -f rootdb.tcl
rm -f core

exit
""" % {"r" : r, "db" : runsummary[r].db})

