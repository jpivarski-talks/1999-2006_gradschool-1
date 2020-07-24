default prompt off
exception continueEventLoop on

run_file $env(C3_SCRIPTS)/getNewestConstants.tcl
run_file $env(C3_SCRIPTS)/trackingDataFull.tcl

run_file $env(C3_SCRIPTS)/CcP2.tcl
prod sel TrackShowerMatchingProd
prod sel EventPropertiesProd
prod sel EventTypeProd
prod sel CesrBeamEnergyProd

module sel DBModule
database in /nfs/objy/data14b/db event startrun beginrun endrun
database read_collection rawdata

proc sel ../build_SunOS/before_BigErrorMatrix_bug/shlib/TrackShowerEfficiency.so

prod lss

go


