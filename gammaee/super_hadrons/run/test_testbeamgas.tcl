default prompt off
exception continueEventLoop on

module sel HbookHistogramModule
hbook file ../rzn/test_testbeamgas2.rzn
hbook init

run_file $env(C3_SCRIPTS)/runOnPass2.tcl
run_file $env(C3_SCRIPTS)/CcHotList.tcl
run_file $env(C3_SCRIPTS)/BeamSpot.tcl

prod sel DBEventHeaderProd
prod sel CesrBeamEnergyProd
prod sel EventPropertiesProd

proc sel ../build_SunOS/shlib/BeamGasFilterProc
param BeamGasFilterProc explicitBeamSpot false
param BeamGasFilterProc weightedZCut 0.15
param BeamGasFilterProc neutralEnergyCut -1.

proc sel ../build_SunOS/shlib/TestBeamGas
param TestBeamGas explicitBeamSpot false
param TestBeamGas weightedZCut 0.15

module sel DBModule
database in /nfs/cleo3/database/data17/db event startrun beginrun endrun
database read_collection pass2 hadron
database run 122585

go

hbook terminate
exit
