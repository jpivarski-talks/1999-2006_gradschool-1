default prompt off
exception continueEventLoop on

run_file $env(C3_SCRIPTS)/getConstants.tcl
run_file $env(C3_SCRIPTS)/trackingDataFull.tcl
run_file $env(C3_SCRIPTS)/CcP2.tcl

proc sel SpExtractStandAloneGeomProc
proc sel SpExtractDRHitsProc
proc sel SpExtractSVHitsProc
proc sel SpExtractSeedTrackProc
proc sel SpExtractSeedTrackDRHitsLinkProc
proc sel SpExtractSeedTrackSVHitsLinkProc
proc sel SpExtractKinePionFitProc
proc sel SpExtractShowerAttributesProc
proc sel SpViewerProc

module sel DBModule
database in /nfs/cleo3/database/data$env(USER_DB)/db event startrun beginrun endrun
database read_collection rawdata
database run $env(USER_RUN)

goto $env(USER_RUN) $env(USER_EVENT)
go 1
hbook terminate
exit
