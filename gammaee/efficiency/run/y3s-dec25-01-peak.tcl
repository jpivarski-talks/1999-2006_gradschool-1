default prompt off
exception continueEventLoop on

module sel HbookHistogramModule
hbook file /cdat/sol300/disk5/mccann/y3s-dec25-01-peak.rzn
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
database in /nfs/cleo3/database/data17/db event startrun beginrun endrun
database read_collection pass2 hadron
database run 122576
go

module sel DBModule
database in /nfs/cleo3/database/data17/db event startrun beginrun endrun
database read_collection pass2 hadron
database run 122577
go

module sel DBModule
database in /nfs/cleo3/database/data17/db event startrun beginrun endrun
database read_collection pass2 hadron
database run 122579
go

module sel DBModule
database in /nfs/cleo3/database/data17/db event startrun beginrun endrun
database read_collection pass2 hadron
database run 122608
go

module sel DBModule
database in /nfs/cleo3/database/data17/db event startrun beginrun endrun
database read_collection pass2 hadron
database run 122610
go

module sel DBModule
database in /nfs/cleo3/database/data17/db event startrun beginrun endrun
database read_collection pass2 hadron
database run 122613
go

module sel DBModule
database in /nfs/cleo3/database/data17/db event startrun beginrun endrun
database read_collection pass2 hadron
database run 122614
go

module sel DBModule
database in /nfs/cleo3/database/data17/db event startrun beginrun endrun
database read_collection pass2 hadron
database run 122615
go

module sel DBModule
database in /nfs/cleo3/database/data17/db event startrun beginrun endrun
database read_collection pass2 hadron
database run 122616
go

module sel DBModule
database in /nfs/cleo3/database/data17/db event startrun beginrun endrun
database read_collection pass2 hadron
database run 122618
go

module sel DBModule
database in /nfs/cleo3/database/data17/db event startrun beginrun endrun
database read_collection pass2 hadron
database run 122619
go

module sel DBModule
database in /nfs/cleo3/database/data17/db event startrun beginrun endrun
database read_collection pass2 hadron
database run 122620
go

module sel DBModule
database in /nfs/cleo3/database/data17/db event startrun beginrun endrun
database read_collection pass2 hadron
database run 122623
go

module sel DBModule
database in /nfs/cleo3/database/data17/db event startrun beginrun endrun
database read_collection pass2 hadron
database run 122625
go

module sel DBModule
database in /nfs/cleo3/database/data17/db event startrun beginrun endrun
database read_collection pass2 hadron
database run 122626
go

module sel DBModule
database in /nfs/cleo3/database/data17/db event startrun beginrun endrun
database read_collection pass2 hadron
database run 122628
go

module sel DBModule
database in /nfs/cleo3/database/data17/db event startrun beginrun endrun
database read_collection pass2 hadron
database run 122629
go

module sel DBModule
database in /nfs/cleo3/database/data17/db event startrun beginrun endrun
database read_collection pass2 hadron
database run 122630
go

module sel DBModule
database in /nfs/cleo3/database/data17/db event startrun beginrun endrun
database read_collection pass2 hadron
database run 122631
go

module sel DBModule
database in /nfs/cleo3/database/data17/db event startrun beginrun endrun
database read_collection pass2 hadron
database run 122632
go

module sel DBModule
database in /nfs/cleo3/database/data17/db event startrun beginrun endrun
database read_collection pass2 hadron
database run 122634
go

module sel DBModule
database in /nfs/cleo3/database/data17/db event startrun beginrun endrun
database read_collection pass2 hadron
database run 122640
go

module sel DBModule
database in /nfs/cleo3/database/data17/db event startrun beginrun endrun
database read_collection pass2 hadron
database run 122641
go

module sel DBModule
database in /nfs/cleo3/database/data17/db event startrun beginrun endrun
database read_collection pass2 hadron
database run 122642
go

module sel DBModule
database in /nfs/cleo3/database/data17/db event startrun beginrun endrun
database read_collection pass2 hadron
database run 122643
go

module sel DBModule
database in /nfs/cleo3/database/data17/db event startrun beginrun endrun
database read_collection pass2 hadron
database run 122646
go

module sel DBModule
database in /nfs/cleo3/database/data17/db event startrun beginrun endrun
database read_collection pass2 hadron
database run 122647
go

module sel DBModule
database in /nfs/cleo3/database/data17/db event startrun beginrun endrun
database read_collection pass2 hadron
database run 122648
go

module sel DBModule
database in /nfs/cleo3/database/data17/db event startrun beginrun endrun
database read_collection pass2 hadron
database run 122649
go

module sel DBModule
database in /nfs/cleo3/database/data17/db event startrun beginrun endrun
database read_collection pass2 hadron
database run 122650
go

module sel DBModule
database in /nfs/cleo3/database/data17/db event startrun beginrun endrun
database read_collection pass2 hadron
database run 122652
go

module sel DBModule
database in /nfs/cleo3/database/data17/db event startrun beginrun endrun
database read_collection pass2 hadron
database run 122653
go

module sel DBModule
database in /nfs/cleo3/database/data17/db event startrun beginrun endrun
database read_collection pass2 hadron
database run 122654
go

module sel DBModule
database in /nfs/cleo3/database/data17/db event startrun beginrun endrun
database read_collection pass2 hadron
database run 122657
go

module sel DBModule
database in /nfs/cleo3/database/data17/db event startrun beginrun endrun
database read_collection pass2 hadron
database run 122658
go

module sel DBModule
database in /nfs/cleo3/database/data17/db event startrun beginrun endrun
database read_collection pass2 hadron
database run 122661
go

module sel DBModule
database in /nfs/cleo3/database/data17/db event startrun beginrun endrun
database read_collection pass2 hadron
database run 122665
go

module sel DBModule
database in /nfs/cleo3/database/data17/db event startrun beginrun endrun
database read_collection pass2 hadron
database run 122667
go

module sel DBModule
database in /nfs/cleo3/database/data17/db event startrun beginrun endrun
database read_collection pass2 hadron
database run 122672
go

module sel DBModule
database in /nfs/cleo3/database/data17/db event startrun beginrun endrun
database read_collection pass2 hadron
database run 122673
go
