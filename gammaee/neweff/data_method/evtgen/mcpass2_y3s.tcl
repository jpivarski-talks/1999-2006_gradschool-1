module sel RandomModule
random create

module select LoadGeantModule
module select LoadHbookModule
module sel HbookHistogramModule
hbook file /home/mccann/neweff/data_method_rzn/evtgen/$env(USER_DIR)/mcpass2_$env(USER_RUN).rzn
hbook init

prod sel CustomBeamEnergyProd

run_file $env(C3_SCRIPTS)/mcpass2_command.tcl
mcpass2 file /home/mccann/neweff/data_method_rzn/evtgen/$env(USER_DIR)/cleog_$env(USER_RUN).pds out /home/mccann/neweff/data_method_rzn/evtgen/$env(USER_DIR)/mcpass2_$env(USER_RUN).pds -post {
    param DetectorConfigurationProd Override true;
    param DetectorConfigurationProd UseZDnotSI false;
    prod desel CesrBeamEnergyProd;
    param CustomBeamEnergyProd BeamEnergy 5.1776;
    param CustomBeamEnergyProd NoRunStat true;
    prod lss
}
