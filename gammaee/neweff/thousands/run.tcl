default prompt off
exception continueEventLoop on

run_file $env(C3_SCRIPTS)/getNewestConstants.tcl
run_file $env(C3_SCRIPTS)/trackingDataFull.tcl
run_file $env(C3_SCRIPTS)/CcP2.tcl

prod sel CesrBeamEnergyProd
prod sel EventPropertiesProd
prod sel TrackShowerMatchingProd
prod sel TriggerDataProd
prod sel ../build_SunOS/shlib/StupidProd.so

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

proc sel L1TriggerSelectProc
param L1TriggerSelectProc TwoTrackKeep true
param L1TriggerSelectProc RandomKeep true
param L1TriggerSelectProc PulserKeep true

proc sel Level4Proc
param Level4Proc TagOnly true

module sel DBModule
database in /nfs/cleo3/database/data$env(USER_DB)/db event startrun beginrun endrun
database read_collection rawdata
database run $env(USER_RUN)

sink_format sel PDSSinkFormat
file out ../thpds/r$env(USER_RUN).pds {event{\
    DBTrackerValues FATable<TRTrack> FATable<TRHelixPionFit> FATable<TRPionQuality> FATable<TRSeedTrack> FATable<TRSeedTrackQuality>\
    FATable<CcBasicShowerAttsArg> TrackShowerLattice FATable<CcConRegAttributes> CcConRegShowerLattice\
    Stupid TriggerL1Data Level3TagWord Level4Decision\
    EventProperties DBEventHeader\
}} startrun beginrun endrun

go
