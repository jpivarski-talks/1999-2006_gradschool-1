default prompt off

module sel HbookHistogramModule
hbook file /cdat/dafe/mccann/getradbhas_1.8.rzn
hbook init

run_file $env(C3_SCRIPTS)/runOnPass2.tcl
prod sel CesrBeamEnergyProd
proc sel ../build_SunOS/shlib/GetRadBhas

module sel DBModule
database in /nfs/cleo3/database/data22/db event startrun beginrun endrun
database read_collection pass2 bhagam
database run 127729 127740

go
source rm db

module sel DBModule
database in /nfs/cleo3/database/data22/db event startrun beginrun endrun
database read_collection pass2 bhagam
database run 127900 127905

go
source rm db

module sel DBModule
database in /nfs/cleo3/database/data22/db event startrun beginrun endrun
database read_collection pass2 bhagam
database run 128068 128069

go
exit
