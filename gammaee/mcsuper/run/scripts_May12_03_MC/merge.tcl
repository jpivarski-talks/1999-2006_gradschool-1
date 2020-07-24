# suez script for merging
# use as follows:
#    run_file $env(C3_SCRIPTS)/merge.tcl
## Prepare the SubFrame to be able to created hit objects & recycle events
#    param      SubFrameProd repeatWhenReachEnd true
#
#    prod inter SubFrameProd
#       file in myRandomTriggerFile.pds beginrun event
#
#       if [info exists getPass2Constants_tcl_loaded] 
#       {
#          unset getPass2Constants_tcl_loaded
#       }
#      run_file $env(C3_SCRIPTS)/getPass2_3Constants.tcl
#    exit
#
# push aside std proxies with special production tag
#   param CalibratedDRHitProd  production_tag PreMerge
#   param DRCACorrectHitProd   production_tag PreMerge
#   param CorrectedSVStripProd production_tag PreMerge
#   param C3ccReconProd        production_tag PreMerge
#   param RichCalibratedHits   production_tag PreMerge
#
# (either cleog_merge.tcl or pass2 tcl script here)
#
#   prod sel DBRunHeaderProd
#   proc sel RunEventNumberProc
#
# *** IMPORTANT NOTE ***
# If the above "prod inter SubFrameProd" is inside a catch block
# as used in cleog_merge.tcl or otherwise, it must instead appear as
#
# catch {
#   prod inter SubFrameProd
# if [ catch { set mergeFileProblem 0
#      file in /nfs/cleo3/cleomc/random_113966_25ev.pds beginrun event
# } ] { set mergeFileProblem 1 }
#   exit
# }
# if { $mergeFileProblem } { error "Had a mergeFileProblem!!!!" }

#--------------------------------------------------------------------------

catch {

   prod sel   SubFrameProd
   prod inter SubFrameProd

if [ catch { set mergeProblem 0

      default prompt off

      prod sel RawDataProd

#   DR producers
      prod sel PreliminaryDRHitProd
      prod sel CalibratedDRHitProd
      prod sel TrackletBunchFinder
      prod sel TriggerPhaseForDataProd
      prod sel TriggerL1DataProd
      prod sel TriggerDataProd
      prod sel CDOffCal
      prod sel ADRGeomProd
      prod sel DRGeom


#   Cathodes producers
      prod sel DRCACorrectHitProd

#   Si producers
      prod sel CorrectedSVStripProd
      prod sel ASiStorePro
      prod sel SiGeom
      prod sel SiHitsProd

#   Rich producers
      prod sel RichCalibratedHits

#   CC producers
      prod sel C3ccReconProd
      prod sel C3ccConProd
      prod sel C3ccProd

      prod sel DBRunHeaderProd
      prod sel DBEventHeaderProd
      proc sel RunEventNumberProc

} caughtProblem] { set mergeProblem 1 }

   exit
}

if { $mergeProblem } { error "Had a mergeProblem!!!!: $caughtProblem" }





