default prompt off
exception continueEventLoop on

module sel LoadHbook4MModule
module sel HbookHistogramModule
hbook file ../rzn5/trigger$env(USER_RUN).rzn
hbook init

run_file $env(C3_SCRIPTS)/getPass2Constants.tcl
run_file $env(C3_SCRIPTS)/trackingDataFull.tcl
run_file $env(C3_SCRIPTS)/CcP2.tcl

prod sel TriggerDataProd
prod sel CesrBeamEnergyProd
prod sel EventPropertiesProd
prod sel TrackShowerMatchingProd

param DRHitCorrectorProd ApplyEntranceAngleCorr $env(USER_EA)
param DRHitCorrectorProd ApplyStandardCorrections $env(USER_EA)
param KalmanProd HyposToFit pion
param KalmanProd OptimizeForAllHypos true
param KalmanProd HitListFromOneHypo true
param KalmanProd ScaleCathodeResolution true
param KalmanProd CathodeResolutionScale 0.7    

proc sel Level4Proc
param Level4Proc TagOnly true

module sel DBModule
database in /nfs/cleo3/database/data$env(USER_DB)/db event startrun beginrun endrun
database read_collection rawdata
database run $env(USER_RUN)

prod sel ../build_SunOS/shlib/TriggerInfoProd
proc sel ../build_SunOS/shlib/TriggerOnlyProc

sink_format sel PDSSinkFormat
file out ../rzn5/trigger$env(USER_RUN).pds {event{\
    TriggerL1Data TriggerInfo\
}} startrun beginrun endrun

go
exit
