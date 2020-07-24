default prompt off
exception continueEventLoop on

module sel RandomModule
random seeds 735501 913059
random create

module sel HbookHistogramModule
hbook file ../rzn2/mc23cascades9.rzn
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

proc sel ../build_SunOS2/shlib/UpsilonGammaEECascadesProc

source_format sel PDSSourceFormat
source create pdschain
file add pdschain ../mccascades/mcpass2_y2pipi_123610_db23.pds physics event beginrun startrun endrun
file add pdschain ../mccascades/mcpass2_y2pipi_123611_db23.pds physics event beginrun startrun endrun
file add pdschain ../mccascades/mcpass2_y2pipi_123612_db23.pds physics event beginrun startrun endrun
file add pdschain ../mccascades/mcpass2_y2pipi_123615_db23.pds physics event beginrun startrun endrun
file add pdschain ../mccascades/mcpass2_y2pipi_123616_db23.pds physics event beginrun startrun endrun
file add pdschain ../mccascades/mcpass2_y2pipi_123617_db23.pds physics event beginrun startrun endrun
file add pdschain ../mccascades/mcpass2_y2pipi_123618_db23.pds physics event beginrun startrun endrun
file add pdschain ../mccascades/mcpass2_y2pipi_123619_db23.pds physics event beginrun startrun endrun
file add pdschain ../mccascades/mcpass2_y2pipi_123620_db23.pds physics event beginrun startrun endrun
file add pdschain ../mccascades/mcpass2_y2pipi_123621_db23.pds physics event beginrun startrun endrun
file add pdschain ../mccascades/mcpass2_y2pipi_123623_db23.pds physics event beginrun startrun endrun
file add pdschain ../mccascades/mcpass2_y2pipi_123624_db23.pds physics event beginrun startrun endrun
file add pdschain ../mccascades/mcpass2_y2pipi_123631_db23.pds physics event beginrun startrun endrun
file add pdschain ../mccascades/mcpass2_y2pipi_123632_db23.pds physics event beginrun startrun endrun
file add pdschain ../mccascades/mcpass2_y2pipi_123633_db23.pds physics event beginrun startrun endrun
file add pdschain ../mccascades/mcpass2_y2pipi_123635_db23.pds physics event beginrun startrun endrun
file add pdschain ../mccascades/mcpass2_y2pipi_123636_db23.pds physics event beginrun startrun endrun
file add pdschain ../mccascades/mcpass2_y2pipi_123637_db23.pds physics event beginrun startrun endrun
file add pdschain ../mccascades/mcpass2_y2pipi_123638_db23.pds physics event beginrun startrun endrun
file add pdschain ../mccascades/mcpass2_y2pipi_123639_db23.pds physics event beginrun startrun endrun
file add pdschain ../mccascades/mcpass2_y2pipi_123640_db23.pds physics event beginrun startrun endrun
file add pdschain ../mccascades/mcpass2_y2pipi_123641_db23.pds physics event beginrun startrun endrun
file add pdschain ../mccascades/mcpass2_y2pipi_123643_db23.pds physics event beginrun startrun endrun
file add pdschain ../mccascades/mcpass2_y2pipi_123644_db23.pds physics event beginrun startrun endrun
file add pdschain ../mccascades/mcpass2_y2pipi_123645_db23.pds physics event beginrun startrun endrun
file add pdschain ../mccascades/mcpass2_y2pipi_123646_db23.pds physics event beginrun startrun endrun
file add pdschain ../mccascades/mcpass2_y2pipi_123647_db23.pds physics event beginrun startrun endrun
file add pdschain ../mccascades/mcpass2_y2pipi_123648_db23.pds physics event beginrun startrun endrun
file add pdschain ../mccascades/mcpass2_y2pipi_123650_db23.pds physics event beginrun startrun endrun
file add pdschain ../mccascades/mcpass2_y2pipi_123651_db23.pds physics event beginrun startrun endrun
file add pdschain ../mccascades/mcpass2_y2pipi_123652_db23.pds physics event beginrun startrun endrun
file add pdschain ../mccascades/mcpass2_y2pipi_123653_db23.pds physics event beginrun startrun endrun
file add pdschain ../mccascades/mcpass2_y2pipi_123654_db23.pds physics event beginrun startrun endrun
file add pdschain ../mccascades/mcpass2_y2pipi_123656_db23.pds physics event beginrun startrun endrun
file add pdschain ../mccascades/mcpass2_y2pipi_123658_db23.pds physics event beginrun startrun endrun

go
summary
exit
