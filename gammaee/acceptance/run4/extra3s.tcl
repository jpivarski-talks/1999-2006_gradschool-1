default prompt off
exception continueEventLoop on

module select LoadGeantModule
module select LoadHbookModule
module sel HbookHistogramModule
hbook file ../rzn4/raw$env(USER_RUN).rzn
hbook init
source_format sel AsciiSourceFormat
sink_format sel AsciiSinkFormat
run_file $env(C3_SCRIPTS)/getPass2Constants.tcl
run_file $env(C3_SCRIPTS)/trackingDataFull.tcl
prod sel MutrReconProd
prod sel MuConsProd
run_file $env(C3_SCRIPTS)/load_geometry_producers.tcl
run_file $env(C3_SCRIPTS)/load_dg_to_geant3_converter.tcl
prod sel MagFieldProd
prod sel RawDataProd
prod sel DBRunHeaderProd

run_file $env(C3_SCRIPTS)/CcP2.tcl

prod sel CesrBeamEnergyProd
prod sel EventPropertiesProd
prod sel TrackShowerMatchingProd

param DRHitCorrectorProd ApplyEntranceAngleCorr false
param DRHitCorrectorProd ApplyStandardCorrections false
param KalmanProd HyposToFit pion
param KalmanProd OptimizeForAllHypos true
param KalmanProd HitListFromOneHypo true
param KalmanProd ScaleCathodeResolution true
param KalmanProd CathodeResolutionScale 0.7    

proc sel Level4Proc
param Level4Proc TagOnly true

prod lss

module sel DBModule
database in /nfs/cleo3/database/data$env(USER_DB)/db event startrun beginrun endrun
database read_collection rawdata
database run $env(USER_RUN)

sink_format sel PDSSinkFormat
file out ../rzn4/raw$env(USER_RUN).pds {event{\
    DBTrackerValues FATable<TRTrack> FATable<TRHelixPionFit> FATable<TRPionQuality> FATable<TRSeedTrack> FATable<TRSeedTrackQuality>\
    FATable<CcBasicShowerAttsArg> TrackShowerLattice FATable<CcConRegAttributes> CcConRegShowerLattice\
    TriggerL1Data Level3TagWord Level4Decision\
    EventProperties DBEventHeader\
}} startrun beginrun endrun

go
exit
