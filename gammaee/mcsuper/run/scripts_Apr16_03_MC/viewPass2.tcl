#============================================================
# File: viewPass2.tcl
#
# Purpose:
#   use the event display to view the information
#    in a pass2'ed event
#
#============================================================
run_file $env(C3_SCRIPTS)/runOnPass2.tcl
proc sel SpExtractStandAloneGeomProc
proc sel SpExtractKinePionFitProc
proc sel SpExtractShowerAttributesProc
proc sel SpExtractDBEventHeaderProc
proc sel SpViewerProc