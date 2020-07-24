##################################################################
# file: $C3_SCRIPTS/mcpass2/monitor_mcpass2.tcl
#
# purpose:
#   monitor various quantities for mcpass2 
#     (output in form of log messages and histograms)
#
# (originally from monitor_hadron.tcl)
#
##################################################################


####
# tracking monitoring
proc sel P2TrackMonProc

####
# CC monitoring
proc sel CcRunAvgProc
prod sel NavigationProd
prod sel TrackShowerMatchingProd
prod sel PhotonDecaysProd
proc sel P1Pi0Proc

####
# rich monitoring
proc sel RichResolutionProc
# use events with at least 4 tracks
param RichResolutionProc RichTrackEventSelectionFlag 4
# minimal track momentum to use as a fraction of beam energy
param RichResolutionProc Pmin 0.20
# maximal track momentum to use as a fraction of beam energy
param RichResolutionProc Pmax 0.75
# analyze each track as pion
param RichResolutionProc Hypothesis 2
# no matching to cc clusters required
param RichResolutionProc RichTrackShowerMatchFlag 0


####
# muon monitoring
proc sel P2MuonMonProc

####
# dedx monitoring
proc sel P2DedxMonProc

#######################################################
