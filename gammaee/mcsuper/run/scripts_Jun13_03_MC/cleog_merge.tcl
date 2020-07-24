# FILE: cleog_merge.tcl
#
# Purpose: Set up Cleog running under Suez with random trigger merging
########################################################################

if [ catch {

# invoke std cleog script
   run_file $env(C3_SCRIPTS)/cleog.tcl

# turn off fake merge
   param MCRawDataProd useRichFakeMerge        false
   param MCRawDataProd useRichNoiseScaleFactor 0.0
   param MCRawDataProd useSVFakeMerge          false
   param MCRawDataProd useCCFakeMerge          false
   param MCRawDataProd useCathodesFakeMerge    false

   run_file $env(C3_SCRIPTS)/merge.tcl

# Prepare the SubFrame to be able to created hit objects & recycle events
   param      SubFrameProd repeatWhenReachEnd true

# DR producers
   prod sel PreliminaryDRHitProd
   prod sel CalibratedDRHitProd
   prod sel TrackletBunchFinder

# Cathodes producers
   prod sel DRCACorrectHitProd

# Si producers
   prod sel CorrectedSVStripProd

# CC producers
   prod sel C3ccReconProd

# Rich producers
   prod sel RichCalibratedHits

# push aside std proxies with special production tag
   param CalibratedDRHitProd  production_tag PreMerge
   param DRCACorrectHitProd   production_tag PreMerge
   param CorrectedSVStripProd production_tag PreMerge
   param C3ccReconProd        production_tag PreMerge
   param RichCalibratedHits   production_tag PreMerge

# merge producers
   prod sel CcMergeProd
   prod sel SiMergeProd
   prod sel CathodesMergeProd
   prod sel DRMergeProd
   prod sel RichMergeProd


} resultString ] { # ------------------- tcl try-catch block
    puts stderr "cleog_merge source/modules **not** ok"
    puts stderr "resultString:"
    puts stderr "$resultString"
    exit
} else {
    puts stdout "Loading cleog_merge ok"
    puts stdout "resultString:"
    puts stdout "$resultString"
}



