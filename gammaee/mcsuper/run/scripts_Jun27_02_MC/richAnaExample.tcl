#
#  This is a complete example how to run Rich analysis
#  on mini pass2 data        8/3/00 TS
#
#  $Id: richAnaExample.tcl,v 1.4 2001/03/29 17:46:24 ajm36 Exp $
#  $Log: richAnaExample.tcl,v $
#  Revision 1.4  2001/03/29 17:46:24  ajm36
#  clean out old scripts, get rid of drcalibration emptysources
#
#  Revision 1.3  2000/11/20 03:12:05  ts
#  update rich scripts to use RichTrackPrototypesProd etc.
#
#  Revision 1.2  2000/11/16 03:12:59  lkg
#  Changed MagField to MagFieldProd
#
#  Revision 1.1  2000/08/03 22:43:41  ts
#  add rich scripts
#
#


default prompt off

# ------- hadronic skim --------------------------------------
module sel DBModule
database in /nfs/cleo3/database/data5/db event beginrun startrun endrun
database read_collection mp2-hadron
# ------------------------------------------------------------

# -----  load constants --------------------------------------
run_file $env(C3_SCRIPTS)/getConstants.tcl
# ------------------------------------------------------------

# Tracking producers when running on mini pass2 --------------
prod sel MagFieldProd
prod sel NavigationProd
prod sel TrackDeliveryProd
# ------------------------------------------------------------

# Rich producers ---------------------------------------------
run_file $env(C3_SCRIPTS)/richAna.tcl
# ------------------------------------------------------------


# replace with your processor --------------------------------
#
# here: processor to print NavRich
proc sel RichExtractPrintAllProc
param RichExtractPrintAllProc NavRich 20
# ------------------------------------------------------------


go 50

exit
