default prompt off
exception continueEventLoop on

run_file $env(C3_SCRIPTS)/runOnPass2.tcl
prod sel EventPropertiesProd
prod sel CesrBeamEnergyProd
prod sel MagFieldProd
run_file $env(C3_SCRIPTS)/BeamSpot.tcl
run_file $env(C3_SCRIPTS)/RunInfo.tcl
param RunInfoProc MinBeamEnergy 4.72815
param RunInfoProc MaxBeamEnergy 4.73215

proc sel ../build_SunOS/shlib/KaonMonitorProc

module sel DBModule
database in /nfs/cleo3/database/data$env(USER_DB)/db event startrun beginrun endrun
database read_collection pass2 tau

go

