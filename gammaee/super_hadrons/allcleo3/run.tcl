default prompt off
exception continueEventLoop on

module sel HbookHistogramModule
hbook file dafedir/db$env(USER_DB).rzn
hbook init

source_format sel BeamSpotFileSourceFormat
file in $env(C3_INFO)/data/beamspot.beamspot

run_file $env(C3_SCRIPTS)/runOnPass2.tcl

prod sel DBEventHeaderProd
prod sel CesrBeamEnergyProd
prod sel EventPropertiesProd

proc sel ../build_SunOS/shlib/BeamGasFilterProc
param BeamGasFilterProc noExplaination true
param BeamGasFilterProc cumulativeFrequency 10000.

module sel DBModule
database in /nfs/cleo3/database/data$env(USER_DB)/db event startrun beginrun endrun
database read_collection pass2 hadron
go

hbook terminate
exit
