default prompt off
exception continueEventLoop on

module sel LoadHbook4MModule
module sel HbookHistogramModule
hbook file ../rzn3/mcagain_y1s.rzn
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

source_format sel PDSSourceFormat
source create pdschain
file add pdschain ../mc/y1s/mcpass2_123610.pds physics event beginrun startrun endrun
file add pdschain ../mc/y1s/mcpass2_123611.pds physics event beginrun startrun endrun
file add pdschain ../mc/y1s/mcpass2_123612.pds physics event beginrun startrun endrun
file add pdschain ../mc/y1s/mcpass2_123615.pds physics event beginrun startrun endrun
file add pdschain ../mc/y1s/mcpass2_123616.pds physics event beginrun startrun endrun
file add pdschain ../mc/y1s/mcpass2_123617.pds physics event beginrun startrun endrun
file add pdschain ../mc/y1s/mcpass2_123618.pds physics event beginrun startrun endrun
file add pdschain ../mc/y1s/mcpass2_123619.pds physics event beginrun startrun endrun
file add pdschain ../mc/y1s/mcpass2_123620.pds physics event beginrun startrun endrun
file add pdschain ../mc/y1s/mcpass2_123621.pds physics event beginrun startrun endrun
file add pdschain ../mc/y1s/mcpass2_123623.pds physics event beginrun startrun endrun
file add pdschain ../mc/y1s/mcpass2_123624.pds physics event beginrun startrun endrun
file add pdschain ../mc/y1s/mcpass2_123631.pds physics event beginrun startrun endrun
file add pdschain ../mc/y1s/mcpass2_123632.pds physics event beginrun startrun endrun
file add pdschain ../mc/y1s/mcpass2_123633.pds physics event beginrun startrun endrun
file add pdschain ../mc/y1s/mcpass2_123635.pds physics event beginrun startrun endrun
file add pdschain ../mc/y1s/mcpass2_123636.pds physics event beginrun startrun endrun
file add pdschain ../mc/y1s/mcpass2_123637.pds physics event beginrun startrun endrun
file add pdschain ../mc/y1s/mcpass2_123638.pds physics event beginrun startrun endrun
file add pdschain ../mc/y1s/mcpass2_123639.pds physics event beginrun startrun endrun
file add pdschain ../mc/y1s/mcpass2_123640.pds physics event beginrun startrun endrun
file add pdschain ../mc/y1s/mcpass2_123641.pds physics event beginrun startrun endrun
file add pdschain ../mc/y1s/mcpass2_123643.pds physics event beginrun startrun endrun
file add pdschain ../mc/y1s/mcpass2_123644.pds physics event beginrun startrun endrun
file add pdschain ../mc/y1s/mcpass2_123645.pds physics event beginrun startrun endrun

go
exit
