basedir = "/home/mccann/synthesis/"

def makeone(typename, goodbunch, ellell, photos, mcsource):
  open(basedir+"run/runscripts/mc_"+typename+".run", 'w').write("""#$ -l u5
#$ -o /cdat/dafe/mccann/synthesis/log/mc_%(typename)s.log
#$ -S /bin/bash
#$ -j y

cd /home/mccann/synthesis/run/
. /nfs/cleo3/scripts/cleo3defs
c3rel Dec10_03

export USER_TYPE=%(typename)s
export USER_GOODBUNCH=%(goodbunch)s
export USER_ELLELL=%(ellell)s
export USER_PHOTOS=%(photos)s
export USER_MCSOURCE=%(mcsource)s
suez -f montecarlo.tcl
rm -f core

exit
""" % vars())

for x in ["_good", "_bad"]:
  yorn = "true"
  if x == "_bad": yorn = "false"
  makeone("mc1ee0_db18"+x,         yorn, "true",  "false", "mc1ee_db18")
  makeone("mc1ee0_db19"+x,         yorn, "true",  "false", "mc1ee_db19")
  makeone("mc1ee_db18"+x,          yorn, "true",  "true",  "mc1ee_db18")
  makeone("mc1ee_db19"+x,          yorn, "true",  "true",  "mc1ee_db19")
  makeone("mc1ggg_db18"+x,         yorn, "false", "false", "mc1ggg_db18")
  makeone("mc1ggg_db19"+x,         yorn, "false", "false", "mc1ggg_db19")
  makeone("mc1gggam_db18"+x,       yorn, "false", "false", "mc1gggam_db18")
  makeone("mc1gggam_db19"+x,       yorn, "false", "false", "mc1gggam_db19")
  makeone("mc1mumu0_db18"+x,       yorn, "true",  "false", "mc1mumu_db18")
  makeone("mc1mumu0_db19"+x,       yorn, "true",  "false", "mc1mumu_db19")
  makeone("mc1mumu_db18"+x,        yorn, "true",  "true",  "mc1mumu_db18")
  makeone("mc1mumu_db19"+x,        yorn, "true",  "true",  "mc1mumu_db19")
  makeone("mc1qq_db18"+x,          yorn, "false", "false", "mc1qq_db18")
  makeone("mc1qq_db19"+x,          yorn, "false", "false", "mc1qq_db19")
  makeone("mc1tautau_db18"+x,      yorn, "false", "false", "mc1tautau_db18")
  makeone("mc1tautau_db19"+x,      yorn, "false", "false", "mc1tautau_db19")
  makeone("mc2cas_db21"+x,         yorn, "false", "false", "mc2cas_db21")
  makeone("mc2cas_db23"+x,         yorn, "false", "false", "mc2cas_db23")
  makeone("mc2casll0_db21"+x,      yorn, "true",  "false", "mc2cas_db21")
  makeone("mc2casll0_db23"+x,      yorn, "true",  "false", "mc2cas_db23")
  makeone("mc2casll_db21"+x,       yorn, "true",  "true",  "mc2cas_db21")
  makeone("mc2casll_db23"+x,       yorn, "true",  "true",  "mc2cas_db23")
  makeone("mc2chibkgnd_db21"+x,    yorn, "false", "false", "mc2chibkgnd_db21")
  makeone("mc2chibkgnd_db23"+x,    yorn, "false", "false", "mc2chibkgnd_db23")
  makeone("mc2ee0_db21"+x,         yorn, "true",  "false", "mc2ee_db21")
  makeone("mc2ee0_db23"+x,         yorn, "true",  "false", "mc2ee_db23")
  makeone("mc2ee_db21"+x,          yorn, "true",  "true",  "mc2ee_db21")
  makeone("mc2ee_db23"+x,          yorn, "true",  "true",  "mc2ee_db23")
  makeone("mc2ggg_db21"+x,         yorn, "false", "false", "mc2ggg_db21")
  makeone("mc2ggg_db23"+x,         yorn, "false", "false", "mc2ggg_db23")
  makeone("mc2gggam_db21"+x,       yorn, "false", "false", "mc2gggam_db21")
  makeone("mc2gggam_db23"+x,       yorn, "false", "false", "mc2gggam_db23")
  makeone("mc2mumu0_db21"+x,       yorn, "true",  "false", "mc2mumu_db21")
  makeone("mc2mumu0_db23"+x,       yorn, "true",  "false", "mc2mumu_db23")
  makeone("mc2mumu_db21"+x,        yorn, "true",  "true",  "mc2mumu_db21")
  makeone("mc2mumu_db23"+x,        yorn, "true",  "true",  "mc2mumu_db23")
  makeone("mc2qq_db21"+x,          yorn, "false", "false", "mc2qq_db21")
  makeone("mc2qq_db23"+x,          yorn, "false", "false", "mc2qq_db23")
  makeone("mc2tautau_db21"+x,      yorn, "false", "false", "mc2tautau_db21")
  makeone("mc2tautau_db23"+x,      yorn, "false", "false", "mc2tautau_db23")
  makeone("mc3cas"+x,              yorn, "false", "false", "mc3cas")
  makeone("mc3casll0"+x,           yorn, "true",  "false", "mc3cas")
  makeone("mc3casll"+x,            yorn, "true",  "true",  "mc3cas")
  makeone("mc3chibkgnd"+x,         yorn, "false", "false", "mc3chibkgnd")
  makeone("mc3ee0"+x,              yorn, "true",  "false", "mc3ee")
  makeone("mc3ee"+x,               yorn, "true",  "true",  "mc3ee")
  makeone("mc3ggg"+x,              yorn, "false", "false", "mc3ggg")
  makeone("mc3gggam"+x,            yorn, "false", "false", "mc3gggam")
  makeone("mc3mumu0"+x,            yorn, "true",  "false", "mc3mumu")
  makeone("mc3mumu"+x,             yorn, "true",  "true",  "mc3mumu")
  makeone("mc3qq"+x,               yorn, "false", "false", "mc3qq")
  makeone("mc3tautau"+x,           yorn, "false", "false", "mc3tautau")
