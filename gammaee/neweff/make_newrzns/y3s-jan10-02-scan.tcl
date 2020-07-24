default prompt off
exception continueEventLoop on

module sel HbookHistogramModule
hbook file ../newrzn/y3s-jan10-02-scan.rzn
hbook init

run_file $env(C3_SCRIPTS)/runOnPass2.tcl

prod sel EventPropertiesProd
prod sel EventTypeProd
prod sel CesrBeamEnergyProd
prod sel DBEventHeaderProd

prod sel MCInfoDelivery
prod desel MCInfoDelivery
prod sel MCTagHolderProd
prod desel MCTagHolderProd

source_format sel BeamSpotFileSourceFormat
file in $env(C3_INFO)/data/beamspot.beamspot beginrun

proc sel ../build_SunOS/shlib/Efficiency.so
param Efficiency isMC false

module sel DBModule
database in /nfs/cleo3/database/data17/db event startrun beginrun endrun
database read_collection pass2 tau
database run 122993
go

module sel DBModule
database in /nfs/cleo3/database/data17/db event startrun beginrun endrun
database read_collection pass2 tau
database run 122995
go

module sel DBModule
database in /nfs/cleo3/database/data17/db event startrun beginrun endrun
database read_collection pass2 tau
database run 122996
go

module sel DBModule
database in /nfs/cleo3/database/data17/db event startrun beginrun endrun
database read_collection pass2 tau
database run 122998
go

module sel DBModule
database in /nfs/cleo3/database/data17/db event startrun beginrun endrun
database read_collection pass2 tau
database run 122999
go

module sel DBModule
database in /nfs/cleo3/database/data17/db event startrun beginrun endrun
database read_collection pass2 tau
database run 123001
go

module sel DBModule
database in /nfs/cleo3/database/data17/db event startrun beginrun endrun
database read_collection pass2 tau
database run 123002
go

module sel DBModule
database in /nfs/cleo3/database/data17/db event startrun beginrun endrun
database read_collection pass2 tau
database run 123003
go

module sel DBModule
database in /nfs/cleo3/database/data17/db event startrun beginrun endrun
database read_collection pass2 tau
database run 123004
go
