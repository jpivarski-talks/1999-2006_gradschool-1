########################################################################
## File:    mcfile_command.tcl
## Purpose: manage the Monte Carlo production files
########################################################################

module sel EnableFPEModule
#***********************************************************************
# Prelude
#***********************************************************************
run_file $env(C3_SCRIPTS)/parse_args_command.tcl
# To make the environmental variables accessible
global env

# Local mcfile.list overwrites the official
if {[tcl_file isfile mcfile.list] == 1} {
    set stringMCFileList mcfile.list
    puts "mcfile: using local mcfile.list"
} else {
    set stringMCFileList $env(C3_INFO)/mc/mcfile.list
    puts "mcfile: using official \$C3_INFO/mc/mcfile.list"
}

# Check if the file exists
if {[tcl_file exists $stringMCFileList] != 1} {
    error "mcfile: $stringMCFileList doesn't exist"
}

#***********************************************************************
# Master procedure that calls all other procedures
#***********************************************************************
tcl_proc mcfile args {
    # Dynamically determine the subcommand to call.
    # This allows for easy addition of new subcommands
    # (i.e. they just need to be called mcfile_<subcommand name>)
    set subCommand [lindex $args 0]
    if {[llength $args] == 0} {    # No sub command, print the "help"
	set subCommand "help"
    } elseif {[string compare mcfile_$subCommand \
		              [info procs mcfile_$subCommand] ] != 0} {
	error "mcfile: unknown sub command: $subCommand"
    }

    # Execute the sub command
    eval mcfile_$subCommand [lrange $args 1 [llength $args]]
    return
}

#***********************************************************************
# standard subcommands
#***********************************************************************
#=======================================================================
# Public sub commands
#=======================================================================
#-----------------
# help sub command
#-----------------
# proc is to print the help information
tcl_proc mcfile_help {} {
    puts ""
    puts "Description: mcfile"
    puts "-----------"
    puts "      Manage Monte Carlo files\n"
    puts "Subcommands:"
    puts "-----------"
    puts "      help   this page"
    puts "      ----\n"
    puts "      in dataset <id> physType <type> -runMin <runMin> -runMax <runMax> -export \[<fileName>\]"
    puts "      --"
    puts "             Create a file chain\n"
    puts "      ls dataset <id> physType <type> -runMin <runMin> -runMax <runMax> -export \[<fileName>\]"
    puts "      --"
    puts "             List the desired files\n"
    puts "      status"
    puts "      ------"
    puts "             List available datasets, physics types, run ranges, and paths\n"
}

#----------------------
# mcfile_in sub command
#----------------------
# proc to get list of pds files for given dataset, physics type, and run range
# It's designed as a public sub command
tcl_proc mcfile_in args {
    # Parse the arguments
    set arg_names {{dataset 1} {physType 1} {-runMin 1} {-runMax 1} {-export 1}}
    set parsedArgs [parse_args $args $arg_names]
    array set arrayArgs $parsedArgs

    # Get dataset
    set stringDataset [format "data%d" $arrayArgs(dataset)]

    # Get physics type
    set stringPhysType $arrayArgs(physType)

    # Get run range
    if [catch {
	set intRunMin $arrayArgs(-runMin)
    }] {
	set intRunMin 0
    }
    if [catch {
	set intRunMax $arrayArgs(-runMax)
    }] {
	set intRunMax 999999
    }
    if {$intRunMin == 0 || $intRunMax == 999999} {
	set listPath [mcfile_getRequiredPathList $stringDataset $stringPhysType $intRunMin $intRunMax]
	set intNewRunMin 999999
	set intNewRunMax 0
	# Loop over paths
	foreach stringPath $listPath {
	    set runRange [mcfile_extractRunRangeFromPath $stringPath]
	    set intCurRunMin [lindex $runRange 0]
	    set intCurRunMax [lindex $runRange 1]
	    if {$intCurRunMin < $intNewRunMin} {
		set intNewRunMin $intCurRunMin
	    }
	    if {$intCurRunMax > $intNewRunMax} {
		set intNewRunMax $intCurRunMax
	    }
	}
	if {$intRunMin == 0} {
	    set intRunMin $intNewRunMin
	}
	if {$intRunMax == 999999} {
	    set intRunMax $intNewRunMax
	}
    }

    # Get export file
    if [catch {
	set stringExportFile $arrayArgs(-export)
	if {[string length $stringExportFile] == 0} {
	    set stringExportFile "$stringDataset$stringPhysType$intRunMin-$intRunMax.tcl"
	}
	puts "mcfile: export file chain to $stringExportFile"
    }] {
	set stringExportFile ""
    }

    # Get a list of pds files
    set listPdsFile [mcfile_getPdsFileList $stringDataset $stringPhysType $intRunMin $intRunMax]
    if {[llength $listPdsFile] == 0} {
	error "No MC run available, check the arguments"
    }

    if {[string length $stringExportFile] == 0} {
	# Create the file chain
	source_format sel PDSSourceFormat
	source create MCFileChain
	foreach stringPdsFile $listPdsFile {
	    file add MCFileChain $stringPdsFile beginrun startrun event physics endrun
	    puts "  added file $stringPdsFile"
	}
    } else {
	# Export to file
	set fileExportFile [open $stringExportFile w]
	puts $fileExportFile "source_format sel PDSSourceFormat"
	puts $fileExportFile "source create MCFileChain"
	foreach stringPdsFile $listPdsFile {
	    puts $fileExportFile "file add MCFileChain $stringPdsFile beginrun startrun event physics endrun"
	}
	close $fileExportFile
    }
}

