default prompt off
exception continueEventLoop on

run_file $env(C3_SCRIPTS)/runOnPass2.tcl
prod sel EventPropertiesProd
prod sel CesrBeamEnergyProd

proc sel ../build_SunOS/shlib/LumiRunCheck

module sel DBModule
database in /nfs/cleo3/database/data$env(USER_DB)/db event startrun beginrun endrun
database read_collection pass2 bhagam
database run $env(USER_START) $env(USER_STOP)

go
exit
