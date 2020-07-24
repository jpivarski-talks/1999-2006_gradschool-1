basedir = "/home/mccann/synthesis/"

rawruns = (121899, 121904, 121906, 121969, 121972, 122080, 122081, \
122083, 122091, 122132, 122133, 122136, 122143, 122147, 122418, \
122429, 122430, 122576, 122586, 122587, 122594, 122647, 122800, \
122802, 122816, 122829, 122831, 122832, 123043, 123044, 123817, \
123853, 124684, 125176, 126473, 126488, 126563, 126831, 126835, \
126870, 127317, 127319, 129071, 129564, 129572, 129630, 129845, \
129848, 130427, 130473)

hasb = {}
for r in rawruns: hasb[r] = 0
hasb[121899] = 1
hasb[122133] = 1
hasb[123853] = 1
hasb[124684] = 1

for r in rawruns:
    open(basedir+"run/runscripts/rd_"+str(r)+".run", 'w').write("""#$ -l u5
#$ -o /cdat/dafe/mccann/synthesis/log/rd_%(r)d.log
#$ -S /bin/bash
#$ -j y

cd /home/mccann/synthesis/run/
. /nfs/cleo3/scripts/cleo3defs
c3rel Dec10_03

export USER_RUN=%(r)d
export USER_HASB=%(hasb)d
suez -f rawdata.tcl
rm -f core

exit
""" % {"r" : r, "hasb" : hasb[r]})