#----------------------
# mcfile_ls sub command
#----------------------
# proc to list the pds files for given dataset, physics type, and run range
# It's designed as a public sub command
tcl_proc mcfile_ls args {
    # Parse the arguments
    set arg_names {{dataset 1} {physType 1} {-runMin 1} {-runMax 1} {-export 1}}
    set parsedArgs [parse_args $args $arg_names]
    array set arrayArgs $parsedArgs

    # Get dataset
    set stringDataset [format "data%d" $arrayArgs(dataset)]

    # Get physics type
    set stringPhysType $arrayArgs(physType)

    # Get run range
    if [catch {
	set intRunMin $arrayArgs(-runMin)
    }] {
	set intRunMin 0
    }
    if [catch {
	set intRunMax $arrayArgs(-runMax)
    }] {
	set intRunMax 999999
    }
    if {$intRunMin == 0 || $intRunMax == 999999} {
	set listPath [mcfile_getRequiredPathList $stringDataset $stringPhysType $intRunMin $intRunMax]
	set intNewRunMin 999999
	set intNewRunMax 0
	# Loop over paths
	foreach stringPath $listPath {
	    set runRange [mcfile_extractRunRangeFromPath $stringPath]
	    set intCurRunMin [lindex $runRange 0]
	    set intCurRunMax [lindex $runRange 1]
	    if {$intCurRunMin < $intNewRunMin} {
		set intNewRunMin $intCurRunMin
	    }
	    if {$intCurRunMax > $intNewRunMax} {
		set intNewRunMax $intCurRunMax
	    }
	}
	if {$intRunMin == 0} {
	    set intRunMin $intNewRunMin
	}
	if {$intRunMax == 999999} {
	    set intRunMax $intNewRunMax
	}
    }

    # Get export file
    if [catch {
	set stringExportFile $arrayArgs(-export)
	if {[string length $stringExportFile] == 0} {
	    set stringExportFile "$stringDataset$stringPhysType$intRunMin-$intRunMax.txt"
	}
	puts "mcfile: export file list to $stringExportFile"
    }] {
	set stringExportFile ""
    }

    # Get a list of pds files
    set listPdsFile [mcfile_getPdsFileList $stringDataset $stringPhysType $intRunMin $intRunMax]

    if {[string length $stringExportFile] == 0} {
	# Print files
	foreach stringPdsFile $listPdsFile {
	    puts $stringPdsFile
	}
    } else {
	# Export to file
	set fileExportFile [open $stringExportFile w]
	foreach stringPdsFile $listPdsFile {
	    puts $fileExportFile $stringPdsFile
	}
	close $fileExportFile
    }
}

