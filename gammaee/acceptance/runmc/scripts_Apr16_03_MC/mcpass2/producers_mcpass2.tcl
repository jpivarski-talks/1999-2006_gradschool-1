#################################################
# file: $C3_SCRIPTS/mcpass2/producers_mcpass2.tcl
#
# purpose: loads all producers used by mcpass2  
#################################################
run_file $env(C3_SCRIPTS)/mcpass2/tracking_mcpass2.tcl

run_file $env(C3_SCRIPTS)/mcpass2/dedx_mcpass2.tcl

run_file $env(C3_SCRIPTS)/pass2/muon_pass2.tcl

run_file $env(C3_SCRIPTS)/pass2/shower_pass2.tcl

run_file $env(C3_SCRIPTS)/mcpass2/shower_mcpass2.tcl

run_file $env(C3_SCRIPTS)/pass2/trackshowermatch_pass2.tcl

# all trigger work now done in cleog job
#run_file $env(C3_SCRIPTS)/pass2/trigger_pass2.tcl

run_file $env(C3_SCRIPTS)/pass2/rich_pass2.tcl

run_file $env(C3_SCRIPTS)/pass2/vfinder_pass2.tcl

run_file $env(C3_SCRIPTS)/pass2/event_class_pass2.tcl
#######################################################

