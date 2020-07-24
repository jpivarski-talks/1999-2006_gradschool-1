default prompt off
exception continueEventLoop on

module sel HbookHistogramModule
hbook file ../rzn/beamgascount_nobg4.rzn
hbook init

source_format sel BeamSpotFileSourceFormat
file in $env(C3_INFO)/data/beamspot.beamspot

run_file $env(C3_SCRIPTS)/runOnPass2.tcl

prod sel DBEventHeaderProd
prod sel CesrBeamEnergyProd
prod sel EventPropertiesProd

prod sel ../build_SunOS/shlib/TrkmanProd
prod sel ../build_SunOS/shlib/TrkmanSelectionProd

proc sel ../build_SunOS/shlib/BeamGasFilterProc

proc sel ../build_SunOS/shlib/BeamGasCounterProc

# proc sel HistogramViewerProc

module sel DBModule
database in /nfs/cleo3/database/data17/db event startrun beginrun endrun
database read_collection pass2 hadron
go 25000

hbook terminate
exit
