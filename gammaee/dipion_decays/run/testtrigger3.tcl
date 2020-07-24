default prompt off
exception continueEventLoop on

module sel HbookHistogramModule
hbook file ../rzn/testtrigger3.rzn
hbook init

run_file $env(C3_SCRIPTS)/runOnPass2.tcl

prod sel DBEventHeaderProd
prod sel CesrBeamEnergyProd
prod sel EventPropertiesProd
prod sel EventTypeProd

proc sel Level4Proc
proc desel Level4Proc
proc sel ../build_SunOS/shlib/TriggerSimulator

source_format sel PDSSourceFormat
source create pdschain

file add pdschain /cdat/sol221/disk1/c3mc/data7/cont/output/cont-cleo3_MCPS2_Jan30_2002-MN-1-R112259-E1847-pass2.pds event
file add pdschain /cdat/sol221/disk1/c3mc/data7/cont/output/cont-cleo3_MCPS2_Jan30_2002-MN-1-R112260-E1868-pass2.pds event
file add pdschain /cdat/sol221/disk1/c3mc/data7/cont/output/cont-cleo3_MCPS2_Jan30_2002-MN-1-R112263-E1302-pass2.pds event
file add pdschain /cdat/sol221/disk1/c3mc/data7/cont/output/cont-cleo3_MCPS2_Jan30_2002-MN-1-R112264-E1398-pass2.pds event
file add pdschain /cdat/sol221/disk1/c3mc/data7/cont/output/cont-cleo3_MCPS2_Jan30_2002-MN-1-R112265-E1784-pass2.pds event
file add pdschain /cdat/sol221/disk1/c3mc/data7/cont/output/cont-cleo3_MCPS2_Jan30_2002-MN-1-R112269-E652-pass2.pds event
file add pdschain /cdat/sol221/disk1/c3mc/data7/cont/output/cont-cleo3_MCPS2_Jan30_2002-MN-1-R112276-E723-pass2.pds event
file add pdschain /cdat/sol221/disk1/c3mc/data7/cont/output/cont-cleo3_MCPS2_Jan30_2002-MN-1-R112279-E1077-pass2.pds event
file add pdschain /cdat/sol221/disk1/c3mc/data7/cont/output/cont-cleo3_MCPS2_Jan30_2002-MN-1-R112281-E733-pass2.pds event
file add pdschain /cdat/sol221/disk1/c3mc/data7/cont/output/cont-cleo3_MCPS2_Jan30_2002-MN-1-R112283-E1279-pass2.pds event
file add pdschain /cdat/sol221/disk1/c3mc/data7/cont/output/cont-cleo3_MCPS2_Jan30_2002-MN-1-R112287-E1081-pass2.pds event
file add pdschain /cdat/sol221/disk1/c3mc/data7/cont/output/cont-cleo3_MCPS2_Jan30_2002-MN-1-R112290-E282-pass2.pds event
file add pdschain /cdat/sol221/disk1/c3mc/data7/cont/output/cont-cleo3_MCPS2_Jan30_2002-MN-1-R112293-E787-pass2.pds event
file add pdschain /cdat/sol221/disk1/c3mc/data7/cont/output/cont-cleo3_MCPS2_Jan30_2002-MN-1-R112295-E184-pass2.pds event
file add pdschain /cdat/sol221/disk1/c3mc/data7/cont/output/cont-cleo3_MCPS2_Jan30_2002-MN-1-R112299-E607-pass2.pds event
file add pdschain /cdat/sol221/disk1/c3mc/data7/cont/output/cont-cleo3_MCPS2_Jan30_2002-MN-1-R112321-E466-pass2.pds event
file add pdschain /cdat/sol221/disk1/c3mc/data7/cont/output/cont-cleo3_MCPS2_Jan30_2002-MN-1-R112322-E581-pass2.pds event
file add pdschain /cdat/sol221/disk1/c3mc/data7/cont/output/cont-cleo3_MCPS2_Jan30_2002-MN-1-R112325-E1171-pass2.pds event
file add pdschain /cdat/sol221/disk1/c3mc/data7/cont/output/cont-cleo3_MCPS2_Jan30_2002-MN-1-R112329-E838-pass2.pds event
file add pdschain /cdat/sol221/disk1/c3mc/data7/cont/output/cont-cleo3_MCPS2_Jan30_2002-MN-1-R112332-E739-pass2.pds event
file add pdschain /cdat/sol221/disk1/c3mc/data7/cont/output/cont-cleo3_MCPS2_Jan30_2002-MN-1-R112334-E1264-pass2.pds event
file add pdschain /cdat/sol221/disk1/c3mc/data7/cont/output/cont-cleo3_MCPS2_Jan30_2002-MN-1-R112335-E1757-pass2.pds event
file add pdschain /cdat/sol221/disk1/c3mc/data7/cont/output/cont-cleo3_MCPS2_Jan30_2002-MN-1-R112337-E1347-pass2.pds event
file add pdschain /cdat/sol221/disk1/c3mc/data7/cont/output/cont-cleo3_MCPS2_Jan30_2002-MN-1-R112338-E255-pass2.pds event
file add pdschain /cdat/sol221/disk1/c3mc/data7/cont/output/cont-cleo3_MCPS2_Jan30_2002-MN-1-R112340-E511-pass2.pds event
file add pdschain /cdat/sol221/disk1/c3mc/data7/cont/output/cont-cleo3_MCPS2_Jan30_2002-MN-1-R112342-E930-pass2.pds event
file add pdschain /cdat/sol221/disk1/c3mc/data7/cont/output/cont-cleo3_MCPS2_Jan30_2002-MN-1-R112343-E236-pass2.pds event
file add pdschain /cdat/sol221/disk1/c3mc/data7/cont/output/cont-cleo3_MCPS2_Jan30_2002-MN-1-R112345-E437-pass2.pds event
file add pdschain /cdat/sol221/disk1/c3mc/data7/cont/output/cont-cleo3_MCPS2_Jan30_2002-MN-1-R112348-E301-pass2.pds event
file add pdschain /cdat/sol221/disk1/c3mc/data7/cont/output/cont-cleo3_MCPS2_Jan30_2002-MN-1-R112351-E2045-pass2.pds event
file add pdschain /cdat/sol221/disk1/c3mc/data7/cont/output/cont-cleo3_MCPS2_Jan30_2002-MN-1-R112352-E1953-pass2.pds event
file add pdschain /cdat/sol221/disk1/c3mc/data7/cont/output/cont-cleo3_MCPS2_Jan30_2002-MN-1-R112353-E1945-pass2.pds event
file add pdschain /cdat/sol221/disk1/c3mc/data7/cont/output/cont-cleo3_MCPS2_Jan30_2002-MN-1-R112354-E1698-pass2.pds event
file add pdschain /cdat/sol221/disk1/c3mc/data7/cont/output/cont-cleo3_MCPS2_Jan30_2002-MN-1-R112357-E1863-pass2.pds event
file add pdschain /cdat/sol221/disk1/c3mc/data7/cont/output/cont-cleo3_MCPS2_Jan30_2002-MN-1-R112358-E2024-pass2.pds event
file add pdschain /cdat/sol221/disk1/c3mc/data7/cont/output/cont-cleo3_MCPS2_Jan30_2002-MN-1-R112359-E1271-pass2.pds event
file add pdschain /cdat/sol221/disk1/c3mc/data7/cont/output/cont-cleo3_MCPS2_Jan30_2002-MN-1-R112360-E1221-pass2.pds event
file add pdschain /cdat/sol221/disk1/c3mc/data7/cont/output/cont-cleo3_MCPS2_Jan30_2002-MN-1-R112361-E179-pass2.pds event
file add pdschain /cdat/sol221/disk1/c3mc/data7/cont/output/cont-cleo3_MCPS2_Jan30_2002-MN-1-R112362-E1272-pass2.pds event
file add pdschain /cdat/sol221/disk1/c3mc/data7/cont/output/cont-cleo3_MCPS2_Jan30_2002-MN-1-R112365-E1959-pass2.pds event
file add pdschain /cdat/sol221/disk1/c3mc/data7/cont/output/cont-cleo3_MCPS2_Jan30_2002-MN-1-R112366-E1853-pass2.pds event
file add pdschain /cdat/sol221/disk1/c3mc/data7/cont/output/cont-cleo3_MCPS2_Jan30_2002-MN-1-R112367-E1837-pass2.pds event
file add pdschain /cdat/sol221/disk1/c3mc/data7/cont/output/cont-cleo3_MCPS2_Jan30_2002-MN-1-R112369-E1254-pass2.pds event
file add pdschain /cdat/sol221/disk1/c3mc/data7/cont/output/cont-cleo3_MCPS2_Jan30_2002-MN-1-R112372-E1404-pass2.pds event
file add pdschain /cdat/sol221/disk1/c3mc/data7/cont/output/cont-cleo3_MCPS2_Jan30_2002-MN-1-R112373-E1153-pass2.pds event
file add pdschain /cdat/sol221/disk1/c3mc/data7/cont/output/cont-cleo3_MCPS2_Jan30_2002-MN-1-R112374-E1874-pass2.pds event
file add pdschain /cdat/sol221/disk1/c3mc/data7/cont/output/cont-cleo3_MCPS2_Jan30_2002-MN-1-R112377-E1322-pass2.pds event
file add pdschain /cdat/sol221/disk1/c3mc/data7/cont/output/cont-cleo3_MCPS2_Jan30_2002-MN-1-R112378-E345-pass2.pds event
file add pdschain /cdat/sol221/disk1/c3mc/data7/cont/output/cont-cleo3_MCPS2_Jan30_2002-MN-1-R112381-E1314-pass2.pds event
file add pdschain /cdat/sol221/disk1/c3mc/data7/cont/output/cont-cleo3_MCPS2_Jan30_2002-MN-1-R112383-E1948-pass2.pds event
file add pdschain /cdat/sol221/disk1/c3mc/data7/cont/output/cont-cleo3_MCPS2_Jan30_2002-MN-1-R112389-E1416-pass2.pds event
file add pdschain /cdat/sol221/disk1/c3mc/data7/cont/output/cont-cleo3_MCPS2_Jan30_2002-MN-1-R112390-E207-pass2.pds event
file add pdschain /cdat/sol221/disk1/c3mc/data7/cont/output/cont-cleo3_MCPS2_Jan30_2002-MN-1-R112391-E1051-pass2.pds event
file add pdschain /cdat/sol221/disk1/c3mc/data7/cont/output/cont-cleo3_MCPS2_Jan30_2002-MN-1-R112392-E869-pass2.pds event
file add pdschain /cdat/sol221/disk1/c3mc/data7/cont/output/cont-cleo3_MCPS2_Jan30_2002-MN-1-R112393-E349-pass2.pds event
file add pdschain /cdat/sol221/disk1/c3mc/data7/cont/output/cont-cleo3_MCPS2_Jan30_2002-MN-1-R112396-E1198-pass2.pds event
file add pdschain /cdat/sol221/disk1/c3mc/data7/cont/output/cont-cleo3_MCPS2_Jan30_2002-MN-1-R112397-E1957-pass2.pds event
file add pdschain /cdat/sol221/disk1/c3mc/data7/cont/output/cont-cleo3_MCPS2_Jan30_2002-MN-1-R112398-E1099-pass2.pds event
file add pdschain /cdat/sol221/disk1/c3mc/data7/cont/output/cont-cleo3_MCPS2_Jan30_2002-MN-1-R112399-E1409-pass2.pds event
file add pdschain /cdat/sol221/disk1/c3mc/data7/cont/output/cont-cleo3_MCPS2_Jan30_2002-MN-1-R112400-E1973-pass2.pds event
file add pdschain /cdat/sol221/disk1/c3mc/data7/cont/output/cont-cleo3_MCPS2_Jan30_2002-MN-1-R112405-E1606-pass2.pds event
file add pdschain /cdat/sol221/disk1/c3mc/data7/cont/output/cont-cleo3_MCPS2_Jan30_2002-MN-1-R112406-E1109-pass2.pds event
file add pdschain /cdat/sol221/disk1/c3mc/data7/cont/output/cont-cleo3_MCPS2_Jan30_2002-MN-1-R112408-E181-pass2.pds event
file add pdschain /cdat/sol221/disk1/c3mc/data7/cont/output/cont-cleo3_MCPS2_Jan30_2002-MN-1-R112409-E1444-pass2.pds event
file add pdschain /cdat/sol221/disk1/c3mc/data7/cont/output/cont-cleo3_MCPS2_Jan30_2002-MN-1-R112414-E189-pass2.pds event
file add pdschain /cdat/sol221/disk1/c3mc/data7/cont/output/cont-cleo3_MCPS2_Jan30_2002-MN-1-R112415-E1174-pass2.pds event
file add pdschain /cdat/sol221/disk1/c3mc/data7/cont/output/cont-cleo3_MCPS2_Jan30_2002-MN-1-R112416-E1364-pass2.pds event
file add pdschain /cdat/sol221/disk1/c3mc/data7/cont/output/cont-cleo3_MCPS2_Jan30_2002-MN-1-R112417-E727-pass2.pds event
file add pdschain /cdat/sol221/disk1/c3mc/data7/cont/output/cont-cleo3_MCPS2_Jan30_2002-MN-1-R112420-E1920-pass2.pds event
file add pdschain /cdat/sol221/disk1/c3mc/data7/cont/output/cont-cleo3_MCPS2_Jan30_2002-MN-1-R112421-E1978-pass2.pds event
file add pdschain /cdat/sol221/disk1/c3mc/data7/cont/output/cont-cleo3_MCPS2_Jan30_2002-MN-1-R112422-E1963-pass2.pds event
file add pdschain /cdat/sol221/disk1/c3mc/data7/cont/output/cont-cleo3_MCPS2_Jan30_2002-MN-1-R112423-E732-pass2.pds event
file add pdschain /cdat/sol221/disk1/c3mc/data7/cont/output/cont-cleo3_MCPS2_Jan30_2002-MN-1-R112424-E233-pass2.pds event
file add pdschain /cdat/sol221/disk1/c3mc/data7/cont/output/cont-cleo3_MCPS2_Jan30_2002-MN-1-R112425-E1992-pass2.pds event
file add pdschain /cdat/sol221/disk1/c3mc/data7/cont/output/cont-cleo3_MCPS2_Jan30_2002-MN-1-R112426-E1808-pass2.pds event
file add pdschain /cdat/sol221/disk1/c3mc/data7/cont/output/cont-cleo3_MCPS2_Jan30_2002-MN-1-R112427-E1789-pass2.pds event
file add pdschain /cdat/sol221/disk1/c3mc/data7/cont/output/cont-cleo3_MCPS2_Jan30_2002-MN-1-R112428-E574-pass2.pds event
file add pdschain /cdat/sol221/disk1/c3mc/data7/cont/output/cont-cleo3_MCPS2_Jan30_2002-MN-1-R112431-E1887-pass2.pds event
file add pdschain /cdat/sol221/disk1/c3mc/data7/cont/output/cont-cleo3_MCPS2_Jan30_2002-MN-1-R112432-E1749-pass2.pds event
file add pdschain /cdat/sol221/disk1/c3mc/data7/cont/output/cont-cleo3_MCPS2_Jan30_2002-MN-1-R112433-E1377-pass2.pds event
file add pdschain /cdat/sol221/disk1/c3mc/data7/cont/output/cont-cleo3_MCPS2_Jan30_2002-MN-1-R112434-E709-pass2.pds event
file add pdschain /cdat/sol221/disk1/c3mc/data7/cont/output/cont-cleo3_MCPS2_Jan30_2002-MN-1-R112435-E409-pass2.pds event
file add pdschain /cdat/sol221/disk1/c3mc/data7/cont/output/cont-cleo3_MCPS2_Jan30_2002-MN-1-R112437-E236-pass2.pds event
file add pdschain /cdat/sol221/disk1/c3mc/data7/cont/output/cont-cleo3_MCPS2_Jan30_2002-MN-1-R112438-E1088-pass2.pds event
file add pdschain /cdat/sol221/disk1/c3mc/data7/cont/output/cont-cleo3_MCPS2_Jan30_2002-MN-1-R112439-E237-pass2.pds event
file add pdschain /cdat/sol221/disk1/c3mc/data7/cont/output/cont-cleo3_MCPS2_Jan30_2002-MN-1-R112441-E1873-pass2.pds event
file add pdschain /cdat/sol221/disk1/c3mc/data7/cont/output/cont-cleo3_MCPS2_Jan30_2002-MN-1-R112442-E1866-pass2.pds event
file add pdschain /cdat/sol221/disk1/c3mc/data7/cont/output/cont-cleo3_MCPS2_Jan30_2002-MN-1-R112444-E1203-pass2.pds event
file add pdschain /cdat/sol221/disk1/c3mc/data7/cont/output/cont-cleo3_MCPS2_Jan30_2002-MN-1-R112445-E1939-pass2.pds event
file add pdschain /cdat/sol221/disk1/c3mc/data7/cont/output/cont-cleo3_MCPS2_Jan30_2002-MN-1-R112448-E1526-pass2.pds event
file add pdschain /cdat/sol221/disk1/c3mc/data7/cont/output/cont-cleo3_MCPS2_Jan30_2002-MN-1-R112454-E2144-pass2.pds event
file add pdschain /cdat/sol221/disk1/c3mc/data7/cont/output/cont-cleo3_MCPS2_Jan30_2002-MN-1-R112456-E2510-pass2.pds event
file add pdschain /cdat/sol221/disk1/c3mc/data7/cont/output/cont-cleo3_MCPS2_Jan30_2002-MN-1-R112457-E1487-pass2.pds event
file add pdschain /cdat/sol221/disk1/c3mc/data7/cont/output/cont-cleo3_MCPS2_Jan30_2002-MN-1-R112461-E2519-pass2.pds event
file add pdschain /cdat/sol221/disk1/c3mc/data7/cont/output/cont-cleo3_MCPS2_Jan30_2002-MN-1-R112463-E2483-pass2.pds event
file add pdschain /cdat/sol221/disk1/c3mc/data7/cont/output/cont-cleo3_MCPS2_Jan30_2002-MN-1-R112464-E2496-pass2.pds event
file add pdschain /cdat/sol221/disk1/c3mc/data7/cont/output/cont-cleo3_MCPS2_Jan30_2002-MN-1-R112466-E2038-pass2.pds event
file add pdschain /cdat/sol221/disk1/c3mc/data7/cont/output/cont-cleo3_MCPS2_Jan30_2002-MN-1-R112469-E2482-pass2.pds event
file add pdschain /cdat/sol221/disk1/c3mc/data7/cont/output/cont-cleo3_MCPS2_Jan30_2002-MN-1-R112475-E1204-pass2.pds event
file add pdschain /cdat/sol221/disk1/c3mc/data7/cont/output/cont-cleo3_MCPS2_Jan30_2002-MN-1-R112477-E1682-pass2.pds event

report level INFO
go

summary
hbook terminate
exit
