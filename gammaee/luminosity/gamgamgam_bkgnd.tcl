module sel HbookHistogramModule
hbook file rzn5/gamgamgam_bkgnd.rzn
hbook init

run_file $env(C3_SCRIPTS)/getMCConstants.tcl
run_file $env(C3_SCRIPTS)/runOnPass2.tcl

proc sel build_SunOS/shlib/ChiSearch.so

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
exit
