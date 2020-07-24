default prompt off
exception continueEventLoop on

module sel LoadHbook4MModule
module sel HbookHistogramModule
hbook file ../../data_method_rzn/sample/r129864.rzn
hbook init

run_file $env(C3_SCRIPTS)/getNewestConstants.tcl
run_file $env(C3_SCRIPTS)/trackingDataFull.tcl
run_file $env(C3_SCRIPTS)/CcP2.tcl

prod sel CesrBeamEnergyProd
prod sel EventPropertiesProd
prod sel TrackShowerMatchingProd

param DRHitCorrectorProd ApplyEntranceAngleCorr true
param DRHitCorrectorProd ApplyStandardCorrections true
param KalmanProd HyposToFit pion
param KalmanProd OptimizeForAllHypos true
param KalmanProd HitListFromOneHypo true
param KalmanProd ScaleCathodeResolution true
param KalmanProd CathodeResolutionScale 0.7    
param DetectorConfigurationProd UseZDnotSI false

run_file $env(C3_SCRIPTS)/CcHotList.tcl
source_format sel BeamSpotFileSourceFormat
file in $env(C3_INFO)/data/beamspot.beamspot beginrun

proc sel Level4Proc
param Level4Proc TagOnly true
proc sel ../../build_SunOS/shlib/DuperCuts

source_format sel BinarySourceFormat
file in /cdat/sol191/disk1/cleo3/data/r129864.bin event startrun beginrun endrun

sink_format sel PDSSinkFormat
file out ../../data_method_rzn/sample/r129864.pds {event{\
    DBTrackerValues FATable<TRTrack> FATable<TRHelixPionFit> FATable<TRPionQuality> FATable<TRSeedTrack> FATable<TRSeedTrackQuality>\
    FATable<CcBasicShowerAttsArg> TrackShowerLattice FATable<CcConRegAttributes> CcConRegShowerLattice\
    TriggerL1Data Level3TagWord Level4Decision\
    EventProperties DBEventHeader\
}} startrun beginrun endrun

go
