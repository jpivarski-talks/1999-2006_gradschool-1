default prompt off
exception continueEventLoop on

module sel HbookHistogramModule
hbook file /cdat/sol300/disk5/mccann/y1s-feb06-02-scan.rzn
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

proc sel ../build_SunOS/shlib/TrackEfficiency.so
param TrackEfficiency isMC false

module sel DBModule
database in /nfs/cleo3/database/data18/db event startrun beginrun endrun
database read_collection pass2 hadron
database run 123781
go

module sel DBModule
database in /nfs/cleo3/database/data18/db event startrun beginrun endrun
database read_collection pass2 hadron
database run 123782
go

module sel DBModule
database in /nfs/cleo3/database/data18/db event startrun beginrun endrun
database read_collection pass2 hadron
database run 123783
go

module sel DBModule
database in /nfs/cleo3/database/data18/db event startrun beginrun endrun
database read_collection pass2 hadron
database run 123784
go

module sel DBModule
database in /nfs/cleo3/database/data18/db event startrun beginrun endrun
database read_collection pass2 hadron
database run 123786
go

module sel DBModule
database in /nfs/cleo3/database/data18/db event startrun beginrun endrun
database read_collection pass2 hadron
database run 123787
go

module sel DBModule
database in /nfs/cleo3/database/data18/db event startrun beginrun endrun
database read_collection pass2 hadron
database run 123789
go

module sel DBModule
database in /nfs/cleo3/database/data18/db event startrun beginrun endrun
database read_collection pass2 hadron
database run 123790
go

module sel DBModule
database in /nfs/cleo3/database/data18/db event startrun beginrun endrun
database read_collection pass2 hadron
database run 123792
go
