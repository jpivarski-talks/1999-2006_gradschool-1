default prompt off
exception continueEventLoop on

module sel HbookHistogramModule
hbook file /cdat/sol300/disk5/mccann/mcres17_01-track.rzn
hbook init

run_file $env(C3_SCRIPTS)/runOnPass2.tcl

prod sel EventPropertiesProd
prod sel EventTypeProd

prod sel DBEventHeaderProd
prod sel MCInfoDelivery
prod sel MCTagHolderProd

prod sel CustomBeamEnergyProd
param CustomBeamEnergyProd BeamEnergy 5.17765

source_format sel BeamSpotFileSourceFormat
file in $env(C3_INFO)/mc/zeromc.beamspot beginrun

source create pdschain
source_format sel PDSSourceFormat
file add pdschain /cdat/sol221/disk2/c3mc/data17/ups3s/output/y3s-Jun27_02_MC-FL-1-R122245-E2529-DTS27092002_141155-pass2.pds physics event beginrun startrun endrun
file add pdschain /cdat/sol221/disk2/c3mc/data17/ups3s/output/y3s-Jun27_02_MC-FL-1-R122246-E2000-DTS27092002_141208-pass2.pds physics event beginrun startrun endrun
file add pdschain /cdat/sol221/disk2/c3mc/data17/ups3s/output/y3s-Jun27_02_MC-FL-1-R122247-E465-DTS27092002_141221-pass2.pds physics event beginrun startrun endrun
file add pdschain /cdat/sol221/disk2/c3mc/data17/ups3s/output/y3s-Jun27_02_MC-FL-1-R122249-E177-DTS27092002_141234-pass2.pds physics event beginrun startrun endrun
file add pdschain /cdat/sol221/disk2/c3mc/data17/ups3s/output/y3s-Jun27_02_MC-FL-1-R122251-E314-DTS27092002_141248-pass2.pds physics event beginrun startrun endrun
file add pdschain /cdat/sol221/disk2/c3mc/data17/ups3s/output/y3s-Jun27_02_MC-FL-1-R122252-E467-DTS27092002_141259-pass2.pds physics event beginrun startrun endrun
file add pdschain /cdat/sol221/disk2/c3mc/data17/ups3s/output/y3s-Jun27_02_MC-FL-1-R122253-E746-DTS27092002_141312-pass2.pds physics event beginrun startrun endrun
file add pdschain /cdat/sol221/disk2/c3mc/data17/ups3s/output/y3s-Jun27_02_MC-FL-1-R122256-E1973-DTS27092002_141326-pass2.pds physics event beginrun startrun endrun
file add pdschain /cdat/sol221/disk2/c3mc/data17/ups3s/output/y3s-Jun27_02_MC-FL-1-R122263-E1136-DTS27092002_141339-pass2.pds physics event beginrun startrun endrun
file add pdschain /cdat/sol221/disk2/c3mc/data17/ups3s/output/y3s-Jun27_02_MC-FL-1-R122264-E29-DTS27092002_141353-pass2.pds physics event beginrun startrun endrun

proc sel ../build_SunOS/shlib/TrackEfficiency.so
param TrackEfficiency isMC true

go 
