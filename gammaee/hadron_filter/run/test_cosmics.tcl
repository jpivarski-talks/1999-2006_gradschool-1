default prompt off
exception continueEventLoop on

module sel HbookHistogramModule
hbook file ../rzn/test_cosmics.rzn
hbook init

module sel CorbaModule
corba init
module sel RunStatisticsSourceModule
runstatistics in
module sel ConstantsModule
constants in $env(C3_CONST) meta FieldMap MetaListRetrieval

source_format sel MagFudgeFileSourceFormat
file in normal.magfudge

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

#  proc sel ../build_SunOS/shlib/HadronFilterProc
#  param HadronFilterProc noBunchWeight true
#  param HadronFilterProc ntupleSize 100000
#  param HadronFilterProc noBeamSpot true
#  param HadronFilterProc fillBuffer false

proc sel ../build_SunOS/shlib/BigNTuple2
param BigNTuple2 getBunchData false
param BigNTuple2 interestingOnly true

source_format sel PDSSourceFormat

file in ../pds/gencos1.pds event startrun beginrun endrun
go
source rm gencos1

report level NOTICE

file in ../pds/gencos2.pds event startrun beginrun endrun
go
source rm gencos2

file in ../pds/gencos3.pds event startrun beginrun endrun
go
source rm gencos3

file in ../pds/gencos4.pds event startrun beginrun endrun
go
source rm gencos4

file in ../pds/gencos5.pds event startrun beginrun endrun
go
source rm gencos5

file in ../pds/gencos6.pds event startrun beginrun endrun
go
source rm gencos6

file in ../pds/gencos7.pds event startrun beginrun endrun
go
source rm gencos7

hbook terminate
exit
