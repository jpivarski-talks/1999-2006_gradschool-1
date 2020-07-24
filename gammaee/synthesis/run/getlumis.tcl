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
# prod sel CesrBeamEnergyProd
prod sel DBEventHeaderProd

run_file $env(C3_SCRIPTS)/BeamSpot.tcl
run_file $env(C3_SCRIPTS)/CcHotList.tcl
source_format sel RunInfoFileSourceFormat
file in $env(C3_INFO)/data/runinfo.runinfo

prod sel CustomBeamEnergyProd
CustomBeamEnergyProd NoRunStat = 1
CustomBeamEnergyProd BeamEnergy = $env(USER_ENERGY)

prod sel GoodThingsProd

proc sel P2LumiMonProc
proc sel ../build_SunOS3/shlib/UpsilonGammaEEAnalysisProc

module sel DBModule
database in /nfs/cleo3/database/data$env(USER_DB)/db event startrun beginrun endrun
database read_collection pass2
database run $env(USER_RUN)

go
summary
exit
