#############################################
# file: $C3_SCRIPTS/mcpass2/filter_mpass2.tcl
#
# purpose of this MONTE CARLO version:
#          execute the filter algorithms but
#          do not reject events based on its
#          decision 
# ("Arbitrary decision" by s/w coordinator.)
# +++++++++++++++++++++++++++++++++++++++++
#
# This means data and MC are being treated
# differently!
#
# +++++++++++++++++++++++++++++++++++++++++
#
# usage:
#    for the simplest case just do
#      Suez> run_file filter_pass2.tcl
#    it is possible to run commands after Level4
#    but before any other filters
#      Suez> set filter_pass2_after_level4 "proc sel MyProc"
#      Suez> run_file filter_pass2.tcl
#
###########################################

proc sel Level3Proc


proc sel Level4Proc
# MC: do not throw out any events:
param Level4Proc TagOnly true 
# (default is false)

proc sel EventTypeFilterProc
# MC: do not throw out any events:
# leave the following line commented,
# which is executed for data.
# param EventTypeFilterProc Known true 

