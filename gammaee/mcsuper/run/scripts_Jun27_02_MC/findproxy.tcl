#==============================================================
# file: findproxy.tcl
# author: Chris Jones
# Purpose: find all Producers that have a proxy of a particular type.
#           Returns a list of
#             -Producer's name
#             -the Proxy's stream
#             -the Proxy's key {TypeKey UsageKey ProductionKey}
#==============================================================
# define a user command
tcl_proc findproxy { datatype } {
    if { 0 == [ string compare "help" $datatype ] } {
	echo ""
	echo "// Description: findproxy"
	echo "//"
	echo "//    Valid subcommands"
	echo "//"
	echo "// findproxy help          this help page"
	echo "// findproxy <type> "
	echo "//       find all proxies that return data of type <type>"
	return
    }
    #get the list of loaded producers
    set prodlss [ split [ prod lss ] "\n" ]
    set producers {} 
    foreach entry $prodlss {
	lappend producers [ lindex [ split $entry ":" ] 0 ]
    }
    set proxies {}
    foreach producer $producers {
	set prodName [ string trim $producer ]
	#skip any blank names
	if { 0 != [string length $prodName] } {
	    #now get all the proxies
	    set proxyls [ split [param $prodName proxy ls] "\n" ]

	    set streamName ""
	    foreach line $proxyls {
		if { 1 == [ regexp "Proxies for stream" $line ] } {
		    #hold the stream name
		    set streamName [ lindex [split $line] 3]
		    set streamName [ string trim $streamName ":" ]
		} else {
		    if { 1 == [ regexp $datatype $line] } {
			#clean up the data
			set keyinfo [ split $line ","]
			set keyinfo [ lreplace $keyinfo 0 0 [string trim [lindex $keyinfo 0] "\"" ] ]
			set keyinfo [ lreplace $keyinfo 1 1 [string trim [lindex $keyinfo 1] ] ] 			
			set keyinfo [ lreplace $keyinfo 2 2 [string trim [lindex $keyinfo 2] ] ]
			lappend proxies [ list $prodName $streamName $keyinfo ]
		    }
		}
	    }
	}
    }
#    echo $proxies
    return $proxies
}
