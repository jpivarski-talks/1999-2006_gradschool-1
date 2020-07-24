default prompt off
exception continueEventLoop on

module sel HbookHistogramModule
hbook file /cdat/sol300/disk5/mccann/mcres17_32.rzn
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
file add pdschain /cdat/sol221/disk2/c3mc/data17/ups3s/output/y3s-Jun27_02_MC-FL-1-R122789-E61-DTS27092002_151648-pass2.pds physics event beginrun startrun endrun
file add pdschain /cdat/sol221/disk2/c3mc/data17/ups3s/output/y3s-Jun27_02_MC-FL-1-R122796-E73-DTS27092002_151701-pass2.pds physics event beginrun startrun endrun
file add pdschain /cdat/sol221/disk2/c3mc/data17/ups3s/output/y3s-Jun27_02_MC-FL-1-R122797-E58-DTS27092002_151712-pass2.pds physics event beginrun startrun endrun
file add pdschain /cdat/sol221/disk2/c3mc/data17/ups3s/output/y3s-Jun27_02_MC-FL-1-R122798-E65-DTS27092002_151724-pass2.pds physics event beginrun startrun endrun
file add pdschain /cdat/sol221/disk2/c3mc/data17/ups3s/output/y3s-Jun27_02_MC-FL-1-R122799-E68-DTS27092002_151736-pass2.pds physics event beginrun startrun endrun
file add pdschain /cdat/sol221/disk2/c3mc/data17/ups3s/output/y3s-Jun27_02_MC-FL-1-R122800-E62-DTS27092002_151749-pass2.pds physics event beginrun startrun endrun
file add pdschain /cdat/sol221/disk2/c3mc/data17/ups3s/output/y3s-Jun27_02_MC-FL-1-R122801-E63-DTS27092002_151801-pass2.pds physics event beginrun startrun endrun
file add pdschain /cdat/sol221/disk2/c3mc/data17/ups3s/output/y3s-Jun27_02_MC-FL-1-R122802-E73-DTS27092002_151813-pass2.pds physics event beginrun startrun endrun
file add pdschain /cdat/sol221/disk2/c3mc/data17/ups3s/output/y3s-Jun27_02_MC-FL-1-R122803-E70-DTS27092002_151825-pass2.pds physics event beginrun startrun endrun
file add pdschain /cdat/sol221/disk2/c3mc/data17/ups3s/output/y3s-Jun27_02_MC-FL-1-R122804-E71-DTS27092002_151837-pass2.pds physics event beginrun startrun endrun

proc sel ../build_SunOS/shlib/Efficiency.so

go 
