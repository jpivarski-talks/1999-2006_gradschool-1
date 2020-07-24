module sel LoadHbook4MModule
module sel HbookHistogramModule
hbook file mademc/chisearch.rzn
hbook init

run_file /nfs/cleo3/Offline/rel/Dec10_03/src/SuezScripts/getMCConstants.tcl
run_file /nfs/cleo3/Offline/rel/Dec10_03/src/SuezScripts/runOnPass2.tcl 

source_format sel PDSSourceFormat
source create pdschain
file add pdschain mademc/db21_followup.pds physics event startrun beginrun endrun
file add pdschain mademc/db23_followup.pds physics event startrun beginrun endrun

proc sel ../build_SunOS/shlib/ChiSearch

go 2

