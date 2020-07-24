basedir = "/home/mccann/synthesis/"

def makeone(typename):
  open(basedir+"run/runscripts/sb_"+typename+".run", 'w').write("""#$ -l u5
#$ -o /cdat/dafe/mccann/synthesis/log/sb_%(typename)s.log
#$ -S /bin/bash
#$ -j y

cd /home/mccann/synthesis/run/
. /nfs/cleo3/scripts/cleo3defs
c3rel Dec10_03

export USER_TYPE=%(typename)s
suez -f controlsample.tcl
rm -f core

exit
""" % vars())

makeone("bgp")
makeone("bge1")
makeone("bge2")
makeone("bge3")
makeone("cos1")
makeone("cos2")
makeone("cos3")
makeone("cos4")
