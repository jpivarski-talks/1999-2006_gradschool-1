#| detailed output -> uncomment here:
#| report level DEBUG
   default prompt off

   module sel TimerModule

   timer reset
   timer display

#| needed for .pds format:
   source_format sel PDSSourceFormat 
   sink_format sel PDSSinkFormat 

   run_file $env(C3_SCRIPTS)/mcpass2/mcpass2.tcl

   file in my_cleog_file.pds beginrun startrun event endrun
#   param MCInfoDelivery userDecayDec my_decay.dec 
   file out my_mcpass2_file.pds "event $listMCOutput" beginrun startrun endrun
#|   hbook file my_histo_file.rzn

   prod lss
   proc lss

   go 1
   source status
   timer display
   go 
   timer display
   exit
 


