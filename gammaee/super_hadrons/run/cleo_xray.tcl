default prompt off
exception continueEventLoop on

module sel HbookHistogramModule
hbook file ../rzn/cleo_xray.rzn
hbook init

run_file $env(C3_SCRIPTS)/runOnPass2.tcl

prod sel DBEventHeaderProd
prod sel CesrBeamEnergyProd
prod sel EventPropertiesProd

#  proc sel ../build_SunOS/shlib/BeamGasFilterProc
#  param BeamGasFilterProc explicitBeamSpot true
#  param BeamGasFilterProc beamX -1e-3
#  param BeamGasFilterProc beamY 6e-4
#  param BeamGasFilterProc beamZ 0.

proc sel ../build_SunOS/shlib/CLEOXRay

module sel DBModule
database in /nfs/cleo3/database/data17/db event startrun beginrun endrun
database read_collection pass2 hadron
go 21600000

hbook terminate
exit
