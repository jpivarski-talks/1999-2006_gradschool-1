default prompt off
exception continueEventLoop on

run_file $env(C3_SCRIPTS)/getNewestConstants.tcl
run_file $env(C3_SCRIPTS)/trackingDataFull.tcl

run_file $env(C3_SCRIPTS)/C3cc.tcl
prod sel DBEventHeaderProd
prod sel CcP2ReconProd
prod sel TrackShowerMatchingProd

module sel DBModule
database in /nfs/cleo3/database/data21/db event startrun beginrun endrun
database read_collection rawdata
database run 126785

proc sel ../build_SunOS/shlib/DiagnoseTrackMatching

go
