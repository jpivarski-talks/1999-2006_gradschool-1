#
#++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#
#  !!!READ THIS NOTE NOW:  THIS IS >>>NOT<<< A PASS2 MU RECO SCRIPT, also: 
#
#++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#
#  This is the standard TCL script for muon 
#  ``reconstruction''/identification USING THE RESULTS OF PASS2
#
#  There are two reasons why you may want to use THIS script:
#
#  1) As of 02/20/01 none of PASS2 run had proper muon reconsruction
#     for (relatively) low momenta tracks because of the bug in
#     Geant3MaterialsMediaProd package (fixed by now).
#
#  2) You might be Vladimir (:)) and you could want to rerun muon reco for 
#     some studies you are doing (and important auxiliary information 
#     that IS produced by MutrReconProd was NOT (and it should NOT)  
#     saved in PASS2 output).
#
#+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#
#  P2MuonMonProc has a working example of using NavTracks to access mu reco
#  info from pass2 - please consult P2MuonMonProc/Class/P2MuonMonProc.cc
#
#++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#
#  Load this script with command
#
#  Suez> run_file $env(C3_SCRIPTS)/muonIdentificationData_fix.tcl
#
#  This script will *not* work on Monte Carlo (MC). 
#
#  For MC use script muonIdentificationMC.tcl
#
#  Questions are welcome at savinov@mail.lns.cornell.edu
#
#                                            Vladimir Savinov
#
#+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#
#  Notes:
#
#    Muon identification will only work if exitPion fits 
#    are present / could be obtained from the event. 
#
#    SUEZ must be run as suez -q
#
#    Some information on muon ``reconstruction''/identification:
#
#    1) Exit pion fits are used. 
#
#    2) Each exit pion fit is extrapolated to where a muon would have 
#       intersected the strips and counters of the muon system. 
#       The extrapolation is being done using GEANT with full 
#       detector simulation thus taking energy losses and 
#       multiple scattering into account. 
#
#    3) When muon system hits are found where expected, 
#       these correlations are used to classify muon candidates. 
#
#    4) Use only muqual=0 muon candidates, their penetration depth 
#       is characterized by parameter depth. 
#
#    5) When using direct information from muon reconstruction producer 
#       MutrReconProd, muqual and depth are accessed using:   
#
#       #include "C3Mu/MuTrack.h"
#       ...
#       FATable<MuTrack> MuTrackList;
#       extract( iFrame.record(Stream::kEvent),
#            MuTrackList );
#       ...
#       FATable<MuTrack>::const_iterator itEnd = MuTrackList.end();
#       for( FATable<MuTrack>::const_iterator itMuTrack = MuTrackList.begin();
#            itMuTrack != itEnd;
#            ++itMuTrack ) {
#       ...
#       float DPTHMU  = itMuTrack->dpthmu ();
#       int   MUQUAL  = itMuTrack->muqual ();
#       int   DRTRACK = itMuTrack->mutrdr ();
#       ...
#       where DRTRACK is DR track number
#
#    6) When using navigation tracks, you can do: 
#
#       float DPTHMU = (*next_navigation_track_pointer).depth()
#
#       DPTHMU is non-zero for MUQUAL=0 muon candidates. 
#       Zero DPTHMU means either not muon or MUQUAL =/ 0 muon candidate. 
#
#+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#
#  P2MuonMonProc has a working example of using NavTracks to 
#  access mu reco info - please consult P2MuonMonProc/Class/P2MuonMonProc.cc
#
#+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#
if [ catch {
#
#---------------------------------------------------------------------------
#
#  load GEANT, HBOOK etc
#
##module select LoadGeantModule
##module select LoadHbookModule
##module select HbookHistogramModule
##hbook init
#
#---------------------------------------------------------------------------
#
#  input data (ASCII format)
#
##source_format sel AsciiSourceFormat
##sink_format sel AsciiSinkFormat
#
#---------------------------------------------------------------------------
#
#  constants access
#
run_file $env(C3_SCRIPTS)/getConstants.tcl
#
#---------------------------------------------------------------------------
#
#  load tracking - NO! Use PASS2 output!!!
#
##run_file $env(C3_SCRIPTS)/trackingDataFull.tcl
#
#---------------------------------------------------------------------------
#
#  load muon reconstruction and constants producer 
#
prod sel MutrReconProd
prod sel MuConsProd
#
#---------------------------------------------------------------------------
#
#  load geometry producers
#
run_file $env(C3_SCRIPTS)/load_geometry_producers.tcl
#
#---------------------------------------------------------------------------
#
#  load DG to GEANT3
#
run_file $env(C3_SCRIPTS)/load_dg_to_geant3_converter.tcl
#
#---------------------------------------------------------------------------
#
#  load magnetic field information (this is needed not only for tracking)
#
prod sel MagFieldProd
#
#  load raw data
#
prod sel RawDataProd
#
#  run info
#
prod sel DBRunHeaderProd
#
#---------------------------------------------------------------------------
#
} resultString ] {
  
    puts stderr "Exception: \"$resultString\"" 
    puts stderr "while loading muon identification."
    puts stderr "Unable to continue. Please investigate. Stop here."

    report level EMERGENCY
    exit

} else { 

    puts stdout " "
    puts stdout "Loading ok: muon identification."
    puts stdout " "

}
#+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++



