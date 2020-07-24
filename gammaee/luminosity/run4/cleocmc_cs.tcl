default prompt off
exception continueEventLoop on

module sel LoadHbook4MModule
module sel HbookHistogramModule
hbook file ../rzn4/cleocmc_cs.rzn
hbook init

module sel CorbaModule
corba init
module sel RunStatisticsSourceModule
runstatistics in
module sel ConstantsModule
constants in $env(C3_CONST) standard CLEO3default

prod sel NavigationProd
prod sel TrackDeliveryProd
prod sel C3ccProd
param C3ccProd RequireRunGainsHotList false
prod sel MagFieldProd
prod sel EventPropertiesProd
prod sel EventTypeProd
prod sel CesrBeamEnergyProd
prod sel VFinderProd
prod sel ElectronFromPionFitProd
prod sel GoodThingsProd

source_format sel BeamSpotFileSourceFormat
file in $env(C3_INFO)/mc/zeromc.beamspot beginrun
run_file $env(C3_SCRIPTS)/CcHotList.tcl

prod sel DetectorConfigurationProd
param DetectorConfigurationProd Override true
param DetectorConfigurationProd UseZDnotSI true
prod sel IRGeomProd
prod sel DRGeom
prod sel ZDGeomProd
prod sel AZDGeomProd
prod sel ADRGeomProd
prod sel DRHitCorrectorProd
prod sel CDOffCal
source_format sel AsciiSourceFormat
file in $env(C3_DATA)/material.asc material

proc sel EventTypeFilterProc
param EventTypeFilterProc GamGam true
param EventTypeFilterProc BhabhaLoose true

proc sel ../build_Linux/shlib/CrystalStudy

run_file /cdat/solpi1/disk1/souren/work/test/Chains/GamGam_203912_203953.tcl

go
hbook terminate
summary
exit
