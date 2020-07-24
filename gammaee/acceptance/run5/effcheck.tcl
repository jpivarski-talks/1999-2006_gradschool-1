default prompt off

module sel HbookHistogramModule
hbook file /cdat/tem/mccann/eff_$env(USER_DB).rzn
hbook init

run_file $env(C3_SCRIPTS)/runOnPass2.tcl
prod sel CesrBeamEnergyProd
proc sel ../build_SunOS/shlib/HitEfficiency

module sel DBModule
database in /nfs/cleo3/database/data$env(USER_DB)/db event startrun beginrun endrun
database read_collection pass2 tau

go
exit
