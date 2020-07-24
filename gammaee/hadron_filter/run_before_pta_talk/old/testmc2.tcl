default prompt off
exception continueEventLoop on

module select LoadGeantModule
module select LoadHbookModule
module sel HbookHistogramModule
hbook file ../rzn/monte_carlo.rzn
hbook init

module sel CorbaModule
corba init
module sel ConstantsModule
constants in $env(C3_CONST) meta Offline MetaListRetrieval
constants in $env(C3_CONST) meta CesrOffset MetaListRetrieval
constants in $env(C3_CONST) meta BaseGeometry MetaListRetrieval
constants in $env(C3_CONST) meta SVHybridEfficiency MetaListRetrieval
constants in $env(C3_CONST) meta Alignment MetaListRetrieval
constants in $env(C3_CONST) meta FieldMap MetaListRetrieval

source_format sel AsciiSourceFormat
file in $env(C3_DATA)/material.asc basegeometry

source_format sel CcHotListFileSourceFormat
file in $env(C3_DATA)/cchotlist.cchotlist beginrun

source_format sel MagFudgeFileSourceFormat
file in normal.magfudge

module sel RunStatisticsSourceModule
runstatistics in

prod sel TrackDeliveryProd
prod sel SeedToTRTrackProd
prod sel NavigationProd
prod sel MagFieldProd

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

proc sel ../build_SunOS/shlib/HadronFilterProc

param HadronFilterProc noBeamSpot true
param HadronFilterProc noBunchWeight true
param HadronFilterProc ntupleSize -1
go

hbook terminate
exit

