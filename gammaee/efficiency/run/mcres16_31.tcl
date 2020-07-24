default prompt off
exception continueEventLoop on

module sel HbookHistogramModule
hbook file /cdat/sol300/disk5/mccann/mcres16_31.rzn
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
file add pdschain /cdat/sol221/disk4/c3mc/data16/y3s/output/y3s-Jun27_02_MC-FL-1-R121996-E10047-DTS17092002_144542-pass2.pds physics event beginrun startrun endrun
file add pdschain /cdat/sol221/disk4/c3mc/data16/y3s/output/y3s-Jun27_02_MC-FL-1-R121997-E3278-DTS17092002_144554-pass2.pds physics event beginrun startrun endrun
file add pdschain /cdat/sol221/disk4/c3mc/data16/y3s/output/y3s-Jun27_02_MC-FL-1-R121999-E9267-DTS17092002_144607-pass2.pds physics event beginrun startrun endrun
file add pdschain /cdat/sol221/disk4/c3mc/data16/y3s/output/y3s-Jun27_02_MC-FL-1-R122001-E4513-DTS17092002_144619-pass2.pds physics event beginrun startrun endrun
file add pdschain /cdat/sol221/disk4/c3mc/data16/y3s/output/y3s-Jun27_02_MC-FL-1-R122003-E10052-DTS17092002_144631-pass2.pds physics event beginrun startrun endrun
file add pdschain /cdat/sol221/disk4/c3mc/data16/y3s/output/y3s-Jun27_02_MC-FL-1-R122006-E9358-DTS17092002_144643-pass2.pds physics event beginrun startrun endrun
file add pdschain /cdat/sol221/disk4/c3mc/data16/y3s/output/y3s-Jun27_02_MC-FL-1-R122007-E2100-DTS17092002_144655-pass2.pds physics event beginrun startrun endrun
file add pdschain /cdat/sol221/disk4/c3mc/data16/y3s/output/y3s-Jun27_02_MC-FL-1-R122066-E15-DTS17092002_144722-pass2.pds physics event beginrun startrun endrun
file add pdschain /cdat/sol221/disk4/c3mc/data16/y3s/output/y3s-Jun27_02_MC-FL-1-R122069-E276-DTS17092002_144734-pass2.pds physics event beginrun startrun endrun
file add pdschain /cdat/sol221/disk4/c3mc/data16/y3s/output/y3s-Jun27_02_MC-FL-1-R122070-E328-DTS17092002_144746-pass2.pds physics event beginrun startrun endrun

proc sel ../build_SunOS/shlib/Efficiency.so

go 
