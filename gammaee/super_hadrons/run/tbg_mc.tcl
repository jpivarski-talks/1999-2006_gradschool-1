default prompt off
exception continueEventLoop on

module sel HbookHistogramModule
hbook file ../rzn/tbg_mc_revamp3.rzn
hbook init

run_file $env(C3_SCRIPTS)/runOnPass2.tcl
run_file $env(C3_SCRIPTS)/CcHotList.tcl

prod sel DBEventHeaderProd
prod sel CesrBeamEnergyProd
prod sel EventPropertiesProd

proc sel EventTypeFilterProc
param EventTypeFilterProc Hadron true

proc sel ../build_SunOS/shlib/BeamGasFilterProc
param BeamGasFilterProc explicitBeamSpot true
param BeamGasFilterProc weightedZCut 1.
param BeamGasFilterProc neutralEnergyCut -1.

proc sel ../build_SunOS/shlib/TestBeamGas
param TestBeamGas explicitBeamSpot true
param TestBeamGas weightedZCut 1.

source_format sel PDSSourceFormat
source create pdschain
file add pdschain /cdat/sol221/disk5/c3mc/data16/cont/output/cont-Jun27_02_MC-MN-1-R121339-E261-pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol221/disk5/c3mc/data16/cont/output/cont-Jun27_02_MC-MN-1-R121340-E396-pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol221/disk5/c3mc/data16/cont/output/cont-Jun27_02_MC-MN-1-R121343-E315-pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol221/disk5/c3mc/data16/cont/output/cont-Jun27_02_MC-MN-1-R121344-E457-pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol221/disk5/c3mc/data16/cont/output/cont-Jun27_02_MC-MN-1-R121346-E501-pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol221/disk5/c3mc/data16/cont/output/cont-Jun27_02_MC-MN-1-R121347-E401-pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol221/disk5/c3mc/data16/cont/output/cont-Jun27_02_MC-MN-1-R121348-E761-pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol221/disk5/c3mc/data16/cont/output/cont-Jun27_02_MC-MN-1-R121349-E1635-pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol221/disk5/c3mc/data16/cont/output/cont-Jun27_02_MC-MN-1-R121361-E860-pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol221/disk5/c3mc/data16/cont/output/cont-Jun27_02_MC-MN-1-R121362-E417-pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol221/disk5/c3mc/data16/cont/output/cont-Jun27_02_MC-MN-1-R121365-E1539-pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol221/disk5/c3mc/data16/cont/output/cont-Jun27_02_MC-MN-1-R121369-E1109-pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol221/disk5/c3mc/data16/cont/output/cont-Jun27_02_MC-MN-1-R121370-E1677-pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol221/disk5/c3mc/data16/cont/output/cont-Jun27_02_MC-MN-1-R121373-E664-pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol221/disk5/c3mc/data16/cont/output/cont-Jun27_02_MC-MN-1-R121374-E1123-pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol221/disk5/c3mc/data16/cont/output/cont-Jun27_02_MC-MN-1-R121375-E944-pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol221/disk5/c3mc/data16/cont/output/cont-Jun27_02_MC-MN-1-R121378-E685-pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol221/disk5/c3mc/data16/cont/output/cont-Jun27_02_MC-MN-1-R121379-E909-pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol221/disk5/c3mc/data16/cont/output/cont-Jun27_02_MC-MN-1-R121381-E1923-pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol221/disk5/c3mc/data16/cont/output/cont-Jun27_02_MC-MN-1-R121382-E431-pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol221/disk5/c3mc/data16/cont/output/cont-Jun27_02_MC-MN-1-R121384-E805-pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol221/disk5/c3mc/data16/cont/output/cont-Jun27_02_MC-MN-1-R121385-E1993-pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol221/disk5/c3mc/data16/cont/output/cont-Jun27_02_MC-MN-1-R121387-E2077-pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol221/disk5/c3mc/data16/cont/output/cont-Jun27_02_MC-MN-1-R121390-E1721-pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol221/disk5/c3mc/data16/cont/output/cont-Jun27_02_MC-MN-1-R121391-E1825-pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol221/disk5/c3mc/data16/cont/output/cont-Jun27_02_MC-MN-1-R121394-E1997-pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol221/disk5/c3mc/data16/cont/output/cont-Jun27_02_MC-MN-1-R121395-E1892-pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol221/disk5/c3mc/data16/cont/output/cont-Jun27_02_MC-MN-1-R121396-E1929-pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol221/disk5/c3mc/data16/cont/output/cont-Jun27_02_MC-MN-1-R121397-E1985-pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol221/disk5/c3mc/data16/cont/output/cont-Jun27_02_MC-MN-1-R121398-E1979-pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol221/disk5/c3mc/data16/cont/output/cont-Jun27_02_MC-MN-1-R121399-E301-pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol221/disk5/c3mc/data16/cont/output/cont-Jun27_02_MC-MN-1-R121400-E651-pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol221/disk5/c3mc/data16/cont/output/cont-Jun27_02_MC-MN-1-R121401-E755-pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol221/disk5/c3mc/data16/cont/output/cont-Jun27_02_MC-MN-1-R121402-E1417-pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol221/disk5/c3mc/data16/cont/output/cont-Jun27_02_MC-MN-1-R121406-E2137-pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol221/disk5/c3mc/data16/cont/output/cont-Jun27_02_MC-MN-1-R121407-E1904-pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol221/disk5/c3mc/data16/cont/output/cont-Jun27_02_MC-MN-1-R121408-E2337-pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol221/disk5/c3mc/data16/cont/output/cont-Jun27_02_MC-MN-1-R121409-E2221-pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol221/disk5/c3mc/data16/cont/output/cont-Jun27_02_MC-MN-1-R121414-E1161-pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol221/disk5/c3mc/data16/cont/output/cont-Jun27_02_MC-MN-1-R121416-E2056-pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol221/disk5/c3mc/data16/cont/output/cont-Jun27_02_MC-MN-1-R121418-E351-pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol221/disk5/c3mc/data16/cont/output/cont-Jun27_02_MC-MN-1-R121419-E1725-pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol221/disk5/c3mc/data16/cont/output/cont-Jun27_02_MC-MN-1-R121420-E2264-pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol221/disk5/c3mc/data16/cont/output/cont-Jun27_02_MC-MN-1-R121421-E1373-pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol221/disk5/c3mc/data16/cont/output/cont-Jun27_02_MC-MN-1-R121422-E1075-pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol221/disk5/c3mc/data16/cont/output/cont-Jun27_02_MC-MN-1-R121424-E323-pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol221/disk5/c3mc/data16/cont/output/cont-Jun27_02_MC-MN-1-R121425-E1231-pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol221/disk5/c3mc/data16/cont/output/cont-Jun27_02_MC-MN-1-R121426-E977-pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol221/disk5/c3mc/data16/cont/output/cont-Jun27_02_MC-MN-1-R121427-E1353-pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol221/disk5/c3mc/data16/cont/output/cont-Jun27_02_MC-MN-1-R121428-E389-pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol221/disk5/c3mc/data16/cont/output/cont-Jun27_02_MC-MN-1-R121429-E1655-pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol221/disk5/c3mc/data16/cont/output/cont-Jun27_02_MC-MN-1-R121430-E860-pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol221/disk5/c3mc/data16/cont/output/cont-Jun27_02_MC-MN-1-R121432-E607-pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol221/disk5/c3mc/data16/cont/output/cont-Jun27_02_MC-MN-1-R121433-E1305-pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol221/disk5/c3mc/data16/cont/output/cont-Jun27_02_MC-MN-1-R121434-E2513-pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol221/disk5/c3mc/data16/cont/output/cont-Jun27_02_MC-MN-1-R121435-E1324-pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol221/disk5/c3mc/data16/cont/output/cont-Jun27_02_MC-MN-1-R121436-E1812-pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol221/disk5/c3mc/data16/cont/output/cont-Jun27_02_MC-MN-1-R121437-E1693-pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol221/disk5/c3mc/data16/cont/output/cont-Jun27_02_MC-MN-1-R121441-E289-pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol221/disk5/c3mc/data16/cont/output/cont-Jun27_02_MC-MN-1-R121442-E668-pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol221/disk5/c3mc/data16/cont/output/cont-Jun27_02_MC-MN-1-R121446-E1203-pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol221/disk5/c3mc/data16/cont/output/cont-Jun27_02_MC-MN-1-R121448-E2401-pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol221/disk5/c3mc/data16/cont/output/cont-Jun27_02_MC-MN-1-R121449-E2308-pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol221/disk5/c3mc/data16/cont/output/cont-Jun27_02_MC-MN-1-R121454-E1672-pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol221/disk5/c3mc/data16/cont/output/cont-Jun27_02_MC-MN-1-R121456-E1835-pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol221/disk5/c3mc/data16/cont/output/cont-Jun27_02_MC-MN-1-R121458-E2025-pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol221/disk5/c3mc/data16/cont/output/cont-Jun27_02_MC-MN-1-R121459-E929-pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol221/disk5/c3mc/data16/cont/output/cont-Jun27_02_MC-MN-1-R121474-E464-pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol221/disk5/c3mc/data16/cont/output/cont-Jun27_02_MC-MN-1-R121476-E2311-pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol221/disk5/c3mc/data16/cont/output/cont-Jun27_02_MC-MN-1-R121477-E2043-pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol221/disk5/c3mc/data16/cont/output/cont-Jun27_02_MC-MN-1-R121479-E2049-pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol221/disk5/c3mc/data16/cont/output/cont-Jun27_02_MC-MN-1-R121480-E799-pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol221/disk5/c3mc/data16/cont/output/cont-Jun27_02_MC-MN-1-R121519-E1733-pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol221/disk5/c3mc/data16/cont/output/cont-Jun27_02_MC-MN-1-R121523-E1495-pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol221/disk5/c3mc/data16/cont/output/cont-Jun27_02_MC-MN-1-R121525-E304-pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol221/disk5/c3mc/data16/cont/output/cont-Jun27_02_MC-MN-1-R121526-E1551-pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol221/disk5/c3mc/data16/cont/output/cont-Jun27_02_MC-MN-1-R121527-E2016-pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol221/disk5/c3mc/data16/cont/output/cont-Jun27_02_MC-MN-1-R121528-E1856-pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol221/disk5/c3mc/data16/cont/output/cont-Jun27_02_MC-MN-1-R121529-E1080-pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol221/disk5/c3mc/data16/cont/output/cont-Jun27_02_MC-MN-1-R121530-E1912-pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol221/disk5/c3mc/data16/cont/output/cont-Jun27_02_MC-MN-1-R121531-E1723-pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol221/disk5/c3mc/data16/cont/output/cont-Jun27_02_MC-MN-1-R121534-E1623-pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol221/disk5/c3mc/data16/cont/output/cont-Jun27_02_MC-MN-1-R121535-E2023-pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol221/disk5/c3mc/data16/cont/output/cont-Jun27_02_MC-MN-1-R121536-E2025-pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol221/disk5/c3mc/data16/cont/output/cont-Jun27_02_MC-MN-1-R121539-E925-pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol221/disk5/c3mc/data16/cont/output/cont-Jun27_02_MC-MN-1-R121540-E2037-pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol221/disk5/c3mc/data16/cont/output/cont-Jun27_02_MC-MN-1-R121542-E1161-pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol221/disk5/c3mc/data16/cont/output/cont-Jun27_02_MC-MN-1-R121543-E669-pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol221/disk5/c3mc/data16/cont/output/cont-Jun27_02_MC-MN-1-R121544-E2005-pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol221/disk5/c3mc/data16/cont/output/cont-Jun27_02_MC-MN-1-R121545-E2003-pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol221/disk5/c3mc/data16/cont/output/cont-Jun27_02_MC-MN-1-R121547-E1400-pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol221/disk5/c3mc/data16/cont/output/cont-Jun27_02_MC-MN-1-R121548-E1995-pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol221/disk5/c3mc/data16/cont/output/cont-Jun27_02_MC-MN-1-R121549-E2028-pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol221/disk5/c3mc/data16/cont/output/cont-Jun27_02_MC-MN-1-R121550-E1991-pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol221/disk5/c3mc/data16/cont/output/cont-Jun27_02_MC-MN-1-R121551-E1909-pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol221/disk5/c3mc/data16/cont/output/cont-Jun27_02_MC-MN-1-R121552-E899-pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol221/disk5/c3mc/data16/cont/output/cont-Jun27_02_MC-MN-1-R121553-E2433-pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol221/disk5/c3mc/data16/cont/output/cont-Jun27_02_MC-MN-1-R121554-E2424-pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol221/disk5/c3mc/data16/cont/output/cont-Jun27_02_MC-MN-1-R121555-E2493-pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol221/disk5/c3mc/data16/cont/output/cont-Jun27_02_MC-MN-1-R121556-E2537-pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol221/disk5/c3mc/data16/cont/output/cont-Jun27_02_MC-MN-1-R121557-E2389-pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol221/disk5/c3mc/data16/cont/output/cont-Jun27_02_MC-MN-1-R121558-E2656-pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol221/disk5/c3mc/data16/cont/output/cont-Jun27_02_MC-MN-1-R121559-E2417-pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol221/disk5/c3mc/data16/cont/output/cont-Jun27_02_MC-MN-1-R121560-E475-pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol221/disk5/c3mc/data16/cont/output/cont-Jun27_02_MC-MN-1-R121561-E2521-pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol221/disk5/c3mc/data16/cont/output/cont-Jun27_02_MC-MN-1-R121563-E2291-pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol221/disk5/c3mc/data16/cont/output/cont-Jun27_02_MC-MN-1-R121565-E2141-pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol221/disk5/c3mc/data16/cont/output/cont-Jun27_02_MC-MN-1-R121567-E1931-pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol221/disk5/c3mc/data16/cont/output/cont-Jun27_02_MC-MN-1-R121568-E1820-pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol221/disk5/c3mc/data16/cont/output/cont-Jun27_02_MC-MN-1-R121569-E2568-pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol221/disk5/c3mc/data16/cont/output/cont-Jun27_02_MC-MN-1-R121574-E969-pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol221/disk5/c3mc/data16/cont/output/cont-Jun27_02_MC-MN-1-R121576-E1819-pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol221/disk5/c3mc/data16/cont/output/cont-Jun27_02_MC-MN-1-R121579-E743-pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol221/disk5/c3mc/data16/cont/output/cont-Jun27_02_MC-MN-1-R121580-E1224-pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol221/disk5/c3mc/data16/cont/output/cont-Jun27_02_MC-MN-1-R121581-E2337-pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol221/disk5/c3mc/data16/cont/output/cont-Jun27_02_MC-MN-1-R121582-E316-pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol221/disk5/c3mc/data16/cont/output/cont-Jun27_02_MC-MN-1-R121585-E2020-pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol221/disk5/c3mc/data16/cont/output/cont-Jun27_02_MC-MN-1-R121588-E713-pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol221/disk5/c3mc/data16/cont/output/cont-Jun27_02_MC-MN-1-R121590-E400-pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol221/disk5/c3mc/data16/cont/output/cont-Jun27_02_MC-MN-1-R121592-E1779-pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol221/disk5/c3mc/data16/cont/output/cont-Jun27_02_MC-MN-1-R121593-E2225-pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol221/disk5/c3mc/data16/cont/output/cont-Jun27_02_MC-MN-1-R121595-E1883-pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol221/disk5/c3mc/data16/cont/output/cont-Jun27_02_MC-MN-1-R121608-E981-pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol221/disk5/c3mc/data16/cont/output/cont-Jun27_02_MC-MN-1-R121609-E1709-pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol221/disk5/c3mc/data16/cont/output/cont-Jun27_02_MC-MN-1-R121623-E357-pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol221/disk5/c3mc/data16/cont/output/cont-Jun27_02_MC-MN-1-R121624-E2236-pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol221/disk5/c3mc/data16/cont/output/cont-Jun27_02_MC-MN-1-R121628-E1719-pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol221/disk5/c3mc/data16/cont/output/cont-Jun27_02_MC-MN-1-R121631-E2105-pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol221/disk5/c3mc/data16/cont/output/cont-Jun27_02_MC-MN-1-R121633-E1825-pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol221/disk5/c3mc/data16/cont/output/cont-Jun27_02_MC-MN-1-R121636-E1792-pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol221/disk5/c3mc/data16/cont/output/cont-Jun27_02_MC-MN-1-R121637-E2319-pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol221/disk5/c3mc/data16/cont/output/cont-Jun27_02_MC-MN-1-R121638-E2188-pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol221/disk5/c3mc/data16/cont/output/cont-Jun27_02_MC-MN-1-R121639-E392-pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol221/disk5/c3mc/data16/cont/output/cont-Jun27_02_MC-MN-1-R121640-E2188-pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol221/disk5/c3mc/data16/cont/output/cont-Jun27_02_MC-MN-1-R121641-E1792-pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol221/disk5/c3mc/data16/cont/output/cont-Jun27_02_MC-MN-1-R121649-E731-pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol221/disk5/c3mc/data16/cont/output/cont-Jun27_02_MC-MN-1-R121650-E1433-pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol221/disk5/c3mc/data16/cont/output/cont-Jun27_02_MC-MN-1-R121651-E2323-pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol221/disk5/c3mc/data16/cont/output/cont-Jun27_02_MC-MN-1-R121652-E2368-pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol221/disk5/c3mc/data16/cont/output/cont-Jun27_02_MC-MN-1-R121653-E2053-pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol221/disk5/c3mc/data16/cont/output/cont-Jun27_02_MC-MN-1-R121656-E1160-pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol221/disk5/c3mc/data16/cont/output/cont-Jun27_02_MC-MN-1-R121678-E777-pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol221/disk5/c3mc/data16/cont/output/cont-Jun27_02_MC-MN-1-R121683-E2227-pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol221/disk5/c3mc/data16/cont/output/cont-Jun27_02_MC-MN-1-R121684-E2125-pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol221/disk5/c3mc/data16/cont/output/cont-Jun27_02_MC-MN-1-R121687-E989-pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol221/disk5/c3mc/data16/cont/output/cont-Jun27_02_MC-MN-1-R121688-E1203-pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol221/disk5/c3mc/data16/cont/output/cont-Jun27_02_MC-MN-1-R121689-E2443-pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol221/disk5/c3mc/data16/cont/output/cont-Jun27_02_MC-MN-1-R121694-E2465-pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol221/disk5/c3mc/data16/cont/output/cont-Jun27_02_MC-MN-1-R121698-E1485-pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol221/disk5/c3mc/data16/cont/output/cont-Jun27_02_MC-MN-1-R121704-E464-pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol221/disk5/c3mc/data16/cont/output/cont-Jun27_02_MC-MN-1-R121705-E512-pass2.pds event startrun beginrun endrun physics

go 889128

hbook terminate
exit
