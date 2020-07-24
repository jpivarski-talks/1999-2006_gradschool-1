default prompt off

module sel HbookHistogramModule
hbook file /cdat/dafe/mccann/getradbhas_16.rzn
hbook init

run_file $env(C3_SCRIPTS)/runOnPass2.tcl
prod sel CesrBeamEnergyProd
proc sel ../build_SunOS/shlib/GetRadBhas

module sel DBModule
database in /nfs/cleo3/database/data16/db event startrun beginrun endrun
database read_collection pass2 bhagam

# source_format sel PDSSourceFormat
# source create pdschain
# file add pdschain /cdat/sol221/disk3/c3mc/data7/bhabha/output/bhabha-cleo3_MCPS2_Jan30_2002-MN-1-R112802-E3387-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol221/disk3/c3mc/data7/bhabha/output/bhabha-cleo3_MCPS2_Jan30_2002-MN-1-R112803-E5539-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol221/disk3/c3mc/data7/bhabha/output/bhabha-cleo3_MCPS2_Jan30_2002-MN-1-R112804-E4832-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol221/disk3/c3mc/data7/bhabha/output/bhabha-cleo3_MCPS2_Jan30_2002-MN-1-R112805-E5269-pass2.pds physics event startrun beginrun endrun
# file add pdschain /cdat/sol221/disk3/c3mc/data7/bhabha/output/bhabha-cleo3_MCPS2_Jan30_2002-MN-1-R112806-E4977-pass2.pds physics event startrun beginrun endrun

go
exit
