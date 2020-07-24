default prompt off
exception continueEventLoop on

#  module sel RandomModule
#  random create

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

prod sel MCInfoDelivery
#  prod sel MCRawDataProd

source_format sel PDSSourceFormat
file in ../pds/gamgam.pds event startrun beginrun endrun physics

#  proc sel EventTypeFilterProc
#  param EventTypeFilterProc Hadron true

proc sel ../build_SunOS/shlib/PrintOutProc

#  proc sel SpExtractStandAloneGeomProc
#  proc sel SpExtractMCDecayTreeProc
#  proc sel SpExtractSeedTrackProc
#  proc sel SpExtractDRHitsProc
#  proc sel SpExtractSVHitsProc
#  proc sel SpViewerProc

go 100
