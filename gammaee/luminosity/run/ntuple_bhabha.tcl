default prompt off
exception continueEventLoop on

module sel LoadHbook4MModule
module sel HbookHistogramModule
hbook file ../rzn/ntuple_bhabha.rzn
hbook init

module sel CorbaModule
corba init
module sel RunStatisticsSourceModule
runstatistics in
module sel ConstantsModule
constants in $env(C3_CONST) standard CLEO3default streams superconductingquad magfudge
constants in $env(C3_CONST) meta BaseGeometry MetaListRetrieval

prod sel NavigationProd
prod sel TrackDeliveryProd
prod sel C3ccProd
param C3ccProd RequireRunGainsHotList false
prod sel MagFieldProd
prod sel EventPropertiesProd
prod sel EventTypeProd
prod sel CesrBeamEnergyProd

source_format sel BeamSpotFileSourceFormat
file in $env(C3_INFO)/mc/zeromc.beamspot beginrun
run_file $env(C3_SCRIPTS)/CcHotList.tcl

proc sel ../build_SunOS/shlib/Lumi

source_format sel PDSSourceFormat
source create pdschain
file add pdschain /cdat/solpi1/disk1/souren/work/test/bhabha_Jun27_02_MC_121576_10000_pass2.pds physics event beginrun startrun endrun
file add pdschain /cdat/solpi1/disk1/souren/work/test/bhabha_Jun27_02_MC_121576_10001_pass2.pds physics event beginrun startrun endrun
file add pdschain /cdat/solpi1/disk1/souren/work/test/bhabha_Jun27_02_MC_121576_10002_pass2.pds physics event beginrun startrun endrun
file add pdschain /cdat/solpi1/disk1/souren/work/test/bhabha_Jun27_02_MC_121576_10003_pass2.pds physics event beginrun startrun endrun
file add pdschain /cdat/solpi1/disk1/souren/work/test/bhabha_Jun27_02_MC_121576_10004_pass2.pds physics event beginrun startrun endrun
file add pdschain /cdat/solpi1/disk1/souren/work/test/bhabha_Jun27_02_MC_121576_10005_pass2.pds physics event beginrun startrun endrun
file add pdschain /cdat/solpi1/disk1/souren/work/test/bhabha_Jun27_02_MC_121576_10006_pass2.pds physics event beginrun startrun endrun
file add pdschain /cdat/solpi1/disk1/souren/work/test/bhabha_Jun27_02_MC_121576_10007_pass2.pds physics event beginrun startrun endrun
file add pdschain /cdat/solpi1/disk1/souren/work/test/bhabha_Jun27_02_MC_121576_10008_pass2.pds physics event beginrun startrun endrun
file add pdschain /cdat/solpi1/disk1/souren/work/test/bhabha_Jun27_02_MC_121576_10009_pass2.pds physics event beginrun startrun endrun
file add pdschain /cdat/solpi1/disk1/souren/work/test/bhabha_Jun27_02_MC_121576_10010_pass2.pds physics event beginrun startrun endrun
file add pdschain /cdat/solpi1/disk1/souren/work/test/bhabha_Jun27_02_MC_121576_10011_pass2.pds physics event beginrun startrun endrun
file add pdschain /cdat/solpi1/disk1/souren/work/test/bhabha_Jun27_02_MC_121576_10012_pass2.pds physics event beginrun startrun endrun
file add pdschain /cdat/solpi1/disk1/souren/work/test/bhabha_Jun27_02_MC_121576_10013_pass2.pds physics event beginrun startrun endrun
file add pdschain /cdat/solpi1/disk1/souren/work/test/bhabha_Jun27_02_MC_121576_10014_pass2.pds physics event beginrun startrun endrun
file add pdschain /cdat/solpi1/disk1/souren/work/test/bhabha_Jun27_02_MC_121576_10015_pass2.pds physics event beginrun startrun endrun
file add pdschain /cdat/solpi1/disk1/souren/work/test/bhabha_Jun27_02_MC_121576_10016_pass2.pds physics event beginrun startrun endrun
file add pdschain /cdat/solpi1/disk1/souren/work/test/bhabha_Jun27_02_MC_121576_10017_pass2.pds physics event beginrun startrun endrun
file add pdschain /cdat/solpi1/disk1/souren/work/test/bhabha_Jun27_02_MC_121576_10018_pass2.pds physics event beginrun startrun endrun
file add pdschain /cdat/solpi1/disk1/souren/work/test/bhabha_Jun27_02_MC_121576_10019_pass2.pds physics event beginrun startrun endrun
file add pdschain /cdat/solpi1/disk1/souren/work/test/bhabha_Jun27_02_MC_121576_10020_pass2.pds physics event beginrun startrun endrun
file add pdschain /cdat/solpi1/disk1/souren/work/test/bhabha_Jun27_02_MC_121576_10021_pass2.pds physics event beginrun startrun endrun
file add pdschain /cdat/solpi1/disk1/souren/work/test/bhabha_Jun27_02_MC_121576_10022_pass2.pds physics event beginrun startrun endrun
file add pdschain /cdat/solpi1/disk1/souren/work/test/bhabha_Jun27_02_MC_121576_10023_pass2.pds physics event beginrun startrun endrun
file add pdschain /cdat/solpi1/disk1/souren/work/test/bhabha_Jun27_02_MC_121576_10024_pass2.pds physics event beginrun startrun endrun
file add pdschain /cdat/solpi1/disk1/souren/work/test/bhabha_Jun27_02_MC_121576_10025_pass2.pds physics event beginrun startrun endrun
file add pdschain /cdat/solpi1/disk1/souren/work/test/bhabha_Jun27_02_MC_121576_10026_pass2.pds physics event beginrun startrun endrun
file add pdschain /cdat/solpi1/disk1/souren/work/test/bhabha_Jun27_02_MC_121576_10027_pass2.pds physics event beginrun startrun endrun
file add pdschain /cdat/solpi1/disk1/souren/work/test/bhabha_Jun27_02_MC_121576_10028_pass2.pds physics event beginrun startrun endrun
file add pdschain /cdat/solpi1/disk1/souren/work/test/bhabha_Jun27_02_MC_121576_10029_pass2.pds physics event beginrun startrun endrun
file add pdschain /cdat/solpi1/disk1/souren/work/test/bhabha_Jun27_02_MC_121772_10000_pass2.pds physics event beginrun startrun endrun
file add pdschain /cdat/solpi1/disk1/souren/work/test/bhabha_Jun27_02_MC_121772_10001_pass2.pds physics event beginrun startrun endrun
file add pdschain /cdat/solpi1/disk1/souren/work/test/bhabha_Jun27_02_MC_121772_10002_pass2.pds physics event beginrun startrun endrun
file add pdschain /cdat/solpi1/disk1/souren/work/test/bhabha_Jun27_02_MC_121772_10003_pass2.pds physics event beginrun startrun endrun
file add pdschain /cdat/solpi1/disk1/souren/work/test/bhabha_Jun27_02_MC_121772_10004_pass2.pds physics event beginrun startrun endrun
file add pdschain /cdat/solpi1/disk1/souren/work/test/bhabha_Jun27_02_MC_121772_10005_pass2.pds physics event beginrun startrun endrun
file add pdschain /cdat/solpi1/disk1/souren/work/test/bhabha_Jun27_02_MC_121772_10006_pass2.pds physics event beginrun startrun endrun
file add pdschain /cdat/solpi1/disk1/souren/work/test/bhabha_Jun27_02_MC_121772_10007_pass2.pds physics event beginrun startrun endrun
file add pdschain /cdat/solpi1/disk1/souren/work/test/bhabha_Jun27_02_MC_121772_10008_pass2.pds physics event beginrun startrun endrun
file add pdschain /cdat/solpi1/disk1/souren/work/test/bhabha_Jun27_02_MC_121772_10009_pass2.pds physics event beginrun startrun endrun
file add pdschain /cdat/solpi1/disk1/souren/work/test/bhabha_Jun27_02_MC_121772_10010_pass2.pds physics event beginrun startrun endrun
file add pdschain /cdat/solpi1/disk1/souren/work/test/bhabha_Jun27_02_MC_121772_10011_pass2.pds physics event beginrun startrun endrun
file add pdschain /cdat/solpi1/disk1/souren/work/test/bhabha_Jun27_02_MC_121772_10012_pass2.pds physics event beginrun startrun endrun
file add pdschain /cdat/solpi1/disk1/souren/work/test/bhabha_Jun27_02_MC_121772_10013_pass2.pds physics event beginrun startrun endrun
file add pdschain /cdat/solpi1/disk1/souren/work/test/bhabha_Jun27_02_MC_121772_10014_pass2.pds physics event beginrun startrun endrun
file add pdschain /cdat/solpi1/disk1/souren/work/test/bhabha_Jun27_02_MC_121772_10015_pass2.pds physics event beginrun startrun endrun
file add pdschain /cdat/solpi1/disk1/souren/work/test/bhabha_Jun27_02_MC_121772_10016_pass2.pds physics event beginrun startrun endrun
file add pdschain /cdat/solpi1/disk1/souren/work/test/bhabha_Jun27_02_MC_121772_10017_pass2.pds physics event beginrun startrun endrun
file add pdschain /cdat/solpi1/disk1/souren/work/test/bhabha_Jun27_02_MC_121772_10018_pass2.pds physics event beginrun startrun endrun
file add pdschain /cdat/solpi1/disk1/souren/work/test/bhabha_Jun27_02_MC_121772_10019_pass2.pds physics event beginrun startrun endrun
file add pdschain /cdat/solpi1/disk1/souren/work/test/bhabha_Jun27_02_MC_121772_10020_pass2.pds physics event beginrun startrun endrun
file add pdschain /cdat/solpi1/disk1/souren/work/test/bhabha_Jun27_02_MC_121772_10021_pass2.pds physics event beginrun startrun endrun
file add pdschain /cdat/solpi1/disk1/souren/work/test/bhabha_Jun27_02_MC_121772_10022_pass2.pds physics event beginrun startrun endrun
file add pdschain /cdat/solpi1/disk1/souren/work/test/bhabha_Jun27_02_MC_121772_10023_pass2.pds physics event beginrun startrun endrun
file add pdschain /cdat/solpi1/disk1/souren/work/test/bhabha_Jun27_02_MC_121772_10024_pass2.pds physics event beginrun startrun endrun
file add pdschain /cdat/solpi1/disk1/souren/work/test/bhabha_Jun27_02_MC_121772_10025_pass2.pds physics event beginrun startrun endrun
file add pdschain /cdat/solpi1/disk1/souren/work/test/bhabha_Jun27_02_MC_121772_10026_pass2.pds physics event beginrun startrun endrun
file add pdschain /cdat/solpi1/disk1/souren/work/test/bhabha_Jun27_02_MC_121772_10027_pass2.pds physics event beginrun startrun endrun
file add pdschain /cdat/solpi1/disk1/souren/work/test/bhabha_Jun27_02_MC_121772_10028_pass2.pds physics event beginrun startrun endrun
file add pdschain /cdat/solpi1/disk1/souren/work/test/bhabha_Jun27_02_MC_121772_10029_pass2.pds physics event beginrun startrun endrun
file add pdschain /cdat/solpi1/disk1/souren/work/test/bhabha_Jun27_02_MC_121905_10001_pass2.pds physics event beginrun startrun endrun
# file add pdschain /cdat/solpi1/disk1/souren/work/test/bhabha_Jun27_02_MC_121905_10002_pass2.pds physics event beginrun startrun endrun
file add pdschain /cdat/solpi1/disk1/souren/work/test/bhabha_Jun27_02_MC_121905_10003_pass2.pds physics event beginrun startrun endrun
file add pdschain /cdat/solpi1/disk1/souren/work/test/bhabha_Jun27_02_MC_121905_10004_pass2.pds physics event beginrun startrun endrun
file add pdschain /cdat/solpi1/disk1/souren/work/test/bhabha_Jun27_02_MC_121905_10005_pass2.pds physics event beginrun startrun endrun
file add pdschain /cdat/solpi1/disk1/souren/work/test/bhabha_Jun27_02_MC_121905_10006_pass2.pds physics event beginrun startrun endrun
file add pdschain /cdat/solpi1/disk1/souren/work/test/bhabha_Jun27_02_MC_121905_10007_pass2.pds physics event beginrun startrun endrun
file add pdschain /cdat/solpi1/disk1/souren/work/test/bhabha_Jun27_02_MC_121905_10008_pass2.pds physics event beginrun startrun endrun
file add pdschain /cdat/solpi1/disk1/souren/work/test/bhabha_Jun27_02_MC_121905_10009_pass2.pds physics event beginrun startrun endrun
file add pdschain /cdat/solpi1/disk1/souren/work/test/bhabha_Jun27_02_MC_121905_10010_pass2.pds physics event beginrun startrun endrun
file add pdschain /cdat/solpi1/disk1/souren/work/test/bhabha_Jun27_02_MC_121905_10011_pass2.pds physics event beginrun startrun endrun
file add pdschain /cdat/solpi1/disk1/souren/work/test/bhabha_Jun27_02_MC_121905_10012_pass2.pds physics event beginrun startrun endrun
file add pdschain /cdat/solpi1/disk1/souren/work/test/bhabha_Jun27_02_MC_121905_10013_pass2.pds physics event beginrun startrun endrun
file add pdschain /cdat/solpi1/disk1/souren/work/test/bhabha_Jun27_02_MC_121905_10014_pass2.pds physics event beginrun startrun endrun
file add pdschain /cdat/solpi1/disk1/souren/work/test/bhabha_Jun27_02_MC_121905_10015_pass2.pds physics event beginrun startrun endrun
file add pdschain /cdat/solpi1/disk1/souren/work/test/bhabha_Jun27_02_MC_121905_10016_pass2.pds physics event beginrun startrun endrun
file add pdschain /cdat/solpi1/disk1/souren/work/test/bhabha_Jun27_02_MC_121905_10017_pass2.pds physics event beginrun startrun endrun
file add pdschain /cdat/solpi1/disk1/souren/work/test/bhabha_Jun27_02_MC_121905_10018_pass2.pds physics event beginrun startrun endrun
file add pdschain /cdat/solpi1/disk1/souren/work/test/bhabha_Jun27_02_MC_121905_10019_pass2.pds physics event beginrun startrun endrun
file add pdschain /cdat/solpi1/disk1/souren/work/test/bhabha_Jun27_02_MC_121905_10020_pass2.pds physics event beginrun startrun endrun
file add pdschain /cdat/solpi1/disk1/souren/work/test/bhabha_Jun27_02_MC_121905_10021_pass2.pds physics event beginrun startrun endrun
file add pdschain /cdat/solpi1/disk1/souren/work/test/bhabha_Jun27_02_MC_121905_10022_pass2.pds physics event beginrun startrun endrun
file add pdschain /cdat/solpi1/disk1/souren/work/test/bhabha_Jun27_02_MC_121905_10023_pass2.pds physics event beginrun startrun endrun
file add pdschain /cdat/solpi1/disk1/souren/work/test/bhabha_Jun27_02_MC_121905_10024_pass2.pds physics event beginrun startrun endrun
file add pdschain /cdat/solpi1/disk1/souren/work/test/bhabha_Jun27_02_MC_121905_10025_pass2.pds physics event beginrun startrun endrun
file add pdschain /cdat/solpi1/disk1/souren/work/test/bhabha_Jun27_02_MC_121905_10026_pass2.pds physics event beginrun startrun endrun
file add pdschain /cdat/solpi1/disk1/souren/work/test/bhabha_Jun27_02_MC_121905_10027_pass2.pds physics event beginrun startrun endrun
file add pdschain /cdat/solpi1/disk1/souren/work/test/bhabha_Jun27_02_MC_121905_10028_pass2.pds physics event beginrun startrun endrun
file add pdschain /cdat/solpi1/disk1/souren/work/test/bhabha_Jun27_02_MC_121905_10029_pass2.pds physics event beginrun startrun endrun

go
hbook terminate
summary
exit
