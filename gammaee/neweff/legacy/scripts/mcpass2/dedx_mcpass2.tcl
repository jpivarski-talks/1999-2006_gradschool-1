#############################################
# file: $C3_SCRIPTS/mcpass2/dedx_mcpass2.tcl
#
# purpose: generate and find dedx information  
#############################################
echo " %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" 
echo " %                            %" 
echo " %     MCPASS2 DEDX SCRIPT    %" 
echo " %                            %" 
echo " %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" 
set MCTagger HitLevelTagger

# Produce the link between CalibratedDRHits and MCResponses
prod sel MCCalibratedHitTagProd

# Produce the link between SeedTracks and MCParticles
prod sel MCTrackTaggerProd
# Fake the physics stream
emptysource def Test2 physics  

prod sel DedxConstProd
prod sel DedxReconProd
prod sel DedxInfoProd
#
# needed for monitoring:
prod sel DedxEventFlagProd
prod sel DedxEventSkimProd
#
echo " %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" 
echo " %  MCPASS2 DEDX SCRIPT DONE  %" 
echo " %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" 

#######################################################
