default prompt off
exception continueEventLoop on

module sel HbookHistogramModule
hbook file /cdat/sol300/disk5/mccann/mcres16_34.rzn
hbook init

run_file $env(C3_SCRIPTS)/runOnPass2.tcl

prod sel EventPropertiesProd
prod sel EventTypeProd

prod sel CustomBeamEnergyProd
param CustomBeamEnergyProd BeamEnergy 5.17765

source_format sel BeamSpotFileSourceFormat
file in $env(C3_INFO)/mc/zeromc.beamspot beginrun

source create pdschain
source_format sel PDSSourceFormat
file add pdschain /cdat/sol221/disk4/c3mc/data16/y3s/output/y3s-Jun27_02_MC-FL-1-R122102-E7974-DTS17092002_145204-pass2.pds physics event beginrun startrun endrun
file add pdschain /cdat/sol221/disk4/c3mc/data16/y3s/output/y3s-Jun27_02_MC-FL-1-R122105-E6666-DTS17092002_145216-pass2.pds physics event beginrun startrun endrun
file add pdschain /cdat/sol221/disk4/c3mc/data16/y3s/output/y3s-Jun27_02_MC-FL-1-R122108-E1033-DTS17092002_145228-pass2.pds physics event beginrun startrun endrun
file add pdschain /cdat/sol221/disk4/c3mc/data16/y3s/output/y3s-Jun27_02_MC-FL-1-R122109-E4308-DTS17092002_145241-pass2.pds physics event beginrun startrun endrun
file add pdschain /cdat/sol221/disk4/c3mc/data16/y3s/output/y3s-Jun27_02_MC-FL-1-R122111-E5118-DTS17092002_145253-pass2.pds physics event beginrun startrun endrun
file add pdschain /cdat/sol221/disk4/c3mc/data16/y3s/output/y3s-Jun27_02_MC-FL-1-R122112-E8174-DTS17092002_145304-pass2.pds physics event beginrun startrun endrun
file add pdschain /cdat/sol221/disk4/c3mc/data16/y3s/output/y3s-Jun27_02_MC-FL-1-R122114-E2178-DTS17092002_145317-pass2.pds physics event beginrun startrun endrun
file add pdschain /cdat/sol221/disk4/c3mc/data16/y3s/output/y3s-Jun27_02_MC-FL-1-R122116-E2295-DTS17092002_145329-pass2.pds physics event beginrun startrun endrun
file add pdschain /cdat/sol221/disk4/c3mc/data16/y3s/output/y3s-Jun27_02_MC-FL-1-R122117-E7421-DTS17092002_145342-pass2.pds physics event beginrun startrun endrun
file add pdschain /cdat/sol221/disk4/c3mc/data16/y3s/output/y3s-Jun27_02_MC-FL-1-R122118-E5906-DTS17092002_145354-pass2.pds physics event beginrun startrun endrun

proc sel ../build_SunOS/shlib/Efficiency.so

go 
