#============================================================
# File: analysis_output_command.tcl
#
# Purpose:
#   execute commands necessary to fill output file with std analysis output
#
# 
#============================================================

# define procedures used by this script
run_file $env(C3_SCRIPTS)/loader_lss.tcl
run_file $env(C3_SCRIPTS)/load_proper_format_command.tcl
run_file $env(C3_SCRIPTS)/parse_args_command.tcl

set analysis_output_prod_list { 
NavigationProd
TrackDeliveryProd
C3ccProd
TrackletBunchFinder
MutrReconProd
DoitProd
VFinderProd
Level3Proc
Level4Proc
DedxReconProd
EventTypeProd
EventPropertiesProd
}


set analysis_output_mc_prod_list { 
MCSymmetricBeamProd
MCCCTaggerProd
MCTrackTaggerProd
MCTriggerPhaseProd
}


#--------------------------------------------------
# master procedure that calls all other procedures
#--------------------------------------------------
tcl_proc analysis_output args {
   # dynamically determine the subcommand to call
   #  this allows for easy addition of new subcommands
   #  (i.e. they just need to be called analysis_output_file_<subcommand name>
   set generationType [lindex $args 0]
   if { 0 != [string compare analysis_output_$generationType [info procs analysis_output_$generationType] ] } {
      error "analysis_output: unknown sub command: $generationType"
   }
   eval analysis_output_$generationType [lrange $args 1 [llength $args] ]
   return
}

#--------------------------------------------------
# standard subcommands
#--------------------------------------------------
tcl_proc analysis_output_help {} {
   puts "\nDescription: analysis_output_file"
   puts "\n      issue commands to write a std analysis output file"
   puts "\n  Subcommands are:"
   puts "     help   this page\n"
   puts "analysis_output fileout <file> <'data' or 'mc'>"
}

tcl_proc analysis_output_fileout args {

    global analysis_output_prod_list
    global analysis_output_mc_prod_list

   if { 2 > [llength $args] } {
      error "analysis output: too few arguments"
   }
   set fileName [lindex $args 0]

   set dataOrMC [lindex $args 1]

   if { $dataOrMC != "data" } {
       if { $dataOrMC != "mc" } {
	   error "analysis_output: 2nd arg not 'data' or 'mc'"
       }
   }

   load_proper_sink_format $fileName

   foreach produ $analysis_output_prod_list {
       analysis_output_load_helpers $produ
   }

   set listOutput [list]

   # pass2 output
   set listOutput [concat $listOutput {\
	   DBTrackerValues \
	   FATable<TRTrack> \
	   FATable<TRHelixExitPionFit> \
	   FATable<TRHelixKaonFit> \
	   FATable<TRHelixPionFit> \
	   FATable<TRHelixProtonFit> \
	   FATable<TRExitPionQuality> \
	   FATable<TRKaonQuality> \
	   FATable<TRPionQuality> \
	   FATable<TRProtonQuality> \
	   FATable<TRSeedTrackQuality> \
	   FATable<TRSeedTrack> \
	   FATable<DoitSeedQuality> \
	   FATable<VXFitVeeKShort> \
	   FATable<VXFitVeeLambda> \
	   FATable<VXFitVeeConversion> \
	   FATable<MuTrack> \
	   FATable<RichTrackAveAngles> \
	   FATable<RichTrackPrototype> \
	   RichTracksMethod \
	   FATable<CcBasicShowerAttsArg> \
	   TrackShowerLattice \
	   FATable<CcConRegAttributes>\
	   CcConRegShowerLattice \
	   TriggerL1Data \
	   Level3TagWord \
	   Level4Decision \
	   EventProperties \
	   BunchDecision \
	   DBEventHeader \
	   EventType \
       } ]


   if { $dataOrMC == "data" } {

       # data specials
       set listOutput [concat $listOutput {\
	       FATable<DedxRecon> \
	   } ]

       set listOutput [ list $listOutput]

       file out $fileName beginrun endrun "event $listOutput"
   }

   if { $dataOrMC == "mc" } {

       foreach produ $analysis_output_mc_prod_list {
	   analysis_output_load_helpers $produ
       }

       # MC specials:
       set listOutput [concat $listOutput {\
	       MCTrackTaggerLatticeTRSeedTrackCleo3 \
	       MCCCTaggerLattice \
	       MCDecayTree \
	       {MCDecayTree Generator} \
	       {FATable<DedxInfo> MC} \
	       MCTriggerPhase \
	       MCTrueRfBucket \
	       MCBeamParticles \
	       MCEventVertex   \
	   } ]

       set listOutput [ list $listOutput]

       file out $fileName beginrun startrun "event $listOutput" endrun physics
   }
}

#check if a producer or processor is loaded and if not select and deselect
tcl_proc analysis_output_load_helpers args {
   if { 1 > [llength $args] } {
      error "analysis_output_load_helpers: too few arguments"
   }
   set thisOne [lindex $args 0]

   if [ catch {
       prod desel $thisOne
       prod sel   $thisOne
   } ] {
       prod sel   $thisOne
       prod desel $thisOne
   }
}
# ========================================
# Command "analysis_output" added.
#   Do "analysis_output help" for further details.
# ========================================

