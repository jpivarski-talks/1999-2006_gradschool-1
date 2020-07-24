#============================================================
# File: cleog_command.tcl
#
# Purpose:
#   create a 'cleog' command used to configure and run MC
#
# 
#============================================================

module sel EnableFPEModule

# default location for random trigger files
set cleog_default_merge_file_dir /cdat/lns150/disk2/c3mc/RandomTriggerEvents

set cleog_dataSet_run_list { 
#format:
# dataset <first run> <last run>
#{3 104100 107913}
#{4 107914 109688}
{5 109762 110278}
{6 110904 112258}
{7 112259 113214}
{8 113243 114137}
{9 114138 115063}
{10 115099 116093}
{11 116128 117105}
{12 117159 118166}
{13 118193 119022}
{14 119033 119927}
{16 121339 122178}
{17 122245 123304}
{18 123369 124548}
{19 124625 125416}
{20 125428 126204}
{21 126252 127545}
{22 127588 128401}
{23 128760 129221}
{24 129257 129488}
{25 129535 129865}
{26 129897 130187}
{27 130198 130630}
{28 130676 131640}
{29 131679 132285}
{30 132286 0     }
}

# define procedures used by this script
run_file $env(C3_SCRIPTS)/loader_lss.tcl
run_file $env(C3_SCRIPTS)/exclude_constants_streams.tcl
run_file $env(C3_SCRIPTS)/load_proper_format_command.tcl
run_file $env(C3_SCRIPTS)/parse_args_command.tcl

#--------------------------------------------------
# master procedure that calls all other procedures
#--------------------------------------------------
tcl_proc cleog args {
   # dynamically determine the subcommand to call
   #  this allows for easy addition of new subcommands
   #  (i.e. they just need to be called cleog_<subcommand name>
   set generationType [lindex $args 0]
   if { 0 != [string compare cleog_$generationType [info procs cleog_$generationType] ] } {
      error "cleog: unknown sub command: $generationType"
   }
   eval cleog_$generationType [lrange $args 1 [llength $args] ]
   return
}

#--------------------------------------------------
# standard subcommands
#--------------------------------------------------
tcl_proc cleog_help {} {
   puts "\nDescription: cleog"
   puts "\n      generate monte carlo files"
   puts "\n  Subcommands are:"
   puts "     help   this page\n"
   puts "cleog file <mc particle file> out <out file> \[-nevents <#>\] \[-nomerge\] "
   puts "          \[ -post <commands>\] \[-user_decay <file>\] \[-standard_decay <file>\]"
   puts "    starting from a file containing the decay particles <mc particle file> write" 
   puts "    out the mc file to <out file>."
   puts "    Can optionally choose to only process only some of the events in the file by"
   puts "    using \"-nevents <#>\"."
   puts ""
   puts "cleog gen <generator to use> <nevents> out <out file>  dataset <#> \[-job <#>\]"
   puts "           \[-start_event <#>\] \[-nomerge\] \[-post <commands>\]"
   puts "           \[-user_decay <file>\] \[-standard_decay <file>\]"
   puts "cleog gen <generator to use> <nevents> out <out file>  run <#>"
   puts "           \[-start_event <#>\] \[-nomerge\] \[-post <commands>\]"
   puts "           \[-user_decay <file>\] \[-standard_decay <file>\]"
   puts "   use the generator producer <generator to use> to <nevents> events and write"
   puts "   out the mc file to <out file>.  The option -start_event allows you to"
   puts "   start generation at an event number other than 1"
   puts "   The two forms differ by the way you specify what run number to use: "
   puts "   First form"
   puts "    specify the dataset number (e.g. 8).  The script then picks a run number"
   puts "    appropriate for that dataset.  Use the -job option to advance the run number"
   puts "    to something other than the default for that dataset"
   puts "   Second form"
   puts "    Specify the exact run number to be used."
   puts ""
   puts "  generation commands have the following standard options"
   puts "       -nomerge                do not run merge"
   puts "       -user_decay <file>      specify a user decay .dec file"
   puts "       -standard_decay <file>  override standard decay.dec file"
   puts "       -post <commands>        tcl commands to issue after the mc"
   puts "                               job has been configured but before"
   puts "                               doing \"go\".  This should be used to"
   puts "                               specify a filter Processor: e.g."
   puts "                                -post \{proc sel MyFilterProc\}"
}

