default prompt off

run_file $env(C3_SCRIPTS)/getMCConstants.tcl
run_file $env(C3_SCRIPTS)/trackingMCFull.tcl
run_file $env(C3_SCRIPTS)/CcP2.tcl
prod sel TrackShowerMatchingProd
prod sel DBEventHeaderProd
prod sel CesrBeamEnergyProd
prod sel TriggerDataProd
prod sel EventPropertiesProd
proc sel ../build_SunOS/shlib/HitEfficiency

source_format sel PDSSourceFormat
source create pdschain
file add pdschain /cdat/dafe/mccann/mcsuper/pds/cleog_y1ggg_123610_db18.pds physics event startrun beginrun endrun
file add pdschain /cdat/dafe/mccann/mcsuper/pds/cleog_y1ggg_123611_db18.pds physics event startrun beginrun endrun
file add pdschain /cdat/dafe/mccann/mcsuper/pds/cleog_y1ggg_123612_db18.pds physics event startrun beginrun endrun
file add pdschain /cdat/dafe/mccann/mcsuper/pds/cleog_y1ggg_123615_db18.pds physics event startrun beginrun endrun
file add pdschain /cdat/dafe/mccann/mcsuper/pds/cleog_y1ggg_123616_db18.pds physics event startrun beginrun endrun
file add pdschain /cdat/dafe/mccann/mcsuper/pds/cleog_y1ggg_123617_db18.pds physics event startrun beginrun endrun
file add pdschain /cdat/dafe/mccann/mcsuper/pds/cleog_y1ggg_123618_db18.pds physics event startrun beginrun endrun
file add pdschain /cdat/dafe/mccann/mcsuper/pds/cleog_y1ggg_123619_db18.pds physics event startrun beginrun endrun
file add pdschain /cdat/dafe/mccann/mcsuper/pds/cleog_y1ggg_123620_db18.pds physics event startrun beginrun endrun
file add pdschain /cdat/dafe/mccann/mcsuper/pds/cleog_y1ggg_123621_db18.pds physics event startrun beginrun endrun
file add pdschain /cdat/dafe/mccann/mcsuper/pds/cleog_y1ggg_123623_db18.pds physics event startrun beginrun endrun
file add pdschain /cdat/dafe/mccann/mcsuper/pds/cleog_y1ggg_123624_db18.pds physics event startrun beginrun endrun
file add pdschain /cdat/dafe/mccann/mcsuper/pds/cleog_y1ggg_123631_db18.pds physics event startrun beginrun endrun
file add pdschain /cdat/dafe/mccann/mcsuper/pds/cleog_y1ggg_123632_db18.pds physics event startrun beginrun endrun
file add pdschain /cdat/dafe/mccann/mcsuper/pds/cleog_y1ggg_123633_db18.pds physics event startrun beginrun endrun
file add pdschain /cdat/dafe/mccann/mcsuper/pds/cleog_y1ggg_123635_db18.pds physics event startrun beginrun endrun
file add pdschain /cdat/dafe/mccann/mcsuper/pds/cleog_y1ggg_123636_db18.pds physics event startrun beginrun endrun
file add pdschain /cdat/dafe/mccann/mcsuper/pds/cleog_y1ggg_123637_db18.pds physics event startrun beginrun endrun
file add pdschain /cdat/dafe/mccann/mcsuper/pds/cleog_y1ggg_123638_db18.pds physics event startrun beginrun endrun
file add pdschain /cdat/dafe/mccann/mcsuper/pds/cleog_y1ggg_123639_db18.pds physics event startrun beginrun endrun
file add pdschain /cdat/dafe/mccann/mcsuper/pds/cleog_y1ggg_123640_db18.pds physics event startrun beginrun endrun

go
