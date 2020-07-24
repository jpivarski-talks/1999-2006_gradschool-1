default prompt off
exception continueEventLoop on

module select LoadHbook4MModule
module sel HbookHistogramModule
hbook file ../rzn/twopions.rzn
hbook init

run_file $env(C3_SCRIPTS)/runOnPass2.tcl

module sel DBModule
database in /nfs/cleo3/database/data16/db event startrun beginrun endrun
database read_collection pass2 hadron
database run 121916 121932

proc sel ../build_SunOS/shlib/TwoPionsProc

param TwoPionsProc fillBuffer true
go 1000
param TwoPionsProc fillBuffer false
go

hbook terminate
exit

