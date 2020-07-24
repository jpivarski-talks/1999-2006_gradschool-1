module sel HbookHistogramModule
hbook file rzn5/gamgamgam_3s.rzn
hbook init

run_file $env(C3_SCRIPTS)/getMCConstants.tcl
run_file $env(C3_SCRIPTS)/runOnPass2.tcl

proc sel build_SunOS/shlib/ChiSearch.so

source_format sel PDSSourceFormat
source create pdschain
file add pdschain /cdat/dafe/mccann/synthesis/mc2chibkgnd/mcpass2_y3pho3_121916_db16.pds physics event startrun beginrun endrun
file add pdschain /cdat/dafe/mccann/synthesis/mc2chibkgnd/mcpass2_y3pho3_121917_db16.pds physics event startrun beginrun endrun
file add pdschain /cdat/dafe/mccann/synthesis/mc2chibkgnd/mcpass2_y3pho3_121918_db16.pds physics event startrun beginrun endrun
file add pdschain /cdat/dafe/mccann/synthesis/mc2chibkgnd/mcpass2_y3pho3_121920_db16.pds physics event startrun beginrun endrun
file add pdschain /cdat/dafe/mccann/synthesis/mc2chibkgnd/mcpass2_y3pho3_121924_db16.pds physics event startrun beginrun endrun
file add pdschain /cdat/dafe/mccann/synthesis/mc2chibkgnd/mcpass2_y3pho3_121925_db16.pds physics event startrun beginrun endrun

go
hbook terminate
exit
