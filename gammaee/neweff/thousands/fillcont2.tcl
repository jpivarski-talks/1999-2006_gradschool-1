default prompt off
exception continueEventLoop on

module sel LoadHbook4MModule
module sel HbookHistogramModule
hbook file ../thrzn/cont2.rzn
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

source_format sel PDSSourceFormat
source create pdschain
file add pdschain ../thpds/r127662.pds event startrun beginrun endrun
file add pdschain ../thpds/r127684.pds event startrun beginrun endrun
file add pdschain ../thpds/r127703.pds event startrun beginrun endrun
file add pdschain ../thpds/r127721.pds event startrun beginrun endrun
file add pdschain ../thpds/r129066.pds event startrun beginrun endrun
file add pdschain ../thpds/r129070.pds event startrun beginrun endrun
file add pdschain ../thpds/r129071.pds event startrun beginrun endrun
file add pdschain ../thpds/r129072.pds event startrun beginrun endrun
file add pdschain ../thpds/r129709.pds event startrun beginrun endrun
file add pdschain ../thpds/r129847.pds event startrun beginrun endrun
file add pdschain ../thpds/r129849.pds event startrun beginrun endrun
file add pdschain ../thpds/r129851.pds event startrun beginrun endrun
file add pdschain ../thpds/r129860.pds event startrun beginrun endrun

go
