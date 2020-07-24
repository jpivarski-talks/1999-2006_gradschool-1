# This is a sample script that does tracking on real data.
#   It does the following:
#
#      o Load necessary constants
#      o Load tracking packages
#      o Load Event selection (Bha-bhas are the default)
#
#   The script in your area should probably look like what you see below.
#
#  $Id: sampleTrackingOnData.tcl,v 1.2 2000/06/22 15:25:36 lyon Exp $
#
#  $Log: sampleTrackingOnData.tcl,v $
#  Revision 1.2  2000/06/22 15:25:36  lyon
#  Fix typo
#
#  Revision 1.1  2000/06/22 15:06:27  lyon
#  Restructured tracking scripts
#
#

# Load histogram stuff
module sel HbookHistogramModule
hbook init

# Load constants
run_file $env(C3_SCRIPTS)/getConstants.tcl

# Load tracking packages for running on data with full Doit/Kalman
run_file $env(C3_SCRIPTS)/trackingDataFull.tcl

# Load CC stuff for event selection
prod sel CcfcReconProd
prod sel C3ccReconProd
proc sel CcEventSelectProc
prod sel C3ccProd
prod sel CcGeomProd
prod sel C3ccConProd

# What kind of events do you want?
param CcEventSelectProc BhabhaKeep true
#param CcEventSelectProc GamGamKeep true
#param CcEventSelectProc HadronKeep true
#param CcEventSelectProc MuPairKeep true    
#param CcEventSelectProc BarrelBhabhaKeep true
#param CcEventSelectProc BarrelGamGamKeep true
#param CcEventSelectProc EndcapBhabhaKeep true
#param CcEventSelectProc EndcapGamgamKeep true
#param CcEventSelectProc BarrelRadBhaGamKeep true
#param CcEventSelectProc EndcapRadBhaGamKeep true

# !!!!!!! Put your processor here !!!!!!!!!
#proc sel MyProcessor


# !!!!!!! Load in the file here !!!!!!!
#source_format sel BinarySourceFormat
#file in /cdat/sol300/disk4/cleo3/data/r105771.bin beginrun event endrun


# Uncomment these to do the event display
#proc sel SpExtractStandAloneGeomProc
#proc sel SpExtractDRHitsProc
#proc sel SpExtractSeedTrackProc
#proc sel SpExtractKinePionFitProc
#proc sel SpExtractDBEventHeaderProc
#proc sel SpViewerProc
