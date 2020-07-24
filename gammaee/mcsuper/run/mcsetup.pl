#!/usr/local/bin/perl

foreach $type ("ggg", "gggam", "qq") {
    
    # y1s
    @runs = (123610, 123611, 123612, 123615, 123616, 123617, 123618,
	     123619, 123620, 123621, 123623, 123624, 123631, 123632,
	     123633, 123635, 123636, 123637, 123638, 123639, 123640) if $type eq "ggg";
    @runs = (123641, 123643, 123644, 123645, 123646, 123647, 123648) if $type eq "gggam";
    @runs = (123650, 123651, 123652, 123653, 123654, 123656, 123658) if $type eq "qq";

    foreach $run (@runs) {
	open(RUN, "> y1$type\_$run.run");
	print RUN "#\$ -l sigmc=1
#\$ -o /cdat/tem/mccann/y1$type\_$run.log
#\$ -S /bin/bash
#\$ -j y

cd /home/mccann/mcsuper/run/
. /nfs/cleo3/scripts/cleo3defs
c3rel Mar04_04_MC
export C3_SHLIB=../build_SunOS/shlib:\$C3_SHLIB

export USER_RUN=$run
export USER_GEN=../pds/generator_y1$type\_$run.pds
export USER_DEC=y1$type.dec
export USER_EBEAM=4.73015
export USER_RES=9.46030
export USER_WIDE=0.0000525

rm -f \$USER_GEN

rm -f core
suez -f generate.tcl
rm -f core

c3rel Jun13_03_MC
export C3_SHLIB=../build_\$CMLIB/shlib:\$C3_SHLIB
export C3_SCRIPTS=/home/mccann/mcsuper/run/scripts_\$CMLIB
export USER_CLEOG=../pds/cleog_y1$type\_$run\_db18.pds
export USER_MCPASS2=../pds/mcpass2_y1$type\_$run\_db18.pds
rm -f \$USER_CLEOG
rm -f \$USER_MCPASS2
suez -f cleog.tcl
rm -f core
suez -f mcpass2.tcl
rm -f core

c3rel May12_03_MC
export C3_SHLIB=../build_\$CMLIB/shlib:\$C3_SHLIB
export C3_SCRIPTS=/home/mccann/mcsuper/run/scripts_\$CMLIB
export USER_CLEOG=../pds/cleog_y1$type\_$run\_db19.pds
export USER_MCPASS2=../pds/mcpass2_y1$type\_$run\_db19.pds
rm -f \$USER_CLEOG
rm -f \$USER_MCPASS2
suez -f cleog.tcl
rm -f core
suez -f mcpass2.tcl
rm -f core
";
    }

    # y2s
    @runs = (129535, 129536, 129538, 129539, 129540, 129541, 129545,
	     129549, 129550, 129551, 129552, 129553, 129564, 129566,
	     129567, 129568, 129572, 129573, 129574, 129575, 129576) if $type eq "ggg";
    @runs = (129579, 129580, 129582, 129591, 129607, 129611, 129617) if $type eq "gggam";
    @runs = (129618, 129619, 129620, 129623, 129626, 129629, 129630) if $type eq "qq";

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

    # y3s
    @runs = (121916, 121917, 121918, 121920, 121924, 121925, 121927,
	     121928, 121929, 121930, 121932, 121933, 121936, 121939,
	     121940, 121943, 121944, 121946, 121948, 121949, 121950) if $type eq "ggg";
    @runs = (121951, 121952, 121953, 121962, 121963, 121965, 121966) if $type eq "gggam";
    @runs = (121968, 121969, 121970, 121972, 121973, 121974, 121975) if $type eq "qq";

    foreach $run (@runs) {
	open(RUN, "> y3$type\_$run.run");
	print RUN "#\$ -l sigmc=1
#\$ -o /cdat/tem/mccann/y3$type\_$run.log
#\$ -S /bin/bash
#\$ -j y

cd /home/mccann/mcsuper/run/
. /nfs/cleo3/scripts/cleo3defs
c3rel Mar04_04_MC
export C3_SHLIB=../build_SunOS/shlib:\$C3_SHLIB

export USER_RUN=$run
export USER_GEN=../pds/generator_y3$type\_$run.pds
export USER_DEC=y3$type.dec
export USER_EBEAM=5.1776
export USER_RES=10.3552
export USER_WIDE=0.0000263

rm -f \$USER_GEN

rm -f core
suez -f generate.tcl
rm -f core

c3rel Jun27_02_MC
export C3_SHLIB=../build_\$CMLIB/shlib:\$C3_SHLIB
export C3_SCRIPTS=/home/mccann/mcsuper/run/scripts_\$CMLIB
export USER_CLEOG=../pds/cleog_y3$type\_$run\_db16.pds
export USER_MCPASS2=../pds/mcpass2_y3$type\_$run\_db16.pds
rm -f \$USER_CLEOG
rm -f \$USER_MCPASS2
suez -f cleog.tcl
rm -f core
suez -f mcpass2.tcl
rm -f core
";
    }

}
