default prompt off
exception continueEventLoop on

module sel LoadHbook4MModule
module sel HbookHistogramModule
hbook file ../rzn4/cleo3mc_deeper_again.rzn
hbook init

module sel CorbaModule
corba init
module sel RunStatisticsSourceModule
runstatistics in
module sel ConstantsModule
constants in $env(C3_CONST) standard CLEO3default
constants in $env(C3_CONST) meta BaseGeometry MetaListRetrieval

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
param DetectorConfigurationProd UseZDnotSI false
prod sel IRGeomProd
prod sel DRGeom
prod sel SiGeom
prod sel ASiStorePro
prod sel ADRGeomProd
prod sel DRHitCorrectorProd
prod sel CDOffCal
source_format sel AsciiSourceFormat
file in $env(C3_DATA)/material.asc material

# proc sel EventTypeFilterProc
# param EventTypeFilterProc GamGam true
# param EventTypeFilterProc BhabhaLoose true

proc sel ../build_SunOS/shlib/Convert

source_format sel PDSSourceFormat
source create pdschain
file add pdschain /cdat/solpi1/disk1/souren/work/test/gamgam_Jun27_02_MC_121772_10000_pass2.pds physics event beginrun startrun endrun
file add pdschain /cdat/solpi1/disk1/souren/work/test/gamgam_Jun27_02_MC_121772_10001_pass2.pds physics event beginrun startrun endrun
file add pdschain /cdat/solpi1/disk1/souren/work/test/gamgam_Jun27_02_MC_121772_10002_pass2.pds physics event beginrun startrun endrun
file add pdschain /cdat/solpi1/disk1/souren/work/test/gamgam_Jun27_02_MC_121772_10003_pass2.pds physics event beginrun startrun endrun
file add pdschain /cdat/solpi1/disk1/souren/work/test/gamgam_Jun27_02_MC_121772_10004_pass2.pds physics event beginrun startrun endrun
file add pdschain /cdat/solpi1/disk1/souren/work/test/gamgam_Jun27_02_MC_121772_10005_pass2.pds physics event beginrun startrun endrun
file add pdschain /cdat/solpi1/disk1/souren/work/test/gamgam_Jun27_02_MC_121772_10006_pass2.pds physics event beginrun startrun endrun
file add pdschain /cdat/solpi1/disk1/souren/work/test/gamgam_Jun27_02_MC_121772_10008_pass2.pds physics event beginrun startrun endrun
file add pdschain /cdat/solpi1/disk1/souren/work/test/gamgam_Jun27_02_MC_121772_10009_pass2.pds physics event beginrun startrun endrun
file add pdschain /cdat/solpi1/disk1/souren/work/test/gamgam_Jun27_02_MC_121772_10010_pass2.pds physics event beginrun startrun endrun
file add pdschain /cdat/solpi1/disk1/souren/work/test/gamgam_Jun27_02_MC_121772_10011_pass2.pds physics event beginrun startrun endrun
file add pdschain /cdat/solpi1/disk1/souren/work/test/gamgam_Jun27_02_MC_121772_10012_pass2.pds physics event beginrun startrun endrun
file add pdschain /cdat/solpi1/disk1/souren/work/test/gamgam_Jun27_02_MC_121772_10013_pass2.pds physics event beginrun startrun endrun
file add pdschain /cdat/solpi1/disk1/souren/work/test/gamgam_Jun27_02_MC_121772_10014_pass2.pds physics event beginrun startrun endrun
file add pdschain /cdat/solpi1/disk1/souren/work/test/gamgam_Jun27_02_MC_121772_10015_pass2.pds physics event beginrun startrun endrun
file add pdschain /cdat/solpi1/disk1/souren/work/test/gamgam_Jun27_02_MC_121772_10016_pass2.pds physics event beginrun startrun endrun
file add pdschain /cdat/solpi1/disk1/souren/work/test/gamgam_Jun27_02_MC_121772_10017_pass2.pds physics event beginrun startrun endrun
file add pdschain /cdat/solpi1/disk1/souren/work/test/gamgam_Jun27_02_MC_121772_10018_pass2.pds physics event beginrun startrun endrun
file add pdschain /cdat/solpi1/disk1/souren/work/test/gamgam_Jun27_02_MC_121772_10019_pass2.pds physics event beginrun startrun endrun

go
hbook terminate
summary
exit
