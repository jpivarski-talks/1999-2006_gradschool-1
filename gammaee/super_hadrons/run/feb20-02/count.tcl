default prompt off
exception continueEventLoop on

module sel HbookHistogramModule
hbook file ../../rzn/count_$env(USER_RUN).rzn
hbook init

source_format sel BeamSpotFileSourceFormat
file in $env(C3_INFO)/data/beamspot.beamspot

run_file $env(C3_SCRIPTS)/runOnPass2.tcl

prod sel DBEventHeaderProd
prod sel CesrBeamEnergyProd
prod sel EventPropertiesProd

proc sel ../../build_SunOS/shlib/BeamGasFilterProc

module sel DBModule
database in /nfs/cleo3/database/data18/db event startrun beginrun endrun
database read_collection pass2 hadron
database run $env(USER_RUN)
go

hbook terminate
exit
