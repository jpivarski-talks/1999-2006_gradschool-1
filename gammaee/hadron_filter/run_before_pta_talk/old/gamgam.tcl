default prompt off
exception continueEventLoop on

run_file $env(C3_SCRIPTS)/getMCConstants.tcl
run_file $env(C3_SCRIPTS)/trackingMCFull.tcl

source_format sel PDSSourceFormat
file in /home/sialign/gamgam/with_purify.pds event startrun beginrun endrun

sink_format sel PDSSinkFormat
file sink ../rzn/gamgam.pds event startrun beginrun endrun

go 3000

exit
