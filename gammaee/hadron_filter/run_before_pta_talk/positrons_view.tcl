default prompt off
exception continueEventLoop on

module sel HbookHistogramModule
hbook file ../rzn/noclobber.rzn
hbook init

run_file $env(C3_SCRIPTS)/runOnPass2.tcl
constants in $env(C3_CONST) meta BaseGeometry MetaListRetrieval

prod sel NavigationProd
prod sel TrackDeliveryProd
prod sel C3ccProd
prod sel MagFieldProd
prod sel DBEventHeaderProd
prod sel CesrBeamEnergyProd
prod sel EventPropertiesProd
prod sel EventTypeProd

prod sel CcGeomProd

proc sel EventTypeFilterProc
param EventTypeFilterProc Hadron true

proc sel ../build_SunOS/shlib/BigNTuple2
param BigNTuple2 lookForCosmics false
param BigNTuple2 getBunchData false
param BigNTuple2 interestingOnly true

proc sel SpExtractStandAloneGeomProc
proc sel SpExtractSeedTrackProc
proc sel SpExtractCcEnergyHitProc
proc sel SpViewerProc

source_format sel PDSSourceFormat

file in ../pds/positrons.pds event startrun beginrun endrun
go 25815
