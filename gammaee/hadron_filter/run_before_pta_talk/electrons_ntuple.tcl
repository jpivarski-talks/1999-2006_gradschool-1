default prompt off
exception continueEventLoop on

module sel HbookHistogramModule
hbook file /cdat/dafe/mccann/hadron_filter/rzn/before_pta_talk/electrons_ntuple_nhc2.rzn
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

file in /home/mccann/hadron_filter/pds/electrons1.pds event startrun beginrun endrun
go 27980
source rm electrons1

file in /home/mccann/hadron_filter/pds/electrons2.pds event startrun beginrun endrun
go 30460
source rm electrons2

file in /home/mccann/hadron_filter/pds/electrons3.pds event startrun beginrun endrun
go 22297
source rm electrons3

file in /home/mccann/hadron_filter/pds/electrons4.pds event startrun beginrun endrun
go 10576

hbook terminate
exit

