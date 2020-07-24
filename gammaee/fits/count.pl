#!/usr/local/bin/perl

require("grand_list.pl");

$r = $ARGV[0];
die if (! defined($run{$r}));
$db = $run{$r}->[3];

open(RUN, "> counting_scripts/go$r.run");
print RUN "#\$ -l u5
#\$ -o /cdat/tem/mccann/counting_logs/r$r.log
#\$ -S /bin/bash
#\$ -j y

cd /home/mccann/fits/
. /nfs/cleo3/scripts/cleo3defs
c3rel Dec10_03

export USER_DB=$db
export USER_RUN=$r

echo \$USER_DB \$USER_RUN

suez -f count.tcl | tee /cdat/tem/mccann/counting_logs/tmp$r.log
rm -f core

export USER_GOODEVENTS=`fgrep ' \%\% SYSTEM-Processor.CountEvents: goodEvents' /cdat/tem/mccann/counting_logs/tmp$r.log | awk '{print \$4}'`
export USER_COSMICEVENTS=`fgrep ' \%\% SYSTEM-Processor.CountEvents: goodEvents' /cdat/tem/mccann/counting_logs/tmp$r.log | awk '{print \$6}'`
export USER_BGPEVENTS=`fgrep ' \%\% SYSTEM-Processor.CountEvents: goodEvents' /cdat/tem/mccann/counting_logs/tmp$r.log | awk '{print \$8}'`
export USER_BGEEVENTS=`fgrep ' \%\% SYSTEM-Processor.CountEvents: goodEvents' /cdat/tem/mccann/counting_logs/tmp$r.log | awk '{print \$10}'`
rm -f /cdat/tem/mccann/counting_logs/tmp$r.log

echo '\$goodEvents{$r} =' \$USER_GOODEVENTS >> goodEvents.pl
echo '\$cosmicEvents{$r} =' \$USER_COSMICEVENTS >> cosmicEvents.pl
echo '\$bgpEvents{$r} =' \$USER_BGPEVENTS >> bgpEvents.pl
echo '\$bgeEvents{$r} =' \$USER_BGEEVENTS >> bgeEvents.pl

exit
";
close(RUN);

system("qsub counting_scripts/go$r.run");
