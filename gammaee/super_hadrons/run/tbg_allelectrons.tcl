default prompt off
exception continueEventLoop on

module sel HbookHistogramModule
hbook file ../rzn/tbg_allelectrons_revamp2.rzn
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

file in /home/mccann/hadron_filter/pds/electrons1.pds event startrun beginrun endrun
go 27980
source rm electrons1

file in /home/mccann/hadron_filter/pds/electrons2.pds event startrun beginrun endrun
go 30460
source rm electrons2

file in /home/mccann/hadron_filter/pds/electrons3.pds event startrun beginrun endrun
go 22297
source rm electrons3

file in /home/mccann/hadron_filter/pds/electrons4.pds event startrun beginrun endrun
go 10576

hbook terminate
exit
