default prompt off
exception continueEventLoop on

module sel LoadHbook4MModule
module sel HbookHistogramModule
hbook file ../rzn4/db19mc.rzn
hbook init

module sel CorbaModule
corba init
module sel RunStatisticsSourceModule
runstatistics in
module sel ConstantsModule
constants in $env(C3_CONST) standard CLEO3default streams superconductingquad magfudge
constants in $env(C3_CONST) meta BaseGeometry MetaListRetrieval

prod sel NavigationProd
prod sel TrackDeliveryProd
prod sel C3ccProd
param C3ccProd RequireRunGainsHotList false
prod sel MagFieldProd
prod sel EventPropertiesProd
prod sel EventTypeProd
prod sel CesrBeamEnergyProd

source_format sel BeamSpotFileSourceFormat
file in $env(C3_INFO)/mc/zeromc.beamspot beginrun
run_file $env(C3_SCRIPTS)/CcHotList.tcl

proc sel ../build_SunOS/shlib/Cuts
param Cuts mcInfo true
param Cuts triggerInfo true
param Cuts res 1

source_format sel PDSSourceFormat
source create pdschain
file add pdschain /cdat/dafe/mccann/acceptance/remc3/y1s/May12_03_MC/mcpass2_123651.pds physics event beginrun startrun endrun
file add pdschain /cdat/dafe/mccann/acceptance/remc3/y1s/May12_03_MC/mcpass2_123652.pds physics event beginrun startrun endrun
file add pdschain /cdat/dafe/mccann/acceptance/remc3/y1s/May12_03_MC/mcpass2_123653.pds physics event beginrun startrun endrun
file add pdschain /cdat/dafe/mccann/acceptance/remc3/y1s/May12_03_MC/mcpass2_123654.pds physics event beginrun startrun endrun
file add pdschain /cdat/dafe/mccann/acceptance/remc3/y1s/May12_03_MC/mcpass2_123656.pds physics event beginrun startrun endrun
file add pdschain /cdat/dafe/mccann/acceptance/remc3/y1s/May12_03_MC/mcpass2_123658.pds physics event beginrun startrun endrun
file add pdschain /cdat/dafe/mccann/acceptance/remc3/y1s/May12_03_MC/mcpass2_123659.pds physics event beginrun startrun endrun
file add pdschain /cdat/dafe/mccann/acceptance/remc3/y1s/May12_03_MC/mcpass2_123665.pds physics event beginrun startrun endrun
file add pdschain /cdat/dafe/mccann/acceptance/remc3/y1s/May12_03_MC/mcpass2_123670.pds physics event beginrun startrun endrun
file add pdschain /cdat/dafe/mccann/acceptance/remc3/y1s/May12_03_MC/mcpass2_123673.pds physics event beginrun startrun endrun
file add pdschain /cdat/dafe/mccann/acceptance/remc3/y1s/May12_03_MC/mcpass2_123674.pds physics event beginrun startrun endrun
file add pdschain /cdat/dafe/mccann/acceptance/remc3/y1s/May12_03_MC/mcpass2_123675.pds physics event beginrun startrun endrun
file add pdschain /cdat/dafe/mccann/acceptance/remc3/y1s/May12_03_MC/mcpass2_123678.pds physics event beginrun startrun endrun

go
hbook terminate
exit
