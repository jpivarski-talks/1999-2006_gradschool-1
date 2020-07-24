prod sel NavigationProd
prod sel TrackDeliveryProd
prod sel C3ccProd
param C3ccProd RequireRunGainsHotList false
prod sel MagFieldProd
prod sel CesrBeamEnergyProd

module sel CorbaModule
corba init
module sel RunStatisticsSourceModule
runstatistics in
module sel ConstantsModule
constants in $env(C3_CONST) standard CLEO3default streams superconductingquad magfudge

proc sel L1TriggerSelectProc
param L1TriggerSelectProc TwoTrackKeep true
# param L1TriggerSelectProc RandomKeep true
# param L1TriggerSelectProc PulserKeep true
proc sel ../build_SunOS/shlib/UnderTwoTracks

proc sel SpExtractStandAloneGeomProc
proc sel SpExtractKinePionFitProc
proc sel SpExtractShowerAttributesProc
proc sel SpExtractDBEventHeaderProc
proc sel SpViewerProc

source_format sel PDSSourceFormat
file in ../thpds/r123378.pds event startrun beginrun endrun

# source create pdschain
# file add pdschain ../data_method_rzn/evtgen/y3s/mcpass2_121916.pds event startrun beginrun endrun
# file add pdschain ../data_method_rzn/evtgen/y3s/mcpass2_121917.pds event startrun beginrun endrun
# file add pdschain ../data_method_rzn/evtgen/y3s/mcpass2_121918.pds event startrun beginrun endrun
# file add pdschain ../data_method_rzn/evtgen/y3s/mcpass2_121920.pds event startrun beginrun endrun
# file add pdschain ../data_method_rzn/evtgen/y3s/mcpass2_121924.pds event startrun beginrun endrun
# file add pdschain ../data_method_rzn/evtgen/y3s/mcpass2_121925.pds event startrun beginrun endrun

go


