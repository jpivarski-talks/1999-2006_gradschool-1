default prompt off
exception continueEventLoop on

module sel HbookHistogramModule
hbook file ../rzn/bhabha_mc3.rzn
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
source create pdschain
file add pdschain mc_bhabha1.pds event startrun beginrun endrun
file add pdschain mc_bhabha2.pds event startrun beginrun endrun
file add pdschain mc_bhabha3.pds event startrun beginrun endrun
file add pdschain mc_bhabha4.pds event startrun beginrun endrun
file add pdschain mc_bhabha5.pds event startrun beginrun endrun

proc sel ../build_SunOS/shlib/HadronFilterProc
param HadronFilterProc noBunchWeight true
param HadronFilterProc ntupleSize -1
param HadronFilterProc noBeamSpot true

param HadronFilterProc fillBuffer false
go

hbook terminate
exit
