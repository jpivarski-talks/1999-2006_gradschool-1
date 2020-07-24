default prompt off
exception continueEventLoop on

module sel LoadHbook4MModule
module sel HbookHistogramModule
hbook file ../rzn5/bgneg.rzn
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
param Cuts mcInfo false
param Cuts triggerInfo false

source_format sel PDSSourceFormat
source create pdschain
file add pdschain /cdat/dafe/mccann/neweff/rzn/beamgas_neg/r126828.pds event beginrun startrun endrun
file add pdschain /cdat/dafe/mccann/neweff/rzn/beamgas_neg/r126920.pds event beginrun startrun endrun
file add pdschain /cdat/dafe/mccann/neweff/rzn/beamgas_neg/r126922.pds event beginrun startrun endrun
file add pdschain /cdat/dafe/mccann/neweff/rzn/beamgas_neg/r127014.pds event beginrun startrun endrun

go
hbook terminate
exit