#setup MC generation using a file containing the QQ information
tcl_proc cleog_file args {
   global cleog_standard_arg_names
   if { 3 > [llength $args] } {
      error "cleog: too few arguments"
   }
   set fileName [lindex $args 0]
   
   #add additional option to allow users to specify number of events to process
   set arg_names [concat { {-nevents 1} } $cleog_standard_arg_names]
   set parsedArgs [parse_args [lrange $args 1 [llength $args]] $arg_names ]
   
   set run_dataSet [cleog_determine_run_dataSet_from_file $fileName]


   # set bunchfinding flag setting to post processing command so that users
   # post processing commands could alter it.
   set rpExtension .rp
   if { 0 == [string compare $rpExtension [string range $fileName end-[expr [string length $rpExtension] -1] end] ] } {

       puts stdout "++++++++                               +++++++++"
       puts stdout "Forcing zero time offset for TrackletBunchFinder"
       puts stdout "++++++++                               +++++++++"

       array set argsArray $parsedArgs
       if [catch {
	   set argsArray(-post) [linsert $argsArray(-post) 0 "param TrackletBunchFinder ForceTimeOffset true; param TrackletBunchFinder TheForcedTimeOffset 0.0;source_format desel BeamSpotFileSourceFormat;"]
       } ] {
	   set argsArray(-post) "param TrackletBunchFinder ForceTimeOffset true; param TrackletBunchFinder TheForcedTimeOffset 0.0;source_format desel BeamSpotFileSourceFormat;"
       }
       set parsedArgs [array get argsArray]
   }

   cleog_setup_job $parsedArgs "set dummyVar \"$run_dataSet\""

   load_proper_format $fileName
   file in $fileName beginrun startrun event endrun physics
   
   if [ catch {
      array set argArray $parsedArgs
      set nevents $argArray(-nevents)
   } ] {
      set nevents -1
   }
   
   puts [prod lss]
   puts [proc lss]
   puts [source list]

   cleog_run_job $nevents [lindex $run_dataSet 0]
}

#use a generator Producer to generate the MC
tcl_proc cleog_gen args {
   global cleog_standard_arg_names
   if { 5 > [llength $args] } {
      error "cleog: too few arguments"
   }
   set generatorProd [lindex $args 0]
   set nevents [lindex $args 1]
   
   switch [lindex $args 4] {
      dataset {
         set arg_names [concat { {dataset 1} {-job 1} {-start_event 1}} $cleog_standard_arg_names]
      }
      run { 
         set arg_names [concat { {run 1} {-start_event 1}} $cleog_standard_arg_names]
      }
      default { error "cleog: unknown sixth argument [lindex $args 5].  Should be \"dataset\" or \"run\""}
   }
   
   #add additional option to allow users to specify number of events to process
   set parsedArgs [parse_args [lrange $args 2 [llength $args]] $arg_names ]
   
   array set argsArray $parsedArgs
   
   switch [lindex $args 4] {
      dataset {
         set dataSet $argsArray(dataset)
         if { 0 != [llength [array get argsArray "-job"] ] } {
            set job $argsArray(-job)
         } else {
            set job 0
         }
         set runNumber [cleog_determine_run_from_dataSet $dataSet $job]
      }
      run {
         set runNumber $argsArray(run)
         set dataSet [cleog_determine_dataSet_from_run $runNumber]
      }
   }
   
   #add generatorProd to post processing command so that users
   # post processing commands could alter the behavior of this producer
   if [catch {
      set argsArray(-post) [linsert $argsArray(-post) 0 "prod sel $generatorProd;"]
   } ] {
      set argsArray(-post) "prod sel $generatorProd"
   }
   set parsedArgs [array get argsArray]
   cleog_setup_job $parsedArgs "list $runNumber $dataSet"


   #now check to see if the user has loaded any Processors
   # if they have, then we need to specify the number of events to process
   #  if not, then we can just let the source handle it
   module sel MCSourceModule
   set start_event 1
   catch {
      set start_event $argsArray(-start_event)
   }
   
   #ignore any procs we know that are not filters
   set nonFilterProcs {RunEventNumberProc MCRunEvtNumberProc}
   set procList [loader_lss proc]
   foreach noFilterProc $nonFilterProcs {
      if {-1 != [set index [lsearch -exact $procList $noFilterProc] ] } {
           set procList [lreplace $procList $index $index] 
      }
   }
   if { 0 < [llength $procList] } {
      set genEvents [expr int(pow(2,30))]
      set runEvents $nevents
   } else {
      set genEvents $nevents
      set runEvents -1
   }
   mcsource in MC $runNumber $genEvents $start_event

   puts [emptysource def givePhysics physics]
   puts [source act givePhysics physics]
   
   puts [prod lss]
   puts [proc lss]
   puts [source list]
   cleog_run_job $runEvents $runNumber
}

