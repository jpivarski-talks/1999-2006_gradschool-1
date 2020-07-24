#########################################################################
## This script allows you to run on specific runs in the database.
## In your tcl script, do
##
## module sel DBModule
## run_file $env(C3_SCRIPTS)/database_run.tcl
##
## database_run <run #>
## go
## database_run <run #>
## go
## etc.
##
## This chooses the hadron subcollection, and has the last runs in each
## db hardcoded.  It will eventually be out of date.  Beware.
#########################################################################


tcl_proc database_run run_number {
    set lastruns {0 0 107913 109688 110278 112258 113216 114137 115063 116093 116918 }
    set dataset 0
    set tempdataset 1
    foreach lastrun $lastruns {
	incr tempdataset
	if { $lastrun < $run_number } {
	    set dataset $tempdataset
	}
    }
    if { $dataset == 0 } {
	error "some error"
    }
    set fdb "/nfs/cleo3/database/data$dataset"
    append fdb "/db"
    database in $fdb beginrun event endrun
    database read_collection pass2 hadron
    database run $run_number
}
