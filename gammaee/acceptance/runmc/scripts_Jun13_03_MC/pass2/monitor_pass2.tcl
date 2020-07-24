##################################################################
# file: $C3_SCRIPTS/pass2/monitor_pass2.tcl
#
# purpose:
#   monitor various quantities for pass2
#     (output in form of log messages and histograms)
#
# (originally from monitor_hadron.tcl)
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

####
# muon monitoring
proc sel P2MuonMonProc


####
# dedx monitoring
proc sel P2DedxMonProc

####
# trigger monitoring
# trigger monitoring done in filter_pass2.tcl

####
# misc monitoring
proc sel SemiLepProc

#######################################################
# CVS Info
# $Id: monitor_pass2.tcl,v 1.2 2001/10/02 21:59:36 jed Exp $
#
# $Log: monitor_pass2.tcl,v $
# Revision 1.2  2001/10/02 21:59:36  jed
#  get rid of RawMuonProc and remove unused Trigger monitor area
#
# Revision 1.1  2001/09/27 18:34:42  cdj
# submitted initial Pass2 scripts
#
# Revision 1.1  2000/09/19 15:31:48  bkh
# Make customized monitor tcl files
#
# Revision 1.1  2000/07/12 20:31:34  mkl
# added monitor script
#
#
