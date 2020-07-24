default prompt off
exception continueEventLoop on

module select LoadGeantModule
module select LoadHbookModule
module select HbookHistogramModule
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

param DRHitCorrectorProd ApplyEntranceAngleCorr $env(USER_EA)
param DRHitCorrectorProd ApplyStandardCorrections $env(USER_EA)
param KalmanProd HyposToFit pion
param KalmanProd OptimizeForAllHypos true
param KalmanProd HitListFromOneHypo true
param KalmanProd ScaleCathodeResolution true
param KalmanProd CathodeResolutionScale 0.7    

prod sel DBEventHeaderProd

proc sel /home/mccann/acceptance/build_$env(USER_REL)/shlib/CcenFailuresFilter
param CcenFailuresFilter ebeam $env(USER_EBEAM)

proc sel Level4Proc
param Level4Proc TagOnly true

proc sel /home/mccann/acceptance/build_$env(USER_REL)/shlib/CcenFailures
param CcenFailures run $env(USER_RUN)
param CcenFailures bsx $env(USER_BSX)
param CcenFailures bsy $env(USER_BSY)
param CcenFailures bsz $env(USER_BSZ)
param CcenFailures ebeam $env(USER_EBEAM)

module sel DBModule
database in /nfs/cleo3/database/data$env(USER_DB)/db event startrun beginrun endrun
database read_collection rawdata
database run $env(USER_RUN)

prod lss

go

exit

