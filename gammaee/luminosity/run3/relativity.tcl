default prompt off
exception continueEventLoop on

module sel CorbaModule
corba init
module sel RunStatisticsSourceModule
runstatistics in
module sel ConstantsModule
constants in $env(C3_CONST) standard CLEO3default
constants in $env(C3_CONST) meta BaseGeometry MetaListRetrieval
 
prod sel NavigationProd
prod sel TrackDeliveryProd
prod sel C3ccProd
param C3ccProd RequireRunGainsHotList false
prod sel MagFieldProd
prod sel EventPropertiesProd
prod sel CesrBeamEnergyProd

proc sel ../build_SunOS/shlib/Relativity

module sel DBModule
database in /nfs/cleo3/database/data$env(USER_DB)/db event startrun beginrun endrun
database read_collection pass2 bhagam
database run $env(USER_RUN)

go
summary
exit
