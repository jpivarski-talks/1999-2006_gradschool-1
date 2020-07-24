default prompt off
exception continueEventLoop on

run_file $env(C3_SCRIPTS)/runOnPass2.tcl
prod sel CesrBeamEnergyProd
run_file $env(C3_SCRIPTS)/BeamSpot.tcl

proc sel /home/mccann/acceptance/build_SunOS/shlib/ReCuts

module sel DBModule
database in /nfs/cleo3/database/data$env(USER_DB)/db event startrun beginrun endrun
database read_collection pass2 tau

if {$env(USER_DB18) == "A"} {database run 123314 123944}
if {$env(USER_DB18) == "B"} {database run 123945 124575}

prod lss

go

exit
