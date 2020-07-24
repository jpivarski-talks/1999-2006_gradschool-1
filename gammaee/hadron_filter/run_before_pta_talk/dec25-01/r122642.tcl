
default prompt off
exception continueEventLoop on

module sel HbookHistogramModule
hbook file rzn/r122642.rzn
hbook init

run_file $env(C3_SCRIPTS)/runOnPass2.tcl

prod sel DBEventHeaderProd
prod sel CesrBeamEnergyProd
prod sel EventPropertiesProd

module sel DBModule
database in /nfs/cleo3/database/data17/db event startrun beginrun endrun
database read_collection pass2 hadron
database run 122642

proc sel EventTypeFilterProc
param EventTypeFilterProc Hadron true

proc sel ../../build_SunOS/shlib/HadronFilterProc
param HadronFilterProc noBunchWeight true
param HadronFilterProc ntupleSize 50
param HadronFilterProc noBeamSpot true
param HadronFilterProc beamSpotX -0.001479129
param HadronFilterProc beamSpotY 0.0006187184

param HadronFilterProc fillBuffer false
go

hbook terminate
exit
