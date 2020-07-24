default prompt off
exception continueEventLoop on

module select LoadGeantModule
module select LoadHbookModule
module sel HbookHistogramModule
hbook file ../rzn/testmc6.rzn
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

prod sel C3ccProd
prod sel TrackDeliveryProd
prod sel SeedToTRTrackProd
prod sel NavigationProd
prod sel MagFieldProd

prod sel MutrReconProd
prod sel MuConsProd
run_file $env(C3_SCRIPTS)/load_geometry_producers.tcl
run_file $env(C3_SCRIPTS)/load_dg_to_geant3_converter.tcl
prod sel MagFieldProd

#  prod sel ../build_SunOS/shlib/EventVertexProd
#  param EventVertexProd EventVXMenu max_d0 1.
#  param EventVertexProd EventVXMenu max_z0 1.
#  param EventVertexProd EventVXMenu max_Chi2perTrack 1e20

prod sel MCInfoDelivery

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

proc sel ../build_SunOS/shlib/BigNTuple2
param BigNTuple2 getBunchData false
param BigNTuple2 lookForCosmics false

#  proc sel SpExtractStandAloneGeomProc
#  proc sel SpExtractSeedTrackProc
#  proc sel SpExtractDBEventHeaderProc
#  prod sel DBEventHeaderProd
#  proc sel SpViewerProc

# report level ERROR
go
# hbook terminate
# exit

exit

