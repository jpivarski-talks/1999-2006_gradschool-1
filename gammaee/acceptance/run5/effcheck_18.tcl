default prompt off

module sel HbookHistogramModule
hbook file /cdat/tem/mccann/eff_18b.rzn
hbook init

run_file $env(C3_SCRIPTS)/runOnPass2.tcl
prod sel CesrBeamEnergyProd
proc sel ../build_SunOS/shlib/HitEfficiency

module sel DBModule
database in /nfs/cleo3/database/data18/db event startrun beginrun endrun
database read_collection pass2 tau
database run 123495 124575

go
exit
