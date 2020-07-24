default prompt off
exception continueEventLoop on

module sel LoadHbook4MModule
module sel HbookHistogramModule
hbook file ../rzn4/cleo3data_deeper.rzn
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
prod sel RunInfoProd

source_format sel BeamSpotFileSourceFormat
file in $env(C3_INFO)/data/beamspot.beamspot beginrun
run_file $env(C3_SCRIPTS)/CcHotList.tcl
source_format sel RunInfoFileSourceFormat
file in $env(C3_INFO)/data/runinfo.runinfo

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

proc sel RunInfoProc
param RunInfoProc MinBeamEnergy 5.16
param RunInfoProc MaxBeamEnergy 5.17

proc sel EventTypeFilterProc
param EventTypeFilterProc GamGam true
param EventTypeFilterProc BhabhaLoose true

proc sel ../build_SunOS/shlib/Convert

module sel DBModule
database in /nfs/cleo3/database/data16/db event startrun beginrun endrun
database read_collection pass2 bhagam

go
hbook terminate
summary
exit
