default prompt off
exception continueEventLoop on

module sel HbookHistogramModule
hbook file dafedir/plots$env(USER_RUN).rzn
hbook init

run_file $env(C3_SCRIPTS)/runOnPass2.tcl
prod sel CesrBeamEnergyProd
run_file $env(C3_SCRIPTS)/BeamSpot.tcl

proc sel /home/mccann/acceptance/build_SunOS/shlib/CountEvents
param CountEvents run $env(USER_RUN)

module sel DBModule
database in /nfs/cleo3/database/data$env(USER_DB)/db event startrun beginrun endrun
database read_collection pass2 tau
database run $env(USER_RUN)

prod lss

go

exit
