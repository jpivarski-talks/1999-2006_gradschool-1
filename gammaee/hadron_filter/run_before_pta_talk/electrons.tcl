default prompt off
exception continueEventLoop on

module sel HbookHistogramModule
hbook file ../rzn/electrons_cut2.rzn
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

proc sel EventTypeFilterProc
param EventTypeFilterProc Hadron true

proc sel ../build_SunOS/shlib/HadronFilterProc
param HadronFilterProc noBunchWeight true
param HadronFilterProc ntupleSize 10000
param HadronFilterProc noBeamSpot true

param HadronFilterProc fillBuffer false

source_format sel PDSSourceFormat

file in ../pds/electrons1.pds event startrun beginrun endrun
go 27980
source rm electrons1

file in ../pds/electrons2.pds event startrun beginrun endrun
go 30460
source rm electrons2

file in ../pds/electrons3.pds event startrun beginrun endrun
go 22297
source rm electrons3

file in ../pds/electrons4.pds event startrun beginrun endrun
go 10576

hbook terminate
exit
