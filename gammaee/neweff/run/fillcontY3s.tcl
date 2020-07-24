default prompt off
exception continueEventLoop on

module sel LoadHbook4MModule
module sel HbookHistogramModule
hbook file ../rzn/conty3s.rzn
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

file in ../rzn/cont3s/r121906.pds event startrun beginrun endrun
go
source rm r121906
file in ../rzn/cont3s/r121914.pds event startrun beginrun endrun
go
source rm r121914
file in ../rzn/cont3s/r122081.pds event startrun beginrun endrun
go
source rm r122081
