default prompt off
exception continueEventLoop on

module sel LoadHbook4MModule
module sel HbookHistogramModule
hbook file ../data_method_rzn/y1sqqmcother_trigger.rzn
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
file add pdschain /cdat/lnsva2/disk2/idanko/Bmumu_mc/Y1S2hadrons/p2_124712.pds event physics startrun beginrun endrun
file add pdschain /cdat/lnsva2/disk2/idanko/Bmumu_mc/Y1S2hadrons/p2_124730.pds event physics startrun beginrun endrun
file add pdschain /cdat/lnsva2/disk2/idanko/Bmumu_mc/Y1S2hadrons/p2_124853.pds event physics startrun beginrun endrun
file add pdschain /cdat/lnsva2/disk2/idanko/Bmumu_mc/Y1S2hadrons/p2_124879.pds event physics startrun beginrun endrun
file add pdschain /cdat/lnsva2/disk2/idanko/Bmumu_mc/Y1S2hadrons/p2_124896.pds event physics startrun beginrun endrun
file add pdschain /cdat/lnsva2/disk2/idanko/Bmumu_mc/Y1S2hadrons/p2_124907.pds event physics startrun beginrun endrun
file add pdschain /cdat/lnsva2/disk2/idanko/Bmumu_mc/Y1S2hadrons/p2_124992.pds event physics startrun beginrun endrun
file add pdschain /cdat/lnsva2/disk2/idanko/Bmumu_mc/Y1S2hadrons/p2_125000.pds event physics startrun beginrun endrun
file add pdschain /cdat/lnsva2/disk2/idanko/Bmumu_mc/Y1S2hadrons/p2_125028.pds event physics startrun beginrun endrun
file add pdschain /cdat/lnsva2/disk2/idanko/Bmumu_mc/Y1S2hadrons/p2_125062.pds event physics startrun beginrun endrun
file add pdschain /cdat/lnsva2/disk2/idanko/Bmumu_mc/Y1S2hadrons/p2_125077.pds event physics startrun beginrun endrun
file add pdschain /cdat/lnsva2/disk2/idanko/Bmumu_mc/Y1S2hadrons/p2_125192.pds event physics startrun beginrun endrun
file add pdschain /cdat/lnsva2/disk2/idanko/Bmumu_mc/Y1S2hadrons/p2_125211.pds event physics startrun beginrun endrun
file add pdschain /cdat/lnsva2/disk2/idanko/Bmumu_mc/Y1S2hadrons/p2_125217.pds event physics startrun beginrun endrun
file add pdschain /cdat/lnsva2/disk2/idanko/Bmumu_mc/Y1S2hadrons/p2_125226.pds event physics startrun beginrun endrun
file add pdschain /cdat/lnsva2/disk2/idanko/Bmumu_mc/Y1S2hadrons/p2_125239.pds event physics startrun beginrun endrun
file add pdschain /cdat/lnsva2/disk2/idanko/Bmumu_mc/Y1S2hadrons/p2_125338.pds event physics startrun beginrun endrun
file add pdschain /cdat/lnsva2/disk2/idanko/Bmumu_mc/Y1S2hadrons/p2_125358.pds event physics startrun beginrun endrun
file add pdschain /cdat/lnsva2/disk2/idanko/Bmumu_mc/Y1S2hadrons/p2_125362.pds event physics startrun beginrun endrun
file add pdschain /cdat/lnsva2/disk2/idanko/Bmumu_mc/Y1S2hadrons/p2_125369.pds event physics startrun beginrun endrun
file add pdschain /cdat/lnsva2/disk2/idanko/Bmumu_mc/Y1S2hadrons/p2_125389.pds event physics startrun beginrun endrun
file add pdschain /cdat/lnsva2/disk2/idanko/Bmumu_mc/Y1S2hadrons/p2_125405.pds event physics startrun beginrun endrun

go
