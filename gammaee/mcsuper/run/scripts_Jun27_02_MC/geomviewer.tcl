#==============================================================
# file: geomviewer.tcl
# author: Chris Jones
# Purpose: make it easier to set up processors used to view
#          detector geometry
#==============================================================
proc sel SpExtractDetectorStoreProc
proc sel SpViewerProc
tcl_source $env(C3_SCRIPTS)/findproxy.tcl
tcl_proc geomviewer { parameter { value ""} } {
    if { 0 == [ string compare "stream" $parameter ] } {
	param SpExtractDetectorStoreProc stream $value
	param SpViewerProc stream $value
    }
    if { 0 == [ string compare "usage_tag" $parameter ] } {
	param SpExtractDetectorStoreProc extract_usage_tag $value
    }
    if { 0 == [string compare "ls" $parameter ] } {
	set proxies [findproxy "DGDetectorStore"]
	foreach proxy $proxies {
	    echo "Producer: [lindex $proxy 0 ]"
	    echo " stream [lindex $proxy 1]"
	    echo " usage_tag [lindex [lindex $proxy 2 ] 1 ]"
	}
    }
    if { 0 == [ string compare "help" $parameter ] } {
	echo ""
	echo "// Description: geomviewer"
	echo "//"
	echo "//    Valid subcommands"
	echo "//"
	echo "// geomviewer help          this help page"
	echo "// geomviewer stream <strm> "
	echo "//       extracts DGDetectorStore from stream <strm>"
	echo "// geomviewer extract_usage_tag <tag>"
	echo "//       extracts DGDetectorStore using Usage tag <tag>"
	echo "// geomviewer ls"
	echo "//       lists all proxies of type DGDetectorStore"
    }
}
echo "--------------------------------------------------"
echo " use 'geomviewer' command to setup the processors"
echo "  geomviewer stream <stream name>"
echo "    extracts the DGDetectorStore from <stream name>"
echo "  geomviewer usage_tag <tag name>"
echo "    extracts the DGDetectorStore using Usage tag <tag name>"
echo "--------------------------------------------------"
