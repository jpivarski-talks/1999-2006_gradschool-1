default prompt off

module sel HbookHistogramModule
hbook file /cdat/tem/mccann/eff_mc2.rzn
hbook init

run_file $env(C3_SCRIPTS)/runOnPass2.tcl

prod sel CesrBeamEnergyProd
prod sel EventTypeProd
proc sel EventTypeFilterProc
param EventTypeFilterProc Tau true

proc sel ../build_SunOS/shlib/HitEfficiency

source_format sel PDSSourceFormat
run_file db21.tcl
run_file db23.tcl

go
exit
