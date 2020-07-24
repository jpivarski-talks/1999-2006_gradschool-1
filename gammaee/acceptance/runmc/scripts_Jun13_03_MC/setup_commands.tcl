#============================================================
#
# Purpose: create a series of commands that load tcl files to
#          setup Suez to do standard types of jobs
#
#============================================================

# create a list containing
#  1) name to append to setup_ which will be used to create command name
#  2) script to run (the script must be in the $C3_SCRIPTS area)
#  3) a help string that explains the purpose of this routine

set commandInfo { 
    { analysis 
      setup_analysis.tcl 
      "load the standard Producers needed for a standard analysis"} 
    { event_display 
      event_display_wizard.tcl
      "load the command used to setup the event display"} 
}

puts "creating setup commands"
# parse our commandInfo list and create the appropriate command
foreach command $commandInfo {
    set _name_ [lindex $command 0]
    puts "  setup_$_name_"
    set _script_ [lindex $command 1]
    set _commandComment_ [lindex $command 2]

# this is the prototype for our command
    set commandPrototype "tcl_proc setup_$_name_ { {value \"\"}} { if { \$value == \"\" } { run_file $env(C3_SCRIPTS)/$_script_ } else { puts \"Command: setup_$_name_ \n $_commandComment_ \n SubCommands:\n  help   show this page\" } }"
#    puts ""
#    puts $commandPrototype
#    puts ""

    eval $commandPrototype
}

