default prompt off
exception continueEventLoop on

module sel HbookHistogramModule
hbook file /cdat/sol300/disk5/mccann/mcres17_25.rzn
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
file add pdschain /cdat/sol221/disk2/c3mc/data17/ups3s/output/y3s-Jun27_02_MC-FL-1-R122683-E7029-DTS27092002_150221-pass2.pds physics event beginrun startrun endrun
file add pdschain /cdat/sol221/disk2/c3mc/data17/ups3s/output/y3s-Jun27_02_MC-FL-1-R122684-E9318-DTS27092002_150233-pass2.pds physics event beginrun startrun endrun
file add pdschain /cdat/sol221/disk2/c3mc/data17/ups3s/output/y3s-Jun27_02_MC-FL-1-R122685-E5320-DTS27092002_150246-pass2.pds physics event beginrun startrun endrun
file add pdschain /cdat/sol221/disk2/c3mc/data17/ups3s/output/y3s-Jun27_02_MC-FL-1-R122686-E2001-DTS27092002_150258-pass2.pds physics event beginrun startrun endrun
file add pdschain /cdat/sol221/disk2/c3mc/data17/ups3s/output/y3s-Jun27_02_MC-FL-1-R122687-E7349-DTS27092002_150310-pass2.pds physics event beginrun startrun endrun
file add pdschain /cdat/sol221/disk2/c3mc/data17/ups3s/output/y3s-Jun27_02_MC-FL-1-R122689-E2131-DTS27092002_150322-pass2.pds physics event beginrun startrun endrun
file add pdschain /cdat/sol221/disk2/c3mc/data17/ups3s/output/y3s-Jun27_02_MC-FL-1-R122690-E8099-DTS27092002_150335-pass2.pds physics event beginrun startrun endrun
file add pdschain /cdat/sol221/disk2/c3mc/data17/ups3s/output/y3s-Jun27_02_MC-FL-1-R122691-E8615-DTS27092002_150347-pass2.pds physics event beginrun startrun endrun
file add pdschain /cdat/sol221/disk2/c3mc/data17/ups3s/output/y3s-Jun27_02_MC-FL-1-R122692-E8565-DTS27092002_150359-pass2.pds physics event beginrun startrun endrun
file add pdschain /cdat/sol221/disk2/c3mc/data17/ups3s/output/y3s-Jun27_02_MC-FL-1-R122693-E5957-DTS27092002_150411-pass2.pds physics event beginrun startrun endrun

proc sel ../build_SunOS/shlib/Efficiency.so

go 
