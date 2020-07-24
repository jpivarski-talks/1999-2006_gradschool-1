default prompt off
exception continueEventLoop on

source_format sel PDSSourceFormat
run_file ldmc_y1ggg_db18.tcl

prod sel CesrBeamEnergyProd

run_file $env(C3_SCRIPTS)/runOnPass2.tcl
proc sel ../build_SunOS/shlib/LookForWierdTrigger
# run_file $env(C3_SCRIPTS)/viewMCPass2.tcl

report level EMERGENCY
go
hbook terminate
exit
