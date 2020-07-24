default prompt off
exception continueEventLoop on

module sel RandomModule
random seeds 1066498 7135548
random create

module sel HbookHistogramModule
hbook file ../rzn2/db21cascades9.rzn
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

run_file $env(C3_SCRIPTS)/BeamSpot.tcl
run_file $env(C3_SCRIPTS)/CcHotList.tcl
source_format sel RunInfoFileSourceFormat
file in $env(C3_INFO)/data/runinfo.runinfo

# this is +/- 4 MeV in COM
proc sel RunInfoProc
param RunInfoProc MinBeamEnergy 5.01085
param RunInfoProc MaxBeamEnergy 5.01485

proc sel ../build_SunOS2/shlib/UpsilonGammaEECascadesProc

module sel DBModule
database in /nfs/cleo3/database/data21/db event startrun beginrun endrun
database read_collection pass2

go
summary
exit

