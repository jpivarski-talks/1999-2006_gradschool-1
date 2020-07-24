default prompt off
exception continueEventLoop on

module sel LoadHbook4MModule
module sel HbookHistogramModule
hbook file ../../data_method_rzn/sample/qqmcll.rzn
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

proc sel ../../build_SunOS/shlib/DuperCuts2
param DuperCuts2 mcll true

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
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R126315-E11410-DTS12092003_141710-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R126316-E15572-DTS12092003_141721-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R126318-E12731-DTS12092003_141732-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R126322-E9895-DTS12092003_141743-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R126323-E16153-DTS12092003_141753-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R126325-E8981-DTS12092003_141804-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R126326-E15140-DTS12092003_141815-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R126329-E10764-DTS12092003_141826-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R126341-E2218-DTS12092003_141837-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R126344-E4147-DTS12092003_141848-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R126345-E11808-DTS12092003_141900-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R126347-E13027-DTS12092003_141910-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R126349-E14554-DTS12092003_141921-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R126352-E14956-DTS12092003_141932-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R126353-E16630-DTS12092003_141943-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R126354-E16074-DTS12092003_141954-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R126355-E16045-DTS12092003_142005-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R126356-E14483-DTS12092003_142016-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R126359-E14002-DTS12092003_142028-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R126361-E14347-DTS12092003_142039-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R126362-E15352-DTS12092003_142050-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R126364-E14697-DTS12092003_142108-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R126367-E11612-DTS12092003_142119-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R126369-E16580-DTS12092003_142130-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R126370-E17200-DTS12092003_142141-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R126371-E15272-DTS12092003_142152-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R126372-E17205-DTS12092003_142203-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R126373-E17370-DTS12092003_142214-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R126374-E16931-DTS12092003_142225-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R126376-E17463-DTS12092003_142236-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R126429-E7060-DTS12092003_142250-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R126431-E6506-DTS12092003_142301-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R126432-E7039-DTS12092003_142312-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R126433-E7401-DTS12092003_142323-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R126434-E7083-DTS12092003_142334-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R126436-E2045-DTS12092003_142345-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R126449-E3279-DTS12092003_142357-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R126451-E1594-DTS12092003_142408-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R126453-E784-DTS12092003_142419-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R126462-E2131-DTS12092003_142502-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R126464-E4706-DTS12092003_142513-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R126465-E6037-DTS12092003_142524-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R126467-E3414-DTS12092003_142536-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R126469-E7691-DTS12092003_142547-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R126496-E3627-DTS12092003_142602-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R126503-E2570-DTS12092003_142624-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R126505-E7462-DTS12092003_142634-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R126506-E5247-DTS12092003_142645-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R126507-E4753-DTS12092003_142656-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R126508-E13437-DTS12092003_142707-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R126509-E11788-DTS12092003_142718-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R126510-E12789-DTS12092003_142728-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R126511-E4066-DTS12092003_142739-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R126512-E2482-DTS12092003_142750-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R126513-E4276-DTS12092003_142800-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R126514-E13161-DTS12092003_142812-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R126517-E11421-DTS12092003_142823-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R126520-E2982-DTS12092003_142833-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R126521-E2440-DTS12092003_142844-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R126522-E13370-DTS12092003_142855-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R126523-E13284-DTS12092003_142905-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R126527-E8315-DTS12092003_142916-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R126528-E1822-DTS12092003_142927-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R126531-E1589-DTS12092003_142938-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R126532-E14300-DTS12092003_142948-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R126535-E1616-DTS12092003_142959-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R126536-E13966-DTS12092003_143010-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R126538-E14356-DTS12092003_143021-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R126539-E15125-DTS12092003_143031-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R126540-E15251-DTS12092003_143042-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R126541-E14218-DTS12092003_143053-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R126542-E3631-DTS12092003_143104-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R126543-E10364-DTS12092003_143115-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R126546-E1902-DTS12092003_143128-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R126552-E15056-DTS12092003_143139-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R126554-E16195-DTS12092003_143149-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R126555-E15883-DTS12092003_143200-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R126556-E16235-DTS12092003_143211-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R126557-E15585-DTS12092003_143221-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R126559-E14887-DTS12092003_143232-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R126562-E14096-DTS12092003_143243-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R126563-E16364-DTS12092003_143253-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R126564-E8344-DTS12092003_143304-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R126566-E1654-DTS12092003_143315-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R126568-E14889-DTS12092003_143326-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R126569-E16321-DTS12092003_143336-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R126572-E15296-DTS12092003_143347-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R126573-E15411-DTS12092003_143358-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R126575-E15208-DTS12092003_143409-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R126576-E16353-DTS12092003_143419-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R126577-E16464-DTS12092003_143430-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R126578-E13501-DTS12092003_143441-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R126579-E9680-DTS12092003_143452-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R126581-E11410-DTS12092003_143502-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R126676-E8094-DTS12092003_143521-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R126677-E2553-DTS12092003_143532-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R126679-E6549-DTS12092003_143542-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R126680-E13076-DTS12092003_143553-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R126682-E8865-DTS12092003_143604-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R126683-E13438-DTS12092003_143615-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R126684-E12219-DTS12092003_143625-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R126685-E11182-DTS12092003_143636-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R126688-E11012-DTS12092003_143647-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R126689-E13701-DTS12092003_143657-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R126690-E13004-DTS12092003_143708-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R126691-E8484-DTS12092003_143719-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R126692-E13670-DTS12092003_143729-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R126693-E12131-DTS12092003_143740-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R126695-E11864-DTS12092003_143751-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R126699-E10522-DTS12092003_143801-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R126701-E13402-DTS12092003_143812-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R126702-E13985-DTS12092003_143823-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R126703-E15760-DTS12092003_143834-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R126704-E16042-DTS12092003_143844-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R126706-E10658-DTS12092003_143855-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R126707-E15323-DTS12092003_143906-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R126709-E16440-DTS12092003_143917-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R126710-E2663-DTS12092003_143928-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R126711-E15200-DTS12092003_143938-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R126714-E13767-DTS12092003_143949-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R126716-E14161-DTS12092003_144000-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R126717-E14340-DTS12092003_144010-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R126718-E4292-DTS12092003_144021-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R126719-E10454-DTS12092003_144031-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R126720-E15679-DTS12092003_144042-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R126721-E3826-DTS12092003_144101-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R126722-E10093-DTS12092003_144112-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R126723-E15757-DTS12092003_144123-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R126725-E13009-DTS12092003_144133-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R126728-E15529-DTS12092003_144144-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R126729-E14930-DTS12092003_144155-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R126731-E15859-DTS12092003_144206-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R126732-E15819-DTS12092003_144216-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R126733-E15793-DTS12092003_144227-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R126734-E16375-DTS12092003_144238-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R126735-E16092-DTS12092003_144248-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R126736-E15499-DTS12092003_144259-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R126737-E15787-DTS12092003_144310-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R126738-E14772-DTS12092003_144320-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R126740-E12223-DTS12092003_144331-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R126744-E12765-DTS12092003_144342-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R126745-E6322-DTS12092003_144353-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R126746-E15876-DTS12092003_144404-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R126747-E14893-DTS12092003_144414-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R126749-E13675-DTS12092003_144425-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R126776-E7620-DTS12092003_144437-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R126777-E7309-DTS12092003_144448-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R126778-E7785-DTS12092003_144458-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R126779-E6995-DTS12092003_144509-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R126782-E2119-DTS12092003_144520-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R126783-E4039-DTS12092003_144531-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R126814-E3427-DTS12092003_144543-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R126823-E7079-DTS12092003_144626-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R126824-E8337-DTS12092003_144637-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R126825-E8033-DTS12092003_144647-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R126831-E5120-DTS12092003_144658-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R126858-E13448-DTS12092003_144712-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R126859-E12433-DTS12092003_144723-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R126862-E8208-DTS12092003_144733-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R126866-E9993-DTS12092003_144744-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R126868-E13643-DTS12092003_144755-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R126869-E13592-DTS12092003_144806-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R126870-E13464-DTS12092003_144817-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R126871-E14188-DTS12092003_144827-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R126872-E13049-DTS12092003_144838-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R126874-E11673-DTS12092003_144849-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R126875-E7624-DTS12092003_144900-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R126877-E3290-DTS12092003_144910-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R126878-E13813-DTS12092003_144921-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R126879-E6935-DTS12092003_144932-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R126880-E3753-DTS12092003_144943-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R126881-E13241-DTS12092003_144953-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R126882-E12371-DTS12092003_145004-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R126883-E12466-DTS12092003_145014-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R126890-E11532-DTS12092003_145025-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R126892-E12929-DTS12092003_145036-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R126893-E9431-DTS12092003_145047-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R126894-E2777-DTS12092003_145057-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R126895-E14620-DTS12092003_145108-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R126906-E1007-DTS12092003_145120-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R126907-E2806-DTS12092003_145131-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R126909-E12795-DTS12092003_145142-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R126910-E14336-DTS12092003_145152-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R126911-E14608-DTS12092003_145203-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R126912-E8575-DTS12092003_145214-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R126913-E14839-DTS12092003_145225-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R126914-E15564-DTS12092003_145235-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R126915-E15895-DTS12092003_145246-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R126923-E6803-DTS12092003_145257-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R126925-E4983-DTS12092003_145308-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R126926-E14813-DTS12092003_145319-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R126929-E9406-DTS12092003_145329-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R126931-E15945-DTS12092003_145340-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R126932-E7826-DTS12092003_145351-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R126933-E15463-DTS12092003_145402-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R126934-E12230-DTS12092003_145413-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R126936-E13079-DTS12092003_145423-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R127251-E9273-DTS12092003_145501-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R127254-E9342-DTS12092003_145512-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R127257-E11206-DTS12092003_145523-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R127261-E11614-DTS12092003_145534-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R127262-E4847-DTS12092003_145545-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R127263-E6645-DTS12092003_145556-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R127264-E12434-DTS12092003_145606-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R127266-E10024-DTS12092003_145617-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R127267-E12590-DTS12092003_145628-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R127268-E12981-DTS12092003_145638-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R127269-E13009-DTS12092003_145649-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R127270-E13041-DTS12092003_145700-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R127271-E13173-DTS12092003_145711-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R127272-E14134-DTS12092003_145721-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R127273-E14041-DTS12092003_145732-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R127278-E7418-DTS12092003_145743-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R127279-E10034-DTS12092003_145754-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R127280-E9255-DTS12092003_145804-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R127283-E1976-DTS12092003_145815-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R127285-E16421-DTS12092003_145826-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R127287-E10943-DTS12092003_145837-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R127289-E16147-DTS12092003_145848-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R127290-E16511-DTS12092003_145858-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R127291-E16289-DTS12092003_145909-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R127294-E15735-DTS12092003_145920-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R127295-E15314-DTS12092003_145930-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R127296-E8864-DTS12092003_145941-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R127297-E16924-DTS12092003_145952-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R127304-E10119-DTS12092003_150003-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R127306-E7509-DTS12092003_150014-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R127307-E17117-DTS12092003_150024-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R127308-E29877-DTS12092003_150041-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R127312-E12680-DTS12092003_150052-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R127314-E16423-DTS12092003_150103-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R127315-E14716-DTS12092003_150114-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R127317-E13094-DTS12092003_150124-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R127318-E2052-DTS12092003_150135-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R127319-E16029-DTS12092003_150146-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R127320-E12114-DTS12092003_150156-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R127321-E1746-DTS12092003_150207-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R127322-E14821-DTS12092003_150218-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R127325-E8443-DTS12092003_150229-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R127327-E16412-DTS12092003_150240-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R127328-E15767-DTS12092003_150250-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R127329-E14879-DTS12092003_150301-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R127330-E15980-DTS12092003_150312-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R127425-E5355-DTS12092003_150328-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R127459-E7184-DTS12092003_150340-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R127460-E12053-DTS12092003_150351-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R127461-E12759-DTS12092003_150402-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R127462-E12861-DTS12092003_150412-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R127465-E11448-DTS12092003_150423-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R127467-E10032-DTS12092003_150434-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R127472-E7701-DTS12092003_150445-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R127473-E12015-DTS12092003_150456-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R127477-E9178-DTS12092003_150506-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R127478-E13166-DTS12092003_150517-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R127479-E13527-DTS12092003_150528-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R127481-E12863-DTS12092003_150538-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R127482-E12422-DTS12092003_150549-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R127483-E12355-DTS12092003_150600-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R127488-E7615-DTS12092003_150611-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R127489-E12465-DTS12092003_150622-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R127492-E15563-DTS12092003_150633-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R127493-E15901-DTS12092003_150643-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R127498-E4775-DTS12092003_150654-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R127499-E7250-DTS12092003_150705-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R127501-E1883-DTS12092003_150716-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R127502-E9350-DTS12092003_150726-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R127503-E2962-DTS12092003_150737-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R127504-E9923-DTS12092003_150748-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R127506-E13821-DTS12092003_150759-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R127507-E16353-DTS12092003_150810-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R127508-E17556-DTS12092003_150821-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R127509-E16119-DTS12092003_150831-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R127510-E9040-DTS12092003_150842-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R127512-E14797-DTS12092003_150853-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R127513-E14380-DTS12092003_150904-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R127518-E12860-DTS12092003_150915-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R127521-E11061-DTS12092003_150926-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R127523-E15995-DTS12092003_150937-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R127524-E15804-DTS12092003_150948-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R127525-E4522-DTS12092003_150958-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R127527-E7992-DTS12092003_151009-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R127531-E15975-DTS12092003_151020-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R127532-E15188-DTS12092003_151031-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R127534-E15778-DTS12092003_151042-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R127535-E4838-DTS12092003_151054-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R127536-E10491-DTS12092003_151105-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R127537-E15961-DTS12092003_151115-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R127538-E15752-DTS12092003_151126-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R127539-E9914-DTS12092003_151137-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R127540-E4755-DTS12092003_151148-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R127542-E12139-DTS12092003_151158-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R127544-E15807-DTS12092003_151209-pass2.pds physics event startrun beginrun endrun 
file add pdschain /cdat/sol532/disk1/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-1-R127545-E6457-DTS12092003_151220-pass2.pds physics event startrun beginrun endrun 

# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R126276-E1011-DTS30092003_081941-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R126288-E9328-DTS30092003_081952-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R126290-E12578-DTS30092003_082003-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R126292-E12787-DTS30092003_082013-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R126293-E12870-DTS30092003_082024-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R126294-E10976-DTS30092003_082034-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R126296-E11571-DTS30092003_082047-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R126298-E13010-DTS30092003_082057-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R126299-E13104-DTS30092003_082108-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R126300-E11851-DTS30092003_082119-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R126302-E12167-DTS30092003_082130-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R126304-E12876-DTS30092003_082140-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R126305-E12877-DTS30092003_082151-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R126308-E12956-DTS30092003_082202-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R126309-E14074-DTS30092003_082212-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R126310-E14554-DTS30092003_082223-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R126311-E3611-DTS30092003_082234-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R126314-E5671-DTS30092003_082245-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R126315-E11410-DTS30092003_082255-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R126316-E15572-DTS30092003_082306-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R126318-E12731-DTS30092003_082317-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R126322-E9895-DTS30092003_082328-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R126323-E16153-DTS30092003_082339-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R126325-E8981-DTS30092003_082350-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R126326-E15140-DTS30092003_082400-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R126329-E10764-DTS30092003_082411-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R126341-E2218-DTS30092003_082423-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R126344-E4147-DTS30092003_082434-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R126345-E11808-DTS30092003_082445-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R126347-E13027-DTS30092003_082455-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R126349-E14554-DTS30092003_082506-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R126352-E14956-DTS30092003_082517-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R126353-E16630-DTS30092003_082529-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R126354-E16074-DTS30092003_082540-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R126355-E16045-DTS30092003_082551-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R126356-E14483-DTS30092003_082601-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R126359-E14002-DTS30092003_082613-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R126361-E14347-DTS30092003_082624-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R126362-E15352-DTS30092003_082636-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R126364-E14697-DTS30092003_082647-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R126367-E11612-DTS30092003_082658-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R126369-E16580-DTS30092003_082709-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R126370-E17200-DTS30092003_082719-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R126371-E15272-DTS30092003_082730-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R126372-E17205-DTS30092003_082742-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R126373-E17370-DTS30092003_082752-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R126374-E16931-DTS30092003_082803-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R126376-E17463-DTS30092003_082814-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R126429-E7060-DTS30092003_082828-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R126431-E6506-DTS30092003_082839-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R126432-E7039-DTS30092003_082851-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R126433-E7401-DTS30092003_082902-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R126434-E7083-DTS30092003_082912-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R126436-E2045-DTS30092003_082924-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R126449-E3279-DTS30092003_082935-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R126451-E1594-DTS30092003_082946-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R126453-E784-DTS30092003_082957-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R126462-E2131-DTS30092003_083047-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R126464-E4706-DTS30092003_083058-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R126465-E6037-DTS30092003_083109-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R126467-E3414-DTS30092003_083120-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R126469-E7691-DTS30092003_083131-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R126496-E3627-DTS30092003_083146-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R126499-E1401-DTS30092003_083156-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R126503-E2570-DTS30092003_083208-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R126505-E7462-DTS30092003_083218-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R126506-E5247-DTS30092003_083229-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R126507-E4753-DTS30092003_083240-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R126508-E13437-DTS30092003_083251-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R126509-E11788-DTS30092003_083302-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R126510-E12789-DTS30092003_083312-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R126511-E4066-DTS30092003_083323-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R126512-E2482-DTS30092003_083334-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R126513-E4276-DTS30092003_083344-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R126514-E13161-DTS30092003_083355-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R126517-E11421-DTS30092003_083406-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R126520-E2982-DTS30092003_083417-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R126521-E2440-DTS30092003_083427-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R126522-E13370-DTS30092003_083438-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R126523-E13284-DTS30092003_083448-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R126527-E8315-DTS30092003_083459-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R126528-E1822-DTS30092003_083510-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R126531-E1589-DTS30092003_083520-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R126532-E14300-DTS30092003_083531-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R126535-E1616-DTS30092003_083543-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R126536-E13966-DTS30092003_083553-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R126538-E14356-DTS30092003_083604-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R126539-E15125-DTS30092003_083615-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R126540-E15251-DTS30092003_083626-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R126541-E14218-DTS30092003_083636-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R126542-E3631-DTS30092003_083647-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R126543-E10364-DTS30092003_083658-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R126546-E1902-DTS30092003_083708-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R126552-E15056-DTS30092003_083719-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R126555-E15883-DTS30092003_083741-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R126556-E16235-DTS30092003_083751-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R126557-E15585-DTS30092003_083802-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R126559-E14887-DTS30092003_083812-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R126562-E14096-DTS30092003_083823-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R126563-E16364-DTS30092003_083834-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R126564-E8344-DTS30092003_083844-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R126566-E1654-DTS30092003_083855-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R126568-E14889-DTS30092003_083906-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R126569-E16321-DTS30092003_083917-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R126572-E15296-DTS30092003_083928-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R126573-E15411-DTS30092003_083939-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R126575-E15208-DTS30092003_083949-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R126576-E16353-DTS30092003_084000-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R126577-E16464-DTS30092003_084011-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R126578-E13501-DTS30092003_084021-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R126579-E9680-DTS30092003_084032-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R126581-E11410-DTS30092003_084043-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R126676-E8094-DTS30092003_084100-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R126677-E2553-DTS30092003_084113-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R126679-E6549-DTS30092003_084124-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R126680-E13076-DTS30092003_084135-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R126682-E8865-DTS30092003_084145-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R126683-E13438-DTS30092003_084156-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R126684-E12219-DTS30092003_084207-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R126685-E11182-DTS30092003_084217-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R126688-E11012-DTS30092003_084228-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R126689-E13701-DTS30092003_084239-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R126690-E13004-DTS30092003_084249-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R126691-E8484-DTS30092003_084300-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R126692-E13670-DTS30092003_084311-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R126693-E12131-DTS30092003_084322-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R126695-E11864-DTS30092003_084332-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R126699-E10522-DTS30092003_084343-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R126701-E13402-DTS30092003_084354-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R126702-E13985-DTS30092003_084404-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R126703-E15760-DTS30092003_084415-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R126704-E16042-DTS30092003_084425-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R126706-E10658-DTS30092003_084436-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R126707-E15323-DTS30092003_084447-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R126709-E16440-DTS30092003_084458-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R126710-E2663-DTS30092003_084509-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R126711-E15200-DTS30092003_084520-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R126714-E13767-DTS30092003_084530-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R126716-E14161-DTS30092003_084541-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R126717-E14340-DTS30092003_084551-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R126718-E4292-DTS30092003_084602-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R126719-E10454-DTS30092003_084613-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R126720-E15679-DTS30092003_084623-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R126721-E3826-DTS30092003_084634-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R126722-E10093-DTS30092003_084645-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R126723-E15757-DTS30092003_084655-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R126725-E13009-DTS30092003_084706-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R126728-E15529-DTS30092003_084717-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R126729-E14930-DTS30092003_084728-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R126731-E15859-DTS30092003_084739-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R126732-E15819-DTS30092003_084750-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R126733-E15793-DTS30092003_084801-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R126735-E16092-DTS30092003_084822-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R126736-E15499-DTS30092003_084833-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R126737-E15787-DTS30092003_084843-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R126738-E14772-DTS30092003_084854-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R126740-E12223-DTS30092003_084905-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R126744-E12765-DTS30092003_084916-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R126745-E6322-DTS30092003_084926-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R126746-E15876-DTS30092003_084937-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R126747-E14893-DTS30092003_084948-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R126749-E13675-DTS30092003_084958-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R126776-E7620-DTS30092003_085010-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R126777-E7309-DTS30092003_085021-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R126778-E7785-DTS30092003_085032-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R126779-E6995-DTS30092003_085049-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R126782-E2119-DTS30092003_085100-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R126783-E4039-DTS30092003_085111-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R126814-E3427-DTS30092003_085123-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R126823-E7079-DTS30092003_085206-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R126824-E8337-DTS30092003_085217-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R126825-E8033-DTS30092003_085227-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R126831-E5120-DTS30092003_085238-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R126858-E13448-DTS30092003_085252-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R126859-E12433-DTS30092003_085303-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R126862-E8208-DTS30092003_085313-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R126866-E9993-DTS30092003_085324-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R126868-E13643-DTS30092003_085335-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R126869-E13592-DTS30092003_085346-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R126870-E13464-DTS30092003_085356-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R126871-E14188-DTS30092003_085407-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R126872-E13049-DTS30092003_085417-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R126874-E11673-DTS30092003_085428-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R126875-E7624-DTS30092003_085439-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R126877-E3290-DTS30092003_085450-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R126878-E13813-DTS30092003_085500-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R126879-E6935-DTS30092003_085511-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R126880-E3753-DTS30092003_085522-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R126881-E13241-DTS30092003_085533-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R126882-E12371-DTS30092003_085544-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R126883-E12466-DTS30092003_085554-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R126890-E11532-DTS30092003_085605-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R126892-E12929-DTS30092003_085616-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R126893-E9431-DTS30092003_085627-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R126894-E2777-DTS30092003_085637-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R126895-E14620-DTS30092003_085648-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R126906-E1007-DTS30092003_085659-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R126907-E2806-DTS30092003_085710-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R126909-E12795-DTS30092003_085721-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R126910-E14336-DTS30092003_085732-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R126911-E14608-DTS30092003_085743-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R126912-E8575-DTS30092003_085753-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R126913-E14839-DTS30092003_085804-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R126914-E15564-DTS30092003_085815-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R126915-E15895-DTS30092003_085826-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R126923-E6803-DTS30092003_085836-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R126925-E4983-DTS30092003_085847-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R126926-E14813-DTS30092003_085858-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R126929-E9406-DTS30092003_085909-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R126931-E15945-DTS30092003_085919-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R126932-E7826-DTS30092003_085930-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R126933-E15463-DTS30092003_085941-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R126934-E12230-DTS30092003_085951-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R126936-E13079-DTS30092003_090002-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R127251-E9273-DTS30092003_090036-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R127254-E9342-DTS30092003_090047-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R127257-E11206-DTS30092003_090058-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R127261-E11614-DTS30092003_090109-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R127262-E4847-DTS30092003_090122-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R127263-E6645-DTS30092003_090133-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R127264-E12434-DTS30092003_090144-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R127266-E10024-DTS30092003_090155-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R127267-E12590-DTS30092003_090206-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R127268-E12981-DTS30092003_090217-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R127269-E13009-DTS30092003_090227-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R127270-E13041-DTS30092003_090238-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R127271-E13173-DTS30092003_090249-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R127272-E14134-DTS30092003_090259-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R127273-E14041-DTS30092003_090310-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R127278-E7418-DTS30092003_090321-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R127279-E10034-DTS30092003_090332-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R127280-E9255-DTS30092003_090343-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R127283-E1976-DTS30092003_090354-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R127285-E16421-DTS30092003_090405-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R127287-E10943-DTS30092003_090416-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R127289-E16147-DTS30092003_090426-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R127290-E16511-DTS30092003_090437-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R127291-E16289-DTS30092003_090448-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R127294-E15735-DTS30092003_090458-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R127295-E15314-DTS30092003_090509-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R127296-E8864-DTS30092003_090520-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R127297-E16924-DTS30092003_090531-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R127304-E10119-DTS30092003_090542-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R127306-E7509-DTS30092003_090552-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R127307-E17117-DTS30092003_090603-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R127308-E29877-DTS30092003_090614-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R127312-E12680-DTS30092003_090625-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R127314-E16423-DTS30092003_090636-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R127315-E14716-DTS30092003_090646-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R127317-E13094-DTS30092003_090657-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R127318-E2052-DTS30092003_090708-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R127321-E1746-DTS30092003_090740-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R127322-E14821-DTS30092003_090751-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R127325-E8443-DTS30092003_090802-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R127327-E16412-DTS30092003_090813-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R127328-E15767-DTS30092003_090824-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R127329-E14879-DTS30092003_090834-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R127330-E15980-DTS30092003_090845-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R127425-E5355-DTS30092003_090900-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R127459-E7184-DTS30092003_090913-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R127460-E12053-DTS30092003_090924-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R127461-E12759-DTS30092003_090935-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R127462-E12861-DTS30092003_090945-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R127465-E11448-DTS30092003_090956-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R127467-E10032-DTS30092003_091006-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R127472-E7701-DTS30092003_091017-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R127473-E12015-DTS30092003_091028-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R127477-E9178-DTS30092003_091039-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R127478-E13166-DTS30092003_091054-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R127479-E13527-DTS30092003_091105-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R127481-E12863-DTS30092003_091116-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R127482-E12422-DTS30092003_091127-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R127483-E12355-DTS30092003_091137-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R127488-E7615-DTS30092003_091148-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R127489-E12465-DTS30092003_091200-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R127492-E15563-DTS30092003_091211-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R127493-E15901-DTS30092003_091221-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R127498-E4775-DTS30092003_091232-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R127499-E7250-DTS30092003_091243-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R127501-E1883-DTS30092003_091254-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R127502-E9350-DTS30092003_091305-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R127503-E2962-DTS30092003_091315-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R127504-E9923-DTS30092003_091326-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R127506-E13821-DTS30092003_091336-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R127507-E16353-DTS30092003_091347-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R127508-E17556-DTS30092003_091358-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R127509-E16119-DTS30092003_091409-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R127510-E9040-DTS30092003_091420-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R127512-E14797-DTS30092003_091430-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R127513-E14380-DTS30092003_091441-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R127518-E12860-DTS30092003_091452-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R127521-E11061-DTS30092003_091503-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R127523-E15995-DTS30092003_091514-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R127524-E15804-DTS30092003_091525-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R127525-E4522-DTS30092003_091535-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R127527-E7992-DTS30092003_091546-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R127531-E15975-DTS30092003_091557-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R127532-E15188-DTS30092003_091608-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R127534-E15778-DTS30092003_091619-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R127535-E4838-DTS30092003_091630-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R127536-E10491-DTS30092003_091640-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R127537-E15961-DTS30092003_091651-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R127538-E15752-DTS30092003_091702-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R127539-E9914-DTS30092003_091713-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R127540-E4755-DTS30092003_091724-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R127542-E12139-DTS30092003_091735-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R127544-E15807-DTS30092003_091746-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-2-R127545-E6457-DTS30092003_091757-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R126276-E1011-DTS20102003_132102-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R126288-E9328-DTS20102003_132113-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R126290-E12578-DTS20102003_132124-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R126292-E12787-DTS20102003_132134-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R126293-E12870-DTS20102003_132145-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R126294-E10976-DTS20102003_132156-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R126296-E11571-DTS20102003_132207-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R126298-E13010-DTS20102003_132217-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R126299-E13104-DTS20102003_132228-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R126300-E11851-DTS20102003_132239-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R126302-E12167-DTS20102003_132249-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R126304-E12876-DTS20102003_132300-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R126305-E12877-DTS20102003_132311-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R126308-E12956-DTS20102003_132322-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R126309-E14074-DTS20102003_132333-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R126310-E14554-DTS20102003_132343-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R126311-E3611-DTS20102003_132354-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R126314-E5671-DTS20102003_132405-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R126315-E11410-DTS20102003_132416-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R126316-E15572-DTS20102003_132427-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R126318-E12731-DTS20102003_132437-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R126322-E9895-DTS20102003_132448-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R126323-E16153-DTS20102003_132459-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R126325-E8981-DTS20102003_132510-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R126326-E15140-DTS20102003_132521-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R126329-E10764-DTS20102003_132533-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R126341-E2218-DTS20102003_132544-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R126344-E4147-DTS20102003_132555-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R126345-E11808-DTS20102003_132606-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R126347-E13027-DTS20102003_132617-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R126349-E14554-DTS20102003_132627-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R126352-E14956-DTS20102003_132638-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R126353-E16630-DTS20102003_132649-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R126354-E16074-DTS20102003_132700-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R126355-E16045-DTS20102003_132711-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R126356-E14483-DTS20102003_132721-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R126359-E14002-DTS20102003_132732-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R126361-E14347-DTS20102003_132743-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R126362-E15352-DTS20102003_132754-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R126364-E14697-DTS20102003_132805-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R126367-E11612-DTS20102003_132816-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R126369-E16580-DTS20102003_132827-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R126370-E17200-DTS20102003_132838-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R126371-E15272-DTS20102003_132848-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R126372-E17205-DTS20102003_132859-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R126373-E17370-DTS20102003_132910-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R126374-E16931-DTS20102003_132921-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R126376-E17463-DTS20102003_132932-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R126429-E7060-DTS20102003_132945-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R126431-E6506-DTS20102003_132956-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R126432-E7039-DTS20102003_133007-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R126433-E7401-DTS20102003_133018-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R126434-E7083-DTS20102003_133028-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R126436-E2045-DTS20102003_133039-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R126449-E3279-DTS20102003_133051-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R126451-E1594-DTS20102003_133101-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R126453-E784-DTS20102003_133112-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R126462-E2131-DTS20102003_133155-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R126464-E4706-DTS20102003_133206-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R126465-E6037-DTS20102003_133217-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R126467-E3414-DTS20102003_133228-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R126469-E7691-DTS20102003_133239-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R126496-E3627-DTS20102003_133253-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R126499-E1401-DTS20102003_133304-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R126503-E2570-DTS20102003_133315-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R126505-E7462-DTS20102003_133325-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R126506-E5247-DTS20102003_133336-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R126507-E4753-DTS20102003_133346-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R126508-E13437-DTS20102003_133357-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R126509-E11788-DTS20102003_133408-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R126510-E12789-DTS20102003_133419-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R126511-E4066-DTS20102003_133429-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R126512-E2482-DTS20102003_133440-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R126513-E4276-DTS20102003_133451-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R126514-E13161-DTS20102003_133502-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R126517-E11421-DTS20102003_133513-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R126520-E2982-DTS20102003_133524-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R126521-E2440-DTS20102003_133534-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R126522-E13370-DTS20102003_133545-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R126523-E13284-DTS20102003_133556-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R126527-E8315-DTS20102003_133606-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R126528-E1822-DTS20102003_133617-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R126531-E1589-DTS20102003_133628-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R126535-E1616-DTS20102003_133649-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R126536-E13966-DTS20102003_133700-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R126538-E14356-DTS20102003_133711-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R126539-E15125-DTS20102003_133721-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R126540-E15251-DTS20102003_133732-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R126541-E14218-DTS20102003_133742-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R126542-E3631-DTS20102003_133753-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R126543-E10364-DTS20102003_133804-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R126546-E1902-DTS20102003_133814-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R126552-E15056-DTS20102003_133825-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R126554-E16195-DTS20102003_133836-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R126555-E15883-DTS20102003_133847-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R126556-E16235-DTS20102003_133858-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R126557-E15585-DTS20102003_133908-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R126559-E14887-DTS20102003_133919-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R126562-E14096-DTS20102003_133930-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R126563-E16364-DTS20102003_133940-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R126564-E8344-DTS20102003_133951-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R126566-E1654-DTS20102003_134001-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R126568-E14889-DTS20102003_134012-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R126569-E16321-DTS20102003_134023-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R126572-E15296-DTS20102003_134034-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R126573-E15411-DTS20102003_134045-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R126575-E15208-DTS20102003_134056-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R126576-E16353-DTS20102003_134106-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R126577-E16464-DTS20102003_134117-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R126578-E13501-DTS20102003_134128-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R126579-E9680-DTS20102003_134138-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R126581-E11410-DTS20102003_134149-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R126676-E8094-DTS20102003_134207-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R126677-E2553-DTS20102003_134219-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R126679-E6549-DTS20102003_134229-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R126680-E13076-DTS20102003_134240-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R126682-E8865-DTS20102003_134251-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R126683-E13438-DTS20102003_134301-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R126684-E12219-DTS20102003_134312-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R126685-E11182-DTS20102003_134323-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R126688-E11012-DTS20102003_134334-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R126689-E13701-DTS20102003_134344-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R126690-E13004-DTS20102003_134355-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R126691-E8484-DTS20102003_134406-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R126692-E13670-DTS20102003_134417-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R126693-E12131-DTS20102003_134427-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R126695-E11864-DTS20102003_134438-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R126699-E10522-DTS20102003_134449-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R126701-E13402-DTS20102003_134500-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R126702-E13985-DTS20102003_134510-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R126703-E15760-DTS20102003_134521-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R126704-E16042-DTS20102003_134532-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R126706-E10658-DTS20102003_134543-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R126707-E15323-DTS20102003_134553-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R126709-E16440-DTS20102003_134604-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R126710-E2663-DTS20102003_134615-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R126711-E15200-DTS20102003_134625-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R126714-E13767-DTS20102003_134636-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R126716-E14161-DTS20102003_134647-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R126717-E14340-DTS20102003_134658-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R126718-E4292-DTS20102003_134708-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R126719-E10454-DTS20102003_134719-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R126720-E15679-DTS20102003_134730-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R126721-E3826-DTS20102003_134741-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R126722-E10093-DTS20102003_134752-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R126723-E15757-DTS20102003_134802-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R126725-E13009-DTS20102003_134813-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R126728-E15529-DTS20102003_134824-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R126729-E14930-DTS20102003_134835-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R126731-E15859-DTS20102003_134846-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R126732-E15819-DTS20102003_134857-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R126733-E15793-DTS20102003_134908-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R126734-E16375-DTS20102003_134919-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R126735-E16092-DTS20102003_134929-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R126736-E15499-DTS20102003_134940-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R126737-E15787-DTS20102003_134951-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R126738-E14772-DTS20102003_135002-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R126740-E12223-DTS20102003_135012-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R126744-E12765-DTS20102003_135023-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R126745-E6322-DTS20102003_135034-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R126746-E15876-DTS20102003_135045-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R126747-E14893-DTS20102003_135055-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R126749-E13675-DTS20102003_135106-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R126776-E7620-DTS20102003_135118-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R126777-E7309-DTS20102003_135129-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R126778-E7785-DTS20102003_135140-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R126779-E6995-DTS20102003_135150-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R126782-E2119-DTS20102003_135201-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R126783-E4039-DTS20102003_135212-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R126814-E3427-DTS20102003_135224-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R126823-E7079-DTS20102003_135307-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R126824-E8337-DTS20102003_135317-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R126825-E8033-DTS20102003_135328-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R126831-E5120-DTS20102003_135339-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R126858-E13448-DTS20102003_135353-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R126859-E12433-DTS20102003_135404-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R126862-E8208-DTS20102003_135414-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R126866-E9993-DTS20102003_135425-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R126868-E13643-DTS20102003_135436-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R126869-E13592-DTS20102003_135447-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R126870-E13464-DTS20102003_135457-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R126871-E14188-DTS20102003_135508-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R126872-E13049-DTS20102003_135519-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R126874-E11673-DTS20102003_135529-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R126875-E7624-DTS20102003_135540-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R126877-E3290-DTS20102003_135551-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R126878-E13813-DTS20102003_135602-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R126879-E6935-DTS20102003_135617-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R126880-E3753-DTS20102003_135628-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R126881-E13241-DTS20102003_135638-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R126882-E12371-DTS20102003_135649-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R126883-E12466-DTS20102003_135700-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R126890-E11532-DTS20102003_135710-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R126892-E12929-DTS20102003_135721-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R126893-E9431-DTS20102003_135732-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R126894-E2777-DTS20102003_135743-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R126895-E14620-DTS20102003_135753-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R126906-E1007-DTS20102003_135804-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R126907-E2806-DTS20102003_135815-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R126909-E12795-DTS20102003_135826-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R126910-E14336-DTS20102003_135837-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R126911-E14608-DTS20102003_135847-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R126912-E8575-DTS20102003_135858-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R126913-E14839-DTS20102003_135909-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R126914-E15564-DTS20102003_135919-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R126915-E15895-DTS20102003_135930-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R126923-E6803-DTS20102003_135941-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R126925-E4983-DTS20102003_135952-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R126926-E14813-DTS20102003_140003-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R126929-E9406-DTS20102003_140014-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R126931-E15945-DTS20102003_140024-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R126932-E7826-DTS20102003_140035-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R126933-E15463-DTS20102003_140046-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R126934-E12230-DTS20102003_140056-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R126936-E13079-DTS20102003_140107-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R127251-E9273-DTS20102003_140144-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R127254-E9342-DTS20102003_140155-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R127257-E11206-DTS20102003_140206-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R127261-E11614-DTS20102003_140217-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R127262-E4847-DTS20102003_140228-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R127263-E6645-DTS20102003_140238-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R127264-E12434-DTS20102003_140249-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R127266-E10024-DTS20102003_140300-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R127267-E12590-DTS20102003_140310-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R127268-E12981-DTS20102003_140321-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R127269-E13009-DTS20102003_140332-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R127270-E13041-DTS20102003_140342-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R127271-E13173-DTS20102003_140353-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R127272-E14134-DTS20102003_140404-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R127273-E14041-DTS20102003_140415-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R127278-E7418-DTS20102003_140426-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R127279-E10034-DTS20102003_140437-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R127280-E9255-DTS20102003_140447-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R127283-E1976-DTS20102003_140458-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R127285-E16421-DTS20102003_140509-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R127287-E10943-DTS20102003_140520-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R127289-E16147-DTS20102003_140530-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R127290-E16511-DTS20102003_140541-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R127291-E16289-DTS20102003_140551-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R127294-E15735-DTS20102003_140602-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R127295-E15314-DTS20102003_140613-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R127296-E8864-DTS20102003_140624-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R127297-E16924-DTS20102003_140634-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R127304-E10119-DTS20102003_140646-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R127306-E7509-DTS20102003_140656-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R127307-E17117-DTS20102003_140707-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R127308-E29877-DTS20102003_140718-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R127312-E12680-DTS20102003_140729-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R127314-E16423-DTS20102003_140739-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R127315-E14716-DTS20102003_140750-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R127317-E13094-DTS20102003_140801-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R127318-E2052-DTS20102003_140812-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R127319-E16029-DTS20102003_140822-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R127320-E12114-DTS20102003_140833-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R127321-E1746-DTS20102003_140844-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R127322-E14821-DTS20102003_140855-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R127325-E8443-DTS20102003_140905-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R127327-E16412-DTS20102003_140916-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R127328-E15767-DTS20102003_140926-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R127329-E14879-DTS20102003_140937-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R127330-E15980-DTS20102003_140948-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R127425-E5355-DTS20102003_141005-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R127459-E7184-DTS20102003_141018-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R127460-E12053-DTS20102003_141028-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R127461-E12759-DTS20102003_141039-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R127462-E12861-DTS20102003_141050-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R127465-E11448-DTS20102003_141101-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R127467-E10032-DTS20102003_141112-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R127472-E7701-DTS20102003_141123-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R127473-E12015-DTS20102003_141134-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R127477-E9178-DTS20102003_141145-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R127478-E13166-DTS20102003_141156-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R127479-E13527-DTS20102003_141207-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R127481-E12863-DTS20102003_141218-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R127482-E12422-DTS20102003_141228-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R127483-E12355-DTS20102003_141239-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R127488-E7615-DTS20102003_141250-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R127489-E12465-DTS20102003_141301-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R127492-E15563-DTS20102003_141312-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R127493-E15901-DTS20102003_141323-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R127498-E4775-DTS20102003_141334-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R127499-E7250-DTS20102003_141345-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R127501-E1883-DTS20102003_141356-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R127502-E9350-DTS20102003_141407-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R127503-E2962-DTS20102003_141417-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R127504-E9923-DTS20102003_141428-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R127506-E13821-DTS20102003_141438-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R127507-E16353-DTS20102003_141449-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R127508-E17556-DTS20102003_141500-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R127509-E16119-DTS20102003_141511-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R127510-E9040-DTS20102003_141522-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R127512-E14797-DTS20102003_141533-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R127513-E14380-DTS20102003_141543-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R127518-E12860-DTS20102003_141554-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R127521-E11061-DTS20102003_141605-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R127523-E15995-DTS20102003_141616-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R127524-E15804-DTS20102003_141627-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R127525-E4522-DTS20102003_141638-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R127527-E7992-DTS20102003_141648-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R127531-E15975-DTS20102003_141659-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R127532-E15188-DTS20102003_141710-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R127534-E15778-DTS20102003_141721-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R127535-E4838-DTS20102003_141731-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R127536-E10491-DTS20102003_141742-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R127537-E15961-DTS20102003_141753-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R127538-E15752-DTS20102003_141804-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R127539-E9914-DTS20102003_141814-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R127540-E4755-DTS20102003_141825-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R127542-E12139-DTS20102003_141836-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R127544-E15807-DTS20102003_141847-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol532/disk2/c3mc/data21/ups2s/output/y2s-Apr16_03_MC-FL-3-R127545-E6457-DTS20102003_141858-pass2.pds physics event startrun beginrun endrun

go
