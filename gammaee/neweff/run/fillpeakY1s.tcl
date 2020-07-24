default prompt off
exception continueEventLoop on

module sel LoadHbook4MModule
module sel HbookHistogramModule
hbook file ../rzn/peaky1s.rzn
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

file in ../rzn/peak1s/r123197.pds event startrun beginrun endrun
go
source rm r123197
file in ../rzn/peak1s/r123636.pds event startrun beginrun endrun
go
source rm r123636
file in ../rzn/peak1s/r123636_2.pds event startrun beginrun endrun
go
source rm r123636
file in ../rzn/peak1s/r123864.pds event startrun beginrun endrun
go
source rm r123864
file in ../rzn/peak1s/r123864_2.pds event startrun beginrun endrun
go
source rm r123864_2
