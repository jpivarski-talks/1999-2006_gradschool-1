# default prompt off
# exception continueEventLoop on

module sel HbookHistogramModule
# hbook file test.rzn
hbook file weighted_ave_z0.rzn
hbook init

module sel CorbaModule
corba init
module sel ConstantsModule
constants in $env(C3_CONST) meta Offline MetaListRetrieval
constants in $env(C3_CONST) meta CesrOffset MetaListRetrieval
constants in $env(C3_CONST) meta BaseGeometry MetaListRetrieval
constants in $env(C3_CONST) meta SVHybridEfficiency MetaListRetrieval
constants in $env(C3_CONST) meta Alignment MetaListRetrieval

source_format sel AsciiSourceFormat
file in $env(C3_DATA)/material.asc basegeometry

module sel RunStatisticsSourceModule
runstatistics in

prod sel C3ccProd
prod sel TrackDeliveryProd
prod sel SeedToTRTrackProd
prod sel NavigationProd
prod sel MagFieldProd

source_format sel PDSSourceFormat
file in ../dafedir/bug-free2_123592_cont.pds event startrun beginrun endrun
source activate bug-free2_123592_cont event startrun beginrun endrun

proc sel ../build_$env(OS_NAME)/shlib/BeamGasWallTester
# proc sel HistogramViewerProc

go 2020
exit