#-------------------
# status sub command
#-------------------
# proc to print the available datasets, physics types, and run ranges
tcl_proc mcfile_status {} {
    # Get all available datasets
    set listDatasets [mcfile_getAvailableDatasets]
    # Loop over datasets to get physics type and run range information
    puts "    Current Available Datasets, Physics Types, Run Ranges, and Paths"
    puts "    ----------------------------------------------------------------"
    puts ""
    if {[llength $listDatasets] == 0} {
	puts "None"
    }
    foreach stringDataset $listDatasets {
	puts "$stringDataset:"
	# Get available physics types
	set listPhysType [mcfile_getPhysTypesForDataset $stringDataset]
	if {[llength $listPhysType] > 0} {
	    # Get the maximum length of physics types
	    # This is for print alignment
	    set intLengthMax 0
	    foreach stringPhysType $listPhysType {
		set intLength [string length $stringPhysType]
		if {$intLengthMax < $intLength} {
		    set intLengthMax $intLength
		}
	    }
	    if {$intLengthMax < 8} {
		set intLengthMax 8
	    }

	    # Loop over physics types to get run range
	    foreach stringPhysType $listPhysType {
		# Get the list of pds files
		set listPdsFile [mcfile_getPdsFileList $stringDataset $stringPhysType 0 999999]
		# Set initial values
		set intRunMin 999999
		set intRunMax 0
		# Loop over all pds files to get the run range
		foreach stringPdsFile $listPdsFile {
		    set intRun [mcfile_extractRunFromPdsFile $stringPdsFile]
		    if {$intRun < $intRunMin} {
			set intRunMin $intRun
		    }
		    if {$intRun > $intRunMax} {
			set intRunMax $intRun
		    }
		}

		# Get corresponding paths
		set listPath [mcfile_getRequiredPathList $stringDataset $stringPhysType $intRunMin $intRunMax]
		if {[llength $listPath] == 0} {
		    continue
		}

		# Align the physcis type printing
		set stringType $stringPhysType
		for {set i [expr [string length $stringPhysType]+1]} {$i <= $intLengthMax} {incr i} {
		    set stringType "$stringType "
		}
		puts "    $stringType \[$intRunMin-$intRunMax\] [lindex $listPath 0]"
		# Print the rest paths
		for {set i 1} {$i < [llength $listPath]} {incr i} {
		    puts "                             [lindex $listPath $i]"
		}
	    }
	} else {
	    puts "     no physics type available"
	}
	puts ""
    }
}

#=======================================================================
# Private sub commands
#=======================================================================
#------------------------
# getPathList sub command
#------------------------
# proc to get a list of paths for all Monte Carlo data
# It's designed as a private sub command, but you can still use it
tcl_proc mcfile_getPathList {} {
    # To make stringMCFileList usable here
    global env stringMCFileList

    # Construct the path list according mcfile.list
    set listPath ""
    set fileMCFileList [open $stringMCFileList RDONLY]
    while {[gets $fileMCFileList stringPath] >= 0} {
	# Check to see if it's a directory accessible
	if {[tcl_file isdirectory $stringPath] != 1} {
	    puts "mcfile: $stringPath is not accessible"
	    continue
	}
	set listPath [lappend listPath $stringPath]
    }
    close $fileMCFileList

    # Check if we have anything in the list
    if {[llength $listPath] == 0} {
	error "mcfile: $stringMCFileList is empty or paths therein are inaccessible"
    }

    return $listPath
}

#--------------------------------
# getRequiredPathList sub command
#--------------------------------
# proc to get a list of paths for required Monte Carlo data
# It's designed as a private sub command, but you can still use it
tcl_proc mcfile_getRequiredPathList {stringDataset stringPhysType intRunMin intRunMax} {
    # To make stringMCFileList usable here
    global env stringMCFileList

    # Construct the path list according mcfile.list
    set listPath ""
    set fileMCFileList [open $stringMCFileList RDONLY]
    while {[gets $fileMCFileList stringPath] >= 0} {
	# Check to see if it's a directory accessible
	if {[tcl_file isdirectory $stringPath] != 1} {
	    puts "mcfile: $stringPath is not accessible"
	    continue
	}

	# Check to see if it's the required dataset
	set stringCurDataset [mcfile_extractDatasetFromPath $stringPath]
	if {$stringCurDataset != $stringDataset} {
	    continue
	}

	# Check to see if it's the required physics type
	set stringCurPhysType [mcfile_extractPhysTypeFromPath $stringPath]
	if {$stringCurPhysType != $stringPhysType} {
	    continue
	}

	# Check to see the run range is ok
	set runRange [mcfile_extractRunRangeFromPath $stringPath]
	set intCurRunMin [lindex $runRange 0]
	set intCurRunMax [lindex $runRange 1]
	if {$intCurRunMax < $intRunMin || $intCurRunMin > $intRunMax} {
	    continue
	}

	# Ok, append the path
	set listPath [lappend listPath $stringPath]
    }
    close $fileMCFileList

    return $listPath
}

