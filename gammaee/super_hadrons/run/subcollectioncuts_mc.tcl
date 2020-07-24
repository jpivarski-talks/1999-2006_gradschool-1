default prompt off
exception continueEventLoop on

module sel HbookHistogramModule
hbook file ../rzn/subcollectioncuts_mc.rzn
hbook init

run_file $env(C3_SCRIPTS)/runOnPass2.tcl
run_file $env(C3_SCRIPTS)/CcHotList.tcl

prod sel DBEventHeaderProd
prod sel CesrBeamEnergyProd
prod sel EventPropertiesProd

source_format sel PDSSourceFormat
source create pdschain

file add pdschain /cdat/sol221/disk4/c3mc/data16/y3s/output/y3s-Jun27_02_MC-FL-1-R121339-E164-DTS17092002_134208-pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol221/disk4/c3mc/data16/y3s/output/y3s-Jun27_02_MC-FL-1-R121340-E265-DTS17092002_134220-pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol221/disk4/c3mc/data16/y3s/output/y3s-Jun27_02_MC-FL-1-R121343-E184-DTS17092002_134232-pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol221/disk4/c3mc/data16/y3s/output/y3s-Jun27_02_MC-FL-1-R121344-E268-DTS17092002_134244-pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol221/disk4/c3mc/data16/y3s/output/y3s-Jun27_02_MC-FL-1-R121346-E295-DTS17092002_134256-pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol221/disk4/c3mc/data16/y3s/output/y3s-Jun27_02_MC-FL-1-R121347-E235-DTS17092002_134310-pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol221/disk4/c3mc/data16/y3s/output/y3s-Jun27_02_MC-FL-1-R121348-E447-DTS17092002_134321-pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol221/disk4/c3mc/data16/y3s/output/y3s-Jun27_02_MC-FL-1-R121349-E960-DTS17092002_134335-pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol221/disk4/c3mc/data16/y3s/output/y3s-Jun27_02_MC-FL-1-R121361-E615-DTS17092002_134348-pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol221/disk4/c3mc/data16/y3s/output/y3s-Jun27_02_MC-FL-1-R121362-E298-DTS17092002_134401-pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol221/disk4/c3mc/data16/y3s/output/y3s-Jun27_02_MC-FL-1-R121365-E1100-DTS17092002_134414-pass2.pds event startrun beginrun endrun physics
file add pdschain /cdat/sol221/disk4/c3mc/data16/y3s/output/y3s-Jun27_02_MC-FL-1-R121369-E793-DTS17092002_134427-pass2.pds event startrun beginrun endrun physics

proc sel ../build_SunOS/shlib/SubcollectionCuts

go 10000

