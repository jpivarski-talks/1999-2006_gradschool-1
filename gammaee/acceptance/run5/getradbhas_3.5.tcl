default prompt off

module sel HbookHistogramModule
hbook file /cdat/dafe/mccann/getradbhas_3.5.rzn
hbook init

run_file $env(C3_SCRIPTS)/runOnPass2.tcl
prod sel CesrBeamEnergyProd
proc sel ../build_SunOS/shlib/GetRadBhas

module sel DBModule
database in /nfs/cleo3/database/data22/db event startrun beginrun endrun
database read_collection pass2 bhagam
database run 128257 128269

go
source rm db

module sel DBModule
database in /nfs/cleo3/database/data22/db event startrun beginrun endrun
database read_collection pass2 bhagam
database run 128285 128298

go
exit
