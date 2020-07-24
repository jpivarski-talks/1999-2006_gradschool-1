
tcl_proc parse_args {args argNames} {
   
   set returnValue(dummy) ""
   set unfoundArgs $args
   set unfoundArgNames []
   foreach arg_info $argNames {
      lappend unfoundArgNames [lindex $arg_info 0]
   }
   foreach arg_info $argNames {
      set argName [lindex $arg_info 0]
      set argIndex [lsearch -exact $args $argName]
      if { $argIndex != -1 } {
         set nArgs [lindex $arg_info 1]
         if { 0 != $nArgs } {
            set returnValue($argName) [lrange $args [expr $argIndex + 1] [expr $argIndex + $nArgs ] ] 
         } else {
            set returnValue($argName) ""
         }
         set unfoundArgsIndex [lsearch -exact $unfoundArgs $argName] 
         if { $unfoundArgsIndex == -1 } {
            error "parse_args: argument name $args was found as the value for the preceeding argument"
         }
         set unfoundArgs [lreplace $unfoundArgs $unfoundArgsIndex [expr $unfoundArgsIndex + $nArgs] ]

         set unfoundArgNamesIndex [lsearch -exact $unfoundArgNames $argName]
         if {$unfoundArgNamesIndex == -1} {
            error "parse_args: found multiple instances of $argName argument"
         }
         set unfoundArgNames [lreplace $unfoundArgNames $unfoundArgNamesIndex $unfoundArgNamesIndex]
      } 
   }
   if { 0 != [llength $unfoundArgs] } {
      error "parse_args: found unknown arguments : $unfoundArgs"
   }
   foreach unfoundArg $unfoundArgNames {
      if { "-" != [string index $unfoundArg 0] } {
         error "parse_args: required argument $unfoundArg was not specified"
      }
   }
   return [array get returnValue]
}
