if [ catch {
   default prompt off
   #load in the mcPass2 command
   run_file $env(C3_SCRIPTS)/mcpass2_command.tcl

   #if our output file exist we want to delete it
   set fileout $env(MCP2OUT)
   if { [ tcl_file exists $fileout ]==1 } {
       echo "deleting file '$fileout'"
       tcl_file delete $fileout
   }  

   mcpass2 file $env(CLEOGOUT) out $fileout

   summary
} catchMessage ] {
   puts $catchMessage
}
exit 
