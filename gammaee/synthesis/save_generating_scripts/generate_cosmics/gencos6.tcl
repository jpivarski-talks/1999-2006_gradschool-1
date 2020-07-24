default prompt off
exception continueEventLoop on

module select LoadGeantModule
module select LoadHbookModule
module sel HbookHistogramModule
hbook file ../../rzn/test_cosmics6.rzn
hbook init

run_file $env(C3_SCRIPTS)/getConstants.tcl
run_file $env(C3_SCRIPTS)/trackingDataFull.tcl

run_file $env(C3_SCRIPTS)/C3cc.tcl
prod sel CcfcReconProd
prod sel TrackShowerMatchingProd

prod sel MutrReconProd
prod sel MuConsProd
run_file $env(C3_SCRIPTS)/load_geometry_producers.tcl
run_file $env(C3_SCRIPTS)/load_dg_to_geant3_converter.tcl
prod sel MagFieldProd
prod sel RawDataProd

prod sel DBEventHeaderProd
prod sel CesrBeamEnergyProd
prod sel EventPropertiesProd
prod sel EventTypeProd

source_format sel BinarySourceFormat
file in r128750.bin event startrun beginrun endrun

proc sel ../../build_SunOS/shlib/BigNTuple2
param BigNTuple2 getBunchData false
param BigNTuple2 interestingOnly true

sink_format sel PDSSinkFormat
file sink $env(USER_TMP)/gencos6.pds event startrun beginrun endrun

go
exit
