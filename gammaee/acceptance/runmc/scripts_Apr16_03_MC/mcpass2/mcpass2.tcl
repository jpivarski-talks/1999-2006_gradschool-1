###########################################
# file: $C3_SCRIPTS/mcpass2/mcpass2.tcl
#
# purpose: run full pass2 on Monte Carlo 
#
# can be executed using 
# $C3_SCRIPTS/mcpass2/runpass2.tcl
#
###########################################

module sel RandomModule
random create

module select LoadGeantModule
module select LoadHbookModule
module select HbookHistogramModule
hbook init

# set up all constants 
run_file $env(C3_SCRIPTS)/getMCPass2_3Constants.tcl

# event selection algorithms
run_file $env(C3_SCRIPTS)/mcpass2/filter_mcpass2.tcl

# monitor output
run_file $env(C3_SCRIPTS)/mcpass2/monitor_mcpass2.tcl

# pass2 producers
run_file $env(C3_SCRIPTS)/mcpass2/producers_mcpass2.tcl 

# for use of MC tagging information
prod sel MCTagHolderProd

# pull in storage helpers for Response objects
prod sel MCRawDataProd
prod desel MCRawDataProd

# cleog ran already PreliminaryDRHitProd, CalibratedDRHitProd,
# DRCACorrectHitProd, CorrectedSVStripProd, SiHitsProd, 
# RichCalibratedHits, C3ccReconProd, TrackletBunchFinder
# trackingMCFull deselected already the first five  
prod desel RichCalibratedHits
prod desel C3ccReconProd

#pull in storage helpers for MC objects
# prod sel   MCSymmetricBeamProd
# prod desel MCSymmetricBeamProd
# prod sel   MCTriggerPhaseProd
# prod desel MCTriggerPhaseProd

#######################################################
