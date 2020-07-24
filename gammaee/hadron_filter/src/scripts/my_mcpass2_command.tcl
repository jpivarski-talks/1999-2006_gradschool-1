default prompt off

run_file $env(C3_SCRIPTS)/loader_lss.tcl
run_file $env(C3_SCRIPTS)/exclude_constants_streams.tcl
run_file $env(C3_SCRIPTS)/parse_args_command.tcl
run_file $env(C3_SCRIPTS)/load_proper_format_command.tcl
run_file $env(C3_SCRIPTS)/mcpass2/mcpass2.tcl
run_file $env(C3_SCRIPTS)/mcpass2/controlMCWriteout_mcpass2.tcl


    run121916/cleog.pds
    run121917/cleog.pds
no solenoid hall probe
    run121919/cleog.pds
    run121920/cleog.pds
    run121921/cleog.pds
no solenoid hall probe
    run121923/cleog.pds
dummy routine reached
floating point exceptions
    run121926/cleog.pds
    run121927/cleog.pds
    run121928/cleog.pds
dummy routine reached
no svcalibonline record found in frame
    run121931/cleog.pds
    run121932/cleog.pds
    run121933/cleog.pds
    run121934/cleog.pds
    run121935/cleog.pds
no solenoid hall probe
no CesrQuadrupoleCurrents found in startrun
    run121938/cleog.pds
    run121939/cleog.pds
no solenoid hall probe
no space left!


















    run121960/cleog.pds





    run121966/cleog.pds
    run121967/cleog.pds
    run121968/cleog.pds
    run121969/cleog.pds
    run121970/cleog.pds
    run121971/cleog.pds
    run121972/cleog.pds
    run121973/cleog.pds
    run121974/cleog.pds







load_proper_format $fileName
file in $fileName beginrun startrun event endrun physics

load_proper_sink_format $filename
file out $filename beginrun startrun "event $listMCOutput" endrun physics
