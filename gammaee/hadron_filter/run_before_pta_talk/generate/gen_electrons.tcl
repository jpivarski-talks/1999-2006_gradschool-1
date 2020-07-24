default prompt off
exception continueEventLoop on

run_file $env(C3_SCRIPTS)/getConstants.tcl
run_file $env(C3_SCRIPTS)/trackingDataFull.tcl

run_file $env(C3_SCRIPTS)/C3cc.tcl
prod sel CcfcReconProd
prod sel TrackShowerMatchingProd

prod sel MutrReconProd
prod sel MuConsProd
run_file $env(C3_SCRIPTS)/load_geometry_producers.tcl
run_file $env(C3_SCRIPTS)/load_dg_to_geant3_converter.tcl
prod sel MagFieldProd
prod sel RawDataProd

prod sel DBEventHeaderProd
prod sel CesrBeamEnergyProd
prod sel EventPropertiesProd
prod sel EventTypeProd

source_format sel BinarySourceFormat
source create binchain
file add binchain sb_binaries/electrons1.bin event startrun beginrun endrun
file add binchain sb_binaries/electrons2.bin event startrun beginrun endrun
file add binchain sb_binaries/electrons3.bin event startrun beginrun endrun
file add binchain sb_binaries/electrons4.bin event startrun beginrun endrun

sink_format sel PDSSinkFormat
file sink $env(USER_TMP)/new_electrons.pds event startrun beginrun endrun

go
exit
