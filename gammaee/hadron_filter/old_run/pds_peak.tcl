default prompt off
exception continueEventLoop on

module select LoadGeantModule

# run_file $env(C3_SCRIPTS)/getConstants.tcl
module sel CorbaModule
corba init
module sel ConstantsModule
constants in $env(C3_CONST) meta Online
constants in $env(C3_CONST) meta Offline MetaListRetrieval
constants in $env(C3_CONST) meta CesrOffset MetaListRetrieval
# constants in $env(C3_CONST) meta RunByRun MetaListRetrieval
constants in $env(C3_CONST) meta BaseGeometry MetaListRetrieval
constants in $env(C3_CONST) meta SVHybridEfficiency MetaListRetrieval
constants in $env(C3_CONST) meta Alignment MetaListRetrieval
# constants in $env(C3_CONST) meta FieldMap MetaListRetrieval

source_format sel AsciiSourceFormat
file in $env(C3_DATA)/material.asc basegeometry

module sel RunStatisticsSourceModule
runstatistics in

prod select MuConsProd

# source_format sel SVHybridEfficiencyFileSourceFormat
# file in normal.svhybridefficiency

#########################################################
# Load DR Geometry-------
	prod sel ADRGeomProd
	prod sel DRGeom

# Load Silicon and IR geometry-------
	prod sel ASiStorePro
	prod sel SiGeom
	prod sel IRGeomProd

# Load Raw data---
	prod sel RawDataProd

# Convert Raw cathode hits to DRCACorrectHits----
	prod sel DRCACorrectHitProd

# Cluster cathodes---
	prod sel DRCAClusterProd

# Make PreliminaryDRHits-----
#	prod sel PreliminaryDRHitProd

# Make CalibratedDRHits-----
	prod sel CalibratedDRHitProd

# Make Si Hits-----
#	prod sel CorrectedSVStripProd
	prod sel SiHitsProd

# Load the magnetic field----
	prod sel MagFieldProd

# CDOffCal
	prod sel ../build_$env(OS_NAME)/shlib/CDOffCal

# Get trigger information
	prod sel TriggerL1DataProd

# Get bunch decision
	prod sel TrackletBunchFinder

# Load Doit
	prod sel DoitProd
	param DoitProd ContinueIfHitsMissing true

# Load DRHitCorrections
	prod sel DRHitCorrectorProd
	 param DRHitCorrectorProd ApplyEntranceAngleCorr false           
         param DRHitCorrectorProd ApplyStandardCorrections false   

# Load Kalman fit
	prod sel ../build_$env(OS_NAME)/shlib/KalmanProd
# Set Kalman to only fit pion kaon and proton since that is all
#  we want store from Pass2
	param KalmanProd HyposToFit pion kaon proton
	param KalmanProd OptimizeForAllHypos true
        param KalmanProd HitListFromOneHypo true
	param KalmanProd ScaleCathodeResolution true 
	param KalmanProd CathodeResolutionScale 0.7     

# If someone requests electrons or muons, give them the pion fit
	prod sel ElectronFromPionFitProd
	prod sel MuonFromPionFitProd

# Set up NavTrack
	prod sel NavigationProd
	prod sel TrackDeliveryProd
	prod sel SeedToTRTrackProd
#########################################################

run_file $env(C3_SCRIPTS)/C3cc.tcl
prod sel CcfcReconProd
prod sel TrackShowerMatchingProd

prod sel MutrReconProd
prod sel MuConsProd
run_file $env(C3_SCRIPTS)/load_geometry_producers.tcl
run_file $env(C3_SCRIPTS)/load_dg_to_geant3_converter.tcl
prod sel MagFieldProd
prod sel RawDataProd

prod sel DBEventHeaderProd
prod sel DBRunHeaderProd
prod sel CesrBeamEnergyProd

source_format sel BinarySourceFormat
file in peak_123717.bin event beginrun startrun endrun
source act peak_123717 event beginrun startrun endrun

sink_format sel PDSSinkFormat
file sink ../dafedir/bug-free2_123717_peak.pds event beginrun startrun endrun

go
exit