#---------------------------------
# getAvailableDatasets sub command
#---------------------------------
# proc to get available datasets by scanning mcfile.list
# It's designed as a private sub command, but you can still use it
tcl_proc mcfile_getAvailableDatasets {} {
    # Get the list of paths
    set listPath [mcfile_getPathList]

    # Loop over all paths in listPath to get all available datasets
    set listAvailableDatasets ""
    foreach stringPath $listPath {
	# Extract the dataset name
	set stringDataset [mcfile_extractDatasetFromPath $stringPath]
	# Skip path which doesn't have dataset information
	if {[string length $stringDataset] == 0} {
	    continue
	}
	# Append it to the list if it's not in
	if {[lsearch $listAvailableDatasets $stringDataset] == -1} {
	    lappend listAvailableDatasets $stringDataset
	}
    }

    # Sort the datasets
    set listAvailableDatasets [lsort -command mcfile_sortDataset $listAvailableDatasets]

    return $listAvailableDatasets
}

#-----------------------------------
# extractDatasetFromPath sub command
#-----------------------------------
# It's designed as a private sub command, but you can still use it
tcl_proc mcfile_extractDatasetFromPath {stringPath} {
    # Using regexp to get the substring with pattern data[0-9]+
    # Note: + in the above pattern means at least one digit,
    # so don't use * (which means zero or more matches of the preceding atom
    set dataset ""
    set numOfMatches [regexp {data[0-9]+} $stringPath dataset]
    if {$numOfMatches > 1} {
	error "mcfile: found more than one matches of data[0-9]+ in $stringPath"
    }

    # Return the dataset string in format of e.g. data15
    return $dataset
}

#------------------------
# sortDataset sub command
#------------------------
# proc to sort dataset
# It's designed as a private sub command for mcfile_getAvailableDatasets
tcl_proc mcfile_sortDataset {dataset1 dataset2} {
    # Get the id (only the digits after "data"
    scan $dataset1 "data%d" datasetId1
    scan $dataset2 "data%d" datasetId2

    # Sort according to the integer ids
    return [expr $datasetId1-$datasetId2]
}

#-----------------------------------
# getPhysTypesForDataset sub command
#-----------------------------------
# proc to get available datasets for a specified dataset
# It's designed as a private sub command, but you can still use it
tcl_proc mcfile_getPhysTypesForDataset {stringDataset} {
    # Get available datasets
    set listDataset [mcfile_getAvailableDatasets]
    # Check if the required dataset is available
    set intIndex [lsearch $listDataset $stringDataset]
    if {$intIndex < 0} {
	error "mcfile: $stringDataset is not available"
    }
    # Loop over listPath to get the corresponding physics types
    set listPhysType {}
    foreach stringPath [mcfile_getPathList] {
	# Get current dataset from the path name
	set stringCurDataset [mcfile_extractDatasetFromPath $stringPath]
	# If it's not required, skip to next path
	if {$stringCurDataset != $stringDataset} {
	    continue
	}
	# Get the physics type from the path name
	set stringPhysType [mcfile_extractPhysTypeFromPath $stringPath]
	# Append it to the list if it's not in
	if {[lsearch $listPhysType $stringPhysType] == -1} {
	    lappend listPhysType $stringPhysType
	}
    }
    # Sort it alphabetically
    return [lsort $listPhysType]
}

#------------------------------------
# extractPhysTypeFromPath sub command
#------------------------------------
# proc to get the physics type from the path name
# It's designed as a private sub command, but you can still use it
tcl_proc mcfile_extractPhysTypeFromPath {stringPath} {
    # Find the matches of the following types
    set numOfMatches [regexp {bhabha|mumu|tau|cont|ups1s|ups2s|ups3s|y3s|ups4s} $stringPath physType]
    if {$numOfMatches == 0 } {
	error "mcfile: unknown physics type in $stringPath"
    } elseif {$numOfMatches > 1 } {
	error "mcfile: found more than one matches of physics type in $stringPath"
    } else {
	if {$physType == "y3s"} {
	    set physType ups3s
	}
    }

    return $physType
}

