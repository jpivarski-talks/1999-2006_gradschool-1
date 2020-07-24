
default prompt off
exception continueEventLoop on

module sel HbookHistogramModule
hbook file simple_124870_end.rzn
hbook init

run_file $env(C3_SCRIPTS)/getConstants.tcl

run_file $env(C3_SCRIPTS)/trackingDataFull.tcl

prod sel C3ccProd
prod sel CcfcReconProd
prod sel CcGeomProd
prod sel C3ccReconProd
prod sel C3ccConProd
prod sel TrackShowerMatchingProd

prod sel DBEventHeaderProd

source_format sel BinarySourceFormat
file in high_124870.bin event startrun beginrun endrun
source activate high_124870 event startrun beginrun endrun

proc sel ../build_$env(OS_NAME)/shlib/SimpleZ0Cut
# proc sel HistogramViewerProc

goto 124870 90000
go 10000
exit

