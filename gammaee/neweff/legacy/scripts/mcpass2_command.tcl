#============================================================
# File: mcpass2_command.tcl
#
# Purpose:
#   create a 'mcpass2' command used to configure and run pass2 on MC
#
# 
#============================================================

default prompt off
module sel EnableFPEModule

# define procedures used by this script
run_file $env(C3_SCRIPTS)/loader_lss.tcl
run_file $env(C3_SCRIPTS)/exclude_constants_streams.tcl
run_file $env(C3_SCRIPTS)/parse_args_command.tcl
run_file $env(C3_SCRIPTS)/load_proper_format_command.tcl

#--------------------------------------------------
# master procedure that calls all other procedures
#--------------------------------------------------
tcl_proc mcpass2 args {
   # dynamically determine the subcommand to call
   #  this allows for easy addition of new subcommands
   #  (i.e. they just need to be called mcpass2_<subcommand name>
   set generationType [lindex $args 0]
   if { 0 != [string compare mcpass2_$generationType [info procs mcpass2_$generationType] ] } {
      error "mcpass2: unknown sub command: $generationType"
   }
   eval mcpass2_$generationType [lrange $args 1 [llength $args] ]
   return
}

#--------------------------------------------------
# standard subcommands
#--------------------------------------------------
tcl_proc mcpass2_help {} {
   puts "\nDescription: mcpass2"
   puts "\n      pass2 monte carlo files"
   puts "\n  Subcommands are:"
   puts "     help   this page\n"
   puts "mcpass2 file <input cleog file> out <out file> \[-nevents <#>\] "
   puts "          \[ -post <commands>\] "
#\[-start_event <#>\]"
   puts "    starting from an input file made by cleog_command write" 
   puts "    out the pass2'd file to <out file>."
   puts "    Can optionally choose to only process only some of the events in the file by"
   puts "    using \"-nevents <#>\"."
   puts ""
#   puts "   The option -start_event allows you to"
#   puts "   start pass2-ing at an event number other than the beginning"
   puts ""
   puts "   The option -post <commands> allows the specification of"
   puts "                               tcl commands to issue after the mc"
   puts "                               job has been configured but before"
   puts "                               doing \"go\".  This should be used to"
   puts "                               specify a filter Processor: e.g."
   puts "                                -post \{proc sel MyFilterProc\}"
}

#setup MCpass2 using a file
tcl_proc mcpass2_file args {
   global mcpass2_standard_arg_names
   if { 2 > [llength $args] } {
      error "mcpass2: too few arguments"
   }
   set fileName [lindex $args 0]
   
   #add additional option to allow users to specify number of events to process
   set arg_names [concat { {-nevents 1} } $mcpass2_standard_arg_names]
   set parsedArgs [parse_args [lrange $args 1 [llength $args]] $arg_names ]

   mcpass2_setup_job $parsedArgs

   load_proper_format $fileName
   file in $fileName beginrun startrun event endrun physics
   
   if [ catch {
      array set argArray $parsedArgs
      set nevents $argArray(-nevents)
   } ] {
      set nevents -1
   }

#   set start_event 1
#   catch {
#      set start_event $argsArray(-start_event)
#   }
   
   puts [prod lss]
   puts [proc lss]
   puts [source list]

#   mcpass2_run_job $nevents $start_event
   mcpass2_run_job $nevents
}

#--------------------------------------------------
# handle the various parts of the job
#--------------------------------------------------

tcl_proc mcpass2_setup_job {argArrayAsList} {
  array set argArray $argArrayAsList
 
   #build a stack of commands we should issue to setup the job
   #  we do this rather than directly calling the commands so
   #  that any initial calculations we need to do to get all the
   #  data necessary to setup the job will not interfere with 
   #  the actual job setup
   set commandStack []
  
    lappend commandStack "mcpass2_setup"

   if { 0 != [llength [array get argArray "-post"] ] } {
      lappend commandStack [join $argArray(-post)]
   }

   lappend commandStack "mcpass2_out_file $argArray(out)"

   #now issue the commands
   foreach command $commandStack {
      eval $command
   }
}


#run this procedure at the end of the job
tcl_proc mcpass2_run_job {{nevents -1} } {
   if {$nevents >= 0 } {
      go $nevents
   }
   if {$nevents < 0 } {
      go
   }
}


#--------------------------------------------------
# procedures used to handle the various optoins
#--------------------------------------------------
tcl_proc mcpass2_setup {} {
   global getMCConstants_tcl_loaded
   global env
   run_file $env(C3_SCRIPTS)/mcpass2/mcpass2.tcl
}

tcl_proc mcpass2_optional_post {post_command} {
   eval $post_command
}

tcl_proc mcpass2_out_file {filename } {
    global env
    run_file $env(C3_SCRIPTS)/mcpass2/controlMCWriteout_mcpass2.tcl
    load_proper_sink_format $filename
    file out $filename beginrun startrun "event $listMCOutput" endrun physics
}

#--------------------------------------------------
# helper procedures
#--------------------------------------------------

#list of standard arguments used by all 'mcpass2 *' commands
set mcpass2_standard_arg_names { {out 1} {-post 1} }

# ========================================
# Command "mcpass2" added.
#   Do "mcpass2 help" for further details.
# ========================================

