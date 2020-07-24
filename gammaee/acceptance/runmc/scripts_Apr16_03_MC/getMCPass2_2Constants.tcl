if { ! [info exists getMCConstants_tcl_loaded] } {
# keep script from multiply loading
    set getMCConstants_tcl_loaded 1
# This is NOT a standard script for configuring/accessing the constants
# database (and the materials properties ascii file).  It can be
# invoked from your tcl script via
#
#    run_file $env(C3_SCRIPTS)/getMCPass2_2Constants.tcl
#
# This is to be used ONLY for data7 and data8.
# Use the "regular" getConstants script for PASS2_2 MonteCarlo
# for other datasets.

    if [ catch {

	global env  # make env available in nested calls

# database and metafiles -------
	module sel CorbaModule
	corba init
	module sel ConstantsModule
	constants in $env(C3_CONST) meta PASS2_2Offline MetaListRetrieval exclude_streams richgains richalignment
	constants in $env(C3_CONST) meta PASS2_2Alignment_NewRICHAlignment MetaListRetrieval
	constants in $env(C3_CONST) meta Online MetaListRetrieval
	constants in $env(C3_CONST) meta PASS2_2CesrOffset MetaListRetrieval
	constants in $env(C3_CONST) meta PASS2_2BaseGeometry_NewRICHAlignment MetaListRetrieval
	constants in $env(C3_CONST) meta PASS2_2RunByRun MetaListRetrieval
	constants in $env(C3_CONST) meta PASS2_2SVHybridEfficiency MetaListRetrieval
	constants in $env(C3_CONST) meta PASS2_2MonteCarlo MetaListRetrieval

# Get saturation constants needed by RICH MC
	source_format sel RICHGainsFileSourceFormat
	file in $env(C3_DATA)/default.richgains richgains

# Get material properties-------
	source_format sel AsciiSourceFormat
	file in $env(C3_DATA)/material.asc basegeometry

# set up runStatistics access
	module sel RunStatisticsSourceModule
	runstatistics in

# load mu constants producer
	prod select MuConsProd

    } resultString ] { # ------------------- tcl try-catch block
	puts stdout "loading failed for constants database:"
	puts stdout "resultString:"
	puts stderr "$resultString"
# throw exception so if this script is included by another script, the
#  parent script can see that there was an exception
	error "constants loading problem: $resultString"
    } else {
	puts stdout "Constants database setup successfully"
    }
}
