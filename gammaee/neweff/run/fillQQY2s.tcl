default prompt off
exception continueEventLoop on

module sel LoadHbook4MModule
module sel HbookHistogramModule
hbook file ../rzn/qqy2s.rzn
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

file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R126288-E9328-DTS12092003_141409-pass2.pds physics event startrun beginrun endrun
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R126290-E12578-DTS12092003_141420-pass2.pds physics event startrun beginrun endrun
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R126292-E12787-DTS12092003_141431-pass2.pds physics event startrun beginrun endrun
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R126293-E12870-DTS12092003_141441-pass2.pds physics event startrun beginrun endrun
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R126294-E10976-DTS12092003_141452-pass2.pds physics event startrun beginrun endrun
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R126296-E11571-DTS12092003_141502-pass2.pds physics event startrun beginrun endrun
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R126298-E13010-DTS12092003_141513-pass2.pds physics event startrun beginrun endrun
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R126299-E13104-DTS12092003_141523-pass2.pds physics event startrun beginrun endrun
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R126300-E11851-DTS12092003_141534-pass2.pds physics event startrun beginrun endrun
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R126302-E12167-DTS12092003_141545-pass2.pds physics event startrun beginrun endrun
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R126304-E12876-DTS12092003_141555-pass2.pds physics event startrun beginrun endrun
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R126305-E12877-DTS12092003_141606-pass2.pds physics event startrun beginrun endrun

go

