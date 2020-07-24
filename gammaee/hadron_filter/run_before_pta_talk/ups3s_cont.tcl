default prompt off
exception continueEventLoop on

module sel HbookHistogramModule
hbook file ../rzn/ups3s_cont_cut3.rzn
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

proc sel ../build_SunOS/shlib/HadronFilterProc
param HadronFilterProc noBunchWeight true
param HadronFilterProc ntupleSize 10000
param HadronFilterProc noBeamSpot false

database run 121899 121915
param HadronFilterProc fillBuffer true
go 1000
param HadronFilterProc fillBuffer false
go

database run 122080 122091
param HadronFilterProc fillBuffer true
go 1000
param HadronFilterProc fillBuffer false
go

hbook terminate
exit
