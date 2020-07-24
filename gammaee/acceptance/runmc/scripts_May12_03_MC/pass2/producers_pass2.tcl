###########################################
# file: $C3_SCRIPTS/pass2/producers_pass2.tcl
#
# purpose: loads all Producers used by pass2  
###########################################
run_file $env(C3_SCRIPTS)/pass2/tracking_pass2.tcl

run_file $env(C3_SCRIPTS)/pass2/dedx_pass2.tcl

run_file $env(C3_SCRIPTS)/pass2/muon_pass2.tcl

run_file $env(C3_SCRIPTS)/pass2/shower_pass2.tcl

run_file $env(C3_SCRIPTS)/pass2/trackshowermatch_pass2.tcl

run_file $env(C3_SCRIPTS)/pass2/trigger_pass2.tcl

run_file $env(C3_SCRIPTS)/pass2/rich_pass2.tcl

run_file $env(C3_SCRIPTS)/pass2/vfinder_pass2.tcl

run_file $env(C3_SCRIPTS)/pass2/event_class_pass2.tcl
#######################################################
# CVS Info
# $Id: producers_pass2.tcl,v 1.2 2001/10/02 22:03:19 jed Exp $
#
# $Log: producers_pass2.tcl,v $
# Revision 1.2  2001/10/02 22:03:19  jed
# minor mod to comments
#
# Revision 1.1  2001/09/27 18:34:44  cdj
# submitted initial Pass2 scripts
#
