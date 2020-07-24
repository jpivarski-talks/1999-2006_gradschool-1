#!/usr/local/bin/perl

# y1s
foreach $rel ("Jun27_02_MC", "Jun13_03_MC", "May12_03_MC") {
    if ($rel eq "Jun27_02_MC") {
	@runs = (123610, 123611, 123612, 123615, 123616, 123617, 123618,
		 123619, 123620, 123621, 123623, 123624, 123631, 123632,);
    }
    elsif ($rel eq "Jun13_03_MC") {
	@runs = (123633, 123635, 123636, 123637, 123638, 123639, 123640,
		 123641, 123643, 123644, 123645, 123646, 123647, 123648,);
    }
    elsif ($rel eq "May12_03_MC") {
	@runs = (123650, 123651, 123652, 123653, 123654, 123656, 123658,
		 123659, 123665, 123670, 123673, 123674, 123675, 123678,);
    }
    else {die;}
    foreach $run (@runs) {
	open(RUN, "> y1s_$rel/mc$run.run");
	print RUN "#\$ -l sigmc=1
#\$ -o /cdat/tem/mccann/mc$run\_$rel.log
#\$ -S /bin/bash
#\$ -j y

cd /home/mccann/acceptance/runmc
. /nfs/cleo3/scripts/cleo3defs
c3rel $rel

export USER_RUN=$run
export USER_GEN=../remc2/y1s/generator_\$USER_RUN.pds
export USER_CLEOG=../remc3/y1s/$rel/cleog_\$USER_RUN.pds
export USER_MCPASS2=../remc3/y1s/$rel/mcpass2_\$USER_RUN.pds
export USER_DEC=ups1s.dec
export USER_EBEAM=4.73015
export USER_RES=9.46030
export USER_WIDE=0.0000525
export C3_SHLIB=../build_$rel/shlib:\$C3_SHLIB
export C3_SCRIPTS=/home/mccann/acceptance/runmc/scripts_$rel

rm -f \$USER_CLEOG
rm -f \$USER_MCPASS2

rm -f core
suez -f cleog.tcl
rm -f core
suez -f mcpass2.tcl
rm -f core
";
    }
}

# y2s
foreach $rel ("Apr16_03_MC", "May12_03_MC", "Jun13_03_MC") {
    if ($rel eq "Apr16_03_MC") {
	@runs = (129535, 129536, 129538, 129539, 129540, 129541, 129545,
                 129549, 129550, 129551, 129552, 129553, 129564, 129566,);
    }
    elsif ($rel eq "May12_03_MC") {
	@runs = (129567, 129568, 129572, 129573, 129574, 129575, 129576,
		 129579, 129580, 129582, 129591, 129607, 129611, 129617,);
    }
    elsif ($rel eq "Jun13_03_MC") {
	@runs = (129618, 129619, 129620, 129623, 129626, 129629, 129630,
		 129631, 129632, 129633, 129635, 129637, 129638, 129641,);
    }
    else {die;}
    foreach $run (@runs) {
	open(RUN, "> y2s_$rel/mc$run.run");
	print RUN "#\$ -l sigmc=1
#\$ -o /cdat/tem/mccann/mc$run\_$rel.log
#\$ -S /bin/bash
#\$ -j y

cd /home/mccann/acceptance/runmc
. /nfs/cleo3/scripts/cleo3defs
c3rel $rel

export USER_RUN=$run
export USER_GEN=../remc2/y2s/generator_\$USER_RUN.pds
export USER_CLEOG=../remc3/y2s/$rel/cleog_\$USER_RUN.pds
export USER_MCPASS2=../remc3/y2s/$rel/mcpass2_\$USER_RUN.pds
export USER_DEC=ups2s.dec
export USER_EBEAM=5.01163
export USER_RES=10.02326
export USER_WIDE=0.000044
export C3_SHLIB=../build_$rel/shlib:\$C3_SHLIB
export C3_SCRIPTS=/home/mccann/acceptance/runmc/scripts_$rel

rm -f \$USER_CLEOG
rm -f \$USER_MCPASS2

rm -f core
suez -f cleog.tcl
rm -f core
suez -f mcpass2.tcl
rm -f core
";
    }
}

# y3s
foreach $rel ("Jun27_02_MC") {
    if ($rel eq "Jun27_02_MC") {
	@runs = (121916, 121917, 121918, 121920, 121924, 121925, 121927,
		 121928, 121929, 121930, 121932, 121933, 121936, 121939,);
    }
    else {die;}
    foreach $run (@runs) {
	open(RUN, "> y3s_$rel/mc$run.run");
	print RUN "#\$ -l sigmc=1
#\$ -o /cdat/tem/mccann/mc$run\_$rel.log
#\$ -S /bin/bash
#\$ -j y

cd /home/mccann/acceptance/runmc
. /nfs/cleo3/scripts/cleo3defs
c3rel $rel

export USER_RUN=$run
export USER_GEN=../remc2/y3s/generator_\$USER_RUN.pds
export USER_CLEOG=../remc3/y3s/$rel/cleog_\$USER_RUN.pds
export USER_MCPASS2=../remc3/y3s/$rel/mcpass2_\$USER_RUN.pds
export USER_DEC=ups3s.dec
export USER_EBEAM=5.1776
export USER_RES=10.3552
export USER_WIDE=0.0000263
export C3_SHLIB=../build_$rel/shlib:\$C3_SHLIB
export C3_SCRIPTS=/home/mccann/acceptance/runmc/scripts_$rel

rm -f \$USER_CLEOG
rm -f \$USER_MCPASS2

rm -f core
suez -f cleog.tcl
rm -f core
suez -f mcpass2.tcl
rm -f core
";
    }
}
