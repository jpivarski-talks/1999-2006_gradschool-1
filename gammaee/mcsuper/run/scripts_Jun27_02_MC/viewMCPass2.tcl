#============================================================
# File: viewMCPass2.tcl
#
# Purpose:
#   use the event display to view the information
#    stored in the MC pass2 file
#
#============================================================
run_file $env(C3_SCRIPTS)/runOnPass2.tcl
proc sel SpExtractStandAloneGeomProc
proc sel SpExtractMCDecayTreeProc
#look at the DecayTree from GEANT (i.e. MCResponseProd)
param SpExtractMCDecayTreeProc extract_usage_tag {""}
proc sel SpExtractKinePionFitProc
proc sel SpExtractShowerAttributesProc
proc sel SpExtractDBEventHeaderProc
proc sel SpViewerProc

echo "_______________"
echo "Don't forget to specify 'physics beginrun startrun event' as "
echo " the streams you should read from the file(s)"
echo "---------------"
