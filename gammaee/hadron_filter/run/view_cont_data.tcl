default prompt off
exception continueEventLoop on

module sel HbookHistogramModule
hbook file tmp.rzn
hbook init

# run_file $env(C3_SCRIPTS)/runOnPass2.tcl

run_file $env(C3_SCRIPTS)/getConstants.tcl
run_file $env(C3_SCRIPTS)/trackingDataFull.tcl

run_file $env(C3_SCRIPTS)/C3cc.tcl
prod sel CcfcReconProd
prod sel TrackShowerMatchingProd

prod sel DBEventHeaderProd
prod sel CesrBeamEnergyProd
prod sel EventPropertiesProd
prod sel EventTypeProd

proc sel EventTypeFilterProc
param EventTypeFilterProc Hadron true

proc sel ../build_SunOS/shlib/HadronFilterProc
param HadronFilterProc noBunchWeight true
param HadronFilterProc ntupleSize 100000
param HadronFilterProc noBeamSpot true
param HadronFilterProc beamSpotX -1e-3
param HadronFilterProc beamSpotY 6e-4
param HadronFilterProc fillBuffer false

#  module sel DBModule
#  database in /nfs/cleo3/database/data17/db event startrun beginrun endrun
#  database read_collection rawdata hadron
#  database run 122585

source_format sel BinarySourceFormat
file in /cdat/sol191/disk2/cleo3/data/r122246.bin event startrun beginrun endrun

proc sel ../build_SunOS/shlib/TmpFilterProc

# run_file $env(C3_SCRIPTS)/viewPass2.tcl
run_file $env(C3_SCRIPTS)/viewTrackFitter.tcl

go