#--------------------------------------------------
# handle the various parts of the job
#--------------------------------------------------

tcl_proc cleog_setup_job {argArrayAsList getRun_RunSetCommand} {
  array set argArray $argArrayAsList
 
   #build a stack of commands we should issue to setup the job
   #  we do this rather than directly calling the commands so
   #  that any initial calculations we need to do to get all the
   #  data necessary to setup the job will not interfere with 
   #  the actual job setup
   set commandStack []
  
   #lappend commandStack "cleog_setup"
   
   if { 0 == [llength [array get argArray "-nomerge"] ] } {
      lappend commandStack "cleog_setup_merge [eval $getRun_RunSetCommand]"
   } else {
      lappend commandStack "cleog_setup"
   }

   if { 0 != [llength [array get argArray "-user_decay"] ] } {
      lappend commandStack "cleog_optional_user_decay $argArray(-user_decay)"
   }

   if { 0 != [llength [array get argArray "-standard_decay"] ] } {
      lappend commandStack "cleog_optional_standard_decay $argArray(-standard_decay)"
   }

   lappend commandStack "cleog_out_file $argArray(out)"

   if { 0 != [llength [array get argArray "-post"] ] } {
      lappend commandStack [join $argArray(-post)]
   }


   #now issue the commands
   foreach command $commandStack {
      eval $command
   }
}


#run this procedure at the end of the job
tcl_proc cleog_run_job {{nevents -1} {runNumber -1}} {
   if {$nevents >= 0 } {
      proc sel StopAfterNEventsProc
      param StopAfterNEventsProc numberOfEvents $nevents
   }
   go
   if {$nevents >= 0 } {
      #make sure their are no sources delivering beginruns, startruns or events
      source clear
     
      #use this number to create endrun
      emptysource one EndRun $runNumber [expr int( pow(2,31)-1)] endrun

      #need a dummy source of other streams
      emptysource one Dummy [incr runNumber] 0 beginrun startrun event physics

      go 1 endrun
      source clear
   }
}


#--------------------------------------------------
# procedures used to handle the various optoins
#--------------------------------------------------
tcl_proc cleog_setup {} {
   global env
   global getMCConstants_tcl_loaded

   run_file $env(C3_SCRIPTS)/cleog.tcl
}

tcl_proc cleog_setup_merge {runNumber dataSet} {
    global env cleog_default_merge_file_dir
    run_file $env(C3_SCRIPTS)/cleog_merge.tcl
   
   #build file chain used for merging
   if [ catch {
      set mergFileDir $env(C3_MERGE_DIR)
      }
   ] {
      set mergFileDir $cleog_default_merge_file_dir
   }

   #create two lists: one with all files for runs less than we want
   # the other for run equal to or greater than that one.
   #Merge the two list so that the files are in order of 'closeness' to 
   # the run we want
   set fileList [glob $mergFileDir/data$dataSet/RandomTriggerEvents_*.pds]
   set lesserList []
   set greaterList []
   set ignoreBefore [string length "$mergFileDir/data$dataSet/RandomTriggerEvents_"]
   
   foreach file $fileList {
      if {[ string range $file $ignoreBefore end-4] < $runNumber} {
         lappend lesserList $file
      } else {
         lappend greaterList $file
      }  
   }

   #NOTE: this assumes that all files have the same length runNumbers
   set greaterList [lsort $greaterList]
   set reverseLesserList [lsort -decreasing $lesserList]
   
   if { [llength $lesserList] < [llength $greaterList] } {
      set shorterList $reverseLesserList
      set longerList $greaterList
   } else {
      set shorterList $greaterList
      set longerList $reverseLesserList
   }
   
   set totalList []
   for { set index 0 } { $index < [llength $shorterList]} {incr index} {
      lappend totalList [lindex $greaterList $index]
      lappend totalList [lindex $reverseLesserList $index]
   }
   
   for { set index [llength $shorterList]} {$index < [llength $longerList]} {incr index} {
      lappend totalList [lindex $longerList $index]
   }

   prod inter SubFrameProd

   if [info exists getMCConstants_tcl_loaded] {
       unset getMCConstants_tcl_loaded
   }
   run_file $env(C3_SCRIPTS)/getMCPass2_3Constants.tcl

   source_format sel PDSSourceFormat
   source create randomTriggerChain
   foreach file $totalList {
       file add randomTriggerChain $file beginrun startrun event
   }
   catch [ 
   quit 
   ]
}

