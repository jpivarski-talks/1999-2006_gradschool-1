##################################################################
# file: $C3_SCRIPTS/prod_tcl_lss.tcl
#
# purpose: generate a tcl list from the 'prod lss' command
#
# usage:
# 
#  inside Suez issue the command 
#    prod_tcl_lss
#
##################################################################

tcl_proc prod_tcl_lss {} {
    set prodList [split [ string trim [prod lss] ] "\n" ]
    set returnValue [list]
    foreach prodInfo $prodList {
	# the format is " prodName : prodFile "
	set prodName [ string trim [ lindex [ split $prodInfo ":"] 0 ] ]
	lappend returnValue $prodName
    }
    return $returnValue
}
