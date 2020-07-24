default prompt off

run_file $env(C3_SCRIPTS)/getConstants.tcl
run_file $env(C3_SCRIPTS)/trackingDataFull.tcl
run_file $env(C3_SCRIPTS)/CcP2.tcl
prod sel TrackShowerMatchingProd
prod sel DBEventHeaderProd
prod sel CesrBeamEnergyProd
prod sel TriggerDataProd
prod sel EventPropertiesProd
proc sel ../build_SunOS/shlib/HitEfficiency

module sel DBModule
database in /nfs/cleo3/database/data18/db event startrun beginrun endrun
database read_collection rawdata
database run 123370

go
