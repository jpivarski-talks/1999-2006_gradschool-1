default prompt off
exception continueEventLoop on

module sel HbookHistogramModule
hbook file ../rzn/monte_carlo4.rzn
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
file add pdschain mc_113244.pds event startrun beginrun endrun
file add pdschain mc_113246.pds event startrun beginrun endrun
file add pdschain mc_113247.pds event startrun beginrun endrun
file add pdschain mc_113248.pds event startrun beginrun endrun
file add pdschain mc_113249.pds event startrun beginrun endrun
file add pdschain mc_113250.pds event startrun beginrun endrun
file add pdschain mc_113255.pds event startrun beginrun endrun
file add pdschain mc_113256.pds event startrun beginrun endrun
file add pdschain mc_113258.pds event startrun beginrun endrun

prod sel CesrBeamEnergyProd
prod sel EventPropertiesProd

proc sel ../build_SunOS/shlib/HadronFilterProc
param HadronFilterProc noBunchWeight true
param HadronFilterProc ntupleSize -1
param HadronFilterProc noBeamSpot true

param HadronFilterProc fillBuffer false
go

