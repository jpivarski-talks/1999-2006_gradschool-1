default prompt off
exception continueEventLoop on

module sel HbookHistogramModule
hbook file ../rzn/subcollectioncuts.rzn
hbook init

run_file $env(C3_SCRIPTS)/getNewestConstants.tcl
run_file $env(C3_SCRIPTS)/trackingDataFull.tcl
run_file $env(C3_SCRIPTS)/CcP2.tcl
prod sel TrackShowerMatchingProd
prod sel EventPropertiesProd
prod sel CesrBeamEnergyProd

# prod sel RunInfoProd
# source_format sel RunInfoFileSourceFormat
# file in $env(C3_INFO)/data/runinfo.runinfo startrun

# prod sel CustomBeamEnergyProd
# param CustomBeamEnergyProd BeamEnergy 4.73005

module sel DBModule
database in /nfs/cleo3/database/data19/db event startrun beginrun endrun
database read_collection rawdata
database run 124671 124806

proc sel ../build_SunOS/shlib/SubcollectionCuts

go
