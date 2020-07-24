default prompt off
exception continueEventLoop on

module sel LoadHbook4MModule
module sel HbookHistogramModule
hbook file ../rzncascades/$env(USER_NAME).rzn
hbook init

run_file $env(C3_SCRIPTS)/runOnPass2.tcl
prod sel EventPropertiesProd
prod sel CesrBeamEnergyProd
prod sel MagFieldProd

run_file $env(C3_SCRIPTS)/BeamSpot.tcl
run_file $env(C3_SCRIPTS)/RunInfo.tcl
param RunInfoProc MinBeamEnergy 5.0120
param RunInfoProc MaxBeamEnergy 5.0135

proc sel ../build_SunOS/shlib/Cascades

module sel DBModule
database in /nfs/cleo3/database/data$env(USER_DB)/db event startrun beginrun endrun
database read_collection pass2 tau
database run $env(USER_RUNMIN) $env(USER_RUNMAX)

go
hbook terminate
exit
