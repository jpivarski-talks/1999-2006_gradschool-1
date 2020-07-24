prod sel CustomBeamEnergyProd

run_file $env(C3_SCRIPTS)/cleog_command.tcl
cleog gen EvtGenProd 5000 out /home/mccann/neweff/data_method_rzn/evtgen/$env(USER_DIR)/cleog_$env(USER_RUN).pds run $env(USER_RUN) -user_decay /home/mccann/neweff/data_method/evtgen/$env(USER_DEC) -standard_decay /home/mccann/neweff/data_method/evtgen/DECAY.DEC -post {
    prod desel CesrBeamEnergyProd;
    param CustomBeamEnergyProd BeamEnergy $env(USER_EBEAM);
    param CustomBeamEnergyProd NoRunStat true;
    param MCSymmetricBeamProd resonantProduction true;
    param MCSymmetricBeamProd BWResonanceMass $env(USER_RES);
    param MCSymmetricBeamProd BWResonanceWidth $env(USER_WIDE);
    param MCSymmetricBeamProd totalEnergySpreadAt10GeV 0.0042036;
    prod lss
}