tcl_proc cleog_optional_standard_decay {decay} {
#   param MCInfoDelivery standardDecayDec $decay
}
tcl_proc cleog_optional_user_decay {decay} {
#   param MCInfoDelivery userDecayDec $decay
}

tcl_proc cleog_optional_post {post_command} {
   eval $post_command
}

tcl_proc cleog_out_file {filename } {
    global env
    run_file $env(C3_SCRIPTS)/controlMCWriteout_cleog.tcl
    load_proper_sink_format $filename
    file out $filename beginrun startrun "event $listMCOutput" endrun physics
}

#--------------------------------------------------
# helper procedures
#--------------------------------------------------

#list of standard arguments used by all 'cleog *' commands
set cleog_standard_arg_names { {out 1} {-nomerge 0} {-post 1} {-user_decay 1} {-standard_decay 1}}

tcl_proc cleog_determine_dataSet_from_run {run} {
   global cleog_dataSet_run_list
   if { $run < [lindex [lindex $cleog_dataSet_run_list 0] 1] } {
      error "cleog: run $run is before CLEO III physics data taking began"
   }
   
   foreach dataSet_run $cleog_dataSet_run_list {
      if { $run >= [lindex $dataSet_run 1] } {
         if {  (0 == [lindex $dataSet_run 2]) || ($run <= [lindex $dataSet_run 2]) } {
               return [lindex $dataSet_run 0]
         }
      }
      if { $run < [lindex $dataSet_run 1] } {
         error "cleog: run $run falls between dataset [expr [lindex $dataSet_run 0] - 1] and [lindex $dataSet_run 0]"
      }
   }
   return 1
}

tcl_proc cleog_determine_run_from_dataSet {dataSet job} {
   global env cleog_default_merge_file_dir
   
   #build file chain used for merging
   if [ catch {
      set mergeFileDir $env(C3_MERGE_DIR)
      }
   ] {
      set mergeFileDir $cleog_default_merge_file_dir
   }

   #create a list of the random trigger runs and use these
   # for the runs for the dataset
   set fileList [glob $mergeFileDir/data$dataSet/RandomTriggerEvents_*.pds]
   set runList []
   set ignoreBefore [string length "$mergeFileDir/data$dataSet/RandomTriggerEvents_"]
   
   foreach file $fileList {
      lappend runList [ string range $file $ignoreBefore end-4]
   }
   
   set runList [lsort -dictionary $runList]

   #start our lists from the center of the list and work our way outward
   if {1 == [expr [llength $runList] % 2] } {
      lreplace runList end end
   }
   
   set beginList []
   set endList []
   set halfwayIndex [expr [llength $runList]/2]
   for { set index 0} {$index < $halfwayIndex} {incr index} {
      lappend beginList [lindex $runList $index]
      lappend endList [lindex $runList [expr $halfwayIndex + $index] ]
   }
   set beginList [lsort -dictionary -decreasing $beginList]
   
   set runList []
   for { set index 0} {$index < $halfwayIndex} {incr index} {
      lappend runList [lindex $beginList $index]
      lappend runList [lindex $endList $index]
   }
   return [lindex $runList [expr $job%$halfwayIndex]]
}

tcl_proc cleog_determine_run_dataSet_from_file {fileName} {
   global runNumber
   load_proper_format $fileName
   
   set fileToken [file in $fileName beginrun]
   proc sel DataInteractProc
   param DataInteractProc auto_execute \{set runNumber \[record syncvalue beginrun\]\}
   param DataInteractProc stop_stream beginrun
   source activate $fileToken beginrun
   go 1 beginrun
   proc desel DataInteractProc
   source remove $fileToken
   #temp
   #set runNumber "run/event/time=114000/0/10101"
   set runNumber [ lindex [ split [lindex [split $runNumber "="] 1 ] "/"] 0]
   return "$runNumber [cleog_determine_dataSet_from_run $runNumber]"
}

# ========================================
# Command "cleog" added.
#   Do "cleog help" for further details.
# ========================================

