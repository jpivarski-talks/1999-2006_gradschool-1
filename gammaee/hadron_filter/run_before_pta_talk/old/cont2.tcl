default prompt off
exception continueEventLoop on

module sel HbookHistogramModule
hbook file ../rzn/cont.rzn
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

source_format sel PDSSourceFormat
file in ../rzn/cont.pds event startrun beginrun endrun

proc sel ../build_SunOS/shlib/HadronFilterProc
param HadronFilterProc noBunchWeight true
param HadronFilterProc ntupleSize 10000
param HadronFilterProc noBeamSpot false

param HadronFilterProc fillBuffer true
go 1000
param HadronFilterProc fillBuffer false
go 100000

hbook terminate
exit
