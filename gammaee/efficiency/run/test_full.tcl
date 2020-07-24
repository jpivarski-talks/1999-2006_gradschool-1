default prompt off
exception continueEventLoop on

module sel RandomModule
random create
module select LoadGeantModule
module select LoadHbookModule
module sel HbookHistogramModule
hbook file ../rzn/test_full.rzn
hbook init

source_format sel BeamSpotFileSourceFormat
file in $env(C3_INFO)/mc/zeromc.beamspot beginrun

run_file $env(C3_SCRIPTS)/getMCPass2_3Constants.tcl
run_file $env(C3_SCRIPTS)/mcpass2/tracking_mcpass2.tcl
run_file $env(C3_SCRIPTS)/pass2/shower_pass2.tcl
run_file $env(C3_SCRIPTS)/mcpass2/shower_mcpass2.tcl
run_file $env(C3_SCRIPTS)/pass2/trackshowermatch_pass2.tcl

prod sel CustomBeamEnergyProd
param CustomBeamEnergyProd BeamEnergy 5.17580
# prod sel Geant3MaterialsMediaProd

prod sel MCTagHolderProd
prod sel MCRawDataProd
prod desel MCRawDataProd
prod desel C3ccReconProd
prod sel   MCSymmetricBeamProd
prod desel MCSymmetricBeamProd
prod sel   MCTriggerPhaseProd
prod desel MCTriggerPhaseProd
prod sel TriggerDataProd
prod desel TriggerDataProd
proc sel Level3Proc
proc sel Level4Proc
param Level4Proc TagOnly true 
prod sel EventPropertiesProd
prod sel EventTypeProd

source_format sel PDSSourceFormat
source create pdschain
file add pdschain /cdat/sol221/disk4/c3mc/data16/y3s/diagnostic/cleogoutput/y3s-Jun27_02_MC-FL-1-R121365-E1100-DTS17092002_134414-cg3.pds physics beginrun startrun event endrun
file add pdschain /cdat/sol221/disk4/c3mc/data16/y3s/diagnostic/cleogoutput/y3s-Jun27_02_MC-FL-1-R121446-E3130-DTS17092002_135454-cg3.pds physics beginrun startrun event endrun
file add pdschain /cdat/sol221/disk4/c3mc/data16/y3s/diagnostic/cleogoutput/y3s-Jun27_02_MC-FL-1-R121574-E3021-DTS17092002_140506-cg3.pds physics beginrun startrun event endrun
file add pdschain /cdat/sol221/disk4/c3mc/data16/y3s/diagnostic/cleogoutput/y3s-Jun27_02_MC-FL-1-R121715-E8186-DTS17092002_141537-cg3.pds physics beginrun startrun event endrun
file add pdschain /cdat/sol221/disk4/c3mc/data16/y3s/diagnostic/cleogoutput/y3s-Jun27_02_MC-FL-1-R121804-E2857-DTS17092002_142548-cg3.pds physics beginrun startrun event endrun
file add pdschain /cdat/sol221/disk4/c3mc/data16/y3s/diagnostic/cleogoutput/y3s-Jun27_02_MC-FL-1-R121916-E5836-DTS17092002_143619-cg3.pds physics beginrun startrun event endrun
file add pdschain /cdat/sol221/disk4/c3mc/data16/y3s/diagnostic/cleogoutput/y3s-Jun27_02_MC-FL-1-R122003-E10052-DTS17092002_144631-cg3.pds physics beginrun startrun event endrun
file add pdschain /cdat/sol221/disk4/c3mc/data16/y3s/diagnostic/cleogoutput/y3s-Jun27_02_MC-FL-1-R122141-E8456-DTS17092002_145647-cg3.pds physics beginrun startrun event endrun

proc sel ../build_SunOS/shlib/Efficiency.so

go
