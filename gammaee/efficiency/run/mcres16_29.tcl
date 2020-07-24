default prompt off
exception continueEventLoop on

module sel HbookHistogramModule
hbook file /cdat/sol300/disk5/mccann/mcres16_29.rzn
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
file add pdschain /cdat/sol221/disk4/c3mc/data16/y3s/output/y3s-Jun27_02_MC-FL-1-R121962-E6162-DTS17092002_144140-pass2.pds physics event beginrun startrun endrun
file add pdschain /cdat/sol221/disk4/c3mc/data16/y3s/output/y3s-Jun27_02_MC-FL-1-R121963-E3545-DTS17092002_144152-pass2.pds physics event beginrun startrun endrun
file add pdschain /cdat/sol221/disk4/c3mc/data16/y3s/output/y3s-Jun27_02_MC-FL-1-R121965-E4293-DTS17092002_144204-pass2.pds physics event beginrun startrun endrun
file add pdschain /cdat/sol221/disk4/c3mc/data16/y3s/output/y3s-Jun27_02_MC-FL-1-R121966-E10205-DTS17092002_144216-pass2.pds physics event beginrun startrun endrun
file add pdschain /cdat/sol221/disk4/c3mc/data16/y3s/output/y3s-Jun27_02_MC-FL-1-R121967-E2822-DTS17092002_144228-pass2.pds physics event beginrun startrun endrun
file add pdschain /cdat/sol221/disk4/c3mc/data16/y3s/output/y3s-Jun27_02_MC-FL-1-R121968-E6022-DTS17092002_144240-pass2.pds physics event beginrun startrun endrun
file add pdschain /cdat/sol221/disk4/c3mc/data16/y3s/output/y3s-Jun27_02_MC-FL-1-R121969-E1095-DTS17092002_144252-pass2.pds physics event beginrun startrun endrun
file add pdschain /cdat/sol221/disk4/c3mc/data16/y3s/output/y3s-Jun27_02_MC-FL-1-R121970-E10455-DTS17092002_144305-pass2.pds physics event beginrun startrun endrun
file add pdschain /cdat/sol221/disk4/c3mc/data16/y3s/output/y3s-Jun27_02_MC-FL-1-R121972-E8822-DTS17092002_144317-pass2.pds physics event beginrun startrun endrun
file add pdschain /cdat/sol221/disk4/c3mc/data16/y3s/output/y3s-Jun27_02_MC-FL-1-R121973-E1149-DTS17092002_144329-pass2.pds physics event beginrun startrun endrun

proc sel ../build_SunOS/shlib/Efficiency.so

go 
