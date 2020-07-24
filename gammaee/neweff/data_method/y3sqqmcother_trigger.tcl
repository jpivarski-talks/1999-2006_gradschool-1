default prompt off
exception continueEventLoop on

module sel LoadHbook4MModule
module sel HbookHistogramModule
hbook file ../data_method_rzn/y3sqqmcother_trigger.rzn
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
prod sel CesrBeamEnergyProd

source_format sel BeamSpotFileSourceFormat
file in $env(C3_INFO)/data/beamspot.beamspot beginrun
run_file $env(C3_SCRIPTS)/CcHotList.tcl

proc sel ../build_SunOS/shlib/Cuts
param Cuts usingQQ true

source_format sel PDSSourceFormat
source create pdschain
file add pdschain /cdat/sol221/disk4/c3mc/data16/ups3s/output/y3s-Jun27_02_MC-FL-1-R121339-E164-DTS17092002_134208-pass2.pds event physics startrun beginrun endrun
file add pdschain /cdat/sol221/disk4/c3mc/data16/ups3s/output/y3s-Jun27_02_MC-FL-1-R121340-E265-DTS17092002_134220-pass2.pds event physics startrun beginrun endrun
file add pdschain /cdat/sol221/disk4/c3mc/data16/ups3s/output/y3s-Jun27_02_MC-FL-1-R121343-E184-DTS17092002_134232-pass2.pds event physics startrun beginrun endrun
file add pdschain /cdat/sol221/disk4/c3mc/data16/ups3s/output/y3s-Jun27_02_MC-FL-1-R121344-E268-DTS17092002_134244-pass2.pds event physics startrun beginrun endrun
file add pdschain /cdat/sol221/disk4/c3mc/data16/ups3s/output/y3s-Jun27_02_MC-FL-1-R121346-E295-DTS17092002_134256-pass2.pds event physics startrun beginrun endrun
file add pdschain /cdat/sol221/disk4/c3mc/data16/ups3s/output/y3s-Jun27_02_MC-FL-1-R121347-E235-DTS17092002_134310-pass2.pds event physics startrun beginrun endrun
file add pdschain /cdat/sol221/disk4/c3mc/data16/ups3s/output/y3s-Jun27_02_MC-FL-1-R121348-E447-DTS17092002_134321-pass2.pds event physics startrun beginrun endrun
file add pdschain /cdat/sol221/disk4/c3mc/data16/ups3s/output/y3s-Jun27_02_MC-FL-1-R121349-E960-DTS17092002_134335-pass2.pds event physics startrun beginrun endrun
file add pdschain /cdat/sol221/disk4/c3mc/data16/ups3s/output/y3s-Jun27_02_MC-FL-1-R121361-E615-DTS17092002_134348-pass2.pds event physics startrun beginrun endrun
file add pdschain /cdat/sol221/disk4/c3mc/data16/ups3s/output/y3s-Jun27_02_MC-FL-1-R121362-E298-DTS17092002_134401-pass2.pds event physics startrun beginrun endrun
file add pdschain /cdat/sol221/disk4/c3mc/data16/ups3s/output/y3s-Jun27_02_MC-FL-1-R121365-E1100-DTS17092002_134414-pass2.pds event physics startrun beginrun endrun
file add pdschain /cdat/sol221/disk4/c3mc/data16/ups3s/output/y3s-Jun27_02_MC-FL-1-R121369-E793-DTS17092002_134427-pass2.pds event physics startrun beginrun endrun
file add pdschain /cdat/sol221/disk4/c3mc/data16/ups3s/output/y3s-Jun27_02_MC-FL-1-R121370-E1199-DTS17092002_134440-pass2.pds event physics startrun beginrun endrun
file add pdschain /cdat/sol221/disk4/c3mc/data16/ups3s/output/y3s-Jun27_02_MC-FL-1-R121373-E474-DTS17092002_134455-pass2.pds event physics startrun beginrun endrun
file add pdschain /cdat/sol221/disk4/c3mc/data16/ups3s/output/y3s-Jun27_02_MC-FL-1-R121374-E803-DTS17092002_134508-pass2.pds event physics startrun beginrun endrun
file add pdschain /cdat/sol221/disk4/c3mc/data16/ups3s/output/y3s-Jun27_02_MC-FL-1-R121375-E675-DTS17092002_134521-pass2.pds event physics startrun beginrun endrun
file add pdschain /cdat/sol221/disk4/c3mc/data16/ups3s/output/y3s-Jun27_02_MC-FL-1-R121378-E490-DTS17092002_134534-pass2.pds event physics startrun beginrun endrun
file add pdschain /cdat/sol221/disk4/c3mc/data16/ups3s/output/y3s-Jun27_02_MC-FL-1-R121381-E1374-DTS17092002_134604-pass2.pds event physics startrun beginrun endrun
file add pdschain /cdat/sol221/disk4/c3mc/data16/ups3s/output/y3s-Jun27_02_MC-FL-1-R121385-E1424-DTS17092002_134645-pass2.pds event physics startrun beginrun endrun
file add pdschain /cdat/sol221/disk4/c3mc/data16/ups3s/output/y3s-Jun27_02_MC-FL-1-R121387-E1484-DTS17092002_134658-pass2.pds event physics startrun beginrun endrun
file add pdschain /cdat/sol221/disk4/c3mc/data16/ups3s/output/y3s-Jun27_02_MC-FL-1-R121390-E1230-DTS17092002_134712-pass2.pds event physics startrun beginrun endrun
file add pdschain /cdat/sol221/disk4/c3mc/data16/ups3s/output/y3s-Jun27_02_MC-FL-1-R121391-E1305-DTS17092002_134724-pass2.pds event physics startrun beginrun endrun
file add pdschain /cdat/sol221/disk4/c3mc/data16/ups3s/output/y3s-Jun27_02_MC-FL-1-R121394-E1525-DTS17092002_134740-pass2.pds event physics startrun beginrun endrun
file add pdschain /cdat/sol221/disk4/c3mc/data16/ups3s/output/y3s-Jun27_02_MC-FL-1-R121395-E1445-DTS17092002_134754-pass2.pds event physics startrun beginrun endrun

go
