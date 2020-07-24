#!/usr/local/bin/perl

foreach $type ("pipi") {

    # y2s
    @runs = (123610, 123611, 123612, 123615, 123616, 123617, 123618,
	     123619, 123620, 123621, 123623, 123624, 123631, 123632,
	     123633, 123635, 123636, 123637, 123638, 123639, 123640,
	     123641, 123643, 123644, 123645, 123646, 123647, 123648,
	     123650, 123651, 123652, 123653, 123654, 123656, 123658) if $type eq "pipi";

    foreach $run (@runs) {
	open(RUN, "> y2$type\_$run.run");
	print RUN "#\$ -l sigmc=1
#\$ -o /cdat/tem/mccann/y2$type\_$run.log
#\$ -S /bin/bash
#\$ -j y

cd /home/mccann/mcsuper/run/
. /nfs/cleo3/scripts/cleo3defs
c3rel Mar04_04_MC
export C3_SHLIB=../build_SunOS/shlib:\$C3_SHLIB

export USER_RUN=$run
export USER_GEN=../pds/generator_y2$type\_$run.pds
export USER_DEC=y2$type.dec
export USER_EBEAM=5.01163
export USER_RES=10.02326
export USER_WIDE=0.000044

rm -f \$USER_GEN

rm -f core
suez -f generate.tcl
rm -f core

c3rel Apr16_03_MC
export C3_SHLIB=../build_\$CMLIB/shlib:\$C3_SHLIB
export C3_SCRIPTS=/home/mccann/mcsuper/run/scripts_\$CMLIB
export USER_CLEOG=../pds/cleog_y2$type\_$run\_db21.pds
export USER_MCPASS2=../pds/mcpass2_y2$type\_$run\_db21.pds
rm -f \$USER_CLEOG
rm -f \$USER_MCPASS2
suez -f cleog.tcl
rm -f core
suez -f mcpass2.tcl
rm -f core

c3rel Jun13_03_MC
export C3_SHLIB=../build_\$CMLIB/shlib:\$C3_SHLIB
export C3_SCRIPTS=/home/mccann/mcsuper/run/scripts_\$CMLIB
export USER_CLEOG=../pds/cleog_y2$type\_$run\_db23.pds
export USER_MCPASS2=../pds/mcpass2_y2$type\_$run\_db23.pds
rm -f \$USER_CLEOG
rm -f \$USER_MCPASS2
suez -f cleog.tcl
rm -f core
suez -f mcpass2.tcl
rm -f core
";
    }

}
