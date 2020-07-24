default prompt off
exception continueEventLoop on

module sel HbookHistogramModule
hbook file /cdat/sol300/disk5/mccann/mcres17_06.rzn
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
file add pdschain /cdat/sol221/disk2/c3mc/data17/ups3s/output/y3s-Jun27_02_MC-FL-1-R122326-E6663-DTS27092002_142302-pass2.pds physics event beginrun startrun endrun
file add pdschain /cdat/sol221/disk2/c3mc/data17/ups3s/output/y3s-Jun27_02_MC-FL-1-R122330-E7571-DTS27092002_142313-pass2.pds physics event beginrun startrun endrun
file add pdschain /cdat/sol221/disk2/c3mc/data17/ups3s/output/y3s-Jun27_02_MC-FL-1-R122331-E722-DTS27092002_142325-pass2.pds physics event beginrun startrun endrun
file add pdschain /cdat/sol221/disk2/c3mc/data17/ups3s/output/y3s-Jun27_02_MC-FL-1-R122335-E434-DTS27092002_142337-pass2.pds physics event beginrun startrun endrun
file add pdschain /cdat/sol221/disk2/c3mc/data17/ups3s/output/y3s-Jun27_02_MC-FL-1-R122336-E2314-DTS27092002_142349-pass2.pds physics event beginrun startrun endrun
file add pdschain /cdat/sol221/disk2/c3mc/data17/ups3s/output/y3s-Jun27_02_MC-FL-1-R122339-E2065-DTS27092002_142401-pass2.pds physics event beginrun startrun endrun
file add pdschain /cdat/sol221/disk2/c3mc/data17/ups3s/output/y3s-Jun27_02_MC-FL-1-R122341-E1966-DTS27092002_142413-pass2.pds physics event beginrun startrun endrun
file add pdschain /cdat/sol221/disk2/c3mc/data17/ups3s/output/y3s-Jun27_02_MC-FL-1-R122342-E1520-DTS27092002_142425-pass2.pds physics event beginrun startrun endrun
file add pdschain /cdat/sol221/disk2/c3mc/data17/ups3s/output/y3s-Jun27_02_MC-FL-1-R122344-E218-DTS27092002_142437-pass2.pds physics event beginrun startrun endrun
file add pdschain /cdat/sol221/disk2/c3mc/data17/ups3s/output/y3s-Jun27_02_MC-FL-1-R122347-E1522-DTS27092002_142501-pass2.pds physics event beginrun startrun endrun

proc sel ../build_SunOS/shlib/Efficiency.so

go 
