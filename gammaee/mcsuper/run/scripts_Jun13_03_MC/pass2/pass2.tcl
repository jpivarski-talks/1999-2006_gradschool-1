###########################################
# file: $C3_SCRIPTS/pass2/pass2.tcl
#
# purpose: run full pass2 on data  
###########################################

#setup all constants
run_file $env(C3_SCRIPTS)/getPass2Constants.tcl

proc sel P1LumiMonProc
proc sel P1CrystalMonProc
proc sel PrescaleBhabhasProc

# Trigger diagnostics 
proc sel TriggerRateProc

set filter_pass2_after_level3 "proc sel Level4TriggerRateProc"

# event selection
run_file $env(C3_SCRIPTS)/pass2/filter_pass2.tcl

# Trigger diagnostics
proc sel EvTypeTriggerRateProc

# monitor output
run_file $env(C3_SCRIPTS)/pass2/monitor_pass2.tcl

# pass2 producers
run_file $env(C3_SCRIPTS)/pass2/producers_pass2.tcl

# define what gets written out
run_file $env(C3_SCRIPTS)/pass2/controlWriteout_pass2.tcl

#######################################################
# CVS Info
# $Id: pass2.tcl,v 1.3 2001/10/02 22:25:33 jed Exp $
#
# $Log: pass2.tcl,v $
# Revision 1.3  2001/10/02 22:25:33  jed
#  add in TriggerRateProc, Level4TriggerRateProc, EvTypeTriggerRateProc - thanks Hanna
#
# Revision 1.2  2001/10/02 22:02:43  jed
# minor mod to comments
#
# Revision 1.1  2001/09/27 18:34:43  cdj
# submitted initial Pass2 scripts
#


