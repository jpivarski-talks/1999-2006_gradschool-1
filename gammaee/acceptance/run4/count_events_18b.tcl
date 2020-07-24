default prompt off
exception continueEventLoop on

run_file $env(C3_SCRIPTS)/runOnPass2.tcl
prod sel CesrBeamEnergyProd
run_file $env(C3_SCRIPTS)/BeamSpot.tcl

proc sel ../build_SunOS/shlib/ReCuts
param ReCuts mode 0

module sel DBModule
database in /nfs/cleo3/database/data$env(USER_DB)/db event startrun beginrun endrun
database read_collection pass2 tau
database run 123945 124575

go
exit
