default prompt off
exception continueEventLoop on

module sel LoadHbook4MModule
module sel HbookHistogramModule
hbook file ../rzncascades/cas_db21.rzn
hbook init

run_file $env(C3_SCRIPTS)/runOnPass2.tcl
prod sel EventPropertiesProd
prod sel CesrBeamEnergyProd
prod sel MagFieldProd

source_format sel BeamSpotFileSourceFormat
file in $env(C3_INFO)/mc/zeromc.beamspot beginrun

proc sel ../build_SunOS/shlib/Cascades

source_format sel PDSSourceFormat
source create pdschain
run_file db21.tcl

go
hbook terminate
exit
