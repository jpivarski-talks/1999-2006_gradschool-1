default prompt off
exception continueEventLoop on

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

run_file $env(C3_SCRIPTS)/BeamSpot.tcl
run_file $env(C3_SCRIPTS)/CcHotList.tcl

# proc sel ../build_SunOS/shlib/ReCuts3
run_file $env(C3_SCRIPTS)/viewPass2.tcl 

source_format sel PDSSourceFormat

# cont
file in /cdat/dafe/mccann/acceptance/rzn5/raw122080.pds event beginrun startrun endrun

# peak
# file in /cdat/dafe/mccann/acceptance/rzn5/raw121972.pds event beginrun startrun endrun

go