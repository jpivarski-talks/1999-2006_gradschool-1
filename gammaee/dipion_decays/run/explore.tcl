default prompt off
exception continueEventLoop on

module sel HbookHistogramModule
hbook file ../rzn/explore.rzn
hbook init

run_file $env(C3_SCRIPTS)/runOnPass2.tcl

prod sel DBEventHeaderProd
prod sel CesrBeamEnergyProd
prod sel EventPropertiesProd

run_file $env(C3_SCRIPTS)/RunInfo.tcl
param RunInfoProc MinBeamEnergy 5.1765
param RunInfoProc MaxBeamEnergy 5.1815

proc sel ../build_SunOS/shlib/NeutralPions

module sel DBModule
database in /nfs/cleo3/database/data16/db event startrun beginrun endrun
database read_collection pass2 hadron
go

source rm db
module sel DBModule
database in /nfs/cleo3/database/data17/db event startrun beginrun endrun
database read_collection pass2 hadron
go

source rm db
module sel DBModule
database in /nfs/cleo3/database/data22/db event startrun beginrun endrun
database read_collection pass2 hadron
go

hbook terminate
exit
