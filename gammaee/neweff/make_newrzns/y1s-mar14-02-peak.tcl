default prompt off
exception continueEventLoop on

module sel HbookHistogramModule
hbook file ../newrzn/y1s-mar14-02-peak.rzn
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
database in /nfs/cleo3/database/data19/db event startrun beginrun endrun
database read_collection pass2 tau
database run 124671
go

module sel DBModule
database in /nfs/cleo3/database/data19/db event startrun beginrun endrun
database read_collection pass2 tau
database run 124672
go

module sel DBModule
database in /nfs/cleo3/database/data19/db event startrun beginrun endrun
database read_collection pass2 tau
database run 124673
go

module sel DBModule
database in /nfs/cleo3/database/data19/db event startrun beginrun endrun
database read_collection pass2 tau
database run 124674
go

module sel DBModule
database in /nfs/cleo3/database/data19/db event startrun beginrun endrun
database read_collection pass2 tau
database run 124675
go

module sel DBModule
database in /nfs/cleo3/database/data19/db event startrun beginrun endrun
database read_collection pass2 tau
database run 124676
go

module sel DBModule
database in /nfs/cleo3/database/data19/db event startrun beginrun endrun
database read_collection pass2 tau
database run 124677
go

module sel DBModule
database in /nfs/cleo3/database/data19/db event startrun beginrun endrun
database read_collection pass2 tau
database run 124679
go

module sel DBModule
database in /nfs/cleo3/database/data19/db event startrun beginrun endrun
database read_collection pass2 tau
database run 124680
go

module sel DBModule
database in /nfs/cleo3/database/data19/db event startrun beginrun endrun
database read_collection pass2 tau
database run 124681
go

module sel DBModule
database in /nfs/cleo3/database/data19/db event startrun beginrun endrun
database read_collection pass2 tau
database run 124684
go

module sel DBModule
database in /nfs/cleo3/database/data19/db event startrun beginrun endrun
database read_collection pass2 tau
database run 124685
go

module sel DBModule
database in /nfs/cleo3/database/data19/db event startrun beginrun endrun
database read_collection pass2 tau
database run 124687
go

module sel DBModule
database in /nfs/cleo3/database/data19/db event startrun beginrun endrun
database read_collection pass2 tau
database run 124688
go

module sel DBModule
database in /nfs/cleo3/database/data19/db event startrun beginrun endrun
database read_collection pass2 tau
database run 124690
go

module sel DBModule
database in /nfs/cleo3/database/data19/db event startrun beginrun endrun
database read_collection pass2 tau
database run 124691
go

module sel DBModule
database in /nfs/cleo3/database/data19/db event startrun beginrun endrun
database read_collection pass2 tau
database run 124699
go

module sel DBModule
database in /nfs/cleo3/database/data19/db event startrun beginrun endrun
database read_collection pass2 tau
database run 124701
go

module sel DBModule
database in /nfs/cleo3/database/data19/db event startrun beginrun endrun
database read_collection pass2 tau
database run 124702
go

module sel DBModule
database in /nfs/cleo3/database/data19/db event startrun beginrun endrun
database read_collection pass2 tau
database run 124704
go

module sel DBModule
database in /nfs/cleo3/database/data19/db event startrun beginrun endrun
database read_collection pass2 tau
database run 124705
go

module sel DBModule
database in /nfs/cleo3/database/data19/db event startrun beginrun endrun
database read_collection pass2 tau
database run 124706
go

module sel DBModule
database in /nfs/cleo3/database/data19/db event startrun beginrun endrun
database read_collection pass2 tau
database run 124707
go

module sel DBModule
database in /nfs/cleo3/database/data19/db event startrun beginrun endrun
database read_collection pass2 tau
database run 124708
go

module sel DBModule
database in /nfs/cleo3/database/data19/db event startrun beginrun endrun
database read_collection pass2 tau
database run 124709
go

module sel DBModule
database in /nfs/cleo3/database/data19/db event startrun beginrun endrun
database read_collection pass2 tau
database run 124712
go

module sel DBModule
database in /nfs/cleo3/database/data19/db event startrun beginrun endrun
database read_collection pass2 tau
database run 124713
go

module sel DBModule
database in /nfs/cleo3/database/data19/db event startrun beginrun endrun
database read_collection pass2 tau
database run 124714
go

module sel DBModule
database in /nfs/cleo3/database/data19/db event startrun beginrun endrun
database read_collection pass2 tau
database run 124716
go

module sel DBModule
database in /nfs/cleo3/database/data19/db event startrun beginrun endrun
database read_collection pass2 tau
database run 124718
go

module sel DBModule
database in /nfs/cleo3/database/data19/db event startrun beginrun endrun
database read_collection pass2 tau
database run 124719
go

module sel DBModule
database in /nfs/cleo3/database/data19/db event startrun beginrun endrun
database read_collection pass2 tau
database run 124711
go
