#======================================
#
# file: exclude_constants_streams.tcl
# author: Chris D Jones
#
# purpose: Make it easy to exclude Constants Streams
#   AFTER the constants source has already been loaded
#
# Usage
#   Typically this script will be used by calibrators
#   to allow them to exclude the stream which contains
#   the constant they are working on while still
#   using a standard constants script to load all the
#   other constants.
#
#   In suez
#    Suez> #load standard constants script
#    Suez> run_file $env(C3_SCRIPTS)/getConstants.tcl
#    Suez> #now exclude svalignment stream
#    Suez> run_file $env(C3_SCRIPTS)/exclude_constants_streams.tcl
#    Suez> exclude_constants_streams svaligment
#
#   Multiple streams may be excluded with one command using
#    tcl's normal list syntax
#    Suez> exclude_constants_streams {svalignment dralignment}
#
#
#======================================
tcl_proc source_stream_list {} {
# create a tcl list containing the source's token and
#  what streams it delivers
    set sourceLs [source ls]
    set tempList [split $sourceLs "\n"]

    set returnValue {}
    set source_stream {}
    set foundSource 0
    foreach entry $tempList {
	if {! $foundSource } {
	    if [regexp " *Source .*" $entry ] {
		set source_stream {}
		set foundSource 1
		regsub "Source" $entry " " token
		set token [string trim $token]
		set token [string trimright $token ":"]
		set token [string trim $token "\""]
		lappend source_stream $token
	    } else {
		continue
	    }
	} else { 
	    if [regexp " *Streams: " $entry] {
		regsub "Streams:" $entry " " streams
		set streams [string trim $streams]
		lappend source_stream [split $streams]
		lappend returnValue $source_stream
		set foundSource 0
	    }
	}
    }
    return $returnValue
}

tcl_proc exclude_constants_streams streamList {
# find the Constants sources
    foreach source [source_stream_list] {
	set token [lindex $source 0]
	if [ regexp "Codi" $token ] {
	    set sourceToStream($token) [lindex $source 1]
	}
    }

# find the source that supplies this stream and
#  tell it to not deliver that stream
# if that was the only stream for that source,
#  remove the source
    foreach stream $streamList {
	set foundStream 0

	foreach token [array names sourceToStream] {
	    set streams $sourceToStream($token)
	    set index [lsearch -exact $streams $stream]
	    if { $index != -1 } {
		set foundStream 1
		if { 1 == [llength $streams] } {
		    source remove $token
		    break
		} else {
		    set streams [lreplace $streams $index $index ]
		    set sourceToStream($token) $streams
		    set streams [split $streams]
# must build and evaluate command seperately to make sure suez
#  doesn't think the variable holding the stream names is actually
#  one very long stream name!
		    set command "source bind $token $streams"
		    eval $command
		    break
		}
	    }
	}
	if { 0 == $foundStream } {
	    puts "no Constants source contains stream $stream"
	}
    }
}
