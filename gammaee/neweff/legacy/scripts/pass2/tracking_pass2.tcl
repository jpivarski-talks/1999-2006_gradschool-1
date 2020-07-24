###########################################
# file:tracking_pass2.tcl
#
# purpose: find tracks in Pass2
###########################################
## setup tracking.  Use the standard tracking script.
echo " %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" 
echo " %                            %" 
echo " %   PASS2 TRACKING SCRIPT    %" 
echo " %                            %" 
echo " %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" 
#
run_file $env(C3_SCRIPTS)/trackingDataFull.tcl

#
echo " %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" 
echo " % PASS2 TRACKING SCRIPT DONE %" 
echo " %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" 
#
#######################################################
# CVS Info
# $Id: tracking_pass2.tcl,v 1.2 2001/10/02 22:05:28 jed Exp $
#
# $Log: tracking_pass2.tcl,v $
# Revision 1.2  2001/10/02 22:05:28  jed
# minor mod to comments, remove kalman params entirely
#
# Revision 1.1  2001/09/27 18:34:45  cdj
# submitted initial Pass2 scripts
#


 