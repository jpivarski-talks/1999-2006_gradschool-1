default prompt off
exception continueEventLoop on

module sel HbookHistogramModule
hbook file ../rzn/test_positron_sb.rzn
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
prod sel EventTypeProd

#  proc sel EventTypeFilterProc
#  param EventTypeFilterProc Hadron true

#  proc sel ../build_SunOS/shlib/HadronFilterProc
#  param HadronFilterProc noBunchWeight true
#  param HadronFilterProc ntupleSize 100000
#  param HadronFilterProc noBeamSpot true
#  param HadronFilterProc fillBuffer false

proc sel ../build_SunOS/shlib/BigNTuple2
param BigNTuple2 getBunchData false
param BigNTuple2 interestingOnly false

source_format sel PDSSourceFormat

file in ../pds/positrons.pds event startrun beginrun endrun
go 25815
source rm positrons

hbook terminate
exit