default prompt off
exception continueEventLoop on

module sel HbookHistogramModule
hbook file ../data_method_rzn/test.rzn
hbook init

run_file $env(C3_SCRIPTS)/CcHotList.tcl
run_file $env(C3_SCRIPTS)/runOnPass2.tcl

prod sel EventPropertiesProd
prod sel TrkmanProd
prod sel TrkmanSelectionProd

source_format sel BeamSpotFileSourceFormat
file in $env(C3_INFO)/mc/zeromc.beamspot beginrun

source_format sel PDSSourceFormat
file in ../data_method_rzn/r129564.pds event startrun

# source_format sel PDSSourceFormat
# source create pdschain
# file add pdschain /cdat/sol221/disk4/c3mc/data16/ups3s/output/y3s-Jun27_02_MC-FL-1-R121339-E164-DTS17092002_134208-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol221/disk4/c3mc/data16/ups3s/output/y3s-Jun27_02_MC-FL-1-R121339-E164-DTS17092002_134208-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol221/disk4/c3mc/data16/ups3s/output/y3s-Jun27_02_MC-FL-1-R121340-E265-DTS17092002_134220-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol221/disk4/c3mc/data16/ups3s/output/y3s-Jun27_02_MC-FL-1-R121343-E184-DTS17092002_134232-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol221/disk4/c3mc/data16/ups3s/output/y3s-Jun27_02_MC-FL-1-R121344-E268-DTS17092002_134244-pass2.pds physics event startrun beginrun endrun

proc sel ../build_SunOS/shlib/SuperCuts
proc sel BeamGasFilterProc
param BeamGasFilterProc cumulativeFrequency 1e10
param BeamGasFilterProc noExplaination true
param BeamGasFilterProc closestIntersectionCut 0.01
param BeamGasFilterProc weightedZCut 0.05

go 1000

