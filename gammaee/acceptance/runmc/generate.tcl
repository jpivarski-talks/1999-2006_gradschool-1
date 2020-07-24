default prompt off
exception continueEventLoop on;

prod sel CustomBeamEnergyProd

run_file $env(C3_SCRIPTS)/cleog_command.tcl
cleog gen EvtGenProd 10000 out $env(USER_GEN) run $env(USER_RUN) -user_decay $env(USER_DEC) -post {
    prod desel CesrBeamEnergyProd;
    param CustomBeamEnergyProd BeamEnergy $env(USER_EBEAM);
    param CustomBeamEnergyProd NoRunStat true;
    param MCSymmetricBeamProd resonantProduction true;
    param MCSymmetricBeamProd BWResonanceMass $env(USER_RES);
    param MCSymmetricBeamProd BWResonanceWidth $env(USER_WIDE);
    param MCSymmetricBeamProd totalEnergySpreadAt10GeV 0.0042036;
    run_file qqonly.tcl;
    prod lss;
}
