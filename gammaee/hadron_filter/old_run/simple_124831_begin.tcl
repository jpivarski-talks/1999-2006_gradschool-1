
default prompt off
exception continueEventLoop on

module sel HbookHistogramModule
hbook file simple_124831_begin.rzn
hbook init

run_file $env(C3_SCRIPTS)/getConstants.tcl

# run_file $env(C3_SCRIPTS)/trackingDataFull.tcl

prod sel C3ccProd
#  prod sel CcfcReconProd
#  prod sel CcGeomProd
#  prod sel C3ccReconProd
#  prod sel C3ccConProd
#  prod sel TrackShowerMatchingProd

prod sel DBEventHeaderProd

prod sel MagFieldProd
prod sel NavigationProd
prod sel TrackDeliveryProd
prod sel SeedToTRTrackProd

source_format sel PDSSourceFormat
file in ../dafedir/low_124831.pds event startrun beginrun endrun
source activate low_124831 event startrun beginrun endrun

proc sel ../build_$env(OS_NAME)/shlib/SimpleZ0Cut
# proc sel HistogramViewerProc

go 10000
exit

