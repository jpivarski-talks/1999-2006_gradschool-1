default prompt off
exception continueEventLoop on

module sel LoadHbook4MModule
module sel HbookHistogramModule
hbook file ../chib_rzn/chib-1.rzn
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
file in $env(C3_INFO)/mc/zeromc.beamspot beginrun
run_file $env(C3_SCRIPTS)/CcHotList.tcl

proc sel ../build_SunOS/shlib/ChiBMC
param ChiBMC mc -1
proc sel ../build_SunOS/shlib/ChiBSkim
param ChiBSkim cut false

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
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R126308-E12956-DTS12092003_141616-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R126309-E14074-DTS12092003_141627-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R126310-E14554-DTS12092003_141638-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R126311-E3611-DTS12092003_141649-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R126314-E5671-DTS12092003_141659-pass2.pds physics event startrun beginrun endrun 

sink_format sel PDSSinkFormat
file out ../chib_rzn/chib-1.pds {event{\
    DBTrackerValues FATable<TRTrack> FATable<TRHelixPionFit> FATable<TRPionQuality>\
    FATable<CcBasicShowerAttsArg> TrackShowerLattice FATable<CcConRegAttributes> CcConRegShowerLattice\
    EventProperties DBEventHeader\
    TriggerL1Data Level3TagWord Level4Decision\
}} startrun beginrun endrun

go




