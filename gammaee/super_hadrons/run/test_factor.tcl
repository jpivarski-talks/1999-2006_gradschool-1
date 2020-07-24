default prompt off
exception continueEventLoop on

module sel HbookHistogramModule
hbook file ../rzn/tf_$env(USER_RUN).rzn
hbook init

run_file $env(C3_SCRIPTS)/runOnPass2.tcl

prod sel DBEventHeaderProd
prod sel CesrBeamEnergyProd
prod sel EventPropertiesProd

proc sel ../build_SunOS/shlib/BeamGasFilterProc
param BeamGasFilterProc explicitBeamSpot true
param BeamGasFilterProc beamX -1e-3
param BeamGasFilterProc beamY 6e-4
param BeamGasFilterProc beamZ 0.

proc sel ../build_SunOS/shlib/TestFactor

module sel DBModule
database in /nfs/cleo3/database/data$env(USER_DB)/db event startrun beginrun endrun
database read_collection pass2 hadron
database run $env(USER_RUN)

go

hbook terminate
exit
