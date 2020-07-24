default prompt off
exception continueEventLoop on

module sel HbookHistogramModule
hbook file /cdat/sol300/disk5/mccann/mcres17_38.rzn
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
file add pdschain /cdat/sol221/disk2/c3mc/data17/ups3s/output/y3s-Jun27_02_MC-FL-1-R122967-E19-DTS27092002_152904-pass2.pds physics event beginrun startrun endrun
file add pdschain /cdat/sol221/disk2/c3mc/data17/ups3s/output/y3s-Jun27_02_MC-FL-1-R122993-E1462-DTS27092002_153005-pass2.pds physics event beginrun startrun endrun
file add pdschain /cdat/sol221/disk2/c3mc/data17/ups3s/output/y3s-Jun27_02_MC-FL-1-R122995-E247-DTS27092002_153017-pass2.pds physics event beginrun startrun endrun
file add pdschain /cdat/sol221/disk2/c3mc/data17/ups3s/output/y3s-Jun27_02_MC-FL-1-R122996-E223-DTS27092002_153029-pass2.pds physics event beginrun startrun endrun
file add pdschain /cdat/sol221/disk2/c3mc/data17/ups3s/output/y3s-Jun27_02_MC-FL-1-R122998-E397-DTS27092002_153041-pass2.pds physics event beginrun startrun endrun
file add pdschain /cdat/sol221/disk2/c3mc/data17/ups3s/output/y3s-Jun27_02_MC-FL-1-R122999-E1292-DTS27092002_153054-pass2.pds physics event beginrun startrun endrun
file add pdschain /cdat/sol221/disk2/c3mc/data17/ups3s/output/y3s-Jun27_02_MC-FL-1-R123001-E166-DTS27092002_153106-pass2.pds physics event beginrun startrun endrun
file add pdschain /cdat/sol221/disk2/c3mc/data17/ups3s/output/y3s-Jun27_02_MC-FL-1-R123002-E503-DTS27092002_153118-pass2.pds physics event beginrun startrun endrun
file add pdschain /cdat/sol221/disk2/c3mc/data17/ups3s/output/y3s-Jun27_02_MC-FL-1-R123003-E346-DTS27092002_153130-pass2.pds physics event beginrun startrun endrun
file add pdschain /cdat/sol221/disk2/c3mc/data17/ups3s/output/y3s-Jun27_02_MC-FL-1-R123004-E1685-DTS27092002_153142-pass2.pds physics event beginrun startrun endrun

proc sel ../build_SunOS/shlib/Efficiency.so

go 
