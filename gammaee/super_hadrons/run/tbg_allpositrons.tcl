default prompt off
exception continueEventLoop on

module sel HbookHistogramModule
hbook file ../rzn/tbg_allpositrons_revamp2.rzn
hbook init

run_file $env(C3_SCRIPTS)/runOnPass2.tcl
run_file $env(C3_SCRIPTS)/CcHotList.tcl
run_file $env(C3_SCRIPTS)/BeamSpot.tcl

prod sel DBEventHeaderProd
prod sel CesrBeamEnergyProd
prod sel EventPropertiesProd

proc sel ../build_SunOS/shlib/BeamGasFilterProc
param BeamGasFilterProc explicitBeamSpot true
param BeamGasFilterProc weightedZCut 1.
param BeamGasFilterProc neutralEnergyCut -1.

proc sel ../build_SunOS/shlib/TestBeamGas
param TestBeamGas explicitBeamSpot true
param TestBeamGas weightedZCut 1.

source_format sel PDSSourceFormat

file in /home/mccann/hadron_filter/pds/positrons.pds event startrun beginrun endrun
go 25815

hbook terminate
exit
