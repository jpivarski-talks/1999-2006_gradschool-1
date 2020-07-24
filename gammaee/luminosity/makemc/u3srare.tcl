run_file $env(C3_SCRIPTS)/cleog_command.tcl
cleog gen QQbarGeneratorProd 1000 out mademc/u3srare.pds dataset 16 -user_decay U3SRARE.DEC -standard_decay DECAY.DEC
prod lss
summary
exit
