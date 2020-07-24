#!/usr/local/bin/perl

require("/home/mccann/fits/grand_list.pl");

foreach $r (keys %run) {
    do {
        $qstat = `qstat -u mccann | wc -l`;
        chop($qstat);

	if ($qstat >= 30) {
	    print "Waiting five minutes...\n";
	    sleep 300;
	}
    } while ($qstat >= 30);

    system("qsub daf9/runs/R$r.run");
} # end foreach run


