default prompt off

module sel HbookHistogramModule
hbook file /cdat/tem/mccann/eff_mc3.rzn
hbook init

run_file $env(C3_SCRIPTS)/runOnPass2.tcl

prod sel CesrBeamEnergyProd
prod sel EventTypeProd
proc sel EventTypeFilterProc
param EventTypeFilterProc Tau true

proc sel ../build_SunOS/shlib/HitEfficiency

source_format sel PDSSourceFormat
run_file db16.tcl
run_file db17.tcl

go
exit
