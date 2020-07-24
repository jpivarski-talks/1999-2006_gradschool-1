###########################################
# file: $C3_SCRIPTS/pass2/filter_pass2.tcl
#
# purpose: do not save certain types of events 
# usage:
#    for the simplest case just do
#      Suez> run_file filter_pass2.tcl
#    it is possible to run commands after Level4
#    but before any other filters
#      Suez> set filter_pass2_after_level4 "proc sel MyProc"
#      Suez> run_file filter_pass2.tcl
###########################################

proc sel Level3Proc

if [info exists filter_pass2_after_level3] {
   eval $filter_pass2_after_level3
}

proc sel Level4Proc
param Level4Proc TagOnly false
param Level4Proc VerboseMode false
param Level4Proc PassL3Garbage false

#if user wants, run commands after 
if [info exists filter_pass2_after_level4] {
   eval $filter_pass2_after_level4
}
#do not store any events that have an unknown type
proc sel EventTypeFilterProc
param EventTypeFilterProc Known true 
