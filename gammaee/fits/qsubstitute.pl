#!/usr/local/bin/perl

require("grand_list.pl");

%gone = ();
open(GOS, "ls counting_scripts/go*.run |");
while (my $go = <GOS>) {
    $go =~ /go([0-9]+)\.run/;
    $gone{$1} = 1;
}

foreach $r (sort numly keys %run) {
    next if (defined($gone{$r}));

    do {
        $qstat = `qstat -u mccann | wc -l`;
        chop($qstat);

	if ($qstat >= 20) {
	    print "Waiting five minutes...\n";
	    sleep 300;
	}
    } while ($qstat >= 20);

    system("perl count.pl $r");
}
