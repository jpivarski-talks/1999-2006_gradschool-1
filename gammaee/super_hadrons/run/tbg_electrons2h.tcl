default prompt off
exception continueEventLoop on

module sel HbookHistogramModule
hbook file ../rzn/tbg_electrons_allnew2h.rzn
hbook init

run_file $env(C3_SCRIPTS)/getNewestConstants.tcl
run_file $env(C3_SCRIPTS)/trackingDataFull.tcl
run_file $env(C3_SCRIPTS)/CcHotList.tcl

run_file $env(C3_SCRIPTS)/C3cc.tcl
prod sel DBEventHeaderProd
prod sel CcP2ReconProd
prod sel TrackShowerMatchingProd

prod sel CesrBeamEnergyProd
prod sel EventPropertiesProd
prod sel EventTypeProd

proc sel ../build_SunOS/shlib/SimpleEventFilter
param SimpleEventFilter start 70000
param SimpleEventFilter end   80000

proc sel EventTypeFilterProc
param EventTypeFilterProc Hadron true

proc sel ../build_SunOS/shlib/BeamGasFilterProc
param BeamGasFilterProc explicitBeamSpot true
param BeamGasFilterProc weightedZCut 1.

proc sel ../build_SunOS/shlib/TestBeamGas
param TestBeamGas explicitBeamSpot true
param TestBeamGas weightedZCut 1.

sink_format sel PDSSinkFormat
file out ../rzn/electrons2h.pds event startrun beginrun endrun

# module sel DBModule
# database in /nfs/cleo3/database/data21/db event startrun beginrun endrun
# database read_collection rawdata
# database run 126828
# go
# source rm db

module sel DBModule
database in /nfs/cleo3/database/data21/db event startrun beginrun endrun
database read_collection rawdata
database run 126922
go
source rm db

# module sel DBModule
# database in /nfs/cleo3/database/data21/db event startrun beginrun endrun
# database read_collection rawdata
# database run 126920
# go
# source rm db

# module sel DBModule
# database in /nfs/cleo3/database/data21/db event startrun beginrun endrun
# database read_collection rawdata
# database run 127014
# go

hbook terminate
exit
