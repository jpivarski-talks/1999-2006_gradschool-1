##################################################################
# file: $C3_SCRIPTS/loader_lss.tcl
#
# purpose: generate a tcl list from a '<loader> lss' command
#
# usage:
# 
#  inside Suez issue the command 
#    loader_lss <type>
#
##################################################################

tcl_proc loader_lss {loader_type} {
    set prodList [split [ string trim [eval "$loader_type lss"] ] "\n" ]
    set returnValue [list]
    foreach prodInfo $prodList {
	# the format is " prodName : prodFile "
	set prodName [ string trim [ lindex [ split $prodInfo ":"] 0 ] ]
	lappend returnValue $prodName
    }
    return $returnValue
}
