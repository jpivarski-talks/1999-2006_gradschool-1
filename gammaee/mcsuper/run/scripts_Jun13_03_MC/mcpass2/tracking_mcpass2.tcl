################################################
# file: $C3_SCRIPTS/mcpass2/tracking_mcpass2.tcl
#
# purpose: find tracks 
################################################
## setup tracking.  Use the standard MC tracking script. 
echo " %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" 
echo " %                            %" 
echo " %  MCPASS2 TRACKING SCRIPT   %" 
echo " %                            %" 
echo " %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" 
#
run_file $env(C3_SCRIPTS)/trackingMCFull.tcl
#
echo " %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" 
echo " % MCPASS2 TRACKING SCRIPT DONE %" 
echo " %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" 
#
#######################################################
