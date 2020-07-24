###########################################
# file: $C3_SCRIPTS/vfinder_pass2.tcl
#
# purpose: find verticies for Pass2
# 
###########################################
echo " %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" 
echo " %                            %" 
echo " %    PASS2 VFINDER SCRIPT    %" 
echo " %                            %" 
echo " %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" 
# 
#   Select proton candidates.
#   Don't try to filter pion candidates; no significant improvement in
#      signal purity and potential for efficiency loss at low
#      momentum.
#
# prod sel VFPionSelectorProd
prod sel VFProtonSelectorProd
#
#   Proton selection criteria:
#
param VFProtonSelectorProd                UseDedx  true
param VFProtonSelectorProd      SetDedxProtonMean  -1.50
param VFProtonSelectorProd     SetDedxProtonSigma   6.00
param VFProtonSelectorProd   ProtonDedxSafetyMode  true

prod sel VFinderProd
# param VFinderProd     PionTrackUsageTag     GoodVFPionNavTrack
param VFinderProd   ProtonTrackUsageTag   GoodVFProtonNavTrack
#
#
echo " %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" 
echo " %   PASS2 VFINDER SCRIPT DONE   %" 
echo " %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" 
#
#######################################################
# CVS Info
# $Id: vfinder_pass2.tcl,v 1.3 2001/10/04 04:29:58 pappas Exp $
#
# $Log: vfinder_pass2.tcl,v $
# Revision 1.3  2001/10/04 04:29:58  pappas
# Turn off pion pre-selection. Risk/Benefit ratio too large...
#
# Revision 1.2  2001/10/02 22:08:21  jed
#  minor comment mods
#
# Revision 1.1  2001/09/27 18:34:46  cdj
# submitted initial Pass2 scripts
#

