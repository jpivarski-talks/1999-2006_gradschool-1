default prompt off
exception continueEventLoop on

module select LoadGeantModule
module select LoadHbookModule
module sel HbookHistogramModule
hbook file ../rzn/test6.rzn
hbook init

#  module select RandomModule
#  random create
#  random status

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
#  prod sel ../build_SunOS/shlib/EventVertexProd.so

source_format sel BinarySourceFormat
file in positrons1.bin event startrun beginrun endrun

proc sel ../build_SunOS/shlib/BigNTuple2

go 1000

hbook terminate
exit

