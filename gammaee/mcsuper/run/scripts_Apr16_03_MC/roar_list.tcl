#############################
# a little script that loads in the rp files for the CLEO II datasets
# all of these return the name of the source that was created
#
# roar_list_named <file> <srcname>
#   creates a chain called srcname, and adds all the files listed in file to
#   the chain
#
# load_dataset <dataset>
#   takes a dataset name (for example 4sT), and reads the file found in 
#   /cdat/roar/list to create a chain
#
# roar_list <path>
#   takes the file in path and calls roar_list_named by using the name of
#   the file
#############################


tcl_proc roar_list_named {filename chain} {
    eval source_format sel DriverSourceFormat
    set sourceName [source create $chain]
    set fileName [open $filename]
    while {[gets $fileName line] >= 0} {
	set isrp [regexp rp$ $line]
	if { $isrp } {
	    eval file add $sourceName $line
	}
    }
    close $fileName
    return $sourceName
}

tcl_proc load_dataset {dset} {
    return [roar_list_named /cdat/roar/list/$dset $dset]
}

tcl_proc roar_list {filename} {
    regexp {.*/([^/]*)$} $filename match srcname
    set srcname
    return [roar_list_named $filename $srcname]
}
