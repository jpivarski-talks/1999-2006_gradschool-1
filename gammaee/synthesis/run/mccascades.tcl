default prompt off
exception continueEventLoop on

module sel RandomModule
random seeds 3658467 7235437
random create

module sel HbookHistogramModule
hbook file ../rzn2/mc21cascades9.rzn
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
prod sel DBEventHeaderProd

# run_file $env(C3_SCRIPTS)/BeamSpot.tcl
source_format sel BeamSpotFileSourceFormat
file in $env(C3_INFO)/mc/zeromc.beamspot beginrun

run_file $env(C3_SCRIPTS)/CcHotList.tcl

proc sel ../build_SunOS/shlib/UpsilonGammaEECascadesProc

source_format sel PDSSourceFormat
source create pdschain
file add pdschain ../mccascades/mcpass2_y2pipi_123610_db21.pds physics event beginrun startrun endrun
# file add pdschain ../mccascades/.pds physics event beginrun startrun endrun

go
summary
exit

