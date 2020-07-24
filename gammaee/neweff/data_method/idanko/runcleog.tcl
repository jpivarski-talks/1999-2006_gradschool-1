if [ catch {
   #load in the cleog command
   run_file $env(C3_SCRIPTS)/cleog_command.tcl

   #if our output file exist we want to delete it
   set fileout $env(CLEOGOUT)
   if { [ tcl_file exists $fileout ]==1 } {
       echo "deleting file '$fileout'"
       tcl_file delete $fileout
   }  

#   cleog gen BBbarGeneratorProd 10 out $fileout dataset 8 -nomerge
#  the QQ file is for a run w/o a magnetic field -- use default value
   cleog file $env(QQOUT) out $fileout -user_decay $env(MYCTR) -post {
       prod sel CustomBeamEnergyProd;
       param CustomBeamEnergyProd BeamEnergy 4.73015;
       param CustomBeamEnergyProd NoRunStat true;
       proc sel ../../build_SunOS/shlib/LookAtRawTrigger
   }
# -nevents 10
# -nomerge

   summary
} catchMessage ] {
   puts $catchMessage
}
exit 
