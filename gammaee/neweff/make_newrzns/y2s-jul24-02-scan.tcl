default prompt off
exception continueEventLoop on

module sel HbookHistogramModule
hbook file ../newrzn/y2s-jul24-02-scan.rzn
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
database in /nfs/cleo3/database/data22/db event startrun beginrun endrun
database read_collection pass2 tau
database run 127924
go

module sel DBModule
database in /nfs/cleo3/database/data22/db event startrun beginrun endrun
database read_collection pass2 tau
database run 127925
go

module sel DBModule
database in /nfs/cleo3/database/data22/db event startrun beginrun endrun
database read_collection pass2 tau
database run 127927
go

module sel DBModule
database in /nfs/cleo3/database/data22/db event startrun beginrun endrun
database read_collection pass2 tau
database run 127928
go

module sel DBModule
database in /nfs/cleo3/database/data22/db event startrun beginrun endrun
database read_collection pass2 tau
database run 127931
go

module sel DBModule
database in /nfs/cleo3/database/data22/db event startrun beginrun endrun
database read_collection pass2 tau
database run 127932
go

module sel DBModule
database in /nfs/cleo3/database/data22/db event startrun beginrun endrun
database read_collection pass2 tau
database run 127933
go

module sel DBModule
database in /nfs/cleo3/database/data22/db event startrun beginrun endrun
database read_collection pass2 tau
database run 127958
go

module sel DBModule
database in /nfs/cleo3/database/data22/db event startrun beginrun endrun
database read_collection pass2 tau
database run 127959
go

module sel DBModule
database in /nfs/cleo3/database/data22/db event startrun beginrun endrun
database read_collection pass2 tau
database run 127961
go

module sel DBModule
database in /nfs/cleo3/database/data22/db event startrun beginrun endrun
database read_collection pass2 tau
database run 127962
go

module sel DBModule
database in /nfs/cleo3/database/data22/db event startrun beginrun endrun
database read_collection pass2 tau
database run 127963
go
