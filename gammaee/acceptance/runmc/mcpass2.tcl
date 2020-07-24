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
prod desel TriggerInfoProd

run_file scripts_$env(CMLIB)/mcpass2_command.tcl
mcpass2 file $env(USER_CLEOG) out $env(USER_MCPASS2) -post {
    global env;
    param CustomBeamEnergyProd BeamEnergy $env(USER_EBEAM);
    param CustomBeamEnergyProd NoRunStat true;
    prod lss
}
