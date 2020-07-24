default prompt off
exception continueEventLoop on

module sel HbookHistogramModule
hbook file /cdat/dafe/mccann/hadron_filter/rzn/before_pta_talk/positrons_ntuple_nhc2.rzn
hbook init

run_file $env(C3_SCRIPTS)/runOnPass2.tcl

prod sel NavigationProd
prod sel TrackDeliveryProd
prod sel C3ccProd
prod sel MagFieldProd
prod sel DBEventHeaderProd
prod sel CesrBeamEnergyProd
prod sel EventPropertiesProd
prod sel EventTypeProd

#  proc sel EventTypeFilterProc
#  param EventTypeFilterProc Hadron true

proc sel /home/mccann/hadron_filter/build_SunOS/shlib/BigNTuple2.so
param BigNTuple2 lookForCosmics false
param BigNTuple2 getBunchData false

source_format sel PDSSourceFormat

report level NOTICE

file in /home/mccann/hadron_filter/pds/positrons.pds event startrun beginrun endrun
go 25815
source rm positrons

hbook terminate
exit