#----------------------------------
# mcfile_getPdsFileList sub command
#----------------------------------
# proc to get list of pds files for given dataset, physics type, and run range
# It's designed as a private sub command, but you can still use it
tcl_proc mcfile_getPdsFileList {stringDataset stringPhysType intRunMin intRunMax} {
    # Save the original directory
    set pwd [pwd]

    # Initialization
    set listPdsFile ""

    # Get a list of paths indicated by mcfile.list
    set listPath [mcfile_getPathList]

    # Loop over the path list
    foreach stringPath $listPath {
	# Check if the path is accessible
	if ![tcl_file isdirectory $stringPath] {
	    continue
	}

	# Check if this path is the required dataset
	set stringCurDataset [mcfile_extractDatasetFromPath $stringPath]
	if {$stringCurDataset != $stringDataset} {
	    continue
	}

	# Check if this path contains the required physics type
	set stringCurPhysType [mcfile_extractPhysTypeFromPath $stringPath]
	if {$stringCurPhysType != $stringPhysType} {
	    continue
	}

	# Change directory
	cd $stringPath

	# Get all pds files, then loop over them to get those in the run range
	set pdsFiles [glob -nocomplain "*.pds"]
	foreach stringPdsFile $pdsFiles {
	    # Get run number, skip to next file if it's not in the range
	    set intRun [mcfile_extractRunFromPdsFile $stringPdsFile]
	    if {$intRun < $intRunMin || $intRun > $intRunMax} {
		continue
	    }
	    # Remove the trailing slash (/) in the path
	    set stringNewPath $stringPath
	    set intLength [string length $stringNewPath]
	    if {[string index $stringNewPath [expr $intLength-1]] == "/"} {
		set stringNewPath [string range $stringNewPath 0 [expr $intLength-2]]
	    }
	    # Construct the file name
	    lappend listPdsFile "$stringNewPath/$stringPdsFile"
	}
    }
    # Change back to original directory
    cd $pwd

    return $listPdsFile
}

#-----------------------------------------
# mcfile_extractRunFromPdsFile sub command
#-----------------------------------------
# proc to get the run number from a given pds file
# It's designed as a private sub command, but you can still use it
tcl_proc mcfile_extractRunFromPdsFile {stringPdsFile} {
    # First search for pattern -RUN[1-9][0-9]+-
    set numOfMatches [regexp {\-RUN[1-9][0-9]+\-} $stringPdsFile stringRun]
    if {$numOfMatches == 1} {
	scan $stringRun "\-RUN%d+\-" intRun
    } else {
	# Then search for pattern -R[1-9][0-9]+-
	set numOfMatches [regexp {\-R[1-9][0-9]+\-} $stringPdsFile stringRun]
	if {$numOfMatches == 1} {
	    scan $stringRun "\-R%d+\-" intRun
	} else {
	    # Lastly search for pattern _[1-9][0-9]+_
	    set numOfMatches [regexp {_[1-9][0-9][0-9][0-9][0-9][0-9]_} $stringPdsFile stringRun]
	    if {$numOfMatches == 1} {
		scan $stringRun "_%d+_" intRun
	    } else {
		error "mcfile: no run number found in $stringPdsFile"
	    }
	}
    }

    return $intRun
}

#-------------------------------------------
# mcfile_extractRunRangeFromPath sub command
#-------------------------------------------
# proc to get the run range from a given path name
# It's designed as a private sub command, but you can still use it
tcl_proc mcfile_extractRunRangeFromPath {stringPath} {
    # Get the list of pds files under the path
    set pwd [pwd]
    cd $stringPath
    set pdsFiles [glob -nocomplain "*.pds"]
    cd $pwd

    # Initialization
    set intRunMin 999999
    set intRunMax 0

    # Loop over pds files and get the minimum/maximum run number
    foreach stringPdsFile $pdsFiles {
	set intRun [mcfile_extractRunFromPdsFile $stringPdsFile]
	if {$intRun < $intRunMin} {
	    set intRunMin $intRun
	}
	if {$intRun > $intRunMax} {
	    set intRunMax $intRun
	}
    }

    return [list $intRunMin $intRunMax]
}
