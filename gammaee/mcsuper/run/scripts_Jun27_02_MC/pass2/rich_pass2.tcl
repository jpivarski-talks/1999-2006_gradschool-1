###########################################
# file: $C3_SCRIPTS/pass2/rich_pass2.tcl
#
# purpose: do RICH identification  for pass2
#
###########################################
echo " %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" 
echo " %                            %" 
echo " %      PASS2 RICH SCRIPT     %" 
echo " %                            %" 
echo " %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" 
# 
# Rich producers ---------------------------------------------
run_file $env(C3_SCRIPTS)/richAna.tcl
#
#
#
echo " %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" 
echo " %   PASS2 RICH SCRIPT DONE   %" 
echo " %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" 

#######################################################
# CVS Info
# $Id: rich_pass2.tcl,v 1.2 2001/10/02 22:03:46 jed Exp $
#
# $Log: rich_pass2.tcl,v $
# Revision 1.2  2001/10/02 22:03:46  jed
# minor mod to comments
#
# Revision 1.1  2001/09/27 18:34:44  cdj
# submitted initial Pass2 scripts
#

