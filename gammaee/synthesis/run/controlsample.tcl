default prompt off
exception continueEventLoop on

module sel HbookHistogramModule
hbook file ../rzn/sb_$env(USER_TYPE).rzn
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
prod sel DBEventHeaderProd

source_format sel BeamSpotFileSourceFormat
file in $env(C3_INFO)/mc/zeromc.beamspot beginrun
run_file $env(C3_SCRIPTS)/CcHotList.tcl

# prod sel CustomBeamEnergyProd
# param CustomBeamEnergyProd BeamEnergy 5.0126
# param CustomBeamEnergyProd NoRunStat true
prod sel CesrBeamEnergyProd

proc sel ../build_SunOS/shlib/UpsilonGammaEEAnalysisProc
param UpsilonGammaEEAnalysisProc runstats false

source_format sel PDSSourceFormat
source create pdschain
run_file $env(USER_TYPE).tcl

go
summary
exit
