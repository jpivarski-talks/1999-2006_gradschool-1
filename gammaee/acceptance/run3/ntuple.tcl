default prompt off
exception continueEventLoop on

module sel LoadHbook4MModule
module sel HbookHistogramModule
hbook file ../rzn3/raw$env(USER_RUN).rzn
hbook init

run_file $env(C3_SCRIPTS)/runOnPass2.tcl
prod sel CesrBeamEnergyProd
run_file $env(C3_SCRIPTS)/BeamSpot.tcl

proc sel ../build_SunOS/shlib/Cuts
param Cuts mcInfo false
param Cuts triggerInfo false

source_format sel PDSSourceFormat
file in ../rzn3/raw$env(USER_RUN).pds event beginrun startrun endrun

go
exit
