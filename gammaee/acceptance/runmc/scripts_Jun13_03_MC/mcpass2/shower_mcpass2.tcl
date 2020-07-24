#############################################
# file: $C3_SCRIPTS/mcpass2/shower_mcpass2.tcl
#
# purpose: generate and find shower information  
#############################################
echo " %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" 
echo " %                            %" 
echo " %     MCPASS2 SHOWER SCRIPT  %" 
echo " %                            %" 
echo " %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" 

# Produce the links between showers and MCCCResponses
prod sel MCCalibratedHitTagProd

# Need NavigationProd
prod sel NavigationProd

# Produce the link between showers and MCParticles
prod sel MCCCTaggerProd

# Fake the physics stream
emptysource def Test2 physics  


#
echo " %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" 
echo " %  MCPASS2 SHOWER SCRIPT DONE  %" 
echo " %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" 

#######################################################
