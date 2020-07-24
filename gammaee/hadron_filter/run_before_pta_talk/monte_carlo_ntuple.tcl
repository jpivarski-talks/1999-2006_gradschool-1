default prompt off
exception continueEventLoop on

module sel HbookHistogramModule
hbook file /cdat/dafe/mccann/hadron_filter/rzn/before_pta_talk/monte_carlo_ntuple2.rzn
hbook init

module sel CorbaModule
corba init
module sel RunStatisticsSourceModule
runstatistics in
module sel ConstantsModule
constants in $env(C3_CONST) meta FieldMap MetaListRetrieval

source_format sel MagFudgeFileSourceFormat
file in normal.magfudge

prod sel NavigationProd
prod sel TrackDeliveryProd
prod sel C3ccProd
prod sel MagFieldProd
prod sel DBEventHeaderProd
prod sel CesrBeamEnergyProd
prod sel EventPropertiesProd

run_file goldmine.tcl

proc sel EventTypeFilterProc
param EventTypeFilterProc Hadron true

proc sel /home/mccann/hadron_filter/build_SunOS/shlib/BigNTuple2.so
param BigNTuple2 lookForCosmics false
param BigNTuple2 getBunchData false

report level NOTICE

go

hbook terminate
exit
