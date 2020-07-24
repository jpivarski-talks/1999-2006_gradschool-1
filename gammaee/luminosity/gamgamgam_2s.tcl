module sel HbookHistogramModule
hbook file rzn5/gamgamgam_2s.rzn
hbook init

run_file $env(C3_SCRIPTS)/getMCConstants.tcl
run_file $env(C3_SCRIPTS)/runOnPass2.tcl

proc sel build_SunOS/shlib/ChiSearch.so

source_format sel PDSSourceFormat
source create pdschain
file add pdschain /cdat/dafe/mccann/synthesis/mc2chibkgnd/mcpass2_y2pho3_129535_db23.pds physics event startrun beginrun endrun
file add pdschain /cdat/dafe/mccann/synthesis/mc2chibkgnd/mcpass2_y2pho3_129536_db23.pds physics event startrun beginrun endrun
file add pdschain /cdat/dafe/mccann/synthesis/mc2chibkgnd/mcpass2_y2pho3_129538_db23.pds physics event startrun beginrun endrun
file add pdschain /cdat/dafe/mccann/synthesis/mc2chibkgnd/mcpass2_y2pho3_129539_db23.pds physics event startrun beginrun endrun
file add pdschain /cdat/dafe/mccann/synthesis/mc2chibkgnd/mcpass2_y2pho3_129540_db23.pds physics event startrun beginrun endrun
file add pdschain /cdat/dafe/mccann/synthesis/mc2chibkgnd/mcpass2_y2pho3_129541_db23.pds physics event startrun beginrun endrun
file add pdschain /cdat/dafe/mccann/synthesis/mc2chibkgnd/mcpass2_y2pho3_129545_db23.pds physics event startrun beginrun endrun

go
hbook terminate
exit
