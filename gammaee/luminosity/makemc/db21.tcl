run_file $env(C3_SCRIPTS)/cleog_command.tcl
cleog gen QQbarGeneratorProd 1000 out mademc/db21.pds dataset 21 -user_decay U2S.DEC -standard_decay DECAY.DEC
prod lss
summary
exit
