#!/usr/local/bin/perl

foreach $run (

	      # evenruns
	      122091, 122133, 122430, 122832, 123817, 123853, 125176,
	      124684, 126488, 126870, 130427, 129572,

	      # oddruns
	      121969, 122634, 122808, 123013, 123592, 123638, 124708,
	      126521, 126531, 126906, 127318, 127418, 127955, 129674,
	      129850, 130316, 130268,

	      ) {
    
    if ($run >= 121339  &&  $run <= 122179) {$db = 16;}
    if ($run >= 122245  &&  $run <= 123304) {$db = 17;}
    if ($run >= 123314  &&  $run <= 124575) {$db = 18;}
    if ($run >= 124624  &&  $run <= 125416) {$db = 19;}
    if ($run >= 125428  &&  $run <= 126206) {$db = 20;}
    if ($run >= 126252  &&  $run <= 127545) {$db = 21;}
    if ($run >= 127550  &&  $run <= 128401) {$db = 22;}
    if ($run >= 128684  &&  $run <= 129223) {$db = 23;}
    if ($run >= 129257  &&  $run <= 129488) {$db = 24;}
    if ($run >= 129519  &&  $run <= 129865) {$db = 25;}
    if ($run >= 129897  &&  $run <= 130187) {$db = 26;}
    if ($run >= 130198  &&  $run <= 130630) {$db = 27;}
    if ($run >= 130676  &&  $run <= 131640) {$db = 28;}
    if ($run >= 131679  &&  $run <= 132285) {$db = 29;}
    if ($run >= 200520  &&  $run <= 200854) {$db = 30;}
    if ($run >= 200978  &&  $run <= 202101) {$db = 31;}
    if ($run >= 202126  &&  $run <= 203089) {$db = 32;}
    if ($run >= 203104  &&  $run <= 203634) {$db = 33;}
    if ($run >= 203912  &&  $run <= 204348) {$db = 34;}

    if ($db == 16) {$rel = "cleo3_Pass2_Jan30_2002";}
    if ($db == 17) {$rel = "cleo3_Pass2_Mar26_2002";}
    if ($db == 18 || $db == 23 || $db == 25 || $db == 27) {$rel = "Apr18_03_P2";}
    if ($db == 19 || $db == 22) {$rel = "Jan24_03_P2";}
    if ($db == 21) {$rel = "Nov04_02_P2";}

    $ea = "true";
    if ($db == 16 || $db == 17) {$ea = "false";}

#     open(RUN, "> db$run.run");
#     print RUN "#\$ -l u5
# #\$ -o /cdat/tem/mccann/db$run.log
# #\$ -S /bin/bash
# #\$ -j y

# cd /home/mccann/acceptance/run3/
# . /nfs/cleo3/scripts/cleo3defs
# c3rel Dec10_03

# export USER_DB=$db
# export USER_RUN=$run

# suez -f make_index.tcl
# rm -f core
# ";

    system("rm -f /cdat/tem/mccann/id$run.log");

    open(RUN2, "> id$run.run");
    print RUN2 "#\$ -l u5
#\$ -o /cdat/tem/mccann/id$run.log
#\$ -S /bin/bash
#\$ -j y

cd /home/mccann/acceptance/run3/
. /nfs/cleo3/scripts/cleo3defs
c3rel $rel

export USER_DB=$db
export USER_RUN=$run
export USER_EA=$ea
export USER_REL=$rel

rm -f ../rzn3/raw\$USER_RUN.pds
suez -f run_index.tcl
rm -f core

c3rel Dec10_03

suez -f trigger_only.tcl
rm -f core

suez -f ntuple.tcl
rm -f core
";
}

# foreach $run (

# # positron beamgas
# 126785,
# # electron beamgas
# 126828, 126920, 126922, 127014,
# # cosmic rays
# 128706, 128736, 128741, 128746, 128748, 128750, 128751,

# ) {

#     if ($run >= 121339  &&  $run <= 122179) {$db = 16;}
#     if ($run >= 122245  &&  $run <= 123304) {$db = 17;}
#     if ($run >= 123314  &&  $run <= 124575) {$db = 18;}
#     if ($run >= 124624  &&  $run <= 125416) {$db = 19;}
#     if ($run >= 125428  &&  $run <= 126206) {$db = 20;}
#     if ($run >= 126252  &&  $run <= 127545) {$db = 21;}
#     if ($run >= 127550  &&  $run <= 128401) {$db = 22;}
#     if ($run >= 128684  &&  $run <= 129223) {$db = 23;}
#     if ($run >= 129257  &&  $run <= 129488) {$db = 24;}
#     if ($run >= 129519  &&  $run <= 129865) {$db = 25;}
#     if ($run >= 129897  &&  $run <= 130187) {$db = 26;}
#     if ($run >= 130198  &&  $run <= 130630) {$db = 27;}
#     if ($run >= 130676  &&  $run <= 131640) {$db = 28;}
#     if ($run >= 131679  &&  $run <= 132285) {$db = 29;}
#     if ($run >= 200520  &&  $run <= 200854) {$db = 30;}
#     if ($run >= 200978  &&  $run <= 202101) {$db = 31;}
#     if ($run >= 202126  &&  $run <= 203089) {$db = 32;}
#     if ($run >= 203104  &&  $run <= 203634) {$db = 33;}
#     if ($run >= 203912  &&  $run <= 204348) {$db = 34;}

#     open(RUN3, "> id$run.run");
#     print RUN3 "#\$ -l u5
# #\$ -o /cdat/tem/mccann/id$run.log
# #\$ -S /bin/bash
# #\$ -j y

# cd /home/mccann/acceptance/run3/
# . /nfs/cleo3/scripts/cleo3defs
# c3rel Dec10_03

# export USER_DB=$db
# export USER_RUN=$run
# export USER_EA=false

# suez -f trigger_only.tcl
# rm -f core
# ";
# }
