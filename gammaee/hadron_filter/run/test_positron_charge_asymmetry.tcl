default prompt off
exception continueEventLoop on

module sel HbookHistogramModule
hbook file ../rzn/test_positron_charge_asymmetry3.rzn
hbook init

module sel CorbaModule
corba init
module sel RunStatisticsSourceModule
runstatistics in
module sel ConstantsModule
constants in $env(C3_CONST) meta FieldMap MetaListRetrieval

source_format sel MagFudgeFileSourceFormat
file in normal.magfudge

prod sel NavigationProd
prod sel TrackDeliveryProd
prod sel C3ccProd
prod sel MagFieldProd
prod sel DBEventHeaderProd
prod sel CesrBeamEnergyProd
prod sel EventPropertiesProd
prod sel EventTypeProd

proc sel EventTypeFilterProc
param EventTypeFilterProc Hadron true

proc sel ../build_SunOS/official/shlib/HadronFilterProc
param HadronFilterProc explicitBeamSpot true
param HadronFilterProc beamX -1e-3
param HadronFilterProc beamY 6e-4
param HadronFilterProc beamZ 0.

proc sel ../build_SunOS/shlib/ChargeDistributionsProc
param ChargeDistributionsProc explicitBeamSpot true
param ChargeDistributionsProc beamX -1e-3
param ChargeDistributionsProc beamY 6e-4
param ChargeDistributionsProc beamZ 0.

source_format sel PDSSourceFormat

file in ../pds/positrons.pds event startrun beginrun endrun
go 25815
source rm positrons

hbook terminate
exit
