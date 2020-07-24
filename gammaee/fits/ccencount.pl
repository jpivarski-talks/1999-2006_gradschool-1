#!/usr/local/bin/perl

require("grand_list.pl");
require("energy.pl");
require("beamspot.pl");

$r = $ARGV[0];
die if (! defined($run{$r}));
$db = $run{$r}->[3];

$ea = "true";
if ($db == 16) {$ea = "false"; $rel = "cleo3_Pass2_Jan30_2002";}
elsif ($db == 17) {$ea = "false"; $rel = "cleo3_Pass2_Mar26_2002";}
elsif ($db == 18) {$rel = "Apr18_03_P2";}
elsif ($db == 19) {$rel = "Jan24_03_P2";}
elsif ($db == 21) {$rel = "Nov04_02_P2";}
elsif ($db == 22) {$rel = "Jan24_03_P2";}
elsif ($db == 23) {$rel = "Apr18_03_P2";}
elsif ($db == 25) {$rel = "Apr18_03_P2";}
elsif ($db == 27) {$rel = "Apr18_03_P2";}

open(RUN, "> ccencounting_scripts/ccg$r.run");
print RUN "#\$ -l u5
#\$ -o /cdat/tem/mccann/ccencounting_logs/r$r.log
#\$ -S /bin/bash
#\$ -j y

cd /home/mccann/fits/
. /nfs/cleo3/scripts/cleo3defs
c3rel $rel

export USER_DB=$db
export USER_RUN=$r
export USER_EA=$ea
export USER_REL=$rel
export USER_BSX=$bsx{$r}
export USER_BSY=$bsy{$r}
export USER_BSZ=$bsz{$r}
export USER_EBEAM=$energy{$r}

suez -f ccencount.tcl | tee /cdat/tem/mccann/ccencounting_logs/tmp$r.log
rm -f core
fgrep \"passedAllButccen\" /cdat/tem/mccann/ccencounting_logs/tmp$r.log >> allbutccen.log
rm -f /cdat/tem/mccann/ccencounting_logs/tmp$r.log

exit
";
close(RUN);

system("qsub ccencounting_scripts/ccg$r.run");
