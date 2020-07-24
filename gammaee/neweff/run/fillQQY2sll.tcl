default prompt off
exception continueEventLoop on

module sel LoadHbook4MModule
module sel HbookHistogramModule
hbook file ../rzn/qqy2sll.rzn
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
param Cuts wantLeptons true

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

go

