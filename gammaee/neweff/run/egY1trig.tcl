prod sel CustomBeamEnergyProd

run_file $env(C3_SCRIPTS)/cleog_command.tcl
module sel RootHistogramModule
root file ../rzn/egY1trig_2.root
root init
cleog gen EvtGenProd 2000 out ../rzn/y1seg_temp.pds run 123610 -user_decay ../data_method/evtgen/ups1s.dec -standard_decay ../data_method/evtgen/DECAY.DEC -post {
    prod desel CesrBeamEnergyProd;
    param CustomBeamEnergyProd BeamEnergy 4.73015;
    param CustomBeamEnergyProd NoRunStat true;
    param MCSymmetricBeamProd resonantProduction true;
    param MCSymmetricBeamProd BWResonanceMass 9.46030;
    param MCSymmetricBeamProd BWResonanceWidth 0.0000525;
    param MCSymmetricBeamProd totalEnergySpreadAt10GeV 0.0042036;
    prod sel DRCAClusterProd;
    prod sel DoitProd;
    param DoitProd ContinueIfHitsMissing true;
    prod sel DRHitCorrectorProd;
    param DRHitCorrectorProd ApplyEntranceAngleCorr false;
    param DRHitCorrectorProd ApplyStandardCorrections false;
    prod sel KalmanProd;
    param KalmanProd HyposToFit pion;
    param KalmanProd OptimizeForAllHypos true;
    param KalmanProd HitListFromOneHypo true;
    param KalmanProd ScaleCathodeResolution true;
    param KalmanProd CathodeResolutionScale 0.7;
    prod sel NavigationProd;
    prod sel TrackDeliveryProd;
    prod sel SeedToTRTrackProd;
    run_file $env(C3_SCRIPTS)/CcP2.tcl;
    prod sel TrackShowerMatchingProd;
    prod sel EventPropertiesProd;
    prod sel EventTypeProd;
    proc sel Level4Proc;
    param Level4Proc TagOnly true;
    proc sel ../build_SunOS/shlib/Cuts;
    param Cuts usingEvtGen true;
    param Cuts studyTrigger true;
    prod lss
}
