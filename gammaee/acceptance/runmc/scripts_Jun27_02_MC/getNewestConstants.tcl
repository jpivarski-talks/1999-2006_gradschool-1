# ===================================================
# getNewestConstants.tcl
# 
# This script provides you with the newest constants
# for data. 
# To obtain the versions that were used together with
# PASS2, use getPass2Constants.tcl.
# ===================================================

if { ! [info exists getConstants_tcl_loaded] } {
# keep script from multiply loading
    set getConstants_tcl_loaded 1
# This is a standard script for configuring/accessing the constants
# database (and the materials properties ascii file).  It can be
# invoked from your tcl script via
#
#    run_file $env(C3_SCRIPTS)/getConstants.tcl
#

    if [ catch {

	global env  # make env available in nested calls

# database and metafiles -------
	module sel CorbaModule
	corba init
	module sel ConstantsModule
	constants in $env(C3_CONST) meta Offline MetaListRetrieval
	constants in $env(C3_CONST) meta Online MetaListRetrieval
	constants in $env(C3_CONST) meta CesrOffset MetaListRetrieval
	constants in $env(C3_CONST) meta BaseGeometry MetaListRetrieval
	constants in $env(C3_CONST) meta RunByRun MetaListRetrieval
	constants in $env(C3_CONST) meta SVHybridEfficiency MetaListRetrieval
	constants in $env(C3_CONST) meta Alignment MetaListRetrieval
	constants in $env(C3_CONST) meta FieldMap MetaListRetrieval
	constants in $env(C3_CONST) meta Dedx MetaListRetrieval
        constants in $env(C3_CONST) meta MagFudge MetaListRetrieval
        constants in $env(C3_CONST) meta DAQID MetaListRetrieval

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
