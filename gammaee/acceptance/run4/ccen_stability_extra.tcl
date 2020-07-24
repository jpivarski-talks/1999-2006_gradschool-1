default prompt off
exception continueEventLoop on

run_file $env(C3_SCRIPTS)/runOnPass2.tcl
prod sel CesrBeamEnergyProd
run_file $env(C3_SCRIPTS)/BeamSpot.tcl

proc sel ../build_SunOS/shlib/ReCuts2

module sel DBModule
database in /nfs/cleo3/database/data$env(USER_DB)/db event startrun beginrun endrun
database read_collection pass2 hadron
database run 124359 124377

go

database in /nfs/cleo3/database/data$env(USER_DB)/db event startrun beginrun endrun
database read_collection pass2 hadron
database run 124479 124527

go

database in /nfs/cleo3/database/data$env(USER_DB)/db event startrun beginrun endrun
database read_collection pass2 hadron
database run 124454 124477

go
exit
