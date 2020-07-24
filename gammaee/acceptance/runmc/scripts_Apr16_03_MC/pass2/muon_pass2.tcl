###########################################
# file: $C3_SCRIPTS/pass2/muon_pass2.tcl
#
# purpose: identify muons 
# 
###########################################
#
echo " %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" 
echo " %                            %" 
echo " %      PASS2 MUON SCRIPT     %" 
echo " %                            %" 
echo " %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" 
#
#
prod sel ASiStorePro 
prod sel IRGeomProd 
prod sel SiGeom 
prod sel DRGeom 
prod sel CoilGeomProd 
prod sel DRWireLayerProd 
prod sel ADRGeomProd 
prod sel CcGeomProd 
prod sel RichGeom 
prod sel MUGeomProd 
# 
# 
# load muon reconstruction and relevant constants producer: 
# 
prod sel MutrReconProd 
prod sel MuConsProd 
# 
#--------------------------------------------------------------------------- 
# 
# load GEANT description of the materials AFTER loading MutrReconProd! 
# 
prod sel Geant3MaterialsMediaProd 
# 
#--------------------------------------------------------------------------- 
# 
# miscellaneous:  
# 
prod sel DBRunHeaderProd 
# 
#--------------------------------------------------------------------------- 
echo " %%%%%%%%%%%%%%%%%%%%%%%%%%%%%" 
echo " %  PASS2 MUON SCRIPT DONE   %" 
echo " %%%%%%%%%%%%%%%%%%%%%%%%%%%%%" 
#
#######################################################
# CVS Info
# $Id: muon_pass2.tcl,v 1.2 2001/10/02 22:02:05 jed Exp $
#
# $Log: muon_pass2.tcl,v $
# Revision 1.2  2001/10/02 22:02:05  jed
# minor mod to comments
#
# Revision 1.1  2001/09/27 18:34:43  cdj
# submitted initial Pass2 scripts
#
