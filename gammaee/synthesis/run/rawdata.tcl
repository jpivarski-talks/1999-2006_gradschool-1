default prompt off
exception continueEventLoop on

module sel HbookHistogramModule
hbook file ../rzn/rd_$env(USER_RUN).rzn
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

proc sel ../build_SunOS/shlib/UpsilonGammaEEAnalysisProc
param UpsilonGammaEEAnalysisProc runstats false

if {$env(USER_HASB) == 1} {
    source_format sel PDSSourceFormat
    file in ../pds/raw$env(USER_RUN)_b.pds event beginrun startrun endrun
    go
}

source_format sel PDSSourceFormat
file in ../pds/raw$env(USER_RUN).pds event beginrun startrun endrun

go
summary
exit
