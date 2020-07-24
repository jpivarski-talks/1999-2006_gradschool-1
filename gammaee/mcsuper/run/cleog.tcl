default prompt off
exception continueEventLoop on

prod sel DBEventHeaderProd
prod sel MCInfoDelivery
prod sel MCTriggerPhaseProd
prod sel MCSymmetricBeamProd
prod desel MCInfoDelivery
prod desel MCTriggerPhaseProd
prod desel MCSymmetricBeamProd

prod sel CustomBeamEnergyProd
prod sel TriggerInfoProd

run_file scripts_$env(CMLIB)/cleog_command.tcl
cleog file $env(USER_GEN) out $env(USER_CLEOG) -post {
    global env;
    param CustomBeamEnergyProd BeamEnergy $env(USER_EBEAM);
    param CustomBeamEnergyProd NoRunStat true;
    prod lss
}
