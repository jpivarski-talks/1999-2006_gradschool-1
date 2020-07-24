default prompt off
exception continueEventLoop on

module sel LoadHbook4MModule
module sel HbookHistogramModule
hbook file ../rzn2/ntuple_m_$env(USER_RUN).rzn
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

run_file $env(C3_SCRIPTS)/BeamSpot.tcl
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

proc sel ../build_SunOS/shlib/Lumi2

if {$env(USER_HASB) == 1} {
    source_format sel PDSSourceFormat
    file in /cdat/dafe/mccann/acceptance/$env(USER_DIR)/raw$env(USER_RUN)_b.pds event beginrun startrun endrun
    go
}

source_format sel PDSSourceFormat
file in /cdat/dafe/mccann/acceptance/$env(USER_DIR)/raw$env(USER_RUN).pds event beginrun startrun endrun

go
hbook terminate
summary
exit
