default prompt off
# exception continueEventLoop on

module select LoadGeantModule
module select LoadHbookModule
module sel LoadHbook4MModule
module sel HbookHistogramModule
hbook file test.rzn
hbook init

run_file $env(C3_SCRIPTS)/getConstants.tcl

source_format sel SVHybridEfficiencyFileSourceFormat
file in normal.svhybridefficiency

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
prod sel DBRunHeaderProd

prod sel DBEventHeaderProd

#  module sel DBModule
#  database in /nfs/cleo3/database/data16/db event beginrun startrun endrun
#  source activate db event beginrun startrun endrun
#  database read_collection rawdata mupair
#  database run 121339

source_format sel BinarySourceFormat
file in run_123404.bin event beginrun startrun endrun

proc sel ../build_SunOS/shlib/Y3sHadronFilter.so
proc sel HistogramViewerProc

go
