default prompt off
exception continueEventLoop on

module sel HbookHistogramModule
hbook file /cdat/dafe/mccann/hadron_filter/rzn/before_pta_talk/ups3s_cont_ntuple2.rzn
hbook init

run_file $env(C3_SCRIPTS)/runOnPass2.tcl

prod sel DBEventHeaderProd
prod sel CesrBeamEnergyProd
prod sel EventPropertiesProd

module sel DBModule
database in /nfs/cleo3/database/data16/db event startrun beginrun endrun
database read_collection pass2 hadron

proc sel EventTypeFilterProc
param EventTypeFilterProc Hadron true

proc sel /cdat/daf9/mccann/hadron_filter/build_SunOS/shlib/BigNTuple2.so
param BigNTuple2 lookForCosmics false
param BigNTuple2 getBunchData false

database run 121899 121915
go

hbook terminate
exit
