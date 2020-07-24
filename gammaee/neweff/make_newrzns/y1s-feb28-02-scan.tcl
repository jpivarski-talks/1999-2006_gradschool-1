default prompt off
exception continueEventLoop on

module sel HbookHistogramModule
hbook file ../newrzn/y1s-feb28-02-scan.rzn
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
database in /nfs/cleo3/database/data18/db event startrun beginrun endrun
database read_collection pass2 tau
database run 124281
go

module sel DBModule
database in /nfs/cleo3/database/data18/db event startrun beginrun endrun
database read_collection pass2 tau
database run 124282
go

module sel DBModule
database in /nfs/cleo3/database/data18/db event startrun beginrun endrun
database read_collection pass2 tau
database run 124289
go

module sel DBModule
database in /nfs/cleo3/database/data18/db event startrun beginrun endrun
database read_collection pass2 tau
database run 124290
go

module sel DBModule
database in /nfs/cleo3/database/data18/db event startrun beginrun endrun
database read_collection pass2 tau
database run 124291
go

module sel DBModule
database in /nfs/cleo3/database/data18/db event startrun beginrun endrun
database read_collection pass2 tau
database run 124293
go

module sel DBModule
database in /nfs/cleo3/database/data18/db event startrun beginrun endrun
database read_collection pass2 tau
database run 124294
go

module sel DBModule
database in /nfs/cleo3/database/data18/db event startrun beginrun endrun
database read_collection pass2 tau
database run 124296
go

module sel DBModule
database in /nfs/cleo3/database/data18/db event startrun beginrun endrun
database read_collection pass2 tau
database run 124327
go
