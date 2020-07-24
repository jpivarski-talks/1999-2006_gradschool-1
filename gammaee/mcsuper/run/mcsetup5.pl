#!/usr/local/bin/perl

foreach $type ("pho3") {

    # y2s
    @runs = (129535, 129536, 129538, 129539, 129540, 129541, 129545) if $type eq "pho3";

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
    @runs = (121916, 121917, 121918, 121920, 121924, 121925, 121927) if $type eq "pho3";

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
