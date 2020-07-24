default prompt off
exception continueEventLoop on

module sel HbookHistogramModule
hbook file ../../rzn/before_improved_zcut/cont_data_zeros_rebin3.rzn
hbook init

run_file $env(C3_SCRIPTS)/runOnPass2.tcl

prod sel DBEventHeaderProd
prod sel CesrBeamEnergyProd
prod sel EventPropertiesProd

proc sel EventTypeFilterProc
param EventTypeFilterProc Hadron true

proc sel ../../build_SunOS/shlib/HadronFilterProc
param HadronFilterProc noBunchWeight true
param HadronFilterProc ntupleSize 100000
param HadronFilterProc noBeamSpot true
param HadronFilterProc beamSpotX -1e-3
param HadronFilterProc beamSpotY 6e-4
param HadronFilterProc fillBuffer false
param HadronFilterProc applyNeutralEnergyCut true
param HadronFilterProc chargeConstraint 50.

module sel DBModule
database in /nfs/cleo3/database/data17/db event startrun beginrun endrun
database read_collection pass2 hadron
database run 122585
go 1

hbook terminate
exit
