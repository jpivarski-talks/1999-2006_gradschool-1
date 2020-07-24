default prompt off
exception continueEventLoop on

module sel LoadHbook4MModule
module sel HbookHistogramModule
hbook file ../rzn3/hsc$env(USER_RUN).rzn
hbook init

run_file $env(C3_SCRIPTS)/runOnPass2.tcl
prod sel CesrBeamEnergyProd
run_file $env(C3_SCRIPTS)/BeamSpot.tcl

proc sel ../build_SunOS/shlib/Cuts
param Cuts mcInfo false
param Cuts triggerInfo false

module sel DBModule
database in /nfs/cleo3/database/data$env(USER_DB)/db event startrun beginrun endrun
database read_collection pass2 hadron
database run $env(USER_RUN)

sink_format sel IndexAsciiSinkFormat
file sink ../idxa/r$env(USER_RUN).idxa event

go
exit
