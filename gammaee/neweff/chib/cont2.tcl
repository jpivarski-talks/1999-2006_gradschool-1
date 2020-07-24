default prompt off
exception continueEventLoop on

module sel LoadHbook4MModule
module sel HbookHistogramModule
hbook file ../chib_rzn/cont.rzn
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
prod sel EventTypeProd
prod sel CesrBeamEnergyProd

source_format sel BeamSpotFileSourceFormat
file in $env(C3_INFO)/data/beamspot.beamspot beginrun
run_file $env(C3_SCRIPTS)/CcHotList.tcl

proc sel ../build_SunOS/shlib/ChiBSkim

source_format sel PDSSourceFormat
source create pdschain
file add pdschain ../chib_rzn/cont21.pds event startrun beginrun endrun
file add pdschain ../chib_rzn/cont22.pds event startrun beginrun endrun
file add pdschain ../chib_rzn/cont23.pds event startrun beginrun endrun
file add pdschain ../chib_rzn/cont25.pds event startrun beginrun endrun
file add pdschain ../chib_rzn/cont27.pds event startrun beginrun endrun

go




