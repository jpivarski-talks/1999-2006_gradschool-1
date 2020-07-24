#!/usr/local/bin/perl

foreach $db (21, 22, 23, 25, 27) {
    if ($db == 21) {$first = 126252;  $last = 127545;}
    if ($db == 22) {$first = 127550;  $last = 128401;}
    if ($db == 23) {$first = 128684;  $last = 129223;}
    if ($db == 25) {$first = 129519;  $last = 129865;}
    if ($db == 27) {$first = 130198;  $last = 130630;}

    $min = $first;
    do {
	$max = $min + 10;
	if ($max > $last) {$max = $last;}

	$name = "cas$min\_$max";

	open(RUN, "> runcascades/$name.run");
	print RUN "#\$ -l u5
#\$ -o /cdat/tem/mccann/$name.log
#\$ -S /bin/bash
#\$ -j y

cd /home/mccann/acceptance/run5/
. /nfs/cleo3/scripts/cleo3defs
c3rel Dec10_03

export USER_NAME=$name
export USER_DB=$db
export USER_RUNMIN=$min
export USER_RUNMAX=$max

suez -f fillcascades.tcl
";
            close(RUN);

            $min = $max + 1;
    } while ($min < $last);
} # foreach db
