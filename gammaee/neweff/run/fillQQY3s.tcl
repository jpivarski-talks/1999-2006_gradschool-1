default prompt off
exception continueEventLoop on

module sel LoadHbook4MModule
module sel HbookHistogramModule
hbook file ../rzn/qqy3s.rzn
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
param Cuts usingQQ true

source_format sel PDSSourceFormat
source create pdschain

file add pdschain /cdat/sol221/disk4/c3mc/data16/ups3s/output/y3s-Jun27_02_MC-FL-1-R121339-E164-DTS17092002_134208-pass2.pds physics event startrun beginrun endrun
file add pdschain /cdat/sol221/disk4/c3mc/data16/ups3s/output/y3s-Jun27_02_MC-FL-1-R121340-E265-DTS17092002_134220-pass2.pds physics event startrun beginrun endrun
file add pdschain /cdat/sol221/disk4/c3mc/data16/ups3s/output/y3s-Jun27_02_MC-FL-1-R121343-E184-DTS17092002_134232-pass2.pds physics event startrun beginrun endrun
file add pdschain /cdat/sol221/disk4/c3mc/data16/ups3s/output/y3s-Jun27_02_MC-FL-1-R121344-E268-DTS17092002_134244-pass2.pds physics event startrun beginrun endrun
file add pdschain /cdat/sol221/disk4/c3mc/data16/ups3s/output/y3s-Jun27_02_MC-FL-1-R121346-E295-DTS17092002_134256-pass2.pds physics event startrun beginrun endrun
file add pdschain /cdat/sol221/disk4/c3mc/data16/ups3s/output/y3s-Jun27_02_MC-FL-1-R121347-E235-DTS17092002_134310-pass2.pds physics event startrun beginrun endrun
file add pdschain /cdat/sol221/disk4/c3mc/data16/ups3s/output/y3s-Jun27_02_MC-FL-1-R121348-E447-DTS17092002_134321-pass2.pds physics event startrun beginrun endrun
file add pdschain /cdat/sol221/disk4/c3mc/data16/ups3s/output/y3s-Jun27_02_MC-FL-1-R121349-E960-DTS17092002_134335-pass2.pds physics event startrun beginrun endrun
file add pdschain /cdat/sol221/disk4/c3mc/data16/ups3s/output/y3s-Jun27_02_MC-FL-1-R121361-E615-DTS17092002_134348-pass2.pds physics event startrun beginrun endrun
file add pdschain /cdat/sol221/disk4/c3mc/data16/ups3s/output/y3s-Jun27_02_MC-FL-1-R121362-E298-DTS17092002_134401-pass2.pds physics event startrun beginrun endrun
file add pdschain /cdat/sol221/disk4/c3mc/data16/ups3s/output/y3s-Jun27_02_MC-FL-1-R121365-E1100-DTS17092002_134414-pass2.pds physics event startrun beginrun endrun
file add pdschain /cdat/sol221/disk4/c3mc/data16/ups3s/output/y3s-Jun27_02_MC-FL-1-R121369-E793-DTS17092002_134427-pass2.pds physics event startrun beginrun endrun

go
