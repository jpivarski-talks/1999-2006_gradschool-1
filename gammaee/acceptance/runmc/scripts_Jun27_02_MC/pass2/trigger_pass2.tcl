###########################################
# file: $C3_SCRIPTS/pass2/trigger_pass2.tcl
#
# purpose: provide trigger info for pass2
#
# 
###########################################
#
echo " %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" 
echo " %                            %" 
echo " %    PASS2 TRIGGER SCRIPT    %" 
echo " %                            %" 
echo " %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" 

# needed for Trigger Diagnostics
prod sel TriggerDataProd

# trigger info
prod sel TriggerL1DataProd

#
#
echo " %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" 
echo " %  PASS2 TRIGGER SCRIPT DONE %" 
echo " %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" 
#
#######################################################
# CVS Info
# $Id: trigger_pass2.tcl,v 1.2 2001/10/02 22:07:35 jed Exp $
#
# $Log: trigger_pass2.tcl,v $
# Revision 1.2  2001/10/02 22:07:35  jed
# minor comment mods, add in TriggerDataProd for trigger monitoring purposes
#
# Revision 1.1  2001/09/27 18:34:46  cdj
# submitted initial Pass2 scripts
#


